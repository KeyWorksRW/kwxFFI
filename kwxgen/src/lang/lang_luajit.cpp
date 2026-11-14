/////////////////////////////////////////////////////////////////////////////
// Purpose:   LuaJIT FFI code generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "lang_luajit.h"

#include "../file_writer.h"
#include "lang_common.h"
#include "luajit_type_map.h"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <map>
#include <print>
#include <set>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// NOLINTBEGIN(readability-magic-string)

namespace fs = std::filesystem;

// Classes excluded from idiomatic generation: the string helper type's lifecycle is managed
// by kwxffi_helpers_gen.lua, so the class is consumer-provided rather than wrapped.
static const std::unordered_set<std::string> kSkipClass = {
    "wxString"  // Lifecycle managed by kwxffi_helpers_gen.lua
};

// Emit a single C function declaration for ffi.cdef.
static void EmitCDecl(std::ostream& stream, const std::string& return_type,
                      const std::string& func_name, const std::vector<LuaCParam>& params)
{
    stream << "    " << return_type << " " << func_name << "(";
    for (size_t index = 0; index < params.size(); ++index)
    {
        if (index > 0)
        {
            stream << ", ";
        }
        stream << params[index].c_type << " " << params[index].name;
    }
    stream << ");\n";
}

// Emit a C declaration from a FunctionDecl.
static void EmitFunctionCDecl(std::ostream& stream, const FunctionDecl& func)
{
    const std::string ret_type = LuaJITReturnType(func.return_type, func.return_macro);
    const std::string func_name = CFuncName(func);

    std::vector<LuaCParam> c_params;
    for (const auto& param: func.params)
    {
        std::vector<LuaCParam> expanded = ExpandParamToC(param);
        for (auto& c_param: expanded)
        {
            c_param.name = LuaEscapeName(c_param.name);
            c_params.push_back(std::move(c_param));
        }
    }

    EmitCDecl(stream, ret_type, func_name, c_params);
}

// -----------------------------------------------------------------
// Idiomatic layer helpers
// -----------------------------------------------------------------

// A single idiomatic Lua parameter and its call expression.
struct LuaIdiomParam
{
    std::string name;       // Lua parameter name in function signature
    std::string call_expr;  // Expression passed to the C call
    std::string pre_call;   // Statement before the call (empty if none)
    std::string post_call;  // Statement after the call (empty if none)
};

// Output filename for a class: "wxButton" -> "wxbutton_gen.lua"
static std::string LuaClassFileName(const std::string& class_name)
{
    std::string result;
    for (const char char_val: class_name)
    {
        result += static_cast<char>(std::tolower(static_cast<unsigned char>(char_val)));
    }
    return result + "_gen.lua";
}

// True if the function return type is void.
[[nodiscard]] static bool IsVoidReturn(const std::string& return_type)
{
    return return_type.empty() || return_type == "void";
}

// True if the return is a string type that needs wxString->Lua conversion.
[[nodiscard]] static bool IsStringReturn(const FunctionDecl& func)
{
    if (func.return_type == "TString" || func.return_type == "TStringOut")
    {
        return true;
    }
    if (func.return_macro == "TClass" && func.return_arg == "wxString")
    {
        return true;
    }
    return false;
}

// True if the return is a boolean type.
[[nodiscard]] static bool IsBoolReturn(const FunctionDecl& func)
{
    return func.return_type == "TBool" || func.return_type == "TBoolInt";
}

// Build a Lua return expression wrapping a raw C call result.
static std::string LuaReturnExpr(const FunctionDecl& func, const std::string& call)
{
    if (IsBoolReturn(func))
    {
        return "_H.to_bool(" + call + ")";
    }
    if (IsStringReturn(func))
    {
        return "_H.wxs_to_str(" + call + ")";
    }
    // Everything else (int, double, pointer, void): pass through.
    return call;
}

// True when a TClass(...) return names a class that has a generated idiomatic module.
// wxString is emitted as a Lua string by LuaReturnExpr, never as a wrapper.
[[nodiscard]] static bool
    IsWrappedClassReturn(const FunctionDecl& func,
                         const std::unordered_set<std::string>& wrapped_classes)
{
    return func.return_macro == "TClass" && !func.return_arg.empty() &&
           func.return_arg != "wxString" && !kSkipClass.contains(func.return_arg) &&
           wrapped_classes.contains(func.return_arg);
}

// The generated module a return is routed through: "wxSize" -> "wxsize_gen".
static std::string LuaClassModuleName(const std::string& class_name)
{
    const std::string file = LuaClassFileName(class_name);
    return file.substr(0, file.size() - 4);  // strip ".lua"
}

// Like LuaReturnExpr(), but routes a wrapped-class return through helpers.wrap().
static std::string LuaWrappedReturnExpr(const FunctionDecl& func, const std::string& call,
                                        const std::unordered_set<std::string>& wrapped_classes)
{
    if (!IsWrappedClassReturn(func, wrapped_classes))
    {
        return LuaReturnExpr(func, call);
    }
    return "_H.wrap(\"" + LuaClassModuleName(func.return_arg) + "\", " + call +
           (func.returns_owned ? ", true)" : ")");
}

// Convert one Param into zero or more idiomatic Lua parameters.
static std::vector<LuaIdiomParam> ConvertToLuaIdiomParams(const Param& param, bool in_constructor)
{
    std::vector<LuaIdiomParam> result;

    // Self param -> handled by method receiver (self._ptr); skip.  A constructor never takes a
    // receiver, so its loop skips TSelf before calling here; a non-receiver TSelf (the second
    // parameter of wxIcon_IsEqual or wxXmlResource_Set) reaches this point only for methods and
    // must marshal like TClass.
    if (param.macro_name == "TSelf")
    {
        if (in_constructor)
        {
            return result;
        }
        const std::string name = LuaEscapeName(param.param_name.empty() ? "arg" : param.param_name);
        result.push_back({ name, "_H.ptr(" + name + ")", "", "" });
        return result;
    }

    // Geometry expansion macros -> multiple numeric params.
    if (param.macro_name == "TPoint" || param.macro_name == "TSize" ||
        param.macro_name == "TRect" || param.macro_name == "TVector")
    {
        for (auto& name: LuaJITSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = LuaEscapeName(name);
            result.push_back({ escaped, escaped, "", "" });
        }
        return result;
    }

    if (param.macro_name == "TPointLong" || param.macro_name == "TSizeLong" ||
        param.macro_name == "TRectLong" || param.macro_name == "TVectorLong")
    {
        for (auto& name: LuaJITSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = LuaEscapeName(name);
            result.push_back({ escaped, escaped, "", "" });
        }
        return result;
    }

    // Output geometry parameters -> pointer params (pass-through).
    if (param.macro_name == "TPointOut" || param.macro_name == "TSizeOut" ||
        param.macro_name == "TRectOut" || param.macro_name == "TVectorOut" ||
        param.macro_name == "TPointOutLong" || param.macro_name == "TSizeOutLong" ||
        param.macro_name == "TPointOutVoid" || param.macro_name == "TSizeOutVoid" ||
        param.macro_name == "TRectOutVoid" || param.macro_name == "TVectorOutVoid")
    {
        for (auto& name: LuaJITSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = LuaEscapeName(name);
            result.push_back({ escaped, escaped, "", "" });
        }
        return result;
    }

    if (param.macro_name == "TSizeOutDouble")
    {
        for (auto& name: LuaJITSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = LuaEscapeName(name);
            result.push_back({ escaped, escaped, "", "" });
        }
        return result;
    }

    if (param.macro_name == "TColorRGB")
    {
        for (auto& name: LuaJITSplitMacroArg(param.macro_arg))
        {
            const std::string escaped = LuaEscapeName(name);
            result.push_back({ escaped, escaped, "", "" });
        }
        return result;
    }

    // Array types: count + pointer.
    if (param.macro_name == "TArrayString" || param.macro_name == "TArrayInt" ||
        param.macro_name == "TByteString" || param.macro_name == "TByteStringLazy")
    {
        const std::vector<std::string> names = LuaJITSplitMacroArg(param.macro_arg);
        if (names.size() >= 2)
        {
            result.push_back({ LuaEscapeName(names[0]), LuaEscapeName(names[0]), "", "" });
            result.push_back({ LuaEscapeName(names[1]), LuaEscapeName(names[1]), "", "" });
        }
        return result;
    }

    if (param.macro_name == "TArrayObjectOutVoid")
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "arr" : param.param_name);
        result.push_back({ name, name, "", "" });
        return result;
    }

    // TClass(wxString) -> String input: create wxString, pass, free.
    if (param.macro_name == "TClass" && param.macro_arg == "wxString")
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "str" : param.param_name);
        const std::string ws_var = "_ws_" + name;
        result.push_back({
            name,
            ws_var,
            "local " + ws_var + " = _H.wxs(" + name + ")",
            "_H.wxs_free(" + ws_var + ")",
        });
        return result;
    }

    // TClass(other) -> Pointer: extract ._ptr via helper.
    if (param.macro_name == "TClass" || param.macro_name == "TClassRef")
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "arg" : param.param_name);
        if (in_constructor && name == "parent")
        {
            // Nullable parent window.
            result.push_back({ "parent", "_H.ptr(parent)", "", "" });
        }
        else
        {
            result.push_back({ name, "_H.ptr(" + name + ")", "", "" });
        }
        return result;
    }

    // TString (char*) input -> Lua string passes directly via LuaJIT FFI.
    if (param.raw_type == "TString" || param.macro_name == "TString")
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "str" : param.param_name);
        result.push_back({ name, name, "", "" });
        return result;
    }

    // TStringVoid -> void* pass-through.
    if (param.raw_type == "TStringVoid" || param.macro_name == "TStringVoid")
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "str" : param.param_name);
        result.push_back({ name, name, "", "" });
        return result;
    }

    // TStringOut -> output buffer pass-through.
    if (param.raw_type == "TStringOut")
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "buf" : param.param_name);
        result.push_back({ name, name, "", "" });
        return result;
    }

    // Scalar output / in-out pointer: the caller owns the storage, so pass it through.
    if (ScalarPointerInfo scalar_pointer; LookupScalarPointer(param, scalar_pointer))
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "arg" : param.param_name);
        result.push_back({ name, name, "", "" });
        return result;
    }

    // TBool -> boolean to int conversion.
    if (param.macro_name == "TBool" || param.raw_type == "TBool")
    {
        const std::string name =
            LuaEscapeName(param.param_name.empty() ? "flag" : param.param_name);
        result.push_back({ name, "_H.from_bool(" + name + ")", "", "" });
        return result;
    }

    if (param.raw_type == "TBoolInt")
    {
        const std::string name =
            LuaEscapeName(param.param_name.empty() ? "flag" : param.param_name);
        result.push_back({ name, name, "", "" });
        return result;
    }

    if (param.raw_type == "TBool*")
    {
        const std::string name =
            LuaEscapeName(param.param_name.empty() ? "flag" : param.param_name);
        result.push_back({ name, name, "", "" });
        return result;
    }

    // Closure/callback function pointer.
    if (param.macro_name == "TClosureFun" || param.raw_type == "TClosureFun")
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "fn" : param.param_name);
        result.push_back({ name, name, "", "" });
        return result;
    }

    // Opaque output arrays -> pass-through.
    if (param.raw_type == "TArrayIntOutVoid" || param.raw_type == "TArrayIntPtrOutVoid" ||
        param.raw_type == "TArrayStringOutVoid" || param.raw_type == "TByteStringOut" ||
        param.raw_type == "TByteStringLazyOut" || param.raw_type == "TArrayObjectOutVoid")
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "arr" : param.param_name);
        result.push_back({ name, name, "", "" });
        return result;
    }

    // Opaque `void*` argument -> accept a wrapper object or already-raw cdata.  _H.ptr()
    // returns cdata and nil unchanged, so this only adds wrapper-table support.  A receiver
    // declared as `void* pObject` / `void* self` never reaches here: the caller skips
    // parameter 0 for every non-static method.
    if (param.macro_name.empty() && param.raw_type == "void*")
    {
        const std::string name = LuaEscapeName(param.param_name.empty() ? "ptr" : param.param_name);
        result.push_back({ name, "_H.ptr(" + name + ")", "", "" });
        return result;
    }

    // Plain C types -> pass through.
    const std::string name = LuaEscapeName(param.param_name.empty() ? "arg" : param.param_name);
    result.push_back({ name, name, "", "" });
    return result;
}

// Find the parent class name that is actually wrapped (has methods).
// Walk the hierarchy until we find a parent that exists in the classes list,
// or return empty string if none found.
static std::string FindWrappedParent(const std::string& class_name, const ParsedFFI& ffi_data,
                                     const std::unordered_set<std::string>& wrapped_classes)
{
    std::unordered_map<std::string, std::string>::const_iterator iter =
        ffi_data.parent_map.find(class_name);
    std::set<std::string> visited;
    while (iter != ffi_data.parent_map.end())
    {
        const std::string& parent = iter->second;
        if (visited.contains(parent))
        {
            break;  // cycle guard
        }
        visited.insert(parent);
        if (wrapped_classes.contains(parent))
        {
            return parent;
        }
        iter = ffi_data.parent_map.find(parent);
    }
    return "";
}

// -------------------------------------------------------------------------
// LuaJITEmitter public interface
// -------------------------------------------------------------------------

void LuaJITEmitter::Generate(const ParsedFFI& ffi_data, const fs::path& out_dir)
{
    GenerateInto(ffi_data, out_dir);

    std::println(stderr, "LuaJIT: generated files in {}", out_dir.string());
}

// The generation sequence without the closing summary line.  Generate() and
// VerifyUiDescriptor() both run exactly these steps, so a verified tree is the tree a real
// generation produces.
void LuaJITEmitter::GenerateInto(const ParsedFFI& ffi_data, const fs::path& out_dir)
{
    (void) fs::create_directories(out_dir);

    // Raw FFI layer
    GenerateEvents(ffi_data, out_dir);
    GenerateKeys(ffi_data, out_dir);
    GenerateConstants(ffi_data, out_dir);
    GenerateClasses(ffi_data, out_dir);
    GenerateFreeFunctions(ffi_data, out_dir);
    GenerateInit(out_dir, ffi_data.lib_name);

    // Idiomatic layer
    GenerateHelpers(out_dir);
    GenerateIdiomaticClasses(ffi_data, out_dir);
    GenerateIdiomaticFreeFunctions(ffi_data, out_dir);
}

VerifyResult LuaJITEmitter::Verify(const ParsedFFI& /* ffi_data */, const fs::path& /* out_dir */)
{
    VerifyResult result;
    result.success = false;
    result.messages.emplace_back("LuaJIT verify: use 'kwxgen verify' command instead");
    return result;
}

// -------------------------------------------------------------------------
// Coverage report
// -------------------------------------------------------------------------

// The Lua member name the idiomatic emitter publishes for a method, or an empty string when
// the emitter skips the method entirely.  Coverage() uses this so the reported counts match
// the emitted modules: constructors land on M.<name>, a destructor without extra parameters
// lands on M:Delete, and every other method keeps its own name.
[[nodiscard]] static std::string LuaEmittedMemberName(const FunctionDecl& func)
{
    if (!IsValidFunction(func))
    {
        return "";
    }
    if (func.is_constructor && !func.has_self)
    {
        return func.method_name;
    }
    if (func.is_destructor)
    {
        bool has_non_self_params = false;
        for (const auto& param: func.params)
        {
            if (param.macro_name != "TSelf")
            {
                has_non_self_params = true;
            }
        }
        if (!has_non_self_params)
        {
            return "Delete";
        }
    }
    return func.method_name;
}

CoverageInfo LuaJITEmitter::Coverage(const ParsedFFI& ffi_data) const
{
    CoverageInfo report;
    report.free_function_count = ffi_data.free_functions.size();
    report.event_count = ffi_data.events.size();
    report.key_count = ffi_data.keys.size();
    report.constant_count = ffi_data.constants.size();

    for (const std::string& skip_name: kSkipClass)
    {
        report.consumer_provided_classes.push_back(skip_name);
    }

    // The same policy GenerateIdiomaticClasses() uses, so the report describes what is emitted.
    const std::unordered_set<std::string> wrapped_classes = CollectWrappedClasses(ffi_data);

    std::unordered_map<std::string, const ClassInfo*> class_index;
    class_index.reserve(ffi_data.classes.size());
    for (const auto& class_decl: ffi_data.classes)
    {
        class_index.emplace(class_decl.name, &class_decl);
    }

    for (const auto& class_decl: ffi_data.classes)
    {
        if (kSkipClass.contains(class_decl.name))
        {
            // The idiomatic module is intentionally omitted; kwxffi_helpers_gen.lua owns the
            // lifecycle instead. GenerateClasses() still emits the raw ffi.cdef declarations for
            // these methods, so they do reach the backend output and belong in the count.
            size_t raw_count = 0;
            for (const auto& func: class_decl.methods)
            {
                if (IsValidFunction(func))
                {
                    ++raw_count;
                }
            }
            if (raw_count != 0)
            {
                report.method_counts_by_class[class_decl.name] = raw_count;
            }
            continue;  // already reported as consumer-provided
        }
        if (!wrapped_classes.contains(class_decl.name))
        {
            report.skipped_classes.push_back(class_decl.name);
            continue;
        }

        report.wrapped_classes.push_back(class_decl.name);

        // Member names are unique per Lua module, so a repeated name collapses onto the
        // already-emitted wrapper instead of producing a second function.
        std::set<std::string> emitted_names;
        size_t wrapped_count = 0;
        size_t collapsed_count = 0;

        for (const auto& func: class_decl.methods)
        {
            const std::string member_name = LuaEmittedMemberName(func);
            if (member_name.empty())
            {
                continue;
            }
            if (emitted_names.insert(member_name).second)
            {
                ++wrapped_count;
            }
            else
            {
                ++collapsed_count;
            }
        }

        // The consumer module merges each wrapped mixin's exported members, so its mixin
        // methods are part of what the consumer actually emits.
        const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
            ffi_data.mixin_map.find(class_decl.name);
        if (mixin_iter != ffi_data.mixin_map.end())
        {
            for (const std::string& mixin_name: mixin_iter->second)
            {
                if (!wrapped_classes.contains(mixin_name) || kSkipClass.contains(mixin_name))
                {
                    continue;
                }
                const std::unordered_map<std::string, const ClassInfo*>::const_iterator
                    mixin_found = class_index.find(mixin_name);
                if (mixin_found == class_index.end())
                {
                    continue;
                }
                for (const auto& func: mixin_found->second->methods)
                {
                    const std::string member_name = LuaEmittedMemberName(func);
                    if (member_name.empty())
                    {
                        continue;
                    }
                    if (emitted_names.insert(member_name).second)
                    {
                        ++wrapped_count;
                    }
                    else
                    {
                        ++collapsed_count;
                    }
                }
            }
        }

        report.method_counts_by_class[class_decl.name] = wrapped_count;
        if (collapsed_count != 0)
        {
            report.deduplicated_method_counts_by_class[class_decl.name] = collapsed_count;
            report.deduplicated_method_count += collapsed_count;
        }
    }

    std::ranges::sort(report.wrapped_classes);
    std::ranges::sort(report.consumer_provided_classes);
    std::ranges::sort(report.skipped_classes);
    return report;
}

// -------------------------------------------------------------------------
// kwxffi_events_gen.lua
// -------------------------------------------------------------------------

// Emit the lazily-resolved name table that a raw constants module returns.  Nothing is
// resolved at require time: each name calls its C accessor on first use and the value is
// cached in the table, so an older library missing a symbol degrades per-name instead of
// breaking the whole module.  `subject` names what the table provides.  `wstring_names`
// names the entries whose accessor returns an owned wxString*, so those are converted to a
// Lua string and released instead of being cached as a raw pointer.
static void EmitLazySymbolTable(std::ostream& stream, const std::string& subject,
                                const std::vector<std::pair<std::string, std::string>>& entries,
                                const std::unordered_set<std::string>& wstring_names = {})
{
    stream << "\nlocal C = ffi.C\n\n";

    if (!wstring_names.empty())
    {
        stream << "-- wxString* accessor result -> Lua string.  The accessor returns a new "
                  "wxString that\n";
        stream << "-- this module owns, so it is converted and then deleted.\n";
        stream << "local function _ws_to_str(ptr)\n";
        stream << "    local buf = C.kwxUtf8Buffer_Create(ptr)\n";
        stream << "    local str = ffi.string(C.kwxUtf8Buffer_Data(buf))\n";
        stream << "    C.kwxUtf8Buffer_Delete(buf)\n";
        stream << "    C.wxString_Delete(ptr)\n";
        stream << "    return str\n";
        stream << "end\n\n";
    }

    // Emit in sorted order so regeneration produces a stable file.
    std::vector<std::string> sorted_wstring_names(wstring_names.begin(), wstring_names.end());
    std::ranges::sort(sorted_wstring_names);
    stream << "local _wstring = {";
    if (!sorted_wstring_names.empty())
    {
        stream << "\n";
    }
    for (const auto& name: sorted_wstring_names)
    {
        stream << "    " << name << " = true,\n";
    }
    stream << "}\n\n";

    stream << "-- " << subject
           << ".  Each name resolves through its C accessor on first use and is cached in the\n";
    stream << "-- table.\n";
    stream << "local _symbols = {\n";
    for (const auto& [symbol_name, export_name]: entries)
    {
        stream << "    " << symbol_name << " = \"" << export_name << "\",\n";
    }
    stream << "}\n\n";
    stream << "local M = setmetatable({}, {\n";
    stream << "    __index = function(self, name)\n";
    stream << "        local symbol = _symbols[name]\n";
    stream << "        if symbol == nil then\n";
    stream << "            return nil\n";
    stream << "        end\n";
    stream << "        local value = C[symbol]()\n";
    stream << "        if _wstring[name] then\n";
    stream << "            value = _ws_to_str(value)\n";
    stream << "        end\n";
    stream << "        rawset(self, name, value)\n";
    stream << "        return value\n";
    stream << "    end,\n";
    stream << "})\n\n";
    stream << "return M\n";
}

void LuaJITEmitter::GenerateEvents(const ParsedFFI& ffi_data, const fs::path& out_dir)
{
    const fs::path path = out_dir / "kwxffi_events_gen.lua";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer, "--", false);
    writer << "local ffi = require(\"ffi\")\n\n";
    writer << "ffi.cdef[[\n";

    std::vector<EventDecl> sorted = ffi_data.events;
    std::ranges::sort(sorted,
                      [](const EventDecl& left, const EventDecl& right)
                      {
                          return left.event_name < right.event_name;
                      });

    for (const auto& event: sorted)
    {
        writer << "    int " << event.export_name << "();\n";
    }

    writer << "]]\n";

    // Idiomatic table: the exported accessor behind each EVT_* macro name.  Entries are
    // sorted by name, then by export name, and a duplicate event_name keeps its first entry.
    std::vector<EventDecl> table_events = ffi_data.events;
    std::ranges::sort(table_events,
                      [](const EventDecl& left, const EventDecl& right)
                      {
                          if (left.event_name != right.event_name)
                          {
                              return left.event_name < right.event_name;
                          }
                          return left.export_name < right.export_name;
                      });

    std::vector<std::pair<std::string, std::string>> entries;
    std::unordered_set<std::string> emitted_names;
    for (const auto& event: table_events)
    {
        if (emitted_names.insert(event.event_name).second)
        {
            entries.emplace_back(event.event_name, event.export_name);
        }
    }

    EmitLazySymbolTable(writer, "Event identifiers exported through EVT_* accessors", entries);

    std::println(stderr, "  kwxffi_events_gen.lua:       {:L} events", ffi_data.events.size());
}

// -------------------------------------------------------------------------
// kwxffi_keys_gen.lua
// -------------------------------------------------------------------------

void LuaJITEmitter::GenerateKeys(const ParsedFFI& ffi_data, const fs::path& out_dir)
{
    const fs::path path = out_dir / "kwxffi_keys_gen.lua";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer, "--", false);
    writer << "local ffi = require(\"ffi\")\n\n";
    writer << "ffi.cdef[[\n";

    std::vector<KeyDecl> sorted = ffi_data.keys;
    std::ranges::sort(sorted,
                      [](const KeyDecl& left, const KeyDecl& right)
                      {
                          return left.key_name < right.key_name;
                      });

    for (const auto& key_decl: sorted)
    {
        writer << "    int " << key_decl.export_name << "();\n";
    }

    writer << "]]\n";

    // Idiomatic table: the exported accessor behind each key-name macro.
    std::vector<std::pair<std::string, std::string>> entries;
    entries.reserve(sorted.size());
    for (const auto& key_decl: sorted)
    {
        entries.emplace_back(key_decl.key_name, key_decl.export_name);
    }

    EmitLazySymbolTable(writer, "Key codes exported as K_* accessors", entries);

    std::println(stderr, "  kwxffi_keys_gen.lua:         {:L} keys", ffi_data.keys.size());
}

// -------------------------------------------------------------------------
// kwxffi_constants_gen.lua
// -------------------------------------------------------------------------

void LuaJITEmitter::GenerateConstants(const ParsedFFI& ffi_data, const fs::path& out_dir)
{
    const fs::path path = out_dir / "kwxffi_constants_gen.lua";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer, "--", false);
    writer << "local ffi = require(\"ffi\")\n\n";
    writer << "ffi.cdef[[\n";

    std::vector<ConstantDecl> sorted = ffi_data.constants;
    std::ranges::sort(sorted,
                      [](const ConstantDecl& left, const ConstantDecl& right)
                      {
                          return left.export_name < right.export_name;
                      });

    for (const auto& constant: sorted)
    {
        const std::string ret_type =
            (constant.return_type.find('*') != std::string::npos) ? "void*" : constant.return_type;
        writer << "    " << ret_type << " " << constant.export_name << "();\n";
    }

    writer << "]]\n";

    // Idiomatic table: scalar constants plus wxString-returning accessors.  A wxString
    // accessor hands back a newly allocated wxString, so its value is converted to a Lua
    // string and released.  Any other pointer-returning accessor would expose a raw pointer
    // (const wxPen*), so those keep their cdef declaration without an idiomatic entry.
    std::vector<ConstantDecl> table_constants;
    for (const auto& constant: ffi_data.constants)
    {
        if (!constant.return_type.contains('*') || constant.return_type.contains("wxString"))
        {
            table_constants.push_back(constant);
        }
    }
    std::ranges::sort(table_constants,
                      [](const ConstantDecl& left, const ConstantDecl& right)
                      {
                          if (left.constant_name != right.constant_name)
                          {
                              return left.constant_name < right.constant_name;
                          }
                          return left.export_name < right.export_name;
                      });

    std::vector<std::pair<std::string, std::string>> entries;
    std::unordered_set<std::string> wstring_names;
    std::unordered_set<std::string> emitted_names;
    for (const auto& constant: table_constants)
    {
        if (emitted_names.insert(constant.constant_name).second)
        {
            entries.emplace_back(constant.constant_name, constant.export_name);
            if (constant.return_type.contains("wxString"))
            {
                wstring_names.insert(constant.constant_name);
            }
        }
    }

    EmitLazySymbolTable(writer, "Scalar and wxString constants exported as accessors", entries,
                        wstring_names);

    std::println(stderr, "  kwxffi_constants_gen.lua:    {:L} constants",
                 ffi_data.constants.size());
}

// -------------------------------------------------------------------------
// kwxffi_classes_gen.lua
// -------------------------------------------------------------------------

void LuaJITEmitter::GenerateClasses(const ParsedFFI& ffi_data, const fs::path& out_dir)
{
    const fs::path path = out_dir / "kwxffi_classes_gen.lua";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer, "--", false);
    writer << "local ffi = require(\"ffi\")\n\n";

    size_t class_count = 0;
    size_t method_count = 0;
    size_t skipped_count = 0;

    for (const auto& class_decl: ffi_data.classes)
    {
        if (class_decl.methods.empty())
        {
            continue;
        }

        ++class_count;
        writer << "-- " << class_decl.name << "\n";
        writer << "ffi.cdef[[\n";

        for (const auto& func: class_decl.methods)
        {
            if (!IsValidFunction(func))
            {
                ++skipped_count;
                continue;
            }
            EmitFunctionCDecl(writer, func);
            ++method_count;
        }

        writer << "]]\n\n";
    }

    std::print(stderr, "  kwxffi_classes_gen.lua:      {:L} classes, {:L} methods", class_count,
               method_count);
    if (skipped_count > 0)
    {
        std::print(stderr, " ({} skipped)", skipped_count);
    }
    std::println(stderr, "");
}

// -------------------------------------------------------------------------
// kwxffi_freefuncs_gen.lua
// -------------------------------------------------------------------------

void LuaJITEmitter::GenerateFreeFunctions(const ParsedFFI& ffi_data, const fs::path& out_dir)
{
    if (ffi_data.free_functions.empty())
    {
        return;
    }

    const fs::path path = out_dir / "kwxffi_freefuncs_gen.lua";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer, "--", false);
    writer << "local ffi = require(\"ffi\")\n\n";
    writer << "ffi.cdef[[\n";

    size_t count = 0;
    for (const auto& func: ffi_data.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        EmitFunctionCDecl(writer, func);
        ++count;
    }

    writer << "]]\n";

    std::println(stderr, "  kwxffi_freefuncs_gen.lua:    {} free functions", count);
}

// -------------------------------------------------------------------------
// kwxffi_gen.lua -- main entry point, loads all sub-files and returns lib
// -------------------------------------------------------------------------

void LuaJITEmitter::GenerateInit(const fs::path& out_dir, const std::string& /* lib_name */)
{
    const fs::path path = out_dir / "kwxffi_gen.lua";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer, "--", false);
    writer << "-- Main entry point for kwxFFI LuaJIT bindings.\n";
    writer << "-- Usage: local C = require(\"kwxffi_gen\")\n";
    writer << "--        C.wxButton_Create(parent, id, label, x, y, w, h, style)\n";
    writer << "\n";
    writer << "require(\"kwxffi_events_gen\")\n";
    writer << "require(\"kwxffi_keys_gen\")\n";
    writer << "require(\"kwxffi_constants_gen\")\n";
    writer << "require(\"kwxffi_classes_gen\")\n";
    writer << "require(\"kwxffi_freefuncs_gen\")\n";
    writer << "\n";
    // kwxLuaJIT is always statically linked into the host executable, so symbols
    // are available via ffi.C (the exe's own export table).
    writer << "return require(\"ffi\").C\n";

    std::println(stderr, "  kwxffi_gen.lua:              main entry point");
}

// =========================================================================
// Idiomatic layer
// =========================================================================

// -------------------------------------------------------------------------
// kwxffi_helpers_gen.lua -- utility functions for idiomatic wrappers
// -------------------------------------------------------------------------

void LuaJITEmitter::GenerateHelpers(const fs::path& out_dir)
{
    const fs::path path = out_dir / "kwxffi_helpers_gen.lua";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer, "--", false);
    writer << "-- Helper utilities for idiomatic LuaJIT wrappers.\n";
    writer << "-- Required by all generated class modules.\n";
    writer << "\n";
    writer << "local ffi = require(\"ffi\")\n";
    writer << "local C = require(\"kwxffi_gen\")\n";
    writer << "\n";
    writer << "local M = {}\n";
    writer << "\n";

    // wxString bridge
    writer << "--- Create a wxString from a Lua string. nil is treated as empty string.\n";
    writer << "--- @param str string|nil\n";
    writer << "--- @return cdata wxString pointer\n";
    writer << "function M.wxs(str)\n";
    writer << "    return C.wxString_CreateUTF8(str or \"\")\n";
    writer << "end\n";
    writer << "\n";

    writer << "--- Free a wxString.\n";
    writer << "--- @param ws cdata|nil\n";
    writer << "function M.wxs_free(ws)\n";
    writer << "    if ws ~= nil then\n";
    writer << "        C.wxString_Delete(ws)\n";
    writer << "    end\n";
    writer << "end\n";
    writer << "\n";

    writer << "--- Convert a wxString pointer to a Lua string, then free the wxString.\n";
    writer << "--- @param ws_ptr cdata wxString pointer returned by a C wrapper\n";
    writer << "--- @return string\n";
    writer << "function M.wxs_to_str(ws_ptr)\n";
    writer << "    if ws_ptr == nil then return \"\" end\n";
    writer << "    local buf = C.kwxUtf8Buffer_Create(ws_ptr)\n";
    writer << "    local str = ffi.string(C.kwxUtf8Buffer_Data(buf))\n";
    writer << "    C.kwxUtf8Buffer_Delete(buf)\n";
    writer << "    C.wxString_Delete(ws_ptr)\n";
    writer << "    return str\n";
    writer << "end\n";
    writer << "\n";

    // Pointer extraction
    writer << "--- Extract the C pointer from a wrapper object (or pass through cdata/nil).\n";
    writer << "--- @param obj table|cdata|nil\n";
    writer << "--- @return cdata pointer (or nil)\n";
    writer << "function M.ptr(obj)\n";
    writer << "    if obj == nil then return nil end\n";
    writer << "    if type(obj) == \"cdata\" then return obj end\n";
    writer << "    return obj._ptr\n";
    writer << "end\n";
    writer << "\n";

    // Wrapper construction.  The cache holds the lazily required class module, which is what
    // keeps the generated module graph cycle-free while still allowing a class module to wrap
    // a return whose type is defined in another module.
    writer << "M._wrap_cache = {}\n";
    writer << "\n";
    writer << "--- Wrap a raw C pointer returned by the FFI layer in its generated class module.\n";
    writer << "--- A table is returned unchanged, so a consumer may call this on an "
              "already-wrapped value.\n";
    writer << "--- @param module_name string generated class module, e.g. \"wxsize_gen\"\n";
    writer << "--- @param ptr cdata|table|nil raw pointer or existing wrapper\n";
    writer << "--- @param owned boolean|nil true when the caller owns the native allocation\n";
    writer << "function M.wrap(module_name, ptr, owned)\n";
    writer << "    if ptr == nil then return nil end\n";
    writer << "    if type(ptr) == \"table\" then return ptr end\n";
    writer << "    local mod = M._wrap_cache[module_name]\n";
    writer << "    if mod == nil then\n";
    writer << "        mod = require(module_name)\n";
    writer << "        M._wrap_cache[module_name] = mod\n";
    writer << "    end\n";
    writer << "    return mod.FromPtr(ptr, owned)\n";
    writer << "end\n";
    writer << "\n";

    // Boolean conversion
    writer << "--- Convert a C int to a Lua boolean.\n";
    writer << "--- @param val number\n";
    writer << "--- @return boolean\n";
    writer << "function M.to_bool(val) return val ~= 0 end\n";
    writer << "\n";

    writer << "--- Convert a Lua boolean to C int (1 or 0).\n";
    writer << "--- @param val boolean\n";
    writer << "--- @return number\n";
    writer << "function M.from_bool(val) return val and 1 or 0 end\n";
    writer << "\n";

    writer << "return M\n";

    std::println(stderr, "  kwxffi_helpers_gen.lua:      helper utilities");
}

// -------------------------------------------------------------------------
// Lua idiomatic-layer emission helpers
// -------------------------------------------------------------------------

// Emits comma-separated Lua parameter names from groups into the output stream.
static void EmitLuaParamNames(std::ostream& output,
                              const std::vector<std::vector<LuaIdiomParam>>& param_groups)
{
    bool first_param = true;
    for (const auto& group: param_groups)
    {
        for (const auto& lua_param: group)
        {
            if (!first_param)
            {
                output << ", ";
            }
            output << lua_param.name;
            first_param = false;
        }
    }
}

// Emits pre-call setup statements for all Lua parameters.
static void EmitLuaPreCalls(std::ostream& output,
                            const std::vector<std::vector<LuaIdiomParam>>& param_groups)
{
    for (const auto& group: param_groups)
    {
        for (const auto& lua_param: group)
        {
            if (!lua_param.pre_call.empty())
            {
                output << "    " << lua_param.pre_call << "\n";
            }
        }
    }
}

// Emits post-call cleanup statements for all Lua parameters.
static void EmitLuaPostCalls(std::ostream& output,
                             const std::vector<std::vector<LuaIdiomParam>>& param_groups)
{
    for (const auto& group: param_groups)
    {
        for (const auto& lua_param: group)
        {
            if (!lua_param.post_call.empty())
            {
                output << "    " << lua_param.post_call << "\n";
            }
        }
    }
}

// Returns true if any parameter in the groups has a post-call statement.
[[nodiscard]] static bool
    HasLuaPostCalls(const std::vector<std::vector<LuaIdiomParam>>& param_groups)
{
    for (const auto& group: param_groups)
    {
        for (const auto& lua_param: group)
        {
            if (!lua_param.post_call.empty())
            {
                return true;
            }
        }
    }
    return false;
}

// Builds a complete C call expression string from a function and its Lua parameter groups.
// When self_expr is non-empty, it is used as the first argument (e.g. "self._ptr").
[[nodiscard]] static std::string
    BuildLuaCCall(const FunctionDecl& func_info,
                  const std::vector<std::vector<LuaIdiomParam>>& param_groups,
                  const std::string& self_expr)
{
    std::string result = "C." + CFuncName(func_info) + "(";
    bool first_arg = true;
    if (!self_expr.empty())
    {
        result += self_expr;
        first_arg = false;
    }
    for (const auto& group: param_groups)
    {
        for (const auto& lua_param: group)
        {
            if (!first_arg)
            {
                result += ", ";
            }
            result += lua_param.call_expr;
            first_arg = false;
        }
    }
    result += ")";
    return result;
}

// -------------------------------------------------------------------------
// kwxffi_freefuncs_idiomatic_gen.lua
// -------------------------------------------------------------------------

void LuaJITEmitter::GenerateIdiomaticFreeFunctions(const ParsedFFI& ffi_data,
                                                   const fs::path& out_dir)
{
    const fs::path path = out_dir / "kwxffi_freefuncs_idiomatic_gen.lua";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer, "--", false);
    writer << "local ffi = require(\"ffi\")\n";
    writer << "local C = require(\"kwxffi_gen\")\n";
    writer << "local _H = require(\"kwxffi_helpers_gen\")\n";
    writer << "\n";
    writer << "local M = {}\n";
    writer << "\n";

    // A wrapped-class return is handed back as the owning class module's wrapper, not a cdata.
    const std::unordered_set<std::string> wrapped_classes = CollectWrappedClasses(ffi_data);

    size_t count = 0;
    for (const auto& func: ffi_data.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }

        // A free function has no receiver, so every parameter is a real argument.
        std::vector<std::vector<LuaIdiomParam>> param_groups;
        for (const auto& param: func.params)
        {
            param_groups.push_back(ConvertToLuaIdiomParams(param, false));
        }

        writer << "function M." << CFuncName(func) << "(";
        EmitLuaParamNames(writer, param_groups);
        writer << ")\n";

        EmitLuaPreCalls(writer, param_groups);

        const std::string c_call = BuildLuaCCall(func, param_groups, "");
        if (IsVoidReturn(func.return_type))
        {
            writer << "    " << c_call << "\n";
            EmitLuaPostCalls(writer, param_groups);
        }
        else if (HasLuaPostCalls(param_groups))
        {
            // Capture result, cleanup, then return.
            writer << "    local _result = " << LuaWrappedReturnExpr(func, c_call, wrapped_classes)
                   << "\n";
            EmitLuaPostCalls(writer, param_groups);
            writer << "    return _result\n";
        }
        else
        {
            writer << "    return " << LuaWrappedReturnExpr(func, c_call, wrapped_classes) << "\n";
        }
        writer << "end\n\n";
        ++count;
    }

    writer << "return M\n";

    std::println(stderr, "  kwxffi_freefuncs_idiomatic_gen.lua: {} free functions", count);
}

// -------------------------------------------------------------------------
// Per-class idiomatic files + master include
// -------------------------------------------------------------------------

void LuaJITEmitter::EmitIdiomaticClassFile(std::ostream& output, const ClassInfo& class_info,
                                           const ParsedFFI& ffi_data)
{
    WriteGeneratedHeader(output, "--", false);
    output << "local ffi = require(\"ffi\")\n";
    output << "local C = require(\"kwxffi_gen\")\n";
    output << "local _H = require(\"kwxffi_helpers_gen\")\n";
    output << "\n";

    // Build the set of wrapped classes (shared policy) for parent resolution.
    const std::unordered_set<std::string> wrapped_classes = CollectWrappedClasses(ffi_data);

    // Check for a wrapped parent to inherit methods from.
    const std::string parent_name = FindWrappedParent(class_info.name, ffi_data, wrapped_classes);

    if (!parent_name.empty())
    {
        const std::string parent_file = LuaClassFileName(parent_name);
        // Strip the ".lua" for require (Lua require uses module names, not filenames)
        const std::string parent_module = parent_file.substr(0, parent_file.size() - 4);
        output << "local _parent = require(\"" << parent_module << "\")\n";
        output << "local M = setmetatable({}, { __index = _parent })\n";
    }
    else
    {
        output << "local M = {}\n";
    }
    output << "local MT = { __index = M }\n";
    output << "\n";

    // Wrap a borrowed C pointer, e.g. the wxEvent* handed to an event handler.  Without a
    // non-owning wrapper the caller cannot reach this class's methods from a raw pointer.
    output
        << "--- Wrap an existing C pointer.  The wrapper does not own the native object unless\n";
    output << "--- `owned` is true, so Delete() is a no-op on a borrowed wrapper.\n";
    output << "function M.FromPtr(ptr, owned)\n";
    output << "    if ptr == nil then return nil end\n";
    output << "    if type(ptr) == \"table\" then return ptr end\n";
    output << "    return setmetatable({ _ptr = ptr, _borrowed = not owned }, MT)\n";
    output << "end\n";
    output << "\n";

    // Inject mixin methods (e.g., wxTextEntry methods into wxTextCtrl).
    // mixin_map: consumer class → list of mixin class names.
    const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_it =
        ffi_data.mixin_map.find(class_info.name);
    if (mixin_it != ffi_data.mixin_map.end())
    {
        for (const auto& mixin_name: mixin_it->second)
        {
            if (wrapped_classes.contains(mixin_name))
            {
                const std::string mixin_file = LuaClassFileName(mixin_name);
                const std::string mixin_module = mixin_file.substr(0, mixin_file.size() - 4);
                const std::string local_var = "_mixin_" + mixin_name;
                output << "local " << local_var << " = require(\"" << mixin_module << "\")\n";
                output << "for _k, _v in pairs(" << local_var
                       << ") do if M[_k] == nil then M[_k] = _v end end\n";
            }
        }
        output << "\n";
    }

    // Ptr accessor
    output << "--- Get the underlying C pointer.\n";
    output << "function M:Ptr() return self._ptr end\n";
    output << "\n";

    // ---------- Constructors ----------
    for (const auto& func: class_info.methods)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        if (!func.is_constructor || func.has_self)
        {
            continue;  // Only true constructors (no self param)
        }

        // Build idiomatic param list.
        std::vector<std::vector<LuaIdiomParam>> param_groups;
        for (const auto& param: func.params)
        {
            if (param.macro_name == "TSelf")
            {
                continue;
            }
            std::vector<LuaIdiomParam> group = ConvertToLuaIdiomParams(param, true);
            param_groups.push_back(std::move(group));
        }

        // Constructor function name: "Create" -> M.Create, "CreateEmpty" -> M.CreateEmpty
        output << "--- Constructor: " << CFuncName(func) << "\n";
        output << "function M." << func.method_name << "(";
        EmitLuaParamNames(output, param_groups);
        output << ")\n";

        EmitLuaPreCalls(output, param_groups);

        // C call.
        const std::string c_call = BuildLuaCCall(func, param_groups, "");
        output << "    local ptr = " << c_call << "\n";

        EmitLuaPostCalls(output, param_groups);

        // Null check and return.
        output << "    if ptr == nil then return nil end\n";
        output << "    return setmetatable({ _ptr = ptr }, MT)\n";
        output << "end\n";
        output << "\n";
    }

    // ---------- Methods (non-constructor, non-destructor) ----------
    for (const auto& func: class_info.methods)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        if (func.is_constructor && !func.has_self)
        {
            continue;  // Already emitted above
        }
        if (func.is_destructor)
        {
            continue;  // Emitted separately below
        }

        const bool is_void = IsVoidReturn(func.return_type);
        const bool is_static = IsStaticClassFunction(func, class_info, /*member_of_class=*/true);

        // Build idiomatic param list.  A non-static method always takes the receiver as
        // parameter 0 (TSelf, a TClass(own class) pseudo-self, or an explicit void* pObject /
        // void* self), so that parameter is skipped unconditionally.  A static method has no
        // receiver, so every parameter is a real argument.
        std::vector<std::vector<LuaIdiomParam>> param_groups;
        for (size_t pi = 0; pi < func.params.size(); ++pi)
        {
            if (!is_static && pi == 0)
            {
                continue;  // Receiver: forwarded to the C call as self._ptr
            }
            param_groups.push_back(ConvertToLuaIdiomParams(func.params[pi], false));
        }
        const bool has_post_calls = HasLuaPostCalls(param_groups);

        output << (is_static ? "function M." : "function M:") << func.method_name << "(";
        EmitLuaParamNames(output, param_groups);
        output << ")\n";

        EmitLuaPreCalls(output, param_groups);

        // Build the C call expression. A receiver-less class function is static in
        // wxWidgets, so it forwards no object pointer.
        const std::string c_call = BuildLuaCCall(func, param_groups, is_static ? "" : "self._ptr");

        // Emit call and return.
        if (is_void)
        {
            output << "    " << c_call << "\n";
            EmitLuaPostCalls(output, param_groups);
        }
        else if (has_post_calls)
        {
            // Capture result, cleanup, then return.
            output << "    local _result = " << LuaWrappedReturnExpr(func, c_call, wrapped_classes)
                   << "\n";
            EmitLuaPostCalls(output, param_groups);
            output << "    return _result\n";
        }
        else
        {
            output << "    return " << LuaWrappedReturnExpr(func, c_call, wrapped_classes) << "\n";
        }

        output << "end\n";
        output << "\n";
    }

    // ---------- Destructor ----------
    for (const auto& func: class_info.methods)
    {
        if (!IsValidFunction(func) || !func.is_destructor)
        {
            continue;
        }

        // Check if this is a true destructor (no non-self params) or a list-item
        // delete (e.g., wxChoice_Delete(self, int index)).  The same receiver rule as the
        // method loop decides whether parameter 0 is a receiver at all — a static class
        // function (wxVariantVector_Delete(void* vec)) has none.
        const bool is_static = IsStaticClassFunction(func, class_info, /*member_of_class=*/true);
        bool has_non_self_params = false;
        for (size_t pi = 0; pi < func.params.size(); ++pi)
        {
            if (!is_static && pi == 0)
            {
                continue;  // Receiver, not an argument
            }
            has_non_self_params = true;
        }

        if (has_non_self_params)
        {
            // Not a true destructor — emit as a regular method.
            std::vector<std::vector<LuaIdiomParam>> param_groups;
            for (size_t pi = 0; pi < func.params.size(); ++pi)
            {
                if (!is_static && pi == 0)
                {
                    continue;  // Receiver: forwarded to the C call as self._ptr
                }
                param_groups.push_back(ConvertToLuaIdiomParams(func.params[pi], false));
            }

            output << (is_static ? "function M." : "function M:") << func.method_name << "(";
            EmitLuaParamNames(output, param_groups);
            output << ")\n";

            const std::string c_call =
                BuildLuaCCall(func, param_groups, is_static ? "" : "self._ptr");

            const bool is_void = IsVoidReturn(func.return_type);
            if (is_void)
            {
                output << "    " << c_call << "\n";
            }
            else
            {
                output << "    return " << LuaWrappedReturnExpr(func, c_call, wrapped_classes)
                       << "\n";
            }
            output << "end\n\n";
        }
        else
        {
            // True destructor: guard against double-delete.
            output << "--- Delete the underlying C++ object.\n";
            output << "function M:Delete()\n";
            output << "    if self._ptr ~= nil and not self._borrowed then\n";
            output << "        C." << CFuncName(func) << "(self._ptr)\n";
            output << "        self._ptr = nil\n";
            output << "    end\n";
            output << "end\n";
            output << "\n";
        }
    }

    output << "return M\n";
}

void LuaJITEmitter::GenerateIdiomaticClasses(const ParsedFFI& ffi_data, const fs::path& out_dir)
{
    // Master include file.
    const fs::path master_path = out_dir / "kwxffi_idiomatic_gen.lua";
    ConditionalFileWriter master(master_path);
    if (!master.is_open())
    {
        std::println(stderr, "Error: cannot create {}", master_path.string());
        return;
    }
    WriteGeneratedHeader(master, "--", false);
    master << "-- Master module for idiomatic LuaJIT wxWidgets wrappers.\n";
    master << "-- Usage: local wx = require(\"kwxffi_idiomatic_gen\")\n";
    master << "--        local btn = wx.wxButton.Create(parent, id, \"OK\", ...)\n";
    master << "--        btn:SetLabel(\"Cancel\")\n";
    master << "\n";
    master << "local M = {}\n";
    master << "\n";

    size_t class_count = 0;
    size_t skipped_count = 0;
    size_t method_count = 0;

    // The shared policy is the single source of truth for which classes get a module. It
    // includes zero-method direct wxEvent subclasses, which still need a wrapper so a caller
    // can downcast an event pointer and reuse the inherited wxEvent accessors.
    const std::unordered_set<std::string> wrapped_classes = CollectWrappedClasses(ffi_data);

    for (const auto& class_decl: ffi_data.classes)
    {
        if (!wrapped_classes.contains(class_decl.name))
        {
            continue;
        }
        if (kSkipClass.contains(class_decl.name))
        {
            ++skipped_count;
            continue;
        }

        const std::string file_name = LuaClassFileName(class_decl.name);
        const fs::path file_path = out_dir / file_name;

        ConditionalFileWriter writer(file_path);
        if (!writer.is_open())
        {
            std::println(stderr, "Error: cannot create {}", file_path.string());
            continue;
        }
        ++class_count;

        EmitIdiomaticClassFile(writer, class_decl, ffi_data);

        for (const auto& func: class_decl.methods)
        {
            if (IsValidFunction(func))
            {
                ++method_count;
            }
        }

        // require module name = filename without .lua extension
        const std::string module_name = file_name.substr(0, file_name.size() - 4);
        master << "M." << class_decl.name << " = require(\"" << module_name << "\")\n";
    }

    // Free functions live in their own module; merge them in without clobbering a class of
    // the same name.
    master << "\n";
    master << "local _freefuncs = require(\"kwxffi_freefuncs_idiomatic_gen\")\n";
    master << "for _k, _v in pairs(_freefuncs) do if M[_k] == nil then M[_k] = _v end end\n";
    master << "\nreturn M\n";

    std::print(stderr, "  kwxffi_idiomatic_gen.lua:    {} classes, {} methods", class_count,
               method_count);
    if (skipped_count > 0)
    {
        std::print(stderr, " ({} skipped)", skipped_count);
    }
    std::println(stderr, "");
}

// -------------------------------------------------------------------------
// UI descriptor (emit-ui / check-ui)
// -------------------------------------------------------------------------

// The Lua shape of one descriptor argument.  Nothing validates this string — it only tells a
// consumer what to pass — so it is derived from the FFI macro rather than from a type map.
static std::string LuaUiParamType(const Param& param)
{
    if (param.macro_name == "TSelf")
    {
        return "self";
    }
    if (param.macro_name == "TClass" || param.macro_name == "TClassRef")
    {
        if (param.macro_arg == "wxString")
        {
            return "string";
        }
        return param.macro_arg.empty() ? "cdata" : param.macro_arg;
    }
    if (param.raw_type == "TString" || param.macro_name == "TString" ||
        param.raw_type == "TStringVoid")
    {
        return "string";
    }
    if (param.macro_name == "TBool" || param.raw_type == "TBool")
    {
        return "bool";
    }
    if (param.raw_type.contains('*'))
    {
        return "cdata";
    }
    return "int";
}

// Every idiomatic module publishes `function M:Ptr()`.  EmitIdiomaticClassFile() writes that
// accessor literally, from no model declaration, so no helper can supply the name.
static UiCallable LuaUiPtrCallable()
{
    UiCallable callable;
    callable.symbol = "Ptr";
    callable.idiom = "method-on-self";
    return callable;
}

static UiCallable LuaUiUnsupportedCallable()
{
    UiCallable callable;
    callable.idiom = "unsupported";
    callable.reason = "no_method";
    return callable;
}

// The argument list the emitter writes for a constructor: every parameter except a TSelf
// receiver, each expanded by the same ConvertToLuaIdiomParams() the emitter calls.
static std::vector<UiParam> LuaUiCtorParams(const FunctionDecl& func)
{
    std::vector<UiParam> params;
    for (const Param& param: func.params)
    {
        if (param.macro_name == "TSelf")
        {
            continue;
        }
        for (const LuaIdiomParam& idiom_param:
             ConvertToLuaIdiomParams(param, /*in_constructor=*/true))
        {
            params.push_back(UiParam { .name = idiom_param.name, .type = LuaUiParamType(param) });
        }
    }
    return params;
}

// The argument list the emitter writes for a colon method: parameter 0 of a non-static method is
// the receiver it forwards as self._ptr, so it is not part of the descriptor's params.
static std::vector<UiParam> LuaUiMethodParams(const FunctionDecl& func,
                                              const ClassInfo& owning_class)
{
    const bool is_static = IsStaticClassFunction(func, owning_class, /*member_of_class=*/true);
    std::vector<UiParam> params;
    for (size_t index = 0; index < func.params.size(); ++index)
    {
        if (!is_static && index == 0)
        {
            continue;  // Receiver
        }
        for (const LuaIdiomParam& idiom_param: ConvertToLuaIdiomParams(func.params[index], false))
        {
            params.push_back(
                UiParam { .name = idiom_param.name, .type = LuaUiParamType(func.params[index]) });
        }
    }
    return params;
}

static UiCallable LuaUiMethodCallable(const ParsedFFI& ffi_data, const ClassInfo& consumer_class,
                                      const FunctionDecl& func)
{
    UiCallable callable;
    callable.symbol = LuaEmittedMemberName(func);

    // A constructor is published as `function M.<name>(...)` and called with a dot, so every
    // parameter — including one the member form would treat as a receiver — is an argument.
    if (func.is_constructor && !func.has_self)
    {
        callable.params = LuaUiCtorParams(func);
        callable.idiom = "constructor";
        callable.returns = consumer_class.name;
        std::map<std::string, std::string> sentinels;
        for (const UiParam& param: callable.params)
        {
            if (param.name == "parent")
            {
                sentinels.emplace("parent", "nil");
            }
        }
        if (!sentinels.empty())
        {
            callable.sentinels = std::move(sentinels);
        }
        return callable;
    }

    // The emitter classifies static-vs-instance against the class that declares the method, so a
    // mixin method is judged by the mixin exactly as its own module is emitted.
    const ClassInfo* const declaring_class = UiFindClass(ffi_data, func.class_name);
    const ClassInfo& declaring = declaring_class != nullptr ? *declaring_class : consumer_class;
    const bool is_static = IsStaticClassFunction(func, declaring, /*member_of_class=*/true);
    callable.params = LuaUiMethodParams(func, declaring);

    if (is_static)
    {
        callable.idiom = "procedure";  // emitted as `function M.<name>(...)`
    }
    else if (!func.class_name.empty() && func.class_name != consumer_class.name)
    {
        // The method is declared on an ancestor or mixin but invoked on this instance, so it is
        // method-on-self; `owner` records the declaring class.  method-on-parent is reserved for
        // a call on the parent whose result is a child handle (wxStdDialogButtonSizer.ctor).
        callable.idiom = "method-on-self";
        callable.owner = func.class_name;
    }
    else
    {
        callable.idiom = "method-on-self";
    }

    // Only a returned wrapper class is a new handle; a returned wxString becomes a Lua string.
    if (func.return_macro == "TClass" && !func.return_arg.empty() && func.return_arg != "wxString")
    {
        callable.returns = func.return_arg;
    }
    return callable;
}

// Resolve a role from ordered candidate method names, walking the class, its mixins and its
// ancestors — the first emitted declaration wins.
static UiCallable LuaUiRoleCallable(const ParsedFFI& ffi_data, const ClassInfo& class_info,
                                    const std::vector<std::string_view>& method_names)
{
    for (const std::string_view method_name: method_names)
    {
        const FunctionDecl* const func = UiFindMethod(ffi_data, class_info.name, method_name);
        if (func != nullptr)
        {
            return LuaUiMethodCallable(ffi_data, class_info, *func);
        }
    }
    return LuaUiUnsupportedCallable();
}

// The class's own Create() factory — the constructor EmitIdiomaticClassFile() publishes as
// `M.Create(...)`.  A parent's factory is not usable, because the module only emits the class's
// own methods.
static UiCallable LuaUiCtorCallable(const ParsedFFI& ffi_data, const ClassInfo& class_info)
{
    const FunctionDecl* create_decl = nullptr;
    for (const FunctionDecl& func: class_info.methods)
    {
        if (!IsValidFunction(func) || !func.is_constructor || func.has_self)
        {
            continue;
        }
        if (func.method_name == "Create")
        {
            create_decl = &func;
            break;
        }
        if (create_decl == nullptr)
        {
            create_decl = &func;  // any other factory, used only when Create() is absent
        }
    }
    if (create_decl == nullptr)
    {
        return LuaUiUnsupportedCallable();
    }
    return LuaUiMethodCallable(ffi_data, class_info, *create_decl);
}

// A std dialog button sizer is never constructed on its own: it comes from the dialog it belongs
// to, so its ctor is wxDialog's method, not wxStdDialogButtonSizer's own Create().
static UiCallable LuaUiStdButtonSizerCtor(const ParsedFFI& ffi_data)
{
    const FunctionDecl* const func =
        UiFindMethod(ffi_data, "wxDialog", "CreateStdDialogButtonSizer");
    const ClassInfo* const dialog_class = UiFindClass(ffi_data, "wxDialog");
    if (func == nullptr || dialog_class == nullptr)
    {
        return LuaUiUnsupportedCallable();
    }

    UiCallable callable;
    callable.symbol = LuaEmittedMemberName(*func);
    callable.params = LuaUiMethodParams(*func, *dialog_class);
    callable.idiom = "method-on-parent";
    callable.owner = "wxDialog";
    callable.returns = "wxStdDialogButtonSizer";
    return callable;
}

// True when kwxffi_constants_gen.lua exposes this name.  GenerateConstants() keeps a scalar or a
// wxString accessor and drops every other pointer-returning accessor.
static bool LuaEmitsConstant(const ParsedFFI& ffi_data, std::string_view constant_name)
{
    for (const ConstantDecl& constant: ffi_data.constants)
    {
        if (constant.constant_name != constant_name)
        {
            continue;
        }
        if (constant.return_type.contains('*') && !constant.return_type.contains("wxString"))
        {
            continue;
        }
        return true;
    }
    return false;
}

// One role of a required class and the method names that can satisfy it, most preferred first.
struct LuaUiRoleSpec
{
    std::string_view role;
    std::vector<std::string_view> method_names;
};

// Fill one role, recording an `unsupported` entry when no emitted method satisfies it.
static void LuaUiAddRole(const ParsedFFI& ffi_data, const ClassInfo& class_info,
                         const std::string& role, const std::vector<std::string_view>& method_names,
                         UiClass& ui_class, std::vector<UiUnsupported>& unsupported)
{
    UiCallable callable = LuaUiRoleCallable(ffi_data, class_info, method_names);
    if (callable.symbol.empty())
    {
        unsupported.push_back(
            UiUnsupported { .class_name = class_info.name, .role = role, .reason = "no_method" });
        return;
    }
    ui_class.roles.emplace(role, std::move(callable));
}

// Describe one required class in `classes`, or list it in `unsupported` when it has no usable
// constructor — never both.
static void LuaUiDescribeClass(const ParsedFFI& ffi_data, std::string_view class_name,
                               std::initializer_list<LuaUiRoleSpec> role_specs,
                               std::initializer_list<std::string_view> constant_names,
                               UiDescriptor& descriptor)
{
    const ClassInfo* const class_info = UiFindClass(ffi_data, class_name);
    if (class_info == nullptr)
    {
        descriptor.unsupported.push_back(UiUnsupported {
            .class_name = std::string(class_name), .role = "", .reason = "no_method" });
        return;
    }

    UiClass ui_class;
    ui_class.ctor = LuaUiCtorCallable(ffi_data, *class_info);
    if (ui_class.ctor.symbol.empty())
    {
        descriptor.unsupported.push_back(
            UiUnsupported { .class_name = class_info->name, .role = "", .reason = "no_method" });
        return;
    }

    ui_class.type = class_info->name;
    ui_class.idiom = "constructor";

    for (const LuaUiRoleSpec& spec: role_specs)
    {
        if (spec.role == "ptr")
        {
            ui_class.roles.emplace(std::string(spec.role), LuaUiPtrCallable());
            continue;
        }
        LuaUiAddRole(ffi_data, *class_info, std::string(spec.role), spec.method_names, ui_class,
                     descriptor.unsupported);
    }

    for (const std::string_view constant_name: constant_names)
    {
        if (!LuaEmitsConstant(ffi_data, constant_name))
        {
            continue;
        }
        ui_class.constants.emplace(std::string(constant_name),
                                   "require(\"kwxffi_constants_gen\")." +
                                       std::string(constant_name));
    }

    descriptor.classes.emplace(class_info->name, std::move(ui_class));
}

// -------------------------------------------------------------------------
// LuaJITEmitter::BuildUiDescriptor
// -------------------------------------------------------------------------

UiDescriptor LuaJITEmitter::BuildUiDescriptor(const ParsedFFI& parsed_ffi) const
{
    // VerifyUiDescriptor has no model parameter and emit-ui calls the two methods back to back on
    // the same emitter, so the model is kept here for the verification pass to regenerate from.
    m_ui_model = parsed_ffi;

    UiDescriptor descriptor;

    descriptor.naming = {
        { "class_type",
          "Lua module table wx.<ClassName> (e.g. wx.wxFrame) - a metatable-backed wrapper table "
          "holding the raw pointer in _ptr" },
        { "constructor",
          "Dotted module function: wx.wxFrame.Create(parent, id, text, left, top, width, height, "
          "style)" },
        { "method",
          "Colon method on the wrapper handle: handle:Method(...).  A receiverless (static) class "
          "function uses a dot: M.Name(...)" },
        { "constant", "Name resolved lazily from require(\"kwxffi_constants_gen\"), e.g. ID_ANY, "
                      "DEFAULT_FRAME_STYLE" },
        { "module",
          "kwxffi_idiomatic_gen, which re-exports each per-class <classname>_gen.lua module and "
          "kwxffi_freefuncs_idiomatic_gen" },
        { "event_bind",
          "Bind lives on the wxEvtHandler module (wxevthandler_gen.lua) and is inherited by every "
          "window: M:Bind(first, last, type, closure).  The id form passes the id as both first "
          "and last" },
    };

    LuaUiDescribeClass(parsed_ffi, "wxFrame",
                       {
                           { "show", { "Show" } },
                           { "hide", { "Hide" } },
                           { "set_title", { "SetTitle" } },
                           { "set_size", { "SetSize" } },
                           { "set_min_size", { "SetMinSize" } },
                           { "center", { "Center", "Centre" } },
                           { "set_sizer", { "SetSizer" } },
                           { "set_font", { "SetFont" } },
                           { "set_icon", { "SetIcon" } },
                           { "create_statusbar", { "CreateStatusBar" } },
                           { "set_menubar", { "SetMenuBar" } },
                           { "bind", { "Bind" } },
                           { "bind_id", { "Bind" } },
                           { "destroy", { "Destroy" } },
                           { "ptr", {} },
                           { "delete", { "Delete" } },
                       },
                       { "ID_ANY", "DEFAULT_FRAME_STYLE" }, descriptor);

    LuaUiDescribeClass(parsed_ffi, "wxDialog",
                       {
                           { "show", { "Show" } },
                           { "hide", { "Hide" } },
                           { "set_title", { "SetTitle" } },
                           { "set_size", { "SetSize" } },
                           { "set_min_size", { "SetMinSize" } },
                           { "center", { "Center", "Centre" } },
                           { "set_sizer", { "SetSizer" } },
                           { "set_font", { "SetFont" } },
                           { "set_icon", { "SetIcon" } },
                           { "show_modal", { "ShowModal" } },
                           { "end_modal", { "EndModal" } },
                           { "set_escape_id", { "SetEscapeId" } },
                           { "set_affirmative_id", { "SetAffirmativeId" } },
                           { "bind", { "Bind" } },
                           { "bind_id", { "Bind" } },
                           { "destroy", { "Destroy" } },
                           { "ptr", {} },
                           { "delete", { "Delete" } },
                       },
                       { "ID_ANY" }, descriptor);

    LuaUiDescribeClass(parsed_ffi, "wxTextCtrl",
                       {
                           { "show", { "Show" } },
                           { "hide", { "Hide" } },
                           { "set_value", { "SetValue" } },
                           { "set_label", { "SetLabel" } },
                           { "set_size", { "SetSize" } },
                           { "set_min_size", { "SetMinSize" } },
                           { "set_font", { "SetFont" } },
                           { "set_size_hints", { "SetSizeHints" } },
                           { "bind", { "Bind" } },
                           { "bind_id", { "Bind" } },
                           { "destroy", { "Destroy" } },
                           { "ptr", {} },
                           { "delete", { "Delete" } },
                       },
                       { "ID_ANY" }, descriptor);

    LuaUiDescribeClass(parsed_ffi, "wxBoxSizer",
                       {
                           { "add_window", { "AddWindow" } },
                           { "add_sizer", { "AddSizer" } },
                           { "add_spacer", { "AddSpacer" } },
                           { "destroy", {} },
                           { "ptr", {} },
                           { "delete", { "Delete" } },
                       },
                       { "VERTICAL", "HORIZONTAL" }, descriptor);

    LuaUiDescribeClass(parsed_ffi, "wxStaticBitmap",
                       {
                           { "set_bitmap", { "SetBitmap" } },
                           { "set_size", { "SetSize" } },
                           { "set_min_size", { "SetMinSize" } },
                           { "show", { "Show" } },
                           { "hide", { "Hide" } },
                           { "destroy", { "Destroy" } },
                           { "ptr", {} },
                           { "delete", { "Delete" } },
                       },
                       { "ID_ANY" }, descriptor);

    LuaUiDescribeClass(parsed_ffi, "wxStdDialogButtonSizer",
                       {
                           { "add_button", { "AddButton" } },
                           { "realize", { "Realize" } },
                           { "add_window", { "AddWindow" } },
                           { "destroy", {} },
                           { "ptr", {} },
                           { "delete", { "Delete" } },
                       },
                       {}, descriptor);

    const std::map<std::string, UiClass>::iterator std_button_iter =
        descriptor.classes.find("wxStdDialogButtonSizer");
    if (std_button_iter != descriptor.classes.end())
    {
        UiCallable sizer_ctor = LuaUiStdButtonSizerCtor(parsed_ffi);
        if (sizer_ctor.symbol.empty())
        {
            // Without the dialog factory the class cannot be built at all, so it moves to
            // unsupported as a whole rather than staying in classes without a constructor.
            descriptor.unsupported.push_back(UiUnsupported {
                .class_name = "wxStdDialogButtonSizer", .role = "", .reason = "no_method" });
            descriptor.classes.erase(std_button_iter);
        }
        else
        {
            std_button_iter->second.ctor = std::move(sizer_ctor);
            std_button_iter->second.idiom = "method-on-parent";
        }
    }

    LuaUiDescribeClass(parsed_ffi, "wxSizerFlags",
                       {
                           { "proportion", { "Proportion" } },
                           { "expand", { "Expand" } },
                           { "border", { "Border" } },
                           { "left", { "Left" } },
                           { "right", { "Right" } },
                           { "top", { "Top" } },
                           { "bottom", { "Bottom" } },
                           { "align_h", { "CenterHorizontal", "Align" } },
                           { "align_v", { "CenterVertical", "Align" } },
                           { "delete", { "Delete" } },
                       },
                       { "EXPAND", "ALL", "ALIGN_CENTER", "ALIGN_LEFT", "ALIGN_RIGHT", "ALIGN_TOP",
                         "ALIGN_BOTTOM" },
                       descriptor);

    // Every other class the selection names gets a constructor-only entry, and the classes this
    // backend cannot express are recorded in `unsupported` rather than silently omitted, so a
    // consumer can tell "not modelled" from "model has no such class".  For `--classes form` the
    // resolved list is exactly the required classes, all handled above, so this loop is a no-op.
    std::vector<std::string> missing;
    const std::vector<std::string> selected_classes =
        UiResolveClassSelection(parsed_ffi, ui_class_selection_, missing);

    const CoverageInfo coverage = Coverage(parsed_ffi);
    const std::unordered_set<std::string> wrapped(coverage.wrapped_classes.begin(),
                                                  coverage.wrapped_classes.end());
    for (const std::string& class_name: selected_classes)
    {
        if (UiIsRequiredClass(class_name) || descriptor.classes.contains(class_name))
        {
            continue;  // owned by the explicit work above
        }
        const ClassInfo* const class_info = UiFindClass(parsed_ffi, class_name);
        if (class_info == nullptr)
        {
            continue;
        }
        // A class outside `wrapped` has no generated module at all (hand-maintained, skipped or
        // consumer-provided), so a constructor naming it would point at a wrapper that is never
        // generated.
        if (!wrapped.contains(class_name))
        {
            descriptor.unsupported.push_back(
                UiUnsupported { .class_name = class_name, .role = "", .reason = "not_supported" });
            continue;
        }
        if (UiFindCanonicalConstructor(parsed_ffi, class_name) == nullptr)
        {
            descriptor.unsupported.push_back(
                UiUnsupported { .class_name = class_name, .role = "", .reason = "no_method" });
            continue;
        }

        // Same spelling as LuaUiDescribeClass: `type` is the model's class name and
        // LuaUiCtorCallable() names the constructor, so the descriptor's symbol is exactly the one
        // the generated Lua module defines — emit-ui --verify depends on that.
        UiClass ui_class;
        ui_class.type = class_info->name;
        ui_class.ctor = LuaUiCtorCallable(parsed_ffi, *class_info);
        if (ui_class.type.empty() || ui_class.ctor.symbol.empty())
        {
            descriptor.unsupported.push_back(
                UiUnsupported { .class_name = class_name, .role = "ctor", .reason = "no_naming" });
            continue;
        }
        ui_class.idiom = "constructor";
        ui_class.ctor.idiom = "constructor";
        ui_class.ctor.returns = class_name;
        descriptor.classes.emplace(class_name, std::move(ui_class));
    }

    // Every global block is filled with a reason-carrying placeholder first, so a class missing
    // from the model leaves a valid descriptor rather than a symbol-less callable.
    descriptor.sizers.wx_box_sizer.ctor = LuaUiUnsupportedCallable();
    descriptor.sizers.wx_box_sizer.add_window = LuaUiUnsupportedCallable();
    descriptor.sizers.wx_box_sizer.add_sizer = LuaUiUnsupportedCallable();
    descriptor.sizers.wx_box_sizer.add_spacer = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.ctor = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.proportion = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.expand = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.border = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.left = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.right = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.top = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.bottom = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.align_h = LuaUiUnsupportedCallable();
    descriptor.sizers.flags.align_v = LuaUiUnsupportedCallable();
    descriptor.events.bind = LuaUiUnsupportedCallable();
    descriptor.events.bind_id = LuaUiUnsupportedCallable();
    descriptor.bitmap.from_base64 = LuaUiUnsupportedCallable();
    descriptor.bitmap.get_bitmap = LuaUiUnsupportedCallable();
    descriptor.bitmap.delete_fn = LuaUiUnsupportedCallable();
    descriptor.font.create = LuaUiUnsupportedCallable();
    descriptor.font.delete_fn = LuaUiUnsupportedCallable();
    descriptor.std_buttons.create = LuaUiUnsupportedCallable();
    descriptor.std_buttons.add_button = LuaUiUnsupportedCallable();
    descriptor.std_buttons.realize = LuaUiUnsupportedCallable();

    const ClassInfo* const box_sizer = UiFindClass(parsed_ffi, "wxBoxSizer");
    if (box_sizer != nullptr)
    {
        UiSizerOps& sizer_ops = descriptor.sizers.wx_box_sizer;
        sizer_ops.ctor = LuaUiCtorCallable(parsed_ffi, *box_sizer);
        sizer_ops.add_window = LuaUiRoleCallable(parsed_ffi, *box_sizer, { "AddWindow" });
        sizer_ops.add_sizer = LuaUiRoleCallable(parsed_ffi, *box_sizer, { "AddSizer" });
        sizer_ops.add_spacer = LuaUiRoleCallable(parsed_ffi, *box_sizer, { "AddSpacer" });
    }

    const ClassInfo* const sizer_flags = UiFindClass(parsed_ffi, "wxSizerFlags");
    if (sizer_flags != nullptr)
    {
        UiFlags& flags = descriptor.sizers.flags;
        flags.ctor = LuaUiCtorCallable(parsed_ffi, *sizer_flags);
        flags.proportion = LuaUiRoleCallable(parsed_ffi, *sizer_flags, { "Proportion" });
        flags.expand = LuaUiRoleCallable(parsed_ffi, *sizer_flags, { "Expand" });
        flags.border = LuaUiRoleCallable(parsed_ffi, *sizer_flags, { "Border" });
        flags.left = LuaUiRoleCallable(parsed_ffi, *sizer_flags, { "Left" });
        flags.right = LuaUiRoleCallable(parsed_ffi, *sizer_flags, { "Right" });
        flags.top = LuaUiRoleCallable(parsed_ffi, *sizer_flags, { "Top" });
        flags.bottom = LuaUiRoleCallable(parsed_ffi, *sizer_flags, { "Bottom" });
        flags.align_h =
            LuaUiRoleCallable(parsed_ffi, *sizer_flags, { "CenterHorizontal", "Align" });
        flags.align_v = LuaUiRoleCallable(parsed_ffi, *sizer_flags, { "CenterVertical", "Align" });
    }

    const ClassInfo* const evt_handler = UiFindClass(parsed_ffi, "wxEvtHandler");
    if (evt_handler != nullptr)
    {
        descriptor.events.bind = LuaUiRoleCallable(parsed_ffi, *evt_handler, { "Bind" });
        descriptor.events.bind_id = LuaUiRoleCallable(parsed_ffi, *evt_handler, { "Bind" });
    }
    descriptor.events.handler_type =
        "function(event_ptr) - a Lua closure wrapped in a wxClosure and passed as Bind's closure "
        "argument; event_ptr is the raw wxEvent pointer the handler receives";

    const ClassInfo* const bitmap_class = UiFindClass(parsed_ffi, "wxBitmap");
    if (bitmap_class != nullptr)
    {
        descriptor.bitmap.from_base64 =
            LuaUiRoleCallable(parsed_ffi, *bitmap_class, { "CreateFromBase64" });
        descriptor.bitmap.delete_fn = LuaUiRoleCallable(parsed_ffi, *bitmap_class, { "Delete" });
    }
    const ClassInfo* const bundle_class = UiFindClass(parsed_ffi, "wxBitmapBundle");
    if (bundle_class != nullptr)
    {
        descriptor.bitmap.get_bitmap =
            LuaUiRoleCallable(parsed_ffi, *bundle_class, { "GetBitmap" });
    }

    const ClassInfo* const font_class = UiFindClass(parsed_ffi, "wxFont");
    if (font_class != nullptr)
    {
        descriptor.font.create = LuaUiRoleCallable(parsed_ffi, *font_class, { "Create" });
        descriptor.font.delete_fn = LuaUiRoleCallable(parsed_ffi, *font_class, { "Delete" });
    }

    descriptor.std_buttons.create = LuaUiStdButtonSizerCtor(parsed_ffi);
    if (descriptor.std_buttons.create.symbol.empty())
    {
        descriptor.std_buttons.create = LuaUiUnsupportedCallable();
    }
    const ClassInfo* const std_button_class = UiFindClass(parsed_ffi, "wxStdDialogButtonSizer");
    if (std_button_class != nullptr)
    {
        descriptor.std_buttons.add_button =
            LuaUiRoleCallable(parsed_ffi, *std_button_class, { "AddButton" });
        descriptor.std_buttons.realize =
            LuaUiRoleCallable(parsed_ffi, *std_button_class, { "Realize" });
    }

    // The Lua layer owns no entry point: an application starts by requiring the idiomatic module
    // and driving the event loop itself, so emit_entry stays false.  Nothing in the generated
    // tree sets the top-level window (kwxApp_SetTopWindow lives in examples/CApp), so the block
    // carries a reason instead of a symbol.
    descriptor.app.entry = "kwxffi_idiomatic_gen";
    descriptor.app.entry_signature = "local wx = require(\"kwxffi_idiomatic_gen\")";
    descriptor.app.set_top_window = LuaUiUnsupportedCallable();
    descriptor.app.emit_entry = false;

    return descriptor;
}

// -------------------------------------------------------------------------
// LuaJITEmitter::VerifyUiDescriptor
// -------------------------------------------------------------------------

// One `function M:Name(...)` / `function M.Name(...)` declaration found in the generated tree.
struct LuaUiDeclaration
{
    std::string name;
    size_t arg_count = 0;
};

// Collect every declaration in one generated file.  EmitIdiomaticClassFile() always writes a
// signature on a single line, so a line at a time is sufficient.
static void LuaCollectDeclarations(const fs::path& file_path,
                                   std::vector<LuaUiDeclaration>& declarations)
{
    std::ifstream input(file_path, std::ios::binary);
    if (!input.is_open())
    {
        return;
    }

    std::string line;
    while (std::getline(input, line))
    {
        const size_t header_pos = line.find("function M");
        if (header_pos == std::string::npos)
        {
            continue;
        }

        size_t cursor = header_pos + std::string_view("function M").size();
        if (cursor >= line.size())
        {
            continue;
        }
        const char separator = line[cursor];
        if (separator != ':' && separator != '.')
        {
            continue;
        }
        ++cursor;

        const size_t name_start = cursor;
        while (cursor < line.size() &&
               (std::isalnum(static_cast<unsigned char>(line[cursor])) != 0 || line[cursor] == '_'))
        {
            ++cursor;
        }
        if (cursor == name_start)
        {
            continue;
        }
        const std::string declaration_name = line.substr(name_start, cursor - name_start);

        while (cursor < line.size() && line[cursor] == ' ')
        {
            ++cursor;
        }
        if (cursor >= line.size() || line[cursor] != '(')
        {
            continue;
        }
        const size_t args_start = cursor + 1;
        const size_t args_end = line.find(')', args_start);
        if (args_end == std::string::npos)
        {
            continue;
        }

        const std::string args = line.substr(args_start, args_end - args_start);
        size_t arg_count = 0;
        bool has_argument = false;
        for (const char argument_char: args)
        {
            if (std::isspace(static_cast<unsigned char>(argument_char)) == 0)
            {
                has_argument = true;
            }
            if (argument_char == ',')
            {
                ++arg_count;
            }
        }
        if (has_argument)
        {
            ++arg_count;
        }

        declarations.push_back(
            LuaUiDeclaration { .name = declaration_name, .arg_count = arg_count });
    }
}

// Every callable the descriptor declares, labelled the way `--verify` reports it.
static void LuaUiCollectCallables(const UiDescriptor& descriptor,
                                  std::vector<std::pair<std::string, const UiCallable*>>& callables)
{
    for (const auto& [class_name, class_info]: descriptor.classes)
    {
        callables.emplace_back(class_name + ".ctor", &class_info.ctor);
        for (const auto& [role, callable]: class_info.roles)
        {
            callables.emplace_back(class_name + "." + role, &callable);
        }
    }

    const UiSizerOps& sizer_ops = descriptor.sizers.wx_box_sizer;
    callables.emplace_back("sizers.wxBoxSizer.ctor", &sizer_ops.ctor);
    callables.emplace_back("sizers.wxBoxSizer.add_window", &sizer_ops.add_window);
    callables.emplace_back("sizers.wxBoxSizer.add_sizer", &sizer_ops.add_sizer);
    callables.emplace_back("sizers.wxBoxSizer.add_spacer", &sizer_ops.add_spacer);

    const UiFlags& flags = descriptor.sizers.flags;
    callables.emplace_back("sizers.flags.ctor", &flags.ctor);
    callables.emplace_back("sizers.flags.proportion", &flags.proportion);
    callables.emplace_back("sizers.flags.expand", &flags.expand);
    callables.emplace_back("sizers.flags.border", &flags.border);
    callables.emplace_back("sizers.flags.left", &flags.left);
    callables.emplace_back("sizers.flags.right", &flags.right);
    callables.emplace_back("sizers.flags.top", &flags.top);
    callables.emplace_back("sizers.flags.bottom", &flags.bottom);
    callables.emplace_back("sizers.flags.align_h", &flags.align_h);
    callables.emplace_back("sizers.flags.align_v", &flags.align_v);

    callables.emplace_back("events.bind", &descriptor.events.bind);
    callables.emplace_back("events.bind_id", &descriptor.events.bind_id);
    callables.emplace_back("bitmap.from_base64", &descriptor.bitmap.from_base64);
    callables.emplace_back("bitmap.get_bitmap", &descriptor.bitmap.get_bitmap);
    callables.emplace_back("bitmap.delete", &descriptor.bitmap.delete_fn);
    callables.emplace_back("font.create", &descriptor.font.create);
    callables.emplace_back("font.delete", &descriptor.font.delete_fn);
    callables.emplace_back("std_buttons.create", &descriptor.std_buttons.create);
    callables.emplace_back("std_buttons.add_button", &descriptor.std_buttons.add_button);
    callables.emplace_back("std_buttons.realize", &descriptor.std_buttons.realize);
    callables.emplace_back("app.set_top_window", &descriptor.app.set_top_window);
}

// Reads the tree `generated_dir` already holds and never modifies a generated file.  The tree is
// rebuilt from the model BuildUiDescriptor() was given, so verification judges real emitted code
// rather than whatever happened to be on disk.  Each declared symbol is verified by locating its
// Lua declaration and comparing the argument count — the implicit colon-method receiver is
// excluded from both sides, so `M:SetTitle(title)` has one argument.
std::vector<std::string> LuaJITEmitter::VerifyUiDescriptor(const UiDescriptor& descriptor,
                                                           const fs::path& generated_dir) const
{
    std::vector<std::string> mismatches;
    if (!m_ui_model.has_value())
    {
        return mismatches;  // BuildUiDescriptor never ran, so there is nothing to regenerate
    }

    GenerateInto(*m_ui_model, generated_dir);

    std::vector<std::pair<std::string, const UiCallable*>> callables;
    LuaUiCollectCallables(descriptor, callables);

    std::vector<LuaUiDeclaration> declarations;
    std::error_code iterate_error;
    if (fs::exists(generated_dir))
    {
        for (const auto& entry: fs::recursive_directory_iterator(
                 generated_dir, fs::directory_options::skip_permission_denied, iterate_error))
        {
            std::error_code file_error;
            if (!entry.is_regular_file(file_error) || file_error)
            {
                continue;
            }
            LuaCollectDeclarations(entry.path(), declarations);
        }
    }

    std::vector<std::string> mismatch_lines;
    for (const auto& [label, callable]: callables)
    {
        if (callable->symbol.empty())
        {
            continue;
        }
        bool matched = false;
        for (const LuaUiDeclaration& declaration: declarations)
        {
            if (declaration.name == callable->symbol &&
                declaration.arg_count == callable->params.size())
            {
                matched = true;
                break;
            }
        }
        if (!matched)
        {
            mismatch_lines.push_back("MISMATCH " + label + " " + callable->symbol);
        }
    }
    return mismatch_lines;
}

// NOLINTEND(readability-magic-string)
