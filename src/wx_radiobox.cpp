#include "wrapper.h"

// wxRadioBox inherits from wxControl and wxItemContainerImmutable.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

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

    EXPORT int wxRadioBox_FindString(void* pObject, wxString* str)
    {
        return ((wxRadioBox*) pObject)->FindString(*str);
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

    EXPORT void wxRadioBox_SetStringSelection(void* pObject, wxString* str)
    {
        ((wxRadioBox*) pObject)->SetStringSelection(*str);
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
        // Note: wxRadioBox does not have SetCount — this is a legacy wrapper
    }

    EXPORT int wxRadioBox_GetColumnCount(wxRadioBox* self)
    {
        return self->GetColumnCount();
    }

    EXPORT int wxRadioBox_GetRowCount(wxRadioBox* self)
    {
        return self->GetRowCount();
    }

    EXPORT bool wxRadioBox_IsItemEnabled(wxRadioBox* self, int item)
    {
        return self->IsItemEnabled(item);
    }

    EXPORT bool wxRadioBox_IsItemShown(wxRadioBox* self, int item)
    {
        return self->IsItemShown(item);
    }

    EXPORT int wxRadioBox_GetCount(wxRadioBox* self)
    {
        return self->GetCount();
    }
}
