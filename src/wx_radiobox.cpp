#include "kwx_wrapper.h"

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

    EXPORT int wxRadioBox_FindString(wxRadioBox* pObject, wxString* str)
    {
        return pObject->FindString(*str);
    }

    EXPORT void wxRadioBox_SetSelection(wxRadioBox* pObject, int selection)
    {
        pObject->SetSelection(selection);
    }

    EXPORT int wxRadioBox_GetSelection(wxRadioBox* pObject)
    {
        return pObject->GetSelection();
    }

    EXPORT void wxRadioBox_SetItemLabel(void* pObject, int item, wxString* label)
    {
        ((wxRadioBoxBase*) pObject)->SetString(item, *label);
    }

    EXPORT wxString* wxRadioBox_GetItemLabel(wxRadioBox* pObject, int item)
    {
        wxString* result = new wxString();
        *result = pObject->GetString(item);
        return result;
    }

    EXPORT void wxRadioBox_EnableItem(wxRadioBox* self, int item, bool enable)
    {
        self->Enable(item, enable);
    }

    EXPORT void wxRadioBox_ShowItem(wxRadioBox* self, int item, bool show)
    {
        self->Show(item, show);
    }

    EXPORT wxString* wxRadioBox_GetStringSelection(wxRadioBox* pObject)
    {
        wxString* result = new wxString();
        *result = pObject->GetStringSelection();
        return result;
    }

    EXPORT void wxRadioBox_SetStringSelection(wxRadioBox* pObject, wxString* str)
    {
        pObject->SetStringSelection(*str);
    }

    EXPORT int wxRadioBox_Number(wxRadioBox* pObject)
    {
        return pObject->GetCount();
    }

    EXPORT int wxRadioBox_GetNumberOfRowsOrCols(wxRadioBox* pObject)
    {
        return pObject->GetCount();
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
