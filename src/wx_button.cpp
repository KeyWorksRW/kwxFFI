#include "wrapper.h"

extern "C"
{
    EXPORT wxButton* wxButton_Create(wxWindow* parent, int id, wxString* text, int x, int y,
                                     int width, int height, int style)
    {
        return new wxButton(parent, id, *text, wxPoint(x, y), wxSize(width, height), style,
                            wxDefaultValidator);
    }

    EXPORT bool wxButton_SetBackgroundColour(wxButton* self, wxColour* colour)
    {
        return self->SetBackgroundColour(*colour);
    }

    EXPORT void wxButton_SetDefault(wxButton* self)
    {
        self->SetDefault();
    }

    EXPORT wxBitmapButton* wxBitmapButton_Create(wxWindow* parent, int id, wxBitmap* bitmap, int x,
                                                 int y, int width, int height, int style)
    {
        return new wxBitmapButton(parent, id, *bitmap, wxPoint(x, y), wxSize(width, height), style,
                                  wxDefaultValidator);
    }

    EXPORT void wxBitmapButton_GetBitmapLabel(wxBitmapButton* self, wxBitmap* ref)
    {
        *ref = self->GetBitmapLabel();
    }

    EXPORT void wxBitmapButton_GetBitmapSelected(wxBitmapButton* self, wxBitmap* ref)
    {
        *ref = self->GetBitmapSelected();
    }

    EXPORT void wxBitmapButton_GetBitmapFocus(wxBitmapButton* self, wxBitmap* ref)
    {
        *ref = self->GetBitmapFocus();
    }

    EXPORT void wxBitmapButton_GetBitmapDisabled(wxBitmapButton* self, wxBitmap* ref)
    {
        *ref = self->GetBitmapDisabled();
    }

    EXPORT void wxBitmapButton_SetBitmapSelected(wxBitmapButton* self, wxBitmap* sel)
    {
        self->SetBitmapSelected(*sel);
    }

    EXPORT void wxBitmapButton_SetBitmapFocus(wxBitmapButton* self, wxBitmap* focus)
    {
        self->SetBitmapFocus(*focus);
    }

    EXPORT void wxBitmapButton_SetBitmapDisabled(wxBitmapButton* self, wxBitmap* disabled)
    {
        self->SetBitmapDisabled(*disabled);
    }

    EXPORT void wxBitmapButton_SetBitmapLabel(wxBitmapButton* self, wxBitmap* bitmap)
    {
        self->SetBitmapLabel(*bitmap);
    }

    EXPORT void wxBitmapButton_SetMargins(wxBitmapButton* self, int x, int y)
    {
        self->SetMargins(x, y);
    }

    EXPORT int wxBitmapButton_GetMarginX(wxBitmapButton* self)
    {
        return self->GetMarginX();
    }

    EXPORT int wxBitmapButton_GetMarginY(wxBitmapButton* self)
    {
        return self->GetMarginY();
    }
}
