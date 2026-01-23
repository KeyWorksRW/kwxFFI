#include "wrapper.h"

extern "C"
{
    EXPORT wxColourDialog* wxColourDialog_Create(wxWindow* parent, wxColourData* col)
    {
        return new wxColourDialog(parent, col);
    }

    EXPORT void wxColourDialog_GetColourData(wxColourDialog* self, wxColourData* col)
    {
        *col = self->GetColourData();
    }
}
