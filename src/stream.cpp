#include "wrapper.h"
#include <wx/wfstream.h>

extern "C"
{
    /*-----------------------------------------------------------------------------
      Memory Input stream
    -----------------------------------------------------------------------------*/

    EXPORT wxMemoryInputStream* wxMemoryInputStream_Create(void* data, int len)
    {
        return new wxMemoryInputStream((unsigned char*) data, len);
    }

    EXPORT void wxMemoryInputStream_Delete(wxMemoryInputStream* self)
    {
        if (self)
            delete self;
    }

    /*-----------------------------------------------------------------------------
      File Input stream
    -----------------------------------------------------------------------------*/

    EXPORT wxFileInputStream* wxFileInputStream_Create(wxString* ofileName)
    {
        return new wxFileInputStream(*ofileName);
    }

    EXPORT void wxFileInputStream_Delete(wxFileInputStream* self)
    {
        if (self)
            delete self;
    }

    EXPORT bool wxFileInputStream_IsOk(wxFileInputStream* self)
    {
        return self->IsOk();
    }

    /*-----------------------------------------------------------------------------
      File Output stream
    -----------------------------------------------------------------------------*/

    EXPORT wxFileOutputStream* wxFileOutputStream_Create(wxString* ofileName)
    {
        return new wxFileOutputStream(*ofileName);
    }

    EXPORT void wxFileOutputStream_Delete(wxFileOutputStream* self)
    {
        if (self)
            delete self;
    }

    EXPORT bool wxFileOutputStream_IsOk(wxFileOutputStream* self)
    {
        return self->IsOk();
    }
}
