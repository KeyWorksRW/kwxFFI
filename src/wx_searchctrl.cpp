#include "kwx_wrapper.h"

// wxSearchCtrl inherits from wxControl and wxTextEntry.
// Additional methods available via:
//   wxWindow_*    — base window methods (see wx_window.cpp)
//   wxControl_*   — label, alignment (see wx_control.cpp)
//   wxTextEntry_* — text editing, hints, margins, selection, auto-complete (see wx_textentry.cpp)

extern "C"
{
    EXPORT wxSearchCtrl* wxSearchCtrl_Create(wxWindow* parent, int id, wxString* value, int x,
                                             int y, int width, int height, int style)
    {
        return new wxSearchCtrl(parent, id, *value, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxSearchCtrl_SetMenu(wxSearchCtrl* self, wxMenu* menu)
    {
        self->SetMenu(menu);
    }

    EXPORT wxMenu* wxSearchCtrl_GetMenu(wxSearchCtrl* self)
    {
        return self->GetMenu();
    }

    EXPORT void wxSearchCtrl_ShowSearchButton(wxSearchCtrl* self, bool show)
    {
        self->ShowSearchButton(show);
    }

    EXPORT bool wxSearchCtrl_IsSearchButtonVisible(wxSearchCtrl* self)
    {
        return self->IsSearchButtonVisible();
    }

    EXPORT void wxSearchCtrl_ShowCancelButton(wxSearchCtrl* self, bool show)
    {
        self->ShowCancelButton(show);
    }

    EXPORT bool wxSearchCtrl_IsCancelButtonVisible(wxSearchCtrl* self)
    {
        return self->IsCancelButtonVisible();
    }

    EXPORT void wxSearchCtrl_SetDescriptiveText(wxSearchCtrl* self, wxString* text)
    {
        self->SetDescriptiveText(*text);
    }

    EXPORT wxString* wxSearchCtrl_GetDescriptiveText(wxSearchCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetDescriptiveText();
        return result;
    }
}
