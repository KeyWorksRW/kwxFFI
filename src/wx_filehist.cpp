#include "kwx_wrapper.h"
#include <wx/docview.h>

extern "C"
{
    EXPORT void* wxFileHistory_Create(int maxFiles)
    {
        return (void*) new wxFileHistory(maxFiles);
    }

    EXPORT void wxFileHistory_Delete(void* pObject)
    {
        delete (wxFileHistory*) pObject;
    }

    EXPORT void wxFileHistory_AddFileToHistory(void* pObject, wxString* file)
    {
        ((wxFileHistory*) pObject)->AddFileToHistory(*file);
    }

    EXPORT void wxFileHistory_RemoveFileFromHistory(void* pObject, int index)
    {
        ((wxFileHistory*) pObject)->RemoveFileFromHistory(index);
    }

    EXPORT int wxFileHistory_GetMaxFiles(void* pObject)
    {
        return ((wxFileHistory*) pObject)->GetMaxFiles();
    }

    EXPORT void wxFileHistory_UseMenu(void* pObject, void* menu)
    {
        ((wxFileHistory*) pObject)->UseMenu((wxMenu*) menu);
    }

    EXPORT void wxFileHistory_RemoveMenu(void* pObject, void* menu)
    {
        ((wxFileHistory*) pObject)->RemoveMenu((wxMenu*) menu);
    }

    EXPORT void wxFileHistory_Load(void* pObject, void* config)
    {
        ((wxFileHistory*) pObject)->Load(*((wxConfigBase*) config));
    }

    EXPORT void wxFileHistory_Save(void* pObject, void* config)
    {
        ((wxFileHistory*) pObject)->Save(*((wxConfigBase*) config));
    }

    EXPORT void wxFileHistory_AddFilesToMenu(void* pObject, void* menu)
    {
        if (menu)
            ((wxFileHistory*) pObject)->AddFilesToMenu((wxMenu*) menu);
        else
            ((wxFileHistory*) pObject)->AddFilesToMenu();
    }

    EXPORT wxString* wxFileHistory_GetHistoryFile(void* pObject, int index)
    {
        wxString* result = new wxString();
        *result = ((wxFileHistory*) pObject)->GetHistoryFile(index);
        return result;
    }

    EXPORT int wxFileHistory_GetCount(void* pObject)
    {
        return ((wxFileHistory*) pObject)->GetCount();
    }

    EXPORT int wxFileHistory_GetMenus(void* pObject, void* ref)
    {
        wxList lst = ((wxFileHistory*) pObject)->GetMenus();
        if (ref)
        {
            int index = 0;
            wxList::compatibility_iterator node = lst.GetFirst();
            while (node)
            {
                ((void**) ref)[index] = node->GetData();
                node = node->GetNext();
                ++index;
            }
        }

        return lst.GetCount();
    }
}
