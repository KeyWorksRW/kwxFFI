#include "events_parser.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace kwxgen
{

    std::vector<EventDecl> ParseEvents(const std::filesystem::path& filePath)
    {
        std::vector<EventDecl> results;
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Error: cannot open " << filePath << "\n";
            return results;
        }

        // Matches: "int expEVT_NAME();"
        std::regex re(R"(^\s*int\s+(expEVT_(\w+))\s*\(\s*\)\s*;)");
        std::string line;
        while (std::getline(file, line))
        {
            std::smatch m;
            if (std::regex_search(line, m, re))
            {
                EventDecl decl;
                decl.export_name = m[1].str();          // "expEVT_BUTTON"
                decl.event_name = "EVT_" + m[2].str();  // "EVT_BUTTON"
                results.push_back(std::move(decl));
            }
        }
        return results;
    }

}  // namespace kwxgen
