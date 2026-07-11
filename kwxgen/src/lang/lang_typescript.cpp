/////////////////////////////////////////////////////////////////////////////
// Purpose:   Deno TypeScript FFI binding generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

// Generated file structure:
//   kwx_ffi_gen.ts          — Deno.dlopen with every C symbol (classes + free functions +
//                             events/keys/constants).  Import `lib` from this module to call
//                             functions directly via lib.symbols.SomeFunc(...).
//   kwx_constants_gen.ts    — Eagerly-initialized numeric exports for all events, keys, and
//                             general constants (calls the FFI accessor functions at load time).
//   kwx_free_functions_gen.ts — TypeScript wrappers for non-class C functions.
//   wx{Class}_gen.ts        — One file per class with a TypeScript class that wraps the FFI.
//   kwx_gen.ts              — Master barrel re-export of every generated module.

#include "lang_typescript.h"

#include "../file_writer.h"
#include "lang_common.h"
#include "typescript_type_map.h"

#include <algorithm>
#include <filesystem>
#include <print>
#include <set>
#include <unordered_set>
#include <vector>

namespace fs = std::filesystem;

// -------------------------------------------------------------------------
// Local helpers
// -------------------------------------------------------------------------

// Return the TypeScript filename for a class: "wxButton" → "wxButton_gen.ts"
[[nodiscard]] static std::string TsClassFileName(const std::string& class_name)
{
    return class_name + "_gen.ts";
}

// Return the TypeScript import path for a class file (Deno resolves .ts automatically).
[[nodiscard]] static std::string TsClassImportPath(const std::string& class_name)
{
    return "./" + class_name + "_gen.ts";
}

// True if a non-constructor method's first parameter is TClass(ClassName) matching
// the function's own class — acts as the implicit "self" receiver for mixin methods.
[[nodiscard]] static bool IsPseudoSelf(const FunctionDecl& func)
{
    if (func.has_self || func.class_name.empty() || func.params.empty())
    {
        return false;
    }
    const Param& first = func.params[0];
    return first.macro_name == "TClass" && first.macro_arg == func.class_name;
}

// True if a destructor has only a TSelf parameter (no item-index or other params).
[[nodiscard]] static bool IsTrueDestructor(const FunctionDecl& func)
{
    if (!func.is_destructor)
    {
        return false;
    }
    for (const auto& param: func.params)
    {
        if (param.macro_name != "TSelf")
        {
            return false;
        }
    }
    return true;
}

// Find the nearest wrapped ancestor of class_name by walking the parent_map chain.
// Returns empty string if no wrapped parent exists (class becomes a root class).
[[nodiscard]] static std::string
    FindTsWrappedParent(const std::string& class_name, const ParsedFFI& ffi,
                        const std::unordered_set<std::string>& wrapped_classes)
{
    std::unordered_map<std::string, std::string>::const_iterator iter =
        ffi.parent_map.find(class_name);
    std::set<std::string> visited;
    while (iter != ffi.parent_map.end())
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
        iter = ffi.parent_map.find(parent);
    }
    return {};
}

// Wraps a single kwx Param into information needed for the idiomatic TS method signature.
// Each returned entry is one visible TypeScript parameter (or a hidden self receiver).
struct WrapParam
{
    std::string name;      // TypeScript parameter name (empty when is_self is true)
    std::string ts_type;   // TypeScript type annotation (e.g., "number", "boolean")
    std::string ffi_expr;  // Expression to pass to the FFI call (e.g., "flag ? 1 : 0")
    bool is_self = false;  // True → not visible in TS signature; ffi_expr is "this._ptr"
};

[[nodiscard]] static std::vector<WrapParam> BuildWrapParams(const Param& param)
{
    std::vector<WrapParam> result;

    // TSelf → hidden receiver, pass this._ptr to the C call
    if (param.macro_name == "TSelf")
    {
        result.push_back({ "", "", "this._ptr", true });
        return result;
    }

    // TBool/TBoolInt → accept boolean in TS, convert to 1/0 for the C call
    if (param.macro_name == "TBool" || param.raw_type == "TBool" || param.raw_type == "TBoolInt" ||
        param.raw_type == "TBool*")
    {
        const std::string pname =
            TsEscapeName(param.param_name.empty() ? "flag" : param.param_name);
        result.push_back({ pname, "boolean", pname + " ? 1 : 0", false });
        return result;
    }

    // All other types: pass through the FFI type mapping
    const std::vector<TsFFIParam> ffi_params = ExpandParamToTsFFI(param);
    for (const auto& fpar: ffi_params)
    {
        result.push_back({ fpar.name, TsRuntimeType(fpar.deno_type), fpar.name, false });
    }
    return result;
}

// Return the TypeScript return type annotation for a method in the class wrapper layer.
// class_name is the enclosing class (used when return is TClass/TSelf → ClassName | null).
[[nodiscard]] static std::string WrapReturnType(const FunctionDecl& func,
                                                const std::string& class_name)
{
    if (func.return_type == "void" || func.return_type.empty())
    {
        return "void";
    }
    if (func.return_macro == "TClass" || func.return_macro == "TSelf" ||
        func.return_macro == "TClassRef")
    {
        // Constructor: return the enclosing class wrapped in null-check.
        // Regular methods returning a pointer: return opaque PointerValue.
        if (func.is_constructor && !func.has_self)
        {
            return class_name + " | null";
        }
        return "Deno.PointerValue";
    }
    if (func.return_type == "TBool" || func.return_type == "TBoolInt")
    {
        return "boolean";
    }
    if (func.return_type == "TString" || func.return_type == "TStringOut" ||
        func.return_type == "TStringVoid")
    {
        return "Deno.PointerValue";
    }
    if (func.return_type == "void*" || func.return_type.find('*') != std::string::npos)
    {
        return "Deno.PointerValue";
    }
    if (func.return_type == "uintptr_t" || func.return_type == "size_t")
    {
        return "bigint";
    }

    // All remaining numeric types (int, long, unsigned, unsigned long, double,
    // float, TArrayLen, TByteStringLen, TChar, TUInt8, time_t, wxUIntPtr, etc.)
    // map to the Deno FFI "number" type.
    return "number";
}

// Emit the return statement for a method wrapper, applying any needed conversions.
// call_expr is the raw lib.symbols.Func(...) expression (without trailing semicolon).
static void EmitWrapReturn(std::ostream& output, const FunctionDecl& func,
                           const std::string& class_name, const std::string& call_expr)
{
    const bool is_void = func.return_type.empty() || func.return_type == "void";
    const bool is_ctor = func.is_constructor && !func.has_self &&
                         (func.return_macro == "TClass" || func.return_macro == "TSelf" ||
                          func.return_macro == "TClassRef");
    const bool is_bool = func.return_type == "TBool" || func.return_type == "TBoolInt";
    const bool is_bigint = func.return_type == "uintptr_t" || func.return_type == "size_t";

    if (is_void)
    {
        output << "    " << call_expr << ";\n";
        return;
    }

    if (is_ctor)
    {
        output << "    const rawPtr = " << call_expr << ";\n";
        output << "    if (rawPtr === null) return null;\n";
        output << "    return new " << class_name << "(rawPtr);\n";
        return;
    }

    if (is_bool)
    {
        output << "    return (" << call_expr << " as number) !== 0;\n";
        return;
    }

    if (is_bigint)
    {
        output << "    return " << call_expr << " as bigint;\n";
        return;
    }

    output << "    return " << call_expr << ";\n";
}

// Emit the Deno.dlopen symbol entry for a single function.
static void EmitSymbolDef(std::ostream& output, const FunctionDecl& func)
{
    const std::string func_name = CFuncName(func);
    const std::string result_str = TsFFIReturnType(func.return_type, func.return_macro);

    // Build the parameters array
    std::vector<TsFFIParam> params;
    for (const auto& param: func.params)
    {
        const std::vector<TsFFIParam> expanded = ExpandParamToTsFFI(param);
        for (const auto& ffi_param: expanded)
        {
            params.push_back(ffi_param);
        }
    }

    output << "  " << func_name << ": {\n";
    output << "    parameters: [";
    for (size_t idx = 0; idx < params.size(); ++idx)
    {
        if (idx > 0)
        {
            output << ", ";
        }
        output << params[idx].deno_type;
    }
    output << "],\n";
    output << "    result: " << result_str << ",\n";
    output << "  },\n";
}

// -------------------------------------------------------------------------
// TypeScriptEmitter public interface
// -------------------------------------------------------------------------

void TypeScriptEmitter::Generate(const ParsedFFI& ffi, const fs::path& out_dir)
{
    if (!fs::create_directories(out_dir))
    {
        if (!fs::exists(out_dir))
        {
            std::println(stderr, "Error: cannot create output directory {}", out_dir.string());
            return;
        }
    }

    GenerateFfi(ffi, out_dir);
    GenerateConstants(ffi, out_dir);
    GenerateHelpers(out_dir);
    GenerateFreeFunctions(ffi, out_dir);
    GenerateClassFiles(ffi, out_dir);
    GenerateIndex(ffi, out_dir);

    std::println(stderr, "TypeScript: generated Deno FFI bindings in {}", out_dir.string());
}

VerifyResult TypeScriptEmitter::Verify(const ParsedFFI& /* ffi */, const fs::path& /* out_dir */)
{
    VerifyResult result;
    result.success = false;
    result.messages.emplace_back("TypeScript verify: use 'kwxgen verify' command instead");
    return result;
}

// -------------------------------------------------------------------------
// kwx_ffi_gen.ts — Deno.dlopen with all C symbols
// -------------------------------------------------------------------------

void TypeScriptEmitter::GenerateFfi(const ParsedFFI& ffi, const fs::path& out_dir)
{
    const fs::path file_path = out_dir / "kwx_ffi_gen.ts";
    ConditionalFileWriter output(file_path);

    WriteGeneratedHeader(output, "//");

    // Platform-specific library name
    output << "const _libName: string = ({\n";
    output << "  windows: \"" << ffi.lib_name << ".dll\",\n";
    output << "  linux:   \"lib" << ffi.lib_name << ".so\",\n";
    output << "  darwin:  \"lib" << ffi.lib_name << ".dylib\",\n";
    output << "} as Record<string, string>)[Deno.build.os] ?? \"" << ffi.lib_name << "\";\n\n";

    output << "// Run with: deno run --allow-ffi your_script.ts\n";
    output << "export const lib = Deno.dlopen(_libName, {\n";

    // Class methods
    std::unordered_set<std::string> emitted_symbols;
    size_t method_count = 0;
    size_t free_count = 0;
    for (const auto& cls: ffi.classes)
    {
        for (const auto& func: cls.methods)
        {
            if (!IsValidFunction(func))
            {
                continue;
            }
            const std::string func_name = CFuncName(func);
            if (!emitted_symbols.insert(func_name).second)
            {
                continue;
            }
            EmitSymbolDef(output, func);
            ++method_count;
        }
    }

    // Free functions
    for (const auto& func: ffi.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        const std::string func_name = CFuncName(func);
        if (!emitted_symbols.insert(func_name).second)
        {
            continue;
        }
        EmitSymbolDef(output, func);
        ++free_count;
    }

    // Event accessor symbols (no parameters, return i32)
    for (const auto& event: ffi.events)
    {
        output << "  " << event.export_name << ": { parameters: [], result: \"i32\" },\n";
    }

    // Key accessor symbols (no parameters, return i32)
    for (const auto& key: ffi.keys)
    {
        output << "  " << key.export_name << ": { parameters: [], result: \"i32\" },\n";
    }

    // Constant accessor symbols (no parameters, return i32 or pointer)
    for (const auto& cnst: ffi.constants)
    {
        const bool is_ptr = cnst.return_type.contains('*');
        const char* result_str = is_ptr ? "\"pointer\"" : "\"i32\"";
        output << "  " << cnst.export_name << ": { parameters: [], result: " << result_str
               << " },\n";
    }

    // Always-available kwxFFI symbols (string buffer utilities)
    if (emitted_symbols.insert("kwxUtf8Buffer_Create").second)
    {
        output << "  kwxUtf8Buffer_Create: { parameters: [\"pointer\"], result: \"pointer\" },\n";
    }
    if (emitted_symbols.insert("kwxUtf8Buffer_Data").second)
    {
        output << "  kwxUtf8Buffer_Data: { parameters: [\"pointer\"], result: \"pointer\" },\n";
    }
    if (emitted_symbols.insert("kwxUtf8Buffer_Delete").second)
    {
        output << "  kwxUtf8Buffer_Delete: { parameters: [\"pointer\"], result: \"void\" },\n";
    }

    output << "} as const);\n";

    std::println(stderr,
                 "  kwx_ffi_gen.ts:          {} class methods, {} free functions, "
                 "{} events, {} keys, {} constants",
                 method_count, free_count, ffi.events.size(), ffi.keys.size(),
                 ffi.constants.size());
}

// -------------------------------------------------------------------------
// kwx_helpers_gen.ts — wxString conversion utilities for generated code
// -------------------------------------------------------------------------

void TypeScriptEmitter::GenerateHelpers(const fs::path& out_dir)
{
    const fs::path file_path = out_dir / "kwx_helpers_gen.ts";
    ConditionalFileWriter output(file_path);

    WriteGeneratedHeader(output, "//");
    output <<
        R"TS(import { lib } from "./kwx_ffi_gen.ts";
import { wxString } from "./wxString_gen.ts";

// --- Helper: create a wxString from a JS string ---
export function createWxString(s: string): wxString
{
    const buf = new TextEncoder().encode(s + "\0");
    const ptr = Deno.UnsafePointer.of(buf);
    const result = wxString.CreateUTF8(ptr);
    if (!result)
    {
        throw new Error(`Failed to create wxString for: ${s}`);
    }
    return result;
}

// --- Helper: read a JS string from a wxString* ---
export function readWxString(wxStrPtr: Deno.PointerValue): string
{
    const buf = lib.symbols.kwxUtf8Buffer_Create(wxStrPtr);
    const data = lib.symbols.kwxUtf8Buffer_Data(buf);
    const result = data ? Deno.UnsafePointerView.getCString(data) : "";
    lib.symbols.kwxUtf8Buffer_Delete(buf);
    return result;
}

// --- Helper: read and delete a wxString* returned from a getter ---
export function readAndDeleteWxString(wxStrPtr: Deno.PointerValue): string
{
    const result = readWxString(wxStrPtr);
    lib.symbols.wxString_Delete(wxStrPtr);
    return result;
}
)TS";

    std::println(stderr, "  kwx_helpers_gen.ts:       wxString conversion helpers");
}

// -------------------------------------------------------------------------
// kwx_constants_gen.ts — eagerly-evaluated constants, events, and keys
// -------------------------------------------------------------------------

void TypeScriptEmitter::GenerateConstants(const ParsedFFI& ffi, const fs::path& out_dir)
{
    const fs::path file_path = out_dir / "kwx_constants_gen.ts";
    ConditionalFileWriter output(file_path);

    WriteGeneratedHeader(output, "//");
    output << "import { lib } from \"./kwx_ffi_gen.ts\";\n\n";

    // Events
    if (!ffi.events.empty())
    {
        output << "// Events\n";
        std::vector<EventDecl> sorted_events = ffi.events;
        std::ranges::sort(sorted_events, {}, &EventDecl::event_name);

        std::string last_event;
        for (const auto& event: sorted_events)
        {
            if (event.event_name == last_event)
            {
                continue;
            }
            last_event = event.event_name;
            output << "export const " << event.event_name << ": number = lib.symbols."
                   << event.export_name << "() as number;\n";
        }
        output << "\n";
    }

    // Keys
    if (!ffi.keys.empty())
    {
        output << "// Keys\n";
        std::vector<KeyDecl> sorted_keys = ffi.keys;
        std::ranges::sort(sorted_keys, {}, &KeyDecl::key_name);

        for (const auto& key: sorted_keys)
        {
            output << "export const " << key.key_name << ": number = lib.symbols."
                   << key.export_name << "() as number;\n";
        }
        output << "\n";
    }

    // General constants
    if (!ffi.constants.empty())
    {
        output << "// Constants\n";
        std::vector<ConstantDecl> sorted_consts = ffi.constants;
        std::ranges::sort(sorted_consts, {}, &ConstantDecl::constant_name);

        for (const auto& cnst: sorted_consts)
        {
            const bool is_ptr = cnst.return_type.contains('*');
            if (is_ptr)
            {
                output << "export const " << cnst.constant_name
                       << ": Deno.PointerValue = lib.symbols." << cnst.export_name
                       << "() as Deno.PointerValue;\n";
            }
            else
            {
                output << "export const " << cnst.constant_name << ": number = lib.symbols."
                       << cnst.export_name << "() as number;\n";
            }
        }
    }

    std::println(stderr, "  kwx_constants_gen.ts:    {} events, {} keys, {} constants",
                 ffi.events.size(), ffi.keys.size(), ffi.constants.size());
}

// -------------------------------------------------------------------------
// kwx_free_functions_gen.ts — free-function wrappers
// -------------------------------------------------------------------------

void TypeScriptEmitter::GenerateFreeFunctions(const ParsedFFI& ffi, const fs::path& out_dir)
{
    if (ffi.free_functions.empty())
    {
        return;
    }

    const fs::path file_path = out_dir / "kwx_free_functions_gen.ts";
    ConditionalFileWriter output(file_path);

    WriteGeneratedHeader(output, "//");
    output << "import { lib } from \"./kwx_ffi_gen.ts\";\n\n";

    size_t func_count = 0;
    for (const auto& func: ffi.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }

        const std::string func_name = CFuncName(func);
        const std::string ret_type = WrapReturnType(func, "");

        // Build visible parameters
        std::vector<WrapParam> wrap_params;
        for (const auto& param: func.params)
        {
            const std::vector<WrapParam> params = BuildWrapParams(param);
            for (const auto& wpar: params)
            {
                wrap_params.push_back(wpar);
            }
        }

        output << "export function " << TsEscapeName(func.method_name) << "(";
        bool first = true;
        for (const auto& wpar: wrap_params)
        {
            if (wpar.is_self)
            {
                continue;
            }
            if (!first)
            {
                output << ", ";
            }
            output << wpar.name << ": " << wpar.ts_type;
            first = false;
        }
        output << "): " << ret_type << " {\n";
        std::string call = "lib.symbols." + func_name + "(";
        bool call_first = true;
        for (const auto& wpar: wrap_params)
        {
            if (!call_first)
            {
                call += ", ";
            }
            call += wpar.ffi_expr;
            call_first = false;
        }
        call += ")";

        EmitWrapReturn(output, func, "", call);

        output << "}\n\n";
        ++func_count;
    }

    std::println(stderr, "  kwx_free_functions_gen.ts: {} free functions", func_count);
}

// -------------------------------------------------------------------------
// wx{Class}_gen.ts — per-class TypeScript wrapper
// -------------------------------------------------------------------------

void TypeScriptEmitter::EmitClassFile(std::ostream& output, const ClassInfo& cls,
                                      const ParsedFFI& ffi)
{
    // Build the set of classes that actually have generated wrapper methods.
    std::unordered_set<std::string> wrapped_classes;
    for (const auto& other: ffi.classes)
    {
        if (!other.methods.empty())
        {
            wrapped_classes.insert(other.name);
        }
    }

    // Find the nearest wrapped ancestor for extends-based inheritance.
    const std::string parent_name = FindTsWrappedParent(cls.name, ffi, wrapped_classes);

    WriteGeneratedHeader(output, "//");
    output << "import { lib } from \"./kwx_ffi_gen.ts\";\n";
    if (!parent_name.empty())
    {
        output << "import { " << parent_name << " } from \"" << TsClassImportPath(parent_name)
               << "\";\n";
    }
    output << "\n";
    output << "export class " << cls.name;
    if (!parent_name.empty())
    {
        output << " extends " << parent_name;
    }
    output << " {\n";
    if (parent_name.empty())
    {
        // Root class (no wrapped parent) — own the pointer field.
        output << "  protected readonly _ptr: Deno.PointerValue;\n\n";
        output << "  constructor(ptr: Deno.PointerValue) {\n";
        output << "    this._ptr = ptr;\n";
        output << "  }\n\n";
    }
    output << "  /** Returns the underlying native pointer. */\n";
    output << "  get ptr(): Deno.PointerValue {\n";
    output << "    return this._ptr;\n";
    output << "  }\n\n";

    // Separate deduplication sets: static and instance methods do not share a namespace.
    std::set<std::string> emitted_static_names;

    // --- Constructors (static factory methods) ---
    for (const auto& func: cls.methods)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        if (!func.is_constructor || func.has_self)
        {
            continue;
        }

        const std::string method_name = func.method_name;
        if (!emitted_static_names.insert(method_name).second)
        {
            continue;  // skip duplicate
        }

        const std::string func_name = CFuncName(func);
        const std::string ret_type = WrapReturnType(func, cls.name);

        std::vector<WrapParam> wrap_params;
        for (const auto& param: func.params)
        {
            const std::vector<WrapParam> params = BuildWrapParams(param);
            for (const auto& wpar: params)
            {
                wrap_params.push_back(wpar);
            }
        }
        output << "  static " << TsEscapeName(method_name) << "(";
        bool first = true;
        for (const auto& wpar: wrap_params)
        {
            if (wpar.is_self)
            {
                continue;
            }
            if (!first)
            {
                output << ", ";
            }
            output << wpar.name << ": " << wpar.ts_type;
            first = false;
        }
        output << "): " << ret_type << " {\n";

        std::string call = "lib.symbols." + func_name + "(";
        bool call_first = true;
        for (const auto& wpar: wrap_params)
        {
            if (!call_first)
            {
                call += ", ";
            }
            call += wpar.ffi_expr;
            call_first = false;
        }
        call += ")";

        EmitWrapReturn(output, func, cls.name, call);

        output << "  }\n\n";
    }

    // --- Destructor ---
    for (const auto& func: cls.methods)
    {
        if (!IsValidFunction(func) || !IsTrueDestructor(func))
        {
            continue;
        }

        const std::string func_name = CFuncName(func);

        output << "  Delete(): void {\n";
        output << "    lib.symbols." << func_name << "(this._ptr);\n";
        output << "  }\n\n";
        output << "  [Symbol.dispose](): void {\n";
        output << "    this.Delete();\n";
        output << "  }\n\n";
        break;
    }

    // --- Regular methods ---
    std::set<std::string> emitted_instance_names;
    for (const auto& func: cls.methods)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        // Skip constructors (emitted above as static)
        if (func.is_constructor && !func.has_self)
        {
            continue;
        }
        // Skip the true destructor (emitted above)
        if (IsTrueDestructor(func))
        {
            continue;
        }

        if (!emitted_instance_names.insert(func.method_name).second)
        {
            continue;  // skip duplicate overload
        }

        const bool pseudo_self = IsPseudoSelf(func);
        const std::string func_name = CFuncName(func);
        const std::string ret_type = WrapReturnType(func, cls.name);

        // Build wrap params; if pseudo-self, treat first param as hidden self
        std::vector<WrapParam> wrap_params;
        for (size_t pidx = 0; pidx < func.params.size(); ++pidx)
        {
            const Param& param = func.params[pidx];
            if (pseudo_self && pidx == 0)
            {
                // First param is TClass(ClassName) acting as self
                wrap_params.push_back({ "", "", "this._ptr", true });
                continue;
            }
            const std::vector<WrapParam> params = BuildWrapParams(param);
            for (const auto& wpar: params)
            {
                wrap_params.push_back(wpar);
            }
        }
        output << "  " << TsEscapeName(func.method_name) << "(";
        bool first = true;
        for (const auto& wpar: wrap_params)
        {
            if (wpar.is_self)
            {
                continue;
            }
            if (!first)
            {
                output << ", ";
            }
            output << wpar.name << ": " << wpar.ts_type;
            first = false;
        }
        output << "): " << ret_type << " {\n";

        // Build FFI call expression
        std::string call = "lib.symbols." + func_name + "(";
        bool call_first = true;

        // TSelf and pseudo-self params are already mapped to this._ptr in BuildWrapParams.
        for (const auto& wpar: wrap_params)
        {
            if (!call_first)
            {
                call += ", ";
            }
            call += wpar.ffi_expr;
            call_first = false;
        }
        call += ")";

        EmitWrapReturn(output, func, cls.name, call);

        output << "  }\n\n";
    }

    output << "}\n";
}

void TypeScriptEmitter::GenerateClassFiles(const ParsedFFI& ffi, const fs::path& out_dir)
{
    std::vector<std::string> class_names;
    size_t total_methods = 0;

    for (const auto& cls: ffi.classes)
    {
        if (cls.methods.empty())
        {
            continue;
        }

        const fs::path file_path = out_dir / TsClassFileName(cls.name);
        ConditionalFileWriter output(file_path);

        EmitClassFile(output, cls, ffi);
        class_names.push_back(cls.name);

        for (const auto& func: cls.methods)
        {
            if (IsValidFunction(func))
            {
                ++total_methods;
            }
        }
    }

    std::println(stderr, "  class files:             {} classes, {} methods", class_names.size(),
                 total_methods);
}

// -------------------------------------------------------------------------
// kwx_gen.ts — master barrel re-export
// -------------------------------------------------------------------------

void TypeScriptEmitter::GenerateIndex(const ParsedFFI& ffi, const fs::path& out_dir)
{
    const fs::path file_path = out_dir / "kwx_gen.ts";
    ConditionalFileWriter output(file_path);

    WriteGeneratedHeader(output, "//");
    output << "// Master barrel re-export for all generated kwxFFI TypeScript bindings.\n";
    output << "// Usage: import { wxButton, EVT_BUTTON } from \"./kwx_gen.ts\";\n\n";

    output << "export { lib } from \"./kwx_ffi_gen.ts\";\n";
    output << "export * from \"./kwx_constants_gen.ts\";\n";

    if (!ffi.free_functions.empty())
    {
        output << "export * from \"./kwx_free_functions_gen.ts\";\n";
    }

    output << "export * from \"./kwx_helpers_gen.ts\";\n";

    // Sort class names for deterministic output
    std::vector<std::string> class_names;
    for (const auto& cls: ffi.classes)
    {
        if (!cls.methods.empty())
        {
            class_names.push_back(cls.name);
        }
    }
    std::ranges::sort(class_names);

    output << "\n";
    for (const auto& name: class_names)
    {
        output << "export { " << name << " } from \"" << TsClassImportPath(name) << "\";\n";
    }

    std::println(stderr, "  kwx_gen.ts:              {} class exports", class_names.size());
}
