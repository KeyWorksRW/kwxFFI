#include "wrapper.h"

extern "C"
{
    EXPORT void* wxDirDialog_Create(wxWindow* parent, wxString* message, wxString* defaultPath,
                                    int x, int y, int style)
    {
        return (void*) new wxDirDialog(parent, *message, *defaultPath, style, wxPoint(x, y));
    }

    EXPORT void wxDirDialog_SetMessage(void* _obj, wxString* msg)
    {
        ((wxDirDialog*) _obj)->SetMessage(*msg);
    }

    EXPORT void wxDirDialog_SetPath(void* _obj, wxString* pth)
    {
        ((wxDirDialog*) _obj)->SetPath(*pth);
    }

    EXPORT void wxDirDialog_SetStyle(void* _obj, int style)
    {
#if WXWIN_COMPATIBILITY_2_6
        ((wxDirDialog*) _obj)->SetStyle((long) style);
#endif
    }

    EXPORT wxString* wxDirDialog_GetMessage(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxDirDialog*) _obj)->GetMessage();
        return result;
    }

    EXPORT wxString* wxDirDialog_GetPath(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxDirDialog*) _obj)->GetPath();
        return result;
    }

    EXPORT int wxDirDialog_GetStyle(void* _obj)
    {
#if WXWIN_COMPATIBILITY_2_6
        return (int) ((wxDirDialog*) _obj)->GetStyle();
#else
        return 0;
#endif
    }
}
