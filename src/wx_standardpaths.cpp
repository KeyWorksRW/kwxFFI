#include "kwx_wrapper.h"

#include <utility>
#include <wx/stdpaths.h>

static wxString PathOrEmpty(wxString* text)
{
    return text ? *text : wxString();
}

// wxStandardPaths_Get returns the global singleton. There is intentionally no
// Delete function: the caller does not own the returned pointer.
extern "C"
{
    wxStandardPaths* wxStandardPaths_Get()
    {
        return &wxStandardPaths::Get();
    }

    wxString* wxStandardPaths_GetConfigDir(wxStandardPaths* self)
    {
        return new wxString(self->GetConfigDir());
    }

    wxString* wxStandardPaths_GetUserConfigDir(wxStandardPaths* self)
    {
        return new wxString(self->GetUserConfigDir());
    }

    wxString* wxStandardPaths_GetDataDir(wxStandardPaths* self)
    {
        return new wxString(self->GetDataDir());
    }

    wxString* wxStandardPaths_GetLocalDataDir(wxStandardPaths* self)
    {
        return new wxString(self->GetLocalDataDir());
    }

    wxString* wxStandardPaths_GetUserDataDir(wxStandardPaths* self)
    {
        return new wxString(self->GetUserDataDir());
    }

    wxString* wxStandardPaths_GetUserLocalDataDir(wxStandardPaths* self)
    {
        return new wxString(self->GetUserLocalDataDir());
    }

    wxString* wxStandardPaths_GetDocumentsDir(wxStandardPaths* self)
    {
        return new wxString(self->GetDocumentsDir());
    }

    wxString* wxStandardPaths_GetAppDocumentsDir(wxStandardPaths* self)
    {
        return new wxString(self->GetAppDocumentsDir());
    }

    wxString* wxStandardPaths_GetExecutablePath(wxStandardPaths* self)
    {
        return new wxString(self->GetExecutablePath());
    }

    wxString* wxStandardPaths_GetPluginsDir(wxStandardPaths* self)
    {
        return new wxString(self->GetPluginsDir());
    }

    wxString* wxStandardPaths_GetResourcesDir(wxStandardPaths* self)
    {
        return new wxString(self->GetResourcesDir());
    }

    wxString* wxStandardPaths_GetSharedLibrariesDir(wxStandardPaths* self)
    {
        return new wxString(self->GetSharedLibrariesDir());
    }

    wxString* wxStandardPaths_GetTempDir(wxStandardPaths* self)
    {
        return new wxString(self->GetTempDir());
    }

    wxString* wxStandardPaths_GetUserDir(wxStandardPaths* self, int user_dir)
    {
        return new wxString(self->GetUserDir(static_cast<wxStandardPathsBase::Dir>(user_dir)));
    }

    wxString* wxStandardPaths_GetLocalizedResourcesDir(wxStandardPaths* self, wxString* lang,
                                                       int category)
    {
        return new wxString(self->GetLocalizedResourcesDir(
            PathOrEmpty(lang), static_cast<wxStandardPathsBase::ResourceCat>(category)));
    }

    wxString* wxStandardPaths_AppendAppInfo(wxStandardPaths* self, wxString* dir)
    {
        return new wxString(self->AppendAppInfo(PathOrEmpty(dir)));
    }

    wxString* wxStandardPaths_MakeConfigFileName(wxStandardPaths* self, wxString* base_name,
                                                 int convention)
    {
        return new wxString(self->MakeConfigFileName(
            PathOrEmpty(base_name), static_cast<wxStandardPathsBase::ConfigFileConv>(convention)));
    }

    int wxStandardPaths_GetFileLayout(wxStandardPaths* self)
    {
        return std::to_underlying(self->GetFileLayout());
    }

    void wxStandardPaths_SetFileLayout(wxStandardPaths* self, int layout)
    {
        self->SetFileLayout(static_cast<wxStandardPathsBase::FileLayout>(layout));
    }

    void wxStandardPaths_UseAppInfo(wxStandardPaths* self, int info)
    {
        self->UseAppInfo(info);
    }

    wxString* wxStandardPaths_GetInstallPrefix(wxStandardPaths* self)
    {
#if defined(wxHAS_STDPATHS_INSTALL_PREFIX)
        return new wxString(self->GetInstallPrefix());
#else
        // This platform has no install prefix.
        wxUnusedVar(self);
        return new wxString();
#endif
    }

    void wxStandardPaths_SetInstallPrefix(wxStandardPaths* self, wxString* prefix)
    {
#if defined(wxHAS_STDPATHS_INSTALL_PREFIX)
        self->SetInstallPrefix(PathOrEmpty(prefix));
#else
        wxUnusedVar(self);
        wxUnusedVar(prefix);
#endif
    }

    void wxStandardPaths_IgnoreAppSubDir(wxStandardPaths* self, wxString* subdir_pattern)
    {
#if defined(__WINDOWS__)
        self->IgnoreAppSubDir(PathOrEmpty(subdir_pattern));
#else
        wxUnusedVar(self);
        wxUnusedVar(subdir_pattern);
#endif
    }

    void wxStandardPaths_IgnoreAppBuildSubDirs(wxStandardPaths* self)
    {
#if defined(__WINDOWS__)
        self->IgnoreAppBuildSubDirs();
#else
        wxUnusedVar(self);
#endif
    }

    void wxStandardPaths_DontIgnoreAppSubDir(wxStandardPaths* self)
    {
#if defined(__WINDOWS__)
        self->DontIgnoreAppSubDir();
#else
        wxUnusedVar(self);
#endif
    }

    wxString* wxStandardPaths_MSWGetShellDir(int csidl)
    {
#if defined(__WINDOWS__)
        return new wxString(wxStandardPaths::MSWGetShellDir(csidl));
#else
        wxUnusedVar(csidl);
        return new wxString();
#endif
    }
}
