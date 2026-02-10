#include "wrapper.h"

extern "C"
{
    EXPORT wxColour* wxColour_CreateEmpty()
    {
        return new wxColour();
    }

    EXPORT wxColour* wxColour_CreateRGB(wxUint8 _red, wxUint8 _green, wxUint8 _blue, wxUint8 _alpha)
    {
        return new wxColour(_red, _green, _blue, _alpha);
    }

    EXPORT wxColour* wxColour_CreateByName(wxString* _name)
    {
        return new wxColour(*_name);
    }

    EXPORT void* wxColour_CreateFromStock(int _id)
    {
        switch (_id)
        {
            case 0:
                return (void*) wxBLACK;
            case 1:
                return (void*) wxWHITE;
            case 2:
                return (void*) wxRED;
            case 3:
                return (void*) wxBLUE;
            case 4:
                return (void*) wxGREEN;
            case 5:
                return (void*) wxCYAN;
            case 6:
                return (void*) wxLIGHT_GREY;
        }

        return nullptr;
    }

    EXPORT void wxColour_Delete(wxColour* self)
    {
        delete self;
    }

    EXPORT void wxColour_Set(wxColour* self, wxUint8 _red, wxUint8 _green, wxUint8 _blue,
                             wxUint8 _alpha)
    {
        self->Set(_red, _green, _blue, _alpha);
    }

    EXPORT void wxColour_Assign(wxColour* self, wxColour* other)
    {
        *self = *other;
    }

    // Returning int instead of bool, due bool not being supported out of the box
    // by Foreign.C.Types, and size of bool varying between platforms and compiler
    // implementations.
    EXPORT int wxColour_IsOk(wxColour* self)
    {
        return self->IsOk();
    }

    EXPORT wxUint8 wxColour_Red(wxColour* self)
    {
        return self->Red();
    }

    EXPORT wxUint8 wxColour_Green(wxColour* self)
    {
        return self->Green();
    }

    EXPORT wxUint8 wxColour_Blue(wxColour* self)
    {
        return self->Blue();
    }

    EXPORT wxUint8 wxColour_Alpha(wxColour* self)
    {
        return self->Alpha();
    }

    // FIXME: the return type on this is platform dependent
    // and thus evil.  If you really want a GetPixel method,
    // please hack this code and throw in the relevant
    // ifdefs, cuz I don't want to deal with it.
    //   Windows - WXCOLORREF
    //   GTK     - int
    //   X11     - long
    //   Mac     - (WXCOLORREF&)
    // EWXWEXPORT(WXCOLORREF,wxColour_GetPixel)(wxColour* self)
    // {
    // 	return self->GetPixel();
    // }

    EXPORT void wxColour_Copy(wxColour* self, wxColour* _other)
    {
        *self = *_other;
    }

    EXPORT void wxColour_SetByName(wxColour* self, wxString* _name)
    {
        *self = *_name;
    }

    EXPORT bool wxColour_ValidName(wxString* _name)
    {
        return wxTheColourDatabase->Find(*_name).IsOk();
    }
}
