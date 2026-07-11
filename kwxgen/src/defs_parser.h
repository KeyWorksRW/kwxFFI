/////////////////////////////////////////////////////////////////////////////
// Purpose:   Parse C++ type definitions for FFI generation
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "model.h"

#include <filesystem>
#include <vector>

// Parse kwx_defs.cpp → vector<ConstantDecl>
// Patterns:
//   EXPORT int expwxNAME() { return (int) wxNAME; }
//   EXPORT wxString* expwxNAME() { return new wxString(...); }
//   EXPORT const wxColour* expwxNAME() { return wxNAME; }
std::vector<ConstantDecl> ParseDefs(const std::filesystem::path& filePath);
