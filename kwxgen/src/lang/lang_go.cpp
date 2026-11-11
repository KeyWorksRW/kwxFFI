/////////////////////////////////////////////////////////////////////////////
// Purpose:   Go/CGo FFI code generator
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see ../LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "lang_go.h"

#include "../file_writer.h"
#include "lang_common.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <print>
#include <sstream>
#include <tuple>
#include <vector>

// NOLINTBEGIN(readability-magic-string)

namespace fs = std::filesystem;

constexpr std::size_t COMMENT_BANNER_WIDTH = 70;

// -------------------------------------------------------------------------
// File header / preamble helpers
// -------------------------------------------------------------------------

constexpr size_t kFixedFileCount =
    7;  // cgo_glue, helpers, constants, events, event_types, keys, functions

// Determine the Go type expression for a constant's return type.
// Returns the Go wrapper around the C call, e.g., "int(C.expwxFOO())"
// or "unsafe.Pointer(C.expwxFOO())".
static std::string GoConstantExpr(const ConstantDecl& decl)
{
    return "cgo_" + decl.export_name + "()";
}

// -----------------------------------------------------------------
// Class generation helpers
// -----------------------------------------------------------------

// Strip common prefixes for Go type names:
//   "wxButton"       → "Button"       (strip 'wx')
//   "wxNewFoo"       → "WxNewFoo"     (keep prefix when stripped name starts with 'New'
//                                       to avoid collision with NewFoo() constructor fns)
//   "kwxDropTarget"  → "KwxDropTarget" (capitalize 'kwx' — do NOT strip it, or kwx*
//                                       classes collide with their wx* counterparts)
static std::string StripPrefix(const std::string& name)
{
    if (name.starts_with(WX_PREFIX) &&
        std::isupper(static_cast<unsigned char>(name[WX_PREFIX.length()])))
    {
        const std::string stripped = name.substr(WX_PREFIX.length());
        // If stripping 'wx' leaves a name starting with 'New', it will collide
        // with NewFoo() constructor functions emitted for other wx* classes.
        // e.g. wxNewBitmapButton → keep as WxNewBitmapButton.
        if (stripped.starts_with("New"))
        {
            return "Wx" + stripped;
        }
        return stripped;
    }
    // kwx* classes: capitalize to "Kwx" rather than stripping, so that
    // kwxDropTarget → KwxDropTarget ≠ DropTarget (from wxDropTarget).
    if (name.starts_with(KWX_PREFIX) &&
        std::isupper(static_cast<unsigned char>(name[KWX_PREFIX.length()])))
    {
        return "Kwx" + name.substr(KWX_PREFIX.length());
    }
    return name;
}

// Go filename: "wxButton" -> "button_gen.go"
// Only strip the "wx" prefix -- kwx classes keep their prefix to
// avoid collisions (e.g. kwxDropTarget vs wxDropTarget).
static std::string GoFileName(const std::string& class_name)
{
    std::string stripped = class_name;
    if (class_name.starts_with(WX_PREFIX) &&
        std::isupper(static_cast<unsigned char>(class_name[WX_PREFIX.length()])))
    {
        stripped = class_name.substr(WX_PREFIX.length());
    }
    return ToLower(stripped) + "_gen.go";
}

// Classes already hand-defined in the Go module (wx/types.go).  Generating them
// would redeclare the type, so they are skipped.
//
// These are consumer-provided: the Go module supplies them, so the coverage report
// counts them as covered rather than missing.  The C accessors the module calls
// (wxSize_GetWidth and friends) still come from the generated glue.
static const std::unordered_set<std::string> kHandMaintainedClasses = {
    "wxPoint",
    "wxSize",
    "wxRect",
};

// Package-level functions already hand-defined in the Go module (wx/app.go).
// A generated free function with one of these names would be a redeclaration, so they
// are skipped.  They are consumer-provided and count as covered in the coverage report.
static const std::unordered_set<std::string> kHandMaintainedFreeFunctions = {
    "Bell",
    "InitAllImageHandlers",
    "SafeYield",
    "Yield",
};

[[nodiscard]] static bool IsFixedGoGeneratedFile(const std::string& filename)
{
    return filename == "cgo_glue_gen.go" || filename == "helpers_gen.go" ||
           filename == "constants_gen.go" || filename == "events_gen.go" ||
           filename == "event_types_gen.go" || filename == "keys_gen.go" ||
           filename == "functions_gen.go";
}

[[nodiscard]] static bool EndsWith(const std::string& value, const std::string& suffix)
{
    if (value.size() < suffix.size())
    {
        return false;
    }
    return value.ends_with(suffix);
}

static size_t RemoveStaleGoClassFiles(const fs::path& out_dir,
                                      const std::unordered_set<std::string>& expected_class_files)
{
    if (!fs::exists(out_dir))
    {
        return 0;
    }

    size_t removed = 0;
    for (const auto& entry: fs::directory_iterator(out_dir))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }

        const std::string filename = entry.path().filename().string();
        if (!EndsWith(filename, "_gen.go"))
        {
            continue;
        }
        if (IsFixedGoGeneratedFile(filename))
        {
            continue;
        }
        if (expected_class_files.contains(filename))
        {
            continue;
        }

        std::error_code errc;
        std::ignore = fs::remove(entry.path(), errc);
        if (errc)
        {
            std::println(stderr, "Warning: failed to remove stale generated file {}: {}",
                         entry.path().string(), errc.message());
        }
        else
        {
            ++removed;
        }
    }

    return removed;
}

// Receiver variable: uniform "o" to avoid name collisions with parameter names.
constexpr const char* kReceiverVar = "o";
// Go reserved keywords that cannot be used as parameter names.
// Returns a safe replacement, or the original name if not a keyword.
static std::string RenameGoKeyword(const std::string& name)
{
    static const std::unordered_map<std::string, std::string> keywords = {
        { "type", "typ" },        { "select", "sel" }, { "range", "rng" },
        { "map", "mp" },          { "func", "fn" },    { "var", "v" },
        { "chan", "ch" },         { "go", "g" },       { "defer", "deferVal" },
        { "switch", "sw" },       { "case", "cs" },    { "default", "def" },
        { "interface", "iface" }, { "struct", "st" },  { "package", "pkg" },
        { "import", "imp" },      { "return", "ret" }, { "break", "brk" },
        { "continue", "cont" },   { "for", "loop" },   { "if", "cond" },
        { "else", "alt" },        { "goto", "jmp" },   { "fallthrough", "ft" },
    };
    const std::unordered_map<std::string, std::string>::const_iterator iter = keywords.find(name);
    return (iter != keywords.end()) ? iter->second : name;
}

// Ensure a Go identifier doesn't start with a digit (illegal in Go).
// e.g. "3STATE" → "X3STATE"
static std::string SafeGoIdentifier(const std::string& name)
{
    if (!name.empty() && std::isdigit(static_cast<unsigned char>(name[0])))
    {
        return "X" + name;
    }
    return RenameGoKeyword(name);
}

// Split comma-separated macro arg: "x, y" → {"x", "y"}
static std::vector<std::string> SplitMacroArg(const std::string& macro_arg)
{
    std::vector<std::string> parts;
    std::istringstream stream(macro_arg);
    std::string part;
    while (std::getline(stream, part, ','))
    {
        const size_t start = part.find_first_not_of(" \t");
        const size_t end_pos = part.find_last_not_of(" \t");
        if (start != std::string::npos)
        {
            parts.push_back(part.substr(start, end_pos - start + 1));
        }
    }
    return parts;
}

struct GoParam
{
    std::string name;           // Go parameter name
    std::string go_type;        // Go type in class-file signature
    std::string cgo_expr;       // Expression to pass to the C call (used in glue body)
    std::string pre_call;       // Statement before call in class file
    std::string defer_call;     // Defer statement in class file
    bool needs_unsafe = false;  // Class file needs "unsafe" import for this param
    // Glue-layer overrides (empty strings → default to go_type / name)
    std::string glue_go_type;    // Type in glue function signature (empty → go_type)
    std::string glue_pass_expr;  // Expression in class body for glue call (empty → name)
    std::string glue_pre;        // Pre-call statement in glue body
    std::string glue_defer;      // Defer statement in glue body
};

// Capitalize first letter of a string
static std::string Capitalize(const std::string& text)
{
    if (text.empty())
    {
        return text;
    }
    std::string result = text;
    result[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[0])));
    return result;
}

// True when a non-constructor method's first parameter is TClass(ClassName) for the
// method's own class. Mixin interfaces (wxTextEntry, wxItemContainer, wxComboPopup)
// declare their receiver this way instead of TSelf, so it is the receiver for those
// methods. Constructors are excluded: their first parameter is never the receiver.
[[nodiscard]] static bool IsPseudoSelf(const FunctionDecl& func_decl)
{
    if (func_decl.is_constructor || func_decl.has_self || func_decl.class_name.empty() ||
        func_decl.params.empty())
    {
        return false;
    }
    const Param& first_param = func_decl.params.front();
    return first_param.macro_name == "TClass" && first_param.macro_arg == func_decl.class_name;
}

// Rename a parameter that would shadow the emitted function's receiver argument.
// `reserved_name` is "o" in class files and "self" in the cgo glue functions.
[[nodiscard]] static std::string ParamName(const std::string& name,
                                           const std::string& reserved_name)
{
    std::string result = RenameGoKeyword(name);
    if (!reserved_name.empty() && result == reserved_name)
    {
        result += "Value";
    }
    return result;
}

// Return the cgo scalar name for a single-indirection C pointer parameter:
// "const unsigned char*" -> "uchar". Returns an empty string when cgo has no
// scalar name for the element type (void*, or pointer-to-pointer); the caller
// then passes the Go unsafe.Pointer through unchanged.
[[nodiscard]] static std::string CgoScalarNameFor(const std::string& raw_type)
{
    const std::size_t begin = raw_type.find_first_not_of(" \t");
    if (begin == std::string::npos)
    {
        return {};
    }
    const std::size_t end = raw_type.find_last_not_of(" \t");
    std::string type = raw_type.substr(begin, end - begin + 1);

    // Only a single level of indirection is mapped; "char**" has no scalar name.
    if (!type.ends_with('*') || type.ends_with("**"))
    {
        return {};
    }
    type.pop_back();
    const std::size_t name_end = type.find_last_not_of(" \t");
    if (name_end == std::string::npos)
    {
        return {};
    }
    type.resize(name_end + 1);

    for (const std::string_view qualifier: { "const", "volatile" })
    {
        if (!type.starts_with(qualifier))
        {
            continue;
        }
        const std::size_t after = type.find_first_not_of(" \t", qualifier.size());
        if (after == std::string::npos)
        {
            return {};
        }
        type = type.substr(after);
    }

    if (type == "unsigned char")
    {
        return "uchar";
    }
    if (type == "signed char")
    {
        return "schar";
    }
    if (type == "char")
    {
        return "char";
    }
    if (type == "unsigned short" || type == "unsigned short int")
    {
        return "ushort";
    }
    if (type == "short" || type == "short int")
    {
        return "short";
    }
    if (type == "unsigned int" || type == "unsigned")
    {
        return "uint";
    }
    if (type == "int")
    {
        return "int";
    }
    // "unsigned long long" must be tested before "unsigned long".
    if (type == "unsigned long long" || type == "unsigned long long int")
    {
        return "ulonglong";
    }
    if (type == "unsigned long" || type == "unsigned long int")
    {
        return "ulong";
    }
    if (type == "long long" || type == "long long int")
    {
        return "longlong";
    }
    if (type == "long" || type == "long int")
    {
        return "long";
    }
    if (type == "double")
    {
        return "double";
    }
    if (type == "float")
    {
        return "float";
    }
    if (type == "size_t")
    {
        return "size_t";
    }
    if (type == "time_t")
    {
        return "time_t";
    }
    if (type == "intptr_t")
    {
        return "intptr_t";
    }
    if (type == "uintptr_t")
    {
        return "uintptr_t";
    }
    if (type == "TChar")
    {
        return "char";
    }
    if (type == "TBool" || type == "TBoolInt")
    {
        return "int";
    }
    if (type == "TUInt8")
    {
        return "uchar";
    }
    if (type == "TUInt16")
    {
        return "uint16_t";
    }
    if (type == "TUInt32" || type == "TUInt")
    {
        return "uint32_t";
    }
    if (type == "TInt64")
    {
        return "longlong";
    }
    if (type == "TIntPtr")
    {
        return "intptr_t";
    }
    if (type == "int8_t")
    {
        return "int8_t";
    }
    if (type == "uint8_t")
    {
        return "uint8_t";
    }
    if (type == "int16_t")
    {
        return "int16_t";
    }
    if (type == "uint16_t")
    {
        return "uint16_t";
    }
    if (type == "int32_t")
    {
        return "int32_t";
    }
    if (type == "uint32_t")
    {
        return "uint32_t";
    }
    if (type == "int64_t")
    {
        return "int64_t";
    }
    if (type == "uint64_t")
    {
        return "uint64_t";
    }
    return {};
}

// CGo type of the pointee behind a scalar-pointer macro. The wrapper accepts a bare
// unsafe.Pointer, so the generated call casts it to the type the C prototype expects.
[[nodiscard]] static std::string GoScalarPointerCType(const std::string& c_type)
{
    if (c_type == "long")
    {
        return "C.long";
    }
    if (c_type == "double")
    {
        return "C.double";
    }
    if (c_type == "unsigned")
    {
        return "C.uint";
    }
    if (c_type == "unsigned long")
    {
        return "C.ulong";
    }
    return "C.int";
}

// Convert one Param to one or more GoParams.
static std::vector<GoParam> ConvertParam(const Param& param, const std::string& reserved_name = {})
{
    std::vector<GoParam> result;

    // TSelf is the receiver — skip in parameter list
    if (param.macro_name == "TSelf")
    {
        return result;
    }

    // Expanded geometry types: TPoint, TSize, TRect, TVector, etc.
    if (param.macro_name == "TPoint" || param.macro_name == "TSize" ||
        param.macro_name == "TRect" || param.macro_name == "TVector")
    {
        for (auto& field: SplitMacroArg(param.macro_arg))
        {
            const std::string n = ParamName(field, reserved_name);
            result.push_back({ n, "int", "C.int(" + n + ")", "", "", false });
        }
        return result;
    }

    if (param.macro_name == "TPointLong" || param.macro_name == "TSizeLong" ||
        param.macro_name == "TRectLong" || param.macro_name == "TVectorLong")
    {
        for (auto& field: SplitMacroArg(param.macro_arg))
        {
            const std::string n = ParamName(field, reserved_name);
            result.push_back({ n, "int", "C.long(" + n + ")", "", "", false });
        }
        return result;
    }

    if (param.macro_name == "TPointOut" || param.macro_name == "TSizeOut" ||
        param.macro_name == "TRectOut" || param.macro_name == "TVectorOut")
    {
        // Output int* geometry params — glue receives unsafe.Pointer, casts to (*C.int)
        // for C call
        for (auto& field: SplitMacroArg(param.macro_arg))
        {
            const std::string n = ParamName(field, reserved_name);
            result.push_back({ n, "unsafe.Pointer", "(*C.int)(" + n + ")", "", "", true });
        }
        return result;
    }

    if (param.macro_name == "TPointOutVoid" || param.macro_name == "TSizeOutVoid" ||
        param.macro_name == "TRectOutVoid" || param.macro_name == "TVectorOutVoid")
    {
        // Output void* geometry params — unsafe.Pointer passes through as-is
        for (auto& field: SplitMacroArg(param.macro_arg))
        {
            const std::string n = ParamName(field, reserved_name);
            result.push_back({ n, "unsafe.Pointer", n, "", "", true });
        }
        return result;
    }

    if (param.macro_name == "TSizeOutDouble")
    {
        // Output double* geometry params — cast to (*C.double) for C call
        for (auto& field: SplitMacroArg(param.macro_arg))
        {
            const std::string n = ParamName(field, reserved_name);
            result.push_back({ n, "unsafe.Pointer", "(*C.double)(" + n + ")", "", "", true });
        }
        return result;
    }

    if (param.macro_name == "TColorRGB")
    {
        for (auto& field: SplitMacroArg(param.macro_arg))
        {
            const std::string n = ParamName(field, reserved_name);
            result.push_back({ n, "int", "C.uchar(" + n + ")", "", "", false });
        }
        return result;
    }

    // Array types: expand to count + pointer
    if (param.macro_name == "TArrayString")
    {
        // int n, char** p  (TString* = char**)
        const std::vector<std::string> names = SplitMacroArg(param.macro_arg);
        if (names.size() >= 2)
        {
            const std::string first_name = ParamName(names[0], reserved_name);
            const std::string second_name = ParamName(names[1], reserved_name);
            result.push_back({ first_name, "int", "C.int(" + first_name + ")", "", "", false });
            result.push_back(
                { second_name, "unsafe.Pointer", "(**C.char)(" + second_name + ")", "", "", true });
        }
        else
        {
            std::println(stderr, "Warning: TArrayString macro_arg '{}' has fewer than 2 components",
                         param.macro_arg);
        }
        return result;
    }

    if (param.macro_name == "TArrayInt" || param.macro_name == "TArrayIntPtr")
    {
        // int n, int* p  (or intptr_t* p)
        const std::vector<std::string> names = SplitMacroArg(param.macro_arg);
        if (names.size() >= 2)
        {
            const std::string first_name = ParamName(names[0], reserved_name);
            const std::string second_name = ParamName(names[1], reserved_name);
            result.push_back({ first_name, "int", "C.int(" + first_name + ")", "", "", false });
            result.push_back(
                { second_name, "unsafe.Pointer", "(*C.int)(" + second_name + ")", "", "", true });
        }
        else
        {
            std::println(stderr, "Warning: TArrayInt macro_arg '{}' has fewer than 2 components",
                         param.macro_arg);
        }
        return result;
    }

    if (param.macro_name == "TByteString" || param.macro_name == "TByteStringLazy")
    {
        // TByteData* d, int n  =  char** d, int n  (args are REVERSED vs TArrayString)
        const std::vector<std::string> names = SplitMacroArg(param.macro_arg);
        if (names.size() >= 2)
        {
            const std::string first_name = ParamName(names[0], reserved_name);   // data pointer
            const std::string second_name = ParamName(names[1], reserved_name);  // length
            result.push_back(
                { first_name, "unsafe.Pointer", "(**C.char)(" + first_name + ")", "", "", true });
            result.push_back({ second_name, "int", "C.int(" + second_name + ")", "", "", false });
        }
        else
        {
            std::println(stderr, "Warning: TByteString macro_arg '{}' has fewer than 2 components",
                         param.macro_arg);
        }
        return result;
    }

    if (param.macro_name == "TArrayObjectOutVoid")
    {
        const std::string name =
            ParamName(param.param_name.empty() ? "arr" : param.param_name, reserved_name);
        result.push_back({ name, "unsafe.Pointer", name, "", "", true });
        return result;
    }

    // Scalar value passed through a pointer: the caller owns the storage.
    if (ScalarPointerInfo scalar_pointer; LookupScalarPointer(param, scalar_pointer))
    {
        const std::string name =
            ParamName(param.param_name.empty() ? "arg" : param.param_name, reserved_name);
        result.push_back({ name, "unsafe.Pointer",
                           "(*" + GoScalarPointerCType(scalar_pointer.c_type) + ")(" + name + ")",
                           "", "", true });
        return result;
    }

    // Single parameter
    GoParam go_param;
    go_param.name = ParamName(param.param_name.empty() ? "arg" : param.param_name, reserved_name);

    if (param.macro_name == "TClass" && param.macro_arg == "wxString" &&
        (param.raw_type.empty() || param.raw_type.back() != '*'))
    {
        // wxString parameter: class file bridges Go string → NewWxString,
        // glue function receives the raw pointer directly.
        const std::string wx_var = "wx" + Capitalize(go_param.name);
        go_param.go_type = "string";
        go_param.pre_call = wx_var + " := NewWxString(" + go_param.name + ")";
        go_param.defer_call = "defer " + wx_var + ".Free()";
        go_param.cgo_expr = go_param.name;  // glue body: pass param name (unsafe.Pointer)
        go_param.needs_unsafe = false;
        go_param.glue_go_type = "unsafe.Pointer";
        go_param.glue_pass_expr = wx_var + ".Ptr()";
    }
    else if (param.macro_name == "TClass" || param.macro_name == "TClassRef")
    {
        go_param.go_type = "unsafe.Pointer";
        go_param.needs_unsafe = true;
        // TClass(Foo) * means void** — CGo sees *unsafe.Pointer, must cast
        if (!param.raw_type.empty() && param.raw_type.back() == '*')
        {
            go_param.cgo_expr = "(*unsafe.Pointer)(" + go_param.name + ")";
        }
        else
        {
            go_param.cgo_expr = go_param.name;
        }
    }
    else if (param.macro_name == "TBool" || param.raw_type == "TBool")
    {
        go_param.go_type = "bool";
        go_param.cgo_expr = "boolToInt(" + go_param.name + ")";
    }
    else if (param.raw_type == "TBoolInt")
    {
        go_param.go_type = "int";
        go_param.cgo_expr = "C.int(" + go_param.name + ")";
    }
    else if (param.raw_type == "TBool*")
    {
        // Output bool pointer — pass as unsafe.Pointer, cast to *C.int
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = "(*C.int)(" + go_param.name + ")";
        go_param.needs_unsafe = true;
    }
    else if (param.macro_name == "TClosureFun" || param.raw_type == "TClosureFun")
    {
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = go_param.name;
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "TStringVoid" || param.macro_name == "TStringVoid")
    {
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = go_param.name;
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "TByteStringOut" || param.raw_type == "TByteStringLazyOut")
    {
        // TByteData = char* — C function takes char*, must cast from unsafe.Pointer
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = "(*C.char)(" + go_param.name + ")";
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "TArrayIntOutVoid" || param.raw_type == "TArrayIntPtrOutVoid" ||
             param.raw_type == "TArrayStringOutVoid")
    {
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = go_param.name;
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "TChar")
    {
        go_param.go_type = "byte";
        go_param.cgo_expr = "C.char(" + go_param.name + ")";
    }
    else if (param.raw_type == "TUInt8")
    {
        go_param.go_type = "uint8";
        go_param.cgo_expr = "C.uchar(" + go_param.name + ")";
    }
    else if (param.raw_type == "TUInt16")
    {
        go_param.go_type = "uint16";
        go_param.cgo_expr = "C.uint16_t(" + go_param.name + ")";
    }
    else if (param.raw_type == "TUInt32" || param.raw_type == "TUInt")
    {
        go_param.go_type = "uint32";
        go_param.cgo_expr = "C.uint32_t(" + go_param.name + ")";
    }
    else if (param.raw_type == "TIntPtr")
    {
        go_param.go_type = "int64";
        go_param.cgo_expr = "C.intptr_t(" + go_param.name + ")";
    }
    else if (param.raw_type == "unsigned char")
    {
        go_param.go_type = "byte";
        go_param.cgo_expr = "C.uchar(" + go_param.name + ")";
    }
    else if (param.raw_type == "signed char")
    {
        go_param.go_type = "int8";
        go_param.cgo_expr = "C.schar(" + go_param.name + ")";
    }
    else if (param.raw_type == "char")
    {
        go_param.go_type = "byte";
        go_param.cgo_expr = "C.char(" + go_param.name + ")";
    }
    else if (param.raw_type == "void**")
    {
        // void** is represented by *unsafe.Pointer in cgo.
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = "(*unsafe.Pointer)(" + go_param.name + ")";
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "intptr_t")
    {
        go_param.go_type = "int64";
        go_param.cgo_expr = "C.intptr_t(" + go_param.name + ")";
    }
    else if (param.raw_type == "TString")
    {
        // char* input: glue function handles C.CString conversion internally.
        go_param.go_type = "string";
        const std::string cstr_var = "c" + Capitalize(go_param.name);
        go_param.cgo_expr = cstr_var;
        go_param.needs_unsafe = false;  // class file just passes a Go string
        go_param.glue_pre = cstr_var + " := C.CString(" + go_param.name + ")";
        go_param.glue_defer = "defer C.free(unsafe.Pointer(" + cstr_var + "))";
    }
    else if (param.raw_type == "TStringOut")
    {
        // char* output buffer: pass as unsafe.Pointer
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = "(*C.char)(" + go_param.name + ")";
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "TBytesIn" || param.raw_type == "TBytesOut" ||
             param.raw_type == "TByteOut")
    {
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = "(*C.uchar)(" + go_param.name + ")";
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "TCharOut")
    {
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = "(*C.char)(" + go_param.name + ")";
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "TIntArrayIn" || param.raw_type == "TIntArrayOut" ||
             param.raw_type == "TIntIn" || param.raw_type == "TBoolIn")
    {
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = "(*C.int)(" + go_param.name + ")";
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "TDoubleArrayOut")
    {
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = "(*C.double)(" + go_param.name + ")";
        go_param.needs_unsafe = true;
    }
    else if (param.raw_type == "TCookie")
    {
        go_param.go_type = "unsafe.Pointer";
        go_param.cgo_expr = "(*unsafe.Pointer)(" + go_param.name + ")";
        go_param.needs_unsafe = true;
    }
    else
    {
        // Plain C types
        const std::string raw_type = param.raw_type;
        if (raw_type.empty() || raw_type == "int")
        {
            go_param.go_type = "int";
            go_param.cgo_expr = "C.int(" + go_param.name + ")";
        }
        else if (raw_type == "long")
        {
            go_param.go_type = "int";
            go_param.cgo_expr = "C.long(" + go_param.name + ")";
        }
        else if (raw_type == "unsigned" || raw_type == "unsigned int")
        {
            go_param.go_type = "uint";
            go_param.cgo_expr = "C.uint(" + go_param.name + ")";
        }
        else if (raw_type == "unsigned long")
        {
            go_param.go_type = "uint";
            go_param.cgo_expr = "C.ulong(" + go_param.name + ")";
        }
        else if (raw_type == "unsigned short")
        {
            go_param.go_type = "uint16";
            go_param.cgo_expr = "C.ushort(" + go_param.name + ")";
        }
        else if (raw_type == "wxUIntPtr")
        {
            go_param.go_type = "uintptr";
            go_param.cgo_expr = "C.uintptr_t(" + go_param.name + ")";
        }
        else if (raw_type == "uintptr_t")
        {
            go_param.go_type = "uintptr";
            go_param.cgo_expr = "C.uintptr_t(" + go_param.name + ")";
        }
        else if (raw_type == "double")
        {
            go_param.go_type = "float64";
            go_param.cgo_expr = "C.double(" + go_param.name + ")";
        }
        else if (raw_type == "float")
        {
            go_param.go_type = "float32";
            go_param.cgo_expr = "C.float(" + go_param.name + ")";
        }
        else if (raw_type == "size_t")
        {
            go_param.go_type = "int";
            go_param.cgo_expr = "C.size_t(" + go_param.name + ")";
        }
        else if (raw_type == "time_t")
        {
            go_param.go_type = "int64";
            go_param.cgo_expr = "C.time_t(" + go_param.name + ")";
        }
        else if (raw_type == "TInt64" || raw_type == "int64_t")
        {
            go_param.go_type = "int64";
            go_param.cgo_expr = "C.longlong(" + go_param.name + ")";
        }
        else if (raw_type == "TInt64*" || raw_type == "int64_t*" || raw_type == "const TInt64*" ||
                 raw_type == "const int64_t*")
        {
            go_param.go_type = "unsafe.Pointer";
            go_param.cgo_expr = "(*C.longlong)(" + go_param.name + ")";
            go_param.needs_unsafe = true;
        }
        else if (raw_type == "int*" || raw_type == "const int*")
        {
            go_param.go_type = "unsafe.Pointer";
            go_param.cgo_expr = "(*C.int)(" + go_param.name + ")";
            go_param.needs_unsafe = true;
        }
        else if (raw_type == "long*")
        {
            go_param.go_type = "unsafe.Pointer";
            go_param.cgo_expr = "(*C.long)(" + go_param.name + ")";
            go_param.needs_unsafe = true;
        }
        else if (raw_type == "double*")
        {
            go_param.go_type = "unsafe.Pointer";
            go_param.cgo_expr = "(*C.double)(" + go_param.name + ")";
            go_param.needs_unsafe = true;
        }
        else if (raw_type == "unsigned*")
        {
            go_param.go_type = "unsafe.Pointer";
            go_param.cgo_expr = "(*C.uint)(" + go_param.name + ")";
            go_param.needs_unsafe = true;
        }
        else if (raw_type.find('*') != std::string::npos)
        {
            // Pointer to a scalar: cgo requires an exact pointer type, so the
            // unsafe.Pointer has to be cast. void* (and any element type without a
            // known cgo name) is already represented by unsafe.Pointer.
            go_param.go_type = "unsafe.Pointer";
            const std::string cgo_scalar = CgoScalarNameFor(raw_type);
            if (cgo_scalar.empty())
            {
                go_param.cgo_expr = go_param.name;
            }
            else
            {
                go_param.cgo_expr = "(*C." + cgo_scalar + ")(" + go_param.name + ")";
            }
            go_param.needs_unsafe = true;
        }
        else
        {
            // Unknown — treat as int
            go_param.go_type = "int";
            go_param.cgo_expr = "C.int(" + go_param.name + ")";
        }
    }

    result.push_back(std::move(go_param));
    return result;
}

// Get Go return type string for a function declaration.
static std::string GoReturnType(const FunctionDecl& func_decl, const std::string& go_class_name)
{
    // True constructors (no self param) return *ClassName
    if (func_decl.is_constructor && !func_decl.has_self && func_decl.return_type != "TBool")
    {
        return "*" + go_class_name;
    }

    if (func_decl.return_type == "void" || func_decl.return_type.empty())
    {
        return "";
    }

    // TClass(wxString) → string
    if (func_decl.return_macro == "TClass" && func_decl.return_arg == "wxString")
    {
        return "string";
    }

    // TClass(wxSize|wxPoint|wxRect) → owning Go value types
    if (func_decl.return_macro == "TClass")
    {
        if (func_decl.return_arg == "wxSize")
        {
            return "Size";
        }
        if (func_decl.return_arg == "wxPoint")
        {
            return "Point";
        }
        if (func_decl.return_arg == "wxRect")
        {
            return "Rect";
        }
    }

    // TClass(wxFoo) → unsafe.Pointer
    if (func_decl.return_macro == "TClass" || func_decl.return_macro == "TSelf")
    {
        return "unsafe.Pointer";
    }

    // String return types
    if (func_decl.return_type == "TString" || func_decl.return_type == "TStringOut")
    {
        return "string";
    }
    if (func_decl.return_type == "TChar")
    {
        return "byte";
    }

    if (func_decl.return_type == "TBool")
    {
        return "bool";
    }
    if (func_decl.return_type == "TInt64" || func_decl.return_type == "int64_t")
    {
        return "int64";
    }
    if (func_decl.return_type == "int" || func_decl.return_type == "long" ||
        func_decl.return_type == "TArrayLen" || func_decl.return_type == "TByteStringLen" ||
        func_decl.return_type == "size_t" || func_decl.return_type == "time_t")
    {
        return "int";
    }
    if (func_decl.return_type == "unsigned" || func_decl.return_type == "unsigned int" ||
        func_decl.return_type == "unsigned long")
    {
        return "uint";
    }
    if (func_decl.return_type == "wxUIntPtr")
    {
        return "uintptr";
    }
    if (func_decl.return_type == "uintptr_t")
    {
        return "uintptr";
    }
    if (func_decl.return_type == "double")
    {
        return "float64";
    }
    if (func_decl.return_type == "float")
    {
        return "float32";
    }
    if (func_decl.return_type == "TUInt8")
    {
        return "uint8";
    }
    if (func_decl.return_type == "TUInt16")
    {
        return "uint16";
    }
    if (func_decl.return_type == "TUInt32" || func_decl.return_type == "TUInt")
    {
        return "uint32";
    }
    if (func_decl.return_type == "unsigned short")
    {
        return "uint16";
    }
    if (func_decl.return_type == "void*")
    {
        return "unsafe.Pointer";
    }

    // Fallback — if it has pointer, use unsafe.Pointer
    if (func_decl.return_type.find('*') != std::string::npos)
    {
        return "unsafe.Pointer";
    }

    return "int";
}

// Go converter for heap-allocated value-class returns. The C wrapper hands back a
// new wxSize/wxPoint/wxRect, so the converter copies the fields and frees it.
// Returns an empty string for every other return type.
[[nodiscard]] static std::string ValueClassFromPtrConverter(const FunctionDecl& func_decl)
{
    if (func_decl.return_macro != "TClass")
    {
        return "";
    }
    if (func_decl.return_arg == "wxSize")
    {
        return "sizeFromPtr";
    }
    if (func_decl.return_arg == "wxPoint")
    {
        return "pointFromPtr";
    }
    if (func_decl.return_arg == "wxRect")
    {
        return "rectFromPtr";
    }
    return "";
}

// Check if a return type needs the "unsafe" import
[[nodiscard]] static bool ReturnNeedsUnsafe(const FunctionDecl& func_decl)
{
    // TClass(wxString) → Go "string", not unsafe.Pointer
    if (func_decl.return_macro == "TClass" && func_decl.return_arg == "wxString")
    {
        return false;
    }
    // TClass(wxSize|wxPoint|wxRect) → Go value type, no unsafe.Pointer in the signature
    if (func_decl.return_macro == "TClass" &&
        (func_decl.return_arg == "wxSize" || func_decl.return_arg == "wxPoint" ||
         func_decl.return_arg == "wxRect"))
    {
        return false;
    }
    if (func_decl.return_macro == "TClass" || func_decl.return_macro == "TSelf")
    {
        return true;
    }
    if (func_decl.return_type == "void*")
    {
        return true;
    }
    if (func_decl.return_type.find('*') != std::string::npos)
    {
        return true;
    }
    return false;
}

// Check if a single free function needs the "unsafe" import
[[nodiscard]] static bool FunctionNeedsUnsafe(const FunctionDecl& func_decl)
{
    if (ReturnNeedsUnsafe(func_decl))
    {
        return true;
    }
    for (const auto& param: func_decl.params)
    {
        const std::vector<GoParam> go_params = ConvertParam(param);
        for (const auto& go_param: go_params)
        {
            if (go_param.needs_unsafe)
            {
                return true;
            }
        }
    }
    return false;
}

// Build call expression to a cgo_ glue function from a class file.
// Returns cgo_wxClassName_MethodName(passthrough_args...).
static std::string BuildGlueCall(const FunctionDecl& func_decl, const std::string& receiver_expr,
                                 const std::vector<std::vector<GoParam>>& param_groups)
{
    const std::string c_name = CFuncName(func_decl);
    std::string call = "cgo_" + c_name + "(";
    bool first = true;

    // A TSelf receiver or a mixin's TClass(OwnClass) receiver is passed first.
    if (func_decl.has_self || IsPseudoSelf(func_decl))
    {
        call += receiver_expr;
        first = false;
    }

    for (const auto& group: param_groups)
    {
        for (const auto& go_param: group)
        {
            if (!first)
            {
                call += ", ";
            }
            call += go_param.glue_pass_expr.empty() ? go_param.name : go_param.glue_pass_expr;
            first = false;
        }
    }

    call += ")";
    return call;
}

// Get the Go return type for a glue function.
// Differs from GoReturnType: constructors and string returns use unsafe.Pointer.
static std::string GlueReturnType(const FunctionDecl& func_decl)
{
    if (func_decl.is_constructor && !func_decl.has_self && func_decl.return_type != "TBool")
    {
        return "unsafe.Pointer";
    }

    if (func_decl.return_type == "void" || func_decl.return_type.empty())
    {
        return "";
    }

    if (func_decl.return_macro == "TClass" || func_decl.return_macro == "TSelf")
    {
        return "unsafe.Pointer";
    }

    if (func_decl.return_type == "TString" || func_decl.return_type == "TStringOut")
    {
        return "unsafe.Pointer";
    }
    if (func_decl.return_type == "TChar")
    {
        return "byte";
    }

    if (func_decl.return_type == "TBool")
    {
        return "bool";
    }
    if (func_decl.return_type == "TInt64" || func_decl.return_type == "int64_t")
    {
        return "int64";
    }
    if (func_decl.return_type == "int" || func_decl.return_type == "long" ||
        func_decl.return_type == "TArrayLen" || func_decl.return_type == "TByteStringLen" ||
        func_decl.return_type == "size_t" || func_decl.return_type == "time_t")
    {
        return "int";
    }
    if (func_decl.return_type == "unsigned" || func_decl.return_type == "unsigned int" ||
        func_decl.return_type == "unsigned long")
    {
        return "uint";
    }
    if (func_decl.return_type == "wxUIntPtr")
    {
        return "uintptr";
    }
    if (func_decl.return_type == "uintptr_t")
    {
        return "uintptr";
    }
    if (func_decl.return_type == "double")
    {
        return "float64";
    }
    if (func_decl.return_type == "float")
    {
        return "float32";
    }
    if (func_decl.return_type == "TUInt8")
    {
        return "uint8";
    }
    if (func_decl.return_type == "TUInt16")
    {
        return "uint16";
    }
    if (func_decl.return_type == "TUInt32" || func_decl.return_type == "TUInt")
    {
        return "uint32";
    }
    if (func_decl.return_type == "unsigned short")
    {
        return "uint16";
    }
    if (func_decl.return_type == "void*")
    {
        return "unsafe.Pointer";
    }
    if (func_decl.return_type.find('*') != std::string::npos)
    {
        return "unsafe.Pointer";
    }
    return "int";
}

// Wrap a C call expression with the appropriate Go return-type conversion.
static std::string GlueReturnExpr(const std::string& ret_type, const std::string& c_call_expr)
{
    if (ret_type.empty())
    {
        return c_call_expr;
    }
    if (ret_type == "bool")
    {
        return c_call_expr + " != 0";
    }
    if (ret_type == "unsafe.Pointer")
    {
        return "unsafe.Pointer(" + c_call_expr + ")";
    }
    // int, uint, float64, float32, uint8, uintptr — wrap with Go type cast
    return ret_type + "(" + c_call_expr + ")";
}

// Emit a single cgo_ glue function for a class method/constructor/destructor.
static void EmitGlueFunction(std::ostream& output, const FunctionDecl& func_decl)
{
    const std::string c_name = CFuncName(func_decl);
    const std::string glue_ret = GlueReturnType(func_decl);

    output << "func cgo_" << c_name << "(";

    bool first_param = true;
    std::vector<std::string> c_call_args;
    std::vector<std::string> pre_lines;
    std::vector<std::string> defer_lines;

    // Self parameter (skipped by ConvertParam — handle explicitly). Mixin
    // methods declare their receiver as TClass(OwnClass) rather than TSelf.
    const bool pseudo_self = IsPseudoSelf(func_decl);
    if (func_decl.has_self || pseudo_self)
    {
        output << "self unsafe.Pointer";
        c_call_args.emplace_back("self");
        first_param = false;
    }

    bool first_tself = true;
    for (size_t param_index = 0; param_index < func_decl.params.size(); ++param_index)
    {
        const Param& param = func_decl.params[param_index];
        if (param_index == 0 && pseudo_self)
        {
            continue;  // receiver already emitted as 'self'
        }
        if (param.macro_name == "TSelf")
        {
            if (first_tself)
            {
                first_tself = false;
                continue;  // first TSelf handled as 'self' above
            }
            // Additional TSelf params (e.g. wxIcon_IsEqual second arg): emit as
            // unsafe.Pointer
            if (!first_param)
            {
                output << ", ";
            }
            const std::string name =
                ParamName(param.param_name.empty() ? "other" : param.param_name, "self");
            output << name << " unsafe.Pointer";
            c_call_args.push_back(name);
            first_param = false;
            continue;
        }
        for (const auto& go_param: ConvertParam(param, "self"))
        {
            if (!first_param)
            {
                output << ", ";
            }
            const std::string param_type =
                go_param.glue_go_type.empty() ? go_param.go_type : go_param.glue_go_type;
            output << go_param.name << " " << param_type;
            c_call_args.push_back(go_param.cgo_expr);
            if (!go_param.glue_pre.empty())
            {
                pre_lines.push_back(go_param.glue_pre);
            }
            if (!go_param.glue_defer.empty())
            {
                defer_lines.push_back(go_param.glue_defer);
            }
            first_param = false;
        }
    }

    output << ")";
    if (!glue_ret.empty())
    {
        output << " " << glue_ret;
    }
    output << " {\n";

    for (const auto& line: pre_lines)
    {
        output << "\t" << line << "\n";
    }
    for (const auto& line: defer_lines)
    {
        output << "\t" << line << "\n";
    }

    // Build C.<funcname>(args...) call
    std::string c_call = "C." + c_name + "(";
    for (size_t i = 0; i < c_call_args.size(); ++i)
    {
        if (i > 0)
        {
            c_call += ", ";
        }
        c_call += c_call_args[i];
    }
    c_call += ")";

    if (glue_ret.empty())
    {
        output << "\t" << c_call << "\n";
    }
    else
    {
        output << "\treturn " << GlueReturnExpr(glue_ret, c_call) << "\n";
    }

    output << "}\n\n";
}

// Build a disambiguated Go constructor name from the C method name.
// "Create" → "New" + goClassName, e.g. "NewBitmap"
// "CreateEmpty" → "New" + goClassName + "Empty", e.g. "NewBitmapEmpty"
// "CreateFromData" → "New" + goClassName + "FromData", e.g. "NewBitmapFromData"
static std::string GoConstructorName(const std::string& go_class_name,
                                     const std::string& method_name)
{
    constexpr std::string_view PREFIX = "Create";
    std::string suffix;
    if (method_name.size() > PREFIX.size() && method_name.starts_with(PREFIX))
    {
        suffix = method_name.substr(PREFIX.size());  // e.g., "Empty", "FromData", "Load"
    }
    // "Create" alone → empty suffix
    return "New" + go_class_name + suffix;
}

// Emit a constructor function: NewClassName(...) or NewClassNameSuffix(...)
static void EmitConstructor(std::ostream& output, const ClassInfo& /*class_info*/,
                            const FunctionDecl& func_decl, const std::string& go_class_name)
{
    // Collect Go params (excluding TSelf since constructors typically don't have it)
    std::vector<std::vector<GoParam>> param_groups;
    for (const auto& param: func_decl.params)
    {
        if (param.macro_name == "TSelf")
        {
            continue;
        }
        param_groups.push_back(ConvertParam(param));
    }

    // Function signature — disambiguate overloaded Create* methods
    const std::string func_name = GoConstructorName(go_class_name, func_decl.method_name);
    output << "func " << func_name << "(";
    bool first = true;
    for (const auto& group: param_groups)
    {
        for (const auto& go_param: group)
        {
            if (!first)
            {
                output << ", ";
            }
            output << go_param.name << " " << go_param.go_type;
            first = false;
        }
    }
    output << ") *" << go_class_name << " {\n";

    // Pre-call statements (e.g., NewWxString)
    for (const auto& group: param_groups)
    {
        for (const auto& go_param: group)
        {
            if (!go_param.pre_call.empty())
            {
                output << "\t" << go_param.pre_call << "\n";
            }
            if (!go_param.defer_call.empty())
            {
                output << "\t" << go_param.defer_call << "\n";
            }
        }
    }

    // Glue call
    const std::string glue_call = BuildGlueCall(func_decl, "", param_groups);
    output << "\tptr := " << glue_call << "\n";

    // Nil check
    output << "\tif ptr == nil {\n";
    output << "\t\treturn nil\n";
    output << "\t}\n";

    // Create and return Go object
    output << "\tobj := &" << go_class_name << "{}\n";
    output << "\tobj.SetPtr(ptr)\n";
    output << "\treturn obj\n";
    output << "}\n\n";
}

// Emit a method: func (recv *ClassName) MethodName(...)
static void EmitMethod(std::ostream& output, const ClassInfo& /*class_info*/,
                       const FunctionDecl& func_decl, const std::string& go_class_name)
{
    const std::string recv(kReceiverVar);
    const std::string go_ret_type = GoReturnType(func_decl, go_class_name);

    // Collect non-self Go params; handle multiple TSelf (e.g. wxIcon_IsEqual)
    const bool pseudo_self = IsPseudoSelf(func_decl);
    std::vector<std::vector<GoParam>> param_groups;
    bool seen_self = false;  // track whether we've seen the receiver self
    for (size_t param_index = 0; param_index < func_decl.params.size(); ++param_index)
    {
        const Param& param = func_decl.params[param_index];
        if (param_index == 0 && pseudo_self)
        {
            seen_self = true;
            continue;  // TClass(OwnClass) receiver, already available as the Go receiver
        }
        if (param.macro_name == "TSelf")
        {
            if (!seen_self)
            {
                seen_self = true;
                continue;  // first TSelf already handled as receiver
            }
            // Additional TSelf — emit as unsafe.Pointer parameter
            const std::string name =
                ParamName(param.param_name.empty() ? "other" : param.param_name, kReceiverVar);
            GoParam go_param;
            go_param.name = name;
            go_param.go_type = "unsafe.Pointer";
            go_param.cgo_expr = name;
            go_param.glue_pass_expr = name;
            go_param.needs_unsafe = true;
            param_groups.push_back({ go_param });
            continue;
        }
        param_groups.push_back(ConvertParam(param, kReceiverVar));
    }

    // Method signature
    output << "func (" << recv << " *" << go_class_name << ") "
           << SafeGoIdentifier(func_decl.method_name)
           << "(";  // SafeGoIdentifier: prefix names starting with a digit
    bool first = true;
    for (const auto& group: param_groups)
    {
        for (const auto& go_param: group)
        {
            if (!first)
            {
                output << ", ";
            }
            output << go_param.name << " " << go_param.go_type;
            first = false;
        }
    }
    output << ")";
    if (!go_ret_type.empty())
    {
        output << " " << go_ret_type;
    }
    output << " {\n";

    // Pre-call statements
    for (const auto& group: param_groups)
    {
        for (const auto& go_param: group)
        {
            if (!go_param.pre_call.empty())
            {
                output << "\t" << go_param.pre_call << "\n";
            }
            if (!go_param.defer_call.empty())
            {
                output << "\t" << go_param.defer_call << "\n";
            }
        }
    }

    // Glue call
    const std::string recv_expr = recv + ".Ptr()";
    const std::string glue_call = BuildGlueCall(func_decl, recv_expr, param_groups);

    // Handle return type
    if (go_ret_type.empty())
    {
        // void return
        output << "\t" << glue_call << "\n";
    }
    else if (go_ret_type == "string")
    {
        // Glue returns unsafe.Pointer (wxString*), convert to Go string.
        // Use "retPtr" (not "wxStr") to avoid collision with input WxString locals.
        output << "\tretPtr := " << glue_call << "\n";
        output << "\treturn WxStringToGoAndFree(retPtr)\n";
    }
    else if (const std::string value_converter = ValueClassFromPtrConverter(func_decl);
             !value_converter.empty())
    {
        // Glue returns a heap-allocated wxSize/wxPoint/wxRect*; the converter
        // copies its fields and frees it, so no pointer escapes to Go.
        output << "\tretPtr := " << glue_call << "\n";
        output << "\treturn " << value_converter << "(retPtr)\n";
    }
    else
    {
        // Glue already returns the correct Go type
        output << "\treturn " << glue_call << "\n";
    }

    output << "}\n\n";
}

// Emit a C free function (class_name empty, no TSelf) as a package-level Go function.
// kwxMessageBox → MessageBox, kwxFoo → Foo, wxFoo → Foo
static void EmitFreeFunction(std::ostream& output, const FunctionDecl& func_decl,
                             const std::string& go_name)
{
    std::vector<std::vector<GoParam>> param_groups;
    param_groups.reserve(func_decl.params.size());
    for (const auto& param: func_decl.params)
    {
        param_groups.push_back(ConvertParam(param));
    }

    const std::string go_ret_type = GoReturnType(func_decl, "");

    output << "func " << SafeGoIdentifier(go_name) << "(";
    bool first = true;
    for (const auto& group: param_groups)
    {
        for (const auto& go_param: group)
        {
            if (!first)
            {
                output << ", ";
            }
            output << go_param.name << " " << go_param.go_type;
            first = false;
        }
    }
    output << ")";
    if (!go_ret_type.empty())
    {
        output << " " << go_ret_type;
    }
    output << " {\n";

    for (const auto& group: param_groups)
    {
        for (const auto& go_param: group)
        {
            if (!go_param.pre_call.empty())
            {
                output << "\t" << go_param.pre_call << "\n";
            }
            if (!go_param.defer_call.empty())
            {
                output << "\t" << go_param.defer_call << "\n";
            }
        }
    }

    const std::string glue_call = BuildGlueCall(func_decl, "", param_groups);

    if (go_ret_type.empty())
    {
        output << "\t" << glue_call << "\n";
    }
    else if (go_ret_type == "string")
    {
        output << "\tretPtr := " << glue_call << "\n";
        output << "\treturn WxStringToGoAndFree(retPtr)\n";
    }
    else if (const std::string value_converter = ValueClassFromPtrConverter(func_decl);
             !value_converter.empty())
    {
        // Glue returns a heap-allocated wxSize/wxPoint/wxRect*; the converter
        // copies its fields and frees it, so no pointer escapes to Go.
        output << "\tretPtr := " << glue_call << "\n";
        output << "\treturn " << value_converter << "(retPtr)\n";
    }
    else
    {
        output << "\treturn " << glue_call << "\n";
    }

    output << "}\n\n";
}

// Strip the kwx/wx prefix and capitalize for an exported Go identifier.
[[nodiscard]] static std::string GoFreeFunctionName(const FunctionDecl& func_decl)
{
    std::string name = func_decl.method_name;
    if (name.starts_with(KWX_PREFIX))
    {
        name = Capitalize(name.substr(KWX_PREFIX.length()));
    }
    else if (name.starts_with(WX_PREFIX))
    {
        name = Capitalize(name.substr(WX_PREFIX.length()));
    }
    else
    {
        name = Capitalize(name);
    }
    return name;
}

// Go type names emitted for the classes that produce their own file.
//
// The class set comes from the shared policy in lang_common.h so Go wraps exactly the
// classes every other backend wraps, including the zero-method direct wxEvent subclasses
// (wxPaintEvent) that need a wrapper to expose the inherited wxEvent accessors.
[[nodiscard]] static std::unordered_set<std::string>
    CollectClassTypeNames(const ParsedFFI& parsed_ffi)
{
    const std::unordered_set<std::string> wrapped_classes = CollectWrappedClasses(parsed_ffi);
    std::unordered_set<std::string> names;
    names.reserve(wrapped_classes.size());
    for (const auto& class_decl: parsed_ffi.classes)
    {
        if (wrapped_classes.contains(class_decl.name) &&
            !kHandMaintainedClasses.contains(class_decl.name))
        {
            names.insert(StripPrefix(class_decl.name));
        }
    }
    return names;
}

// A free function together with the package-level Go name it is emitted under.
struct GoFreeFunction
{
    const FunctionDecl* decl = nullptr;
    std::string go_name;
};

// Canonical package-level free functions for the Go backend.
//
// The same C function can be reached through more than one header (wxBell from
// kwx_constants.h and kwxBell from kwx_classes_sync.h), and some names are already
// defined by hand-written files in the Go module.  Emitting one Go function per Go
// identifier here keeps functions_gen.go and the cgo glue consistent; a free
// function that would collide with a class type is suffixed with "Func".
[[nodiscard]] static std::vector<GoFreeFunction> CollectFreeFunctions(const ParsedFFI& parsed_ffi)
{
    const std::unordered_set<std::string> class_names = CollectClassTypeNames(parsed_ffi);
    std::vector<GoFreeFunction> result;
    std::unordered_set<std::string> emitted_names;
    for (const auto& func: parsed_ffi.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        std::string go_name = GoFreeFunctionName(func);
        if (kHandMaintainedFreeFunctions.contains(go_name))
        {
            continue;
        }
        if (class_names.contains(go_name))
        {
            go_name += "Func";
        }
        if (!emitted_names.insert(go_name).second)
        {
            continue;  // second declaration of the same Go identifier
        }
        result.push_back({ &func, std::move(go_name) });
    }
    return result;
}

// Canonical constant list: drops entries that would declare the same Go name.
// Each ribbon constant is exported from both kwx_defs.cpp (expwx*) and
// kwx_constants.h (exp*); emitting both is a redeclaration in one const block.
[[nodiscard]] static std::vector<const ConstantDecl*> CollectConstants(const ParsedFFI& parsed_ffi)
{
    std::vector<const ConstantDecl*> result;
    std::unordered_set<std::string> emitted_names;
    result.reserve(parsed_ffi.constants.size());
    for (const auto& constant: parsed_ffi.constants)
    {
        if (emitted_names.insert(constant.constant_name).second)
        {
            result.push_back(&constant);
        }
    }
    return result;
}

// -------------------------------------------------------------------------
// Coverage report
// -------------------------------------------------------------------------

// True when EmitClassFile emits a Go member for this declaration: a free function is
// routed to functions_gen.go, a constructor becomes a factory, a class static becomes a
// package-level function, and everything else becomes a method on the wrapper type.
[[nodiscard]] static bool IsGoEmittedMember(const FunctionDecl& func)
{
    return IsValidFunction(func);
}

// The Go identifier EmitClassFile gives this declaration inside the class block.  Mirrors
// the classifier in EmitClassFile: a free function keeps its package-level name, a class
// static is prefixed with the class name, a true constructor becomes NewXxx, a destructor
// becomes Delete, and everything else is a plain method name.
[[nodiscard]] static std::string GoMemberName(const std::string& class_name,
                                              const FunctionDecl& func)
{
    const bool is_free_function = func.class_name.empty() && !func.has_self;
    const bool is_true_constructor =
        func.is_constructor && !func.has_self && func.return_type != "TBool";
    const bool is_class_static = !is_free_function && !is_true_constructor && !func.is_destructor &&
                                 !func.has_self && !IsPseudoSelf(func);

    if (is_free_function)
    {
        return GoFreeFunctionName(func);
    }
    if (is_class_static)
    {
        return StripPrefix(class_name) + "_" + SafeGoIdentifier(func.method_name);
    }
    if (is_true_constructor)
    {
        return GoConstructorName(StripPrefix(class_name), func.method_name);
    }
    if (func.is_destructor)
    {
        return "Delete";
    }
    return SafeGoIdentifier(func.method_name);
}

// Count the members a class block produces, collapsing a declaration whose member name is
// already taken.  A mixin's methods are counted for the consumer that uses the mixin: Go
// exposes them through the mixin's own wrapper type, and the parity gate compares the
// total against the consumer's model count plus its mixin methods.
static void CountGoClassMethods(
    const std::string& class_name, const ClassInfo& class_decl, const ParsedFFI& parsed_ffi,
    const std::unordered_map<std::string, const ClassInfo*>& class_index, CoverageInfo& report)
{
    std::unordered_set<std::string> emitted_member_names;
    size_t wrapped_count = 0;
    size_t collapsed_count = 0;

    const auto count_member =
        [&emitted_member_names, &wrapped_count, &collapsed_count](const std::string& member_name)
    {
        if (emitted_member_names.insert(member_name).second)
        {
            ++wrapped_count;
        }
        else
        {
            ++collapsed_count;
        }
    };

    for (const auto& func: class_decl.methods)
    {
        if (!IsGoEmittedMember(func))
        {
            continue;
        }
        const std::string member_name = GoMemberName(class_name, func);
        // wx/event.go hand-implements the idiomatic event API on EvtHandler.  EmitClassFile
        // drops those raw wrappers, so the consumer supplies the member instead.
        if (class_name == "wxEvtHandler" && (member_name == "Bind" || member_name == "Unbind"))
        {
            ++collapsed_count;
            continue;
        }
        count_member(member_name);
    }

    const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
        parsed_ffi.mixin_map.find(class_name);
    if (mixin_iter != parsed_ffi.mixin_map.end())
    {
        for (const std::string& mixin_name: mixin_iter->second)
        {
            const std::unordered_map<std::string, const ClassInfo*>::const_iterator mixin_found =
                class_index.find(mixin_name);
            if (mixin_found == class_index.end())
            {
                continue;
            }
            for (const auto& func: mixin_found->second->methods)
            {
                if (!IsGoEmittedMember(func))
                {
                    continue;
                }
                count_member(GoMemberName(mixin_name, func));
            }
        }
    }

    report.method_counts_by_class[class_name] = wrapped_count;
    if (collapsed_count != 0)
    {
        report.deduplicated_method_counts_by_class[class_name] = collapsed_count;
        report.deduplicated_method_count += collapsed_count;
    }
}

CoverageInfo GoEmitter::Coverage(const ParsedFFI& parsed_ffi) const
{
    CoverageInfo report;
    report.free_function_count = parsed_ffi.free_functions.size();
    report.event_count = parsed_ffi.events.size();
    report.key_count = parsed_ffi.keys.size();
    report.constant_count = parsed_ffi.constants.size();

    std::unordered_map<std::string, const ClassInfo*> class_index;
    class_index.reserve(parsed_ffi.classes.size());
    for (const auto& class_decl: parsed_ffi.classes)
    {
        class_index.emplace(class_decl.name, &class_decl);
    }

    // wxPoint/wxSize/wxRect are hand-defined value types in the Go module (wx/types.go),
    // which also drives the native accessors through the generated glue (sizeFromPtr and
    // friends).  They are consumer-provided, so they are reported as covered rather than
    // missing, and their model methods are counted as supplied by the consumer.
    for (const std::string& maintained: kHandMaintainedClasses)
    {
        report.consumer_provided_classes.push_back(maintained);
        const std::unordered_map<std::string, const ClassInfo*>::const_iterator maintained_iter =
            class_index.find(maintained);
        if (maintained_iter == class_index.end())
        {
            continue;
        }
        size_t maintained_count = 0;
        for (const auto& func: maintained_iter->second->methods)
        {
            if (IsValidFunction(func))
            {
                ++maintained_count;
            }
        }
        report.method_counts_by_class[maintained] = maintained_count;
    }

    for (const auto& class_decl: parsed_ffi.classes)
    {
        if (kHandMaintainedClasses.contains(class_decl.name))
        {
            continue;  // already reported as consumer-provided
        }
        if (!ShouldWrapClass(class_decl, parsed_ffi))
        {
            report.skipped_classes.push_back(class_decl.name);
            continue;
        }

        report.wrapped_classes.push_back(class_decl.name);
        CountGoClassMethods(class_decl.name, class_decl, parsed_ffi, class_index, report);
    }

    std::ranges::sort(report.wrapped_classes);
    std::ranges::sort(report.consumer_provided_classes);
    std::ranges::sort(report.skipped_classes);
    return report;
}

// -------------------------------------------------------------------------
// GoEmitter public interface
// -------------------------------------------------------------------------

void GoEmitter::Generate(const ParsedFFI& parsed_ffi, const fs::path& out_dir)
{
    std::ignore = fs::create_directories(out_dir);

    GenerateGlueFile(parsed_ffi, out_dir);
    GenerateHelpers(out_dir);
    GenerateConstants(parsed_ffi, out_dir);
    GenerateEvents(parsed_ffi, out_dir);
    GenerateEventTypes(parsed_ffi, out_dir);
    GenerateKeys(parsed_ffi, out_dir);
    GenerateFreeFunctions(parsed_ffi, out_dir);
    const size_t class_file_count = GenerateClassFiles(parsed_ffi, out_dir);

    std::println(stderr, "Go: checked {:L} files in {}", kFixedFileCount + class_file_count,
                 out_dir.string());
}

VerifyResult GoEmitter::Verify(const ParsedFFI& /* parsed_ffi */, const fs::path& /* directory */)
{
    VerifyResult result;
    result.success = false;
    result.messages.emplace_back("Go verify: use 'kwxgen verify' command instead");
    return result;
}

// -------------------------------------------------------------------------
// helpers_gen.go — utility functions used by generated code
// -------------------------------------------------------------------------

void GoEmitter::GenerateHelpers(const fs::path& out_dir)
{
    const fs::path path = out_dir / "helpers_gen.go";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer);
    writer << "package wx\n";
    writer << "\n";
    writer << "import \"unsafe\"\n";
    writer << "\n";
    writer << "// BaseObject is the root type for all non-window wxWidgets objects.\n";
    writer << "// All generated non-window class structs embed this type directly or "
              "indirectly.\n";
    writer << "type BaseObject struct {\n";
    writer << "\tptr      unsafe.Pointer\n";
    writer << "\tborrowed bool\n";
    writer << "}\n";
    writer << "\n";
    writer << "// Ptr returns the underlying wxWidgets object pointer.\n";
    writer << "func (o *BaseObject) Ptr() unsafe.Pointer { return o.ptr }\n";
    writer << "\n";
    writer << "// SetPtr sets the underlying wxWidgets object pointer.\n";
    writer << "func (o *BaseObject) SetPtr(p unsafe.Pointer) { o.ptr = p }\n";
    writer << "\n";
    writer << "// Borrowed reports whether this wrapper is a non-owning view of a native "
              "object.\n";
    writer << "func (o *BaseObject) Borrowed() bool { return o.borrowed }\n";
    writer << "\n";
    writer << "// SetBorrowed marks the wrapper as non-owning, so Delete() does not free it.\n";
    writer << "func (o *BaseObject) SetBorrowed(b bool) { o.borrowed = b }\n";
    writer << "\n";
    writer << "// BaseWindow is the root type for all window-derived wxWidgets objects.\n";
    writer << "// All generated window class structs embed this type directly or "
              "indirectly.\n";
    writer << "type BaseWindow struct{ BaseObject }\n";
    writer << "\n";
    writer << "// WxString wraps a heap-allocated wxString for bridging Go strings to the C++ "
              "API.\n";
    writer << "// Create with NewWxString and always call Free() when done (typically via "
              "defer).\n";
    writer << "type WxString struct {\n";
    writer << "\tptr unsafe.Pointer\n";
    writer << "}\n";
    writer << "\n";
    writer << "// NewWxString creates a heap-allocated wxString from a Go string.\n";
    writer << "// The caller must call Free() when the wxString is no longer needed.\n";
    writer << "func NewWxString(s string) *WxString { return &WxString{ptr: "
              "cgo_NewWxString(s)} "
              "}\n";
    writer << "\n";
    writer << "// Ptr returns the opaque wxString pointer for passing to generated C "
              "wrappers.\n";
    writer << "func (w *WxString) Ptr() unsafe.Pointer { return w.ptr }\n";
    writer << "\n";
    writer << "// Free releases the underlying wxString. Safe to call multiple times.\n";
    writer << "func (w *WxString) Free() {\n";
    writer << "\tif w.ptr != nil {\n";
    writer << "\t\tcgo_FreeWxString(w.ptr)\n";
    writer << "\t\tw.ptr = nil\n";
    writer << "\t}\n";
    writer << "}\n";
    writer << "\n";
    writer << "// WxStringToGoAndFree converts a wxString pointer returned by a C wrapper "
              "into a "
              "Go\n";
    writer << "// string, then frees the wxString. The pointer must not be used after this "
              "call.\n";
    writer << "func WxStringToGoAndFree(ptr unsafe.Pointer) string {\n";
    writer << "\treturn cgo_WxStringToGoAndFree(ptr)\n";
    writer << "}\n";

    std::ignore = writer.Flush();
    std::print(stderr, "  helpers_gen.go:   BaseObject + BaseWindow + WxString types");
    if (!writer.WasWritten())
    {
        std::print(stderr, " (unchanged)");
    }
    std::println(stderr, "");
}

// -------------------------------------------------------------------------
// functions_gen.go — package-level free functions (e.g. kwxMessageBox → MessageBox)
// -------------------------------------------------------------------------

void GoEmitter::GenerateFreeFunctions(const ParsedFFI& parsed_ffi, const fs::path& out_dir)
{
    const std::vector<GoFreeFunction> free_functions = CollectFreeFunctions(parsed_ffi);
    if (free_functions.empty())
    {
        return;
    }

    const fs::path path = out_dir / "functions_gen.go";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer);
    writer << "package wx\n\n";

    // Check if any emitted free function needs the "unsafe" import
    bool needs_unsafe = false;
    for (const auto& func: free_functions)
    {
        if (FunctionNeedsUnsafe(*func.decl))
        {
            needs_unsafe = true;
            break;
        }
    }
    if (needs_unsafe)
    {
        writer << "import \"unsafe\"\n\n";
    }

    for (const auto& func: free_functions)
    {
        EmitFreeFunction(writer, *func.decl, func.go_name);
    }
    const size_t count = free_functions.size();

    std::ignore = writer.Flush();
    std::println(stderr, "  functions_gen.go: {:L} free functions{}", count,
                 writer.WasWritten() ? "" : " (unchanged)");
}

// -------------------------------------------------------------------------
// constants_gen.go
// -------------------------------------------------------------------------

void GoEmitter::GenerateConstants(const ParsedFFI& parsed_ffi, const fs::path& out_dir)
{
    const fs::path path = out_dir / "constants_gen.go";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer);
    writer << "package wx\n\n";

    // One Go name per constant, sorted for stable output.
    std::vector<const ConstantDecl*> sorted = CollectConstants(parsed_ffi);
    std::ranges::sort(sorted,
                      [](const ConstantDecl* left, const ConstantDecl* right)
                      {
                          return left->constant_name < right->constant_name;
                      });

    writer << "var (\n";
    for (const ConstantDecl* constant: sorted)
    {
        writer << "\t" << constant->constant_name << " = " << GoConstantExpr(*constant) << "\n";
    }
    writer << ")\n";

    std::ignore = writer.Flush();
    std::println(stderr, "  constants_gen.go: {:L} constants{}", sorted.size(),
                 writer.WasWritten() ? "" : " (unchanged)");
}

// -------------------------------------------------------------------------
// events_gen.go
// -------------------------------------------------------------------------

void GoEmitter::GenerateEvents(const ParsedFFI& parsed_ffi, const fs::path& out_dir)
{
    const fs::path path = out_dir / "events_gen.go";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer);
    writer << "package wx\n\n";

    // Sort events by name for stable output
    std::vector<EventDecl> sorted = parsed_ffi.events;
    std::ranges::sort(sorted,
                      [](const EventDecl& left, const EventDecl& right)
                      {
                          return left.event_name < right.event_name;
                      });

    writer << "var (\n";
    for (const auto& event: sorted)
    {
        writer << "\t" << event.event_name << " = cgo_" << event.export_name << "()\n";
    }
    writer << ")\n";

    std::ignore = writer.Flush();
    std::println(stderr, "  events_gen.go:    {:L} events{}", parsed_ffi.events.size(),
                 writer.WasWritten() ? "" : " (unchanged)");
}

// -------------------------------------------------------------------------
// event_types_gen.go — downcast helpers from *Event to a concrete event type
// -------------------------------------------------------------------------

// True when walking parent_map from `class_name` reaches "wxEvent".
[[nodiscard]] static bool
    IsEventDerived(const std::string& class_name,
                   const std::unordered_map<std::string, std::string>& parent_map)
{
    std::unordered_set<std::string> visited;
    std::string current = class_name;
    while (visited.insert(current).second)
    {
        const auto iter = parent_map.find(current);
        if (iter == parent_map.end())
        {
            return false;
        }
        if (iter->second == "wxEvent")
        {
            return true;
        }
        current = iter->second;
    }
    return false;
}

void GoEmitter::GenerateEventTypes(const ParsedFFI& parsed_ffi, const fs::path& out_dir)
{
    const fs::path path = out_dir / "event_types_gen.go";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    const std::unordered_set<std::string> class_types = CollectClassTypeNames(parsed_ffi);

    // Keep the C++ class name alongside the Go type name: the generated
    // downcast helper passes the class name to wxEvent_IsOfClass so the cast is
    // verified at runtime instead of being a blind reinterpretation.
    struct EventTypeName
    {
        std::string c_name;
        std::string go_name;
    };

    std::vector<EventTypeName> event_types;
    for (const auto& class_decl: parsed_ffi.classes)
    {
        const std::string& c_name = class_decl.name;
        if (c_name == "wxEvent" || kHandMaintainedClasses.contains(c_name))
        {
            continue;
        }
        if (!IsEventDerived(c_name, parsed_ffi.parent_map))
        {
            continue;
        }
        if (!class_types.contains(StripPrefix(c_name)))
        {
            continue;
        }
        event_types.push_back({ c_name, StripPrefix(c_name) });
    }

    std::ranges::sort(event_types,
                      [](const EventTypeName& left, const EventTypeName& right)
                      {
                          return left.go_name < right.go_name;
                      });
    event_types.erase(std::unique(event_types.begin(), event_types.end(),
                                  [](const EventTypeName& left, const EventTypeName& right)
                                  {
                                      return left.go_name == right.go_name;
                                  }),
                      event_types.end());

    WriteGeneratedHeader(writer);
    writer << "package wx\n";

    for (const auto& event_type: event_types)
    {
        const std::string& c_name = event_type.c_name;
        const std::string& go_name = event_type.go_name;

        writer << "\n";
        writer << "// As" << go_name << " reinterprets evt as a *" << go_name
               << " without taking ownership.\n";
        writer << "// Returns nil when evt is not a " << c_name << " (runtime class check).\n";
        writer << "func As" << go_name << "(evt *Event) *" << go_name << " {\n";
        writer << "\tif evt == nil || !cgo_wxEvent_IsOfClass(evt.Ptr(), \"" << c_name << "\") {\n";
        writer << "\t\treturn nil\n";
        writer << "\t}\n";
        writer << "\tobj := &" << go_name << "{}\n";
        writer << "\tobj.SetPtr(evt.Ptr())\n";
        writer << "\tobj.SetBorrowed(true)\n";
        writer << "\treturn obj\n";
        writer << "}\n";
    }

    std::ignore = writer.Flush();
    std::print(stderr, "  event_types_gen.go: {:L} event classes", event_types.size());
    if (!writer.WasWritten())
    {
        std::print(stderr, " (unchanged)");
    }
    std::println(stderr, "");
}

// -------------------------------------------------------------------------
// keys_gen.go
// -------------------------------------------------------------------------

void GoEmitter::GenerateKeys(const ParsedFFI& parsed_ffi, const fs::path& out_dir)
{
    const fs::path path = out_dir / "keys_gen.go";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer);
    writer << "package wx\n\n";

    // Sort keys by name for stable output
    std::vector<KeyDecl> sorted = parsed_ffi.keys;
    std::ranges::sort(sorted,
                      [](const KeyDecl& left, const KeyDecl& right)
                      {
                          return left.key_name < right.key_name;
                      });

    writer << "var (\n";
    for (const auto& k: sorted)
    {
        writer << "\t" << k.key_name << " = cgo_" << k.export_name << "()\n";
    }
    writer << ")\n";

    std::ignore = writer.Flush();
    std::println(stderr, "  keys_gen.go:      {:L} keys{}", parsed_ffi.keys.size(),
                 writer.WasWritten() ? "" : " (unchanged)");
}

// -------------------------------------------------------------------------
// Class files: one file per class
// -------------------------------------------------------------------------

size_t GoEmitter::GenerateClassFiles(const ParsedFFI& parsed_ffi, const fs::path& out_dir)
{
    size_t file_count = 0;
    size_t written_count = 0;
    size_t method_count = 0;
    size_t skipped_methods = 0;

    // Classes already hand-defined in the Go module (wx/types.go) are skipped by
    // kHandMaintainedClasses, which is shared with the free-function collision check.

    // Only include classes that will actually be generated.  The set comes from the shared
    // policy so a class is wrapped in Go exactly when it is wrapped everywhere.  This also
    // keeps parent-embed resolution from referencing a type that is never emitted — e.g.
    // wxObject has no wrapped methods, so "Object" is never defined, yet child classes would
    // try to embed it.  Those classes fall back to BaseObject instead.
    const std::unordered_set<std::string> policy_classes = CollectWrappedClasses(parsed_ffi);
    std::unordered_set<std::string> wrapped_classes;
    wrapped_classes.reserve(policy_classes.size());
    for (const std::string& wrapped_name: policy_classes)
    {
        if (!kHandMaintainedClasses.contains(wrapped_name))
        {
            wrapped_classes.insert(wrapped_name);
        }
    }

    std::unordered_set<std::string> expected_class_files;
    expected_class_files.reserve(wrapped_classes.size());

    for (const auto& class_decl: parsed_ffi.classes)
    {
        if (!wrapped_classes.contains(class_decl.name))
        {
            continue;  // not in the shared policy, or defined in types.go
        }

        const std::string file_name = GoFileName(class_decl.name);
        expected_class_files.insert(file_name);

        const fs::path path = out_dir / file_name;
        ConditionalFileWriter writer(path);
        if (!writer.is_open())
        {
            std::println(stderr, "Error: cannot create {}", path.string());
            continue;
        }

        EmitClassFile(writer, class_decl, parsed_ffi, wrapped_classes);
        if (writer.Flush())
        {
            ++written_count;
        }
        ++file_count;

        for (const auto& method: class_decl.methods)
        {
            if (IsValidFunction(method))
            {
                ++method_count;
            }
            else
            {
                ++skipped_methods;
            }
        }
    }

    const size_t removed_stale = RemoveStaleGoClassFiles(out_dir, expected_class_files);

    std::print(stderr, "  class files:      {:L} files, {:L} methods", file_count, method_count);
    if (skipped_methods > 0)
    {
        std::print(stderr, " ({:L} skipped)", skipped_methods);
    }
    std::print(stderr, " [{:L} written, {:L} unchanged", written_count, file_count - written_count);
    if (removed_stale > 0)
    {
        std::print(stderr, ", {:L} stale removed", removed_stale);
    }
    std::println(stderr, "]");

    return file_count;
}

void GoEmitter::EmitClassFile(std::ostream& output, const ClassInfo& class_info,
                              const ParsedFFI& /*parsed_ffi*/,
                              const std::unordered_set<std::string>& wrapped_classes)
{
    const std::string go_class_name = StripPrefix(class_info.name);
    const bool is_window_derived = class_info.is_window_derived;

    // Header
    WriteGeneratedHeader(output);
    output << "package wx\n\n";

    // Pure Go — no CGo preamble (all C calls go through cgo_glue_gen.go)
    output << "import \"unsafe\"\n\n";

    // Type definition — embed actual parent type from class hierarchy.
    // Both window-derived and non-window classes use the same logic: prefer the
    // wrapped parent class so Go embedding gives full method inheritance; fall back
    // to BaseWindow (window hierarchy) or BaseObject (non-window hierarchy).
    {
        std::string embed_type = is_window_derived ? "BaseWindow" : "BaseObject";
        if (!class_info.parent.empty() && wrapped_classes.contains(class_info.parent))
        {
            embed_type = StripPrefix(class_info.parent);
        }
        output << "type " << go_class_name << " struct{ " << embed_type << " }\n\n";
    }

    // Non-owning factory: a pointer returned by e.g. wxBookCtrlBase_GetPage() is
    // borrowed, so wrapping it with the owning Delete() would double-free.
    output << "// " << go_class_name
           << "FromPtr wraps ptr without taking ownership of the "
              "native object:\n";
    output << "// Delete() is a no-op for the returned wrapper.\n";
    output << "func " << go_class_name << "FromPtr(ptr unsafe.Pointer) *" << go_class_name
           << " {\n";
    output << "\tif ptr == nil {\n";
    output << "\t\treturn nil\n";
    output << "\t}\n";
    output << "\tobj := &" << go_class_name << "{}\n";
    output << "\tobj.SetPtr(ptr)\n";
    output << "\tobj.SetBorrowed(true)\n";
    output << "\treturn obj\n";
    output << "}\n\n";

    // Emit methods. The public headers sometimes declare the same operation twice
    // under two C symbols (wxTextDataObject_GetText and TextDataObject_GetText);
    // only the first Go member of a given name can exist on the type.
    std::unordered_set<std::string> emitted_member_names;
    for (const auto& func: class_info.methods)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }

        // Free functions (class_name empty, no TSelf) — emit as package-level Go functions.
        // These are bare C functions (e.g. kwxMessageBox) that appear inside a class block
        // in the header but have no class prefix; route them out as free functions.
        const bool is_free_function = func.class_name.empty() && !func.has_self;
        const bool is_true_constructor =
            func.is_constructor && !func.has_self && func.return_type != "TBool";

        // wxWidgets statics (e.g. ArtProvider_GetBitmap) live in the class block but
        // take no receiver.  Emitting them as methods would force callers to fabricate
        // a zero-value wrapper, so they become package-level Class_Method functions.
        const bool is_class_static = !is_free_function && !is_true_constructor &&
                                     !func.is_destructor && !func.has_self && !IsPseudoSelf(func);

        std::string member_name;
        if (is_free_function)
        {
            member_name = GoFreeFunctionName(func);
        }
        else if (is_class_static)
        {
            member_name = StripPrefix(class_info.name) + "_" + SafeGoIdentifier(func.method_name);
        }
        else if (is_true_constructor)
        {
            member_name = GoConstructorName(go_class_name, func.method_name);
        }
        else
        {
            member_name = SafeGoIdentifier(func.method_name);
        }

        // wx/event.go hand-implements the idiomatic Go event API on EvtHandler.
        // Emitting the raw C-shaped wrappers for these would redeclare the same
        // method on the same receiver type and break the package.
        if (class_info.name == "wxEvtHandler" && (member_name == "Bind" || member_name == "Unbind"))
        {
            continue;
        }

        if (!emitted_member_names.insert(member_name).second)
        {
            continue;  // second C wrapper for the same Go member name
        }

        if (is_free_function || is_class_static)
        {
            EmitFreeFunction(output, func, member_name);
            continue;
        }

        if (is_true_constructor)
        {
            EmitConstructor(output, class_info, func, go_class_name);
        }
        else if (func.is_destructor)
        {
            // Only treat as a true class destructor if there are no non-self parameters.
            // e.g. wxChoice_Delete(self, int index) is a list-item method, not a
            // destructor.
            // A TClass(OwnClass) receiver (e.g. wxDataViewItem_Delete) is the receiver,
            // not a parameter, so it does not turn Delete into a list-item method.
            const bool pseudo_self = IsPseudoSelf(func);
            bool has_non_self_params = false;
            for (size_t param_index = 0; param_index < func.params.size(); ++param_index)
            {
                const Param& param = func.params[param_index];
                if (param_index == 0 && pseudo_self)
                {
                    continue;
                }
                if (param.macro_name != "TSelf")
                {
                    has_non_self_params = true;
                }
            }

            if (has_non_self_params)
            {
                EmitMethod(output, class_info, func, go_class_name);
            }
            else
            {
                const std::string recv(kReceiverVar);
                output << "func (" << recv << " *" << go_class_name << ") Delete() {\n";
                output << "\tif " << recv << ".Borrowed() {\n";
                output << "\t\treturn\n";
                output << "\t}\n";
                output << "\tcgo_" << CFuncName(func) << "(" << recv << ".Ptr())\n";
                output << "}\n\n";
            }
        }
        else
        {
            EmitMethod(output, class_info, func, go_class_name);
        }
    }
}

// -------------------------------------------------------------------------
// cgo_glue_gen.go — single CGo file consolidating all C function calls
// -------------------------------------------------------------------------

void GoEmitter::GenerateGlueFile(const ParsedFFI& parsed_ffi, const fs::path& out_dir)
{
    const fs::path path = out_dir / "cgo_glue_gen.go";
    ConditionalFileWriter writer(path);
    if (!writer.is_open())
    {
        std::println(stderr, "Error: cannot create {}", path.string());
        return;
    }

    WriteGeneratedHeader(writer);
    writer << "package wx\n\n";

    // CGo preamble — all includes and extern declarations
    writer << "/*\n";
    writer << "#include \"kwx_classes.h\"\n";
    writer << "#include \"kwx_events.h\"\n";
    writer << "#include \"kwx_keys.h\"\n";
    writer << "#include \"kwx_constants.h\"\n";
    writer << "#include <stdlib.h>\n";

    // Extern declarations for defs constants (defined in kwx_defs.cpp, no header)
    if (!parsed_ffi.constants.empty())
    {
        writer << "\n// extern declarations for defs constants (from kwx_defs.cpp)\n";
        for (const auto& constant: parsed_ffi.constants)
        {
            if (constant.return_type == "int")
            {
                writer << "extern int " << constant.export_name << "(void);\n";
            }
            else
            {
                writer << "extern void* " << constant.export_name << "(void);\n";
            }
        }
    }

    writer << "*/\n";
    writer << "import \"C\"\n\n";
    writer << "import \"unsafe\"\n\n";

    // boolToInt helper — used by glue functions for TBool parameters
    writer << "// boolToInt converts a Go bool to C.int for use in CGo calls.\n";
    writer << "func boolToInt(b bool) C.int {\n";
    writer << "\tif b {\n";
    writer << "\t\treturn 1\n";
    writer << "\t}\n";
    writer << "\treturn 0\n";
    writer << "}\n\n";

    // wxString utility glue — bridging Go strings to wxWidgets C++ strings.
    // Called from helpers_gen.go (pure Go) to keep class files CGo-free.
    writer << "// cgo_NewWxString creates a heap-allocated wxString from a Go string.\n";
    writer << "func cgo_NewWxString(s string) unsafe.Pointer {\n";
    writer << "\tcs := C.CString(s)\n";
    writer << "\tdefer C.free(unsafe.Pointer(cs))\n";
    writer << "\treturn C.wxString_CreateUTF8(cs)\n";
    writer << "}\n\n";
    writer << "// cgo_FreeWxString deletes a wxString allocated by the C++ side.\n";
    writer << "func cgo_FreeWxString(ptr unsafe.Pointer) { C.wxString_Delete(ptr) }\n\n";
    writer << "// cgo_WxStringToGoAndFree extracts a Go string from a wxString pointer\n";
    writer << "// via a transient UTF-8 buffer, then frees both objects.\n";
    writer << "func cgo_WxStringToGoAndFree(ptr unsafe.Pointer) string {\n";
    writer << "\tbuf := C.kwxUtf8Buffer_Create(ptr)\n";
    writer << "\ts := C.GoString(C.kwxUtf8Buffer_Data(buf))\n";
    writer << "\tC.kwxUtf8Buffer_Delete(buf)\n";
    writer << "\tC.wxString_Delete(ptr)\n";
    writer << "\treturn s\n";
    writer << "}\n\n";

    size_t glue_count = 0;
    // One glue function per C symbol: a symbol declared in a class header and again
    // in a standalone header must not produce two cgo_ wrappers.
    std::unordered_set<std::string> emitted_symbols;

    // --- Class method glue functions ---
    writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n";
    writer << "// Class method glue functions\n";
    writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n\n";

    for (const auto& class_decl: parsed_ffi.classes)
    {
        for (const auto& func: class_decl.methods)
        {
            if (!IsValidFunction(func))
            {
                continue;
            }
            if (!emitted_symbols.insert(CFuncName(func)).second)
            {
                continue;
            }
            EmitGlueFunction(writer, func);
            ++glue_count;
        }
    }

    // --- Free function glue ---
    const std::vector<GoFreeFunction> free_functions = CollectFreeFunctions(parsed_ffi);
    if (!free_functions.empty())
    {
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n";
        writer << "// Free function glue\n";
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n\n";

        for (const auto& func: free_functions)
        {
            if (!emitted_symbols.insert(CFuncName(*func.decl)).second)
            {
                continue;
            }
            EmitGlueFunction(writer, *func.decl);
            ++glue_count;
        }
    }
    // --- Event glue functions ---
    if (!parsed_ffi.events.empty())
    {
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n";
        writer << "// Event glue functions\n";
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n\n";

        for (const auto& event: parsed_ffi.events)
        {
            writer << "func cgo_" << event.export_name << "() int { return int(C."
                   << event.export_name << "()) }\n";
            ++glue_count;
        }
        writer << "\n";
    }

    // --- Key glue functions ---
    if (!parsed_ffi.keys.empty())
    {
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n";
        writer << "// Key glue functions\n";
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n\n";

        for (const auto& key_decl: parsed_ffi.keys)
        {
            writer << "func cgo_" << key_decl.export_name << "() int { return int(C."
                   << key_decl.export_name << "()) }\n";
            ++glue_count;
        }
        writer << "\n";
    }

    // --- Constant glue functions ---
    if (!parsed_ffi.constants.empty())
    {
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n";
        writer << "// Constant glue functions\n";
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n\n";

        for (const ConstantDecl* constant: CollectConstants(parsed_ffi))
        {
            if (constant->return_type == "int")
            {
                writer << "func cgo_" << constant->export_name << "() int { return int(C."
                       << constant->export_name << "()) }\n";
            }
            else
            {
                writer << "func cgo_" << constant->export_name
                       << "() unsafe.Pointer { return unsafe.Pointer(C." << constant->export_name
                       << "()) }\n";
            }
            ++glue_count;
        }
        writer << "\n";
    }

    std::ignore = writer.Flush();
    std::println(stderr, "  cgo_glue_gen.go:  {:L} glue functions{}", glue_count,
                 writer.WasWritten() ? "" : " (unchanged)");
}

// NOLINTEND(readability-magic-string)
