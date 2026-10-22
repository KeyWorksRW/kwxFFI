/////////////////////////////////////////////////////////////////////////////
// Purpose:   Common text parsing utility functions
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

// Parser utility functions shared between class_parser.cpp and constants_parser.cpp.
// Provides the canonical implementations of Trim, ParseMacroType, SplitParams, ParseOneParam,
// and ExpandLocalIncludes.

#include "model.h"

#include <filesystem>
#include <set>
#include <string>
#include <vector>

// Trim leading and trailing whitespace from a string.
std::string Trim(const std::string& text);

// Parse a macro-wrapped type like "TClass(wxWindow)" into macro_name and macro_arg.
// Returns true if it matched a macro form (e.g. TClass, TSelf, TPoint, TRect, TArrayString).
// On failure, clears both macro_name and macro_arg and returns false.
[[nodiscard]] bool ParseMacroType(const std::string& type, std::string& macro_name,
                                  std::string& macro_arg);

// Split a parameter list string by commas, respecting parenthesized groups.
// "TClass(wxImage) src, int flags" → ["TClass(wxImage) src", "int flags"]
std::vector<std::string> SplitParams(const std::string& param_str);

// Parse a single parameter token like "TClass(wxWindow) parent" or "int flags" into a Param.
Param ParseOneParam(const std::string& token);

// Replace every quoted `#include "name"` line in `lines` with the contents of the included file,
// resolved relative to `file_path.parent_path()`, and recurse into that file's own quoted
// includes. `visited` holds canonicalized paths already expanded and breaks include cycles;
// expansion stops at depth 8. Angle-bracket includes, kwx_types.h, kwx_def.h, and kwx_wrapper.h
// are never expanded, and a missing file leaves the original line unchanged.
void ExpandLocalIncludes(std::vector<std::string>& lines, const std::filesystem::path& file_path,
                         std::set<std::filesystem::path>& visited, int depth);
