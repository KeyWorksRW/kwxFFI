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

    EXPORT int wxRadioBox_FindString(void* _obj, wxString* s)
    {
        return ((wxRadioBox*) _obj)->FindString(*s);
    }

    EXPORT void wxRadioBox_SetSelection(void* _obj, int _n)
    {
        ((wxRadioBox*) _obj)->SetSelection(_n);
    }

    EXPORT int wxRadioBox_GetSelection(void* _obj)
    {
        return ((wxRadioBox*) _obj)->GetSelection();
    }

    EXPORT void wxRadioBox_SetItemLabel(void* _obj, int item, wxString* label)
    {
        ((wxRadioBoxBase*) _obj)->SetString(item, *label);
    }

    EXPORT wxString* wxRadioBox_GetItemLabel(void* _obj, int item)
    {
        wxString* result = new wxString();
        *result = ((wxRadioBox*) _obj)->GetString(item);
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

    EXPORT wxString* wxRadioBox_GetStringSelection(void* _obj)
    {
        wxString* result = new wxString();
        *result = ((wxRadioBox*) _obj)->GetStringSelection();
        return result;
    }

    EXPORT void wxRadioBox_SetStringSelection(void* _obj, wxString* s)
    {
        ((wxRadioBox*) _obj)->SetStringSelection(*s);
    }

    EXPORT int wxRadioBox_Number(void* _obj)
    {
        return ((wxRadioBox*) _obj)->GetCount();
    }

    EXPORT int wxRadioBox_GetNumberOfRowsOrCols(void* _obj)
    {
        return ((wxRadioBox*) _obj)->GetCount();
    }

    EXPORT void wxRadioBox_SetNumberOfRowsOrCols(void* _obj, int count)
    {
        // No-op: SetNumberOfRowsOrCols was removed in wxWidgets 2.6
    }
}
