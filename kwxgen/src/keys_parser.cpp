/////////////////////////////////////////////////////////////////////////////
// Purpose:   Parse keyboard key definitions from source files
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "keys_parser.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::vector<KeyDecl> ParseKeys(const std::filesystem::path& file_path)
{
    std::vector<KeyDecl> results;
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open " << file_path << "\n";
        return results;
    }

    // Matches: "int expK_NAME();"
    const std::regex key_regex(R"(^\s*int\s+(expK_(\w+))\s*\(\s*\)\s*;)");
    std::string line;
    while (std::getline(file, line))
    {
        std::smatch match;
        if (std::regex_search(line, match, key_regex))
        {
            KeyDecl decl;
            decl.export_name = match[1].str();      // "expK_BACK"
            decl.key_name = "K_" + match[2].str();  // "K_BACK"
            results.push_back(std::move(decl));
        }
    }
    return results;
}
