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
#include <unordered_set>
#include <vector>

// NOLINTBEGIN(readability-magic-string)

namespace fs = std::filesystem;

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

    // Self param -> handled by method receiver (self._ptr); skip.
    if (param.macro_name == "TSelf")
    {
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

// True if a non-constructor method's first parameter is TClass(ClassName)
// matching the function's own class — acts as self for mixin interface methods.
[[nodiscard]] static bool HasPseudoSelf(const FunctionDecl& func)
{
    if (func.has_self || func.class_name.empty() || func.params.empty())
    {
        return false;
    }
    const Param& first = func.params[0];
    return first.macro_name == "TClass" && first.macro_arg == func.class_name;
}

// True if a method should use Lua ':' (colon) syntax — i.e., it has
// either a real TSelf or a pseudo-self TClass(ClassName) first parameter.
[[nodiscard]] static bool UsesColonSyntax(const FunctionDecl& func)
{
    return func.has_self || HasPseudoSelf(func);
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
// kwxffi_events_gen.lua
// -------------------------------------------------------------------------

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

    // Build the set of wrapped classes for parent resolution.
    std::unordered_set<std::string> wrapped_classes;
    for (const auto& other: ffi_data.classes)
    {
        if (!other.methods.empty() && other.name != "wxString")
        {
            wrapped_classes.insert(other.name);
        }
    }

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
        const bool pseudo_self = HasPseudoSelf(func);

        // Build idiomatic param list (skip TSelf and pseudo-self first param).
        std::vector<std::vector<LuaIdiomParam>> param_groups;
        for (size_t pi = 0; pi < func.params.size(); ++pi)
        {
            const Param& param = func.params[pi];
            if (param.macro_name == "TSelf")
            {
                continue;
            }
            if (pseudo_self && pi == 0)
            {
                continue;  // Skip the TClass(ClassName) acting as self
            }
            param_groups.push_back(ConvertToLuaIdiomParams(param, false));
        }
        const bool has_post_calls = HasLuaPostCalls(param_groups);

        output << "function M:" << func.method_name << "(";
        EmitLuaParamNames(output, param_groups);
        output << ")\n";

        EmitLuaPreCalls(output, param_groups);

        // Build the C call expression.
        const std::string c_call = BuildLuaCCall(func, param_groups, "self._ptr");

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
        // delete (e.g., wxChoice_Delete(self, int index)).
        bool has_non_self_params = false;
        for (const auto& param: func.params)
        {
            if (param.macro_name != "TSelf")
            {
                has_non_self_params = true;
            }
        }

        if (has_non_self_params)
        {
            // Not a true destructor — emit as a regular method.
            std::vector<std::vector<LuaIdiomParam>> param_groups;
            for (const auto& param: func.params)
            {
                if (param.macro_name == "TSelf")
                {
                    continue;
                }
                param_groups.push_back(ConvertToLuaIdiomParams(param, false));
            }

            output << "function M:" << func.method_name << "(";
            EmitLuaParamNames(output, param_groups);
            output << ")\n";

            const std::string c_call = BuildLuaCCall(func, param_groups, "self._ptr");

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
            output << "    if self._ptr ~= nil then\n";
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

    static const std::unordered_set<std::string> kSkipClass = {
        "wxString"  // Lifecycle managed by kwxffi_helpers_gen.lua
    };

    size_t class_count = 0;
    size_t skipped_count = 0;
    size_t method_count = 0;

    for (const auto& class_decl: ffi_data.classes)
    {
        if (class_decl.methods.empty())
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
