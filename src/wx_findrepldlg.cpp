/*==============================================================================
 * eljfindrepdlg.cpp
 *
 * C wrapper for wxFindReplaceData
 *
 * (C) 2002-2011 wxEiffel and wxHaskell contributors. See contributors.txt
 *
 *==============================================================================*/

#include "wrapper.h"
#include <wx/fdrepdlg.h>

extern "C"
{
    ////////////////////////////////////////////////////////////////////////////////
    // Event Handlers
    ////////////////////////////////////////////////////////////////////////////////

    /* #pragma message "wxWidgets find/replace dialog event wrappers generated" */
    MAKE_EVENT_WRAPPER(EVT_COMMAND_FIND)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_FIND_NEXT)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_FIND_REPLACE)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_FIND_REPLACE_ALL)
    MAKE_EVENT_WRAPPER(EVT_COMMAND_FIND_CLOSE)

    ////////////////////////////////////////////////////////////////////////////////
    // Wrappers
    ////////////////////////////////////////////////////////////////////////////////

    EXPORT void* wxFindReplaceData_CreateDefault()
    {
        return (void*) new wxFindReplaceData();
    }

    EXPORT void* wxFindReplaceData_Create(int flags)
    {
        return (void*) new wxFindReplaceData((wxUint32) flags);
    }

    EXPORT void wxFindReplaceData_Delete(void* _obj)
    {
        delete (wxFindReplaceData*) _obj;
    }

    EXPORT wxString* wxFindReplaceData_GetFindString(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxFindReplaceData*) _obj)->GetFindString();
        return result;
    }

    EXPORT wxString* wxFindReplaceData_GetReplaceString(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxFindReplaceData*) _obj)->GetReplaceString();
        return result;
    }

    EXPORT int wxFindReplaceData_GetFlags(void* _obj)
    {
        return ((wxFindReplaceData*) _obj)->GetFlags();
    }

    EXPORT void wxFindReplaceData_SetFlags(void* _obj, int flags)
    {
        ((wxFindReplaceData*) _obj)->SetFlags((wxUint32) flags);
    }

    EXPORT void wxFindReplaceData_SetFindString(void* _obj, wxString* str)
    {
        ((wxFindReplaceData*) _obj)->SetFindString(*str);
    }

    EXPORT void wxFindReplaceData_SetReplaceString(void* _obj, wxString* str)
    {
        ((wxFindReplaceData*) _obj)->SetReplaceString(*str);
    }

    EXPORT int wxFindDialogEvent_GetFlags(void* _obj)
    {
        return ((wxFindDialogEvent*) _obj)->GetFlags();
    }

    EXPORT wxString* wxFindDialogEvent_GetFindString(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxFindReplaceData*) _obj)->GetFindString();
        return result;
    }

    EXPORT wxString* wxFindDialogEvent_GetReplaceString(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxFindReplaceData*) _obj)->GetFindString();
        return result;
    }

    EXPORT void* wxFindReplaceDialog_Create(wxWindow* parent, void* data, wxString* title,
                                            int style)
    {
        return (void*) new wxFindReplaceDialog(parent, (wxFindReplaceData*) data, *title, style);
    }

    EXPORT void* wxFindReplaceDialog_GetData(void* _obj)
    {
        return (void*) ((wxFindReplaceDialog*) _obj)->GetData();
    }

    EXPORT void wxFindReplaceDialog_SetData(void* _obj, void* data)
    {
        ((wxFindReplaceDialog*) _obj)->SetData((wxFindReplaceData*) data);
    }
}
