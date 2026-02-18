#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxImageList* wxImageList_Create(int width, int height, bool mask, int initialCount)
    {
        return new wxImageList(width, height, mask, initialCount);
    }

    EXPORT void wxImageList_Delete(wxImageList* self)
    {
        delete self;
    }

    EXPORT int wxImageList_GetImageCount(wxImageList* self)
    {
        return self->GetImageCount();
    }

    EXPORT void wxImageList_GetSize(wxImageList* self, int index, int* width, int* height)
    {
        bool success = self->GetSize(index, *width, *height);
        if (!success)
        {
            *width = -1;
            *height = -1;
        };
    }

    EXPORT int wxImageList_AddBitmap(wxImageList* self, wxBitmap* bitmap, wxBitmap* mask)
    {
        return self->Add(*bitmap, *mask);
    }

    EXPORT int wxImageList_AddMasked(wxImageList* self, wxBitmap* bitmap, wxColour* maskColour)
    {
        return self->Add(*bitmap, *maskColour);
    }

    EXPORT int wxImageList_AddIcon(wxImageList* self, wxIcon* icon)
    {
        return self->Add(*icon);
    }

    EXPORT bool wxImageList_Replace(wxImageList* self, int index, wxBitmap* bitmap, wxBitmap* mask)
    {
#ifdef __WIN32__
        return self->Replace(index, *bitmap, *mask);
#else
        return self->Replace(index, *bitmap);
#endif
    }

    EXPORT bool wxImageList_ReplaceIcon(wxImageList* self, int index, wxIcon* icon)
    {
        return self->Replace(index, *icon);
    }

    EXPORT bool wxImageList_Remove(wxImageList* self, int index)
    {
        return self->Remove(index);
    }

    EXPORT bool wxImageList_RemoveAll(wxImageList* self)
    {
        return self->RemoveAll();
    }

    EXPORT bool wxImageList_Draw(wxImageList* self, int index, wxDC* dc, int x, int y, int flags,
                                 bool solidBackground)
    {
        return self->Draw(index, *dc, x, y, flags, solidBackground);
    }
}
