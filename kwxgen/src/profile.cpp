/////////////////////////////////////////////////////////////////////////////
// Purpose:   Generation profiles that filter the parsed FFI surface
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "profile.h"

#include <array>
#include <unordered_map>
#include <unordered_set>

// Deepest parent chain that will be walked while collecting references. Guards against a
// malformed parent_map containing a cycle.
static constexpr int MAX_PARENT_DEPTH = 50;

// Macro names that name a class in a return type or parameter.
static constexpr std::string_view MACRO_TCLASS = "TClass";
static constexpr std::string_view MACRO_TCLASS_DEF = "TClassDef";
static constexpr std::string_view MACRO_TSELF = "TSelf";

static constexpr std::string_view PROFILE_FULL = "full";
static constexpr std::string_view PROFILE_GUI = "gui";

[[nodiscard]] static bool IsClassReturnMacro(std::string_view macro_name)
{
    return macro_name == MACRO_TCLASS || macro_name == MACRO_TCLASS_DEF;
}

[[nodiscard]] static bool IsClassParamMacro(std::string_view macro_name)
{
    return macro_name == MACRO_TCLASS || macro_name == MACRO_TCLASS_DEF ||
           macro_name == MACRO_TSELF;
}

// Append every class name referenced by a signature on this class: its ancestors, its
// mixins, and every class named by a return type or parameter type.
static void CollectReferences(const ClassInfo& class_info, const ParsedFFI& ffi_data,
                              std::vector<std::string>& references)
{
    std::string current = class_info.name;
    for (int depth = 0; depth < MAX_PARENT_DEPTH; ++depth)
    {
        const std::unordered_map<std::string, std::string>::const_iterator parent_iter =
            ffi_data.parent_map.find(current);
        if (parent_iter == ffi_data.parent_map.end() || parent_iter->second.empty())
        {
            break;
        }
        references.push_back(parent_iter->second);
        current = parent_iter->second;
    }

    const std::unordered_map<std::string, std::vector<std::string>>::const_iterator mixin_iter =
        ffi_data.mixin_map.find(class_info.name);
    if (mixin_iter != ffi_data.mixin_map.end())
    {
        for (const std::string& mixin_name: mixin_iter->second)
        {
            references.push_back(mixin_name);
        }
    }

    for (const FunctionDecl& method: class_info.methods)
    {
        if (IsClassReturnMacro(method.return_macro) && !method.return_arg.empty())
        {
            references.push_back(method.return_arg);
        }
        for (const Param& param: method.params)
        {
            if (IsClassParamMacro(param.macro_name) && !param.macro_arg.empty())
            {
                references.push_back(param.macro_arg);
            }
        }
    }
}

std::vector<std::string_view> ProfileNames()
{
    static constexpr std::array<std::string_view, 2> PROFILE_NAME_LIST { PROFILE_FULL,
                                                                         PROFILE_GUI };
    return { PROFILE_NAME_LIST.begin(), PROFILE_NAME_LIST.end() };
}

bool IsKnownProfile(std::string_view profile_name)
{
    for (const std::string_view known_profile: ProfileNames())
    {
        if (known_profile == profile_name)
        {
            return true;
        }
    }
    return false;
}

std::string DefaultProfileForLanguage(std::string_view lang)
{
    if (lang == "go" || lang == "julia")
    {
        return std::string { PROFILE_GUI };
    }
    return std::string { PROFILE_FULL };
}

// Classes the `gui` profile drops. These are base-utility classes whose functionality the Go
// and Julia standard libraries already provide, so wrapping them would duplicate the runtime.
//
// The list is derived from the parsed model and recorded, with method counts and owning
// phases, in `.private/coverage_expansion_inventory.md`. Every class added to the headers must
// be classified there and, when it is base-utility, added here; an unclassified base-utility
// class leaks into the Go/Julia surface. Exact names only — no wildcards.
//
// Names the current parse does not declare yet are kept so a later phase cannot leak them.
// A class listed here is still emitted when a retained class names it in a signature, because
// ApplyProfile adds referenced classes back.
static const std::unordered_set<std::string>& GuiExcludedClasses()
{
    static const std::unordered_set<std::string> excluded_classes {
        // Helper object for the wxCmdLineEntryDesc table; only useful with wxCmdLineParser.
        "kwxCmdLineDesc",
        "wxArray",
        "wxArrayString",
        "wxBufferedInputStream",
        "wxBufferedOutputStream",
        "wxCmdLineParser",
        "wxCommandLineParser",
        "wxCondition",
        "wxCountingOutputStream",
        "wxCriticalSection",
        "wxCriticalSectionLocker",
        "wxDataInputStream",
        "wxDataOutputStream",
        "wxDateSpan",
        "wxDateTime",
        "wxDynamicLibrary",
        "wxExecuteEnv",
        "wxFFile",
        "wxFFileInputStream",
        "wxFFileOutputStream",
        "wxFTP",
        "wxFileInputStream",
        "wxFileOutputStream",
        "wxFilterInputStream",
        "wxFilterOutputStream",
        "wxGzipInputStream",
        "wxGzipOutputStream",
        "wxHTTP",
        "wxHashMap",
        "wxIPV4address",
        "wxIPaddress",
        "wxInputStream",
        "wxList",
        "wxMemoryBuffer",
        "wxMemoryInputStream",
        "wxMemoryOutputStream",
        "wxMutex",
        "wxMutexLocker",
        "wxOutputStream",
        "wxPathList",
        "wxProcess",
        "wxProcessEvent",
        "wxProcessEx",
        "wxProtocol",
        "wxRegEx",
        "wxSemaphore",
        "wxSockAddress",
        "wxSocketBase",
        "wxSocketClient",
        "wxSocketEvent",
        "wxSocketInputStream",
        "wxSocketOutputStream",
        "wxSocketServer",
        "wxStopWatch",
        "wxStreamBase",
        "wxStreamBuffer",
        "wxStreamToTextRedirector",
        "wxStringTokenizer",
        "wxTarEntry",
        "wxTarInputStream",
        "wxTarOutputStream",
        "wxTempFile",
        "wxTextFile",
        "wxTextInputStream",
        "wxTextOutputStream",
        "wxThread",
        "wxTimeSpan",
        "wxURI",
        "wxURL",
        "wxVariant",
        "wxVariantVector",
        "wxXmlAttribute",
        "wxXmlDocument",
        "wxXmlNode",
        "wxZipEntry",
        "wxZipInputStream",
        "wxZipOutputStream",
        "wxZlibInputStream",
        "wxZlibOutputStream",
    };
    return excluded_classes;
}

ParsedFFI ApplyProfile(const ParsedFFI& ffi_data, std::string_view profile)
{
    // Anything other than `gui` leaves the model untouched.
    if (profile != PROFILE_GUI)
    {
        return ffi_data;
    }

    const std::unordered_set<std::string>& excluded_classes = GuiExcludedClasses();

    std::unordered_map<std::string, const ClassInfo*> class_lookup;
    for (const ClassInfo& class_info: ffi_data.classes)
    {
        class_lookup.emplace(class_info.name, &class_info);
    }

    std::unordered_set<std::string> retained_names;
    for (const ClassInfo& class_info: ffi_data.classes)
    {
        if (!excluded_classes.contains(class_info.name))
        {
            retained_names.insert(class_info.name);
        }
    }

    // Fixpoint closure: drop the excluded classes, then add back any class still referenced
    // by a retained signature. Repeat until a pass adds nothing.
    bool added_class = true;
    while (added_class)
    {
        added_class = false;

        std::vector<std::string> references;
        for (const std::string& retained_name: retained_names)
        {
            const std::unordered_map<std::string, const ClassInfo*>::const_iterator class_iter =
                class_lookup.find(retained_name);
            if (class_iter == class_lookup.end())
            {
                continue;
            }
            CollectReferences(*(class_iter->second), ffi_data, references);
        }

        for (const std::string& reference: references)
        {
            if (!class_lookup.contains(reference))
            {
                continue;
            }
            if (retained_names.insert(reference).second)
            {
                added_class = true;
            }
        }
    }

    ParsedFFI filtered_ffi;
    for (const ClassInfo& class_info: ffi_data.classes)
    {
        if (retained_names.contains(class_info.name))
        {
            filtered_ffi.classes.push_back(class_info);
        }
    }

    filtered_ffi.events = ffi_data.events;
    filtered_ffi.keys = ffi_data.keys;
    filtered_ffi.constants = ffi_data.constants;
    filtered_ffi.free_functions = ffi_data.free_functions;
    filtered_ffi.parent_map = ffi_data.parent_map;
    filtered_ffi.mixin_map = ffi_data.mixin_map;
    filtered_ffi.lib_name = ffi_data.lib_name;

    return filtered_ffi;
}
