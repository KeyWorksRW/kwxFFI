#include "kwx_wrapper.h"
#include <wx/filename.h>
#include <wx/tokenzr.h>

#include <algorithm>

// wxFileName is exported as an opaque handle: the C caller never sees the class
// layout, only pointers returned by the Create* functions.

static wxString PathOrEmpty(wxString* text)
{
    return text ? *text : wxString();
}

// Copies at most capacity strings into a caller-supplied array of char pointers and
// returns the total number of values.  Each written entry is a strdup() copy owned by
// the caller.
static int FillStringArray(const wxArrayString& values, void* output, int capacity)
{
    const size_t limit =
        capacity > 0 ? std::min(values.GetCount(), static_cast<size_t>(capacity)) : 0;

    if (output)
    {
        for (size_t index = 0; index < limit; ++index)
        {
            static_cast<const char**>(output)[index] =
                strdup(values.Item(index).utf8_string().data());
        }
    }

    return static_cast<int>(values.GetCount());
}

// Mirrors wxFileName::MakeSafeRelativePath() from wx 3.3.  Some wx 3.3 builds
// do not ship that function, so kwxFFI carries the implementation.
static wxString ForbiddenNameChars(wxPathFormat format)
{
    wxString forbidden("*?");

    switch (format)
    {
        case wxPATH_MAC:
            forbidden.clear();
            break;

        case wxPATH_DOS:
            forbidden += "\\/:\"<>|";
            break;

        default:
            break;
    }

    return forbidden;
}

static bool IsReservedDosName(const wxString& name)
{
    wxString base = name.BeforeFirst('.');
    base.Trim();
    base.MakeUpper();

    if (base == "CON" || base == "PRN" || base == "AUX" || base == "NUL")
    {
        return true;
    }

    if (base.length() == 4 && (base.StartsWith("COM") || base.StartsWith("LPT")))
    {
        const wxUniChar digit = base[3];
        return (digit >= '0' && digit <= '9') || digit == wxUniChar(0x00B9) ||
               digit == wxUniChar(0x00B2) || digit == wxUniChar(0x00B3);
    }

    return false;
}

static wxString MakeSafeComponent(const wxString& name, wxPathFormat format)
{
    wxString forbidden = ForbiddenNameChars(format);
    if (format != wxPATH_VMS)
    {
        forbidden += wxFileName::GetPathSeparators(format);
    }

    wxString valid;
    valid.reserve(name.length());
    for (const wxUniChar character: name)
    {
        if (character < 32 || forbidden.Find(character) != wxNOT_FOUND)
        {
            valid += '_';
        }
        else
        {
            valid += character;
        }
    }

    if (valid == "." || valid == "..")
    {
        // These special names refer to directories and cannot be used.
        valid.assign(valid.length(), '_');
    }
    else if (format == wxPATH_DOS)
    {
        // Windows silently strips trailing spaces and dots from names.
        const size_t length = valid.length();
        while (!valid.empty() && (valid.Last() == '.' || valid.Last() == ' '))
        {
            valid.RemoveLast();
        }

        if (valid.empty())
        {
            valid.assign(length, '_');
        }
        else if (IsReservedDosName(valid))
        {
            valid.Prepend("_");
        }
    }

    if (valid.empty())
    {
        valid = "_";
    }

    return valid;
}

static wxString MakeSafeRelativePathLocal(const wxString& path, wxPathFormat format)
{
    format = wxFileName::GetFormat(format);

    // VMS paths use a different syntax for directories and file names.
    if (format == wxPATH_VMS)
    {
        return wxString();
    }

    wxString safe;
    wxStringTokenizer tokenizer(path, wxFileName::GetPathSeparators(format), wxTOKEN_STRTOK);
    while (tokenizer.HasMoreTokens())
    {
        const wxString component = tokenizer.GetNextToken();
        if (component == ".")
        {
            continue;
        }

        // A parent-directory reference may escape the target directory.
        if (component == "..")
        {
            return wxString();
        }

        if (!safe.empty())
        {
            safe += wxFileName::GetPathSeparator(format);
        }
        safe += MakeSafeComponent(component, format);
    }

    return safe;
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

    EXPORT int wxFileName_GetDirs(wxFileName* self, void* dirs, int capacity)
    {
        return FillStringArray(self->GetDirs(), dirs, capacity);
    }

    EXPORT int wxFileName_HasName(wxFileName* self)
    {
        return self->HasName();
    }

    EXPORT int wxFileName_HasExt(wxFileName* self)
    {
        return self->HasExt();
    }

    EXPORT int wxFileName_HasVolume(wxFileName* self)
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

    EXPORT int wxFileName_AppendDir(wxFileName* self, wxString* dir)
    {
        return self->AppendDir(PathOrEmpty(dir));
    }

    EXPORT void wxFileName_PrependDir(wxFileName* self, wxString* dir)
    {
        self->PrependDir(PathOrEmpty(dir));
    }

    EXPORT int wxFileName_InsertDir(wxFileName* self, size_t before, wxString* dir)
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

    EXPORT int wxFileName_Normalize(wxFileName* self, int flags, wxString* cwd, int format)
    {
        return self->Normalize(flags, PathOrEmpty(cwd), static_cast<wxPathFormat>(format));
    }

    EXPORT int wxFileName_MakeAbsolute(wxFileName* self, wxString* cwd, int format)
    {
        return self->MakeAbsolute(PathOrEmpty(cwd), static_cast<wxPathFormat>(format));
    }

    EXPORT int wxFileName_MakeRelativeTo(wxFileName* self, wxString* path_base, int format)
    {
        return self->MakeRelativeTo(PathOrEmpty(path_base), static_cast<wxPathFormat>(format));
    }

    EXPORT wxString* wxFileName_MakeSafeRelativePath(wxString* path, int format)
    {
        if (!path)
        {
            return new wxString();
        }

        return new wxString(MakeSafeRelativePathLocal(*path, static_cast<wxPathFormat>(format)));
    }

    EXPORT wxString* wxFileName_GetAbsolutePath(wxFileName* self, wxString* cwd, int format)
    {
        return new wxString(
            self->GetAbsolutePath(PathOrEmpty(cwd), static_cast<wxPathFormat>(format)));
    }

    EXPORT int wxFileName_ReplaceEnvVariable(wxFileName* self, wxString* env_name,
                                             wxString* replacement_format, int format)
    {
        const wxString replacement = replacement_format ? *replacement_format : wxString("$%s");
        return self->ReplaceEnvVariable(PathOrEmpty(env_name), replacement,
                                        static_cast<wxPathFormat>(format));
    }

    EXPORT int wxFileName_ReplaceHomeDir(wxFileName* self, int format)
    {
        return self->ReplaceHomeDir(static_cast<wxPathFormat>(format));
    }

    EXPORT int wxFileName_IsOk(wxFileName* self)
    {
        return self->IsOk();
    }

    EXPORT int wxFileName_IsDir(wxFileName* self)
    {
        return self->IsDir();
    }

    EXPORT int wxFileName_IsAbsolute(wxFileName* self, int format)
    {
        return self->IsAbsolute(static_cast<wxPathFormat>(format));
    }

    EXPORT int wxFileName_IsRelative(wxFileName* self, int format)
    {
        return self->IsRelative(static_cast<wxPathFormat>(format));
    }

    EXPORT int wxFileName_FileExists(wxFileName* self)
    {
        return self->FileExists();
    }

    EXPORT int wxFileName_DirExists(wxFileName* self)
    {
        return self->DirExists();
    }

    EXPORT int wxFileName_Exists(wxFileName* self, int flags)
    {
        return self->Exists(flags);
    }

    EXPORT int wxFileName_IsFileReadable(wxFileName* self)
    {
        return self->IsFileReadable();
    }

    EXPORT int wxFileName_IsFileWritable(wxFileName* self)
    {
        return self->IsFileWritable();
    }

    EXPORT int wxFileName_IsFileExecutable(wxFileName* self)
    {
        return self->IsFileExecutable();
    }

    EXPORT int wxFileName_IsDirReadable(wxFileName* self)
    {
        return self->IsDirReadable();
    }

    EXPORT int wxFileName_IsDirWritable(wxFileName* self)
    {
        return self->IsDirWritable();
    }

    EXPORT int wxFileName_SameAs(wxFileName* self, wxFileName* other, int format)
    {
        return self->SameAs(*other, static_cast<wxPathFormat>(format));
    }

    EXPORT int wxFileName_ShouldFollowLink(wxFileName* self)
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

    EXPORT int wxFileName_Mkdir(wxFileName* self, int perm, int flags)
    {
        return self->Mkdir(perm, flags);
    }

    EXPORT int wxFileName_Rmdir(wxFileName* self, int flags)
    {
        return self->Rmdir(flags);
    }

    EXPORT int wxFileName_SetPermissions(wxFileName* self, int permissions)
    {
        return self->SetPermissions(permissions);
    }

    EXPORT int wxFileName_Touch(wxFileName* self)
    {
        return self->Touch();
    }

    EXPORT int wxFileName_GetTimes(wxFileName* self, wxDateTime* access_time, wxDateTime* mod_time,
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

    EXPORT int wxFileName_FileExistsForPath(wxString* file)
    {
        return wxFileName::FileExists(PathOrEmpty(file));
    }

    EXPORT int wxFileName_DirExistsForPath(wxString* dir)
    {
        return wxFileName::DirExists(PathOrEmpty(dir));
    }

    EXPORT int wxFileName_ExistsForPath(wxString* path, int flags)
    {
        return wxFileName::Exists(PathOrEmpty(path), flags);
    }

    EXPORT int wxFileName_IsFileReadableForPath(wxString* file)
    {
        return wxFileName::IsFileReadable(PathOrEmpty(file));
    }

    EXPORT int wxFileName_IsFileWritableForPath(wxString* file)
    {
        return wxFileName::IsFileWritable(PathOrEmpty(file));
    }

    EXPORT int wxFileName_IsFileExecutableForPath(wxString* file)
    {
        return wxFileName::IsFileExecutable(PathOrEmpty(file));
    }

    EXPORT int wxFileName_IsDirReadableForPath(wxString* dir)
    {
        return wxFileName::IsDirReadable(PathOrEmpty(dir));
    }

    EXPORT int wxFileName_IsDirWritableForPath(wxString* dir)
    {
        return wxFileName::IsDirWritable(PathOrEmpty(dir));
    }

    EXPORT int wxFileName_MkdirForPath(wxString* dir, int perm, int flags)
    {
        return wxFileName::Mkdir(PathOrEmpty(dir), perm, flags);
    }

    EXPORT int wxFileName_RmdirForPath(wxString* dir, int flags)
    {
        return wxFileName::Rmdir(PathOrEmpty(dir), flags);
    }

    EXPORT int wxFileName_SetCwdForPath(wxString* cwd)
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

    EXPORT int wxFileName_IsCaseSensitive(int format)
    {
        return wxFileName::IsCaseSensitive(static_cast<wxPathFormat>(format));
    }

    // ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
    EXPORT void wxFileName_SplitPath(void* fullpath, void* volume, void* path, void* name,
                                     void* ext, int* hasExt, int format)
    {
        // The FFI passes the out-param as int*; wxFileName wants bool*.
        bool has_ext = false;
        wxFileName::SplitPath(*(wxString*) fullpath, (wxString*) volume, (wxString*) path,
                              (wxString*) name, (wxString*) ext, hasExt ? &has_ext : nullptr,
                              static_cast<wxPathFormat>(format));
        if (hasExt)
        {
            *hasExt = has_ext ? 1 : 0;
        }
    }

    EXPORT int wxPathList_Add(void* pObject, void* path)
    {
        return ((wxPathList*) pObject)->Add(*(wxString*) path);
    }

    EXPORT void* wxPathList_FindValidPath(void* pObject, void* filename)
    {
        wxString value = ((wxPathList*) pObject)->FindValidPath(*(wxString*) filename);
        return new wxString(value);
    }
}
