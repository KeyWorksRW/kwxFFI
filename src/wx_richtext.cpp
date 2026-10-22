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

    EXPORT bool wxRichTextObject_IsComposite(wxRichTextObject* self)
    {
        return self->IsComposite();
    }

    EXPORT bool wxRichTextObject_IsEmpty(wxRichTextObject* self)
    {
        return self->IsEmpty();
    }

    EXPORT bool wxRichTextObject_IsTopLevel(wxRichTextObject* self)
    {
        return self->IsTopLevel();
    }

    EXPORT bool wxRichTextObject_IsShown(wxRichTextObject* self)
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

    EXPORT bool wxRichTextCompositeObject_InsertChild(wxRichTextCompositeObject* self,
                                                      wxRichTextObject* child,
                                                      wxRichTextObject* inFrontOf)
    {
        return self->InsertChild(child, inFrontOf);
    }

    EXPORT bool wxRichTextCompositeObject_RemoveChild(wxRichTextCompositeObject* self,
                                                      wxRichTextObject* child, bool deleteChild)
    {
        return self->RemoveChild(child, deleteChild);
    }

    EXPORT bool wxRichTextCompositeObject_DeleteChildren(wxRichTextCompositeObject* self)
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

    EXPORT bool wxRichTextParagraphLayoutBox_DeleteRange(wxRichTextParagraphLayoutBox* self,
                                                         long startPos, long endPos)
    {
        return self->DeleteRange(wxRichTextRange(startPos, endPos));
    }

    EXPORT bool wxRichTextParagraphLayoutBox_SetStyle(wxRichTextParagraphLayoutBox* self,
                                                      long startPos, long endPos,
                                                      wxRichTextAttr* style, int flags)
    {
        return self->SetStyle(wxRichTextRange(startPos, endPos), *style, flags);
    }

    EXPORT bool wxRichTextParagraphLayoutBox_GetStyle(wxRichTextParagraphLayoutBox* self,
                                                      long position, wxRichTextAttr* style)
    {
        return self->GetStyle(position, *style);
    }

    EXPORT bool wxRichTextParagraphLayoutBox_GetUncombinedStyle(wxRichTextParagraphLayoutBox* self,
                                                                long position,
                                                                wxRichTextAttr* style)
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

    EXPORT bool wxRichTextParagraphLayoutBox_PositionToXY(wxRichTextParagraphLayoutBox* self,
                                                          long position, long* x, long* y)
    {
        return self->PositionToXY(position, x, y);
    }

    EXPORT bool wxRichTextParagraphLayoutBox_SetDefaultStyle(wxRichTextParagraphLayoutBox* self,
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

    EXPORT bool wxRichTextParagraphLayoutBox_GetPartialParagraph(wxRichTextParagraphLayoutBox* self)
    {
        return self->GetPartialParagraph();
    }

    EXPORT void wxRichTextParagraphLayoutBox_UpdateRanges(wxRichTextParagraphLayoutBox* self)
    {
        self->UpdateRanges();
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

    EXPORT bool wxRichTextImageBlock_IsOk(wxRichTextImageBlock* self)
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

    EXPORT bool wxRichTextBuffer_DeleteRange(wxRichTextBuffer* self, long startPos, long endPos)
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

    EXPORT bool wxRichTextBuffer_LoadFile(wxRichTextBuffer* self, wxString* filename, int type)
    {
        return self->LoadFile(*filename, static_cast<wxRichTextFileType>(type));
    }

    EXPORT bool wxRichTextBuffer_SaveFile(wxRichTextBuffer* self, wxString* filename, int type)
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

    EXPORT bool wxRichTextBuffer_SetStyleSheetAndNotify(wxRichTextBuffer* self,
                                                        wxRichTextStyleSheet* sheet)
    {
        return self->SetStyleSheetAndNotify(sheet);
    }

    EXPORT bool wxRichTextBuffer_PushStyleSheet(wxRichTextBuffer* self,
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

    EXPORT bool wxRichTextBuffer_BeginBatchUndo(wxRichTextBuffer* self, wxString* cmdName)
    {
        return self->BeginBatchUndo(*cmdName);
    }

    EXPORT bool wxRichTextBuffer_EndBatchUndo(wxRichTextBuffer* self)
    {
        return self->EndBatchUndo();
    }

    EXPORT bool wxRichTextBuffer_BatchingUndo(wxRichTextBuffer* self)
    {
        return self->BatchingUndo();
    }

    EXPORT bool wxRichTextBuffer_BeginSuppressUndo(wxRichTextBuffer* self)
    {
        return self->BeginSuppressUndo();
    }

    EXPORT bool wxRichTextBuffer_EndSuppressUndo(wxRichTextBuffer* self)
    {
        return self->EndSuppressUndo();
    }

    EXPORT bool wxRichTextBuffer_SuppressingUndo(wxRichTextBuffer* self)
    {
        return self->SuppressingUndo();
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

    EXPORT bool wxRichTextFileHandler_CanHandle(wxRichTextFileHandler* self, wxString* filename)
    {
        return self->CanHandle(*filename);
    }

    EXPORT bool wxRichTextFileHandler_CanLoad(wxRichTextFileHandler* self)
    {
        return self->CanLoad();
    }

    EXPORT bool wxRichTextFileHandler_CanSave(wxRichTextFileHandler* self)
    {
        return self->CanSave();
    }

    EXPORT bool wxRichTextFileHandler_IsVisible(wxRichTextFileHandler* self)
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

    EXPORT bool wxRichTextHTMLHandler_CanHandle(wxRichTextHTMLHandler* self, wxString* filename)
    {
        return self->CanHandle(*filename);
    }

    EXPORT void wxRichTextHTMLHandler_ClearTemporaryImageLocations(wxRichTextHTMLHandler* self)
    {
        self->ClearTemporaryImageLocations();
    }

    EXPORT bool wxRichTextHTMLHandler_DeleteTemporaryImages(wxRichTextHTMLHandler* self)
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
}
