#include "wrapper.h"

extern "C"
{
    EXPORT wxListView* wxListView_Create(wxWindow* parent, int id, int x, int y, int w, int h,
                                         int style)
    {
        return new wxListView(parent, id, wxPoint(x, y), wxSize(w, h), style);
    }

    EXPORT void wxListView_ClearColumnImage(wxListView* self, int col)
    {
        self->ClearColumnImage(col);
    }

    EXPORT void wxListView_Focus(wxListView* self, long index)
    {
        self->Focus(index);
    }

    EXPORT long wxListView_GetFirstSelected(wxListView* self)
    {
        return self->GetFirstSelected();
    }

    EXPORT long wxListView_GetFocusedItem(wxListView* self)
    {
        return self->GetFocusedItem();
    }

    EXPORT long wxListView_GetNextSelected(wxListView* self, long item)
    {
        return self->GetNextSelected(item);
    }

    EXPORT bool wxListView_IsSelected(wxListView* self, long index)
    {
        return self->IsSelected(index);
    }

    EXPORT void wxListView_Select(wxListView* self, long n, bool on)
    {
        self->Select(n, on);
    }

    EXPORT void wxListView_SetColumnImage(wxListView* self, int col, int image)
    {
        self->SetColumnImage(col, image);
    }
}
