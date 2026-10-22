#include "kwx_wrapper.h"

#include <vector>

extern "C"
{
    EXPORT void* wxMultiChoiceDialog_Create(wxWindow* parent, wxString* message, wxString* caption,
                                            int n, void* choices, long style, int x, int y)
    {
        std::vector<wxString> items;
        items.reserve(static_cast<size_t>(n));
        for (int i = 0; i < n; ++i)
        {
            items.emplace_back(static_cast<char**>(choices)[i]);
        }

        wxMultiChoiceDialog* dialog = new wxMultiChoiceDialog();
        if (!dialog->Create(parent, *message, *caption, static_cast<int>(items.size()),
                            items.data(), style, wxPoint(x, y)))
        {
            delete dialog;
            return nullptr;
        }
        return static_cast<void*>(dialog);
    }

    EXPORT void wxMultiChoiceDialog_GetSelections(wxMultiChoiceDialog* self, wxArrayInt* selections)
    {
        *selections = self->GetSelections();
    }

    EXPORT void wxMultiChoiceDialog_SetSelections(wxMultiChoiceDialog* self, wxArrayInt* selections)
    {
        self->SetSelections(*selections);
    }

    EXPORT int wxMultiChoiceDialog_ShowModal(wxMultiChoiceDialog* self)
    {
        return self->ShowModal();
    }

    EXPORT void wxMultiChoiceDialog_Delete(wxMultiChoiceDialog* self)
    {
        delete self;
    }
}
