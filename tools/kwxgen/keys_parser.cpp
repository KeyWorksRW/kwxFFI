#include "keys_parser.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

namespace kwxgen
{

    std::vector<KeyDecl> ParseKeys(const std::filesystem::path& filePath)
    {
        std::vector<KeyDecl> results;
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Error: cannot open " << filePath << "\n";
            return results;
        }

        // Matches: "int expK_NAME();"
        std::regex re(R"(^\s*int\s+(expK_(\w+))\s*\(\s*\)\s*;)");
        std::string line;
        while (std::getline(file, line))
        {
            std::smatch m;
            if (std::regex_search(line, m, re))
            {
                KeyDecl decl;
                decl.export_name = m[1].str();      // "expK_BACK"
                decl.key_name = "K_" + m[2].str();  // "K_BACK"
                results.push_back(std::move(decl));
            }
        }
        return results;
    }

}  // namespace kwxgen
