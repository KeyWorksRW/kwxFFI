#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxColour* wxColour_CreateEmpty()
    {
        return new wxColour();
    }

    EXPORT wxColour* wxColour_CreateRGB(wxUint8 red, wxUint8 green, wxUint8 blue, wxUint8 alpha)
    {
        return new wxColour(red, green, blue, alpha);
    }

    EXPORT wxColour* wxColour_CreateByName(wxString* name)
    {
        return new wxColour(*name);
    }

    EXPORT void* wxColour_CreateFromStock(int id)
    {
        switch (id)
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

    EXPORT void wxColour_Set(wxColour* self, wxUint8 red, wxUint8 green, wxUint8 blue,
                             wxUint8 alpha)
    {
        self->Set(red, green, blue, alpha);
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

    EXPORT void wxColour_Copy(wxColour* self, wxColour* other)
    {
        *self = *other;
    }

    EXPORT void wxColour_SetByName(wxColour* self, wxString* name)
    {
        *self = *name;
    }

    EXPORT bool wxColour_ValidName(wxString* name)
    {
        return wxTheColourDatabase->Find(*name).IsOk();
    }
}
