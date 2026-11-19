#pragma once

// kwx<Base> override-hook exports — the declaration model for
// include/kwx_helper_hooks.h.
//
// kwxgen expands the quoted includes of kwx_classes.h and parses every
// declaration it reaches.  The kwx<Base> C++ class bodies that implement these
// hooks are not declarations, so they live in include/kwx_helper_hooks.h, which
// is deliberately absent from that include list — the same split
// include/kwx_combo_extra.h:9-10 documents for the combo helpers.
//
// Every block header below names the class the functions under it belong to, so
// kwxgen attributes each method to that class instead of creating a stray one.
// The <Base>_SetOn<Method> aliases use the base name because the portability
// matrix resolves an override row to both spellings.
//
// EXPORT is a no-op outside the library build.  The declarations carry it
// because an unqualified function would get C++ language linkage and would not
// match the definitions in src/kwx_hooks.cpp, which sit inside extern "C".
//
// Keep the file timestamp-free: a re-run must be byte-identical.

#include "kwx_def.h"
#include "kwx_types.h"

TClassDefExtend(kwxAppConsole, wxAppConsole) EXPORT void* kwxAppConsole_Create(void* pObject);
EXPORT void kwxAppConsole_Delete(TSelf(kwxAppConsole) pObject);
EXPORT void kwxAppConsole_SetOnOnCmdLineParsed(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnOnInitCmdLine(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnOnExit(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnOnRun(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnOnAssertFailure(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnOnEventLoopEnter(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnOnExceptionInMainLoop(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnOnFatalException(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnOnUnhandledException(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnStoreCurrentException(TSelf(kwxAppConsole) pObject, void* pFunction);
EXPORT void kwxAppConsole_SetOnRethrowStoredException(TSelf(kwxAppConsole) pObject,
                                                      void* pFunction);
EXPORT void kwxAppConsole_SetOnCreateTraits(TSelf(kwxAppConsole) pObject, void* pFunction);

TClassDef(wxAppConsole) EXPORT
    void wxAppConsole_SetOnOnCmdLineParsed(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnOnInitCmdLine(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnOnExit(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnOnRun(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnOnAssertFailure(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnOnEventLoopEnter(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnOnExceptionInMainLoop(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnOnFatalException(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnOnUnhandledException(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnStoreCurrentException(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnRethrowStoredException(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT void wxAppConsole_SetOnCreateTraits(TSelf(wxAppConsole) pObject, void* pFunction);
EXPORT TClass(wxString) wxAppConsole_GetAppName(TSelf(wxAppConsole) pObject);
EXPORT void wxAppConsole_SetAppName(TSelf(wxAppConsole) pObject, TClass(wxString) name);
EXPORT TClass(wxString) wxAppConsole_GetAppDisplayName(TSelf(wxAppConsole) pObject);
EXPORT void wxAppConsole_SetAppDisplayName(TSelf(wxAppConsole) pObject, TClass(wxString) name);
EXPORT TClass(wxString) wxAppConsole_GetVendorName(TSelf(wxAppConsole) pObject);
EXPORT void wxAppConsole_SetVendorName(TSelf(wxAppConsole) pObject, TClass(wxString) name);
EXPORT void wxAppConsole_ExitMainLoop(TSelf(wxAppConsole) pObject);
EXPORT void wxAppConsole_ProcessPendingEvents(TSelf(wxAppConsole) pObject);
EXPORT TBool wxAppConsole_Yield(TSelf(wxAppConsole) pObject);

TClassDefExtend(kwxApp, wxApp) EXPORT void* kwxApp_Create(void* pObject);
EXPORT void kwxApp_Delete(TSelf(kwxApp) pObject);
EXPORT void kwxApp_SetOnOnCmdLineParsed(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnOnInitCmdLine(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnOnExit(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnFilterEvent(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnGetClassInfo(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnOnAssertFailure(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnCreateTraits(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnOnFatalException(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnOnUnhandledException(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnStoreCurrentException(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnOnExceptionInMainLoop(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnRethrowStoredException(TSelf(kwxApp) pObject, void* pFunction);

// wxDebugReportUpload hooks: the wxWidgets sample derives from the class only to
// log the server reply, so the helper publishes that reply through a callback.
TClassDefExtend(kwxDebugReportUpload, wxDebugReportUpload) EXPORT TClass(kwxDebugReportUpload)
    kwxDebugReportUpload_Create(void* pObject, TClass(wxString) url, TClass(wxString) input,
                                TClass(wxString) action);
EXPORT void kwxDebugReportUpload_Delete(TSelf(kwxDebugReportUpload) pObject);
EXPORT void kwxDebugReportUpload_SetOnOnServerReply(TSelf(kwxDebugReportUpload) pObject,
                                                    void* pFunction);
EXPORT void kwxDebugReportUpload_SetOnServerReplyResult(TSelf(kwxDebugReportUpload) pObject,
                                                        TBool result);

// The kwxObject and kwxPanel setters are declared in the wxObject and wxPanel
// blocks of include/kwx_classes.h and include/kwx_classes_sync.h: both classes
// already own a block, and a second block header for one class rewrites its
// hierarchy (kwxgen merges blocks by class name).  Only the classes that had no
// block at all get one here.

TClassDefExtend(kwxObject, wxObject) EXPORT void* kwxObject_Create(void* pObject);
EXPORT void kwxObject_Delete(TSelf(kwxObject) pObject);
EXPORT void kwxObject_SetOnGetClassInfo(TSelf(kwxObject) pObject, void* pFunction);

TClassDefExtend(kwxPanel, wxPanel) EXPORT TClass(kwxPanel)
    kwxPanel_Create(void* pObject, TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                    long style);
EXPORT void kwxPanel_Delete(TSelf(kwxPanel) pObject);
EXPORT void kwxPanel_SetOnTransferDataFromWindow(TSelf(kwxPanel) pObject, void* pFunction);
EXPORT void kwxPanel_SetOnTransferDataToWindow(TSelf(kwxPanel) pObject, void* pFunction);
// The best-size callback receives two int* outputs (width, height) so no wxSize
// crosses the boundary; the scroll callback receives the deltas and a
// const wxRect* that is null when the caller passed no rectangle.
EXPORT void kwxPanel_SetOnDoGetBestClientSize(TSelf(kwxPanel) pObject, void* pFunction);
EXPORT void kwxPanel_SetOnScrollWindow(TSelf(kwxPanel) pObject, void* pFunction);

// A dialog a port can override TransferDataFromWindow / TransferDataToWindow on
// (drawing.cpp:2472-2550: TransformDataDialog rejects out-of-range values from its
// own transfer).  Like every kwx* helper it must be CREATED through this factory:
// the setters are only valid on a kwxDialog, never on a plain wxDialog.  The hooks
// replace the wxDialog implementation, so chain them with
// kwxDialogOnTransferDataFromWindowBase / ...ToWindowBase to keep the child
// validators working.  There is deliberately no kwxDialog_Delete: a dialog is a
// window, so dispose of it with wxWindow_Destroy (emitted as destroy()).
TClassDefExtend(kwxDialog, wxDialog) EXPORT TClass(kwxDialog)
    kwxDialog_Create(void* pObject, TClass(wxWindow) parent, int id, TClass(wxString) title,
                     TRect(x, y, width, height), long style);
EXPORT void kwxDialog_SetOnTransferDataFromWindow(TSelf(kwxDialog) pObject, void* pFunction);
EXPORT void kwxDialog_SetOnTransferDataToWindow(TSelf(kwxDialog) pObject, void* pFunction);
EXPORT TBool kwxDialogOnTransferDataFromWindowBase(TClass(kwxDialog) pObject);
EXPORT TBool kwxDialogOnTransferDataToWindowBase(TClass(kwxDialog) pObject);

// handle is the platform-native child window (HWND / GtkWidget* / NSView*);
// kwxNativeWindow neither creates nor destroys it.  The notify callback is
// MSW-only but is accepted and stored on every platform.
TClassDefExtend(kwxNativeWindow, wxNativeWindow) EXPORT TClass(kwxNativeWindow)
    kwxNativeWindow_Create(void* pObject, TClass(wxWindow) parent, int id, void* handle);
EXPORT void kwxNativeWindow_Delete(TSelf(kwxNativeWindow) pObject);
EXPORT void kwxNativeWindow_SetOnMSWNotify(TSelf(kwxNativeWindow) pObject, void* pFunction);

TClassDefExtend(kwxEvtHandler, wxEvtHandler) EXPORT void* kwxEvtHandler_Create(void* pObject);
EXPORT void kwxEvtHandler_Delete(TSelf(kwxEvtHandler) pObject);
EXPORT void kwxEvtHandler_SetOnProcessEvent(TSelf(kwxEvtHandler) pObject, void* pFunction);

// A frame a port can override ProcessEvent on.  kwxEvtHandler_SetOnProcessEvent
// is only valid on a kwxEvtHandler helper object and must never be handed a
// frame: a real wxFrame has a different layout, so the cast is undefined
// behaviour and the override would never be consulted.  The plain callback is
// int (*)(void*, void*), receiving the callback object and a wxEvent*, and
// returns non-zero when it handled the event; the ...WithData callback is
// void (*)(void*, void*, void*) and publishes its answer with
// kwxFrame_SetProcessEventResult.  A callback that publishes nothing means "not
// handled", so the event falls through to wxFrame::ProcessEvent.
TClassDefExtend(kwxFrame, wxFrame) TClass(kwxFrame)
    kwxFrame_Create(TClass(wxWindow) parent, int id, TClass(wxString) title, int x, int y,
                    int width, int height, long style);
void kwxFrame_Delete(TSelf(kwxFrame) pObject);
void kwxFrame_SetCallbackObject(TSelf(kwxFrame) pObject, void* object);
void* kwxFrame_GetCallbackObject(TSelf(kwxFrame) pObject);
void kwxFrame_SetOnProcessEvent(TSelf(kwxFrame) pObject, void* pFunction);
void kwxFrame_SetOnProcessEventWithData(TSelf(kwxFrame) pObject, void* pFunction, void* data);
void kwxFrame_SetProcessEventResult(TSelf(kwxFrame) pObject, TBool result);
// TryBefore() is the pre-handler hook wxEvtHandler::ProcessEventLocally() calls, so it
// is the C++ route for "let the frame hand a command/update-UI event to a child before
// the frame's own handlers see it" (samples/dnd/dnd.cpp:1894-1907).  A callback that
// publishes nothing means "not handled" and wxFrame::TryBefore() runs, so inherited
// frame behaviour (menu processing, navigation) is preserved.  The plain callback is
// int (*)(void*, void*), receiving the callback object set with
// kwxFrame_SetCallbackObject and a wxEvent*, returning non-zero when it handled the
// event; the ...WithData callback is void (*)(void*, void*, void*) and publishes its
// answer with kwxFrame_SetTryBeforeResult.  The wxEvent* is valid only for the
// duration of the call -- do not store it.
void kwxFrame_SetOnTryBefore(TSelf(kwxFrame) pObject, void* pFunction);
void kwxFrame_SetOnTryBeforeWithData(TSelf(kwxFrame) pObject, void* pFunction, void* data);
void kwxFrame_SetTryBeforeResult(TSelf(kwxFrame) pObject, TBool result);

TClassDefExtend(kwxVarHScrollHelper, wxVarHScrollHelper) EXPORT TClass(kwxVarHScrollHelper)
    kwxVarHScrollHelper_Create(TClass(wxWindow) winToScroll, void* pObject);
EXPORT void kwxVarHScrollHelper_Delete(TSelf(kwxVarHScrollHelper) pObject);
EXPORT void kwxVarHScrollHelper_SetOnOnGetColumnWidth(TSelf(kwxVarHScrollHelper) pObject,
                                                      void* pFunction);

TClassDef(wxVarHScrollHelper) EXPORT
    void wxVarHScrollHelper_SetOnOnGetColumnWidth(TSelf(wxVarHScrollHelper) pObject,
                                                  void* pFunction);

TClassDefExtend(kwxVarVScrollHelper, wxVarVScrollHelper) EXPORT TClass(kwxVarVScrollHelper)
    kwxVarVScrollHelper_Create(TClass(wxWindow) winToScroll, void* pObject);
EXPORT void kwxVarVScrollHelper_Delete(TSelf(kwxVarVScrollHelper) pObject);
EXPORT void kwxVarVScrollHelper_SetOnOnGetRowHeight(TSelf(kwxVarVScrollHelper) pObject,
                                                    void* pFunction);

TClassDef(wxVarVScrollHelper) EXPORT
    void wxVarVScrollHelper_SetOnOnGetRowHeight(TSelf(wxVarVScrollHelper) pObject, void* pFunction);

TClassDefExtend(kwxTimer, wxTimer) EXPORT TClass(kwxTimer) kwxTimer_Create(void* pObject);
EXPORT void kwxTimer_Delete(TSelf(kwxTimer) pObject);
EXPORT void kwxTimer_SetOnNotify(TSelf(kwxTimer) pObject, void* pFunction);

TClassDefExtend(kwxValidator, wxValidator) EXPORT void* kwxValidator_Create(void* pObject);
EXPORT void kwxValidator_Delete(TSelf(kwxValidator) pObject);
EXPORT void kwxValidator_SetOnClone(TSelf(kwxValidator) pObject, void* pFunction);
EXPORT void kwxValidator_SetOnValidate(TSelf(kwxValidator) pObject, void* pFunction);
EXPORT void kwxValidator_SetOnTransferFromWindow(TSelf(kwxValidator) pObject, void* pFunction);
EXPORT void kwxValidator_SetOnTransferToWindow(TSelf(kwxValidator) pObject, void* pFunction);

TClassDefExtend(kwxPreferencesPage, wxPreferencesPage) EXPORT
    void* kwxPreferencesPage_Create(void* pObject);
EXPORT void kwxPreferencesPage_Delete(TSelf(kwxPreferencesPage) pObject);
// The <Base>_Delete spelling, declared in the wxPreferencesPage block below, is
// the same delete on the same helper object.
// GetName()/CreateWindow()/GetIcon() return char*/wxWindow*/wxBitmapBundle*, which
// the void-only FFI callback ABI cannot carry.  The SetOn* setters install a void
// callback, and that callback publishes its result with the matching
// SetOn*Result call before it returns.  A callback that returns without calling
// its result setter yields an empty name, a null window or no icon.
EXPORT void kwxPreferencesPage_SetOnGetName(TSelf(kwxPreferencesPage) pObject, void* pFunction);
// Call from the GetName callback with a UTF-8 char*; the name is copied.
EXPORT void kwxPreferencesPage_SetOnGetNameResult(TSelf(kwxPreferencesPage) pObject, TString name);
EXPORT void kwxPreferencesPage_SetOnCreateWindow(TSelf(kwxPreferencesPage) pObject,
                                                 void* pFunction);
// Call from the CreateWindow callback with the wxWindow* it created.  The page
// takes ownership of that window, so the caller must not delete it.
EXPORT void kwxPreferencesPage_SetOnCreateWindowResult(TSelf(kwxPreferencesPage) pObject,
                                                       TClass(wxWindow) window);
EXPORT void kwxPreferencesPage_SetOnGetIcon(TSelf(kwxPreferencesPage) pObject, void* pFunction);
// Call from the GetIcon callback with a wxBitmapBundle* allocated with new; the
// page copies it and deletes the original.
EXPORT void kwxPreferencesPage_SetOnGetIconResult(TSelf(kwxPreferencesPage) pObject,
                                                  TClass(wxBitmapBundle) bundle);

TClassDef(wxPreferencesEditor) TClass(wxPreferencesEditor)
    wxPreferencesEditor_Create(TClass(wxString) title);
void wxPreferencesEditor_Delete(TSelf(wxPreferencesEditor) pObject);
// The editor takes ownership of the page and deletes it when it is destroyed.
void wxPreferencesEditor_AddPage(TSelf(wxPreferencesEditor) pObject,
                                 TClass(wxPreferencesPage) page);
// wxStockPreferencesPage is modelled parentless on purpose (see its own block
// below), so it is not a TClass(wxPreferencesPage) in the generated bindings even
// though the C++ type really does derive from wxPreferencesPage.  This entry point
// accepts the stock page directly and up-casts it in C++, which is safe, and it
// avoids exposing the kwxPreferencesPage down-casting setters on the stock page.
void wxPreferencesEditor_AddStockPage(TSelf(wxPreferencesEditor) pObject,
                                      TClass(wxStockPreferencesPage) page);
void wxPreferencesEditor_Show(TSelf(wxPreferencesEditor) pObject, TClass(wxWindow) parent);
void wxPreferencesEditor_Dismiss(TSelf(wxPreferencesEditor) pObject);
// Non-zero when the platform applies a page's changes immediately (OS X, GTK+)
// rather than only when the user confirms the dialog (MSW).
TBool wxPreferencesEditor_ShouldApplyChangesImmediately();
// Non-zero when Show() blocks until the dialog is dismissed.
TBool wxPreferencesEditor_ShownModally();

// Kind: 0 = General, 1 = Advanced.  The block is deliberately parentless: the
// C++ helper behind these functions derives from wxStockPreferencesPage, not from
// kwxPreferencesPage, so a binding must not inherit the kwxPreferencesPage
// setters (they down-cast their receiver).
TClassDef(wxStockPreferencesPage) TClass(wxStockPreferencesPage)
    wxStockPreferencesPage_Create(int kind);
// Like wxStockPreferencesPage_Create, but hands pObject to every CreateWindow
// callback, so a port's window factory has its own context instead of a static.
EXPORT void* wxStockPreferencesPage_CreateWithState(int kind, void* pObject);
void wxStockPreferencesPage_Delete(TSelf(wxStockPreferencesPage) pObject);
int wxStockPreferencesPage_GetKind(TSelf(wxStockPreferencesPage) pObject);
// CreateWindow() is still pure on the stock page, so this helper supplies the
// callback-driven override the two stock kinds need to become usable.
EXPORT void wxStockPreferencesPage_SetOnCreateWindow(TSelf(wxStockPreferencesPage) pObject,
                                                     void* pFunction);
// Call from the CreateWindow callback with the wxWindow* it created; the page
// takes ownership of that window.
EXPORT void wxStockPreferencesPage_SetOnCreateWindowResult(TSelf(wxStockPreferencesPage) pObject,
                                                           TClass(wxWindow) window);

// wxPreferencesPage had no declaration block at all, so the <Base>_SetOn
// spellings the portability matrix resolves an ovh row to get their own block
// here.  The receiver is the same kwxPreferencesPage helper object.

TClassDef(wxPreferencesPage) EXPORT void wxPreferencesPage_Delete(TSelf(wxPreferencesPage) pObject);
EXPORT void wxPreferencesPage_SetOnGetName(TSelf(wxPreferencesPage) pObject, void* pFunction);
EXPORT void wxPreferencesPage_SetOnCreateWindow(TSelf(wxPreferencesPage) pObject, void* pFunction);
EXPORT void wxPreferencesPage_SetOnGetIcon(TSelf(wxPreferencesPage) pObject, void* pFunction);
EXPORT void wxPreferencesPage_SetOnGetNameResult(TSelf(wxPreferencesPage) pObject, TString name);
EXPORT void wxPreferencesPage_SetOnCreateWindowResult(TSelf(wxPreferencesPage) pObject,
                                                      TClass(wxWindow) window);
EXPORT void wxPreferencesPage_SetOnGetIconResult(TSelf(wxPreferencesPage) pObject,
                                                 TClass(wxBitmapBundle) bundle);

TClassDefExtend(kwxHtmlListBox, wxHtmlListBox) EXPORT TClass(kwxHtmlListBox)
    kwxHtmlListBox_Create(void* pObject, TClass(wxWindow) parent, int id,
                          TRect(x, y, width, height), long style);
EXPORT void kwxHtmlListBox_Delete(TSelf(kwxHtmlListBox) pObject);
EXPORT void kwxHtmlListBox_SetOnOnGetItem(TSelf(kwxHtmlListBox) pObject, void* pFunction);
EXPORT void kwxHtmlListBox_SetOnGetSelectedTextColour(TSelf(kwxHtmlListBox) pObject,
                                                      void* pFunction);

// wxHtmlListBox already owns a block in include/kwx_html.h, so its <Base>_SetOn
// spellings are declared there rather than in a second block header here.

TClassDefExtend(kwxVListBox, wxVListBox) EXPORT TClass(kwxVListBox)
    kwxVListBox_Create(void* pObject, TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                       long style);
EXPORT void kwxVListBox_Delete(TSelf(kwxVListBox) pObject);
EXPORT void kwxVListBox_SetOnOnDrawItem(TSelf(kwxVListBox) pObject, void* pFunction);
EXPORT void kwxVListBox_SetOnOnDrawSeparator(TSelf(kwxVListBox) pObject, void* pFunction);
EXPORT void kwxVListBox_SetOnOnMeasureItem(TSelf(kwxVListBox) pObject, void* pFunction);

// wxVListBox already owns a block in include/kwx_classes_sync.h, so its
// <Base>_SetOn spellings are declared there rather than in a second block header
// here.

// The bases below had no declaration block at all, so each gets one block that
// covers both the kwx<Base>_ and the <Base>_ spelling the portability matrix
// resolves an override row to.  wxDocument, wxView, wxLog, wxLogGui,
// wxFileSystemHandler, wxHtmlTagHandler and wxVariantData already own blocks, so
// their <Base>_SetOn spellings are declared in those files instead (a second
// block header for one class rewrites its hierarchy).

TClassDefExtend(kwxRendererNative, wxRendererNative) EXPORT
    void* kwxRendererNative_Create(void* pObject);
EXPORT void kwxRendererNative_Delete(TSelf(kwxRendererNative) pObject);
EXPORT void kwxRendererNative_SetOnDrawHeaderButton(TSelf(kwxRendererNative) pObject,
                                                    void* pFunction);
EXPORT void kwxRendererNative_SetOnGetVersion(TSelf(kwxRendererNative) pObject, void* pFunction);

TClassDef(wxRendererNative) EXPORT
    void wxRendererNative_SetOnDrawHeaderButton(TSelf(wxRendererNative) pObject, void* pFunction);
EXPORT void wxRendererNative_SetOnGetVersion(TSelf(wxRendererNative) pObject, void* pFunction);

TClassDefExtend(kwxModalDialogHook, wxModalDialogHook) EXPORT
    void* kwxModalDialogHook_Create(void* pObject);
EXPORT void kwxModalDialogHook_Delete(TSelf(kwxModalDialogHook) pObject);
EXPORT void kwxModalDialogHook_SetOnEnter(TSelf(kwxModalDialogHook) pObject, void* pFunction);
EXPORT void kwxModalDialogHook_SetOnExit(TSelf(kwxModalDialogHook) pObject, void* pFunction);
EXPORT void kwxModalDialogHook_CaptureEnterDialog(TSelf(kwxModalDialogHook) pObject, TBool capture);

TClassDef(wxModalDialogHook) EXPORT
    void wxModalDialogHook_SetOnEnter(TSelf(wxModalDialogHook) pObject, void* pFunction);
EXPORT void wxModalDialogHook_SetOnExit(TSelf(wxModalDialogHook) pObject, void* pFunction);
EXPORT void wxModalDialogHook_CaptureEnterDialog(TSelf(wxModalDialogHook) pObject, TBool capture);
EXPORT void wxModalDialogHook_Register(TSelf(wxModalDialogHook) pObject);
EXPORT void wxModalDialogHook_Unregister(TSelf(wxModalDialogHook) pObject);
EXPORT void wxModalDialogHook_Delete(TSelf(wxModalDialogHook) pObject);

// wxAddRemoveAdaptor has no wxWidgets block of its own, so its C++ helper
// class (include/kwx_helper_hooks.h) and the functions below form its block
// here.  wxAddRemoveCtrl::SetAdaptor() takes ownership of the adaptor, so
// kwxAddRemoveAdaptor_Delete is only for an adaptor that was never handed to a
// control.
TClassDef(kwxAddRemoveAdaptor) EXPORT TClass(kwxAddRemoveAdaptor)
    kwxAddRemoveAdaptor_Create(void* pObject);
EXPORT void kwxAddRemoveAdaptor_SetOnGetItemsCtrl(TSelf(kwxAddRemoveAdaptor) pObject,
                                                  void* pFunction);
EXPORT void kwxAddRemoveAdaptor_SetOnCanAdd(TSelf(kwxAddRemoveAdaptor) pObject, void* pFunction);
EXPORT void kwxAddRemoveAdaptor_SetOnCanRemove(TSelf(kwxAddRemoveAdaptor) pObject, void* pFunction);
EXPORT void kwxAddRemoveAdaptor_SetOnAdd(TSelf(kwxAddRemoveAdaptor) pObject, void* pFunction);
EXPORT void kwxAddRemoveAdaptor_SetOnRemove(TSelf(kwxAddRemoveAdaptor) pObject, void* pFunction);
EXPORT void kwxAddRemoveAdaptor_SetItemsCtrl(TSelf(kwxAddRemoveAdaptor) pObject,
                                             TClass(wxWindow) ctrl);
EXPORT void kwxAddRemoveAdaptor_SetCanAdd(TSelf(kwxAddRemoveAdaptor) pObject, TBool value);
EXPORT void kwxAddRemoveAdaptor_SetCanRemove(TSelf(kwxAddRemoveAdaptor) pObject, TBool value);
EXPORT void kwxAddRemoveAdaptor_Delete(TSelf(kwxAddRemoveAdaptor) pObject);

TClassDefExtend(kwxTextCompleterSimple, wxTextCompleterSimple) EXPORT
    void* kwxTextCompleterSimple_Create(void* pObject);
EXPORT void kwxTextCompleterSimple_Delete(TSelf(kwxTextCompleterSimple) pObject);
EXPORT void kwxTextCompleterSimple_SetOnGetCompletions(TSelf(kwxTextCompleterSimple) pObject,
                                                       void* pFunction);

TClassDef(wxTextCompleterSimple) EXPORT
    void wxTextCompleterSimple_SetOnGetCompletions(TSelf(wxTextCompleterSimple) pObject,
                                                   void* pFunction);

TClassDefExtend(kwxHtmlTagsModule, wxHtmlTagsModule) EXPORT
    void* kwxHtmlTagsModule_Create(void* pObject);
EXPORT void kwxHtmlTagsModule_Delete(TSelf(kwxHtmlTagsModule) pObject);
EXPORT void kwxHtmlTagsModule_SetOnFillHandlersTable(TSelf(kwxHtmlTagsModule) pObject,
                                                     void* pFunction);

TClassDef(wxHtmlTagsModule) EXPORT
    void wxHtmlTagsModule_SetOnFillHandlersTable(TSelf(wxHtmlTagsModule) pObject, void* pFunction);

// SetLogTarget() stores the target on a kwxAppTraits helper.  When the receiver
// is a platform traits object (the type wxApp::GetTraits() returns), the same
// target is installed as the process-wide active log target instead, so the
// call is safe for either object.  Both forms return the previous target.
TClassDefExtend(kwxAppTraits, wxAppTraits) EXPORT void* kwxAppTraits_Create(void* pObject);
EXPORT void kwxAppTraits_Delete(TSelf(kwxAppTraits) pObject);
EXPORT void kwxAppTraits_SetOnCreateLogTarget(TSelf(kwxAppTraits) pObject, void* pFunction);
EXPORT void kwxAppTraits_SetOnCreateRenderer(TSelf(kwxAppTraits) pObject, void* pFunction);
EXPORT TClass(wxLog) kwxAppTraits_SetLogTarget(TSelf(kwxAppTraits) pObject, TClass(wxLog) target);

TClassDef(wxAppTraits) EXPORT
    void wxAppTraits_SetOnCreateLogTarget(TSelf(wxAppTraits) pObject, void* pFunction);
EXPORT void wxAppTraits_SetOnCreateRenderer(TSelf(wxAppTraits) pObject, void* pFunction);
EXPORT TClass(wxLog) wxAppTraits_SetLogTarget(TSelf(wxAppTraits) pObject, TClass(wxLog) target);

TClassDefExtend(kwxDocument, wxDocument) EXPORT void* kwxDocument_Create(void* pObject);
EXPORT void kwxDocument_Delete(TSelf(kwxDocument) pObject);
EXPORT void kwxDocument_SetOnDoOpenDocument(TSelf(kwxDocument) pObject, void* pFunction);
EXPORT void kwxDocument_SetOnDoSaveDocument(TSelf(kwxDocument) pObject, void* pFunction);
EXPORT void kwxDocument_SetOnGetClassInfo(TSelf(kwxDocument) pObject, void* pFunction);
EXPORT void kwxDocument_SetOnIsModified(TSelf(kwxDocument) pObject, void* pFunction);
EXPORT void kwxDocument_SetOnModify(TSelf(kwxDocument) pObject, void* pFunction);
EXPORT void kwxDocument_SetOnOnCreate(TSelf(kwxDocument) pObject, void* pFunction);
EXPORT void kwxDocument_SetOnOnOpenDocument(TSelf(kwxDocument) pObject, void* pFunction);

// The typed setters above take a typed callback whose return value C reads back out of
// the call.  TypeScript's runtime offers one fixed void (*)(void*, void*, void*) thunk,
// so a value-returning hook cannot be installed there.  These are the same hooks in the
// uniform WithData shape -- void (*)(void* data, void* arg1, void* arg2) -- with the answer
// published by the matching Set...Result.
//
// Rules the implementations honour:
//   * a WithData hook installed takes precedence over the typed one;
//   * publishing nothing falls back to the base class implementation;
//   * a published answer is consumed once (reset before each invocation);
//   * integers/bools travel as (void*)(intptr_t)value.
EXPORT void kwxDocument_SetOnDoOpenDocumentWithData(TSelf(kwxDocument) pObject, void* pFunction,
                                                    void* data);
EXPORT void kwxDocument_SetDoOpenDocumentResult(TSelf(kwxDocument) pObject, TBool result);
EXPORT void kwxDocument_SetOnDoSaveDocumentWithData(TSelf(kwxDocument) pObject, void* pFunction,
                                                    void* data);
EXPORT void kwxDocument_SetDoSaveDocumentResult(TSelf(kwxDocument) pObject, TBool result);
EXPORT void kwxDocument_SetOnIsModifiedWithData(TSelf(kwxDocument) pObject, void* pFunction,
                                                void* data);
EXPORT void kwxDocument_SetIsModifiedResult(TSelf(kwxDocument) pObject, TBool result);
// Modify() returns void: arg1 == (void*)(intptr_t)modified.  The base flag is NOT set
// when a hook is installed -- use kwxDocument_ModifyBase for that.
EXPORT void kwxDocument_SetOnModifyWithData(TSelf(kwxDocument) pObject, void* pFunction,
                                            void* data);
// OnCreate: arg1 == const wxString* path (valid only during the call),
// arg2 == (void*)(intptr_t)flags.
EXPORT void kwxDocument_SetOnOnCreateWithData(TSelf(kwxDocument) pObject, void* pFunction,
                                              void* data);
EXPORT void kwxDocument_SetOnCreateResult(TSelf(kwxDocument) pObject, TBool result);
EXPORT void kwxDocument_SetOnOnOpenDocumentWithData(TSelf(kwxDocument) pObject, void* pFunction,
                                                    void* data);
EXPORT void kwxDocument_SetOnOpenDocumentResult(TSelf(kwxDocument) pObject, TBool result);

// Chaining exports: a hook replaces the base implementation, so a hook that must keep
// the base behaviour calls these.  They perform a QUALIFIED call -- a plain virtual call
// would re-enter the override and recurse.  kwxDocument_OnCreateBase is order-sensitive:
// it is what creates the view through the document's template.
EXPORT TBool kwxDocument_OnCreateBase(TSelf(kwxDocument) pObject, TClass(wxString) path,
                                      long flags);
EXPORT TBool kwxDocument_OnOpenDocumentBase(TSelf(kwxDocument) pObject, TClass(wxString) filename);
EXPORT TBool kwxDocument_IsModifiedBase(TSelf(kwxDocument) pObject);
EXPORT void kwxDocument_ModifyBase(TSelf(kwxDocument) pObject, TBool modified);

// A document created outside a template (a child/details document) is constructed with
// its parent: wxDocument(wxDocument* parent) moves the new object into the parent's
// child list and does NOT register it with the manager -- that is the C++ behaviour.
EXPORT void* kwxDocument_CreateWithParent(void* pObject, TClass(wxDocument) parent);

TClassDefExtend(kwxView, wxView) EXPORT void* kwxView_Create(void* pObject);
EXPORT void kwxView_Delete(TSelf(kwxView) pObject);
EXPORT void kwxView_SetOnOnDraw(TSelf(kwxView) pObject, void* pFunction);
EXPORT void kwxView_SetOnOnClose(TSelf(kwxView) pObject, void* pFunction);
EXPORT void kwxView_SetOnOnCreate(TSelf(kwxView) pObject, void* pFunction);
EXPORT void kwxView_SetOnOnUpdate(TSelf(kwxView) pObject, void* pFunction);
// OnDraw and OnUpdate are already void-shaped with <= 3 arguments, so they need no
// WithData form.  OnCreate and OnClose return bool and do.
EXPORT void kwxView_SetOnOnCreateWithData(TSelf(kwxView) pObject, void* pFunction, void* data);
EXPORT void kwxView_SetOnCreateResult(TSelf(kwxView) pObject, TBool result);
EXPORT void kwxView_SetOnOnCloseWithData(TSelf(kwxView) pObject, void* pFunction, void* data);
EXPORT void kwxView_SetOnCloseResult(TSelf(kwxView) pObject, TBool result);
// Chaining export: a hooked OnClose replaces wxView::OnClose, so a hook that must keep
// the base teardown calls this.  It is a QUALIFIED call -- a plain virtual call would
// re-enter the override and recurse.  With deleteWindow the base deletes the view.
EXPORT TBool kwxView_OnCloseBase(TSelf(kwxView) pObject, TBool deleteWindow);

// ---------------------------------------------------------------------------
// kwxDocTemplate -- a wxDocTemplate that creates the port's own document and view.
//
// wxDocTemplate can only instantiate a document/view pair through a wxClassInfo
// (docview.cpp:966-980), which no language binding can supply, so every doc/view
// pair a port uses goes through this helper.  DoCreateDocument()/DoCreateView() are
// the override points: they call the installed hook and then take the object the hook
// published with SetCreatedDocument()/SetCreatedView().  Publishing is the only shape
// that works for all six backends -- TypeScript's runtime can install exactly one
// thunk, void (*)(void*, void*, void*), so a value-returning callback is impossible
// there.  Everything the base class does around creation (InitDocument, filename,
// command processor, OnCreate, SetDocument, OnCreate) still runs.
//
// Ownership: wxDocTemplate's constructor calls manager->AssociateTemplate(this) and
// its destructor calls DisassociateTemplate, so the template is OWNED BY THE MANAGER
// (its destructor's Clear() deletes every template).  Never Delete() a template, and
// never let a manager be destroyed before a template created for it.
// ---------------------------------------------------------------------------
TClassDefExtend(kwxDocTemplate, wxDocTemplate) EXPORT TClass(kwxDocTemplate)
    kwxDocTemplate_Create(void* pObject, TClass(wxDocManager) manager, TClass(wxString) descr,
                          TClass(wxString) filter, TClass(wxString) dir, TClass(wxString) ext,
                          TClass(wxString) docTypeName, TClass(wxString) viewTypeName, long flags);
// Hook ABI: (pObject, templateObject) for the document, (pObject, templateObject,
// wxDocument*) for the view.  Both are plain void* and already match the fixed TS thunk.
EXPORT void kwxDocTemplate_SetOnCreateDocument(TSelf(kwxDocTemplate) pObject, void* pFunction);
EXPORT void kwxDocTemplate_SetOnCreateView(TSelf(kwxDocTemplate) pObject, void* pFunction);
// Called from inside the hook.  The template takes over the published object.
EXPORT void kwxDocTemplate_SetCreatedDocument(TSelf(kwxDocTemplate) pObject,
                                              TClass(wxDocument) doc);
EXPORT void kwxDocTemplate_SetCreatedView(TSelf(kwxDocTemplate) pObject, TClass(wxView) view);

// The two AUI MDI document/view frames (see include/kwx_helper_hooks.h).  They exist
// because wxDocParentFrameAny<T> / wxDocChildFrameAny<T, P> are templates and cannot be
// named by a generated binding.  Frames are wx-owned: destroy with wxWindow_Destroy.
TClassDefExtend(kwxDocAuiParentFrame, wxAuiMDIParentFrame) EXPORT TClass(kwxDocAuiParentFrame)
    kwxDocAuiParentFrame_Create(TClass(wxDocManager) manager, TClass(wxFrame) parent, int id,
                                TClass(wxString) title, TRect(x, y, width, height), int style);
EXPORT TClass(wxDocManager)
    kwxDocAuiParentFrame_GetDocumentManager(TSelf(kwxDocAuiParentFrame) self);

TClassDefExtend(kwxDocAuiChildFrame, wxAuiMDIChildFrame) EXPORT TClass(kwxDocAuiChildFrame)
    kwxDocAuiChildFrame_Create(TClass(wxDocument) doc, TClass(wxView) view,
                               TClass(wxAuiMDIParentFrame) parent, int id, TClass(wxString) title,
                               TRect(x, y, width, height), int style);
EXPORT TClass(wxDocument) kwxDocAuiChildFrame_GetDocument(TSelf(kwxDocAuiChildFrame) self);
EXPORT TClass(wxView) kwxDocAuiChildFrame_GetView(TSelf(kwxDocAuiChildFrame) self);

TClassDefExtend(kwxFileSystemHandler, wxFileSystemHandler) EXPORT
    void* kwxFileSystemHandler_Create(void* pObject);
EXPORT void kwxFileSystemHandler_Delete(TSelf(kwxFileSystemHandler) pObject);
EXPORT void kwxFileSystemHandler_SetOnCanOpen(TSelf(kwxFileSystemHandler) pObject, void* pFunction);
EXPORT void kwxFileSystemHandler_SetOnOpenFile(TSelf(kwxFileSystemHandler) pObject,
                                               void* pFunction);

TClassDefExtend(kwxHtmlTagHandler, wxHtmlTagHandler) EXPORT
    void* kwxHtmlTagHandler_Create(void* pObject);
EXPORT void kwxHtmlTagHandler_Delete(TSelf(kwxHtmlTagHandler) pObject);
EXPORT void kwxHtmlTagHandler_SetOnGetSupportedTags(TSelf(kwxHtmlTagHandler) pObject,
                                                    void* pFunction);
EXPORT void kwxHtmlTagHandler_SetOnHandleTag(TSelf(kwxHtmlTagHandler) pObject, void* pFunction);

TClassDefExtend(kwxEvent, wxEvent) EXPORT void* kwxEvent_Create(void* pObject);
EXPORT void kwxEvent_Delete(TSelf(kwxEvent) pObject);
EXPORT void kwxEvent_SetOnClone(TSelf(kwxEvent) pObject, void* pFunction);

TClassDefExtend(kwxVariantData, wxVariantData) EXPORT void* kwxVariantData_Create(void* pObject);
EXPORT void kwxVariantData_Delete(TSelf(kwxVariantData) pObject);
EXPORT void kwxVariantData_SetOnEq(TSelf(kwxVariantData) pObject, void* pFunction);
EXPORT void kwxVariantData_SetOnGetType(TSelf(kwxVariantData) pObject, void* pFunction);

TClassDefExtend(kwxWizardPage, wxWizardPage) EXPORT void* kwxWizardPage_Create(void* pObject);
EXPORT void kwxWizardPage_Delete(TSelf(kwxWizardPage) pObject);
EXPORT TBool kwxWizardPage_Create2(TSelf(kwxWizardPage) pObject, TClass(wxWizard) parent,
                                   TClass(wxBitmapBundle) bitmap);
EXPORT void kwxWizardPage_SetOnGetNext(TSelf(kwxWizardPage) pObject, void* pFunction);
EXPORT void kwxWizardPage_SetOnGetPrev(TSelf(kwxWizardPage) pObject, void* pFunction);
EXPORT void kwxWizardPage_SetOnTransferDataFromWindow(TSelf(kwxWizardPage) pObject,
                                                      void* pFunction);
EXPORT void kwxWizardPage_SetOnTransferDataToWindow(TSelf(kwxWizardPage) pObject, void* pFunction);
EXPORT void kwxWizardPage_SetOnGetNextOut(TSelf(kwxWizardPage) pObject, void* pFunction);
EXPORT void kwxWizardPage_SetOnGetPrevOut(TSelf(kwxWizardPage) pObject, void* pFunction);
EXPORT void kwxWizardPage_SetOnTransferDataFromWindowOut(TSelf(kwxWizardPage) pObject,
                                                         void* pFunction);
EXPORT void kwxWizardPage_SetOnTransferDataToWindowOut(TSelf(kwxWizardPage) pObject,
                                                       void* pFunction);

// The same hook family on the page class that owns the chain.  The leading
// void* pObject makes the generator emit a one-call constructor and is the
// language-object pointer every hook receives.  wxWizardPage declares no
// SetNext()/SetPrev()/Chain() at all, so this is the only helper available to a
// page that overrides a hook and must stay linkable.
TClassDefExtend(kwxWizardPageSimple, wxWizardPageSimple) EXPORT TClass(kwxWizardPageSimple)
    kwxWizardPageSimple_Create(void* pObject, TClass(wxWizard) parent, TClass(wxWizardPage) prev,
                               TClass(wxWizardPage) next, TClass(wxBitmapBundle) bitmap);
EXPORT void kwxWizardPageSimple_Delete(TSelf(kwxWizardPageSimple) pObject);
EXPORT void kwxWizardPageSimple_SetOnGetNext(TSelf(kwxWizardPageSimple) pObject, void* pFunction);
EXPORT void kwxWizardPageSimple_SetOnGetPrev(TSelf(kwxWizardPageSimple) pObject, void* pFunction);
EXPORT void kwxWizardPageSimple_SetOnTransferDataFromWindow(TSelf(kwxWizardPageSimple) pObject,
                                                            void* pFunction);
EXPORT void kwxWizardPageSimple_SetOnTransferDataToWindow(TSelf(kwxWizardPageSimple) pObject,
                                                          void* pFunction);
EXPORT void kwxWizardPageSimple_SetOnGetNextOut(TSelf(kwxWizardPageSimple) pObject,
                                                void* pFunction);
EXPORT void kwxWizardPageSimple_SetOnGetPrevOut(TSelf(kwxWizardPageSimple) pObject,
                                                void* pFunction);
EXPORT void kwxWizardPageSimple_SetOnTransferDataFromWindowOut(TSelf(kwxWizardPageSimple) pObject,
                                                               void* pFunction);
EXPORT void kwxWizardPageSimple_SetOnTransferDataToWindowOut(TSelf(kwxWizardPageSimple) pObject,
                                                             void* pFunction);

TClassDefExtend(kwxPopupTransientWindow, wxPopupTransientWindow) EXPORT
    TClass(kwxPopupTransientWindow)
        kwxPopupTransientWindow_Create(void* pObject, TClass(wxWindow) parent, int style);
EXPORT void kwxPopupTransientWindow_Delete(TSelf(kwxPopupTransientWindow) pObject);
EXPORT void kwxPopupTransientWindow_SetOnPopup(TSelf(kwxPopupTransientWindow) pObject,
                                               void* pFunction);
EXPORT void kwxPopupTransientWindow_SetOnShow(TSelf(kwxPopupTransientWindow) pObject,
                                              void* pFunction);
EXPORT void kwxPopupTransientWindow_SetOnProcessLeftDown(TSelf(kwxPopupTransientWindow) pObject,
                                                         void* pFunction);
EXPORT void kwxPopupTransientWindow_SetOnOnDismiss(TSelf(kwxPopupTransientWindow) pObject,
                                                   void* pFunction);
EXPORT void kwxPopupTransientWindow_CallBasePopup(TSelf(kwxPopupTransientWindow) pObject,
                                                  TClass(wxWindow) focus);
EXPORT TBool kwxPopupTransientWindow_CallBaseShow(TSelf(kwxPopupTransientWindow) pObject,
                                                  TBool show);
EXPORT TBool kwxPopupTransientWindow_CallBaseProcessLeftDown(TSelf(kwxPopupTransientWindow) pObject,
                                                             TClass(wxMouseEvent) event);
EXPORT void kwxPopupTransientWindow_CallBaseOnDismiss(TSelf(kwxPopupTransientWindow) pObject);

// ---------------------------------------------------------------------------
// wxDataView model and renderer hooks — the scripted half of the wxDataView surface
// ---------------------------------------------------------------------------
//
// A port cannot subclass wxDataViewModel, wxDataViewIndexListModel,
// wxDataViewVirtualListModel or wxDataViewCustomRenderer, so kwxFFI ships one helper
// object per type (include/kwx_helper_hooks.h) whose C++ virtuals each call a single
// foreign function.  Every hook uses the library's uniform single-thunk ABI
//
//     void (*)(void* data, void* arg1, void* arg2)
//
// where `data` is the per-hook token given to that same setter -- never the pObject
// handed to the _Create function.  Pointers travel unchanged; integers travel as
// (void*)(intptr_t)value, so an integer zero arrives as NULL and a callback must not
// read NULL as "missing" for an integer position.  Context the three-argument shape
// cannot carry -- a model column, a row, the wxDC and wxRect of a Render call -- is
// read back through the in-flight Get* getters on the same object while the callback
// runs.  A hook that returns a value publishes it with the matching Set*Result call
// before it returns; the in-flight block is cleared before every call, so a callback
// that publishes nothing leaves the documented neutral default in place (see
// include/kwx_helper_hooks.h) and a partially hooked object still behaves.  A
// …WithData setter overrides the plain typed setter for the same hook; passing a NULL
// pFunction clears it.
//
// wxDataViewModel hook argument map, after `data`:
//
//   GetValue            (&item, &variant)    column   -> GetPendingColumn
//   SetValue            (&item, &variant)    column   -> GetPendingColumn
//   GetParent           (&item, NULL)
//   IsContainer         (&item, NULL)
//   GetChildren         (&item, NULL)        children -> AddChildResult,
//                                            count    -> SetGetChildrenCountResult
//   HasValue            (&item, NULL)        column   -> GetPendingColumn
//   IsEnabled           (&item, NULL)        column   -> GetPendingColumn
//   GetAttr             (&item, NULL)        column   -> GetPendingColumn,
//                                            attr   -> SetGetAttrResult
//   HasContainerColumns (&item, NULL)
//   Compare             (&item1, &item2)     column   -> GetPendingColumn,
//                                            ascending-> GetPendingAscending
//   HasDefaultCompare   (NULL, NULL)
//   Resort              (NULL, NULL)

// The helper is reference counted exactly like every wxDataViewModel: release it with
// wxDataViewModel_DecRef (never delete it -- the destructor is protected).
TClassDefExtend(wxDataViewModel, wxObject) EXPORT TClass(wxDataViewModel)
    wxDataViewModel_CreateDefault(void* pObject);
EXPORT void wxDataViewModel_SetOnGetValueWithData(TSelf(wxDataViewModel) pObject, void* pFunction,
                                                  void* data);
EXPORT void wxDataViewModel_SetOnSetValueWithData(TSelf(wxDataViewModel) pObject, void* pFunction,
                                                  void* data);
EXPORT void wxDataViewModel_SetOnGetParentWithData(TSelf(wxDataViewModel) pObject, void* pFunction,
                                                   void* data);
EXPORT void wxDataViewModel_SetOnIsContainerWithData(TSelf(wxDataViewModel) pObject,
                                                     void* pFunction, void* data);
EXPORT void wxDataViewModel_SetOnGetChildrenWithData(TSelf(wxDataViewModel) pObject,
                                                     void* pFunction, void* data);
EXPORT void wxDataViewModel_SetOnHasValueWithData(TSelf(wxDataViewModel) pObject, void* pFunction,
                                                  void* data);
EXPORT void wxDataViewModel_SetOnIsEnabledWithData(TSelf(wxDataViewModel) pObject, void* pFunction,
                                                   void* data);
EXPORT void wxDataViewModel_SetOnHasContainerColumnsWithData(TSelf(wxDataViewModel) pObject,
                                                             void* pFunction, void* data);
EXPORT void wxDataViewModel_SetOnCompareWithData(TSelf(wxDataViewModel) pObject, void* pFunction,
                                                 void* data);
EXPORT void wxDataViewModel_SetOnHasDefaultCompareWithData(TSelf(wxDataViewModel) pObject,
                                                           void* pFunction, void* data);
EXPORT void wxDataViewModel_SetOnResortWithData(TSelf(wxDataViewModel) pObject, void* pFunction,
                                                void* data);
EXPORT void wxDataViewModel_SetOnGetAttrWithData(TSelf(wxDataViewModel) pObject, void* pFunction,
                                                 void* data);

// In-flight getters for the two hooks whose column does not fit in three arguments.
EXPORT unsigned int wxDataViewModel_GetPendingColumn(TSelf(wxDataViewModel) pObject);
EXPORT TBool wxDataViewModel_GetPendingAscending(TSelf(wxDataViewModel) pObject);

// Result publishers.  Call the one that matches the hook from inside that hook's
// callback, before it returns.  AddChildResult appends to the wxDataViewItemArray the
// in-flight GetChildren() received and is the preferred way to answer it.
EXPORT void wxDataViewModel_SetGetValueResult(TSelf(wxDataViewModel) pObject,
                                              TClass(wxVariant) value);
EXPORT void wxDataViewModel_SetSetValueResult(TSelf(wxDataViewModel) pObject, TBool result);
EXPORT void wxDataViewModel_SetGetParentResult(TSelf(wxDataViewModel) pObject,
                                               TClass(wxDataViewItem) parent);
EXPORT void wxDataViewModel_SetIsContainerResult(TSelf(wxDataViewModel) pObject, TBool result);
EXPORT void wxDataViewModel_SetGetChildrenCountResult(TSelf(wxDataViewModel) pObject,
                                                      unsigned int count);
EXPORT void wxDataViewModel_AddChildResult(TSelf(wxDataViewModel) pObject,
                                           TClass(wxDataViewItem) item);
EXPORT void wxDataViewModel_SetHasValueResult(TSelf(wxDataViewModel) pObject, TBool result);
EXPORT void wxDataViewModel_SetIsEnabledResult(TSelf(wxDataViewModel) pObject, TBool result);
EXPORT void wxDataViewModel_SetHasContainerColumnsResult(TSelf(wxDataViewModel) pObject,
                                                         TBool result);
EXPORT void wxDataViewModel_SetCompareResult(TSelf(wxDataViewModel) pObject, int result);
EXPORT void wxDataViewModel_SetHasDefaultCompareResult(TSelf(wxDataViewModel) pObject,
                                                       TBool result);
// Copies the attribute into the helper and is itself the success signal for GetAttr;
// publishing nothing means "default attributes".
EXPORT void wxDataViewModel_SetGetAttrResult(TSelf(wxDataViewModel) pObject,
                                             TClass(wxDataViewItemAttr) attr);

// ---------------------------------------------------------------------------
// wxDataViewVirtualListModel / wxDataViewIndexListModel
// ---------------------------------------------------------------------------
//
// Both row-based models expose the same hook set; they differ only in the wxWidgets
// base they derive from (wxDataViewVirtualListModel is a typedef of
// wxDataViewIndexListModel on macOS, which is why the two helpers are separate
// classes over one shared template).  Hook argument map, after `data`:
//
//   GetValueByRow        ((void*)(intptr_t)row, NULL)  column -> GetPendingColumn
//   SetValueByRow        (&variant, NULL)              row    -> GetPendingRow,
//                                                      column -> GetPendingColumn
//   GetRow               (&item, NULL)
//   GetCount             (NULL, NULL)
//   GetAttrByRow         ((void*)(intptr_t)row, (void*)(intptr_t)col)
//                                            attr -> SetGetAttrByRowAttr
//   IsEnabledByRow       ((void*)(intptr_t)row, (void*)(intptr_t)col)
//   Compare              (&item1, &item2)              column -> GetPendingColumn,
//                                                      ascending -> GetPendingAscending
//   HasDefaultCompare    (NULL, NULL)
//
// GetAttrByRow publishes the attribute with SetGetAttrByRowAttr, which copies it and
// implies success; a port that publishes nothing leaves the row undecorated.
//
// Like every wxDataViewModel these are reference counted: release them with
// wxDataViewModel_DecRef, never delete.
TClassDefExtend(wxDataViewVirtualListModel, wxDataViewModel) EXPORT
    TClass(wxDataViewVirtualListModel)
        wxDataViewVirtualListModel_Create(void* pObject, unsigned int initialSize);
EXPORT void wxDataViewVirtualListModel_SetOnGetValueByRowWithData(TSelf(wxDataViewVirtualListModel)
                                                                      pObject,
                                                                  void* pFunction, void* data);
EXPORT void wxDataViewVirtualListModel_SetOnSetValueByRowWithData(TSelf(wxDataViewVirtualListModel)
                                                                      pObject,
                                                                  void* pFunction, void* data);
EXPORT void wxDataViewVirtualListModel_SetOnGetRowWithData(TSelf(wxDataViewVirtualListModel)
                                                               pObject,
                                                           void* pFunction, void* data);
EXPORT void wxDataViewVirtualListModel_SetOnGetCountWithData(TSelf(wxDataViewVirtualListModel)
                                                                 pObject,
                                                             void* pFunction, void* data);
EXPORT void wxDataViewVirtualListModel_SetOnGetAttrByRowWithData(TSelf(wxDataViewVirtualListModel)
                                                                     pObject,
                                                                 void* pFunction, void* data);
EXPORT void wxDataViewVirtualListModel_SetOnIsEnabledByRowWithData(TSelf(wxDataViewVirtualListModel)
                                                                       pObject,
                                                                   void* pFunction, void* data);
EXPORT void wxDataViewVirtualListModel_SetOnCompareWithData(TSelf(wxDataViewVirtualListModel)
                                                                pObject,
                                                            void* pFunction, void* data);
EXPORT void wxDataViewVirtualListModel_SetOnHasDefaultCompareWithData(
    TSelf(wxDataViewVirtualListModel) pObject, void* pFunction, void* data);
EXPORT unsigned int wxDataViewVirtualListModel_GetPendingColumn(TSelf(wxDataViewVirtualListModel)
                                                                    pObject);
EXPORT unsigned int wxDataViewVirtualListModel_GetPendingRow(TSelf(wxDataViewVirtualListModel)
                                                                 pObject);
EXPORT TBool wxDataViewVirtualListModel_GetPendingAscending(TSelf(wxDataViewVirtualListModel)
                                                                pObject);
EXPORT void wxDataViewVirtualListModel_SetGetValueByRowResult(TSelf(wxDataViewVirtualListModel)
                                                                  pObject,
                                                              TClass(wxVariant) value);
EXPORT void wxDataViewVirtualListModel_SetSetValueByRowResult(TSelf(wxDataViewVirtualListModel)
                                                                  pObject,
                                                              TBool result);
EXPORT void wxDataViewVirtualListModel_SetGetRowResult(TSelf(wxDataViewVirtualListModel) pObject,
                                                       unsigned int row);
EXPORT void wxDataViewVirtualListModel_SetGetCountResult(TSelf(wxDataViewVirtualListModel) pObject,
                                                         unsigned int count);
EXPORT void wxDataViewVirtualListModel_SetGetAttrByRowResult(TSelf(wxDataViewVirtualListModel)
                                                                 pObject,
                                                             TBool result);
EXPORT void wxDataViewVirtualListModel_SetGetAttrByRowAttr(TSelf(wxDataViewVirtualListModel)
                                                               pObject,
                                                           TClass(wxDataViewItemAttr) attr);
EXPORT void wxDataViewVirtualListModel_SetIsEnabledByRowResult(TSelf(wxDataViewVirtualListModel)
                                                                   pObject,
                                                               TBool result);
EXPORT void wxDataViewVirtualListModel_SetCompareResult(TSelf(wxDataViewVirtualListModel) pObject,
                                                        int result);
EXPORT void wxDataViewVirtualListModel_SetHasDefaultCompareResult(TSelf(wxDataViewVirtualListModel)
                                                                      pObject,
                                                                  TBool result);

// Row notifications.  A port must call the matching one after it changes its own data,
// or the attached wxDataViewCtrl keeps showing stale rows.
TClassDefExtend(wxDataViewVirtualListModel, wxDataViewModel) EXPORT
    void wxDataViewVirtualListModel_RowPrepended(TSelf(wxDataViewVirtualListModel) pObject);
EXPORT void wxDataViewVirtualListModel_RowInserted(TSelf(wxDataViewVirtualListModel) pObject,
                                                   unsigned int before);
EXPORT void wxDataViewVirtualListModel_RowAppended(TSelf(wxDataViewVirtualListModel) pObject);
EXPORT void wxDataViewVirtualListModel_RowDeleted(TSelf(wxDataViewVirtualListModel) pObject,
                                                  unsigned int row);
// Deleting several rows in one notification.  wxArrayInt::Sort() orders the array, so a
// port does not have to announce rows one at a time.
EXPORT void wxDataViewVirtualListModel_RowsDeleted(TSelf(wxDataViewVirtualListModel) pObject,
                                                   TClass(wxArrayInt) rows);
EXPORT void wxDataViewVirtualListModel_RowChanged(TSelf(wxDataViewVirtualListModel) pObject,
                                                  unsigned int row);
EXPORT void wxDataViewVirtualListModel_RowValueChanged(TSelf(wxDataViewVirtualListModel) pObject,
                                                       unsigned int row, unsigned int col);
EXPORT void wxDataViewVirtualListModel_Reset(TSelf(wxDataViewVirtualListModel) pObject,
                                             unsigned int newSize);
// Writes the wxDataViewItem for `row` into the caller's `result` object.
EXPORT void wxDataViewVirtualListModel_GetItem(TSelf(wxDataViewVirtualListModel) pObject,
                                               unsigned int row, TClass(wxDataViewItem) result);

TClassDefExtend(wxDataViewIndexListModel, wxDataViewModel) EXPORT TClass(wxDataViewIndexListModel)
    wxDataViewIndexListModel_Create(void* pObject, unsigned int initialSize);
EXPORT void wxDataViewIndexListModel_SetOnGetValueByRowWithData(TSelf(wxDataViewIndexListModel)
                                                                    pObject,
                                                                void* pFunction, void* data);
EXPORT void wxDataViewIndexListModel_SetOnSetValueByRowWithData(TSelf(wxDataViewIndexListModel)
                                                                    pObject,
                                                                void* pFunction, void* data);
EXPORT void wxDataViewIndexListModel_SetOnGetRowWithData(TSelf(wxDataViewIndexListModel) pObject,
                                                         void* pFunction, void* data);
EXPORT void wxDataViewIndexListModel_SetOnGetCountWithData(TSelf(wxDataViewIndexListModel) pObject,
                                                           void* pFunction, void* data);
EXPORT void wxDataViewIndexListModel_SetOnGetAttrByRowWithData(TSelf(wxDataViewIndexListModel)
                                                                   pObject,
                                                               void* pFunction, void* data);
EXPORT void wxDataViewIndexListModel_SetOnIsEnabledByRowWithData(TSelf(wxDataViewIndexListModel)
                                                                     pObject,
                                                                 void* pFunction, void* data);
EXPORT void wxDataViewIndexListModel_SetOnCompareWithData(TSelf(wxDataViewIndexListModel) pObject,
                                                          void* pFunction, void* data);
EXPORT void wxDataViewIndexListModel_SetOnHasDefaultCompareWithData(TSelf(wxDataViewIndexListModel)
                                                                        pObject,
                                                                    void* pFunction, void* data);
EXPORT unsigned int wxDataViewIndexListModel_GetPendingColumn(TSelf(wxDataViewIndexListModel)
                                                                  pObject);
EXPORT unsigned int wxDataViewIndexListModel_GetPendingRow(TSelf(wxDataViewIndexListModel) pObject);
EXPORT TBool wxDataViewIndexListModel_GetPendingAscending(TSelf(wxDataViewIndexListModel) pObject);
EXPORT void wxDataViewIndexListModel_SetGetValueByRowResult(TSelf(wxDataViewIndexListModel) pObject,
                                                            TClass(wxVariant) value);
EXPORT void wxDataViewIndexListModel_SetSetValueByRowResult(TSelf(wxDataViewIndexListModel) pObject,
                                                            TBool result);
EXPORT void wxDataViewIndexListModel_SetGetRowResult(TSelf(wxDataViewIndexListModel) pObject,
                                                     unsigned int row);
EXPORT void wxDataViewIndexListModel_SetGetCountResult(TSelf(wxDataViewIndexListModel) pObject,
                                                       unsigned int count);
EXPORT void wxDataViewIndexListModel_SetGetAttrByRowResult(TSelf(wxDataViewIndexListModel) pObject,
                                                           TBool result);
EXPORT void wxDataViewIndexListModel_SetGetAttrByRowAttr(TSelf(wxDataViewIndexListModel) pObject,
                                                         TClass(wxDataViewItemAttr) attr);
EXPORT void wxDataViewIndexListModel_SetIsEnabledByRowResult(TSelf(wxDataViewIndexListModel)
                                                                 pObject,
                                                             TBool result);
EXPORT void wxDataViewIndexListModel_SetCompareResult(TSelf(wxDataViewIndexListModel) pObject,
                                                      int result);
EXPORT void wxDataViewIndexListModel_SetHasDefaultCompareResult(TSelf(wxDataViewIndexListModel)
                                                                    pObject,
                                                                TBool result);

TClassDefExtend(wxDataViewIndexListModel, wxDataViewModel) EXPORT
    void wxDataViewIndexListModel_RowPrepended(TSelf(wxDataViewIndexListModel) pObject);
EXPORT void wxDataViewIndexListModel_RowInserted(TSelf(wxDataViewIndexListModel) pObject,
                                                 unsigned int before);
EXPORT void wxDataViewIndexListModel_RowAppended(TSelf(wxDataViewIndexListModel) pObject);
EXPORT void wxDataViewIndexListModel_RowDeleted(TSelf(wxDataViewIndexListModel) pObject,
                                                unsigned int row);
// Deleting several rows in one notification.  wxArrayInt::Sort() orders the array, so a
// port does not have to announce rows one at a time.
EXPORT void wxDataViewIndexListModel_RowsDeleted(TSelf(wxDataViewIndexListModel) pObject,
                                                 TClass(wxArrayInt) rows);
EXPORT void wxDataViewIndexListModel_RowChanged(TSelf(wxDataViewIndexListModel) pObject,
                                                unsigned int row);
EXPORT void wxDataViewIndexListModel_RowValueChanged(TSelf(wxDataViewIndexListModel) pObject,
                                                     unsigned int row, unsigned int col);
EXPORT void wxDataViewIndexListModel_Reset(TSelf(wxDataViewIndexListModel) pObject,
                                           unsigned int newSize);
EXPORT void wxDataViewIndexListModel_GetItem(TSelf(wxDataViewIndexListModel) pObject,
                                             unsigned int row, TClass(wxDataViewItem) result);

// ---------------------------------------------------------------------------
// wxDataViewListStore
// ---------------------------------------------------------------------------
//
// The factory constructs the scripted subclass; with no hook installed every override of
// the subclass calls the wxDataViewListStore implementation, so the store keeps its own
// storage and default answers.  Hook argument map, after `data`:
//
//   HasValue            (&item, NULL)                     column -> GetPendingColumn
//   IsEnabledByRow      ((void*)(intptr_t)row, (void*)(intptr_t)col)
//   GetAttrByRow        ((void*)(intptr_t)row, (void*)(intptr_t)col)
//                                                       attr   -> SetGetAttrByRowAttr
//
// The attribute is published with SetGetAttrByRowAttr, which copies it and implies
// success.  A NULL pFunction clears that hook again.
//
// The store is reference counted like every wxDataViewModel: a consumer releases it with
// wxDataViewModel_DecRef, never with delete.
TClassDefExtend(wxDataViewListStore, wxDataViewModel) EXPORT
    void wxDataViewListStore_SetOnHasValueWithData(TSelf(wxDataViewListStore) pObject,
                                                   void* pFunction, void* data);
EXPORT void wxDataViewListStore_SetOnIsEnabledByRowWithData(TSelf(wxDataViewListStore) pObject,
                                                            void* pFunction, void* data);
EXPORT void wxDataViewListStore_SetOnGetAttrByRowWithData(TSelf(wxDataViewListStore) pObject,
                                                          void* pFunction, void* data);

EXPORT void wxDataViewListStore_SetHasValueResult(TSelf(wxDataViewListStore) pObject, TBool result);
EXPORT void wxDataViewListStore_SetIsEnabledByRowResult(TSelf(wxDataViewListStore) pObject,
                                                        TBool result);
EXPORT void wxDataViewListStore_SetGetAttrByRowResult(TSelf(wxDataViewListStore) pObject,
                                                      TBool result);
EXPORT void wxDataViewListStore_SetGetAttrByRowAttr(TSelf(wxDataViewListStore) pObject,
                                                    TClass(wxDataViewItemAttr) attr);

EXPORT unsigned int wxDataViewListStore_GetPendingRow(TSelf(wxDataViewListStore) pObject);
EXPORT unsigned int wxDataViewListStore_GetPendingColumn(TSelf(wxDataViewListStore) pObject);

// ---------------------------------------------------------------------------
// wxDataViewRenderer / wxDataViewCustomRenderer
// ---------------------------------------------------------------------------
//
// wxDataViewRenderer derives from wxDataViewRendererBase, which derives from wxObject;
// neither wxDataViewRendererBase nor wxDataViewCustomRendererBase is a class kwxFFI
// wraps, so wxObject is the declared parent.  These accessors work on any renderer,
// including the standard ones created by wxWidgets.
TClassDefExtend(wxDataViewRenderer, wxObject) EXPORT
    void wxDataViewRenderer_SetMode(TSelf(wxDataViewRenderer) pObject, int mode);
EXPORT int wxDataViewRenderer_GetMode(TSelf(wxDataViewRenderer) pObject);
EXPORT void wxDataViewRenderer_SetAlignment(TSelf(wxDataViewRenderer) pObject, int align);
EXPORT int wxDataViewRenderer_GetAlignment(TSelf(wxDataViewRenderer) pObject);
EXPORT void wxDataViewRenderer_EnableEllipsize(TSelf(wxDataViewRenderer) pObject, int mode);
EXPORT int wxDataViewRenderer_GetEllipsizeMode(TSelf(wxDataViewRenderer) pObject);
// The variant type the renderer expects -- wx 3.3's replacement for the deprecated
// wxDataViewModel::GetColumnType().
EXPORT TClassOwned(wxString) wxDataViewRenderer_GetVariantType(TSelf(wxDataViewRenderer) pObject);
// Copies the renderer's current value into the wxVariant the caller owns.
EXPORT TBool wxDataViewRenderer_GetValue(TSelf(wxDataViewRenderer) pObject,
                                         TClass(wxVariant) value);
EXPORT TBool wxDataViewRenderer_SetValue(TSelf(wxDataViewRenderer) pObject,
                                         TClass(wxVariant) value);
EXPORT void wxDataViewRenderer_SetEnabled(TSelf(wxDataViewRenderer) pObject, TBool enabled);
EXPORT TBool wxDataViewRenderer_IsHighlighted(TSelf(wxDataViewRenderer) pObject);
// Reads the renderer's accessible description.  The value is the pure virtual of
// wxDataViewRendererBase when wxUSE_ACCESSIBILITY is on; a build without accessibility
// answers with an empty string.  The caller owns the returned string.
EXPORT TClassOwned(wxString)
    wxDataViewRenderer_GetAccessibleDescription(TSelf(wxDataViewRenderer) pObject);

// Hook argument map, after `data`:
//
//   Render                 (dcPtr, NULL)        cell -> GetRenderRect,
//                                               state -> GetRenderState
//   GetSize                (NULL, NULL)
//   SetValue               (&variant, NULL)
//   GetValue               (&variant, NULL)
//   ActivateCell           (NULL, NULL)        cell -> GetRenderRect,
//                                               column -> GetPendingColumn,
//                                               mouse event -> GetActivateCellMouseEvent
//   Activate               (NULL, NULL)        cell -> GetRenderRect,
//                                               column -> GetPendingColumn
//   LeftClick              (NULL, NULL)        cell -> GetRenderRect,
//                                               column -> GetPendingColumn,
//                                               cursor -> GetPendingCursorX/Y
//   StartDrag              (NULL, NULL)        cell -> GetRenderRect,
//                                               column -> GetPendingColumn,
//                                               cursor -> GetPendingCursorX/Y
//   CreateEditorCtrl       (parentWnd, &value) labelRect -> GetEditorRect
//   GetValueFromEditorCtrl (editorWnd, NULL)    value out-slot -> SetGetValueFromEditorCtrlValue
//   Validate               (&value, NULL)
//   HasEditorCtrl          (NULL, NULL)
//   GetAccessibleDescription (NULL, NULL)   text -> SetAccessibleDescription
//
// The renderer keeps the value it was last given, so a Render callback reads it with
// GetCurrentValue.  GetValue publishes with SetGetValueResult and publishing a value is
// itself the success signal; GetValueFromEditorCtrl does the same with
// SetGetValueFromEditorCtrlValue.  Every other hook publishes its boolean explicitly.
TClassDefExtend(wxDataViewCustomRenderer, wxDataViewRenderer) EXPORT
    TClass(wxDataViewCustomRenderer)
        wxDataViewCustomRenderer_Create(TString variantType, int mode, int align);
EXPORT void wxDataViewCustomRenderer_SetOnRenderWithData(TSelf(wxDataViewCustomRenderer) pObject,
                                                         void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnGetSizeWithData(TSelf(wxDataViewCustomRenderer) pObject,
                                                          void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnSetValueWithData(TSelf(wxDataViewCustomRenderer) pObject,
                                                           void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnGetValueWithData(TSelf(wxDataViewCustomRenderer) pObject,
                                                           void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnActivateCellWithData(TSelf(wxDataViewCustomRenderer)
                                                                   pObject,
                                                               void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnActivateWithData(TSelf(wxDataViewCustomRenderer) pObject,
                                                           void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnLeftClickWithData(TSelf(wxDataViewCustomRenderer) pObject,
                                                            void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnStartDragWithData(TSelf(wxDataViewCustomRenderer) pObject,
                                                            void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnCreateEditorCtrlWithData(TSelf(wxDataViewCustomRenderer)
                                                                       pObject,
                                                                   void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnGetValueFromEditorCtrlWithData(
    TSelf(wxDataViewCustomRenderer) pObject, void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnValidateWithData(TSelf(wxDataViewCustomRenderer) pObject,
                                                           void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnHasEditorCtrlWithData(TSelf(wxDataViewCustomRenderer)
                                                                    pObject,
                                                                void* pFunction, void* data);
EXPORT void wxDataViewCustomRenderer_SetOnGetAccessibleDescriptionWithData(
    TSelf(wxDataViewCustomRenderer) pObject, void* pFunction, void* data);

// In-flight getters.  GetRenderDC, GetEditorParent and GetEditorCtrl are borrowed
// pointers that are only valid for the duration of the callback; GetCurrentValue
// returns a new wxVariant the caller must free.
EXPORT TClass(wxDC) wxDataViewCustomRenderer_GetRenderDC(TSelf(wxDataViewCustomRenderer) pObject);
EXPORT void wxDataViewCustomRenderer_GetRenderRect(TSelf(wxDataViewCustomRenderer) pObject,
                                                   TRectOut(x, y, width, height));
EXPORT int wxDataViewCustomRenderer_GetRenderState(TSelf(wxDataViewCustomRenderer) pObject);
EXPORT TClassOwned(wxVariant)
    wxDataViewCustomRenderer_GetCurrentValue(TSelf(wxDataViewCustomRenderer) pObject);
EXPORT TClassOwned(wxRect)
    wxDataViewCustomRenderer_GetEditorRect(TSelf(wxDataViewCustomRenderer) pObject);
EXPORT TClass(wxWindow)
    wxDataViewCustomRenderer_GetEditorParent(TSelf(wxDataViewCustomRenderer) pObject);
EXPORT TClass(wxWindow)
    wxDataViewCustomRenderer_GetEditorCtrl(TSelf(wxDataViewCustomRenderer) pObject);
EXPORT unsigned int wxDataViewCustomRenderer_GetPendingColumn(TSelf(wxDataViewCustomRenderer)
                                                                  pObject);
// The mouse event ActivateCell received -- borrowed, valid only inside that callback, and
// null when the cell was activated without a mouse event.
EXPORT TClass(wxMouseEvent)
    wxDataViewCustomRenderer_GetActivateCellMouseEvent(TSelf(wxDataViewCustomRenderer) pObject);
// The cursor LeftClick/StartDrag received; 0 when the hook was not called with a point.
EXPORT int wxDataViewCustomRenderer_GetPendingCursorX(TSelf(wxDataViewCustomRenderer) pObject);
EXPORT int wxDataViewCustomRenderer_GetPendingCursorY(TSelf(wxDataViewCustomRenderer) pObject);
// The two protected wxDataViewCustomRenderer helpers, for a Render()/GetSize() callback.
// RenderText() is what the standard renderers use, so it also paints the selection state;
// it needs the wxDC and state the callback received and a cell rect in DC coordinates.
// The wrapper always calls the base implementation, never an override.
EXPORT void wxDataViewCustomRenderer_RenderText(TSelf(wxDataViewCustomRenderer) pObject,
                                                TString text, int xoffset,
                                                TRect(cell_x, cell_y, cell_width, cell_height),
                                                TClass(wxDC) dc, int state);
EXPORT void wxDataViewCustomRenderer_GetTextExtent(TSelf(wxDataViewCustomRenderer) pObject,
                                                   TString text, TSizeOut(width, height));

EXPORT void wxDataViewCustomRenderer_SetRenderResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                     TBool result);
EXPORT void wxDataViewCustomRenderer_SetGetSizeResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                      int width, int height);
EXPORT void wxDataViewCustomRenderer_SetGetValueResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                       TClass(wxVariant) value);
EXPORT void wxDataViewCustomRenderer_SetSetValueResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                       TBool result);
EXPORT void wxDataViewCustomRenderer_SetActivateCellResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                           TBool result);
EXPORT void wxDataViewCustomRenderer_SetActivateResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                       TBool result);
EXPORT void wxDataViewCustomRenderer_SetLeftClickResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                        TBool result);
EXPORT void wxDataViewCustomRenderer_SetStartDragResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                        TBool result);
// The renderer takes no ownership of the editor window; wxDataViewCtrl does.
EXPORT void wxDataViewCustomRenderer_SetCreateEditorCtrlResult(TSelf(wxDataViewCustomRenderer)
                                                                   pObject,
                                                               TClass(wxWindow) editor);
EXPORT void wxDataViewCustomRenderer_SetGetValueFromEditorCtrlResult(TSelf(wxDataViewCustomRenderer)
                                                                         pObject,
                                                                     TBool result);
// The value the editor produced.  Copying it in is itself the success signal for
// GetValueFromEditorCtrl, so a port that publishes only the value reports success.
EXPORT void wxDataViewCustomRenderer_SetGetValueFromEditorCtrlValue(TSelf(wxDataViewCustomRenderer)
                                                                        pObject,
                                                                    TClass(wxVariant) value);
EXPORT void wxDataViewCustomRenderer_SetValidateResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                       TBool result);
EXPORT void wxDataViewCustomRenderer_SetHasEditorCtrlResult(TSelf(wxDataViewCustomRenderer) pObject,
                                                            TBool result);
// Publishes the text GetAccessibleDescription() answers with.  The wrapper COPIES it, so the
// caller's buffer may be released as soon as this returns; publishing is itself the signal
// that the hook answered, and publishing an empty string is a valid answer.
EXPORT void wxDataViewCustomRenderer_SetAccessibleDescription(TSelf(wxDataViewCustomRenderer)
                                                                  pObject,
                                                              TClass(wxString) description);

// ---------------------------------------------------------------------------
// Standard wxDataView renderers
// ---------------------------------------------------------------------------
//
// These are real wxWidgets classes, not helpers: they are created directly and the
// renderer is then owned by the column it is handed to (wxDataViewColumn_CreateWithRenderer).
// A column that needs scripted behaviour uses wxDataViewCustomRenderer instead.
TClassDefExtend(wxDataViewTextRenderer, wxDataViewRenderer) EXPORT TClass(wxDataViewTextRenderer)
    wxDataViewTextRenderer_CreateDefault();
EXPORT TClass(wxDataViewTextRenderer)
    wxDataViewTextRenderer_Create(TString variantType, int mode, int align);
// wxUSE_MARKUP only.
EXPORT void wxDataViewTextRenderer_EnableMarkup(TSelf(wxDataViewTextRenderer) pObject,
                                                TBool enable);

TClassDefExtend(wxDataViewToggleRenderer, wxDataViewRenderer) EXPORT
    TClass(wxDataViewToggleRenderer) wxDataViewToggleRenderer_CreateDefault();
EXPORT TClass(wxDataViewToggleRenderer)
    wxDataViewToggleRenderer_Create(TString variantType, int mode, int align);
// C++ has no "unset" for this: radio is a one-way switch, so TBool false does nothing.
EXPORT void wxDataViewToggleRenderer_ShowAsRadio(TSelf(wxDataViewToggleRenderer) pObject,
                                                 TBool radio);

TClassDefExtend(wxDataViewBitmapRenderer, wxDataViewRenderer) EXPORT
    TClass(wxDataViewBitmapRenderer) wxDataViewBitmapRenderer_CreateDefault();
EXPORT TClass(wxDataViewBitmapRenderer)
    wxDataViewBitmapRenderer_Create(TString variantType, int mode, int align);

TClassDefExtend(wxDataViewProgressRenderer, wxDataViewRenderer) EXPORT
    TClass(wxDataViewProgressRenderer)
        wxDataViewProgressRenderer_Create(TClass(wxString) label, TString variantType, int mode,
                                          int align);

TClassDefExtend(wxDataViewIconTextRenderer, wxDataViewRenderer) EXPORT
    TClass(wxDataViewIconTextRenderer) wxDataViewIconTextRenderer_CreateDefault();
EXPORT TClass(wxDataViewIconTextRenderer)
    wxDataViewIconTextRenderer_Create(TString variantType, int mode, int align);

TClassDefExtend(wxDataViewSpinRenderer, wxDataViewCustomRenderer) EXPORT
    TClass(wxDataViewSpinRenderer)
        wxDataViewSpinRenderer_Create(int min, int max, int mode, int align);

TClassDefExtend(wxDataViewChoiceRenderer, wxDataViewCustomRenderer) EXPORT
    TClass(wxDataViewChoiceRenderer)
        wxDataViewChoiceRenderer_Create(TClass(wxArrayString) choices, int mode, int align);
EXPORT TClassOwned(wxString)
    wxDataViewChoiceRenderer_GetChoice(TSelf(wxDataViewChoiceRenderer) pObject, TArrayLen index);
// Borrowed: the renderer's own choice list.
EXPORT TClass(wxArrayString)
    wxDataViewChoiceRenderer_GetChoices(TSelf(wxDataViewChoiceRenderer) pObject);

TClassDefExtend(wxDataViewChoiceByIndexRenderer, wxDataViewChoiceRenderer) EXPORT
    TClass(wxDataViewChoiceByIndexRenderer)
        wxDataViewChoiceByIndexRenderer_Create(TClass(wxArrayString) choices, int mode, int align);

TClassDefExtend(wxDataViewDateRenderer, wxDataViewRenderer) EXPORT TClass(wxDataViewDateRenderer)
    wxDataViewDateRenderer_Create(TString variantType, int mode, int align);

TClassDefExtend(wxDataViewCheckIconTextRenderer, wxDataViewCustomRenderer) EXPORT
    TClass(wxDataViewCheckIconTextRenderer) wxDataViewCheckIconTextRenderer_CreateDefault();
EXPORT TClass(wxDataViewCheckIconTextRenderer)
    wxDataViewCheckIconTextRenderer_Create(int mode, int align);
// Once allowed, the user may also set the third (undetermined) checkbox state.
EXPORT void wxDataViewCheckIconTextRenderer_Allow3rdStateForUser(
    TSelf(wxDataViewCheckIconTextRenderer) pObject, TBool allow);

// ---------------------------------------------------------------------------
// wxDataViewColumn — factory for a column driven by a scripted renderer
// ---------------------------------------------------------------------------
//
// The column takes ownership of the renderer: do not delete the renderer after
// handing it here.  align is a wxALIGN_* value or wxDVR_DEFAULT_ALIGNMENT, flags a
// combination of wxDATAVIEW_COL_*.
TClassDef(wxDataViewColumn) EXPORT TClass(wxDataViewColumn)
    wxDataViewColumn_CreateWithRenderer(TClass(wxString) title, TClass(wxDataViewRenderer) renderer,
                                        unsigned int modelColumn, int width, int align, int flags);
