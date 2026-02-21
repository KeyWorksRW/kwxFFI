#pragma once

#include "emitter.h"

#include <filesystem>
#include <string>
#include <vector>

namespace kwxgen
{

    // Compare generated files in genDir against existing on-disk files in refDir.
    // Returns a VerifyResult indicating which files are missing, extra, or mismatched.
    VerifyResult VerifyGeneratedFiles(const std::filesystem::path& genDir,
                                      const std::filesystem::path& refDir);

}  // namespace kwxgen
