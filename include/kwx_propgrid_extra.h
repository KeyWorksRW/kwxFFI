#pragma once

// PropertyGrid additions that are absent from include/kwx_classes.h.
//
// Declarations for wxPropertyGrid and wxPropertyGridPage extend the blocks in
// kwx_classes.h; kwxgen merges repeated TClassDef/TClassDefExtend blocks by
// class name.

// ---------------------------------------------------------------------------
// wxPGEditor
// ---------------------------------------------------------------------------

TClassDefExtend(wxPGEditor, wxObject) TClass(wxString)
    wxPGEditor_GetName(TSelf(wxPGEditor) pObject);
TBool wxPGEditor_CanContainCustomImage(TSelf(wxPGEditor) pObject);

// ---------------------------------------------------------------------------
// wxPGMultiButton
// ---------------------------------------------------------------------------

TClassDefExtend(wxPGMultiButton, wxWindow) TClass(wxPGMultiButton)
    wxPGMultiButton_Create(TClass(wxPropertyGrid) propgrid, TSize(width, height));
void wxPGMultiButton_Delete(TSelf(wxPGMultiButton) pObject);
TClass(wxWindow) wxPGMultiButton_GetButton(TSelf(wxPGMultiButton) pObject, unsigned int index);
int wxPGMultiButton_GetButtonId(TSelf(wxPGMultiButton) pObject, unsigned int index);
int wxPGMultiButton_GetCount(TSelf(wxPGMultiButton) pObject);
void wxPGMultiButton_Add(TSelf(wxPGMultiButton) pObject, TClass(wxString) label, int id);
void wxPGMultiButton_AddBitmap(TSelf(wxPGMultiButton) pObject, TClass(wxBitmapBundle) bitmap,
                               int id);
TClass(wxSize) wxPGMultiButton_GetPrimarySize(TSelf(wxPGMultiButton) pObject);
void wxPGMultiButton_Finalize(TSelf(wxPGMultiButton) pObject, TClass(wxPropertyGrid) propgrid,
                              TPoint(x, y));

// ---------------------------------------------------------------------------
// wxPGCell
// ---------------------------------------------------------------------------

TClassDef(wxPGCell) TClass(wxPGCell) wxPGCell_Create();
TClass(wxPGCell) wxPGCell_CreateWithText(TClass(wxString) text);
void wxPGCell_Delete(TSelf(wxPGCell) pObject);
TBool wxPGCell_HasText(TSelf(wxPGCell) pObject);
TBool wxPGCell_IsInvalid(TSelf(wxPGCell) pObject);
void wxPGCell_SetEmptyData(TSelf(wxPGCell) pObject);
void wxPGCell_MergeFrom(TSelf(wxPGCell) pObject, TClass(wxPGCell) srcCell);
void wxPGCell_SetText(TSelf(wxPGCell) pObject, TClass(wxString) text);
void wxPGCell_SetBitmap(TSelf(wxPGCell) pObject, TClass(wxBitmapBundle) bitmap);
void wxPGCell_SetFgCol(TSelf(wxPGCell) pObject, TClass(wxColour) colour);
void wxPGCell_SetBgCol(TSelf(wxPGCell) pObject, TClass(wxColour) colour);
void wxPGCell_SetFont(TSelf(wxPGCell) pObject, TClass(wxFont) font);
TClass(wxString) wxPGCell_GetText(TSelf(wxPGCell) pObject);
TClass(wxBitmapBundle) wxPGCell_GetBitmap(TSelf(wxPGCell) pObject);
TClass(wxColour) wxPGCell_GetFgCol(TSelf(wxPGCell) pObject);
TClass(wxColour) wxPGCell_GetBgCol(TSelf(wxPGCell) pObject);
TClass(wxFont) wxPGCell_GetFont(TSelf(wxPGCell) pObject);

// ---------------------------------------------------------------------------
// wxNumericPropertyValidator
// ---------------------------------------------------------------------------

TClassDefExtend(wxNumericPropertyValidator, wxTextValidator) TClass(wxNumericPropertyValidator)
    wxNumericPropertyValidator_Create(int numeric_type, int base);
void wxNumericPropertyValidator_Delete(TSelf(wxNumericPropertyValidator) pObject);
TBool wxNumericPropertyValidator_Validate(TSelf(wxNumericPropertyValidator) pObject,
                                          TClass(wxWindow) parent);

// ---------------------------------------------------------------------------
// wxPGArrayEditorDialog
// ---------------------------------------------------------------------------

TClassDefExtend(wxPGArrayEditorDialog, wxDialog)
    // wxPGArrayEditorDialog is abstract (pure virtual ArrayGet, ArrayGetCount,
    // ArrayInsert, ArraySet, ArrayRemoveAt and ArraySwap) and no public factory is
    // exposed by the wrapped API, so it has no Create/Delete wrapper.
    void wxPGArrayEditorDialog_SetDialogValue(TSelf(wxPGArrayEditorDialog) pObject,
                                              TClass(wxVariant) value);
TClass(wxVariant) wxPGArrayEditorDialog_GetDialogValue(TSelf(wxPGArrayEditorDialog) pObject);
void wxPGArrayEditorDialog_EnableCustomNewAction(TSelf(wxPGArrayEditorDialog) pObject);
void wxPGArrayEditorDialog_SetNewButtonText(TSelf(wxPGArrayEditorDialog) pObject,
                                            TClass(wxString) text);
TBool wxPGArrayEditorDialog_IsModified(TSelf(wxPGArrayEditorDialog) pObject);
int wxPGArrayEditorDialog_GetSelection(TSelf(wxPGArrayEditorDialog) pObject);

// ---------------------------------------------------------------------------
// wxPGValidationInfo
// ---------------------------------------------------------------------------

TClassDef(wxPGValidationInfo) TClass(wxPGValidationInfo) wxPGValidationInfo_Create();
void wxPGValidationInfo_Delete(TSelf(wxPGValidationInfo) pObject);
int wxPGValidationInfo_GetFailureBehavior(TSelf(wxPGValidationInfo) pObject);
void wxPGValidationInfo_SetFailureBehavior(TSelf(wxPGValidationInfo) pObject, int failure_behavior);
TClass(wxString) wxPGValidationInfo_GetFailureMessage(TSelf(wxPGValidationInfo) pObject);
void wxPGValidationInfo_SetFailureMessage(TSelf(wxPGValidationInfo) pObject,
                                          TClass(wxString) message);
TClass(wxVariant) wxPGValidationInfo_GetValue(TSelf(wxPGValidationInfo) pObject);

// ---------------------------------------------------------------------------
// wxPropertyGridPageState
// ---------------------------------------------------------------------------

TClassDef(wxPropertyGridPageState) TClass(wxPropertyGridPageState) wxPropertyGridPageState_Create();
void wxPropertyGridPageState_Delete(TSelf(wxPropertyGridPageState) pObject);
TClass(wxPropertyGrid) wxPropertyGridPageState_GetGrid(TSelf(wxPropertyGridPageState) pObject);
int wxPropertyGridPageState_GetColumnCount(TSelf(wxPropertyGridPageState) pObject);
int wxPropertyGridPageState_GetColumnMinWidth(TSelf(wxPropertyGridPageState) pObject, int column);
int wxPropertyGridPageState_GetColumnWidth(TSelf(wxPropertyGridPageState) pObject,
                                           unsigned int column);
int wxPropertyGridPageState_GetVirtualWidth(TSelf(wxPropertyGridPageState) pObject);
int wxPropertyGridPageState_GetVirtualHeight(TSelf(wxPropertyGridPageState) pObject);
int wxPropertyGridPageState_GetActualVirtualHeight(TSelf(wxPropertyGridPageState) pObject);
TClass(wxPGProperty)
    wxPropertyGridPageState_GetLastItem(TSelf(wxPropertyGridPageState) pObject, int flags);
TClass(wxPGProperty) wxPropertyGridPageState_GetSelection(TSelf(wxPropertyGridPageState) pObject);
TBool wxPropertyGridPageState_EnableCategories(TSelf(wxPropertyGridPageState) pObject,
                                               TBool enable);
TBool wxPropertyGridPageState_IsDisplayed(TSelf(wxPropertyGridPageState) pObject);
TBool wxPropertyGridPageState_IsInNonCatMode(TSelf(wxPropertyGridPageState) pObject);
void wxPropertyGridPageState_CheckColumnWidths(TSelf(wxPropertyGridPageState) pObject,
                                               int width_change);
void wxPropertyGridPageState_VirtualHeightChanged(TSelf(wxPropertyGridPageState) pObject);

// ---------------------------------------------------------------------------
// wxPropertyGridInterface
// ---------------------------------------------------------------------------

TClassDef(wxPropertyGridInterface) TClass(wxPGProperty)
    wxPropertyGridInterface_GetPropertyByName(TSelf(wxPropertyGridInterface) pObject,
                                              TClass(wxString) name);
TClass(wxPGProperty)
    wxPropertyGridInterface_GetPropertyByName2(TSelf(wxPropertyGridInterface) pObject,
                                               TClass(wxString) name, TClass(wxString) subname);
TClass(wxPGProperty)
    wxPropertyGridInterface_GetPropertyByLabel(TSelf(wxPropertyGridInterface) pObject,
                                               TClass(wxString) label);
TClass(wxString) wxPropertyGridInterface_GetPropertyName(TSelf(wxPropertyGridInterface) pObject,
                                                         TClass(wxPGProperty) property);
TClass(wxString) wxPropertyGridInterface_GetPropertyLabel(TSelf(wxPropertyGridInterface) pObject,
                                                          TClass(wxPGProperty) id);
TClass(wxString)
    wxPropertyGridInterface_GetPropertyHelpString(TSelf(wxPropertyGridInterface) pObject,
                                                  TClass(wxPGProperty) id);
TClass(wxPGProperty)
    wxPropertyGridInterface_GetPropertyParent(TSelf(wxPropertyGridInterface) pObject,
                                              TClass(wxPGProperty) id);
TClass(wxPropertyCategory)
    wxPropertyGridInterface_GetPropertyCategory(TSelf(wxPropertyGridInterface) pObject,
                                                TClass(wxPGProperty) id);
TClass(wxPGEditor) wxPropertyGridInterface_GetPropertyEditor(TSelf(wxPropertyGridInterface) pObject,
                                                             TClass(wxPGProperty) id);
TClass(wxBitmap) wxPropertyGridInterface_GetPropertyImage(TSelf(wxPropertyGridInterface) pObject,
                                                          TClass(wxPGProperty) id);
TClass(wxPGProperty) wxPropertyGridInterface_GetFirstChild(TSelf(wxPropertyGridInterface) pObject,
                                                           TClass(wxPGProperty) id);
TClass(wxPGProperty)
    wxPropertyGridInterface_GetFirst(TSelf(wxPropertyGridInterface) pObject, int flags);
TClass(wxPGProperty) wxPropertyGridInterface_GetSelection(TSelf(wxPropertyGridInterface) pObject);
TClass(wxPropertyGridPageState)
    wxPropertyGridInterface_GetState(TSelf(wxPropertyGridInterface) pObject);
TClass(wxPGProperty) wxPropertyGridInterface_Append(TSelf(wxPropertyGridInterface) pObject,
                                                    TClass(wxPGProperty) property);
TClass(wxPGProperty)
    wxPropertyGridInterface_AppendIn(TSelf(wxPropertyGridInterface) pObject,
                                     TClass(wxPGProperty) id, TClass(wxPGProperty) property);
TClass(wxPGProperty)
    wxPropertyGridInterface_Insert(TSelf(wxPropertyGridInterface) pObject,
                                   TClass(wxPGProperty) prior_this, TClass(wxPGProperty) property);
TClass(wxPGProperty) wxPropertyGridInterface_Insert2(TSelf(wxPropertyGridInterface) pObject,
                                                     TClass(wxPGProperty) parent, int index,
                                                     TClass(wxPGProperty) property);
TClass(wxPGProperty)
    wxPropertyGridInterface_ReplaceProperty(TSelf(wxPropertyGridInterface) pObject,
                                            TClass(wxPGProperty) id, TClass(wxPGProperty) property);
TClass(wxPGProperty) wxPropertyGridInterface_RemoveProperty(TSelf(wxPropertyGridInterface) pObject,
                                                            TClass(wxPGProperty) id);
void wxPropertyGridInterface_DeleteProperty(TSelf(wxPropertyGridInterface) pObject,
                                            TClass(wxPGProperty) id);
void wxPropertyGridInterface_Clear(TSelf(wxPropertyGridInterface) pObject);
TBool wxPropertyGridInterface_ClearSelection(TSelf(wxPropertyGridInterface) pObject,
                                             TBool validation);
void wxPropertyGridInterface_ClearModifiedStatus(TSelf(wxPropertyGridInterface) pObject);
TBool wxPropertyGridInterface_EditorValidate(TSelf(wxPropertyGridInterface) pObject);
TBool wxPropertyGridInterface_Collapse(TSelf(wxPropertyGridInterface) pObject,
                                       TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_CollapseAll(TSelf(wxPropertyGridInterface) pObject);
TBool wxPropertyGridInterface_Expand(TSelf(wxPropertyGridInterface) pObject,
                                     TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_ExpandAll(TSelf(wxPropertyGridInterface) pObject, TBool expand);
TBool wxPropertyGridInterface_DisableProperty(TSelf(wxPropertyGridInterface) pObject,
                                              TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_EnableProperty(TSelf(wxPropertyGridInterface) pObject,
                                             TClass(wxPGProperty) id, TBool enable);
TBool wxPropertyGridInterface_HideProperty(TSelf(wxPropertyGridInterface) pObject,
                                           TClass(wxPGProperty) id, TBool hide, int flags);
void wxPropertyGridInterface_LimitPropertyEditing(TSelf(wxPropertyGridInterface) pObject,
                                                  TClass(wxPGProperty) id, TBool limit);
void wxPropertyGridInterface_RefreshGrid(TSelf(wxPropertyGridInterface) pObject,
                                         TClass(wxPropertyGridPageState) state);
void wxPropertyGridInterface_RefreshProperty(TSelf(wxPropertyGridInterface) pObject,
                                             TClass(wxPGProperty) property);
TClass(wxVariant) wxPropertyGridInterface_GetPropertyValue(TSelf(wxPropertyGridInterface) pObject,
                                                           TClass(wxPGProperty) id);
TClass(wxString)
    wxPropertyGridInterface_GetPropertyValueAsString(TSelf(wxPropertyGridInterface) pObject,
                                                     TClass(wxPGProperty) id);
long wxPropertyGridInterface_GetPropertyValueAsLong(TSelf(wxPropertyGridInterface) pObject,
                                                    TClass(wxPGProperty) id);
int wxPropertyGridInterface_GetPropertyValueAsInt(TSelf(wxPropertyGridInterface) pObject,
                                                  TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_GetPropertyValueAsBool(TSelf(wxPropertyGridInterface) pObject,
                                                     TClass(wxPGProperty) id);
double wxPropertyGridInterface_GetPropertyValueAsDouble(TSelf(wxPropertyGridInterface) pObject,
                                                        TClass(wxPGProperty) id);
void wxPropertyGridInterface_SetPropertyValue(TSelf(wxPropertyGridInterface) pObject,
                                              TClass(wxPGProperty) id, TClass(wxVariant) value);
void wxPropertyGridInterface_SetPropertyValueString(TSelf(wxPropertyGridInterface) pObject,
                                                    TClass(wxPGProperty) id,
                                                    TClass(wxString) value);
void wxPropertyGridInterface_SetPropertyValueLong(TSelf(wxPropertyGridInterface) pObject,
                                                  TClass(wxPGProperty) id, long value);
void wxPropertyGridInterface_SetPropertyValueInt(TSelf(wxPropertyGridInterface) pObject,
                                                 TClass(wxPGProperty) id, int value);
void wxPropertyGridInterface_SetPropertyValueDouble(TSelf(wxPropertyGridInterface) pObject,
                                                    TClass(wxPGProperty) id, double value);
void wxPropertyGridInterface_SetPropertyValueBool(TSelf(wxPropertyGridInterface) pObject,
                                                  TClass(wxPGProperty) id, TBool value);
void wxPropertyGridInterface_SetPropertyValueUnspecified(TSelf(wxPropertyGridInterface) pObject,
                                                         TClass(wxPGProperty) id);
void wxPropertyGridInterface_SetPropertyLabel(TSelf(wxPropertyGridInterface) pObject,
                                              TClass(wxPGProperty) id, TClass(wxString) label);
void wxPropertyGridInterface_SetPropertyName(TSelf(wxPropertyGridInterface) pObject,
                                             TClass(wxPGProperty) id, TClass(wxString) name);
void wxPropertyGridInterface_SetPropertyHelpString(TSelf(wxPropertyGridInterface) pObject,
                                                   TClass(wxPGProperty) id, TClass(wxString) text);
void wxPropertyGridInterface_SetPropertyReadOnly(TSelf(wxPropertyGridInterface) pObject,
                                                 TClass(wxPGProperty) id, TBool read_only,
                                                 int flags);
void wxPropertyGridInterface_SetPropertyEditor(TSelf(wxPropertyGridInterface) pObject,
                                               TClass(wxPGProperty) id, TClass(wxPGEditor) editor);
void wxPropertyGridInterface_SetPropertyEditorByName(TSelf(wxPropertyGridInterface) pObject,
                                                     TClass(wxPGProperty) id,
                                                     TClass(wxString) name);
void wxPropertyGridInterface_SetPropertyImage(TSelf(wxPropertyGridInterface) pObject,
                                              TClass(wxPGProperty) id,
                                              TClass(wxBitmapBundle) bitmap);
void wxPropertyGridInterface_SetPropertyCell(TSelf(wxPropertyGridInterface) pObject,
                                             TClass(wxPGProperty) id, int column,
                                             TClass(wxString) text, TClass(wxBitmapBundle) bitmap,
                                             TClass(wxColour) fg_col, TClass(wxColour) bg_col);
TBool wxPropertyGridInterface_IsPropertyCategory(TSelf(wxPropertyGridInterface) pObject,
                                                 TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_IsPropertyEnabled(TSelf(wxPropertyGridInterface) pObject,
                                                TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_IsPropertyExpanded(TSelf(wxPropertyGridInterface) pObject,
                                                 TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_IsPropertyModified(TSelf(wxPropertyGridInterface) pObject,
                                                 TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_IsPropertySelected(TSelf(wxPropertyGridInterface) pObject,
                                                 TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_IsPropertyShown(TSelf(wxPropertyGridInterface) pObject,
                                              TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_IsPropertyValueUnspecified(TSelf(wxPropertyGridInterface) pObject,
                                                         TClass(wxPGProperty) id);
TBool wxPropertyGridInterface_SetColumnProportion(TSelf(wxPropertyGridInterface) pObject,
                                                  unsigned int column, int proportion);
int wxPropertyGridInterface_GetColumnProportion(TSelf(wxPropertyGridInterface) pObject,
                                                unsigned int column);
TClass(wxString) wxPropertyGridInterface_SaveEditableState(TSelf(wxPropertyGridInterface) pObject,
                                                           int included_states);
TBool wxPropertyGridInterface_RestoreEditableState(TSelf(wxPropertyGridInterface) pObject,
                                                   TClass(wxString) src, int restore_states);
void wxPropertyGridInterface_Sort(TSelf(wxPropertyGridInterface) pObject, int flags);
void wxPropertyGridInterface_SortChildren(TSelf(wxPropertyGridInterface) pObject,
                                          TClass(wxPGProperty) id, int flags);

// ---------------------------------------------------------------------------
// wxPropertyGrid (extends TClassDefExtend(wxPropertyGrid, wxControl))
// ---------------------------------------------------------------------------

TClassDefExtend(wxPropertyGrid,
                wxControl) int wxPropertyGrid_GetColumnCount(TSelf(wxPropertyGrid) pObject);
int wxPropertyGrid_GetRowHeight(TSelf(wxPropertyGrid) pObject);
int wxPropertyGrid_GetFontHeight(TSelf(wxPropertyGrid) pObject);
int wxPropertyGrid_GetMarginWidth(TSelf(wxPropertyGrid) pObject);
int wxPropertyGrid_GetVerticalSpacing(TSelf(wxPropertyGrid) pObject);
int wxPropertyGrid_GetSpacingY(TSelf(wxPropertyGrid) pObject);
TClass(wxWindow) wxPropertyGrid_GetPanel(TSelf(wxPropertyGrid) pObject);
TClass(wxPropertyGrid) wxPropertyGrid_GetGrid(TSelf(wxPropertyGrid) pObject);
TClass(wxPGProperty) wxPropertyGrid_GetRoot(TSelf(wxPropertyGrid) pObject);
TClass(wxPGProperty) wxPropertyGrid_GetLastItem(TSelf(wxPropertyGrid) pObject, int flags);
TClass(wxPGProperty) wxPropertyGrid_GetSelectedProperty(TSelf(wxPropertyGrid) pObject);
TClass(wxPGProperty) wxPropertyGrid_GetSelection(TSelf(wxPropertyGrid) pObject);
TClass(wxTextCtrl) wxPropertyGrid_GetEditorTextCtrl(TSelf(wxPropertyGrid) pObject);
TClass(wxWindow) wxPropertyGrid_GetEditorControl(TSelf(wxPropertyGrid) pObject);
TClass(wxWindow) wxPropertyGrid_GetEditorControlSecondary(TSelf(wxPropertyGrid) pObject);
TClass(wxTextCtrl) wxPropertyGrid_GetLabelEditor(TSelf(wxPropertyGrid) pObject);
TClass(wxPGValidationInfo) wxPropertyGrid_GetValidationInfo(TSelf(wxPropertyGrid) pObject);
TClass(wxSize) wxPropertyGrid_GetImageSize(TSelf(wxPropertyGrid) pObject,
                                           TClass(wxPGProperty) property, int item);
TClass(wxRect) wxPropertyGrid_GetImageRect(TSelf(wxPropertyGrid) pObject,
                                           TClass(wxPGProperty) property, int item);
TClass(wxRect)
    wxPropertyGrid_GetPropertyRect(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) first,
                                   TClass(wxPGProperty) last);
TClass(wxSize) wxPropertyGrid_FitColumns(TSelf(wxPropertyGrid) pObject);
TClass(wxFont) wxPropertyGrid_GetCaptionFont(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetCaptionBackgroundColour(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetCaptionForegroundColour(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetCellBackgroundColour(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetCellDisabledTextColour(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetCellTextColour(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetEmptySpaceColour(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetLineColour(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetMarginColour(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetSelectionBackgroundColour(TSelf(wxPropertyGrid) pObject);
TClass(wxColour) wxPropertyGrid_GetSelectionForegroundColour(TSelf(wxPropertyGrid) pObject);
void wxPropertyGrid_SetCaptionBackgroundColour(TSelf(wxPropertyGrid) pObject,
                                               TClass(wxColour) colour);
void wxPropertyGrid_SetCaptionTextColour(TSelf(wxPropertyGrid) pObject, TClass(wxColour) colour);
void wxPropertyGrid_SetCellBackgroundColour(TSelf(wxPropertyGrid) pObject, TClass(wxColour) colour);
void wxPropertyGrid_SetCellDisabledTextColour(TSelf(wxPropertyGrid) pObject,
                                              TClass(wxColour) colour);
void wxPropertyGrid_SetCellTextColour(TSelf(wxPropertyGrid) pObject, TClass(wxColour) colour);
void wxPropertyGrid_SetEmptySpaceColour(TSelf(wxPropertyGrid) pObject, TClass(wxColour) colour);
void wxPropertyGrid_SetLineColour(TSelf(wxPropertyGrid) pObject, TClass(wxColour) colour);
void wxPropertyGrid_SetMarginColour(TSelf(wxPropertyGrid) pObject, TClass(wxColour) colour);
void wxPropertyGrid_SetSelectionBackgroundColour(TSelf(wxPropertyGrid) pObject,
                                                 TClass(wxColour) colour);
void wxPropertyGrid_SetSelectionTextColour(TSelf(wxPropertyGrid) pObject, TClass(wxColour) colour);
TClass(wxPGCell) wxPropertyGrid_GetPropertyDefaultCell(TSelf(wxPropertyGrid) pObject);
TClass(wxPGCell) wxPropertyGrid_GetCategoryDefaultCell(TSelf(wxPropertyGrid) pObject);
TClass(wxPGCell) wxPropertyGrid_GetUnspecifiedValueAppearance(TSelf(wxPropertyGrid) pObject);
void wxPropertyGrid_SetUnspecifiedValueAppearance(TSelf(wxPropertyGrid) pObject,
                                                  TClass(wxPGCell) cell);
void wxPropertyGrid_SetColumnCount(TSelf(wxPropertyGrid) pObject, int column_count);
void wxPropertyGrid_SetSplitterPosition(TSelf(wxPropertyGrid) pObject, int position, int column);
int wxPropertyGrid_GetSplitterPosition(TSelf(wxPropertyGrid) pObject, unsigned int splitter_index);
void wxPropertyGrid_SetSplitterLeft(TSelf(wxPropertyGrid) pObject, TBool private_children_too);
void wxPropertyGrid_SetVirtualWidth(TSelf(wxPropertyGrid) pObject, int width);
TBool wxPropertyGrid_HasVirtualWidth(TSelf(wxPropertyGrid) pObject);
void wxPropertyGrid_CenterSplitter(TSelf(wxPropertyGrid) pObject, TBool enable_auto_resizing);
void wxPropertyGrid_ResetColumnSizes(TSelf(wxPropertyGrid) pObject, TBool enable_auto_resizing);
void wxPropertyGrid_ResetColours(TSelf(wxPropertyGrid) pObject);
void wxPropertyGrid_MakeColumnEditable(TSelf(wxPropertyGrid) pObject, unsigned int column,
                                       TBool editable);
void wxPropertyGrid_SetVerticalSpacing(TSelf(wxPropertyGrid) pObject, int spacing);
TBool wxPropertyGrid_SelectProperty(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id,
                                    TBool focus);
TBool wxPropertyGrid_AddToSelection(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id);
TBool wxPropertyGrid_RemoveFromSelection(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id);
TBool wxPropertyGrid_EnsureVisible(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id);
TBool wxPropertyGrid_EnableCategories(TSelf(wxPropertyGrid) pObject, TBool enable);
TBool wxPropertyGrid_CommitChangesFromEditor(TSelf(wxPropertyGrid) pObject, int flags);
void wxPropertyGrid_BeginLabelEdit(TSelf(wxPropertyGrid) pObject, unsigned int column);
void wxPropertyGrid_EndLabelEdit(TSelf(wxPropertyGrid) pObject, TBool commit);
TBool wxPropertyGrid_IsAnyModified(TSelf(wxPropertyGrid) pObject);
TBool wxPropertyGrid_IsEditorFocused(TSelf(wxPropertyGrid) pObject);
TBool wxPropertyGrid_IsEditorsValueModified(TSelf(wxPropertyGrid) pObject);
void wxPropertyGrid_EditorsValueWasModified(TSelf(wxPropertyGrid) pObject);
void wxPropertyGrid_EditorsValueWasNotModified(TSelf(wxPropertyGrid) pObject);
void wxPropertyGrid_RefreshEditor(TSelf(wxPropertyGrid) pObject);
TBool wxPropertyGrid_UnfocusEditor(TSelf(wxPropertyGrid) pObject);
void wxPropertyGrid_RefreshProperty(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) property);
void wxPropertyGrid_SetCurrentCategory(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id);
void wxPropertyGrid_DedicateKey(TSelf(wxPropertyGrid) pObject, int keycode);
void wxPropertyGrid_AddActionTrigger(TSelf(wxPropertyGrid) pObject, int action, int keycode,
                                     int modifiers);
void wxPropertyGrid_ClearActionTriggers(TSelf(wxPropertyGrid) pObject, int action);
TBool wxPropertyGrid_SetFont(TSelf(wxPropertyGrid) pObject, TClass(wxFont) font);

// ---------------------------------------------------------------------------
// wxPropertyGridPage (extends TClassDefExtend(wxPropertyGridPage, wxEvtHandler))
// ---------------------------------------------------------------------------

TClassDefExtend(wxPropertyGridPage, wxEvtHandler) TClass(wxSize)
    wxPropertyGridPage_FitColumns(TSelf(wxPropertyGridPage) pObject);
TClass(wxPropertyGridPageState) wxPropertyGridPage_GetStatePtr(TSelf(wxPropertyGridPage) pObject);
int wxPropertyGridPage_GetToolId(TSelf(wxPropertyGridPage) pObject);
void wxPropertyGridPage_Init(TSelf(wxPropertyGridPage) pObject);
TBool wxPropertyGridPage_IsHandlingAllEvents(TSelf(wxPropertyGridPage) pObject);
void wxPropertyGridPage_OnShow(TSelf(wxPropertyGridPage) pObject);
void wxPropertyGridPage_RefreshProperty(TSelf(wxPropertyGridPage) pObject,
                                        TClass(wxPGProperty) property);

// ---------------------------------------------------------------------------
// Typed property classes (the Wx::PG "wxPGProperties" group)
// ---------------------------------------------------------------------------

void wxStringProperty_Delete(TSelf(wxStringProperty) pObject);
void wxIntProperty_Delete(TSelf(wxIntProperty) pObject);
void wxBoolProperty_Delete(TSelf(wxBoolProperty) pObject);
void wxFloatProperty_Delete(TSelf(wxFloatProperty) pObject);
void wxDateProperty_Delete(TSelf(wxDateProperty) pObject);
void wxFileProperty_Delete(TSelf(wxFileProperty) pObject);
void wxPropertyCategory_Delete(TSelf(wxPropertyCategory) pObject);

TClassDefExtend(wxUIntProperty, wxPGProperty) TClass(wxUIntProperty)
    wxUIntProperty_Create(TClass(wxString) label, TClass(wxString) name, unsigned long value);
void wxUIntProperty_Delete(TSelf(wxUIntProperty) pObject);

TClassDefExtend(wxLongStringProperty, wxPGProperty) TClass(wxLongStringProperty)
    wxLongStringProperty_Create(TClass(wxString) label, TClass(wxString) name,
                                TClass(wxString) value);
void wxLongStringProperty_Delete(TSelf(wxLongStringProperty) pObject);

TClassDefExtend(wxDirProperty, wxPGProperty) TClass(wxDirProperty)
    wxDirProperty_Create(TClass(wxString) label, TClass(wxString) name, TClass(wxString) value);
void wxDirProperty_Delete(TSelf(wxDirProperty) pObject);

TClassDefExtend(wxArrayStringProperty, wxPGProperty) TClass(wxArrayStringProperty)
    wxArrayStringProperty_Create(TClass(wxString) label, TClass(wxString) name,
                                 TArrayString(count, values));
void wxArrayStringProperty_Delete(TSelf(wxArrayStringProperty) pObject);

TClassDefExtend(wxFontProperty, wxPGProperty) TClass(wxFontProperty)
    wxFontProperty_Create(TClass(wxString) label, TClass(wxString) name, TClass(wxFont) value);
void wxFontProperty_Delete(TSelf(wxFontProperty) pObject);

TClassDefExtend(wxColourProperty, wxPGProperty) TClass(wxColourProperty)
    wxColourProperty_Create(TClass(wxString) label, TClass(wxString) name, TClass(wxColour) value);
void wxColourProperty_Delete(TSelf(wxColourProperty) pObject);

TClassDefExtend(wxMultiChoiceProperty, wxPGProperty) TClass(wxMultiChoiceProperty)
    wxMultiChoiceProperty_Create(TClass(wxString) label, TClass(wxString) name,
                                 TArrayString(count, values));
void wxMultiChoiceProperty_Delete(TSelf(wxMultiChoiceProperty) pObject);

TClassDefExtend(wxEnumProperty, wxPGProperty) TClass(wxEnumProperty)
    wxEnumProperty_Create(TClass(wxString) label, TClass(wxString) name,
                          TArrayString(label_count, labels), TArrayInt(value_count, values),
                          int value);
void wxEnumProperty_Delete(TSelf(wxEnumProperty) pObject);

TClassDefExtend(wxEditEnumProperty, wxEnumProperty) TClass(wxEditEnumProperty)
    wxEditEnumProperty_Create(TClass(wxString) label, TClass(wxString) name,
                              TArrayString(label_count, labels), TArrayInt(value_count, values),
                              TClass(wxString) value);
void wxEditEnumProperty_Delete(TSelf(wxEditEnumProperty) pObject);

TClassDefExtend(wxFlagsProperty, wxPGProperty) TClass(wxFlagsProperty)
    wxFlagsProperty_Create(TClass(wxString) label, TClass(wxString) name,
                           TArrayString(label_count, labels), TArrayInt(value_count, values),
                           int value);
void wxFlagsProperty_Delete(TSelf(wxFlagsProperty) pObject);

TClassDefExtend(wxImageFileProperty, wxFileProperty) TClass(wxImageFileProperty)
    wxImageFileProperty_Create(TClass(wxString) label, TClass(wxString) name,
                               TClass(wxString) value);
void wxImageFileProperty_Delete(TSelf(wxImageFileProperty) pObject);
