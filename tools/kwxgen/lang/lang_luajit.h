#pragma once

#include "../emitter.h"

namespace kwxgen
{

    class LuaJITEmitter : public LanguageEmitter
    {
    public:
        void Generate(const ParsedFFI& ffi, const std::filesystem::path& outDir) override;
        VerifyResult Verify(const ParsedFFI& ffi, const std::filesystem::path& dir) override;
        auto Name() const -> std::string_view override { return "luajit"; }

    private:
        // Raw FFI layer: ffi.cdef declarations for all C functions
        void GenerateEvents(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateKeys(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateConstants(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateClasses(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateFreeFunctions(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void GenerateInit(const std::filesystem::path& outDir, const std::string& libName);

        // Idiomatic layer: per-class Lua modules with metatables and method wrappers
        void GenerateHelpers(const std::filesystem::path& outDir);
        void GenerateIdiomaticClasses(const ParsedFFI& ffi, const std::filesystem::path& outDir);
        void EmitIdiomaticClassFile(std::ostream& out, const ClassInfo& cls, const ParsedFFI& ffi);
    };

}  // namespace kwxgen
