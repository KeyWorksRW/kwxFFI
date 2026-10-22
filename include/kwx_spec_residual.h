#pragma once

// Phase 15: residual wxRuby3 spec entries that no other phase owns.
// Source list: .private/coverage-baseline.md "Gaps with no owning phase".
// Declarations for the implementations in src/wx_spec_residual.cpp.

// Not declared here, with the reasons reported by Phase 15:
// - wxGridCtrl: wxRuby3 composite spec name, no wxWidgets class exists.
// - wxDataObjectSimpleBase: wxRuby3 base name, no wxWidgets class exists.
// - wxGridCellAutoWrapStringEditor: its only wrappable own member (the _Ctor
//   factory) is already declared in include/kwx_grid_extra.h.

// ---------------------------------------------------------------------------
// Event classes
// ---------------------------------------------------------------------------

TClassDefExtend(wxSpinDoubleEvent, wxNotifyEvent) TClass(wxSpinDoubleEvent)
    wxSpinDoubleEvent_Create(int command_type, int win_id, double value);
void wxSpinDoubleEvent_Delete(TSelf(wxSpinDoubleEvent) pObject);
double wxSpinDoubleEvent_GetValue(TSelf(wxSpinDoubleEvent) pObject);
void wxSpinDoubleEvent_SetValue(TSelf(wxSpinDoubleEvent) pObject, double value);

TClassDefExtend(wxFontPickerEvent, wxCommandEvent) TClass(wxFontPickerEvent)
    wxFontPickerEvent_Create(TClass(wxObject) generator, int id, TClass(wxFont) font);
void wxFontPickerEvent_Delete(TSelf(wxFontPickerEvent) pObject);
TClass(wxFont) wxFontPickerEvent_GetFont(TSelf(wxFontPickerEvent) pObject);
void wxFontPickerEvent_SetFont(TSelf(wxFontPickerEvent) pObject, TClass(wxFont) font);

TClassDefExtend(wxColourPickerEvent, wxCommandEvent) TClass(wxColourPickerEvent)
    wxColourPickerEvent_Create(TClass(wxObject) generator, int id, TClass(wxColour) colour,
                               int command_type);
void wxColourPickerEvent_Delete(TSelf(wxColourPickerEvent) pObject);
TClass(wxColour) wxColourPickerEvent_GetColour(TSelf(wxColourPickerEvent) pObject);
void wxColourPickerEvent_SetColour(TSelf(wxColourPickerEvent) pObject, TClass(wxColour) colour);

TClassDefExtend(wxFileDirPickerEvent, wxCommandEvent) TClass(wxFileDirPickerEvent)
    wxFileDirPickerEvent_Create(int event_type, TClass(wxObject) generator, int id,
                                TClass(wxString) path);
void wxFileDirPickerEvent_Delete(TSelf(wxFileDirPickerEvent) pObject);
TClass(wxString) wxFileDirPickerEvent_GetPath(TSelf(wxFileDirPickerEvent) pObject);
void wxFileDirPickerEvent_SetPath(TSelf(wxFileDirPickerEvent) pObject, TClass(wxString) path);

TClassDefExtend(wxFileCtrlEvent, wxCommandEvent) TClass(wxFileCtrlEvent)
    wxFileCtrlEvent_Create(int event_type, TClass(wxObject) generator, int id);
void wxFileCtrlEvent_Delete(TSelf(wxFileCtrlEvent) pObject);
void wxFileCtrlEvent_SetFiles(TSelf(wxFileCtrlEvent) pObject, TClass(wxArrayString) files);
void wxFileCtrlEvent_SetDirectory(TSelf(wxFileCtrlEvent) pObject, TClass(wxString) directory);
void wxFileCtrlEvent_SetFilterIndex(TSelf(wxFileCtrlEvent) pObject, int filter_index);
void wxFileCtrlEvent_GetFiles(TSelf(wxFileCtrlEvent) pObject, TClass(wxArrayString) files);
TClass(wxString) wxFileCtrlEvent_GetDirectory(TSelf(wxFileCtrlEvent) pObject);
int wxFileCtrlEvent_GetFilterIndex(TSelf(wxFileCtrlEvent) pObject);
TClass(wxString) wxFileCtrlEvent_GetFile(TSelf(wxFileCtrlEvent) pObject);

TClassDefExtend(wxHeaderCtrlEvent, wxNotifyEvent) TClass(wxHeaderCtrlEvent)
    wxHeaderCtrlEvent_Create(int command_type, int win_id);
void wxHeaderCtrlEvent_Delete(TSelf(wxHeaderCtrlEvent) pObject);
int wxHeaderCtrlEvent_GetColumn(TSelf(wxHeaderCtrlEvent) pObject);
void wxHeaderCtrlEvent_SetColumn(TSelf(wxHeaderCtrlEvent) pObject, int column);
int wxHeaderCtrlEvent_GetWidth(TSelf(wxHeaderCtrlEvent) pObject);
void wxHeaderCtrlEvent_SetWidth(TSelf(wxHeaderCtrlEvent) pObject, int width);
int wxHeaderCtrlEvent_GetNewOrder(TSelf(wxHeaderCtrlEvent) pObject);
void wxHeaderCtrlEvent_SetNewOrder(TSelf(wxHeaderCtrlEvent) pObject, int order);

TClassDefExtend(wxDateEvent, wxCommandEvent) TClass(wxDateEvent) wxDateEvent_Create();
void wxDateEvent_Delete(TSelf(wxDateEvent) pObject);
void wxDateEvent_GetDate(TSelf(wxDateEvent) pObject, TClass(wxDateTime) date);
void wxDateEvent_SetDate(TSelf(wxDateEvent) pObject, TClass(wxDateTime) date);

TClassDefExtend(wxTaskBarIconEvent, wxEvent) TClass(wxTaskBarIconEvent)
    wxTaskBarIconEvent_Create(int event_type, TClass(wxTaskBarIcon) task_bar_icon);
void wxTaskBarIconEvent_Delete(TSelf(wxTaskBarIconEvent) pObject);

TClassDefExtend(wxMediaEvent, wxNotifyEvent) TClass(wxMediaEvent)
    wxMediaEvent_Create(int command_type, int win_id);
void wxMediaEvent_Delete(TSelf(wxMediaEvent) pObject);

TClassDefExtend(wxHyperlinkEvent, wxCommandEvent) TClass(wxHyperlinkEvent)
    wxHyperlinkEvent_Create(TClass(wxObject) generator, int id, TClass(wxString) url);
void wxHyperlinkEvent_Delete(TSelf(wxHyperlinkEvent) pObject);
TClass(wxString) wxHyperlinkEvent_GetURL(TSelf(wxHyperlinkEvent) pObject);
void wxHyperlinkEvent_SetURL(TSelf(wxHyperlinkEvent) pObject, TClass(wxString) url);

TClassDefExtend(wxThreadEvent, wxEvent) TClass(wxThreadEvent)
    wxThreadEvent_Create(int event_type, int id);
void wxThreadEvent_Delete(TSelf(wxThreadEvent) pObject);
TClass(wxString) wxThreadEvent_GetString(TSelf(wxThreadEvent) pObject);
void wxThreadEvent_SetString(TSelf(wxThreadEvent) pObject, TClass(wxString) text);
int wxThreadEvent_GetInt(TSelf(wxThreadEvent) pObject);
void wxThreadEvent_SetInt(TSelf(wxThreadEvent) pObject, int value);
long wxThreadEvent_GetExtraLong(TSelf(wxThreadEvent) pObject);
void wxThreadEvent_SetExtraLong(TSelf(wxThreadEvent) pObject, long value);

TClassDefExtend(wxSplitterEvent, wxNotifyEvent) TClass(wxSplitterEvent)
    wxSplitterEvent_Create(int event_type, TClass(wxSplitterWindow) splitter);
void wxSplitterEvent_Delete(TSelf(wxSplitterEvent) pObject);
void wxSplitterEvent_SetSashPosition(TSelf(wxSplitterEvent) pObject, int position);
int wxSplitterEvent_GetSashPosition(TSelf(wxSplitterEvent) pObject);
void wxSplitterEvent_SetSize(TSelf(wxSplitterEvent) pObject, int old_size, int new_size);
int wxSplitterEvent_GetOldSize(TSelf(wxSplitterEvent) pObject);
int wxSplitterEvent_GetNewSize(TSelf(wxSplitterEvent) pObject);
TClass(wxWindow) wxSplitterEvent_GetWindowBeingRemoved(TSelf(wxSplitterEvent) pObject);
int wxSplitterEvent_GetX(TSelf(wxSplitterEvent) pObject);
int wxSplitterEvent_GetY(TSelf(wxSplitterEvent) pObject);

// ---------------------------------------------------------------------------
// wxPickerBase
// ---------------------------------------------------------------------------

// wxPickerBase is abstract (UpdatePickerFromTextCtrl and UpdateTextCtrlFromPicker
// are pure virtual) so it has no Create/Delete wrapper.
TClassDefExtend(wxPickerBase, wxControl) void wxPickerBase_SetInternalMargin(TSelf(wxPickerBase)
                                                                                 pObject,
                                                                             int margin);
int wxPickerBase_GetInternalMargin(TSelf(wxPickerBase) pObject);
void wxPickerBase_SetTextCtrlProportion(TSelf(wxPickerBase) pObject, int proportion);
int wxPickerBase_GetTextCtrlProportion(TSelf(wxPickerBase) pObject);
void wxPickerBase_SetPickerCtrlProportion(TSelf(wxPickerBase) pObject, int proportion);
int wxPickerBase_GetPickerCtrlProportion(TSelf(wxPickerBase) pObject);
TBool wxPickerBase_IsTextCtrlGrowable(TSelf(wxPickerBase) pObject);
void wxPickerBase_SetTextCtrlGrowable(TSelf(wxPickerBase) pObject, TBool grow);
TBool wxPickerBase_IsPickerCtrlGrowable(TSelf(wxPickerBase) pObject);
void wxPickerBase_SetPickerCtrlGrowable(TSelf(wxPickerBase) pObject, TBool grow);
TBool wxPickerBase_HasTextCtrl(TSelf(wxPickerBase) pObject);
TClass(wxTextCtrl) wxPickerBase_GetTextCtrl(TSelf(wxPickerBase) pObject);
TClass(wxControl) wxPickerBase_GetPickerCtrl(TSelf(wxPickerBase) pObject);

// ---------------------------------------------------------------------------
// wxEditableListBox
// ---------------------------------------------------------------------------

TClassDefExtend(wxEditableListBox, wxPanel) TClass(wxEditableListBox)
    wxEditableListBox_Create(TClass(wxWindow) parent, int id, TClass(wxString) label,
                             TRect(x, y, width, height), int style);
void wxEditableListBox_Delete(TSelf(wxEditableListBox) pObject);
void wxEditableListBox_SetStrings(TSelf(wxEditableListBox) pObject, TClass(wxArrayString) strings);
void wxEditableListBox_GetStrings(TSelf(wxEditableListBox) pObject, TClass(wxArrayString) strings);
TClass(wxListCtrl) wxEditableListBox_GetListCtrl(TSelf(wxEditableListBox) pObject);
TClass(wxBitmapButton) wxEditableListBox_GetDelButton(TSelf(wxEditableListBox) pObject);
TClass(wxBitmapButton) wxEditableListBox_GetNewButton(TSelf(wxEditableListBox) pObject);
TClass(wxBitmapButton) wxEditableListBox_GetUpButton(TSelf(wxEditableListBox) pObject);
TClass(wxBitmapButton) wxEditableListBox_GetDownButton(TSelf(wxEditableListBox) pObject);
TClass(wxBitmapButton) wxEditableListBox_GetEditButton(TSelf(wxEditableListBox) pObject);

// ---------------------------------------------------------------------------
// wxRearrangeList
// ---------------------------------------------------------------------------

TClassDefExtend(wxRearrangeList, wxCheckListBox) TClass(wxRearrangeList)
    wxRearrangeList_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                           TClass(wxArrayInt) order, TClass(wxArrayString) items, int style);
void wxRearrangeList_Delete(TSelf(wxRearrangeList) pObject);
TClass(wxArrayInt) wxRearrangeList_GetCurrentOrder(TSelf(wxRearrangeList) pObject);
TBool wxRearrangeList_CanMoveCurrentUp(TSelf(wxRearrangeList) pObject);
TBool wxRearrangeList_CanMoveCurrentDown(TSelf(wxRearrangeList) pObject);
TBool wxRearrangeList_MoveCurrentUp(TSelf(wxRearrangeList) pObject);
TBool wxRearrangeList_MoveCurrentDown(TSelf(wxRearrangeList) pObject);
void wxRearrangeList_Check(TSelf(wxRearrangeList) pObject, unsigned int item, TBool check);

// ---------------------------------------------------------------------------
// wxTipProvider
// ---------------------------------------------------------------------------

TClassDef(wxTipProvider) TClass(wxTipProvider)
    wxTipProvider_CreateFile(TClass(wxString) filename, int current_tip);
void wxTipProvider_Delete(TSelf(wxTipProvider) pObject);
TClass(wxString) wxTipProvider_GetTip(TSelf(wxTipProvider) pObject);
int wxTipProvider_GetCurrentTip(TSelf(wxTipProvider) pObject);

// ---------------------------------------------------------------------------
// wxGBSizerItem
// ---------------------------------------------------------------------------

TClassDefExtend(wxGBSizerItem, wxSizerItem) TClass(wxGBSizerItem) wxGBSizerItem_Create();
TClass(wxGBSizerItem)
    wxGBSizerItem_CreateSpacer(int width, int height, int row, int col, int rowspan, int colspan,
                               int flag, int border, TClass(wxObject) user_data);
void wxGBSizerItem_Delete(TSelf(wxGBSizerItem) pObject);
void wxGBSizerItem_GetPos(TSelf(wxGBSizerItem) pObject, int* row, int* col);
void wxGBSizerItem_SetPos(TSelf(wxGBSizerItem) pObject, int row, int col);
void wxGBSizerItem_GetSpan(TSelf(wxGBSizerItem) pObject, int* rowspan, int* colspan);
TBool wxGBSizerItem_SetSpan(TSelf(wxGBSizerItem) pObject, int rowspan, int colspan);
TBool wxGBSizerItem_Intersects(TSelf(wxGBSizerItem) pObject, TClass(wxGBSizerItem) other);
TBool wxGBSizerItem_IntersectsPos(TSelf(wxGBSizerItem) pObject, int row, int col, int rowspan,
                                  int colspan);
void wxGBSizerItem_GetEndPos(TSelf(wxGBSizerItem) pObject, int* row, int* col);
TClass(wxGridBagSizer) wxGBSizerItem_GetGBSizer(TSelf(wxGBSizerItem) pObject);
void wxGBSizerItem_SetGBSizer(TSelf(wxGBSizerItem) pObject, TClass(wxGridBagSizer) sizer);

// ---------------------------------------------------------------------------
// wxDCOverlay
// ---------------------------------------------------------------------------

// The constructors take a wxOverlay reference that outlives the overlay, so the
// wrapper keeps it opaque.
TClassDef(wxDCOverlay) TClass(wxDCOverlay)
    wxDCOverlay_Create(TClass(wxOverlay) overlay, TClass(wxDC) dc, TRect(x, y, width, height));
TClass(wxDCOverlay) wxDCOverlay_CreateFull(TClass(wxOverlay) overlay, TClass(wxDC) dc);
void wxDCOverlay_Delete(TSelf(wxDCOverlay) pObject);
void wxDCOverlay_Clear(TSelf(wxDCOverlay) pObject);

// ---------------------------------------------------------------------------
// wxAffineMatrix2D
// ---------------------------------------------------------------------------

TClassDef(wxAffineMatrix2D) TClass(wxAffineMatrix2D) wxAffineMatrix2D_Create();
void wxAffineMatrix2D_Delete(TSelf(wxAffineMatrix2D) pObject);
void wxAffineMatrix2D_Set(TSelf(wxAffineMatrix2D) pObject, double m11, double m12, double m21,
                          double m22, double tr_x, double tr_y);
void wxAffineMatrix2D_Get(TSelf(wxAffineMatrix2D) pObject, double* m11, double* m12, double* m21,
                          double* m22, double* tr_x, double* tr_y);
void wxAffineMatrix2D_Concat(TSelf(wxAffineMatrix2D) pObject, TClass(wxAffineMatrix2D) other);
TBool wxAffineMatrix2D_Invert(TSelf(wxAffineMatrix2D) pObject);
TBool wxAffineMatrix2D_IsIdentity(TSelf(wxAffineMatrix2D) pObject);
TBool wxAffineMatrix2D_IsEqual(TSelf(wxAffineMatrix2D) pObject, TClass(wxAffineMatrix2D) other);
void wxAffineMatrix2D_Translate(TSelf(wxAffineMatrix2D) pObject, double dx, double dy);
void wxAffineMatrix2D_Scale(TSelf(wxAffineMatrix2D) pObject, double x_scale, double y_scale);
void wxAffineMatrix2D_Rotate(TSelf(wxAffineMatrix2D) pObject, double radians);
void wxAffineMatrix2D_Mirror(TSelf(wxAffineMatrix2D) pObject, int direction);
void wxAffineMatrix2D_TransformPoint(TSelf(wxAffineMatrix2D) pObject, double* x, double* y);
void wxAffineMatrix2D_TransformDistance(TSelf(wxAffineMatrix2D) pObject, double* x, double* y);

// ---------------------------------------------------------------------------
// wxArtProvider
// ---------------------------------------------------------------------------

// Static provider stack and lookup functions; the instance-based
// PushProvider/PopProvider/RemoveProvider wrappers live in src/wx_artprov.cpp.
TClassDefExtend(wxArtProvider, wxObject) TClass(wxBitmap)
    wxArtProvider_GetBitmap(TClass(wxString) id, TClass(wxString) client, TSize(width, height));
TClass(wxBitmapBundle) wxArtProvider_GetBitmapBundle(TClass(wxString) id, TClass(wxString) client,
                                                     TSize(width, height));
TClass(wxIcon)
    wxArtProvider_GetIcon(TClass(wxString) id, TClass(wxString) client, TSize(width, height));
TClass(wxIconBundle) wxArtProvider_GetIconBundle(TClass(wxString) id, TClass(wxString) client);
TClass(wxSize) wxArtProvider_GetNativeSizeHint(TClass(wxString) client, TClass(wxWindow) window);
TClass(wxSize) wxArtProvider_GetSizeHint(TClass(wxString) client, TClass(wxWindow) window);
TBool wxArtProvider_HasNativeProvider();
void wxArtProvider_PushBack(TClass(wxArtProvider) provider);
TBool wxArtProvider_DeleteProvider(TClass(wxArtProvider) provider);

// ---------------------------------------------------------------------------
// wxSystemOptions
// ---------------------------------------------------------------------------

TClassDefExtend(wxSystemOptions, wxObject) void wxSystemOptions_SetOption(TClass(wxString) name,
                                                                          TClass(wxString) value);
void wxSystemOptions_SetOptionInt(TClass(wxString) name, int value);
TClass(wxString) wxSystemOptions_GetOption(TClass(wxString) name);
int wxSystemOptions_GetOptionInt(TClass(wxString) name);
TBool wxSystemOptions_HasOption(TClass(wxString) name);
TBool wxSystemOptions_IsFalse(TClass(wxString) name);

// ---------------------------------------------------------------------------
// wxSingleChoiceDialog
// ---------------------------------------------------------------------------

TClassDefExtend(wxSingleChoiceDialog, wxDialog) TClass(wxSingleChoiceDialog)
    wxSingleChoiceDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                                TClass(wxString) caption, TClass(wxArrayString) choices, int style);
void wxSingleChoiceDialog_Delete(TSelf(wxSingleChoiceDialog) pObject);
void wxSingleChoiceDialog_SetSelection(TSelf(wxSingleChoiceDialog) pObject, int selection);
int wxSingleChoiceDialog_GetSelection(TSelf(wxSingleChoiceDialog) pObject);
TClass(wxString) wxSingleChoiceDialog_GetStringSelection(TSelf(wxSingleChoiceDialog) pObject);
void* wxSingleChoiceDialog_GetSelectionData(TSelf(wxSingleChoiceDialog) pObject);

// ---------------------------------------------------------------------------
// wxHelpController
// ---------------------------------------------------------------------------

// wxHelpController is a platform alias (wxCHMHelpController on MSW,
// wxHtmlHelpController elsewhere), so only the inherited base surface is wrapped
// and no platform-specific constructor is declared.
TClassDefExtend(wxHelpController, wxHelpControllerBase) TBool
    wxHelpController_Initialize(TSelf(wxHelpController) pObject, TClass(wxString) file);
TBool wxHelpController_LoadFile(TSelf(wxHelpController) pObject, TClass(wxString) file);
TBool wxHelpController_DisplayContents(TSelf(wxHelpController) pObject);
TBool wxHelpController_DisplaySection(TSelf(wxHelpController) pObject, int section);
TBool wxHelpController_DisplaySectionName(TSelf(wxHelpController) pObject,
                                          TClass(wxString) section);
TBool wxHelpController_DisplayBlock(TSelf(wxHelpController) pObject, int block);
TBool wxHelpController_KeywordSearch(TSelf(wxHelpController) pObject, TClass(wxString) keyword,
                                     int mode);
TBool wxHelpController_Quit(TSelf(wxHelpController) pObject);
TClass(wxWindow) wxHelpController_GetParentWindow(TSelf(wxHelpController) pObject);
void wxHelpController_SetParentWindow(TSelf(wxHelpController) pObject, TClass(wxWindow) window);

// ---------------------------------------------------------------------------
// wxWizardPage
// ---------------------------------------------------------------------------

// wxWizardPage is abstract (GetPrev and GetNext are pure virtual) so it has no
// Create wrapper; the accessors work on the wrapped wxWizardPageSimple objects.
TClassDefExtend(wxWizardPage, wxPanel) TClass(wxWizardPage)
    wxWizardPage_GetPrev(TSelf(wxWizardPage) pObject);
TClass(wxWizardPage) wxWizardPage_GetNext(TSelf(wxWizardPage) pObject);
TClass(wxBitmap) wxWizardPage_GetBitmap(TSelf(wxWizardPage) pObject);

// ---------------------------------------------------------------------------
// wxMDIClientWindow
// ---------------------------------------------------------------------------

TClassDefExtend(wxMDIClientWindow, wxWindow) TClass(wxMDIClientWindow) wxMDIClientWindow_Create();
void wxMDIClientWindow_Delete(TSelf(wxMDIClientWindow) pObject);
TBool wxMDIClientWindow_CreateClient(TSelf(wxMDIClientWindow) pObject,
                                     TClass(wxMDIParentFrame) parent, int style);

// ---------------------------------------------------------------------------
// wxGridTableBase
// ---------------------------------------------------------------------------

// Abstract (GetNumberRows, GetNumberCols, GetValue and SetValue are pure
// virtual) so it has no Create/Delete wrapper; the methods dispatch on the
// wrapped wxGridStringTable instances.
TClassDefExtend(wxGridTableBase,
                wxObject) int wxGridTableBase_GetNumberRows(TSelf(wxGridTableBase) pObject);
int wxGridTableBase_GetNumberCols(TSelf(wxGridTableBase) pObject);
int wxGridTableBase_GetRowsCount(TSelf(wxGridTableBase) pObject);
int wxGridTableBase_GetColsCount(TSelf(wxGridTableBase) pObject);
TBool wxGridTableBase_IsEmptyCell(TSelf(wxGridTableBase) pObject, int row, int col);
TClass(wxString) wxGridTableBase_GetValue(TSelf(wxGridTableBase) pObject, int row, int col);
void wxGridTableBase_SetValue(TSelf(wxGridTableBase) pObject, int row, int col,
                              TClass(wxString) value);
TClass(wxString) wxGridTableBase_GetTypeName(TSelf(wxGridTableBase) pObject, int row, int col);
TBool wxGridTableBase_CanGetValueAs(TSelf(wxGridTableBase) pObject, int row, int col,
                                    TClass(wxString) type_name);
TBool wxGridTableBase_CanSetValueAs(TSelf(wxGridTableBase) pObject, int row, int col,
                                    TClass(wxString) type_name);
long wxGridTableBase_GetValueAsLong(TSelf(wxGridTableBase) pObject, int row, int col);
double wxGridTableBase_GetValueAsDouble(TSelf(wxGridTableBase) pObject, int row, int col);
TBool wxGridTableBase_GetValueAsBool(TSelf(wxGridTableBase) pObject, int row, int col);
void wxGridTableBase_SetValueAsLong(TSelf(wxGridTableBase) pObject, int row, int col, long value);
void wxGridTableBase_SetValueAsDouble(TSelf(wxGridTableBase) pObject, int row, int col,
                                      double value);
void wxGridTableBase_SetValueAsBool(TSelf(wxGridTableBase) pObject, int row, int col, TBool value);
TClass(wxGrid) wxGridTableBase_GetView(TSelf(wxGridTableBase) pObject);
void wxGridTableBase_SetView(TSelf(wxGridTableBase) pObject, TClass(wxGrid) grid);
void wxGridTableBase_Clear(TSelf(wxGridTableBase) pObject);
TBool wxGridTableBase_InsertRows(TSelf(wxGridTableBase) pObject, int pos, int num_rows);
TBool wxGridTableBase_AppendRows(TSelf(wxGridTableBase) pObject, int num_rows);
TBool wxGridTableBase_DeleteRows(TSelf(wxGridTableBase) pObject, int pos, int num_rows);
TBool wxGridTableBase_InsertCols(TSelf(wxGridTableBase) pObject, int pos, int num_cols);
TBool wxGridTableBase_AppendCols(TSelf(wxGridTableBase) pObject, int num_cols);
TBool wxGridTableBase_DeleteCols(TSelf(wxGridTableBase) pObject, int pos, int num_cols);
TClass(wxString) wxGridTableBase_GetRowLabelValue(TSelf(wxGridTableBase) pObject, int row);
TClass(wxString) wxGridTableBase_GetColLabelValue(TSelf(wxGridTableBase) pObject, int col);
void wxGridTableBase_SetRowLabelValue(TSelf(wxGridTableBase) pObject, int row,
                                      TClass(wxString) label);
void wxGridTableBase_SetColLabelValue(TSelf(wxGridTableBase) pObject, int col,
                                      TClass(wxString) label);
TClass(wxString) wxGridTableBase_GetCornerLabelValue(TSelf(wxGridTableBase) pObject);
void wxGridTableBase_SetCornerLabelValue(TSelf(wxGridTableBase) pObject, TClass(wxString) label);
TBool wxGridTableBase_CanHaveAttributes(TSelf(wxGridTableBase) pObject);

// ---------------------------------------------------------------------------
// Grid cell renderers
// ---------------------------------------------------------------------------

// wxGridCellRenderer is abstract (Draw is pure virtual) so it has no Create
// wrapper; the accessors dispatch on the wrapped renderer instances.
TClassDefExtend(wxGridCellRenderer, wxGridCellWorker) void wxGridCellRenderer_Draw(
    TSelf(wxGridCellRenderer) pObject, TClass(wxGrid) grid, TClass(wxGridCellAttr) attr,
    TClass(wxDC) dc, TRect(x, y, width, height), int row, int col, TBool is_selected);
TClass(wxSize) wxGridCellRenderer_GetPreferredSize(TSelf(wxGridCellRenderer) pObject,
                                                   TClass(wxGrid) grid, TClass(wxGridCellAttr) attr,
                                                   TClass(wxDC) dc, int row, int col);
int wxGridCellRenderer_GetPreferredHeight(TSelf(wxGridCellRenderer) pObject, TClass(wxGrid) grid,
                                          TClass(wxGridCellAttr) attr, TClass(wxDC) dc, int row,
                                          int col, int width);
int wxGridCellRenderer_GetPreferredWidth(TSelf(wxGridCellRenderer) pObject, TClass(wxGrid) grid,
                                         TClass(wxGridCellAttr) attr, TClass(wxDC) dc, int row,
                                         int col, int height);

TClassDefExtend(wxGridCellBoolRenderer, wxGridCellRenderer) void wxGridCellBoolRenderer_Draw(
    TSelf(wxGridCellBoolRenderer) pObject, TClass(wxGrid) grid, TClass(wxGridCellAttr) attr,
    TClass(wxDC) dc, TRect(x, y, width, height), int row, int col, TBool is_selected);
TClass(wxSize)
    wxGridCellBoolRenderer_GetPreferredSize(TSelf(wxGridCellBoolRenderer) pObject,
                                            TClass(wxGrid) grid, TClass(wxGridCellAttr) attr,
                                            TClass(wxDC) dc, int row, int col);
TClass(wxSize) wxGridCellBoolRenderer_GetMaxBestSize(TSelf(wxGridCellBoolRenderer) pObject,
                                                     TClass(wxGrid) grid,
                                                     TClass(wxGridCellAttr) attr, TClass(wxDC) dc);

TClassDefExtend(wxGridCellStringRenderer, wxGridCellRenderer) void wxGridCellStringRenderer_Draw(
    TSelf(wxGridCellStringRenderer) pObject, TClass(wxGrid) grid, TClass(wxGridCellAttr) attr,
    TClass(wxDC) dc, TRect(x, y, width, height), int row, int col, TBool is_selected);
TClass(wxSize)
    wxGridCellStringRenderer_GetPreferredSize(TSelf(wxGridCellStringRenderer) pObject,
                                              TClass(wxGrid) grid, TClass(wxGridCellAttr) attr,
                                              TClass(wxDC) dc, int row, int col);

TClassDefExtend(wxGridCellFloatRenderer, wxGridCellStringRenderer) TClass(wxGridCellFloatRenderer)
    wxGridCellFloatRenderer_Create(int width, int precision, int format);
void wxGridCellFloatRenderer_Delete(TSelf(wxGridCellFloatRenderer) pObject);
int wxGridCellFloatRenderer_GetWidth(TSelf(wxGridCellFloatRenderer) pObject);
void wxGridCellFloatRenderer_SetWidth(TSelf(wxGridCellFloatRenderer) pObject, int width);
int wxGridCellFloatRenderer_GetPrecision(TSelf(wxGridCellFloatRenderer) pObject);
void wxGridCellFloatRenderer_SetPrecision(TSelf(wxGridCellFloatRenderer) pObject, int precision);
int wxGridCellFloatRenderer_GetFormat(TSelf(wxGridCellFloatRenderer) pObject);
void wxGridCellFloatRenderer_SetFormat(TSelf(wxGridCellFloatRenderer) pObject, int format);
void wxGridCellFloatRenderer_SetParameters(TSelf(wxGridCellFloatRenderer) pObject,
                                           TClass(wxString) params);

// ---------------------------------------------------------------------------
// wxVariant (limited to the value types wxRuby3 exposes)
// ---------------------------------------------------------------------------

TClassDefExtend(wxVariant, wxObject) TClass(wxVariant) wxVariant_Create();
void wxVariant_Delete(TSelf(wxVariant) pObject);
TClass(wxString) wxVariant_GetType(TSelf(wxVariant) pObject);
TClass(wxString) wxVariant_MakeString(TSelf(wxVariant) pObject);
TClass(wxString) wxVariant_GetString(TSelf(wxVariant) pObject);
TBool wxVariant_GetBool(TSelf(wxVariant) pObject);
long wxVariant_GetLong(TSelf(wxVariant) pObject);
double wxVariant_GetDouble(TSelf(wxVariant) pObject);

// ---------------------------------------------------------------------------
// wxDataObject
// ---------------------------------------------------------------------------

// Abstract (every wxDataObjectBase format function is pure virtual), so it has
// no Create/Delete wrapper. direction is wxDataObjectBase::Direction.
TClassDef(wxDataObject) TClass(wxDataFormat)
    wxDataObject_GetPreferredFormat(TSelf(wxDataObject) pObject, int direction);
int wxDataObject_GetFormatCount(TSelf(wxDataObject) pObject, int direction);
TBool wxDataObject_IsSupported(TSelf(wxDataObject) pObject, TClass(wxDataFormat) format,
                               int direction);
size_t wxDataObject_GetDataSize(TSelf(wxDataObject) pObject, TClass(wxDataFormat) format);
TBool wxDataObject_GetDataHere(TSelf(wxDataObject) pObject, TClass(wxDataFormat) format,
                               void* buffer);
TBool wxDataObject_SetData(TSelf(wxDataObject) pObject, TClass(wxDataFormat) format, int length,
                           void* buffer);

// ---------------------------------------------------------------------------
// wxPGProperty
// ---------------------------------------------------------------------------

// wxPGProperty is abstract and its constructors are protected, so it has no
// Create/Delete wrapper; the accessors dispatch on the wrapped typed
// properties. GetLabel, GetName, GetValueAsString, GetValueType and
// SetHelpString are declared in include/kwx_classes.h.
TClassDefExtend(wxPGProperty, wxObject) TClass(wxString)
    wxPGProperty_GetBaseName(TSelf(wxPGProperty) pObject);
int wxPGProperty_GetY(TSelf(wxPGProperty) pObject);
TClass(wxVariant) wxPGProperty_GetValue(TSelf(wxPGProperty) pObject);
TClass(wxString) wxPGProperty_GetHintText(TSelf(wxPGProperty) pObject);
TClass(wxPropertyGrid) wxPGProperty_GetGrid(TSelf(wxPGProperty) pObject);
TClass(wxPropertyGrid) wxPGProperty_GetGridIfDisplayed(TSelf(wxPGProperty) pObject);
TClass(wxPGProperty) wxPGProperty_GetMainParent(TSelf(wxPGProperty) pObject);
TClass(wxPGProperty) wxPGProperty_GetParent(TSelf(wxPGProperty) pObject);
TClass(wxPGProperty) wxPGProperty_Item(TSelf(wxPGProperty) pObject, unsigned int index);
int wxPGProperty_GetChildCount(TSelf(wxPGProperty) pObject);
int wxPGProperty_GetChoiceSelection(TSelf(wxPGProperty) pObject);
void wxPGProperty_SetChoiceSelection(TSelf(wxPGProperty) pObject, int selection);
void wxPGProperty_Enable(TSelf(wxPGProperty) pObject, TBool enable);
TBool wxPGProperty_AreChildrenComponents(TSelf(wxPGProperty) pObject);
int wxPGProperty_GetDisplayedCommonValueCount(TSelf(wxPGProperty) pObject);
void wxPGProperty_SetLabel(TSelf(wxPGProperty) pObject, TClass(wxString) label);
void wxPGProperty_SetName(TSelf(wxPGProperty) pObject, TClass(wxString) name);

// ---------------------------------------------------------------------------
// wxPropertyGrid
// ---------------------------------------------------------------------------

// Only the property-value members that wxPropertyGridInterface does not
// declare in include/kwx_propgrid_extra.h.
TClassDefExtend(wxPropertyGrid, wxControl) TClass(wxVariant)
    wxPropertyGrid_GetPropertyValue(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id);
void wxPropertyGrid_SetPropertyValue(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id,
                                     TClass(wxVariant) value);
void wxPropertyGrid_SetPropertyValueUnspecified(TSelf(wxPropertyGrid) pObject,
                                                TClass(wxPGProperty) id);
TClass(wxString)
    wxPropertyGrid_GetPropertyHelpString(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id);
void wxPropertyGrid_SetPropertyHelpString(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id,
                                          TClass(wxString) help);
TBool wxPropertyGrid_IsPropertyModified(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) id);
TClass(wxVariant) wxPropertyGrid_GetUncommittedPropertyValue(TSelf(wxPropertyGrid) pObject);

// ---------------------------------------------------------------------------
// wxPrintAbortDialog
// ---------------------------------------------------------------------------

TClassDefExtend(wxPrintAbortDialog, wxDialog) TClass(wxPrintAbortDialog)
    wxPrintAbortDialog_Create(TClass(wxWindow) parent, TClass(wxString) document_title,
                              TRect(x, y, width, height), int style);
void wxPrintAbortDialog_Delete(TSelf(wxPrintAbortDialog) pObject);
void wxPrintAbortDialog_SetProgress(TSelf(wxPrintAbortDialog) pObject, int current_page,
                                    int total_pages, int current_copy, int total_copies);
