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
#include <filesystem>
#include <print>
#include <set>
#include <tuple>
#include <unordered_set>
#include <vector>

// NOLINTBEGIN(readability-magic-string)

namespace fs = std::filesystem;

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
    std::string post_call;  // statement(s) emitted after the call
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
        // Special case: TClass(wxString) → idiomatic String param with wxString lifecycle.
        if (param.macro_arg == "wxString")
        {
            std::string name = param.param_name.empty() ? "str" : param.param_name;
            name = JuliaEscapeName(name);
            const std::string wx_str = name + "_ws";
            result.push_back({ name + "::String", wx_str + ".ptr",
                               wx_str + " = wxString(" + name + ")", "delete!(" + wx_str + ")" });
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

    // String input → wxString create/delete.
    if (param.raw_type == "TString" || param.macro_name == "TString")
    {
        std::string name = param.param_name.empty() ? "str" : param.param_name;
        name = JuliaEscapeName(name);
        const std::string wx_str = name + "_ws";
        result.push_back({ name + "::String", wx_str + ".ptr", wx_str + " = wxString(" + name + ")",
                           "delete!(" + wx_str + ")" });
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

    // String output buffer.
    if (param.raw_type == "TStringOut")
    {
        std::string name = param.param_name.empty() ? "buf" : param.param_name;
        name = JuliaEscapeName(name);
        result.push_back({ name + "::Ptr{UInt8}", name, "", "" });
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
    else if (raw_type == "long" || raw_type == "time_t")
    {
        result.push_back({ name + "::Integer", "Clong(" + name + ")", "", "" });
    }
    else if (raw_type == "unsigned" || raw_type == "unsigned int")
    {
        result.push_back({ name + "::Integer", "Cuint(" + name + ")", "", "" });
    }
    else if (raw_type == "unsigned long" || raw_type == "wxUIntPtr" || raw_type == "uintptr_t")
    {
        result.push_back({ name + "::Integer", "Culong(" + name + ")", "", "" });
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

// Build the KwxFFI return expression for a function call string.
static std::string JuliaReturnExpr(const FunctionDecl& func, const std::string& call)
{
    if (func.return_type == "TBool" || func.return_type == "TBoolInt")
    {
        return call + " != 0";
    }
    if (func.return_macro == "TClass" || func.return_macro == "TSelf" ||
        func.return_macro == "TClassRef")
    {
        return call;  // Ptr{Cvoid}
    }
    if (func.return_type == "TString" || func.return_type == "TStringOut" ||
        func.return_type == "TStringVoid")
    {
        return "_wx_get_string(" + call + ")";
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
    if (func.return_type == "long" || func.return_type == "time_t")
    {
        return "Int(" + call + ")";
    }
    // Pointers, void*, and anything else: return as-is.
    return call;
}

// Emit one idiomatic Julia method (non-constructor, non-duplicate-name guard
// is the caller's responsibility).
static void EmitIdiomaticMethod(std::ostream& output, const FunctionDecl& func,
                                const std::string& julia_cls)
{
    if (!IsValidFunction(func) || (func.is_constructor && !func.has_self))
    {
        return;
    }

    bool is_void = IsVoidReturn(func.return_type, func.return_macro);

    // Snake-case method name; add ! for void (mutating) methods.
    std::string method_name;
    if (func.is_destructor)
    {
        method_name = "delete!";
        is_void = true;
    }
    if (!IsValidFunction(func) || (func.is_constructor && !func.has_self))
    {
        const std::string snake = JuliaEscapeName(ToSnakeCase(func.method_name));
        method_name = snake + (is_void ? "!" : "");
    }

    // Build idiomatic param list (skip TSelf).
    std::vector<std::vector<JuliaIdiomParam>> param_groups;
    bool has_post_calls = false;
    for (const auto& param: func.params)
    {
        if (param.macro_name == "TSelf")
        {
            continue;
        }
        std::vector<JuliaIdiomParam> group = ConvertToIdiomParams(param, false);
        for (const auto& julia_param: group)
        {
            if (!julia_param.post_call.empty())
            {
                has_post_calls = true;
            }
        }
        param_groups.push_back(std::move(group));
    }

    // Signature line.
    output << "function " << method_name << "(obj::" << julia_cls;
    for (const auto& group: param_groups)
    {
        for (const auto& julia_param: group)
        {
            if (!julia_param.decl.empty())
            {
                output << ", " << julia_param.decl;
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

    // Build the KwxFFI call expression.
    std::string call = "KwxFFI." + CFuncName(func) + "(obj.ptr";
    for (const auto& group: param_groups)
    {
        for (const auto& julia_param: group)
        {
            if (!julia_param.call_expr.empty())
            {
                call += ", " + julia_param.call_expr;
            }
        }
    }
    call += ")";

    // Emit call + return value.
    if (is_void)
    {
        output << "    " << call << "\n";
        for (const auto& group: param_groups)
        {
            for (const auto& julia_param: group)
            {
                if (!julia_param.post_call.empty())
                {
                    output << "    " << julia_param.post_call << "\n";
                }
            }
        }
        output << "    nothing\n";
    }
    else if (has_post_calls)
    {
        // Capture result, cleanup, then return.
        output << "    _result = " << JuliaReturnExpr(func, call) << "\n";
        for (const auto& group: param_groups)
        {
            for (const auto& julia_param: group)
            {
                if (!julia_param.post_call.empty())
                {
                    output << "    " << julia_param.post_call << "\n";
                }
            }
        }
        output << "    return _result\n";
    }
    else
    {
        output << "    return " << JuliaReturnExpr(func, call) << "\n";
    }

    output << "end\n\n";
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
    GenerateIdiomaticClasses(parsed_ffi, outDir);  // idiomatic Julia wrappers

    std::println(stderr, "Julia: generated files in {}", outDir.string());
}

VerifyResult JuliaEmitter::Verify(const ParsedFFI& /* parsed_ffi */,
                                  const fs::path& /* directory */)
{
    VerifyResult result;
    result.success = false;
    result.messages.emplace_back("Julia verify: use 'kwxgen verify' command instead");
    return result;
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

    // kSkipStruct: skip concrete struct + constructor, but STILL emit methods.
    // These are types declared abstractly in types.jl, or types with existing
    // definitions (wxEvent in types.jl). Methods dispatch on them polymorphically.
    static const std::unordered_set<std::string> kSkipStruct = {
        "wxObject", "wxEvtHandler", "wxWindow", "wxControl", "wxTopLevelWindow", "wxSizer",
        "wxEvent"  // struct wxEvent defined in core/types.jl
    };
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

            // Build idiomatic param list.
            std::vector<std::vector<JuliaIdiomParam>> param_groups;
            for (const auto& param: func.params)
            {
                if (param.macro_name == "TSelf")
                {
                    continue;
                }
                param_groups.push_back(ConvertToIdiomParams(param, true));
            }

            // Constructor signature.
            output << "function " << class_info.name << "(";
            bool first_param = true;
            for (const auto& group: param_groups)
            {
                for (const auto& julia_param: group)
                {
                    if (!julia_param.decl.empty())
                    {
                        if (!first_param)
                        {
                            output << ", ";
                        }
                        output << julia_param.decl;
                        first_param = false;
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

            // C call.
            output << "    ptr = KwxFFI." << CFuncName(func) << "(";
            bool first_arg = true;
            for (const auto& group: param_groups)
            {
                for (const auto& julia_param: group)
                {
                    if (!julia_param.call_expr.empty())
                    {
                        if (!first_arg)
                        {
                            output << ", ";
                        }
                        output << julia_param.call_expr;
                        first_arg = false;
                    }
                }
            }
            output << ")\n";

            // Post-call cleanup.
            for (const auto& group: param_groups)
            {
                for (const auto& julia_param: group)
                {
                    if (!julia_param.post_call.empty())
                    {
                        output << "    " << julia_param.post_call << "\n";
                    }
                }
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

    // ---------- methods (emitted for ALL classes, including abstract types) ----------
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

        EmitIdiomaticMethod(output, func, class_info.name);
    }
}

void JuliaEmitter::GenerateIdiomaticClasses(const ParsedFFI& parsed_ffi, const fs::path& outDir)
{
    // Master include file that WxWidgets.jl (or similar) can include after
    // core types (types.jl) and strings (strings.jl) are loaded.
    const fs::path masterPath = outDir / "wx_idiomatic_gen.jl";
    ConditionalFileWriter master(masterPath);
    if (!master.is_open())
    {
        std::println(stderr, "Error: cannot create {}", masterPath.string());
        return;
    }
    master << "# Code generated by kwxgen. DO NOT EDIT.\n";
    master << "# Include this file from your module AFTER:\n";
    master << "#   include(\"core/types.jl\")   -- abstract type hierarchy\n";
    master << "#   include(\"core/strings.jl\") -- wxString helpers\n\n";

    size_t classCount = 0;
    size_t skippedCount = 0;
    size_t methodCount = 0;

    // kSkipClass: completely exclude from idiomatic generation.
    // Only utility types that have dedicated implementations (strings.jl) are excluded.
    // Abstract types (wxWindow, etc.) are included here but kSkipStruct prevents
    // struct generation; their methods are still emitted and dispatch polymorphically.
    static const std::unordered_set<std::string> kSkipClass = {
        "wxString"  // lifecycle managed by core/strings.jl
    };

    for (const auto& class_entry: parsed_ffi.classes)
    {
        if (class_entry.methods.empty())
        {
            continue;
        }
        if (kSkipClass.contains(class_entry.name))
        {
            ++skippedCount;
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
    if (skippedCount > 0)
    {
        std::print(stderr, " ({} skipped)", skippedCount);
    }
    std::println(stderr, "");
}

// NOLINTEND(readability-magic-string)
