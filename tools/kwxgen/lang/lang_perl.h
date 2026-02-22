#pragma once

#include "../emitter.h"

namespace kwxgen
{

    class PerlEmitter : public LanguageEmitter
    {
    public:
        void Generate(const ParsedFFI& ffi, const std::filesystem::path& outDir) override;
        VerifyResult Verify(const ParsedFFI& ffi, const std::filesystem::path& dir) override;
        std::string_view Name() const override { return "perl"; }

    private:
        void GenerateEvents(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateKeys(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateConstants(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateClasses(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateFreeFunctions(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateInit(const std::filesystem::path& outDir);
    };

}  // namespace kwxgen
