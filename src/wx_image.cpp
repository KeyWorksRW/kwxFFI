#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void wxImage_Copy(wxImage* self, wxImage* image)
    {
        *image = self->Copy();
    }

    EXPORT wxImage* wxImage_CreateDefault()
    {
        return new wxImage();
    }

    EXPORT wxImage* wxImage_CreateSized(int width, int height)
    {
        return new wxImage(width, height);
    }

    EXPORT wxImage* wxImage_CreateFromByteString(const wxSize& text, unsigned char* data)
    {
        return new wxImage(text, data);
    }

    EXPORT wxImage* wxImage_CreateFromLazyByteString(const wxSize& text, unsigned char* data)
    {
        return new wxImage(text, data);
    }

    EXPORT size_t wxImage_ConvertToByteString(wxImage* self, wxBitmapType type, char* data)
    {
        wxMemoryOutputStream out;
        self->SaveFile(out, type);
        size_t len = out.GetLength();
        if (!data)
            return len;
        return out.CopyTo(data, len);
    }

    EXPORT size_t wxImage_ConvertToLazyByteString(wxImage* self, wxBitmapType type, char* data)
    {
        wxMemoryOutputStream out;
        self->SaveFile(out, type);
        size_t len = out.GetLength();
        if (!data)
            return len;
        return out.CopyTo(data, len);
    }

    EXPORT wxImage* wxImage_CreateFromData(int width, int height, void* data)
    {
        return new wxImage(width, height, (unsigned char*) data, true);
    }

    EXPORT wxImage* wxImage_CreateFromFile(wxString* name)
    {
        return new wxImage(*name);
    }

    EXPORT wxImage* wxImage_CreateFromBitmap(wxBitmap* bitmap)
    {
        return new wxImage(bitmap->ConvertToImage());
    }

    EXPORT void wxImage_ConvertToBitmap(wxImage* self, wxBitmap* bitmap)
    {
        wxBitmap tmp(*self);
        *bitmap = tmp;
    }

    EXPORT void wxImage_Initialize(wxImage* self, int width, int height, bool clear)
    {
        self->Create(width, height, clear);
    }

    EXPORT void wxImage_InitializeFromData(wxImage* self, int width, int height, void* data)
    {
        self->Create(width, height, (unsigned char*) data, true);
    }

    EXPORT void wxImage_Destroy(wxImage* self)
    {
        self->Destroy();
    }

    EXPORT void wxImage_GetSubImage(wxImage* self, int x, int y, int width, int height, wxImage* image)
    {
        *image = self->GetSubImage(wxRect(x, y, width, height));
    }

    EXPORT int wxImage_GetType(wxImage* self)
    {
        return self->GetType();
    }

    EXPORT void wxImage_SetType(wxImage* self, int type)
    {
        self->SetType((wxBitmapType) type);
    }

    EXPORT void wxImage_Paste(wxImage* self, wxImage* image, int x, int y, int alphaBlend)
    {
        self->Paste(*image, x, y, (wxImageAlphaBlendMode) alphaBlend);
    }

    EXPORT void wxImage_Scale(wxImage* self, int width, int height, wxImage* image)
    {
        *image = self->Scale(width, height);
    }

    EXPORT void wxImage_ScaleEx(wxImage* self, int width, int height, int quality, wxImage* image)
    {
        *image = self->Scale(width, height, (wxImageResizeQuality) quality);
    }

    EXPORT void wxImage_Rescale(wxImage* self, int width, int height)
    {
        self->Rescale(width, height);
    }

    EXPORT void wxImage_RescaleEx(wxImage* self, int width, int height, int quality)
    {
        self->Rescale(width, height, (wxImageResizeQuality) quality);
    }

    EXPORT void wxImage_Rotate(wxImage* self, double angle, int c_x, int c_y, bool interpolating,
                               void* offset_after_rotation, wxImage* image)
    {
        *image =
            self->Rotate(angle, wxPoint(c_x, c_y), interpolating, (wxPoint*) offset_after_rotation);
    }

    EXPORT void wxImage_Rotate90(wxImage* self, bool clockwise, wxImage* image)
    {
        *image = self->Rotate90(clockwise);
    }

    EXPORT void wxImage_Mirror(wxImage* self, bool horizontally, wxImage* image)
    {
        *image = self->Mirror(horizontally);
    }

    EXPORT void wxImage_Replace(wxImage* self, wxUint8 r1, wxUint8 g1, wxUint8 b1, wxUint8 r2,
                                wxUint8 g2, wxUint8 b2)
    {
        self->Replace(r1, g1, b1, r2, g2, b2);
    }

    EXPORT void wxImage_SetRGB(wxImage* self, int x, int y, wxUint8 r, wxUint8 g, wxUint8 b)
    {
        self->SetRGB(x, y, r, g, b);
    }

    EXPORT wxUint8 wxImage_GetRed(wxImage* self, int x, int y)
    {
        return self->GetRed(x, y);
    }

    EXPORT wxUint8 wxImage_GetGreen(wxImage* self, int x, int y)
    {
        return self->GetGreen(x, y);
    }

    EXPORT wxUint8 wxImage_GetBlue(wxImage* self, int x, int y)
    {
        return self->GetBlue(x, y);
    }

    EXPORT bool wxImage_CanRead(wxString* name)
    {
        return wxImage::CanRead(*name);
    }

    EXPORT bool wxImage_LoadFile(wxImage* self, wxString* name, wxBitmapType type, int index)
    {
        return self->LoadFile(*name, type, index);
    }

    EXPORT bool wxImage_LoadStream(wxImage* self, wxInputStream* stream, wxBitmapType type,
                                   int index)
    {
        return self->LoadFile(*stream, type, index);
    }

    EXPORT bool wxImage_SaveFile(wxImage* self, wxString* name, wxBitmapType type)
    {
        return self->SaveFile(*name, type);
    }

    EXPORT bool wxImage_SaveStream(wxImage* self, wxOutputStream* stream, wxBitmapType type)
    {
        return self->SaveFile(*stream, type);
    }

    EXPORT bool wxImage_IsOk(wxImage* self)
    {
        return self->IsOk();
    }

    EXPORT int wxImage_GetWidth(wxImage* self)
    {
        return self->GetWidth();
    }

    EXPORT int wxImage_GetHeight(wxImage* self)
    {
        return self->GetHeight();
    }

    EXPORT void* wxImage_GetData(wxImage* self)
    {
        return (void*) self->GetData();
    }

    EXPORT void wxImage_SetData(wxImage* self, void* data, bool static_data)
    {
        self->SetData((unsigned char*) data, static_data);
    }

    EXPORT void wxImage_SetDataAndSize(wxImage* self, char* data, int new_width, int new_height,
                                       bool static_data)
    {
        self->SetData((unsigned char*) data, new_width, new_height, static_data);
    }

    EXPORT void wxImage_SetMaskColour(wxImage* self, wxUint8 r, wxUint8 g, wxUint8 b)
    {
        self->SetMaskColour(r, g, b);
    }

    EXPORT wxUint8 wxImage_GetMaskRed(wxImage* self)
    {
        return self->GetMaskRed();
    }

    EXPORT wxUint8 wxImage_GetMaskGreen(wxImage* self)
    {
        return self->GetMaskGreen();
    }

    EXPORT wxUint8 wxImage_GetMaskBlue(wxImage* self)
    {
        return self->GetMaskBlue();
    }

    EXPORT void wxImage_SetMask(wxImage* self, bool mask)
    {
        self->SetMask(mask);
    }

    EXPORT bool wxImage_HasMask(wxImage* self)
    {
        return self->HasMask();
    }

    EXPORT int wxImage_CountColours(wxImage* self, int stopafter)
    {
        return self->CountColours((long) stopafter);
    }

    EXPORT wxString* wxImage_GetOption(wxImage* self, wxString* key)
    {
        wxString* result = new wxString();
        *result = self->GetOption(*key);
        return result;
    }

    EXPORT int wxImage_GetOptionInt(wxImage* self, wxString* key)
    {
        return self->GetOptionInt(*key);
    }

    EXPORT void wxImage_SetOption(wxImage* self, wxString* key, wxString* value)
    {
        self->SetOption(*key, *value);
    }

    EXPORT void wxImage_SetOptionInt(wxImage* self, wxString* key, int value)
    {
        self->SetOption(*key, value);
    }

    EXPORT int wxImage_HasOption(wxImage* self, wxString* key)
    {
        return self->HasOption(*key);
    }
}
