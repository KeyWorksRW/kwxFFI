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

    // Read existing file (text mode — so \r\n → \n on Windows).
    if (std::filesystem::exists(m_path))
    {
        std::ifstream existing(m_path);
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

    // Content differs or file is new — write it out.
    std::ofstream file(m_path);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot write " << m_path << "\n";
        return false;
    }
    file << content;
    m_wrote = true;
    return true;
}
