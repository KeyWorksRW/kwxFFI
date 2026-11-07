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

TClassDefExtend(kwxApp, wxApp) EXPORT void* kwxApp_Create(void* pObject);
EXPORT void kwxApp_Delete(TSelf(kwxApp) pObject);
EXPORT void kwxApp_SetOnOnCmdLineParsed(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnOnInitCmdLine(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnOnExit(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnFilterEvent(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnGetClassInfo(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnOnAssertFailure(TSelf(kwxApp) pObject, void* pFunction);
EXPORT void kwxApp_SetOnCreateTraits(TSelf(kwxApp) pObject, void* pFunction);

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

TClassDefExtend(kwxEvtHandler, wxEvtHandler) EXPORT void* kwxEvtHandler_Create(void* pObject);
EXPORT void kwxEvtHandler_Delete(TSelf(kwxEvtHandler) pObject);
EXPORT void kwxEvtHandler_SetOnProcessEvent(TSelf(kwxEvtHandler) pObject, void* pFunction);

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
EXPORT void kwxPreferencesPage_SetOnGetName(TSelf(kwxPreferencesPage) pObject, void* pFunction);
EXPORT void kwxPreferencesPage_SetOnCreateWindow(TSelf(kwxPreferencesPage) pObject,
                                                 void* pFunction);
EXPORT void kwxPreferencesPage_SetOnGetIcon(TSelf(kwxPreferencesPage) pObject, void* pFunction);

// wxPreferencesPage had no declaration block at all, so the <Base>_SetOn
// spellings the portability matrix resolves an ovh row to get their own block
// here.  The receiver is the same kwxPreferencesPage helper object.

TClassDef(wxPreferencesPage) EXPORT
    void wxPreferencesPage_SetOnGetName(TSelf(wxPreferencesPage) pObject, void* pFunction);
EXPORT void wxPreferencesPage_SetOnCreateWindow(TSelf(wxPreferencesPage) pObject, void* pFunction);
EXPORT void wxPreferencesPage_SetOnGetIcon(TSelf(wxPreferencesPage) pObject, void* pFunction);

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

TClassDefExtend(kwxView, wxView) EXPORT void* kwxView_Create(void* pObject);
EXPORT void kwxView_Delete(TSelf(kwxView) pObject);
EXPORT void kwxView_SetOnOnDraw(TSelf(kwxView) pObject, void* pFunction);
EXPORT void kwxView_SetOnOnClose(TSelf(kwxView) pObject, void* pFunction);
EXPORT void kwxView_SetOnOnCreate(TSelf(kwxView) pObject, void* pFunction);
EXPORT void kwxView_SetOnOnUpdate(TSelf(kwxView) pObject, void* pFunction);

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
EXPORT void kwxWizardPage_SetOnGetNext(TSelf(kwxWizardPage) pObject, void* pFunction);
EXPORT void kwxWizardPage_SetOnGetPrev(TSelf(kwxWizardPage) pObject, void* pFunction);

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
