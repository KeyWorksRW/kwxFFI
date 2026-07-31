/////////////////////////////////////////////////////////////////////////////
// Purpose:   Parse event declarations from source files
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "model.h"

#include <filesystem>
#include <vector>

// Parse kwx_events.h → vector<EventDecl>
// Pattern: "int expEVT_NAME();"
std::vector<EventDecl> ParseEvents(const std::filesystem::path& file_path);
