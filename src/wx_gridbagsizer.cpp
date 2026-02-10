// wxGridBagSizer - Grid bag sizer with precise cell positioning
#include "wrapper.h"

extern "C"
{
    // Constructor
    EXPORT wxGridBagSizer* wxGridBagSizer_Create(int vgap, int hgap)
    {
        return new wxGridBagSizer(vgap, hgap);
    }

    // Add window with position and span
    EXPORT wxSizerItem* wxGridBagSizer_AddWindow(wxGridBagSizer* self, wxWindow* window, int row,
                                                 int col, int rowspan, int colspan, int flag,
                                                 int border, void* userData)
    {
        return self->Add(window, wxGBPosition(row, col), wxGBSpan(rowspan, colspan), flag, border,
                         new kwxDataObject(userData));
    }

    // Add sizer with position and span
    EXPORT wxSizerItem* wxGridBagSizer_AddSizer(wxGridBagSizer* self, wxSizer* sizer, int row,
                                                int col, int rowspan, int colspan, int flag,
                                                int border, void* userData)
    {
        return self->Add(sizer, wxGBPosition(row, col), wxGBSpan(rowspan, colspan), flag, border,
                         new kwxDataObject(userData));
    }

    // Add spacer with position and span
    EXPORT wxSizerItem* wxGridBagSizer_AddSpacer(wxGridBagSizer* self, int width, int height,
                                                 int row, int col, int rowspan, int colspan,
                                                 int flag, int border, void* userData)
    {
        return self->Add(width, height, wxGBPosition(row, col), wxGBSpan(rowspan, colspan), flag,
                         border, new kwxDataObject(userData));
    }

    // Get item position
    EXPORT void wxGridBagSizer_GetItemPosition(wxGridBagSizer* self, wxWindow* window, int* row,
                                               int* col)
    {
        wxGBPosition pos = self->GetItemPosition(window);
        *row = pos.GetRow();
        *col = pos.GetCol();
    }

    EXPORT void wxGridBagSizer_GetItemPositionSizer(wxGridBagSizer* self, wxSizer* sizer, int* row,
                                                    int* col)
    {
        wxGBPosition pos = self->GetItemPosition(sizer);
        *row = pos.GetRow();
        *col = pos.GetCol();
    }

    EXPORT void wxGridBagSizer_GetItemPositionIndex(wxGridBagSizer* self, size_t index, int* row,
                                                    int* col)
    {
        wxGBPosition pos = self->GetItemPosition(index);
        *row = pos.GetRow();
        *col = pos.GetCol();
    }

    // Set item position
    EXPORT bool wxGridBagSizer_SetItemPosition(wxGridBagSizer* self, wxWindow* window, int row,
                                               int col)
    {
        return self->SetItemPosition(window, wxGBPosition(row, col));
    }

    EXPORT bool wxGridBagSizer_SetItemPositionSizer(wxGridBagSizer* self, wxSizer* sizer, int row,
                                                    int col)
    {
        return self->SetItemPosition(sizer, wxGBPosition(row, col));
    }

    EXPORT bool wxGridBagSizer_SetItemPositionIndex(wxGridBagSizer* self, size_t index, int row,
                                                    int col)
    {
        return self->SetItemPosition(index, wxGBPosition(row, col));
    }

    // Get item span
    EXPORT void wxGridBagSizer_GetItemSpan(wxGridBagSizer* self, wxWindow* window, int* rowspan,
                                           int* colspan)
    {
        wxGBSpan span = self->GetItemSpan(window);
        *rowspan = span.GetRowspan();
        *colspan = span.GetColspan();
    }

    EXPORT void wxGridBagSizer_GetItemSpanSizer(wxGridBagSizer* self, wxSizer* sizer, int* rowspan,
                                                int* colspan)
    {
        wxGBSpan span = self->GetItemSpan(sizer);
        *rowspan = span.GetRowspan();
        *colspan = span.GetColspan();
    }

    EXPORT void wxGridBagSizer_GetItemSpanIndex(wxGridBagSizer* self, size_t index, int* rowspan,
                                                int* colspan)
    {
        wxGBSpan span = self->GetItemSpan(index);
        *rowspan = span.GetRowspan();
        *colspan = span.GetColspan();
    }

    // Set item span
    EXPORT bool wxGridBagSizer_SetItemSpan(wxGridBagSizer* self, wxWindow* window, int rowspan,
                                           int colspan)
    {
        return self->SetItemSpan(window, wxGBSpan(rowspan, colspan));
    }

    EXPORT bool wxGridBagSizer_SetItemSpanSizer(wxGridBagSizer* self, wxSizer* sizer, int rowspan,
                                                int colspan)
    {
        return self->SetItemSpan(sizer, wxGBSpan(rowspan, colspan));
    }

    EXPORT bool wxGridBagSizer_SetItemSpanIndex(wxGridBagSizer* self, size_t index, int rowspan,
                                                int colspan)
    {
        return self->SetItemSpan(index, wxGBSpan(rowspan, colspan));
    }

    // Find item at position
    EXPORT wxSizerItem* wxGridBagSizer_FindItemAtPosition(wxGridBagSizer* self, int row, int col)
    {
        return self->FindItemAtPosition(wxGBPosition(row, col));
    }

    // Check for intersection
    EXPORT bool wxGridBagSizer_CheckForIntersection(wxGridBagSizer* self, wxGBSizerItem* item,
                                                    wxGBSizerItem* excludeItem)
    {
        return self->CheckForIntersection(item, excludeItem);
    }

    EXPORT bool wxGridBagSizer_CheckForIntersectionPos(wxGridBagSizer* self, int row, int col,
                                                       int rowspan, int colspan,
                                                       wxGBSizerItem* excludeItem)
    {
        return self->CheckForIntersection(wxGBPosition(row, col), wxGBSpan(rowspan, colspan),
                                          excludeItem);
    }

    // Get empty cell size
    EXPORT void wxGridBagSizer_GetEmptyCellSize(wxGridBagSizer* self, int* width, int* height)
    {
        wxSize text = self->GetEmptyCellSize();
        *width = text.GetWidth();
        *height = text.GetHeight();
    }

    EXPORT void wxGridBagSizer_SetEmptyCellSize(wxGridBagSizer* self, int width, int height)
    {
        self->SetEmptyCellSize(wxSize(width, height));
    }
}
