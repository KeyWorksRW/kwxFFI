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
#include <fstream>
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

// True if a class passes its object through an explicit TClass(OwnClass) first parameter
// instead of TSelf for most of its methods (mixin/value-object shape: wxTextEntry,
// wxItemContainer, wxDataViewItemArray).  For those the parameter is a receiver, not an
// argument.
[[nodiscard]] static bool UsesExplicitReceiver(const ClassInfo& cls)
{
    size_t receiver_count = 0;
    size_t method_count = 0;
    for (const auto& method: cls.methods)
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
        if (IsPseudoSelf(method))
        {
            ++receiver_count;
        }
    }
    return receiver_count > 0 && (receiver_count * 2U) > method_count;
}

// True for a function declared inside a TClassDef block that has no receiver at all: no
// TSelf, no TClass(own class) pseudo-self, and no receiver-named first parameter.  Such a
// function is static in wxWidgets and must be emitted at module scope, not as an instance
// method that forwards this._ptr.
[[nodiscard]] static bool IsStaticClassFunction(const FunctionDecl& func,
                                                const ClassInfo* owning_class)
{
    if (func.class_name.empty())
    {
        return false;
    }
    if (func.is_constructor || func.is_destructor || func.method_name == "Ctor")
    {
        return false;
    }
    if (func.has_self)
    {
        return false;
    }
    // IsPseudoSelf also matches a TClass(own class) *argument* (wxLog_SetActiveTarget takes
    // the new target, wxArtProvider_PushBack the provider), so it only denotes a receiver in
    // a class that declares no TSelf receiver at all.
    if (IsPseudoSelf(func) && UsesExplicitReceiver(*owning_class))
    {
        return false;
    }
    // Hand-written wrappers (wxStyledTextCtrl and friends) pass the object pointer as an
    // explicit first parameter; those blocks keep their instance-method shape.
    if (!func.params.empty())
    {
        const Param& first = func.params[0];
        if (first.macro_name.empty() && first.raw_type == "void*" &&
            (first.param_name == "pObject" || first.param_name == "self"))
        {
            return false;
        }
    }
    return true;
}

// A C++ method that hides a same-named base method with an incompatible signature
// cannot keep that name on the TypeScript side.  Rename only the TS wrapper; the
// exported C symbol and its ABI stay unchanged.
// Entries are sorted by class, then method.  Every class that redeclares a renamed
// ancestor method needs its own entry: a derived member adopts the name the ancestor
// *exposes*, not the original method name, so a missing entry renames it again.
struct TsMemberRename
{
    std::string_view class_name;
    std::string_view method_name;
    std::string_view ts_name;
};

static constexpr std::array<TsMemberRename, 30> TS_MEMBER_RENAMES = { {
    { "wxBitmapComboBox", "Append", "AppendWithBitmap" },
    { "wxBitmapComboBox", "Insert", "InsertWithBitmap" },
    { "wxBookCtrlBase", "HitTest", "HitTestPage" },
    { "wxCalendarCtrl", "HitTest", "HitTestDate" },
    { "wxChoicebook", "HitTest", "HitTestPage" },
    { "wxComboBox", "GetClientData", "GetItemClientData" },
    { "wxComboBox", "SetClientData", "SetItemClientData" },
    { "wxGridBagSizer", "AddSizer", "AddSizerAt" },
    { "wxGridBagSizer", "AddSpacer", "AddSpacerAt" },
    { "wxGridBagSizer", "AddWindow", "AddWindowAt" },
    { "wxListBox", "GetClientData", "GetItemClientData" },
    { "wxListBox", "SetClientData", "SetItemClientData" },
    { "wxListCtrl", "HitTest", "HitTestItem" },
    { "wxListbook", "HitTest", "HitTestPage" },
    { "wxNotebook", "HitTest", "HitTestPage" },
    { "wxProcessEx", "Connect", "SetClosure" },
    { "wxProgressDialog", "Update", "UpdateProgress" },
    { "wxRichTextCtrl", "HitTest", "HitTestPosition" },
    { "wxRichTextCtrl", "PageDown", "PageDownBy" },
    { "wxRichTextCtrl", "PageUp", "PageUpBy" },
    { "wxScrolledWindow", "GetVirtualSize", "GetVirtualSizeXY" },
    { "wxSimpleHtmlListBox", "GetClientData", "GetItemClientData" },
    { "wxSimpleHtmlListBox", "SetClientData", "SetItemClientData" },
    { "wxTextCtrl", "HitTest", "HitTestPosition" },
    { "wxTimerEx", "Connect", "SetClosure" },
    { "wxTipWindow", "Close", "CloseTip" },
    { "wxToolbook", "HitTest", "HitTestPage" },
    { "wxTreeCtrl", "GetParent", "GetItemParent" },
    { "wxTreeCtrl", "HitTest", "HitTestItem" },
    { "wxTreebook", "HitTest", "HitTestPage" },
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
// (e.g. TClass(wxButton) → "wxButton"); fall back to the enclosing class when the name
// does not denote a generated class (it would otherwise be an unresolved identifier).
[[nodiscard]] static std::string
    EffectiveFactoryClass(const FunctionDecl& func, const std::string& class_name,
                          const std::unordered_set<std::string>& wrapped_classes)
{
    if (!func.return_arg.empty() && wrapped_classes.contains(func.return_arg))
    {
        return func.return_arg;
    }
    return class_name;
}

// Return the TypeScript return type annotation for a method in the class wrapper layer.
// class_name is the enclosing class (used when return is TClass/TSelf → ClassName | null).
[[nodiscard]] static std::string
    WrapReturnType(const FunctionDecl& func, const std::string& class_name,
                   const std::unordered_set<std::string>& wrapped_classes)
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
            return EffectiveFactoryClass(func, class_name, wrapped_classes) + " | null";
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
    if (func.return_type == "uintptr_t" || func.return_type == "wxUIntPtr" ||
        func.return_type == "size_t" || func.return_type == "long" ||
        func.return_type == "unsigned long" || func.return_type == "time_t")
    {
        return "bigint";
    }
    if (func.return_type == "TInt64" || func.return_type == "int64_t")
    {
        return "bigint";
    }

    // All remaining numeric types (int, unsigned, double, float, TArrayLen,
    // TByteStringLen, TChar, TUInt8, etc.) map to a JavaScript number.
    return "number";
}

// Emit the return statement for a method wrapper, applying any needed conversions.
// call_expr is the raw lib.symbols.Func(...) expression (without trailing semicolon).
static void EmitWrapReturn(std::ostream& output, const FunctionDecl& func,
                           const std::string& class_name, const std::string& call_expr,
                           const std::unordered_set<std::string>& wrapped_classes,
                           std::string_view indent = "    ")
{
    const bool is_void = func.return_type.empty() || func.return_type == "void";
    const bool is_ctor = !class_name.empty() && IsFactoryMethod(func) &&
                         (func.return_macro == "TClass" || func.return_macro == "TSelf" ||
                          func.return_macro == "TClassRef");
    const bool is_bool = func.return_type == "TBool" || func.return_type == "TBoolInt";
    const bool is_bigint = func.return_type == "uintptr_t" || func.return_type == "wxUIntPtr" ||
                           func.return_type == "size_t" || func.return_type == "TInt64" ||
                           func.return_type == "int64_t" || func.return_type == "long" ||
                           func.return_type == "unsigned long" || func.return_type == "time_t";

    if (is_void)
    {
        output << indent << call_expr << ";\n";
        return;
    }

    if (is_ctor)
    {
        output << indent << "const rawPtr = " << call_expr << ";\n";
        output << indent << "if (rawPtr === null) return null;\n";
        output << indent << "return new "
               << EffectiveFactoryClass(func, class_name, wrapped_classes) << "(rawPtr);\n";
        return;
    }

    if (is_bool)
    {
        output << indent << "return (" << call_expr << " as number) !== 0;\n";
        return;
    }

    if (is_bigint)
    {
        output << indent << "return " << call_expr << " as bigint;\n";
        return;
    }

    output << indent << "return " << call_expr << ";\n";
}

// True if GenerateFreeFunctions emits a file at all: either true free functions exist, or a
// class-block static has to be emitted at module scope.
[[nodiscard]] static bool HasModuleLevelFunctions(const ParsedFFI& ffi)
{
    if (!ffi.free_functions.empty())
    {
        return true;
    }
    for (const auto& cls: ffi.classes)
    {
        for (const auto& func: cls.methods)
        {
            if (IsValidFunction(func) && IsStaticClassFunction(func, &cls))
            {
                return true;
            }
        }
    }
    return false;
}

// The visible TypeScript signature of one member: parameter types in order, then the
// return type.
struct AncestorMemberInfo
{
    std::vector<std::string> param_types;
    std::string return_type;
    std::string origin_name;        // declared name before any ancestor-side rename
    std::vector<WrapParam> params;  // visible parameters, in order
};

// Member names exposed by the TypeScript ancestors of a class.  Each name maps to the
// complete set of overload signatures a consumer inherits under that name.
struct AncestorMembers
{
    std::unordered_set<std::string> instance_names;
    std::unordered_map<std::string, std::vector<AncestorMemberInfo>> signatures;
    bool has_ptr = false;
    bool has_delete = false;
};

// How one C-call argument is produced from an implementation parameter.
enum class FfiArgumentKind
{
    self,
    boolean,
    plain,
};

struct FfiArgument
{
    FfiArgumentKind kind = FfiArgumentKind::plain;
    std::string ts_type;  // visible type; empty for the hidden receiver
};

// One overload emitted for a member: its visible parameters, the C-call arguments, and
// where its body comes from.
struct EmittedOverload
{
    std::vector<WrapParam> params;           // visible signature parameters
    std::vector<FfiArgument> ffi_arguments;  // one entry per C-call argument
    std::string return_type;
    bool from_ancestor = false;
    const FunctionDecl* func = nullptr;  // non-null when from_ancestor is false
};

// True when `derived` can legally override `base` as the only visible signature: it adds
// no required parameters and has an identical return type.
[[nodiscard]] static bool IsAssignableOverride(const AncestorMemberInfo& derived,
                                               const AncestorMemberInfo& base)
{
    if (derived.param_types.size() > base.param_types.size())
    {
        return false;
    }
    for (size_t idx = 0; idx < derived.param_types.size(); ++idx)
    {
        if (derived.param_types[idx] != base.param_types[idx])
        {
            return false;
        }
    }
    return derived.return_type == base.return_type;
}

[[nodiscard]] static bool HasSameParameters(const AncestorMemberInfo& lhs,
                                            const AncestorMemberInfo& rhs)
{
    return lhs.param_types == rhs.param_types;
}

[[nodiscard]] static bool IsSameSignature(const AncestorMemberInfo& lhs,
                                          const AncestorMemberInfo& rhs)
{
    return HasSameParameters(lhs, rhs) && lhs.return_type == rhs.return_type;
}

// True for the TypeScript primitives whose runtime type is visible through `typeof`.
[[nodiscard]] static bool HasTypeGuard(std::string_view ts_type)
{
    return ts_type == "number" || ts_type == "bigint" || ts_type == "boolean" ||
           ts_type == "string";
}

[[nodiscard]] static std::string TypeGuardExpression(const std::string& ts_type,
                                                     const std::string& expr)
{
    return "typeof " + expr + " === \"" + ts_type + "\"";
}

// True when two signatures can be told apart at run time: either they take a different
// number of arguments, or a `typeof` check on a primitive parameter separates them.
[[nodiscard]] static bool SameArityDistinguishable(const AncestorMemberInfo& lhs,
                                                   const AncestorMemberInfo& rhs)
{
    if (lhs.param_types.size() != rhs.param_types.size())
    {
        return true;
    }
    for (size_t idx = 0; idx < lhs.param_types.size(); ++idx)
    {
        if (lhs.param_types[idx] != rhs.param_types[idx] &&
            (HasTypeGuard(lhs.param_types[idx]) || HasTypeGuard(rhs.param_types[idx])))
        {
            return true;
        }
    }
    return lhs.param_types == rhs.param_types;
}

// True when `overloads` can be emitted as one TypeScript overload set without a TS2394
// conflict and without an ambiguous runtime dispatch.
[[nodiscard]] static bool CanMergeOverloads(const std::vector<AncestorMemberInfo>& overloads)
{
    for (size_t left = 0; left < overloads.size(); ++left)
    {
        for (size_t right = left + 1; right < overloads.size(); ++right)
        {
            const AncestorMemberInfo& lhs = overloads[left];
            const AncestorMemberInfo& rhs = overloads[right];
            if (HasSameParameters(lhs, rhs) && lhs.return_type != rhs.return_type)
            {
                return false;  // identical signature, different return type
            }
            if (!SameArityDistinguishable(lhs, rhs))
            {
                return false;  // same arity, types indistinguishable at run time
            }
        }
    }
    return true;
}

[[nodiscard]] static std::vector<AncestorMemberInfo>
    CombineOverloads(const std::vector<AncestorMemberInfo>& own_overloads,
                     const std::vector<AncestorMemberInfo>& inherited)
{
    std::vector<AncestorMemberInfo> combined = own_overloads;
    for (const auto& overload: inherited)
    {
        bool present = false;
        for (const auto& existing: combined)
        {
            if (IsSameSignature(existing, overload))
            {
                present = true;
                break;
            }
        }
        if (!present)
        {
            combined.push_back(overload);
        }
    }
    return combined;
}

// Owner-qualified fallback for a member that cannot share the plain name: the declaring
// class is part of the name, so the suffix survives parameter-map changes.
[[nodiscard]] static std::string
    OwnerQualifiedName(const std::string& name, const std::string& owner,
                       const std::set<std::string>& taken,
                       const std::unordered_set<std::string>& ancestor_names)
{
    const std::string base_name = name + "__" + owner;
    std::string candidate = base_name;
    for (size_t suffix = 2; taken.contains(candidate) || ancestor_names.contains(candidate);
         ++suffix)
    {
        candidate = base_name + "v" + std::to_string(suffix);
    }
    return candidate;
}

// How a member is exposed on the TypeScript side of a class.
struct MemberNameResolution
{
    std::string name;             // identifier to emit
    bool use_override = false;    // an ancestor exposes the same member name
    bool adopted_rename = false;  // took over an ancestor's renamed member
    bool renamed = false;         // fresh owner-qualified name; cannot share the plain name
    std::vector<AncestorMemberInfo> inherited_overloads;  // re-emitted under `name`
};

// Resolve the name under which a member group is emitted.  A member that cannot share the
// plain name with an inherited signature either adopts an ancestor's owner-qualified
// rename (which keeps the override intact) or gets a fresh one.
[[nodiscard]] static MemberNameResolution
    ResolveMemberName(const std::string& declared_name, const std::string& owner_class,
                      const std::vector<AncestorMemberInfo>& own_overloads,
                      const AncestorMembers& inherited, const std::set<std::string>& taken)
{
    MemberNameResolution resolution;
    resolution.name = declared_name;

    const std::unordered_map<std::string, std::vector<AncestorMemberInfo>>::const_iterator
        base_iter = inherited.signatures.find(declared_name);
    if (base_iter == inherited.signatures.end())
    {
        return resolution;  // no inherited member of that name
    }

    const std::vector<AncestorMemberInfo> combined =
        CombineOverloads(own_overloads, base_iter->second);
    if (CanMergeOverloads(combined))
    {
        if (base_iter->second.size() == 1 && own_overloads.size() == 1 &&
            IsAssignableOverride(own_overloads[0], base_iter->second[0]))
        {
            resolution.use_override = true;
            return resolution;
        }
        resolution.use_override = true;
        for (const auto& overload: base_iter->second)
        {
            bool already_own = false;
            for (const auto& own_entry: own_overloads)
            {
                if (IsSameSignature(own_entry, overload))
                {
                    already_own = true;
                    break;
                }
            }
            if (!already_own)
            {
                resolution.inherited_overloads.push_back(overload);
            }
        }
        return resolution;
    }

    // The plain name cannot carry every signature.  Prefer an ancestor's existing
    // owner-qualified rename of the same member over inventing a new one.
    for (const auto& entry: inherited.signatures)
    {
        if (entry.first == declared_name)
        {
            continue;
        }
        bool same_origin = true;
        for (const auto& overload: entry.second)
        {
            if (overload.origin_name != declared_name)
            {
                same_origin = false;
                break;
            }
        }
        if (!same_origin)
        {
            continue;
        }
        const std::vector<AncestorMemberInfo> adopted =
            CombineOverloads(own_overloads, entry.second);
        if (!CanMergeOverloads(adopted))
        {
            continue;
        }
        if (!resolution.adopted_rename || entry.first < resolution.name)
        {
            resolution.name = entry.first;
            resolution.adopted_rename = true;
            resolution.use_override = true;
            resolution.inherited_overloads.clear();
            for (const auto& overload: entry.second)
            {
                bool already_own = false;
                for (const auto& own_entry: own_overloads)
                {
                    if (IsSameSignature(own_entry, overload))
                    {
                        already_own = true;
                        break;
                    }
                }
                if (!already_own)
                {
                    resolution.inherited_overloads.push_back(overload);
                }
            }
        }
    }
    if (resolution.adopted_rename)
    {
        return resolution;
    }

    resolution.name =
        OwnerQualifiedName(declared_name, owner_class, taken, inherited.instance_names);
    resolution.renamed = true;
    return resolution;
}

// Compute the member signature exactly as EmitInstanceMethod emits it.
// (TSelf, or a TClass(ClassName) pseudo-self first parameter) are not visible parameters.
[[nodiscard]] static AncestorMemberInfo BuildAncestorMemberInfo(const FunctionDecl& func,
                                                                const std::string& owner)
{
    AncestorMemberInfo info;
    // Factory methods never reach this point (callers skip them), so the wrapped-class
    // filter is irrelevant here.
    const std::unordered_set<std::string> no_wrapped_classes;
    info.return_type = WrapReturnType(func, owner, no_wrapped_classes);

    const bool pseudo_self = IsPseudoSelf(func);
    for (size_t pidx = 0; pidx < func.params.size(); ++pidx)
    {
        if (pseudo_self && pidx == 0)
        {
            continue;  // TClass(ClassName) first parameter acts as the receiver
        }
        const std::vector<WrapParam> params = BuildWrapParams(func.params[pidx]);
        for (const auto& wpar: params)
        {
            if (!wpar.is_self)
            {
                info.param_types.push_back(wpar.ts_type);
                info.params.push_back(wpar);
            }
        }
    }
    return info;
}

[[nodiscard]] static AncestorMembers
    CollectAncestorMembers(const std::string& class_name, const ParsedFFI& ffi,
                           const std::unordered_set<std::string>& wrapped_classes,
                           const std::unordered_map<std::string, const ClassInfo*>& class_index)
{
    // Walk the parent chain nearest-first and keep every wrapped ancestor in order.
    std::vector<const ClassInfo*> ancestor_chain;
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
            if (found != class_index.end())
            {
                ancestor_chain.push_back(found->second);
            }
        }
        iter = ffi.parent_map.find(parent);
    }

    // Resolve from the farthest ancestor down: each ancestor's own rename decision depends
    // on what it inherits, so nearer ancestors must see the already-resolved names.
    AncestorMembers members;
    for (std::vector<const ClassInfo*>::const_reverse_iterator chain_iter = ancestor_chain.rbegin();
         chain_iter != ancestor_chain.rend(); ++chain_iter)
    {
        const ClassInfo& parent_class = **chain_iter;
        AncestorMembers resolved;
        std::set<std::string> emitted;
        bool declares_delete = false;

        // Collect this ancestor's own members first, then the mixin members it re-emits.
        std::vector<std::pair<std::string, AncestorMemberInfo>> candidates;
        for (const auto& func: parent_class.methods)
        {
            if (!IsValidFunction(func))
            {
                continue;
            }
            if (IsFactoryMethod(func))
            {
                continue;  // factories are module-level, not inherited statics
            }
            if (IsStaticClassFunction(func, &parent_class))
            {
                continue;  // a static is not an inherited instance member
            }
            if (IsTrueDestructor(func))
            {
                declares_delete = true;
                continue;
            }
            AncestorMemberInfo info = BuildAncestorMemberInfo(func, parent_class.name);
            info.origin_name = TsMethodName(parent_class.name, func);
            candidates.emplace_back(info.origin_name, std::move(info));
        }

        // A wrapped ancestor re-emits its own mixin members on the TypeScript side, so a
        // consumer inherits them too — under the same names the ancestor exposes them.
        const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
            ffi.mixin_map.find(parent_class.name);
        if (mixin_iter != ffi.mixin_map.end())
        {
            for (const std::string& mixin_name: mixin_iter->second)
            {
                const std::unordered_map<std::string, const ClassInfo*>::const_iterator
                    mixin_found = class_index.find(mixin_name);
                const ClassInfo* const mixin_class =
                    mixin_found != class_index.end() ? mixin_found->second : nullptr;
                if (!mixin_class)
                {
                    continue;
                }
                for (const auto& func: mixin_class->methods)
                {
                    if (!IsValidFunction(func) || IsFactoryMethod(func) || IsTrueDestructor(func) ||
                        IsStaticClassFunction(func, mixin_class))
                    {
                        continue;
                    }
                    const std::string member_name = TsMethodName(mixin_name, func);
                    if (members.instance_names.contains(member_name))
                    {
                        continue;  // farther ancestor already exposes this name
                    }
                    bool already_listed = false;
                    for (const auto& candidate: candidates)
                    {
                        if (candidate.first == member_name)
                        {
                            already_listed = true;
                            break;
                        }
                    }
                    if (already_listed)
                    {
                        continue;  // this ancestor already exposes (or re-emits) the name
                    }
                    AncestorMemberInfo info = BuildAncestorMemberInfo(func, mixin_name);
                    info.origin_name = member_name;
                    candidates.emplace_back(member_name, std::move(info));
                }
            }
        }

        // Methods that share an exposed name are overloads of one member; resolve them as
        // a group so the whole set is visible to descendants.
        std::vector<std::string> group_order;
        std::unordered_map<std::string, std::vector<AncestorMemberInfo>> groups;
        for (auto& candidate: candidates)
        {
            if (!groups.contains(candidate.first))
            {
                group_order.push_back(candidate.first);
            }
            groups[candidate.first].push_back(std::move(candidate.second));
        }

        for (const std::string& declared_name: group_order)
        {
            std::vector<AncestorMemberInfo> own_overloads;
            for (const auto& info: groups[declared_name])
            {
                bool duplicate = false;
                for (const auto& existing: own_overloads)
                {
                    if (IsSameSignature(existing, info))
                    {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate)
                {
                    own_overloads.push_back(info);
                }
            }
            if (own_overloads.empty())
            {
                continue;
            }
            if (!CanMergeOverloads(own_overloads))
            {
                // EmitClassFile drops these same-class duplicates; keep the first only.
                own_overloads.resize(1);
            }

            const MemberNameResolution resolution = ResolveMemberName(
                declared_name, parent_class.name, own_overloads, members, emitted);
            resolved.instance_names.insert(resolution.name);
            resolved.signatures.insert_or_assign(
                resolution.name, CombineOverloads(own_overloads, resolution.inherited_overloads));
            emitted.insert(resolution.name);
        }

        // The nearer ancestor shadows same-named members of the farther ones.
        for (const auto& name: resolved.instance_names)
        {
            members.instance_names.insert(name);
        }
        for (const auto& entry: resolved.signatures)
        {
            members.signatures.insert_or_assign(entry.first, entry.second);
        }
        members.has_ptr = true;
        members.has_delete = members.has_delete || declares_delete;
    }
    return members;
}

struct RenameRecord
{
    std::string class_name;
    std::string member_name;
    std::string exposed_as;
    std::string reason;
};

static std::vector<RenameRecord> s_rename_records;
static std::string s_rename_report_path;

static void RecordRename(const RenameRecord& record)
{
    s_rename_records.push_back(record);
}

static void WriteRenameReport()
{
    std::ofstream report(s_rename_report_path, std::ios::binary | std::ios::trunc);
    if (!report.is_open())
    {
        std::println(stderr, "  Warning: could not write rename report to {}",
                     s_rename_report_path);
        return;
    }
    report << "{\n  \"count\": " << s_rename_records.size() << ",\n  \"renames\": [\n";
    for (size_t idx = 0; idx < s_rename_records.size(); ++idx)
    {
        const RenameRecord& record = s_rename_records[idx];
        report << "    { \"class\": \"" << EscapeTsString(record.class_name) << "\", \"member\": \""
               << EscapeTsString(record.member_name) << "\", \"exposed_as\": \""
               << EscapeTsString(record.exposed_as) << "\", \"reason\": \""
               << EscapeTsString(record.reason) << "\" }";
        if (idx + 1 < s_rename_records.size())
        {
            report << ",";
        }
        report << "\n";
    }
    report << "  ]\n}\n";
}

// Set the destination for the machine-readable rename report.  An empty path disables it.
void SetTypeScriptRenameReportPath(const std::string& path)
{
    s_rename_report_path = path;
}

// The early-return guard for a member that deletes an item; the value must match the
// declared return type.
static void EmitDisposedGuard(std::ostream& output, const std::string& return_type)
{
    if (return_type == "void")
    {
        output << "    if (this._disposed) return;\n";
    }
    else if (return_type == "boolean")
    {
        output << "    if (this._disposed) return false;\n";
    }
    else if (return_type == "number")
    {
        output << "    if (this._disposed) return 0;\n";
    }
    else if (return_type == "bigint")
    {
        output << "    if (this._disposed) return 0n;\n";
    }
    else
    {
        output << "    if (this._disposed) return null;\n";
    }
}

[[nodiscard]] static std::string CastArgument(const std::string& impl_name,
                                              const std::string& impl_type, bool impl_optional,
                                              const std::string& target_type)
{
    if (impl_type == target_type && !impl_optional)
    {
        return impl_name;
    }
    if (target_type.contains('|'))
    {
        return impl_name + " as (" + target_type + ")";
    }
    return impl_name + " as " + target_type;
}

[[nodiscard]] static std::string BuildFfiArgumentExpr(const FfiArgument& argument,
                                                      const std::string& impl_name,
                                                      const std::string& impl_type,
                                                      bool impl_optional)
{
    switch (argument.kind)
    {
        case FfiArgumentKind::self:
            return "this._ptr";
        case FfiArgumentKind::boolean:
            return impl_name + " ? 1 : 0";
        case FfiArgumentKind::plain:
            return CastArgument(impl_name, impl_type, impl_optional, argument.ts_type);
    }
    return impl_name;
}

static void EmitSingleOverload(std::ostream& output, const std::string& declared_name,
                               const MemberNameResolution& resolution,
                               const EmittedOverload& overload, const std::string& method_owner,
                               const std::unordered_set<std::string>& wrapped_classes)
{
    output << "  " << (resolution.use_override ? "override " : "") << resolution.name << "(";
    bool first = true;
    for (const auto& wpar: overload.params)
    {
        if (!first)
        {
            output << ", ";
        }
        output << wpar.name << ": " << wpar.ts_type;
        first = false;
    }
    output << "): " << overload.return_type << " {\n";

    if (declared_name == "DeleteItem")
    {
        EmitDisposedGuard(output, overload.return_type);
    }

    std::string call = "lib.symbols." + CFuncName(*overload.func) + "(";
    size_t visible_index = 0;
    bool call_first = true;
    for (const auto& argument: overload.ffi_arguments)
    {
        if (!call_first)
        {
            call += ", ";
        }
        call_first = false;
        if (argument.kind == FfiArgumentKind::self)
        {
            call += "this._ptr";
            continue;
        }
        const WrapParam& wpar = overload.params[visible_index];
        call += BuildFfiArgumentExpr(argument, wpar.name, wpar.ts_type, false);
        ++visible_index;
    }
    call += ")";

    EmitWrapReturn(output, *overload.func, method_owner, call, wrapped_classes);
    output << "  }\n\n";
}

static void EmitMergedBranch(std::ostream& output, const EmittedOverload& overload,
                             const std::string& declared_name, const std::string& method_name,
                             const std::vector<std::string>& impl_names,
                             const std::vector<std::string>& impl_types,
                             const std::vector<bool>& impl_optional,
                             const std::string& method_owner,
                             const std::unordered_set<std::string>& wrapped_classes)
{
    if (overload.from_ancestor)
    {
        std::string call = "super." + method_name + "(";
        for (size_t idx = 0; idx < overload.params.size(); ++idx)
        {
            if (idx > 0)
            {
                call += ", ";
            }
            call += CastArgument(impl_names[idx], impl_types[idx], impl_optional[idx],
                                 overload.params[idx].ts_type);
        }
        call += ")";
        if (overload.return_type == "void")
        {
            output << "      " << call << ";\n";
        }
        else
        {
            output << "      return " << call << ";\n";
        }
        return;
    }

    if (declared_name == "DeleteItem")
    {
        EmitDisposedGuard(output, overload.return_type);
    }

    std::string call = "lib.symbols." + CFuncName(*overload.func) + "(";
    size_t visible_index = 0;
    bool call_first = true;
    for (const auto& argument: overload.ffi_arguments)
    {
        if (!call_first)
        {
            call += ", ";
        }
        call_first = false;
        if (argument.kind == FfiArgumentKind::self)
        {
            call += "this._ptr";
            continue;
        }
        call += BuildFfiArgumentExpr(argument, impl_names[visible_index], impl_types[visible_index],
                                     impl_optional[visible_index]);
        ++visible_index;
    }
    call += ")";

    EmitWrapReturn(output, *overload.func, method_owner, call, wrapped_classes, "      ");
}

// True when this overload must run before an unguarded same-arity overload because it has
// a `typeof` check that separates it from a peer.
[[nodiscard]] static bool IsGuardedOverload(size_t self_index,
                                            const std::vector<EmittedOverload>& overloads)
{
    const EmittedOverload& self = overloads[self_index];
    for (size_t other_index = 0; other_index < overloads.size(); ++other_index)
    {
        if (other_index == self_index)
        {
            continue;
        }
        const EmittedOverload& other = overloads[other_index];
        if (self.params.size() != other.params.size())
        {
            continue;
        }
        for (size_t pidx = 0; pidx < self.params.size(); ++pidx)
        {
            if (self.params[pidx].ts_type != other.params[pidx].ts_type &&
                HasTypeGuard(self.params[pidx].ts_type))
            {
                return true;
            }
        }
    }
    return false;
}

[[nodiscard]] static std::vector<size_t>
    BuildDispatchOrder(const std::vector<EmittedOverload>& overloads)
{
    std::vector<size_t> arities;
    for (const auto& overload: overloads)
    {
        if (std::ranges::find(arities, overload.params.size()) == arities.end())
        {
            arities.push_back(overload.params.size());
        }
    }

    std::vector<size_t> order;
    for (const size_t arity: arities)
    {
        for (size_t idx = 0; idx < overloads.size(); ++idx)
        {
            if (overloads[idx].params.size() == arity && IsGuardedOverload(idx, overloads))
            {
                order.push_back(idx);
            }
        }
        for (size_t idx = 0; idx < overloads.size(); ++idx)
        {
            if (overloads[idx].params.size() == arity && !IsGuardedOverload(idx, overloads))
            {
                order.push_back(idx);
            }
        }
    }
    return order;
}

[[nodiscard]] static std::string
    BuildDispatchCondition(size_t self_index, const std::vector<EmittedOverload>& overloads,
                           const std::vector<std::string>& impl_names)
{
    const EmittedOverload& self = overloads[self_index];
    std::string condition = "arguments.length === " + std::to_string(self.params.size());
    for (size_t pidx = 0; pidx < self.params.size(); ++pidx)
    {
        if (!HasTypeGuard(self.params[pidx].ts_type))
        {
            continue;
        }
        bool differs = false;
        for (size_t other_index = 0; other_index < overloads.size(); ++other_index)
        {
            if (other_index == self_index)
            {
                continue;
            }
            const EmittedOverload& other = overloads[other_index];
            if (other.params.size() != self.params.size())
            {
                continue;
            }
            if (other.params[pidx].ts_type != self.params[pidx].ts_type)
            {
                differs = true;
                break;
            }
        }
        if (differs)
        {
            condition += " && " + TypeGuardExpression(self.params[pidx].ts_type, impl_names[pidx]);
        }
    }
    return condition;
}

static void EmitOverloadSet(std::ostream& output, const std::string& declared_name,
                            const MemberNameResolution& resolution,
                            const std::vector<EmittedOverload>& overloads,
                            const std::string& method_owner,
                            const std::unordered_set<std::string>& wrapped_classes)
{
    // Declarations: the class's own signature first, then every inherited signature that
    // must stay visible under the same name.
    for (const auto& overload: overloads)
    {
        output << "  override " << resolution.name << "(";
        bool first = true;
        for (const auto& wpar: overload.params)
        {
            if (!first)
            {
                output << ", ";
            }
            output << wpar.name << ": " << wpar.ts_type;
            first = false;
        }
        output << "): " << overload.return_type << ";\n";
    }

    // Implementation signature: the union of all parameter types, with optional
    // parameters where an overload is shorter.
    size_t arity = 0;
    for (const auto& overload: overloads)
    {
        arity = std::max(arity, overload.params.size());
    }

    std::vector<std::string> impl_names(arity);
    std::vector<std::string> impl_types(arity);
    std::vector<bool> impl_optional(arity, false);
    for (size_t idx = 0; idx < arity; ++idx)
    {
        std::vector<std::string> types;
        for (const auto& overload: overloads)
        {
            if (idx < overload.params.size())
            {
                const WrapParam& wpar = overload.params[idx];
                if (std::ranges::find(types, wpar.ts_type) == types.end())
                {
                    types.push_back(wpar.ts_type);
                }
                if (impl_names[idx].empty())
                {
                    impl_names[idx] = wpar.name;
                }
            }
            else
            {
                impl_optional[idx] = true;
            }
        }
        if (impl_names[idx].empty())
        {
            impl_names[idx] = "arg" + std::to_string(idx);
        }
        for (size_t type_index = 0; type_index < types.size(); ++type_index)
        {
            if (type_index > 0)
            {
                impl_types[idx] += " | ";
            }
            impl_types[idx] += types[type_index];
        }
    }

    // Implementation parameter names must be unique even when overloads use the same
    // name at different positions.
    std::set<std::string> used_names;
    for (size_t idx = 0; idx < arity; ++idx)
    {
        std::string candidate = impl_names[idx];
        if (used_names.contains(candidate))
        {
            size_t suffix = 2;
            std::string unique_name = candidate + std::to_string(suffix);
            while (used_names.contains(unique_name))
            {
                ++suffix;
                unique_name = candidate + std::to_string(suffix);
            }
            candidate = unique_name;
        }
        used_names.insert(candidate);
        impl_names[idx] = candidate;
    }

    std::vector<std::string> return_types;
    for (const auto& overload: overloads)
    {
        if (std::ranges::find(return_types, overload.return_type) == return_types.end())
        {
            return_types.push_back(overload.return_type);
        }
    }
    std::string impl_return;
    for (size_t type_index = 0; type_index < return_types.size(); ++type_index)
    {
        if (type_index > 0)
        {
            impl_return += " | ";
        }
        impl_return += return_types[type_index];
    }

    output << "  override " << resolution.name << "(";
    for (size_t idx = 0; idx < arity; ++idx)
    {
        if (idx > 0)
        {
            output << ", ";
        }
        output << impl_names[idx];
        if (impl_optional[idx])
        {
            output << "?";
        }
        output << ": " << impl_types[idx];
    }
    output << "): " << impl_return << " {\n";

    const std::vector<size_t> dispatch_order = BuildDispatchOrder(overloads);
    for (size_t order_index = 0; order_index < dispatch_order.size(); ++order_index)
    {
        const size_t overload_index = dispatch_order[order_index];
        const bool is_last = order_index + 1 == dispatch_order.size();
        if (order_index == 0)
        {
            output << "    if (" << BuildDispatchCondition(overload_index, overloads, impl_names)
                   << ") {\n";
        }
        else if (is_last)
        {
            output << "    else {\n";
        }
        else
        {
            output << "    else if ("
                   << BuildDispatchCondition(overload_index, overloads, impl_names) << ") {\n";
        }
        EmitMergedBranch(output, overloads[overload_index], declared_name, resolution.name,
                         impl_names, impl_types, impl_optional, method_owner, wrapped_classes);
        output << "    }\n";
    }
    output << "  }\n\n";
}

// Emit a single instance-method wrapper.  method_owner is the class the method is
// declared against (used for member renames); the receiver is always this._ptr.
// Returns the emitted TypeScript member name, which differs from TsMethodName() when the
// member hides an ancestor signature it cannot override.
static std::string EmitInstanceMethod(std::ostream& output, const AncestorMembers& ancestors,
                                      const std::string& method_owner, const FunctionDecl& func,
                                      const std::set<std::string>& taken,
                                      const std::unordered_set<std::string>& wrapped_classes)
{
    const bool pseudo_self = IsPseudoSelf(func);
    const std::string original_name = TsMethodName(method_owner, func);

    EmittedOverload own_overload;
    own_overload.return_type = WrapReturnType(func, method_owner, wrapped_classes);
    own_overload.func = &func;

    for (size_t pidx = 0; pidx < func.params.size(); ++pidx)
    {
        const Param& param = func.params[pidx];
        if (pseudo_self && pidx == 0)
        {
            own_overload.ffi_arguments.push_back({ FfiArgumentKind::self, "" });
            continue;
        }
        const std::vector<WrapParam> params = BuildWrapParams(param);
        for (const auto& wpar: params)
        {
            if (wpar.is_self)
            {
                own_overload.ffi_arguments.push_back({ FfiArgumentKind::self, "" });
                continue;
            }
            own_overload.params.push_back(wpar);
            own_overload.ffi_arguments.push_back(
                { wpar.ts_type == "boolean" ? FfiArgumentKind::boolean : FfiArgumentKind::plain,
                  wpar.ts_type });
        }
    }

    AncestorMemberInfo own_info = BuildAncestorMemberInfo(func, method_owner);
    own_info.origin_name = original_name;
    const std::vector<AncestorMemberInfo> own_overloads { own_info };
    const MemberNameResolution resolution =
        ResolveMemberName(original_name, method_owner, own_overloads, ancestors, taken);

    if (resolution.renamed)
    {
        RecordRename({ method_owner, func.method_name, resolution.name, "incompatible overload" });
    }
    else if (resolution.adopted_rename)
    {
        RecordRename({ method_owner, func.method_name, resolution.name, "inherited rename" });
    }

    std::vector<EmittedOverload> overloads;
    overloads.push_back(std::move(own_overload));
    for (const auto& inherited: resolution.inherited_overloads)
    {
        EmittedOverload inherited_overload;
        inherited_overload.params = inherited.params;
        inherited_overload.return_type = inherited.return_type;
        inherited_overload.from_ancestor = true;
        overloads.push_back(std::move(inherited_overload));
    }

    if (overloads.size() == 1)
    {
        EmitSingleOverload(output, original_name, resolution, overloads[0], method_owner,
                           wrapped_classes);
    }
    else
    {
        EmitOverloadSet(output, original_name, resolution, overloads, method_owner,
                        wrapped_classes);
    }
    return resolution.name;
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
        params.insert(params.end(), expanded.begin(), expanded.end());
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
    s_rename_records.clear();

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

    std::ranges::sort(s_rename_records,
                      [](const RenameRecord& lhs, const RenameRecord& rhs)
                      {
                          if (lhs.class_name != rhs.class_name)
                          {
                              return lhs.class_name < rhs.class_name;
                          }
                          return lhs.member_name < rhs.member_name;
                      });
    if (!s_rename_records.empty())
    {
        std::println(stderr, "  member renames:          {}", s_rename_records.size());
        for (const auto& record: s_rename_records)
        {
            std::println(stderr, "    {}.{} -> {} ({})", record.class_name, record.member_name,
                         record.exposed_as, record.reason);
        }
    }
    if (!s_rename_report_path.empty())
    {
        WriteRenameReport();
        std::println(stderr, "  rename report:           {}", s_rename_report_path);
    }

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
    output << "}\n\n";

    // Name table: one entry per value, in the same order and cardinality so callers can
    // pair kwxConstants_IntTable()[i] with kwxConstants_NameTable()[i].
    if (table.empty())
    {
        output << "WXFFI_EXPORT(const char* const*, kwxConstants_NameTable)()\n{\n";
        output << "    static const char* const s_names[1] = { nullptr };\n";
        output << "    return s_names;\n";
        output << "}\n";
    }
    else
    {
        output << "WXFFI_EXPORT(const char* const*, kwxConstants_NameTable)()\n{\n";
        output << "    static const char* const s_names[" << table_size << "] = {\n";
        for (const auto& entry: table)
        {
            output << "        \"" << entry.ts_name << "\",\n";
        }
        output << "    };\n";
        output << "    return s_names;\n";
        output << "}\n";
    }

    output << "}\n";

    std::println(stderr, "  kwx_constants_table_gen.cpp: {} table entries", table.size());
}

// -------------------------------------------------------------------------
// kwx_free_functions_gen.ts — free-function wrappers
// -------------------------------------------------------------------------

void TypeScriptEmitter::GenerateFreeFunctions(const ParsedFFI& ffi, const fs::path& out_dir)
{
    if (!HasModuleLevelFunctions(ffi))
    {
        return;
    }

    const fs::path file_path = out_dir / "kwx_free_functions_gen.ts";
    ConditionalFileWriter output(file_path);

    WriteGeneratedHeader(output, "//");

    std::ostringstream body;
    size_t func_count = 0;
    size_t free_func_count = 0;
    for (const auto& func: ffi.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }

        const std::string func_name = CFuncName(func);
        // Free functions have no enclosing class, so the factory path never applies.
        const std::unordered_set<std::string> no_wrapped_classes;
        const std::string ret_type = WrapReturnType(func, "", no_wrapped_classes);

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

        EmitWrapReturn(body, func, "", call, no_wrapped_classes);

        body << "}\n\n";
        ++func_count;
        ++free_func_count;
    }

    // Functions declared inside a class block without a receiver are static in wxWidgets, so
    // they are emitted at module scope as <Class>_<Method> instead of instance methods.
    std::set<std::string> emitted_static_names;
    for (const auto& cls: ffi.classes)
    {
        for (const auto& func: cls.methods)
        {
            if (!IsValidFunction(func) || !IsStaticClassFunction(func, &cls))
            {
                continue;
            }

            const std::string export_name = cls.name + "_" + TsEscapeName(func.method_name);
            if (!emitted_static_names.insert(export_name).second)
            {
                std::println(stderr, "  Warning: {}: dropping duplicate static {} (C symbol {})",
                             cls.name, export_name, CFuncName(func));
                continue;
            }

            const std::string func_name = CFuncName(func);
            // No enclosing class, so the factory path of WrapReturnType must never trigger.
            const std::unordered_set<std::string> no_wrapped_classes;
            const std::string ret_type = WrapReturnType(func, "", no_wrapped_classes);

            std::vector<WrapParam> wrap_params;
            for (const auto& param: func.params)
            {
                const std::vector<WrapParam> params = BuildWrapParams(param);
                wrap_params.insert(wrap_params.end(), params.begin(), params.end());
            }

            body << "export function " << export_name << "(";
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

            EmitWrapReturn(body, func, "", call, no_wrapped_classes);

            body << "}\n\n";
            ++func_count;
        }
    }

    const std::string body_str = body.str();
    output << "import { lib } from \"./kwx_ffi_gen.ts\";\n";
    if (body_str.find("Pointer") != std::string::npos)
    {
        output << "import { Pointer } from \"kwx/platform\";\n";
    }
    output << "\n";
    output << body_str;

    std::println(stderr,
                 "  kwx_free_functions_gen.ts: {} free functions, {} static class functions",
                 free_func_count, func_count - free_func_count);
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
        body << "  protected _borrowed: boolean = false;\n";
        body << "  protected _disposed: boolean = false;\n\n";
        body << "  constructor(ptr: Pointer, borrowed: boolean = false) {\n";
        body << "    this._ptr = ptr;\n";
        body << "    this._borrowed = borrowed;\n";
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
        body << "    if (this._disposed || this._borrowed) return;\n";
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
        // Skip statics (emitted at module scope in kwx_free_functions_gen.ts)
        if (IsStaticClassFunction(func, &cls))
        {
            continue;
        }

        const std::string method_name = TsMethodName(cls.name, func);
        if (emitted_instance_names.contains(method_name))
        {
            std::println(stderr, "  Warning: {}: dropping duplicate method {} (C symbol {})",
                         cls.name, method_name, CFuncName(func));
            continue;  // skip duplicate overload
        }
        const std::string emitted_name = EmitInstanceMethod(
            body, ancestors, cls.name, func, emitted_instance_names, wrapped_classes);
        emitted_instance_names.insert(emitted_name);
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
                if (!IsValidFunction(func) || IsFactoryMethod(func) || IsTrueDestructor(func) ||
                    IsStaticClassFunction(func, mixin_class))
                {
                    continue;
                }
                const std::string mixin_member_name = TsMethodName(mixin_name, func);
                if (ancestors.instance_names.contains(mixin_member_name))
                {
                    // A wrapped ancestor already exposes this member; re-emitting it here
                    // would produce a duplicate member (TS4114) or a signature clash (TS2416).
                    continue;
                }
                if (emitted_instance_names.contains(mixin_member_name))
                {
                    continue;  // consumer already exposes this name
                }
                const std::string emitted_name = EmitInstanceMethod(
                    body, ancestors, mixin_name, func, emitted_instance_names, wrapped_classes);
                emitted_instance_names.insert(emitted_name);
            }
        }
    }

    body << "}\n";

    // --- Constructors as module-level factory functions ---
    // Static factories cannot be inherited: TypeScript requires every derived static
    // member to be assignable to the ancestor's static side (TS2417), which is
    // impossible when each class declares a different Create() signature.
    std::set<std::string> emitted_factory_names;
    std::set<std::string> factory_return_imports;
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
        const std::string ret_type = WrapReturnType(func, cls.name, wrapped_classes);

        // A factory may construct a different generated class; that name must be imported
        // or the emitted identifier is unresolved (TS2552).
        const std::string created_class = EffectiveFactoryClass(func, cls.name, wrapped_classes);
        if (created_class != cls.name && created_class != parent_name)
        {
            factory_return_imports.insert(created_class);
        }

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

        EmitWrapReturn(body, func, cls.name, call, wrapped_classes);

        body << "}\n";
    }

    // Non-owning factory: the pointer belongs to wxWidgets, so Delete() is a no-op.
    // Dropping the wx prefix gives wrapWxWindow / wrapWxNotebook.
    std::string wrap_suffix = cls.name;
    if (wrap_suffix.starts_with(WX_PREFIX) && wrap_suffix.size() > WX_PREFIX.size())
    {
        wrap_suffix = wrap_suffix.substr(WX_PREFIX.size());
    }
    body << "\n/** Wraps a pointer to an object owned by wxWidgets; Delete() is a no-op. */\n";
    body << "export function wrapWx" << wrap_suffix << "(ptr: Pointer): " << cls.name << " {\n";
    body << "    return new " << cls.name << "(ptr, true);\n";
    body << "}\n";

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
    for (const std::string& imported_class: factory_return_imports)
    {
        output << "import { " << imported_class << " } from \"" << TsClassImportPath(imported_class)
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

    if (HasModuleLevelFunctions(ffi))
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
