#include "wrapper.h"
#include <wx/clrpicker.h>

extern "C"
{
    EXPORT wxColourPickerCtrl* wxColorPickerCtrl_Create(wxWindow* parent, int id,
                                                        const wxColour& colour, int x, int y, int width,
                                                        int height, int style)
    {
        return new wxColourPickerCtrl(parent, id, colour, wxPoint(x, y), wxSize(width, height), style);
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
