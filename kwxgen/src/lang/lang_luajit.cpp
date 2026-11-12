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
#include <print>
#include <set>
#include <unordered_map>
#include <unordered_set>
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

    std::println(stderr, "LuaJIT: generated files in {}", out_dir.string());
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
            writer << "    local _result = " << LuaReturnExpr(func, c_call) << "\n";
            EmitLuaPostCalls(writer, param_groups);
            writer << "    return _result\n";
        }
        else
        {
            writer << "    return " << LuaReturnExpr(func, c_call) << "\n";
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
            output << "    local _result = " << LuaReturnExpr(func, c_call) << "\n";
            EmitLuaPostCalls(output, param_groups);
            output << "    return _result\n";
        }
        else
        {
            output << "    return " << LuaReturnExpr(func, c_call) << "\n";
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
                output << "    return " << LuaReturnExpr(func, c_call) << "\n";
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

// NOLINTEND(readability-magic-string)
