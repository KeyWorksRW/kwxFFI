#include "wrapper.h"

extern "C"
{
    EXPORT void* wxStatusBar_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                    int style)
    {
        return (void*) new wxStatusBar(parent, id, style);
    }

    EXPORT void wxStatusBar_SetFieldsCount(wxStatusBar* self, int number, int* widths)
    {
        self->SetFieldsCount(number, widths);
    }

    EXPORT int wxStatusBar_GetFieldsCount(wxStatusBar* self)
    {
        return self->GetFieldsCount();
    }

    EXPORT void wxStatusBar_SetStatusText(wxStatusBar* self, wxString* text, int number)
    {
        self->SetStatusText(*text, number);
    }

    EXPORT wxString* wxStatusBar_GetStatusText(wxStatusBar* self, int number)
    {
        wxString* result = new wxString();
        *result = self->GetStatusText(number);
        return result;
    }

    EXPORT void wxStatusBar_SetStatusWidths(wxStatusBar* self, int count, int* widths)
    {
        self->SetStatusWidths(count, widths);
    }

    EXPORT void wxStatusBar_SetMinHeight(wxStatusBar* self, int height)
    {
        self->SetMinHeight(height);
    }

    EXPORT int wxStatusBar_GetBorderX(wxStatusBar* self)
    {
        return self->GetBorderX();
    }

    EXPORT int wxStatusBar_GetBorderY(wxStatusBar* self)
    {
        return self->GetBorderY();
    }
}
