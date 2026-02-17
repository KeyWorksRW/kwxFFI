#include "wrapper.h"
#include <wx/dirctrl.h>

// wxGenericDirCtrl inherits from wxControl.
// Additional methods available via:
//   wxWindow_*  — base window methods (see wx_window.cpp)
//   wxControl_* — label, alignment (see wx_control.cpp)

extern "C"
{
    EXPORT void* wxGenericDirCtrl_Create(wxWindow* parent, int id, wxString* dir, int x, int y,
                                         int width, int height, long style, wxString* filter,
                                         int defaultFilter)
    {
        wxString d = dir ? *dir : wxString(wxDirDialogDefaultFolderStr);
        wxString f = filter ? *filter : wxString();
        return (void*) new wxGenericDirCtrl(parent, id, d, wxPoint(x, y), wxSize(width, height),
                                            style, f, defaultFilter);
    }

    EXPORT bool wxGenericDirCtrl_CollapsePath(wxGenericDirCtrl* self, wxString* path)
    {
        return self->CollapsePath(*path);
    }

    EXPORT void wxGenericDirCtrl_CollapseTree(wxGenericDirCtrl* self)
    {
        self->CollapseTree();
    }

    EXPORT bool wxGenericDirCtrl_ExpandPath(wxGenericDirCtrl* self, wxString* path)
    {
        return self->ExpandPath(*path);
    }

    EXPORT wxString* wxGenericDirCtrl_GetDefaultPath(wxGenericDirCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetDefaultPath();
        return result;
    }

    EXPORT wxString* wxGenericDirCtrl_GetPath(wxGenericDirCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetPath();
        return result;
    }

    EXPORT void wxGenericDirCtrl_GetPaths(wxGenericDirCtrl* self, wxArrayString* paths)
    {
        self->GetPaths(*paths);
    }

    EXPORT wxString* wxGenericDirCtrl_GetFilePath(wxGenericDirCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetFilePath();
        return result;
    }

    EXPORT void wxGenericDirCtrl_GetFilePaths(wxGenericDirCtrl* self, wxArrayString* paths)
    {
        self->GetFilePaths(*paths);
    }

    EXPORT wxString* wxGenericDirCtrl_GetFilter(wxGenericDirCtrl* self)
    {
        wxString* result = new wxString();
        *result = self->GetFilter();
        return result;
    }

    EXPORT int wxGenericDirCtrl_GetFilterIndex(wxGenericDirCtrl* self)
    {
        return self->GetFilterIndex();
    }

    EXPORT void* wxGenericDirCtrl_GetFilterListCtrl(wxGenericDirCtrl* self)
    {
        return (void*) self->GetFilterListCtrl();
    }

    EXPORT void* wxGenericDirCtrl_GetTreeCtrl(wxGenericDirCtrl* self)
    {
        return (void*) self->GetTreeCtrl();
    }

    EXPORT void wxGenericDirCtrl_ReCreateTree(wxGenericDirCtrl* self)
    {
        self->ReCreateTree();
    }

    EXPORT void wxGenericDirCtrl_SetDefaultPath(wxGenericDirCtrl* self, wxString* path)
    {
        self->SetDefaultPath(*path);
    }

    EXPORT void wxGenericDirCtrl_SetFilter(wxGenericDirCtrl* self, wxString* filter)
    {
        self->SetFilter(*filter);
    }

    EXPORT void wxGenericDirCtrl_SetFilterIndex(wxGenericDirCtrl* self, int index)
    {
        self->SetFilterIndex(index);
    }

    EXPORT void wxGenericDirCtrl_SetPath(wxGenericDirCtrl* self, wxString* path)
    {
        self->SetPath(*path);
    }

    EXPORT void wxGenericDirCtrl_ShowHidden(wxGenericDirCtrl* self, bool show)
    {
        self->ShowHidden(show);
    }

    EXPORT void wxGenericDirCtrl_SelectPath(wxGenericDirCtrl* self, wxString* path, bool select)
    {
        self->SelectPath(*path, select);
    }

    EXPORT void wxGenericDirCtrl_SelectPaths(wxGenericDirCtrl* self, wxArrayString* paths)
    {
        self->SelectPaths(*paths);
    }

    EXPORT void wxGenericDirCtrl_UnselectAll(wxGenericDirCtrl* self)
    {
        self->UnselectAll();
    }

    // Events
    MAKE_EVENT_WRAPPER(EVT_DIRCTRL_SELECTIONCHANGED)
    MAKE_EVENT_WRAPPER(EVT_DIRCTRL_FILEACTIVATED)
}
