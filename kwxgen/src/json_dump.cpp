/////////////////////////////////////////////////////////////////////////////
// Purpose:   Dump the parsed FFI model as JSON output
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "json_dump.h"

#include <fstream>
#include <iostream>

#include <glaze/json.hpp>

void DumpJson(const ParsedFFI& parsed_ffi, std::ostream& output)
{
    std::string buffer {};
    const glz::error_ctx errc = glz::write<glz::opts { .prettify = true }>(parsed_ffi, buffer);
    if (errc)
    {
        std::cerr << "Error: JSON serialization failed\n";
        return;
    }
    output << buffer << "\n";
}

bool DumpJsonToFile(const ParsedFFI& parsed_ffi, const std::string& file_path)
{
    std::string buffer {};
    const glz::error_ctx errc = glz::write<glz::opts { .prettify = true }>(parsed_ffi, buffer);
    if (errc)
    {
        std::cerr << "Error: JSON serialization failed\n";
        return false;
    }

    std::ofstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open output file " << file_path << "\n";
        return false;
    }
    file << buffer << "\n";
    return true;
}
