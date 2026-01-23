#pragma once

#ifdef EXPORT
    #undef EXPORT
#endif

#if defined(_WIN32)
    #if defined(SHARED_LIBRARY)
        #define EXPORT     __declspec(dllexport)
        #define WXFFI_FUNC extern "C" __declspec(dllexport)
    #else
        #define EXPORT
        #define WXFFI_FUNC extern "C"
    #endif
#else  // not defined(_WIN32)
    #if defined(SHARED_LIBRARY)
        #define EXPORT     __attribute__((visibility("default")))
        #define WXFFI_FUNC extern "C" __attribute__((visibility("default")))
    #else
        #define EXPORT
        #define WXFFI_FUNC extern "C"
    #endif
#endif  // defined(_WIN32)

#ifdef _WIN32
    // REVIEW: [Randalphwa - 10-07-2024]
    // Use this until there is a way to know whether the library is being built as a dll or not
    #define WXFFI_EXPORT(TYPE, FUNC_NAME) TYPE FUNC_NAME
// REVIEW: [Randalphwa - 10-07-2024]
// This assumes that wxFFI_lang has been built as a dll which is not necessarily the case
// #define WXFFI_EXPORT(TYPE, FUNC_NAME) __declspec(dllexport) TYPE __cdecl FUNC_NAME
// #undef EXPORT
// #define EXPORT extern "C" __declspec(dllexport)
#else
    #define WXFFI_EXPORT(TYPE, FUNC_NAME) TYPE FUNC_NAME
#endif

// REVIEW: [Randalphwa - 10-07-2024]
// Default calling convention for C functiosn is cdecl so why are we specifying this?

#if defined(_MSC_VER)
    // Microsoft compiler
    #ifndef _cdecl
        #define _cdecl __cdecl
    #endif
#elif defined(__GNUC__)
    // GCC and Clang compilers
    #ifndef _cdecl
        #define _cdecl __attribute__((cdecl))
    #endif
#else
    // Other compilers
    #ifndef _cdecl
        #define _cdecl
    #endif
#endif

#define WXFFI_CONSTANT_INT(NAME, VAL) \
    WXFFI_EXPORT(int, exp##NAME)()    \
    {                                 \
        return (int) VAL;             \
    };
#define WXFFI_CONSTANT_STR(NAME, VAL)                           \
    WXFFI_EXPORT(wxString*, exp##NAME)()                        \
    {                                                           \
        return new wxString((const wchar_t*) VAL, wxConvLocal); \
    };
#ifdef __EWX_PREPROCESS
    #undef WXFFI_EXPORT
    #undef WXFFI_CONSTANT_INT
    #undef WXFFI_CONSTANT_STR
    #define WXFFI_CONSTANT_INT(NAME, VAL) def_const_int(#NAME, VAL);
    #define WXFFI_CONSTANT_STR(NAME, VAL) def_const_str(#NAME, VAL);
#endif
