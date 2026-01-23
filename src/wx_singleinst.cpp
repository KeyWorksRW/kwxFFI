#include "wrapper.h"
#include <wx/snglinst.h>

extern "C"
{
    EXPORT void* wxSingleInstanceChecker_CreateDefault()
    {
        return (void*) new wxSingleInstanceChecker();
    }

    EXPORT bool wxSingleInstanceChecker_Create(wxSingleInstanceChecker* self, wxString* name,
                                               wxString* path)
    {
        return self->Create(*name, *path);
    }

    EXPORT bool wxSingleInstanceChecker_IsAnotherRunning(wxSingleInstanceChecker* self)
    {
        return self->IsAnotherRunning();
    }

    EXPORT void wxSingleInstanceChecker_Delete(void* self)
    {
        delete (wxSingleInstanceChecker*) self;
    }
}
