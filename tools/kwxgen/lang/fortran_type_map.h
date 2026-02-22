#pragma once

// Fortran type mapping: converts parsed FFI model types to ISO_C_BINDING type strings.
// Two aspects:
//   1. Parameter declarations: "type(c_ptr), value" / "integer(c_int), value"
//   2. Import statements: which ISO_C_BINDING symbols are needed per function

#include "../model.h"

#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace kwxgen
{

    // A single Fortran-typed parameter for interface block declarations.
    struct FortranParam
    {
        std::string fortran_type;   // "type(c_ptr)", "integer(c_int)", "real(c_double)", etc.
        std::string import_sym;     // "c_ptr", "c_int", "c_double" — needed for import statement
        std::string name;           // parameter name
        bool pass_by_value = true;  // almost always true for C interop
    };

    // Return type info for Fortran interface declarations.
    struct FortranReturnInfo
    {
        std::string fortran_type;  // "type(c_ptr)", "integer(c_int)", or "" for void
        std::string import_sym;    // "c_ptr", "c_int", or "" for void
        bool is_void = false;      // true → use subroutine instead of function
    };

    // Convert a return type to its Fortran ISO_C_BINDING equivalent.
    inline FortranReturnInfo FortranReturnType(const std::string& return_type,
                                               const std::string& return_macro)
    {
        FortranReturnInfo info;

        if (return_type == "void" || return_type.empty())
        {
            info.is_void = true;
            return info;
        }
        if (return_macro == "TClass" || return_macro == "TSelf" || return_macro == "TClassRef")
        {
            info.fortran_type = "type(c_ptr)";
            info.import_sym = "c_ptr";
            return info;
        }
        if (return_type == "TBool" || return_type == "TBoolInt")
        {
            info.fortran_type = "integer(c_int)";
            info.import_sym = "c_int";
            return info;
        }
        if (return_type == "TString" || return_type == "TStringOut" || return_type == "TStringVoid")
        {
            info.fortran_type = "type(c_ptr)";
            info.import_sym = "c_ptr";
            return info;
        }
        if (return_type == "int" || return_type == "TArrayLen" || return_type == "TByteStringLen")
        {
            info.fortran_type = "integer(c_int)";
            info.import_sym = "c_int";
            return info;
        }
        if (return_type == "long" || return_type == "time_t")
        {
            info.fortran_type = "integer(c_long)";
            info.import_sym = "c_long";
            return info;
        }
        if (return_type == "unsigned" || return_type == "unsigned int")
        {
            // Fortran has no unsigned; use c_int
            info.fortran_type = "integer(c_int)";
            info.import_sym = "c_int";
            return info;
        }
        if (return_type == "unsigned long" || return_type == "wxUIntPtr")
        {
            info.fortran_type = "integer(c_long)";
            info.import_sym = "c_long";
            return info;
        }
        if (return_type == "double")
        {
            info.fortran_type = "real(c_double)";
            info.import_sym = "c_double";
            return info;
        }
        if (return_type == "float")
        {
            info.fortran_type = "real(c_float)";
            info.import_sym = "c_float";
            return info;
        }
        if (return_type == "size_t")
        {
            info.fortran_type = "integer(c_size_t)";
            info.import_sym = "c_size_t";
            return info;
        }
        if (return_type == "TChar")
        {
            info.fortran_type = "character(c_char)";
            info.import_sym = "c_char";
            return info;
        }
        if (return_type == "TUInt8")
        {
            info.fortran_type = "integer(c_int8_t)";
            info.import_sym = "c_int8_t";
            return info;
        }
        if (return_type == "void*")
        {
            info.fortran_type = "type(c_ptr)";
            info.import_sym = "c_ptr";
            return info;
        }

        // Any pointer type → c_ptr
        if (return_type.find('*') != std::string::npos)
        {
            info.fortran_type = "type(c_ptr)";
            info.import_sym = "c_ptr";
            return info;
        }

        // Fallback
        info.fortran_type = "integer(c_int)";
        info.import_sym = "c_int";
        return info;
    }

    // Fortran reserved words that must be avoided as parameter names.
    inline std::string FortranEscapeName(const std::string& name)
    {
        // Fortran keywords that could collide with C parameter names
        if (name == "type" || name == "class" || name == "data" || name == "real" ||
            name == "integer" || name == "double" || name == "complex" || name == "character" ||
            name == "logical" || name == "result" || name == "value" || name == "target" ||
            name == "pointer" || name == "intent" || name == "in" || name == "out" ||
            name == "inout" || name == "allocatable" || name == "end" || name == "do" ||
            name == "if" || name == "then" || name == "else" || name == "select" ||
            name == "case" || name == "where" || name == "forall" || name == "use" ||
            name == "module" || name == "function" || name == "subroutine" || name == "program" ||
            name == "call" || name == "return" || name == "stop" || name == "implicit" ||
            name == "none" || name == "interface" || name == "contains" || name == "block" ||
            name == "associate" || name == "import" || name == "only" || name == "operator" ||
            name == "assignment" || name == "sequence" || name == "private" || name == "public" ||
            name == "save" || name == "common" || name == "equivalence" || name == "external" ||
            name == "intrinsic" || name == "kind" || name == "len" || name == "dimension" ||
            name == "parameter" || name == "optional" || name == "recursive" || name == "pure" ||
            name == "elemental")
        {
            return name + "_";
        }
        return name;
    }

    // Split comma-separated macro arg: "x, y" → {"x", "y"}
    inline std::vector<std::string> FortranSplitMacroArg(const std::string& arg)
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

    // Expand a Param to one or more Fortran-typed parameters.
    inline std::vector<FortranParam> ExpandParamToFortran(const Param& p)
    {
        std::vector<FortranParam> result;

        // Expanded geometry types: TPoint, TSize, TRect, TVector → individual c_int params
        if (p.macro_name == "TPoint" || p.macro_name == "TSize" || p.macro_name == "TRect" ||
            p.macro_name == "TVector")
        {
            for (auto& n: FortranSplitMacroArg(p.macro_arg))
                result.push_back({ "integer(c_int)", "c_int", FortranEscapeName(n) });
            return result;
        }

        if (p.macro_name == "TPointLong" || p.macro_name == "TSizeLong" ||
            p.macro_name == "TRectLong" || p.macro_name == "TVectorLong")
        {
            for (auto& n: FortranSplitMacroArg(p.macro_arg))
                result.push_back({ "integer(c_long)", "c_long", FortranEscapeName(n) });
            return result;
        }

        // Output geometry parameters → c_ptr (int* pointers)
        if (p.macro_name == "TPointOut" || p.macro_name == "TSizeOut" ||
            p.macro_name == "TRectOut" || p.macro_name == "TVectorOut")
        {
            for (auto& n: FortranSplitMacroArg(p.macro_arg))
                result.push_back({ "type(c_ptr)", "c_ptr", FortranEscapeName(n) });
            return result;
        }

        // Output geometry void pointers
        if (p.macro_name == "TPointOutVoid" || p.macro_name == "TSizeOutVoid" ||
            p.macro_name == "TRectOutVoid" || p.macro_name == "TVectorOutVoid")
        {
            for (auto& n: FortranSplitMacroArg(p.macro_arg))
                result.push_back({ "type(c_ptr)", "c_ptr", FortranEscapeName(n) });
            return result;
        }

        if (p.macro_name == "TSizeOutDouble")
        {
            for (auto& n: FortranSplitMacroArg(p.macro_arg))
                result.push_back({ "type(c_ptr)", "c_ptr", FortranEscapeName(n) });
            return result;
        }

        if (p.macro_name == "TColorRGB")
        {
            for (auto& n: FortranSplitMacroArg(p.macro_arg))
                result.push_back({ "integer(c_int8_t)", "c_int8_t", FortranEscapeName(n) });
            return result;
        }

        // Array types: expand to count + pointer
        if (p.macro_name == "TArrayString" || p.macro_name == "TArrayInt" ||
            p.macro_name == "TByteString" || p.macro_name == "TByteStringLazy")
        {
            auto names = FortranSplitMacroArg(p.macro_arg);
            if (names.size() >= 2)
            {
                result.push_back({ "integer(c_int)", "c_int", FortranEscapeName(names[0]) });
                result.push_back({ "type(c_ptr)", "c_ptr", FortranEscapeName(names[1]) });
            }
            return result;
        }

        if (p.macro_name == "TArrayObjectOutVoid")
        {
            std::string name = p.param_name.empty() ? "arr" : p.param_name;
            result.push_back({ "type(c_ptr)", "c_ptr", FortranEscapeName(name) });
            return result;
        }

        // Single-valued macro types
        if (p.macro_name == "TClass" || p.macro_name == "TSelf" || p.macro_name == "TClassRef")
        {
            result.push_back({ "type(c_ptr)", "c_ptr",
                               FortranEscapeName(p.param_name.empty() ? "arg" : p.param_name) });
            return result;
        }

        if (p.macro_name == "TBool" || p.raw_type == "TBool")
        {
            result.push_back({ "integer(c_int)", "c_int",
                               FortranEscapeName(p.param_name.empty() ? "arg" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TBoolInt" || p.raw_type == "TBool*")
        {
            result.push_back({ "integer(c_int)", "c_int",
                               FortranEscapeName(p.param_name.empty() ? "arg" : p.param_name) });
            return result;
        }

        if (p.macro_name == "TClosureFun" || p.raw_type == "TClosureFun")
        {
            result.push_back({ "type(c_ptr)", "c_ptr",
                               FortranEscapeName(p.param_name.empty() ? "fn" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TStringVoid" || p.macro_name == "TStringVoid")
        {
            result.push_back({ "type(c_ptr)", "c_ptr",
                               FortranEscapeName(p.param_name.empty() ? "str" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TArrayIntOutVoid" || p.raw_type == "TArrayIntPtrOutVoid" ||
            p.raw_type == "TArrayStringOutVoid" || p.raw_type == "TByteStringOut" ||
            p.raw_type == "TByteStringLazyOut" || p.raw_type == "TArrayObjectOutVoid")
        {
            result.push_back({ "type(c_ptr)", "c_ptr",
                               FortranEscapeName(p.param_name.empty() ? "arr" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TChar")
        {
            result.push_back({ "character(c_char)", "c_char",
                               FortranEscapeName(p.param_name.empty() ? "ch" : p.param_name) });
            return result;
        }

        if (p.raw_type == "TUInt8")
        {
            result.push_back({ "integer(c_int8_t)", "c_int8_t",
                               FortranEscapeName(p.param_name.empty() ? "val" : p.param_name) });
            return result;
        }

        // Plain C types
        std::string name = FortranEscapeName(p.param_name.empty() ? "arg" : p.param_name);
        std::string raw = p.raw_type;

        if (raw.empty() || raw == "int")
            result.push_back({ "integer(c_int)", "c_int", name });
        else if (raw == "long")
            result.push_back({ "integer(c_long)", "c_long", name });
        else if (raw == "unsigned" || raw == "unsigned int")
            result.push_back({ "integer(c_int)", "c_int", name });
        else if (raw == "unsigned long" || raw == "wxUIntPtr")
            result.push_back({ "integer(c_long)", "c_long", name });
        else if (raw == "double")
            result.push_back({ "real(c_double)", "c_double", name });
        else if (raw == "float")
            result.push_back({ "real(c_float)", "c_float", name });
        else if (raw == "size_t")
            result.push_back({ "integer(c_size_t)", "c_size_t", name });
        else if (raw.find('*') != std::string::npos)
            result.push_back({ "type(c_ptr)", "c_ptr", name });
        else
            result.push_back({ "integer(c_int)", "c_int", name });  // fallback

        return result;
    }

    // Collect all unique import symbols needed for a set of Fortran params + return type.
    inline std::set<std::string> CollectImports(const std::vector<FortranParam>& params,
                                                const FortranReturnInfo& retInfo)
    {
        std::set<std::string> imports;
        if (!retInfo.import_sym.empty())
            imports.insert(retInfo.import_sym);
        for (const auto& p: params)
        {
            if (!p.import_sym.empty())
                imports.insert(p.import_sym);
        }
        return imports;
    }

}  // namespace kwxgen
