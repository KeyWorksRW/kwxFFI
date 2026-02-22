#pragma once

// Go type mapping table for CGo code generation.
// Maps C/FFI macro types to Go types, CGo types, and conversion patterns.
// Used by lang_go.cpp for both constants (Phase 5) and class wrappers (Phase 6).

#include <string>
#include <string_view>
#include <unordered_map>

namespace kwxgen
{

    // Describes how a C/FFI type maps to a Go type and its CGo conversion.
    struct GoTypeMapping
    {
        std::string go_type;        // Go type: "int", "bool", "string", "unsafe.Pointer", "float64"
        std::string cgo_type;       // CGo type: "C.int", "C.int", "C.double", "unsafe.Pointer"
        std::string to_cgo;         // Conversion pattern from Go to CGo (use {v} as placeholder)
        std::string from_cgo;       // Conversion pattern from CGo to Go (use {v} as placeholder)
        bool needs_unsafe = false;  // Whether the conversion needs "unsafe" import
    };

    // Returns the Go type mapping for a given C macro name.
    // For plain types, macro_name is the type itself ("int", "double", "void*").
    // For macro types, macro_name is the macro ("TClass", "TSelf", "TBool", etc.).
    inline GoTypeMapping GetGoTypeMapping(const std::string& macro_name,
                                          const std::string& macro_arg = "")
    {
        // Macro-wrapped types
        if (macro_name == "TClass" || macro_name == "TSelf")
        {
            return { "unsafe.Pointer", "unsafe.Pointer", "{v}", "{v}", true };
        }
        if (macro_name == "TBool")
        {
            return { "bool", "C.int", "C.int(boolToInt({v}))", "intToBool({v})", false };
        }
        if (macro_name == "TString")
        {
            // Input string: Go string → wxString bridge via NewWxString / defer Delete
            return { "string", "unsafe.Pointer", "/* wxString bridge */", "/* wxString bridge */",
                     true };
        }
        if (macro_name == "TStringOut")
        {
            // Output string: wxString* → Go string
            return { "string", "unsafe.Pointer", "", "GoString({v})", true };
        }
        if (macro_name == "TStringVoid")
        {
            // String parameter passed as void* (for some legacy APIs)
            return { "string", "unsafe.Pointer", "/* wxString bridge */", "/* wxString bridge */",
                     true };
        }
        if (macro_name == "TPoint")
        {
            // Expands to two int params: x, y
            return { "int, int", "C.int, C.int", "C.int({v})", "int({v})", false };
        }
        if (macro_name == "TSize")
        {
            // Expands to two int params: w, h
            return { "int, int", "C.int, C.int", "C.int({v})", "int({v})", false };
        }
        if (macro_name == "TRect")
        {
            // Expands to four int params: x, y, w, h
            return { "int, int, int, int", "C.int, C.int, C.int, C.int", "C.int({v})", "int({v})",
                     false };
        }
        if (macro_name == "TArrayString")
        {
            // []string → count + C array pointer
            return { "[]string", "C.int, **C.char", "/* marshal string array */",
                     "/* unmarshal string array */", true };
        }
        if (macro_name == "TArrayInt")
        {
            // []int → count + C array pointer
            return { "[]int", "C.int, *C.int", "/* marshal int array */",
                     "/* unmarshal int array */", true };
        }

        // Plain C types
        if (macro_name == "int")
        {
            return { "int", "C.int", "C.int({v})", "int({v})", false };
        }
        if (macro_name == "long")
        {
            return { "int", "C.long", "C.long({v})", "int({v})", false };
        }
        if (macro_name == "size_t")
        {
            return { "int", "C.size_t", "C.size_t({v})", "int({v})", false };
        }
        if (macro_name == "unsigned" || macro_name == "unsigned int")
        {
            return { "uint", "C.uint", "C.uint({v})", "uint({v})", false };
        }
        if (macro_name == "unsigned long")
        {
            return { "uint", "C.ulong", "C.ulong({v})", "uint({v})", false };
        }
        if (macro_name == "double")
        {
            return { "float64", "C.double", "C.double({v})", "float64({v})", false };
        }
        if (macro_name == "float")
        {
            return { "float32", "C.float", "C.float({v})", "float32({v})", false };
        }
        if (macro_name == "void")
        {
            return { "", "", "", "", false };
        }
        if (macro_name == "void*")
        {
            return { "unsafe.Pointer", "unsafe.Pointer", "{v}", "{v}", true };
        }
        if (macro_name == "char*" || macro_name == "const char*")
        {
            return { "string", "*C.char", "C.CString({v})", "C.GoString({v})", false };
        }

        // Pointer types (e.g., "wxString*", "const wxColour*")
        if (macro_name.find('*') != std::string::npos)
        {
            return { "unsafe.Pointer", "unsafe.Pointer", "{v}", "{v}", true };
        }

        // Unknown / fallback — treat as int
        return { "int", "C.int", "C.int({v})", "int({v})", false };
    }

}  // namespace kwxgen
