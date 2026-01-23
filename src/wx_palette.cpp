#include "wrapper.h"

extern "C"
{
    EXPORT void* wxPalette_CreateDefault()
    {
        return (void*) new wxPalette();
    }

    EXPORT void* wxPalette_CreateRGB(int count, void* red, void* green, void* blue)
    {
        return (void*) new wxPalette(count, (unsigned char*) red, (unsigned char*) green,
                                     (unsigned char*) blue);
    }

    EXPORT void wxPalette_Delete(wxPalette* self)
    {
        delete self;
    }

    EXPORT int wxPalette_GetPixel(wxPalette* self, wxUint8 red, wxUint8 green, wxUint8 blue)
    {
        return self->GetPixel(red, green, blue);
    }

    EXPORT bool wxPalette_GetRGB(wxPalette* self, int pixel, void* red, void* green, void* blue)
    {
        return self->GetRGB(pixel, (unsigned char*) red, (unsigned char*) green,
                            (unsigned char*) blue);
    }

    EXPORT bool wxPalette_IsOk(wxPalette* self)
    {
        return self->IsOk();
    }

    EXPORT void wxPalette_Assign(void* self, void* palette)
    {
        *((wxPalette*) self) = *((wxPalette*) palette);
    }

    EXPORT bool wxPalette_IsEqual(wxPalette* self, wxPalette* palette)
    {
        wxPalette* pal1 = self;
        wxPalette* pal2 = palette;
        if (pal1->GetColoursCount() == pal2->GetColoursCount())
        {
            bool equal = true;
            unsigned char red1 = 0;
            unsigned char red2 = 0;
            unsigned char green1 = 0;
            unsigned char green2 = 0;
            unsigned char blue1 = 0;
            unsigned char blue2 = 0;
            for (int x = 0; x < (pal1->GetColoursCount()); x++)
            {
                pal1->GetRGB(x, &red1, &green1, &blue1);
                pal2->GetRGB(x, &red2, &green2, &blue2);
                equal = equal && (red1 == red2 && green1 == green2 && blue1 == blue2);
            }
            return equal;
        }
        else
        {
            return false;
        }
    }
}
