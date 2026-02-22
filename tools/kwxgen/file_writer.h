#pragma once

// ConditionalFileWriter — a drop-in replacement for std::ofstream that buffers
// all output in memory and only writes the file to disk if the content differs
// from what is already there.  This avoids unnecessary file-system writes that
// trigger downstream rebuilds (e.g., CMake custom-command stamps, Go compiler).

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace kwxgen
{

    class ConditionalFileWriter : public std::ostringstream
    {
    public:
        explicit ConditionalFileWriter(std::filesystem::path path) : m_path(std::move(path)) {}

        ~ConditionalFileWriter() { Flush(); }

        // Non-copyable, non-movable (owns a pending write).
        ConditionalFileWriter(const ConditionalFileWriter&) = delete;
        ConditionalFileWriter& operator=(const ConditionalFileWriter&) = delete;

        // Compatibility with the std::ofstream error-check pattern:
        //   if (!out.is_open()) { ... }
        // Always returns true because we buffer in an ostringstream.
        bool is_open() const { return true; }

        // Compare buffered content with existing file and write only if different.
        // Returns true if the file was (re)written.
        bool Flush()
        {
            if (m_flushed)
                return m_wrote;
            m_flushed = true;

            auto content = str();

            // Read existing file (text mode — so \r\n → \n on Windows).
            if (std::filesystem::exists(m_path))
            {
                std::ifstream existing(m_path);
                if (existing.is_open())
                {
                    std::string old((std::istreambuf_iterator<char>(existing)),
                                    std::istreambuf_iterator<char>());
                    if (old == content)
                        return false;  // Unchanged — skip write.
                }
            }

            // Content differs or file is new — write it out.
            std::ofstream out(m_path);
            if (!out.is_open())
            {
                std::cerr << "Error: cannot write " << m_path << "\n";
                return false;
            }
            out << content;
            m_wrote = true;
            return true;
        }

        bool WasWritten() const { return m_wrote; }

    private:
        std::filesystem::path m_path;
        bool m_flushed = false;
        bool m_wrote = false;
    };

}  // namespace kwxgen
