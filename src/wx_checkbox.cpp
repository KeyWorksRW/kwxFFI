#include "wrapper.h"

extern "C"
{
    EXPORT void* wxCheckBox_Create(wxWindow* parent, int id, wxString* text, int x, int y,
                                   int width, int height, int style)
    {
        return (void*) new wxCheckBox(parent, id, *text, wxPoint(x, y), wxSize(width, height),
                                      style, wxDefaultValidator);
    }

    EXPORT void wxCheckBox_Delete(wxCheckBox* self)
    {
        delete self;
    }

    EXPORT void wxCheckBox_SetValue(wxCheckBox* self, bool value)
    {
        self->SetValue(value);
    }

    EXPORT bool wxCheckBox_GetValue(wxCheckBox* self)
    {
        return self->GetValue();
    }

    EXPORT int wxCheckBox_Get3StateValue(wxCheckBox* self)
    {
        return static_cast<int>(self->Get3StateValue());
    }

    EXPORT bool wxCheckBox_Is3State(wxCheckBox* self)
    {
        return self->Is3State();
    }

    EXPORT void wxCheckBox_Set3StateValue(wxCheckBox* self, int state)
    {
        self->Set3StateValue(static_cast<wxCheckBoxState>(state));
    }
}
