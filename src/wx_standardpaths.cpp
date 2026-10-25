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

#ifdef wxHAS_STDPATHS_INSTALL_PREFIX
    wxString* wxStandardPaths_GetInstallPrefix(wxStandardPaths* self)
    {
        return new wxString(self->GetInstallPrefix());
    }

    void wxStandardPaths_SetInstallPrefix(wxStandardPaths* self, wxString* prefix)
    {
        self->SetInstallPrefix(PathOrEmpty(prefix));
    }
#endif

#ifdef __WINDOWS__
    void wxStandardPaths_IgnoreAppSubDir(wxStandardPaths* self, wxString* subdir_pattern)
    {
        self->IgnoreAppSubDir(PathOrEmpty(subdir_pattern));
    }

    void wxStandardPaths_IgnoreAppBuildSubDirs(wxStandardPaths* self)
    {
        self->IgnoreAppBuildSubDirs();
    }

    void wxStandardPaths_DontIgnoreAppSubDir(wxStandardPaths* self)
    {
        self->DontIgnoreAppSubDir();
    }

    wxString* wxStandardPaths_MSWGetShellDir(int csidl)
    {
        return new wxString(wxStandardPaths::MSWGetShellDir(csidl));
    }
#endif
}
