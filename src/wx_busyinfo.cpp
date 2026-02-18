#include "kwx_wrapper.h"
#include <wx/busyinfo.h>

extern "C"
{
    EXPORT void* wxBusyInfo_Create(wxString* text, wxWindow* parent)
    {
        return (void*) new wxBusyInfo(*text, parent);
    }

    EXPORT void wxBusyInfo_Delete(wxBusyInfo* pObject)
    {
        delete pObject;
    }

    EXPORT void* wxBusyCursor_Create()
    {
        return (void*) new wxBusyCursor();
    }

    EXPORT void* wxBusyCursor_CreateWithCursor(void* cursor)
    {
        return (void*) new wxBusyCursor((wxCursor*) cursor);
    }

    EXPORT void wxBusyCursor_Delete(wxBusyCursor* pObject)
    {
        delete pObject;
    }
}
