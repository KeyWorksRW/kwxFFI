#pragma once

#include "../emitter.h"

namespace kwxgen
{

    class JuliaEmitter : public LanguageEmitter
    {
    public:
        void Generate(const ParsedFFI& ffi, const std::filesystem::path& outDir) override;
        VerifyResult Verify(const ParsedFFI& ffi, const std::filesystem::path& dir) override;
        std::string_view Name() const override { return "julia"; }

    private:
        void GenerateEvents(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateKeys(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateConstants(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateClasses(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateFreeFunctions(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateModule(const std::filesystem::path& outDir);
    };

}  // namespace kwxgen
