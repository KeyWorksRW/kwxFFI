#include "wrapper.h"

// wxBitmapComboBox inherits from wxComboBox (wxControl, wxItemContainer, and wxTextEntry).
// Additional methods available via:
//   wxWindow_*         — base window methods (see wx_window.cpp)
//   wxControl_*        — label, alignment (see wx_control.cpp)
//   wxItemContainer_*  — item management, selection (see wx_itemcontainer.cpp)
//   wxTextEntry_*      — text editing, hints, margins, selection (see wx_textentry.cpp)

extern "C"
{
    EXPORT wxBitmapComboBox* wxBitmapComboBox_Create(wxWindow* parent, int id, wxString* value,
                                                     int x, int y, int width, int height, int count,
                                                     void* str, int style)
    {
        wxString* list = new wxString[count];

        for (int i = 0; i < count; i++)
            list[i] = ((char**) str)[i];

        wxBitmapComboBox* result = new wxBitmapComboBox(parent, id, *value, wxPoint(x, y),
                                                        wxSize(width, height), count, list, style);

        delete[] list;

        if ((result->GetCount()) && (result->GetSelection() == -1))
            result->SetSelection(0);

        return result;
    }

    EXPORT void wxBitmapComboBox_Append(wxBitmapComboBox* self, wxString* item, wxBitmap* bitmap)
    {
        self->Append(*item, *bitmap);
    }

    EXPORT void wxBitmapComboBox_AppendWithClientData(wxBitmapComboBox* self, wxString* item,
                                                      wxBitmap* bitmap, void* data)
    {
        self->Append(*item, *bitmap, data);
    }

    EXPORT void wxBitmapComboBox_Insert(wxBitmapComboBox* self, wxString* item, wxBitmap* bitmap,
                                        int pos)
    {
        self->Insert(*item, *bitmap, pos);
    }

    EXPORT void wxBitmapComboBox_InsertWithClientData(wxBitmapComboBox* self, wxString* item,
                                                      wxBitmap* bitmap, int pos, void* data)
    {
        self->Insert(*item, *bitmap, pos, data);
    }

    EXPORT wxBitmap* wxBitmapComboBox_GetItemBitmap(wxBitmapComboBox* self, int index)
    {
        wxBitmap* result = new wxBitmap();
        *result = self->GetItemBitmap(index);
        return result;
    }

    EXPORT void wxBitmapComboBox_SetItemBitmap(wxBitmapComboBox* self, int index, wxBitmap* bitmap)
    {
        self->SetItemBitmap(index, *bitmap);
    }

    EXPORT wxSize* wxBitmapComboBox_GetBitmapSize(wxBitmapComboBox* self)
    {
        wxSize* result = new wxSize();
        *result = self->GetBitmapSize();
        return result;
    }
}
