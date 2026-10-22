// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

// Rich text header/footer data and printing.
// Declarations: include/kwx_richtext.h

extern "C"
{
    // ------------------------------------------------------------------
    // wxRichTextHeaderFooterData
    // ------------------------------------------------------------------

    EXPORT wxRichTextHeaderFooterData* wxRichTextHeaderFooterData_Create()
    {
        return new wxRichTextHeaderFooterData();
    }

    EXPORT void wxRichTextHeaderFooterData_Delete(wxRichTextHeaderFooterData* self)
    {
        delete self;
    }

    EXPORT void wxRichTextHeaderFooterData_SetHeaderText(wxRichTextHeaderFooterData* self,
                                                         wxString* text, int page, int location)
    {
        self->SetHeaderText(*text, static_cast<wxRichTextOddEvenPage>(page),
                            static_cast<wxRichTextPageLocation>(location));
    }

    EXPORT wxString* wxRichTextHeaderFooterData_GetHeaderText(wxRichTextHeaderFooterData* self,
                                                              int page, int location)
    {
        wxString* result = new wxString();
        *result = self->GetHeaderText(static_cast<wxRichTextOddEvenPage>(page),
                                      static_cast<wxRichTextPageLocation>(location));
        return result;
    }

    EXPORT void wxRichTextHeaderFooterData_SetFooterText(wxRichTextHeaderFooterData* self,
                                                         wxString* text, int page, int location)
    {
        self->SetFooterText(*text, static_cast<wxRichTextOddEvenPage>(page),
                            static_cast<wxRichTextPageLocation>(location));
    }

    EXPORT wxString* wxRichTextHeaderFooterData_GetFooterText(wxRichTextHeaderFooterData* self,
                                                              int page, int location)
    {
        wxString* result = new wxString();
        *result = self->GetFooterText(static_cast<wxRichTextOddEvenPage>(page),
                                      static_cast<wxRichTextPageLocation>(location));
        return result;
    }

    EXPORT void wxRichTextHeaderFooterData_SetText(wxRichTextHeaderFooterData* self, wxString* text,
                                                   int headerFooter, int page, int location)
    {
        self->SetText(*text, headerFooter, static_cast<wxRichTextOddEvenPage>(page),
                      static_cast<wxRichTextPageLocation>(location));
    }

    EXPORT wxString* wxRichTextHeaderFooterData_GetText(wxRichTextHeaderFooterData* self,
                                                        int headerFooter, int page, int location)
    {
        wxString* result = new wxString();
        *result = self->GetText(headerFooter, static_cast<wxRichTextOddEvenPage>(page),
                                static_cast<wxRichTextPageLocation>(location));
        return result;
    }

    EXPORT void wxRichTextHeaderFooterData_SetMargins(wxRichTextHeaderFooterData* self,
                                                      int headerMargin, int footerMargin)
    {
        self->SetMargins(headerMargin, footerMargin);
    }

    EXPORT int wxRichTextHeaderFooterData_GetHeaderMargin(wxRichTextHeaderFooterData* self)
    {
        return self->GetHeaderMargin();
    }

    EXPORT int wxRichTextHeaderFooterData_GetFooterMargin(wxRichTextHeaderFooterData* self)
    {
        return self->GetFooterMargin();
    }

    EXPORT void wxRichTextHeaderFooterData_SetShowOnFirstPage(wxRichTextHeaderFooterData* self,
                                                              bool showOnFirstPage)
    {
        self->SetShowOnFirstPage(showOnFirstPage);
    }

    EXPORT bool wxRichTextHeaderFooterData_GetShowOnFirstPage(wxRichTextHeaderFooterData* self)
    {
        return self->GetShowOnFirstPage();
    }

    EXPORT void wxRichTextHeaderFooterData_Clear(wxRichTextHeaderFooterData* self)
    {
        self->Clear();
    }

    EXPORT void wxRichTextHeaderFooterData_SetFont(wxRichTextHeaderFooterData* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT void wxRichTextHeaderFooterData_GetFont(wxRichTextHeaderFooterData* self, wxFont* font)
    {
        *font = self->GetFont();
    }

    EXPORT void wxRichTextHeaderFooterData_SetTextColour(wxRichTextHeaderFooterData* self,
                                                         wxColour* colour)
    {
        self->SetTextColour(*colour);
    }

    EXPORT void wxRichTextHeaderFooterData_GetTextColour(wxRichTextHeaderFooterData* self,
                                                         wxColour* colour)
    {
        *colour = self->GetTextColour();
    }

    // ------------------------------------------------------------------
    // wxRichTextPrinting
    // ------------------------------------------------------------------

    EXPORT wxRichTextPrinting* wxRichTextPrinting_Create(wxString* name, wxWindow* parentWindow)
    {
        return new wxRichTextPrinting(*name, parentWindow);
    }

    EXPORT void wxRichTextPrinting_Delete(wxRichTextPrinting* self)
    {
        delete self;
    }

    EXPORT bool wxRichTextPrinting_PreviewFile(wxRichTextPrinting* self, wxString* richTextFile)
    {
        return self->PreviewFile(*richTextFile);
    }

    EXPORT bool wxRichTextPrinting_PrintFile(wxRichTextPrinting* self, wxString* richTextFile,
                                             bool showPrintDialog)
    {
        return self->PrintFile(*richTextFile, showPrintDialog);
    }

    EXPORT void wxRichTextPrinting_PageSetup(wxRichTextPrinting* self)
    {
        self->PageSetup();
    }

    EXPORT void wxRichTextPrinting_SetHeaderFooterData(wxRichTextPrinting* self,
                                                       wxRichTextHeaderFooterData* data)
    {
        self->SetHeaderFooterData(*data);
    }

    EXPORT void wxRichTextPrinting_GetHeaderFooterData(wxRichTextPrinting* self,
                                                       wxRichTextHeaderFooterData* data)
    {
        *data = self->GetHeaderFooterData();
    }

    EXPORT void wxRichTextPrinting_SetHeaderText(wxRichTextPrinting* self, wxString* text, int page,
                                                 int location)
    {
        self->SetHeaderText(*text, static_cast<wxRichTextOddEvenPage>(page),
                            static_cast<wxRichTextPageLocation>(location));
    }

    EXPORT wxString* wxRichTextPrinting_GetHeaderText(wxRichTextPrinting* self, int page,
                                                      int location)
    {
        wxString* result = new wxString();
        *result = self->GetHeaderText(static_cast<wxRichTextOddEvenPage>(page),
                                      static_cast<wxRichTextPageLocation>(location));
        return result;
    }

    EXPORT void wxRichTextPrinting_SetFooterText(wxRichTextPrinting* self, wxString* text, int page,
                                                 int location)
    {
        self->SetFooterText(*text, static_cast<wxRichTextOddEvenPage>(page),
                            static_cast<wxRichTextPageLocation>(location));
    }

    EXPORT wxString* wxRichTextPrinting_GetFooterText(wxRichTextPrinting* self, int page,
                                                      int location)
    {
        wxString* result = new wxString();
        *result = self->GetFooterText(static_cast<wxRichTextOddEvenPage>(page),
                                      static_cast<wxRichTextPageLocation>(location));
        return result;
    }

    EXPORT void wxRichTextPrinting_SetShowOnFirstPage(wxRichTextPrinting* self, bool show)
    {
        self->SetShowOnFirstPage(show);
    }

    EXPORT void wxRichTextPrinting_SetHeaderFooterFont(wxRichTextPrinting* self, wxFont* font)
    {
        self->SetHeaderFooterFont(*font);
    }

    EXPORT void wxRichTextPrinting_SetHeaderFooterTextColour(wxRichTextPrinting* self,
                                                             wxColour* colour)
    {
        self->SetHeaderFooterTextColour(*colour);
    }

    EXPORT wxPrintData* wxRichTextPrinting_GetPrintData(wxRichTextPrinting* self)
    {
        return self->GetPrintData();
    }

    EXPORT wxPageSetupDialogData* wxRichTextPrinting_GetPageSetupData(wxRichTextPrinting* self)
    {
        return self->GetPageSetupData();
    }

    EXPORT void wxRichTextPrinting_SetPrintData(wxRichTextPrinting* self, wxPrintData* printData)
    {
        self->SetPrintData(*printData);
    }

    EXPORT void wxRichTextPrinting_SetPageSetupData(wxRichTextPrinting* self,
                                                    wxPageSetupDialogData* pageSetupData)
    {
        self->SetPageSetupData(*pageSetupData);
    }

    EXPORT void wxRichTextPrinting_SetRichTextBufferPreview(wxRichTextPrinting* self,
                                                            wxRichTextBuffer* buffer)
    {
        self->SetRichTextBufferPreview(buffer);
    }

    EXPORT wxRichTextBuffer* wxRichTextPrinting_GetRichTextBufferPreview(wxRichTextPrinting* self)
    {
        return self->GetRichTextBufferPreview();
    }

    EXPORT void wxRichTextPrinting_SetRichTextBufferPrinting(wxRichTextPrinting* self,
                                                             wxRichTextBuffer* buffer)
    {
        self->SetRichTextBufferPrinting(buffer);
    }

    EXPORT wxRichTextBuffer* wxRichTextPrinting_GetRichTextBufferPrinting(wxRichTextPrinting* self)
    {
        return self->GetRichTextBufferPrinting();
    }

    EXPORT void wxRichTextPrinting_SetParentWindow(wxRichTextPrinting* self, wxWindow* parent)
    {
        self->SetParentWindow(parent);
    }

    EXPORT wxWindow* wxRichTextPrinting_GetParentWindow(wxRichTextPrinting* self)
    {
        return self->GetParentWindow();
    }

    EXPORT void wxRichTextPrinting_SetTitle(wxRichTextPrinting* self, wxString* title)
    {
        self->SetTitle(*title);
    }

    EXPORT wxString* wxRichTextPrinting_GetTitle(wxRichTextPrinting* self)
    {
        wxString* result = new wxString();
        *result = self->GetTitle();
        return result;
    }

    EXPORT void wxRichTextPrinting_SetPreviewRect(wxRichTextPrinting* self, int x, int y, int width,
                                                  int height)
    {
        self->SetPreviewRect(wxRect(x, y, width, height));
    }

    EXPORT void wxRichTextPrinting_GetPreviewRect(wxRichTextPrinting* self, int* x, int* y,
                                                  int* width, int* height)
    {
        const wxRect& rect = self->GetPreviewRect();
        *x = rect.GetX();
        *y = rect.GetY();
        *width = rect.GetWidth();
        *height = rect.GetHeight();
    }
}
