#pragma once

#include "model.h"

#include <filesystem>
#include <vector>

namespace kwxgen
{

    // Parse kwx_events.h → vector<EventDecl>
    // Pattern: "int expEVT_NAME();"
    std::vector<EventDecl> ParseEvents(const std::filesystem::path& filePath);

}  // namespace kwxgen
