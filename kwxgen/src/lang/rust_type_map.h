#pragma once

// Rust type mapping: converts parsed FFI model types to Rust FFI type strings.
// Two layers:
//   1. FFI types for extern "C" declarations in sys.rs (*mut c_void, c_int, etc.)
//   2. Safe Rust types for wrapper structs (i32, bool, f64, etc.)

#include "../model.h"
#include "lang_common.h"

#include <sstream>
#include <string>
#include <vector>

// A single Rust-typed parameter for FFI declarations (sys.rs).
struct RustFFIParam
{
    std::string rust_type;  // "c_int", "*mut c_void", "c_double", etc.
    std::string name;       // parameter name (Rust-safe, keywords escaped)
};

// Rust keywords that must be escaped with trailing underscore in parameter names.
inline std::string RustEscapeName(const std::string& name)
{
    // Rust strict and reserved keywords that could appear as C parameter names
    if (name == "self" || name == "Self" || name == "type" || name == "in" || name == "ref" ||
        name == "fn" || name == "mod" || name == "use" || name == "mut" || name == "pub" ||
        name == "let" || name == "match" || name == "move" || name == "loop" || name == "super" ||
        name == "crate" || name == "where" || name == "impl" || name == "trait" ||
        name == "async" || name == "await" || name == "dyn" || name == "box" || name == "yield" ||
        name == "macro" || name == "return" || name == "break" || name == "continue" ||
        name == "static" || name == "const" || name == "extern" || name == "struct" ||
        name == "enum" || name == "union" || name == "unsafe" || name == "as" || name == "if" ||
        name == "else" || name == "for" || name == "while" || name == "true" || name == "false")
    {
        return name + "_";
    }
    return name;
}

// Convert a return type to its Rust FFI equivalent (for extern "C" declarations).
inline std::string RustFFIReturnType(const std::string& return_type,
                                     const std::string& return_macro)
{
    if (return_type == "void" || return_type.empty())
    {
        return "";  // No return type annotation needed
    }
    if (return_macro == "TClass" || return_macro == "TSelf" || return_macro == "TClassRef")
    {
        return "*mut c_void";
    }
    if (return_type == "TBool" || return_type == "TBoolInt")
    {
        return "c_int";
    }
    if (return_type == "TString" || return_type == "TStringOut" || return_type == "TStringVoid")
    {
        return "*mut c_void";
    }
    if (return_type == "int" || return_type == "TArrayLen" || return_type == "TByteStringLen")
    {
        return "c_int";
    }
    if (return_type == "long" || return_type == "time_t")
    {
        return "c_long";
    }
    if (return_type == "unsigned" || return_type == "unsigned int")
    {
        return "c_uint";
    }
    if (return_type == "unsigned long" || return_type == "wxUIntPtr")
    {
        return "c_ulong";
    }
    if (return_type == "uintptr_t")
    {
        return "usize";
    }
    if (return_type == "double")
    {
        return "c_double";
    }
    if (return_type == "float")
    {
        return "c_float";
    }
    if (return_type == "size_t")
    {
        return "usize";
    }
    if (return_type == "TChar")
    {
        return "c_char";
    }
    if (return_type == "TUInt8")
    {
        return "u8";
    }
    if (return_type == "void*")
    {
        return "*mut c_void";
    }

    // Any pointer type → *mut c_void
    if (return_type.find('*') != std::string::npos)
    {
        return "*mut c_void";
    }

    // Fallback
    return "c_int";
}

// FFI type for the pointee behind a scalar-pointer macro.
[[nodiscard]] inline std::string RustScalarPointerFfiType(const std::string& c_type)
{
    if (c_type == "long")
    {
        return "*mut c_long";
    }
    if (c_type == "unsigned long")
    {
        return "*mut c_ulong";
    }
    if (c_type == "double")
    {
        return "*mut c_double";
    }
    if (c_type == "unsigned")
    {
        return "*mut c_uint";
    }
    return "*mut c_int";
}

// Safe wrapper type for the same parameter; the call site casts it to the FFI pointee.
[[nodiscard]] inline std::string RustScalarPointerSafeType(const std::string& c_type)
{
    if (c_type == "long")
    {
        return "*mut i64";
    }
    if (c_type == "unsigned long")
    {
        return "*mut u64";
    }
    if (c_type == "double")
    {
        return "*mut f64";
    }
    if (c_type == "unsigned")
    {
        return "*mut u32";
    }
    return "*mut i32";
}

// Split comma-separated macro arg: "x, y" → {"x", "y"}
inline std::vector<std::string> RustSplitMacroArg(const std::string& arg)
{
    std::vector<std::string> parts;
    std::istringstream stream(arg);
    std::string part;
    while (std::getline(stream, part, ','))
    {
        const std::size_t start = part.find_first_not_of(" \t");
        const std::size_t end = part.find_last_not_of(" \t");
        if (start != std::string::npos)
        {
            parts.push_back(part.substr(start, end - start + 1));
        }
    }
    return parts;
}

// Expand a Param to one or more Rust FFI parameters (for extern "C" declarations).
inline std::vector<RustFFIParam> ExpandParamToRustFFI(const Param& param)
{
    std::vector<RustFFIParam> result;

    // Expanded geometry types: TPoint, TSize, TRect, TVector → individual c_int params
    if (param.macro_name == "TPoint" || param.macro_name == "TSize" ||
        param.macro_name == "TRect" || param.macro_name == "TVector")
    {
        for (auto& n: RustSplitMacroArg(param.macro_arg))
        {
            result.push_back({ "c_int", RustEscapeName(n) });
        }
        return result;
    }

    if (param.macro_name == "TPointLong" || param.macro_name == "TSizeLong" ||
        param.macro_name == "TRectLong" || param.macro_name == "TVectorLong")
    {
        for (auto& n: RustSplitMacroArg(param.macro_arg))
        {
            result.push_back({ "c_long", RustEscapeName(n) });
        }
        return result;
    }

    // Output geometry parameters → *mut c_int pointers
    if (param.macro_name == "TPointOut" || param.macro_name == "TSizeOut" ||
        param.macro_name == "TRectOut" || param.macro_name == "TVectorOut")
    {
        for (auto& n: RustSplitMacroArg(param.macro_arg))
        {
            result.push_back({ "*mut c_int", RustEscapeName(n) });
        }
        return result;
    }

    // Output long geometry parameters → *mut c_long pointers
    if (param.macro_name == "TPointOutLong" || param.macro_name == "TSizeOutLong")
    {
        for (auto& n: RustSplitMacroArg(param.macro_arg))
        {
            result.push_back({ "*mut c_long", RustEscapeName(n) });
        }
        return result;
    }

    // Output geometry void pointers
    if (param.macro_name == "TPointOutVoid" || param.macro_name == "TSizeOutVoid" ||
        param.macro_name == "TRectOutVoid" || param.macro_name == "TVectorOutVoid")
    {
        for (auto& n: RustSplitMacroArg(param.macro_arg))
        {
            result.push_back({ "*mut c_void", RustEscapeName(n) });
        }
        return result;
    }

    if (param.macro_name == "TSizeOutDouble")
    {
        for (auto& n: RustSplitMacroArg(param.macro_arg))
        {
            result.push_back({ "*mut c_double", RustEscapeName(n) });
        }
        return result;
    }

    if (param.macro_name == "TColorRGB")
    {
        for (auto& n: RustSplitMacroArg(param.macro_arg))
        {
            result.push_back({ "u8", RustEscapeName(n) });
        }
        return result;
    }

    // Array types: expand to count + pointer
    if (param.macro_name == "TArrayString" || param.macro_name == "TArrayInt" ||
        param.macro_name == "TByteString" || param.macro_name == "TByteStringLazy")
    {
        const std::vector<std::string> names = RustSplitMacroArg(param.macro_arg);
        if (names.size() >= 2)
        {
            result.push_back({ "c_int", RustEscapeName(names[0]) });
            result.push_back({ "*mut c_void", RustEscapeName(names[1]) });
        }
        return result;
    }

    if (param.macro_name == "TArrayObjectOutVoid")
    {
        const std::string name = param.param_name.empty() ? "arr" : param.param_name;
        result.push_back({ "*mut c_void", RustEscapeName(name) });
        return result;
    }

    if (IsTypedPointerMacro(param.raw_type))
    {
        result.push_back(
            { "*mut c_void", RustEscapeName(param.param_name.empty() ? "arg" : param.param_name) });
        return result;
    }

    // Scalar value passed through a pointer.
    if (ScalarPointerInfo scalar_pointer; LookupScalarPointer(param, scalar_pointer))
    {
        result.push_back({ RustScalarPointerFfiType(scalar_pointer.c_type),
                           RustEscapeName(param.param_name.empty() ? "arg" : param.param_name) });
        return result;
    }

    // Single-valued macro types
    if (param.macro_name == "TClass" || param.macro_name == "TSelf" ||
        param.macro_name == "TClassRef")
    {
        result.push_back(
            { "*mut c_void", RustEscapeName(param.param_name.empty() ? "arg" : param.param_name) });
        return result;
    }

    if (param.macro_name == "TBool" || param.raw_type == "TBool")
    {
        result.push_back(
            { "c_int", RustEscapeName(param.param_name.empty() ? "arg" : param.param_name) });
        return result;
    }

    if (param.raw_type == "TBoolInt" || param.raw_type == "TBool*")
    {
        result.push_back(
            { "c_int", RustEscapeName(param.param_name.empty() ? "arg" : param.param_name) });
        return result;
    }

    if (param.macro_name == "TClosureFun" || param.raw_type == "TClosureFun")
    {
        result.push_back(
            { "*mut c_void", RustEscapeName(param.param_name.empty() ? "fn_" : param.param_name) });
        return result;
    }

    if (param.raw_type == "TStringVoid" || param.macro_name == "TStringVoid")
    {
        result.push_back({ "*mut c_void",
                           RustEscapeName(param.param_name.empty() ? "str_" : param.param_name) });
        return result;
    }

    if (param.raw_type == "TArrayIntOutVoid" || param.raw_type == "TArrayIntPtrOutVoid" ||
        param.raw_type == "TArrayStringOutVoid" || param.raw_type == "TByteStringOut" ||
        param.raw_type == "TByteStringLazyOut" || param.raw_type == "TArrayObjectOutVoid")
    {
        result.push_back(
            { "*mut c_void", RustEscapeName(param.param_name.empty() ? "arr" : param.param_name) });
        return result;
    }

    if (param.raw_type == "TChar")
    {
        result.push_back(
            { "c_char", RustEscapeName(param.param_name.empty() ? "ch" : param.param_name) });
        return result;
    }

    if (param.raw_type == "TUInt8")
    {
        result.push_back(
            { "u8", RustEscapeName(param.param_name.empty() ? "val" : param.param_name) });
        return result;
    }

    // String types: TString = char* input, TStringOut = char* output buffer
    if (param.raw_type == "TString")
    {
        result.push_back({ "*const c_char",
                           RustEscapeName(param.param_name.empty() ? "str_" : param.param_name) });
        return result;
    }
    if (param.raw_type == "TStringOut")
    {
        result.push_back(
            { "*mut c_char", RustEscapeName(param.param_name.empty() ? "buf" : param.param_name) });
        return result;
    }
    // Plain C types
    const std::string name = RustEscapeName(param.param_name.empty() ? "arg" : param.param_name);
    const std::string raw_type = param.raw_type;

    if (raw_type.empty() || raw_type == "int")
    {
        result.push_back({ "c_int", name });
    }
    else if (raw_type == "long")
    {
        result.push_back({ "c_long", name });
    }
    else if (raw_type == "unsigned" || raw_type == "unsigned int")
    {
        result.push_back({ "c_uint", name });
    }
    else if (raw_type == "unsigned long" || raw_type == "wxUIntPtr")
    {
        result.push_back({ "c_ulong", name });
    }
    else if (raw_type == "uintptr_t")
    {
        result.push_back({ "usize", name });
    }
    else if (raw_type == "double")
    {
        result.push_back({ "c_double", name });
    }
    else if (raw_type == "float")
    {
        result.push_back({ "c_float", name });
    }
    else if (raw_type == "size_t")
    {
        result.push_back({ "usize", name });
    }
    else if (raw_type.find('*') != std::string::npos)
    {
        result.push_back({ "*mut c_void", name });
    }
    else
    {
        result.push_back({ "c_int", name });  // fallback
    }

    return result;
}
