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
// bindings. A C translation unit (the cgo preamble) never defines wxUSE_* and
// cannot see the wxWidgets headers, so it takes the block unconditionally.

#if !defined(__cplusplus) || wxUSE_ACCESSIBILITY

    #if defined(__cplusplus) && !defined(__WXMSW__)
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
void wxAccessible_SetOnGetSelections(TSelf(wxAccessible) pObject, void* pFunction);

// ---------------------------------------------------------------------------
// wxAccessible — uniform single-thunk hooks (the …WithData family)
// ---------------------------------------------------------------------------

// A …WithData callback has the type
//
//     void (*)(void* data, void* arg1, void* arg2)
//
// `data` is the per-hook token given to that same setter -- not the pObject passed
// to wxAccessible_Create. Integers are delivered as (void*)(intptr_t)value; an
// unused position is NULL. The callback publishes its status with
// wxAccessible_SetHookResult(pObject, status) and its out-values with the matching
// Set…Result call before it returns. When it publishes no status, the override
// calls the base wxWindowAccessible implementation with the same arguments, so a
// callback declines a case by publishing nothing -- the rule the typed setters
// already follow. A …WithData setter takes precedence over the plain typed setter
// for the same hook. Passing a NULL pFunction clears it.
//
// Argument positions after `data`:
//
//   HitTest                 (intptr_t)x, (intptr_t)y
//   GetLocation             (intptr_t)elementId, NULL
//   Navigate                (intptr_t)navDir, (intptr_t)fromId
//   GetChildCount           NULL, NULL
//   GetChild                (intptr_t)childId, NULL
//   GetParent               NULL, NULL
//   DoDefaultAction         (intptr_t)childId, NULL
//   GetRole                 (intptr_t)childId, NULL
//   GetState                (intptr_t)childId, NULL
//   Select                  (intptr_t)childId, (intptr_t)selectFlags
//   GetFocus                NULL, NULL
//   GetSelections           the wxVariant* wxWidgets supplied, NULL
//   GetName, GetDefaultAction, GetDescription, GetHelpText, GetKeyboardShortcut,
//   GetValue                (intptr_t)childId, and the same const char* slot the
//                           typed callback receives as its `name` parameter, so
//                           the callback publishes with kwxAccString_SetValue(arg2,
//                           text)
//
// Result publishers by hook: HitTest -> SetHitTestResult(childId, childObject);
// GetLocation -> SetGetLocationResult(x, y, width, height), the final screen rect;
// Navigate -> SetNavigateResult(toId, toObject); GetChildCount ->
// SetGetChildCountResult(childCount); GetChild -> SetGetChildResult(child);
// GetParent -> SetGetParentResult(parent); GetRole -> SetGetRoleResult(role);
// GetState -> SetGetStateResult(state), a combination of wxACC_STATE_SYSTEM_*
// values carried as int here, the way src/kwx_defs.cpp exports them; GetFocus ->
// SetGetFocusResult(childId, child); the six string hooks publish their text
// through kwxAccString_SetValue; every hook publishes its status through
// SetHookResult. Published out-values are applied only when the published status is
// wxACC_OK, mirroring exactly what the typed branch does for that hook.
void wxAccessible_SetOnHitTestWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnGetLocationWithData(TSelf(wxAccessible) pObject, void* pFunction,
                                           void* data);
void wxAccessible_SetOnNavigateWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnGetNameWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnGetChildCountWithData(TSelf(wxAccessible) pObject, void* pFunction,
                                             void* data);
void wxAccessible_SetOnGetChildWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnGetParentWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnDoDefaultActionWithData(TSelf(wxAccessible) pObject, void* pFunction,
                                               void* data);
void wxAccessible_SetOnGetDefaultActionWithData(TSelf(wxAccessible) pObject, void* pFunction,
                                                void* data);
void wxAccessible_SetOnGetDescriptionWithData(TSelf(wxAccessible) pObject, void* pFunction,
                                              void* data);
void wxAccessible_SetOnGetHelpTextWithData(TSelf(wxAccessible) pObject, void* pFunction,
                                           void* data);
void wxAccessible_SetOnGetKeyboardShortcutWithData(TSelf(wxAccessible) pObject, void* pFunction,
                                                   void* data);
void wxAccessible_SetOnGetRoleWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnGetStateWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnGetValueWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnSelectWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnGetFocusWithData(TSelf(wxAccessible) pObject, void* pFunction, void* data);
void wxAccessible_SetOnGetSelectionsWithData(TSelf(wxAccessible) pObject, void* pFunction,
                                             void* data);
void wxAccessible_SetHookResult(TSelf(wxAccessible) pObject, int result);
void wxAccessible_SetHitTestResult(TSelf(wxAccessible) pObject, int childId, void* childObject);
void wxAccessible_SetGetLocationResult(TSelf(wxAccessible) pObject, int x, int y, int width,
                                       int height);
void wxAccessible_SetNavigateResult(TSelf(wxAccessible) pObject, int toId, void* toObject);
void wxAccessible_SetGetChildCountResult(TSelf(wxAccessible) pObject, int childCount);
void wxAccessible_SetGetChildResult(TSelf(wxAccessible) pObject, void* child);
void wxAccessible_SetGetParentResult(TSelf(wxAccessible) pObject, void* parent);
void wxAccessible_SetGetRoleResult(TSelf(wxAccessible) pObject, int role);
void wxAccessible_SetGetStateResult(TSelf(wxAccessible) pObject, int state);
void wxAccessible_SetGetFocusResult(TSelf(wxAccessible) pObject, int childId, void* child);

    #ifdef __cplusplus
extern "C"
{
    #endif

    // Stores a UTF-8 string for a string-returning accessibility callback. Pass the
    // `void*` the callback received as `name` (it is a `const char**`, see
    // include/kwx_helper_accessible.h) and a UTF-8 string. kwxFFI copies the text
    // immediately, so the buffer behind `value` only has to stay valid for the duration
    // of this call, and you may free it as soon as this call returns. A NULL `value`
    // publishes an empty string. Do not free the pointer stored in `*name` -- it belongs
    // to kwxFFI.
    void kwxAccString_SetValue(void* name, TString value);

    #ifdef __cplusplus
}  // extern "C"
    #endif

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
TClass(wxAccessible) wxWindow_CreateAccessible(TSelf(wxWindow) pObject);
void wxWindow_SetAccessibleName(TSelf(wxWindow) pObject, TClass(wxString) name);

#endif  // !defined(__cplusplus) || wxUSE_ACCESSIBILITY
