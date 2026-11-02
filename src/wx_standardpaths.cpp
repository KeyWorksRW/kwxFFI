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
    EXPORT wxStandardPaths* wxStandardPaths_Get()
    {
        return &wxStandardPaths::Get();
    }

    EXPORT wxString* wxStandardPaths_GetConfigDir(wxStandardPaths* self)
    {
        return new wxString(self->GetConfigDir());
    }

    EXPORT wxString* wxStandardPaths_GetUserConfigDir(wxStandardPaths* self)
    {
        return new wxString(self->GetUserConfigDir());
    }

    EXPORT wxString* wxStandardPaths_GetDataDir(wxStandardPaths* self)
    {
        return new wxString(self->GetDataDir());
    }

    EXPORT wxString* wxStandardPaths_GetLocalDataDir(wxStandardPaths* self)
    {
        return new wxString(self->GetLocalDataDir());
    }

    EXPORT wxString* wxStandardPaths_GetUserDataDir(wxStandardPaths* self)
    {
        return new wxString(self->GetUserDataDir());
    }

    EXPORT wxString* wxStandardPaths_GetUserLocalDataDir(wxStandardPaths* self)
    {
        return new wxString(self->GetUserLocalDataDir());
    }

    EXPORT wxString* wxStandardPaths_GetDocumentsDir(wxStandardPaths* self)
    {
        return new wxString(self->GetDocumentsDir());
    }

    EXPORT wxString* wxStandardPaths_GetAppDocumentsDir(wxStandardPaths* self)
    {
        return new wxString(self->GetAppDocumentsDir());
    }

    EXPORT wxString* wxStandardPaths_GetExecutablePath(wxStandardPaths* self)
    {
        return new wxString(self->GetExecutablePath());
    }

    EXPORT wxString* wxStandardPaths_GetPluginsDir(wxStandardPaths* self)
    {
        return new wxString(self->GetPluginsDir());
    }

    EXPORT wxString* wxStandardPaths_GetResourcesDir(wxStandardPaths* self)
    {
        return new wxString(self->GetResourcesDir());
    }

    EXPORT wxString* wxStandardPaths_GetSharedLibrariesDir(wxStandardPaths* self)
    {
        return new wxString(self->GetSharedLibrariesDir());
    }

    EXPORT wxString* wxStandardPaths_GetTempDir(wxStandardPaths* self)
    {
        return new wxString(self->GetTempDir());
    }

    EXPORT wxString* wxStandardPaths_GetUserDir(wxStandardPaths* self, int user_dir)
    {
        return new wxString(self->GetUserDir(static_cast<wxStandardPathsBase::Dir>(user_dir)));
    }

    EXPORT wxString* wxStandardPaths_GetLocalizedResourcesDir(wxStandardPaths* self, wxString* lang,
                                                              int category)
    {
        return new wxString(self->GetLocalizedResourcesDir(
            PathOrEmpty(lang), static_cast<wxStandardPathsBase::ResourceCat>(category)));
    }

    EXPORT wxString* wxStandardPaths_AppendAppInfo(wxStandardPaths* self, wxString* dir)
    {
        return new wxString(self->AppendAppInfo(PathOrEmpty(dir)));
    }

    EXPORT wxString* wxStandardPaths_MakeConfigFileName(wxStandardPaths* self, wxString* base_name,
                                                        int convention)
    {
        return new wxString(self->MakeConfigFileName(
            PathOrEmpty(base_name), static_cast<wxStandardPathsBase::ConfigFileConv>(convention)));
    }

    EXPORT int wxStandardPaths_GetFileLayout(wxStandardPaths* self)
    {
        return std::to_underlying(self->GetFileLayout());
    }

    EXPORT void wxStandardPaths_SetFileLayout(wxStandardPaths* self, int layout)
    {
        self->SetFileLayout(static_cast<wxStandardPathsBase::FileLayout>(layout));
    }

    EXPORT void wxStandardPaths_UseAppInfo(wxStandardPaths* self, int info)
    {
        self->UseAppInfo(info);
    }

    EXPORT wxString* wxStandardPaths_GetInstallPrefix(wxStandardPaths* self)
    {
#if defined(wxHAS_STDPATHS_INSTALL_PREFIX)
        return new wxString(self->GetInstallPrefix());
#else
        // This platform has no install prefix.
        wxUnusedVar(self);
        return new wxString();
#endif
    }

    EXPORT void wxStandardPaths_SetInstallPrefix(wxStandardPaths* self, wxString* prefix)
    {
#if defined(wxHAS_STDPATHS_INSTALL_PREFIX)
        self->SetInstallPrefix(PathOrEmpty(prefix));
#else
        wxUnusedVar(self);
        wxUnusedVar(prefix);
#endif
    }

    EXPORT void wxStandardPaths_IgnoreAppSubDir(wxStandardPaths* self, wxString* subdir_pattern)
    {
#if defined(__WINDOWS__)
        self->IgnoreAppSubDir(PathOrEmpty(subdir_pattern));
#else
        wxUnusedVar(self);
        wxUnusedVar(subdir_pattern);
#endif
    }

    EXPORT void wxStandardPaths_IgnoreAppBuildSubDirs(wxStandardPaths* self)
    {
#if defined(__WINDOWS__)
        self->IgnoreAppBuildSubDirs();
#else
        wxUnusedVar(self);
#endif
    }

    EXPORT void wxStandardPaths_DontIgnoreAppSubDir(wxStandardPaths* self)
    {
#if defined(__WINDOWS__)
        self->DontIgnoreAppSubDir();
#else
        wxUnusedVar(self);
#endif
    }

    EXPORT wxString* wxStandardPaths_MSWGetShellDir(int csidl)
    {
#if defined(__WINDOWS__)
        return new wxString(wxStandardPaths::MSWGetShellDir(csidl));
#else
        wxUnusedVar(csidl);
        return new wxString();
#endif
    }
}
