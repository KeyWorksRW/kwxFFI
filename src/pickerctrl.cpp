#include "wrapper.h"
#include <wx/clrpicker.h>

extern "C"
{
    EXPORT wxColourPickerCtrl* wxColorPickerCtrl_Create(wxWindow* parent, int id,
                                                        const wxColour& colour, int x, int y, int w,
                                                        int h, int style)
    {
        return new wxColourPickerCtrl(parent, id, colour, wxPoint(x, y), wxSize(w, h), style);
    }

    EXPORT void wxColorPickerCtrl_GetColour(wxColourPickerCtrl* self, wxColour* colour)
    {
        *colour = self->GetColour();
    }

    EXPORT void wxColorPickerCtrl_SetColour(wxColourPickerCtrl* self, const wxColour& colour)
    {
        self->SetColour(colour);
    }
}
