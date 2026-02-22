#pragma once

#include "../emitter.h"

namespace kwxgen
{

    class RustEmitter : public LanguageEmitter
    {
    public:
        void Generate(const ParsedFFI& ffi, const std::filesystem::path& outDir) override;
        VerifyResult Verify(const ParsedFFI& ffi, const std::filesystem::path& dir) override;
        std::string_view Name() const override { return "rust"; }

    private:
        void GenerateCargoToml(const std::filesystem::path& outDir);
        void GenerateSys(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
        void GenerateTraits(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
        void GenerateEvents(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
        void GenerateKeys(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
        void GenerateConstants(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
        void GenerateFreeFunctions(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
        void GenerateClassFiles(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
        void GenerateLib(const ParsedFFI& ffi, const std::filesystem::path& srcDir);

        // Emit a single class safe wrapper file.
        void EmitClassFile(std::ostream& out, const ClassInfo& cls, const ParsedFFI& ffi);
    };

}  // namespace kwxgen
