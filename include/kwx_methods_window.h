#pragma once

/* Phase 9A: method fill for window and control classes.
 *
 * These blocks extend the class definitions in kwx_classes.h.  kwxgen merges
 * repeated TClassDef/TClassDefExtend blocks by class name, so the declarations
 * below are appended to the existing wxWindow/wxControl/wxTextCtrl/... method
 * lists.
 *
 * Accessibility methods (SetAccessible, GetAccessible, GetOrCreateAccessible,
 * SetAccessibleName, CreateAccessible) belong to Phase 14 and are deliberately
 * absent here.
 */

/* ------------------------------------------------------------------------- */
/* wxWindow                                                                  */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxWindow, wxEvtHandler) int wxWindow_NewControlId(int count);
void wxWindow_UnreserveControlId(int id, int count);
int wxWindow_GetWindowVariant(TSelf(wxWindow) pObject);
void wxWindow_SetWindowVariant(TSelf(wxWindow) pObject, int variant);
int wxWindow_GetLayoutDirection(TSelf(wxWindow) pObject);
void wxWindow_SetLayoutDirection(TSelf(wxWindow) pObject, int direction);
void wxWindow_SetPosition(TSelf(wxWindow) pObject, TPoint(x, y));
void wxWindow_GetScreenPosition(TSelf(wxWindow) pObject, TPointOut(x, y));
TClass(wxRect) wxWindow_GetScreenRect(TSelf(wxWindow) pObject);
void wxWindow_GetClientAreaOrigin(TSelf(wxWindow) pObject, TPointOut(x, y));
TClass(wxRect) wxWindow_GetClientRect(TSelf(wxWindow) pObject);
void wxWindow_ClientToWindowSize(TSelf(wxWindow) pObject, TSizeOut(width, height));
void wxWindow_WindowToClientSize(TSelf(wxWindow) pObject, TSizeOut(width, height));
int wxWindow_GetBestHeight(TSelf(wxWindow) pObject, int width);
int wxWindow_GetBestWidth(TSelf(wxWindow) pObject, int height);
void wxWindow_InvalidateBestSize(TSelf(wxWindow) pObject);
void wxWindow_CacheBestSize(TSelf(wxWindow) pObject, TSize(width, height));
TBool wxWindow_SetInitialSize(TSelf(wxWindow) pObject, TSize(width, height));
void wxWindow_Centre(TSelf(wxWindow) pObject, int direction);
TClass(wxSize) wxWindow_GetMinSize(TSelf(wxWindow) pObject);
TClass(wxSize) wxWindow_GetMaxSize(TSelf(wxWindow) pObject);
void wxWindow_SetMinClientSize(TSelf(wxWindow) pObject, TSize(width, height));
void wxWindow_SetMaxClientSize(TSelf(wxWindow) pObject, TSize(width, height));
TClass(wxSize) wxWindow_GetMinClientSize(TSelf(wxWindow) pObject);
TClass(wxSize) wxWindow_GetMaxClientSize(TSelf(wxWindow) pObject);
TClass(wxSize) wxWindow_GetBestVirtualSize(TSelf(wxWindow) pObject);
double wxWindow_GetContentScaleFactor(TSelf(wxWindow) pObject);
double wxWindow_GetDPIScaleFactor(TSelf(wxWindow) pObject);
TClass(wxSize) wxWindow_GetWindowBorderSize(TSelf(wxWindow) pObject);
void wxWindow_SendSizeEvent(TSelf(wxWindow) pObject, int flags);
void wxWindow_SendSizeEventToParent(TSelf(wxWindow) pObject, int flags);
TBool wxWindow_ShowWithEffect(TSelf(wxWindow) pObject, int effect, int timeout);
TBool wxWindow_HideWithEffect(TSelf(wxWindow) pObject, int effect, int timeout);
TBool wxWindow_IsThisEnabled(TSelf(wxWindow) pObject);
TBool wxWindow_IsShownOnScreen(TSelf(wxWindow) pObject);
void wxWindow_SetWindowStyle(TSelf(wxWindow) pObject, long style);
long wxWindow_GetWindowStyle(TSelf(wxWindow) pObject);
TBool wxWindow_IsRetained(TSelf(wxWindow) pObject);
TBool wxWindow_ToggleWindowStyle(TSelf(wxWindow) pObject, int flag);
long wxWindow_GetExtraStyle(TSelf(wxWindow) pObject);
TBool wxWindow_HasExtraStyle(TSelf(wxWindow) pObject, int exFlag);
void wxWindow_SetThemeEnabled(TSelf(wxWindow) pObject, TBool enableTheme);
TBool wxWindow_GetThemeEnabled(TSelf(wxWindow) pObject);
void wxWindow_SetFocusFromKbd(TSelf(wxWindow) pObject);
TBool wxWindow_AcceptsFocus(TSelf(wxWindow) pObject);
TBool wxWindow_AcceptsFocusRecursively(TSelf(wxWindow) pObject);
TBool wxWindow_AcceptsFocusFromKeyboard(TSelf(wxWindow) pObject);
void wxWindow_DisableFocusFromKeyboard(TSelf(wxWindow) pObject);
void wxWindow_EnableFocusFromKeyboard(TSelf(wxWindow) pObject);
TBool wxWindow_CanBeFocused(TSelf(wxWindow) pObject);
TBool wxWindow_IsFocusable(TSelf(wxWindow) pObject);
TBool wxWindow_CanAcceptFocus(TSelf(wxWindow) pObject);
TBool wxWindow_CanAcceptFocusFromKeyboard(TSelf(wxWindow) pObject);
void wxWindow_SetCanFocus(TSelf(wxWindow) pObject, TBool canFocus);
void wxWindow_EnableVisibleFocus(TSelf(wxWindow) pObject, TBool enabled);
TBool wxWindow_NavigateIn(TSelf(wxWindow) pObject, int flags);
TBool wxWindow_Navigate(TSelf(wxWindow) pObject, int flags);
void wxWindow_MoveBeforeInTabOrder(TSelf(wxWindow) pObject, TClass(wxWindow) win);
void wxWindow_MoveAfterInTabOrder(TSelf(wxWindow) pObject, TClass(wxWindow) win);
TBool wxWindow_IsDescendant(TSelf(wxWindow) pObject, TClass(wxWindow) win);
void wxWindow_SetParent(TSelf(wxWindow) pObject, TClass(wxWindow) parent);
void wxWindow_SetEventHandler(TSelf(wxWindow) pObject, TClass(wxEvtHandler) handler);
TBool wxWindow_RemoveEventHandler(TSelf(wxWindow) pObject, TClass(wxEvtHandler) handler);
TBool wxWindow_ProcessWindowEvent(TSelf(wxWindow) pObject, TClass(wxEvent) event);
TBool wxWindow_ProcessWindowEventLocally(TSelf(wxWindow) pObject, TClass(wxEvent) event);
TBool wxWindow_HandleWindowEvent(TSelf(wxWindow) pObject, TClass(wxEvent) event);
TClass(wxAcceleratorTable) wxWindow_GetAcceleratorTable(TSelf(wxWindow) pObject);
TBool wxWindow_RegisterHotKey(TSelf(wxWindow) pObject, int hotkeyId, int modifiers, int keycode);
TBool wxWindow_UnregisterHotKey(TSelf(wxWindow) pObject, int hotkeyId);
TClass(wxSize) wxWindow_GetDPI(TSelf(wxWindow) pObject);
int wxWindow_FromDIP(TSelf(wxWindow) pObject, int value);
int wxWindow_ToDIP(TSelf(wxWindow) pObject, int value);
TBool wxWindow_HasCapture(TSelf(wxWindow) pObject);
TBool wxWindow_EnableTouchEvents(TSelf(wxWindow) pObject, int eventsMask);
TBool wxWindow_IsFrozen(TSelf(wxWindow) pObject);
void wxWindow_SetDoubleBuffered(TSelf(wxWindow) pObject, TBool on);
TBool wxWindow_IsDoubleBuffered(TSelf(wxWindow) pObject);
TClass(wxRect) wxWindow_GetUpdateClientRect(TSelf(wxWindow) pObject);
void wxWindow_SetOwnBackgroundColour(TSelf(wxWindow) pObject, TClass(wxColour) colour);
TBool wxWindow_UseBgCol(TSelf(wxWindow) pObject);
TBool wxWindow_UseBackgroundColour(TSelf(wxWindow) pObject);
TBool wxWindow_InheritsBackgroundColour(TSelf(wxWindow) pObject);
void wxWindow_SetOwnForegroundColour(TSelf(wxWindow) pObject, TClass(wxColour) colour);
TBool wxWindow_UseForegroundColour(TSelf(wxWindow) pObject);
TBool wxWindow_InheritsForegroundColour(TSelf(wxWindow) pObject);
TBool wxWindow_SetBackgroundStyle(TSelf(wxWindow) pObject, int style);
int wxWindow_GetBackgroundStyle(TSelf(wxWindow) pObject);
TBool wxWindow_HasTransparentBackground(TSelf(wxWindow) pObject);
void wxWindow_SetOwnFont(TSelf(wxWindow) pObject, TClass(wxFont) font);
void wxWindow_EnableInputMethod(TSelf(wxWindow) pObject, TBool enable);
TBool wxWindow_IsInputMethodEnabled(TSelf(wxWindow) pObject);
void wxWindow_UpdateInputMethodCursorRect(TSelf(wxWindow) pObject, TRect(x, y, width, height));
TClass(wxRect) wxWindow_GetInputMethodCursorRect(TSelf(wxWindow) pObject);
int wxWindow_HitTest(TSelf(wxWindow) pObject, TPoint(x, y));
int wxWindow_GetBorder(TSelf(wxWindow) pObject, long flags);
TBool wxWindow_HasMultiplePages(TSelf(wxWindow) pObject);
TBool wxWindow_CanScroll(TSelf(wxWindow) pObject, int orient);
TBool wxWindow_HasScrollbar(TSelf(wxWindow) pObject, int orient);
int wxWindow_GetScrollbarSize(TSelf(wxWindow) pObject, int orient);
TBool wxWindow_ScrollLines(TSelf(wxWindow) pObject, int lines);
TBool wxWindow_ScrollPages(TSelf(wxWindow) pObject, int pages);
TBool wxWindow_LineUp(TSelf(wxWindow) pObject);
TBool wxWindow_LineDown(TSelf(wxWindow) pObject);
TBool wxWindow_PageUp(TSelf(wxWindow) pObject);
TBool wxWindow_PageDown(TSelf(wxWindow) pObject);
void wxWindow_AlwaysShowScrollbars(TSelf(wxWindow) pObject, TBool horz, TBool vert);
TBool wxWindow_IsScrollbarAlwaysShown(TSelf(wxWindow) pObject, int orient);
void wxWindow_SetHelpText(TSelf(wxWindow) pObject, TClass(wxString) text);
TClass(wxString) wxWindow_GetHelpText(TSelf(wxWindow) pObject);
void wxWindow_UnsetToolTip(TSelf(wxWindow) pObject);
TClass(wxString) wxWindow_GetToolTipText(TSelf(wxWindow) pObject);
void wxWindow_DragAcceptFiles(TSelf(wxWindow) pObject, TBool accept);
void wxWindow_SetContainingSizer(TSelf(wxWindow) pObject, TClass(wxSizer) sizer);
TBool wxWindow_SetTransparent(TSelf(wxWindow) pObject, TUInt8 alpha);
TBool wxWindow_CanSetTransparent(TSelf(wxWindow) pObject);
TClass(wxPalette) wxWindow_GetPalette(TSelf(wxWindow) pObject);
void wxWindow_SetPalette(TSelf(wxWindow) pObject, TClass(wxPalette) palette);
TBool wxWindow_HasCustomPalette(TSelf(wxWindow) pObject);
void wxWindow_InheritAttributes(TSelf(wxWindow) pObject);
TBool wxWindow_ShouldInheritColours(TSelf(wxWindow) pObject);
int wxWindow_GetPopupMenuSelectionFromUser(TSelf(wxWindow) pObject, TClass(wxMenu) menu,
                                           TPoint(x, y));
int wxWindow_AdjustForLayoutDirection(TSelf(wxWindow) pObject, int x, int width, int widthTotal);
TBool wxWindow_BeginRepositioningChildren(TSelf(wxWindow) pObject);
void wxWindow_EndRepositioningChildren(TSelf(wxWindow) pObject);
TBool wxWindow_IsClientAreaChild(TSelf(wxWindow) pObject, TClass(wxWindow) child);
int wxWindow_FromPhys(TSelf(wxWindow) pObject, int value);
int wxWindow_ToPhys(TSelf(wxWindow) pObject, int value);
TClass(wxString) wxWindow_GetHelpTextAtPoint(TSelf(wxWindow) pObject, TPoint(x, y), int origin);
int wxWindow_GetHelpIdAtPoint(TSelf(wxWindow) pObject, TPoint(x, y));
TBool wxWindow_CopyToolTip(TSelf(wxWindow) pObject, TClass(wxToolTip) tip);
TBool wxWindow_CanBeOutsideClientArea(TSelf(wxWindow) pObject);
TBool wxWindow_CanApplyThemeBorder(TSelf(wxWindow) pObject);
TBool wxWindow_IsTopNavigationDomain(TSelf(wxWindow) pObject, int kind);

/* ------------------------------------------------------------------------- */
/* wxControl                                                                 */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxControl, wxWindow) int wxControl_FindAccelIndex(TClass(wxString) label);
TBool wxControl_ShouldInheritColours(TSelf(wxControl) pObject);

/* ------------------------------------------------------------------------- */
/* wxTextCtrl                                                                */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxTextCtrl, wxControl) TClass(wxPoint)
    wxTextCtrl_PositionToCoords(TSelf(wxTextCtrl) pObject, long pos);
int wxTextCtrl_HitTest(TSelf(wxTextCtrl) pObject, TPoint(x, y), long* pos);
int wxTextCtrl_HitTestColumnRow(TSelf(wxTextCtrl) pObject, TPoint(x, y), long* column, long* row);
TBool wxTextCtrl_IsRTFSupported(TSelf(wxTextCtrl) pObject);
TClass(wxString) wxTextCtrl_GetRTFValue(TSelf(wxTextCtrl) pObject);
void wxTextCtrl_SetRTFValue(TSelf(wxTextCtrl) pObject, TClass(wxString) value);
TBool wxTextCtrl_ShouldInheritColours(TSelf(wxTextCtrl) pObject);

/* ------------------------------------------------------------------------- */
/* wxTextEntry                                                               */
/* ------------------------------------------------------------------------- */

TClassDef(wxTextEntry) void wxTextEntry_ConvertToUpperCase(TClass(wxTextEntry) self);
void wxTextEntry_ForwardEnableTextChangedEvents(TClass(wxTextEntry) self, TBool enable);

/* ------------------------------------------------------------------------- */
/* wxItemContainer                                                           */
/* ------------------------------------------------------------------------- */

TClassDef(wxItemContainer) void wxItemContainer_AppendString(TClass(wxItemContainer) self,
                                                             TClass(wxString) item);
void wxItemContainer_SetClientObject(TClass(wxItemContainer) self, unsigned int n,
                                     TClass(wxClientData) clientData);
TClass(wxClientData) wxItemContainer_GetClientObject(TClass(wxItemContainer) self, unsigned int n);
TClass(wxClientData)
    wxItemContainer_DetachClientObject(TClass(wxItemContainer) self, unsigned int n);
int wxItemContainer_GetClientDataType(TClass(wxItemContainer) self);
TBool wxItemContainer_HasClientObjectData(TClass(wxItemContainer) self);
TBool wxItemContainer_HasClientUntypedData(TClass(wxItemContainer) self);

/* ------------------------------------------------------------------------- */
/* wxDialog                                                                  */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxDialog, wxTopLevelWindow) void wxDialog_ShowWindowModal(TSelf(wxDialog) pObject);
int wxDialog_GetModality(TSelf(wxDialog) pObject);
void wxDialog_AddMainButtonId(TSelf(wxDialog) pObject, int id);
TBool wxDialog_IsMainButtonId(TSelf(wxDialog) pObject, int id);
void wxDialog_SetLayoutAdaptationLevel(TSelf(wxDialog) pObject, int level);
int wxDialog_GetLayoutAdaptationLevel(TSelf(wxDialog) pObject);
void wxDialog_SetLayoutAdaptationMode(TSelf(wxDialog) pObject, int mode);
int wxDialog_GetLayoutAdaptationMode(TSelf(wxDialog) pObject);
void wxDialog_SetLayoutAdaptationDone(TSelf(wxDialog) pObject, TBool adaptationDone);
TBool wxDialog_GetLayoutAdaptationDone(TSelf(wxDialog) pObject);
TBool wxDialog_IsLayoutAdaptationEnabled();
void wxDialog_EnableLayoutAdaptation(TBool enable);
TBool wxDialog_CanDoLayoutAdaptation(TSelf(wxDialog) pObject);
TBool wxDialog_DoLayoutAdaptation(TSelf(wxDialog) pObject);
TClass(wxWindow) wxDialog_GetContentWindow(TSelf(wxDialog) pObject);

/* ------------------------------------------------------------------------- */
/* wxFrame                                                                   */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxFrame, wxTopLevelWindow) TClass(wxPoint)
    wxFrame_GetClientAreaOriginPoint(TSelf(wxFrame) pObject);
void wxFrame_SetWindowModality(TSelf(wxFrame) pObject, int modality);
TBool wxFrame_ProcessCommandItem(TSelf(wxFrame) pObject, TClass(wxMenuItem) item);
void wxFrame_DoMenuUpdates(TSelf(wxFrame) pObject, TClass(wxMenu) menu);
TBool wxFrame_IsClientAreaChild(TSelf(wxFrame) pObject, TClass(wxWindow) child);

/* ------------------------------------------------------------------------- */
/* wxTopLevelWindow                                                          */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxTopLevelWindow, wxWindow) TBool
    wxTopLevelWindow_IsAlwaysMaximized(TSelf(wxTopLevelWindow) pObject);
TClass(wxIconBundle) wxTopLevelWindow_GetIcons(TSelf(wxTopLevelWindow) pObject);
TBool wxTopLevelWindow_EnableFullScreenView(TSelf(wxTopLevelWindow) pObject, TBool enable,
                                            long style);
int wxTopLevelWindow_GetContentProtection(TSelf(wxTopLevelWindow) pObject);
TClass(wxSize) wxTopLevelWindow_GetDefaultSize();
