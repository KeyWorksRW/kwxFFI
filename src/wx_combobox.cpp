#include "wrapper.h"

// wxComboBox inherits from wxControl, wxItemContainer, and wxTextEntry.
// Additional methods available via:
//   wxWindow_*         — base window methods (see wx_window.cpp)
//   wxControl_*        — label, alignment (see wx_control.cpp)
//   wxItemContainer_*  — item management, selection (see wx_itemcontainer.cpp)
//   wxTextEntry_*      — text editing, hints, margins, selection (see wx_textentry.cpp)

extern "C"
{
    EXPORT wxComboBox* wxComboBox_Create(wxWindow* parent, int id, wxString* text, int x, int y,
                                         int width, int height, int count, void* items, int style)
    {
        wxString* list = new wxString[count];

        for (int i = 0; i < count; i++)
            list[i] = ((char**) items)[i];

        wxComboBox* result = new wxComboBox(parent, id, *text, wxPoint(x, y), wxSize(width, height),
                                            count, list, style, wxDefaultValidator);

        delete[] list;
        if ((result->GetCount()) && (result->GetSelection() == -1))
            result->SetSelection(0);

        return result;
    }

    EXPORT void wxComboBox_Copy(wxComboBox* self)
    {
        self->Copy();
    }

    EXPORT void wxComboBox_Cut(wxComboBox* self)
    {
        self->Cut();
    }

    EXPORT void wxComboBox_Paste(wxComboBox* self)
    {
        self->Paste();
    }

    EXPORT void wxComboBox_SetInsertionPoint(wxComboBox* self, int pos)
    {
        self->SetInsertionPoint(pos);
    }

    EXPORT void wxComboBox_SetInsertionPointEnd(wxComboBox* self)
    {
        self->SetInsertionPointEnd();
    }

    EXPORT int wxComboBox_GetInsertionPoint(wxComboBox* self)
    {
        return self->GetInsertionPoint();
    }

    EXPORT int wxComboBox_GetLastPosition(wxComboBox* self)
    {
        return self->GetLastPosition();
    }

    EXPORT void wxComboBox_Replace(wxComboBox* self, int from, int toPos, wxString* value)
    {
        self->Replace(from, toPos, *value);
    }

    EXPORT void wxComboBox_Remove(wxComboBox* self, int from, int toPos)
    {
        self->Remove(from, toPos);
        if ((self->GetCount()) && (self->GetSelection() == -1))
            self->SetSelection(0);
    }

    EXPORT void wxComboBox_SetTextSelection(wxComboBox* self, int from, int toPos)
    {
        self->SetSelection(from, toPos);
    }

    EXPORT void wxComboBox_SetEditable(wxComboBox* self, bool editable)
    {
        self->SetEditable(editable);
    }

    EXPORT wxString* wxComboBox_GetStringSelection(wxComboBox* self)
    {
        return new wxString(self->GetStringSelection());
    }

    EXPORT wxString* wxComboBox_GetValue(wxComboBox* self)
    {
        return new wxString(self->GetValue());
    }

    EXPORT void wxComboBox_SetValue(wxComboBox* self, wxString* value)
    {
        self->SetValue(*value);
    }

    EXPORT void wxComboBox_Append(wxComboBox* self, wxString* item)
    {
        self->Append(*item);
        if (self->GetCount() && (self->GetSelection() == -1))
            self->SetSelection(0);
    }

    EXPORT void wxComboBox_AppendData(wxComboBox* self, wxString* item, void* clientData)
    {
#if defined(__WXMAC__)
        self->Append(*item);
#else
        self->Append(*item, clientData);
#endif

        if ((self->GetCount()) && (self->GetSelection() == -1))
            self->SetSelection(0);
    }

    EXPORT void wxComboBox_Delete(wxComboBox* self, int index)
    {
        self->Delete(index);
        if ((self->GetCount()) && (self->GetSelection() == -1))
            self->SetSelection(0);
    }

    EXPORT void wxComboBox_Clear(wxComboBox* self)
    {
        self->Clear();
    }

    EXPORT int wxComboBox_GetCount(wxComboBox* self)
    {
        return self->GetCount();
    }

    EXPORT int wxComboBox_GetSelection(wxComboBox* self)
    {
        return self->GetSelection();
    }

    EXPORT void wxComboBox_SetSelection(wxComboBox* self, int index)
    {
        self->SetSelection(index);
    }

    EXPORT int wxComboBox_FindString(wxComboBox* self, wxString* str)
    {
        return self->FindString(*str);
    }

    EXPORT wxString* wxComboBox_GetString(wxComboBox* self, int index)
    {
        return new wxString(self->GetString(index));
    }

    EXPORT void wxComboBox_SetString(wxComboBox* self, int index, wxString* str)
    {
        self->SetString(index, *str);
    }

    EXPORT void wxComboBox_SetClientData(wxComboBox* self, int index, void* clientData)
    {
        ((wxItemContainer*) self)->SetClientData(index, clientData);
    }

    EXPORT void* wxComboBox_GetClientData(wxComboBox* self, int index)
    {
        return ((wxItemContainer*) self)->GetClientData(index);
    }
}
