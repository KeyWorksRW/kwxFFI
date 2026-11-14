// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

// Rich text object hierarchy, buffer operations and file handlers.
// Declarations: include/kwx_richtext.h

extern "C"
{
    // ------------------------------------------------------------------
    // wxRichTextObject
    // ------------------------------------------------------------------

    EXPORT wxRichTextObject* wxRichTextObject_GetParent(wxRichTextObject* self)
    {
        return self->GetParent();
    }

    EXPORT wxRichTextObject* wxRichTextObject_GetFirstChild(wxRichTextObject* self)
    {
        wxRichTextCompositeObject* composite = wxDynamicCast(self, wxRichTextCompositeObject);
        if (!composite)
        {
            return nullptr;
        }
        return composite->GetChild(0);
    }

    EXPORT wxRichTextObject* wxRichTextObject_GetNextSibling(wxRichTextObject* self)
    {
        wxRichTextObject* parent = self->GetParent();
        if (!parent)
        {
            return nullptr;
        }

        wxRichTextCompositeObject* composite = wxDynamicCast(parent, wxRichTextCompositeObject);
        if (!composite)
        {
            return nullptr;
        }

        const size_t count = composite->GetChildCount();
        for (size_t i = 0; i < count; ++i)
        {
            if (composite->GetChild(i) != self)
            {
                continue;
            }
            if (i + 1 < count)
            {
                return composite->GetChild(i + 1);
            }
            return nullptr;
        }
        return nullptr;
    }

    EXPORT void wxRichTextObject_GetPosition(wxRichTextObject* self, int* x, int* y)
    {
        wxPoint position = self->GetPosition();
        *x = position.x;
        *y = position.y;
    }

    EXPORT void wxRichTextObject_SetPosition(wxRichTextObject* self, int x, int y)
    {
        self->SetPosition(wxPoint(x, y));
    }

    EXPORT void wxRichTextObject_GetSize(wxRichTextObject* self, int* width, int* height)
    {
        wxSize size = self->GetCachedSize();
        *width = size.GetWidth();
        *height = size.GetHeight();
    }

    EXPORT void wxRichTextObject_SetSize(wxRichTextObject* self, int width, int height)
    {
        self->SetCachedSize(wxSize(width, height));
    }

    EXPORT void wxRichTextObject_GetRect(wxRichTextObject* self, int* x, int* y, int* width,
                                         int* height)
    {
        wxRect rect = self->GetRect();
        *x = rect.GetX();
        *y = rect.GetY();
        *width = rect.GetWidth();
        *height = rect.GetHeight();
    }

    EXPORT void wxRichTextObject_GetRange(wxRichTextObject* self, long* startPos, long* endPos)
    {
        const wxRichTextRange& range = self->GetRange();
        *startPos = range.GetStart();
        *endPos = range.GetEnd();
    }

    EXPORT void wxRichTextObject_SetRange(wxRichTextObject* self, long startPos, long endPos)
    {
        self->SetRange(wxRichTextRange(startPos, endPos));
    }

    EXPORT void wxRichTextObject_GetAttributes(wxRichTextObject* self, wxRichTextAttr* attr)
    {
        *attr = self->GetAttributes();
    }

    EXPORT void wxRichTextObject_SetAttributes(wxRichTextObject* self, wxRichTextAttr* attr)
    {
        self->SetAttributes(*attr);
    }

    EXPORT wxString* wxRichTextObject_GetName(wxRichTextObject* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    EXPORT void wxRichTextObject_SetName(wxRichTextObject* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxRichTextObject_GetTextForRange(wxRichTextObject* self, long startPos,
                                                      long endPos)
    {
        wxString* result = new wxString();
        *result = self->GetTextForRange(wxRichTextRange(startPos, endPos));
        return result;
    }

    EXPORT int wxRichTextObject_IsComposite(wxRichTextObject* self)
    {
        return self->IsComposite();
    }

    EXPORT int wxRichTextObject_IsEmpty(wxRichTextObject* self)
    {
        return self->IsEmpty();
    }

    EXPORT int wxRichTextObject_IsTopLevel(wxRichTextObject* self)
    {
        return self->IsTopLevel();
    }

    EXPORT int wxRichTextObject_IsShown(wxRichTextObject* self)
    {
        return self->IsShown();
    }

    EXPORT void wxRichTextObject_Show(wxRichTextObject* self, bool show)
    {
        self->Show(show);
    }

    EXPORT void wxRichTextObject_Delete(wxRichTextObject* self)
    {
        delete self;
    }

    // ------------------------------------------------------------------
    // wxRichTextCompositeObject
    // ------------------------------------------------------------------

    EXPORT size_t wxRichTextCompositeObject_GetChildCount(wxRichTextCompositeObject* self)
    {
        return self->GetChildCount();
    }

    EXPORT wxRichTextObject* wxRichTextCompositeObject_GetChild(wxRichTextCompositeObject* self,
                                                                size_t index)
    {
        return self->GetChild(index);
    }

    EXPORT wxRichTextObject*
        wxRichTextCompositeObject_GetChildAtPosition(wxRichTextCompositeObject* self, long position)
    {
        return self->GetChildAtPosition(position);
    }

    EXPORT size_t wxRichTextCompositeObject_AppendChild(wxRichTextCompositeObject* self,
                                                        wxRichTextObject* child)
    {
        return self->AppendChild(child);
    }

    EXPORT int wxRichTextCompositeObject_InsertChild(wxRichTextCompositeObject* self,
                                                     wxRichTextObject* child,
                                                     wxRichTextObject* inFrontOf)
    {
        return self->InsertChild(child, inFrontOf);
    }

    EXPORT int wxRichTextCompositeObject_RemoveChild(wxRichTextCompositeObject* self,
                                                     wxRichTextObject* child, bool deleteChild)
    {
        return self->RemoveChild(child, deleteChild);
    }

    EXPORT int wxRichTextCompositeObject_DeleteChildren(wxRichTextCompositeObject* self)
    {
        return self->DeleteChildren();
    }

    EXPORT void wxRichTextCompositeObject_Delete(wxRichTextCompositeObject* self)
    {
        delete self;
    }

    // ------------------------------------------------------------------
    // wxRichTextParagraphLayoutBox
    // ------------------------------------------------------------------

    EXPORT wxRichTextParagraphLayoutBox*
        wxRichTextParagraphLayoutBox_Create(wxRichTextObject* parent)
    {
        return new wxRichTextParagraphLayoutBox(parent);
    }

    EXPORT void wxRichTextParagraphLayoutBox_Delete(wxRichTextParagraphLayoutBox* self)
    {
        delete self;
    }

    EXPORT void wxRichTextParagraphLayoutBox_Clear(wxRichTextParagraphLayoutBox* self)
    {
        self->Clear();
    }

    EXPORT void wxRichTextParagraphLayoutBox_Reset(wxRichTextParagraphLayoutBox* self)
    {
        self->Reset();
    }

    EXPORT void wxRichTextParagraphLayoutBox_AddParagraph(wxRichTextParagraphLayoutBox* self,
                                                          wxString* text, wxRichTextAttr* paraStyle,
                                                          long* startPos, long* endPos)
    {
        wxRichTextRange range = self->AddParagraph(*text, paraStyle);
        *startPos = range.GetStart();
        *endPos = range.GetEnd();
    }

    EXPORT void wxRichTextParagraphLayoutBox_AddParagraphs(wxRichTextParagraphLayoutBox* self,
                                                           wxString* text,
                                                           wxRichTextAttr* paraStyle,
                                                           long* startPos, long* endPos)
    {
        wxRichTextRange range = self->AddParagraphs(*text, paraStyle);
        *startPos = range.GetStart();
        *endPos = range.GetEnd();
    }

    EXPORT void wxRichTextParagraphLayoutBox_AddImage(wxRichTextParagraphLayoutBox* self,
                                                      wxImage* image, wxRichTextAttr* paraStyle,
                                                      long* startPos, long* endPos)
    {
        wxRichTextRange range = self->AddImage(*image, paraStyle);
        *startPos = range.GetStart();
        *endPos = range.GetEnd();
    }

    EXPORT wxString* wxRichTextParagraphLayoutBox_GetText(wxRichTextParagraphLayoutBox* self)
    {
        wxString* result = new wxString();
        *result = self->GetText();
        return result;
    }

    EXPORT int wxRichTextParagraphLayoutBox_DeleteRange(wxRichTextParagraphLayoutBox* self,
                                                        long startPos, long endPos)
    {
        return self->DeleteRange(wxRichTextRange(startPos, endPos));
    }

    EXPORT int wxRichTextParagraphLayoutBox_SetStyle(wxRichTextParagraphLayoutBox* self,
                                                     long startPos, long endPos,
                                                     wxRichTextAttr* style, int flags)
    {
        return self->SetStyle(wxRichTextRange(startPos, endPos), *style, flags);
    }

    EXPORT int wxRichTextParagraphLayoutBox_GetStyle(wxRichTextParagraphLayoutBox* self,
                                                     long position, wxRichTextAttr* style)
    {
        return self->GetStyle(position, *style);
    }

    EXPORT int wxRichTextParagraphLayoutBox_GetUncombinedStyle(wxRichTextParagraphLayoutBox* self,
                                                               long position, wxRichTextAttr* style)
    {
        return self->GetUncombinedStyle(position, *style);
    }

    EXPORT int wxRichTextParagraphLayoutBox_GetParagraphCount(wxRichTextParagraphLayoutBox* self)
    {
        return self->GetParagraphCount();
    }

    EXPORT wxString*
        wxRichTextParagraphLayoutBox_GetParagraphText(wxRichTextParagraphLayoutBox* self,
                                                      long paragraphNumber)
    {
        wxString* result = new wxString();
        *result = self->GetParagraphText(paragraphNumber);
        return result;
    }

    EXPORT int wxRichTextParagraphLayoutBox_GetParagraphLength(wxRichTextParagraphLayoutBox* self,
                                                               long paragraphNumber)
    {
        return self->GetParagraphLength(paragraphNumber);
    }

    EXPORT long wxRichTextParagraphLayoutBox_XYToPosition(wxRichTextParagraphLayoutBox* self,
                                                          long x, long y)
    {
        return self->XYToPosition(x, y);
    }

    EXPORT int wxRichTextParagraphLayoutBox_PositionToXY(wxRichTextParagraphLayoutBox* self,
                                                         long position, long* x, long* y)
    {
        return self->PositionToXY(position, x, y);
    }

    EXPORT int wxRichTextParagraphLayoutBox_SetDefaultStyle(wxRichTextParagraphLayoutBox* self,
                                                            wxRichTextAttr* style)
    {
        return self->SetDefaultStyle(*style);
    }

    EXPORT void wxRichTextParagraphLayoutBox_GetDefaultStyle(wxRichTextParagraphLayoutBox* self,
                                                             wxRichTextAttr* style)
    {
        *style = self->GetDefaultStyle();
    }

    EXPORT void wxRichTextParagraphLayoutBox_SetBasicStyle(wxRichTextParagraphLayoutBox* self,
                                                           wxRichTextAttr* style)
    {
        self->SetBasicStyle(*style);
    }

    EXPORT void wxRichTextParagraphLayoutBox_GetBasicStyle(wxRichTextParagraphLayoutBox* self,
                                                           wxRichTextAttr* style)
    {
        *style = self->GetBasicStyle();
    }

    EXPORT wxRichTextStyleSheet*
        wxRichTextParagraphLayoutBox_GetStyleSheet(wxRichTextParagraphLayoutBox* self)
    {
        return self->GetStyleSheet();
    }

    EXPORT void wxRichTextParagraphLayoutBox_SetRichTextCtrl(wxRichTextParagraphLayoutBox* self,
                                                             wxRichTextCtrl* ctrl)
    {
        self->SetRichTextCtrl(ctrl);
    }

    EXPORT wxRichTextCtrl*
        wxRichTextParagraphLayoutBox_GetRichTextCtrl(wxRichTextParagraphLayoutBox* self)
    {
        return self->GetRichTextCtrl();
    }

    EXPORT void wxRichTextParagraphLayoutBox_SetPartialParagraph(wxRichTextParagraphLayoutBox* self,
                                                                 bool partialParagraph)
    {
        self->SetPartialParagraph(partialParagraph);
    }

    EXPORT int wxRichTextParagraphLayoutBox_GetPartialParagraph(wxRichTextParagraphLayoutBox* self)
    {
        return self->GetPartialParagraph();
    }

    EXPORT void wxRichTextParagraphLayoutBox_UpdateRanges(wxRichTextParagraphLayoutBox* self)
    {
        self->UpdateRanges();
    }

    EXPORT void* wxRichTextParagraphLayoutBox_GetBuffer(wxRichTextParagraphLayoutBox* self)
    {
        if (!self)
        {
            return nullptr;
        }
        return self->GetBuffer();
    }

    // ------------------------------------------------------------------
    // wxRichTextBox
    // ------------------------------------------------------------------

    EXPORT wxRichTextBox* wxRichTextBox_Create(wxRichTextObject* parent)
    {
        return new wxRichTextBox(parent);
    }

    EXPORT void wxRichTextBox_Delete(wxRichTextBox* self)
    {
        delete self;
    }

    EXPORT wxString* wxRichTextBox_GetXMLNodeName(wxRichTextBox* self)
    {
        wxString* result = new wxString();
        *result = self->GetXMLNodeName();
        return result;
    }

    // ------------------------------------------------------------------
    // wxRichTextTable
    // ------------------------------------------------------------------

    EXPORT wxRichTextTable* wxRichTextTable_Create(wxRichTextObject* parent)
    {
        return new wxRichTextTable(parent);
    }

    EXPORT void wxRichTextTable_Delete(wxRichTextTable* self)
    {
        delete self;
    }

    EXPORT int wxRichTextTable_GetRowCount(wxRichTextTable* self)
    {
        return self->GetRowCount();
    }

    EXPORT void wxRichTextTable_SetRowCount(wxRichTextTable* self, int count)
    {
        self->SetRowCount(count);
    }

    EXPORT int wxRichTextTable_GetColumnCount(wxRichTextTable* self)
    {
        return self->GetColumnCount();
    }

    EXPORT void wxRichTextTable_SetColumnCount(wxRichTextTable* self, int count)
    {
        self->SetColumnCount(count);
    }

    EXPORT wxRichTextCell* wxRichTextTable_GetCell(wxRichTextTable* self, int row, int col)
    {
        return self->GetCell(row, col);
    }

    EXPORT wxRichTextCell* wxRichTextTable_GetCellAtPosition(wxRichTextTable* self, long pos)
    {
        return self->GetCell(pos);
    }

    EXPORT int wxRichTextTable_GetCellRowColumnPosition(wxRichTextTable* self, long pos, int* row,
                                                        int* col)
    {
        return self->GetCellRowColumnPosition(pos, *row, *col);
    }

    EXPORT void wxRichTextTable_GetFocusedCell(wxRichTextTable* self, int* row, int* col)
    {
        wxPosition position = self->GetFocusedCell();
        *row = position.GetRow();
        *col = position.GetColumn();
    }

    EXPORT void wxRichTextTable_ClearTable(wxRichTextTable* self)
    {
        self->ClearTable();
    }

    EXPORT int wxRichTextTable_CreateTable(wxRichTextTable* self, int rows, int cols)
    {
        return self->CreateTable(rows, cols);
    }

    EXPORT int wxRichTextTable_DeleteRows(wxRichTextTable* self, int startRow, int noRows)
    {
        return self->DeleteRows(startRow, noRows);
    }

    EXPORT int wxRichTextTable_DeleteColumns(wxRichTextTable* self, int startCol, int noCols)
    {
        return self->DeleteColumns(startCol, noCols);
    }

    EXPORT int wxRichTextTable_AddRows(wxRichTextTable* self, int startRow, int noRows,
                                       wxRichTextAttr* attr)
    {
        if (attr)
        {
            return self->AddRows(startRow, noRows, *attr);
        }
        return self->AddRows(startRow, noRows);
    }

    EXPORT int wxRichTextTable_AddColumns(wxRichTextTable* self, int startCol, int noCols,
                                          wxRichTextAttr* attr)
    {
        if (attr)
        {
            return self->AddColumns(startCol, noCols, *attr);
        }
        return self->AddColumns(startCol, noCols);
    }

    EXPORT void wxRichTextTable_Copy(wxRichTextTable* self, wxRichTextTable* obj)
    {
        self->Copy(*obj);
    }

    // ------------------------------------------------------------------
    // wxRichTextCell
    // ------------------------------------------------------------------

    EXPORT wxRichTextCell* wxRichTextCell_Create(wxRichTextObject* parent)
    {
        return new wxRichTextCell(parent);
    }

    EXPORT void wxRichTextCell_Delete(wxRichTextCell* self)
    {
        delete self;
    }

    EXPORT int wxRichTextCell_GetColSpan(wxRichTextCell* self)
    {
        return self->GetColSpan();
    }

    EXPORT void wxRichTextCell_SetColSpan(wxRichTextCell* self, int span)
    {
        self->SetColSpan(span);
    }

    EXPORT int wxRichTextCell_GetRowSpan(wxRichTextCell* self)
    {
        return self->GetRowSpan();
    }

    EXPORT void wxRichTextCell_SetRowSpan(wxRichTextCell* self, int span)
    {
        self->SetRowSpan(span);
    }

    EXPORT void wxRichTextCell_Copy(wxRichTextCell* self, wxRichTextCell* obj)
    {
        self->Copy(*obj);
    }

    // ------------------------------------------------------------------
    // wxRichTextField
    // ------------------------------------------------------------------

    EXPORT wxRichTextField* wxRichTextField_Create(wxString* fieldType, wxRichTextObject* parent)
    {
        return new wxRichTextField(*fieldType, parent);
    }

    EXPORT void wxRichTextField_Delete(wxRichTextField* self)
    {
        delete self;
    }

    EXPORT void wxRichTextField_SetFieldType(wxRichTextField* self, wxString* fieldType)
    {
        self->SetFieldType(*fieldType);
    }

    EXPORT wxString* wxRichTextField_GetFieldType(wxRichTextField* self)
    {
        wxString* result = new wxString();
        *result = self->GetFieldType();
        return result;
    }

    EXPORT int wxRichTextField_UpdateField(wxRichTextField* self, wxRichTextBuffer* buffer)
    {
        return self->UpdateField(buffer);
    }

    EXPORT void wxRichTextField_Copy(wxRichTextField* self, wxRichTextField* obj)
    {
        self->Copy(*obj);
    }

    // ------------------------------------------------------------------
    // wxRichTextFieldType
    // ------------------------------------------------------------------

    EXPORT void wxRichTextFieldType_SetName(wxRichTextFieldType* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxRichTextFieldType_GetName(wxRichTextFieldType* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    EXPORT void wxRichTextFieldType_Copy(wxRichTextFieldType* self, wxRichTextFieldType* fieldType)
    {
        self->Copy(*fieldType);
    }

    // ------------------------------------------------------------------
    // wxRichTextFieldTypeStandard
    // ------------------------------------------------------------------

    EXPORT wxRichTextFieldTypeStandard*
        wxRichTextFieldTypeStandard_Create(wxString* name, wxString* label, int displayStyle)
    {
        return new wxRichTextFieldTypeStandard(*name, *label, displayStyle);
    }

    EXPORT wxRichTextFieldTypeStandard*
        wxRichTextFieldTypeStandard_CreateWithBitmap(wxString* name, wxBitmap* bitmap,
                                                     int displayStyle)
    {
        return new wxRichTextFieldTypeStandard(*name, *bitmap, displayStyle);
    }

    EXPORT wxRichTextFieldTypeStandard* wxRichTextFieldTypeStandard_CreateDefault()
    {
        return new wxRichTextFieldTypeStandard();
    }

    EXPORT void wxRichTextFieldTypeStandard_Delete(wxRichTextFieldTypeStandard* self)
    {
        delete self;
    }

    EXPORT void wxRichTextFieldTypeStandard_Copy(wxRichTextFieldTypeStandard* self,
                                                 wxRichTextFieldTypeStandard* field)
    {
        self->Copy(*field);
    }

    EXPORT void wxRichTextFieldTypeStandard_SetLabel(wxRichTextFieldTypeStandard* self,
                                                     wxString* label)
    {
        self->SetLabel(*label);
    }

    EXPORT wxString* wxRichTextFieldTypeStandard_GetLabel(wxRichTextFieldTypeStandard* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    EXPORT void wxRichTextFieldTypeStandard_SetBitmap(wxRichTextFieldTypeStandard* self,
                                                      wxBitmap* bitmap)
    {
        self->SetBitmap(*bitmap);
    }

    EXPORT wxBitmap* wxRichTextFieldTypeStandard_GetBitmap(wxRichTextFieldTypeStandard* self)
    {
        return const_cast<wxBitmap*>(&self->GetBitmap());
    }

    EXPORT int wxRichTextFieldTypeStandard_GetDisplayStyle(wxRichTextFieldTypeStandard* self)
    {
        return self->GetDisplayStyle();
    }

    EXPORT void wxRichTextFieldTypeStandard_SetDisplayStyle(wxRichTextFieldTypeStandard* self,
                                                            int displayStyle)
    {
        self->SetDisplayStyle(displayStyle);
    }

    EXPORT wxFont* wxRichTextFieldTypeStandard_GetFont(wxRichTextFieldTypeStandard* self)
    {
        return const_cast<wxFont*>(&self->GetFont());
    }

    EXPORT void wxRichTextFieldTypeStandard_SetFont(wxRichTextFieldTypeStandard* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT void wxRichTextFieldTypeStandard_GetTextColour(wxRichTextFieldTypeStandard* self,
                                                          wxColour* colour)
    {
        *colour = self->GetTextColour();
    }

    EXPORT void wxRichTextFieldTypeStandard_SetTextColour(wxRichTextFieldTypeStandard* self,
                                                          wxColour* colour)
    {
        self->SetTextColour(*colour);
    }

    EXPORT void wxRichTextFieldTypeStandard_GetBorderColour(wxRichTextFieldTypeStandard* self,
                                                            wxColour* colour)
    {
        *colour = self->GetBorderColour();
    }

    EXPORT void wxRichTextFieldTypeStandard_SetBorderColour(wxRichTextFieldTypeStandard* self,
                                                            wxColour* colour)
    {
        self->SetBorderColour(*colour);
    }

    EXPORT void wxRichTextFieldTypeStandard_GetBackgroundColour(wxRichTextFieldTypeStandard* self,
                                                                wxColour* colour)
    {
        *colour = self->GetBackgroundColour();
    }

    EXPORT void wxRichTextFieldTypeStandard_SetBackgroundColour(wxRichTextFieldTypeStandard* self,
                                                                wxColour* colour)
    {
        self->SetBackgroundColour(*colour);
    }

    EXPORT void wxRichTextFieldTypeStandard_SetVerticalPadding(wxRichTextFieldTypeStandard* self,
                                                               int padding)
    {
        self->SetVerticalPadding(padding);
    }

    EXPORT int wxRichTextFieldTypeStandard_GetVerticalPadding(wxRichTextFieldTypeStandard* self)
    {
        return self->GetVerticalPadding();
    }

    EXPORT void wxRichTextFieldTypeStandard_SetHorizontalPadding(wxRichTextFieldTypeStandard* self,
                                                                 int padding)
    {
        self->SetHorizontalPadding(padding);
    }

    EXPORT int wxRichTextFieldTypeStandard_GetHorizontalPadding(wxRichTextFieldTypeStandard* self)
    {
        return self->GetHorizontalPadding();
    }

    EXPORT void wxRichTextFieldTypeStandard_SetHorizontalMargin(wxRichTextFieldTypeStandard* self,
                                                                int margin)
    {
        self->SetHorizontalMargin(margin);
    }

    EXPORT int wxRichTextFieldTypeStandard_GetHorizontalMargin(wxRichTextFieldTypeStandard* self)
    {
        return self->GetHorizontalMargin();
    }

    EXPORT void wxRichTextFieldTypeStandard_SetVerticalMargin(wxRichTextFieldTypeStandard* self,
                                                              int margin)
    {
        self->SetVerticalMargin(margin);
    }

    EXPORT int wxRichTextFieldTypeStandard_GetVerticalMargin(wxRichTextFieldTypeStandard* self)
    {
        return self->GetVerticalMargin();
    }

    // ------------------------------------------------------------------
    // wxRichTextDrawingHandler
    // ------------------------------------------------------------------

    EXPORT void wxRichTextDrawingHandler_SetName(wxRichTextDrawingHandler* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxRichTextDrawingHandler_GetName(wxRichTextDrawingHandler* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    // ------------------------------------------------------------------
    // wxRichTextImageBlock
    // ------------------------------------------------------------------

    EXPORT wxRichTextImageBlock* wxRichTextImageBlock_Create()
    {
        return new wxRichTextImageBlock();
    }

    EXPORT void wxRichTextImageBlock_Delete(wxRichTextImageBlock* self)
    {
        delete self;
    }

    EXPORT void wxRichTextImageBlock_Clear(wxRichTextImageBlock* self)
    {
        self->Clear();
    }

    EXPORT int wxRichTextImageBlock_IsOk(wxRichTextImageBlock* self)
    {
        return self->IsOk();
    }

    EXPORT size_t wxRichTextImageBlock_GetDataSize(wxRichTextImageBlock* self)
    {
        return self->GetDataSize();
    }

    // ------------------------------------------------------------------
    // wxRichTextImage
    // ------------------------------------------------------------------

    EXPORT wxRichTextImage* wxRichTextImage_Create(wxRichTextObject* parent)
    {
        return new wxRichTextImage(parent);
    }

    EXPORT wxRichTextImage* wxRichTextImage_CreateFromImage(wxImage* image,
                                                            wxRichTextObject* parent,
                                                            wxRichTextAttr* charStyle)
    {
        return new wxRichTextImage(*image, parent, charStyle);
    }

    EXPORT wxRichTextImage* wxRichTextImage_CreateFromImageBlock(wxRichTextImageBlock* imageBlock,
                                                                 wxRichTextObject* parent,
                                                                 wxRichTextAttr* charStyle)
    {
        return new wxRichTextImage(*imageBlock, parent, charStyle);
    }

    EXPORT void wxRichTextImage_Delete(wxRichTextImage* self)
    {
        delete self;
    }

    EXPORT void wxRichTextImage_GetImageCache(wxRichTextImage* self, wxBitmap* bitmap)
    {
        *bitmap = self->GetImageCache();
    }

    EXPORT void wxRichTextImage_SetImageCache(wxRichTextImage* self, wxBitmap* bitmap)
    {
        self->SetImageCache(*bitmap);
    }

    EXPORT wxRichTextImageBlock* wxRichTextImage_GetImageBlock(wxRichTextImage* self)
    {
        return &self->GetImageBlock();
    }

    EXPORT void wxRichTextImage_GetOriginalImageSize(wxRichTextImage* self, int* width, int* height)
    {
        wxSize size = self->GetOriginalImageSize();
        *width = size.GetWidth();
        *height = size.GetHeight();
    }

    EXPORT void wxRichTextImage_SetOriginalImageSize(wxRichTextImage* self, int width, int height)
    {
        self->SetOriginalImageSize(wxSize(width, height));
    }

    EXPORT int wxRichTextImage_GetImageState(wxRichTextImage* self)
    {
        return self->GetImageState();
    }

    EXPORT void wxRichTextImage_SetImageState(wxRichTextImage* self, int state)
    {
        self->SetImageState(state);
    }

    // ------------------------------------------------------------------
    // wxRichTextBuffer
    // ------------------------------------------------------------------

    EXPORT wxRichTextBuffer* wxRichTextBuffer_Create()
    {
        return new wxRichTextBuffer();
    }

    EXPORT void wxRichTextBuffer_Delete(wxRichTextBuffer* self)
    {
        delete self;
    }

    EXPORT void wxRichTextBuffer_AddParagraph(wxRichTextBuffer* self, wxString* text,
                                              wxRichTextAttr* paraStyle, long* startPos,
                                              long* endPos)
    {
        wxRichTextRange range = self->AddParagraph(*text, paraStyle);
        *startPos = range.GetStart();
        *endPos = range.GetEnd();
    }

    EXPORT int wxRichTextBuffer_DeleteRange(wxRichTextBuffer* self, long startPos, long endPos)
    {
        return self->DeleteRange(wxRichTextRange(startPos, endPos));
    }

    EXPORT void wxRichTextBuffer_GetRange(wxRichTextBuffer* self, long* startPos, long* endPos)
    {
        const wxRichTextRange& range = self->GetRange();
        *startPos = range.GetStart();
        *endPos = range.GetEnd();
    }

    EXPORT wxString* wxRichTextBuffer_GetText(wxRichTextBuffer* self)
    {
        wxString* result = new wxString();
        *result = self->GetText();
        return result;
    }

    EXPORT void wxRichTextBuffer_Clear(wxRichTextBuffer* self)
    {
        self->Clear();
    }

    EXPORT int wxRichTextBuffer_LoadFile(wxRichTextBuffer* self, wxString* filename, int type)
    {
        return self->LoadFile(*filename, static_cast<wxRichTextFileType>(type));
    }

    EXPORT int wxRichTextBuffer_SaveFile(wxRichTextBuffer* self, wxString* filename, int type)
    {
        return self->SaveFile(*filename, static_cast<wxRichTextFileType>(type));
    }

    EXPORT void wxRichTextBuffer_ResetAndClearCommands(wxRichTextBuffer* self)
    {
        self->ResetAndClearCommands();
    }

    EXPORT void wxRichTextBuffer_SetStyleSheet(wxRichTextBuffer* self,
                                               wxRichTextStyleSheet* styleSheet)
    {
        self->SetStyleSheet(styleSheet);
    }

    EXPORT wxRichTextStyleSheet* wxRichTextBuffer_GetStyleSheet(wxRichTextBuffer* self)
    {
        return self->GetStyleSheet();
    }

    EXPORT int wxRichTextBuffer_SetStyleSheetAndNotify(wxRichTextBuffer* self,
                                                       wxRichTextStyleSheet* sheet)
    {
        return self->SetStyleSheetAndNotify(sheet);
    }

    EXPORT int wxRichTextBuffer_PushStyleSheet(wxRichTextBuffer* self,
                                               wxRichTextStyleSheet* styleSheet)
    {
        return self->PushStyleSheet(styleSheet);
    }

    EXPORT wxRichTextStyleSheet* wxRichTextBuffer_PopStyleSheet(wxRichTextBuffer* self)
    {
        return self->PopStyleSheet();
    }

    EXPORT void wxRichTextBuffer_SetHandlerFlags(wxRichTextBuffer* self, int flags)
    {
        self->SetHandlerFlags(flags);
    }

    EXPORT int wxRichTextBuffer_GetHandlerFlags(wxRichTextBuffer* self)
    {
        return self->GetHandlerFlags();
    }

    EXPORT void wxRichTextBuffer_SetFontScale(wxRichTextBuffer* self, double fontScale)
    {
        self->SetFontScale(fontScale);
    }

    EXPORT double wxRichTextBuffer_GetFontScale(wxRichTextBuffer* self)
    {
        return self->GetFontScale();
    }

    EXPORT void wxRichTextBuffer_SetDimensionScale(wxRichTextBuffer* self, double dimScale)
    {
        self->SetDimensionScale(dimScale);
    }

    EXPORT double wxRichTextBuffer_GetDimensionScale(wxRichTextBuffer* self)
    {
        return self->GetDimensionScale();
    }

    EXPORT int wxRichTextBuffer_BeginBatchUndo(wxRichTextBuffer* self, wxString* cmdName)
    {
        return self->BeginBatchUndo(*cmdName);
    }

    EXPORT int wxRichTextBuffer_EndBatchUndo(wxRichTextBuffer* self)
    {
        return self->EndBatchUndo();
    }

    EXPORT int wxRichTextBuffer_BatchingUndo(wxRichTextBuffer* self)
    {
        return self->BatchingUndo();
    }

    EXPORT int wxRichTextBuffer_BeginSuppressUndo(wxRichTextBuffer* self)
    {
        return self->BeginSuppressUndo();
    }

    EXPORT int wxRichTextBuffer_EndSuppressUndo(wxRichTextBuffer* self)
    {
        return self->EndSuppressUndo();
    }

    EXPORT int wxRichTextBuffer_SuppressingUndo(wxRichTextBuffer* self)
    {
        return self->SuppressingUndo();
    }

    EXPORT wxString* wxRichTextBuffer_GetExtWildcard(int combine, int save, wxArrayInt* types)
    {
        wxArrayInt collected_types;
        const wxString result = wxRichTextBuffer::GetExtWildcard(
            combine != 0, save != 0, types ? &collected_types : nullptr);
        if (types)
        {
            *types = collected_types;
        }
        return new wxString(result);
    }

    // ------------------------------------------------------------------
    // wxRichTextAttr and the text-box attribute classes
    // ------------------------------------------------------------------
    // These factories exist so a caller can obtain a genuine wxRichTextAttr. Before them
    // the generated binding only had wxTextAttr for these parameters, so passing a
    // wxTextAttr where wxRichTextAttr is expected corrupted the heap instead of failing to
    // compile.

    EXPORT wxRichTextAttr* wxRichTextAttr_Create()
    {
        return new wxRichTextAttr();
    }

    EXPORT wxRichTextAttr* wxRichTextAttr_CreateFromTextAttr(wxTextAttr* attr)
    {
        return new wxRichTextAttr(*attr);
    }

    EXPORT wxRichTextAttr* wxRichTextAttr_CreateCopy(wxRichTextAttr* attr)
    {
        return new wxRichTextAttr(*attr);
    }

    EXPORT void wxRichTextAttr_Delete(wxRichTextAttr* self)
    {
        delete self;
    }

    EXPORT void wxRichTextAttr_Copy(wxRichTextAttr* self, wxRichTextAttr* attr)
    {
        self->Copy(*attr);
    }

    EXPORT wxTextBoxAttr* wxRichTextAttr_GetTextBoxAttr(wxRichTextAttr* self)
    {
        return &self->GetTextBoxAttr();
    }

    EXPORT void wxRichTextAttr_SetTextBoxAttr(wxRichTextAttr* self, wxTextBoxAttr* attr)
    {
        self->SetTextBoxAttr(*attr);
    }

    EXPORT int wxRichTextAttr_HasTextBoxAttr(wxRichTextAttr* self)
    {
        return !self->GetTextBoxAttr().IsDefault();
    }

    EXPORT void wxTextAttrDimension_Reset(wxTextAttrDimension* self)
    {
        self->Reset();
    }

    EXPORT int wxTextAttrDimension_GetValue(wxTextAttrDimension* self)
    {
        return self->GetValue();
    }

    EXPORT void wxTextAttrDimension_SetValue(wxTextAttrDimension* self, int value)
    {
        self->SetValue(value);
    }

    EXPORT void wxTextAttrDimension_SetValueWithUnits(wxTextAttrDimension* self, int value,
                                                      int units)
    {
        self->SetValue(value, static_cast<wxTextAttrUnits>(units));
    }

    EXPORT int wxTextAttrDimension_GetUnits(wxTextAttrDimension* self)
    {
        return self->GetUnits();
    }

    EXPORT void wxTextAttrDimension_SetUnits(wxTextAttrDimension* self, int units)
    {
        self->SetUnits(static_cast<wxTextAttrUnits>(units));
    }

    EXPORT int wxTextAttrDimension_IsValid(wxTextAttrDimension* self)
    {
        return self->IsValid();
    }

    EXPORT void wxTextAttrDimensions_Reset(wxTextAttrDimensions* self)
    {
        self->Reset();
    }

    EXPORT wxTextAttrDimension* wxTextAttrDimensions_GetLeft(wxTextAttrDimensions* self)
    {
        return &self->GetLeft();
    }

    EXPORT wxTextAttrDimension* wxTextAttrDimensions_GetTop(wxTextAttrDimensions* self)
    {
        return &self->GetTop();
    }

    EXPORT wxTextAttrDimension* wxTextAttrDimensions_GetRight(wxTextAttrDimensions* self)
    {
        return &self->GetRight();
    }

    EXPORT wxTextAttrDimension* wxTextAttrDimensions_GetBottom(wxTextAttrDimensions* self)
    {
        return &self->GetBottom();
    }

    EXPORT int wxTextAttrDimensions_IsValid(wxTextAttrDimensions* self)
    {
        return self->IsValid();
    }

    EXPORT void wxTextAttrBorder_Reset(wxTextAttrBorder* self)
    {
        self->Reset();
    }

    EXPORT void wxTextAttrBorder_SetStyle(wxTextAttrBorder* self, int style)
    {
        self->SetStyle(style);
    }

    EXPORT int wxTextAttrBorder_GetStyle(wxTextAttrBorder* self)
    {
        return self->GetStyle();
    }

    EXPORT void wxTextAttrBorder_SetColour(wxTextAttrBorder* self, wxColour* colour)
    {
        self->SetColour(*colour);
    }

    EXPORT void wxTextAttrBorder_GetColour(wxTextAttrBorder* self, wxColour* colour)
    {
        *colour = self->GetColour();
    }

    EXPORT void wxTextAttrBorder_SetColourLong(wxTextAttrBorder* self, unsigned long colour)
    {
        self->SetColour(colour);
    }

    EXPORT unsigned long wxTextAttrBorder_GetColourLong(wxTextAttrBorder* self)
    {
        return self->GetColourLong();
    }

    EXPORT void wxTextAttrBorder_SetWidth(wxTextAttrBorder* self, int value, int units)
    {
        self->SetWidth(value, static_cast<wxTextAttrUnits>(units));
    }

    EXPORT wxTextAttrDimension* wxTextAttrBorder_GetWidth(wxTextAttrBorder* self)
    {
        return &self->GetWidth();
    }

    EXPORT int wxTextAttrBorder_HasStyle(wxTextAttrBorder* self)
    {
        return self->HasStyle();
    }

    EXPORT int wxTextAttrBorder_HasColour(wxTextAttrBorder* self)
    {
        return self->HasColour();
    }

    EXPORT int wxTextAttrBorder_HasWidth(wxTextAttrBorder* self)
    {
        return self->HasWidth();
    }

    EXPORT int wxTextAttrBorder_IsDefault(wxTextAttrBorder* self)
    {
        return self->IsDefault();
    }

    EXPORT void wxTextAttrBorders_Reset(wxTextAttrBorders* self)
    {
        self->Reset();
    }

    EXPORT void wxTextAttrBorders_SetStyle(wxTextAttrBorders* self, int style)
    {
        self->SetStyle(style);
    }

    EXPORT void wxTextAttrBorders_SetColour(wxTextAttrBorders* self, wxColour* colour)
    {
        self->SetColour(*colour);
    }

    EXPORT void wxTextAttrBorders_SetColourLong(wxTextAttrBorders* self, unsigned long colour)
    {
        self->SetColour(colour);
    }

    EXPORT void wxTextAttrBorders_SetWidth(wxTextAttrBorders* self, int value, int units)
    {
        self->SetWidth(value, static_cast<wxTextAttrUnits>(units));
    }

    EXPORT wxTextAttrBorder* wxTextAttrBorders_GetLeft(wxTextAttrBorders* self)
    {
        return &self->GetLeft();
    }

    EXPORT wxTextAttrBorder* wxTextAttrBorders_GetTop(wxTextAttrBorders* self)
    {
        return &self->GetTop();
    }

    EXPORT wxTextAttrBorder* wxTextAttrBorders_GetRight(wxTextAttrBorders* self)
    {
        return &self->GetRight();
    }

    EXPORT wxTextAttrBorder* wxTextAttrBorders_GetBottom(wxTextAttrBorders* self)
    {
        return &self->GetBottom();
    }

    EXPORT int wxTextAttrBorders_IsValid(wxTextAttrBorders* self)
    {
        return self->IsValid();
    }

    EXPORT int wxTextAttrBorders_IsDefault(wxTextAttrBorders* self)
    {
        return self->IsDefault();
    }

    EXPORT void wxTextBoxAttr_Reset(wxTextBoxAttr* self)
    {
        self->Reset();
    }

    EXPORT int wxTextBoxAttr_IsDefault(wxTextBoxAttr* self)
    {
        return self->IsDefault();
    }

    EXPORT void wxTextBoxAttr_SetFlags(wxTextBoxAttr* self, int flags)
    {
        self->SetFlags(flags);
    }

    EXPORT int wxTextBoxAttr_GetFlags(wxTextBoxAttr* self)
    {
        return self->GetFlags();
    }

    EXPORT int wxTextBoxAttr_HasFlag(wxTextBoxAttr* self, int flag)
    {
        return self->HasFlag(static_cast<wxTextBoxAttrFlags>(flag));
    }

    EXPORT void wxTextBoxAttr_AddFlag(wxTextBoxAttr* self, int flag)
    {
        self->AddFlag(static_cast<wxTextBoxAttrFlags>(flag));
    }

    EXPORT void wxTextBoxAttr_RemoveFlag(wxTextBoxAttr* self, int flag)
    {
        self->RemoveFlag(static_cast<wxTextBoxAttrFlags>(flag));
    }

    EXPORT void wxTextBoxAttr_SetFloatMode(wxTextBoxAttr* self, int mode)
    {
        self->SetFloatMode(static_cast<wxTextBoxAttrFloatStyle>(mode));
    }

    EXPORT int wxTextBoxAttr_GetFloatMode(wxTextBoxAttr* self)
    {
        return self->GetFloatMode();
    }

    EXPORT int wxTextBoxAttr_IsFloating(wxTextBoxAttr* self)
    {
        return self->IsFloating();
    }

    EXPORT void wxTextBoxAttr_SetClearMode(wxTextBoxAttr* self, int mode)
    {
        self->SetClearMode(static_cast<wxTextBoxAttrClearStyle>(mode));
    }

    EXPORT int wxTextBoxAttr_GetClearMode(wxTextBoxAttr* self)
    {
        return self->GetClearMode();
    }

    EXPORT wxTextAttrDimensions* wxTextBoxAttr_GetMargins(wxTextBoxAttr* self)
    {
        return &self->GetMargins();
    }

    EXPORT void wxTextBoxAttr_SetMargins(wxTextBoxAttr* self, wxTextAttrDimensions* margins)
    {
        self->GetMargins() = *margins;
    }

    EXPORT wxTextAttrDimensions* wxTextBoxAttr_GetPadding(wxTextBoxAttr* self)
    {
        return &self->GetPadding();
    }

    EXPORT void wxTextBoxAttr_SetPadding(wxTextBoxAttr* self, wxTextAttrDimensions* padding)
    {
        self->GetPadding() = *padding;
    }

    EXPORT wxTextAttrBorders* wxTextBoxAttr_GetBorder(wxTextBoxAttr* self)
    {
        return &self->GetBorder();
    }

    EXPORT wxTextAttrBorder* wxTextBoxAttr_GetLeftBorder(wxTextBoxAttr* self)
    {
        return &self->GetLeftBorder();
    }

    EXPORT wxTextAttrBorder* wxTextBoxAttr_GetTopBorder(wxTextBoxAttr* self)
    {
        return &self->GetTopBorder();
    }

    EXPORT wxTextAttrBorder* wxTextBoxAttr_GetRightBorder(wxTextBoxAttr* self)
    {
        return &self->GetRightBorder();
    }

    EXPORT wxTextAttrBorder* wxTextBoxAttr_GetBottomBorder(wxTextBoxAttr* self)
    {
        return &self->GetBottomBorder();
    }

    EXPORT wxTextAttrDimension* wxTextBoxAttr_GetWidth(wxTextBoxAttr* self)
    {
        return &self->GetWidth();
    }

    EXPORT wxTextAttrDimension* wxTextBoxAttr_GetHeight(wxTextBoxAttr* self)
    {
        return &self->GetHeight();
    }

    EXPORT wxTextAttrDimension* wxTextBoxAttr_GetLeft(wxTextBoxAttr* self)
    {
        return &self->GetLeft();
    }

    EXPORT wxTextAttrDimension* wxTextBoxAttr_GetTop(wxTextBoxAttr* self)
    {
        return &self->GetTop();
    }

    EXPORT wxTextAttrDimension* wxTextBoxAttr_GetRight(wxTextBoxAttr* self)
    {
        return &self->GetRight();
    }

    EXPORT wxTextAttrDimension* wxTextBoxAttr_GetBottom(wxTextBoxAttr* self)
    {
        return &self->GetBottom();
    }

    EXPORT wxString* wxTextBoxAttr_GetBoxStyleName(wxTextBoxAttr* self)
    {
        return new wxString(self->GetBoxStyleName());
    }

    EXPORT void wxTextBoxAttr_SetBoxStyleName(wxTextBoxAttr* self, wxString* name)
    {
        self->SetBoxStyleName(*name);
    }

    // ------------------------------------------------------------------
    // wxRichTextFileHandler
    // ------------------------------------------------------------------

    EXPORT wxString* wxRichTextFileHandler_GetName(wxRichTextFileHandler* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    EXPORT void wxRichTextFileHandler_SetName(wxRichTextFileHandler* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT wxString* wxRichTextFileHandler_GetExtension(wxRichTextFileHandler* self)
    {
        wxString* result = new wxString();
        *result = self->GetExtension();
        return result;
    }

    EXPORT void wxRichTextFileHandler_SetExtension(wxRichTextFileHandler* self, wxString* ext)
    {
        self->SetExtension(*ext);
    }

    EXPORT int wxRichTextFileHandler_GetType(wxRichTextFileHandler* self)
    {
        return self->GetType();
    }

    EXPORT void wxRichTextFileHandler_SetType(wxRichTextFileHandler* self, int type)
    {
        self->SetType(type);
    }

    EXPORT int wxRichTextFileHandler_GetFlags(wxRichTextFileHandler* self)
    {
        return self->GetFlags();
    }

    EXPORT void wxRichTextFileHandler_SetFlags(wxRichTextFileHandler* self, int flags)
    {
        self->SetFlags(flags);
    }

    EXPORT void wxRichTextFileHandler_SetEncoding(wxRichTextFileHandler* self, wxString* encoding)
    {
        self->SetEncoding(*encoding);
    }

    EXPORT wxString* wxRichTextFileHandler_GetEncoding(wxRichTextFileHandler* self)
    {
        wxString* result = new wxString();
        *result = self->GetEncoding();
        return result;
    }

    EXPORT int wxRichTextFileHandler_CanHandle(wxRichTextFileHandler* self, wxString* filename)
    {
        return self->CanHandle(*filename);
    }

    EXPORT int wxRichTextFileHandler_CanLoad(wxRichTextFileHandler* self)
    {
        return self->CanLoad();
    }

    EXPORT int wxRichTextFileHandler_CanSave(wxRichTextFileHandler* self)
    {
        return self->CanSave();
    }

    EXPORT int wxRichTextFileHandler_IsVisible(wxRichTextFileHandler* self)
    {
        return self->IsVisible();
    }

    EXPORT void wxRichTextFileHandler_SetVisible(wxRichTextFileHandler* self, bool visible)
    {
        self->SetVisible(visible);
    }

    EXPORT void wxRichTextFileHandler_Delete(wxRichTextFileHandler* self)
    {
        delete self;
    }

    // ------------------------------------------------------------------
    // wxRichTextXMLHandler
    // ------------------------------------------------------------------

    EXPORT wxRichTextXMLHandler* wxRichTextXMLHandler_Create(wxString* name, wxString* ext,
                                                             int type)
    {
        return new wxRichTextXMLHandler(*name, *ext, type);
    }

    EXPORT void wxRichTextXMLHandler_Delete(wxRichTextXMLHandler* self)
    {
        delete self;
    }

    // ------------------------------------------------------------------
    // wxRichTextHTMLHandler
    // ------------------------------------------------------------------

    EXPORT wxRichTextHTMLHandler* wxRichTextHTMLHandler_Create(wxString* name, wxString* ext,
                                                               int type)
    {
        return new wxRichTextHTMLHandler(*name, *ext, type);
    }

    EXPORT void wxRichTextHTMLHandler_Delete(wxRichTextHTMLHandler* self)
    {
        delete self;
    }

    EXPORT int wxRichTextHTMLHandler_CanHandle(wxRichTextHTMLHandler* self, wxString* filename)
    {
        return self->CanHandle(*filename);
    }

    EXPORT void wxRichTextHTMLHandler_ClearTemporaryImageLocations(wxRichTextHTMLHandler* self)
    {
        self->ClearTemporaryImageLocations();
    }

    EXPORT int wxRichTextHTMLHandler_DeleteTemporaryImages(wxRichTextHTMLHandler* self)
    {
        return self->DeleteTemporaryImages();
    }

    EXPORT void wxRichTextHTMLHandler_SetTempDir(wxRichTextHTMLHandler* self, wxString* tempDir)
    {
        self->SetTempDir(*tempDir);
    }

    EXPORT wxString* wxRichTextHTMLHandler_GetTempDir(wxRichTextHTMLHandler* self)
    {
        wxString* result = new wxString();
        *result = self->GetTempDir();
        return result;
    }

    EXPORT void wxRichTextHTMLHandler_SetFontSizeMapping(wxRichTextHTMLHandler* self,
                                                         wxArrayInt* mapping)
    {
        self->SetFontSizeMapping(*mapping);
    }

    EXPORT wxArrayInt* wxRichTextHTMLHandler_GetFontSizeMapping(wxRichTextHTMLHandler* self)
    {
        return new wxArrayInt(self->GetFontSizeMapping());
    }

    // ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
    EXPORT void wxRichTextBuffer_AddHandler(void* handler)
    {
        wxRichTextBuffer::AddHandler((wxRichTextFileHandler*) handler);
    }

    // The field-type and drawing-handler registries own the registered objects; the
    // wrappers below must therefore never be paired with a Delete call by the caller.
    EXPORT void wxRichTextBuffer_AddFieldType(wxRichTextFieldType* fieldType)
    {
        wxRichTextBuffer::AddFieldType(fieldType);
    }

    EXPORT int wxRichTextBuffer_RemoveFieldType(wxString* name)
    {
        return wxRichTextBuffer::RemoveFieldType(*name);
    }

    EXPORT wxRichTextFieldType* wxRichTextBuffer_FindFieldType(wxString* name)
    {
        return wxRichTextBuffer::FindFieldType(*name);
    }

    EXPORT void wxRichTextBuffer_AddDrawingHandler(wxRichTextDrawingHandler* handler)
    {
        wxRichTextBuffer::AddDrawingHandler(handler);
    }

    EXPORT void wxRichTextBuffer_InsertDrawingHandler(wxRichTextDrawingHandler* handler)
    {
        wxRichTextBuffer::InsertDrawingHandler(handler);
    }

    EXPORT int wxRichTextBuffer_RemoveDrawingHandler(wxString* name)
    {
        return wxRichTextBuffer::RemoveDrawingHandler(*name);
    }

    EXPORT wxRichTextDrawingHandler* wxRichTextBuffer_FindDrawingHandler(wxString* name)
    {
        return wxRichTextBuffer::FindDrawingHandler(*name);
    }

    EXPORT int wxRichTextFileHandler_SaveFile(void* pObject, void* buffer, void* stream)
    {
        return ((wxRichTextFileHandler*) pObject)
            ->SaveFile((wxRichTextBuffer*) buffer, *(wxOutputStream*) stream);
    }

    // Borrowed subobject of the object -- never delete the returned pointer. Returning the
    // reference (rather than a copy) lets the caller mutate the object's own property set,
    // which is how wxRichTextCtrl::PrepareContent tags content for CanDeleteRange /
    // CanInsertContent / the drawing handler.
    EXPORT void* wxRichTextObject_GetProperties(void* pObject)
    {
        return &((wxRichTextObject*) pObject)->GetProperties();
    }

    EXPORT void* wxRichTextParagraphLayoutBox_GetLeafObjectAtPosition(void* pObject, long position)
    {
        return (void*) ((wxRichTextParagraphLayoutBox*) pObject)->GetLeafObjectAtPosition(position);
    }

    // ------------------------------------------------------------------
    // wxRichTextProperties
    // ------------------------------------------------------------------

    EXPORT wxRichTextProperties* wxRichTextProperties_Create()
    {
        return new wxRichTextProperties();
    }

    EXPORT wxRichTextProperties* wxRichTextProperties_CreateCopy(wxRichTextProperties* props)
    {
        return new wxRichTextProperties(*props);
    }

    EXPORT void wxRichTextProperties_Delete(wxRichTextProperties* self)
    {
        delete self;
    }

    EXPORT void wxRichTextProperties_Copy(wxRichTextProperties* self, wxRichTextProperties* props)
    {
        self->Copy(*props);
    }

    EXPORT void wxRichTextProperties_Clear(wxRichTextProperties* self)
    {
        self->Clear();
    }

    EXPORT size_t wxRichTextProperties_GetCount(wxRichTextProperties* self)
    {
        return self->GetCount();
    }

    EXPORT int wxRichTextProperties_HasProperty(wxRichTextProperties* self, wxString* name)
    {
        return self->HasProperty(*name);
    }

    EXPORT int wxRichTextProperties_Find(wxRichTextProperties* self, wxString* name)
    {
        return self->Find(*name);
    }

    EXPORT int wxRichTextProperties_Remove(wxRichTextProperties* self, wxString* name)
    {
        return self->Remove(*name);
    }

    EXPORT wxString* wxRichTextProperties_GetPropertyString(wxRichTextProperties* self,
                                                            wxString* name)
    {
        wxString* result = new wxString();
        *result = self->GetPropertyString(*name);
        return result;
    }

    EXPORT long wxRichTextProperties_GetPropertyLong(wxRichTextProperties* self, wxString* name)
    {
        return self->GetPropertyLong(*name);
    }

    EXPORT int wxRichTextProperties_GetPropertyBool(wxRichTextProperties* self, wxString* name)
    {
        return self->GetPropertyBool(*name);
    }

    EXPORT double wxRichTextProperties_GetPropertyDouble(wxRichTextProperties* self, wxString* name)
    {
        return self->GetPropertyDouble(*name);
    }

    EXPORT void wxRichTextProperties_SetPropertyString(wxRichTextProperties* self, wxString* name,
                                                       wxString* value)
    {
        self->SetProperty(*name, *value);
    }

    EXPORT void wxRichTextProperties_SetPropertyLong(wxRichTextProperties* self, wxString* name,
                                                     long value)
    {
        self->SetProperty(*name, value);
    }

    EXPORT void wxRichTextProperties_SetPropertyBool(wxRichTextProperties* self, wxString* name,
                                                     bool value)
    {
        self->SetProperty(*name, value);
    }

    EXPORT void wxRichTextProperties_SetPropertyDouble(wxRichTextProperties* self, wxString* name,
                                                       double value)
    {
        self->SetProperty(*name, value);
    }

    EXPORT wxArrayString* wxRichTextProperties_GetPropertyNames(wxRichTextProperties* self)
    {
        return new wxArrayString(self->GetPropertyNames());
    }

    EXPORT void wxRichTextProperties_RemoveProperties(wxRichTextProperties* self,
                                                      wxRichTextProperties* props)
    {
        self->RemoveProperties(*props);
    }

    EXPORT void wxRichTextProperties_MergeProperties(wxRichTextProperties* self,
                                                     wxRichTextProperties* props)
    {
        self->MergeProperties(*props);
    }
}
