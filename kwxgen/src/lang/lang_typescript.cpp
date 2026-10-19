/////////////////////////////////////////////////////////////////////////////
// Purpose:   TypeScript FFI binding generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////
// CR: [10-19-2026]

// Generated file structure:
//   kwx_ffi_gen.ts          — dlopen with every C symbol (classes + free functions +
//                             events/keys/constants).  Import `lib` from this module to call
//                             functions directly via lib.symbols.SomeFunc(...).
//   kwx_constants_gen.ts    — Numeric exports for all events, keys, and general constants;
//                             integer values come from one lazily-filled C table.
//   kwx_constants_table_gen.cpp — Generated C side of that table.
//   kwx_free_functions_gen.ts — TypeScript wrappers for non-class C functions.
//   wx{Class}_gen.ts        — One file per class with a TypeScript class that wraps the FFI.
//   kwx_gen.ts              — Master barrel re-export of every generated module.

#include "lang_typescript.h"

#include "../file_writer.h"
#include "lang_common.h"
#include "typescript_type_map.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <print>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
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

// Return the TypeScript import path for a class file (kwx_ts resolves .ts automatically).
[[nodiscard]] static std::string TsClassImportPath(const std::string& class_name)
{
    return "./" + class_name + "_gen.ts";
}

// Escape a value for embedding in a TypeScript double-quoted string literal.
[[nodiscard]] static std::string EscapeTsString(std::string_view text)
{
    std::string out;
    out.reserve(text.size());
    for (const char character: text)
    {
        switch (character)
        {
            case '\\':
                out += "\\\\";
                break;
            case '"':
                out += "\\\"";
                break;
            case '\n':
                out += "\\n";
                break;
            case '\r':
                out += "\\r";
                break;
            case '\t':
                out += "\\t";
                break;
            default:
                out += character;
                break;
        }
    }
    return out;
}

// True if a non-constructor method's first parameter is TClass(ClassName) matching
// the function's own class — acts as the implicit "self" receiver for mixin methods.
// NOTE: this heuristic exists only for mixin methods, which are declared against the
// mixin class with a TClass(mixin) receiver instead of TSelf.  The parser sets has_self
// for genuine receivers, so a real method's first parameter is never mistaken for the
// receiver.  Do NOT widen this predicate without that guarantee.
[[nodiscard]] static bool IsPseudoSelf(const FunctionDecl& func)
{
    if (func.has_self || func.class_name.empty() || func.params.empty())
    {
        return false;
    }
    const Param& first = func.params[0];
    return first.macro_name == "TClass" && first.macro_arg == func.class_name;
}

// True if a destructor names the receiver (TSelf, or TClass of its own class) and has no
// item-index/other params.
[[nodiscard]] static bool IsTrueDestructor(const FunctionDecl& func)
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
        // A destructor may be declared against the class itself (TClass(OwnClass))
        // instead of TSelf; both denote the receiver.
        if (param.macro_name == "TClass" && param.macro_arg == func.class_name)
        {
            continue;
        }
        return false;
    }
    return true;
}

// A C++ method that hides a same-named base method with an incompatible signature
// cannot keep that name on the TypeScript side.  Rename only the TS wrapper; the
// exported C symbol and its ABI stay unchanged.
struct TsMemberRename
{
    std::string_view class_name;
    std::string_view method_name;
    std::string_view ts_name;
};

static constexpr std::array<TsMemberRename, 11> TS_MEMBER_RENAMES = { {
    { "wxBitmapComboBox", "Append", "AppendWithBitmap" },
    { "wxComboBox", "GetClientData", "GetItemClientData" },
    { "wxComboBox", "SetClientData", "SetItemClientData" },
    { "wxListBox", "GetClientData", "GetItemClientData" },
    { "wxListBox", "SetClientData", "SetItemClientData" },
    { "wxTreeCtrl", "GetParent", "GetItemParent" },
    { "wxScrolledWindow", "GetVirtualSize", "GetVirtualSizeXY" },
    { "wxTipWindow", "Close", "CloseTip" },
    { "wxGridBagSizer", "AddWindow", "AddWindowAt" },
    { "wxGridBagSizer", "AddSizer", "AddSizerAt" },
    { "wxGridBagSizer", "AddSpacer", "AddSpacerAt" },
} };

// Return the TypeScript member name for a method.  Item-level Delete methods
// collide with the Delete() destructor emitted for every owned class, so they are
// exposed as DeleteItem() while still calling the original C symbol.
[[nodiscard]] static std::string TsMethodName(const std::string& class_name,
                                              const FunctionDecl& func)
{
    if (func.method_name == "Delete" && !IsTrueDestructor(func))
    {
        return "DeleteItem";
    }
    for (const auto& rename: TS_MEMBER_RENAMES)
    {
        if (rename.class_name == class_name && rename.method_name == func.method_name)
        {
            return std::string(rename.ts_name);
        }
    }
    return TsEscapeName(func.method_name);
}

// True for methods that build an object and are therefore emitted as module-level
// factories.  The grid-cell classes historically used "Ctor" instead of "Create".
[[nodiscard]] static bool IsFactoryMethod(const FunctionDecl& func)
{
    return (func.is_constructor || func.method_name == "Ctor") && !func.has_self;
}

// Return the module-level factory name for a constructor, e.g. wxButton + CreateLoad
// → createWxButtonLoad.  Static factories cannot stay on the class because a derived
// static side must be assignable to every ancestor's static side (TS2417).
[[nodiscard]] static std::string TsFactoryName(const std::string& class_name,
                                               const FunctionDecl& func)
{
    std::string suffix;
    if (func.method_name == "Ctor")
    {
        suffix.clear();
    }
    else if (func.method_name.starts_with("Create"))
    {
        suffix = func.method_name.substr(std::string_view("Create").size());
    }
    else
    {
        suffix = func.method_name;
    }

    std::string factory_name = "create";
    if (!class_name.empty())
    {
        factory_name += static_cast<char>(std::toupper(static_cast<unsigned char>(class_name[0])));
        factory_name += class_name.substr(1);
    }
    factory_name += suffix;

    // kwx_helpers_gen.ts already exports createWxString(string).  The wxString_Create
    // factory takes a buffer pointer instead, so give it a non-conflicting name.
    if (factory_name == "createWxString")
    {
        return "createWxStringFromBuffer";
    }
    return factory_name;
}

// Member names exposed by the TypeScript ancestors of a class.  Used to decide where
// an `override` modifier is required (TS4114 / TS4113).
struct AncestorMembers
{
    std::unordered_set<std::string> instance_names;
    bool has_ptr = false;
    bool has_delete = false;
};

[[nodiscard]] static AncestorMembers
    CollectAncestorMembers(const std::string& class_name, const ParsedFFI& ffi,
                           const std::unordered_set<std::string>& wrapped_classes,
                           const std::unordered_map<std::string, const ClassInfo*>& class_index)
{
    AncestorMembers members;
    std::set<std::string> visited;
    visited.insert(class_name);  // seed the walk so a self-parent or cycle is caught
    std::unordered_map<std::string, std::string>::const_iterator iter =
        ffi.parent_map.find(class_name);
    while (iter != ffi.parent_map.end())
    {
        const std::string& parent = iter->second;
        if (!visited.insert(parent).second)
        {
            break;  // cycle guard
        }

        if (wrapped_classes.contains(parent))
        {
            const std::unordered_map<std::string, const ClassInfo*>::const_iterator found =
                class_index.find(parent);
            const ClassInfo* const parent_class =
                found != class_index.end() ? found->second : nullptr;
            if (parent_class)
            {
                members.has_ptr = true;
                for (const auto& func: parent_class->methods)
                {
                    if (!IsValidFunction(func))
                    {
                        continue;
                    }
                    if (IsFactoryMethod(func))
                    {
                        continue;  // factories are module-level, not inherited statics
                    }
                    if (IsTrueDestructor(func))
                    {
                        members.has_delete = true;
                        continue;
                    }
                    members.instance_names.insert(TsMethodName(parent, func));
                }
            }
        }

        iter = ffi.parent_map.find(parent);
    }
    return members;
}

// True if an FFI return type is an integer type safe to read through an int-returning
// C accessor.  Anything else (including pointers) must NOT be declared with an `int`
// prototype — such constants are skipped with a diagnostic instead.
[[nodiscard]] static bool IsIntegerConstType(std::string_view return_type)
{
    static constexpr std::array<std::string_view, 9> INTEGER_TYPES = {
        "int",   "unsigned",       "unsigned int", "long", "unsigned long",
        "short", "unsigned short", "size_t",       "bool",
    };
    return std::ranges::find(INTEGER_TYPES, return_type) != INTEGER_TYPES.end();
}

// One row of the shared integer-constant table.  ts_name is the exported TypeScript
// identifier; c_name is the C accessor symbol (e.g. "exp_wxEVT_ACTIVATE").
struct ConstTableEntry
{
    std::string ts_name;
    std::string c_name;
    std::string c_type;  // C return type of the accessor (for the generated prototype)
};

// Build the integer-valued constant table in the exact order used to assign TS array
// indices.  Both the TypeScript emitter and the C-table emitter call this so their
// orderings cannot drift.  Events are de-duplicated by name (first wins after sort),
// keys are included in full, and constants are restricted to non-pointer return types.
[[nodiscard]] static std::vector<ConstTableEntry> BuildIntConstantTable(const ParsedFFI& ffi)
{
    std::vector<ConstTableEntry> entries;

    std::vector<EventDecl> sorted_events = ffi.events;
    std::ranges::stable_sort(sorted_events, {}, &EventDecl::event_name);
    std::string last_event;
    for (const auto& event: sorted_events)
    {
        if (event.event_name == last_event)
        {
            continue;
        }
        last_event = event.event_name;
        entries.push_back({ event.event_name, event.export_name, "int" });
    }

    std::vector<KeyDecl> sorted_keys = ffi.keys;
    std::ranges::stable_sort(sorted_keys, {}, &KeyDecl::key_name);
    std::set<std::string> seen_keys;
    for (const auto& key: sorted_keys)
    {
        if (!seen_keys.insert(key.key_name).second)
        {
            continue;  // duplicate name
        }
        entries.push_back({ key.key_name, key.export_name, "int" });
    }

    std::vector<ConstantDecl> sorted_consts = ffi.constants;
    std::ranges::stable_sort(sorted_consts, {}, &ConstantDecl::constant_name);
    std::set<std::string> seen_consts;
    for (const auto& cnst: sorted_consts)
    {
        if (!seen_consts.insert(cnst.constant_name).second)
        {
            continue;  // duplicate name
        }
        if (cnst.return_type.contains('*'))
        {
            continue;  // pointer-valued: exported directly, never in the int table
        }
        if (!IsIntegerConstType(cnst.return_type))
        {
            std::println(stderr, "  Warning: constant {} has unsupported return type {} — omitted",
                         cnst.constant_name, cnst.return_type);
            continue;
        }
        entries.push_back({ cnst.constant_name, cnst.export_name, cnst.return_type });
    }

    return entries;
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
    visited.insert(class_name);  // seed the walk so a self-parent or cycle is caught
    while (iter != ffi.parent_map.end())
    {
        const std::string& parent = iter->second;
        if (parent == class_name || visited.contains(parent))
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
    if (param.macro_name == "TBool" || param.raw_type == "TBool" || param.raw_type == "TBoolInt")
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
        result.push_back({ fpar.name, TsRuntimeType(fpar.native_type), fpar.name, false });
    }
    return result;
}

// The class a factory wrapper constructs.  return_arg holds the actual returned class
// (e.g. TClass(wxButton) → "wxButton"); fall back to the enclosing class.
[[nodiscard]] static std::string EffectiveFactoryClass(const FunctionDecl& func,
                                                       const std::string& class_name)
{
    return func.return_arg.empty() ? class_name : func.return_arg;
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
        // Constructor: return the wrapped class in a null-check.  A free function has no
        // enclosing class, so it never takes the factory path.
        if (IsFactoryMethod(func) && !class_name.empty())
        {
            return EffectiveFactoryClass(func, class_name) + " | null";
        }
        return "Pointer";
    }
    if (func.return_type == "TBool" || func.return_type == "TBoolInt")
    {
        return "boolean";
    }
    if (func.return_type == "TString" || func.return_type == "TStringOut" ||
        func.return_type == "TStringVoid")
    {
        return "Pointer";
    }
    if (func.return_type == "void*" || func.return_type.find('*') != std::string::npos)
    {
        return "Pointer";
    }
    if (func.return_type == "uintptr_t" || func.return_type == "size_t")
    {
        return "bigint";
    }

    // All remaining numeric types (int, long, unsigned, unsigned long, double,
    // float, TArrayLen, TByteStringLen, TChar, TUInt8, time_t, wxUIntPtr, etc.)
    // map to a JavaScript number.
    return "number";
}

// Emit the return statement for a method wrapper, applying any needed conversions.
// call_expr is the raw lib.symbols.Func(...) expression (without trailing semicolon).
static void EmitWrapReturn(std::ostream& output, const FunctionDecl& func,
                           const std::string& class_name, const std::string& call_expr)
{
    const bool is_void = func.return_type.empty() || func.return_type == "void";
    const bool is_ctor = !class_name.empty() && IsFactoryMethod(func) &&
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
        output << "    return new " << EffectiveFactoryClass(func, class_name) << "(rawPtr);\n";
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

// Emit a single instance-method wrapper.  method_owner is the class the method is
// declared against (used for member renames); the receiver is always this._ptr.
static void EmitInstanceMethod(std::ostream& output, const AncestorMembers& ancestors,
                               const std::string& method_owner, const FunctionDecl& func)
{
    const bool pseudo_self = IsPseudoSelf(func);
    const std::string method_name = TsMethodName(method_owner, func);
    const std::string func_name = CFuncName(func);
    const std::string ret_type = WrapReturnType(func, method_owner);

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
        wrap_params.insert(wrap_params.end(), params.begin(), params.end());
    }
    output << "  " << (ancestors.instance_names.contains(method_name) ? "override " : "")
           << method_name << "(";
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

    if (method_name == "DeleteItem")
    {
        output << "    if (this._disposed) return;\n";
    }

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

    EmitWrapReturn(output, func, method_owner, call);

    output << "  }\n\n";
}

// Emit the dlopen symbol entry for a single function.
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
        output << params[idx].native_type;
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
    std::error_code dir_error;
    fs::create_directories(out_dir, dir_error);
    if (dir_error)
    {
        std::println(stderr, "Error: cannot create output directory {}: {}", out_dir.string(),
                     dir_error.message());
        return;
    }

    GenerateFfi(ffi, out_dir);
    GenerateConstants(ffi, out_dir);
    GenerateConstantsTableC(ffi, out_dir);
    GenerateHelpers(ffi, out_dir);
    GenerateFreeFunctions(ffi, out_dir);
    GenerateClassFiles(ffi, out_dir);
    GenerateIndex(ffi, out_dir);

    std::println(stderr, "TypeScript: generated TypeScript FFI bindings in {}", out_dir.string());
}

VerifyResult TypeScriptEmitter::Verify(const ParsedFFI& /* ffi */, const fs::path& /* out_dir */)
{
    VerifyResult result;
    result.success = false;
    result.messages.emplace_back("TypeScript verify: use 'kwxgen verify' command instead");
    return result;
}

// -------------------------------------------------------------------------
// kwx_ffi_gen.ts — dlopen with all C symbols
// -------------------------------------------------------------------------

void TypeScriptEmitter::GenerateFfi(const ParsedFFI& ffi, const fs::path& out_dir)
{
    const fs::path file_path = out_dir / "kwx_ffi_gen.ts";
    ConditionalFileWriter output(file_path);

    WriteGeneratedHeader(output, "//");

    output << "import { dlopen } from \"kwx/platform\";\n\n";
    output << "export const lib = dlopen(\"" << EscapeTsString(ffi.lib_name) << "\", {\n";

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
        if (!emitted_symbols.insert(event.export_name).second)
        {
            continue;  // duplicate C export name
        }
        output << "  " << event.export_name << ": { parameters: [], result: \"i32\" },\n";
    }

    // Key accessor symbols (no parameters, return i32)
    for (const auto& key: ffi.keys)
    {
        if (!emitted_symbols.insert(key.export_name).second)
        {
            continue;  // duplicate C export name
        }
        output << "  " << key.export_name << ": { parameters: [], result: \"i32\" },\n";
    }

    // Constant accessor symbols (no parameters; result uses the mapped FFI type)
    for (const auto& cnst: ffi.constants)
    {
        if (!emitted_symbols.insert(cnst.export_name).second)
        {
            continue;  // duplicate C export name
        }
        output << "  " << cnst.export_name
               << ": { parameters: [], result: " << TsFFIReturnType(cnst.return_type, "")
               << " },\n";
    }

    // Integer constant table accessors (always available — defined in the generated
    // kwx_constants_table_gen.cpp).
    if (emitted_symbols.insert("kwxConstants_IntCount").second)
    {
        output << "  kwxConstants_IntCount: { parameters: [], result: \"i32\" },\n";
    }
    if (emitted_symbols.insert("kwxConstants_IntTable").second)
    {
        output << "  kwxConstants_IntTable: { parameters: [], result: \"pointer\" },\n";
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

// The helper module imports the generated wxString wrapper, its UTF8 factory and its
// destructor.  Without all three the module (and the barrel that re-exports it) cannot
// compile, so only emit it when they exist.
[[nodiscard]] static bool HasWxStringHelpers(const ParsedFFI& ffi)
{
    const ClassInfo* wxstring_class = nullptr;
    for (const auto& cls: ffi.classes)
    {
        if (cls.name == "wxString")
        {
            wxstring_class = &cls;
            break;
        }
    }
    if (!wxstring_class)
    {
        return false;
    }
    bool has_factory = false;
    bool has_destructor = false;
    for (const auto& func: wxstring_class->methods)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        if (IsTrueDestructor(func))
        {
            has_destructor = true;
        }
        else if (IsFactoryMethod(func))
        {
            has_factory = true;
        }
    }
    return has_factory && has_destructor;
}

void TypeScriptEmitter::GenerateHelpers(const ParsedFFI& ffi, const fs::path& out_dir)
{
    if (!HasWxStringHelpers(ffi))
    {
        std::println(stderr, "  kwx_helpers_gen.ts:       skipped — no wrapped wxString with a "
                             "CreateUTF8 factory and destructor");
        return;
    }

    const fs::path file_path = out_dir / "kwx_helpers_gen.ts";
    ConditionalFileWriter output(file_path);

    WriteGeneratedHeader(output, "//");

    const std::string module = R"TS(import { lib } from "./kwx_ffi_gen.ts";
import { pointerOf, readCString, Pointer } from "kwx/platform";
import { %%FACTORY%%, wxString } from "./wxString_gen.ts";

// --- Helper: create a wxString from a JS string ---
export function createWxString(s: string): wxString
{
    const buf = new TextEncoder().encode(s + "\0");
    const ptr = pointerOf(buf);
    const result = %%FACTORY%%(ptr);
    if (!result)
    {
        throw new Error(`Failed to create wxString for: ${s}`);
    }
    return result;
}

// --- Helper: read a JS string from a wxString* ---
export function readWxString(wxStrPtr: Pointer): string
{
    if (!wxStrPtr) return "";
    const buf = lib.symbols.kwxUtf8Buffer_Create(wxStrPtr);
    const data = lib.symbols.kwxUtf8Buffer_Data(buf);
    const result = data ? readCString(data) : "";
    lib.symbols.kwxUtf8Buffer_Delete(buf);
    return result;
}

// --- Helper: read and delete a wxString* returned from a getter ---
// The pointer is assumed to be owned by the caller and is consumed (freed) by this
// call.  Never pass a borrowed or const pointer, and never call it twice.
export function readAndDeleteWxString(wxStrPtr: Pointer): string
{
    if (!wxStrPtr) return "";
    const result = readWxString(wxStrPtr);
    lib.symbols.wxString_Delete(wxStrPtr);
    return result;
}
)TS";

    // Derive the wxString UTF8 factory wrapper name (falls back to the first factory).
    std::string factory_name;
    for (const auto& cls: ffi.classes)
    {
        if (cls.name != "wxString")
        {
            continue;
        }
        for (const auto& func: cls.methods)
        {
            if (!IsValidFunction(func) || !IsFactoryMethod(func))
            {
                continue;
            }
            if (factory_name.empty())
            {
                factory_name = TsFactoryName("wxString", func);
            }
            if (func.method_name == "CreateUTF8")
            {
                factory_name = TsFactoryName("wxString", func);
                break;
            }
        }
    }

    std::string escaped_module = module;
    const std::string placeholder = "%%FACTORY%%";
    for (std::string::size_type pos = escaped_module.find(placeholder); pos != std::string::npos;
         pos = escaped_module.find(placeholder, pos + factory_name.size()))
    {
        escaped_module.replace(pos, placeholder.size(), factory_name);
    }
    output << escaped_module;

    std::println(stderr, "  kwx_helpers_gen.ts:       wxString conversion helpers");
}

// -------------------------------------------------------------------------
// kwx_constants_gen.ts — table-backed constants, events, and keys
// -------------------------------------------------------------------------

void TypeScriptEmitter::GenerateConstants(const ParsedFFI& ffi, const fs::path& out_dir)
{
    const fs::path file_path = out_dir / "kwx_constants_gen.ts";
    ConditionalFileWriter output(file_path);

    WriteGeneratedHeader(output, "//");

    std::ostringstream body;

    const std::vector<ConstTableEntry> table = BuildIntConstantTable(ffi);

    // Integer constants are read from a single generated C table (lazily filled) rather
    // than issuing one eager FFI accessor call per constant.
    body << "const _intCount = lib.symbols.kwxConstants_IntCount() as number;\n";
    body << "const _intTable = lib.symbols.kwxConstants_IntTable() as Pointer;\n";
    body << "const _ints = new Int32Array(\n";
    body << "    arrayBufferView(_intTable!, _intCount * 4)\n";
    body << ");\n\n";

    size_t index = 0;

    // Events
    if (!ffi.events.empty())
    {
        body << "// Events\n";
        std::vector<EventDecl> sorted_events = ffi.events;
        std::ranges::stable_sort(sorted_events, {}, &EventDecl::event_name);

        std::string last_event;
        for (const auto& event: sorted_events)
        {
            if (event.event_name == last_event)
            {
                continue;
            }
            last_event = event.event_name;
            body << "export const " << TsEscapeName(event.event_name) << ": number = _ints["
                 << std::to_string(index) << "];\n";
            ++index;
        }
        body << "\n";
    }

    // Keys
    if (!ffi.keys.empty())
    {
        body << "// Keys\n";
        std::vector<KeyDecl> sorted_keys = ffi.keys;
        std::ranges::stable_sort(sorted_keys, {}, &KeyDecl::key_name);
        std::set<std::string> seen_keys;
        for (const auto& key: sorted_keys)
        {
            if (!seen_keys.insert(key.key_name).second)
            {
                continue;  // duplicate name
            }
            body << "export const " << TsEscapeName(key.key_name) << ": number = _ints["
                 << std::to_string(index) << "];\n";
            ++index;
        }
        body << "\n";
    }

    // General constants
    if (!ffi.constants.empty())
    {
        body << "// Constants\n";
        std::vector<ConstantDecl> sorted_consts = ffi.constants;
        std::ranges::stable_sort(sorted_consts, {}, &ConstantDecl::constant_name);
        std::set<std::string> seen_consts;
        for (const auto& cnst: sorted_consts)
        {
            if (!seen_consts.insert(cnst.constant_name).second)
            {
                continue;  // duplicate name
            }
            const bool is_ptr = cnst.return_type.contains('*');
            if (is_ptr)
            {
                body << "export const " << TsEscapeName(cnst.constant_name)
                     << ": Pointer = lib.symbols." << cnst.export_name << "() as Pointer;\n";
            }
            else if (IsIntegerConstType(cnst.return_type))
            {
                body << "export const " << TsEscapeName(cnst.constant_name) << ": number = _ints["
                     << std::to_string(index) << "];\n";
                ++index;
            }
            // else: unsupported return type — reported by BuildIntConstantTable, skipped here
        }
    }

    const std::string body_str = body.str();
    output << "import { lib } from \"./kwx_ffi_gen.ts\";\n";
    output << "import { arrayBufferView";
    if (body_str.find("Pointer") != std::string::npos)
    {
        output << ", Pointer";
    }
    output << " } from \"kwx/platform\";\n\n";
    output << body_str;

    std::println(stderr,
                 "  kwx_constants_gen.ts:    {} events, {} keys, {} constants, "
                 "{} in int table",
                 ffi.events.size(), ffi.keys.size(), ffi.constants.size(), table.size());
}

// -------------------------------------------------------------------------
// kwx_constants_table_gen.cpp — the integer constant table (C side)
// -------------------------------------------------------------------------

// Emits the C translation unit that exposes the integer-valued events, keys and
// constants through a single lazily-filled int array.  Declarations are written as
// bare `extern "C" int name();` prototypes (the events/keys/constants headers are not
// included: events/keys declare C++ linkage and some constants have no prototype).
void TypeScriptEmitter::GenerateConstantsTableC(const ParsedFFI& ffi, const fs::path& out_dir)
{
    const fs::path file_path = out_dir / "kwx_constants_table_gen.cpp";
    ConditionalFileWriter output(file_path);

    const std::vector<ConstTableEntry> table = BuildIntConstantTable(ffi);

    output << "// Generated by kwxgen -- do not edit\n";
    output << "#include \"kwx_def.h\"\n";
    output << "#include <mutex>\n\n";

    output << "extern \"C\"\n{\n";

    // One declaration per distinct C export name, in table order.
    std::unordered_set<std::string> declared;
    for (const auto& entry: table)
    {
        if (!declared.insert(entry.c_name).second)
        {
            continue;
        }
        output << entry.c_type << " " << entry.c_name << "();\n";
    }
    output << "\n";

    // Cast to a plain decimal string — the output stream may carry a locale that
    // inserts thousands separators, which would corrupt the generated C.
    const std::string table_size = std::to_string(table.size());

    if (table.empty())
    {
        output << "static int s_values[1];\n";
    }
    else
    {
        output << "static int s_values[" << table_size << "];\n";
    }
    output << "static std::once_flag s_once;\n\n";

    output << "WXFFI_EXPORT(int, kwxConstants_IntCount)()\n{\n";
    output << "    return " << table_size << ";\n";
    output << "}\n\n";

    output << "WXFFI_EXPORT(const int*, kwxConstants_IntTable)()\n{\n";
    output << "    std::call_once(s_once, [] {\n";
    if (!table.empty())
    {
        output << "        int i = 0;\n";
        for (const auto& entry: table)
        {
            output << "        s_values[i++] = " << entry.c_name << "();\n";
        }
    }
    output << "    });\n";
    output << "    return s_values;\n";
    output << "}\n";

    output << "}\n";

    std::println(stderr, "  kwx_constants_table_gen.cpp: {} table entries", table.size());
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

    std::ostringstream body;
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
            wrap_params.insert(wrap_params.end(), params.begin(), params.end());
        }

        body << "export function " << TsEscapeName(func.method_name) << "(";
        bool first = true;
        for (const auto& wpar: wrap_params)
        {
            if (wpar.is_self)
            {
                continue;
            }
            if (!first)
            {
                body << ", ";
            }
            body << wpar.name << ": " << wpar.ts_type;
            first = false;
        }
        body << "): " << ret_type << " {\n";
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

        EmitWrapReturn(body, func, "", call);

        body << "}\n\n";
        ++func_count;
    }

    const std::string body_str = body.str();
    output << "import { lib } from \"./kwx_ffi_gen.ts\";\n";
    if (body_str.find("Pointer") != std::string::npos)
    {
        output << "import { Pointer } from \"kwx/platform\";\n";
    }
    output << "\n";
    output << body_str;

    std::println(stderr, "  kwx_free_functions_gen.ts: {} free functions", func_count);
}

// -------------------------------------------------------------------------
// wx{Class}_gen.ts — per-class TypeScript wrapper
// -------------------------------------------------------------------------

void TypeScriptEmitter::EmitClassFile(
    std::ostream& output, const ClassInfo& cls, const ParsedFFI& ffi,
    const std::unordered_map<std::string, const ClassInfo*>& class_index,
    const std::unordered_set<std::string>& wrapped_classes)
{
    // Find the nearest wrapped ancestor for extends-based inheritance.
    const std::string parent_name = FindTsWrappedParent(cls.name, ffi, wrapped_classes);
    const AncestorMembers ancestors =
        CollectAncestorMembers(cls.name, ffi, wrapped_classes, class_index);

    WriteGeneratedHeader(output, "//");

    std::ostringstream body;
    body << "export class " << cls.name;
    if (!parent_name.empty())
    {
        body << " extends " << parent_name;
    }
    body << " {\n";
    if (parent_name.empty())
    {
        // Root class (no wrapped parent) — own the pointer field.
        body << "  protected readonly _ptr: Pointer;\n";
        body << "  protected _disposed: boolean = false;\n\n";
        body << "  constructor(ptr: Pointer) {\n";
        body << "    this._ptr = ptr;\n";
        body << "  }\n\n";
    }
    body << "  /** Returns the underlying native pointer. */\n";
    body << "  " << (ancestors.has_ptr ? "override " : "") << "get ptr(): Pointer {\n";
    body << "    return this._ptr;\n";
    body << "  }\n\n";

    // --- Destructor ---
    for (const auto& func: cls.methods)
    {
        if (!IsValidFunction(func) || !IsTrueDestructor(func))
        {
            continue;
        }

        const std::string func_name = CFuncName(func);
        const std::string override_prefix = ancestors.has_delete ? "override " : "";

        body << "  " << override_prefix << "Delete(): void {\n";
        body << "    if (this._disposed) return;\n";
        body << "    this._disposed = true;\n";
        body << "    lib.symbols." << func_name << "(this._ptr);\n";
        body << "  }\n\n";
        body << "  " << override_prefix << "[Symbol.dispose](): void {\n";
        body << "    this.Delete();\n";
        body << "  }\n\n";
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
        // Skip constructors (emitted below as module-level factory functions)
        if (IsFactoryMethod(func))
        {
            continue;
        }
        // Skip the true destructor (emitted above)
        if (IsTrueDestructor(func))
        {
            continue;
        }

        const std::string method_name = TsMethodName(cls.name, func);
        if (!emitted_instance_names.insert(method_name).second)
        {
            std::println(stderr, "  Warning: {}: dropping duplicate method {} (C symbol {})",
                         cls.name, method_name, CFuncName(func));
            continue;  // skip duplicate overload
        }
        EmitInstanceMethod(body, ancestors, cls.name, func);
    }

    // --- Mixin methods ---
    // A consumer class (e.g. wxTextCtrl) declares part of its API against a mixin class
    // (e.g. wxTextEntry).  Re-emit the mixin's non-factory, non-destructor methods here
    // so the consumer exposes them, calling the mixin class's C symbols with the
    // consumer's this._ptr.
    const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
        ffi.mixin_map.find(cls.name);
    if (mixin_iter != ffi.mixin_map.end())
    {
        for (const std::string& mixin_name: mixin_iter->second)
        {
            const std::unordered_map<std::string, const ClassInfo*>::const_iterator mixin_found =
                class_index.find(mixin_name);
            const ClassInfo* const mixin_class =
                mixin_found != class_index.end() ? mixin_found->second : nullptr;
            if (!mixin_class)
            {
                continue;
            }
            for (const auto& func: mixin_class->methods)
            {
                if (!IsValidFunction(func) || IsFactoryMethod(func) || IsTrueDestructor(func))
                {
                    continue;
                }
                if (!emitted_instance_names.insert(TsMethodName(mixin_name, func)).second)
                {
                    continue;  // consumer already exposes this name
                }
                EmitInstanceMethod(body, ancestors, mixin_name, func);
            }
        }
    }

    body << "}\n";

    // --- Constructors as module-level factory functions ---
    // Static factories cannot be inherited: TypeScript requires every derived static
    // member to be assignable to the ancestor's static side (TS2417), which is
    // impossible when each class declares a different Create() signature.
    std::set<std::string> emitted_factory_names;
    for (const auto& func: cls.methods)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        if (!IsFactoryMethod(func))
        {
            continue;
        }

        const std::string factory_name = TsFactoryName(cls.name, func);
        if (!emitted_factory_names.insert(factory_name).second)
        {
            std::println(stderr, "  Warning: {}: dropping duplicate factory {} (C symbol {})",
                         cls.name, factory_name, CFuncName(func));
            continue;  // skip duplicate overload
        }

        const std::string func_name = CFuncName(func);
        const std::string ret_type = WrapReturnType(func, cls.name);

        std::vector<WrapParam> wrap_params;
        for (const auto& param: func.params)
        {
            const std::vector<WrapParam> params = BuildWrapParams(param);
            wrap_params.insert(wrap_params.end(), params.begin(), params.end());
        }
        body << "\nexport function " << factory_name << "(";
        bool first = true;
        for (const auto& wpar: wrap_params)
        {
            if (wpar.is_self)
            {
                continue;
            }
            if (!first)
            {
                body << ", ";
            }
            body << wpar.name << ": " << wpar.ts_type;
            first = false;
        }
        body << "): " << ret_type << " {\n";

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

        EmitWrapReturn(body, func, cls.name, call);

        body << "}\n";
    }

    const std::string body_str = body.str();
    output << "import { lib } from \"./kwx_ffi_gen.ts\";\n";
    if (body_str.find("Pointer") != std::string::npos)
    {
        output << "import { Pointer } from \"kwx/platform\";\n";
    }
    if (!parent_name.empty())
    {
        output << "import { " << parent_name << " } from \"" << TsClassImportPath(parent_name)
               << "\";\n";
    }
    output << "\n";
    output << body_str;
}

void TypeScriptEmitter::GenerateClassFiles(const ParsedFFI& ffi, const fs::path& out_dir)
{
    std::vector<std::string> class_names;
    size_t total_methods = 0;

    std::unordered_map<std::string, const ClassInfo*> class_index;
    class_index.reserve(ffi.classes.size());
    for (const auto& cls: ffi.classes)
    {
        class_index.emplace(cls.name, &cls);
    }

    // Build the set of classes that actually have generated wrapper methods.  It is
    // identical for every class file, so compute it once.
    std::unordered_set<std::string> wrapped_classes;
    for (const auto& other: ffi.classes)
    {
        if (!other.methods.empty())
        {
            wrapped_classes.insert(other.name);
        }
    }

    for (const auto& cls: ffi.classes)
    {
        if (cls.methods.empty())
        {
            continue;
        }

        const fs::path file_path = out_dir / TsClassFileName(cls.name);
        ConditionalFileWriter output(file_path);

        EmitClassFile(output, cls, ffi, class_index, wrapped_classes);
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

    if (HasWxStringHelpers(ffi))
    {
        output << "export * from \"./kwx_helpers_gen.ts\";\n";
    }

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
        // Re-export the class and its module-level factory functions.
        output << "export * from \"" << TsClassImportPath(name) << "\";\n";
    }

    std::println(stderr, "  kwx_gen.ts:              {} class exports", class_names.size());
}
