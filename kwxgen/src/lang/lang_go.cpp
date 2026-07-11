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

constexpr size_t kFixedFileCount = 6;  // cgo_glue, helpers, constants, events, keys, functions

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
//   "kwxDropTarget"  → "KwxDropTarget" (capitalise 'kwx' — do NOT strip it, or kwx*
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
    // kwx* classes: capitalise to "Kwx" rather than stripping, so that
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

[[nodiscard]] static bool IsFixedGoGeneratedFile(const std::string& filename)
{
    return filename == "cgo_glue_gen.go" || filename == "helpers_gen.go" ||
           filename == "constants_gen.go" || filename == "events_gen.go" ||
           filename == "keys_gen.go" || filename == "functions_gen.go";
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

// Convert one Param to one or more GoParams.
static std::vector<GoParam> ConvertParam(const Param& param)
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
            const std::string n = RenameGoKeyword(field);
            result.push_back({ n, "int", "C.int(" + n + ")", "", "", false });
        }
        return result;
    }

    if (param.macro_name == "TPointLong" || param.macro_name == "TSizeLong" ||
        param.macro_name == "TRectLong" || param.macro_name == "TVectorLong")
    {
        for (auto& field: SplitMacroArg(param.macro_arg))
        {
            const std::string n = RenameGoKeyword(field);
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
            const std::string n = RenameGoKeyword(field);
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
            const std::string n = RenameGoKeyword(field);
            result.push_back({ n, "unsafe.Pointer", n, "", "", true });
        }
        return result;
    }

    if (param.macro_name == "TSizeOutDouble")
    {
        // Output double* geometry params — cast to (*C.double) for C call
        for (auto& field: SplitMacroArg(param.macro_arg))
        {
            const std::string n = RenameGoKeyword(field);
            result.push_back({ n, "unsafe.Pointer", "(*C.double)(" + n + ")", "", "", true });
        }
        return result;
    }

    if (param.macro_name == "TColorRGB")
    {
        for (auto& field: SplitMacroArg(param.macro_arg))
        {
            const std::string n = RenameGoKeyword(field);
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
            const std::string first_name = RenameGoKeyword(names[0]);
            const std::string second_name = RenameGoKeyword(names[1]);
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
            const std::string first_name = RenameGoKeyword(names[0]);
            const std::string second_name = RenameGoKeyword(names[1]);
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
            const std::string first_name = RenameGoKeyword(names[0]);   // data pointer
            const std::string second_name = RenameGoKeyword(names[1]);  // length
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
            RenameGoKeyword(param.param_name.empty() ? "arr" : param.param_name);
        result.push_back({ name, "unsafe.Pointer", name, "", "", true });
        return result;
    }

    // Single parameter
    GoParam go_param;
    go_param.name = RenameGoKeyword(param.param_name.empty() ? "arg" : param.param_name);

    if (param.macro_name == "TClass" && param.macro_arg == "wxString")
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
        else if (raw_type == "unsigned long" || raw_type == "wxUIntPtr")
        {
            go_param.go_type = "uint";
            go_param.cgo_expr = "C.ulong(" + go_param.name + ")";
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
            // Any other pointer type
            go_param.go_type = "unsafe.Pointer";
            go_param.cgo_expr = go_param.name;
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
    if (func_decl.return_type == "int" || func_decl.return_type == "long" ||
        func_decl.return_type == "TArrayLen" || func_decl.return_type == "TByteStringLen" ||
        func_decl.return_type == "size_t" || func_decl.return_type == "time_t")
    {
        return "int";
    }
    if (func_decl.return_type == "unsigned" || func_decl.return_type == "unsigned int" ||
        func_decl.return_type == "wxUIntPtr" || func_decl.return_type == "unsigned long")
    {
        return "uint";
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

// Check if a return type needs the "unsafe" import
[[nodiscard]] static bool ReturnNeedsUnsafe(const FunctionDecl& func_decl)
{
    // TClass(wxString) → Go "string", not unsafe.Pointer
    if (func_decl.return_macro == "TClass" && func_decl.return_arg == "wxString")
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

// Check if any method in the class needs the "unsafe" import
[[nodiscard]] static bool ClassNeedsUnsafe(const ClassInfo& class_info)
{
    for (auto& method: class_info.methods)
    {
        // True constructors emit *ClassName in the class file (not unsafe.Pointer)
        // — no explicit unsafe.Pointer in source text, so don't count them.
        const bool is_true_constructor =
            method.is_constructor && !method.has_self && method.return_type != "TBool";
        if (!is_true_constructor && ReturnNeedsUnsafe(method))
        {
            return true;
        }
        bool seen_self = false;
        for (auto& param: method.params)
        {
            if (param.macro_name == "TSelf")
            {
                if (!seen_self)
                {
                    seen_self = true;
                    continue;  // first TSelf is receiver, not a param
                }
                return true;  // additional TSelf emitted as unsafe.Pointer
            }
            const std::vector<GoParam> go_params = ConvertParam(param);
            for (const auto& go_param: go_params)
            {
                if (go_param.needs_unsafe)
                {
                    return true;
                }
            }
        }
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

    if (func_decl.has_self)
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
    if (func_decl.return_type == "int" || func_decl.return_type == "long" ||
        func_decl.return_type == "TArrayLen" || func_decl.return_type == "TByteStringLen" ||
        func_decl.return_type == "size_t" || func_decl.return_type == "time_t")
    {
        return "int";
    }
    if (func_decl.return_type == "unsigned" || func_decl.return_type == "unsigned int" ||
        func_decl.return_type == "wxUIntPtr" || func_decl.return_type == "unsigned long")
    {
        return "uint";
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

    // Self parameter (skipped by ConvertParam — handle explicitly)
    if (func_decl.has_self)
    {
        output << "self unsafe.Pointer";
        c_call_args.emplace_back("self");
        first_param = false;
    }

    bool first_tself = true;
    for (const auto& param: func_decl.params)
    {
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
            const std::string name = param.param_name.empty() ? "other" : param.param_name;
            output << name << " unsafe.Pointer";
            c_call_args.push_back(name);
            first_param = false;
            continue;
        }
        for (const auto& go_param: ConvertParam(param))
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
    std::vector<std::vector<GoParam>> param_groups;
    bool seen_self = false;  // track whether we've seen the receiver TSelf
    for (const auto& param: func_decl.params)
    {
        if (param.macro_name == "TSelf")
        {
            if (!seen_self)
            {
                seen_self = true;
                continue;  // first TSelf already handled as receiver
            }
            // Additional TSelf — emit as unsafe.Pointer parameter
            const std::string name = param.param_name.empty() ? "other" : param.param_name;
            GoParam go_param;
            go_param.name = name;
            go_param.go_type = "unsafe.Pointer";
            go_param.cgo_expr = name;
            go_param.glue_pass_expr = name;
            go_param.needs_unsafe = true;
            param_groups.push_back({ go_param });
            continue;
        }
        param_groups.push_back(ConvertParam(param));
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
    else
    {
        // Glue already returns the correct Go type
        output << "\treturn " << glue_call << "\n";
    }

    output << "}\n\n";
}

// Emit a C free function (class_name empty, no TSelf) as a package-level Go function.
// kwxMessageBox → MessageBox, kwxFoo → Foo, wxFoo → Foo
static void EmitFreeFunction(std::ostream& output, const FunctionDecl& func_decl)
{
    // Strip kwx/wx prefix and capitalize for an exported Go identifier.
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

    std::vector<std::vector<GoParam>> param_groups;
    param_groups.reserve(func_decl.params.size());
    for (const auto& param: func_decl.params)
    {
        param_groups.push_back(ConvertParam(param));
    }

    const std::string go_ret_type = GoReturnType(func_decl, "");

    output << "func " << SafeGoIdentifier(name) << "(";
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
    else
    {
        output << "\treturn " << glue_call << "\n";
    }

    output << "}\n\n";
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
    writer << "\tptr unsafe.Pointer\n";
    writer << "}\n";
    writer << "\n";
    writer << "// Ptr returns the underlying wxWidgets object pointer.\n";
    writer << "func (o *BaseObject) Ptr() unsafe.Pointer { return o.ptr }\n";
    writer << "\n";
    writer << "// SetPtr sets the underlying wxWidgets object pointer.\n";
    writer << "func (o *BaseObject) SetPtr(p unsafe.Pointer) { o.ptr = p }\n";
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
    if (parsed_ffi.free_functions.empty())
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

    // Check if any free function needs the "unsafe" import
    bool needs_unsafe = false;
    for (const auto& func: parsed_ffi.free_functions)
    {
        if (IsValidFunction(func) && FunctionNeedsUnsafe(func))
        {
            needs_unsafe = true;
            break;
        }
    }
    if (needs_unsafe)
    {
        writer << "import \"unsafe\"\n\n";
    }

    size_t count = 0;
    for (const auto& func: parsed_ffi.free_functions)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }
        EmitFreeFunction(writer, func);
        ++count;
    }

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

    // Sort constants by name for stable output
    std::vector<ConstantDecl> sorted = parsed_ffi.constants;
    std::ranges::sort(sorted,
                      [](const ConstantDecl& left, const ConstantDecl& right)
                      {
                          return left.constant_name < right.constant_name;
                      });

    writer << "var (\n";
    for (const auto& constant: sorted)
    {
        writer << "\t" << constant.constant_name << " = " << GoConstantExpr(constant) << "\n";
    }
    writer << ")\n";

    std::ignore = writer.Flush();
    std::println(stderr, "  constants_gen.go: {:L} constants{}", parsed_ffi.constants.size(),
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

    // Classes already hand-defined in types.go — skip generation to avoid
    // redeclaration errors.  Add entries here whenever a new class is added
    // to the hand-maintained types.go file.
    static const std::unordered_set<std::string> kHandMaintainedClasses = {
        "wxPoint",
        "wxSize",
        "wxRect",
    };

    // Only include classes that will actually be generated (have methods and
    // aren't hand-maintained).  This prevents parent-embed resolution from
    // referencing types that will never be emitted — e.g. wxObject has no
    // wrapped methods, so "Object" would never be defined, yet child classes
    // would try to embed it.  Those classes fall back to BaseObject instead.
    std::unordered_set<std::string> wrapped_classes;
    wrapped_classes.reserve(parsed_ffi.classes.size());
    for (const auto& class_decl: parsed_ffi.classes)
    {
        if (!class_decl.methods.empty() && !kHandMaintainedClasses.contains(class_decl.name))
        {
            wrapped_classes.insert(class_decl.name);
        }
    }

    std::unordered_set<std::string> expected_class_files;
    expected_class_files.reserve(parsed_ffi.classes.size());

    for (const auto& class_decl: parsed_ffi.classes)
    {
        if (class_decl.methods.empty())
        {
            continue;
        }
        if (kHandMaintainedClasses.contains(class_decl.name))
        {
            continue;  // defined in types.go — skip to avoid redeclaration
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
    const bool needs_unsafe = ClassNeedsUnsafe(class_info);

    // Header
    WriteGeneratedHeader(output);
    output << "package wx\n\n";

    // Pure Go — no CGo preamble (all C calls go through cgo_glue_gen.go)
    if (needs_unsafe)
    {
        output << "import \"unsafe\"\n\n";
    }

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

    // Emit methods
    for (const auto& func: class_info.methods)
    {
        if (!IsValidFunction(func))
        {
            continue;
        }

        // Free functions (class_name empty, no TSelf) — emit as package-level Go functions.
        // These are bare C functions (e.g. kwxMessageBox) that appear inside a class block
        // in the header but have no class prefix; route them out as free functions.
        if (func.class_name.empty() && !func.has_self)
        {
            EmitFreeFunction(output, func);
            continue;
        }

        const bool is_true_constructor =
            func.is_constructor && !func.has_self && func.return_type != "TBool";

        if (is_true_constructor)
        {
            EmitConstructor(output, class_info, func, go_class_name);
        }
        else if (func.is_destructor)
        {
            // Only treat as a true class destructor if there are no non-self parameters.
            // e.g. wxChoice_Delete(self, int index) is a list-item method, not a
            // destructor.
            bool has_non_self_params = false;
            for (const auto& param: func.params)
            {
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
            EmitGlueFunction(writer, func);
            ++glue_count;
        }
    }

    // --- Free function glue ---
    if (!parsed_ffi.free_functions.empty())
    {
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n";
        writer << "// Free function glue\n";
        writer << "// " << std::string(COMMENT_BANNER_WIDTH, '-') << "\n\n";

        for (const auto& func: parsed_ffi.free_functions)
        {
            if (!IsValidFunction(func))
            {
                continue;
            }
            EmitGlueFunction(writer, func);
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

        for (const auto& constant: parsed_ffi.constants)
        {
            if (constant.return_type == "int")
            {
                writer << "func cgo_" << constant.export_name << "() int { return int(C."
                       << constant.export_name << "()) }\n";
            }
            else
            {
                writer << "func cgo_" << constant.export_name
                       << "() unsafe.Pointer { return unsafe.Pointer(C." << constant.export_name
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
