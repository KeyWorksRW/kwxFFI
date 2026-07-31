/////////////////////////////////////////////////////////////////////////////
// Purpose:   Entry point for the kwxgen FFI code generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

// Require C++23 or later — all major compilers are covered:
//   MSVC uses _MSVC_LANG (more reliable than __cplusplus without /Zc:__cplusplus)
//   GCC, Clang, and others use __cplusplus
#if defined(_MSVC_LANG)
    #if _MSVC_LANG < 202302L
        #error "C++23 or later is required to build this project. Please upgrade your compiler."
    #endif
#elif (__cplusplus < 202101L)
    #error "C++23 or later is required to build this project. Please upgrade your compiler."
#endif

// Example kwxgen.config.json (all fields are optional; command-line args override):
//
// {
//     "command": "generate",
//     "headers_dir": "../kwxFFI/include",
//     "defs_file": "../kwxFFI/kwx_defs.h",
//     "out_path": "./generated",
//     "verify_dir": "./reference",
//     "manifest_file": "./manifest.json",
//     "lib_name": "kwxFFI",
//     "exports": false
// }

#include "class_parser.h"
#include "constants_parser.h"
#include "defs_parser.h"
#include "emitter.h"
#include "events_parser.h"
#include "exports_gen.h"
#include "json_dump.h"
#include "keys_parser.h"
#include "lang/lang_fortran.h"
#include "lang/lang_go.h"
#include "lang/lang_julia.h"
#include "lang/lang_luajit.h"
// #include "lang/lang_perl.h"
#include "lang/lang_typescript.h"
#include "md_files_gen.h"
#include "model.h"
#include "verify.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <print>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

#include <glaze/json.hpp>

namespace fs = std::filesystem;

// Command names
static constexpr std::string_view CMD_PARSE = "parse";
static constexpr std::string_view CMD_GENERATE = "generate";
static constexpr std::string_view CMD_VERIFY = "verify";
static constexpr std::string_view CMD_EXPORTS = "exports";
static constexpr std::string_view CMD_DIFF = "diff";
static constexpr std::string_view CMD_LANGS = "langs";
static constexpr std::string_view CMD_ALL_MD_FILES = "all_md_files";

// Argument flags
static constexpr std::string_view ARG_HEADERS = "--headers";
static constexpr std::string_view ARG_DEFS = "--defs";
static constexpr std::string_view ARG_OUT = "--out";
static constexpr std::string_view ARG_LANG = "--lang";
static constexpr std::string_view ARG_DIR = "--dir";
static constexpr std::string_view ARG_MANIFEST = "--manifest";
static constexpr std::string_view ARG_LIBNAME = "--libname";
static constexpr std::string_view ARG_EXPORTS_FLAG = "--exports";
static constexpr std::string_view ARG_ALL_MD_FILES = "--amdfiles";
static constexpr std::string_view STDOUT_MARKER = "-";

static void PrintUsage(const char* prog_name)
{
    std::println(stderr, "Usage:");
    std::println(stderr, "  {} parse    --headers <dir> --defs <file> [--out <file>]", prog_name);
    std::println(
        stderr, "  {} generate --headers <dir> --defs <file> --lang <lang> --out <dir> [--exports]",
        prog_name);
    std::println(stderr, "  {} verify   --headers <dir> --defs <file> --lang <lang> --dir <dir>",
                 prog_name);
    std::println(stderr, "  Available langs: fortran go julia lua typescript");
    std::println(stderr, "  {} exports  --headers <dir> --defs <file> --out <dir>", prog_name);
    std::println(stderr, "  {} diff     --headers <dir> --manifest <file>", prog_name);
    std::println(stderr, "  {} langs", prog_name);
    std::println(stderr, "");
    std::println(stderr, "Global options (for generate/verify):");
    std::println(
        stderr,
        "  --libname <name>   Runtime shared-library name in generated bindings (default: kwxFFI)");
    std::println(stderr,
                 "  --exports          Also generate platform export files (.def/.map/.exp)");
}

struct Args
{
    std::string command;
    std::string headers_dir;
    std::string defs_file;
    std::string out_path;  // file for parse, dir for generate
    std::string lang;
    std::string verify_dir;
    std::string manifest_file;
    std::string lib_name = "kwxFFI";  // --libname
    bool exports = false;             // --exports
};

static constexpr std::string_view CONFIG_FILE_NAME = "kwxgen.config.json";

// Load Args from kwxgen.config.json in the current directory (if it exists).
// Returns false only on parse errors; a missing config file is not an error.
static bool LoadConfigFile(Args& args)
{
    const fs::path config_path = fs::current_path() / CONFIG_FILE_NAME;
    if (!fs::exists(config_path))
    {
        return true;
    }

    std::string buffer;
    const glz::error_ctx errc = glz::read_file_json<glz::opts { .error_on_unknown_keys = false }>(
        args, config_path.string(), buffer);
    if (errc)
    {
        std::println(stderr, "Error reading {}: {}", config_path.string(),
                     glz::format_error(errc, buffer));
        return false;
    }

    std::println(stderr, "Loaded config from {}", config_path.string());
    return true;
}

[[nodiscard]] static bool ParseArgs(int argc, char* argv[], Args& args)
{
    if (argc < 2)
    {
        // If a config file already set the command, no command-line args are needed.
        return !args.command.empty();
    }

    args.command = argv[1];
    if (args.command == ARG_ALL_MD_FILES)
    {
        args.command = CMD_ALL_MD_FILES;
    }

    for (int i = 2; i < argc; ++i)
    {
        const std::string argument = argv[i];
        if (argument == ARG_HEADERS && i + 1 < argc)
        {
            args.headers_dir = argv[++i];
        }
        else if (argument == ARG_DEFS && i + 1 < argc)
        {
            args.defs_file = argv[++i];
        }
        else if (argument == ARG_OUT && i + 1 < argc)
        {
            args.out_path = argv[++i];
        }
        else if (argument == ARG_LANG && i + 1 < argc)
        {
            args.lang = argv[++i];
        }
        else if (argument == ARG_DIR && i + 1 < argc)
        {
            args.verify_dir = argv[++i];
        }
        else if (argument == ARG_MANIFEST && i + 1 < argc)
        {
            args.manifest_file = argv[++i];
        }
        else if (argument == ARG_LIBNAME && i + 1 < argc)
        {
            args.lib_name = argv[++i];
        }
        else if (argument == ARG_EXPORTS_FLAG)
        {
            args.exports = true;
        }
        else if (argument == ARG_ALL_MD_FILES)
        {
            // Override command — generate all markdown docs instead of code
            args.command = CMD_ALL_MD_FILES;
        }
        else
        {
            std::println(stderr, "Unknown argument: {}", argument);
            return false;
        }
    }
    return true;
}

// -------------------------------------------------------------------------
// Emitter registry
// -------------------------------------------------------------------------

static std::vector<std::unique_ptr<LanguageEmitter>> CreateEmitters()
{
    std::vector<std::unique_ptr<LanguageEmitter>> emitters;
    emitters.push_back(std::make_unique<FortranEmitter>());
    emitters.push_back(std::make_unique<GoEmitter>());
    emitters.push_back(std::make_unique<JuliaEmitter>());
    emitters.push_back(std::make_unique<LuaJITEmitter>());
    // emitters.push_back(std::make_unique<PerlEmitter>());
    emitters.push_back(std::make_unique<TypeScriptEmitter>());
    return emitters;
}

static LanguageEmitter* FindEmitter(const std::vector<std::unique_ptr<LanguageEmitter>>& emitters,
                                    const std::string& name)
{
    for (const auto& emitter: emitters)
    {
        if (emitter->Name() == name)
        {
            return emitter.get();
        }
    }
    return nullptr;
}

// -------------------------------------------------------------------------
// Parsers
// -------------------------------------------------------------------------

static ParsedFFI RunParsers(const fs::path& headers_dir, const fs::path& defs_file)
{
    ParsedFFI parsed_ffi;

    // Parse events
    const fs::path events_file = headers_dir / "kwx_events.h";
    if (fs::exists(events_file))
    {
        parsed_ffi.events = ParseEvents(events_file);
        std::println(stderr, "  Events:         {:L}", parsed_ffi.events.size());
    }
    else
    {
        std::println(stderr, "  Warning: {} not found", events_file.string());
    }

    // Parse keys
    const fs::path keys_file = headers_dir / "kwx_keys.h";
    if (fs::exists(keys_file))
    {
        parsed_ffi.keys = ParseKeys(keys_file);
        std::println(stderr, "  Keys:           {:L}", parsed_ffi.keys.size());
    }
    else
    {
        std::println(stderr, "  Warning: {} not found", keys_file.string());
    }

    // Parse defs constants
    if (fs::exists(defs_file))
    {
        parsed_ffi.constants = ParseDefs(defs_file);
        std::println(stderr, "  Defs constants: {:L}", parsed_ffi.constants.size());
    }
    else
    {
        std::println(stderr, "  Warning: {} not found", defs_file.string());
    }

    // Parse constants header (free functions + WXFFI_EXPORT constants)
    const fs::path constants_file = headers_dir / "kwx_constants.h";
    if (fs::exists(constants_file))
    {
        ConstantsFileResult constants_result = ParseConstants(constants_file);
        parsed_ffi.free_functions = std::move(constants_result.free_functions);
        // Merge WXFFI_EXPORT constants into the constants list
        for (auto& constant: constants_result.constants)
        {
            parsed_ffi.constants.push_back(std::move(constant));
        }
        std::println(stderr, "  Free functions: {:L}", parsed_ffi.free_functions.size());
        std::println(stderr, "  Header consts:  {:L} (merged into constants total: {:L})",
                     constants_result.constants.size(), parsed_ffi.constants.size());
    }
    else
    {
        std::println(stderr, "  Warning: {} not found", constants_file.string());
    }

    // Parse classes
    const fs::path classes_file = headers_dir / "kwx_classes.h";
    if (fs::exists(classes_file))
    {
        ClassParseResult classes_result = ParseClasses(classes_file);
        parsed_ffi.classes = std::move(classes_result.classes);
        parsed_ffi.parent_map = std::move(classes_result.parent_map);
        parsed_ffi.mixin_map = std::move(classes_result.mixin_map);
        // Merge any free functions (e.g., expPROPSHEET_*) found embedded in kwx_classes.h
        for (auto& func: classes_result.free_functions)
        {
            parsed_ffi.free_functions.push_back(std::move(func));
        }
    }
    else
    {
        std::println(stderr, "  Warning: {} not found", classes_file.string());
    }

    return parsed_ffi;
}

int main(int argc, char* argv[])
{
    Args args;
    std::locale::global(std::locale(""));
    std::ignore = LoadConfigFile(args);
    if (!ParseArgs(argc, argv, args))
    {
        PrintUsage(argc > 0 ? argv[0] : "kwxgen");
        return 1;
    }

    if (args.command == CMD_PARSE)
    {
        if (args.headers_dir.empty() || args.defs_file.empty())
        {
            std::println(stderr, "Error: 'parse' requires --headers and --defs");
            return 1;
        }

        std::println(stderr, "Parsing...");
        ParsedFFI parsed_ffi = RunParsers(args.headers_dir, args.defs_file);
        parsed_ffi.lib_name = args.lib_name;

        // See json_dump.h for a description of why one might want to dump the parsed FFI as JSON.

        if (args.out_path.empty() || args.out_path == STDOUT_MARKER)
        {
            DumpJson(parsed_ffi, std::cout);
        }
        else
        {
            if (!DumpJsonToFile(parsed_ffi, args.out_path))
            {
                return 1;
            }
            std::println(stderr, "JSON written to {}", args.out_path);
        }
        return 0;
    }

    if (args.command == CMD_GENERATE)
    {
        if (args.headers_dir.empty() || args.defs_file.empty())
        {
            std::println(stderr, "Error: 'generate' requires --headers and --defs");
            return 1;
        }
        if (args.lang.empty())
        {
            std::println(stderr, "Error: 'generate' requires --lang");
            return 1;
        }
        if (args.out_path.empty())
        {
            std::println(stderr, "Error: 'generate' requires --out");
            return 1;
        }

        const std::vector<std::unique_ptr<LanguageEmitter>> emitters = CreateEmitters();
        LanguageEmitter* const emitter = FindEmitter(emitters, args.lang);
        if (!emitter)
        {
            std::println(stderr, "Error: unknown language '{}'", args.lang);
            std::print(stderr, "Available:");
            for (const auto& entry: emitters)
            {
                std::print(stderr, " {}", entry->Name());
            }
            std::println(stderr, "");
            return 1;
        }

        std::println(stderr, "Parsing...");
        ParsedFFI parsed_ffi = RunParsers(args.headers_dir, args.defs_file);
        parsed_ffi.lib_name = args.lib_name;

        std::println(stderr, "Generating {} bindings...", args.lang);
        emitter->Generate(parsed_ffi, args.out_path);

        if (args.exports)
        {
            GenerateExportFiles(parsed_ffi, args.out_path);
        }

        return 0;
    }

    if (args.command == CMD_VERIFY)
    {
        if (args.headers_dir.empty() || args.defs_file.empty())
        {
            std::println(stderr, "Error: 'verify' requires --headers and --defs");
            return 1;
        }
        if (args.lang.empty())
        {
            std::println(stderr, "Error: 'verify' requires --lang");
            return 1;
        }
        if (args.verify_dir.empty())
        {
            std::println(stderr, "Error: 'verify' requires --dir");
            return 1;
        }

        const std::vector<std::unique_ptr<LanguageEmitter>> emitters = CreateEmitters();
        LanguageEmitter* const emitter = FindEmitter(emitters, args.lang);
        if (!emitter)
        {
            std::println(stderr, "Error: unknown language '{}'", args.lang);
            return 1;
        }

        // Generate into a temp directory, then compare with the reference dir
        const fs::path temp_dir = fs::temp_directory_path() / "kwxgen_verify";
        std::ignore = fs::remove_all(temp_dir);
        std::ignore = fs::create_directories(temp_dir);

        std::println(stderr, "Parsing...");
        ParsedFFI parsed_ffi = RunParsers(args.headers_dir, args.defs_file);
        parsed_ffi.lib_name = args.lib_name;

        std::println(stderr, "Generating to temp dir: {}", temp_dir.string());
        emitter->Generate(parsed_ffi, temp_dir);

        std::println(stderr, "Verifying against: {}", args.verify_dir);
        const VerifyResult verify_result = VerifyGeneratedFiles(temp_dir, args.verify_dir);

        if (verify_result.success)
        {
            std::println("Verify: OK \u2014 all generated files match.");
        }
        else
        {
            std::println("Verify: DIFFERENCES FOUND");
            for (const auto& message: verify_result.messages)
            {
                std::println("  {}", message);
            }
            if (!verify_result.missing_files.empty())
            {
                std::println("  Missing files in generated output:");
                for (const auto& file_path: verify_result.missing_files)
                {
                    std::println("    {}", file_path);
                }
            }
            if (!verify_result.extra_files.empty())
            {
                std::println("  Extra files in generated output:");
                for (const auto& file_path: verify_result.extra_files)
                {
                    std::println("    {}", file_path);
                }
            }
            if (!verify_result.mismatched_files.empty())
            {
                std::println("  Mismatched files:");
                for (const auto& file_path: verify_result.mismatched_files)
                {
                    std::println("    {}", file_path);
                }
            }
        }

        // Clean up temp dir
        std::ignore = fs::remove_all(temp_dir);

        return verify_result.success ? 0 : 1;
    }

    if (args.command == CMD_ALL_MD_FILES)
    {
        if (args.headers_dir.empty() || args.defs_file.empty())
        {
            std::println(stderr, "Error: '{}' requires --headers and --defs", CMD_ALL_MD_FILES);
            return 1;
        }
        if (args.out_path.empty())
        {
            std::println(stderr, "Error: '{}' requires --out", CMD_ALL_MD_FILES);
            return 1;
        }

        std::println(stderr, "Parsing...");
        ParsedFFI parsed_ffi = RunParsers(args.headers_dir, args.defs_file);

        std::println(stderr, "Generating agent markdown documentation...");
        GenerateAllMarkdownFiles(parsed_ffi, args.out_path);

        return 0;
    }

    if (args.command == CMD_EXPORTS)
    {
        if (args.headers_dir.empty() || args.defs_file.empty())
        {
            std::println(stderr, "Error: 'exports' requires --headers and --defs");
            return 1;
        }
        if (args.out_path.empty())
        {
            std::println(stderr, "Error: 'exports' requires --out");
            return 1;
        }

        std::println(stderr, "Parsing...");
        ParsedFFI parsed_ffi = RunParsers(args.headers_dir, args.defs_file);
        parsed_ffi.lib_name = args.lib_name;

        GenerateExportFiles(parsed_ffi, args.out_path);
        return 0;
    }

    if (args.command == CMD_DIFF)
    {
        std::println(stderr, "Error: 'diff' is not yet implemented");
        return 1;
    }

    if (args.command == CMD_LANGS)
    {
        const std::vector<std::unique_ptr<LanguageEmitter>> emitters = CreateEmitters();
        std::println("Available language backends:");
        for (const auto& emitter: emitters)
        {
            std::println("  {}", emitter->Name());
        }
        return 0;
    }

    std::println(stderr, "Unknown command: {}", args.command);
    PrintUsage(argv[0]);
    return 1;
}
