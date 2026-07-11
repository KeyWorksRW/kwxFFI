/////////////////////////////////////////////////////////////////////////////
// Purpose:   Verify generated output files against expected content
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "verify.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <locale>
#include <set>
#include <sstream>

namespace fs = std::filesystem;

static std::string ReadFileContents(const fs::path& path)
{
    const std::ifstream input_file(path, std::ios::binary);
    if (!input_file.is_open())
    {
        return std::string {};
    }
    std::ostringstream content_stream;
    content_stream << input_file.rdbuf();
    return content_stream.str();
}

VerifyResult VerifyGeneratedFiles(const fs::path& gen_dir, const fs::path& ref_dir)
{
    VerifyResult result;

    if (!fs::exists(gen_dir))
    {
        result.success = false;
        result.messages.push_back("Generated directory does not exist: " + gen_dir.string());
        return result;
    }

    if (!fs::exists(ref_dir))
    {
        result.success = false;
        result.messages.push_back("Reference directory does not exist: " + ref_dir.string());
        return result;
    }

    // Collect filenames in each directory (non-recursive, *.go files only)
    std::set<std::string> gen_files;
    std::set<std::string> ref_files;

    for (const auto& entry: fs::directory_iterator(gen_dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".go")
        {
            gen_files.insert(entry.path().filename().string());
        }
    }

    for (const auto& entry: fs::directory_iterator(ref_dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".go")
        {
            ref_files.insert(entry.path().filename().string());
        }
    }

    // Files in genDir but not in refDir
    for (const auto& file_name: gen_files)
    {
        if (!ref_files.contains(file_name))
        {
            result.extra_files.push_back(file_name);
        }
    }

    // Files in refDir but not in genDir
    for (const auto& file_name: ref_files)
    {
        if (!gen_files.contains(file_name))
        {
            result.missing_files.push_back(file_name);
        }
    }

    // Files in both — compare content
    for (const auto& file_name: gen_files)
    {
        if (ref_files.contains(file_name))
        {
            const std::string gen_content = ReadFileContents(gen_dir / file_name);
            const std::string ref_content = ReadFileContents(ref_dir / file_name);
            if (gen_content != ref_content)
            {
                result.mismatched_files.push_back(file_name);
            }
        }
    }

    result.success = result.missing_files.empty() && result.extra_files.empty() &&
                     result.mismatched_files.empty();

    if (!result.success)
    {
        static const std::locale user_locale("");
        if (!result.missing_files.empty())
        {
            result.messages.push_back(std::format(user_locale,
                                                  "Missing {:L} file(s) in generated output",
                                                  result.missing_files.size()));
        }
        if (!result.extra_files.empty())
        {
            result.messages.push_back(std::format(
                user_locale, "Extra {:L} file(s) in generated output", result.extra_files.size()));
        }
        if (!result.mismatched_files.empty())
        {
            result.messages.push_back(std::format(user_locale, "{:L} file(s) differ from reference",
                                                  result.mismatched_files.size()));
        }
    }

    return result;
}
