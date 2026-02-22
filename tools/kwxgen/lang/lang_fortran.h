#pragma once

#include "../emitter.h"

namespace kwxgen
{

    class FortranEmitter : public LanguageEmitter
    {
    public:
        void Generate(const ParsedFFI& ffi, const std::filesystem::path& outDir) override;
        VerifyResult Verify(const ParsedFFI& ffi, const std::filesystem::path& dir) override;
        std::string_view Name() const override { return "fortran"; }

    private:
        void GenerateEvents(const ParsedFFI& ffi, std::ostream& out);
        void GenerateKeys(const ParsedFFI& ffi, std::ostream& out);
        void GenerateConstants(const ParsedFFI& ffi, std::ostream& out);
        void GenerateClasses(const ParsedFFI& ffi, std::ostream& out);
        void GenerateFreeFunctions(const ParsedFFI& ffi, std::ostream& out);
    };

}  // namespace kwxgen
