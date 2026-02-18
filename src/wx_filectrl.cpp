#include "kwx_wrapper.h"

// wxFileCtrl inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT wxFileCtrl* wxFileCtrl_Create(wxWindow* parent, int id, wxString* defaultDirectory,
                                         wxString* defaultFilename, wxString* wildCard, int x,
                                         int y, int width, int height, int style)
    {
        return new wxFileCtrl(parent, id, *defaultDirectory, *defaultFilename, *wildCard, style,
                              wxPoint(x, y), wxSize(width, height));
    }

    EXPORT wxString* wxFileCtrl_GetDirectory(wxFileCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetDirectory();
        return result;
    }

    EXPORT wxString* wxFileCtrl_GetFilename(wxFileCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetFilename();
        return result;
    }

    EXPORT void wxFileCtrl_GetFilenames(wxFileCtrl* self, wxArrayString* filenames)
    {
        self->GetFilenames(*filenames);
    }

    EXPORT int wxFileCtrl_GetFilterIndex(wxFileCtrl* self)
    {
        return self->GetFilterIndex();
    }

    EXPORT wxString* wxFileCtrl_GetPath(wxFileCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetPath();
        return result;
    }

    EXPORT void wxFileCtrl_GetPaths(wxFileCtrl* self, wxArrayString* paths)
    {
        self->GetPaths(*paths);
    }

    EXPORT wxString* wxFileCtrl_GetWildcard(wxFileCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetWildcard();
        return result;
    }

    EXPORT bool wxFileCtrl_SetDirectory(wxFileCtrl* self, wxString* directory)
    {
        return self->SetDirectory(*directory);
    }

    EXPORT bool wxFileCtrl_SetFilename(wxFileCtrl* self, wxString* filename)
    {
        return self->SetFilename(*filename);
    }

    EXPORT bool wxFileCtrl_SetPath(wxFileCtrl* self, wxString* path)
    {
        return self->SetPath(*path);
    }

    EXPORT void wxFileCtrl_SetFilterIndex(wxFileCtrl* self, int filterIndex)
    {
        self->SetFilterIndex(filterIndex);
    }

    EXPORT void wxFileCtrl_SetWildcard(wxFileCtrl* self, wxString* wildCard)
    {
        self->SetWildcard(*wildCard);
    }

    EXPORT void wxFileCtrl_ShowHidden(wxFileCtrl* self, bool show)
    {
        self->ShowHidden(show);
    }
}
