#include "kwx_wrapper.h"

// wxFileName is exported as an opaque handle: the C caller never sees the class
// layout, only pointers returned by the Create* functions.

static wxString PathOrEmpty(wxString* text)
{
    return text ? *text : wxString();
}

// Copies an array of strings into a caller-supplied array of char pointers.
// Each element is a strdup() copy owned by the caller.
static int FillStringArray(const wxArrayString& values, void* output)
{
    if (!output)
    {
        return 0;
    }

    for (size_t index = 0; index < values.GetCount(); ++index)
    {
        static_cast<const char**>(output)[index] = strdup(values.Item(index).utf8_string().data());
    }

    return static_cast<int>(values.GetCount());
}

extern "C"
{
    wxFileName* wxFileName_Create()
    {
        return new wxFileName();
    }

    wxFileName* wxFileName_CreateFromPath(wxString* full_path, int format)
    {
        return new wxFileName(PathOrEmpty(full_path), static_cast<wxPathFormat>(format));
    }

    wxFileName* wxFileName_CreateWithName(wxString* path, wxString* name, int format)
    {
        return new wxFileName(PathOrEmpty(path), PathOrEmpty(name),
                              static_cast<wxPathFormat>(format));
    }

    wxFileName* wxFileName_CreateWithExt(wxString* path, wxString* name, wxString* ext, int format)
    {
        return new wxFileName(PathOrEmpty(path), PathOrEmpty(name), PathOrEmpty(ext),
                              static_cast<wxPathFormat>(format));
    }

    wxFileName* wxFileName_CreateFull(wxString* volume, wxString* path, wxString* name,
                                      wxString* ext, int format)
    {
        return new wxFileName(PathOrEmpty(volume), PathOrEmpty(path), PathOrEmpty(name),
                              PathOrEmpty(ext), static_cast<wxPathFormat>(format));
    }

    void wxFileName_Delete(wxFileName* self)
    {
        delete self;
    }

    wxFileName* wxFileName_DirName(wxString* dir, int format)
    {
        return new wxFileName(
            wxFileName::DirName(PathOrEmpty(dir), static_cast<wxPathFormat>(format)));
    }

    wxFileName* wxFileName_FileName(wxString* file, int format)
    {
        return new wxFileName(
            wxFileName::FileName(PathOrEmpty(file), static_cast<wxPathFormat>(format)));
    }

    wxFileName* wxFileName_URLToFileName(wxString* url)
    {
        return new wxFileName(wxFileName::URLToFileName(PathOrEmpty(url)));
    }

    wxString* wxFileName_GetFullPath(wxFileName* self, int format)
    {
        return new wxString(self->GetFullPath(static_cast<wxPathFormat>(format)));
    }

    wxString* wxFileName_GetPath(wxFileName* self, int flags, int format)
    {
        return new wxString(self->GetPath(flags, static_cast<wxPathFormat>(format)));
    }

    wxString* wxFileName_GetPathWithSep(wxFileName* self, int format)
    {
        return new wxString(self->GetPathWithSep(static_cast<wxPathFormat>(format)));
    }

    wxString* wxFileName_GetFullName(wxFileName* self)
    {
        return new wxString(self->GetFullName());
    }

    wxString* wxFileName_GetName(wxFileName* self)
    {
        return new wxString(self->GetName());
    }

    wxString* wxFileName_GetExt(wxFileName* self)
    {
        return new wxString(self->GetExt());
    }

    wxString* wxFileName_GetVolume(wxFileName* self)
    {
        return new wxString(self->GetVolume());
    }

    size_t wxFileName_GetDirCount(wxFileName* self)
    {
        return self->GetDirCount();
    }

    int wxFileName_GetDirs(wxFileName* self, void* dirs)
    {
        return FillStringArray(self->GetDirs(), dirs);
    }

    bool wxFileName_HasName(wxFileName* self)
    {
        return self->HasName();
    }

    bool wxFileName_HasExt(wxFileName* self)
    {
        return self->HasExt();
    }

    bool wxFileName_HasVolume(wxFileName* self)
    {
        return self->HasVolume();
    }

    void wxFileName_SetPath(wxFileName* self, wxString* path, int format)
    {
        self->SetPath(PathOrEmpty(path), static_cast<wxPathFormat>(format));
    }

    void wxFileName_SetName(wxFileName* self, wxString* name)
    {
        self->SetName(PathOrEmpty(name));
    }

    void wxFileName_SetFullName(wxFileName* self, wxString* full_name)
    {
        self->SetFullName(PathOrEmpty(full_name));
    }

    void wxFileName_SetExt(wxFileName* self, wxString* ext)
    {
        self->SetExt(PathOrEmpty(ext));
    }

    void wxFileName_SetEmptyExt(wxFileName* self)
    {
        self->SetEmptyExt();
    }

    void wxFileName_ClearExt(wxFileName* self)
    {
        self->ClearExt();
    }

    void wxFileName_SetVolume(wxFileName* self, wxString* volume)
    {
        self->SetVolume(PathOrEmpty(volume));
    }

    void wxFileName_Assign(wxFileName* self, wxString* full_path, int format)
    {
        self->Assign(PathOrEmpty(full_path), static_cast<wxPathFormat>(format));
    }

    void wxFileName_AssignDir(wxFileName* self, wxString* dir, int format)
    {
        self->AssignDir(PathOrEmpty(dir), static_cast<wxPathFormat>(format));
    }

    void wxFileName_AssignCwd(wxFileName* self, wxString* volume)
    {
        self->AssignCwd(PathOrEmpty(volume));
    }

    void wxFileName_AssignHomeDir(wxFileName* self)
    {
        self->AssignHomeDir();
    }

    void wxFileName_Clear(wxFileName* self)
    {
        self->Clear();
    }

    bool wxFileName_AppendDir(wxFileName* self, wxString* dir)
    {
        return self->AppendDir(PathOrEmpty(dir));
    }

    void wxFileName_PrependDir(wxFileName* self, wxString* dir)
    {
        self->PrependDir(PathOrEmpty(dir));
    }

    bool wxFileName_InsertDir(wxFileName* self, size_t before, wxString* dir)
    {
        return self->InsertDir(before, PathOrEmpty(dir));
    }

    void wxFileName_RemoveDir(wxFileName* self, size_t position)
    {
        self->RemoveDir(position);
    }

    void wxFileName_RemoveLastDir(wxFileName* self)
    {
        self->RemoveLastDir();
    }

    bool wxFileName_Normalize(wxFileName* self, int flags, wxString* cwd, int format)
    {
        return self->Normalize(flags, PathOrEmpty(cwd), static_cast<wxPathFormat>(format));
    }

    bool wxFileName_MakeAbsolute(wxFileName* self, wxString* cwd, int format)
    {
        return self->MakeAbsolute(PathOrEmpty(cwd), static_cast<wxPathFormat>(format));
    }

    bool wxFileName_MakeRelativeTo(wxFileName* self, wxString* path_base, int format)
    {
        return self->MakeRelativeTo(PathOrEmpty(path_base), static_cast<wxPathFormat>(format));
    }

    wxString* wxFileName_GetAbsolutePath(wxFileName* self, wxString* cwd, int format)
    {
        return new wxString(
            self->GetAbsolutePath(PathOrEmpty(cwd), static_cast<wxPathFormat>(format)));
    }

    bool wxFileName_ReplaceEnvVariable(wxFileName* self, wxString* env_name,
                                       wxString* replacement_format, int format)
    {
        const wxString replacement = replacement_format ? *replacement_format : wxString("$%s");
        return self->ReplaceEnvVariable(PathOrEmpty(env_name), replacement,
                                        static_cast<wxPathFormat>(format));
    }

    bool wxFileName_ReplaceHomeDir(wxFileName* self, int format)
    {
        return self->ReplaceHomeDir(static_cast<wxPathFormat>(format));
    }

    bool wxFileName_IsOk(wxFileName* self)
    {
        return self->IsOk();
    }

    bool wxFileName_IsDir(wxFileName* self)
    {
        return self->IsDir();
    }

    bool wxFileName_IsAbsolute(wxFileName* self, int format)
    {
        return self->IsAbsolute(static_cast<wxPathFormat>(format));
    }

    bool wxFileName_IsRelative(wxFileName* self, int format)
    {
        return self->IsRelative(static_cast<wxPathFormat>(format));
    }

    bool wxFileName_FileExists(wxFileName* self)
    {
        return self->FileExists();
    }

    bool wxFileName_DirExists(wxFileName* self)
    {
        return self->DirExists();
    }

    bool wxFileName_Exists(wxFileName* self, int flags)
    {
        return self->Exists(flags);
    }

    bool wxFileName_IsFileReadable(wxFileName* self)
    {
        return self->IsFileReadable();
    }

    bool wxFileName_IsFileWritable(wxFileName* self)
    {
        return self->IsFileWritable();
    }

    bool wxFileName_IsFileExecutable(wxFileName* self)
    {
        return self->IsFileExecutable();
    }

    bool wxFileName_IsDirReadable(wxFileName* self)
    {
        return self->IsDirReadable();
    }

    bool wxFileName_IsDirWritable(wxFileName* self)
    {
        return self->IsDirWritable();
    }

    bool wxFileName_SameAs(wxFileName* self, wxFileName* other, int format)
    {
        return self->SameAs(*other, static_cast<wxPathFormat>(format));
    }

    bool wxFileName_ShouldFollowLink(wxFileName* self)
    {
        return self->ShouldFollowLink();
    }

    void wxFileName_DontFollowLink(wxFileName* self)
    {
        self->DontFollowLink();
    }

    wxFileName* wxFileName_ResolveLink(wxFileName* self)
    {
        return new wxFileName(self->ResolveLink());
    }

    bool wxFileName_Mkdir(wxFileName* self, int perm, int flags)
    {
        return self->Mkdir(perm, flags);
    }

    bool wxFileName_Rmdir(wxFileName* self, int flags)
    {
        return self->Rmdir(flags);
    }

    bool wxFileName_SetPermissions(wxFileName* self, int permissions)
    {
        return self->SetPermissions(permissions);
    }

    bool wxFileName_Touch(wxFileName* self)
    {
        return self->Touch();
    }

    bool wxFileName_GetTimes(wxFileName* self, wxDateTime* access_time, wxDateTime* mod_time,
                             wxDateTime* create_time)
    {
        return self->GetTimes(access_time, mod_time, create_time);
    }

    wxDateTime* wxFileName_GetModificationTime(wxFileName* self)
    {
        return new wxDateTime(self->GetModificationTime());
    }

    double wxFileName_GetSize(wxFileName* self)
    {
        const wxULongLong size = self->GetSize();
        if (size == wxInvalidSize)
        {
            return -1.0;
        }

        return static_cast<double>(size.GetValue());
    }

    wxString* wxFileName_GetHumanReadableSize(wxFileName* self, wxString* fail_message,
                                              int precision, int convention)
    {
        const wxString fail_text = fail_message ? *fail_message : wxString("Not available");
        return new wxString(self->GetHumanReadableSize(fail_text, precision,
                                                       static_cast<wxSizeConvention>(convention)));
    }

    wxString* wxFileName_FileNameToURL(wxFileName* self)
    {
        return new wxString(wxFileName::FileNameToURL(*self));
    }

    bool wxFileName_FileExistsForPath(wxString* file)
    {
        return wxFileName::FileExists(PathOrEmpty(file));
    }

    bool wxFileName_DirExistsForPath(wxString* dir)
    {
        return wxFileName::DirExists(PathOrEmpty(dir));
    }

    bool wxFileName_ExistsForPath(wxString* path, int flags)
    {
        return wxFileName::Exists(PathOrEmpty(path), flags);
    }

    bool wxFileName_IsFileReadableForPath(wxString* file)
    {
        return wxFileName::IsFileReadable(PathOrEmpty(file));
    }

    bool wxFileName_IsFileWritableForPath(wxString* file)
    {
        return wxFileName::IsFileWritable(PathOrEmpty(file));
    }

    bool wxFileName_IsFileExecutableForPath(wxString* file)
    {
        return wxFileName::IsFileExecutable(PathOrEmpty(file));
    }

    bool wxFileName_IsDirReadableForPath(wxString* dir)
    {
        return wxFileName::IsDirReadable(PathOrEmpty(dir));
    }

    bool wxFileName_IsDirWritableForPath(wxString* dir)
    {
        return wxFileName::IsDirWritable(PathOrEmpty(dir));
    }

    bool wxFileName_MkdirForPath(wxString* dir, int perm, int flags)
    {
        return wxFileName::Mkdir(PathOrEmpty(dir), perm, flags);
    }

    bool wxFileName_RmdirForPath(wxString* dir, int flags)
    {
        return wxFileName::Rmdir(PathOrEmpty(dir), flags);
    }

    bool wxFileName_SetCwdForPath(wxString* cwd)
    {
        return wxFileName::SetCwd(PathOrEmpty(cwd));
    }

    wxString* wxFileName_GetCwd(wxString* volume)
    {
        return new wxString(wxFileName::GetCwd(PathOrEmpty(volume)));
    }

    wxString* wxFileName_GetHomeDir()
    {
        return new wxString(wxFileName::GetHomeDir());
    }

    wxString* wxFileName_GetTempDir()
    {
        return new wxString(wxFileName::GetTempDir());
    }

    wxString* wxFileName_GetTempFileName(wxString* prefix)
    {
        return new wxString(wxFileName::CreateTempFileName(PathOrEmpty(prefix)));
    }

    wxString* wxFileName_GetForbiddenChars(int format)
    {
        return new wxString(wxFileName::GetForbiddenChars(static_cast<wxPathFormat>(format)));
    }

    wxString* wxFileName_StripExtension(wxString* full_name)
    {
        return new wxString(wxFileName::StripExtension(PathOrEmpty(full_name)));
    }

    bool wxFileName_IsCaseSensitive(int format)
    {
        return wxFileName::IsCaseSensitive(static_cast<wxPathFormat>(format));
    }
}
