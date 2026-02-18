#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxPen_CreateDefault()
    {
        return new wxPen();
    }

    EXPORT void* wxPen_CreateFromColour(wxColour* col, int width, int style)
    {
        return new wxPen(*col, width, (wxPenStyle) style);
    }

    EXPORT void* wxPen_CreateFromBitmap(wxBitmap* stipple, int width)
    {
#ifdef __WXGTK__
        return 0;
#else
        return new wxPen(*stipple, width);
#endif
    }

    EXPORT void* wxPen_CreateFromStock(int id)
    {
        switch (id)
        {
            case 0:
                return (void*) wxRED_PEN;
            case 1:
                return (void*) wxCYAN_PEN;
            case 2:
                return (void*) wxGREEN_PEN;
            case 3:
                return (void*) wxBLACK_PEN;
            case 4:
                return (void*) wxWHITE_PEN;
            case 5:
                return (void*) wxTRANSPARENT_PEN;
            case 6:
                return (void*) wxBLACK_DASHED_PEN;
            case 7:
                return (void*) wxGREY_PEN;
            case 8:
                return (void*) wxMEDIUM_GREY_PEN;
            case 9:
                return (void*) wxLIGHT_GREY_PEN;
        }

        return nullptr;
    }

    EXPORT void wxPen_Delete(wxPen* self)
    {
        delete self;
    }

    EXPORT void wxPen_Assign(wxPen* self, void* pen)
    {
        *self = *((wxPen*) pen);
    }

    EXPORT bool wxPen_IsEqual(wxPen* self, wxPen* pen)
    {
        return *self == *pen;
    }

    EXPORT bool wxPen_IsOk(wxPen* self)
    {
        return self->IsOk();
    }

    EXPORT void wxPen_SetColour(wxPen* self, wxColour* col)
    {
        self->SetColour(*col);
    }

    EXPORT void wxPen_SetColourSingle(wxPen* self, wxUint8 r, wxUint8 g, wxUint8 b)
    {
        self->SetColour(r, g, b);
    }

    EXPORT void wxPen_SetWidth(wxPen* self, int width)
    {
        self->SetWidth(width);
    }

    EXPORT void wxPen_SetStyle(wxPen* self, int style)
    {
        self->SetStyle((wxPenStyle) style);
    }

    EXPORT void wxPen_SetStipple(wxPen* self, wxBitmap* stipple)
    {
#if !defined(__WXGTK__)
        self->SetStipple(*stipple);
#endif
    }

    EXPORT void wxPen_SetDashes(wxPen* self, int nb_dashes, void* dash)
    {
        self->SetDashes(nb_dashes, (wxDash*) dash);
    }

    EXPORT void wxPen_SetJoin(wxPen* self, int join)
    {
        wxPenJoin joinStyle = (wxPenJoin) join;
        self->SetJoin(joinStyle);
    }

    EXPORT void wxPen_SetCap(wxPen* self, int cap)
    {
        wxPenCap penCap = (wxPenCap) cap;
        self->SetCap(penCap);
    }

    EXPORT void wxPen_GetColour(wxPen* self, wxColour* ref)
    {
        *ref = self->GetColour();
    }

    EXPORT int wxPen_GetWidth(wxPen* self)
    {
        return self->GetWidth();
    }

    EXPORT int wxPen_GetStyle(wxPen* self)
    {
        return self->GetStyle();
    }

    EXPORT int wxPen_GetJoin(wxPen* self)
    {
        return (int) self->GetJoin();
    }

    EXPORT int wxPen_GetCap(wxPen* self)
    {
        return (int) self->GetCap();
    }

    EXPORT int wxPen_GetDashes(wxPen* self, void* ptr)
    {
        return self->GetDashes((wxDash**) ptr);
    }

    EXPORT void wxPen_GetStipple(wxPen* self, wxBitmap* ref)
    {
#if defined(__WXGTK__)
        *ref = (GdkPixbuf*) nullptr;
#else
        *ref = *(self->GetStipple());
#endif
    }
}
