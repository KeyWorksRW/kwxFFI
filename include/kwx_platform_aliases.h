#pragma once

/* Phase 11: platform alias classes.
 *
 * wxAnyButton, wxNonOwnedWindow, and wxGUIEventLoop are the port-specific
 * classes that wx/wx.h selects for the current platform.  Expose those classes
 * directly instead of adding a synthetic typedef wrapper.
 *
 * kwxgen skips preprocessor lines, so the guarded declarations below are
 * always parsed.  The implementations in src/wx_platform_aliases.cpp compile
 * on every supported platform.
 */

#if wxUSE_GUI

/* ------------------------------------------------------------------------- */
/* wxAnyButton                                                               */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxAnyButton, wxControl) TClass(wxBitmap)
    wxAnyButton_GetBitmap(TSelf(wxAnyButton) pObject);
TClass(wxBitmap) wxAnyButton_GetBitmapLabel(TSelf(wxAnyButton) pObject);
TClass(wxBitmap) wxAnyButton_GetBitmapPressed(TSelf(wxAnyButton) pObject);
TClass(wxBitmap) wxAnyButton_GetBitmapDisabled(TSelf(wxAnyButton) pObject);
TClass(wxBitmap) wxAnyButton_GetBitmapCurrent(TSelf(wxAnyButton) pObject);
TClass(wxBitmap) wxAnyButton_GetBitmapFocus(TSelf(wxAnyButton) pObject);
TClass(wxBitmap) wxAnyButton_GetBitmapSelected(TSelf(wxAnyButton) pObject);
TClass(wxBitmap) wxAnyButton_GetBitmapHover(TSelf(wxAnyButton) pObject);
void wxAnyButton_SetBitmap(TSelf(wxAnyButton) pObject, TClass(wxBitmapBundle) bitmap, int dir);
void wxAnyButton_SetBitmapLabel(TSelf(wxAnyButton) pObject, TClass(wxBitmapBundle) bitmap);
void wxAnyButton_SetBitmapPressed(TSelf(wxAnyButton) pObject, TClass(wxBitmapBundle) bitmap);
void wxAnyButton_SetBitmapDisabled(TSelf(wxAnyButton) pObject, TClass(wxBitmapBundle) bitmap);
void wxAnyButton_SetBitmapCurrent(TSelf(wxAnyButton) pObject, TClass(wxBitmapBundle) bitmap);
void wxAnyButton_SetBitmapFocus(TSelf(wxAnyButton) pObject, TClass(wxBitmapBundle) bitmap);
void wxAnyButton_SetBitmapSelected(TSelf(wxAnyButton) pObject, TClass(wxBitmap) bitmap);
void wxAnyButton_SetBitmapHover(TSelf(wxAnyButton) pObject, TClass(wxBitmap) bitmap);
void wxAnyButton_SetBitmapMargins(TSelf(wxAnyButton) pObject, int x, int y);
TClass(wxSize) wxAnyButton_GetBitmapMargins(TSelf(wxAnyButton) pObject);
void wxAnyButton_SetBitmapPosition(TSelf(wxAnyButton) pObject, int dir);
int wxAnyButton_GetNormalState(TSelf(wxAnyButton) pObject);
TBool wxAnyButton_DontShowLabel(TSelf(wxAnyButton) pObject);
TBool wxAnyButton_ShowsLabel(TSelf(wxAnyButton) pObject);

/* ------------------------------------------------------------------------- */
/* wxNonOwnedWindow                                                          */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxNonOwnedWindow, wxWindow) TBool
    wxNonOwnedWindow_SetShape(TSelf(wxNonOwnedWindow) pObject, TClass(wxRegion) region);
    #if wxUSE_GRAPHICS_CONTEXT
TBool wxNonOwnedWindow_SetPathShape(TSelf(wxNonOwnedWindow) pObject, TClass(wxGraphicsPath) path);
    #endif

/* ------------------------------------------------------------------------- */
/* wxGUIEventLoop                                                            */
/* ------------------------------------------------------------------------- */

TClassDef(wxGUIEventLoop) TClass(wxGUIEventLoop) wxGUIEventLoop_Create();
void wxGUIEventLoop_Delete(TSelf(wxGUIEventLoop) pObject);
TClass(wxGUIEventLoop) wxGUIEventLoop_GetActive();
TBool wxGUIEventLoop_IsOk(TSelf(wxGUIEventLoop) pObject);
TBool wxGUIEventLoop_IsMain(TSelf(wxGUIEventLoop) pObject);
int wxGUIEventLoop_Run(TSelf(wxGUIEventLoop) pObject);
TBool wxGUIEventLoop_IsRunning(TSelf(wxGUIEventLoop) pObject);
void wxGUIEventLoop_Exit(TSelf(wxGUIEventLoop) pObject, int rc);
void wxGUIEventLoop_ScheduleExit(TSelf(wxGUIEventLoop) pObject, int rc);
TBool wxGUIEventLoop_Pending(TSelf(wxGUIEventLoop) pObject);
TBool wxGUIEventLoop_Dispatch(TSelf(wxGUIEventLoop) pObject);
int wxGUIEventLoop_DispatchTimeout(TSelf(wxGUIEventLoop) pObject, unsigned long timeout);
void wxGUIEventLoop_WakeUp(TSelf(wxGUIEventLoop) pObject);
void wxGUIEventLoop_WakeUpIdle(TSelf(wxGUIEventLoop) pObject);
TBool wxGUIEventLoop_ProcessIdle(TSelf(wxGUIEventLoop) pObject);
TBool wxGUIEventLoop_Yield(TSelf(wxGUIEventLoop) pObject, TBool onlyIfNeeded);
TBool wxGUIEventLoop_YieldFor(TSelf(wxGUIEventLoop) pObject, long eventsToProcess);
TBool wxGUIEventLoop_IsYielding(TSelf(wxGUIEventLoop) pObject);
TBool wxGUIEventLoop_IsEventAllowedInsideYield(TSelf(wxGUIEventLoop) pObject, int cat);

#endif  // wxUSE_GUI
