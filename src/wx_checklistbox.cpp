#include "wrapper.h"

extern "C"
{
    EXPORT wxCheckListBox* wxCheckListBox_Create(wxWindow* parent, int id, int x, int y, int width,
                                                 int height, int count, void* items, int style)
    {
        wxCheckListBox* result =
            new wxCheckListBox(parent, id, wxPoint(x, y), wxSize(width, height), 0, nullptr, style,
                               wxDefaultValidator);

        for (int i = 0; i < count; i++)
            result->Append(((char**) items)[i]);

        return result;
    }

    EXPORT void wxCheckListBox_Delete(wxCheckListBox* self)
    {
        delete self;
    }

    EXPORT void wxCheckListBox_Check(wxCheckListBox* self, int item, bool check)
    {
        self->Check(item, check);
    }

    EXPORT bool wxCheckListBox_IsChecked(wxCheckListBox* self, int item)
    {
        return self->IsChecked(item);
    }
}
