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

// WXFFI_EXPORT - used for constant export functions in headers/implementations
#if defined(_WIN32)
    #if defined(SHARED_LIBRARY)
        #define WXFFI_EXPORT(TYPE, FUNC_NAME) __declspec(dllexport) TYPE FUNC_NAME
    #else
        #define WXFFI_EXPORT(TYPE, FUNC_NAME) TYPE FUNC_NAME
    #endif
#else  // Unix
    #if defined(SHARED_LIBRARY)
        #define WXFFI_EXPORT(TYPE, FUNC_NAME) __attribute__((visibility("default"))) TYPE FUNC_NAME
    #else
        #define WXFFI_EXPORT(TYPE, FUNC_NAME) TYPE FUNC_NAME
    #endif
#endif  // defined(_WIN32)

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
