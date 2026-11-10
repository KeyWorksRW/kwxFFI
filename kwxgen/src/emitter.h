/////////////////////////////////////////////////////////////////////////////
// Purpose:   Base class for language-specific code emitters
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "model.h"

#include <cstddef>
#include <filesystem>
#include <map>
#include <string>
#include <string_view>
#include <vector>

struct VerifyResult
{
    bool success = true;
    std::vector<std::string> missing_files;
    std::vector<std::string> extra_files;
    std::vector<std::string> mismatched_files;
    std::vector<std::string> messages;
};

// What a backend actually wraps, as reported by the `coverage` command.
//
// wrapped_classes are the classes the backend emits a wrapper for, named exactly as the
// C++ model names them.  consumer_provided_classes are the classes the generated code
// deliberately omits because the target runtime supplies an equivalent (hand-maintained
// types, kSkipStruct types).  skipped_classes are parsed classes the backend leaves out.
//
// method_counts_by_class counts the valid model methods that reach the backend's wrapper
// output, while deduplicated_method_counts_by_class counts the methods that were collapsed
// into an already-emitted wrapper (the same member name or the same C symbol).  The two
// maps together must account for every valid model method of a wrapped class, including
// its mixin methods, which is what the parity check enforces.
struct CoverageInfo
{
    std::vector<std::string> wrapped_classes;
    std::vector<std::string> consumer_provided_classes;
    std::vector<std::string> skipped_classes;
    std::map<std::string, size_t> method_counts_by_class;
    std::map<std::string, size_t> deduplicated_method_counts_by_class;
    size_t deduplicated_method_count = 0;
    size_t free_function_count = 0;
    size_t event_count = 0;
    size_t key_count = 0;
    size_t constant_count = 0;
};

class LanguageEmitter
{
public:
    virtual ~LanguageEmitter() = default;

    // Generate all output files for this language into outDir.
    virtual void Generate(const ParsedFFI& ffi, const std::filesystem::path& outDir) = 0;

    // Verify existing generated files in dir match the current FFI model.
    virtual VerifyResult Verify(const ParsedFFI& ffi, const std::filesystem::path& dir) = 0;

    // Short name of the language backend (e.g., "go", "luajit").
    virtual std::string_view Name() const = 0;

    // Report which classes, methods and symbols this backend wraps.  The default report is
    // empty, which the coverage command shows as zero coverage.
    virtual CoverageInfo Coverage(const ParsedFFI& /* ffi */) const { return CoverageInfo {}; }
};
