#include "kwx_wrapper.h"
#include <wx/vlbox.h>

// wxVListBox inherits from wxWindow (via wxVScrolledCanvas).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

// wxVListBox is an abstract class - users override OnDrawItem and OnMeasureItem
// We provide the navigation and selection methods

extern "C"
{
    // Selection and navigation

    EXPORT bool wxVListBox_Create(wxVListBox* self, wxWindow* parent, int id, int x, int y,
                                  int width, int height, long style, wxString* name)
    {
        return self->Create(parent, id, wxPoint(x, y), wxSize(width, height), style,
                            name ? *name : wxString(wxVListBoxNameStr));
    }

    EXPORT void wxVListBox_Clear(wxVListBox* self)
    {
        self->Clear();
    }

    EXPORT bool wxVListBox_DeselectAll(wxVListBox* self)
    {
        return self->DeselectAll();
    }

    EXPORT int wxVListBox_GetFirstSelected(wxVListBox* self, unsigned long* cookie)
    {
        return self->GetFirstSelected(*cookie);
    }

    EXPORT size_t wxVListBox_GetItemCount(wxVListBox* self)
    {
        return self->GetItemCount();
    }

    EXPORT void wxVListBox_GetItemRect(wxVListBox* self, size_t item, int* x, int* y, int* width,
                                       int* height)
    {
        wxRect rect = self->GetItemRect(item);
        *x = rect.x;
        *y = rect.y;
        *width = rect.width;
        *height = rect.height;
    }

    EXPORT int wxVListBox_GetNextSelected(wxVListBox* self, unsigned long* cookie)
    {
        return self->GetNextSelected(*cookie);
    }

    EXPORT size_t wxVListBox_GetSelectedCount(wxVListBox* self)
    {
        return self->GetSelectedCount();
    }

    EXPORT int wxVListBox_GetSelection(wxVListBox* self)
    {
        return self->GetSelection();
    }

    EXPORT void wxVListBox_GetSelectionBackground(wxVListBox* self, wxColour* colour)
    {
        *colour = self->GetSelectionBackground();
    }

    EXPORT bool wxVListBox_HasMultipleSelection(wxVListBox* self)
    {
        return self->HasMultipleSelection();
    }

    EXPORT bool wxVListBox_IsCurrent(wxVListBox* self, size_t item)
    {
        return self->IsCurrent(item);
    }

    EXPORT bool wxVListBox_IsSelected(wxVListBox* self, size_t item)
    {
        return self->IsSelected(item);
    }

    EXPORT bool wxVListBox_Select(wxVListBox* self, size_t item, bool select)
    {
        return self->Select(item, select);
    }

    EXPORT bool wxVListBox_SelectAll(wxVListBox* self)
    {
        return self->SelectAll();
    }

    EXPORT bool wxVListBox_SelectRange(wxVListBox* self, size_t from, size_t toPos)
    {
        return self->SelectRange(from, toPos);
    }

    EXPORT void wxVListBox_SetItemCount(wxVListBox* self, size_t count)
    {
        self->SetItemCount(count);
    }

    EXPORT void wxVListBox_SetMargins(wxVListBox* self, int x, int y)
    {
        self->SetMargins(wxPoint(x, y));
    }

    EXPORT void wxVListBox_SetSelection(wxVListBox* self, int selection)
    {
        self->SetSelection(selection);
    }

    EXPORT void wxVListBox_SetSelectionBackground(wxVListBox* self, wxColour* col)
    {
        self->SetSelectionBackground(*col);
    }

    EXPORT void wxVListBox_Toggle(wxVListBox* self, size_t item)
    {
        self->Toggle(item);
    }
}
