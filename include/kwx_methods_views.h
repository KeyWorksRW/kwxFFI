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
TClass(wxColour) wxListCtrl_GetItemTextColour(TSelf(wxListCtrl) pObject, long item);
void wxListCtrl_SetItemTextColour(TSelf(wxListCtrl) pObject, long item, TClass(wxColour) col);
TClass(wxColour) wxListCtrl_GetItemBackgroundColour(TSelf(wxListCtrl) pObject, long item);
void wxListCtrl_SetItemBackgroundColour(TSelf(wxListCtrl) pObject, long item, TClass(wxColour) col);
void wxListCtrl_SetItemFont(TSelf(wxListCtrl) pObject, long item, TClass(wxFont) font);
int wxListCtrl_AppendColumn(TSelf(wxListCtrl) pObject, TClass(wxString) heading, int format,
                            int width);
TBool wxListCtrl_IsEmpty(TSelf(wxListCtrl) pObject);
TBool wxListCtrl_InReportView(TSelf(wxListCtrl) pObject);
void wxListCtrl_EnableBellOnNoMatch(TSelf(wxListCtrl) pObject, TBool on);
void wxListCtrl_EnableAlternateRowColours(TSelf(wxListCtrl) pObject, TBool enable);
void wxListCtrl_SetAlternateRowColour(TSelf(wxListCtrl) pObject, TClass(wxColour) colour);
TClass(wxColour) wxListCtrl_GetAlternateRowColour(TSelf(wxListCtrl) pObject);
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
/* wxDataViewCtrl                                                            */
/* ------------------------------------------------------------------------- */

TClassDef(wxDataViewCtrl) TBool
    wxDataViewCtrl_SetHeaderAttr(TSelf(wxDataViewCtrl) pObject, TClass(wxItemAttr) attr);

/* ------------------------------------------------------------------------- */
/* wxDataViewListCtrl                                                        */
/* ------------------------------------------------------------------------- */

TClassDef(wxDataViewListCtrl) TBool
    wxDataViewListCtrl_AppendColumn(TSelf(wxDataViewListCtrl) pObject,
                                    TClass(wxDataViewColumn) column, TClass(wxString) variantType);
TBool wxDataViewListCtrl_PrependColumn(TSelf(wxDataViewListCtrl) pObject,
                                       TClass(wxDataViewColumn) column,
                                       TClass(wxString) variantType);
TBool wxDataViewListCtrl_InsertColumn(TSelf(wxDataViewListCtrl) pObject, unsigned int pos,
                                      TClass(wxDataViewColumn) column,
                                      TClass(wxString) variantType);

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

TClassDefExtend(wxNotebook, wxControl) TClass(wxWindow)
    wxNotebook_GetCurrentPage(TSelf(wxNotebook) pObject);
TClass(wxSize) wxNotebook_GetControllerSize(TSelf(wxNotebook) pObject);
TClass(wxSize) wxNotebook_CalcSizeFromPage(TSelf(wxNotebook) pObject, TSize(width, height));
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
TClass(wxRect) wxNotebook_GetTabRect(TSelf(wxNotebook) pObject, int page);
int wxNotebook_GetTabOrientation(TSelf(wxNotebook) pObject);
TClass(wxColour) wxNotebook_GetThemeBackgroundColour(TSelf(wxNotebook) pObject);
TBool wxNotebook_SendPageChangingEvent(TSelf(wxNotebook) pObject, int nPage);
void wxNotebook_SendPageChangedEvent(TSelf(wxNotebook) pObject, int nPageOld, int nPageNew);

/* ------------------------------------------------------------------------- */
/* wxToolBar                                                                 */
/* ------------------------------------------------------------------------- */

TClassDefExtend(wxToolBar, wxToolBarBase) TClass(wxSize)
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

TClassDefExtend(wxStatusBar, wxWindow) TClass(wxSize)
    wxStatusBar_GetBorders(TSelf(wxStatusBar) pObject);
TBool wxStatusBar_AddFieldControl(TSelf(wxStatusBar) pObject, int n, TClass(wxWindow) win);
