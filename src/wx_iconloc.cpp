#include "kwx_wrapper.h"

#include <tuple>

extern "C"
{
    EXPORT wxIconLocation* wxIconLocation_Create(wxString* file_name, int index)
    {
#ifdef __WINDOWS__
        return new wxIconLocation(*file_name, index);
#else
        std::ignore = index;
        return new wxIconLocation(*file_name);
#endif
    }

    EXPORT void wxIconLocation_Delete(wxIconLocation* self)
    {
        delete self;
    }

    EXPORT bool wxIconLocation_IsOk(wxIconLocation* self)
    {
        return self->IsOk();
    }

    EXPORT wxString* wxIconLocation_GetFileName(wxIconLocation* self)
    {
        return new wxString(self->GetFileName());
    }

    EXPORT void wxIconLocation_SetFileName(wxIconLocation* self, wxString* file_name)
    {
        self->SetFileName(*file_name);
    }
}
