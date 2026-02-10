// wx_ribbongallery.cpp - wxRibbonGallery wrapper
#include "wrapper.h"

extern "C"
{
    // Constructor
    EXPORT wxRibbonGallery* wxRibbonGallery_Create(wxWindow* parent, int id, int x, int y, int width,
                                                   int height, int style)
    {
        return new wxRibbonGallery(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    // Item management
    EXPORT wxRibbonGalleryItem* wxRibbonGallery_Append(wxRibbonGallery* self, wxBitmap* bitmap,
                                                       int id)
    {
        return self->Append(*bitmap, id);
    }

    EXPORT wxRibbonGalleryItem* wxRibbonGallery_Append_WithClientData(wxRibbonGallery* self,
                                                                      wxBitmap* bitmap, int id,
                                                                      void* clientData)
    {
        return self->Append(*bitmap, id, clientData);
    }

    EXPORT void wxRibbonGallery_Clear(wxRibbonGallery* self)
    {
        self->Clear();
    }

    EXPORT bool wxRibbonGallery_IsEmpty(wxRibbonGallery* self)
    {
        return self->IsEmpty();
    }

    EXPORT unsigned int wxRibbonGallery_GetCount(wxRibbonGallery* self)
    {
        return self->GetCount();
    }

    EXPORT wxRibbonGalleryItem* wxRibbonGallery_GetItem(wxRibbonGallery* self, unsigned int index)
    {
        return self->GetItem(index);
    }

    // Selection
    EXPORT void wxRibbonGallery_SetSelection(wxRibbonGallery* self, wxRibbonGalleryItem* item)
    {
        self->SetSelection(item);
    }

    EXPORT wxRibbonGalleryItem* wxRibbonGallery_GetSelection(wxRibbonGallery* self)
    {
        return self->GetSelection();
    }

    EXPORT wxRibbonGalleryItem* wxRibbonGallery_GetHoveredItem(wxRibbonGallery* self)
    {
        return self->GetHoveredItem();
    }

    EXPORT wxRibbonGalleryItem* wxRibbonGallery_GetActiveItem(wxRibbonGallery* self)
    {
        return self->GetActiveItem();
    }

    // Client data
    EXPORT void wxRibbonGallery_SetItemClientData(wxRibbonGallery* self, wxRibbonGalleryItem* item,
                                                  void* data)
    {
        self->SetItemClientData(item, data);
    }

    EXPORT void* wxRibbonGallery_GetItemClientData(wxRibbonGallery* self, wxRibbonGalleryItem* item)
    {
        return self->GetItemClientData(item);
    }

    // Scrolling
    EXPORT bool wxRibbonGallery_ScrollLines(wxRibbonGallery* self, int lines)
    {
        return self->ScrollLines(lines);
    }

    EXPORT bool wxRibbonGallery_ScrollPixels(wxRibbonGallery* self, int pixels)
    {
        return self->ScrollPixels(pixels);
    }

    EXPORT void wxRibbonGallery_EnsureVisible(wxRibbonGallery* self, wxRibbonGalleryItem* item)
    {
        self->EnsureVisible(item);
    }

    // Button states
    EXPORT int wxRibbonGallery_GetUpButtonState(wxRibbonGallery* self)
    {
        return (int) self->GetUpButtonState();
    }

    EXPORT int wxRibbonGallery_GetDownButtonState(wxRibbonGallery* self)
    {
        return (int) self->GetDownButtonState();
    }

    EXPORT int wxRibbonGallery_GetExtensionButtonState(wxRibbonGallery* self)
    {
        return (int) self->GetExtensionButtonState();
    }

    // State queries
    EXPORT bool wxRibbonGallery_IsHovered(wxRibbonGallery* self)
    {
        return self->IsHovered();
    }

    // Layout
    EXPORT bool wxRibbonGallery_IsSizingContinuous(wxRibbonGallery* self)
    {
        return self->IsSizingContinuous();
    }

    // Art provider
    EXPORT void wxRibbonGallery_SetArtProvider(wxRibbonGallery* self, wxRibbonArtProvider* art)
    {
        self->SetArtProvider(art);
    }

    EXPORT wxRibbonArtProvider* wxRibbonGallery_GetArtProvider(wxRibbonGallery* self)
    {
        return self->GetArtProvider();
    }

    // Events
    EXPORT int expEVT_RIBBONGALLERY_HOVER_CHANGED()
    {
        return wxEVT_RIBBONGALLERY_HOVER_CHANGED;
    }

    EXPORT int expEVT_RIBBONGALLERY_SELECTED()
    {
        return wxEVT_RIBBONGALLERY_SELECTED;
    }

    EXPORT int expEVT_RIBBONGALLERY_CLICKED()
    {
        return wxEVT_RIBBONGALLERY_CLICKED;
    }

    // Gallery button state constants
    EXPORT int expwxRIBBON_GALLERY_BUTTON_NORMAL()
    {
        return wxRIBBON_GALLERY_BUTTON_NORMAL;
    }

    EXPORT int expwxRIBBON_GALLERY_BUTTON_HOVERED()
    {
        return wxRIBBON_GALLERY_BUTTON_HOVERED;
    }

    EXPORT int expwxRIBBON_GALLERY_BUTTON_ACTIVE()
    {
        return wxRIBBON_GALLERY_BUTTON_ACTIVE;
    }

    EXPORT int expwxRIBBON_GALLERY_BUTTON_DISABLED()
    {
        return wxRIBBON_GALLERY_BUTTON_DISABLED;
    }

}  // extern "C"
