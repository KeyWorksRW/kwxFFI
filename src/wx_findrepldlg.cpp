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

    EXPORT void wxFindReplaceData_Delete(void* pObject)
    {
        delete (wxFindReplaceData*) pObject;
    }

    EXPORT wxString* wxFindReplaceData_GetFindString(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxFindReplaceData*) pObject)->GetFindString();
        return result;
    }

    EXPORT wxString* wxFindReplaceData_GetReplaceString(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxFindReplaceData*) pObject)->GetReplaceString();
        return result;
    }

    EXPORT int wxFindReplaceData_GetFlags(void* pObject)
    {
        return ((wxFindReplaceData*) pObject)->GetFlags();
    }

    EXPORT void wxFindReplaceData_SetFlags(void* pObject, int flags)
    {
        ((wxFindReplaceData*) pObject)->SetFlags((wxUint32) flags);
    }

    EXPORT void wxFindReplaceData_SetFindString(void* pObject, wxString* str)
    {
        ((wxFindReplaceData*) pObject)->SetFindString(*str);
    }

    EXPORT void wxFindReplaceData_SetReplaceString(void* pObject, wxString* str)
    {
        ((wxFindReplaceData*) pObject)->SetReplaceString(*str);
    }

    EXPORT int wxFindDialogEvent_GetFlags(void* pObject)
    {
        return ((wxFindDialogEvent*) pObject)->GetFlags();
    }

    EXPORT wxString* wxFindDialogEvent_GetFindString(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxFindReplaceData*) pObject)->GetFindString();
        return result;
    }

    EXPORT wxString* wxFindDialogEvent_GetReplaceString(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxFindReplaceData*) pObject)->GetFindString();
        return result;
    }

    EXPORT void* wxFindReplaceDialog_Create(wxWindow* parent, void* data, wxString* title,
                                            int style)
    {
        return (void*) new wxFindReplaceDialog(parent, (wxFindReplaceData*) data, *title, style);
    }

    EXPORT void* wxFindReplaceDialog_GetData(void* pObject)
    {
        return (void*) ((wxFindReplaceDialog*) pObject)->GetData();
    }

    EXPORT void wxFindReplaceDialog_SetData(void* pObject, void* data)
    {
        ((wxFindReplaceDialog*) pObject)->SetData((wxFindReplaceData*) data);
    }
}
