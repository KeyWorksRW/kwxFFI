#include "wrapper.h"
#include <wx/busyinfo.h>

extern "C"
{
    EXPORT void* wxBusyInfo_Create(wxString* _txt)
    {
        return (void*) new wxBusyInfo(*_txt);
    }

    EXPORT void wxBusyInfo_Delete(wxBusyInfo* _obj)
    {
        delete _obj;
    }

    EXPORT void* wxBusyCursor_Create()
    {
        return (void*) new wxBusyCursor();
    }

    EXPORT void* wxBusyCursor_CreateWithCursor(void* _cur)
    {
        return (void*) new wxBusyCursor((wxCursor*) _cur);
    }

    EXPORT void wxBusyCursor_Delete(wxBusyCursor* _obj)
    {
        delete _obj;
    }
}
