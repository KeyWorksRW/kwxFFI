/////////////////////////////////////////////////////////////////////////////
// Purpose:   Verify generated output files against expected content
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <filesystem>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "emitter.h"

// Compare generated files in genDir against existing on-disk files in refDir.
// Only files whose name ends with one of the suffixes is considered, so hand-written
// files that share the output directory are ignored.
// Returns a VerifyResult indicating which files are missing, extra, or mismatched.
VerifyResult VerifyGeneratedFiles(const std::filesystem::path& gen_dir,
                                  const std::filesystem::path& ref_dir,
                                  std::span<const std::string_view> suffixes);
