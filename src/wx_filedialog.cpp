#include "wrapper.h"

extern "C"
{
    EXPORT void* wxFileDialog_Create(wxWindow* parent, wxString* message, wxString* defaultDir,
                                     wxString* defaultFile, wxString* wildcard, int x, int y,
                                     int style)
    {
        return (void*) new wxFileDialog(parent, *message, *defaultDir, *defaultFile, *wildcard,
                                        style, wxPoint(x, y));
    }

    EXPORT void wxFileDialog_SetMessage(void* _obj, wxString* message)
    {
        ((wxFileDialog*) _obj)->SetMessage(*message);
    }

    EXPORT void wxFileDialog_SetPath(void* _obj, wxString* path)
    {
        ((wxFileDialog*) _obj)->SetPath(*path);
    }

    EXPORT void wxFileDialog_SetDirectory(void* _obj, wxString* dir)
    {
        ((wxFileDialog*) _obj)->SetDirectory(*dir);
    }

    EXPORT void wxFileDialog_SetFilename(void* _obj, wxString* name)
    {
        ((wxFileDialog*) _obj)->SetFilename(*name);
    }

    EXPORT void wxFileDialog_SetWildcard(void* _obj, wxString* wildCard)
    {
        ((wxFileDialog*) _obj)->SetWildcard(*wildCard);
    }

    EXPORT void wxFileDialog_SetStyle(void* _obj, int style)
    {
#if WXWIN_COMPATIBILITY_2_6
        ((wxFileDialog*) _obj)->SetStyle((long) style);
#endif
    }

    EXPORT void wxFileDialog_SetFilterIndex(void* _obj, int filterIndex)
    {
        ((wxFileDialog*) _obj)->SetFilterIndex(filterIndex);
    }

    EXPORT wxString* wxFileDialog_GetMessage(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) _obj)->GetMessage();
        return result;
    }

    EXPORT wxString* wxFileDialog_GetPath(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) _obj)->GetPath();
        return result;
    }

    EXPORT int wxFileDialog_GetPaths(void* _obj, void* paths)
    {
        wxArrayString arr;
        ((wxFileDialog*) _obj)->GetPaths(arr);
        if (paths)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((const char**) paths)[i] = strdup(arr.Item(i).utf8_str().data());
        }
        return arr.GetCount();
    }

    EXPORT wxString* wxFileDialog_GetDirectory(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) _obj)->GetDirectory();
        return result;
    }

    EXPORT wxString* wxFileDialog_GetFilename(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) _obj)->GetFilename();
        return result;
    }

    EXPORT int wxFileDialog_GetFilenames(void* _obj, void* paths)
    {
        wxArrayString arr;
        ((wxFileDialog*) _obj)->GetFilenames(arr);
        if (paths)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((const char**) paths)[i] = strdup(arr.Item(i).utf8_str().data());
        }
        return arr.GetCount();
    }

    EXPORT wxString* wxFileDialog_GetWildcard(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxFileDialog*) _obj)->GetWildcard();
        return result;
    }

    EXPORT int wxFileDialog_GetStyle(void* _obj)
    {
#if WXWIN_COMPATIBILITY_2_6
        return (int) ((wxFileDialog*) _obj)->GetStyle();
#else
        return 0;
#endif
    }

    EXPORT int wxFileDialog_GetFilterIndex(void* _obj)
    {
        return ((wxFileDialog*) _obj)->GetFilterIndex();
    }
}
