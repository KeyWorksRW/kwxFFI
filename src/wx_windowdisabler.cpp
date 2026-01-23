#include "wrapper.h"

extern "C"
{
    // wxWindowDisabler - RAII class to disable windows

    EXPORT void* wxWindowDisabler_Create(wxWindow* winToSkip)
    {
        return (void*) new wxWindowDisabler(winToSkip);
    }

    EXPORT void wxWindowDisabler_Delete(wxWindowDisabler* self)
    {
        delete self;
    }
}
