#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace kwxgen
{

    struct Param
    {
        std::string raw_type;    // As written: "TClass(wxWindow)", "int", "TBool"
        std::string macro_name;  // "TClass", "TSelf", "TPoint", "" for plain types
        std::string macro_arg;   // "wxWindow", "x, y", "" for plain types
        std::string param_name;  // "parent", "id", "x" (may be empty for expanded macros)
    };

    struct FunctionDecl
    {
        std::string class_name;    // "wxButton" (empty for free functions)
        std::string method_name;   // "Create", "SetDefault", "GetLabel"
        std::string return_type;   // "void", "int", "TClass(wxButton)", "TBool"
        std::string return_macro;  // "TClass" if return is macro-wrapped
        std::string return_arg;    // "wxButton" if return is TClass(wxButton)
        std::vector<Param> params;
        bool is_constructor = false;  // true if method_name starts with "Create"
        bool is_destructor = false;   // true if method_name == "Delete"
        bool has_self = false;        // true if first param is TSelf(...)
    };

    struct ClassInfo
    {
        std::string name;    // "wxButton"
        std::string parent;  // "wxControl" (empty for TClassDef)
        std::vector<FunctionDecl> methods;
        bool is_window_derived = false;  // Computed: walks hierarchy to wxWindow
        bool is_object_derived = false;  // Computed: walks hierarchy to wxObject
    };

    struct EventDecl
    {
        std::string export_name;  // "expEVT_BUTTON"
        std::string event_name;   // "EVT_BUTTON"
    };

    struct KeyDecl
    {
        std::string export_name;  // "expK_BACK"
        std::string key_name;     // "K_BACK"
    };

    struct ConstantDecl
    {
        std::string export_name;    // "expwxID_ANY"
        std::string constant_name;  // "ID_ANY" or "wxBLACK"
        std::string return_type;    // "int", "wxString*", "const wxColour*", etc.
    };

    struct ParsedFFI
    {
        std::vector<ClassInfo> classes;
        std::vector<EventDecl> events;
        std::vector<KeyDecl> keys;
        std::vector<ConstantDecl> constants;
        std::vector<FunctionDecl> free_functions;  // Null_*, kwxSysErrorCode, etc.
        std::unordered_map<std::string, std::string> parent_map;
    };

}  // namespace kwxgen
