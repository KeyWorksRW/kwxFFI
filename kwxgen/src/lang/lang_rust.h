/////////////////////////////////////////////////////////////////////////////
// Purpose:   Rust FFI code generator with safe wrappers
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../emitter.h"

#include <memory>

class RustEmitter : public LanguageEmitter
{
public:
    void Generate(const ParsedFFI& ffi, const std::filesystem::path& outDir) override;
    [[nodiscard]] VerifyResult Verify(const ParsedFFI& ffi,
                                      const std::filesystem::path& dir) override;
    [[nodiscard]] std::string_view Name() const override { return "rust"; }
    [[nodiscard]] CoverageInfo Coverage(const ParsedFFI& ffi) const override;

    UiDescriptor BuildUiDescriptor(const ParsedFFI& parsed_ffi) const override;
    std::vector<std::string>
        VerifyUiDescriptor(const UiDescriptor& descriptor,
                           const std::filesystem::path& generated_dir) const override;

private:
    // Set by BuildUiDescriptor so VerifyUiDescriptor can regenerate the crate into the
    // temporary directory emit-ui hands it; it receives no FFI of its own.
    mutable std::shared_ptr<const ParsedFFI> ui_ffi;

    static void GenerateCargoToml(const std::filesystem::path& outDir);
    static void GenerateSys(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
    static void GenerateObject(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
    static void GenerateSupport(const std::filesystem::path& srcDir);
    static void GenerateTraits(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
    static void GenerateEvents(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
    static void GenerateKeys(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
    static void GenerateConstants(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
    static void GenerateFreeFunctions(const ParsedFFI& ffi, const std::filesystem::path& srcDir);
    // Writes one file per class and records the module name of each written file.
    static void GenerateClassFiles(const ParsedFFI& ffi, const std::filesystem::path& srcDir,
                                   std::vector<std::string>& classModules);
    static void GenerateLib(const ParsedFFI& ffi, const std::filesystem::path& srcDir,
                            const std::vector<std::string>& classModules);

    // Emit a single class safe wrapper file.
    static void EmitClassFile(std::ostream& out, const ClassInfo& cls, const ParsedFFI& ffi);
};
