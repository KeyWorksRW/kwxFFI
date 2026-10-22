#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxHtmlEasyPrinting* wxHtmlEasyPrinting_Create(wxString* name, wxWindow* parentWindow)
    {
        return new wxHtmlEasyPrinting(*name, parentWindow);
    }

    EXPORT void wxHtmlEasyPrinting_Delete(wxHtmlEasyPrinting* self)
    {
        delete self;
    }

    EXPORT bool wxHtmlEasyPrinting_PreviewFile(wxHtmlEasyPrinting* self, wxString* htmlfile)
    {
        return self->PreviewFile(*htmlfile);
    }

    EXPORT bool wxHtmlEasyPrinting_PreviewText(wxHtmlEasyPrinting* self, wxString* htmltext,
                                               wxString* basepath)
    {
        return self->PreviewText(*htmltext, *basepath);
    }

    EXPORT bool wxHtmlEasyPrinting_PrintFile(wxHtmlEasyPrinting* self, wxString* htmlfile)
    {
        return self->PrintFile(*htmlfile);
    }

    EXPORT bool wxHtmlEasyPrinting_PrintText(wxHtmlEasyPrinting* self, wxString* htmltext,
                                             wxString* basepath)
    {
        return self->PrintText(*htmltext, *basepath);
    }

    EXPORT void wxHtmlEasyPrinting_PageSetup(wxHtmlEasyPrinting* self)
    {
        self->PageSetup();
    }

    EXPORT void wxHtmlEasyPrinting_SetHeader(wxHtmlEasyPrinting* self, wxString* header, int pg)
    {
        self->SetHeader(*header, pg);
    }

    EXPORT void wxHtmlEasyPrinting_SetFooter(wxHtmlEasyPrinting* self, wxString* footer, int pg)
    {
        self->SetFooter(*footer, pg);
    }

    EXPORT void wxHtmlEasyPrinting_SetFonts(wxHtmlEasyPrinting* self, wxString* normal_face,
                                            wxString* fixed_face, int* sizes)
    {
        self->SetFonts(*normal_face, *fixed_face, sizes);
    }

    EXPORT void wxHtmlEasyPrinting_SetStandardFonts(wxHtmlEasyPrinting* self, int size,
                                                    wxString* normal_face, wxString* fixed_face)
    {
        self->SetStandardFonts(size, *normal_face, *fixed_face);
    }

    EXPORT wxPrintData* wxHtmlEasyPrinting_GetPrintData(wxHtmlEasyPrinting* self)
    {
        return self->GetPrintData();
    }

    EXPORT wxPageSetupDialogData* wxHtmlEasyPrinting_GetPageSetupData(wxHtmlEasyPrinting* self)
    {
        return self->GetPageSetupData();
    }

    EXPORT wxWindow* wxHtmlEasyPrinting_GetParentWindow(wxHtmlEasyPrinting* self)
    {
        return self->GetParentWindow();
    }

    EXPORT void wxHtmlEasyPrinting_SetParentWindow(wxHtmlEasyPrinting* self, wxWindow* window)
    {
        self->SetParentWindow(window);
    }

    EXPORT wxString* wxHtmlEasyPrinting_GetName(wxHtmlEasyPrinting* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT void wxHtmlEasyPrinting_SetName(wxHtmlEasyPrinting* self, wxString* name)
    {
        self->SetName(*name);
    }

    EXPORT void wxHtmlEasyPrinting_SetPromptMode(wxHtmlEasyPrinting* self, int promptMode)
    {
        self->SetPromptMode(static_cast<wxHtmlEasyPrinting::PromptMode>(promptMode));
    }

    EXPORT wxHtmlPrintout* wxHtmlPrintout_Create(wxString* title)
    {
        return new wxHtmlPrintout(*title);
    }

    EXPORT void wxHtmlPrintout_Delete(wxHtmlPrintout* self)
    {
        delete self;
    }

    EXPORT void wxHtmlPrintout_SetHtmlFile(wxHtmlPrintout* self, wxString* htmlfile)
    {
        self->SetHtmlFile(*htmlfile);
    }

    EXPORT void wxHtmlPrintout_SetHtmlText(wxHtmlPrintout* self, wxString* html, wxString* basepath,
                                           bool isdir)
    {
        self->SetHtmlText(*html, *basepath, isdir);
    }

    EXPORT void wxHtmlPrintout_SetHeader(wxHtmlPrintout* self, wxString* header, int pg)
    {
        self->SetHeader(*header, pg);
    }

    EXPORT void wxHtmlPrintout_SetFooter(wxHtmlPrintout* self, wxString* footer, int pg)
    {
        self->SetFooter(*footer, pg);
    }

    EXPORT void wxHtmlPrintout_SetFonts(wxHtmlPrintout* self, wxString* normal_face,
                                        wxString* fixed_face, int* sizes)
    {
        self->SetFonts(*normal_face, *fixed_face, sizes);
    }

    EXPORT void wxHtmlPrintout_SetStandardFonts(wxHtmlPrintout* self, int size,
                                                wxString* normal_face, wxString* fixed_face)
    {
        self->SetStandardFonts(size, *normal_face, *fixed_face);
    }

    EXPORT void wxHtmlPrintout_SetMargins(wxHtmlPrintout* self, float top, float bottom, float left,
                                          float right, float spaces)
    {
        self->SetMargins(top, bottom, left, right, spaces);
    }
}
