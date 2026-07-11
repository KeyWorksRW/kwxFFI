/////////////////////////////////////////////////////////////////////////////
// Purpose:   Common text parsing utility functions
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

// Parser utility functions shared between class_parser.cpp and constants_parser.cpp.
// Provides the canonical implementations of Trim, ParseMacroType, SplitParams, ParseOneParam.

#include "model.h"

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
