#include "wrapper.h"

extern "C"
{
    EXPORT void* wxListBox_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                  int count, void* items, int style)
    {
        wxListBox* result = new wxListBox(parent, id, wxPoint(x, y), wxSize(width, height), 0,
                                          nullptr, style, wxDefaultValidator);

        for (int i = 0; i < count; i++)
            result->Append(((char**) items)[i]);

        return (void*) result;
    }

    EXPORT void wxListBox_Clear(wxListBox* self)
    {
        self->Clear();
    }

    EXPORT void wxListBox_Delete(wxListBox* self, int index)
    {
        self->Delete(index);
    }

    EXPORT int wxListBox_GetCount(wxListBox* self)
    {
        return self->GetCount();
    }

    EXPORT wxString* wxListBox_GetString(wxListBox* self, int index)
    {
        wxString* result = new wxString();
        *result = self->GetString(index);
        return result;
    }

    EXPORT void wxListBox_SetString(wxListBox* self, int index, wxString* str)
    {
        self->SetString(index, *str);
    }

    EXPORT int wxListBox_FindString(wxListBox* self, wxString* str)
    {
        return self->FindString(*str);
    }

    EXPORT bool wxListBox_IsSelected(wxListBox* self, int index)
    {
        return self->IsSelected(index);
    }

    EXPORT void wxListBox_SetSelection(wxListBox* self, int index, bool select)
    {
        self->SetSelection(index, select);
    }

    EXPORT int wxListBox_GetSelection(wxListBox* self)
    {
        return self->GetSelection();
    }

    EXPORT int wxListBox_GetSelections(wxListBox* self, int* aSelections, int allocated)
    {
        wxArrayInt sel;
        int result = self->GetSelections(sel);

        if (allocated < result)
            return -result;

        for (int i = 0; i < result; i++)
            aSelections[i] = sel[i];
        return result;
    }

    EXPORT void wxListBox_Append(wxListBox* self, wxString* item)
    {
        self->Append(*item);
    }

    EXPORT void wxListBox_AppendData(wxListBox* self, wxString* item, void* data)
    {
        self->Append(*item, data);
    }

    EXPORT void wxListBox_InsertItems(wxListBox* self, void* items, int pos, int count)
    {
        wxArrayString array;

        for (int i = 0; i < count; i++)
            array[i] = ((char**) items)[i];

        self->InsertItems(array, pos);
    }

    EXPORT void wxListBox_SetFirstItem(wxListBox* self, int index)
    {
        self->SetFirstItem(index);
    }

    EXPORT void wxListBox_SetClientData(wxListBox* self, int index, void* clientData)
    {
        self->SetClientData(index, clientData);
    }

    EXPORT void* wxListBox_GetClientData(wxListBox* self, int index)
    {
        return (void*) self->GetClientData(index);
    }

    EXPORT void wxListBox_SetStringSelection(wxListBox* self, wxString* str, bool sel)
    {
        self->SetStringSelection(*str, sel);
    }
}
