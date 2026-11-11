#pragma once

// wxComboCtrl / wxComboPopup additions (kwxFFI issue #73).
//
// kwxgen merges repeated TClassDef/TClassDefExtend blocks by class name, so the
// blocks below extend the declarations in kwx_classes_sync.h instead of
// duplicating them.
//
// The kwx* classes are implemented in kwx_helper_combo.h; this header only
// carries their declaration model.

// ---------------------------------------------------------------------------
// wxComboPopup: the mix-in every popup control implements.
//
// Every method takes TClass(wxComboPopup) as its receiver (not TSelf) so that
// kwxgen's DetectMixinClasses() classifies the block as a mix-in and
// BuildMixinMap() attaches these methods to the concrete popup consumers.
// Create() is pure virtual, which is why the concrete helpers below exist.
// ---------------------------------------------------------------------------

TClassDef(wxComboPopup) void wxComboPopup_Init(TClass(wxComboPopup) pObject);
void wxComboPopup_DestroyPopup(TClass(wxComboPopup) pObject);
TClass(wxWindow) wxComboPopup_GetControl(TClass(wxComboPopup) pObject);
void wxComboPopup_OnPopup(TClass(wxComboPopup) pObject);
void wxComboPopup_OnDismiss(TClass(wxComboPopup) pObject);
void wxComboPopup_SetStringValue(TClass(wxComboPopup) pObject, TClass(wxString) value);
TClass(wxString) wxComboPopup_GetStringValue(TClass(wxComboPopup) pObject);
TBool wxComboPopup_FindItem(TClass(wxComboPopup) pObject, TClass(wxString) item,
                            TClass(wxString) trueItem);
void wxComboPopup_PaintComboControl(TClass(wxComboPopup) pObject, TClass(wxDC) dc,
                                    TRect(x, y, width, height));
void wxComboPopup_OnComboKeyEvent(TClass(wxComboPopup) pObject, TClass(wxKeyEvent) event);
void wxComboPopup_OnComboCharEvent(TClass(wxComboPopup) pObject, TClass(wxKeyEvent) event);
void wxComboPopup_OnComboDoubleClick(TClass(wxComboPopup) pObject);
void wxComboPopup_GetAdjustedSize(TClass(wxComboPopup) pObject, int minWidth, int prefHeight,
                                  int maxHeight, TSizeOut(width, height));
TBool wxComboPopup_LazyCreate(TClass(wxComboPopup) pObject);
void wxComboPopup_Dismiss(TClass(wxComboPopup) pObject);
TBool wxComboPopup_IsCreated(TClass(wxComboPopup) pObject);
TClass(wxComboCtrl) wxComboPopup_GetComboCtrl(TClass(wxComboPopup) pObject);

// ---------------------------------------------------------------------------
// wxGenericComboCtrl: the generic implementation exercised by the combo sample.
// On MSW wxGenericComboCtrl is an alias for the native wxComboCtrl; on the other
// ports it is the generic wxComboCtrlBase implementation. wxComboCtrl is used as
// the declaration-model parent so the bindings expose the wxComboCtrl methods.
// ---------------------------------------------------------------------------

TClassDefExtend(wxGenericComboCtrl, wxComboCtrl)
    TClass(wxComboCtrl) wxGenericComboCtrl_Create(TClass(wxWindow) parent, int id,
                                                  TClass(wxString) value, int x, int y,
                                                  int width, int height, long style);

// ---------------------------------------------------------------------------
// kwxComboCtrl: wxComboCtrl with callback overrides (see kwx_helper_combo.h).
// ---------------------------------------------------------------------------

TClassDefExtend(kwxComboCtrl, wxComboCtrl)
    TClass(kwxComboCtrl) kwxComboCtrl_CreateDefault(void* pObject);
TClass(kwxComboCtrl) kwxComboCtrl_CreateWith(void* pObject, TClass(wxWindow) parent, int id,
                                             TClass(wxString) value, TRect(x, y, width, height),
                                             long style);
TBool kwxComboCtrl_Create(TSelf(kwxComboCtrl) pObject, TClass(wxWindow) parent, int id,
                          TClass(wxString) value, TRect(x, y, width, height), long style);
void kwxComboCtrl_SetOnButtonClick(TSelf(kwxComboCtrl) pObject, void* pFunction);
void kwxComboCtrl_SetOnAnimateShow(TSelf(kwxComboCtrl) pObject, void* pFunction);
void kwxComboCtrl_SetOnDoSetPopupControl(TSelf(kwxComboCtrl) pObject, void* pFunction);
void kwxComboCtrl_SetOnDoShowPopup(TSelf(kwxComboCtrl) pObject, void* pFunction);

// ---------------------------------------------------------------------------
// kwxOwnerDrawnComboBox: wxOwnerDrawnComboBox with callback overrides.
// ---------------------------------------------------------------------------

TClassDefExtend(kwxOwnerDrawnComboBox, wxOwnerDrawnComboBox)
    TClass(kwxOwnerDrawnComboBox) kwxOwnerDrawnComboBox_CreateDefault(void* pObject);
TClass(kwxOwnerDrawnComboBox) kwxOwnerDrawnComboBox_CreateWith(
    void* pObject, TClass(wxWindow) parent, int id, TClass(wxString) value,
    TRect(x, y, width, height), long style);
TBool kwxOwnerDrawnComboBox_Create(TSelf(kwxOwnerDrawnComboBox) pObject, TClass(wxWindow) parent,
                                   int id, TClass(wxString) value, TRect(x, y, width, height),
                                   long style);
void kwxOwnerDrawnComboBox_SetOnDrawItem(TSelf(kwxOwnerDrawnComboBox) pObject, void* pFunction);
void kwxOwnerDrawnComboBox_SetOnDrawBackground(TSelf(kwxOwnerDrawnComboBox) pObject,
                                               void* pFunction);
void kwxOwnerDrawnComboBox_SetOnMeasureItem(TSelf(kwxOwnerDrawnComboBox) pObject, void* pFunction);
void kwxOwnerDrawnComboBox_SetOnMeasureItemWidth(TSelf(kwxOwnerDrawnComboBox) pObject,
                                                 void* pFunction);

// ---------------------------------------------------------------------------
// Concrete wxComboPopup implementations (see kwx_helper_combo.h).
//
// Each helper owns its control: the object itself is the wxComboPopup and
// GetControl() returns the wrapped wxListView / wxTreeCtrl. The handle can
// therefore be passed straight to wxComboCtrl_SetPopupControl(), and the item
// helpers below are the only way to populate the popup.
// ---------------------------------------------------------------------------

TClassDef(kwxListViewComboPopup)
    TClass(kwxListViewComboPopup) kwxListViewComboPopup_Create();
void kwxListViewComboPopup_AddString(TSelf(kwxListViewComboPopup) pObject, TClass(wxString) item);
int kwxListViewComboPopup_GetItemCount(TSelf(kwxListViewComboPopup) pObject);

TClassDef(kwxTreeCtrlComboPopup)
    TClass(kwxTreeCtrlComboPopup) kwxTreeCtrlComboPopup_Create();
void kwxTreeCtrlComboPopup_AddRoot(TSelf(kwxTreeCtrlComboPopup) pObject, TClass(wxString) text,
                                   TClassRef(wxTreeItemId) result);
void kwxTreeCtrlComboPopup_AppendItem(TSelf(kwxTreeCtrlComboPopup) pObject,
                                      TClass(wxTreeItemId) parent, TClass(wxString) text,
                                      TClassRef(wxTreeItemId) result);
