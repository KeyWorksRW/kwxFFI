#pragma once

// Wx::RTC declarations (Phase 5).
// Implementations live in:
//   src/wx_richtext.cpp        - object hierarchy, buffer operations, file handlers
//   src/wx_richtextctrl.cpp    - wxRichTextCtrl additions and wxRichTextEvent
//   src/wx_richtextdlg.cpp     - symbol picker, formatting dialog, style organiser
//   src/wx_richtextprint.cpp   - header/footer data and printing
//   src/wx_richtextstyles.cpp  - style list box and buffer data object
// kwxgen merges these blocks with the existing wxRichTextCtrl block in kwx_classes.h.

// Attribute and style classes that appear in the rich-text signatures below but have no
// wrapper block of their own.
// clang-format off
TClassDefExtend(wxRichTextAttr, wxTextAttr)
TClassDefExtend(wxRichTextProperties, wxObject)
TClassDefExtend(wxRichTextStyleDefinition, wxObject)
TClassDefExtend(wxRichTextStyleSheet, wxObject)

// wxRichTextAttr must be constructible: it is the real argument type of the rich-text
// attribute methods (BeginStyle, WriteTextBox, GetBasicStyle, ...). Without a constructor
// the bindings only exposed wxTextAttr, and passing one where a wxRichTextAttr is expected
// is undefined behaviour (heap corruption) instead of a compile-time type error.
TClass(wxRichTextAttr) wxRichTextAttr_Create();
TClass(wxRichTextAttr) wxRichTextAttr_CreateFromTextAttr(TClass(wxTextAttr) attr);
TClass(wxRichTextAttr) wxRichTextAttr_CreateCopy(TClass(wxRichTextAttr) attr);
void wxRichTextAttr_Delete(TSelf(wxRichTextAttr) self);
void wxRichTextAttr_Copy(TSelf(wxRichTextAttr) self, TClass(wxRichTextAttr) attr);
TClass(wxTextBoxAttr) wxRichTextAttr_GetTextBoxAttr(TSelf(wxRichTextAttr) self);
void wxRichTextAttr_SetTextBoxAttr(TSelf(wxRichTextAttr) self, TClass(wxTextBoxAttr) attr);
TBool wxRichTextAttr_HasTextBoxAttr(TSelf(wxRichTextAttr) self);

// ---- wxRichTextProperties ----
TClass(wxRichTextProperties) wxRichTextProperties_Create();
TClass(wxRichTextProperties) wxRichTextProperties_CreateCopy(TClass(wxRichTextProperties) props);
void wxRichTextProperties_Delete(TSelf(wxRichTextProperties) self);
void wxRichTextProperties_Copy(TSelf(wxRichTextProperties) self, TClass(wxRichTextProperties) props);
void wxRichTextProperties_Clear(TSelf(wxRichTextProperties) self);
size_t wxRichTextProperties_GetCount(TSelf(wxRichTextProperties) self);
TBool wxRichTextProperties_HasProperty(TSelf(wxRichTextProperties) self, TClass(wxString) name);
int wxRichTextProperties_Find(TSelf(wxRichTextProperties) self, TClass(wxString) name);
TBool wxRichTextProperties_Remove(TSelf(wxRichTextProperties) self, TClass(wxString) name);
TClass(wxString) wxRichTextProperties_GetPropertyString(TSelf(wxRichTextProperties) self,
                                                      TClass(wxString) name);
long wxRichTextProperties_GetPropertyLong(TSelf(wxRichTextProperties) self,
                                          TClass(wxString) name);
TBool wxRichTextProperties_GetPropertyBool(TSelf(wxRichTextProperties) self,
                                           TClass(wxString) name);
double wxRichTextProperties_GetPropertyDouble(TSelf(wxRichTextProperties) self,
                                              TClass(wxString) name);
void wxRichTextProperties_SetPropertyString(TSelf(wxRichTextProperties) self,
                                            TClass(wxString) name, TClass(wxString) value);
void wxRichTextProperties_SetPropertyLong(TSelf(wxRichTextProperties) self, TClass(wxString) name,
                                          long value);
void wxRichTextProperties_SetPropertyBool(TSelf(wxRichTextProperties) self, TClass(wxString) name,
                                          TBool value);
void wxRichTextProperties_SetPropertyDouble(TSelf(wxRichTextProperties) self,
                                            TClass(wxString) name, double value);
TClassOwned(wxArrayString) wxRichTextProperties_GetPropertyNames(TSelf(wxRichTextProperties) self);
void wxRichTextProperties_RemoveProperties(TSelf(wxRichTextProperties) self,
                                           TClass(wxRichTextProperties) props);
void wxRichTextProperties_MergeProperties(TSelf(wxRichTextProperties) self,
                                          TClass(wxRichTextProperties) props);

// Text-box attribute classes. Every TClass return is a borrowed subobject of the
// object it was obtained from -- callers must never delete it.
TClassDef(wxTextAttrDimension)
void wxTextAttrDimension_Reset(TSelf(wxTextAttrDimension) self);
int wxTextAttrDimension_GetValue(TSelf(wxTextAttrDimension) self);
void wxTextAttrDimension_SetValue(TSelf(wxTextAttrDimension) self, int value);
void wxTextAttrDimension_SetValueWithUnits(TSelf(wxTextAttrDimension) self, int value, int units);
int wxTextAttrDimension_GetUnits(TSelf(wxTextAttrDimension) self);
void wxTextAttrDimension_SetUnits(TSelf(wxTextAttrDimension) self, int units);
TBool wxTextAttrDimension_IsValid(TSelf(wxTextAttrDimension) self);

TClassDef(wxTextAttrDimensions)
void wxTextAttrDimensions_Reset(TSelf(wxTextAttrDimensions) self);
TClass(wxTextAttrDimension) wxTextAttrDimensions_GetLeft(TSelf(wxTextAttrDimensions) self);
TClass(wxTextAttrDimension) wxTextAttrDimensions_GetTop(TSelf(wxTextAttrDimensions) self);
TClass(wxTextAttrDimension) wxTextAttrDimensions_GetRight(TSelf(wxTextAttrDimensions) self);
TClass(wxTextAttrDimension) wxTextAttrDimensions_GetBottom(TSelf(wxTextAttrDimensions) self);
TBool wxTextAttrDimensions_IsValid(TSelf(wxTextAttrDimensions) self);

TClassDef(wxTextAttrBorder)
void wxTextAttrBorder_Reset(TSelf(wxTextAttrBorder) self);
void wxTextAttrBorder_SetStyle(TSelf(wxTextAttrBorder) self, int style);
int wxTextAttrBorder_GetStyle(TSelf(wxTextAttrBorder) self);
void wxTextAttrBorder_SetColour(TSelf(wxTextAttrBorder) self, TClass(wxColour) colour);
void wxTextAttrBorder_GetColour(TSelf(wxTextAttrBorder) self, TClass(wxColour) colour);
void wxTextAttrBorder_SetColourLong(TSelf(wxTextAttrBorder) self, unsigned long colour);
unsigned long wxTextAttrBorder_GetColourLong(TSelf(wxTextAttrBorder) self);
void wxTextAttrBorder_SetWidth(TSelf(wxTextAttrBorder) self, int value, int units);
TClass(wxTextAttrDimension) wxTextAttrBorder_GetWidth(TSelf(wxTextAttrBorder) self);
TBool wxTextAttrBorder_HasStyle(TSelf(wxTextAttrBorder) self);
TBool wxTextAttrBorder_HasColour(TSelf(wxTextAttrBorder) self);
TBool wxTextAttrBorder_HasWidth(TSelf(wxTextAttrBorder) self);
TBool wxTextAttrBorder_IsDefault(TSelf(wxTextAttrBorder) self);

TClassDef(wxTextAttrBorders)
void wxTextAttrBorders_Reset(TSelf(wxTextAttrBorders) self);
void wxTextAttrBorders_SetStyle(TSelf(wxTextAttrBorders) self, int style);
void wxTextAttrBorders_SetColour(TSelf(wxTextAttrBorders) self, TClass(wxColour) colour);
void wxTextAttrBorders_SetColourLong(TSelf(wxTextAttrBorders) self, unsigned long colour);
void wxTextAttrBorders_SetWidth(TSelf(wxTextAttrBorders) self, int value, int units);
TClass(wxTextAttrBorder) wxTextAttrBorders_GetLeft(TSelf(wxTextAttrBorders) self);
TClass(wxTextAttrBorder) wxTextAttrBorders_GetTop(TSelf(wxTextAttrBorders) self);
TClass(wxTextAttrBorder) wxTextAttrBorders_GetRight(TSelf(wxTextAttrBorders) self);
TClass(wxTextAttrBorder) wxTextAttrBorders_GetBottom(TSelf(wxTextAttrBorders) self);
TBool wxTextAttrBorders_IsValid(TSelf(wxTextAttrBorders) self);
TBool wxTextAttrBorders_IsDefault(TSelf(wxTextAttrBorders) self);

TClassDef(wxTextBoxAttr)
void wxTextBoxAttr_Reset(TSelf(wxTextBoxAttr) self);
TBool wxTextBoxAttr_IsDefault(TSelf(wxTextBoxAttr) self);
void wxTextBoxAttr_SetFlags(TSelf(wxTextBoxAttr) self, int flags);
int wxTextBoxAttr_GetFlags(TSelf(wxTextBoxAttr) self);
TBool wxTextBoxAttr_HasFlag(TSelf(wxTextBoxAttr) self, int flag);
void wxTextBoxAttr_AddFlag(TSelf(wxTextBoxAttr) self, int flag);
void wxTextBoxAttr_RemoveFlag(TSelf(wxTextBoxAttr) self, int flag);
void wxTextBoxAttr_SetFloatMode(TSelf(wxTextBoxAttr) self, int mode);
int wxTextBoxAttr_GetFloatMode(TSelf(wxTextBoxAttr) self);
TBool wxTextBoxAttr_IsFloating(TSelf(wxTextBoxAttr) self);
void wxTextBoxAttr_SetClearMode(TSelf(wxTextBoxAttr) self, int mode);
int wxTextBoxAttr_GetClearMode(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrDimensions) wxTextBoxAttr_GetMargins(TSelf(wxTextBoxAttr) self);
void wxTextBoxAttr_SetMargins(TSelf(wxTextBoxAttr) self, TClass(wxTextAttrDimensions) margins);
TClass(wxTextAttrDimensions) wxTextBoxAttr_GetPadding(TSelf(wxTextBoxAttr) self);
void wxTextBoxAttr_SetPadding(TSelf(wxTextBoxAttr) self, TClass(wxTextAttrDimensions) padding);
TClass(wxTextAttrBorders) wxTextBoxAttr_GetBorder(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrBorder) wxTextBoxAttr_GetLeftBorder(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrBorder) wxTextBoxAttr_GetTopBorder(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrBorder) wxTextBoxAttr_GetRightBorder(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrBorder) wxTextBoxAttr_GetBottomBorder(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrDimension) wxTextBoxAttr_GetWidth(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrDimension) wxTextBoxAttr_GetHeight(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrDimension) wxTextBoxAttr_GetLeft(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrDimension) wxTextBoxAttr_GetTop(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrDimension) wxTextBoxAttr_GetRight(TSelf(wxTextBoxAttr) self);
TClass(wxTextAttrDimension) wxTextBoxAttr_GetBottom(TSelf(wxTextBoxAttr) self);
TClass(wxString) wxTextBoxAttr_GetBoxStyleName(TSelf(wxTextBoxAttr) self);
void wxTextBoxAttr_SetBoxStyleName(TSelf(wxTextBoxAttr) self, TClass(wxString) name);

TClassDefExtend(wxRichTextObject, wxObject)

    TClass(wxRichTextObject) wxRichTextObject_GetParent(TSelf(wxRichTextObject) self);
// clang-format on
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
// Borrowed subobject of the object -- never delete the returned pointer. Mutating it
// mutates the object (e.g. SetPropertyLong("Lock", id) as in the richtext sample).
TClass(wxRichTextProperties) wxRichTextObject_GetProperties(TSelf(wxRichTextObject) pObject);
TClass(wxRichTextObject) wxRichTextObject_GetFirstChild(TSelf(wxRichTextObject) self);
TClass(wxRichTextObject) wxRichTextObject_GetNextSibling(TSelf(wxRichTextObject) self);
void wxRichTextObject_GetPosition(TSelf(wxRichTextObject) self, TPointOut(x, y));
void wxRichTextObject_SetPosition(TSelf(wxRichTextObject) self, TPoint(x, y));
void wxRichTextObject_GetSize(TSelf(wxRichTextObject) self, TSizeOut(w, h));
void wxRichTextObject_SetSize(TSelf(wxRichTextObject) self, TSize(w, h));
void wxRichTextObject_GetRect(TSelf(wxRichTextObject) self, TRectOut(x, y, w, h));
void wxRichTextObject_GetRange(TSelf(wxRichTextObject) self, TLongOut start, TLongOut end);
void wxRichTextObject_SetRange(TSelf(wxRichTextObject) self, long start, long end);
void wxRichTextObject_GetAttributes(TSelf(wxRichTextObject) self, TClass(wxRichTextAttr) attr);
void wxRichTextObject_SetAttributes(TSelf(wxRichTextObject) self, TClass(wxRichTextAttr) attr);
TClass(wxString) wxRichTextObject_GetName(TSelf(wxRichTextObject) self);
void wxRichTextObject_SetName(TSelf(wxRichTextObject) self, TClass(wxString) name);
TClass(wxString)
    wxRichTextObject_GetTextForRange(TSelf(wxRichTextObject) self, long start, long end);
TBool wxRichTextObject_IsComposite(TSelf(wxRichTextObject) self);
TBool wxRichTextObject_IsEmpty(TSelf(wxRichTextObject) self);
TBool wxRichTextObject_IsTopLevel(TSelf(wxRichTextObject) self);
TBool wxRichTextObject_IsShown(TSelf(wxRichTextObject) self);
void wxRichTextObject_Show(TSelf(wxRichTextObject) self, TBool show);
void wxRichTextObject_Delete(TSelf(wxRichTextObject) self);

TClassDefExtend(wxRichTextCompositeObject, wxRichTextObject)

    size_t wxRichTextCompositeObject_GetChildCount(TSelf(wxRichTextCompositeObject) self);
TClass(wxRichTextObject)
    wxRichTextCompositeObject_GetChild(TSelf(wxRichTextCompositeObject) self, size_t index);
TClass(wxRichTextObject)
    wxRichTextCompositeObject_GetChildAtPosition(TSelf(wxRichTextCompositeObject) self,
                                                 long position);
size_t wxRichTextCompositeObject_AppendChild(TSelf(wxRichTextCompositeObject) self,
                                             TClass(wxRichTextObject) child);
TBool wxRichTextCompositeObject_InsertChild(TSelf(wxRichTextCompositeObject) self,
                                            TClass(wxRichTextObject) child,
                                            TClass(wxRichTextObject) inFrontOf);
TBool wxRichTextCompositeObject_RemoveChild(TSelf(wxRichTextCompositeObject) self,
                                            TClass(wxRichTextObject) child, TBool deleteChild);
TBool wxRichTextCompositeObject_DeleteChildren(TSelf(wxRichTextCompositeObject) self);
void wxRichTextCompositeObject_Delete(TSelf(wxRichTextCompositeObject) self);

TClassDefExtend(wxRichTextParagraphLayoutBox, wxRichTextCompositeObject)

    TClass(wxRichTextParagraphLayoutBox)
        wxRichTextParagraphLayoutBox_Create(TClass(wxRichTextObject) parent);
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
void* wxRichTextParagraphLayoutBox_GetLeafObjectAtPosition(TSelf(wxRichTextParagraphLayoutBox)
                                                               pObject,
                                                           long position);
void wxRichTextParagraphLayoutBox_Delete(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_Clear(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_Reset(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_AddParagraph(TSelf(wxRichTextParagraphLayoutBox) self,
                                               TClass(wxString) text,
                                               TClass(wxRichTextAttr) paraStyle, TLongOut start,
                                               TLongOut end);
void wxRichTextParagraphLayoutBox_AddParagraphs(TSelf(wxRichTextParagraphLayoutBox) self,
                                                TClass(wxString) text,
                                                TClass(wxRichTextAttr) paraStyle, TLongOut start,
                                                TLongOut end);
void wxRichTextParagraphLayoutBox_AddImage(TSelf(wxRichTextParagraphLayoutBox) self,
                                           TClass(wxImage) image, TClass(wxRichTextAttr) paraStyle,
                                           TLongOut start, TLongOut end);
TClass(wxString) wxRichTextParagraphLayoutBox_GetText(TSelf(wxRichTextParagraphLayoutBox) self);
TBool wxRichTextParagraphLayoutBox_DeleteRange(TSelf(wxRichTextParagraphLayoutBox) self, long start,
                                               long end);
TBool wxRichTextParagraphLayoutBox_SetStyle(TSelf(wxRichTextParagraphLayoutBox) self, long start,
                                            long end, TClass(wxRichTextAttr) style, int flags);
TBool wxRichTextParagraphLayoutBox_GetStyle(TSelf(wxRichTextParagraphLayoutBox) self, long position,
                                            TClass(wxRichTextAttr) style);
TBool wxRichTextParagraphLayoutBox_GetUncombinedStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                      long position, TClass(wxRichTextAttr) style);
int wxRichTextParagraphLayoutBox_GetParagraphCount(TSelf(wxRichTextParagraphLayoutBox) self);
TClass(wxString)
    wxRichTextParagraphLayoutBox_GetParagraphText(TSelf(wxRichTextParagraphLayoutBox) self,
                                                  long paragraphNumber);
int wxRichTextParagraphLayoutBox_GetParagraphLength(TSelf(wxRichTextParagraphLayoutBox) self,
                                                    long paragraphNumber);
long wxRichTextParagraphLayoutBox_XYToPosition(TSelf(wxRichTextParagraphLayoutBox) self, long x,
                                               long y);
TBool wxRichTextParagraphLayoutBox_PositionToXY(TSelf(wxRichTextParagraphLayoutBox) self,
                                                long position, TPointOutLong(x, y));
TBool wxRichTextParagraphLayoutBox_SetDefaultStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                   TClass(wxRichTextAttr) style);
void wxRichTextParagraphLayoutBox_GetDefaultStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                  TClass(wxRichTextAttr) style);
void wxRichTextParagraphLayoutBox_SetBasicStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                TClass(wxRichTextAttr) style);
void wxRichTextParagraphLayoutBox_GetBasicStyle(TSelf(wxRichTextParagraphLayoutBox) self,
                                                TClass(wxRichTextAttr) style);
TClass(wxRichTextStyleSheet)
    wxRichTextParagraphLayoutBox_GetStyleSheet(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_SetRichTextCtrl(TSelf(wxRichTextParagraphLayoutBox) self,
                                                  TClass(wxRichTextCtrl) ctrl);
TClass(wxRichTextCtrl)
    wxRichTextParagraphLayoutBox_GetRichTextCtrl(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_SetPartialParagraph(TSelf(wxRichTextParagraphLayoutBox) self,
                                                      TBool partialParagraph);
TBool wxRichTextParagraphLayoutBox_GetPartialParagraph(TSelf(wxRichTextParagraphLayoutBox) self);
void wxRichTextParagraphLayoutBox_UpdateRanges(TSelf(wxRichTextParagraphLayoutBox) self);
TClass(wxRichTextBuffer)
    wxRichTextParagraphLayoutBox_GetBuffer(TSelf(wxRichTextParagraphLayoutBox) self);

TClassDefExtend(wxRichTextBox, wxRichTextParagraphLayoutBox)

    TClass(wxRichTextBox) wxRichTextBox_Create(TClass(wxRichTextObject) parent);
void wxRichTextBox_Delete(TSelf(wxRichTextBox) self);
TClass(wxString) wxRichTextBox_GetXMLNodeName(TSelf(wxRichTextBox) self);

// wxRichTextTable is the real return type of wxRichTextCtrl::WriteTable, so it needs a
// wrapper block of its own for the typed return to resolve in every backend.
TClassDefExtend(wxRichTextTable, wxRichTextBox)

    TClass(wxRichTextTable) wxRichTextTable_Create(TClass(wxRichTextObject) parent);
void wxRichTextTable_Delete(TSelf(wxRichTextTable) self);
int wxRichTextTable_GetRowCount(TSelf(wxRichTextTable) self);
void wxRichTextTable_SetRowCount(TSelf(wxRichTextTable) self, int count);
int wxRichTextTable_GetColumnCount(TSelf(wxRichTextTable) self);
void wxRichTextTable_SetColumnCount(TSelf(wxRichTextTable) self, int count);
// GetCell(row, col) and GetCell(pos) are overloads of one C++ name; they get distinct C
// names below (GetCell / GetCellAtPosition).
TClass(wxRichTextCell) wxRichTextTable_GetCell(TSelf(wxRichTextTable) self, int row, int col);
TClass(wxRichTextCell) wxRichTextTable_GetCellAtPosition(TSelf(wxRichTextTable) self, long pos);
TBool wxRichTextTable_GetCellRowColumnPosition(TSelf(wxRichTextTable) self, long pos,
                                               TPointOut(row, col));
void wxRichTextTable_GetFocusedCell(TSelf(wxRichTextTable) self, TPointOut(row, col));
void wxRichTextTable_ClearTable(TSelf(wxRichTextTable) self);
TBool wxRichTextTable_CreateTable(TSelf(wxRichTextTable) self, int rows, int cols);
TBool wxRichTextTable_DeleteRows(TSelf(wxRichTextTable) self, int startRow, int noRows);
TBool wxRichTextTable_DeleteColumns(TSelf(wxRichTextTable) self, int startCol, int noCols);
TBool wxRichTextTable_AddRows(TSelf(wxRichTextTable) self, int startRow, int noRows,
                              TClass(wxRichTextAttr) attr);
TBool wxRichTextTable_AddColumns(TSelf(wxRichTextTable) self, int startCol, int noCols,
                                 TClass(wxRichTextAttr) attr);
void wxRichTextTable_Copy(TSelf(wxRichTextTable) self, TClass(wxRichTextTable) obj);

// wxRichTextCell is what wxRichTextTable::GetCell returns, so it needs its own block.
// Clear() comes from wxRichTextParagraphLayoutBox and is already bound there.
TClassDefExtend(wxRichTextCell, wxRichTextBox)

    TClass(wxRichTextCell) wxRichTextCell_Create(TClass(wxRichTextObject) parent);
void wxRichTextCell_Delete(TSelf(wxRichTextCell) self);
int wxRichTextCell_GetColSpan(TSelf(wxRichTextCell) self);
void wxRichTextCell_SetColSpan(TSelf(wxRichTextCell) self, int span);
int wxRichTextCell_GetRowSpan(TSelf(wxRichTextCell) self);
void wxRichTextCell_SetRowSpan(TSelf(wxRichTextCell) self, int span);
void wxRichTextCell_Copy(TSelf(wxRichTextCell) self, TClass(wxRichTextCell) obj);

// wxRichTextField is the return type of wxRichTextCtrl::WriteField; paragraph plumbing is
// inherited from wxRichTextParagraphLayoutBox.
TClassDefExtend(wxRichTextField, wxRichTextParagraphLayoutBox)

    TClass(wxRichTextField)
        wxRichTextField_Create(TClass(wxString) fieldType, TClass(wxRichTextObject) parent);
void wxRichTextField_Delete(TSelf(wxRichTextField) self);
void wxRichTextField_SetFieldType(TSelf(wxRichTextField) self, TClass(wxString) fieldType);
TClass(wxString) wxRichTextField_GetFieldType(TSelf(wxRichTextField) self);
TBool wxRichTextField_UpdateField(TSelf(wxRichTextField) self, TClass(wxRichTextBuffer) buffer);
void wxRichTextField_Copy(TSelf(wxRichTextField) self, TClass(wxRichTextField) obj);

// wxRichTextFieldType is abstract (Draw/Layout/GetRangeSize are pure virtual), so there is
// deliberately no factory here: register a concrete subclass such as
// wxRichTextFieldTypeStandard with wxRichTextBuffer_AddFieldType.
TClassDefExtend(wxRichTextFieldType, wxObject)

    void wxRichTextFieldType_SetName(TSelf(wxRichTextFieldType) self, TClass(wxString) name);
TClass(wxString) wxRichTextFieldType_GetName(TSelf(wxRichTextFieldType) self);
void wxRichTextFieldType_Copy(TSelf(wxRichTextFieldType) self,
                              TClass(wxRichTextFieldType) fieldType);

TClassDefExtend(wxRichTextFieldTypeStandard, wxRichTextFieldType)

    TClass(wxRichTextFieldTypeStandard)
        wxRichTextFieldTypeStandard_Create(TClass(wxString) name, TClass(wxString) label,
                                           int displayStyle);
TClass(wxRichTextFieldTypeStandard)
    wxRichTextFieldTypeStandard_CreateWithBitmap(TClass(wxString) name, TClass(wxBitmap) bitmap,
                                                 int displayStyle);
TClass(wxRichTextFieldTypeStandard) wxRichTextFieldTypeStandard_CreateDefault();
void wxRichTextFieldTypeStandard_Delete(TSelf(wxRichTextFieldTypeStandard) self);
void wxRichTextFieldTypeStandard_Copy(TSelf(wxRichTextFieldTypeStandard) self,
                                      TClass(wxRichTextFieldTypeStandard) field);
void wxRichTextFieldTypeStandard_SetLabel(TSelf(wxRichTextFieldTypeStandard) self,
                                          TClass(wxString) label);
TClass(wxString) wxRichTextFieldTypeStandard_GetLabel(TSelf(wxRichTextFieldTypeStandard) self);
void wxRichTextFieldTypeStandard_SetBitmap(TSelf(wxRichTextFieldTypeStandard) self,
                                           TClass(wxBitmap) bitmap);
// GetBitmap/GetFont return borrowed pointers into the field type, not owned copies.
TClass(wxBitmap) wxRichTextFieldTypeStandard_GetBitmap(TSelf(wxRichTextFieldTypeStandard) self);
int wxRichTextFieldTypeStandard_GetDisplayStyle(TSelf(wxRichTextFieldTypeStandard) self);
void wxRichTextFieldTypeStandard_SetDisplayStyle(TSelf(wxRichTextFieldTypeStandard) self,
                                                 int displayStyle);
TClass(wxFont) wxRichTextFieldTypeStandard_GetFont(TSelf(wxRichTextFieldTypeStandard) self);
void wxRichTextFieldTypeStandard_SetFont(TSelf(wxRichTextFieldTypeStandard) self,
                                         TClass(wxFont) font);
void wxRichTextFieldTypeStandard_GetTextColour(TSelf(wxRichTextFieldTypeStandard) self,
                                               TClass(wxColour) colour);
void wxRichTextFieldTypeStandard_SetTextColour(TSelf(wxRichTextFieldTypeStandard) self,
                                               TClass(wxColour) colour);
void wxRichTextFieldTypeStandard_GetBorderColour(TSelf(wxRichTextFieldTypeStandard) self,
                                                 TClass(wxColour) colour);
void wxRichTextFieldTypeStandard_SetBorderColour(TSelf(wxRichTextFieldTypeStandard) self,
                                                 TClass(wxColour) colour);
void wxRichTextFieldTypeStandard_GetBackgroundColour(TSelf(wxRichTextFieldTypeStandard) self,
                                                     TClass(wxColour) colour);
void wxRichTextFieldTypeStandard_SetBackgroundColour(TSelf(wxRichTextFieldTypeStandard) self,
                                                     TClass(wxColour) colour);
void wxRichTextFieldTypeStandard_SetVerticalPadding(TSelf(wxRichTextFieldTypeStandard) self,
                                                    int padding);
int wxRichTextFieldTypeStandard_GetVerticalPadding(TSelf(wxRichTextFieldTypeStandard) self);
void wxRichTextFieldTypeStandard_SetHorizontalPadding(TSelf(wxRichTextFieldTypeStandard) self,
                                                      int padding);
int wxRichTextFieldTypeStandard_GetHorizontalPadding(TSelf(wxRichTextFieldTypeStandard) self);
void wxRichTextFieldTypeStandard_SetHorizontalMargin(TSelf(wxRichTextFieldTypeStandard) self,
                                                     int margin);
int wxRichTextFieldTypeStandard_GetHorizontalMargin(TSelf(wxRichTextFieldTypeStandard) self);
void wxRichTextFieldTypeStandard_SetVerticalMargin(TSelf(wxRichTextFieldTypeStandard) self,
                                                   int margin);
int wxRichTextFieldTypeStandard_GetVerticalMargin(TSelf(wxRichTextFieldTypeStandard) self);

// wxRichTextDrawingHandler is abstract too (all virtual hooks are pure); only the shared
// name accessors are exposed. A callback-driven subclass is a separate follow-up.
TClassDefExtend(wxRichTextDrawingHandler, wxObject)

    void wxRichTextDrawingHandler_SetName(TSelf(wxRichTextDrawingHandler) self,
                                          TClass(wxString) name);
TClass(wxString) wxRichTextDrawingHandler_GetName(TSelf(wxRichTextDrawingHandler) self);

TClassDefExtend(wxRichTextImage, wxRichTextObject)

    TClass(wxRichTextImage) wxRichTextImage_Create(TClass(wxRichTextObject) parent);
TClass(wxRichTextImage)
    wxRichTextImage_CreateFromImage(TClass(wxImage) image, TClass(wxRichTextObject) parent,
                                    TClass(wxRichTextAttr) charStyle);
TClass(wxRichTextImage)
    wxRichTextImage_CreateFromImageBlock(TClass(wxRichTextImageBlock) imageBlock,
                                         TClass(wxRichTextObject) parent,
                                         TClass(wxRichTextAttr) charStyle);
void wxRichTextImage_Delete(TSelf(wxRichTextImage) self);
void wxRichTextImage_GetImageCache(TSelf(wxRichTextImage) self, TClass(wxBitmap) bitmap);
void wxRichTextImage_SetImageCache(TSelf(wxRichTextImage) self, TClass(wxBitmap) bitmap);
TClass(wxRichTextImageBlock) wxRichTextImage_GetImageBlock(TSelf(wxRichTextImage) self);
void wxRichTextImage_GetOriginalImageSize(TSelf(wxRichTextImage) self, TSizeOut(w, h));
void wxRichTextImage_SetOriginalImageSize(TSelf(wxRichTextImage) self, TSize(w, h));
int wxRichTextImage_GetImageState(TSelf(wxRichTextImage) self);
void wxRichTextImage_SetImageState(TSelf(wxRichTextImage) self, int state);

TClassDef(wxRichTextImageBlock)

    TClass(wxRichTextImageBlock) wxRichTextImageBlock_Create();
void wxRichTextImageBlock_Delete(TSelf(wxRichTextImageBlock) self);
void wxRichTextImageBlock_Clear(TSelf(wxRichTextImageBlock) self);
TBool wxRichTextImageBlock_IsOk(TSelf(wxRichTextImageBlock) self);
size_t wxRichTextImageBlock_GetDataSize(TSelf(wxRichTextImageBlock) self);

TClassDefExtend(wxRichTextBuffer, wxRichTextParagraphLayoutBox)

    TClass(wxRichTextBuffer) wxRichTextBuffer_Create();
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
void wxRichTextBuffer_AddHandler(void* handler);
// Field-type / drawing-handler registries. The registry takes ownership of the object, so
// do not Delete it after registering it here.
void wxRichTextBuffer_AddFieldType(TClass(wxRichTextFieldType) fieldType);
TBool wxRichTextBuffer_RemoveFieldType(TClass(wxString) name);
TClass(wxRichTextFieldType) wxRichTextBuffer_FindFieldType(TClass(wxString) name);
void wxRichTextBuffer_AddDrawingHandler(TClass(wxRichTextDrawingHandler) handler);
void wxRichTextBuffer_InsertDrawingHandler(TClass(wxRichTextDrawingHandler) handler);
TBool wxRichTextBuffer_RemoveDrawingHandler(TClass(wxString) name);
TClass(wxRichTextDrawingHandler) wxRichTextBuffer_FindDrawingHandler(TClass(wxString) name);
void wxRichTextBuffer_Delete(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_AddParagraph(TSelf(wxRichTextBuffer) self, TClass(wxString) text,
                                   TClass(wxRichTextAttr) paraStyle, TLongOut start, TLongOut end);
TBool wxRichTextBuffer_DeleteRange(TSelf(wxRichTextBuffer) self, long start, long end);
void wxRichTextBuffer_GetRange(TSelf(wxRichTextBuffer) self, TLongOut start, TLongOut end);
TClass(wxString) wxRichTextBuffer_GetText(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_Clear(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_LoadFile(TSelf(wxRichTextBuffer) self, TClass(wxString) filename, int type);
TBool wxRichTextBuffer_SaveFile(TSelf(wxRichTextBuffer) self, TClass(wxString) filename, int type);
void wxRichTextBuffer_ResetAndClearCommands(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_SetStyleSheet(TSelf(wxRichTextBuffer) self,
                                    TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet) wxRichTextBuffer_GetStyleSheet(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_SetStyleSheetAndNotify(TSelf(wxRichTextBuffer) self,
                                              TClass(wxRichTextStyleSheet) sheet);
TBool wxRichTextBuffer_PushStyleSheet(TSelf(wxRichTextBuffer) self,
                                      TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet) wxRichTextBuffer_PopStyleSheet(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_SetHandlerFlags(TSelf(wxRichTextBuffer) self, int flags);
int wxRichTextBuffer_GetHandlerFlags(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_SetFontScale(TSelf(wxRichTextBuffer) self, double fontScale);
double wxRichTextBuffer_GetFontScale(TSelf(wxRichTextBuffer) self);
void wxRichTextBuffer_SetDimensionScale(TSelf(wxRichTextBuffer) self, double dimScale);
double wxRichTextBuffer_GetDimensionScale(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_BeginBatchUndo(TSelf(wxRichTextBuffer) self, TClass(wxString) cmdName);
TBool wxRichTextBuffer_EndBatchUndo(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_BatchingUndo(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_BeginSuppressUndo(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_EndSuppressUndo(TSelf(wxRichTextBuffer) self);
TBool wxRichTextBuffer_SuppressingUndo(TSelf(wxRichTextBuffer) self);
TClass(wxString)
    wxRichTextBuffer_GetExtWildcard(TBool combine, TBool save, TClass(wxArrayInt) types);

TClassDefExtend(wxRichTextFileHandler, wxObject)

    TClass(wxString) wxRichTextFileHandler_GetName(TSelf(wxRichTextFileHandler) self);
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
TBool wxRichTextFileHandler_SaveFile(TSelf(wxRichTextFileHandler) pObject, void* buffer,
                                     TClass(wxOutputStream) stream);
void wxRichTextFileHandler_SetName(TSelf(wxRichTextFileHandler) self, TClass(wxString) name);
TClass(wxString) wxRichTextFileHandler_GetExtension(TSelf(wxRichTextFileHandler) self);
void wxRichTextFileHandler_SetExtension(TSelf(wxRichTextFileHandler) self, TClass(wxString) ext);
int wxRichTextFileHandler_GetType(TSelf(wxRichTextFileHandler) self);
void wxRichTextFileHandler_SetType(TSelf(wxRichTextFileHandler) self, int type);
int wxRichTextFileHandler_GetFlags(TSelf(wxRichTextFileHandler) self);
void wxRichTextFileHandler_SetFlags(TSelf(wxRichTextFileHandler) self, int flags);
void wxRichTextFileHandler_SetEncoding(TSelf(wxRichTextFileHandler) self,
                                       TClass(wxString) encoding);
TClass(wxString) wxRichTextFileHandler_GetEncoding(TSelf(wxRichTextFileHandler) self);
TBool wxRichTextFileHandler_CanHandle(TSelf(wxRichTextFileHandler) self, TClass(wxString) filename);
TBool wxRichTextFileHandler_CanLoad(TSelf(wxRichTextFileHandler) self);
TBool wxRichTextFileHandler_CanSave(TSelf(wxRichTextFileHandler) self);
TBool wxRichTextFileHandler_IsVisible(TSelf(wxRichTextFileHandler) self);
void wxRichTextFileHandler_SetVisible(TSelf(wxRichTextFileHandler) self, TBool visible);
void wxRichTextFileHandler_Delete(TSelf(wxRichTextFileHandler) self);

TClassDefExtend(wxRichTextXMLHandler, wxRichTextFileHandler)

    TClass(wxRichTextXMLHandler)
        wxRichTextXMLHandler_Create(TClass(wxString) name, TClass(wxString) ext, int type);
void wxRichTextXMLHandler_Delete(TSelf(wxRichTextXMLHandler) self);

TClassDefExtend(wxRichTextHTMLHandler, wxRichTextFileHandler)

    TClass(wxRichTextHTMLHandler)
        wxRichTextHTMLHandler_Create(TClass(wxString) name, TClass(wxString) ext, int type);
void wxRichTextHTMLHandler_Delete(TSelf(wxRichTextHTMLHandler) self);
TBool wxRichTextHTMLHandler_CanHandle(TSelf(wxRichTextHTMLHandler) self, TClass(wxString) filename);
void wxRichTextHTMLHandler_ClearTemporaryImageLocations(TSelf(wxRichTextHTMLHandler) self);
TBool wxRichTextHTMLHandler_DeleteTemporaryImages(TSelf(wxRichTextHTMLHandler) self);
void wxRichTextHTMLHandler_SetTempDir(TSelf(wxRichTextHTMLHandler) self, TClass(wxString) tempDir);
TClass(wxString) wxRichTextHTMLHandler_GetTempDir(TSelf(wxRichTextHTMLHandler) self);
void wxRichTextHTMLHandler_SetFontSizeMapping(TSelf(wxRichTextHTMLHandler) self,
                                              TClass(wxArrayInt) mapping);
TClassOwned(wxArrayInt) wxRichTextHTMLHandler_GetFontSizeMapping(TSelf(wxRichTextHTMLHandler) self);

TClassDefExtend(wxRichTextEvent, wxNotifyEvent)

    long wxRichTextEvent_GetPosition(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetPosition(TSelf(wxRichTextEvent) self, long position);
int wxRichTextEvent_GetFlags(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetFlags(TSelf(wxRichTextEvent) self, int flags);
TClass(wxRichTextStyleSheet) wxRichTextEvent_GetOldStyleSheet(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetOldStyleSheet(TSelf(wxRichTextEvent) self,
                                      TClass(wxRichTextStyleSheet) sheet);
TClass(wxRichTextStyleSheet) wxRichTextEvent_GetNewStyleSheet(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetNewStyleSheet(TSelf(wxRichTextEvent) self,
                                      TClass(wxRichTextStyleSheet) sheet);
void wxRichTextEvent_GetRange(TSelf(wxRichTextEvent) self, TLongOut start, TLongOut end);
void wxRichTextEvent_SetRange(TSelf(wxRichTextEvent) self, long start, long end);
int wxRichTextEvent_GetCharacter(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetCharacter(TSelf(wxRichTextEvent) self, int character);
TClass(wxRichTextParagraphLayoutBox) wxRichTextEvent_GetContainer(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetContainer(TSelf(wxRichTextEvent) self,
                                  TClass(wxRichTextParagraphLayoutBox) container);
TClass(wxRichTextParagraphLayoutBox) wxRichTextEvent_GetOldContainer(TSelf(wxRichTextEvent) self);
void wxRichTextEvent_SetOldContainer(TSelf(wxRichTextEvent) self,
                                     TClass(wxRichTextParagraphLayoutBox) container);

TClassDefExtend(wxRichTextCtrl, wxControl)

    TClass(wxRichTextBuffer) wxRichTextCtrl_GetBuffer(TSelf(wxRichTextCtrl) self);
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
TBool wxRichTextCtrl_BeginSuppressUndo(TSelf(wxRichTextCtrl) pObject);
TBool wxRichTextCtrl_EndSuppressUndo(TSelf(wxRichTextCtrl) pObject);
void* wxRichTextCtrl_GetCommandProcessor(TSelf(wxRichTextCtrl) pObject);
TClass(wxRichTextField)
    wxRichTextCtrl_WriteField(TSelf(wxRichTextCtrl) pObject, TClass(wxString) fieldType,
                              TClass(wxRichTextProperties) properties,
                              TClass(wxRichTextAttr) textAttr);
TClass(wxRichTextTable)
    wxRichTextCtrl_WriteTable(TSelf(wxRichTextCtrl) pObject, int rows, int cols,
                              TClass(wxRichTextAttr) tableAttr, TClass(wxRichTextAttr) cellAttr);
TClass(wxRichTextBox)
    wxRichTextCtrl_WriteTextBox(TSelf(wxRichTextCtrl) pObject, TClass(wxRichTextAttr) textAttr);
TClass(wxRichTextParagraphLayoutBox) wxRichTextCtrl_GetFocusObject(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_SetFocusObject(TSelf(wxRichTextCtrl) self,
                                    TClass(wxRichTextParagraphLayoutBox) obj,
                                    TBool setCaretPosition);
TBool wxRichTextCtrl_IsSingleLine(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsMultiLine(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_HasSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_HasUnfocusedSelection(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_GetSelectionRange(TSelf(wxRichTextCtrl) self, TLongOut start, TLongOut end);
void wxRichTextCtrl_SetSelectionRange(TSelf(wxRichTextCtrl) self, long start, long end);
void wxRichTextCtrl_GetInternalSelectionRange(TSelf(wxRichTextCtrl) self, TLongOut start,
                                              TLongOut end);
void wxRichTextCtrl_SetInternalSelectionRange(TSelf(wxRichTextCtrl) self, long start, long end);
TBool wxRichTextCtrl_SelectWord(TSelf(wxRichTextCtrl) self, long position);
long wxRichTextCtrl_GetDelayedLayoutThreshold(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetDelayedLayoutThreshold(TSelf(wxRichTextCtrl) self, long threshold);
TBool wxRichTextCtrl_GetFullLayoutRequired(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetFullLayoutRequired(TSelf(wxRichTextCtrl) self, TBool required);
long wxRichTextCtrl_GetFullLayoutSavedPosition(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetFullLayoutSavedPosition(TSelf(wxRichTextCtrl) self, long position);
TBool wxRichTextCtrl_GetCaretAtLineStart(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetCaretAtLineStart(TSelf(wxRichTextCtrl) self, TBool atStart);
TBool wxRichTextCtrl_GetVerticalScrollbarEnabled(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_EnableVerticalScrollbar(TSelf(wxRichTextCtrl) self, TBool enable);
TBool wxRichTextCtrl_GetVirtualAttributesEnabled(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_EnableVirtualAttributes(TSelf(wxRichTextCtrl) self, TBool enable);
double wxRichTextCtrl_GetFontScale(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetFontScale(TSelf(wxRichTextCtrl) self, double fontScale, TBool refresh);
double wxRichTextCtrl_GetDimensionScale(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetDimensionScale(TSelf(wxRichTextCtrl) self, double dimScale, TBool refresh);
double wxRichTextCtrl_GetScale(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetScale(TSelf(wxRichTextCtrl) self, double scale, TBool refresh);
void wxRichTextCtrl_GetBasicStyle(TSelf(wxRichTextCtrl) self, TClass(wxRichTextAttr) style);
void wxRichTextCtrl_SetBasicStyle(TSelf(wxRichTextCtrl) self, TClass(wxRichTextAttr) style);
void wxRichTextCtrl_GetDefaultStyleEx(TSelf(wxRichTextCtrl) self, TClass(wxRichTextAttr) style);
int wxRichTextCtrl_GetHandlerFlags(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetHandlerFlags(TSelf(wxRichTextCtrl) self, int flags);
TClass(wxRichTextStyleSheet) wxRichTextCtrl_GetStyleSheet(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetStyleSheet(TSelf(wxRichTextCtrl) self,
                                  TClass(wxRichTextStyleSheet) styleSheet);
TBool wxRichTextCtrl_PushStyleSheet(TSelf(wxRichTextCtrl) self,
                                    TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet) wxRichTextCtrl_PopStyleSheet(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_ApplyStyleSheet(TSelf(wxRichTextCtrl) self,
                                     TClass(wxRichTextStyleSheet) styleSheet);
TBool wxRichTextCtrl_SetDefaultStyleToCursorStyle(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_AddParagraph(TSelf(wxRichTextCtrl) self, TClass(wxString) text, TLongOut start,
                                 TLongOut end);
void wxRichTextCtrl_AddImage(TSelf(wxRichTextCtrl) self, TClass(wxImage) image, TLongOut start,
                             TLongOut end);
TBool wxRichTextCtrl_WriteImageBitmap(TSelf(wxRichTextCtrl) self, TClass(wxBitmap) bitmap,
                                      int bitmapType, TClass(wxRichTextAttr) textAttr);
TBool wxRichTextCtrl_WriteImageBlock(TSelf(wxRichTextCtrl) self,
                                     TClass(wxRichTextImageBlock) imageBlock,
                                     TClass(wxRichTextAttr) textAttr);
TBool wxRichTextCtrl_DeleteRange(TSelf(wxRichTextCtrl) self, long start, long end);
TBool wxRichTextCtrl_SetStyleEx(TSelf(wxRichTextCtrl) self, long start, long end,
                                TClass(wxRichTextAttr) style, int flags);
TBool wxRichTextCtrl_GetUncombinedStyle(TSelf(wxRichTextCtrl) self, long position,
                                        TClass(wxRichTextAttr) style);
TBool wxRichTextCtrl_GetStyleForRange(TSelf(wxRichTextCtrl) self, long start, long end,
                                      TClass(wxRichTextAttr) style);
TBool wxRichTextCtrl_BeginStyle(TSelf(wxRichTextCtrl) self, TClass(wxRichTextAttr) style);
TBool wxRichTextCtrl_EndStyle(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_EndAllStyles(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginCharacterStyle(TSelf(wxRichTextCtrl) self, TClass(wxString) name);
TBool wxRichTextCtrl_EndCharacterStyle(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginParagraphStyle(TSelf(wxRichTextCtrl) self, TClass(wxString) name);
TBool wxRichTextCtrl_EndParagraphStyle(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginListStyle(TSelf(wxRichTextCtrl) self, TClass(wxString) name, int level,
                                    int number);
TBool wxRichTextCtrl_EndListStyle(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_SetListStyle(TSelf(wxRichTextCtrl) self, long start, long end,
                                  TClass(wxString) defName, int flags, int startFrom,
                                  int specifiedLevel);
TBool wxRichTextCtrl_ClearListStyle(TSelf(wxRichTextCtrl) self, long start, long end, int flags);
TBool wxRichTextCtrl_NumberList(TSelf(wxRichTextCtrl) self, long start, long end,
                                TClass(wxString) defName, int flags, int startFrom,
                                int specifiedLevel);
TBool wxRichTextCtrl_PromoteList(TSelf(wxRichTextCtrl) self, int promoteBy, long start, long end,
                                 TClass(wxString) defName, int flags, int specifiedLevel);
TBool wxRichTextCtrl_ApplyStyle(TSelf(wxRichTextCtrl) self, TClass(wxRichTextStyleDefinition) def);
TBool wxRichTextCtrl_MoveCaret(TSelf(wxRichTextCtrl) self, long position, TBool showAtLineStart);
TBool wxRichTextCtrl_MoveRight(TSelf(wxRichTextCtrl) self, int noPositions, int flags);
TBool wxRichTextCtrl_MoveLeft(TSelf(wxRichTextCtrl) self, int noPositions, int flags);
TBool wxRichTextCtrl_MoveUp(TSelf(wxRichTextCtrl) self, int noLines, int flags);
TBool wxRichTextCtrl_MoveDown(TSelf(wxRichTextCtrl) self, int noLines, int flags);
TBool wxRichTextCtrl_MoveToLineEnd(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveToLineStart(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveToParagraphEnd(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveToParagraphStart(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveHome(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_MoveEnd(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_PageUp(TSelf(wxRichTextCtrl) self, int noPages, int flags);
TBool wxRichTextCtrl_PageDown(TSelf(wxRichTextCtrl) self, int noPages, int flags);
TBool wxRichTextCtrl_WordLeft(TSelf(wxRichTextCtrl) self, int noPages, int flags);
TBool wxRichTextCtrl_WordRight(TSelf(wxRichTextCtrl) self, int noPages, int flags);
TBool wxRichTextCtrl_IsSelectionBold(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsSelectionItalics(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsSelectionUnderlined(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_DoesSelectionHaveTextEffectFlag(TSelf(wxRichTextCtrl) self, int flag);
TBool wxRichTextCtrl_IsSelectionAligned(TSelf(wxRichTextCtrl) self, int alignment);
TBool wxRichTextCtrl_ApplyBoldToSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_ApplyItalicToSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_ApplyUnderlineToSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_ApplyTextEffectToSelection(TSelf(wxRichTextCtrl) self, int flags);
TBool wxRichTextCtrl_ApplyAlignmentToSelection(TSelf(wxRichTextCtrl) self, int alignment);
TBool wxRichTextCtrl_ShowContextMenu(TSelf(wxRichTextCtrl) self, TClass(wxMenu) menu, TPoint(x, y),
                                     TBool addPropertyCommands);
int wxRichTextCtrl_PrepareContextMenu(TSelf(wxRichTextCtrl) self, TClass(wxMenu) menu, TPoint(x, y),
                                      TBool addPropertyCommands);
void wxRichTextCtrl_SetContextMenu(TSelf(wxRichTextCtrl) self, TClass(wxMenu) menu);
TClass(wxMenu) wxRichTextCtrl_GetContextMenu(TSelf(wxRichTextCtrl) self);
long wxRichTextCtrl_GetSelectionAnchor(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetSelectionAnchor(TSelf(wxRichTextCtrl) self, long anchor);
TClass(wxRichTextObject) wxRichTextCtrl_GetSelectionAnchorObject(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_Freeze(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_Thaw(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsFrozen(TSelf(wxRichTextCtrl) self);
int wxRichTextCtrl_HitTest(TSelf(wxRichTextCtrl) self, TPoint(x, y), TLongOut position);
void wxRichTextCtrl_SetCaretPosition(TSelf(wxRichTextCtrl) self, long position,
                                     TBool showAtLineStart);
long wxRichTextCtrl_GetAdjustedCaretPosition(TSelf(wxRichTextCtrl) self, long caretPosition);
long wxRichTextCtrl_FindNextWordPosition(TSelf(wxRichTextCtrl) self, int direction);
TBool wxRichTextCtrl_IsPositionVisible(TSelf(wxRichTextCtrl) self, long position);
long wxRichTextCtrl_GetFirstVisiblePosition(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_GetFirstVisiblePoint(TSelf(wxRichTextCtrl) self, TPointOut(x, y));

TClassDefExtend(wxRichTextHeaderFooterData, wxObject)

    TClass(wxRichTextHeaderFooterData) wxRichTextHeaderFooterData_Create();
void wxRichTextHeaderFooterData_Delete(TSelf(wxRichTextHeaderFooterData) self);
void wxRichTextHeaderFooterData_SetHeaderText(TSelf(wxRichTextHeaderFooterData) self,
                                              TClass(wxString) text, int page, int location);
TClass(wxString) wxRichTextHeaderFooterData_GetHeaderText(TSelf(wxRichTextHeaderFooterData) self,
                                                          int page, int location);
void wxRichTextHeaderFooterData_SetFooterText(TSelf(wxRichTextHeaderFooterData) self,
                                              TClass(wxString) text, int page, int location);
TClass(wxString) wxRichTextHeaderFooterData_GetFooterText(TSelf(wxRichTextHeaderFooterData) self,
                                                          int page, int location);
void wxRichTextHeaderFooterData_SetText(TSelf(wxRichTextHeaderFooterData) self,
                                        TClass(wxString) text, int headerFooter, int page,
                                        int location);
TClass(wxString) wxRichTextHeaderFooterData_GetText(TSelf(wxRichTextHeaderFooterData) self,
                                                    int headerFooter, int page, int location);
void wxRichTextHeaderFooterData_SetMargins(TSelf(wxRichTextHeaderFooterData) self, int headerMargin,
                                           int footerMargin);
int wxRichTextHeaderFooterData_GetHeaderMargin(TSelf(wxRichTextHeaderFooterData) self);
int wxRichTextHeaderFooterData_GetFooterMargin(TSelf(wxRichTextHeaderFooterData) self);
void wxRichTextHeaderFooterData_SetShowOnFirstPage(TSelf(wxRichTextHeaderFooterData) self,
                                                   TBool showOnFirstPage);
TBool wxRichTextHeaderFooterData_GetShowOnFirstPage(TSelf(wxRichTextHeaderFooterData) self);
void wxRichTextHeaderFooterData_Clear(TSelf(wxRichTextHeaderFooterData) self);
void wxRichTextHeaderFooterData_SetFont(TSelf(wxRichTextHeaderFooterData) self,
                                        TClass(wxFont) font);
void wxRichTextHeaderFooterData_GetFont(TSelf(wxRichTextHeaderFooterData) self,
                                        TClass(wxFont) font);
void wxRichTextHeaderFooterData_SetTextColour(TSelf(wxRichTextHeaderFooterData) self,
                                              TClass(wxColour) colour);
void wxRichTextHeaderFooterData_GetTextColour(TSelf(wxRichTextHeaderFooterData) self,
                                              TClass(wxColour) colour);

TClassDefExtend(wxRichTextPrinting, wxObject)

    TClass(wxRichTextPrinting)
        wxRichTextPrinting_Create(TClass(wxString) name, TClass(wxWindow) parentWindow);
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
TBool wxRichTextPrinting_PreviewBuffer(TSelf(wxRichTextPrinting) pObject,
                                       TClass(wxRichTextBuffer) buffer);
TBool wxRichTextPrinting_PrintBuffer(TSelf(wxRichTextPrinting) pObject,
                                     TClass(wxRichTextBuffer) buffer, TBool showPrintDialog);
void wxRichTextPrinting_Delete(TSelf(wxRichTextPrinting) self);
TBool wxRichTextPrinting_PreviewFile(TSelf(wxRichTextPrinting) self, TClass(wxString) richTextFile);
TBool wxRichTextPrinting_PrintFile(TSelf(wxRichTextPrinting) self, TClass(wxString) richTextFile,
                                   TBool showPrintDialog);
void wxRichTextPrinting_PageSetup(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetHeaderFooterData(TSelf(wxRichTextPrinting) self,
                                            TClass(wxRichTextHeaderFooterData) data);
void wxRichTextPrinting_GetHeaderFooterData(TSelf(wxRichTextPrinting) self,
                                            TClass(wxRichTextHeaderFooterData) data);
void wxRichTextPrinting_SetHeaderText(TSelf(wxRichTextPrinting) self, TClass(wxString) text,
                                      int page, int location);
TClass(wxString)
    wxRichTextPrinting_GetHeaderText(TSelf(wxRichTextPrinting) self, int page, int location);
void wxRichTextPrinting_SetFooterText(TSelf(wxRichTextPrinting) self, TClass(wxString) text,
                                      int page, int location);
TClass(wxString)
    wxRichTextPrinting_GetFooterText(TSelf(wxRichTextPrinting) self, int page, int location);
void wxRichTextPrinting_SetShowOnFirstPage(TSelf(wxRichTextPrinting) self, TBool show);
void wxRichTextPrinting_SetHeaderFooterFont(TSelf(wxRichTextPrinting) self, TClass(wxFont) font);
void wxRichTextPrinting_SetHeaderFooterTextColour(TSelf(wxRichTextPrinting) self,
                                                  TClass(wxColour) colour);
TClass(wxPrintData) wxRichTextPrinting_GetPrintData(TSelf(wxRichTextPrinting) self);
TClass(wxPageSetupDialogData) wxRichTextPrinting_GetPageSetupData(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetPrintData(TSelf(wxRichTextPrinting) self, TClass(wxPrintData) printData);
void wxRichTextPrinting_SetPageSetupData(TSelf(wxRichTextPrinting) self,
                                         TClass(wxPageSetupDialogData) pageSetupData);
void wxRichTextPrinting_SetRichTextBufferPreview(TSelf(wxRichTextPrinting) self,
                                                 TClass(wxRichTextBuffer) buffer);
TClass(wxRichTextBuffer)
    wxRichTextPrinting_GetRichTextBufferPreview(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetRichTextBufferPrinting(TSelf(wxRichTextPrinting) self,
                                                  TClass(wxRichTextBuffer) buffer);
TClass(wxRichTextBuffer)
    wxRichTextPrinting_GetRichTextBufferPrinting(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetParentWindow(TSelf(wxRichTextPrinting) self, TClass(wxWindow) parent);
TClass(wxWindow) wxRichTextPrinting_GetParentWindow(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetTitle(TSelf(wxRichTextPrinting) self, TClass(wxString) title);
TClass(wxString) wxRichTextPrinting_GetTitle(TSelf(wxRichTextPrinting) self);
void wxRichTextPrinting_SetPreviewRect(TSelf(wxRichTextPrinting) self, TRect(x, y, w, h));
void wxRichTextPrinting_GetPreviewRect(TSelf(wxRichTextPrinting) self, TRectOut(x, y, w, h));

TClassDefExtend(wxSymbolPickerDialog, wxDialog)

    TClass(wxSymbolPickerDialog)
        wxSymbolPickerDialog_Create(TClass(wxString) symbol, TClass(wxString) fontName,
                                    TClass(wxString) normalTextFont, TClass(wxWindow) parent,
                                    int id, TClass(wxString) caption, TRect(x, y, w, h),
                                    long style);
void wxSymbolPickerDialog_Delete(TSelf(wxSymbolPickerDialog) self);
int wxSymbolPickerDialog_GetSymbolChar(TSelf(wxSymbolPickerDialog) self);
TBool wxSymbolPickerDialog_HasSelection(TSelf(wxSymbolPickerDialog) self);
TBool wxSymbolPickerDialog_UseNormalFont(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetUnicodeMode(TSelf(wxSymbolPickerDialog) self, TBool unicodeMode);
void wxSymbolPickerDialog_ShowAtSubset(TSelf(wxSymbolPickerDialog) self);
TClass(wxString) wxSymbolPickerDialog_GetSymbol(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetSymbol(TSelf(wxSymbolPickerDialog) self, TClass(wxString) symbol);
TClass(wxString) wxSymbolPickerDialog_GetFontName(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetFontName(TSelf(wxSymbolPickerDialog) self, TClass(wxString) fontName);
TBool wxSymbolPickerDialog_GetFromUnicode(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetFromUnicode(TSelf(wxSymbolPickerDialog) self, TBool fromUnicode);
TClass(wxString) wxSymbolPickerDialog_GetNormalTextFontName(TSelf(wxSymbolPickerDialog) self);
void wxSymbolPickerDialog_SetNormalTextFontName(TSelf(wxSymbolPickerDialog) self,
                                                TClass(wxString) fontName);

TClassDefExtend(wxRichTextFormattingDialog, wxPropertySheetDialog)

    TClass(wxRichTextFormattingDialog)
        wxRichTextFormattingDialog_Create(long flags, TClass(wxWindow) parent,
                                          TClass(wxString) title, int id, TRect(x, y, w, h),
                                          long style);
void wxRichTextFormattingDialog_Delete(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_GetStyle(TSelf(wxRichTextFormattingDialog) self,
                                          TClass(wxRichTextCtrl) ctrl, long start, long end);
TBool wxRichTextFormattingDialog_SetStyle(TSelf(wxRichTextFormattingDialog) self,
                                          TClass(wxRichTextAttr) style, TBool update);
TBool wxRichTextFormattingDialog_SetStyleDefinition(TSelf(wxRichTextFormattingDialog) self,
                                                    TClass(wxRichTextStyleDefinition) styleDef,
                                                    TClass(wxRichTextStyleSheet) sheet,
                                                    TBool update);
TClass(wxRichTextStyleDefinition)
    wxRichTextFormattingDialog_GetStyleDefinition(TSelf(wxRichTextFormattingDialog) self);
TClass(wxRichTextStyleSheet)
    wxRichTextFormattingDialog_GetStyleSheet(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_UpdateDisplay(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_ApplyStyle(TSelf(wxRichTextFormattingDialog) self,
                                            TClass(wxRichTextCtrl) ctrl, long start, long end,
                                            int flags);
TBool wxRichTextFormattingDialog_ApplyStyleToCtrl(TSelf(wxRichTextFormattingDialog) self,
                                                  TClass(wxRichTextCtrl) ctrl, int flags);
void wxRichTextFormattingDialog_GetAttributes(TSelf(wxRichTextFormattingDialog) self,
                                              TClass(wxRichTextAttr) attr);
void wxRichTextFormattingDialog_SetAttributes(TSelf(wxRichTextFormattingDialog) self,
                                              TClass(wxRichTextAttr) attr);
void wxRichTextFormattingDialog_SetOptions(TSelf(wxRichTextFormattingDialog) self, int options);
int wxRichTextFormattingDialog_GetOptions(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_HasOption(TSelf(wxRichTextFormattingDialog) self, int option);
TClass(wxRichTextObject)
    wxRichTextFormattingDialog_GetObject(TSelf(wxRichTextFormattingDialog) self);
void wxRichTextFormattingDialog_SetObject(TSelf(wxRichTextFormattingDialog) self,
                                          TClass(wxRichTextObject) obj);
TBool wxRichTextFormattingDialog_TransferDataToWindow(TSelf(wxRichTextFormattingDialog) self);
TBool wxRichTextFormattingDialog_TransferDataFromWindow(TSelf(wxRichTextFormattingDialog) self);

TClassDefExtend(wxRichTextStyleOrganiserDialog, wxDialog)

    TClass(wxRichTextStyleOrganiserDialog)
        wxRichTextStyleOrganiserDialog_Create(int flags, TClass(wxRichTextStyleSheet) sheet,
                                              TClass(wxRichTextCtrl) ctrl, TClass(wxWindow) parent,
                                              int id, TClass(wxString) caption, TRect(x, y, w, h),
                                              long style);
void wxRichTextStyleOrganiserDialog_Delete(TSelf(wxRichTextStyleOrganiserDialog) self);
void wxRichTextStyleOrganiserDialog_SetStyleSheet(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                  TClass(wxRichTextStyleSheet) sheet);
TClass(wxRichTextStyleSheet)
    wxRichTextStyleOrganiserDialog_GetStyleSheet(TSelf(wxRichTextStyleOrganiserDialog) self);
void wxRichTextStyleOrganiserDialog_SetRichTextCtrl(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                    TClass(wxRichTextCtrl) ctrl);
TClass(wxRichTextCtrl)
    wxRichTextStyleOrganiserDialog_GetRichTextCtrl(TSelf(wxRichTextStyleOrganiserDialog) self);
void wxRichTextStyleOrganiserDialog_SetFlags(TSelf(wxRichTextStyleOrganiserDialog) self, int flags);
int wxRichTextStyleOrganiserDialog_GetFlags(TSelf(wxRichTextStyleOrganiserDialog) self);
void wxRichTextStyleOrganiserDialog_ShowPreview(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                int sel);
void wxRichTextStyleOrganiserDialog_ClearPreview(TSelf(wxRichTextStyleOrganiserDialog) self);
TBool wxRichTextStyleOrganiserDialog_GetRestartNumbering(TSelf(wxRichTextStyleOrganiserDialog)
                                                             self);
void wxRichTextStyleOrganiserDialog_SetRestartNumbering(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                        TBool restartNumbering);
TClass(wxString)
    wxRichTextStyleOrganiserDialog_GetSelectedStyle(TSelf(wxRichTextStyleOrganiserDialog) self);
TClass(wxRichTextStyleDefinition)
    wxRichTextStyleOrganiserDialog_GetSelectedStyleDefinition(TSelf(wxRichTextStyleOrganiserDialog)
                                                                  self);
TBool wxRichTextStyleOrganiserDialog_ApplyStyle(TSelf(wxRichTextStyleOrganiserDialog) self,
                                                TClass(wxRichTextCtrl) ctrl);

TClassDefExtend(wxRichTextStyleListBox, wxHtmlListBox)

    TClass(wxRichTextStyleListBox) wxRichTextStyleListBox_Create(TClass(wxWindow) parent, int id,
                                                                 TRect(x, y, w, h), long style);
void wxRichTextStyleListBox_Delete(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_SetStyleSheet(TSelf(wxRichTextStyleListBox) self,
                                          TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet)
    wxRichTextStyleListBox_GetStyleSheet(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_SetRichTextCtrl(TSelf(wxRichTextStyleListBox) self,
                                            TClass(wxRichTextCtrl) ctrl);
TClass(wxRichTextCtrl) wxRichTextStyleListBox_GetRichTextCtrl(TSelf(wxRichTextStyleListBox) self);
TClass(wxRichTextStyleDefinition)
    wxRichTextStyleListBox_GetStyle(TSelf(wxRichTextStyleListBox) self, size_t index);
int wxRichTextStyleListBox_GetIndexForStyle(TSelf(wxRichTextStyleListBox) self,
                                            TClass(wxString) name);
int wxRichTextStyleListBox_SetStyleSelection(TSelf(wxRichTextStyleListBox) self,
                                             TClass(wxString) name);
void wxRichTextStyleListBox_UpdateStyles(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_ApplyStyle(TSelf(wxRichTextStyleListBox) self, int index);
void wxRichTextStyleListBox_SetApplyOnSelection(TSelf(wxRichTextStyleListBox) self,
                                                TBool applyOnSelection);
TBool wxRichTextStyleListBox_GetApplyOnSelection(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_SetStyleType(TSelf(wxRichTextStyleListBox) self, int styleType);
int wxRichTextStyleListBox_GetStyleType(TSelf(wxRichTextStyleListBox) self);
void wxRichTextStyleListBox_SetAutoSetSelection(TSelf(wxRichTextStyleListBox) self, TBool autoSet);
TBool wxRichTextStyleListBox_CanAutoSetSelection(TSelf(wxRichTextStyleListBox) self);

TClassDefExtend(wxRichTextBufferDataObject, wxDataObjectSimple)

    TClass(wxRichTextBufferDataObject)
        wxRichTextBufferDataObject_Create(TClass(wxRichTextBuffer) richTextBuffer);
void wxRichTextBufferDataObject_Delete(TSelf(wxRichTextBufferDataObject) self);
TClass(wxRichTextBuffer)
    wxRichTextBufferDataObject_GetRichTextBuffer(TSelf(wxRichTextBufferDataObject) self);
TClass(wxString)
    wxRichTextBufferDataObject_GetRichTextBufferFormatId(TSelf(wxRichTextBufferDataObject) self);
size_t wxRichTextBufferDataObject_GetDataSize(TSelf(wxRichTextBufferDataObject) self);

// ---- Style definitions, style sheet and the style list/combo controls ----
// wxRichTextStyleDefinition is abstract: it has no factory, only the members shared by
// every definition type. TClass returns on GetStyle/GetProperties/GetLevelAttributes are
// borrowed subobjects of the definition -- callers must never delete them.
void wxRichTextStyleDefinition_Copy(TSelf(wxRichTextStyleDefinition) self,
                                    TClass(wxRichTextStyleDefinition) def);
TBool wxRichTextStyleDefinition_Eq(TSelf(wxRichTextStyleDefinition) self,
                                   TClass(wxRichTextStyleDefinition) def);
void wxRichTextStyleDefinition_SetName(TSelf(wxRichTextStyleDefinition) self,
                                       TClass(wxString) name);
TClass(wxString) wxRichTextStyleDefinition_GetName(TSelf(wxRichTextStyleDefinition) self);
void wxRichTextStyleDefinition_SetDescription(TSelf(wxRichTextStyleDefinition) self,
                                              TClass(wxString) descr);
TClass(wxString) wxRichTextStyleDefinition_GetDescription(TSelf(wxRichTextStyleDefinition) self);
void wxRichTextStyleDefinition_SetBaseStyle(TSelf(wxRichTextStyleDefinition) self,
                                            TClass(wxString) name);
TClass(wxString) wxRichTextStyleDefinition_GetBaseStyle(TSelf(wxRichTextStyleDefinition) self);
void wxRichTextStyleDefinition_SetStyle(TSelf(wxRichTextStyleDefinition) self,
                                        TClass(wxRichTextAttr) style);
TClass(wxRichTextAttr) wxRichTextStyleDefinition_GetStyle(TSelf(wxRichTextStyleDefinition) self);
TClass(wxRichTextProperties)
    wxRichTextStyleDefinition_GetProperties(TSelf(wxRichTextStyleDefinition) self);
void wxRichTextStyleDefinition_SetProperties(TSelf(wxRichTextStyleDefinition) self,
                                             TClass(wxRichTextProperties) props);

TClassDefExtend(wxRichTextCharacterStyleDefinition, wxRichTextStyleDefinition)

    TClass(wxRichTextCharacterStyleDefinition)
        wxRichTextCharacterStyleDefinition_Create(TClass(wxString) name);
void wxRichTextCharacterStyleDefinition_Delete(TSelf(wxRichTextCharacterStyleDefinition) self);

TClassDefExtend(wxRichTextParagraphStyleDefinition, wxRichTextStyleDefinition)

    TClass(wxRichTextParagraphStyleDefinition)
        wxRichTextParagraphStyleDefinition_Create(TClass(wxString) name);
void wxRichTextParagraphStyleDefinition_Delete(TSelf(wxRichTextParagraphStyleDefinition) self);
void wxRichTextParagraphStyleDefinition_SetNextStyle(TSelf(wxRichTextParagraphStyleDefinition) self,
                                                     TClass(wxString) name);
TClass(wxString)
    wxRichTextParagraphStyleDefinition_GetNextStyle(TSelf(wxRichTextParagraphStyleDefinition) self);
void wxRichTextParagraphStyleDefinition_Copy(TSelf(wxRichTextParagraphStyleDefinition) self,
                                             TClass(wxRichTextParagraphStyleDefinition) def);

TClassDefExtend(wxRichTextListStyleDefinition, wxRichTextParagraphStyleDefinition)

    TClass(wxRichTextListStyleDefinition)
        wxRichTextListStyleDefinition_Create(TClass(wxString) name);
void wxRichTextListStyleDefinition_Delete(TSelf(wxRichTextListStyleDefinition) self);
void wxRichTextListStyleDefinition_Copy(TSelf(wxRichTextListStyleDefinition) self,
                                        TClass(wxRichTextListStyleDefinition) def);
void wxRichTextListStyleDefinition_SetLevelAttributes(TSelf(wxRichTextListStyleDefinition) self,
                                                      int level, TClass(wxRichTextAttr) attr);
TClass(wxRichTextAttr)
    wxRichTextListStyleDefinition_GetLevelAttributes(TSelf(wxRichTextListStyleDefinition) self,
                                                     int level);
void wxRichTextListStyleDefinition_SetAttributes(TSelf(wxRichTextListStyleDefinition) self,
                                                 int level, int leftIndent, int leftSubIndent,
                                                 int bulletStyle, TClass(wxString) bulletSymbol);
int wxRichTextListStyleDefinition_FindLevelForIndent(TSelf(wxRichTextListStyleDefinition) self,
                                                     int indent);
TClassOwned(wxRichTextAttr) wxRichTextListStyleDefinition_CombineWithParagraphStyle(
    TSelf(wxRichTextListStyleDefinition) self, int indent, TClass(wxRichTextAttr) paraStyle,
    TClass(wxRichTextStyleSheet) styleSheet);
TClassOwned(wxRichTextAttr)
    wxRichTextListStyleDefinition_GetCombinedStyle(TSelf(wxRichTextListStyleDefinition) self,
                                                   int indent,
                                                   TClass(wxRichTextStyleSheet) styleSheet);
TClassOwned(wxRichTextAttr) wxRichTextListStyleDefinition_GetCombinedStyleForLevel(
    TSelf(wxRichTextListStyleDefinition) self, int level, TClass(wxRichTextStyleSheet) styleSheet);
int wxRichTextListStyleDefinition_GetLevelCount(TSelf(wxRichTextListStyleDefinition) self);
TBool wxRichTextListStyleDefinition_IsNumbered(TSelf(wxRichTextListStyleDefinition) self,
                                               int level);

TClassDefExtend(wxRichTextBoxStyleDefinition, wxRichTextStyleDefinition)

    TClass(wxRichTextBoxStyleDefinition) wxRichTextBoxStyleDefinition_Create(TClass(wxString) name);
void wxRichTextBoxStyleDefinition_Delete(TSelf(wxRichTextBoxStyleDefinition) self);
void wxRichTextBoxStyleDefinition_Copy(TSelf(wxRichTextBoxStyleDefinition) self,
                                       TClass(wxRichTextBoxStyleDefinition) def);

// The Add*Style/Remove*Style members take ownership semantics from the style sheet: see
// the implementation notes in src/wx_richtextstyles.cpp.
TClass(wxRichTextStyleSheet) wxRichTextStyleSheet_Create();
TClass(wxRichTextStyleSheet) wxRichTextStyleSheet_CreateCopy(TClass(wxRichTextStyleSheet) sheet);
void wxRichTextStyleSheet_Delete(TSelf(wxRichTextStyleSheet) self);
void wxRichTextStyleSheet_Init(TSelf(wxRichTextStyleSheet) self);
void wxRichTextStyleSheet_Copy(TSelf(wxRichTextStyleSheet) self,
                               TClass(wxRichTextStyleSheet) sheet);
// the style sheet takes ownership of def; do not Delete() it afterwards.
TBool wxRichTextStyleSheet_AddCharacterStyle(TSelf(wxRichTextStyleSheet) self,
                                             TClass(wxRichTextCharacterStyleDefinition) def);
TBool wxRichTextStyleSheet_AddParagraphStyle(TSelf(wxRichTextStyleSheet) self,
                                             TClass(wxRichTextParagraphStyleDefinition) def);
TBool wxRichTextStyleSheet_AddListStyle(TSelf(wxRichTextStyleSheet) self,
                                        TClass(wxRichTextListStyleDefinition) def);
TBool wxRichTextStyleSheet_AddBoxStyle(TSelf(wxRichTextStyleSheet) self,
                                       TClass(wxRichTextBoxStyleDefinition) def);
TBool wxRichTextStyleSheet_AddStyle(TSelf(wxRichTextStyleSheet) self,
                                    TClass(wxRichTextStyleDefinition) def);
TBool wxRichTextStyleSheet_RemoveCharacterStyle(TSelf(wxRichTextStyleSheet) self,
                                                TClass(wxRichTextStyleDefinition) def,
                                                TBool deleteStyle);
TBool wxRichTextStyleSheet_RemoveParagraphStyle(TSelf(wxRichTextStyleSheet) self,
                                                TClass(wxRichTextStyleDefinition) def,
                                                TBool deleteStyle);
TBool wxRichTextStyleSheet_RemoveListStyle(TSelf(wxRichTextStyleSheet) self,
                                           TClass(wxRichTextStyleDefinition) def,
                                           TBool deleteStyle);
TBool wxRichTextStyleSheet_RemoveBoxStyle(TSelf(wxRichTextStyleSheet) self,
                                          TClass(wxRichTextStyleDefinition) def, TBool deleteStyle);
TBool wxRichTextStyleSheet_RemoveStyle(TSelf(wxRichTextStyleSheet) self,
                                       TClass(wxRichTextStyleDefinition) def, TBool deleteStyle);
TClass(wxRichTextCharacterStyleDefinition)
    wxRichTextStyleSheet_FindCharacterStyle(TSelf(wxRichTextStyleSheet) self, TClass(wxString) name,
                                            TBool recurse);
TClass(wxRichTextParagraphStyleDefinition)
    wxRichTextStyleSheet_FindParagraphStyle(TSelf(wxRichTextStyleSheet) self, TClass(wxString) name,
                                            TBool recurse);
TClass(wxRichTextListStyleDefinition)
    wxRichTextStyleSheet_FindListStyle(TSelf(wxRichTextStyleSheet) self, TClass(wxString) name,
                                       TBool recurse);
TClass(wxRichTextBoxStyleDefinition)
    wxRichTextStyleSheet_FindBoxStyle(TSelf(wxRichTextStyleSheet) self, TClass(wxString) name,
                                      TBool recurse);
TClass(wxRichTextStyleDefinition)
    wxRichTextStyleSheet_FindStyle(TSelf(wxRichTextStyleSheet) self, TClass(wxString) name,
                                   TBool recurse);
size_t wxRichTextStyleSheet_GetCharacterStyleCount(TSelf(wxRichTextStyleSheet) self);
size_t wxRichTextStyleSheet_GetParagraphStyleCount(TSelf(wxRichTextStyleSheet) self);
size_t wxRichTextStyleSheet_GetListStyleCount(TSelf(wxRichTextStyleSheet) self);
size_t wxRichTextStyleSheet_GetBoxStyleCount(TSelf(wxRichTextStyleSheet) self);
TClass(wxRichTextCharacterStyleDefinition)
    wxRichTextStyleSheet_GetCharacterStyle(TSelf(wxRichTextStyleSheet) self, size_t index);
TClass(wxRichTextParagraphStyleDefinition)
    wxRichTextStyleSheet_GetParagraphStyle(TSelf(wxRichTextStyleSheet) self, size_t index);
TClass(wxRichTextListStyleDefinition)
    wxRichTextStyleSheet_GetListStyle(TSelf(wxRichTextStyleSheet) self, size_t index);
TClass(wxRichTextBoxStyleDefinition)
    wxRichTextStyleSheet_GetBoxStyle(TSelf(wxRichTextStyleSheet) self, size_t index);
void wxRichTextStyleSheet_DeleteStyles(TSelf(wxRichTextStyleSheet) self);
TBool wxRichTextStyleSheet_InsertSheet(TSelf(wxRichTextStyleSheet) self,
                                       TClass(wxRichTextStyleSheet) before);
TBool wxRichTextStyleSheet_AppendSheet(TSelf(wxRichTextStyleSheet) self,
                                       TClass(wxRichTextStyleSheet) after);
void wxRichTextStyleSheet_Unlink(TSelf(wxRichTextStyleSheet) self);
TClass(wxRichTextStyleSheet) wxRichTextStyleSheet_GetNextSheet(TSelf(wxRichTextStyleSheet) self);
void wxRichTextStyleSheet_SetNextSheet(TSelf(wxRichTextStyleSheet) self,
                                       TClass(wxRichTextStyleSheet) sheet);
TClass(wxRichTextStyleSheet)
    wxRichTextStyleSheet_GetPreviousSheet(TSelf(wxRichTextStyleSheet) self);
void wxRichTextStyleSheet_SetPreviousSheet(TSelf(wxRichTextStyleSheet) self,
                                           TClass(wxRichTextStyleSheet) sheet);
void wxRichTextStyleSheet_SetName(TSelf(wxRichTextStyleSheet) self, TClass(wxString) name);
TClass(wxString) wxRichTextStyleSheet_GetName(TSelf(wxRichTextStyleSheet) self);
void wxRichTextStyleSheet_SetDescription(TSelf(wxRichTextStyleSheet) self, TClass(wxString) descr);
TClass(wxString) wxRichTextStyleSheet_GetDescription(TSelf(wxRichTextStyleSheet) self);
TClass(wxRichTextProperties) wxRichTextStyleSheet_GetProperties(TSelf(wxRichTextStyleSheet) self);
void wxRichTextStyleSheet_SetProperties(TSelf(wxRichTextStyleSheet) self,
                                        TClass(wxRichTextProperties) props);

TClassDefExtend(wxRichTextStyleListCtrl, wxControl)

    TClass(wxRichTextStyleListCtrl)
        wxRichTextStyleListCtrl_Create(TClass(wxWindow) parent, int id, TPoint(x, y), TSize(w, h),
                                       long style);
void wxRichTextStyleListCtrl_Delete(TSelf(wxRichTextStyleListCtrl) self);
void wxRichTextStyleListCtrl_UpdateStyles(TSelf(wxRichTextStyleListCtrl) self);
void wxRichTextStyleListCtrl_SetStyleSheet(TSelf(wxRichTextStyleListCtrl) self,
                                           TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet)
    wxRichTextStyleListCtrl_GetStyleSheet(TSelf(wxRichTextStyleListCtrl) self);
void wxRichTextStyleListCtrl_SetRichTextCtrl(TSelf(wxRichTextStyleListCtrl) self,
                                             TClass(wxRichTextCtrl) ctrl);
TClass(wxRichTextCtrl) wxRichTextStyleListCtrl_GetRichTextCtrl(TSelf(wxRichTextStyleListCtrl) self);
void wxRichTextStyleListCtrl_SetStyleType(TSelf(wxRichTextStyleListCtrl) self, int styleType);
int wxRichTextStyleListCtrl_GetStyleType(TSelf(wxRichTextStyleListCtrl) self);
TClass(wxRichTextStyleListBox)
    wxRichTextStyleListCtrl_GetStyleListBox(TSelf(wxRichTextStyleListCtrl) self);
TClass(wxChoice) wxRichTextStyleListCtrl_GetStyleChoice(TSelf(wxRichTextStyleListCtrl) self);

TClassDefExtend(wxRichTextStyleComboCtrl, wxComboCtrl)

    TClass(wxRichTextStyleComboCtrl)
        wxRichTextStyleComboCtrl_Create(TClass(wxWindow) parent, int id, TPoint(x, y), TSize(w, h),
                                        long style);
void wxRichTextStyleComboCtrl_Delete(TSelf(wxRichTextStyleComboCtrl) self);
void wxRichTextStyleComboCtrl_UpdateStyles(TSelf(wxRichTextStyleComboCtrl) self);
void wxRichTextStyleComboCtrl_SetStyleSheet(TSelf(wxRichTextStyleComboCtrl) self,
                                            TClass(wxRichTextStyleSheet) styleSheet);
TClass(wxRichTextStyleSheet)
    wxRichTextStyleComboCtrl_GetStyleSheet(TSelf(wxRichTextStyleComboCtrl) self);
void wxRichTextStyleComboCtrl_SetRichTextCtrl(TSelf(wxRichTextStyleComboCtrl) self,
                                              TClass(wxRichTextCtrl) ctrl);
TClass(wxRichTextCtrl)
    wxRichTextStyleComboCtrl_GetRichTextCtrl(TSelf(wxRichTextStyleComboCtrl) self);

TClassDefExtend(wxRichTextObjectPropertiesDialog, wxRichTextFormattingDialog)

    TClass(wxRichTextObjectPropertiesDialog)
        wxRichTextObjectPropertiesDialog_Create(TClass(wxRichTextObject) obj,
                                                TClass(wxWindow) parent, int id,
                                                TClass(wxString) caption, TRect(x, y, w, h),
                                                long style);
void wxRichTextObjectPropertiesDialog_Delete(TSelf(wxRichTextObjectPropertiesDialog) self);
