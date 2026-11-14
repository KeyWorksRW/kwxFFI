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
//     "profile": "gui",
//     "exports": false
// }

#include "class_parser.h"
#include "constants_parser.h"
#include "dedupe.h"
#include "defs_parser.h"
#include "deno_check.h"
#include "emitter.h"
#include "events_parser.h"
#include "exports_gen.h"
#include "json_dump.h"
#include "keys_parser.h"
#include "lang/lang_common.h"
#include "lang/lang_fortran.h"
#include "lang/lang_go.h"
#include "lang/lang_julia.h"
#include "lang/lang_luajit.h"
// #include "lang/lang_perl.h"
#include "lang/lang_rust.h"
#include "lang/lang_typescript.h"
#include "md_files_gen.h"
#include "model.h"
#include "profile.h"
#include "ui_descriptor.h"
#include "verify.h"

#include <algorithm>
#include <array>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <print>
#include <set>
#include <sstream>
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
static constexpr std::string_view CMD_CHECK = "check";
static constexpr std::string_view CMD_EXPORTS = "exports";
static constexpr std::string_view CMD_DIFF = "diff";
static constexpr std::string_view CMD_LANGS = "langs";
static constexpr std::string_view CMD_PROFILES = "profiles";
static constexpr std::string_view CMD_ALL_MD_FILES = "all_md_files";
static constexpr std::string_view CMD_COVERAGE = "coverage";
static constexpr std::string_view CMD_EMIT_UI = "emit-ui";
static constexpr std::string_view CMD_CHECK_UI = "check-ui";

// Argument flags
static constexpr std::string_view ARG_HEADERS = "--headers";
static constexpr std::string_view ARG_DEFS = "--defs";
static constexpr std::string_view ARG_OUT = "--out";
static constexpr std::string_view ARG_LANG = "--lang";
static constexpr std::string_view ARG_DIR = "--dir";
static constexpr std::string_view ARG_MANIFEST = "--manifest";
static constexpr std::string_view ARG_LIBNAME = "--libname";
static constexpr std::string_view ARG_PROFILE = "--profile";
static constexpr std::string_view ARG_EXPORTS_FLAG = "--exports";
static constexpr std::string_view ARG_ALL_MD_FILES = "--amdfiles";
static constexpr std::string_view ARG_DENO = "--deno";
static constexpr std::string_view ARG_DENO_CONFIG = "--deno-config";
static constexpr std::string_view ARG_DENO_LOG = "--deno-log";
static constexpr std::string_view ARG_DENO_CHECK = "--deno-check";
static constexpr std::string_view ARG_RENAME_REPORT = "--rename-report";
static constexpr std::string_view ARG_CONSTANTS_VALUES = "--constants-values";
static constexpr std::string_view ARG_JSON = "--json";
static constexpr std::string_view ARG_INVENTORY = "--inventory";
static constexpr std::string_view ARG_REQUIRE_PARITY = "--require-parity";
static constexpr std::string_view ARG_IR = "--ir";
static constexpr std::string_view ARG_DESCRIPTOR = "--descriptor";
static constexpr std::string_view ARG_VERIFY_FLAG = "--verify";
static constexpr std::string_view ARG_CLASSES = "--classes";
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
    std::println(
        stderr, "  {} check    --headers <dir> --defs <file> [--deno <exe>] [--deno-config <file>]",
        prog_name);
    std::println(stderr, "  Available langs: fortran go julia lua rust typescript");
    std::println(stderr, "  {} exports  --headers <dir> --defs <file> --out <dir>", prog_name);
    std::println(stderr, "  {} diff     --headers <dir> --manifest <file>", prog_name);
    std::println(stderr, "  {} langs", prog_name);
    std::println(stderr, "  {} profiles", prog_name);
    std::println(stderr,
                 "  {} coverage --headers <dir> --defs <file> [--lang <lang>] [--profile <name>] "
                 "[--json <file>] [--inventory <file>] [--require-parity]",
                 prog_name);
    std::println(stderr,
                 "  {} emit-ui  --headers <dir> --defs <file> --lang <lang> [--profile <name>] "
                 "[--classes auto|<file>|form] [--out <file>|-] [--verify]",
                 prog_name);
    std::println(stderr, "  {} check-ui --lang <lang> --ir <file> --descriptor <file>", prog_name);
    std::println(stderr, "");
    std::println(stderr, "Global options (for generate/verify):");
    std::println(
        stderr,
        "  --libname <name>   Runtime shared-library name in generated bindings (default: kwxFFI)");
    std::println(stderr,
                 "  --profile <name>   Surface profile: full or gui (default: full; run "
                 "`{} profiles`)",
                 prog_name);
    std::println(stderr,
                 "  --exports          Also generate platform export files (.def/.map/.exp)");
    std::println(
        stderr,
        "  --deno-check       Run `deno check` on the generated TypeScript output during verify");
    std::println(stderr, "  --deno <exe>       deno executable to use (default: deno)");
    std::println(stderr, "  --deno-config <f>  deno.jsonc import map (default: generated shim)");
    std::println(stderr,
                 "  --deno-log <file>  write the complete deno diagnostic output to <file>");
    std::println(stderr,
                 "  --rename-report <f>  write a JSON report of TypeScript member renames to "
                 "<f>");
    std::println(stderr,
                 "  --constants-values <file>  NAME<TAB>VALUE dump used to emit true `const` "
                 "declarations");
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
    std::string profile;              // --profile (empty means the language default)
    bool exports = false;             // --exports
    std::string deno_exe = "deno";    // --deno
    std::string deno_config;          // --deno-config
    std::string deno_log;             // --deno-log
    std::string rename_report;        // --rename-report (TypeScript only)
    bool deno_check = false;          // --deno-check
    std::string constants_values;     // --constants-values (NAME<TAB>VALUE dump)
    std::string json_path;            // --json (coverage report)
    std::string inventory_path;       // --inventory (coverage Markdown table)
    bool require_parity = false;      // --require-parity (coverage gate)
    std::string ir_path;              // --ir (check-ui project IR)
    std::string descriptor_path;      // --descriptor (check-ui UI descriptor)
    bool verify_ui = false;           // --verify flag for emit-ui
    std::string classes = "auto";     // --classes (emit-ui: auto|<file>|form)
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

// Read one --classes file: one class name per line.  Blank lines and lines whose first
// non-space character is '#' are skipped; a trailing '\r' and surrounding whitespace are
// stripped so a CRLF file from Windows parses the same as an LF file.
[[nodiscard]] static bool ReadClassNamesFile(const std::string& path,
                                             std::vector<std::string>& class_names)
{
    std::ifstream input(path);
    if (!input.is_open())
    {
        std::println(stderr, "Error: cannot read classes file '{}'", path);
        return false;
    }

    std::string line;
    while (std::getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        const size_t first_char = line.find_first_not_of(" \t\v\f");
        if (first_char == std::string::npos)
        {
            continue;
        }
        if (line[first_char] == '#')
        {
            continue;
        }
        const size_t last_char = line.find_last_not_of(" \t\v\f");
        class_names.push_back(line.substr(first_char, (last_char - first_char) + 1));
    }
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
        else if (argument == ARG_PROFILE && i + 1 < argc)
        {
            args.profile = argv[++i];
        }
        else if (argument == ARG_EXPORTS_FLAG)
        {
            args.exports = true;
        }
        else if (argument == ARG_DENO && i + 1 < argc)
        {
            args.deno_exe = argv[++i];
        }
        else if (argument == ARG_DENO_CONFIG && i + 1 < argc)
        {
            args.deno_config = argv[++i];
        }
        else if (argument == ARG_DENO_LOG && i + 1 < argc)
        {
            args.deno_log = argv[++i];
        }
        else if (argument == ARG_DENO_CHECK)
        {
            args.deno_check = true;
        }
        else if (argument == ARG_RENAME_REPORT && i + 1 < argc)
        {
            args.rename_report = argv[++i];
        }
        else if (argument == ARG_CONSTANTS_VALUES && i + 1 < argc)
        {
            args.constants_values = argv[++i];
        }
        else if (argument == ARG_JSON && i + 1 < argc)
        {
            args.json_path = argv[++i];
        }
        else if (argument == ARG_INVENTORY && i + 1 < argc)
        {
            args.inventory_path = argv[++i];
        }
        else if (argument == ARG_REQUIRE_PARITY)
        {
            args.require_parity = true;
        }
        else if (argument == ARG_IR && i + 1 < argc)
        {
            args.ir_path = argv[++i];
        }
        else if (argument == ARG_DESCRIPTOR && i + 1 < argc)
        {
            args.descriptor_path = argv[++i];
        }
        else if (argument == ARG_CLASSES && i + 1 < argc)
        {
            args.classes = argv[++i];
        }
        else if (argument == ARG_VERIFY_FLAG)
        {
            args.verify_ui = true;
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
    emitters.push_back(std::make_unique<RustEmitter>());
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

// Filename suffixes produced by each backend; used by `verify` when comparing a
// generated directory against a reference directory.  Matching on the generated-name
// suffix keeps hand-written files in the same directory out of the comparison.
[[nodiscard]] static std::vector<std::string_view> GeneratedSuffixes(std::string_view lang)
{
    if (lang == "typescript")
    {
        return { "_gen.ts", "kwx_constants_table_gen.cpp" };
    }
    if (lang == "fortran")
    {
        return { ".f90" };
    }
    if (lang == "julia")
    {
        return { ".jl" };
    }
    if (lang == "luajit")
    {
        return { ".lua" };
    }
    // The LuaJIT emitter's Name() is "lua", so `verify --lang lua` reaches this function
    // with "lua" and must not fall through to the Go suffix below.
    if (lang == "lua")
    {
        return { ".lua" };
    }
    if (lang == "rust")
    {
        return { ".rs" };
    }
    return { "_gen.go" };
}

// Write the complete deno output to log_path.  No-op when no log path was requested.
static void WriteDenoLog(const std::string& output, const std::string& log_path)
{
    if (log_path.empty())
    {
        return;
    }
    std::ofstream log_file(log_path, std::ios::binary | std::ios::trunc);
    if (log_file.is_open())
    {
        log_file << output;
        log_file.close();
    }
    else
    {
        std::println(stderr, "  Warning: could not write deno log to {}", log_path);
    }
}

// deno can emit thousands of diagnostic lines; keep terminal output usable.
static void PrintDenoOutput(const std::string& output, const std::string& log_path)
{
    WriteDenoLog(output, log_path);

    static constexpr size_t MAX_DENO_LINES = 200;
    std::istringstream stream(output);
    std::string line;
    size_t line_count = 0;
    while (std::getline(stream, line))
    {
        if (line_count >= MAX_DENO_LINES)
        {
            if (log_path.empty())
            {
                std::println(stderr, "  ... output truncated ...");
            }
            else
            {
                std::println(stderr, "  ... output truncated, full log: {} ...", log_path);
            }
            break;
        }
        std::println(stderr, "  {}", line);
        ++line_count;
    }
}

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

    // Every emitter keys its output on the C symbol name, so the repeats the headers can
    // produce (see dedupe.h) must be gone before any emitter sees the model.  Constant-name
    // collisions are resolved in ApplyProfile(), because the export manifests describe the C
    // library's symbol set and must keep both spellings.
    const std::size_t duplicate_count = RemoveDuplicateFunctions(parsed_ffi);
    if (duplicate_count != 0)
    {
        std::println(stderr, "  Duplicate C symbols skipped: {:L}", duplicate_count);
    }

    return parsed_ffi;
}

// Parse a NAME<TAB>VALUE dump produced by kwx_constants_dump.  Blank lines and lines
// starting with '#' are ignored.  A malformed value is reported with its line number.
[[nodiscard]] static bool LoadConstantsValues(const std::string& path,
                                              std::unordered_map<std::string, long long>& values)
{
    std::ifstream input(path);
    if (!input.is_open())
    {
        std::println(stderr, "Error: cannot open constants values file '{}'", path);
        return false;
    }

    std::string line;
    long line_number = 0;
    while (std::getline(input, line))
    {
        ++line_number;
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        if (line.empty() || line.starts_with('#'))
        {
            continue;
        }

        const size_t tab_pos = line.find('\t');
        if (tab_pos == std::string::npos || tab_pos == 0 || tab_pos + 1 >= line.size())
        {
            std::println(stderr, "Error: {}:{}: malformed line '{}' (expected NAME<TAB>VALUE)",
                         path, line_number, line);
            return false;
        }

        const std::string value_text = line.substr(tab_pos + 1);
        long long value = 0;
        const char* const value_begin = value_text.data();
        const char* const value_end = value_begin + value_text.size();
        const std::from_chars_result parse_result = std::from_chars(value_begin, value_end, value);
        if (parse_result.ec != std::errc() || parse_result.ptr != value_end)
        {
            std::println(stderr, "Error: {}:{}: malformed value '{}'", path, line_number,
                         value_text);
            return false;
        }

        values[line.substr(0, tab_pos)] = value;
    }

    std::println(stderr, "  Constant values: {:L} entries from {}", values.size(), path);
    return true;
}

// Apply --constants-values to a freshly parsed model.  No-op when the flag is absent.
[[nodiscard]] static bool ApplyConstantsValues(const Args& args, ParsedFFI& parsed_ffi)
{
    if (args.constants_values.empty())
    {
        return true;
    }
    return LoadConstantsValues(args.constants_values, parsed_ffi.constant_values);
}

// Resolve the effective profile: an explicit --profile wins, otherwise the language default.
// Prints an error and returns an empty string when the requested profile is unknown.
[[nodiscard]] static std::string ResolveProfile(const Args& args)
{
    std::string profile = args.profile;
    if (profile.empty())
    {
        profile = DefaultProfileForLanguage(args.lang);
        return profile;
    }

    if (!IsKnownProfile(profile))
    {
        std::println(stderr, "Error: unknown profile '{}'", profile);
        std::print(stderr, "Available:");
        for (const std::string_view profile_name: ProfileNames())
        {
            std::print(stderr, " {}", profile_name);
        }
        std::println(stderr, "");
        return {};
    }

    return profile;
}

// -------------------------------------------------------------------------
// Coverage reports
// -------------------------------------------------------------------------

// True when class_name appears in either coverage list.
[[nodiscard]] static bool CoverageHasClass(const CoverageInfo& report,
                                           const std::string& class_name)
{
    return std::ranges::find(report.wrapped_classes, class_name) != report.wrapped_classes.end() ||
           std::ranges::find(report.consumer_provided_classes, class_name) !=
               report.consumer_provided_classes.end();
}

// Number of valid model methods a wrapped class must expose: its own valid methods plus the
// valid methods of every mixin it consumes.
[[nodiscard]] static size_t ModelMethodCount(const std::string& class_name, const ParsedFFI& ffi)
{
    size_t model_count = 0;
    for (const auto& cls: ffi.classes)
    {
        if (cls.name != class_name)
        {
            continue;
        }
        for (const auto& func: cls.methods)
        {
            if (IsValidFunction(func))
            {
                ++model_count;
            }
        }
        break;
    }

    const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
        ffi.mixin_map.find(class_name);
    if (mixin_iter == ffi.mixin_map.end())
    {
        return model_count;
    }
    for (const std::string& mixin_name: mixin_iter->second)
    {
        for (const auto& cls: ffi.classes)
        {
            if (cls.name != mixin_name)
            {
                continue;
            }
            for (const auto& func: cls.methods)
            {
                if (IsValidFunction(func))
                {
                    ++model_count;
                }
            }
            break;
        }
    }
    return model_count;
}

// Sum the per-class method counts in a report.
[[nodiscard]] static size_t CoverageMethodTotal(const CoverageInfo& report)
{
    size_t method_total = 0;
    for (const auto& [class_name, count]: report.method_counts_by_class)
    {
        std::ignore = class_name;
        method_total += count;
    }
    return method_total;
}

// Print one coverage table row per language backend.
static void PrintCoverageTable(const std::vector<std::pair<std::string, CoverageInfo>>& reports)
{
    std::println("{:<11} | {:>7} | {:>8} | {:>7} | {:>7} | {:>4} | {:>6} | {:>4} | {:>9}", "lang",
                 "wrapped", "consumer", "skipped", "methods", "free", "events", "keys",
                 "constants");
    for (const auto& [language, report]: reports)
    {
        std::println("{:<11} | {:>7} | {:>8} | {:>7} | {:>7} | {:>4} | {:>6} | {:>4} | {:>9}",
                     language, report.wrapped_classes.size(),
                     report.consumer_provided_classes.size(), report.skipped_classes.size(),
                     CoverageMethodTotal(report), report.free_function_count, report.event_count,
                     report.key_count, report.constant_count);
    }
}

// Write a deterministic JSON object keyed by language.  Hand-written because the report has a
// small fixed shape and the command must not depend on the model serializer.
[[nodiscard]] static std::string
    CoverageJson(const std::vector<std::pair<std::string, CoverageInfo>>& reports)
{
    std::ostringstream json;
    // The program-local locale adds digit-group separators, which are invalid JSON numbers.
    json.imbue(std::locale::classic());
    json << "{\n";
    bool first_language = true;
    for (const auto& [language, report]: reports)
    {
        json << (first_language ? "" : ",\n");
        first_language = false;
        json << "  \"" << language << "\": {\n";

        const auto write_strings = [&json](const char* key, const std::vector<std::string>& values)
        {
            json << "    \"" << key << "\": [";
            for (size_t i = 0; i < values.size(); ++i)
            {
                if (i != 0)
                {
                    json << ", ";
                }
                json << "\"" << values[i] << "\"";
            }
            json << "],\n";
        };
        write_strings("wrapped_classes", report.wrapped_classes);
        write_strings("consumer_provided_classes", report.consumer_provided_classes);
        write_strings("skipped_classes", report.skipped_classes);

        const auto write_counts =
            [&json](const char* key, const std::map<std::string, size_t>& counts)
        {
            json << "    \"" << key << "\": {";
            bool first_entry = true;
            for (const auto& [name, count]: counts)
            {
                json << (first_entry ? "" : ", ") << "\"" << name << "\": " << count;
                first_entry = false;
            }
            json << "},\n";
        };
        write_counts("method_counts_by_class", report.method_counts_by_class);
        write_counts("deduplicated_method_counts_by_class",
                     report.deduplicated_method_counts_by_class);

        json << "    \"deduplicated_method_count\": " << report.deduplicated_method_count << ",\n";
        json << "    \"free_function_count\": " << report.free_function_count << ",\n";
        json << "    \"event_count\": " << report.event_count << ",\n";
        json << "    \"key_count\": " << report.key_count << ",\n";
        json << "    \"constant_count\": " << report.constant_count << "\n";
        json << "  }";
    }
    json << "\n}\n";
    return json.str();
}

// Write the Markdown inventory: one row per parsed class with a yes/no cell per backend.
[[nodiscard]] static bool
    WriteCoverageInventory(const std::string& path, const ParsedFFI& ffi,
                           const std::vector<std::pair<std::string, CoverageInfo>>& reports)
{
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    if (!output.is_open())
    {
        std::println(stderr, "Error: cannot write inventory '{}'", path);
        return false;
    }
    // The program-local locale adds digit-group separators; the table must stay plain.
    output.imbue(std::locale::classic());

    output << "# kwxgen coverage inventory\n\n";
    output << "Generated by `kwxgen coverage --inventory`. `yes` means the backend wraps the "
              "class or the target runtime provides it.\n\n";
    output << "| class | methods | gui | fortran | go | julia | lua | rust | typescript |\n";
    output << "|---|---|---|---|---|---|---|---|---|\n";

    for (const auto& cls: ffi.classes)
    {
        size_t method_count = 0;
        for (const auto& func: cls.methods)
        {
            if (IsValidFunction(func))
            {
                ++method_count;
            }
        }

        output << "| " << cls.name << " | " << method_count << " | "
               << (IsGuiExcludedClass(cls.name) ? "yes" : "no") << " |";
        for (const auto& [language, report]: reports)
        {
            std::ignore = language;
            output << " " << (CoverageHasClass(report, cls.name) ? "yes" : "no") << " |";
        }
        output << "\n";
    }
    return true;
}

// Compare every language against the TypeScript reference.  Returns true when no class,
// method or symbol is missing; prints each shortfall.
[[nodiscard]] static bool
    CheckCoverageParity(const ParsedFFI& ffi,
                        const std::vector<std::pair<std::string, CoverageInfo>>& reports)
{
    const CoverageInfo* reference = nullptr;
    for (const auto& [language, report]: reports)
    {
        if (language == "typescript")
        {
            reference = &report;
        }
    }
    if (reference == nullptr)
    {
        std::println(stderr, "Error: parity check needs the TypeScript reference report");
        return false;
    }

    bool parity_ok = true;
    for (const auto& [language, report]: reports)
    {
        if (language == "typescript")
        {
            continue;
        }

        for (const std::string& class_name: reference->wrapped_classes)
        {
            if (!CoverageHasClass(report, class_name))
            {
                std::println("  MISSING CLASS  {}: {}", language, class_name);
                parity_ok = false;
                continue;
            }

            const size_t model_count = ModelMethodCount(class_name, ffi);
            size_t wrapped_count = 0;
            const std::map<std::string, size_t>::const_iterator wrapped_iter =
                report.method_counts_by_class.find(class_name);
            if (wrapped_iter != report.method_counts_by_class.end())
            {
                wrapped_count += wrapped_iter->second;
            }
            const std::map<std::string, size_t>::const_iterator collapsed_iter =
                report.deduplicated_method_counts_by_class.find(class_name);
            if (collapsed_iter != report.deduplicated_method_counts_by_class.end())
            {
                wrapped_count += collapsed_iter->second;
            }
            if (wrapped_count < model_count)
            {
                std::println("  METHOD SHORTFALL {}: {} ({} wrapped, {} model)", language,
                             class_name, wrapped_count, model_count);
                parity_ok = false;
            }
        }

        if (report.free_function_count < ffi.free_functions.size())
        {
            std::println("  FREE FUNCTION SHORTFALL {}: {} of {}", language,
                         report.free_function_count, ffi.free_functions.size());
            parity_ok = false;
        }
        if (report.event_count < ffi.events.size())
        {
            std::println("  EVENT SHORTFALL {}: {} of {}", language, report.event_count,
                         ffi.events.size());
            parity_ok = false;
        }
        if (report.key_count < ffi.keys.size())
        {
            std::println("  KEY SHORTFALL {}: {} of {}", language, report.key_count,
                         ffi.keys.size());
            parity_ok = false;
        }
        if (report.constant_count < ffi.constants.size())
        {
            std::println("  CONSTANT SHORTFALL {}: {} of {}", language, report.constant_count,
                         ffi.constants.size());
            parity_ok = false;
        }
    }

    return parity_ok;
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
        if (!ApplyConstantsValues(args, parsed_ffi))
        {
            return 1;
        }

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
        if (!ApplyConstantsValues(args, parsed_ffi))
        {
            return 1;
        }

        const std::string profile = ResolveProfile(args);
        if (profile.empty())
        {
            return 1;
        }

        std::println(stderr, "Generating {} bindings (profile: {})...", args.lang, profile);
        if (args.lang == "typescript")
        {
            SetTypeScriptRenameReportPath(args.rename_report);
        }
        else if (!args.rename_report.empty())
        {
            std::println(stderr,
                         "  Warning: --rename-report is only supported for --lang typescript");
        }
        emitter->Generate(ApplyProfile(parsed_ffi, profile), args.out_path);

        if (args.exports)
        {
            // Export files always describe the complete surface, never a filtered profile.
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
        if (!ApplyConstantsValues(args, parsed_ffi))
        {
            return 1;
        }

        const std::string profile = ResolveProfile(args);
        if (profile.empty())
        {
            return 1;
        }

        std::println(stderr, "Generating to temp dir: {}", temp_dir.string());
        emitter->Generate(ApplyProfile(parsed_ffi, profile), temp_dir);

        // The Julia emitter adds content checks the file diff cannot make (nothing defines an
        // anonymous method, every generated signature is unique).  The other backends leave
        // Verify() unimplemented, so calling it would fail every run.
        VerifyResult content_result;
        if (args.lang == "julia")
        {
            content_result = emitter->Verify(parsed_ffi, temp_dir);
        }

        std::println(stderr, "Verifying against: {}", args.verify_dir);
        VerifyResult verify_result =
            VerifyGeneratedFiles(temp_dir, args.verify_dir, GeneratedSuffixes(args.lang));
        if (!content_result.success)
        {
            verify_result.success = false;
        }
        verify_result.messages.insert(verify_result.messages.end(), content_result.messages.begin(),
                                      content_result.messages.end());

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

        if (args.deno_check)
        {
            if (args.lang != "typescript")
            {
                std::println(stderr, "Error: --deno-check is only supported for --lang typescript");
                std::ignore = fs::remove_all(temp_dir);
                return 1;
            }

            fs::path deno_config = args.deno_config;
            if (deno_config.empty())
            {
                WriteDenoCheckShim(temp_dir);
                deno_config = temp_dir / "deno.jsonc";
            }

            std::println(stderr, "Running deno check...");
            const DenoCheckResult deno_result =
                RunDenoCheck(temp_dir / "kwx_gen.ts", deno_config, args.deno_exe);
            if (deno_result.success)
            {
                WriteDenoLog(deno_result.output, args.deno_log);
                std::println("Deno check: OK");
            }
            else
            {
                verify_result.success = false;
                std::println("Deno check: FAILED");
                PrintDenoOutput(deno_result.output, args.deno_log);
            }
        }

        // Clean up temp dir
        std::ignore = fs::remove_all(temp_dir);

        return verify_result.success ? 0 : 1;
    }

    if (args.command == CMD_CHECK)
    {
        if (args.headers_dir.empty() || args.defs_file.empty())
        {
            std::println(stderr, "Error: 'check' requires --headers and --defs");
            return 1;
        }
        if (!args.lang.empty() && args.lang != "typescript")
        {
            std::println(stderr, "Error: 'check' only supports --lang typescript");
            return 1;
        }

        std::println(stderr, "Parsing...");
        ParsedFFI parsed_ffi = RunParsers(args.headers_dir, args.defs_file);
        parsed_ffi.lib_name = args.lib_name;
        if (!ApplyConstantsValues(args, parsed_ffi))
        {
            return 1;
        }

        const std::string profile = ResolveProfile(args);
        if (profile.empty())
        {
            return 1;
        }

        // Generate into a temp directory so the caller's tree is untouched.
        const fs::path temp_dir = fs::temp_directory_path() / "kwxgen_check";
        std::ignore = fs::remove_all(temp_dir);
        std::ignore = fs::create_directories(temp_dir);

        std::println(stderr, "Generating TypeScript bindings to temp dir: {}", temp_dir.string());
        TypeScriptEmitter emitter;
        emitter.Generate(ApplyProfile(parsed_ffi, profile), temp_dir);

        fs::path deno_config = args.deno_config;
        if (deno_config.empty())
        {
            WriteDenoCheckShim(temp_dir);
            deno_config = temp_dir / "deno.jsonc";
        }

        std::println(stderr, "Running deno check...");
        const DenoCheckResult deno_result =
            RunDenoCheck(temp_dir / "kwx_gen.ts", deno_config, args.deno_exe);
        if (deno_result.success)
        {
            WriteDenoLog(deno_result.output, args.deno_log);
            std::println("Deno check: OK");
        }
        else
        {
            std::println("Deno check: FAILED");
            PrintDenoOutput(deno_result.output, args.deno_log);
        }

        std::ignore = fs::remove_all(temp_dir);
        return deno_result.success ? 0 : 1;
    }

    if (args.command == CMD_COVERAGE)
    {
        if (args.headers_dir.empty() || args.defs_file.empty())
        {
            std::println(stderr, "Error: 'coverage' requires --headers and --defs");
            return 1;
        }

        // The default is the language default only when --lang selects a backend; a report
        // over every backend always describes the full surface.
        std::string profile = args.profile;
        if (profile.empty())
        {
            profile =
                args.lang.empty() ? std::string("full") : DefaultProfileForLanguage(args.lang);
        }
        if (!IsKnownProfile(profile))
        {
            std::println(stderr, "Error: unknown profile '{}'", profile);
            return 1;
        }

        const std::vector<std::unique_ptr<LanguageEmitter>> emitters = CreateEmitters();
        std::vector<const LanguageEmitter*> selected;
        if (args.lang.empty())
        {
            for (const auto& emitter: emitters)
            {
                selected.push_back(emitter.get());
            }
        }
        else
        {
            const LanguageEmitter* const emitter = FindEmitter(emitters, args.lang);
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
            selected.push_back(emitter);
        }

        std::println(stderr, "Parsing...");
        ParsedFFI parsed_ffi = RunParsers(args.headers_dir, args.defs_file);
        parsed_ffi.lib_name = args.lib_name;
        if (!ApplyConstantsValues(args, parsed_ffi))
        {
            return 1;
        }
        const ParsedFFI profiled_ffi = ApplyProfile(parsed_ffi, profile);

        std::vector<std::pair<std::string, CoverageInfo>> reports;
        for (const LanguageEmitter* const emitter: selected)
        {
            reports.emplace_back(std::string(emitter->Name()), emitter->Coverage(profiled_ffi));
        }

        // The parity gate always needs the TypeScript reference, even when --lang picked
        // exactly one other backend.
        if (args.require_parity && args.lang != "typescript")
        {
            bool has_reference = false;
            for (const auto& [language, report]: reports)
            {
                std::ignore = report;
                if (language == "typescript")
                {
                    has_reference = true;
                }
            }
            if (!has_reference)
            {
                const std::vector<std::unique_ptr<LanguageEmitter>> all_emitters = CreateEmitters();
                if (const LanguageEmitter* const reference_emitter =
                        FindEmitter(all_emitters, "typescript"))
                {
                    reports.emplace_back("typescript", reference_emitter->Coverage(profiled_ffi));
                }
            }
        }

        std::println(stderr, "");
        PrintCoverageTable(reports);

        if (!args.json_path.empty())
        {
            std::ofstream json_output(args.json_path, std::ios::binary | std::ios::trunc);
            if (!json_output.is_open())
            {
                std::println(stderr, "Error: cannot write JSON report '{}'", args.json_path);
                return 1;
            }
            json_output << CoverageJson(reports);
            std::println(stderr, "Coverage JSON written to {}", args.json_path);
        }

        if (!args.inventory_path.empty())
        {
            if (!WriteCoverageInventory(args.inventory_path, profiled_ffi, reports))
            {
                return 1;
            }
            std::println(stderr, "Coverage inventory written to {}", args.inventory_path);
        }

        if (!args.require_parity)
        {
            return 0;
        }

        std::println("");
        std::println("Parity check against the TypeScript reference (profile: {}):", profile);
        if (CheckCoverageParity(profiled_ffi, reports))
        {
            std::println("Coverage parity: OK");
            return 0;
        }
        std::println("Coverage parity: FAILED");
        return 1;
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
        if (!ApplyConstantsValues(args, parsed_ffi))
        {
            return 1;
        }

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
        if (!args.profile.empty())
        {
            std::println(stderr,
                         "Error: 'exports' always emits the complete surface; --profile is not "
                         "supported");
            return 1;
        }

        std::println(stderr, "Parsing...");
        ParsedFFI parsed_ffi = RunParsers(args.headers_dir, args.defs_file);
        parsed_ffi.lib_name = args.lib_name;
        if (!ApplyConstantsValues(args, parsed_ffi))
        {
            return 1;
        }

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

    if (args.command == CMD_PROFILES)
    {
        std::println("Available profiles:");
        for (const std::string_view profile_name: ProfileNames())
        {
            std::println("  {}", profile_name);
        }
        std::println("\nDefault profile per language:");
        static constexpr std::array<std::string_view, 6> LANGS { "fortran", "go",   "julia",
                                                                 "luajit",  "rust", "typescript" };
        for (const std::string_view lang: LANGS)
        {
            std::println("  {:<11} {}", lang, DefaultProfileForLanguage(lang));
        }
        return 0;
    }

    if (args.command == CMD_EMIT_UI)
    {
        if (args.headers_dir.empty() || args.defs_file.empty())
        {
            std::println(stderr, "Error: 'emit-ui' requires --headers and --defs");
            return 1;
        }
        if (args.lang.empty())
        {
            std::println(stderr, "Error: 'emit-ui' requires --lang");
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
        if (!ApplyConstantsValues(args, parsed_ffi))
        {
            return 1;
        }

        // emit-ui defaults to the gui profile: a descriptor exists to describe the classes a
        // UI layer needs.  The other commands keep their own defaults.
        Args emit_args = args;
        if (emit_args.profile.empty())
        {
            emit_args.profile = "gui";
        }
        const std::string profile = ResolveProfile(emit_args);
        if (profile.empty())
        {
            return 1;
        }

        UiClassSelection selection;
        if (args.classes == "auto")
        {
            selection.mode = UiClassMode::Auto;
        }
        else if (args.classes == "form")
        {
            selection.mode = UiClassMode::Form;
        }
        else
        {
            selection.mode = UiClassMode::File;
            if (!ReadClassNamesFile(args.classes, selection.class_names))
            {
                return 1;
            }
        }

        const ParsedFFI profiled_ffi = ApplyProfile(parsed_ffi, profile);

        std::vector<std::string> missing;
        const std::vector<std::string> selected =
            UiResolveClassSelection(profiled_ffi, selection, missing);
        if (!missing.empty())
        {
            std::string missing_list;
            for (const std::string& class_name: missing)
            {
                if (!missing_list.empty())
                {
                    missing_list += ", ";
                }
                missing_list += class_name;
            }
            std::println(stderr, "Error: --classes file names unknown classes: {}", missing_list);
            return 1;
        }

        emitter->SetUiClassSelection(selection);
        UiDescriptor descriptor = emitter->BuildUiDescriptor(profiled_ffi);
        descriptor.schema = UI_SCHEMA_VERSION;
        descriptor.lang = std::string(emitter->Name());
        descriptor.generated_by =
            UiGeneratedBy { .tool = std::string(UI_TOOL_NAME),
                            .version = std::string(UI_TOOL_VERSION),
                            .headers_hash = UiHeadersHash(args.headers_dir, args.defs_file),
                            .profile = profile };

        UiAccountForRequiredClasses(descriptor, selected);

        std::string validate_error;
        if (!UiValidateDescriptor(descriptor, validate_error))
        {
            std::println(stderr, "Error: invalid descriptor: {}", validate_error);
            return 1;
        }

        const std::string json = UiDescriptorToJson(descriptor);
        if (json.empty())
        {
            std::println(stderr, "Error: descriptor JSON serialization failed");
            return 1;
        }
        const std::string document = json + "\n";

        if (args.out_path.empty() || args.out_path == STDOUT_MARKER)
        {
            std::cout << document;
            std::cout.flush();
        }
        else
        {
            std::ofstream output(args.out_path, std::ios::binary | std::ios::trunc);
            if (!output.is_open())
            {
                std::println(stderr, "Error: cannot open output file '{}'", args.out_path);
                return 1;
            }
            output << document;
        }

        std::println(stderr, "Emitted {} classes for {} ({} unsupported)",
                     descriptor.classes.size(), descriptor.lang, descriptor.unsupported.size());

        if (!args.verify_ui)
        {
            return 0;
        }

        const fs::path temp_dir = fs::temp_directory_path() / ("kwxgen_emit_ui_" + args.lang);
        std::ignore = fs::remove_all(temp_dir);
        std::ignore = fs::create_directories(temp_dir);

        // The contract for --verify is that the emitter is run into the temp dir first; the
        // backend's VerifyUiDescriptor only inspects that output.
        emitter->Generate(profiled_ffi, temp_dir);

        const std::vector<std::string> mismatches =
            emitter->VerifyUiDescriptor(descriptor, temp_dir);

        std::ignore = fs::remove_all(temp_dir);

        for (const std::string& mismatch: mismatches)
        {
            std::println(stderr, "{}", mismatch);
        }
        return mismatches.empty() ? 0 : 1;
    }

    if (args.command == CMD_CHECK_UI)
    {
        if (args.lang.empty())
        {
            std::println(stderr, "Error: 'check-ui' requires --lang");
            return 1;
        }
        if (args.ir_path.empty() || args.descriptor_path.empty())
        {
            std::println(stderr, "Error: 'check-ui' requires --ir and --descriptor");
            return 1;
        }

        std::ifstream ir_input(args.ir_path, std::ios::binary);
        if (!ir_input.is_open())
        {
            std::println(stderr, "Error: cannot read IR file '{}'", args.ir_path);
            return 1;
        }
        std::ostringstream ir_buffer;
        ir_buffer << ir_input.rdbuf();

        std::ifstream descriptor_input(args.descriptor_path, std::ios::binary);
        if (!descriptor_input.is_open())
        {
            std::println(stderr, "Error: cannot read descriptor file '{}'", args.descriptor_path);
            return 1;
        }
        std::ostringstream descriptor_buffer;
        descriptor_buffer << descriptor_input.rdbuf();

        const std::string descriptor_json = descriptor_buffer.str();

        // The language selector must agree with the descriptor, otherwise the MISSING lines
        // would be attributed to the wrong backend.
        UiDescriptor descriptor;
        std::string parse_error;
        if (!UiDescriptorFromJson(descriptor_json, descriptor, parse_error))
        {
            std::println(stderr, "Error: {}", parse_error);
            return 1;
        }
        if (descriptor.lang != args.lang)
        {
            std::println(stderr, "Error: descriptor language '{}' does not match --lang '{}'",
                         descriptor.lang, args.lang);
            return 1;
        }

        return UiCheckIr(descriptor_json, ir_buffer.str(), std::cout, std::cerr);
    }

    std::println(stderr, "Unknown command: {}", args.command);
    PrintUsage(argv[0]);
    return 1;
}
