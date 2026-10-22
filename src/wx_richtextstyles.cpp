// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

// Rich text style list box and buffer data object.
// Declarations: include/kwx_richtext.h

extern "C"
{
    // ------------------------------------------------------------------
    // wxRichTextStyleListBox
    // ------------------------------------------------------------------

    EXPORT wxRichTextStyleListBox* wxRichTextStyleListBox_Create(wxWindow* parent, int windowId,
                                                                 int x, int y, int width,
                                                                 int height, long style)
    {
        return new wxRichTextStyleListBox(parent, windowId, wxPoint(x, y), wxSize(width, height),
                                          style);
    }

    EXPORT void wxRichTextStyleListBox_Delete(wxRichTextStyleListBox* self)
    {
        delete self;
    }

    EXPORT void wxRichTextStyleListBox_SetStyleSheet(wxRichTextStyleListBox* self,
                                                     wxRichTextStyleSheet* styleSheet)
    {
        self->SetStyleSheet(styleSheet);
    }

    EXPORT wxRichTextStyleSheet* wxRichTextStyleListBox_GetStyleSheet(wxRichTextStyleListBox* self)
    {
        return self->GetStyleSheet();
    }

    EXPORT void wxRichTextStyleListBox_SetRichTextCtrl(wxRichTextStyleListBox* self,
                                                       wxRichTextCtrl* ctrl)
    {
        self->SetRichTextCtrl(ctrl);
    }

    EXPORT wxRichTextCtrl* wxRichTextStyleListBox_GetRichTextCtrl(wxRichTextStyleListBox* self)
    {
        return self->GetRichTextCtrl();
    }

    EXPORT wxRichTextStyleDefinition* wxRichTextStyleListBox_GetStyle(wxRichTextStyleListBox* self,
                                                                      size_t index)
    {
        return self->GetStyle(index);
    }

    EXPORT int wxRichTextStyleListBox_GetIndexForStyle(wxRichTextStyleListBox* self, wxString* name)
    {
        return self->GetIndexForStyle(*name);
    }

    EXPORT int wxRichTextStyleListBox_SetStyleSelection(wxRichTextStyleListBox* self,
                                                        wxString* name)
    {
        return self->SetStyleSelection(*name);
    }

    EXPORT void wxRichTextStyleListBox_UpdateStyles(wxRichTextStyleListBox* self)
    {
        self->UpdateStyles();
    }

    EXPORT void wxRichTextStyleListBox_ApplyStyle(wxRichTextStyleListBox* self, int index)
    {
        self->ApplyStyle(index);
    }

    EXPORT void wxRichTextStyleListBox_SetApplyOnSelection(wxRichTextStyleListBox* self,
                                                           bool applyOnSelection)
    {
        self->SetApplyOnSelection(applyOnSelection);
    }

    EXPORT bool wxRichTextStyleListBox_GetApplyOnSelection(wxRichTextStyleListBox* self)
    {
        return self->GetApplyOnSelection();
    }

    EXPORT void wxRichTextStyleListBox_SetStyleType(wxRichTextStyleListBox* self, int styleType)
    {
        self->SetStyleType(static_cast<wxRichTextStyleListBox::wxRichTextStyleType>(styleType));
    }

    EXPORT int wxRichTextStyleListBox_GetStyleType(wxRichTextStyleListBox* self)
    {
        return static_cast<int>(self->GetStyleType());
    }

    EXPORT void wxRichTextStyleListBox_SetAutoSetSelection(wxRichTextStyleListBox* self,
                                                           bool autoSet)
    {
        self->SetAutoSetSelection(autoSet);
    }

    EXPORT bool wxRichTextStyleListBox_CanAutoSetSelection(wxRichTextStyleListBox* self)
    {
        return self->CanAutoSetSelection();
    }

    // ------------------------------------------------------------------
    // wxRichTextBufferDataObject
    // ------------------------------------------------------------------

    EXPORT wxRichTextBufferDataObject*
        wxRichTextBufferDataObject_Create(wxRichTextBuffer* richTextBuffer)
    {
        return new wxRichTextBufferDataObject(richTextBuffer);
    }

    EXPORT void wxRichTextBufferDataObject_Delete(wxRichTextBufferDataObject* self)
    {
        delete self;
    }

    EXPORT wxRichTextBuffer*
        wxRichTextBufferDataObject_GetRichTextBuffer(wxRichTextBufferDataObject* self)
    {
        return self->GetRichTextBuffer();
    }

    EXPORT wxString* wxRichTextBufferDataObject_GetRichTextBufferFormatId(
        [[maybe_unused]] wxRichTextBufferDataObject* self)
    {
        wxString* result = new wxString();
        *result = wxString(wxRichTextBufferDataObject::GetRichTextBufferFormatId());
        return result;
    }

    EXPORT size_t wxRichTextBufferDataObject_GetDataSize(wxRichTextBufferDataObject* self)
    {
        return self->GetDataSize();
    }
}
