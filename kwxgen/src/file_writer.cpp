/////////////////////////////////////////////////////////////////////////////
// Purpose:   ConditionalFileWriter — buffers output, writes only if changed
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "file_writer.h"

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

ConditionalFileWriter::~ConditionalFileWriter()
{
    std::ignore = Flush();
}

bool ConditionalFileWriter::Flush()
{
    if (m_flushed)
    {
        return m_wrote;
    }
    m_flushed = true;

    const std::string content = str();

    // Read the existing file in binary mode so the comparison is byte-exact: a CRLF file
    // left on disk by an earlier build must not compare equal to the LF content below.
    if (std::filesystem::exists(m_path))
    {
        std::ifstream existing(m_path, std::ios::binary);
        if (existing.is_open())
        {
            const std::string old_content((std::istreambuf_iterator<char>(existing)),
                                          std::istreambuf_iterator<char>());
            if (old_content == content)
            {
                return false;  // Unchanged — skip write.
            }
        }
    }

    // Content differs or file is new. Binary mode suppresses newline translation, so the
    // buffered bytes are written verbatim and generated files always use LF.
    std::ofstream file(m_path, std::ios::binary | std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot write " << m_path << "\n";
        return false;
    }
    file << content;
    m_wrote = true;
    return true;
}
