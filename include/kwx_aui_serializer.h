#pragma once

// Declarations for wxAuiManager/wxAuiNotebook layout serialization.
//
// wxWidgets 3.3 dispatches layout save/load through the abstract
// wxAuiSerializer and wxAuiDeserializer classes.  A foreign language cannot
// derive from them, so src/kwx_aui_serializer.cpp provides callback-driven
// subclasses (the declarations below name them kwxAuiSerializer and
// kwxAuiDeserializer).  The hooks have the same shape as the override hooks in
// include/kwx_hook_exports.h: a void* object supplied at creation time and one
// void* callback per virtual.
//
// The layout information structures cross the ABI as handles.  A callback
// receives a borrowed handle that is valid only for the duration of that
// callback.  The arrays a deserializer callback returns are owned by the
// library: it copies them and then deletes them, so the callback must allocate
// them with the matching *_Create function and must not retain them.

#include "kwx_def.h"
#include "kwx_types.h"

// ---------------------------------------------------------------------------
// wxAuiPaneLayoutInfo
// ---------------------------------------------------------------------------

TClassDef(wxAuiPaneLayoutInfo) TClass(wxAuiPaneLayoutInfo)
    wxAuiPaneLayoutInfo_Create(TClass(wxString) name);
void wxAuiPaneLayoutInfo_Delete(TSelf(wxAuiPaneLayoutInfo) pObject);
TClass(wxString) wxAuiPaneLayoutInfo_GetName(TSelf(wxAuiPaneLayoutInfo) pObject);
int wxAuiPaneLayoutInfo_GetDockDirection(TSelf(wxAuiPaneLayoutInfo) pObject);
int wxAuiPaneLayoutInfo_GetDockLayer(TSelf(wxAuiPaneLayoutInfo) pObject);
int wxAuiPaneLayoutInfo_GetDockRow(TSelf(wxAuiPaneLayoutInfo) pObject);
int wxAuiPaneLayoutInfo_GetDockPos(TSelf(wxAuiPaneLayoutInfo) pObject);
int wxAuiPaneLayoutInfo_GetDockProportion(TSelf(wxAuiPaneLayoutInfo) pObject);
int wxAuiPaneLayoutInfo_GetDockSize(TSelf(wxAuiPaneLayoutInfo) pObject);
void wxAuiPaneLayoutInfo_SetDockDirection(TSelf(wxAuiPaneLayoutInfo) pObject, int direction);
void wxAuiPaneLayoutInfo_SetDockLayer(TSelf(wxAuiPaneLayoutInfo) pObject, int layer);
void wxAuiPaneLayoutInfo_SetDockRow(TSelf(wxAuiPaneLayoutInfo) pObject, int row);
void wxAuiPaneLayoutInfo_SetDockPos(TSelf(wxAuiPaneLayoutInfo) pObject, int pos);
void wxAuiPaneLayoutInfo_SetDockProportion(TSelf(wxAuiPaneLayoutInfo) pObject, int proportion);
void wxAuiPaneLayoutInfo_SetDockSize(TSelf(wxAuiPaneLayoutInfo) pObject, int size);
TClass(wxPoint) wxAuiPaneLayoutInfo_GetFloatingPos(TSelf(wxAuiPaneLayoutInfo) pObject);
void wxAuiPaneLayoutInfo_SetFloatingPos(TSelf(wxAuiPaneLayoutInfo) pObject, TPoint(pos_x, pos_y));
TClass(wxSize) wxAuiPaneLayoutInfo_GetFloatingSize(TSelf(wxAuiPaneLayoutInfo) pObject);
void wxAuiPaneLayoutInfo_SetFloatingSize(TSelf(wxAuiPaneLayoutInfo) pObject, TSize(width, height));
TClass(wxSize) wxAuiPaneLayoutInfo_GetFloatingClientSize(TSelf(wxAuiPaneLayoutInfo) pObject);
void wxAuiPaneLayoutInfo_SetFloatingClientSize(TSelf(wxAuiPaneLayoutInfo) pObject,
                                               TSize(width, height));
TBool wxAuiPaneLayoutInfo_IsMaximized(TSelf(wxAuiPaneLayoutInfo) pObject);
void wxAuiPaneLayoutInfo_SetMaximized(TSelf(wxAuiPaneLayoutInfo) pObject, TBool maximized);
TBool wxAuiPaneLayoutInfo_IsHidden(TSelf(wxAuiPaneLayoutInfo) pObject);
void wxAuiPaneLayoutInfo_SetHidden(TSelf(wxAuiPaneLayoutInfo) pObject, TBool hidden);

// ---------------------------------------------------------------------------
// wxAuiTabLayoutInfo
// ---------------------------------------------------------------------------

TClassDef(wxAuiTabLayoutInfo) TClass(wxAuiTabLayoutInfo) wxAuiTabLayoutInfo_Create();
void wxAuiTabLayoutInfo_Delete(TSelf(wxAuiTabLayoutInfo) pObject);
int wxAuiTabLayoutInfo_GetDockDirection(TSelf(wxAuiTabLayoutInfo) pObject);
int wxAuiTabLayoutInfo_GetDockLayer(TSelf(wxAuiTabLayoutInfo) pObject);
int wxAuiTabLayoutInfo_GetDockRow(TSelf(wxAuiTabLayoutInfo) pObject);
int wxAuiTabLayoutInfo_GetDockPos(TSelf(wxAuiTabLayoutInfo) pObject);
int wxAuiTabLayoutInfo_GetDockProportion(TSelf(wxAuiTabLayoutInfo) pObject);
int wxAuiTabLayoutInfo_GetDockSize(TSelf(wxAuiTabLayoutInfo) pObject);
void wxAuiTabLayoutInfo_SetDockDirection(TSelf(wxAuiTabLayoutInfo) pObject, int direction);
void wxAuiTabLayoutInfo_SetDockLayer(TSelf(wxAuiTabLayoutInfo) pObject, int layer);
void wxAuiTabLayoutInfo_SetDockRow(TSelf(wxAuiTabLayoutInfo) pObject, int row);
void wxAuiTabLayoutInfo_SetDockPos(TSelf(wxAuiTabLayoutInfo) pObject, int pos);
void wxAuiTabLayoutInfo_SetDockProportion(TSelf(wxAuiTabLayoutInfo) pObject, int proportion);
void wxAuiTabLayoutInfo_SetDockSize(TSelf(wxAuiTabLayoutInfo) pObject, int size);
TClass(wxArrayInt) wxAuiTabLayoutInfo_GetPages(TSelf(wxAuiTabLayoutInfo) pObject);
void wxAuiTabLayoutInfo_SetPages(TSelf(wxAuiTabLayoutInfo) pObject, TClass(wxArrayInt) pages);
TClass(wxArrayInt) wxAuiTabLayoutInfo_GetPinned(TSelf(wxAuiTabLayoutInfo) pObject);
void wxAuiTabLayoutInfo_SetPinned(TSelf(wxAuiTabLayoutInfo) pObject, TClass(wxArrayInt) pinned);
int wxAuiTabLayoutInfo_GetActive(TSelf(wxAuiTabLayoutInfo) pObject);
void wxAuiTabLayoutInfo_SetActive(TSelf(wxAuiTabLayoutInfo) pObject, int active);

// ---------------------------------------------------------------------------
// Arrays used by the deserializer callbacks
// ---------------------------------------------------------------------------

TClassDef(wxAuiPaneLayoutInfoArray) TClass(wxAuiPaneLayoutInfoArray)
    wxAuiPaneLayoutInfoArray_Create();
void wxAuiPaneLayoutInfoArray_Delete(TSelf(wxAuiPaneLayoutInfoArray) pObject);
int wxAuiPaneLayoutInfoArray_GetCount(TSelf(wxAuiPaneLayoutInfoArray) pObject);
void wxAuiPaneLayoutInfoArray_Add(TSelf(wxAuiPaneLayoutInfoArray) pObject,
                                  TClass(wxAuiPaneLayoutInfo) item);
TClass(wxAuiPaneLayoutInfo)
    wxAuiPaneLayoutInfoArray_Item(TSelf(wxAuiPaneLayoutInfoArray) pObject, int index);

TClassDef(wxAuiTabLayoutInfoArray) TClass(wxAuiTabLayoutInfoArray) wxAuiTabLayoutInfoArray_Create();
void wxAuiTabLayoutInfoArray_Delete(TSelf(wxAuiTabLayoutInfoArray) pObject);
int wxAuiTabLayoutInfoArray_GetCount(TSelf(wxAuiTabLayoutInfoArray) pObject);
void wxAuiTabLayoutInfoArray_Add(TSelf(wxAuiTabLayoutInfoArray) pObject,
                                 TClass(wxAuiTabLayoutInfo) item);
TClass(wxAuiTabLayoutInfo)
    wxAuiTabLayoutInfoArray_Item(TSelf(wxAuiTabLayoutInfoArray) pObject, int index);

// ---------------------------------------------------------------------------
// Callback plumbing
//
// Every callback uses the fixed three-pointer void shape the language
// runtimes provide.  A hook that has to return a value writes it into one of
// the helper objects below, which is passed as a callback argument.
// ---------------------------------------------------------------------------

TClassDef(kwxAuiCallbackResult) void kwxAuiCallbackResult_SetPointer(TSelf(kwxAuiCallbackResult)
                                                                         pObject,
                                                                     void* value);
void* kwxAuiCallbackResult_GetPointer(TSelf(kwxAuiCallbackResult) pObject);

TClassDef(kwxAuiOrphanedPage) TClass(wxAuiNotebook)
    kwxAuiOrphanedPage_GetNotebook(TSelf(kwxAuiOrphanedPage) pObject);
int kwxAuiOrphanedPage_GetPage(TSelf(kwxAuiOrphanedPage) pObject);
TClass(wxAuiTabCtrl) kwxAuiOrphanedPage_GetTabCtrl(TSelf(kwxAuiOrphanedPage) pObject);
void kwxAuiOrphanedPage_SetTabCtrl(TSelf(kwxAuiOrphanedPage) pObject, TClass(wxAuiTabCtrl) tabCtrl);
int kwxAuiOrphanedPage_GetTabIndex(TSelf(kwxAuiOrphanedPage) pObject);
void kwxAuiOrphanedPage_SetTabIndex(TSelf(kwxAuiOrphanedPage) pObject, int tabIndex);
TBool kwxAuiOrphanedPage_GetResult(TSelf(kwxAuiOrphanedPage) pObject);
void kwxAuiOrphanedPage_SetResult(TSelf(kwxAuiOrphanedPage) pObject, TBool result);

// ---------------------------------------------------------------------------
// kwxAuiSerializer — callback-driven wxAuiSerializer
//
// Callback arguments are (pObject, arg1, arg2), result void:
//   BeforeSave, BeforeSavePanes, AfterSavePanes, BeforeSaveNotebooks,
//   AfterSaveNotebooks, AfterSave, AfterSaveNotebook: (pObject, null, null)
//   SavePane:                    (pObject, wxAuiPaneLayoutInfo*, null)
//   BeforeSaveNotebook:          (pObject, wxString*, null)
//   SaveNotebookTabControl:      (pObject, wxAuiTabLayoutInfo*, null)
// The pane, tab and name handles are borrowed and valid only during the call.
// ---------------------------------------------------------------------------

TClassDefExtend(kwxAuiSerializer, wxAuiSerializer) TClass(kwxAuiSerializer)
    kwxAuiSerializer_Create(void* pObject);
void kwxAuiSerializer_Delete(TSelf(kwxAuiSerializer) pObject);
void kwxAuiSerializer_SetOnBeforeSave(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_SetOnBeforeSavePanes(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_SetOnSavePane(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_SetOnAfterSavePanes(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_SetOnBeforeSaveNotebooks(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_SetOnAfterSaveNotebooks(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_SetOnAfterSave(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_SetOnBeforeSaveNotebook(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_SetOnSaveNotebookTabControl(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_SetOnAfterSaveNotebook(TSelf(kwxAuiSerializer) pObject, void* pFunction);
void kwxAuiSerializer_BeforeSave(TSelf(kwxAuiSerializer) pObject);
void kwxAuiSerializer_BeforeSavePanes(TSelf(kwxAuiSerializer) pObject);
void kwxAuiSerializer_AfterSavePanes(TSelf(kwxAuiSerializer) pObject);
void kwxAuiSerializer_BeforeSaveNotebooks(TSelf(kwxAuiSerializer) pObject);
void kwxAuiSerializer_AfterSaveNotebooks(TSelf(kwxAuiSerializer) pObject);
void kwxAuiSerializer_AfterSave(TSelf(kwxAuiSerializer) pObject);

// ---------------------------------------------------------------------------
// kwxAuiDeserializer — callback-driven wxAuiDeserializer
//
// Callback arguments are (pObject, arg1, arg2), result void:
//   BeforeLoad, AfterLoad:       (pObject, null, null)
//   LoadPanes:                   (pObject, kwxAuiCallbackResult*, null)
//       set the result to a wxAuiPaneLayoutInfoArray created with *_Create
//   LoadNotebookTabs:            (pObject, wxString*, kwxAuiCallbackResult*)
//       set the result to a wxAuiTabLayoutInfoArray created with *_Create
//   CreatePaneWindow:            (pObject, wxAuiPaneInfo*, kwxAuiCallbackResult*)
//       set the result to the wxWindow* to add, or leave null to skip the pane
//   HandleOrphanedPage:          (pObject, kwxAuiOrphanedPage*, null)
//       GetResult() is true unless the callback sets it to false
// ---------------------------------------------------------------------------

TClassDefExtend(kwxAuiDeserializer, wxAuiDeserializer) TClass(kwxAuiDeserializer)
    kwxAuiDeserializer_Create(TClass(wxAuiManager) manager, void* pObject);
void kwxAuiDeserializer_Delete(TSelf(kwxAuiDeserializer) pObject);
void kwxAuiDeserializer_SetOnBeforeLoad(TSelf(kwxAuiDeserializer) pObject, void* pFunction);
void kwxAuiDeserializer_SetOnLoadPanes(TSelf(kwxAuiDeserializer) pObject, void* pFunction);
void kwxAuiDeserializer_SetOnLoadNotebookTabs(TSelf(kwxAuiDeserializer) pObject, void* pFunction);
void kwxAuiDeserializer_SetOnCreatePaneWindow(TSelf(kwxAuiDeserializer) pObject, void* pFunction);
void kwxAuiDeserializer_SetOnHandleOrphanedPage(TSelf(kwxAuiDeserializer) pObject, void* pFunction);
void kwxAuiDeserializer_SetOnAfterLoad(TSelf(kwxAuiDeserializer) pObject, void* pFunction);
void kwxAuiDeserializer_BeforeLoad(TSelf(kwxAuiDeserializer) pObject);
void kwxAuiDeserializer_AfterLoad(TSelf(kwxAuiDeserializer) pObject);
