/////////////////////////////////////////////////////////////////////////////
// Purpose:   Common text parsing utility functions
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "parser_utils.h"

#include <cctype>
#include <string>
#include <unordered_set>
#include <vector>

std::string Trim(const std::string& text)
{
    const size_t begin_pos = text.find_first_not_of(" \t\r\n");
    if (begin_pos == std::string::npos)
    {
        return {};
    }
    const size_t end_pos = text.find_last_not_of(" \t\r\n");
    return text.substr(begin_pos, end_pos - begin_pos + 1);
}

bool ParseMacroType(const std::string& type, std::string& macro_name, std::string& macro_arg)
{
    // Match: WORD(CONTENT) where CONTENT may contain nested parens
    // e.g. TClass(wxWindow), TSelf(wxButton), TRect(x, y, w, h)
    const size_t paren_pos = type.find('(');
    if (paren_pos == std::string::npos || type.back() != ')')
    {
        macro_name.clear();
        macro_arg.clear();
        return false;
    }
    const std::string prefix = type.substr(0, paren_pos);
    // prefix must be a valid identifier
    if (prefix.empty() ||
        !(std::isalpha(static_cast<unsigned char>(prefix[0])) || prefix[0] == '_'))
    {
        macro_name.clear();
        macro_arg.clear();
        return false;
    }
    macro_name = prefix;
    macro_arg = type.substr(paren_pos + 1, type.size() - paren_pos - 2);
    return true;
}

std::vector<std::string> SplitParams(const std::string& param_str)
{
    std::vector<std::string> result;
    int depth = 0;
    size_t start = 0;
    for (size_t i = 0; i < param_str.size(); ++i)
    {
        if (param_str[i] == '(')
        {
            ++depth;
        }
        else if (param_str[i] == ')')
        {
            --depth;
        }
        else if (param_str[i] == ',' && depth == 0)
        {
            const std::string token = Trim(param_str.substr(start, i - start));
            if (!token.empty())
            {
                result.push_back(token);
            }
            start = i + 1;
        }
    }
    // Last token
    if (start < param_str.size())
    {
        const std::string token = Trim(param_str.substr(start));
        if (!token.empty())
        {
            result.push_back(token);
        }
    }
    return result;
}

Param ParseOneParam(const std::string& token)
{
    Param param;

    // Try macro form: "MacroName(args) paramName" or "MacroName(args)"
    // Find the closing paren of the macro
    const size_t paren_open = token.find('(');
    if (paren_open != std::string::npos)
    {
        // Find the matching close paren
        int depth = 0;
        size_t paren_close = std::string::npos;
        for (size_t i = paren_open; i < token.size(); ++i)
        {
            if (token[i] == '(')
            {
                ++depth;
            }
            else if (token[i] == ')')
            {
                --depth;
                if (depth == 0)
                {
                    paren_close = i;
                    break;
                }
            }
        }

        if (paren_close != std::string::npos)
        {
            const std::string prefix = token.substr(0, paren_open);
            // Check if prefix is a valid macro identifier
            bool is_macro =
                !prefix.empty() &&
                (std::isalpha(static_cast<unsigned char>(prefix[0])) || prefix[0] == '_');
            for (size_t i = 1; is_macro && i < prefix.size(); ++i)
            {
                is_macro = std::isalnum(static_cast<unsigned char>(prefix[i])) || prefix[i] == '_';
            }

            if (is_macro)
            {
                param.macro_name = prefix;
                param.macro_arg = token.substr(paren_open + 1, paren_close - paren_open - 1);
                param.raw_type = prefix + "(" + param.macro_arg + ")";

                // Check for param name after closing paren
                std::string rest = Trim(token.substr(paren_close + 1));
                if (!rest.empty())
                {
                    // Could be "* name" for pointer, or just "name"
                    if (rest[0] == '*')
                    {
                        param.raw_type += "*";
                        rest = Trim(rest.substr(1));
                    }
                    param.param_name = rest;
                }
                return param;
            }
        }
    }

    // Plain type: "int flags", "void* pointer", "double value", etc.
    const size_t last_space = token.rfind(' ');
    if (last_space != std::string::npos)
    {
        const std::string maybe_name = Trim(token.substr(last_space + 1));
        const std::string maybe_type = Trim(token.substr(0, last_space));

        // Check if maybe_name looks like an identifier (and isn't a keyword/type)
        bool is_ident =
            !maybe_name.empty() &&
            (std::isalpha(static_cast<unsigned char>(maybe_name[0])) || maybe_name[0] == '_');
        for (size_t i = 1; is_ident && i < maybe_name.size(); ++i)
        {
            is_ident =
                std::isalnum(static_cast<unsigned char>(maybe_name[i])) || maybe_name[i] == '_';
        }

        static const std::unordered_set<std::string> type_keywords = { "int",   "void", "double",
                                                                       "float", "char", "long" };
        if (is_ident && !type_keywords.contains(maybe_name))
        {
            param.raw_type = maybe_type;
            param.param_name = maybe_name;
            return param;
        }
    }

    // No parameter name — type only
    param.raw_type = token;
    return param;
}
