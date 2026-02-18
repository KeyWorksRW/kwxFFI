#include "kwx_wrapper.h"
#include <wx/uiaction.h>

extern "C"
{
    EXPORT void* wxUIActionSimulator_Create()
    {
        return (void*) new wxUIActionSimulator();
    }

    EXPORT void wxUIActionSimulator_Delete(wxUIActionSimulator* self)
    {
        delete self;
    }

    // Mouse actions

    EXPORT bool wxUIActionSimulator_MouseMove(wxUIActionSimulator* self, int x, int y)
    {
        return self->MouseMove(x, y);
    }

    EXPORT bool wxUIActionSimulator_MouseMoveToWindow(wxUIActionSimulator* self, wxWindow* window,
                                                      int x, int y)
    {
        return self->MouseMove(window->ClientToScreen(wxPoint(x, y)));
    }

    EXPORT bool wxUIActionSimulator_MouseDown(wxUIActionSimulator* self, int button)
    {
        return self->MouseDown(button);
    }

    EXPORT bool wxUIActionSimulator_MouseUp(wxUIActionSimulator* self, int button)
    {
        return self->MouseUp(button);
    }

    EXPORT bool wxUIActionSimulator_MouseClick(wxUIActionSimulator* self, int button)
    {
        return self->MouseClick(button);
    }

    EXPORT bool wxUIActionSimulator_MouseDblClick(wxUIActionSimulator* self, int button)
    {
        return self->MouseDblClick(button);
    }

    EXPORT bool wxUIActionSimulator_MouseDragDrop(wxUIActionSimulator* self, int x1, int y1, int x2,
                                                  int y2, int button)
    {
        return self->MouseDragDrop(x1, y1, x2, y2, button);
    }

    // Keyboard actions

    EXPORT bool wxUIActionSimulator_Char(wxUIActionSimulator* self, int keycode, int modifiers)
    {
        return self->Char(keycode, modifiers);
    }

    EXPORT bool wxUIActionSimulator_KeyDown(wxUIActionSimulator* self, int keycode, int modifiers)
    {
        return self->KeyDown(keycode, modifiers);
    }

    EXPORT bool wxUIActionSimulator_KeyUp(wxUIActionSimulator* self, int keycode, int modifiers)
    {
        return self->KeyUp(keycode, modifiers);
    }

    EXPORT bool wxUIActionSimulator_Text(wxUIActionSimulator* self, wxString* text)
    {
        return self->Text(text->utf8_str().data());
    }

    // Convenience: select all text in current control
    EXPORT bool wxUIActionSimulator_Select(wxUIActionSimulator* self, wxString* text)
    {
        return self->Select(*text);
    }
}
