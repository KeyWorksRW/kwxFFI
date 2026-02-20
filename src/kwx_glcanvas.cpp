#include "kwx_wrapper.h"

#include <wx/glcanvas.h>

// wxGLCanvas inherits from wxWindow.
// Additional methods available via:
//   wxWindow_* — base window methods (see wx_window.cpp)

// We want to include the function signatures always -- even on
// systems that don't support openGL. This means that every function body is
// surrounded by #if wxUSE_GLCANVAS directives :-(
#if defined(wxUSE_GLCANVAS) && (wxUSE_GLCANVAS == 0)
    #undef wxUSE_GLCANVAS
#endif

#if defined(wxcREFUSE_OPENGL)
    #undef wxUSE_GLCANVAS
#endif

#if !wxUSE_GLCANVAS
    #define wxGLCanvas  void
    #define wxGLContext void
#endif

extern "C"
{
    EXPORT wxGLCanvas* wxGLCanvas_Create(wxWindow* parent, int windowID, int* attributes, int x,
                                         int y, int width,
                                         int height,  // TRect
                                         int style, wxString* title, wxPalette* palette)
    {
#if wxUSE_GLCANVAS
        return new wxGLCanvas(parent, windowID, attributes, wxPoint(x, y), wxSize(width, height),
                              style, (title ? *title : wxString("GLCanvas")),
                              (palette ? *palette : wxNullPalette));
#else
        return nullptr;
#endif
    }

    EXPORT bool wxGLCanvas_SetCurrent(wxGLCanvas* self, wxGLContext* ctxt)
    {
#if wxUSE_GLCANVAS
        if (ctxt == nullptr)
            return false;
        else
            return self->SetCurrent(*ctxt);
#else
        return false;
#endif
    }

    EXPORT bool wxGLCanvas_SetColour(wxGLCanvas* self, wxColour* colour)
    {
#if wxUSE_GLCANVAS
        wxString name = wxTheColourDatabase->FindName(*colour);
        if (name.IsEmpty())
            return self->SetColour(wxString("WHITE"));
        else
            return self->SetColour(name);
#else
        return false;
#endif
    }

    EXPORT bool wxGLCanvas_SwapBuffers(wxGLCanvas* self)
    {
#if wxUSE_GLCANVAS
        return self->SwapBuffers();
#else
        return false;
#endif
    }

    EXPORT bool wxGLCanvas_IsDisplaySupported(int* attributes)
    {
#if wxUSE_GLCANVAS
        return wxGLCanvas::IsDisplaySupported(attributes);
#else
        return false;
#endif
    }

    EXPORT bool wxGLCanvas_IsExtensionSupported(wxString* extension)
    {
#if wxUSE_GLCANVAS
        const char* str = (const char*) extension->c_str();
        if (str != nullptr)
        {
            bool retval = wxGLCanvas::IsExtensionSupported(str);
            delete str;
            return retval;
        }
        else
            return false;
#else
        return false;
#endif
    }

    EXPORT wxGLContext* wxGLContext_Create(wxGLCanvas* win, wxGLContext* other)
    {
#if wxUSE_GLCANVAS
        return new wxGLContext(win, other);
#endif
    }

    EXPORT wxGLContext* wxGLContext_CreateFromNull(wxGLCanvas* win)
    {
#if wxUSE_GLCANVAS
        return new wxGLContext(win);
#endif
    }

    EXPORT bool wxGLContext_SetCurrent(wxGLContext* self, wxGLCanvas* win)
    {
#if wxUSE_GLCANVAS
        if (win == nullptr)
            return false;
        else
            return self->SetCurrent(*win);
#else
        return false;
#endif
    }
}
