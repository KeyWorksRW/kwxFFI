#include "wrapper.h"

extern "C"
{
    EXPORT void wxControl_SetLabel(wxControl* self, wxString* text)
    {
        self->SetLabel(*text);
    }

    EXPORT wxString* wxControl_GetLabel(wxControl* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    EXPORT void wxControl_Command(wxControl* self, wxCommandEvent* event)
    {
        self->Command(*event);
    }
}
