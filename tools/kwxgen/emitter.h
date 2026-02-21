#pragma once

#include "model.h"

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace kwxgen
{

    struct VerifyResult
    {
        bool success = true;
        std::vector<std::string> missing_files;
        std::vector<std::string> extra_files;
        std::vector<std::string> mismatched_files;
        std::vector<std::string> messages;
    };

    class LanguageEmitter
    {
    public:
        virtual ~LanguageEmitter() = default;

        // Generate all output files for this language into outDir.
        virtual void Generate(const ParsedFFI& ffi, const std::filesystem::path& outDir) = 0;

        // Verify existing generated files in dir match the current FFI model.
        virtual VerifyResult Verify(const ParsedFFI& ffi, const std::filesystem::path& dir) = 0;

        // Short name of the language backend (e.g., "go", "luajit", "rust").
        virtual std::string_view Name() const = 0;
    };

}  // namespace kwxgen
