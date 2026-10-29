#include "kwx_wrapper.h"

#include <wx/fs_mem.h>

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

    EXPORT void wxMemoryFSHandler_AddFile(wxString* filename, wxString* textdata)
    {
        wxMemoryFSHandler::AddFile(*filename, *textdata);
    }

    EXPORT void wxMemoryFSHandler_AddFileBinary(wxString* filename, void* binarydata, size_t size)
    {
        wxMemoryFSHandler::AddFile(*filename, binarydata, size);
    }

    EXPORT void wxMemoryFSHandler_AddFileWithMimeType(wxString* filename, wxString* textdata,
                                                      wxString* mimetype)
    {
        wxMemoryFSHandler::AddFileWithMimeType(*filename, *textdata, *mimetype);
    }

    EXPORT void wxMemoryFSHandler_AddFileWithMimeTypeBinary(wxString* filename, void* binarydata,
                                                            size_t size, wxString* mimetype)
    {
        wxMemoryFSHandler::AddFileWithMimeType(*filename, binarydata, size, *mimetype);
    }

    EXPORT void wxMemoryFSHandler_AddFileImage(wxString* filename, wxImage* image, int type)
    {
#if wxUSE_IMAGE
        wxMemoryFSHandler::AddFile(*filename, *image, static_cast<wxBitmapType>(type));
#else
        wxUnusedVar(filename);
        wxUnusedVar(image);
        wxUnusedVar(type);
#endif
    }

    EXPORT void wxMemoryFSHandler_AddFileBitmap(wxString* filename, wxBitmap* bitmap, int type)
    {
#if wxUSE_IMAGE
        wxMemoryFSHandler::AddFile(*filename, *bitmap, static_cast<wxBitmapType>(type));
#else
        wxUnusedVar(filename);
        wxUnusedVar(bitmap);
        wxUnusedVar(type);
#endif
    }

    EXPORT void wxMemoryFSHandler_RemoveFile(wxString* filename)
    {
        wxMemoryFSHandler::RemoveFile(*filename);
    }
}
