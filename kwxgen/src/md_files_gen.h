/////////////////////////////////////////////////////////////////////////////
// Purpose:   Generate agent-oriented markdown documentation for all kwxFFI
//            languages from the parsed FFI model data.
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "model.h"

#include <filesystem>

// Generate one .md file per class per language, plus constants.md, events.md,
// and free_functions.md for each of the 7 kwxFFI languages.
// Output goes into out_dir/<lang>-<ClassName>.md etc.
void GenerateAllMarkdownFiles(const ParsedFFI& ffi, const std::filesystem::path& out_dir);
