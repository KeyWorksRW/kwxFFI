/////////////////////////////////////////////////////////////////////////////
// Purpose:   Language-neutral UI descriptor shared by emit-ui and check-ui
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

// The UI descriptor (JSON schema 1) tells a language backend which kwxFFI symbols map to the
// UI idioms a language port needs: how to construct a frame or dialog, how to size and center
// it, how to add children to a sizer, how to bind an event.  It is deliberately language
// neutral — every field is either a target-language symbol or a name from the closed
// vocabularies below — so that the `check-ui` command can validate a real project's IR
// against any backend's descriptor without knowing that backend.
//
// Everything lives in the global namespace to match the rest of kwxgen.

#pragma once

#include "model.h"

#include <filesystem>
#include <map>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

inline constexpr int UI_SCHEMA_VERSION = 1;
inline constexpr std::string_view UI_TOOL_NAME = "kwxgen";
inline constexpr std::string_view UI_TOOL_VERSION = "1.0.0";

struct UiParam
{
    std::string name;
    std::string type;
};

// A single emitted call.  `symbol` is the target-language symbol; an empty symbol means the
// backend cannot express this idiom, and `reason` then explains why.
struct UiCallable
{
    std::string symbol;
    std::vector<UiParam> params;
    std::string idiom;                   // one of the closed idiom vocabulary
    std::optional<std::string> owner;    // method-on-parent only
    std::optional<std::string> returns;  // set when the call yields a new handle
    std::optional<std::string> reason;   // required when symbol is empty
    std::optional<std::map<std::string, std::string>> sentinels;  // ctor only
};

struct UiClass
{
    std::string type;
    std::string idiom;
    UiCallable ctor;
    std::map<std::string, UiCallable> roles;
    std::map<std::string, std::string> constants;
};

struct UiSizerOps
{
    UiCallable ctor;
    UiCallable add_window;
    UiCallable add_sizer;
    UiCallable add_spacer;
};

struct UiFlags
{
    UiCallable ctor;
    UiCallable proportion;
    UiCallable expand;
    UiCallable border;
    UiCallable left;
    UiCallable right;
    UiCallable top;
    UiCallable bottom;
    UiCallable align_h;
    UiCallable align_v;
};

// JSON: {"wxBoxSizer": { ... }, "flags": { ... }}
struct UiSizersBlock
{
    UiSizerOps wx_box_sizer;
    UiFlags flags;
};

struct UiEvents
{
    UiCallable bind;
    UiCallable bind_id;
    std::string handler_type;
};

// JSON key "delete" for delete_fn.
struct UiBitmap
{
    UiCallable from_base64;
    UiCallable get_bitmap;
    UiCallable delete_fn;
};

// JSON key "delete" for delete_fn.
struct UiFont
{
    UiCallable create;
    UiCallable delete_fn;
};

struct UiStdButtons
{
    UiCallable create;
    UiCallable add_button;
    UiCallable realize;
};

struct UiApp
{
    std::string entry;
    std::string entry_signature;
    UiCallable set_top_window;
    bool emit_entry = false;
};

struct UiGeneratedBy
{
    std::string tool;
    std::string version;
    std::string headers_hash;
    std::string profile;
};

// JSON key "class" for class_name.
struct UiUnsupported
{
    std::string class_name;
    std::string role;
    std::string reason;
};

struct UiDescriptor
{
    int schema = UI_SCHEMA_VERSION;
    std::string lang;
    UiGeneratedBy generated_by;
    std::map<std::string, std::string> naming;
    std::map<std::string, UiClass> classes;
    UiSizersBlock sizers;
    UiEvents events;
    UiBitmap bitmap;
    UiFont font;
    UiStdButtons std_buttons;
    UiApp app;
    std::vector<UiUnsupported> unsupported;
};

// -------------------------------------------------------------------------
// Closed vocabularies
// -------------------------------------------------------------------------

const std::vector<std::string_view>& UiRoleVocabulary();
bool UiIsKnownRole(std::string_view role);

const std::vector<std::string_view>& UiIdiomVocabulary();
bool UiIsKnownIdiom(std::string_view idiom);

const std::vector<std::string_view>& UiReasonCodeVocabulary();
bool UiIsKnownReason(std::string_view reason);

const std::vector<std::string_view>& UiRequiredClasses();

// The roles a backend must account for when it supports this class.  Empty when the class is
// not one of the required classes.
const std::vector<std::string_view>& UiRequiredRolesForClass(std::string_view wx_class);

// How emit-ui decides which classes the descriptor describes.
//   Auto  every class in the parsed (already profiled) model
//   Form  exactly UiRequiredClasses() -- the pre-change behaviour
//   File  the class names read from --classes <file>, in file order
enum class UiClassMode
{
    Auto,
    Form,
    File,
};

struct UiClassSelection
{
    UiClassMode mode = UiClassMode::Auto;
    std::vector<std::string> class_names;  // File mode only
};

// Deterministic, de-duplicated class list for a selection.
//   Auto: every non-empty ClassInfo::name in ffi.classes, sorted ascending.
//   Form: UiRequiredClasses() in declaration order.
//   File: class_names in the given order, blanks and duplicates removed; names that are not
//         in ffi.classes are appended to `missing` in the order encountered.
std::vector<std::string> UiResolveClassSelection(const ParsedFFI& ffi,
                                                 const UiClassSelection& selection,
                                                 std::vector<std::string>& missing);

bool UiIsRequiredClass(std::string_view wx_class);

// Every UiRequiredClasses() entry not present in `selected` gets a whole-class
// unsupported entry (empty role) with reason "not_in_profile", so a narrow
// `--classes <file>` selection still produces a descriptor that validates and the
// omission stays visible. No-op for Auto/Form, which always contain all seven.
void UiAccountForRequiredClasses(UiDescriptor& descriptor,
                                 const std::vector<std::string>& selected);

// -------------------------------------------------------------------------
// Header hash and serialization
// -------------------------------------------------------------------------

// Deterministic FNV-1a 64-bit hash (16 lowercase hex chars) over every regular file in
// headers_dir (recursive, sorted by generic relative path) plus defs_file, hashing the
// relative path bytes, a NUL, then the file bytes.
std::string UiHeadersHash(const std::filesystem::path& headers_dir,
                          const std::filesystem::path& defs_file);

// Prettified JSON with no trailing newline.  Returns an empty string when serialization
// fails, which callers must treat as an error.
std::string UiDescriptorToJson(const UiDescriptor& descriptor);

bool UiDescriptorFromJson(const std::string& json, UiDescriptor& out, std::string& error);

bool UiValidateDescriptor(const UiDescriptor& descriptor, std::string& error);

// check-ui entry point: reads both JSON documents, prints MISSING lines to `out`,
// diagnostics to `err`; returns 0 (supported), 2 (at least one MISSING), 1 (usage/parse
// error).  The MISSING lines are "MISSING <lang> <class> <role>".
int UiCheckIr(const std::string& descriptor_json, const std::string& ir_json, std::ostream& out,
              std::ostream& err);

// -------------------------------------------------------------------------
// Lookups shared by the language backends
// -------------------------------------------------------------------------

const ClassInfo* UiFindClass(const ParsedFFI& ffi, std::string_view class_name);

// Searches the class's own methods, then its mixins, then walks the parent chain.  Only
// declarations that pass IsValidFunction() are considered; the first match wins.
const FunctionDecl* UiFindMethod(const ParsedFFI& ffi, std::string_view class_name,
                                 std::string_view method_name);

// Same search order as UiFindMethod, but restricted to a true constructor — a constructor
// whose return type is not TBool.  A TBool constructor is the two-phase Create() pattern.
const FunctionDecl* UiFindConstructor(const ParsedFFI& ffi, std::string_view class_name);

// A class's canonical allocating constructor: the first declaration found by the same search
// order as UiFindConstructor() (own methods, mixins, then ancestors) whose method name is
// exactly "Create" and whose return type is not TBool.  UiFindConstructor() accepts any
// Create* factory, which is right for the hand-written required-class blocks but wrong for
// auto coverage: a name such as wxWindow_CreateAccessible is not a constructor and no backend
// emits it as one.
const FunctionDecl* UiFindCanonicalConstructor(const ParsedFFI& ffi, std::string_view class_name);
