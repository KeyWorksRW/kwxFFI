#include "wrapper.h"
#include <wx/docview.h>

extern "C"
{
    EXPORT void* wxFileHistory_Create(int maxFiles)
    {
        return (void*) new wxFileHistory(maxFiles);
    }

    EXPORT void wxFileHistory_Delete(void* _obj)
    {
        delete (wxFileHistory*) _obj;
    }

    EXPORT void wxFileHistory_AddFileToHistory(void* _obj, wxString* file)
    {
        ((wxFileHistory*) _obj)->AddFileToHistory(*file);
    }

    EXPORT void wxFileHistory_RemoveFileFromHistory(void* _obj, int i)
    {
        ((wxFileHistory*) _obj)->RemoveFileFromHistory(i);
    }

    EXPORT int wxFileHistory_GetMaxFiles(void* _obj)
    {
        return ((wxFileHistory*) _obj)->GetMaxFiles();
    }

    EXPORT void wxFileHistory_UseMenu(void* _obj, void* menu)
    {
        ((wxFileHistory*) _obj)->UseMenu((wxMenu*) menu);
    }

    EXPORT void wxFileHistory_RemoveMenu(void* _obj, void* menu)
    {
        ((wxFileHistory*) _obj)->RemoveMenu((wxMenu*) menu);
    }

    EXPORT void wxFileHistory_Load(void* _obj, void* config)
    {
        ((wxFileHistory*) _obj)->Load(*((wxConfigBase*) config));
    }

    EXPORT void wxFileHistory_Save(void* _obj, void* config)
    {
        ((wxFileHistory*) _obj)->Save(*((wxConfigBase*) config));
    }

    EXPORT void wxFileHistory_AddFilesToMenu(void* _obj, void* menu)
    {
        if (menu)
            ((wxFileHistory*) _obj)->AddFilesToMenu((wxMenu*) menu);
        else
            ((wxFileHistory*) _obj)->AddFilesToMenu();
    }

    EXPORT wxString* wxFileHistory_GetHistoryFile(void* _obj, int i)
    {
        wxString* result = new wxString();
        *result = ((wxFileHistory*) _obj)->GetHistoryFile(i);
        return result;
    }

    EXPORT int wxFileHistory_GetCount(void* _obj)
    {
        return ((wxFileHistory*) _obj)->GetCount();
    }

    EXPORT int wxFileHistory_GetMenus(void* _obj, void* _ref)
    {
        wxList lst = ((wxFileHistory*) _obj)->GetMenus();
        if (_ref)
        {
            int i = 0;
            wxList::compatibility_iterator node = lst.GetFirst();
            while (node)
            {
                ((void**) _ref)[i] = node->GetData();
                node = node->GetNext();
                ++i;
            }
        }

        return lst.GetCount();
    }
}
