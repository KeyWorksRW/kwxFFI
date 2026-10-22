#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxDialUpManager* wxDialUpManager_Create()
    {
        return wxDialUpManager::Create();
    }

    EXPORT void wxDialUpManager_Delete(wxDialUpManager* self)
    {
        delete self;
    }

    EXPORT bool wxDialUpManager_IsOk(wxDialUpManager* self)
    {
        return self->IsOk();
    }

    // Fills the caller-supplied array of char pointers; each name is a copy
    // that the caller owns. Returns the number of names.
    EXPORT int wxDialUpManager_GetISPNames(wxDialUpManager* self, void* names)
    {
        wxArrayString isp_names;
        self->GetISPNames(isp_names);
        if (names)
        {
            for (unsigned int i = 0; i < isp_names.GetCount(); ++i)
            {
                static_cast<const char**>(names)[i] =
                    strdup(isp_names.Item(i).utf8_string().data());
            }
        }

        return static_cast<int>(isp_names.GetCount());
    }

    EXPORT bool wxDialUpManager_Dial(wxDialUpManager* self, wxString* isp_name, wxString* username,
                                     wxString* password, bool async)
    {
        return self->Dial(*isp_name, *username, *password, async);
    }

    EXPORT bool wxDialUpManager_IsDialing(wxDialUpManager* self)
    {
        return self->IsDialing();
    }

    EXPORT bool wxDialUpManager_CancelDialing(wxDialUpManager* self)
    {
        return self->CancelDialing();
    }

    EXPORT bool wxDialUpManager_HangUp(wxDialUpManager* self)
    {
        return self->HangUp();
    }

    EXPORT bool wxDialUpManager_IsAlwaysOnline(wxDialUpManager* self)
    {
        return self->IsAlwaysOnline();
    }

    EXPORT bool wxDialUpManager_IsOnline(wxDialUpManager* self)
    {
        return self->IsOnline();
    }

    EXPORT void wxDialUpManager_SetOnlineStatus(wxDialUpManager* self, bool is_online)
    {
        self->SetOnlineStatus(is_online);
    }

    EXPORT bool wxDialUpManager_EnableAutoCheckOnlineStatus(wxDialUpManager* self, int seconds)
    {
        return self->EnableAutoCheckOnlineStatus(static_cast<size_t>(seconds));
    }

    EXPORT void wxDialUpManager_DisableAutoCheckOnlineStatus(wxDialUpManager* self)
    {
        self->DisableAutoCheckOnlineStatus();
    }

    EXPORT void wxDialUpManager_SetWellKnownHost(wxDialUpManager* self, wxString* host_name,
                                                 int port_number)
    {
        self->SetWellKnownHost(*host_name, port_number);
    }

    EXPORT void wxDialUpManager_SetConnectCommand(wxDialUpManager* self, wxString* dial_command,
                                                  wxString* hangup_command)
    {
        self->SetConnectCommand(*dial_command, *hangup_command);
    }

    EXPORT bool wxDialUpEvent_IsConnectedEvent(wxDialUpEvent* self)
    {
        return self->IsConnectedEvent();
    }

    EXPORT bool wxDialUpEvent_IsOwnEvent(wxDialUpEvent* self)
    {
        return self->IsOwnEvent();
    }
}
