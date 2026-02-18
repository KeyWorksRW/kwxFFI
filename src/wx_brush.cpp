#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxBrush* wxBrush_CreateDefault()
    {
        return new wxBrush();
    }

    EXPORT wxBrush* wxBrush_CreateFromBitmap(wxBitmap* bitmap)
    {
        return new wxBrush(*bitmap);
    }

    EXPORT wxBrush* wxBrush_CreateFromColour(wxColour* col, int style)
    {
        return new wxBrush(*col, (wxBrushStyle) style);
    }

    EXPORT void* wxBrush_CreateFromStock(int id)
    {
        switch (id)
        {
            case 0:
                return (void*) wxBLUE_BRUSH;
            case 1:
                return (void*) wxGREEN_BRUSH;
            case 2:
                return (void*) wxWHITE_BRUSH;
            case 3:
                return (void*) wxBLACK_BRUSH;
            case 4:
                return (void*) wxGREY_BRUSH;
            case 5:
                return (void*) wxMEDIUM_GREY_BRUSH;
            case 6:
                return (void*) wxLIGHT_GREY_BRUSH;
            case 7:
                return (void*) wxTRANSPARENT_BRUSH;
            case 8:
                return (void*) wxCYAN_BRUSH;
            case 9:
                return (void*) wxRED_BRUSH;
        }

        return nullptr;
    }

    EXPORT void wxBrush_Delete(wxBrush* self)
    {
        delete self;
    }

    EXPORT void wxBrush_SetColour(wxBrush* self, wxColour* col)
    {
        self->SetColour(*col);
    }

    EXPORT void wxBrush_SetColourSingle(wxBrush* self, wxUint8 r, wxUint8 g, wxUint8 b)
    {
        self->SetColour(r, g, b);
    }

    EXPORT void wxBrush_SetStyle(wxBrush* self, int style)
    {
        self->SetStyle((wxBrushStyle) style);
    }

    EXPORT void wxBrush_SetStipple(wxBrush* self, wxBitmap* stipple)
    {
        self->SetStipple(*stipple);
    }

    EXPORT void wxBrush_Assign(wxBrush* self, wxBrush* brush)
    {
        *self = *brush;
    }

    EXPORT bool wxBrush_IsEqual(wxBrush* self, wxBrush* brush)
    {
        return *self == *brush;
    }

    EXPORT void wxBrush_GetColour(wxBrush* self, wxColour* ref)
    {
        *ref = self->GetColour();
    }

    EXPORT int wxBrush_GetStyle(wxBrush* self)
    {
        return self->GetStyle();
    }

    EXPORT void wxBrush_GetStipple(wxBrush* self, wxBitmap* ref)
    {
        *ref = *(self->GetStipple());
    }

    EXPORT bool wxBrush_IsOk(wxBrush* self)
    {
        return self->IsOk();
    }
}
