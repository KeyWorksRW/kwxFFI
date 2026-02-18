#include "kwx_wrapper.h"

// wxChoice inherits from wxControl and wxItemContainer.
// Additional methods available via:
//   wxWindow_*         — base window methods (see wx_window.cpp)
//   wxControl_*        — label, alignment (see wx_control.cpp)
//   wxItemContainer_*  — item management, selection (see wx_itemcontainer.cpp)

extern "C"
{
    EXPORT wxChoice* wxChoice_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                     int count, void* items, int style)
    {
        wxString* list = new wxString[count];

        for (int i = 0; i < count; i++)
            list[i] = ((char**) items)[i];

        wxChoice* result = new wxChoice(parent, id, wxPoint(x, y), wxSize(width, height), count,
                                        list, style, wxDefaultValidator);

        delete[] list;

        return result;
    }

    EXPORT void wxChoice_Append(wxChoice* self, wxString* item)
    {
        self->Append(*item);
    }

    EXPORT void wxChoice_Delete(wxChoice* self, int index)
    {
        self->Delete(index);
    }

    EXPORT void wxChoice_Clear(wxChoice* self)
    {
        self->Clear();
    }

    EXPORT int wxChoice_GetCount(wxChoice* self)
    {
        return self->GetCount();
    }

    EXPORT int wxChoice_GetSelection(wxChoice* self)
    {
        return self->GetSelection();
    }

    EXPORT void wxChoice_SetSelection(wxChoice* self, int index)
    {
        self->SetSelection(index);
    }

    EXPORT int wxChoice_FindString(wxChoice* self, wxString* str)
    {
        return self->FindString(*str);
    }

    EXPORT wxString* wxChoice_GetString(wxChoice* self, int index)
    {
        wxString* result = new wxString();
        *result = self->GetString(index);
        return result;
    }

    EXPORT void wxChoice_SetString(wxChoice* self, int index, wxString* str)
    {
        self->SetString(index, *str);
    }

    EXPORT void wxChoice_SetColumns(wxChoice* self, int n)
    {
        self->SetColumns(n);
    }

    EXPORT int wxChoice_GetColumns(wxChoice* self)
    {
        return self->GetColumns();
    }

    EXPORT int wxChoice_GetCurrentSelection(wxChoice* self)
    {
        return self->GetCurrentSelection();
    }
}
