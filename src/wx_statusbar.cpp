#include "kwx_wrapper.h"

// wxStatusBar inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

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

    EXPORT bool wxStatusBar_GetFieldRect(wxStatusBar* self, int i, int* x, int* y, int* w, int* h)
    {
        wxRect rect;
        bool result = self->GetFieldRect(i, rect);
        *x = rect.x;
        *y = rect.y;
        *w = rect.width;
        *h = rect.height;
        return result;
    }

    EXPORT void wxStatusBar_SetStatusStyles(wxStatusBar* self, int n, const int* styles)
    {
        self->SetStatusStyles(n, styles);
    }

    EXPORT void wxStatusBar_PushStatusText(wxStatusBar* self, wxString* text, int field)
    {
        self->PushStatusText(*text, field);
    }

    EXPORT void wxStatusBar_PopStatusText(wxStatusBar* self, int field)
    {
        self->PopStatusText(field);
    }

    EXPORT int wxStatusBar_GetStatusWidth(wxStatusBar* self, int n)
    {
        return self->GetStatusWidth(n);
    }

    EXPORT int wxStatusBar_GetStatusStyle(wxStatusBar* self, int n)
    {
        return self->GetStatusStyle(n);
    }
}
