#pragma once

// MSAA (Microsoft Active Accessibility) query surface.
//
// wxWidgets' accessible objects are reachable from kwxFFI through
// wxAccessible, but the layer the operating system exposes for them
// (IAccessible plus AccessibleObjectFromWindow / AccessibleChildren /
// GetRoleText) is a Win32 COM API that no language backend can call without
// hand-writing vtables. These entry points give every backend the same
// read-only view a diagnostic tool needs.
//
// Every `accessible` parameter is an IAccessible* obtained from
// kwxMSAA_FromWindow or one of the child getters below. Only MSW has this
// API; on every other platform each entry point still exists and returns 0,
// an empty string or a null pointer, so the generated bindings are identical
// everywhere.

#ifdef __cplusplus
extern "C"
{
#endif

    // Returns the IAccessible* the OS exposes for window's objectId (pass
    // wxOBJID_CLIENT for the client area), or null when it cannot be obtained.
    // Release it with kwxMSAA_Release.
    EXPORT void* kwxMSAA_FromWindow(TClass(wxWindow) window, int objectId);

    // Releases an IAccessible* obtained from this header. Null is accepted.
    EXPORT void kwxMSAA_Release(void* accessible);

    // get_accChildCount(); -1 when the count cannot be obtained.
    EXPORT int kwxMSAA_GetChildCount(void* accessible);

    // get_accName(). The result is a strdup()ed UTF-8 string owned by the
    // caller, freed with wxCFree, and is empty when the call fails.
    EXPORT TString kwxMSAA_GetName(void* accessible, int childId);

    // get_accRole() followed by GetRoleText(), the same text MSAA reports.
    // strdup()ed UTF-8 string owned by the caller, freed with wxCFree.
    EXPORT TString kwxMSAA_GetRoleText(void* accessible, int childId);

    // get_accValue(). strdup()ed UTF-8 string owned by the caller.
    EXPORT TString kwxMSAA_GetValue(void* accessible, int childId);

    // get_accDescription(). strdup()ed UTF-8 string owned by the caller.
    EXPORT TString kwxMSAA_GetDescription(void* accessible, int childId);

    // kwxMSAA_GetName() etc. cannot tell an accessible object that answers with an
    // empty string from one where the COM call failed: both arrive at a binding as an
    // empty string. These companions store the call's HRESULT in *result, so a caller
    // can honour the real distinction -- 0 is S_OK, anything else means the call
    // failed and the returned string is empty because there is none.
    // The string has the same ownership as the non-WithStatus form: strdup()ed UTF-8
    // owned by the caller, released with wxCFree, and null when the call failed.
    // On platforms without MSAA, *result is -1 and the function returns null.
    EXPORT TString kwxMSAA_GetNameWithStatus(void* accessible, int childId, TIntOut result);
    EXPORT TString kwxMSAA_GetRoleTextWithStatus(void* accessible, int childId, TIntOut result);
    EXPORT TString kwxMSAA_GetValueWithStatus(void* accessible, int childId, TIntOut result);
    EXPORT TString kwxMSAA_GetDescriptionWithStatus(void* accessible, int childId, TIntOut result);

    // get_accState(); -1 when the state cannot be obtained.
    EXPORT int kwxMSAA_GetState(void* accessible, int childId);

    // get_accChild(childId) as an IAccessible*, or null when that child is a
    // simple element rather than an object. Release with kwxMSAA_Release.
    EXPORT void* kwxMSAA_GetChild(void* accessible, int childId);

    // AccessibleChildren(): the number of children the OS enumerates, or -1 when
    // the call fails. This is the count the accessibility layer itself reports,
    // which can differ from kwxMSAA_GetChildCount.
    EXPORT int kwxMSAA_GetAccessibleChildCount(void* accessible);

    // AccessibleChildren() child at a 0-based index, as an IAccessible*, or null
    // when that child is a simple element. Release with kwxMSAA_Release.
    EXPORT void* kwxMSAA_GetAccessibleChild(void* accessible, int index);

#ifdef __cplusplus
}  // extern "C"
#endif
