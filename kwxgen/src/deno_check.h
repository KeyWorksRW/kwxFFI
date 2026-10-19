/////////////////////////////////////////////////////////////////////////////
// Purpose:   Type-check generated TypeScript bindings with `deno check`
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <filesystem>
#include <string>

struct DenoCheckResult
{
    bool success = false;
    std::string output;  // combined stdout/stderr from `deno check`
};

// Writes a minimal `kwx/platform` compile-time shim and a deno.jsonc import map into
// out_dir.  The shim mirrors the small surface used by generated bindings; it is only
// used when the caller does not supply a real kwxTypeScript deno.jsonc.
void WriteDenoCheckShim(const std::filesystem::path& out_dir);

// Runs `deno check --no-lock --config <config_file> <entry_file>`.
// deno_exe may be a bare command name (resolved via PATH) or a full path.
[[nodiscard]] DenoCheckResult RunDenoCheck(const std::filesystem::path& entry_file,
                                           const std::filesystem::path& config_file,
                                           const std::string& deno_exe);
