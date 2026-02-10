// wx_ribbonbuttonbar.cpp - wxRibbonButtonBar wrapper
#include "wrapper.h"

extern "C"
{
    // Constructor
    EXPORT wxRibbonButtonBar* wxRibbonButtonBar_Create(wxWindow* parent, int id, int x, int y,
                                                       int width, int height, int style)
    {
        return new wxRibbonButtonBar(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    // Button management - Add methods
    EXPORT wxRibbonButtonBarButtonBase*
        wxRibbonButtonBar_AddButton(wxRibbonButtonBar* self, int button_id, wxString* label,
                                    wxBitmap* bitmap, wxBitmap* bitmap_small,
                                    wxBitmap* bitmap_disabled, wxBitmap* bitmap_small_disabled,
                                    wxString* help_string, int kind)
    {
        wxBitmap bmpSmall = bitmap_small ? *bitmap_small : wxNullBitmap;
        wxBitmap bmpDisabled = bitmap_disabled ? *bitmap_disabled : wxNullBitmap;
        wxBitmap bmpSmallDisabled = bitmap_small_disabled ? *bitmap_small_disabled : wxNullBitmap;
        return self->AddButton(button_id, *label, *bitmap, bmpSmall, bmpDisabled, bmpSmallDisabled,
                               (wxRibbonButtonKind) kind, *help_string);
    }

    EXPORT wxRibbonButtonBarButtonBase*
        wxRibbonButtonBar_AddDropdownButton(wxRibbonButtonBar* self, int button_id, wxString* label,
                                            wxBitmap* bitmap, wxString* help_string)
    {
        return self->AddDropdownButton(button_id, *label, *bitmap, *help_string);
    }

    EXPORT wxRibbonButtonBarButtonBase*
        wxRibbonButtonBar_AddHybridButton(wxRibbonButtonBar* self, int button_id, wxString* label,
                                          wxBitmap* bitmap, wxString* help_string)
    {
        return self->AddHybridButton(button_id, *label, *bitmap, *help_string);
    }

    EXPORT wxRibbonButtonBarButtonBase*
        wxRibbonButtonBar_AddToggleButton(wxRibbonButtonBar* self, int button_id, wxString* label,
                                          wxBitmap* bitmap, wxString* help_string)
    {
        return self->AddToggleButton(button_id, *label, *bitmap, *help_string);
    }

    // Button management - Insert methods
    EXPORT wxRibbonButtonBarButtonBase*
        wxRibbonButtonBar_InsertButton(wxRibbonButtonBar* self, size_t pos, int button_id,
                                       wxString* label, wxBitmap* bitmap, wxBitmap* bitmap_small,
                                       wxBitmap* bitmap_disabled, wxBitmap* bitmap_small_disabled,
                                       wxString* help_string, int kind)
    {
        wxBitmap bmpSmall = bitmap_small ? *bitmap_small : wxNullBitmap;
        wxBitmap bmpDisabled = bitmap_disabled ? *bitmap_disabled : wxNullBitmap;
        wxBitmap bmpSmallDisabled = bitmap_small_disabled ? *bitmap_small_disabled : wxNullBitmap;
        return self->InsertButton(pos, button_id, *label, *bitmap, bmpSmall, bmpDisabled,
                                  bmpSmallDisabled, (wxRibbonButtonKind) kind, *help_string);
    }

    EXPORT wxRibbonButtonBarButtonBase*
        wxRibbonButtonBar_InsertDropdownButton(wxRibbonButtonBar* self, size_t pos, int button_id,
                                               wxString* label, wxBitmap* bitmap,
                                               wxString* help_string)
    {
        return self->InsertDropdownButton(pos, button_id, *label, *bitmap, *help_string);
    }

    EXPORT wxRibbonButtonBarButtonBase*
        wxRibbonButtonBar_InsertHybridButton(wxRibbonButtonBar* self, size_t pos, int button_id,
                                             wxString* label, wxBitmap* bitmap,
                                             wxString* help_string)
    {
        return self->InsertHybridButton(pos, button_id, *label, *bitmap, *help_string);
    }

    EXPORT wxRibbonButtonBarButtonBase*
        wxRibbonButtonBar_InsertToggleButton(wxRibbonButtonBar* self, size_t pos, int button_id,
                                             wxString* label, wxBitmap* bitmap,
                                             wxString* help_string)
    {
        return self->InsertToggleButton(pos, button_id, *label, *bitmap, *help_string);
    }

    // Button management - Delete/Clear
    EXPORT void wxRibbonButtonBar_ClearButtons(wxRibbonButtonBar* self)
    {
        self->ClearButtons();
    }

    EXPORT bool wxRibbonButtonBar_DeleteButton(wxRibbonButtonBar* self, int button_id)
    {
        return self->DeleteButton(button_id);
    }

    // Button properties
    EXPORT void wxRibbonButtonBar_EnableButton(wxRibbonButtonBar* self, int button_id, bool enable)
    {
        self->EnableButton(button_id, enable);
    }

    EXPORT void wxRibbonButtonBar_SetButtonIcon(wxRibbonButtonBar* self, int button_id,
                                                wxBitmap* bitmap, wxBitmap* bitmap_small,
                                                wxBitmap* bitmap_disabled,
                                                wxBitmap* bitmap_small_disabled)
    {
        wxBitmap bmpSmall = bitmap_small ? *bitmap_small : wxNullBitmap;
        wxBitmap bmpDisabled = bitmap_disabled ? *bitmap_disabled : wxNullBitmap;
        wxBitmap bmpSmallDisabled = bitmap_small_disabled ? *bitmap_small_disabled : wxNullBitmap;
        self->SetButtonIcon(button_id, *bitmap, bmpSmall, bmpDisabled, bmpSmallDisabled);
    }

    EXPORT void wxRibbonButtonBar_SetButtonText(wxRibbonButtonBar* self, int button_id,
                                                wxString* label)
    {
        self->SetButtonText(button_id, *label);
    }

    EXPORT void wxRibbonButtonBar_SetButtonTextMinWidth_Int(wxRibbonButtonBar* self, int button_id,
                                                            int min_width_medium,
                                                            int min_width_large)
    {
        self->SetButtonTextMinWidth(button_id, min_width_medium, min_width_large);
    }

    EXPORT void wxRibbonButtonBar_SetButtonTextMinWidth_String(wxRibbonButtonBar* self,
                                                               int button_id, wxString* label)
    {
        self->SetButtonTextMinWidth(button_id, *label);
    }

    EXPORT void wxRibbonButtonBar_SetButtonMinSizeClass(wxRibbonButtonBar* self, int button_id,
                                                        int min_class)
    {
        self->SetButtonMinSizeClass(button_id, (wxRibbonButtonBarButtonState) min_class);
    }

    EXPORT void wxRibbonButtonBar_SetButtonMaxSizeClass(wxRibbonButtonBar* self, int button_id,
                                                        int max_class)
    {
        self->SetButtonMaxSizeClass(button_id, (wxRibbonButtonBarButtonState) max_class);
    }

    // Button access
    EXPORT size_t wxRibbonButtonBar_GetButtonCount(wxRibbonButtonBar* self)
    {
        return self->GetButtonCount();
    }

    EXPORT wxRibbonButtonBarButtonBase* wxRibbonButtonBar_GetItem(wxRibbonButtonBar* self, size_t index)
    {
        return self->GetItem(index);
    }

    EXPORT wxRibbonButtonBarButtonBase* wxRibbonButtonBar_GetItemById(wxRibbonButtonBar* self,
                                                                      int button_id)
    {
        return self->GetItemById(button_id);
    }

    EXPORT int wxRibbonButtonBar_GetItemId(wxRibbonButtonBar* self,
                                           wxRibbonButtonBarButtonBase* button)
    {
        return self->GetItemId(button);
    }

    EXPORT void wxRibbonButtonBar_GetItemRect(wxRibbonButtonBar* self, int button_id, int* x,
                                              int* y, int* width, int* height)
    {
        wxRect r = self->GetItemRect(button_id);
        *x = r.x;
        *y = r.y;
        *width = r.width;
        *height = r.height;
    }

    EXPORT wxRibbonButtonBarButtonBase* wxRibbonButtonBar_GetActiveItem(wxRibbonButtonBar* self)
    {
        return self->GetActiveItem();
    }

    EXPORT wxRibbonButtonBarButtonBase* wxRibbonButtonBar_GetHoveredItem(wxRibbonButtonBar* self)
    {
        return self->GetHoveredItem();
    }

    // Client data
    EXPORT void wxRibbonButtonBar_SetItemClientData(wxRibbonButtonBar* self,
                                                    wxRibbonButtonBarButtonBase* item, void* data)
    {
        self->SetItemClientData(item, data);
    }

    EXPORT void* wxRibbonButtonBar_GetItemClientData(wxRibbonButtonBar* self,
                                                     wxRibbonButtonBarButtonBase* item)
    {
        return self->GetItemClientData(item);
    }

    // Tooltips
    EXPORT void wxRibbonButtonBar_SetShowToolTipsForDisabled(wxRibbonButtonBar* self, bool show)
    {
        self->SetShowToolTipsForDisabled(show);
    }

    EXPORT bool wxRibbonButtonBar_GetShowToolTipsForDisabled(wxRibbonButtonBar* self)
    {
        return self->GetShowToolTipsForDisabled();
    }

    // Layout
    EXPORT void wxRibbonButtonBar_Realize(wxRibbonButtonBar* self)
    {
        self->Realize();
    }

    // Art provider
    EXPORT void wxRibbonButtonBar_SetArtProvider(wxRibbonButtonBar* self, wxRibbonArtProvider* art)
    {
        self->SetArtProvider(art);
    }

    EXPORT wxRibbonArtProvider* wxRibbonButtonBar_GetArtProvider(wxRibbonButtonBar* self)
    {
        return self->GetArtProvider();
    }

    // Events
    EXPORT int expEVT_RIBBONBUTTONBAR_CLICKED()
    {
        return wxEVT_RIBBONBUTTONBAR_CLICKED;
    }

    EXPORT int expEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED()
    {
        return wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED;
    }

    // Button kind constants
    EXPORT int expwxRIBBON_BUTTON_NORMAL()
    {
        return wxRIBBON_BUTTON_NORMAL;
    }

    EXPORT int expwxRIBBON_BUTTON_DROPDOWN()
    {
        return wxRIBBON_BUTTON_DROPDOWN;
    }

    EXPORT int expwxRIBBON_BUTTON_HYBRID()
    {
        return wxRIBBON_BUTTON_HYBRID;
    }

    EXPORT int expwxRIBBON_BUTTON_TOGGLE()
    {
        return wxRIBBON_BUTTON_TOGGLE;
    }

    // Button size class constants
    EXPORT int expwxRIBBON_BUTTONBAR_BUTTON_SMALL()
    {
        return wxRIBBON_BUTTONBAR_BUTTON_SMALL;
    }

    EXPORT int expwxRIBBON_BUTTONBAR_BUTTON_MEDIUM()
    {
        return wxRIBBON_BUTTONBAR_BUTTON_MEDIUM;
    }

    EXPORT int expwxRIBBON_BUTTONBAR_BUTTON_LARGE()
    {
        return wxRIBBON_BUTTONBAR_BUTTON_LARGE;
    }

}  // extern "C"
