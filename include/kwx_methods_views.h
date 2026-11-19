#pragma once

/* Phase 9B: method fill for item views, notebook, toolbar and status bar.
 *
 * These blocks extend the class definitions in kwx_classes.h.  kwxgen merges
 * repeated TClassDef/TClassDefExtend blocks by class name, so the declarations
 * below are appended to the existing wxListCtrl/wxTreeCtrl/wxDataViewCtrl/...
 * method lists.
 *
 * Methods that are inherited unchanged from wxWindow/wxControl are not repeated
 * here: they remain available through the wxWindow_* and wxControl_* entry
 * points.
 */

/* ------------------------------------------------------------------------- */
/* wxListCtrl                                                                */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxListCtrl, wxControl) int wxListCtrl_GetColumnOrder(TSelf(wxListCtrl) pObject,
                                                                     int col);
int wxListCtrl_GetColumnIndexFromOrder(TSelf(wxListCtrl) pObject, int order);
TBool wxListCtrl_SetItemColumnImage(TSelf(wxListCtrl) pObject, long item, long column, int image);
TBool wxListCtrl_SetItemPtrData(TSelf(wxListCtrl) pObject, long item, uintptr_t data);
uintptr_t wxListCtrl_GetItemPtrData(TSelf(wxListCtrl) pObject, long item);
TClassOwned(wxColour) wxListCtrl_GetItemTextColour(TSelf(wxListCtrl) pObject, long item);
void wxListCtrl_SetItemTextColour(TSelf(wxListCtrl) pObject, long item, TClass(wxColour) col);
TClassOwned(wxColour) wxListCtrl_GetItemBackgroundColour(TSelf(wxListCtrl) pObject, long item);
void wxListCtrl_SetItemBackgroundColour(TSelf(wxListCtrl) pObject, long item, TClass(wxColour) col);
void wxListCtrl_SetItemFont(TSelf(wxListCtrl) pObject, long item, TClass(wxFont) font);
int wxListCtrl_AppendColumn(TSelf(wxListCtrl) pObject, TClass(wxString) heading, int format,
                            int width);
TBool wxListCtrl_IsEmpty(TSelf(wxListCtrl) pObject);
TBool wxListCtrl_InReportView(TSelf(wxListCtrl) pObject);
void wxListCtrl_EnableBellOnNoMatch(TSelf(wxListCtrl) pObject, TBool on);
void wxListCtrl_EnableAlternateRowColours(TSelf(wxListCtrl) pObject, TBool enable);
void wxListCtrl_SetAlternateRowColour(TSelf(wxListCtrl) pObject, TClass(wxColour) colour);
TClassOwned(wxColour) wxListCtrl_GetAlternateRowColour(TSelf(wxListCtrl) pObject);
void wxListCtrl_ExtendRulesAndAlternateColour(TSelf(wxListCtrl) pObject, TBool extend);
void wxListCtrl_RemoveSortIndicator(TSelf(wxListCtrl) pObject);
TBool wxListCtrl_GetUpdatedAscendingSortIndicator(TSelf(wxListCtrl) pObject, int col);

/* ------------------------------------------------------------------------- */
/* wxTreeCtrl                                                                */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxTreeCtrl, wxControl) TBool wxTreeCtrl_HasImages(TSelf(wxTreeCtrl) pObject);
int wxTreeCtrl_GetImageCount(TSelf(wxTreeCtrl) pObject);
TBool wxTreeCtrl_HasStateImages(TSelf(wxTreeCtrl) pObject);
int wxTreeCtrl_GetStateImageCount(TSelf(wxTreeCtrl) pObject);
TBool wxTreeCtrl_HasChildren(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
TBool wxTreeCtrl_IsEmpty(TSelf(wxTreeCtrl) pObject);
void wxTreeCtrl_UnselectItem(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_ToggleItemSelection(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_EnableBellOnNoMatch(TSelf(wxTreeCtrl) pObject, TBool on);

/* ------------------------------------------------------------------------- */
/* wxDataViewColumn — the portable header-column surface                      */
/* ------------------------------------------------------------------------- */

// clang-format off
// A wxDataViewColumn is created by the control that appends it and is owned by
// that control afterwards, so there is deliberately no Create/_Delete pair.
TClassDef(wxDataViewColumn) TClassOwned(wxString) wxDataViewColumn_GetTitle(
    TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetTitle(TSelf(wxDataViewColumn) pObject, TClass(wxString) title);
TClassOwned(wxBitmapBundle) wxDataViewColumn_GetBitmapBundle(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetBitmap(TSelf(wxDataViewColumn) pObject, TClass(wxBitmapBundle) bitmap);
int wxDataViewColumn_GetWidth(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetWidth(TSelf(wxDataViewColumn) pObject, int width);
int wxDataViewColumn_GetMinWidth(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetMinWidth(TSelf(wxDataViewColumn) pObject, int min_width);
int wxDataViewColumn_GetAlignment(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetAlignment(TSelf(wxDataViewColumn) pObject, int alignment);
int wxDataViewColumn_GetFlags(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetFlags(TSelf(wxDataViewColumn) pObject, int flags);
void wxDataViewColumn_SetFlag(TSelf(wxDataViewColumn) pObject, int flag);
void wxDataViewColumn_ChangeFlag(TSelf(wxDataViewColumn) pObject, int flag, TBool set);
TBool wxDataViewColumn_IsResizeable(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetResizeable(TSelf(wxDataViewColumn) pObject, TBool resizeable);
TBool wxDataViewColumn_IsSortable(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetSortable(TSelf(wxDataViewColumn) pObject, TBool sortable);
TBool wxDataViewColumn_IsReorderable(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetReorderable(TSelf(wxDataViewColumn) pObject, TBool reorderable);
TBool wxDataViewColumn_IsHidden(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetHidden(TSelf(wxDataViewColumn) pObject, TBool hidden);
TBool wxDataViewColumn_IsShown(TSelf(wxDataViewColumn) pObject);
TBool wxDataViewColumn_IsSortKey(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_SetSortOrder(TSelf(wxDataViewColumn) pObject, TBool ascending);
TBool wxDataViewColumn_IsSortOrderAscending(TSelf(wxDataViewColumn) pObject);
void wxDataViewColumn_UnsetAsSortKey(TSelf(wxDataViewColumn) pObject);
unsigned int wxDataViewColumn_GetModelColumn(TSelf(wxDataViewColumn) pObject);
TClass(wxDataViewRenderer) wxDataViewColumn_GetRenderer(TSelf(wxDataViewColumn) pObject);

/* ------------------------------------------------------------------------- */
/* wxDataViewItemAttr — the per-cell colour/font decoration                   */
/* ------------------------------------------------------------------------- */

// Filled by a model or renderer hook and read back by the control.  The colour getters
// return a borrowed pointer to a member of the attribute: it lives only as long as the
// attribute does.
TClassDef(wxDataViewItemAttr)
    TClass(wxDataViewItemAttr) wxDataViewItemAttr_Create();
    void wxDataViewItemAttr_Copy(TSelf(wxDataViewItemAttr) pObject,
                                 TClass(wxDataViewItemAttr) other);
    void wxDataViewItemAttr_Delete(TSelf(wxDataViewItemAttr) pObject);
    void wxDataViewItemAttr_SetColour(TSelf(wxDataViewItemAttr) pObject, TClass(wxColour) colour);
    void wxDataViewItemAttr_SetBackgroundColour(TSelf(wxDataViewItemAttr) pObject,
                                                TClass(wxColour) colour);
    void wxDataViewItemAttr_SetBold(TSelf(wxDataViewItemAttr) pObject, TBool set);
    void wxDataViewItemAttr_SetItalic(TSelf(wxDataViewItemAttr) pObject, TBool set);
    void wxDataViewItemAttr_SetStrikethrough(TSelf(wxDataViewItemAttr) pObject, TBool set);
    TBool wxDataViewItemAttr_HasColour(TSelf(wxDataViewItemAttr) pObject);
    TBool wxDataViewItemAttr_HasFont(TSelf(wxDataViewItemAttr) pObject);
    TBool wxDataViewItemAttr_HasBackgroundColour(TSelf(wxDataViewItemAttr) pObject);
    TBool wxDataViewItemAttr_GetBold(TSelf(wxDataViewItemAttr) pObject);
    TBool wxDataViewItemAttr_GetItalic(TSelf(wxDataViewItemAttr) pObject);
    TBool wxDataViewItemAttr_GetStrikethrough(TSelf(wxDataViewItemAttr) pObject);
    TBool wxDataViewItemAttr_IsDefault(TSelf(wxDataViewItemAttr) pObject);
    TClass(wxColour) wxDataViewItemAttr_GetColour(TSelf(wxDataViewItemAttr) pObject);
    TClass(wxColour) wxDataViewItemAttr_GetBackgroundColour(TSelf(wxDataViewItemAttr) pObject);
    TClassOwned(wxFont) wxDataViewItemAttr_GetEffectiveFont(TSelf(wxDataViewItemAttr) pObject,
                                                            TClass(wxFont) font);

/* ------------------------------------------------------------------------- */
/* wxDataViewModel — queries and change notifications                        */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxDataViewModel, wxObject) void wxDataViewModel_GetValue(
    TSelf(wxDataViewModel) pObject, TClass(wxVariant) variant, TClass(wxDataViewItem) item,
    unsigned int col);
TBool wxDataViewModel_SetValue(TSelf(wxDataViewModel) pObject, TClass(wxVariant) variant,
                               TClass(wxDataViewItem) item, unsigned int col);
TBool wxDataViewModel_ChangeValue(TSelf(wxDataViewModel) pObject, TClass(wxVariant) variant,
                                  TClass(wxDataViewItem) item, unsigned int col);
TBool wxDataViewModel_HasValue(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) item,
                               unsigned int col);
TBool wxDataViewModel_IsEnabled(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) item,
                                unsigned int col);
TBool wxDataViewModel_GetAttr(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) item,
                              unsigned int col, TClass(wxDataViewItemAttr) attr);
void wxDataViewModel_GetParent(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) item,
                               TClass(wxDataViewItem) parent);
TBool wxDataViewModel_IsContainer(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) item);
TBool wxDataViewModel_HasContainerColumns(TSelf(wxDataViewModel) pObject,
                                          TClass(wxDataViewItem) item);
unsigned int wxDataViewModel_GetChildren(TSelf(wxDataViewModel) pObject,
                                         TClass(wxDataViewItem) item,
                                         TClass(wxDataViewItemArray) children);
TBool wxDataViewModel_ItemAdded(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) parent,
                                TClass(wxDataViewItem) item);
TBool wxDataViewModel_ItemsAdded(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) parent,
                                 TClass(wxDataViewItemArray) items);
TBool wxDataViewModel_ItemDeleted(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) parent,
                                  TClass(wxDataViewItem) item);
TBool wxDataViewModel_ItemsDeleted(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) parent,
                                   TClass(wxDataViewItemArray) items);
TBool wxDataViewModel_ItemChanged(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) item);
TBool wxDataViewModel_ItemsChanged(TSelf(wxDataViewModel) pObject,
                                   TClass(wxDataViewItemArray) items);
TBool wxDataViewModel_ValueChanged(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) item,
                                   unsigned int col);
TBool wxDataViewModel_Cleared(TSelf(wxDataViewModel) pObject);
TBool wxDataViewModel_BeforeReset(TSelf(wxDataViewModel) pObject);
TBool wxDataViewModel_AfterReset(TSelf(wxDataViewModel) pObject);
int wxDataViewModel_Compare(TSelf(wxDataViewModel) pObject, TClass(wxDataViewItem) item1,
                            TClass(wxDataViewItem) item2, unsigned int column, TBool ascending);
TBool wxDataViewModel_HasDefaultCompare(TSelf(wxDataViewModel) pObject);
void wxDataViewModel_Resort(TSelf(wxDataViewModel) pObject);
// wxDataViewModel's destructor is protected and wxDataViewCtrl_AssociateModel does
// not take ownership of the model, so a model is released with DecRef(), never
// with delete.
void wxDataViewModel_IncRef(TSelf(wxDataViewModel) pObject);
void wxDataViewModel_DecRef(TSelf(wxDataViewModel) pObject);

/* ------------------------------------------------------------------------- */
/* wxDataViewListStore                                                       */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxDataViewListStore, wxDataViewModel) void wxDataViewListStore_PrependColumn(
    TSelf(wxDataViewListStore) pObject, TClass(wxString) variant_type);
void wxDataViewListStore_AppendColumn(TSelf(wxDataViewListStore) pObject,
                                      TClass(wxString) variant_type);
void wxDataViewListStore_InsertColumn(TSelf(wxDataViewListStore) pObject, unsigned int pos,
                                      TClass(wxString) variant_type);
// `values` is the wxVector<wxVariant>* handed out by wxVariantVector_Create().
void wxDataViewListStore_AppendItem(TSelf(wxDataViewListStore) pObject, void* values,
                                    uintptr_t data);
void wxDataViewListStore_PrependItem(TSelf(wxDataViewListStore) pObject, void* values,
                                     uintptr_t data);
void wxDataViewListStore_InsertItem(TSelf(wxDataViewListStore) pObject, unsigned int row,
                                    void* values, uintptr_t data);
void wxDataViewListStore_DeleteItem(TSelf(wxDataViewListStore) pObject, unsigned int pos);
void wxDataViewListStore_DeleteAllItems(TSelf(wxDataViewListStore) pObject);
void wxDataViewListStore_ClearColumns(TSelf(wxDataViewListStore) pObject);
unsigned int wxDataViewListStore_GetItemCount(TSelf(wxDataViewListStore) pObject);
void wxDataViewListStore_SetItemData(TSelf(wxDataViewListStore) pObject,
                                     TClass(wxDataViewItem) item, uintptr_t data);
uintptr_t wxDataViewListStore_GetItemData(TSelf(wxDataViewListStore) pObject,
                                          TClass(wxDataViewItem) item);
void wxDataViewListStore_GetValueByRow(TSelf(wxDataViewListStore) pObject,
                                       TClass(wxVariant) value, unsigned int row,
                                       unsigned int col);
TBool wxDataViewListStore_SetValueByRow(TSelf(wxDataViewListStore) pObject,
                                        TClass(wxVariant) value, unsigned int row,
                                        unsigned int col);
// The factory constructs the scripted subclass the hooks attach to; with no hook
// installed it behaves exactly like a plain wxDataViewListStore.  Like every
// wxDataViewModel it is reference counted: release it with wxDataViewModel_DecRef.
TClass(wxDataViewListStore) wxDataViewListStore_Create(void* pObject);
TBool wxDataViewListStore_IsEnabledByRow(TSelf(wxDataViewListStore) pObject, unsigned int row,
                                         unsigned int col);
TBool wxDataViewListStore_GetAttrByRow(TSelf(wxDataViewListStore) pObject, unsigned int row,
                                       unsigned int col, TClass(wxDataViewItemAttr) attr);

/* ------------------------------------------------------------------------- */
/* wxDataViewCtrl                                                            */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxDataViewCtrl, wxControl) TBool
    wxDataViewCtrl_SetHeaderAttr(TSelf(wxDataViewCtrl) pObject, TClass(wxItemAttr) attr);
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
TBool wxDataViewCtrl_Enable(TSelf(wxDataViewCtrl) pObject, TBool enable);
TBool wxDataViewCtrl_EnableDragSource(TSelf(wxDataViewCtrl) pObject, TClass(wxDataFormat) format);
// Only the single-format overload is wrapped: there is no wxVector<wxDataFormat> handle.
TBool wxDataViewCtrl_EnableDropTarget(TSelf(wxDataViewCtrl) pObject, TClass(wxDataFormat) format);
TBool wxDataViewCtrl_SetBackgroundColour(TSelf(wxDataViewCtrl) pObject, TClass(wxColour) colour);
void wxDataViewCtrl_SetFocus(TSelf(wxDataViewCtrl) pObject);
int wxDataViewCtrl_SetForegroundColour(TSelf(wxDataViewCtrl) pObject, TClass(wxColour) colour);
// GetSortingColumns() returns a wxVector<wxDataViewColumn*>, which cannot cross the
// boundary, so it is exposed as a count plus an index.  The column is owned by the
// control (borrowed); an out-of-range pos returns null.
int wxDataViewCtrl_GetSortingColumnCount(TSelf(wxDataViewCtrl) pObject);
TClass(wxDataViewColumn) wxDataViewCtrl_GetSortingColumnAt(TSelf(wxDataViewCtrl) pObject,
                                                           int pos);

// GenericGetHeader() exists only on the generic implementation (the one this build uses);
// the definition is guarded and answers null when wxWidgets was built with a native
// control.  The header is owned by the control (borrowed).  Header height is changed
// through the inherited wxWindow::SetMinSize.
TClass(wxHeaderCtrl) wxDataViewCtrl_GenericGetHeader(TSelf(wxDataViewCtrl) pObject);

// HitTest() reports the column through a wxDataViewColumn*& that every binding has to back
// with a raw pointer slot and then re-wrap.  This companion writes the item into the
// caller's holder exactly like HitTest() and returns the hit column's position in the
// control (-1 when the point is outside every item, or when no column was hit), so the
// column itself is reached with the already wrapped wxDataViewCtrl_GetColumn(pos).
// The item holder must be a real wxDataViewItem (wxDataViewItem_Create(NULL) for the empty
// one); a null holder is dereferenced.
int wxDataViewCtrl_HitTestColumnPosition(TSelf(wxDataViewCtrl) pObject, int x, int y,
                                         TClass(wxDataViewItem) item);

/* ------------------------------------------------------------------------- */
/* wxDataViewListCtrl                                                        */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxDataViewListCtrl, wxDataViewCtrl) TBool
    wxDataViewListCtrl_AppendColumn(TSelf(wxDataViewListCtrl) pObject,
                                    TClass(wxDataViewColumn) column, TClass(wxString) variantType);
TBool wxDataViewListCtrl_PrependColumn(TSelf(wxDataViewListCtrl) pObject,
                                       TClass(wxDataViewColumn) column,
                                       TClass(wxString) variantType);
TBool wxDataViewListCtrl_InsertColumn(TSelf(wxDataViewListCtrl) pObject, unsigned int pos,
                                      TClass(wxDataViewColumn) column,
                                      TClass(wxString) variantType);

/* ------------------------------------------------------------------------- */
/* wxDataViewTreeStore                                                       */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxDataViewTreeStore, wxDataViewModel) TClass(wxDataViewTreeStore)
    wxDataViewTreeStore_Create();
// wxDataViewTreeStore is reference counted (it derives from wxDataViewModel, whose
// destructor is protected): Delete() drops the reference, it never calls delete.
void wxDataViewTreeStore_Delete(TSelf(wxDataViewTreeStore) pObject);
void wxDataViewTreeStore_AppendContainer(TSelf(wxDataViewTreeStore) pObject,
                                         TClass(wxDataViewItem) parent, TClass(wxString) text,
                                         TClass(wxBitmapBundle) icon,
                                         TClass(wxBitmapBundle) expanded,
                                         TClass(wxClientData) data,
                                         TClass(wxDataViewItem) result);
void wxDataViewTreeStore_AppendItem(TSelf(wxDataViewTreeStore) pObject,
                                    TClass(wxDataViewItem) parent, TClass(wxString) text,
                                    TClass(wxBitmapBundle) icon, TClass(wxClientData) data,
                                    TClass(wxDataViewItem) result);
void wxDataViewTreeStore_PrependContainer(TSelf(wxDataViewTreeStore) pObject,
                                          TClass(wxDataViewItem) parent, TClass(wxString) text,
                                          TClass(wxBitmapBundle) icon,
                                          TClass(wxBitmapBundle) expanded,
                                          TClass(wxClientData) data,
                                          TClass(wxDataViewItem) result);
void wxDataViewTreeStore_PrependItem(TSelf(wxDataViewTreeStore) pObject,
                                     TClass(wxDataViewItem) parent, TClass(wxString) text,
                                     TClass(wxBitmapBundle) icon, TClass(wxClientData) data,
                                     TClass(wxDataViewItem) result);
void wxDataViewTreeStore_InsertContainer(TSelf(wxDataViewTreeStore) pObject,
                                         TClass(wxDataViewItem) parent,
                                         TClass(wxDataViewItem) previous, TClass(wxString) text,
                                         TClass(wxBitmapBundle) icon,
                                         TClass(wxBitmapBundle) expanded,
                                         TClass(wxClientData) data,
                                         TClass(wxDataViewItem) result);
void wxDataViewTreeStore_InsertItem(TSelf(wxDataViewTreeStore) pObject,
                                    TClass(wxDataViewItem) parent,
                                    TClass(wxDataViewItem) previous, TClass(wxString) text,
                                    TClass(wxBitmapBundle) icon, TClass(wxClientData) data,
                                    TClass(wxDataViewItem) result);
void wxDataViewTreeStore_GetNthChild(TSelf(wxDataViewTreeStore) pObject,
                                     TClass(wxDataViewItem) parent, unsigned int pos,
                                     TClass(wxDataViewItem) result);
int wxDataViewTreeStore_GetChildCount(TSelf(wxDataViewTreeStore) pObject,
                                      TClass(wxDataViewItem) parent);
void wxDataViewTreeStore_SetItemText(TSelf(wxDataViewTreeStore) pObject,
                                     TClass(wxDataViewItem) item, TClass(wxString) text);
TClassOwned(wxString) wxDataViewTreeStore_GetItemText(TSelf(wxDataViewTreeStore) pObject,
                                                      TClass(wxDataViewItem) item);
void wxDataViewTreeStore_SetItemIcon(TSelf(wxDataViewTreeStore) pObject,
                                     TClass(wxDataViewItem) item, TClass(wxBitmapBundle) icon);
TClassOwned(wxIcon) wxDataViewTreeStore_GetItemIcon(TSelf(wxDataViewTreeStore) pObject,
                                               TClass(wxDataViewItem) item);
void wxDataViewTreeStore_SetItemExpandedIcon(TSelf(wxDataViewTreeStore) pObject,
                                             TClass(wxDataViewItem) item,
                                             TClass(wxBitmapBundle) icon);
TClassOwned(wxIcon) wxDataViewTreeStore_GetItemExpandedIcon(TSelf(wxDataViewTreeStore) pObject,
                                                       TClass(wxDataViewItem) item);
void wxDataViewTreeStore_SetItemData(TSelf(wxDataViewTreeStore) pObject,
                                     TClass(wxDataViewItem) item, TClass(wxClientData) data);
TClass(wxClientData) wxDataViewTreeStore_GetItemData(TSelf(wxDataViewTreeStore) pObject,
                                                     TClass(wxDataViewItem) item);
void wxDataViewTreeStore_DeleteItem(TSelf(wxDataViewTreeStore) pObject,
                                    TClass(wxDataViewItem) item);
void wxDataViewTreeStore_DeleteChildren(TSelf(wxDataViewTreeStore) pObject,
                                        TClass(wxDataViewItem) item);
void wxDataViewTreeStore_DeleteAllItems(TSelf(wxDataViewTreeStore) pObject);

/* ------------------------------------------------------------------------- */
/* wxDataViewTreeCtrl                                                        */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxDataViewTreeCtrl, wxDataViewCtrl) TClass(wxDataViewTreeCtrl)
    wxDataViewTreeCtrl_Create(TClass(wxWindow) parent, int id, int x, int y, int width, int height,
                              int style);
TClass(wxDataViewTreeStore) wxDataViewTreeCtrl_GetStore(TSelf(wxDataViewTreeCtrl) pObject);
void wxDataViewTreeCtrl_AppendContainer(TSelf(wxDataViewTreeCtrl) pObject,
                                        TClass(wxDataViewItem) parent, TClass(wxString) text,
                                        int icon, int expanded, TClass(wxClientData) data,
                                        TClass(wxDataViewItem) result);
void wxDataViewTreeCtrl_AppendItem(TSelf(wxDataViewTreeCtrl) pObject,
                                   TClass(wxDataViewItem) parent, TClass(wxString) text,
                                   int icon, TClass(wxClientData) data,
                                   TClass(wxDataViewItem) result);
void wxDataViewTreeCtrl_PrependContainer(TSelf(wxDataViewTreeCtrl) pObject,
                                         TClass(wxDataViewItem) parent, TClass(wxString) text,
                                         int icon, int expanded, TClass(wxClientData) data,
                                         TClass(wxDataViewItem) result);
void wxDataViewTreeCtrl_PrependItem(TSelf(wxDataViewTreeCtrl) pObject,
                                    TClass(wxDataViewItem) parent, TClass(wxString) text,
                                    int icon, TClass(wxClientData) data,
                                    TClass(wxDataViewItem) result);
void wxDataViewTreeCtrl_InsertContainer(TSelf(wxDataViewTreeCtrl) pObject,
                                        TClass(wxDataViewItem) parent,
                                        TClass(wxDataViewItem) previous, TClass(wxString) text,
                                        int icon, int expanded, TClass(wxClientData) data,
                                        TClass(wxDataViewItem) result);
void wxDataViewTreeCtrl_InsertItem(TSelf(wxDataViewTreeCtrl) pObject,
                                   TClass(wxDataViewItem) parent,
                                   TClass(wxDataViewItem) previous, TClass(wxString) text,
                                   int icon, TClass(wxClientData) data,
                                   TClass(wxDataViewItem) result);
void wxDataViewTreeCtrl_DeleteItem(TSelf(wxDataViewTreeCtrl) pObject,
                                   TClass(wxDataViewItem) item);
void wxDataViewTreeCtrl_DeleteChildren(TSelf(wxDataViewTreeCtrl) pObject,
                                       TClass(wxDataViewItem) item);
void wxDataViewTreeCtrl_DeleteAllItems(TSelf(wxDataViewTreeCtrl) pObject);
int wxDataViewTreeCtrl_GetChildCount(TSelf(wxDataViewTreeCtrl) pObject,
                                     TClass(wxDataViewItem) parent);
TClassOwned(wxString) wxDataViewTreeCtrl_GetItemText(TSelf(wxDataViewTreeCtrl) pObject,
                                                     TClass(wxDataViewItem) item);
void wxDataViewTreeCtrl_SetItemText(TSelf(wxDataViewTreeCtrl) pObject,
                                    TClass(wxDataViewItem) item, TClass(wxString) text);
TClassOwned(wxIcon) wxDataViewTreeCtrl_GetItemIcon(TSelf(wxDataViewTreeCtrl) pObject,
                                              TClass(wxDataViewItem) item);
void wxDataViewTreeCtrl_SetItemIcon(TSelf(wxDataViewTreeCtrl) pObject,
                                    TClass(wxDataViewItem) item, TClass(wxBitmapBundle) icon);
TClassOwned(wxIcon) wxDataViewTreeCtrl_GetItemExpandedIcon(TSelf(wxDataViewTreeCtrl) pObject,
                                                      TClass(wxDataViewItem) item);
void wxDataViewTreeCtrl_SetItemExpandedIcon(TSelf(wxDataViewTreeCtrl) pObject,
                                            TClass(wxDataViewItem) item,
                                            TClass(wxBitmapBundle) icon);
TClass(wxClientData) wxDataViewTreeCtrl_GetItemData(TSelf(wxDataViewTreeCtrl) pObject,
                                                    TClass(wxDataViewItem) item);
void wxDataViewTreeCtrl_SetItemData(TSelf(wxDataViewTreeCtrl) pObject,
                                    TClass(wxDataViewItem) item, TClass(wxClientData) data);
TBool wxDataViewTreeCtrl_IsContainer(TSelf(wxDataViewTreeCtrl) pObject,
                                     TClass(wxDataViewItem) item);
void wxDataViewTreeCtrl_GetItemParent(TSelf(wxDataViewTreeCtrl) pObject,
                                      TClass(wxDataViewItem) item,
                                      TClass(wxDataViewItem) result);
void wxDataViewTreeCtrl_GetNthChild(TSelf(wxDataViewTreeCtrl) pObject,
                                    TClass(wxDataViewItem) parent, unsigned int pos,
                                    TClass(wxDataViewItem) result);
void wxDataViewTreeCtrl_Expand(TSelf(wxDataViewTreeCtrl) pObject, TClass(wxDataViewItem) item);
void wxDataViewTreeCtrl_Collapse(TSelf(wxDataViewTreeCtrl) pObject, TClass(wxDataViewItem) item);
TBool wxDataViewTreeCtrl_IsExpanded(TSelf(wxDataViewTreeCtrl) pObject,
                                    TClass(wxDataViewItem) item);
void wxDataViewTreeCtrl_SetImageList(TSelf(wxDataViewTreeCtrl) pObject, TClass(wxImageList) list);
TClass(wxImageList) wxDataViewTreeCtrl_GetImageList(TSelf(wxDataViewTreeCtrl) pObject);
void wxDataViewTreeCtrl_AssignImageList(TSelf(wxDataViewTreeCtrl) pObject,
                                        TClass(wxImageList) list);
// wxDataViewTreeCtrl::Images is wxVector<wxBitmapBundle>, i.e. the already wrapped
// wxBitmapBundleArray.  This is the C++ SetImages(images); building a wxImageList and
// calling SetImageList instead loses the bundle's DPI variants.
void wxDataViewTreeCtrl_SetImages(TSelf(wxDataViewTreeCtrl) pObject,
                                  TClass(wxBitmapBundleArray) images);

/* ------------------------------------------------------------------------- */
/* wxDataViewEvent                                                           */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxDataViewEvent, wxNotifyEvent) void wxDataViewEvent_GetItem(
    TSelf(wxDataViewEvent) pObject, TClass(wxDataViewItem) item);
int wxDataViewEvent_GetColumn(TSelf(wxDataViewEvent) pObject);
TClass(wxDataViewColumn) wxDataViewEvent_GetDataViewColumn(TSelf(wxDataViewEvent) pObject);
TClassOwned(wxVariant) wxDataViewEvent_GetValue(TSelf(wxDataViewEvent) pObject);
void wxDataViewEvent_SetValue(TSelf(wxDataViewEvent) pObject, TClass(wxVariant) value);
TClass(wxDataObject) wxDataViewEvent_GetDataObject(TSelf(wxDataViewEvent) pObject);
void wxDataViewEvent_SetDataObject(TSelf(wxDataViewEvent) pObject, TClass(wxDataObject) obj);
TClassOwned(wxDataFormat) wxDataViewEvent_GetDataFormat(TSelf(wxDataViewEvent) pObject);
void wxDataViewEvent_SetDataFormat(TSelf(wxDataViewEvent) pObject, TClass(wxDataFormat) format);
size_t wxDataViewEvent_GetDataSize(TSelf(wxDataViewEvent) pObject);
void wxDataViewEvent_SetDataSize(TSelf(wxDataViewEvent) pObject, size_t size);
void* wxDataViewEvent_GetDataBuffer(TSelf(wxDataViewEvent) pObject);
void wxDataViewEvent_SetDataBuffer(TSelf(wxDataViewEvent) pObject, void* buffer);
int wxDataViewEvent_GetDropEffect(TSelf(wxDataViewEvent) pObject);
void wxDataViewEvent_SetDropEffect(TSelf(wxDataViewEvent) pObject, int effect);
void wxDataViewEvent_SetDragFlags(TSelf(wxDataViewEvent) pObject, int flags);
int wxDataViewEvent_GetDragFlags(TSelf(wxDataViewEvent) pObject);
void wxDataViewEvent_SetProposedDropIndex(TSelf(wxDataViewEvent) pObject, int index);
int wxDataViewEvent_GetProposedDropIndex(TSelf(wxDataViewEvent) pObject);
void wxDataViewEvent_GetPosition(TSelf(wxDataViewEvent) pObject, TPointOut(x, y));
void wxDataViewEvent_SetPosition(TSelf(wxDataViewEvent) pObject, TPoint(x, y));
TBool wxDataViewEvent_IsEditCancelled(TSelf(wxDataViewEvent) pObject);
void wxDataViewEvent_SetEditCancelled(TSelf(wxDataViewEvent) pObject);
TClass(wxDataViewModel) wxDataViewEvent_GetModel(TSelf(wxDataViewEvent) pObject);
// clang-format on

/* ------------------------------------------------------------------------- */
/* wxTreeListCtrl                                                            */
/* ------------------------------------------------------------------------- */

/* Overload that sets the label of column 0; the explicit column overload is
 * already declared in kwx_classes.h. */
TClassDefExtend(wxTreeListCtrl,
                wxWindow) void wxTreeListCtrl_SetItemTextSimple(TSelf(wxTreeListCtrl) pObject,
                                                                TClass(wxTreeListItem) item,
                                                                TClass(wxString) text);
TClass(wxClientData)
    wxTreeListCtrl_GetItemData(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);
void wxTreeListCtrl_SetItemData(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item,
                                TClass(wxClientData) data);

/* ------------------------------------------------------------------------- */
/* wxNotebook                                                                */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxNotebook, wxBookCtrlBase) TClass(wxWindow)
    wxNotebook_GetCurrentPage(TSelf(wxNotebook) pObject);
TClassOwned(wxSize) wxNotebook_GetControllerSize(TSelf(wxNotebook) pObject);
TClassOwned(wxSize) wxNotebook_CalcSizeFromPage(TSelf(wxNotebook) pObject, TSize(width, height));
unsigned int wxNotebook_GetInternalBorder(TSelf(wxNotebook) pObject);
void wxNotebook_SetInternalBorder(TSelf(wxNotebook) pObject, unsigned int border);
void wxNotebook_SetControlMargin(TSelf(wxNotebook) pObject, int margin);
int wxNotebook_GetControlMargin(TSelf(wxNotebook) pObject);
TBool wxNotebook_IsVertical(TSelf(wxNotebook) pObject);
void wxNotebook_SetFitToCurrentPage(TSelf(wxNotebook) pObject, TBool fit);
TBool wxNotebook_GetFitToCurrentPage(TSelf(wxNotebook) pObject);
int wxNotebook_ChangeSelection(TSelf(wxNotebook) pObject, int nPage);
int wxNotebook_FindPage(TSelf(wxNotebook) pObject, TClass(wxWindow) page);
void wxNotebook_SetTabSize(TSelf(wxNotebook) pObject, TSize(width, height));
TClassOwned(wxRect) wxNotebook_GetTabRect(TSelf(wxNotebook) pObject, int page);
int wxNotebook_GetTabOrientation(TSelf(wxNotebook) pObject);
TClassOwned(wxColour) wxNotebook_GetThemeBackgroundColour(TSelf(wxNotebook) pObject);
TBool wxNotebook_SendPageChangingEvent(TSelf(wxNotebook) pObject, int nPage);
void wxNotebook_SendPageChangedEvent(TSelf(wxNotebook) pObject, int nPageOld, int nPageNew);

/* ------------------------------------------------------------------------- */
/* wxToolBar                                                                 */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxToolBar, wxToolBarBase) TClassOwned(wxSize)
    wxToolBar_GetToolMargins(TSelf(wxToolBar) pObject);
void wxToolBar_SetMaxRowsCols(TSelf(wxToolBar) pObject, int rows, int cols);
int wxToolBar_GetMaxRows(TSelf(wxToolBar) pObject);
int wxToolBar_GetMaxCols(TSelf(wxToolBar) pObject);
int wxToolBar_GetDirection(TSelf(wxToolBar) pObject);
void* wxToolBar_GetToolByPos(TSelf(wxToolBar) pObject, int pos);
void wxToolBar_SetRows(TSelf(wxToolBar) pObject, int nRows);

/* ------------------------------------------------------------------------- */
/* wxStatusBar                                                               */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxStatusBar, wxWindow) TClassOwned(wxSize)
    wxStatusBar_GetBorders(TSelf(wxStatusBar) pObject);
TBool wxStatusBar_AddFieldControl(TSelf(wxStatusBar) pObject, int n, TClass(wxWindow) win);

/* ------------------------------------------------------------------------- */
/* wxDataViewIconText / wxDataViewCheckIconText (variant value classes)      */
/* ------------------------------------------------------------------------- */

// The value a wxVariant built by wxVariant_CreateFromDataViewIconText /
// ...FromDataViewCheckIconText holds.  Read it back with
// wxVariant_GetDataViewIconText / wxVariant_GetDataViewCheckIconText.  A null icon is the
// empty bundle.
TClassDefExtend(wxDataViewIconText, wxObject) TClass(wxDataViewIconText)
    wxDataViewIconText_Create(TClass(wxString) text, TClass(wxBitmapBundle) icon);
TClass(wxDataViewIconText) wxDataViewIconText_CreateDefault();
void wxDataViewIconText_Copy(TSelf(wxDataViewIconText) pObject, TClass(wxDataViewIconText) other);
void wxDataViewIconText_Delete(TSelf(wxDataViewIconText) pObject);
void wxDataViewIconText_SetText(TSelf(wxDataViewIconText) pObject, TClass(wxString) text);
TClassOwned(wxString) wxDataViewIconText_GetText(TSelf(wxDataViewIconText) pObject);
void wxDataViewIconText_SetBitmapBundle(TSelf(wxDataViewIconText) pObject,
                                        TClass(wxBitmapBundle) icon);
// Borrowed reference to the member bundle: never free it, and do not keep it past the
// wxDataViewIconText it came from.
TClass(wxBitmapBundle) wxDataViewIconText_GetBitmapBundle(TSelf(wxDataViewIconText) pObject);
void wxDataViewIconText_SetIcon(TSelf(wxDataViewIconText) pObject, TClass(wxIcon) icon);
TClassOwned(wxIcon) wxDataViewIconText_GetIcon(TSelf(wxDataViewIconText) pObject);

// checkedState is the integer the constant module exports for wxCheckBoxState:
// 0 = wxCHK_UNCHECKED, 1 = wxCHK_CHECKED, 2 = wxCHK_UNDETERMINED.
TClassDefExtend(wxDataViewCheckIconText, wxDataViewIconText) TClass(wxDataViewCheckIconText)
    wxDataViewCheckIconText_Create(TClass(wxString) text, TClass(wxBitmapBundle) icon,
                                   int checkedState);
TClass(wxDataViewCheckIconText) wxDataViewCheckIconText_CreateDefault();
void wxDataViewCheckIconText_Copy(TSelf(wxDataViewCheckIconText) pObject,
                                  TClass(wxDataViewCheckIconText) other);
void wxDataViewCheckIconText_Delete(TSelf(wxDataViewCheckIconText) pObject);
void wxDataViewCheckIconText_SetCheckedState(TSelf(wxDataViewCheckIconText) pObject, int state);
int wxDataViewCheckIconText_GetCheckedState(TSelf(wxDataViewCheckIconText) pObject);
