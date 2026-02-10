#include "wrapper.h"

#ifndef wxUSE_SVG
    #define wxUSE_SVG 1
#endif
#include <wx/dcsvg.h>

extern "C"
{
    EXPORT void* wxSVGFileDC_Create(wxString* a_filename)
    {
#ifdef wxUSE_SVG
        return (void*) new wxSVGFileDC(*a_filename);
#else
        return nullptr;
#endif
    }

    EXPORT void* wxSVGFileDC_CreateWithSize(wxString* a_filename, int a_width, int a_height)
    {
#ifdef wxUSE_SVG
        return (void*) new wxSVGFileDC(*a_filename, a_width, a_height);
#else
        return nullptr;
#endif
    }

    EXPORT void* wxSVGFileDC_CreateWithSizeAndResolution(wxString* a_filename, int a_width,
                                                         int a_height, float a_dpi)
    {
#ifdef wxUSE_SVG
        return (void*) new wxSVGFileDC(*a_filename, a_width, a_height, a_dpi);
#else
        return nullptr;
#endif
    }

    EXPORT void wxSVGFileDC_Delete(void* pObject)
    {
#ifdef wxUSE_SVG
        delete (wxSVGFileDC*) pObject;
#endif
    }
}
