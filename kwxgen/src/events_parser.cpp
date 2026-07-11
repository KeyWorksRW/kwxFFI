/////////////////////////////////////////////////////////////////////////////
// Purpose:   Parse event declarations from source files
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "events_parser.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::vector<EventDecl> ParseEvents(const std::filesystem::path& file_path)
{
    std::vector<EventDecl> results;
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open " << file_path << "\n";
        return results;
    }

    // Matches both event export forms:
    //   int exp_wxEVT_NAME();                    (normal wx events)
    //   WXFFI_EXPORT(int, exp_wxEVT_NAME)();     (normal — WXFFI form)
    //   WXFFI_EXPORT(int, exp_EVT_NAME)();       (non-wx events: ribbon etc.)
    // Group 1 = full export_name ("exp_wxEVT_BUTTON" or "exp_EVT_RIBBONBAR_*")
    // Group 2 = EVT_ suffix      ("EVT_BUTTON")  => event_name = group2 (no "wx" prefix)
    const std::regex event_regex(
        R"(^\s*(?:int|WXFFI_EXPORT\s*\(\s*int\s*,)\s*(exp_(?:wx)?(EVT_\w+))\s*\)?\s*\(\s*\)\s*;)");
    std::string line;
    while (std::getline(file, line))
    {
        std::smatch match;
        if (std::regex_search(line, match, event_regex))
        {
            EventDecl decl;
            decl.export_name = match[1].str();  // "exp_wxEVT_BUTTON" / "exp_EVT_RIBBONBAR_*"
            decl.event_name = match[2].str();   // "EVT_BUTTON" / "EVT_RIBBONBAR_*"
            results.push_back(std::move(decl));
        }
    }
    return results;
}
