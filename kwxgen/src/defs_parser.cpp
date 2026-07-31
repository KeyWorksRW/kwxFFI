/////////////////////////////////////////////////////////////////////////////
// Purpose:   Parse C++ type definitions for FFI generation
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "defs_parser.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::vector<ConstantDecl> ParseDefs(const std::filesystem::path& filePath)
{
    std::vector<ConstantDecl> results;
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open " << filePath << "\n";
        return results;
    }

    // Pattern 1: EXPORT int expwxNAME()
    const std::regex re_int(R"(^\s*EXPORT\s+int\s+(expwx(\w+))\s*\(\s*\))");

    // Pattern 2: EXPORT wxString* expwxNAME()
    const std::regex re_str(R"(^\s*EXPORT\s+wxString\*\s+(expwx(\w+))\s*\(\s*\))");

    // Pattern 3: EXPORT const TYPE* expwxNAME()
    // Captures: 1=const TYPE*, 2=TYPE, 3=full func name, 4=suffix after "expwx"
    constexpr int CONST_EXPORT_GROUP = 3;
    constexpr int CONST_SUFFIX_GROUP = 4;
    const std::regex re_const(R"(^\s*EXPORT\s+(const\s+(\w+)\*)\s+(expwx(\w+))\s*\(\s*\))");

    std::string line;
    while (std::getline(file, line))
    {
        std::smatch match;
        if (std::regex_search(line, match, re_int))
        {
            ConstantDecl decl;
            decl.export_name = match[1].str();
            decl.constant_name = match[2].str();
            decl.return_type = "int";
            results.push_back(std::move(decl));
        }
        else if (std::regex_search(line, match, re_str))
        {
            ConstantDecl decl;
            decl.export_name = match[1].str();
            decl.constant_name = match[2].str();
            decl.return_type = "wxString*";
            results.push_back(std::move(decl));
        }
        else if (std::regex_search(line, match, re_const))
        {
            ConstantDecl decl;
            decl.export_name = match[CONST_EXPORT_GROUP].str();
            decl.constant_name = match[CONST_SUFFIX_GROUP].str();
            // Normalize: "const wxColour*" with no space before *
            decl.return_type = "const " + match[2].str() + "*";
            results.push_back(std::move(decl));
        }
    }
    return results;
}
