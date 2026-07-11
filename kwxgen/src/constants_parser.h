/////////////////////////////////////////////////////////////////////////////
// Purpose:   Parse constant and free function definitions
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "model.h"

#include <filesystem>
#include <vector>

struct ConstantsFileResult
{
    std::vector<FunctionDecl> free_functions;  // Null_*, kwxSysErrorCode, etc.
    std::vector<ConstantDecl> constants;       // WXFFI_EXPORT constants (ribbon, gallery)
};

// Parse kwx_constants.h → free functions + inline constants
// Patterns:
//   TClass(wxFoo) Null_Foo();                       → free function
//   int kwxSysErrorCode();                           → free function
//   void LogErrorMsg(TClass(wxString) message);      → free function
//   WXFFI_EXPORT(int, expNAME)();                    → constant
ConstantsFileResult ParseConstants(const std::filesystem::path& file_path);
