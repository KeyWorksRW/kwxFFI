#include "wrapper.h"

extern "C"
{
    EXPORT void* wxRadioButton_Create(wxWindow* parent, int id, wxString* label, int x, int y,
                                      int width, int height, int style)
    {
        return new wxRadioButton(parent, id, *label, wxPoint(x, y), wxSize(width, height), style,
                                 wxDefaultValidator);
    }

    EXPORT void wxRadioButton_SetValue(wxRadioButton* self, bool value)
    {
        self->SetValue(value);
    }

    EXPORT bool wxRadioButton_GetValue(wxRadioButton* self)
    {
        return self->GetValue();
    }
}
