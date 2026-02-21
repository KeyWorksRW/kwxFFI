#pragma once

#include "model.h"

#include <ostream>
#include <string>

namespace kwxgen
{

    // Serialize ParsedFFI to JSON on the given output stream.
    void DumpJson(const ParsedFFI& ffi, std::ostream& out);

    // Serialize ParsedFFI to JSON and write to a file. Returns true on success.
    bool DumpJsonToFile(const ParsedFFI& ffi, const std::string& filePath);

}  // namespace kwxgen
