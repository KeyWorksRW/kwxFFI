#pragma once

// Generate platform-specific symbol export files from the parsed FFI model.
// These files allow LuaJIT (and other runtimes that resolve symbols at runtime
// via GetProcAddress/dlsym) to find kwxFFI symbols when the library is
// statically linked into the host executable.
//
// Output files:
//   kwxffi_exports.def  — Windows module-definition file (EXPORTS section)
//   kwxffi_exports.map  — Linux linker version script (global/local)
//   kwxffi_exports.exp  — macOS exported symbols list (leading underscore)

#include "model.h"

#include <filesystem>
#include <string>
#include <vector>

namespace kwxgen
{

    // Collect all C symbol names from the parsed FFI model.
    // Returns a sorted, deduplicated list of every public C function name.
    std::vector<std::string> CollectExportSymbols(const ParsedFFI& ffi);

    // Generate all three platform export files into outDir.
    // Uses ConditionalFileWriter so files are only rewritten when content changes.
    void GenerateExportFiles(const ParsedFFI& ffi, const std::filesystem::path& outDir);

}  // namespace kwxgen
