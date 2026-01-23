#include "wrapper.h"
#include <wx/tipwin.h>

extern "C"
{
    EXPORT void* wxTipWindow_Create(wxWindow* parent, wxString* text, int maxLength)
    {
        return (void*) new wxTipWindow(parent, *text, (wxCoord) maxLength);
    }

    EXPORT void wxTipWindow_SetTipWindowPtr(void* _obj, void* windowPtr)
    {
        ((wxTipWindow*) _obj)->SetTipWindowPtr((wxTipWindow**) windowPtr);
    }

    EXPORT void wxTipWindow_SetBoundingRect(void* _obj, int x, int y, int w, int h)
    {
        ((wxTipWindow*) _obj)->SetBoundingRect(wxRect(x, y, w, h));
    }

    EXPORT void wxTipWindow_Close(void* _obj)
    {
        ((wxTipWindow*) _obj)->Close();
    }
}
