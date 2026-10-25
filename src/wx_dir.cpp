#include "kwx_wrapper.h"

#include <bit>
#include <wx/dir.h>

// Forwards wxDirTraverser virtuals to a C callback. The callback receives an
// action code (0 = file, 1 = directory, 2 = open error) and returns a
// wxDirTraverseResult value: -1 = ignore, 0 = stop, 1 = continue.
class kwxDirTraverser : public wxDirTraverser
{
public:
    typedef int (*TraverseFunc)(void* pObject, int action, wxString* path);

    kwxDirTraverser(void* pObject, void* pFunction) : wxDirTraverser()
    {
        kwx_object = pObject;
        traverse_func = std::bit_cast<TraverseFunc>(pFunction);
    }

    wxDirTraverseResult OnFile(const wxString& filename) override { return Call(0, filename); }

    wxDirTraverseResult OnDir(const wxString& dirname) override { return Call(1, dirname); }

    wxDirTraverseResult OnOpenError(const wxString& dirname) override
    {
        if (!traverse_func)
        {
            return wxDirTraverser::OnOpenError(dirname);
        }

        return Call(2, dirname);
    }

private:
    wxDirTraverseResult Call(int action, const wxString& path)
    {
        if (!traverse_func)
        {
            return wxDIR_CONTINUE;
        }

        wxString path_copy = path;
        return static_cast<wxDirTraverseResult>(traverse_func(kwx_object, action, &path_copy));
    }

    void* kwx_object;
    TraverseFunc traverse_func;
};

static wxString PathOrEmpty(wxString* text)
{
    return text ? *text : wxString();
}

extern "C"
{
    wxDir* wxDir_Create()
    {
        return new wxDir();
    }

    wxDir* wxDir_CreateFromPath(wxString* directory)
    {
        return new wxDir(PathOrEmpty(directory));
    }

    void wxDir_Delete(wxDir* self)
    {
        delete self;
    }

    bool wxDir_Open(wxDir* self, wxString* directory)
    {
        return self->Open(PathOrEmpty(directory));
    }

    void wxDir_Close(wxDir* self)
    {
        self->Close();
    }

    bool wxDir_IsOpened(wxDir* self)
    {
        return self->IsOpened();
    }

    wxString* wxDir_GetName(wxDir* self)
    {
        return new wxString(self->GetName());
    }

    wxString* wxDir_GetNameWithSep(wxDir* self)
    {
        return new wxString(self->GetNameWithSep());
    }

    bool wxDir_GetFirst(wxDir* self, wxString* filename, wxString* spec, int flags)
    {
        wxString found;
        const bool result = self->GetFirst(&found, PathOrEmpty(spec), flags);
        if (filename)
        {
            *filename = found;
        }

        return result;
    }

    bool wxDir_GetNext(wxDir* self, wxString* filename)
    {
        wxString found;
        const bool result = self->GetNext(&found);
        if (filename)
        {
            *filename = found;
        }

        return result;
    }

    bool wxDir_HasFiles(wxDir* self, wxString* spec)
    {
        return self->HasFiles(PathOrEmpty(spec));
    }

    bool wxDir_HasSubDirs(wxDir* self, wxString* spec)
    {
        return self->HasSubDirs(PathOrEmpty(spec));
    }

    size_t wxDir_Traverse(wxDir* self, wxDirTraverser* sink, wxString* spec, int flags)
    {
        if (!sink)
        {
            return 0;
        }

        return self->Traverse(*sink, PathOrEmpty(spec), flags);
    }

    size_t wxDir_GetAllFiles(wxString* dir_name, void* files, wxString* spec, int flags)
    {
        wxArrayString found;
        wxDir::GetAllFiles(PathOrEmpty(dir_name), &found, PathOrEmpty(spec), flags);

        if (files)
        {
            for (size_t index = 0; index < found.GetCount(); ++index)
            {
                static_cast<const char**>(files)[index] =
                    strdup(found.Item(index).utf8_string().data());
            }
        }

        return found.GetCount();
    }

    wxString* wxDir_FindFirst(wxString* dir_name, wxString* spec, int flags)
    {
        return new wxString(wxDir::FindFirst(PathOrEmpty(dir_name), PathOrEmpty(spec), flags));
    }

    double wxDir_GetTotalSize(wxString* dir_name)
    {
        const wxULongLong size = wxDir::GetTotalSize(PathOrEmpty(dir_name));
        if (size == wxInvalidSize)
        {
            return -1.0;
        }

        return static_cast<double>(size.GetValue());
    }

    bool wxDir_Exists(wxString* dir)
    {
        return wxDir::Exists(PathOrEmpty(dir));
    }

    bool wxDir_Make(wxString* dir, int perm, int flags)
    {
        return wxDir::Make(PathOrEmpty(dir), perm, flags);
    }

    bool wxDir_Remove(wxString* dir, int flags)
    {
        return wxDir::Remove(PathOrEmpty(dir), flags);
    }

    wxDirTraverser* wxDirTraverser_Create(void* pObject, void* pFunction)
    {
        return new kwxDirTraverser(pObject, pFunction);
    }

    void wxDirTraverser_Delete(wxDirTraverser* self)
    {
        delete self;
    }
}
