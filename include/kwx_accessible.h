#pragma once

// wxAccessible — accessibility object driven by foreign-language callbacks.
//
// wxAccessible itself only exists on MSW; wx/access.h includes
// wx/msw/ole/access.h there and every other platform declares only
// wxAccessibleBase. The alias below makes the class block compile on GTK and
// macOS builds, where the implementation derives from wxAccessibleBase.
//
// Every declaration is guarded by wxUSE_ACCESSIBILITY because neither the
// accessibility classes nor the wxACC_* constants exist without it. kwxgen
// skips preprocessor lines, so the guarded block is still parsed for the
// bindings.

#if wxUSE_ACCESSIBILITY

    #if !defined(__WXMSW__)
using wxAccessible = wxAccessibleBase;
    #endif

// ---------------------------------------------------------------------------
// wxAccessible — kwxAccessible callback helper (see kwx_helper_accessible.h)
// ---------------------------------------------------------------------------

TClassDefExtend(wxAccessible, wxAccessibleBase) TClass(wxAccessible)
    wxAccessible_Create(TClass(wxWindow) win, void* pObject);
void wxAccessible_Delete(TSelf(wxAccessible) pObject);
TClass(wxWindow) wxAccessible_GetWindow(TSelf(wxAccessible) pObject);
void wxAccessible_SetWindow(TSelf(wxAccessible) pObject, TClass(wxWindow) win);
int wxAccessible_NotifyEvent(int eventType, TClass(wxWindow) win, int objectType, int objectId);
void wxAccessible_SetOnHitTest(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetLocation(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnNavigate(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetName(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetChildCount(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetChild(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetParent(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnDoDefaultAction(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetDefaultAction(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetDescription(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetHelpText(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetKeyboardShortcut(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetRole(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetState(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetValue(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnSelect(TSelf(wxAccessible) pObject, void* pFunction);
void wxAccessible_SetOnGetFocus(TSelf(wxAccessible) pObject, void* pFunction);

// ---------------------------------------------------------------------------
// wxWindow — accessibility methods
// ---------------------------------------------------------------------------

// The window takes ownership of the accessible object: wxWindowBase stores the
// pointer and deletes it in its own destructor. wxAccessible_Delete therefore
// becomes a no-op for the transferred pointer — a window-owned instance is
// intentionally left alive and freed by the window.
TClassDefExtend(wxWindow, wxWindowBase)

    void wxWindow_SetAccessible(TSelf(wxWindow) pObject, TClass(wxAccessible) accessible);
TClass(wxAccessible) wxWindow_GetAccessible(TSelf(wxWindow) pObject);
TClass(wxAccessible) wxWindow_GetOrCreateAccessible(TSelf(wxWindow) pObject);
void wxWindow_SetAccessibleName(TSelf(wxWindow) pObject, TClass(wxString) name);

#endif  // wxUSE_ACCESSIBILITY
