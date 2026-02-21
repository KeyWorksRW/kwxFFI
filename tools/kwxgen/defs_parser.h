#pragma once

#include "model.h"

#include <filesystem>
#include <vector>

namespace kwxgen
{

    // Parse kwx_defs.cpp → vector<ConstantDecl>
    // Patterns:
    //   EXPORT int expwxNAME() { return (int) wxNAME; }
    //   EXPORT wxString* expwxNAME() { return new wxString(...); }
    //   EXPORT const wxColour* expwxNAME() { return wxNAME; }
    std::vector<ConstantDecl> ParseDefs(const std::filesystem::path& filePath);

}  // namespace kwxgen
