#include "wrapper.h"
#include <wx/dialup.h>

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

    EXPORT int wxDialUpManager_GetISPNames(wxDialUpManager* self, void* _lst)
    {
        wxArrayString arr;
        self->GetISPNames(arr);

        if (_lst)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((char**) _lst)[i] = strdup(arr.Item(i).utf8_str().data());
        }

        return arr.GetCount();
    }

    EXPORT bool wxDialUpManager_Dial(wxDialUpManager* self, wxString* nameOfISP, wxString* username,
                                     wxString* password, bool async)
    {
        return self->Dial(*nameOfISP, *username, *password, async);
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

    EXPORT void wxDialUpManager_SetOnlineStatus(wxDialUpManager* self, bool isOnline)
    {
        self->SetOnlineStatus(isOnline);
    }

    EXPORT bool wxDialUpManager_EnableAutoCheckOnlineStatus(wxDialUpManager* self, size_t nSeconds)
    {
        return self->EnableAutoCheckOnlineStatus(nSeconds);
    }

    EXPORT void wxDialUpManager_DisableAutoCheckOnlineStatus(wxDialUpManager* self)
    {
        self->DisableAutoCheckOnlineStatus();
    }

    EXPORT void wxDialUpManager_SetWellKnownHost(wxDialUpManager* self, wxString* hostname,
                                                 int portno)
    {
        self->SetWellKnownHost(*hostname, portno);
    }

    EXPORT void wxDialUpManager_SetConnectCommand(wxDialUpManager* self, wxString* commandDial,
                                                  wxString* commandHangup)
    {
        self->SetConnectCommand(*commandDial, *commandHangup);
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
