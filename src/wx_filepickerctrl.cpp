// wx_filepickerctrl.cpp - wxFilePickerCtrl wrappers
#include "wrapper.h"

extern "C"
{
    EXPORT wxFilePickerCtrl* wxFilePickerCtrl_Create(wxWindow* parent, int id, int x, int y, int w,
                                                     int h, wxString* path, wxString* message,
                                                     wxString* wildcard, long style)
    {
        wxString pathStr = path ? *path : wxString(wxEmptyString);
        wxString msgStr = message ? *message : wxString(wxFileSelectorPromptStr);
        wxString wcStr = wildcard ? *wildcard : wxString(wxFileSelectorDefaultWildcardStr);
        return new wxFilePickerCtrl(parent, id, pathStr, msgStr, wcStr, wxPoint(x, y), wxSize(w, h),
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
}
