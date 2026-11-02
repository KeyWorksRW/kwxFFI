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
    EXPORT wxFileName* wxFileName_Create()
    {
        return new wxFileName();
    }

    EXPORT wxFileName* wxFileName_CreateFromPath(wxString* full_path, int format)
    {
        return new wxFileName(PathOrEmpty(full_path), static_cast<wxPathFormat>(format));
    }

    EXPORT wxFileName* wxFileName_CreateWithName(wxString* path, wxString* name, int format)
    {
        return new wxFileName(PathOrEmpty(path), PathOrEmpty(name),
                              static_cast<wxPathFormat>(format));
    }

    EXPORT wxFileName* wxFileName_CreateWithExt(wxString* path, wxString* name, wxString* ext,
                                                int format)
    {
        return new wxFileName(PathOrEmpty(path), PathOrEmpty(name), PathOrEmpty(ext),
                              static_cast<wxPathFormat>(format));
    }

    EXPORT wxFileName* wxFileName_CreateFull(wxString* volume, wxString* path, wxString* name,
                                             wxString* ext, int format)
    {
        return new wxFileName(PathOrEmpty(volume), PathOrEmpty(path), PathOrEmpty(name),
                              PathOrEmpty(ext), static_cast<wxPathFormat>(format));
    }

    EXPORT void wxFileName_Delete(wxFileName* self)
    {
        delete self;
    }

    EXPORT wxFileName* wxFileName_DirName(wxString* dir, int format)
    {
        return new wxFileName(
            wxFileName::DirName(PathOrEmpty(dir), static_cast<wxPathFormat>(format)));
    }

    EXPORT wxFileName* wxFileName_FileName(wxString* file, int format)
    {
        return new wxFileName(
            wxFileName::FileName(PathOrEmpty(file), static_cast<wxPathFormat>(format)));
    }

    EXPORT wxFileName* wxFileName_URLToFileName(wxString* url)
    {
        return new wxFileName(wxFileName::URLToFileName(PathOrEmpty(url)));
    }

    EXPORT wxString* wxFileName_GetFullPath(wxFileName* self, int format)
    {
        return new wxString(self->GetFullPath(static_cast<wxPathFormat>(format)));
    }

    EXPORT wxString* wxFileName_GetPath(wxFileName* self, int flags, int format)
    {
        return new wxString(self->GetPath(flags, static_cast<wxPathFormat>(format)));
    }

    EXPORT wxString* wxFileName_GetPathWithSep(wxFileName* self, int format)
    {
        return new wxString(self->GetPathWithSep(static_cast<wxPathFormat>(format)));
    }

    EXPORT wxString* wxFileName_GetFullName(wxFileName* self)
    {
        return new wxString(self->GetFullName());
    }

    EXPORT wxString* wxFileName_GetName(wxFileName* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT wxString* wxFileName_GetExt(wxFileName* self)
    {
        return new wxString(self->GetExt());
    }

    EXPORT wxString* wxFileName_GetVolume(wxFileName* self)
    {
        return new wxString(self->GetVolume());
    }

    EXPORT size_t wxFileName_GetDirCount(wxFileName* self)
    {
        return self->GetDirCount();
    }

    EXPORT int wxFileName_GetDirs(wxFileName* self, void* dirs)
    {
        return FillStringArray(self->GetDirs(), dirs);
    }

    EXPORT bool wxFileName_HasName(wxFileName* self)
    {
        return self->HasName();
    }

    EXPORT bool wxFileName_HasExt(wxFileName* self)
    {
        return self->HasExt();
    }

    EXPORT bool wxFileName_HasVolume(wxFileName* self)
    {
        return self->HasVolume();
    }

    EXPORT void wxFileName_SetPath(wxFileName* self, wxString* path, int format)
    {
        self->SetPath(PathOrEmpty(path), static_cast<wxPathFormat>(format));
    }

    EXPORT void wxFileName_SetName(wxFileName* self, wxString* name)
    {
        self->SetName(PathOrEmpty(name));
    }

    EXPORT void wxFileName_SetFullName(wxFileName* self, wxString* full_name)
    {
        self->SetFullName(PathOrEmpty(full_name));
    }

    EXPORT void wxFileName_SetExt(wxFileName* self, wxString* ext)
    {
        self->SetExt(PathOrEmpty(ext));
    }

    EXPORT void wxFileName_SetEmptyExt(wxFileName* self)
    {
        self->SetEmptyExt();
    }

    EXPORT void wxFileName_ClearExt(wxFileName* self)
    {
        self->ClearExt();
    }

    EXPORT void wxFileName_SetVolume(wxFileName* self, wxString* volume)
    {
        self->SetVolume(PathOrEmpty(volume));
    }

    EXPORT void wxFileName_Assign(wxFileName* self, wxString* full_path, int format)
    {
        self->Assign(PathOrEmpty(full_path), static_cast<wxPathFormat>(format));
    }

    EXPORT void wxFileName_AssignDir(wxFileName* self, wxString* dir, int format)
    {
        self->AssignDir(PathOrEmpty(dir), static_cast<wxPathFormat>(format));
    }

    EXPORT void wxFileName_AssignCwd(wxFileName* self, wxString* volume)
    {
        self->AssignCwd(PathOrEmpty(volume));
    }

    EXPORT void wxFileName_AssignHomeDir(wxFileName* self)
    {
        self->AssignHomeDir();
    }

    EXPORT void wxFileName_Clear(wxFileName* self)
    {
        self->Clear();
    }

    EXPORT bool wxFileName_AppendDir(wxFileName* self, wxString* dir)
    {
        return self->AppendDir(PathOrEmpty(dir));
    }

    EXPORT void wxFileName_PrependDir(wxFileName* self, wxString* dir)
    {
        self->PrependDir(PathOrEmpty(dir));
    }

    EXPORT bool wxFileName_InsertDir(wxFileName* self, size_t before, wxString* dir)
    {
        return self->InsertDir(before, PathOrEmpty(dir));
    }

    EXPORT void wxFileName_RemoveDir(wxFileName* self, size_t position)
    {
        self->RemoveDir(position);
    }

    EXPORT void wxFileName_RemoveLastDir(wxFileName* self)
    {
        self->RemoveLastDir();
    }

    EXPORT bool wxFileName_Normalize(wxFileName* self, int flags, wxString* cwd, int format)
    {
        return self->Normalize(flags, PathOrEmpty(cwd), static_cast<wxPathFormat>(format));
    }

    EXPORT bool wxFileName_MakeAbsolute(wxFileName* self, wxString* cwd, int format)
    {
        return self->MakeAbsolute(PathOrEmpty(cwd), static_cast<wxPathFormat>(format));
    }

    EXPORT bool wxFileName_MakeRelativeTo(wxFileName* self, wxString* path_base, int format)
    {
        return self->MakeRelativeTo(PathOrEmpty(path_base), static_cast<wxPathFormat>(format));
    }

    EXPORT wxString* wxFileName_GetAbsolutePath(wxFileName* self, wxString* cwd, int format)
    {
        return new wxString(
            self->GetAbsolutePath(PathOrEmpty(cwd), static_cast<wxPathFormat>(format)));
    }

    EXPORT bool wxFileName_ReplaceEnvVariable(wxFileName* self, wxString* env_name,
                                              wxString* replacement_format, int format)
    {
        const wxString replacement = replacement_format ? *replacement_format : wxString("$%s");
        return self->ReplaceEnvVariable(PathOrEmpty(env_name), replacement,
                                        static_cast<wxPathFormat>(format));
    }

    EXPORT bool wxFileName_ReplaceHomeDir(wxFileName* self, int format)
    {
        return self->ReplaceHomeDir(static_cast<wxPathFormat>(format));
    }

    EXPORT bool wxFileName_IsOk(wxFileName* self)
    {
        return self->IsOk();
    }

    EXPORT bool wxFileName_IsDir(wxFileName* self)
    {
        return self->IsDir();
    }

    EXPORT bool wxFileName_IsAbsolute(wxFileName* self, int format)
    {
        return self->IsAbsolute(static_cast<wxPathFormat>(format));
    }

    EXPORT bool wxFileName_IsRelative(wxFileName* self, int format)
    {
        return self->IsRelative(static_cast<wxPathFormat>(format));
    }

    EXPORT bool wxFileName_FileExists(wxFileName* self)
    {
        return self->FileExists();
    }

    EXPORT bool wxFileName_DirExists(wxFileName* self)
    {
        return self->DirExists();
    }

    EXPORT bool wxFileName_Exists(wxFileName* self, int flags)
    {
        return self->Exists(flags);
    }

    EXPORT bool wxFileName_IsFileReadable(wxFileName* self)
    {
        return self->IsFileReadable();
    }

    EXPORT bool wxFileName_IsFileWritable(wxFileName* self)
    {
        return self->IsFileWritable();
    }

    EXPORT bool wxFileName_IsFileExecutable(wxFileName* self)
    {
        return self->IsFileExecutable();
    }

    EXPORT bool wxFileName_IsDirReadable(wxFileName* self)
    {
        return self->IsDirReadable();
    }

    EXPORT bool wxFileName_IsDirWritable(wxFileName* self)
    {
        return self->IsDirWritable();
    }

    EXPORT bool wxFileName_SameAs(wxFileName* self, wxFileName* other, int format)
    {
        return self->SameAs(*other, static_cast<wxPathFormat>(format));
    }

    EXPORT bool wxFileName_ShouldFollowLink(wxFileName* self)
    {
        return self->ShouldFollowLink();
    }

    EXPORT void wxFileName_DontFollowLink(wxFileName* self)
    {
        self->DontFollowLink();
    }

    EXPORT wxFileName* wxFileName_ResolveLink(wxFileName* self)
    {
        return new wxFileName(self->ResolveLink());
    }

    EXPORT bool wxFileName_Mkdir(wxFileName* self, int perm, int flags)
    {
        return self->Mkdir(perm, flags);
    }

    EXPORT bool wxFileName_Rmdir(wxFileName* self, int flags)
    {
        return self->Rmdir(flags);
    }

    EXPORT bool wxFileName_SetPermissions(wxFileName* self, int permissions)
    {
        return self->SetPermissions(permissions);
    }

    EXPORT bool wxFileName_Touch(wxFileName* self)
    {
        return self->Touch();
    }

    EXPORT bool wxFileName_GetTimes(wxFileName* self, wxDateTime* access_time, wxDateTime* mod_time,
                                    wxDateTime* create_time)
    {
        return self->GetTimes(access_time, mod_time, create_time);
    }

    EXPORT wxDateTime* wxFileName_GetModificationTime(wxFileName* self)
    {
        return new wxDateTime(self->GetModificationTime());
    }

    EXPORT double wxFileName_GetSize(wxFileName* self)
    {
        const wxULongLong size = self->GetSize();
        if (size == wxInvalidSize)
        {
            return -1.0;
        }

        return static_cast<double>(size.GetValue());
    }

    EXPORT wxString* wxFileName_GetHumanReadableSize(wxFileName* self, wxString* fail_message,
                                                     int precision, int convention)
    {
        const wxString fail_text = fail_message ? *fail_message : wxString("Not available");
        return new wxString(self->GetHumanReadableSize(fail_text, precision,
                                                       static_cast<wxSizeConvention>(convention)));
    }

    EXPORT wxString* wxFileName_FileNameToURL(wxFileName* self)
    {
        return new wxString(wxFileName::FileNameToURL(*self));
    }

    EXPORT bool wxFileName_FileExistsForPath(wxString* file)
    {
        return wxFileName::FileExists(PathOrEmpty(file));
    }

    EXPORT bool wxFileName_DirExistsForPath(wxString* dir)
    {
        return wxFileName::DirExists(PathOrEmpty(dir));
    }

    EXPORT bool wxFileName_ExistsForPath(wxString* path, int flags)
    {
        return wxFileName::Exists(PathOrEmpty(path), flags);
    }

    EXPORT bool wxFileName_IsFileReadableForPath(wxString* file)
    {
        return wxFileName::IsFileReadable(PathOrEmpty(file));
    }

    EXPORT bool wxFileName_IsFileWritableForPath(wxString* file)
    {
        return wxFileName::IsFileWritable(PathOrEmpty(file));
    }

    EXPORT bool wxFileName_IsFileExecutableForPath(wxString* file)
    {
        return wxFileName::IsFileExecutable(PathOrEmpty(file));
    }

    EXPORT bool wxFileName_IsDirReadableForPath(wxString* dir)
    {
        return wxFileName::IsDirReadable(PathOrEmpty(dir));
    }

    EXPORT bool wxFileName_IsDirWritableForPath(wxString* dir)
    {
        return wxFileName::IsDirWritable(PathOrEmpty(dir));
    }

    EXPORT bool wxFileName_MkdirForPath(wxString* dir, int perm, int flags)
    {
        return wxFileName::Mkdir(PathOrEmpty(dir), perm, flags);
    }

    EXPORT bool wxFileName_RmdirForPath(wxString* dir, int flags)
    {
        return wxFileName::Rmdir(PathOrEmpty(dir), flags);
    }

    EXPORT bool wxFileName_SetCwdForPath(wxString* cwd)
    {
        return wxFileName::SetCwd(PathOrEmpty(cwd));
    }

    EXPORT wxString* wxFileName_GetCwd(wxString* volume)
    {
        return new wxString(wxFileName::GetCwd(PathOrEmpty(volume)));
    }

    EXPORT wxString* wxFileName_GetHomeDir()
    {
        return new wxString(wxFileName::GetHomeDir());
    }

    EXPORT wxString* wxFileName_GetTempDir()
    {
        return new wxString(wxFileName::GetTempDir());
    }

    EXPORT wxString* wxFileName_GetTempFileName(wxString* prefix)
    {
        return new wxString(wxFileName::CreateTempFileName(PathOrEmpty(prefix)));
    }

    EXPORT wxString* wxFileName_GetForbiddenChars(int format)
    {
        return new wxString(wxFileName::GetForbiddenChars(static_cast<wxPathFormat>(format)));
    }

    EXPORT wxString* wxFileName_StripExtension(wxString* full_name)
    {
        return new wxString(wxFileName::StripExtension(PathOrEmpty(full_name)));
    }

    EXPORT bool wxFileName_IsCaseSensitive(int format)
    {
        return wxFileName::IsCaseSensitive(static_cast<wxPathFormat>(format));
    }
}
