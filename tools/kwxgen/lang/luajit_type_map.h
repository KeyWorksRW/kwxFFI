#pragma once

// LuaJIT type mapping: converts parsed FFI model types to C declaration strings
// for use in LuaJIT ffi.cdef blocks.

#include "../model.h"

#include <sstream>
#include <string>
#include <vector>

namespace kwxgen
{

    // A single C-typed parameter for LuaJIT ffi.cdef declarations.
    struct LuaCParam
    {
        std::string c_type;  // "void*", "int", "double", etc.
        std::string name;    // parameter name
    };

    // Convert a return type to its plain C equivalent for ffi.cdef.
    inline std::string LuaJITReturnType(const std::string& return_type,
                                        const std::string& return_macro)
    {
        if (return_type == "void" || return_type.empty())
            return "void";
        if (return_macro == "TClass" || return_macro == "TSelf" || return_macro == "TClassRef")
            return "void*";
        if (return_type == "TBool" || return_type == "TBoolInt")
            return "int";
        if (return_type == "TString" || return_type == "TStringOut" || return_type == "TStringVoid")
            return "void*";
        if (return_type == "int" || return_type == "TArrayLen" || return_type == "TByteStringLen")
            return "int";
        if (return_type == "long" || return_type == "time_t")
            return "long";
        if (return_type == "unsigned" || return_type == "unsigned int")
            return "unsigned int";
        if (return_type == "unsigned long" || return_type == "wxUIntPtr")
            return "unsigned long";
        if (return_type == "double")
            return "double";
        if (return_type == "float")
            return "float";
        if (return_type == "size_t")
            return "size_t";
        if (return_type == "TChar")
            return "char";
        if (return_type == "TUInt8")
            return "unsigned char";
        if (return_type == "void*")
            return "void*";

        // Any pointer type → void*
        if (return_type.find('*') != std::string::npos)
            return "void*";

        // Fallback
        return "int";
    }

    // Split comma-separated macro arg: "x, y" → {"x", "y"}
    inline std::vector<std::string> LuaJITSplitMacroArg(const std::string& arg)
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

    // Expand a Param to one or more C-typed parameters for ffi.cdef.
    inline std::vector<LuaCParam> ExpandParamToC(const Param& p)
    {
        std::vector<LuaCParam> result;

        // Expanded geometry types: TPoint, TSize, TRect, TVector → individual int params
        if (p.macro_name == "TPoint" || p.macro_name == "TSize" || p.macro_name == "TRect" ||
            p.macro_name == "TVector")
        {
            for (auto& n: LuaJITSplitMacroArg(p.macro_arg))
                result.push_back({ "int", n });
            return result;
        }

        if (p.macro_name == "TPointLong" || p.macro_name == "TSizeLong" ||
            p.macro_name == "TRectLong" || p.macro_name == "TVectorLong")
        {
            for (auto& n: LuaJITSplitMacroArg(p.macro_arg))
                result.push_back({ "long", n });
            return result;
        }

        // Output geometry parameters → int* pointers
        if (p.macro_name == "TPointOut" || p.macro_name == "TSizeOut" ||
            p.macro_name == "TRectOut" || p.macro_name == "TVectorOut")
        {
            for (auto& n: LuaJITSplitMacroArg(p.macro_arg))
                result.push_back({ "int*", n });
            return result;
        }

        // Output geometry void pointers
        if (p.macro_name == "TPointOutVoid" || p.macro_name == "TSizeOutVoid" ||
            p.macro_name == "TRectOutVoid" || p.macro_name == "TVectorOutVoid")
        {
            for (auto& n: LuaJITSplitMacroArg(p.macro_arg))
                result.push_back({ "void*", n });
            return result;
        }

        if (p.macro_name == "TSizeOutDouble")
        {
            for (auto& n: LuaJITSplitMacroArg(p.macro_arg))
                result.push_back({ "double*", n });
            return result;
        }

        if (p.macro_name == "TColorRGB")
        {
            for (auto& n: LuaJITSplitMacroArg(p.macro_arg))
                result.push_back({ "unsigned char", n });
            return result;
        }

        // Array types: expand to count + pointer
        if (p.macro_name == "TArrayString" || p.macro_name == "TArrayInt" ||
            p.macro_name == "TByteString" || p.macro_name == "TByteStringLazy")
        {
            auto names = LuaJITSplitMacroArg(p.macro_arg);
            if (names.size() >= 2)
            {
                result.push_back({ "int", names[0] });
                result.push_back({ "void*", names[1] });
            }
            return result;
        }

        if (p.macro_name == "TArrayObjectOutVoid")
        {
            std::string name = p.param_name.empty() ? "arr" : p.param_name;
            result.push_back({ "void*", name });
            return result;
        }

        // Single-valued macro types
        if (p.macro_name == "TClass" || p.macro_name == "TSelf" || p.macro_name == "TClassRef")
        {
            result.push_back({ "void*", p.param_name.empty() ? "arg" : p.param_name });
            return result;
        }

        if (p.macro_name == "TBool" || p.raw_type == "TBool")
        {
            result.push_back({ "int", p.param_name.empty() ? "arg" : p.param_name });
            return result;
        }

        if (p.raw_type == "TBoolInt" || p.raw_type == "TBool*")
        {
            result.push_back({ "int", p.param_name.empty() ? "arg" : p.param_name });
            return result;
        }

        if (p.macro_name == "TClosureFun" || p.raw_type == "TClosureFun")
        {
            result.push_back({ "void*", p.param_name.empty() ? "fn" : p.param_name });
            return result;
        }

        if (p.raw_type == "TStringVoid" || p.macro_name == "TStringVoid")
        {
            result.push_back({ "void*", p.param_name.empty() ? "str" : p.param_name });
            return result;
        }

        if (p.raw_type == "TArrayIntOutVoid" || p.raw_type == "TArrayIntPtrOutVoid" ||
            p.raw_type == "TArrayStringOutVoid" || p.raw_type == "TByteStringOut" ||
            p.raw_type == "TByteStringLazyOut" || p.raw_type == "TArrayObjectOutVoid")
        {
            result.push_back({ "void*", p.param_name.empty() ? "arr" : p.param_name });
            return result;
        }

        if (p.raw_type == "TChar")
        {
            result.push_back({ "char", p.param_name.empty() ? "ch" : p.param_name });
            return result;
        }

        if (p.raw_type == "TUInt8")
        {
            result.push_back({ "unsigned char", p.param_name.empty() ? "val" : p.param_name });
            return result;
        }

        // Plain C types
        std::string name = p.param_name.empty() ? "arg" : p.param_name;
        std::string raw = p.raw_type;

        if (raw.empty() || raw == "int")
            result.push_back({ "int", name });
        else if (raw == "long")
            result.push_back({ "long", name });
        else if (raw == "unsigned" || raw == "unsigned int")
            result.push_back({ "unsigned int", name });
        else if (raw == "unsigned long" || raw == "wxUIntPtr")
            result.push_back({ "unsigned long", name });
        else if (raw == "double")
            result.push_back({ "double", name });
        else if (raw == "float")
            result.push_back({ "float", name });
        else if (raw == "size_t")
            result.push_back({ "size_t", name });
        else if (raw.find('*') != std::string::npos)
            result.push_back({ "void*", name });
        else
            result.push_back({ "int", name });  // fallback

        return result;
    }

}  // namespace kwxgen
