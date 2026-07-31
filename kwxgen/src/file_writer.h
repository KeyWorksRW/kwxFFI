/////////////////////////////////////////////////////////////////////////////
// Purpose:   ConditionalFileWriter — buffers output, writes only if changed
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

// ConditionalFileWriter — a drop-in replacement for std::ofstream that buffers
// all output in memory and only writes the file to disk if the content differs
// from what is already there.  This avoids unnecessary file-system writes that
// trigger downstream rebuilds (e.g., CMake custom-command stamps, Go compiler).

#include <filesystem>
#include <sstream>

class ConditionalFileWriter : public std::ostringstream
{
public:
    explicit ConditionalFileWriter(std::filesystem::path path) : m_path(std::move(path)) {}

    ~ConditionalFileWriter();

    // Non-copyable, non-movable (owns a pending write).
    ConditionalFileWriter(const ConditionalFileWriter&) = delete;
    ConditionalFileWriter& operator=(const ConditionalFileWriter&) = delete;

    // Compatibility with the std::ofstream error-check pattern:
    //   if (!out.is_open()) { ... }
    // Always returns true because we buffer in an ostringstream.
    [[nodiscard]] bool is_open() const { return true; }

    // Compare buffered content with existing file and write only if different.
    // Returns true if the file was (re)written.
    [[nodiscard]] bool Flush();

    [[nodiscard]] bool WasWritten() const { return m_wrote; }

private:
    std::filesystem::path m_path;
    bool m_flushed = false;
    bool m_wrote = false;
};
