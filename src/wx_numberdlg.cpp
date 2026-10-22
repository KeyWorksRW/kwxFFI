#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxNumberEntryDialog_Create(wxWindow* parent, wxString* message, wxString* prompt,
                                            wxString* caption, long value, long min_value,
                                            long max_value, int x, int y)
    {
        wxNumberEntryDialog* dialog = new wxNumberEntryDialog();
        if (!dialog->Create(parent, *message, *prompt, *caption, value, min_value, max_value,
                            wxPoint(x, y)))
        {
            delete dialog;
            return nullptr;
        }
        return static_cast<void*>(dialog);
    }

    EXPORT long wxNumberEntryDialog_GetValue(wxNumberEntryDialog* self)
    {
        return self->GetValue();
    }

    EXPORT void wxNumberEntryDialog_Delete(wxNumberEntryDialog* self)
    {
        delete self;
    }
}
