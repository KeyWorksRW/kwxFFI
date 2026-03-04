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
        // kwxffi_gen.f90 — raw C interface declarations
        void GenerateEvents(const std::vector<EventDecl>& events, std::ostream& out);
        void GenerateKeys(const std::vector<KeyDecl>& keys, std::ostream& out);
        void GenerateConstants(const std::vector<ConstantDecl>& constants, std::ostream& out);
        void GenerateClasses(const ParsedFFI& ffi, std::ostream& out);
        void GenerateFreeFunctions(const ParsedFFI& ffi, std::ostream& out);

        // Idiomatic Fortran wrapper modules
        void GenerateTypes(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateStringModule(const std::filesystem::path& outDir);
        void GenerateConstantsModule(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateWindowModule(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateFrameModule(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateControlsModule(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateMenusModule(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateSizersModule(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateEventsModule(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateDialogsModule(const ParsedFFI& ffi, const std::filesystem::path& outDir);
    };

}  // namespace kwxgen
