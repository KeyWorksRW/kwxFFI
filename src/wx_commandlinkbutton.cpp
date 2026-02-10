#include "wrapper.h"

extern "C"
{
    EXPORT wxCommandLinkButton* wxCommandLinkButton_Create(wxWindow* parent, int id,
                                                           wxString* mainLabel, wxString* note,
                                                           int x, int y, int width, int height, int style)
    {
        return new wxCommandLinkButton(parent, id, *mainLabel, *note, wxPoint(x, y), wxSize(width, height),
                                       style);
    }

    EXPORT void wxCommandLinkButton_SetMainLabel(wxCommandLinkButton* self, wxString* mainLabel)
    {
        self->SetMainLabel(*mainLabel);
    }

    EXPORT void wxCommandLinkButton_SetNote(wxCommandLinkButton* self, wxString* note)
    {
        self->SetNote(*note);
    }

    EXPORT wxString* wxCommandLinkButton_GetMainLabel(wxCommandLinkButton* self)
    {
        wxString* result = new wxString();
        *result = self->GetMainLabel();
        return result;
    }

    EXPORT wxString* wxCommandLinkButton_GetNote(wxCommandLinkButton* self)
    {
        wxString* result = new wxString();
        *result = self->GetNote();
        return result;
    }
}
