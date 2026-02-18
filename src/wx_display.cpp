#include "kwx_wrapper.h"
#include <wx/display.h>

extern "C"
{
    // wxDisplay

    EXPORT int wxDisplay_GetCount()
    {
        return wxDisplay::GetCount();
    }

    EXPORT int wxDisplay_GetFromPoint(int x, int y)
    {
        return wxDisplay::GetFromPoint(wxPoint(x, y));
    }

    EXPORT int wxDisplay_GetFromWindow(wxWindow* win)
    {
        return wxDisplay::GetFromWindow(win);
    }

    EXPORT void* wxDisplay_Create(unsigned int index)
    {
        return (void*) new wxDisplay(index);
    }

    EXPORT void* wxDisplay_CreateFromWindow(wxWindow* win)
    {
        return (void*) new wxDisplay(win);
    }

    EXPORT void wxDisplay_Delete(wxDisplay* self)
    {
        delete self;
    }

    EXPORT bool wxDisplay_IsOk(wxDisplay* self)
    {
        return self->IsOk();
    }

    EXPORT void wxDisplay_GetClientArea(wxDisplay* self, int* x, int* y, int* width, int* height)
    {
        wxRect rect = self->GetClientArea();
        *x = rect.x;
        *y = rect.y;
        *width = rect.width;
        *height = rect.height;
    }

    EXPORT void wxDisplay_GetGeometry(wxDisplay* self, int* x, int* y, int* width, int* height)
    {
        wxRect rect = self->GetGeometry();
        *x = rect.x;
        *y = rect.y;
        *width = rect.width;
        *height = rect.height;
    }

    EXPORT wxString* wxDisplay_GetName(wxDisplay* self)
    {
        wxString* result = new wxString();
        *result = self->GetName();
        return result;
    }

    EXPORT bool wxDisplay_IsPrimary(wxDisplay* self)
    {
        return self->IsPrimary();
    }

    EXPORT double wxDisplay_GetScaleFactor(wxDisplay* self)
    {
        return self->GetScaleFactor();
    }

    EXPORT void wxDisplay_GetPPI(wxDisplay* self, int* width, int* height)
    {
        wxSize ppi = self->GetPPI();
        *width = ppi.x;
        *height = ppi.y;
    }

    // wxVideoMode

    EXPORT void* wxVideoMode_Create(int width, int height, int depth, int freq)
    {
        return (void*) new wxVideoMode(width, height, depth, freq);
    }

    EXPORT void wxVideoMode_Delete(wxVideoMode* self)
    {
        delete self;
    }

    EXPORT int wxVideoMode_GetWidth(wxVideoMode* self)
    {
        return self->GetWidth();
    }

    EXPORT int wxVideoMode_GetHeight(wxVideoMode* self)
    {
        return self->GetHeight();
    }

    EXPORT int wxVideoMode_GetDepth(wxVideoMode* self)
    {
        return self->GetDepth();
    }

    EXPORT bool wxVideoMode_IsOk(wxVideoMode* self)
    {
        return self->IsOk();
    }

    EXPORT bool wxVideoMode_Matches(wxVideoMode* self, wxVideoMode* other)
    {
        return self->Matches(*other);
    }

    EXPORT void* wxDisplay_GetCurrentMode(wxDisplay* self)
    {
        wxVideoMode* result = new wxVideoMode();
        *result = self->GetCurrentMode();
        return (void*) result;
    }
}
