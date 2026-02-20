#include "kwx_wrapper.h"

// wxDirDialog inherits from wxDialog (wxTopLevelWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxDirDialog_Create(wxWindow* parent, wxString* message, wxString* defaultPath,
                                    int x, int y, int style)
    {
        return (void*) new wxDirDialog(parent, *message, *defaultPath, style, wxPoint(x, y));
    }

    EXPORT void wxDirDialog_SetMessage(void* pObject, wxString* msg)
    {
        ((wxDirDialog*) pObject)->SetMessage(*msg);
    }

    EXPORT void wxDirDialog_SetPath(void* pObject, wxString* pth)
    {
        ((wxDirDialog*) pObject)->SetPath(*pth);
    }

    EXPORT void wxDirDialog_SetStyle(void* pObject, int style)
    {
#if WXWIN_COMPATIBILITY_2_6
        ((wxDirDialog*) pObject)->SetStyle((long) style);
#endif
    }

    EXPORT wxString* wxDirDialog_GetMessage(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxDirDialog*) pObject)->GetMessage();
        return result;
    }

    EXPORT wxString* wxDirDialog_GetPath(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxDirDialog*) pObject)->GetPath();
        return result;
    }

    EXPORT int wxDirDialog_GetStyle(void* pObject)
    {
#if WXWIN_COMPATIBILITY_2_6
        return (int) ((wxDirDialog*) pObject)->GetStyle();
#else
        return 0;
#endif
    }

    EXPORT int wxDirDialog_GetPaths(wxDirDialog* self, void* paths)
    {
        wxArrayString arr;
        self->GetPaths(arr);
        if (paths)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((const char**) paths)[i] = strdup(arr.Item(i).utf8_string().data());
        }
        return arr.GetCount();
    }
}
