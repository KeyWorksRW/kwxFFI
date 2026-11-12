/////////////////////////////////////////////////////////////////////////////
// Purpose:   Julia FFI code generator using ccall bindings
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "lang_julia.h"

#include "../file_writer.h"
#include "julia_type_map.h"
#include "lang_common.h"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <print>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// NOLINTBEGIN(readability-magic-string)

namespace fs = std::filesystem;

// Classes whose concrete struct and constructor are skipped: they are declared abstractly in
// the hand-written core/types.jl, or already have a struct there.  Their methods are still
// emitted so they dispatch polymorphically, which is why the names are not wrapped classes
// but consumer-provided types.
static const std::unordered_set<std::string> kSkipStruct = {
    "wxObject", "wxEvtHandler", "wxWindow", "wxControl", "wxTopLevelWindow", "wxSizer",
    "wxEvent"  // struct wxEvent defined in core/types.jl
};

// Classes excluded from idiomatic generation entirely.  Only the string helper type is
// excluded, because core/strings.jl manages its lifecycle.
static const std::unordered_set<std::string> kSkipClass = {
    "wxString"  // lifecycle managed by core/strings.jl
};

// Method names that already exist in Base.  A plain `function length(obj::wxTempFile)` in a
// module creates a new module-local `length` that shadows Base.length inside the module; the
// same name must be qualified as Base.length so it extends the generic function instead.
static const std::unordered_set<std::string> kBaseMethodNames = {
    "append!",  "bind",     "broadcast!", "close",  "compile",       "contains",   "copy",
    "copy!",    "count",    "delete!",    "detach", "display",       "dump",       "eof",
    "error",    "float",    "flush",      "get!",   "get_extension", "get_offset", "insert!",
    "length",   "lock",     "mkdir",      "open",   "parse",         "pause",      "peek",
    "position", "prepend!", "print",      "pwd",    "read",          "read!",      "rename",
    "replace",  "replace!", "resize!",    "run",    "seek",          "show",       "size",
    "sort!",    "time",     "touch",      "unlock", "wait",          "write",      "yield"
};
// One entry in a class file's duplicate-dispatch guard: the C symbol that claimed a Julia dispatch
// signature, and the Julia name the wrapper was emitted under.
struct JuliaEmittedSignature
{
    std::string c_name;
    std::string julia_name;
};

// Run-wide tallies for the two duplicate-dispatch populations.  Each collision is detected by a
// per-class-file map; these counters exist so GenerateIdiomaticClasses can report all of them in
// one aggregate line instead of one line per case.
struct JuliaDuplicateTally
{
    size_t inherent_mixin_duplicates { 0 };
    size_t recovered_methods { 0 };
    size_t recovered_factories { 0 };
};

static JuliaDuplicateTally s_duplicate_tally;

// Build a C function name from a FunctionDecl.

// Groups the three string identifiers needed by EmitCCallWrapper.
struct CCallInfo
{
    std::string julia_name;
    std::string c_name;
    std::string return_type;
};

// Emit a Julia ccall wrapper for a function.
// Output format:
//   function name(param::Type, ...)
//       ccall((:c_name, libkwxFFI), RetType, (ParamTypes...), params...)
//   end
static void EmitCCallWrapper(std::ostream& output, const CCallInfo& info,
                             const std::vector<JuliaParam>& params)
{
    if (params.empty())
    {
        // Zero-argument function: use compact form
        output << info.julia_name << "() = ccall((:" << info.c_name << ", libkwxFFI), "
               << info.return_type << ", ())\n";
        return;
    }

    // Multi-argument function
    output << "function " << info.julia_name << "(";
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (i > 0)
        {
            output << ", ";
        }
        output << params[i].name << "::" << params[i].julia_type;
    }
    output << ")\n";

    // ccall line
    output << "    ccall((:" << info.c_name << ", libkwxFFI), " << info.return_type << ",\n";

    // Type tuple
    output << "        (";
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (i > 0)
        {
            output << ", ";
        }
        output << params[i].julia_type;
    }
    // Julia requires trailing comma for single-element tuples
    if (params.size() == 1)
    {
        output << ",";
    }
    output << "),\n";

    // Argument names
    output << "        ";
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (i > 0)
        {
            output << ", ";
        }
        output << params[i].name;
    }
    output << ")\n";

    output << "end\n";
}

// Emit a ccall wrapper from a FunctionDecl.
static void EmitFunctionWrapper(std::ostream& output, const FunctionDecl& func)
{
    const std::string cName = CFuncName(func);
    const std::string retType = JuliaReturnType(func.return_type, func.return_macro);

    std::vector<JuliaParam> jParams;
    for (const auto& param: func.params)
    {
        std::vector<JuliaParam> expanded = ExpandParamToJulia(param);
        for (auto& julia_param: expanded)
        {
            julia_param.name = JuliaEscapeName(julia_param.name);
            jParams.push_back(std::move(julia_param));
        }
    }

    EmitCCallWrapper(output, { .julia_name = cName, .c_name = cName, .return_type = retType },
                     jParams);
}

// Check if a function declaration looks valid (skip malformed ones).

// -------------------------------------------------------------------------
// Idiomatic-layer helpers
// -------------------------------------------------------------------------

// Strip wx/kwx prefix: "wxButton" → "Button"
static std::string StripWxPrefix(const std::string& name)
{
    if (name.size() > WX_PREFIX.length() && name.starts_with(WX_PREFIX) &&
        std::isupper(static_cast<unsigned char>(name[WX_PREFIX.length()])))
    {
        return name.substr(WX_PREFIX.length());
    }
    if (name.size() > KWX_PREFIX.length() && name.starts_with(KWX_PREFIX) &&
        std::isupper(static_cast<unsigned char>(name[KWX_PREFIX.length()])))
    {
        return name.substr(KWX_PREFIX.length());
    }
    return name;
}

// CamelCase → snake_case (matches Rust/Go helper).

// True if the function return type is void.
[[nodiscard]] static bool IsVoidReturn(const std::string& return_type,
                                       const std::string& return_macro)
{
    std::ignore = return_macro;
    return return_type.empty() || return_type == "void";
}

// True when a non-constructor method's first parameter is TClass(ClassName) for the method's
// own class.  A mixin (wxTextEntry, wxItemContainer, wxComboPopup) declares its receiver this
// way instead of TSelf, so the parameter is the receiver and must not be emitted as an
// argument.  The parser sets has_self for genuine TSelf receivers, so a real method's first
// parameter is never mistaken for the receiver.
[[nodiscard]] static bool IsJuliaPseudoSelf(const FunctionDecl& func)
{
    if (func.is_constructor || func.has_self || func.class_name.empty() || func.params.empty())
    {
        return false;
    }
    const Param& first_param = func.params.front();
    return first_param.macro_name == "TClass" && first_param.macro_arg == func.class_name;
}

// True when a class passes its object through an explicit TClass(OwnClass) first parameter
// instead of TSelf for most of its methods (the mixin shape: wxTextEntry, wxItemContainer,
// wxComboPopup).  Only for such a class does a leading TClass(own class) parameter denote the
// receiver; elsewhere it is an ordinary argument (wxLog_SetActiveTarget takes the new target).
[[nodiscard]] static bool JuliaUsesExplicitReceiver(const ClassInfo& class_info)
{
    size_t receiver_count = 0;
    size_t method_count = 0;
    for (const auto& method: class_info.methods)
    {
        if (!IsValidFunction(method) || method.is_constructor || method.is_destructor)
        {
            continue;
        }
        if (method.has_self)
        {
            return false;  // the class names its receiver with TSelf
        }
        ++method_count;
        if (IsJuliaPseudoSelf(method))
        {
            ++receiver_count;
        }
    }
    return receiver_count != 0 && (receiver_count * 2U) > method_count;
}

// True when a destructor's only parameter is the receiver (TSelf, or TClass of its own
// class).  A method merely named "Delete" that takes an index (wxItemContainer_Delete) is an
// ordinary method, so it is re-emitted on a mixin's consumers like any other.
[[nodiscard]] static bool IsJuliaTrueDestructor(const FunctionDecl& func)
{
    if (!func.is_destructor || func.params.empty())
    {
        return false;
    }
    for (const auto& param: func.params)
    {
        if (param.macro_name == "TSelf")
        {
            continue;
        }
        if (param.macro_name == "TClass" && param.macro_arg == func.class_name)
        {
            continue;
        }
        return false;
    }
    return true;
}

// Walk parent_map to find the nearest Julia abstract parent type.
// Returns one of: wxObject wxEvtHandler wxWindow wxControl wxTopLevelWindow wxSizer
// (These must match the abstract types declared in the Julia repo's types.jl)
static std::string
    JuliaAbstractParent(const std::string& class_name,
                        const std::unordered_map<std::string, std::string>& parent_map)
{
    static const std::unordered_set<std::string> kAbstract = { "wxObject",         "wxEvtHandler",
                                                               "wxWindow",         "wxControl",
                                                               "wxTopLevelWindow", "wxSizer" };
    std::string current = class_name;
    std::set<std::string> visited;
    while (true)
    {
        const std::unordered_map<std::string, std::string>::const_iterator iter =
            parent_map.find(current);
        if (iter == parent_map.end())
        {
            break;
        }
        const std::string& parent = iter->second;
        if (kAbstract.contains(parent))
        {
            return parent;
        }
        if (visited.contains(parent))
        {
            break;  // cycle guard
        }
        visited.insert(current);
        current = parent;
    }
    return "wxObject";  // fallback
}

// Output filename for a class: "wxButton" → "wxbutton_gen.jl"
static std::string JuliaClassFileName(const std::string& class_name)
{
    std::string lower_name;
    for (const char char_val: class_name)
    {
        lower_name += static_cast<char>(std::tolower(static_cast<unsigned char>(char_val)));
    }
    return lower_name + "_gen.jl";
}

// -------------------------------------------------------------------------
// Idiomatic parameter conversion
// -------------------------------------------------------------------------

// A single idiomatic Julia parameter and its call expression.
struct JuliaIdiomParam
{
    std::string decl;       // "name::Type" — empty for skipped params
    std::string call_expr;  // expression passed to KwxFFI call
    std::string pre_call;   // statement(s) emitted before the call
    std::string post_call;  // statement(s) emitted in the call's finally block
    std::string preserve;   // variable kept alive across the call with GC.@preserve
};

// Convert one Param to zero or more idiomatic Julia parameters.
static std::vector<JuliaIdiomParam> ConvertToIdiomParams(const Param& param, bool in_constructor)
{
    std::vector<JuliaIdiomParam> result;

    // Self param → handled by typed receiver; skip.
    if (param.macro_name == "TSelf")
    {
        return result;
    }

    // Geometry expansion macros → multiple Cint params.
    if (param.macro_name == "TPoint" || param.macro_name == "TSize" ||
        param.macro_name == "TRect" || param.macro_name == "TVector")
    {
        for (auto& n: JuliaSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = JuliaEscapeName(n);
            result.push_back({ escaped + "::Integer", "Cint(" + escaped + ")", "", "" });
        }
        return result;
    }

    if (param.macro_name == "TPointLong" || param.macro_name == "TSizeLong" ||
        param.macro_name == "TRectLong" || param.macro_name == "TVectorLong")
    {
        for (auto& n: JuliaSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = JuliaEscapeName(n);
            result.push_back({ escaped + "::Integer", "Clong(" + escaped + ")", "", "" });
        }
        return result;
    }

    // Output geometry → pass through as Ref{Int32}.
    if (param.macro_name == "TPointOut" || param.macro_name == "TSizeOut" ||
        param.macro_name == "TRectOut" || param.macro_name == "TVectorOut")
    {
        for (auto& n: JuliaSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = JuliaEscapeName(n);
            result.push_back({ escaped + "::Ref{Int32}", escaped, "", "" });
        }
        return result;
    }

    // Output long geometry → pass through as Ref{Clong}.
    if (param.macro_name == "TPointOutLong" || param.macro_name == "TSizeOutLong")
    {
        for (auto& n: JuliaSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = JuliaEscapeName(n);
            result.push_back({ escaped + "::Ref{Clong}", escaped, "", "" });
        }
        return result;
    }

    if (param.macro_name == "TColorRGB")
    {
        for (auto& n: JuliaSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = JuliaEscapeName(n);
            result.push_back({ escaped + "::Integer", "Cuchar(" + escaped + ")", "", "" });
        }
        return result;
    }

    // Array types: count + pointer.
    if (param.macro_name == "TArrayString" || param.macro_name == "TArrayInt" ||
        param.macro_name == "TByteString" || param.macro_name == "TByteStringLazy")
    {
        const std::vector<std::string> names = JuliaSplitMacroArg(param.macro_arg);
        if (names.size() < 2)
        {
            std::println(stderr, "Warning: {}({}) expected 2 names, got {}", param.macro_name,
                         param.macro_arg, names.size());
            return result;
        }
        result.push_back({ names[0] + "::Integer", "Cint(" + names[0] + ")", "", "" });
        result.push_back({ names[1] + "::Ptr{Cvoid}", names[1], "", "" });
        return result;
    }

    // Opaque output arrays → Ptr{Cvoid}.
    if (param.macro_name == "TArrayObjectOutVoid" || param.macro_name == "TArrayIntOutVoid" ||
        param.macro_name == "TArrayIntPtrOutVoid" || param.macro_name == "TArrayStringOutVoid" ||
        param.macro_name == "TByteStringOut" || param.macro_name == "TByteStringLazyOut")
    {
        std::string name = param.param_name.empty() ? "arr" : param.param_name;
        name = JuliaEscapeName(name);
        result.push_back({ name + "::Ptr{Cvoid}", name, "", "" });
        return result;
    }

    // Class pointer params.
    if (param.macro_name == "TClass" || param.macro_name == "TClassRef")
    {
        // TClass(wxString): the callee takes an owned wxString*.  The temporary is not a
        // conversion — the bytes are already UTF-8 — it is the object's lifetime, so it is
        // created here and released in the call's finally block.
        if (param.macro_arg == "wxString")
        {
            std::string name = param.param_name.empty() ? "str" : param.param_name;
            name = JuliaEscapeName(name);
            const std::string wx_str = name + "_ws";
            result.push_back({ name + "::AbstractString", wx_str + ".ptr",
                               wx_str + " = wxString(" + name + ")", "Base.delete!(" + wx_str + ")",
                               "" });
            return result;
        }

        std::string name = param.param_name.empty() ? "arg" : param.param_name;
        name = JuliaEscapeName(name);
        // Avoid clash with the method receiver which is always named "obj".
        if (name == "obj")
        {
            name = "arg_ptr";
        }
        if (in_constructor && name == "parent")
        {
            // Nullable parent window.
            result.push_back({ "parent::Union{wxWindow, Nothing}", "parent_ptr",
                               "parent_ptr = isnothing(parent) ? C_NULL : parent.ptr", "" });
        }
        else
        {
            result.push_back({ name + "::Ptr{Cvoid}", name, "", "" });
        }
        return result;
    }

    // TString is TChar* (kwx_types.h:160) — raw UTF-8 bytes needing no wrapper, no allocation
    // and no conversion.  The string stays alive across the ccall via GC.@preserve.
    if (param.raw_type == "TString" || param.macro_name == "TString")
    {
        std::string name = param.param_name.empty() ? "str" : param.param_name;
        name = JuliaEscapeName(name);
        result.push_back({ name + "::AbstractString", "Base.unsafe_convert(Cstring, " + name + ")",
                           "", "", name });
        return result;
    }

    // Opaque string void pointer.
    if (param.raw_type == "TStringVoid" || param.macro_name == "TStringVoid")
    {
        std::string name = param.param_name.empty() ? "str" : param.param_name;
        name = JuliaEscapeName(name);
        result.push_back({ name + "::Ptr{Cvoid}", name, "", "" });
        return result;
    }

    // String output buffer: a byte vector the callee writes into.
    if (param.raw_type == "TStringOut")
    {
        std::string name = param.param_name.empty() ? "buf" : param.param_name;
        name = JuliaEscapeName(name);
        result.push_back({ name + "::AbstractVector{UInt8}",
                           "Base.unsafe_convert(Ptr{UInt8}, " + name + ")", "", "", name });
        return result;
    }

    // Scalar output / in-out pointer.
    if (ScalarPointerInfo scalar_pointer; LookupScalarPointer(param, scalar_pointer))
    {
        std::string name = param.param_name.empty() ? "arg" : param.param_name;
        name = JuliaEscapeName(name);
        result.push_back({ name + "::" + JuliaScalarRefType(scalar_pointer.c_type), name, "", "" });
        return result;
    }

    // Bool pointer (output parameter).
    if (param.raw_type == "TBool*")
    {
        std::string name = param.param_name.empty() ? "flag" : param.param_name;
        name = JuliaEscapeName(name);
        result.push_back({ name + "::Ref{Bool}", name, "", "" });
        return result;
    }

    // Bool.
    if (param.macro_name == "TBool" || param.raw_type == "TBool" || param.raw_type == "TBoolInt")
    {
        std::string name = param.param_name.empty() ? "flag" : param.param_name;
        name = JuliaEscapeName(name);
        result.push_back({ name + "::Bool", "Cint(" + name + ")", "", "" });
        return result;
    }

    // Closure/callback function pointer.
    if (param.macro_name == "TClosureFun" || param.raw_type == "TClosureFun")
    {
        std::string name = param.param_name.empty() ? "fn" : param.param_name;
        name = JuliaEscapeName(name);
        result.push_back({ name + "::Ptr{Cvoid}", name, "", "" });
        return result;
    }

    // Plain C types.
    std::string name = param.param_name.empty() ? "arg" : param.param_name;
    name = JuliaEscapeName(name);
    if (name == "obj")
    {
        name = "arg";  // avoid clash with method receiver
    }
    const std::string& raw_type = param.raw_type;

    if (raw_type == "double")
    {
        result.push_back({ name + "::Float64", "Cdouble(" + name + ")", "", "" });
    }
    else if (raw_type == "float")
    {
        result.push_back({ name + "::Float32", "Cfloat(" + name + ")", "", "" });
    }
    else if (raw_type == "TInt64" || raw_type == "int64_t")
    {
        result.push_back({ name + "::Int64", "Clonglong(" + name + ")", "", "" });
    }
    else if (raw_type == "long")
    {
        result.push_back({ name + "::Integer", "Clong(" + name + ")", "", "" });
    }
    else if (raw_type == "time_t")
    {
        result.push_back({ name + "::Integer", "Clonglong(" + name + ")", "", "" });
    }
    else if (raw_type == "unsigned" || raw_type == "unsigned int")
    {
        result.push_back({ name + "::Integer", "Cuint(" + name + ")", "", "" });
    }
    else if (raw_type == "unsigned long")
    {
        result.push_back({ name + "::Integer", "Culong(" + name + ")", "", "" });
    }
    else if (raw_type == "wxUIntPtr" || raw_type == "uintptr_t")
    {
        result.push_back({ name + "::Integer", "Csize_t(" + name + ")", "", "" });
    }
    else if (raw_type == "TChar")
    {
        result.push_back({ name + "::Integer", "Cchar(" + name + ")", "", "" });
    }
    else if (raw_type == "TUInt8")
    {
        result.push_back({ name + "::Integer", "Cuchar(" + name + ")", "", "" });
    }
    else if (raw_type == "size_t")
    {
        result.push_back({ name + "::Integer", "Csize_t(" + name + ")", "", "" });
    }
    else if (raw_type.find('*') != std::string::npos)
    {
        result.push_back({ name + "::Ptr{Cvoid}", name, "", "" });
    }
    else
    {
        result.push_back({ name + "::Integer", "Cint(" + name + ")", "", "" });  // int + fallback
    }

    return result;
}

// The type half of a Julia parameter declaration ("x::Integer" → "Integer").  Parameter
// names are irrelevant to dispatch, so this is what duplicate-signature detection compares.
[[nodiscard]] static std::string JuliaParamType(const std::string& decl)
{
    const std::size_t separator = decl.find("::");
    return separator == std::string::npos ? decl : decl.substr(separator + 2);
}

// Build the KwxFFI return expression for a function call string.
static std::string JuliaReturnExpr(const FunctionDecl& func, const std::string& call,
                                   const std::unordered_set<std::string>& wrapped_classes)
{
    if (func.return_type == "TBool" || func.return_type == "TBoolInt")
    {
        return call + " != 0";
    }
    if (func.return_macro == "TClass" || func.return_macro == "TSelf" ||
        func.return_macro == "TClassRef")
    {
        const std::string type_name = func.return_arg.empty() ? func.class_name : func.return_arg;
        if (type_name == "wxString")
        {
            // Owned refcounted buffer: copy the text, then release the C++ object.
            return "_wx_take_wxstring(" + call + ")";
        }
        if (type_name == "wxEvent")
        {
            // The only kSkipStruct type that is a concrete struct in types_gen.jl.
            return "wxEvent(" + call + ")";
        }
        // A wrapped class gets a typed wrapper; anything else (wxPoint, wxArrayInt, an abstract
        // root) stays a raw pointer because no struct exists to construct.
        if (!type_name.empty() && !kSkipStruct.contains(type_name) &&
            wrapped_classes.contains(type_name))
        {
            return "_wx_wrap(" + type_name + ", " + call +
                   (func.returns_owned ? "; owned = true)" : ")");
        }
        return call;  // Ptr{Cvoid}
    }
    if (func.return_type == "TString" || func.return_type == "TStringOut")
    {
        // The C side strdup's the buffer, so copy it and free the original.
        return "_wx_take_cstring(" + call + ")";
    }
    if (func.return_type == "TStringVoid")
    {
        return call;  // opaque void*, no ownership contract
    }
    if (func.return_type == "int" || func.return_type == "TArrayLen" ||
        func.return_type == "TByteStringLen")
    {
        return "Int(" + call + ")";
    }
    if (func.return_type == "double")
    {
        return "Float64(" + call + ")";
    }
    if (func.return_type == "float")
    {
        return "Float32(" + call + ")";
    }
    if (func.return_type == "long")
    {
        return "Int(" + call + ")";
    }
    if (func.return_type == "time_t")
    {
        return "Int64(" + call + ")";
    }
    if (func.return_type == "wxUIntPtr" || func.return_type == "uintptr_t")
    {
        return "UInt(" + call + ")";
    }
    if (func.return_type == "TInt64" || func.return_type == "int64_t")
    {
        return "Int64(" + call + ")";
    }
    // Pointers, void*, and anything else: return as-is.
    return call;
}

// Emit one idiomatic Julia method (non-constructor, non-duplicate-name guard
// is the caller's responsibility).
//
// julia_cls is the type the receiver is annotated with: the method's own class normally, or the
// consumer class when a mixin method is re-emitted through a class that consumes it.
// explicit_receiver is true when the defining class names its receiver with a leading
// TClass(own class) parameter instead of TSelf (the mixin shape).
// wrapped_classes holds every type with a generated struct, so a class return can be wrapped.
// emitted maps each Julia dispatch signature already written in this file to the C symbol and
// Julia name that produced it; a repeated signature must be skipped or renamed because method
// overwriting is a hard error during precompilation.
static bool EmitIdiomaticMethod(std::ostream& output, const FunctionDecl& func,
                                const std::string& julia_cls, bool explicit_receiver,
                                const std::unordered_set<std::string>& wrapped_classes,
                                std::unordered_map<std::string, JuliaEmittedSignature>& emitted)
{
    if (!IsValidFunction(func) || (func.is_constructor && !func.has_self))
    {
        return false;
    }

    // A mixin declares its receiver as TClass(own class); it is the receiver, not an argument.
    const bool pseudo_self = explicit_receiver && IsJuliaPseudoSelf(func);

    // Only a method that takes nothing but its receiver is a real destructor; Delete(index) on
    // wxItemContainer is an ordinary method and must keep its argument.
    const bool is_true_destructor = func.is_destructor && IsJuliaTrueDestructor(func);
    bool is_void = IsVoidReturn(func.return_type, func.return_macro);

    // A TClassDef block declares both instance methods (TSelf receiver) and static functions
    // (no receiver at all), e.g. wxNumberFormatter_GetThousandsSeparator.  A function without
    // a receiver must be emitted as a module-level function; giving it one would pass an
    // extra argument the ccall signature does not accept.
    const bool has_self_param = std::ranges::any_of(func.params,
                                                    [](const Param& param)
                                                    {
                                                        return param.macro_name == "TSelf";
                                                    });
    const bool has_receiver = has_self_param || pseudo_self || is_true_destructor;

    // Snake-case method name; add ! for void (mutating) methods.  Destructors extend Base,
    // otherwise they land in KwxFFI and a caller in Main gets Base.delete! instead.  A
    // receiver-less function keeps its C symbol name: the snake-case name would collide across
    // classes (get(), get_current(), find(), ...) and a module-wide duplicate method fails
    // precompilation, while the C symbol is unique by construction (dedupe removed repeats).
    std::string method_name;
    if (is_true_destructor)
    {
        method_name = "Base.delete!";
        is_void = true;
    }
    else if (!has_receiver)
    {
        method_name = CFuncName(func);
    }
    else
    {
        const std::string snake = JuliaEscapeName(ToSnakeCase(func.method_name));
        method_name = snake + (is_void ? "!" : "");
        // Extend the existing Base function rather than shadowing it inside the module.
        if (kBaseMethodNames.contains(method_name))
        {
            method_name = "Base." + method_name;
        }
    }
    if (method_name.empty())
    {
        std::println(stderr, "Warning: {}_{} produced an empty Julia method name; skipped",
                     func.class_name, func.method_name);
        return false;
    }

    // Build idiomatic param list (skip the receiver parameter).
    std::vector<std::vector<JuliaIdiomParam>> param_groups;
    bool has_post_calls = false;
    std::string preserve_names;
    std::string signature = method_name + "(";
    bool first_signature_param = true;
    if (has_receiver)
    {
        signature += julia_cls;
        first_signature_param = false;
    }
    bool skipped_receiver = !pseudo_self;
    for (const auto& param: func.params)
    {
        if (param.macro_name == "TSelf")
        {
            continue;
        }
        if (!skipped_receiver && param.macro_name == "TClass" && param.macro_arg == func.class_name)
        {
            skipped_receiver = true;  // the mixin's TClass(own class) receiver
            continue;
        }
        std::vector<JuliaIdiomParam> group = ConvertToIdiomParams(param, false);
        for (const auto& julia_param: group)
        {
            if (!julia_param.decl.empty())
            {
                if (!first_signature_param)
                {
                    signature += ", ";
                }
                signature += JuliaParamType(julia_param.decl);
                first_signature_param = false;
            }
            if (!julia_param.post_call.empty())
            {
                has_post_calls = true;
            }
            if (!julia_param.preserve.empty())
            {
                preserve_names += " " + julia_param.preserve;
            }
        }
        param_groups.push_back(std::move(group));
    }
    signature += ")";

    const auto [existing, was_inserted] =
        emitted.try_emplace(signature, JuliaEmittedSignature { CFuncName(func), method_name });
    if (!was_inserted)
    {
        // A consumer re-emits its mixins' methods on its own type, so the same Julia name and
        // parameter types can be reached again.  Both wrappers call the same C symbol and
        // dispatch virtually to the same wxWidgets method, so the repeat is inherent and
        // dropping it loses nothing.
        if (existing->second.julia_name == method_name)
        {
            ++s_duplicate_tally.inherent_mixin_duplicates;
            return false;
        }
        // Distinct Julia names sharing one dispatch signature (two mixins exposing clear! for the
        // same receiver type) would be a method overwrite, which fails precompilation.  Keep the
        // binding by emitting it under its C symbol instead.
        const std::string fallback_signature =
            CFuncName(func) + signature.substr(method_name.size());
        if (!emitted
                 .try_emplace(fallback_signature,
                              JuliaEmittedSignature { CFuncName(func), CFuncName(func) })
                 .second)
        {
            ++s_duplicate_tally.inherent_mixin_duplicates;
            return false;
        }
        method_name = CFuncName(func);
        ++s_duplicate_tally.recovered_methods;
    }

    // Signature line.
    output << "function " << method_name << "(";
    bool first_output_param = true;
    if (has_receiver)
    {
        output << "obj::" << julia_cls;
        first_output_param = false;
    }
    for (const auto& group: param_groups)
    {
        for (const auto& julia_param: group)
        {
            if (!julia_param.decl.empty())
            {
                if (!first_output_param)
                {
                    output << ", ";
                }
                output << julia_param.decl;
                first_output_param = false;
            }
        }
    }
    output << ")\n";

    // Pre-call statements.
    for (const auto& group: param_groups)
    {
        for (const auto& julia_param: group)
        {
            if (!julia_param.pre_call.empty())
            {
                output << "    " << julia_param.pre_call << "\n";
            }
        }
    }

    // Build the KwxFFI call expression.  GC.@preserve keeps every AbstractString and byte
    // vector argument alive until the ccall has returned.
    std::string call = "KwxFFI." + CFuncName(func) + "(";
    bool first_call_arg = true;
    if (has_receiver)
    {
        call += "obj.ptr";
        first_call_arg = false;
    }
    for (const auto& group: param_groups)
    {
        for (const auto& julia_param: group)
        {
            if (!julia_param.call_expr.empty())
            {
                if (!first_call_arg)
                {
                    call += ", ";
                }
                call += julia_param.call_expr;
                first_call_arg = false;
            }
        }
    }
    call += ")";
    if (!preserve_names.empty())
    {
        call = "GC.@preserve" + preserve_names + " " + call;
    }

    // Emit call + return value.  A wxString temporary must be released even when the call
    // throws, so cleanup runs in a finally block instead of after the call.
    if (is_void)
    {
        if (has_post_calls)
        {
            output << "    try\n        " << call << "\n    finally\n";
            for (const auto& group: param_groups)
            {
                for (const auto& julia_param: group)
                {
                    if (!julia_param.post_call.empty())
                    {
                        output << "        " << julia_param.post_call << "\n";
                    }
                }
            }
            output << "    end\n";
        }
        else
        {
            output << "    " << call << "\n";
        }
        if (is_true_destructor)
        {
            output << "    obj.ptr = C_NULL\n";
        }
        output << "    nothing\n";
    }
    else if (has_post_calls)
    {
        // Capture the result inside try so the finally block still runs on a throw.
        output << "    _result = try\n        " << JuliaReturnExpr(func, call, wrapped_classes)
               << "\n    finally\n";
        for (const auto& group: param_groups)
        {
            for (const auto& julia_param: group)
            {
                if (!julia_param.post_call.empty())
                {
                    output << "        " << julia_param.post_call << "\n";
                }
            }
        }
        output << "    end\n    return _result\n";
    }
    else
    {
        output << "    return " << JuliaReturnExpr(func, call, wrapped_classes) << "\n";
    }

    output << "end\n\n";
    return true;
}

// end of static helpers

// -------------------------------------------------------------------------
// JuliaEmitter public interface
// -------------------------------------------------------------------------

void JuliaEmitter::Generate(const ParsedFFI& parsed_ffi, const fs::path& outDir)
{
    std::ignore = fs::create_directories(outDir);

    GenerateEvents(parsed_ffi, outDir);
    GenerateKeys(parsed_ffi, outDir);
    GenerateConstants(parsed_ffi, outDir);
    GenerateClasses(parsed_ffi, outDir);  // raw ccall layer (KwxFFI module)
    GenerateFreeFunctions(parsed_ffi, outDir);
    GenerateModule(outDir, parsed_ffi.lib_name);
    GenerateTypePreamble(parsed_ffi, outDir);      // abstract roots + _wx_wrap
    GenerateStringRuntime(outDir);                 // wxString + C string helpers
    GenerateIdiomaticClasses(parsed_ffi, outDir);  // idiomatic Julia wrappers

    std::println(stderr, "Julia: generated files in {}", outDir.string());
}

// -------------------------------------------------------------------------
// types_gen.jl — abstract roots, wxEvent, and the class-return wrapper
// -------------------------------------------------------------------------

// The same policy list JuliaAbstractParent() uses.  Emitting the roots here means the
// idiomatic tree no longer depends on a hand-written core/types.jl.
void JuliaEmitter::GenerateTypePreamble(const ParsedFFI& parsed_ffi, const fs::path& outDir)
{
    std::ignore = parsed_ffi;
    const fs::path path = outDir / "types_gen.jl";
    ConditionalFileWriter output(path);
    if (!output.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(output, "#");

    // Guarded so a consumer that already includes core/types.jl (or includes this file twice)
    // does not hit "invalid redefinition of constant".
    output << "if !@isdefined(wxObject)\n";
    output << "    abstract type wxObject end\n";
    output << "    abstract type wxEvtHandler <: wxObject end\n";
    output << "    abstract type wxWindow <: wxEvtHandler end\n";
    output << "    abstract type wxControl <: wxWindow end\n";
    output << "    abstract type wxTopLevelWindow <: wxWindow end\n";
    output << "    abstract type wxSizer <: wxObject end\n";
    output << "\n";
    output << "    struct wxEvent\n";
    output << "        ptr::Ptr{Cvoid}\n";
    output << "    end\n";
    output << "end\n\n";

    // A borrowed class pointer never gets a finalizer; only a caller-owned (TClassOwned)
    // pointer may.  A type with no destructor binding simply stays unfinalized.
    output << "if !@isdefined(_wx_wrap)\n";
    output << "    function _wx_attach_finalizer(obj, owned::Bool)\n";
    output << "        if owned && hasmethod(Base.delete!, Tuple{typeof(obj)})\n";
    output << "            finalizer(o -> (o.ptr == C_NULL || Base.delete!(o); nothing), obj)\n";
    output << "        end\n";
    output << "        return obj\n";
    output << "    end\n\n";
    output << "    function _wx_wrap(::Type{T}, ptr::Ptr{Cvoid}; owned::Bool = false) where {T}\n";
    output << "        return _wx_attach_finalizer(T(ptr), owned)\n";
    output << "    end\n\n";
    output << "    function _wx_wrap(::Type{T}, ptr::Ptr{Cvoid}; owned::Bool = false) where {T <: "
              "wxWindow}\n";
    output << "        return _wx_attach_finalizer(T(ptr, Any[], Any[]), owned)\n";
    output << "    end\n";
    output << "end\n";

    std::println(stderr, "  types_gen.jl:        type preamble");
}

// -------------------------------------------------------------------------
// wxstring_gen.jl — wxString lifecycle and free-standing C string helpers
// -------------------------------------------------------------------------

// Ported from the consumer's core/strings.jl, which was correct apart from relying on a
// hand-written file.  TString parameters never need this type; only TClass(wxString)
// parameters and TClass(wxString) returns do.
void JuliaEmitter::GenerateStringRuntime(const fs::path& outDir)
{
    const fs::path path = outDir / "wxstring_gen.jl";
    ConditionalFileWriter output(path);
    if (!output.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(output, "#");

    output << "if !@isdefined(wxString)\n";
    output << "    mutable struct wxString\n";
    output << "        ptr::Ptr{Cvoid}\n\n";
    output << "        function wxString(s::AbstractString)\n";
    output << "            ptr = GC.@preserve s "
              "KwxFFI.wxString_CreateUTF8(Base.unsafe_convert(Cstring, s))\n";
    output << "            obj = new(ptr)\n";
    output << "            finalizer(Base.delete!, obj)\n";
    output << "            return obj\n";
    output << "        end\n\n";
    output << "        function wxString(ptr::Ptr{Cvoid}, own::Bool = false)\n";
    output << "            obj = new(ptr)\n";
    output << "            own && finalizer(Base.delete!, obj)\n";
    output << "            return obj\n";
    output << "        end\n";
    output << "    end\n\n";
    output << "    function Base.delete!(ws::wxString)\n";
    output << "        if ws.ptr != C_NULL\n";
    output << "            KwxFFI.wxString_Delete(ws.ptr)\n";
    output << "            ws.ptr = C_NULL\n";
    output << "        end\n";
    output << "        return nothing\n";
    output << "    end\n\n";
    output << "    function Base.String(ws::wxString)\n";
    output << "        ws.ptr == C_NULL && return \"\"\n";
    output << "        buf = KwxFFI.kwxUtf8Buffer_Create(ws.ptr)\n";
    output << "        buf == C_NULL && return \"\"\n";
    output << "        try\n";
    output << "            return unsafe_string(KwxFFI.kwxUtf8Buffer_Data(buf))\n";
    output << "        finally\n";
    output << "            KwxFFI.kwxUtf8Buffer_Delete(buf)\n";
    output << "        end\n";
    output << "    end\n\n";
    output << "    Base.convert(::Type{wxString}, s::AbstractString) = wxString(s)\n";
    output << "    Base.convert(::Type{String}, ws::wxString) = String(ws)\n";
    output << "end\n\n";

    // TString returns are the strdup'ed byte buffer owned by the caller.  The buffer is freed
    // by the library's own wxCFree, not Libc.free: on Windows the DLL and Julia use different
    // C runtimes, and freeing across them corrupts the heap.
    output << "if !@isdefined(_wx_take_cstring)\n";
    output << "    function _wx_take_cstring(ptr::Ptr{Cchar})\n";
    output << "        ptr == C_NULL && return \"\"\n";
    output << "        try\n";
    output << "            return unsafe_string(ptr)\n";
    output << "        finally\n";
    output << "            KwxFFI.wxCFree(Ptr{Cvoid}(ptr))\n";
    output << "        end\n";
    output << "    end\n";
    output << "end\n\n";

    // TClass(wxString) returns a refcounted object that the caller must delete.
    output << "if !@isdefined(_wx_take_wxstring)\n";
    output << "    function _wx_take_wxstring(ptr::Ptr{Cvoid})\n";
    output << "        ptr == C_NULL && return \"\"\n";
    output << "        ws = wxString(ptr, false)\n";
    output << "        try\n";
    output << "            return String(ws)\n";
    output << "        finally\n";
    output << "            Base.delete!(ws)\n";
    output << "        end\n";
    output << "    end\n";
    output << "end\n";

    std::println(stderr, "  wxstring_gen.jl:     wxString runtime");
}

// -------------------------------------------------------------------------
// Verify
// -------------------------------------------------------------------------

namespace
{
    // True when a `julia` executable answers on PATH.  The parse check is optional: a consumer
    // that builds bindings without a Julia toolchain still gets the static checks below.
    [[nodiscard]] bool JuliaInterpreterAvailable()
    {
#ifdef _WIN32
        return std::system("julia --version > NUL 2>&1") == 0;
#else
        return std::system("julia --version > /dev/null 2>&1") == 0;
#endif
    }

    // Double-quote a path for std::system / a Julia string literal.  Paths may contain
    // spaces; neither shell nor Julia treats the quotes as content.
    [[nodiscard]] std::string QuoteForShell(const std::string& text)
    {
        return "\"" + text + "\"";
    }

    [[nodiscard]] std::string TrimEdges(const std::string& text)
    {
        const std::size_t first = text.find_first_not_of(" \t\r");
        if (first == std::string::npos)
        {
            return {};
        }
        const std::size_t last = text.find_last_not_of(" \t\r");
        return text.substr(first, last - first + 1);
    }

    // Julia dispatch signature of a "function ..." line: the name plus parameter types only,
    // so two declarations that differ only in parameter names compare equal.
    [[nodiscard]] std::string DeclarationSignature(const std::string& line)
    {
        const std::size_t open = line.find('(');
        if (open == std::string::npos)
        {
            return TrimEdges(line);
        }
        std::string signature = TrimEdges(line.substr(0, open)) + "(";
        std::string params = line.substr(open + 1);
        const std::size_t close = params.rfind(')');
        if (close != std::string::npos)
        {
            params = params.substr(0, close);
        }

        bool first = true;
        std::size_t start = 0;
        int depth = 0;
        for (std::size_t index = 0; index <= params.size(); ++index)
        {
            if (index < params.size())
            {
                const char character = params[index];
                if (character == '{' || character == '(' || character == '[')
                {
                    ++depth;
                }
                else if (character == '}' || character == ')' || character == ']')
                {
                    --depth;
                }
                if (character != ',' || depth != 0)
                {
                    continue;
                }
            }

            std::string decl = TrimEdges(params.substr(start, index - start));
            start = index + 1;
            const std::size_t separator = decl.find("::");
            if (separator != std::string::npos)
            {
                decl = TrimEdges(decl.substr(separator + 2));
            }
            if (!first)
            {
                signature += ", ";
            }
            signature += decl;
            first = false;
        }
        return signature + ")";
    }
}  // namespace

VerifyResult JuliaEmitter::Verify(const ParsedFFI& parsed_ffi, const fs::path& directory)
{
    std::ignore = parsed_ffi;
    VerifyResult result;

    if (!fs::is_directory(directory))
    {
        result.success = false;
        result.messages.push_back("Julia verify: '" + directory.string() + "' is not a directory");
        return result;
    }

    std::vector<fs::path> generated_files;
    for (const auto& entry: fs::directory_iterator(directory))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }
        const std::string file_name = entry.path().filename().string();
        if (file_name.ends_with("_gen.jl"))
        {
            generated_files.push_back(entry.path());
        }
    }
    std::ranges::sort(generated_files);

    for (const fs::path& file_path: generated_files)
    {
        std::ifstream input(file_path);
        if (!input.is_open())
        {
            result.success = false;
            result.messages.push_back("Julia verify: cannot read " + file_path.string());
            continue;
        }

        // The same signature twice is a method overwrite, which fails precompilation.
        std::unordered_map<std::string, std::size_t> signatures;
        std::string line;
        std::size_t line_number = 0;
        while (std::getline(input, line))
        {
            ++line_number;
            if (!line.starts_with("function"))
            {
                continue;
            }
            const std::string signature = DeclarationSignature(line);
            if (signature.starts_with("("))
            {
                // "function (obj::T)" — a definition whose value is discarded and which
                // defines no method (lang_julia.cpp's inverted guard produced 9,000 of these).
                result.success = false;
                result.messages.push_back(file_path.filename().string() + ":" +
                                          std::to_string(line_number) +
                                          ": anonymous method definition");
                continue;
            }
            const auto [existing, was_inserted] = signatures.try_emplace(signature, line_number);
            if (!was_inserted)
            {
                result.success = false;
                result.messages.push_back(file_path.filename().string() + ":" +
                                          std::to_string(line_number) + ": duplicate signature '" +
                                          signature + "' (first at line " +
                                          std::to_string(existing->second) + ")");
            }
        }
    }

    if (!JuliaInterpreterAvailable())
    {
        result.messages.emplace_back(
            "Julia parse check skipped: 'julia' not found on PATH (static checks ran)");
        return result;
    }

    // Meta.parseall over every file catches syntax errors the static checks cannot see.  The
    // script lives outside the compared directory (or verify would report it as an extra file)
    // and takes the directory as ARGV[1] (so no path escaping inside a Julia literal).
    const fs::path script_path = fs::temp_directory_path() / "kwxgen_julia_verify.jl";
    {
        std::ofstream script(script_path, std::ios::binary | std::ios::trunc);
        if (!script.is_open())
        {
            result.success = false;
            result.messages.push_back("Julia verify: cannot create " + script_path.string());
            return result;
        }
        script << "failed = Ref(false)\n";
        script << "for f in readdir(ARGS[1]; join=true)\n";
        script << "    endswith(f, \".jl\") || continue\n";
        script << "    try\n";
        script << "        Meta.parseall(read(f, String))\n";
        script << "    catch err\n";
        script << "        println(stderr, \"parse error: \", f, \": \", err)\n";
        script << "        failed[] = true\n";
        script << "    end\n";
        script << "end\n";
        script << "exit(failed[] ? 1 : 0)\n";
    }

    const std::string command = "julia --startup-file=no " + QuoteForShell(script_path.string()) +
                                " " + QuoteForShell(directory.string());
    if (std::system(command.c_str()) != 0)
    {
        result.success = false;
        result.messages.push_back("Julia parse check failed (script: " + script_path.string() +
                                  ")");
    }
    else
    {
        std::error_code error_code;
        fs::remove(script_path, error_code);
    }

    return result;
}

// -------------------------------------------------------------------------
// Coverage report
// -------------------------------------------------------------------------

// Count the valid methods the backend emits for one class.  The idiomatic wrapper file writes
// one block per valid method, plus one per plain (non-constructor, non-destructor) method of
// each mixin the class consumes.  A kSkipStruct class skips its idiomatic struct and
// constructor, but the raw ccall layer in classes_gen.jl still declares that constructor, so it
// is emitted by the backend and counts here.
[[nodiscard]] static size_t CountJuliaEmittedMethods(const ClassInfo& class_info,
                                                     const ParsedFFI& parsed_ffi)
{
    size_t method_count = 0;
    for (const auto& func: class_info.methods)
    {
        if (IsValidFunction(func))
        {
            ++method_count;
        }
    }

    const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
        parsed_ffi.mixin_map.find(class_info.name);
    if (mixin_iter == parsed_ffi.mixin_map.end())
    {
        return method_count;
    }
    for (const std::string& mixin_name: mixin_iter->second)
    {
        if (kSkipClass.contains(mixin_name))
        {
            continue;  // its lifecycle lives in core/strings.jl
        }
        for (const auto& mixin_class: parsed_ffi.classes)
        {
            if (mixin_class.name != mixin_name)
            {
                continue;
            }
            for (const auto& func: mixin_class.methods)
            {
                if (!IsValidFunction(func) || func.is_constructor || IsJuliaTrueDestructor(func))
                {
                    continue;
                }
                ++method_count;
            }
            break;
        }
    }
    return method_count;
}

CoverageInfo JuliaEmitter::Coverage(const ParsedFFI& parsed_ffi) const
{
    CoverageInfo report;
    report.free_function_count = parsed_ffi.free_functions.size();
    report.event_count = parsed_ffi.events.size();
    report.key_count = parsed_ffi.keys.size();
    report.constant_count = parsed_ffi.constants.size();

    for (const std::string& skip_name: kSkipClass)
    {
        report.consumer_provided_classes.push_back(skip_name);
    }
    for (const std::string& skip_name: kSkipStruct)
    {
        report.consumer_provided_classes.push_back(skip_name);
    }

    // The same policy GenerateIdiomaticClasses() uses, so the report describes what is emitted.
    const std::unordered_set<std::string> wrapped_classes = CollectWrappedClasses(parsed_ffi);

    for (const auto& class_entry: parsed_ffi.classes)
    {
        if (kSkipClass.contains(class_entry.name))
        {
            // core/strings.jl owns the wxString lifecycle, but the raw ccall layer in
            // classes_gen.jl still declares every method, so those methods do reach the
            // backend output and belong in the count.
            size_t raw_count = 0;
            for (const auto& func: class_entry.methods)
            {
                if (IsValidFunction(func))
                {
                    ++raw_count;
                }
            }
            if (raw_count != 0)
            {
                report.method_counts_by_class[class_entry.name] = raw_count;
            }
            continue;  // already reported as consumer-provided
        }
        if (!wrapped_classes.contains(class_entry.name))
        {
            report.skipped_classes.push_back(class_entry.name);
            continue;
        }

        report.wrapped_classes.push_back(class_entry.name);

        report.method_counts_by_class[class_entry.name] =
            CountJuliaEmittedMethods(class_entry, parsed_ffi);
    }

    std::ranges::sort(report.wrapped_classes);
    std::ranges::sort(report.consumer_provided_classes);
    std::ranges::sort(report.skipped_classes);
    return report;
}

// -------------------------------------------------------------------------
// events_gen.jl
// -------------------------------------------------------------------------

void JuliaEmitter::GenerateEvents(const ParsedFFI& parsed_ffi, const fs::path& outDir)
{
    const fs::path path = outDir / "events_gen.jl";
    ConditionalFileWriter output(path);
    if (!output.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(output, "#");

    std::vector<EventDecl> sorted = parsed_ffi.events;
    std::ranges::sort(sorted,
                      [](const EventDecl& lhs, const EventDecl& rhs)
                      {
                          return lhs.event_name < rhs.event_name;
                      });

    for (const auto& event: sorted)
    {
        output << event.event_name << "() = ccall((:" << event.export_name
               << ", libkwxFFI), Cint, ())\n";
        // Every docstring refers to the wxEVT_ spelling, but the export symbol only records
        // the un-prefixed name.  Emit the prefixed form as a deprecated alias.
        if (event.export_name.starts_with("exp_wx") && !event.event_name.starts_with("wx"))
        {
            output << "Base.@deprecate wx" << event.event_name << "() " << event.event_name
                   << "()\n";
        }
    }

    std::println(stderr, "  events_gen.jl:       {} events", parsed_ffi.events.size());
}

// -------------------------------------------------------------------------
// keys_gen.jl
// -------------------------------------------------------------------------

void JuliaEmitter::GenerateKeys(const ParsedFFI& parsed_ffi, const fs::path& outDir)
{
    const fs::path path = outDir / "keys_gen.jl";
    ConditionalFileWriter output(path);
    if (!output.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(output, "#");

    std::vector<KeyDecl> sorted = parsed_ffi.keys;
    std::ranges::sort(sorted,
                      [](const KeyDecl& lhs, const KeyDecl& rhs)
                      {
                          return lhs.key_name < rhs.key_name;
                      });

    for (const auto& key_item: sorted)
    {
        output << key_item.key_name << "() = ccall((:" << key_item.export_name
               << ", libkwxFFI), Cint, ())\n";
    }

    std::println(stderr, "  keys_gen.jl:         {} keys", parsed_ffi.keys.size());
}

// -------------------------------------------------------------------------
// constants_gen.jl
// -------------------------------------------------------------------------

void JuliaEmitter::GenerateConstants(const ParsedFFI& parsed_ffi, const fs::path& outDir)
{
    const fs::path path = outDir / "constants_gen.jl";
    ConditionalFileWriter output(path);
    if (!output.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(output, "#");

    std::vector<ConstantDecl> sorted = parsed_ffi.constants;
    std::ranges::sort(sorted,
                      [](const ConstantDecl& lhs, const ConstantDecl& rhs)
                      {
                          return lhs.export_name < rhs.export_name;
                      });

    for (const auto& constant: sorted)
    {
        const std::string retType =
            (constant.return_type.find('*') != std::string::npos) ? "Ptr{Cvoid}" : "Cint";

        output << constant.constant_name << "() = ccall((:" << constant.export_name
               << ", libkwxFFI), " << retType << ", ())\n";
    }

    std::println(stderr, "  constants_gen.jl:    {} constants", parsed_ffi.constants.size());
}

void JuliaEmitter::GenerateClasses(const ParsedFFI& parsed_ffi, const fs::path& outDir)
{
    const fs::path path = outDir / "classes_gen.jl";
    ConditionalFileWriter output(path);
    if (!output.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(output, "#");

    size_t methodCount = 0;
    size_t skippedCount = 0;

    for (const auto& class_entry: parsed_ffi.classes)
    {
        if (class_entry.methods.empty())
        {
            continue;
        }

        output << "# " << class_entry.name << "\n";

        for (const auto& func: class_entry.methods)
        {
            if (!IsValidFunction(func))
            {
                ++skippedCount;
                continue;
            }
            EmitFunctionWrapper(output, func);
            ++methodCount;
        }

        output << "\n";
    }

    std::print(stderr, "  classes_gen.jl:      {} methods", methodCount);
    if (skippedCount > 0)
    {
        std::print(stderr, " ({} skipped)", skippedCount);
    }
    std::println(stderr, "");
}

// -------------------------------------------------------------------------
// freefuncs_gen.jl
// -------------------------------------------------------------------------

void JuliaEmitter::GenerateFreeFunctions(const ParsedFFI& parsed_ffi, const fs::path& outDir)
{
    const fs::path path = outDir / "freefuncs_gen.jl";
    ConditionalFileWriter output(path);
    if (!output.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(output, "#");

    size_t count = 0;

    for (const auto& func: parsed_ffi.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        EmitFunctionWrapper(output, func);
        ++count;
    }

    std::println(stderr, "  freefuncs_gen.jl:    {} free functions", count);
}

// -------------------------------------------------------------------------
// KwxFFI_gen.jl — Julia module that includes all generated files
// -------------------------------------------------------------------------

void JuliaEmitter::GenerateModule(const fs::path& outDir, const std::string& libName)
{
    const fs::path path = outDir / "KwxFFI_gen.jl";
    ConditionalFileWriter output(path);
    if (!output.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(output, "#");
    output << "module KwxFFI\n\n";
    output << "const libkwxFFI = \"" << libName << "\"\n\n";
    output << "include(\"events_gen.jl\")\n";
    output << "include(\"keys_gen.jl\")\n";
    output << "include(\"constants_gen.jl\")\n";
    output << "include(\"classes_gen.jl\")\n";
    output << "include(\"freefuncs_gen.jl\")\n";
    output << "\nend # module KwxFFI\n";

    std::println(stderr, "  KwxFFI_gen.jl:       module definition");
}

// -------------------------------------------------------------------------
// GenerateIdiomaticClasses: per-class idiomatic Julia wrapper files
// + a master wx_idiomatic_gen.jl that includes them all.
// -------------------------------------------------------------------------

void JuliaEmitter::EmitIdiomaticClassFile(std::ostream& output, const ClassInfo& class_info,
                                          const ParsedFFI& parsed_ffi)
{
    WriteGeneratedHeader(output, "#");

    // Types with a generated struct: only those can be constructed by _wx_wrap().
    const std::unordered_set<std::string> wrapped_classes = CollectWrappedClasses(parsed_ffi);
    // Julia dispatch signatures already written in this file, mapped to the C symbol and Julia
    // name that produced them.  A repeat must be skipped or renamed: method overwriting fails
    // precompilation.
    std::unordered_map<std::string, JuliaEmittedSignature> emitted_signatures;

    // kSkipStruct: skip concrete struct + constructor, but STILL emit methods.
    // These are types declared abstractly in types_gen.jl, or types with existing
    // definitions (wxEvent). Methods dispatch on them polymorphically.
    const bool skip_struct = kSkipStruct.contains(class_info.name);

    if (!skip_struct)
    {
        // Determine Julia abstract parent by walking the parent_map.
        const std::string abstract_parent =
            JuliaAbstractParent(class_info.name, parsed_ffi.parent_map);

        // ---------- mutable struct ----------
        output << "mutable struct " << class_info.name << " <: " << abstract_parent << "\n";
        output << "    ptr::Ptr{Cvoid}\n";
        if (class_info.is_window_derived)
        {
            output << "    children::Vector{Any}\n";
            output << "    closures::Vector{Any}\n";
        }
        output << "end\n\n";

        // The struct's own default constructors already occupy these signatures.  A C
        // Create* factory that maps to the same shape (wxMemoryDC_CreateCompatible,
        // wxStyledTextCtrl_Create) would overwrite them, which fails precompilation, so the
        // guard makes such a factory fall back to its C symbol name.
        emitted_signatures.emplace(
            class_info.name + "(Ptr{Cvoid})",
            JuliaEmittedSignature { class_info.name + "(implicit struct constructor)",
                                    class_info.name });
        if (class_info.is_window_derived)
        {
            emitted_signatures.emplace(
                class_info.name + "(Ptr{Cvoid}, Vector{Any}, Vector{Any})",
                JuliaEmittedSignature { class_info.name + "(implicit struct constructor)",
                                        class_info.name });
        }

        // ---------- constructors ----------
        for (const auto& func: class_info.methods)
        {
            if (!IsValidFunction(func))
            {
                continue;
            }
            if (!func.is_constructor || func.has_self)
            {
                continue;  // skip factory methods (has_self) and non-constructors
            }

            // Build the idiomatic parameter list.
            std::string declaration;
            std::string type_signature;
            std::vector<std::vector<JuliaIdiomParam>> param_groups;
            std::string preserve_names;
            bool has_post_calls = false;
            for (const auto& param: func.params)
            {
                if (param.macro_name == "TSelf")
                {
                    continue;
                }
                std::vector<JuliaIdiomParam> group = ConvertToIdiomParams(param, true);
                for (const auto& julia_param: group)
                {
                    if (julia_param.decl.empty())
                    {
                        continue;
                    }
                    if (!declaration.empty())
                    {
                        declaration += ", ";
                        type_signature += ", ";
                    }
                    declaration += julia_param.decl;
                    type_signature += JuliaParamType(julia_param.decl);
                    if (!julia_param.post_call.empty())
                    {
                        has_post_calls = true;
                    }
                    if (!julia_param.preserve.empty())
                    {
                        preserve_names += " " + julia_param.preserve;
                    }
                }
                param_groups.push_back(std::move(group));
            }

            // Every factory is named ClassName(paramtypes...), so two genuinely different
            // factories collapse onto one signature: wxColour_CreateFromStock(int) and
            // wxColour_CreateFromUnsignedInt(unsigned) are both wxColour(::Integer).  A collision
            // therefore does not mean a duplicate, so the second factory is emitted under its C
            // symbol name and its binding is kept.
            std::string julia_name = class_info.name;
            const std::string signature = class_info.name + "(" + type_signature + ")";
            if (!emitted_signatures
                     .try_emplace(signature, JuliaEmittedSignature { CFuncName(func), julia_name })
                     .second)
            {
                // Only the emitted function name changes; the constructed struct type, the error
                // message and the wrapping still name the class.
                julia_name = CFuncName(func);
                const std::string fallback_signature = julia_name + "(" + type_signature + ")";
                if (!emitted_signatures
                         .try_emplace(fallback_signature,
                                      JuliaEmittedSignature { CFuncName(func), julia_name })
                         .second)
                {
                    continue;
                }
                ++s_duplicate_tally.recovered_factories;
            }

            // Constructor signature.
            output << "function " << julia_name << "(" << declaration << ")\n";

            // Pre-call statements.
            for (const auto& group: param_groups)
            {
                for (const auto& julia_param: group)
                {
                    if (!julia_param.pre_call.empty())
                    {
                        output << "    " << julia_param.pre_call << "\n";
                    }
                }
            }

            // C call, with string/vector arguments preserved across it.
            std::string call = "KwxFFI." + CFuncName(func) + "(";
            bool first_arg = true;
            for (const auto& group: param_groups)
            {
                for (const auto& julia_param: group)
                {
                    if (!julia_param.call_expr.empty())
                    {
                        if (!first_arg)
                        {
                            call += ", ";
                        }
                        call += julia_param.call_expr;
                        first_arg = false;
                    }
                }
            }
            call += ")";
            if (!preserve_names.empty())
            {
                call = "GC.@preserve" + preserve_names + " " + call;
            }

            // A wxString temporary must be released even when the call throws.
            if (has_post_calls)
            {
                output << "    ptr = try\n        " << call << "\n    finally\n";
                for (const auto& group: param_groups)
                {
                    for (const auto& julia_param: group)
                    {
                        if (!julia_param.post_call.empty())
                        {
                            output << "        " << julia_param.post_call << "\n";
                        }
                    }
                }
                output << "    end\n";
            }
            else
            {
                output << "    ptr = " << call << "\n";
            }

            // Null check.
            output << "    ptr == C_NULL && error(\"Failed to create " << class_info.name
                   << "\")\n";

            // Construct Julia object.
            if (class_info.is_window_derived)
            {
                bool has_parent_param = false;
                for (const auto& group: param_groups)
                {
                    for (const auto& julia_param: group)
                    {
                        if (julia_param.pre_call.find("parent_ptr") != std::string::npos)
                        {
                            has_parent_param = true;
                        }
                    }
                }

                output << "    obj = " << class_info.name << "(ptr, Any[], Any[])\n";
                if (has_parent_param)
                {
                    output << "    isnothing(parent) || push!(parent.children, obj)\n";
                }
            }
            else
            {
                output << "    obj = " << class_info.name << "(ptr)\n";
            }
            output << "    return obj\n";
            output << "end\n\n";
        }
    }  // !skip_struct

    // ---------- mixin methods re-emitted through this class ----------
    // A consumer of a mixin (wxTextCtrl consumes wxTextEntry, wxListBox consumes
    // wxItemContainer) exposes the mixin's methods on itself, so the wrapper is emitted here
    // against the consumer's own type.
    //
    // This block is written before the class's own methods, so when the class also declares a
    // method with the same dispatch signature the mixin's wrapper claims it and the class's own
    // wrapper is the one dropped.  That is harmless: both wrappers call the same C symbol and
    // dispatch virtually to the same wxWidgets method, so the duplicate is inherent.
    const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
        parsed_ffi.mixin_map.find(class_info.name);
    if (mixin_iter != parsed_ffi.mixin_map.end())
    {
        for (const std::string& mixin_name: mixin_iter->second)
        {
            if (kSkipClass.contains(mixin_name))
            {
                continue;  // its lifecycle lives in core/strings.jl
            }
            for (const auto& mixin_class: parsed_ffi.classes)
            {
                if (mixin_class.name != mixin_name)
                {
                    continue;
                }
                const bool mixin_explicit_receiver = JuliaUsesExplicitReceiver(mixin_class);
                for (const auto& func: mixin_class.methods)
                {
                    if (!IsValidFunction(func) || func.is_constructor ||
                        IsJuliaTrueDestructor(func))
                    {
                        continue;
                    }
                    // A receiver-less function (static member of the mixin, e.g.
                    // wxPropertyGridInterface_RegisterAdditionalEditors) belongs to the mixin
                    // class, not to each consumer; re-emitting it here would define the same
                    // module-level method once per consumer and fail precompilation.
                    if (!func.has_self && !IsJuliaPseudoSelf(func))
                    {
                        continue;
                    }
                    EmitIdiomaticMethod(output, func, class_info.name, mixin_explicit_receiver,
                                        wrapped_classes, emitted_signatures);
                }
                break;
            }
        }
    }

    // ---------- methods (emitted for ALL classes, including abstract types) ----------
    const bool explicit_receiver = JuliaUsesExplicitReceiver(class_info);
    for (const auto& func: class_info.methods)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        if (func.is_constructor && !func.has_self)
        {
            continue;  // true constructors already emitted (or skipped for abstract)
        }

        EmitIdiomaticMethod(output, func, class_info.name, explicit_receiver, wrapped_classes,
                            emitted_signatures);
    }
}

void JuliaEmitter::GenerateIdiomaticClasses(const ParsedFFI& parsed_ffi, const fs::path& outDir)
{
    // Master include file that a package includes after the raw KwxFFI module.  types_gen.jl
    // is included here so the tree loads with no hand-written type preamble; its definitions
    // are guarded and tolerate a second include.
    const fs::path masterPath = outDir / "wx_idiomatic_gen.jl";
    ConditionalFileWriter master(masterPath);
    if (!master.is_open())
    {
        std::println(stderr, "Error: cannot create {}", masterPath.string());
        return;
    }
    master << "# Code generated by kwxgen. DO NOT EDIT.\n";
    master << "# Include this file from your module AFTER KwxFFI_gen.jl and wxstring_gen.jl.\n";
    master << "include(\"types_gen.jl\")\n\n";

    size_t classCount = 0;
    size_t skippedCount = 0;
    size_t methodCount = 0;

    // The collision maps are per class file; these counters are reset per run so the aggregate
    // line reports only this generation.
    s_duplicate_tally = {};

    // kSkipClass: completely exclude from idiomatic generation.
    // Only utility types that have dedicated implementations (strings.jl) are excluded.
    // Abstract types (wxWindow, etc.) are included here but kSkipStruct prevents
    // struct generation; their methods are still emitted and dispatch polymorphically.
    //
    // The class set comes from the shared wrapper policy, so a zero-method direct wxEvent
    // subclass still gets a struct and an include line even though it contributes no methods.
    const std::unordered_set<std::string> wrapped_classes = CollectWrappedClasses(parsed_ffi);

    for (const auto& class_entry: parsed_ffi.classes)
    {
        if (kSkipClass.contains(class_entry.name))
        {
            ++skippedCount;
            continue;
        }
        if (!wrapped_classes.contains(class_entry.name))
        {
            continue;
        }

        const std::string fileName = JuliaClassFileName(class_entry.name);
        const fs::path filePath = outDir / fileName;

        ConditionalFileWriter output(filePath);
        if (!output.is_open())
        {
            std::println(stderr, "Error: cannot create {}", filePath.string());
            continue;
        }
        ++classCount;

        EmitIdiomaticClassFile(output, class_entry, parsed_ffi);

        for (const auto& func: class_entry.methods)
        {
            if (IsValidFunction(func))
            {
                ++methodCount;
            }
        }

        master << "include(\"" << fileName << "\")\n";
    }

    std::print(stderr, "  wx_idiomatic_gen.jl: {} classes, {} methods", classCount, methodCount);
    bool has_detail = false;
    const auto start_detail = [&has_detail]()
    {
        if (has_detail)
        {
            std::print(stderr, "; ");
            return;
        }
        std::print(stderr, " (");
        has_detail = true;
    };
    if (skippedCount > 0)
    {
        start_detail();
        std::print(stderr, "{} skipped", skippedCount);
    }
    if (s_duplicate_tally.inherent_mixin_duplicates > 0)
    {
        start_detail();
        std::print(stderr, "{} inherent mixin duplicates suppressed",
                   s_duplicate_tally.inherent_mixin_duplicates);
    }
    if (s_duplicate_tally.recovered_methods > 0)
    {
        start_detail();
        std::print(stderr, "{} method bindings recovered under their C names",
                   s_duplicate_tally.recovered_methods);
    }
    if (s_duplicate_tally.recovered_factories > 0)
    {
        start_detail();
        std::print(stderr, "{} factories emitted under their C names",
                   s_duplicate_tally.recovered_factories);
    }
    if (has_detail)
    {
        std::print(stderr, ")");
    }
    std::println(stderr, "");
}

// NOLINTEND(readability-magic-string)
