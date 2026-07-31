/////////////////////////////////////////////////////////////////////////////
// Purpose:   Parse keyboard key definitions from source files
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "model.h"

#include <filesystem>
#include <vector>

// Parse kwx_keys.h → vector<KeyDecl>
// Pattern: "int expK_NAME();"
std::vector<KeyDecl> ParseKeys(const std::filesystem::path& file_path);
