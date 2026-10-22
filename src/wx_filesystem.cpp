#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void wxFSFile_Delete(wxFSFile* self)
    {
        delete self;
    }

    EXPORT wxInputStream* wxFSFile_GetStream(wxFSFile* self)
    {
        return self->GetStream();
    }

    EXPORT wxInputStream* wxFSFile_DetachStream(wxFSFile* self)
    {
        return self->DetachStream();
    }

    EXPORT wxString* wxFSFile_GetLocation(wxFSFile* self)
    {
        return new wxString(self->GetLocation());
    }

    EXPORT wxString* wxFSFile_GetMimeType(wxFSFile* self)
    {
        return new wxString(self->GetMimeType());
    }

    EXPORT wxString* wxFSFile_GetAnchor(wxFSFile* self)
    {
        return new wxString(self->GetAnchor());
    }

    EXPORT wxDateTime* wxFSFile_GetModificationTime(wxFSFile* self)
    {
        return new wxDateTime(self->GetModificationTime());
    }

    EXPORT wxFileSystem* wxFileSystem_Create()
    {
        return new wxFileSystem();
    }

    EXPORT void wxFileSystem_Delete(wxFileSystem* self)
    {
        delete self;
    }

    EXPORT void wxFileSystem_ChangePathTo(wxFileSystem* self, wxString* location, bool is_dir)
    {
        self->ChangePathTo(*location, is_dir);
    }

    EXPORT wxString* wxFileSystem_GetPath(wxFileSystem* self)
    {
        return new wxString(self->GetPath());
    }

    EXPORT wxFSFile* wxFileSystem_OpenFile(wxFileSystem* self, wxString* location, int flags)
    {
        return self->OpenFile(*location, flags);
    }

    EXPORT wxString* wxFileSystem_FindFirst(wxFileSystem* self, wxString* spec, int flags)
    {
        return new wxString(self->FindFirst(*spec, flags));
    }

    EXPORT wxString* wxFileSystem_FindNext(wxFileSystem* self)
    {
        return new wxString(self->FindNext());
    }

    EXPORT wxString* wxFileSystem_FileNameToURL([[maybe_unused]] wxFileSystem* self,
                                                wxString* file_name)
    {
        return new wxString(wxFileSystem::FileNameToURL(wxFileName(*file_name)));
    }

    EXPORT wxString* wxFileSystem_URLToFileName([[maybe_unused]] wxFileSystem* self, wxString* url)
    {
        return new wxString(wxFileSystem::URLToFileName(*url).GetFullPath());
    }
}
