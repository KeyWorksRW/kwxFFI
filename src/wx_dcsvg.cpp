#include "kwx_wrapper.h"

#ifndef wxUSE_SVG
    #define wxUSE_SVG 1
#endif
#include <wx/dcsvg.h>

extern "C"
{
    EXPORT void* wxSVGFileDC_Create(wxString* a_filename)
    {
        return (void*) new wxSVGFileDC(*a_filename);
    }

    EXPORT void* wxSVGFileDC_CreateWithSize(wxString* a_filename, int a_width, int a_height)
    {
        return (void*) new wxSVGFileDC(*a_filename, a_width, a_height);
    }

    EXPORT void* wxSVGFileDC_CreateWithSizeAndResolution(wxString* a_filename, int a_width,
                                                         int a_height, float a_dpi)
    {
        return (void*) new wxSVGFileDC(*a_filename, a_width, a_height, a_dpi);
    }

    EXPORT void wxSVGFileDC_Delete(void* pObject)
    {
        delete (wxSVGFileDC*) pObject;
    }
}
