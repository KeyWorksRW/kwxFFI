#pragma once

// Rust type mapping: converts parsed FFI model types to Rust FFI type strings.
// Two layers:
//   1. FFI types for extern "C" declarations in sys.rs (*mut c_void, c_int, etc.)
//   2. Safe Rust types for wrapper structs (i32, bool, f64, etc.)

#include "../model.h"

#include <sstream>
#include <string>
#include <vector>

namespace kwxgen
{

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
            name == "let" || name == "match" || name == "move" || name == "loop" ||
            name == "super" || name == "crate" || name == "where" || name == "impl" ||
            name == "trait" || name == "async" || name == "await" || name == "dyn" ||
            name == "box" || name == "yield" || name == "macro" || name == "return" ||
            name == "break" || name == "continue" || name == "static" || name == "const" ||
            name == "extern" || name == "struct" || name == "enum" || name == "union" ||
            name == "unsafe" || name == "as" || name == "if" || name == "else" || name == "for" ||
            name == "while" || name == "true" || name == "false")
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
            return "";  // No return type annotation needed
        if (return_macro == "TClass" || return_macro == "TSelf" || return_macro == "TClassRef")
            return "*mut c_void";
        if (return_type == "TBool" || return_type == "TBoolInt")
            return "c_int";
        if (return_type == "TString" || return_type == "TStringOut" || return_type == "TStringVoid")
            return "*mut c_void";
        if (return_type == "int" || return_type == "TArrayLen" || return_type == "TByteStringLen")
            return "c_int";
        if (return_type == "long" || return_type == "time_t")
            return "c_long";
        if (return_type == "unsigned" || return_type == "unsigned int")
            return "c_uint";
        if (return_type == "unsigned long" || return_type == "wxUIntPtr")
            return "c_ulong";
        if (return_type == "uintptr_t")
            return "usize";
        if (return_type == "double")
            return "c_double";
        if (return_type == "float")
            return "c_float";
        if (return_type == "size_t")
            return "usize";
        if (return_type == "TChar")
            return "c_char";
        if (return_type == "TUInt8")
            return "u8";
        if (return_type == "void*")
            return "*mut c_void";

        // Any pointer type → *mut c_void
        if (return_type.find('*') != std::string::npos)
            return "*mut c_void";

        // Fallback
        return "c_int";
    }

    // Split comma-separated macro arg: "x, y" → {"x", "y"}
    inline std::vector<std::string> RustSplitMacroArg(const std::string& arg)
    {
        std::vector<std::string> parts;
        std::istringstream ss(arg);
        std::string part;
        while (std::getline(ss, part, ','))
        {
            auto start = part.find_first_not_of(" \t");
            auto end = part.find_last_not_of(" \t");
            if (start != std::string::npos)
                parts.push_back(part.substr(start, end - start + 1));
        }
        return parts;
    }

    // Expand a Param to one or more Rust FFI parameters (for extern "C" declarations).
    inline std::vector<RustFFIParam> ExpandParamToRustFFI(const Param& p)
    {
        std::vector<RustFFIParam> result;

        // Expanded geometry types: TPoint, TSize, TRect, TVector → individual c_int params
        if (p.macro_name == "TPoint" || p.macro_name == "TSize" || p.macro_name == "TRect" ||
            p.macro_name == "TVector")
        {
            for (auto& n: RustSplitMacroArg(p.macro_arg))
                result.push_back({ "c_int", RustEscapeName(n) });
            return result;
        }

        if (p.macro_name == "TPointLong" || p.macro_name == "TSizeLong" ||
            p.macro_name == "TRectLong" || p.macro_name == "TVectorLong")
        {
            for (auto& n: RustSplitMacroArg(p.macro_arg))
                result.push_back({ "c_long", RustEscapeName(n) });
            return result;
        }

        // Output geometry parameters → *mut c_int pointers
        if (p.macro_name == "TPointOut" || p.macro_name == "TSizeOut" ||
            p.macro_name == "TRectOut" || p.macro_name == "TVectorOut")
        {
            for (auto& n: RustSplitMacroArg(p.macro_arg))
                result.push_back({ "*mut c_int", RustEscapeName(n) });
            return result;
        }

        // Output geometry void pointers
        if (p.macro_name == "TPointOutVoid" || p.macro_name == "TSizeOutVoid" ||
            p.macro_name == "TRectOutVoid" || p.macro_name == "TVectorOutVoid")
        {
            for (auto& n: RustSplitMacroArg(p.macro_arg))
                result.push_back({ "*mut c_void", RustEscapeName(n) });
            return result;
        }

        if (p.macro_name == "TSizeOutDouble")
        {
            for (auto& n: RustSplitMacroArg(p.macro_arg))
                result.push_back({ "*mut c_double", RustEscapeName(n) });
            return result;
        }

        if (p.macro_name == "TColorRGB")
        {
            for (auto& n: RustSplitMacroArg(p.macro_arg))
                result.push_back({ "u8", RustEscapeName(n) });
            return result;
        }

        // Array types: expand to count + pointer
        if (p.macro_name == "TArrayString" || p.macro_name == "TArrayInt" ||
            p.macro_name == "TByteString" || p.macro_name == "TByteStringLazy")
        {
            auto names = RustSplitMacroArg(p.macro_arg);
            if (names.size() >= 2)
            {
                result.push_back({ "c_int", RustEscapeName(names[0]) });
                result.push_back({ "*mut c_void", RustEscapeName(names[1]) });
            }
            return result;
        }

        if (p.macro_name == "TArrayObjectOutVoid")
        {
            std::string name = p.param_name.empty() ? "arr" : p.param_name;
            result.push_back({ "*mut c_void", RustEscapeName(name) });
            return result;
        }

        // Single-valued macro types
        if (p.macro_name == "TClass" || p.macro_name == "TSelf" || p.macro_name == "TClassRef")
        {
            result.push_back(
                { "*mut c_void", RustEscapeName(p.param_name.empty() ? "arg" : p.param_name) });
            return result;
        }

        if (p.macro_name == "TBool" || p.raw_type == "TBool")
        {
            result.push_back(
                { "c_int", RustEscapeName(p.param_name.empty() ? "arg" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TBoolInt" || p.raw_type == "TBool*")
        {
            result.push_back(
                { "c_int", RustEscapeName(p.param_name.empty() ? "arg" : p.param_name) });
            return result;
        }

        if (p.macro_name == "TClosureFun" || p.raw_type == "TClosureFun")
        {
            result.push_back(
                { "*mut c_void", RustEscapeName(p.param_name.empty() ? "fn_" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TStringVoid" || p.macro_name == "TStringVoid")
        {
            result.push_back(
                { "*mut c_void", RustEscapeName(p.param_name.empty() ? "str_" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TArrayIntOutVoid" || p.raw_type == "TArrayIntPtrOutVoid" ||
            p.raw_type == "TArrayStringOutVoid" || p.raw_type == "TByteStringOut" ||
            p.raw_type == "TByteStringLazyOut" || p.raw_type == "TArrayObjectOutVoid")
        {
            result.push_back(
                { "*mut c_void", RustEscapeName(p.param_name.empty() ? "arr" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TChar")
        {
            result.push_back(
                { "c_char", RustEscapeName(p.param_name.empty() ? "ch" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TUInt8")
        {
            result.push_back({ "u8", RustEscapeName(p.param_name.empty() ? "val" : p.param_name) });
            return result;
        }

        // Plain C types
        std::string name = RustEscapeName(p.param_name.empty() ? "arg" : p.param_name);
        std::string raw = p.raw_type;

        if (raw.empty() || raw == "int")
            result.push_back({ "c_int", name });
        else if (raw == "long")
            result.push_back({ "c_long", name });
        else if (raw == "unsigned" || raw == "unsigned int")
            result.push_back({ "c_uint", name });
        else if (raw == "unsigned long" || raw == "wxUIntPtr")
            result.push_back({ "c_ulong", name });
        else if (raw == "uintptr_t")
            result.push_back({ "usize", name });
        else if (raw == "double")
            result.push_back({ "c_double", name });
        else if (raw == "float")
            result.push_back({ "c_float", name });
        else if (raw == "size_t")
            result.push_back({ "usize", name });
        else if (raw.find('*') != std::string::npos)
            result.push_back({ "*mut c_void", name });
        else
            result.push_back({ "c_int", name });  // fallback

        return result;
    }

}  // namespace kwxgen
