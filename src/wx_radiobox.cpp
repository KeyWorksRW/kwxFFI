#include "wrapper.h"

extern "C"
{
    EXPORT void* wxRadioBox_Create(wxWindow* parent, int id, wxString* label, int x, int y,
                                   int width, int height, int count, void* choices, int majorDim,
                                   int style)
    {
        wxString items[256];

        for (int i = 0; i < count; i++)
            items[i] = ((char**) choices)[i];

        return new wxRadioBox(parent, id, *label, wxPoint(x, y), wxSize(width, height), count,
                              items, majorDim, style, wxDefaultValidator);
    }

    EXPORT int wxRadioBox_FindString(void* pObject, wxString* s)
    {
        return ((wxRadioBox*) pObject)->FindString(*s);
    }

    EXPORT void wxRadioBox_SetSelection(void* pObject, int selection)
    {
        ((wxRadioBox*) pObject)->SetSelection(selection);
    }

    EXPORT int wxRadioBox_GetSelection(void* pObject)
    {
        return ((wxRadioBox*) pObject)->GetSelection();
    }

    EXPORT void wxRadioBox_SetItemLabel(void* pObject, int item, wxString* label)
    {
        ((wxRadioBoxBase*) pObject)->SetString(item, *label);
    }

    EXPORT wxString* wxRadioBox_GetItemLabel(void* pObject, int item)
    {
        wxString* result = new wxString();
        *result = ((wxRadioBox*) pObject)->GetString(item);
        return result;
    }

    EXPORT void wxRadioBox_EnableItem(void* self, int item, bool enable)
    {
        ((wxRadioBox*) self)->Enable(item, enable);
    }

    EXPORT void wxRadioBox_ShowItem(void* self, int item, bool show)
    {
        ((wxRadioBox*) self)->Show(item, show);
    }

    EXPORT wxString* wxRadioBox_GetStringSelection(void* pObject)
    {
        wxString* result = new wxString();
        *result = ((wxRadioBox*) pObject)->GetStringSelection();
        return result;
    }

    EXPORT void wxRadioBox_SetStringSelection(void* pObject, wxString* s)
    {
        ((wxRadioBox*) pObject)->SetStringSelection(*s);
    }

    EXPORT int wxRadioBox_Number(void* pObject)
    {
        return ((wxRadioBox*) pObject)->GetCount();
    }

    EXPORT int wxRadioBox_GetNumberOfRowsOrCols(void* pObject)
    {
        return ((wxRadioBox*) pObject)->GetCount();
    }

    EXPORT void wxRadioBox_SetNumberOfRowsOrCols(void* pObject, int count)
    {
        // No-op: SetNumberOfRowsOrCols was removed in wxWidgets 2.6
    }
}
