#pragma once

#include "model.h"

#include <filesystem>
#include <vector>

namespace kwxgen
{

    // Parse kwx_keys.h → vector<KeyDecl>
    // Pattern: "int expK_NAME();"
    std::vector<KeyDecl> ParseKeys(const std::filesystem::path& filePath);

}  // namespace kwxgen
