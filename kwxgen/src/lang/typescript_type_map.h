/////////////////////////////////////////////////////////////////////////////
// Purpose:   Deno TypeScript FFI type mapping
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ..\..\LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

// Deno FFI type mapping for TypeScript code generation.
// Maps parsed kwx FFI model types to Deno NativeType strings for Deno.dlopen symbol definitions.
//
// Deno NativeType strings: "void", "i8", "u8", "i16", "u16", "i32", "u32",
//   "i64", "u64", "usize", "isize", "f32", "f64", "pointer", "buffer", "function"
//
// JavaScript runtime types from Deno:
//   number     — i8, u8, i16, u16, i32, u32, f32, f64
//   bigint     — i64, u64, usize, isize
//   Deno.PointerValue — pointer, function
//   BufferSource | null — buffer
//   void       — void (result only)
//
// Note: C "long" maps to "i32" here. On Windows, C long is 32-bit.
// On POSIX 64-bit, C long is 64-bit. wx long usage (IDs, flags) fits in 32 bits.

#include "../model.h"

#include <sstream>
#include <string>
#include <vector>

// A single Deno FFI parameter: a NativeType string and a TypeScript identifier name.
struct TsFFIParam
{
    std::string deno_type;  // "\"i32\"", "\"pointer\"", "\"void\"", etc.
    std::string name;       // TypeScript-safe parameter name
};

// TypeScript / JavaScript keywords that must not be used as identifiers.
inline std::string TsEscapeName(const std::string& name)
{
    if (name == "in" || name == "if" || name == "do" || name == "for" || name == "let" ||
        name == "new" || name == "try" || name == "var" || name == "case" || name == "else" ||
        name == "enum" || name == "null" || name == "this" || name == "true" || name == "void" ||
        name == "with" || name == "break" || name == "catch" || name == "class" ||
        name == "const" || name == "false" || name == "super" || name == "throw" ||
        name == "while" || name == "yield" || name == "delete" || name == "export" ||
        name == "import" || name == "return" || name == "static" || name == "switch" ||
        name == "typeof" || name == "default" || name == "extends" || name == "finally" ||
        name == "function" || name == "continue" || name == "debugger" || name == "instanceof" ||
        name == "from" || name == "of" || name == "type" || name == "interface" ||
        name == "implements" || name == "private" || name == "protected" || name == "public" ||
        name == "abstract" || name == "declare" || name == "override" || name == "readonly" ||
        name == "satisfies" || name == "as" || name == "namespace" || name == "async" ||
        name == "await")
    {
        return name + "_";
    }
    return name;
}

// Split a comma-separated macro argument string into individual names: "x, y" → {"x", "y"}
inline std::vector<std::string> TsSplitMacroArg(const std::string& arg)
{
    std::vector<std::string> parts;
    std::istringstream stream(arg);
    std::string part;
    while (std::getline(stream, part, ','))
    {
        const std::string::size_type start_pos = part.find_first_not_of(" \t");
        const std::string::size_type end_pos = part.find_last_not_of(" \t");
        if (start_pos != std::string::npos)
        {
            parts.push_back(part.substr(start_pos, end_pos - start_pos + 1ULL));
        }
    }
    return parts;
}

// Convert a kwx return type to a Deno NativeType string (quoted, ready to embed in TS source).
// Returns "\"void\"" for void/empty, "\"i32\"" for int, "\"pointer\"" for pointer types, etc.
inline std::string TsFFIReturnType(const std::string& return_type, const std::string& return_macro)
{
    if (return_type == "void" || return_type.empty())
    {
        return "\"void\"";
    }
    if (return_macro == "TClass" || return_macro == "TSelf" || return_macro == "TClassRef")
    {
        return "\"pointer\"";
    }
    if (return_type == "TBool" || return_type == "TBoolInt")
    {
        return "\"i32\"";
    }
    if (return_type == "TString" || return_type == "TStringOut" || return_type == "TStringVoid")
    {
        return "\"pointer\"";
    }
    if (return_type == "int" || return_type == "TArrayLen" || return_type == "TByteStringLen")
    {
        return "\"i32\"";
    }
    if (return_type == "long" || return_type == "time_t")
    {
        return "\"i32\"";
    }
    if (return_type == "unsigned" || return_type == "unsigned int")
    {
        return "\"u32\"";
    }
    if (return_type == "unsigned long" || return_type == "wxUIntPtr")
    {
        return "\"u32\"";
    }
    if (return_type == "uintptr_t")
    {
        return "\"usize\"";
    }
    if (return_type == "double")
    {
        return "\"f64\"";
    }
    if (return_type == "float")
    {
        return "\"f32\"";
    }
    if (return_type == "size_t")
    {
        return "\"usize\"";
    }
    if (return_type == "TChar")
    {
        return "\"u8\"";
    }
    if (return_type == "TUInt8")
    {
        return "\"u8\"";
    }
    if (return_type == "void*")
    {
        return "\"pointer\"";
    }
    // Any remaining pointer type → pointer
    if (return_type.find('*') != std::string::npos)
    {
        return "\"pointer\"";
    }
    // Fallback
    return "\"i32\"";
}

// Expand a single kwx Param into one or more Deno FFI TsFFIParam entries.
// Geometry macros expand to multiple scalar params; most types expand to exactly one.
inline std::vector<TsFFIParam> ExpandParamToTsFFI(const Param& param_in)
{
    std::vector<TsFFIParam> result;

    // Geometry expansion macros: TPoint, TSize, TVector → two "i32" params
    if (param_in.macro_name == "TPoint" || param_in.macro_name == "TSize" ||
        param_in.macro_name == "TVector")
    {
        for (const auto& name_str: TsSplitMacroArg(param_in.macro_arg))
        {
            result.push_back({ "\"i32\"", TsEscapeName(name_str) });
        }
        return result;
    }

    if (param_in.macro_name == "TRect")
    {
        for (const auto& name_str: TsSplitMacroArg(param_in.macro_arg))
        {
            result.push_back({ "\"i32\"", TsEscapeName(name_str) });
        }
        return result;
    }

    if (param_in.macro_name == "TPointLong" || param_in.macro_name == "TSizeLong" ||
        param_in.macro_name == "TRectLong" || param_in.macro_name == "TVectorLong")
    {
        for (const auto& name_str: TsSplitMacroArg(param_in.macro_arg))
        {
            result.push_back({ "\"i32\"", TsEscapeName(name_str) });
        }
        return result;
    }

    // Output geometry: int* output pointers → "pointer"
    if (param_in.macro_name == "TPointOut" || param_in.macro_name == "TSizeOut" ||
        param_in.macro_name == "TRectOut" || param_in.macro_name == "TVectorOut")
    {
        for (const auto& name_str: TsSplitMacroArg(param_in.macro_arg))
        {
            result.push_back({ "\"pointer\"", TsEscapeName(name_str) });
        }
        return result;
    }

    if (param_in.macro_name == "TPointOutVoid" || param_in.macro_name == "TSizeOutVoid" ||
        param_in.macro_name == "TRectOutVoid" || param_in.macro_name == "TVectorOutVoid")
    {
        for (const auto& name_str: TsSplitMacroArg(param_in.macro_arg))
        {
            result.push_back({ "\"pointer\"", TsEscapeName(name_str) });
        }
        return result;
    }

    if (param_in.macro_name == "TSizeOutDouble")
    {
        for (const auto& name_str: TsSplitMacroArg(param_in.macro_arg))
        {
            result.push_back({ "\"pointer\"", TsEscapeName(name_str) });
        }
        return result;
    }

    if (param_in.macro_name == "TColorRGB")
    {
        for (const auto& name_str: TsSplitMacroArg(param_in.macro_arg))
        {
            result.push_back({ "\"u8\"", TsEscapeName(name_str) });
        }
        return result;
    }

    // Array types: count (i32) + pointer to data
    if (param_in.macro_name == "TArrayString" || param_in.macro_name == "TArrayInt" ||
        param_in.macro_name == "TByteString" || param_in.macro_name == "TByteStringLazy")
    {
        const std::vector<std::string> names = TsSplitMacroArg(param_in.macro_arg);
        if (names.size() >= 2ULL)
        {
            result.push_back({ "\"i32\"", TsEscapeName(names[0]) });
            result.push_back({ "\"pointer\"", TsEscapeName(names[1]) });
        }
        return result;
    }

    if (param_in.macro_name == "TArrayObjectOutVoid")
    {
        const std::string pname = param_in.param_name.empty() ? "arr" : param_in.param_name;
        result.push_back({ "\"pointer\"", TsEscapeName(pname) });
        return result;
    }

    // Single-valued macro types
    if (param_in.macro_name == "TClass" || param_in.macro_name == "TSelf" ||
        param_in.macro_name == "TClassRef")
    {
        const std::string pname = param_in.param_name.empty() ? "self_" : param_in.param_name;
        result.push_back({ "\"pointer\"", TsEscapeName(pname) });
        return result;
    }

    if (param_in.macro_name == "TBool" || param_in.raw_type == "TBool")
    {
        const std::string pname = param_in.param_name.empty() ? "flag" : param_in.param_name;
        result.push_back({ "\"i32\"", TsEscapeName(pname) });
        return result;
    }

    if (param_in.raw_type == "TBoolInt" || param_in.raw_type == "TBool*")
    {
        const std::string pname = param_in.param_name.empty() ? "flag" : param_in.param_name;
        result.push_back({ "\"i32\"", TsEscapeName(pname) });
        return result;
    }

    if (param_in.macro_name == "TClosureFun" || param_in.raw_type == "TClosureFun")
    {
        const std::string pname = param_in.param_name.empty() ? "func_" : param_in.param_name;
        result.push_back({ "\"function\"", TsEscapeName(pname) });
        return result;
    }

    if (param_in.raw_type == "TStringVoid" || param_in.macro_name == "TStringVoid")
    {
        const std::string pname = param_in.param_name.empty() ? "wstr" : param_in.param_name;
        result.push_back({ "\"pointer\"", TsEscapeName(pname) });
        return result;
    }

    if (param_in.raw_type == "TArrayIntOutVoid" || param_in.raw_type == "TArrayIntPtrOutVoid" ||
        param_in.raw_type == "TArrayStringOutVoid" || param_in.raw_type == "TByteStringOut" ||
        param_in.raw_type == "TByteStringLazyOut" || param_in.raw_type == "TArrayObjectOutVoid")
    {
        const std::string pname = param_in.param_name.empty() ? "arrp" : param_in.param_name;
        result.push_back({ "\"pointer\"", TsEscapeName(pname) });
        return result;
    }

    if (param_in.raw_type == "TChar")
    {
        const std::string pname = param_in.param_name.empty() ? "char_" : param_in.param_name;
        result.push_back({ "\"u8\"", TsEscapeName(pname) });
        return result;
    }

    if (param_in.raw_type == "TUInt8")
    {
        const std::string pname = param_in.param_name.empty() ? "byte_" : param_in.param_name;
        result.push_back({ "\"u8\"", TsEscapeName(pname) });
        return result;
    }

    if (param_in.raw_type == "TString")
    {
        const std::string pname = param_in.param_name.empty() ? "wstr" : param_in.param_name;
        result.push_back({ "\"pointer\"", TsEscapeName(pname) });
        return result;
    }

    if (param_in.raw_type == "TStringOut")
    {
        const std::string pname = param_in.param_name.empty() ? "wbuf" : param_in.param_name;
        result.push_back({ "\"pointer\"", TsEscapeName(pname) });
        return result;
    }

    // Plain C types
    const std::string pname =
        TsEscapeName(param_in.param_name.empty() ? "arg_" : param_in.param_name);
    const std::string& rtype = param_in.raw_type;

    if (rtype.empty() || rtype == "int")
    {
        result.push_back({ "\"i32\"", pname });
    }
    else if (rtype == "long")
    {
        result.push_back({ "\"i32\"", pname });
    }
    else if (rtype == "unsigned" || rtype == "unsigned int")
    {
        result.push_back({ "\"u32\"", pname });
    }
    else if (rtype == "unsigned long" || rtype == "wxUIntPtr")
    {
        result.push_back({ "\"u32\"", pname });
    }
    else if (rtype == "uintptr_t")
    {
        result.push_back({ "\"usize\"", pname });
    }
    else if (rtype == "double")
    {
        result.push_back({ "\"f64\"", pname });
    }
    else if (rtype == "float")
    {
        result.push_back({ "\"f32\"", pname });
    }
    else if (rtype == "size_t")
    {
        result.push_back({ "\"usize\"", pname });
    }
    else if (rtype.find('*') != std::string::npos)
    {
        result.push_back({ "\"pointer\"", pname });
    }
    else
    {
        result.push_back({ "\"i32\"", pname });  // fallback
    }

    return result;
}

// Map a Deno NativeType string to the corresponding TypeScript runtime type annotation.
inline std::string TsRuntimeType(const std::string& deno_type)
{
    if (deno_type == "\"void\"")
    {
        return "void";
    }
    if (deno_type == "\"i8\"" || deno_type == "\"u8\"" || deno_type == "\"i16\"" ||
        deno_type == "\"u16\"" || deno_type == "\"i32\"" || deno_type == "\"u32\"" ||
        deno_type == "\"f32\"" || deno_type == "\"f64\"")
    {
        return "number";
    }
    if (deno_type == "\"i64\"" || deno_type == "\"u64\"" || deno_type == "\"usize\"" ||
        deno_type == "\"isize\"")
    {
        return "bigint";
    }
    if (deno_type == "\"pointer\"" || deno_type == "\"function\"")
    {
        return "Deno.PointerValue";
    }
    if (deno_type == "\"buffer\"")
    {
        return "BufferSource | null";
    }
    return "unknown";
}
