#include "kwx_wrapper.h"

// wxFileDialog inherits from wxDialog (wxTopLevelWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxFileDialog_Create(wxWindow* parent, wxString* message, wxString* defaultDir,
                                     wxString* defaultFile, wxString* wildcard, int x, int y,
                                     int style, int sz_w, int sz_h)
    {
        return (void*) new wxFileDialog(parent, *message, *defaultDir, *defaultFile, *wildcard,
                                        style, wxPoint(x, y), wxSize(sz_w, sz_h));
    }

    EXPORT void wxFileDialog_SetMessage(void* pObject, wxString* message)
    {
        ((wxFileDialog*) pObject)->SetMessage(*message);
    }

    EXPORT void wxFileDialog_SetPath(void* pObject, wxString* path)
    {
        ((wxFileDialog*) pObject)->SetPath(*path);
    }

    EXPORT void wxFileDialog_SetDirectory(void* pObject, wxString* dir)
    {
        ((wxFileDialog*) pObject)->SetDirectory(*dir);
    }

    EXPORT void wxFileDialog_SetFilename(void* pObject, wxString* name)
    {
        ((wxFileDialog*) pObject)->SetFilename(*name);
    }

    EXPORT void wxFileDialog_SetWildcard(void* pObject, wxString* wildCard)
    {
        ((wxFileDialog*) pObject)->SetWildcard(*wildCard);
    }

    EXPORT void wxFileDialog_SetStyle(void* pObject, int style)
    {
#if WXWIN_COMPATIBILITY_2_6
        ((wxFileDialog*) pObject)->SetStyle((long) style);
#endif
    }

    EXPORT void wxFileDialog_SetFilterIndex(void* pObject, int filterIndex)
    {
        ((wxFileDialog*) pObject)->SetFilterIndex(filterIndex);
    }

    EXPORT wxString* wxFileDialog_GetMessage(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) pObject)->GetMessage();
        return result;
    }

    EXPORT wxString* wxFileDialog_GetPath(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) pObject)->GetPath();
        return result;
    }

    EXPORT int wxFileDialog_GetPaths(void* pObject, void* paths)
    {
        wxArrayString arr;
        ((wxFileDialog*) pObject)->GetPaths(arr);
        if (paths)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((const char**) paths)[i] = strdup(arr.Item(i).utf8_str().data());
        }
        return arr.GetCount();
    }

    EXPORT wxString* wxFileDialog_GetDirectory(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) pObject)->GetDirectory();
        return result;
    }

    EXPORT wxString* wxFileDialog_GetFilename(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) pObject)->GetFilename();
        return result;
    }

    EXPORT int wxFileDialog_GetFilenames(void* pObject, void* paths)
    {
        wxArrayString arr;
        ((wxFileDialog*) pObject)->GetFilenames(arr);
        if (paths)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((const char**) paths)[i] = strdup(arr.Item(i).utf8_str().data());
        }
        return arr.GetCount();
    }

    EXPORT wxString* wxFileDialog_GetWildcard(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) pObject)->GetWildcard();
        return result;
    }

    EXPORT int wxFileDialog_GetStyle(void* pObject)
    {
#if WXWIN_COMPATIBILITY_2_6
        return (int) ((wxFileDialog*) pObject)->GetStyle();
#else
        return 0;
#endif
    }

    EXPORT int wxFileDialog_GetFilterIndex(void* pObject)
    {
        return ((wxFileDialog*) pObject)->GetFilterIndex();
    }

    EXPORT wxString* wxFileDialog_GetCurrentlySelectedFilename(wxFileDialog* self)
    {
        wxString* result = new wxString();
        *result = self->GetCurrentlySelectedFilename();
        return result;
    }

    EXPORT void* wxFileDialog_GetExtraControl(wxFileDialog* self)
    {
        return (void*) self->GetExtraControl();
    }
}
