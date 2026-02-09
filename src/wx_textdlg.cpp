#include "wrapper.h"

extern "C"
{
    EXPORT void* wxTextEntryDialog_Create(wxWindow* parent, wxString* message, wxString* caption,
                                          wxString* defaultValue, long style, int x, int y)
    {
        return new wxTextEntryDialog(parent, *message, *caption, *defaultValue, style,
                                     wxPoint(x, y));
    }

    EXPORT wxString* wxTextEntryDialog_GetValue(wxTextEntryDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetValue();
        return result;
    }

    EXPORT void wxTextEntryDialog_SetValue(wxTextEntryDialog* self, wxString* value)
    {
        self->SetValue(*value);
    }
}
