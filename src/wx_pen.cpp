#include "wrapper.h"

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

    EXPORT void wxPen_Delete(void* self)
    {
        delete (wxPen*) self;
    }

    EXPORT void wxPen_Assign(void* self, void* pen)
    {
        *((wxPen*) self) = *((wxPen*) pen);
    }

    EXPORT bool wxPen_IsEqual(wxPen* self, wxPen* pen)
    {
        return *self == *pen;
    }

    EXPORT bool wxPen_IsOk(wxPen* self)
    {
        return self->IsOk();
    }

    EXPORT void wxPen_SetColour(void* self, wxColour* col)
    {
        ((wxPen*) self)->SetColour(*col);
    }

    EXPORT void wxPen_SetColourSingle(void* self, wxUint8 r, wxUint8 g, wxUint8 b)
    {
        ((wxPen*) self)->SetColour(r, g, b);
    }

    EXPORT void wxPen_SetWidth(void* self, int width)
    {
        ((wxPen*) self)->SetWidth(width);
    }

    EXPORT void wxPen_SetStyle(void* self, int style)
    {
        ((wxPen*) self)->SetStyle((wxPenStyle) style);
    }

    EXPORT void wxPen_SetStipple(void* self, wxBitmap* stipple)
    {
#if !defined(__WXGTK__)
        ((wxPen*) self)->SetStipple(*stipple);
#endif
    }

    EXPORT void wxPen_SetDashes(void* self, int nb_dashes, void* dash)
    {
        ((wxPen*) self)->SetDashes(nb_dashes, (wxDash*) dash);
    }

    EXPORT void wxPen_SetJoin(void* self, int join)
    {
        wxPenJoin _join = (wxPenJoin) join;
        ((wxPen*) self)->SetJoin(_join);
    }

    EXPORT void wxPen_SetCap(void* self, int cap)
    {
        wxPenCap _cap = (wxPenCap) cap;
        ((wxPen*) self)->SetCap(_cap);
    }

    EXPORT void wxPen_GetColour(void* self, wxColour* _ref)
    {
        *_ref = ((wxPen*) self)->GetColour();
    }

    EXPORT int wxPen_GetWidth(void* self)
    {
        return ((wxPen*) self)->GetWidth();
    }

    EXPORT int wxPen_GetStyle(void* self)
    {
        return ((wxPen*) self)->GetStyle();
    }

    EXPORT int wxPen_GetJoin(void* self)
    {
        return (int) ((wxPen*) self)->GetJoin();
    }

    EXPORT int wxPen_GetCap(void* self)
    {
        return (int) ((wxPen*) self)->GetCap();
    }

    EXPORT int wxPen_GetDashes(void* self, void* ptr)
    {
        return ((wxPen*) self)->GetDashes((wxDash**) ptr);
    }

    EXPORT void wxPen_GetStipple(void* self, wxBitmap* _ref)
    {
#if defined(__WXGTK__)
        *_ref = (GdkPixbuf*) nullptr;
#else
        *_ref = *(((wxPen*) self)->GetStipple());
#endif
    }
}
