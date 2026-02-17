// wx_filepickerctrl.cpp - wxFilePickerCtrl wrappers
#include "wrapper.h"

// wxFilePickerCtrl inherits from wxControl (via wxPickerBase).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT wxFilePickerCtrl* wxFilePickerCtrl_Create(wxWindow* parent, int id, int x, int y, int width,
                                                     int height, wxString* path, wxString* message,
                                                     wxString* wildcard, long style)
    {
        wxString pathStr = path ? *path : wxString(wxEmptyString);
        wxString msgStr = message ? *message : wxString(wxFileSelectorPromptStr);
        wxString wcStr = wildcard ? *wildcard : wxString(wxFileSelectorDefaultWildcardStr);
        return new wxFilePickerCtrl(parent, id, pathStr, msgStr, wcStr, wxPoint(x, y), wxSize(width, height),
                                    style);
    }

    EXPORT wxString* wxFilePickerCtrl_GetPath(wxFilePickerCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetPath();
        return result;
    }

    EXPORT void wxFilePickerCtrl_SetPath(wxFilePickerCtrl* self, wxString* path)
    {
        if (path)
            self->SetPath(*path);
    }

    EXPORT void wxFilePickerCtrl_SetInitialDirectory(wxFilePickerCtrl* self, wxString* dir)
    {
        if (dir)
            self->SetInitialDirectory(*dir);
    }

    EXPORT void wxFilePickerCtrl_SetFileName(wxFilePickerCtrl* self, wxString* filename)
    {
        if (filename)
            self->SetFileName(wxFileName(*filename));
    }

    EXPORT wxString* wxFilePickerCtrl_GetFileName(wxFilePickerCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetFileName().GetFullPath();
        return result;
    }
}
