#pragma once

#include "../emitter.h"

namespace kwxgen
{

    class GoEmitter : public LanguageEmitter
    {
    public:
        void Generate(const ParsedFFI& ffi, const std::filesystem::path& outDir) override;
        VerifyResult Verify(const ParsedFFI& ffi, const std::filesystem::path& dir) override;
        std::string_view Name() const override { return "go"; }

    private:
        void GenerateHelpers(const std::filesystem::path& outDir);
        void GenerateConstants(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateEvents(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateKeys(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateClassFiles(const ParsedFFI& ffi, const std::filesystem::path& outDir);

        // Emit a single class file: classname_gen.go
        void EmitClassFile(std::ostream& out, const ClassInfo& cls, const ParsedFFI& ffi);
    };

}  // namespace kwxgen
