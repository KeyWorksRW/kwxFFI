#include "wrapper.h"

extern "C"
{
    EXPORT void* wxMessageDialog_Create(wxWindow* parent, wxString* message, wxString* caption,
                                        int style)
    {
        return new wxMessageDialog(parent, *message, *caption, style);
    }

    EXPORT void wxMessageDialog_Delete(void* _obj)
    {
        delete (wxMessageDialog*) _obj;
    }

    EXPORT int wxMessageDialog_ShowModal(void* _obj)
    {
        return ((wxMessageDialog*) _obj)->ShowModal();
    }
}
