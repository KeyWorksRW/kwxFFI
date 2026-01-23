/*==============================================================================
 * taskbaricon.cpp
 *
 * C wrapper for wxTaskbarIcon
 *
 * (C) 2002-2011 wxEiffel and wxHaskell contributors. See contributors.txt
 *
 * Licensed under the wxWidgets library license. see LICENSE.
 *
 *==============================================================================*/

#include "wrapper.h"
#include <wx/taskbar.h>

extern "C"
{
    ////////////////////////////////////////////////////////////////////////////////
    // Event Handlers
    ////////////////////////////////////////////////////////////////////////////////

    // #pragma message "wxWidgets taskbar event wrappers generated"
    MAKE_EVENT_WRAPPER(EVT_TASKBAR_MOVE)
    MAKE_EVENT_WRAPPER(EVT_TASKBAR_LEFT_DOWN)
    MAKE_EVENT_WRAPPER(EVT_TASKBAR_LEFT_UP)
    MAKE_EVENT_WRAPPER(EVT_TASKBAR_RIGHT_DOWN)
    MAKE_EVENT_WRAPPER(EVT_TASKBAR_RIGHT_UP)
    MAKE_EVENT_WRAPPER(EVT_TASKBAR_LEFT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_TASKBAR_RIGHT_DCLICK)
    MAKE_EVENT_WRAPPER(EVT_TASKBAR_BALLOON_TIMEOUT)
    MAKE_EVENT_WRAPPER(EVT_TASKBAR_BALLOON_CLICK)

    ////////////////////////////////////////////////////////////////////////////////
    // Wrappers
    ////////////////////////////////////////////////////////////////////////////////

    /*-----------------------------------------------------------------------------
      TaskBarIcon
    -----------------------------------------------------------------------------*/
    EXPORT wxTaskBarIcon* wxTaskBarIcon_Create()
    {
        return new wxTaskBarIcon();
    }

    EXPORT void wxTaskBarIcon_Delete(wxTaskBarIcon* self)
    {
        if (self)
            delete self;
    }

    EXPORT bool wxTaskBarIcon_IsIconInstalled(wxTaskBarIcon* self)
    {
        return self->IsIconInstalled();
    }

    EXPORT bool wxTaskBarIcon_IsOk(wxTaskBarIcon* self)
    {
        return self->IsOk();
    }

    EXPORT bool wxTaskBarIcon_PopupMenu(wxTaskBarIcon* self, wxMenu* menu)
    {
        return self->PopupMenu(menu);
    }

    EXPORT bool wxTaskBarIcon_RemoveIcon(wxTaskBarIcon* self)
    {
        return self->RemoveIcon();
    }

    EXPORT bool wxTaskBarIcon_SetIcon(wxTaskBarIcon* self, wxIcon* icon, wxString* tooltip)
    {
        return tooltip ? self->SetIcon(*icon, *tooltip) : self->SetIcon(*icon);
    }
}
