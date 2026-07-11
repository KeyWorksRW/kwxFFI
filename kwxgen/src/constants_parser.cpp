/////////////////////////////////////////////////////////////////////////////
// Purpose:   Parse constant and free function definitions
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "constants_parser.h"
#include "parser_utils.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <tuple>

// Parse a single-line free function declaration.
// Returns true if parsed, false otherwise.
[[nodiscard]] static bool ParseFreeFunction(const std::string& line, FunctionDecl& decl)
{
    // Match: RETURN_TYPE FUNC_NAME(PARAMS);
    // Return type can be: "TClass(wxFoo)", "int", "void", "void*", "TBool", "TStringVoid"
    // The return type may include parens for macros.

    // Strategy: find the function name by looking for the last identifier before '('
    // that isn't inside a TClass(...) macro.

    // Find the parameter list between outermost ( and );
    const size_t paren_open = line.find('(');

    // But TClass(wxFoo) in the return type also has parens. We need the *function* paren.
    // The function paren is the one that matches ');' at the end.
    const size_t semicolon = line.rfind(';');
    if (semicolon == std::string::npos)
    {
        return false;
    }

    const size_t paren_close = line.rfind(')', semicolon);
    if (paren_close == std::string::npos)
    {
        return false;
    }

    // Now find the matching open paren for this close paren
    int depth = 0;
    size_t func_paren_open = std::string::npos;
    for (size_t i = paren_close; i != std::string::npos; --i)
    {
        if (line[i] == ')')
        {
            ++depth;
        }
        else if (line[i] == '(')
        {
            --depth;
            if (depth == 0)
            {
                func_paren_open = i;
                break;
            }
        }
        if (i == 0)
        {
            break;
        }
    }
    if (func_paren_open == std::string::npos)
    {
        return false;
    }

    // Extract the part before the function paren: "TClass(wxFoo) Null_Foo"
    std::string prefix = line.substr(0, func_paren_open);
    // Trim
    const size_t prefix_end = prefix.find_last_not_of(" \t");
    if (prefix_end == std::string::npos)
    {
        return false;
    }
    prefix = prefix.substr(0, prefix_end + 1);

    // The function name is the last word in prefix
    const size_t last_space = prefix.rfind(' ');
    const size_t last_close_paren = prefix.rfind(')');

    std::string func_name;
    std::string return_type_str;

    if (last_close_paren != std::string::npos &&
        (last_space == std::string::npos || last_close_paren > last_space))
    {
        // Return type ends with ')' — it's a macro like TClass(wxFoo)
        // Function name follows after the closing paren + space
        const size_t after_paren = prefix.find_first_not_of(" \t", last_close_paren + 1);
        if (after_paren == std::string::npos)
        {
            return false;
        }
        func_name = prefix.substr(after_paren);
        return_type_str = prefix.substr(0, last_close_paren + 1);
        // Trim return type
        const size_t return_begin = return_type_str.find_first_not_of(" \t");
        if (return_begin != std::string::npos)
        {
            return_type_str = return_type_str.substr(return_begin);
        }
    }
    else if (last_space != std::string::npos)
    {
        func_name = prefix.substr(last_space + 1);
        return_type_str = prefix.substr(0, last_space);
        const size_t return_begin = return_type_str.find_first_not_of(" \t");
        if (return_begin != std::string::npos)
        {
            return_type_str = return_type_str.substr(return_begin);
        }
    }
    else
    {
        return false;  // No return type + name separation
    }

    decl.method_name = func_name;
    decl.return_type = return_type_str;
    std::ignore = ParseMacroType(return_type_str, decl.return_macro, decl.return_arg);

    // Extract parameter string
    std::string param_str = line.substr(func_paren_open + 1, paren_close - func_paren_open - 1);
    // Trim
    const size_t param_begin = param_str.find_first_not_of(" \t");
    if (param_begin != std::string::npos)
    {
        const size_t param_end = param_str.find_last_not_of(" \t");
        param_str = param_str.substr(param_begin, param_end - param_begin + 1);

        const std::vector<std::string> tokens = SplitParams(param_str);
        for (const auto& token: tokens)
        {
            decl.params.push_back(ParseOneParam(token));
        }
    }

    return true;
}

ConstantsFileResult ParseConstants(const std::filesystem::path& file_path)
{
    ConstantsFileResult result;
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open " << file_path << "\n";
        return result;
    }

    // WXFFI_EXPORT pattern: "WXFFI_EXPORT(int, expNAME)();"
    const std::regex re_wxffi(R"(^\s*WXFFI_EXPORT\s*\(\s*(\w+)\s*,\s*(exp\w+)\s*\)\s*\(\s*\)\s*;)");

    std::string accumulated;
    std::string line;

    while (std::getline(file, line))
    {
        // Skip preprocessor, comment, and blank lines
        if (line.empty() || line[0] == '#')
        {
            continue;
        }
        // Skip single-line comments
        {
            const size_t first_char = line.find_first_not_of(" \t");
            if (first_char != std::string::npos && line.size() >= first_char + 2 &&
                line[first_char] == '/' && line[first_char + 1] == '/')
            {
                continue;
            }
        }

        // Check for WXFFI_EXPORT constant
        std::smatch match;
        if (std::regex_search(line, match, re_wxffi))
        {
            ConstantDecl decl;
            decl.return_type = match[1].str();
            decl.export_name = match[2].str();
            // Strip "exp" or "expwx" prefix for constant_name
            static constexpr std::string_view EXPWX_PREFIX = "expwx";
            static constexpr std::string_view EXP_PREFIX = "exp";
            const std::string name = decl.export_name;
            if (name.starts_with(EXPWX_PREFIX))
            {
                decl.constant_name = name.substr(EXPWX_PREFIX.size());
            }
            else if (name.starts_with(EXP_PREFIX))
            {
                decl.constant_name = name.substr(EXP_PREFIX.size());
            }
            else
            {
                decl.constant_name = name;
            }
            result.constants.push_back(std::move(decl));
            continue;
        }

        // Handle multi-line continuation: if line starts with whitespace and we have
        // accumulated content, join it.
        const bool is_continuation =
            !accumulated.empty() && !line.empty() && (line[0] == ' ' || line[0] == '\t');

        if (is_continuation)
        {
            // Trim leading whitespace from continuation and join
            const size_t line_begin = line.find_first_not_of(" \t");
            if (line_begin != std::string::npos)
            {
                accumulated += " " + line.substr(line_begin);
            }
            // Check if now complete (ends with ;)
            const size_t trimmed_end = accumulated.find_last_not_of(" \t");
            if (trimmed_end != std::string::npos && accumulated[trimmed_end] == ';')
            {
                FunctionDecl decl;
                if (ParseFreeFunction(accumulated, decl))
                {
                    result.free_functions.push_back(std::move(decl));
                }
                accumulated.clear();
            }
            continue;
        }

        // If we had accumulated content that didn't continue, process it
        if (!accumulated.empty())
        {
            FunctionDecl decl;
            if (ParseFreeFunction(accumulated, decl))
            {
                result.free_functions.push_back(std::move(decl));
            }
            accumulated.clear();
        }

        // Try to parse as a complete single-line free function
        const size_t trimmed_end = line.find_last_not_of(" \t");
        if (trimmed_end != std::string::npos && line[trimmed_end] == ';')
        {
            FunctionDecl decl;
            if (ParseFreeFunction(line, decl))
            {
                result.free_functions.push_back(std::move(decl));
            }
        }
        else if (trimmed_end != std::string::npos)
        {
            // Doesn't end with ; — start accumulating for multi-line
            const size_t line_begin = line.find_first_not_of(" \t");
            if (line_begin != std::string::npos)
            {
                accumulated = line.substr(line_begin);
            }
        }
    }

    // Flush any remaining accumulated line
    if (!accumulated.empty())
    {
        FunctionDecl decl;
        if (ParseFreeFunction(accumulated, decl))
        {
            result.free_functions.push_back(std::move(decl));
        }
    }

    return result;
}
