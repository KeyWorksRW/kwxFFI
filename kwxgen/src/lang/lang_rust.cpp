/////////////////////////////////////////////////////////////////////////////
// Purpose:   Rust FFI code generator with safe wrappers
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "lang_rust.h"

#include "../file_writer.h"
#include "lang_common.h"
#include "rust_type_map.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <map>
#include <print>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

// NOLINTBEGIN(readability-magic-string)

namespace fs = std::filesystem;

// Build a C function name from a FunctionDecl.

// Strip wx/kwx prefix: "wxButton" → "Button"
[[nodiscard]] static std::string StripPrefix(const std::string& name)
{
    if (name.size() > WX_PREFIX.length() && name.starts_with(WX_PREFIX) &&
        std::isupper(name[WX_PREFIX.length()]))
    {
        return name.substr(WX_PREFIX.length());
    }
    if (name.size() > KWX_PREFIX.length() && name.starts_with(KWX_PREFIX) &&
        std::isupper(name[KWX_PREFIX.length()]))
    {
        return name.substr(KWX_PREFIX.length());
    }
    return name;
}

// Convert CamelCase to snake_case: "SetDefault" → "set_default"

// Convert a method name to a safe Rust method name (snake_case, keyword-escaped).
[[nodiscard]] static std::string RustSafeMethodName(const std::string& methodName)
{
    const std::string snake = ToSnakeCase(methodName);
    // Check for Rust keywords
    if (snake == "move" || snake == "break" || snake == "continue" || snake == "return" ||
        snake == "type" || snake == "self" || snake == "super" || snake == "crate" ||
        snake == "match" || snake == "ref" || snake == "mod" || snake == "use" || snake == "fn" ||
        snake == "let" || snake == "mut" || snake == "pub" || snake == "if" || snake == "else" ||
        snake == "for" || snake == "while" || snake == "loop" || snake == "in" || snake == "as" ||
        snake == "impl" || snake == "trait" || snake == "struct" || snake == "enum" ||
        snake == "union" || snake == "const" || snake == "static" || snake == "extern" ||
        snake == "unsafe" || snake == "async" || snake == "await" || snake == "dyn" ||
        snake == "where" || snake == "yield" || snake == "box" || snake == "macro" ||
        snake == "true" || snake == "false" || snake == "abstract" || snake == "become" ||
        snake == "do" || snake == "final" || snake == "override" || snake == "priv" ||
        snake == "try" || snake == "typeof" || snake == "unsized" || snake == "virtual")
    {
        return snake + "_";
    }
    // Identifiers starting with a digit are invalid in Rust
    if (!snake.empty() && std::isdigit(static_cast<unsigned char>(snake[0])))
    {
        return "_" + snake;
    }
    return snake;
}

// Lowercase a string entirely.

// Rust module name from class name: "wxButton" → "button"
[[nodiscard]] static std::string RustModuleName(const std::string& className)
{
    return ToSnakeCase(StripPrefix(className));
}

// Emit a single extern "C" declaration for sys.rs.
static void EmitExternDecl(std::ostream& out, const std::string& funcName,
                           const std::string& returnType, const std::vector<RustFFIParam>& params)
{
    out << "    pub fn " << funcName << "(";
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (i > 0)
        {
            out << ", ";
        }
        out << params[i].name << ": " << params[i].rust_type;
    }
    out << ")";
    if (!returnType.empty())
    {
        out << " -> " << returnType;
    }
    out << ";\n";
}

// Emit an extern "C" declaration from a FunctionDecl.
static void EmitFunctionExternDecl(std::ostream& out, const FunctionDecl& func)
{
    const std::string retType = RustFFIReturnType(func.return_type, func.return_macro);
    const std::string funcName = CFuncName(func);

    std::vector<RustFFIParam> params;
    for (const auto& param: func.params)
    {
        std::vector<RustFFIParam> expanded = ExpandParamToRustFFI(param);
        for (auto& rust_param: expanded)
        {
            params.push_back(std::move(rust_param));
        }
    }

    EmitExternDecl(out, funcName, retType, params);
}

// Check if a function declaration looks valid (skip malformed ones).

// A true destructor takes only self as its parameter.
[[nodiscard]] static bool IsDestructor(const FunctionDecl& func)
{
    return func.is_destructor && func.params.size() == 1;
}

// Determine the safe Rust return type for a method.
[[nodiscard]] static std::string
    RustSafeReturnType(const FunctionDecl& func, [[maybe_unused]] const std::string& rustClassName)
{
    if (func.return_type == "void" || func.return_type.empty())
    {
        return "";
    }
    if (func.return_macro == "TClass" || func.return_macro == "TSelf" ||
        func.return_macro == "TClassRef")
    {
        return "*mut c_void";
    }
    if (func.return_type == "TBool" || func.return_type == "TBoolInt")
    {
        return "bool";
    }
    if (func.return_type == "TString" || func.return_type == "TStringOut" ||
        func.return_type == "TStringVoid")
    {
        return "*mut c_void";
    }
    if (func.return_type == "int" || func.return_type == "TArrayLen" ||
        func.return_type == "TByteStringLen")
    {
        return "i32";
    }
    if (func.return_type == "long" || func.return_type == "time_t")
    {
        return "i64";
    }
    if (func.return_type == "unsigned" || func.return_type == "unsigned int")
    {
        return "u32";
    }
    if (func.return_type == "unsigned long" || func.return_type == "wxUIntPtr")
    {
        return "u64";
    }
    if (func.return_type == "uintptr_t")
    {
        return "usize";
    }
    if (func.return_type == "double")
    {
        return "f64";
    }
    if (func.return_type == "float")
    {
        return "f32";
    }
    if (func.return_type == "TChar")
    {
        return "u8";
    }
    if (func.return_type == "TUInt8")
    {
        return "u8";
    }
    if (func.return_type == "size_t")
    {
        return "usize";
    }
    if (func.return_type == "void*")
    {
        return "*mut c_void";
    }
    if (func.return_type.contains('*'))
    {
        return "*mut c_void";
    }

    return "i32";
}

// Generate the conversion expression wrapping a raw FFI return value to safe Rust type.
// `call_expr` is the unsafe FFI call expression.
[[nodiscard]] static std::string WrapReturnExpr(const FunctionDecl& func,
                                                const std::string& callExpr)
{
    const std::string safeType = RustSafeReturnType(func, "");

    if (safeType.empty())
    {
        return callExpr;  // void
    }
    if (safeType == "bool")
    {
        return callExpr + " != 0";
    }
    if (safeType == "i32")
    {
        return callExpr + " as i32";
    }
    if (safeType == "i64")
    {
        return callExpr + " as i64";
    }
    if (safeType == "u32")
    {
        return callExpr + " as u32";
    }
    if (safeType == "u64")
    {
        return callExpr + " as u64";
    }
    if (safeType == "f64")
    {
        return callExpr + " as f64";
    }
    if (safeType == "f32")
    {
        return callExpr + " as f32";
    }
    if (safeType == "u8")
    {
        return callExpr + " as u8";
    }
    if (safeType == "usize")
    {
        return callExpr + " as usize";
    }

    // Pointers pass through
    return callExpr;
}

// Info about a safe Rust parameter in a method signature.
struct RustSafeParam
{
    std::string name;
    std::string safe_type;      // Safe Rust type for the method signature
    std::string ffi_expr;       // Expression(s) to convert and pass to the FFI call
    std::string setup;          // Local declaration emitted before the FFI call
    std::string new_default;    // FFI arguments used by `new` when the parameter is defaulted
    bool new_excluded = false;  // Omitted from `new`; `new_default` supplies its arguments
};

// Context shared by the parameter converter.
struct RustConvertContext
{
    const ParsedFFI& ffi;
    const std::set<std::string>& parent_classes;
    const std::string& rust_name;
    std::set<std::string>& support_imports;
};

// Convert a C parameter name to a Rust-safe snake_case identifier.
[[nodiscard]] static std::string RustSafeParamName(const std::string& raw_name)
{
    return RustEscapeName(ToSnakeCase(raw_name));
}

// Classes that serve as parents get a marker trait in traits.rs.
[[nodiscard]] static std::set<std::string> BuildParentClassSet(const ParsedFFI& ffi)
{
    std::set<std::string> parent_classes;
    for (const auto& [child, parent]: ffi.parent_map)
    {
        parent_classes.insert(parent);
    }
    for (const auto& cls: ffi.classes)
    {
        if (!cls.parent.empty())
        {
            parent_classes.insert(cls.parent);
        }
    }
    return parent_classes;
}

// Marker trait generated for a class, or empty when the class has no trait.
[[nodiscard]] static std::string TraitForClass(const std::string& class_name,
                                               const std::set<std::string>& parent_classes)
{
    if (!parent_classes.contains(class_name))
    {
        return {};
    }
    const std::string trait_name = StripPrefix(class_name);
    if (trait_name == "Object")
    {
        return {};
    }
    return "Wx" + trait_name;
}

// True for the geometry value types emitted in support.rs.
[[nodiscard]] static bool IsSupportTypeName(const std::string& type_name)
{
    return type_name == "Point" || type_name == "Size" || type_name == "Rect";
}

// Type name for a support.rs value type inside a generated module. A module that defines a
// type with the same name (point.rs, size.rs, rect.rs) must use the qualified path.
[[nodiscard]] static std::string SupportTypeName(const std::string& type_name,
                                                 const std::string& rust_name)
{
    if (type_name == rust_name)
    {
        return "crate::support::" + type_name;
    }
    return type_name;
}

// True when BuildEmitClasses will emit a module for this class.
[[nodiscard]] static bool HasGeneratedClass(const std::string& class_name, const ParsedFFI& ffi)
{
    if (class_name == "wxObject")
    {
        return true;
    }
    if (ffi.parent_map.contains(class_name))
    {
        return true;
    }
    for (const auto& cls: ffi.classes)
    {
        if (cls.name == class_name || cls.parent == class_name)
        {
            return true;
        }
    }
    return false;
}

// Generated wrapper name overrides that are part of the public binding contract.
[[nodiscard]] static std::string RustWrapperMethodName(const FunctionDecl& func)
{
    const std::string c_func_name = CFuncName(func);
    if (c_func_name == "wxSizer_Add")
    {
        return "add_sized_spacer";
    }
    if (c_func_name == "wxDialog_CreateStdDialogButtonSizer")
    {
        return "create_std_button_sizer";
    }
    return RustSafeMethodName(func.method_name);
}

// Expand a value-geometry parameter (TRect/TPoint/TSize) into one support.rs struct argument.
[[nodiscard]] static std::vector<RustSafeParam>
    ConvertGeometryParam(const Param& param, const RustConvertContext& context)
{
    std::vector<RustSafeParam> result;
    const std::vector<std::string> components = RustSplitMacroArg(param.macro_arg);

    std::string type_name;
    std::vector<std::string> fields;
    std::string default_name;
    if (param.macro_name == "TRect")
    {
        type_name = "Rect";
        default_name = "rect";
        fields = { "x", "y", "width", "height" };
    }
    else if (param.macro_name == "TPoint")
    {
        type_name = "Point";
        default_name = "point";
        fields = { "x", "y" };
    }
    else if (param.macro_name == "TSize")
    {
        type_name = "Size";
        default_name = "size";
        fields = { "width", "height" };
    }

    if (fields.empty() || components.size() != fields.size())
    {
        // Unexpected shape: keep the raw component expansion so the FFI call stays correct.
        for (const std::string& component: components)
        {
            const std::string name = RustSafeParamName(component);
            result.push_back({ name, "i32", name + " as c_int", {}, {}, false });
        }
        return result;
    }

    RustSafeParam safe_param;
    safe_param.name = RustSafeParamName(param.param_name.empty() ? default_name : param.param_name);
    const std::string display_type = SupportTypeName(type_name, context.rust_name);
    if (display_type == type_name)
    {
        context.support_imports.insert(type_name);
    }
    safe_param.safe_type = display_type;

    std::string ffi_expr;
    std::string new_default;
    for (size_t i = 0; i < fields.size(); ++i)
    {
        if (i > 0)
        {
            ffi_expr += ", ";
            new_default += ", ";
        }
        ffi_expr += safe_param.name + "." + fields[i] + " as c_int";
        new_default += display_type + "::default()." + fields[i] + " as c_int";
    }
    safe_param.ffi_expr = ffi_expr;
    // Only TRect has a default in the short constructor; Point/Size stay required.
    if (param.macro_name == "TRect")
    {
        safe_param.new_excluded = true;
        safe_param.new_default = new_default;
    }
    result.push_back(std::move(safe_param));
    return result;
}

// Convert one Param to safe Rust parameters (for method wrappers).
[[nodiscard]] static std::vector<RustSafeParam>
    ConvertParamToSafe(const Param& param, const RustConvertContext& context)
{
    std::vector<RustSafeParam> result;

    if (param.macro_name == "TRect" || param.macro_name == "TPoint" || param.macro_name == "TSize")
    {
        return ConvertGeometryParam(param, context);
    }

    // Vector geometry and long geometry types keep their component expansion.
    if (param.macro_name == "TVector" || param.macro_name == "TPointLong" ||
        param.macro_name == "TSizeLong" || param.macro_name == "TRectLong" ||
        param.macro_name == "TVectorLong")
    {
        const bool is_long = param.macro_name != "TVector";
        const std::string type_name = is_long ? "i64" : "i32";
        const std::string cast = is_long ? " as c_long" : " as c_int";
        for (const std::string& component: RustSplitMacroArg(param.macro_arg))
        {
            const std::string name = RustSafeParamName(component);
            result.push_back({ name, type_name, name + cast, {}, {}, false });
        }
        return result;
    }

    // Output geometry passes through as raw pointers.
    if (param.macro_name == "TPointOut" || param.macro_name == "TSizeOut" ||
        param.macro_name == "TRectOut" || param.macro_name == "TVectorOut")
    {
        for (const std::string& component: RustSplitMacroArg(param.macro_arg))
        {
            const std::string name = RustSafeParamName(component);
            result.push_back({ name, "*mut i32", name + " as *mut c_int", {}, {}, false });
        }
        return result;
    }

    if (param.macro_name == "TPointOutVoid" || param.macro_name == "TSizeOutVoid" ||
        param.macro_name == "TRectOutVoid" || param.macro_name == "TVectorOutVoid")
    {
        for (const std::string& component: RustSplitMacroArg(param.macro_arg))
        {
            const std::string name = RustSafeParamName(component);
            result.push_back({ name, "*mut c_void", name, {}, {}, false });
        }
        return result;
    }

    if (param.macro_name == "TSizeOutDouble")
    {
        for (const std::string& component: RustSplitMacroArg(param.macro_arg))
        {
            const std::string name = RustSafeParamName(component);
            result.push_back({ name, "*mut f64", name + " as *mut c_double", {}, {}, false });
        }
        return result;
    }

    if (param.macro_name == "TColorRGB")
    {
        for (const std::string& component: RustSplitMacroArg(param.macro_arg))
        {
            const std::string name = RustSafeParamName(component);
            result.push_back({ name, "u8", name, {}, {}, false });
        }
        return result;
    }

    // Array types stay raw.
    if (param.macro_name == "TArrayString" || param.macro_name == "TArrayInt" ||
        param.macro_name == "TByteString" || param.macro_name == "TByteStringLazy")
    {
        const std::vector<std::string> names = RustSplitMacroArg(param.macro_arg);
        if (names.size() >= 2)
        {
            const std::string count_name = RustSafeParamName(names[0]);
            const std::string array_name = RustSafeParamName(names[1]);
            result.push_back({ count_name, "i32", count_name + " as c_int", {}, {}, false });
            result.push_back({ array_name, "*mut c_void", array_name, {}, {}, false });
        }
        return result;
    }

    if (param.macro_name == "TArrayObjectOutVoid")
    {
        const std::string name =
            RustSafeParamName(param.param_name.empty() ? "arr" : param.param_name);
        result.push_back({ name, "*mut c_void", name, {}, {}, false });
        return result;
    }

    // Single parameter
    RustSafeParam safe_param;
    safe_param.name = RustSafeParamName(param.param_name.empty() ? "arg" : param.param_name);

    if (param.macro_name == "TSelf")
    {
        const std::string trait_name = TraitForClass(param.macro_arg, context.parent_classes);
        safe_param.safe_type =
            "&impl " + (trait_name.empty() ? std::string { "WxObject" } : trait_name);
        safe_param.ffi_expr = safe_param.name + ".as_ptr()";
    }
    else if (param.macro_name == "TClass" || param.macro_name == "TClassRef")
    {
        if (param.macro_arg == "wxString")
        {
            safe_param.safe_type = "impl AsRef<str>";
            const std::string local = safe_param.name + "_wx";
            safe_param.setup = "let " + local + " = WxStr::new(" + safe_param.name + ".as_ref());";
            safe_param.ffi_expr = local + ".as_ptr()";
            context.support_imports.insert("WxStr");
        }
        else
        {
            const std::string trait_name = TraitForClass(param.macro_arg, context.parent_classes);
            safe_param.safe_type =
                "&impl " + (trait_name.empty() ? std::string { "WxObject" } : trait_name);
            safe_param.ffi_expr = safe_param.name + ".as_ptr()";
        }
    }
    else if (param.raw_type == "TBool*")
    {
        safe_param.safe_type = "i32";
        safe_param.ffi_expr = safe_param.name + " as c_int";
    }
    else if (param.macro_name == "TBool" || param.raw_type == "TBool" ||
             param.raw_type == "TBoolInt")
    {
        safe_param.safe_type = "bool";
        safe_param.ffi_expr = safe_param.name + " as c_int";
    }
    else if (param.macro_name == "TClosureFun" || param.raw_type == "TClosureFun")
    {
        safe_param.safe_type = "*mut c_void";
        safe_param.ffi_expr = safe_param.name;
    }
    else if (param.raw_type == "TStringVoid" || param.macro_name == "TStringVoid")
    {
        safe_param.safe_type = "*mut c_void";
        safe_param.ffi_expr = safe_param.name;
    }
    else if (param.raw_type == "TArrayIntOutVoid" || param.raw_type == "TArrayIntPtrOutVoid" ||
             param.raw_type == "TArrayStringOutVoid" || param.raw_type == "TByteStringOut" ||
             param.raw_type == "TByteStringLazyOut" || param.raw_type == "TArrayObjectOutVoid")
    {
        safe_param.safe_type = "*mut c_void";
        safe_param.ffi_expr = safe_param.name;
    }
    else if (param.raw_type == "TChar")
    {
        safe_param.safe_type = "u8";
        safe_param.ffi_expr = safe_param.name + " as c_char";
    }
    else if (param.raw_type == "TUInt8")
    {
        safe_param.safe_type = "u8";
        safe_param.ffi_expr = safe_param.name;
    }
    else if (param.raw_type == "TString")
    {
        // char* input: build a NUL-terminated copy for the FFI call.
        safe_param.safe_type = "impl AsRef<str>";
        const std::string local = safe_param.name + "_c";
        safe_param.setup = "let " + local + " = std::ffi::CString::new(" + safe_param.name +
                           ".as_ref()).unwrap_or_else(|_| std::ffi::CString::new(\"\").unwrap());";
        safe_param.ffi_expr = local + ".as_ptr()";
    }
    else if (param.raw_type == "TStringOut")
    {
        safe_param.safe_type = "*mut c_char";
        safe_param.ffi_expr = safe_param.name;
    }
    else
    {
        const std::string& raw_type = param.raw_type;
        if (raw_type.empty() || raw_type == "int")
        {
            safe_param.safe_type = "i32";
            safe_param.ffi_expr = safe_param.name + " as c_int";
        }
        else if (raw_type == "long")
        {
            safe_param.safe_type = "i32";
            safe_param.ffi_expr = safe_param.name + " as c_long";
        }
        else if (raw_type == "unsigned" || raw_type == "unsigned int")
        {
            safe_param.safe_type = "u32";
            safe_param.ffi_expr = safe_param.name + " as c_uint";
        }
        else if (raw_type == "unsigned long" || raw_type == "wxUIntPtr")
        {
            safe_param.safe_type = "u64";
            safe_param.ffi_expr = safe_param.name + " as c_ulong";
        }
        else if (raw_type == "uintptr_t")
        {
            safe_param.safe_type = "usize";
            safe_param.ffi_expr = safe_param.name + " as usize";
        }
        else if (raw_type == "double")
        {
            safe_param.safe_type = "f64";
            safe_param.ffi_expr = safe_param.name + " as c_double";
        }
        else if (raw_type == "float")
        {
            safe_param.safe_type = "f32";
            safe_param.ffi_expr = safe_param.name + " as c_float";
        }
        else if (raw_type == "size_t")
        {
            safe_param.safe_type = "usize";
            safe_param.ffi_expr = safe_param.name;
        }
        else if (raw_type.contains('*'))
        {
            safe_param.safe_type = "*mut c_void";
            safe_param.ffi_expr = safe_param.name;
        }
        else
        {
            safe_param.safe_type = "i32";
            safe_param.ffi_expr = safe_param.name + " as c_int";
        }
    }

    // `id` and `style` have sensible defaults in the short constructor.
    if (param.macro_name.empty())
    {
        if (safe_param.name == "id")
        {
            safe_param.new_excluded = true;
            // Use the literal wxID_ANY value so the short constructor compiles
            // whether ID_ANY is emitted as a `const` or as an accessor function.
            safe_param.new_default = "-1";
        }
        else if (safe_param.name == "style")
        {
            safe_param.new_excluded = true;
            safe_param.new_default = "0";
        }
    }

    result.push_back(std::move(safe_param));
    return result;
}

// How a method's return value crosses back into safe Rust.
struct SafeReturn
{
    enum class Kind
    {
        none,
        scalar,
        string,
        class_ptr
    };

    Kind kind = Kind::none;
    std::string type;        // Type shown in the wrapper signature
    std::string class_type;  // Type used to build the returned handle
};

// Context needed to classify a method return and collect its imports.
struct RustReturnContext
{
    const ParsedFFI& ffi;
    const std::string& rust_name;
    const std::string& current_module;
    const std::string& parent_type;
    std::set<std::string>& class_imports;
    std::set<std::string>& support_imports;
};

// Classify a method return, recording any module imports the signature needs.
[[nodiscard]] static SafeReturn ClassifyMethodReturn(const FunctionDecl& method,
                                                     const RustReturnContext& context)
{
    SafeReturn result;

    if (method.return_type == "void" || method.return_type.empty())
    {
        return result;
    }

    const std::string string_type =
        (context.rust_name == "String") ? "::std::string::String" : "String";
    const bool is_class_return =
        method.return_macro == "TClass" || method.return_macro == "TClassRef";

    if ((is_class_return && method.return_arg == "wxString") || method.return_type == "TString")
    {
        result.kind = SafeReturn::Kind::string;
        result.type = string_type;
        context.support_imports.insert("take_string");
        return result;
    }

    if (is_class_return && !method.return_arg.empty() &&
        HasGeneratedClass(method.return_arg, context.ffi))
    {
        const std::string type_name = StripPrefix(method.return_arg);
        const std::string module_name = RustModuleName(method.return_arg);
        std::string display_type;
        if (module_name == context.current_module || type_name == context.rust_name ||
            type_name == context.parent_type)
        {
            display_type = type_name;
        }
        else if (IsSupportTypeName(type_name))
        {
            // The support.rs value type of the same name already owns the bare name.
            display_type = "crate::" + module_name + "::" + type_name;
        }
        else
        {
            context.class_imports.insert("use crate::" + module_name + "::" + type_name + ";");
            display_type = type_name;
        }
        result.kind = SafeReturn::Kind::class_ptr;
        result.class_type = display_type;
        result.type = "Option<" + display_type + ">";
        return result;
    }

    result.kind = SafeReturn::Kind::scalar;
    result.type = RustSafeReturnType(method, context.rust_name);
    if (result.type.empty())
    {
        result.kind = SafeReturn::Kind::none;
    }
    return result;
}

// Build the list of trait names a class should implement based on its hierarchy.
// Returns the chain from the most derived parent to the root.
[[nodiscard]] static std::vector<std::string> BuildTraitChain(const ClassInfo& cls,
                                                              const ParsedFFI& ffi)
{
    std::vector<std::string> chain;
    std::string current = cls.parent;
    std::set<std::string> visited;

    while (!current.empty() && !visited.contains(current))
    {
        visited.insert(current);
        chain.push_back(current);
        const std::unordered_map<std::string, std::string>::const_iterator parent_iter =
            ffi.parent_map.find(current);
        if (parent_iter != ffi.parent_map.end())
        {
            current = parent_iter->second;
        }
        else
        {
            break;
        }
    }

    return chain;
}

// -------------------------------------------------------------------------
// RustEmitter public interface
// -------------------------------------------------------------------------

void RustEmitter::Generate(const ParsedFFI& ffi, const fs::path& outDir)
{
    std::ignore = fs::create_directories(outDir);
    const fs::path srcDir = outDir / "src";
    std::ignore = fs::create_directories(srcDir);

    GenerateCargoToml(outDir);
    GenerateSys(ffi, srcDir);
    GenerateObject(ffi, srcDir);
    GenerateSupport(srcDir);
    GenerateTraits(ffi, srcDir);
    GenerateEvents(ffi, srcDir);
    GenerateKeys(ffi, srcDir);
    GenerateConstants(ffi, srcDir);
    GenerateFreeFunctions(ffi, srcDir);

    std::vector<std::string> classModules;
    GenerateClassFiles(ffi, srcDir, classModules);
    GenerateLib(ffi, srcDir, classModules);

    std::println(stderr, "Rust: generated crate in {}", outDir.string());
}

VerifyResult RustEmitter::Verify(const ParsedFFI& /* ffi */, const fs::path& /* dir */)
{
    VerifyResult result;
    result.success = true;
    result.messages.emplace_back("Rust verify: per-file verification is not implemented for Rust");
    return result;
}

// -------------------------------------------------------------------------
// Cargo.toml
// -------------------------------------------------------------------------

void RustEmitter::GenerateCargoToml(const fs::path& outDir)
{
    const fs::path path = outDir / "Cargo.toml";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    out << "# Code generated by kwxgen. DO NOT EDIT.\n\n";
    out << "[package]\n";
    out << "name = \"kwxffi-sys\"\n";
    out << "version = \"0.1.0\"\n";
    out << "edition = \"2021\"\n";
    out << "description = \"Raw FFI bindings to kwxFFI (wxWidgets C wrapper)\"\n";
    out << "publish = false\n";
    out << "\n";
    out << "[lib]\n";
    out << "name = \"kwxffi_sys\"\n";
    out << "path = \"src/lib.rs\"\n";
    out << "\n";
    // build.rs is hand-maintained (Phase 5 rule: regeneration must not disturb it), so the
    // generated manifest must keep declaring the helper crates build.rs depends on.
    out << "[build-dependencies]\n";
    out << "cc = \"1\"\n";

    std::println(stderr, "  Cargo.toml");
}

// -------------------------------------------------------------------------
// src/sys.rs — All extern "C" declarations
// -------------------------------------------------------------------------

void RustEmitter::GenerateSys(const ParsedFFI& ffi, const fs::path& srcDir)
{
    const fs::path path = srcDir / "sys.rs";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(out);
    out << "#![allow(non_snake_case)]\n\n";
    out << "use std::os::raw::*;\n\n";

    out << "extern \"C\" {\n";

    // Events
    {
        std::vector<EventDecl> sorted = ffi.events;
        std::ranges::sort(sorted, {}, &EventDecl::event_name);

        out << "    // Events\n";
        std::string lastEvtExport;
        for (const auto& event: sorted)
        {
            if (event.export_name == lastEvtExport)
            {
                continue;
            }
            lastEvtExport = event.export_name;
            out << "    pub fn " << event.export_name << "() -> c_int;\n";
        }
        out << "\n";
    }

    // Keys
    {
        std::vector<KeyDecl> sorted = ffi.keys;
        std::ranges::sort(sorted, {}, &KeyDecl::key_name);

        out << "    // Keys\n";
        for (const auto& k: sorted)
        {
            out << "    pub fn " << k.export_name << "() -> c_int;\n";
        }
        out << "\n";
    }

    // Constants
    {
        std::vector<ConstantDecl> sorted = ffi.constants;
        std::ranges::sort(sorted, {}, &ConstantDecl::export_name);

        out << "    // Constants\n";
        for (const auto& cnst: sorted)
        {
            const std::string retType = cnst.return_type.contains('*') ? "*mut c_void" : "c_int";
            out << "    pub fn " << cnst.export_name << "() -> " << retType << ";\n";
        }
        out << "\n";
    }

    // Free functions
    if (!ffi.free_functions.empty())
    {
        out << "    // Free functions\n";
        for (const auto& func: ffi.free_functions)
        {
            if (!IsValidFunction(func))
            {
                continue;
            }
            EmitFunctionExternDecl(out, func);
        }
        out << "\n";
    }

    // Class methods
    size_t methodCount = 0;
    size_t skippedCount = 0;
    for (const auto& cls: ffi.classes)
    {
        if (cls.methods.empty())
        {
            continue;
        }

        out << "    // " << cls.name << "\n";
        for (const auto& method: cls.methods)
        {
            if (!IsValidFunction(method))
            {
                ++skippedCount;
                continue;
            }
            EmitFunctionExternDecl(out, method);
            ++methodCount;
        }
        out << "\n";
    }

    out << "}\n";

    std::print(stderr, "  sys.rs:              {} events, {} keys, {} constants, {} methods",
               ffi.events.size(), ffi.keys.size(), ffi.constants.size(), methodCount);
    if (skippedCount > 0)
    {
        std::print(stderr, " ({} skipped)", skippedCount);
    }
    std::println(stderr, "");
}

// -------------------------------------------------------------------------
// src/traits.rs — Trait hierarchy for safe wrappers
// -------------------------------------------------------------------------

void RustEmitter::GenerateTraits(const ParsedFFI& ffi, const fs::path& srcDir)
{
    const fs::path path = srcDir / "traits.rs";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(out);
    out << "use std::os::raw::c_void;\n\n";

    // Collect all classes that serve as parents.
    const std::set<std::string> parentClasses = BuildParentClassSet(ffi);

    // Root trait: WxObject — all wxWidgets objects impl this.
    out << "/// Base trait for all wxWidgets objects providing raw pointer access.\n";
    out << "pub trait WxObject {\n";
    out << "    /// Returns the underlying raw pointer.\n";
    out << "    fn as_ptr(&self) -> *mut c_void;\n";
    out << "\n";
    out << "    /// Returns true if the underlying pointer is null.\n";
    out << "    fn is_null(&self) -> bool {\n";
    out << "        self.as_ptr().is_null()\n";
    out << "    }\n";
    out << "}\n\n";

    // Generate a trait for each class that serves as a parent, establishing the hierarchy.
    // Sort for deterministic output.
    std::vector<std::string> sortedParents(parentClasses.begin(), parentClasses.end());
    std::ranges::sort(sortedParents);

    size_t traitCount = 0;
    for (const auto& parentName: sortedParents)
    {
        const std::string traitName = StripPrefix(parentName);

        // Skip wxObject — it's already defined as the root trait WxObject above.
        if (traitName == "Object")
        {
            continue;
        }

        // Find parent of this parent to establish supertrait.
        const std::unordered_map<std::string, std::string>::const_iterator parent_iter =
            ffi.parent_map.find(parentName);
        std::string supertrait;
        if (parent_iter != ffi.parent_map.end() && !parent_iter->second.empty())
        {
            supertrait = "Wx" + StripPrefix(parent_iter->second);
            // Check if the supertrait's parent is also a parent class; if not, use WxObject
            if (!parentClasses.contains(parent_iter->second))
            {
                supertrait = "WxObject";
            }
        }
        else
        {
            supertrait = "WxObject";
        }

        out << "pub trait Wx" << traitName << ": " << supertrait << " {}\n";
        ++traitCount;
    }

    std::println(stderr, "  traits.rs:           {} traits", traitCount);
}

// -------------------------------------------------------------------------
// src/events.rs
// -------------------------------------------------------------------------

// One constant-like name emitted into events.rs / keys.rs / constants.rs.
struct ConstEmitEntry
{
    std::string rust_name;
    std::string export_name;
};

// Emit `pub const NAME: i32 = VALUE;` when a value is known, otherwise keep the
// `#[inline] pub fn NAME() -> i32` accessor wrapper.  Returns true when the const form
// was emitted.
static bool EmitConstOrFallback(std::ostream& out, const std::string& rust_name,
                                const std::string& export_name, bool has_value, long long value)
{
    if (has_value)
    {
        // std::to_string never adds locale grouping, unlike integer stream insertion.
        out << "pub const " << rust_name << ": i32 = " << std::to_string(value) << ";\n\n";
        return true;
    }
    out << "#[inline]\n";
    out << "pub fn " << rust_name << "() -> i32 {\n";
    out << "    unsafe { sys::" << export_name << "() as i32 }\n";
    out << "}\n\n";
    return false;
}

// Emit a test module asserting every emitted const matches the FFI accessor, so a stale
// --constants-values dump fails the build instead of silently assigning wrong values.
static void WriteDriftTests(std::ostream& out, const std::vector<ConstEmitEntry>& const_entries)
{
    if (const_entries.empty())
    {
        return;
    }

    out << "#[cfg(test)]\n";
    out << "mod drift {\n";
    out << "    use super::*;\n";
    out << "    use crate::sys;\n\n";
    out << "    #[test]\n";
    out << "    fn matches_ffi() {\n";
    for (const auto& entry: const_entries)
    {
        out << "        assert_eq!(" << entry.rust_name << ", unsafe { sys::" << entry.export_name
            << "() } as i32);\n";
    }
    out << "    }\n";
    out << "}\n";
}

void RustEmitter::GenerateEvents(const ParsedFFI& ffi, const fs::path& srcDir)
{
    const fs::path path = srcDir / "events.rs";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(out);
    out << "use crate::sys;\n\n";

    std::vector<EventDecl> sorted = ffi.events;
    std::ranges::sort(sorted, {}, &EventDecl::event_name);

    std::vector<ConstEmitEntry> const_entries;
    size_t const_count = 0;
    size_t fallback_count = 0;
    std::string lastEvtName;
    for (const auto& event: sorted)
    {
        if (event.event_name == lastEvtName)
        {
            continue;
        }
        lastEvtName = event.event_name;

        const std::unordered_map<std::string, long long>::const_iterator value_iter =
            ffi.constant_values.find(event.event_name);
        const bool has_value = value_iter != ffi.constant_values.end();
        if (EmitConstOrFallback(out, event.event_name, event.export_name, has_value,
                                has_value ? value_iter->second : 0))
        {
            ++const_count;
            const_entries.push_back({ event.event_name, event.export_name });
        }
        else
        {
            ++fallback_count;
        }
    }

    WriteDriftTests(out, const_entries);

    std::println(stderr, "  events.rs:           {} events ({} consts, {} fallbacks)",
                 ffi.events.size(), const_count, fallback_count);
}

// -------------------------------------------------------------------------
// src/keys.rs
// -------------------------------------------------------------------------

void RustEmitter::GenerateKeys(const ParsedFFI& ffi, const fs::path& srcDir)
{
    const fs::path path = srcDir / "keys.rs";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(out);
    out << "use crate::sys;\n\n";

    std::vector<KeyDecl> sorted = ffi.keys;
    std::ranges::sort(sorted, {}, &KeyDecl::key_name);

    std::vector<ConstEmitEntry> const_entries;
    std::set<std::string> emitted_names;
    size_t const_count = 0;
    size_t fallback_count = 0;
    for (const auto& k: sorted)
    {
        if (!emitted_names.insert(k.key_name).second)
        {
            continue;
        }

        const std::unordered_map<std::string, long long>::const_iterator value_iter =
            ffi.constant_values.find(k.key_name);
        const bool has_value = value_iter != ffi.constant_values.end();
        if (EmitConstOrFallback(out, k.key_name, k.export_name, has_value,
                                has_value ? value_iter->second : 0))
        {
            ++const_count;
            const_entries.push_back({ k.key_name, k.export_name });
        }
        else
        {
            ++fallback_count;
        }
    }

    WriteDriftTests(out, const_entries);

    std::println(stderr, "  keys.rs:             {} keys ({} consts, {} fallbacks)",
                 ffi.keys.size(), const_count, fallback_count);
}

// -------------------------------------------------------------------------
// src/constants.rs
// -------------------------------------------------------------------------

void RustEmitter::GenerateConstants(const ParsedFFI& ffi, const fs::path& srcDir)
{
    const fs::path path = srcDir / "constants.rs";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(out);
    out << "use std::os::raw::c_void;\n\n";
    out << "use crate::sys;\n\n";

    std::vector<ConstantDecl> sorted = ffi.constants;
    std::ranges::sort(sorted, {}, &ConstantDecl::export_name);

    std::vector<ConstEmitEntry> const_entries;
    std::set<std::string> emitted_names;
    size_t const_count = 0;
    size_t fallback_count = 0;
    for (const auto& cnst: sorted)
    {
        if (!emitted_names.insert(cnst.constant_name).second)
        {
            continue;
        }

        const bool isPointer = cnst.return_type.contains('*');
        const std::unordered_map<std::string, long long>::const_iterator value_iter =
            ffi.constant_values.find(cnst.constant_name);
        // Pointer-valued constants are exported directly and never appear in the integer
        // dump, so they always keep the accessor wrapper.
        const bool has_value = !isPointer && value_iter != ffi.constant_values.end();
        if (has_value)
        {
            out << "pub const " << cnst.constant_name
                << ": i32 = " << std::to_string(value_iter->second) << ";\n\n";
            ++const_count;
            const_entries.push_back({ cnst.constant_name, cnst.export_name });
            continue;
        }

        const std::string retType = isPointer ? "*mut c_void" : "i32";
        const std::string cast = isPointer ? "" : " as i32";

        out << "#[inline]\n";
        out << "pub fn " << cnst.constant_name << "() -> " << retType << " {\n";
        out << "    unsafe { sys::" << cnst.export_name << "()" << cast << " }\n";
        out << "}\n\n";
        ++fallback_count;
    }

    WriteDriftTests(out, const_entries);

    std::println(stderr, "  constants.rs:        {} constants ({} consts, {} fallbacks)",
                 ffi.constants.size(), const_count, fallback_count);
}

// -------------------------------------------------------------------------
// src/freefuncs.rs
// -------------------------------------------------------------------------

void RustEmitter::GenerateFreeFunctions(const ParsedFFI& ffi, const fs::path& srcDir)
{
    if (ffi.free_functions.empty())
    {
        return;
    }

    const fs::path path = srcDir / "freefuncs.rs";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(out);
    out << "#![allow(non_snake_case)]\n\n";
    out << "use std::os::raw::*;\n\n";

    std::ostringstream body;
    std::set<std::string> supportImports;
    std::set<std::string> classImports;
    const std::set<std::string> parentClasses = BuildParentClassSet(ffi);
    const std::string noName;
    const RustConvertContext context { ffi, parentClasses, noName, supportImports };
    const RustReturnContext returnContext { ffi,    noName,       noName,
                                            noName, classImports, supportImports };

    size_t count = 0;
    for (const auto& func: ffi.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }

        const std::string funcName = CFuncName(func);
        const SafeReturn ret = ClassifyMethodReturn(func, returnContext);

        // Collect safe params
        std::vector<RustSafeParam> params;
        for (const auto& param: func.params)
        {
            std::vector<RustSafeParam> expanded = ConvertParamToSafe(param, context);
            for (auto& safe_param: expanded)
            {
                params.push_back(std::move(safe_param));
            }
        }

        // Function signature
        body << "#[inline]\n";
        body << "pub fn " << funcName << "(";
        for (size_t i = 0; i < params.size(); ++i)
        {
            if (i > 0)
            {
                body << ", ";
            }
            body << params[i].name << ": " << params[i].safe_type;
        }
        body << ")";
        if (!ret.type.empty())
        {
            body << " -> " << ret.type;
        }
        body << " {\n";

        for (const auto& safe_param: params)
        {
            if (!safe_param.setup.empty())
            {
                body << "    " << safe_param.setup << "\n";
            }
        }

        // Build FFI call
        std::string call = "sys::" + funcName + "(";
        for (size_t i = 0; i < params.size(); ++i)
        {
            if (i > 0)
            {
                call += ", ";
            }
            call += params[i].ffi_expr;
        }
        call += ")";

        if (ret.kind == SafeReturn::Kind::none)
        {
            body << "    unsafe { " << call << " }\n";
        }
        else if (ret.kind == SafeReturn::Kind::string)
        {
            body << "    take_string(unsafe { " << call << " })\n";
        }
        else if (ret.kind == SafeReturn::Kind::class_ptr)
        {
            body << "    let ptr = unsafe { " << call << " };\n";
            body << "    if ptr.is_null() {\n";
            body << "        None\n";
            body << "    } else {\n";
            body << "        Some(" << ret.class_type << "::from_raw(ptr))\n";
            body << "    }\n";
        }
        else
        {
            body << "    unsafe { " << WrapReturnExpr(func, call) << " }\n";
        }

        body << "}\n\n";
        ++count;
    }

    out << "use crate::sys;\n";
    out << "use crate::traits::*;\n";
    for (const std::string& name: supportImports)
    {
        out << "use crate::support::" << name << ";\n";
    }
    for (const std::string& line: classImports)
    {
        out << line << "\n";
    }
    out << "\n" << body.str();

    std::println(stderr, "  freefuncs.rs:        {} free functions", count);
}

// -------------------------------------------------------------------------
// Per-class safe wrapper files
// -------------------------------------------------------------------------

// True when the class does not derive from another generated wrapper; such a class wraps
// the root Object handle directly.
[[nodiscard]] static bool WrapsObject(const ClassInfo& cls)
{
    return cls.parent.empty() || cls.parent == "wxObject";
}

// Report a fatal generation problem and stop. A Deref target that has no generated type
// would fail the whole generated crate at compile time, so generation must not continue.
[[noreturn]] static void AbortGeneration(const std::string& message)
{
    std::println(stderr, "Error: {}", message);
    std::exit(EXIT_FAILURE);
}

// Add a class to the module-keyed emit map. Classes that would share a Rust module name
// (the kwx* wrappers duplicate their wx* counterparts) are merged into a single type; the
// wx* declaration wins because it carries the real parent and the full method set.
static void AddClassToEmitGroups(std::map<std::string, ClassInfo>& groups, ClassInfo cls)
{
    const std::string moduleName = RustModuleName(cls.name);
    const std::map<std::string, ClassInfo>::iterator groupIter = groups.find(moduleName);
    if (groupIter == groups.end())
    {
        groups.emplace(moduleName, std::move(cls));
        return;
    }

    ClassInfo& existing = groupIter->second;
    if (existing.name.starts_with(KWX_PREFIX) && !cls.name.starts_with(KWX_PREFIX))
    {
        cls.methods.insert(cls.methods.end(), existing.methods.begin(), existing.methods.end());
        existing = std::move(cls);
        return;
    }

    existing.methods.insert(existing.methods.end(), cls.methods.begin(), cls.methods.end());
}

// Build the complete list of classes to emit, sorted by module name. Every parent that a
// generated type dereferences to is itself part of the list.
[[nodiscard]] static std::vector<ClassInfo> BuildEmitClasses(const ParsedFFI& ffi)
{
    std::map<std::string, ClassInfo> groups;

    for (const ClassInfo& classInfo: ffi.classes)
    {
        // wxObject is the root handle emitted by object.rs, including its methods.
        if (classInfo.name == "wxObject")
        {
            continue;
        }
        AddClassToEmitGroups(groups, classInfo);
    }

    // Classes that only appear in the parent map still need a generated type.
    for (const auto& [child, parent]: ffi.parent_map)
    {
        if (child == "wxObject" || groups.contains(RustModuleName(child)))
        {
            continue;
        }
        ClassInfo classInfo;
        classInfo.name = child;
        classInfo.parent = parent;
        AddClassToEmitGroups(groups, std::move(classInfo));
    }

    // Headers do not declare every parent class (for example wxAccessibleBase), so
    // synthesize a root-derived wrapper for each parent that has no declaration.
    bool added = true;
    while (added)
    {
        added = false;
        std::vector<std::string> missingParents;
        for (const auto& group: groups)
        {
            const ClassInfo& classInfo = group.second;
            if (WrapsObject(classInfo) || groups.contains(RustModuleName(classInfo.parent)))
            {
                continue;
            }
            missingParents.push_back(classInfo.parent);
        }

        for (const std::string& parentName: missingParents)
        {
            if (parentName == "wxObject" || groups.contains(RustModuleName(parentName)))
            {
                continue;
            }
            ClassInfo classInfo;
            classInfo.name = parentName;
            const std::unordered_map<std::string, std::string>::const_iterator parentIter =
                ffi.parent_map.find(parentName);
            if (parentIter != ffi.parent_map.end())
            {
                classInfo.parent = parentIter->second;
            }
            AddClassToEmitGroups(groups, std::move(classInfo));
            added = true;
        }
    }

    // Every Deref target must resolve to a generated type.
    for (const auto& group: groups)
    {
        const ClassInfo& classInfo = group.second;
        if (WrapsObject(classInfo) || groups.contains(RustModuleName(classInfo.parent)))
        {
            continue;
        }
        AbortGeneration("class '" + classInfo.name + "' has parent '" + classInfo.parent +
                        "' with no generated type");
    }

    std::vector<ClassInfo> classes;
    classes.reserve(groups.size());
    for (const auto& group: groups)
    {
        classes.push_back(group.second);
    }
    return classes;
}

// Emit the wrapper methods for a class inside an impl block. Destructor methods are never
// wrapped: handles are non-owning Copy values, so there is no Drop and no delete().
static void EmitMethodWrappers(std::ostream& out, const ClassInfo& cls, const std::string& rustName,
                               const ParsedFFI& ffi, const std::string& parentType)
{
    std::ostringstream body;
    size_t methodCount = 0;
    std::set<std::string> emittedMethods;
    std::set<std::string> supportImports;
    std::set<std::string> classImports;

    const std::set<std::string> parentClasses = BuildParentClassSet(ffi);
    const std::string currentModule = RustModuleName(cls.name);
    const RustConvertContext context { ffi, parentClasses, rustName, supportImports };
    const RustReturnContext returnContext { ffi,        rustName,     currentModule,
                                            parentType, classImports, supportImports };

    for (const auto& method: cls.methods)
    {
        if (!IsValidFunction(method))
        {
            continue;
        }

        if (IsDestructor(method))
        {
            continue;
        }

        // Collect safe params (excluding the first TSelf which becomes &self)
        std::vector<RustSafeParam> params;
        bool selfSkipped = false;
        for (const auto& param: method.params)
        {
            if (!selfSkipped && param.macro_name == "TSelf")
            {
                selfSkipped = true;
                continue;
            }
            std::vector<RustSafeParam> expanded = ConvertParamToSafe(param, context);
            for (auto& safeParam: expanded)
            {
                params.push_back(std::move(safeParam));
            }
        }

        const std::string cFuncName = CFuncName(method);

        if (method.is_constructor && !method.has_self)
        {
            // Only treat as constructor if the return type is a pointer.
            const bool isPointerReturn = method.return_type.contains('*') ||
                                         method.return_macro == "TClass" ||
                                         method.return_macro == "TSelf";
            if (!isPointerReturn)
            {
                continue;  // Skip non-pointer constructors (e.g., returns int)
            }

            if (method.method_name != "Create")
            {
                // Named factory (for example wxString_CreateUTF8).
                const std::string factoryName = RustWrapperMethodName(method);
                if (!emittedMethods.insert(factoryName).second)
                {
                    continue;
                }

                body << "    pub fn " << factoryName << "(";
                bool firstFactoryParam = true;
                for (const auto& safeParam: params)
                {
                    if (!firstFactoryParam)
                    {
                        body << ", ";
                    }
                    body << safeParam.name << ": " << safeParam.safe_type;
                    firstFactoryParam = false;
                }
                body << ") -> Self {\n";
                for (const auto& safeParam: params)
                {
                    if (!safeParam.setup.empty())
                    {
                        body << "        " << safeParam.setup << "\n";
                    }
                }
                body << "        let ptr = unsafe { sys::" << cFuncName << "(";
                bool firstFactoryArg = true;
                for (const auto& safeParam: params)
                {
                    if (!firstFactoryArg)
                    {
                        body << ", ";
                    }
                    body << safeParam.ffi_expr;
                    firstFactoryArg = false;
                }
                body << ") };\n";
                body << "        assert!(!ptr.is_null(), \"" << cFuncName << " returned null\");\n";
                body << "        Self::from_raw(ptr)\n";
                body << "    }\n\n";
            }
            else
            {
                if (!emittedMethods.insert("new").second)
                {
                    continue;  // One short and one full constructor per class
                }
                emittedMethods.insert("new_full");

                // `new` drops the parameters that have a sensible default.
                body << "    pub fn new(";
                bool firstUserParam = true;
                for (const auto& safeParam: params)
                {
                    if (safeParam.new_excluded)
                    {
                        continue;
                    }
                    if (!firstUserParam)
                    {
                        body << ", ";
                    }
                    body << safeParam.name << ": " << safeParam.safe_type;
                    firstUserParam = false;
                }
                body << ") -> Self {\n";
                for (const auto& safeParam: params)
                {
                    if (!safeParam.new_excluded && !safeParam.setup.empty())
                    {
                        body << "        " << safeParam.setup << "\n";
                    }
                }
                body << "        let ptr = unsafe { sys::" << cFuncName << "(";
                bool firstArg = true;
                for (const auto& safeParam: params)
                {
                    if (!firstArg)
                    {
                        body << ", ";
                    }
                    body << (safeParam.new_excluded ? safeParam.new_default : safeParam.ffi_expr);
                    firstArg = false;
                }
                body << ") };\n";
                body << "        assert!(!ptr.is_null(), \"" << cFuncName << " returned null\");\n";
                body << "        Self::from_raw(ptr)\n";
                body << "    }\n\n";

                // `new_full` exposes every constructor parameter.
                body << "    pub fn new_full(";
                bool firstFullParam = true;
                for (const auto& safeParam: params)
                {
                    if (!firstFullParam)
                    {
                        body << ", ";
                    }
                    body << safeParam.name << ": " << safeParam.safe_type;
                    firstFullParam = false;
                }
                body << ") -> Self {\n";
                for (const auto& safeParam: params)
                {
                    if (!safeParam.setup.empty())
                    {
                        body << "        " << safeParam.setup << "\n";
                    }
                }
                body << "        let ptr = unsafe { sys::" << cFuncName << "(";
                bool firstFullArg = true;
                for (const auto& safeParam: params)
                {
                    if (!firstFullArg)
                    {
                        body << ", ";
                    }
                    body << safeParam.ffi_expr;
                    firstFullArg = false;
                }
                body << ") };\n";
                body << "        assert!(!ptr.is_null(), \"" << cFuncName << " returned null\");\n";
                body << "        Self::from_raw(ptr)\n";
                body << "    }\n\n";
            }
        }
        else
        {
            // Regular method: pub fn method_name(&self, ...) -> RetType
            const std::string methodName = RustWrapperMethodName(method);

            if (!emittedMethods.insert(methodName).second)
            {
                continue;  // Skip duplicate method name
            }

            const SafeReturn ret = ClassifyMethodReturn(method, returnContext);

            body << "    pub fn " << methodName << "(&self";
            for (const auto& safeParam: params)
            {
                body << ", " << safeParam.name << ": " << safeParam.safe_type;
            }
            body << ")";
            if (!ret.type.empty())
            {
                body << " -> " << ret.type;
            }
            body << " {\n";

            for (const auto& safeParam: params)
            {
                if (!safeParam.setup.empty())
                {
                    body << "        " << safeParam.setup << "\n";
                }
            }

            // Build FFI call
            std::string call = "sys::" + cFuncName + "(";
            bool first = true;
            if (method.has_self)
            {
                call += "self.as_ptr()";
                first = false;
            }
            for (const auto& safeParam: params)
            {
                if (!first)
                {
                    call += ", ";
                }
                call += safeParam.ffi_expr;
                first = false;
            }
            call += ")";

            if (ret.kind == SafeReturn::Kind::none)
            {
                body << "        unsafe { " << call << " }\n";
            }
            else if (ret.kind == SafeReturn::Kind::string)
            {
                body << "        take_string(unsafe { " << call << " })\n";
            }
            else if (ret.kind == SafeReturn::Kind::class_ptr)
            {
                body << "        let ptr = unsafe { " << call << " };\n";
                body << "        if ptr.is_null() {\n";
                body << "            None\n";
                body << "        } else {\n";
                body << "            Some(" << ret.class_type << "::from_raw(ptr))\n";
                body << "        }\n";
            }
            else
            {
                body << "        unsafe { " << WrapReturnExpr(method, call) << " }\n";
            }

            body << "    }\n\n";
        }
        ++methodCount;
    }

    if (methodCount == 0)
    {
        return;
    }

    std::set<std::string> importLines;
    for (const std::string& name: supportImports)
    {
        importLines.insert("use crate::support::" + name + ";");
    }
    for (const std::string& line: classImports)
    {
        importLines.insert(line);
    }
    for (const std::string& line: importLines)
    {
        out << line << "\n";
    }
    if (!importLines.empty())
    {
        out << "\n";
    }

    out << "impl " << rustName << " {\n" << body.str() << "}\n\n";
}

void RustEmitter::GenerateClassFiles(const ParsedFFI& ffi, const fs::path& srcDir,
                                     std::vector<std::string>& classModules)
{
    const std::vector<ClassInfo> classes = BuildEmitClasses(ffi);
    size_t fileCount = 0;

    for (const auto& cls: classes)
    {
        const std::string moduleName = RustModuleName(cls.name);
        const fs::path path = srcDir / (moduleName + ".rs");
        ConditionalFileWriter out(path);
        if (!out.is_open())
        {
            std::println(stderr, "Error: cannot create {}", path.string());
            continue;
        }

        EmitClassFile(out, cls, ffi);
        // Record the module in the same pass that writes the file so lib.rs can never
        // declare a module the generator did not write, or miss one it did.
        classModules.push_back(moduleName);
        ++fileCount;
    }

    std::println(stderr, "  class files:         {} files", fileCount);
}

void RustEmitter::EmitClassFile(std::ostream& out, const ClassInfo& cls, const ParsedFFI& ffi)
{
    WriteGeneratedHeader(out);
    out << "#![allow(non_snake_case)]\n\n";
    out << "use std::os::raw::*;\n\n";

    const std::string rustName = StripPrefix(cls.name);
    const bool wrapsObject = WrapsObject(cls);
    const std::string parentType = wrapsObject ? "Object" : StripPrefix(cls.parent);
    const std::string parentModule = wrapsObject ? "object" : RustModuleName(cls.parent);

    out << "use crate::" << parentModule << "::" << parentType << ";\n";
    out << "use crate::sys;\n";
    out << "use crate::traits::*;\n\n";

    // Type-safe handle: a parent-chained newtype so inherited methods resolve through
    // Deref without duplicating wrappers.
    out << "#[derive(Copy, Clone)]\n";
    out << "pub struct " << rustName << "(pub(crate) " << parentType << ");\n\n";

    out << "impl " << rustName << " {\n";
    out << "    pub(crate) const fn from_raw(ptr: *mut c_void) -> Self {\n";
    out << "        Self(" << parentType << "::from_raw(ptr))\n";
    out << "    }\n\n";
    out << "    pub fn as_ptr(&self) -> *mut c_void {\n";
    out << "        self.0.as_ptr()\n";
    out << "    }\n";
    out << "}\n\n";

    out << "impl std::ops::Deref for " << rustName << " {\n";
    out << "    type Target = " << parentType << ";\n\n";
    out << "    fn deref(&self) -> &" << parentType << " {\n";
    out << "        &self.0\n";
    out << "    }\n";
    out << "}\n\n";

    out << "impl WxObject for " << rustName << " {\n";
    out << "    fn as_ptr(&self) -> *mut c_void {\n";
    out << "        self.0.as_ptr()\n";
    out << "    }\n";
    out << "}\n\n";

    // Trait implementations for parent chain
    {
        // Build the full trait chain: immediate parent up to the root.
        const std::vector<std::string> chain = BuildTraitChain(cls, ffi);

        // Collect the set of classes that are used as parents (and thus have traits).
        std::set<std::string> parentClasses;
        for (const auto& [child, parent]: ffi.parent_map)
        {
            parentClasses.insert(parent);
        }
        for (const auto& cls_info: ffi.classes)
        {
            if (!cls_info.parent.empty())
            {
                parentClasses.insert(cls_info.parent);
            }
        }

        for (const auto& parentName: chain)
        {
            const std::string traitName = "Wx" + StripPrefix(parentName);
            if (traitName == "WxObject")
            {
                continue;  // Already explicitly implemented above
            }
            if (parentClasses.contains(parentName))
            {
                out << "impl " << traitName << " for " << rustName << " {}\n";
            }
        }

        // If the class itself is used as a parent, it has a trait too.
        if (parentClasses.contains(cls.name))
        {
            out << "impl Wx" << rustName << " for " << rustName << " {}\n";
        }

        if (!chain.empty())
        {
            out << "\n";
        }
    }

    if (!cls.methods.empty())
    {
        EmitMethodWrappers(out, cls, rustName, ffi, parentType);
    }
}

// -------------------------------------------------------------------------
// src/support.rs — string and geometry helpers shared by every wrapper
// -------------------------------------------------------------------------

void RustEmitter::GenerateSupport(const fs::path& srcDir)
{
    const fs::path path = srcDir / "support.rs";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(out);
    out << "#![allow(non_snake_case)]\n\n";
    out << "use std::os::raw::*;\n\n";
    out << "use crate::sys;\n";
    out << "use crate::traits::*;\n\n";

    out << "/// Owned wxString used to pass a Rust string across the FFI boundary.\n";
    out << "/// The wxString is released when this value goes out of scope.\n";
    out << "pub struct WxStr(*mut c_void);\n\n";
    out << "impl WxStr {\n";
    out << "    pub fn new(value: &str) -> Self {\n";
    out << "        let bytes = value.as_bytes();\n";
    out << "        let ptr = unsafe {\n";
    out << "            sys::wxString_CreateLen(bytes.as_ptr() as *const c_char, bytes.len() as "
           "c_int)\n";
    out << "        };\n";
    out << "        Self(ptr)\n";
    out << "    }\n\n";
    out << "    pub fn as_ptr(&self) -> *mut c_void {\n";
    out << "        self.0\n";
    out << "    }\n";
    out << "}\n\n";
    out << "impl Drop for WxStr {\n";
    out << "    fn drop(&mut self) {\n";
    out << "        unsafe {\n";
    out << "            sys::wxString_Delete(self.0);\n";
    out << "        }\n";
    out << "    }\n";
    out << "}\n\n";

    out << "/// Copies a wxString returned by the FFI into a Rust String and releases it.\n";
    out << "pub fn take_string(ptr: *mut c_void) -> String {\n";
    out << "    if ptr.is_null() {\n";
    out << "        return String::new();\n";
    out << "    }\n";
    out << "    let len = unsafe { sys::wxString_GetString(ptr, std::ptr::null_mut()) };\n";
    out << "    if len <= 0 {\n";
    out << "        unsafe {\n";
    out << "            sys::wxString_Delete(ptr);\n";
    out << "        }\n";
    out << "        return String::new();\n";
    out << "    }\n";
    out << "    let mut buffer = vec![0u8; len as usize];\n";
    out << "    unsafe {\n";
    out << "        sys::wxString_GetString(ptr, buffer.as_mut_ptr() as *mut c_char);\n";
    out << "        sys::wxString_Delete(ptr);\n";
    out << "    }\n";
    out << "    String::from_utf8_lossy(&buffer).into_owned()\n";
    out << "}\n\n";

    out << "#[derive(Copy, Clone, Default)]\n";
    out << "pub struct Point {\n";
    out << "    pub x: i32,\n";
    out << "    pub y: i32,\n";
    out << "}\n\n";

    out << "#[derive(Copy, Clone, Default)]\n";
    out << "pub struct Size {\n";
    out << "    pub width: i32,\n";
    out << "    pub height: i32,\n";
    out << "}\n\n";

    out << "#[derive(Copy, Clone)]\n";
    out << "pub struct Rect {\n";
    out << "    pub x: i32,\n";
    out << "    pub y: i32,\n";
    out << "    pub width: i32,\n";
    out << "    pub height: i32,\n";
    out << "}\n\n";
    out << "impl Rect {\n";
    out << "    pub const fn new(x: i32, y: i32, width: i32, height: i32) -> Self {\n";
    out << "        Self { x, y, width, height }\n";
    out << "    }\n";
    out << "}\n\n";
    out << "impl Default for Rect {\n";
    out << "    fn default() -> Self {\n";
    out << "        Self {\n";
    out << "            x: -1,\n";
    out << "            y: -1,\n";
    out << "            width: -1,\n";
    out << "            height: -1,\n";
    out << "        }\n";
    out << "    }\n";
    out << "}\n\n";

    out << "/// Stands in for a missing parent window in top-level constructors.\n";
    out << "pub struct NoParent;\n\n";
    out << "impl WxObject for NoParent {\n";
    out << "    fn as_ptr(&self) -> *mut c_void {\n";
    out << "        std::ptr::null_mut()\n";
    out << "    }\n";
    out << "}\n\n";
    out << "impl WxEvtHandler for NoParent {}\n";
    out << "impl WxWindow for NoParent {}\n\n";
    out << "pub const NO_PARENT: NoParent = NoParent;\n";

    std::println(stderr, "  support.rs:          WxStr + take_string + Point/Size/Rect");
}

// -------------------------------------------------------------------------
// src/object.rs — root handle shared by every wrapper
// -------------------------------------------------------------------------

void RustEmitter::GenerateObject(const ParsedFFI& ffi, const fs::path& srcDir)
{
    const fs::path path = srcDir / "object.rs";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(out);
    out << "#![allow(non_snake_case)]\n\n";
    out << "use std::os::raw::*;\n\n";
    out << "use crate::sys;\n";
    out << "use crate::traits::*;\n\n";

    out << "/// Non-owning handle to a wxWidgets object.\n";
    out << "#[derive(Copy, Clone)]\n";
    out << "pub struct Object(*mut c_void);\n\n";

    out << "impl Object {\n";
    out << "    pub(crate) const fn from_raw(ptr: *mut c_void) -> Self {\n";
    out << "        Self(ptr)\n";
    out << "    }\n\n";
    out << "    pub fn as_ptr(&self) -> *mut c_void {\n";
    out << "        self.0\n";
    out << "    }\n\n";
    out << "    pub fn is_null(&self) -> bool {\n";
    out << "        self.0.is_null()\n";
    out << "    }\n";
    out << "}\n\n";

    out << "impl WxObject for Object {\n";
    out << "    fn as_ptr(&self) -> *mut c_void {\n";
    out << "        self.0\n";
    out << "    }\n";
    out << "}\n\n";

    // wxObject's own methods (GetClassInfo, IsKindOf, ...) live on the root handle.
    for (const ClassInfo& classInfo: ffi.classes)
    {
        if (classInfo.name != "wxObject")
        {
            continue;
        }
        EmitMethodWrappers(out, classInfo, "Object", ffi, {});
        break;
    }

    std::println(stderr, "  object.rs:           root handle");
}

// -------------------------------------------------------------------------
// src/lib.rs — Module root
// -------------------------------------------------------------------------

void RustEmitter::GenerateLib(const ParsedFFI& ffi, const fs::path& srcDir,
                              const std::vector<std::string>& classModules)
{
    const fs::path path = srcDir / "lib.rs";
    ConditionalFileWriter out(path);
    if (!out.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(out);
    out << "#![allow(non_snake_case, non_camel_case_types, unused_imports)]\n\n";

    // Core modules
    out << "pub mod sys;\n";
    out << "pub mod object;\n";
    out << "pub mod support;\n";
    out << "pub mod traits;\n";
    out << "pub mod events;\n";
    out << "pub mod keys;\n";
    out << "pub mod constants;\n";

    if (!ffi.free_functions.empty())
    {
        out << "pub mod freefuncs;\n";
    }

    out << "\n";

    // One module per class file written by GenerateClassFiles.
    for (const auto& moduleName: classModules)
    {
        out << "pub mod " << moduleName << ";\n";
    }

    std::println(stderr, "  lib.rs:              {} class modules", classModules.size());
}

// NOLINTEND(readability-magic-string)
