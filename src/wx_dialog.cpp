#include "wrapper.h"

extern "C"
{
    EXPORT wxDialog* wxDialog_Create(wxWindow* parent, int id, wxString* title, int x, int y,
                                     int width, int height, int style)
    {
        return new wxDialog(parent, id, *title, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT bool wxDialog_IsModal(wxDialog* self)
    {
        return self->IsModal();
    }

    EXPORT int wxDialog_ShowModal(wxDialog* self)
    {
        return self->ShowModal();
    }

    EXPORT void wxDialog_EndModal(wxDialog* self, int retCode)
    {
        self->EndModal(retCode);
    }

    EXPORT void wxDialog_SetReturnCode(wxDialog* self, int returnCode)
    {
        self->SetReturnCode(returnCode);
    }

    EXPORT int wxDialog_GetReturnCode(wxDialog* self)
    {
        return self->GetReturnCode();
    }
}
