#include "wrapper.h"

// wxFontDialog inherits from wxDialog (wxTopLevelWindow).
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

extern "C"
{
    EXPORT void* wxFontDialog_Create(void* parent, void* fontData)
    {
#if WXWIN_COMPATIBILITY_2_6
    #ifdef wxMAC_USE_EXPERIMENTAL_FONTDIALOG
        return (void*) new wxFontDialog((wxWindow*) parent, (wxFontData&) fontData);
    #else
        return (void*) new wxFontDialog((wxWindow*) parent, (wxFontData*) fontData);
    #endif
#else
        return (void*) new wxFontDialog((wxWindow*) parent, (wxFontData&) fontData);
#endif
    }

    EXPORT void wxFontDialog_GetFontData(void* pObject, void* ref)
    {
        *((wxFontData*) ref) = ((wxFontDialog*) pObject)->GetFontData();
    }
}
