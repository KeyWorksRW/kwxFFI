// wx_dirpickerctrl.cpp - wxDirPickerCtrl wrappers
#include "wrapper.h"

// wxDirPickerCtrl inherits from wxControl (via wxPickerBase).
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT wxDirPickerCtrl* wxDirPickerCtrl_Create(wxWindow* parent, int id, int x, int y, int width,
                                                   int height, wxString* path, wxString* message,
                                                   long style)
    {
        wxString pathStr = path ? *path : wxString(wxEmptyString);
        wxString msgStr = message ? *message : wxString(wxDirSelectorPromptStr);
        return new wxDirPickerCtrl(parent, id, pathStr, msgStr, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT wxString* wxDirPickerCtrl_GetPath(wxDirPickerCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetPath();
        return result;
    }

    EXPORT void wxDirPickerCtrl_SetPath(wxDirPickerCtrl* self, wxString* path)
    {
        if (path)
            self->SetPath(*path);
    }

    EXPORT void wxDirPickerCtrl_SetInitialDirectory(wxDirPickerCtrl* self, wxString* dir)
    {
        if (dir)
            self->SetInitialDirectory(*dir);
    }

    EXPORT void wxDirPickerCtrl_SetDirName(wxDirPickerCtrl* self, wxString* dirname)
    {
        if (dirname)
            self->SetDirName(wxFileName::DirName(*dirname));
    }

    EXPORT wxString* wxDirPickerCtrl_GetDirName(wxDirPickerCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetDirName().GetPath();
        return result;
    }
}
