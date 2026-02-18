#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void* wxIcon_CreateDefault()
    {
        return (void*) new wxIcon();
    }

    EXPORT void wxIcon_Delete(wxIcon* self)
    {
        delete self;
    }

    EXPORT void* wxIcon_FromRaw(void* data, int width, int height)
    {
#ifdef __WIN32__
        return (void*) new wxIcon((const char*) data, wxBITMAP_TYPE_ICO, width, height);
#else
        return (void*) new wxIcon((const char*) data, wxBITMAP_TYPE_ANY, width, height);
#endif
    }

    EXPORT void* wxIcon_FromXPM(void* data)
    {
        return (void*) new wxIcon((const char*) data);
    }

    EXPORT void* wxIcon_CreateLoad(wxString* name, long type, int width, int height)
    {
        return (void*) new wxIcon(*name, (wxBitmapType) type, width, height);
    }

    EXPORT bool wxIcon_Load(wxIcon* self, wxString* name, long type, int width, int height)
    {
#ifdef __WIN32__
        return self->LoadFile(*name, (wxBitmapType) type, width, height);
#else
        return self->LoadFile(*name, (wxBitmapType) type);
#endif
    }

    EXPORT void wxIcon_CopyFromBitmap(wxIcon* self, wxBitmap* bmp)
    {
#ifdef __WIN32__
        self->CopyFromBitmap(*bmp);
#endif
    }

    EXPORT bool wxIcon_IsOk(wxIcon* self)
    {
        return self->IsOk();
    }

    EXPORT int wxIcon_GetDepth(wxIcon* self)
    {
        return self->GetDepth();
    }

    EXPORT int wxIcon_GetWidth(wxIcon* self)
    {
        return self->GetWidth();
    }

    EXPORT int wxIcon_GetHeight(wxIcon* self)
    {
        return self->GetHeight();
    }

    EXPORT void wxIcon_Assign(wxIcon* self, void* other)
    {
        *self = *((wxIcon*) other);
    }

    EXPORT bool wxIcon_IsEqual(wxIcon* self, wxIcon* other)
    {
        wxIcon* icon1 = self;
        wxIcon* icon2 = other;
        wxBitmap bmp1;
        wxBitmap bmp2;
        bmp1.CopyFromIcon(*icon1);
        bmp2.CopyFromIcon(*icon2);
        wxImage image1 = (wxImage) bmp1.ConvertToImage();
        wxImage image2 = (wxImage) bmp2.ConvertToImage();
        wxImage* img1 = &image1;
        wxImage* img2 = &image2;
        if ((icon1->GetWidth() == icon2->GetWidth()) &&
            (icon1->GetHeight() == icon2->GetHeight()) && (icon1->GetDepth() == icon2->GetDepth()))
        {
            bool equal = true;
            for (int sizeX = 0; sizeX < (icon1->GetWidth()); sizeX++)
            {
                for (int sizeY = 0; sizeY < (icon1->GetHeight()); sizeY++)
                {
                    equal = equal && (img1->GetRed(sizeX, sizeY) == img2->GetRed(sizeX, sizeY) &&
                                      img1->GetGreen(sizeX, sizeY) == img2->GetGreen(sizeX, sizeY) &&
                                      img1->GetBlue(sizeX, sizeY) == img2->GetBlue(sizeX, sizeY) &&
                                      img1->GetAlpha(sizeX, sizeY) == img2->GetAlpha(sizeX, sizeY));
                }
            }
            return equal;
        }
        else
        {
            return false;
        }
    }
}
