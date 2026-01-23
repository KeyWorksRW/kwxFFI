// wx_dirpickerctrl.cpp - wxDirPickerCtrl wrappers
#include "wrapper.h"

extern "C"
{
    EXPORT wxDirPickerCtrl* wxDirPickerCtrl_Create(wxWindow* parent, int id, int x, int y, int w,
                                                   int h, wxString* path, wxString* message,
                                                   long style)
    {
        wxString pathStr = path ? *path : wxString(wxEmptyString);
        wxString msgStr = message ? *message : wxString(wxDirSelectorPromptStr);
        return new wxDirPickerCtrl(parent, id, pathStr, msgStr, wxPoint(x, y), wxSize(w, h), style);
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
}
