#include "wrapper.h"
#include <wx/notifmsg.h>

extern "C"
{
    EXPORT void* wxNotificationMessage_Create(wxString* title, wxString* message, wxWindow* parent,
                                              int flags)
    {
        wxString t = title ? *title : wxString();
        wxString m = message ? *message : wxString();
        return (void*) new wxNotificationMessage(t, m, parent, flags);
    }

    EXPORT void wxNotificationMessage_Delete(wxNotificationMessage* self)
    {
        delete self;
    }

    EXPORT bool wxNotificationMessage_Show(wxNotificationMessage* self, int timeout)
    {
        return self->Show(timeout);
    }

    EXPORT bool wxNotificationMessage_Close(wxNotificationMessage* self)
    {
        return self->Close();
    }

    EXPORT void wxNotificationMessage_SetTitle(wxNotificationMessage* self, wxString* title)
    {
        self->SetTitle(*title);
    }

    EXPORT void wxNotificationMessage_SetMessage(wxNotificationMessage* self, wxString* message)
    {
        self->SetMessage(*message);
    }

    EXPORT void wxNotificationMessage_SetParent(wxNotificationMessage* self, wxWindow* parent)
    {
        self->SetParent(parent);
    }

    EXPORT void wxNotificationMessage_SetFlags(wxNotificationMessage* self, int flags)
    {
        self->SetFlags(flags);
    }

    EXPORT void wxNotificationMessage_SetIcon(wxNotificationMessage* self, wxIcon* icon)
    {
        self->SetIcon(*icon);
    }

    EXPORT bool wxNotificationMessage_AddAction(wxNotificationMessage* self, int actionid,
                                                wxString* label)
    {
        wxString lbl = label ? *label : wxString();
        return self->AddAction(actionid, lbl);
    }

    // Static methods for platform capabilities
    EXPORT bool wxNotificationMessage_UseTaskBarIcon(wxTaskBarIcon* icon)
    {
        return wxNotificationMessage::UseTaskBarIcon(icon);
    }

    EXPORT bool wxNotificationMessage_MSWUseToasts(wxString* shortcutPath, wxString* appId)
    {
#ifdef __WXMSW__
        wxString sp = shortcutPath ? *shortcutPath : wxString();
        wxString ai = appId ? *appId : wxString();
        return wxNotificationMessage::MSWUseToasts(sp, ai);
#else
        return false;
#endif
    }

    // Event type exports
    MAKE_EVENT_WRAPPER(EVT_NOTIFICATION_MESSAGE_CLICK)
    MAKE_EVENT_WRAPPER(EVT_NOTIFICATION_MESSAGE_DISMISSED)
    MAKE_EVENT_WRAPPER(EVT_NOTIFICATION_MESSAGE_ACTION)
}
