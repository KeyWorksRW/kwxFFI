#include "wrapper.h"
#include <wx/artprov.h>

extern "C"
{
    EXPORT void* wxIconBundle_CreateDefault()
    {
        return (void*) new wxIconBundle();
    }

    EXPORT void* wxIconBundle_CreateFromFile(wxString* file, int type)
    {
        return (void*) new wxIconBundle(*file, (wxBitmapType) type);
    }

    EXPORT void* wxIconBundle_CreateFromIcon(void* icon)
    {
        return (void*) new wxIconBundle(*((wxIcon*) icon));
    }

    EXPORT void wxIconBundle_Assign(void* _obj, void* _ref)
    {
        *((wxIconBundle*) _ref) = *((wxIconBundle*) _obj);
    }

    EXPORT void wxIconBundle_Delete(void* _obj)
    {
        delete (wxIconBundle*) _obj;
    }

    EXPORT void wxIconBundle_AddIconFromFile(void* _obj, wxString* file, int type)
    {
        ((wxIconBundle*) _obj)->AddIcon(*file, (wxBitmapType) type);
    }

    EXPORT void wxIconBundle_AddIcon(void* _obj, void* icon)
    {
        ((wxIconBundle*) _obj)->AddIcon(*((wxIcon*) icon));
    }

    EXPORT void wxIconBundle_GetIcon(void* _obj, int w, int h, void* _ref)
    {
        *((wxIcon*) _ref) = ((wxIconBundle*) _obj)->GetIcon(wxSize(w, h));
    }
}
