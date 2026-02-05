#include "wrapper.h"

extern "C"
{
    EXPORT void* kwxConnection_CreateDefault()
    {
        return new kwxConnection();
    }

    EXPORT void* kwxConnection_Create(char* buffer, int size)
    {
        return new kwxConnection(buffer, size);
    }

    EXPORT void kwxConnection_Delete(void* self)
    {
        delete (kwxConnection*) self;
    }

    EXPORT bool kwxConnection_Execute(kwxConnection* self, wxString* data, int size, int format)
    {
        return self->Execute(*data, size, (wxIPCFormat) format);
    }

    EXPORT void* kwxConnection_Request(void* self, wxString* item, void* size, int format)
    {
        return (void*) ((kwxConnection*) self)
            ->Request(*item, (size_t*) size, (wxIPCFormat) format);
    }

    EXPORT bool kwxConnection_Poke(kwxConnection* self, wxString* item, char* data, int size,
                                   int format)
    {
        return self->Poke(*item, data, size, (wxIPCFormat) format);
    }

    EXPORT bool kwxConnection_StartAdvise(kwxConnection* self, wxString* item)
    {
        return self->StartAdvise(*item);
    }

    EXPORT bool kwxConnection_StopAdvise(kwxConnection* self, wxString* item)
    {
        return self->StopAdvise(*item);
    }

    EXPORT bool kwxConnection_Advise(kwxConnection* self, wxString* item, char* data, int size,
                                     int format)
    {
        return self->Advise(*item, data, size, (wxIPCFormat) format);
    }

    EXPORT bool kwxConnection_Disconnect(kwxConnection* self)
    {
        return self->Disconnect();
    }

    EXPORT void kwxConnection_Compress(void* self, bool on)
    {
        ((kwxConnection*) self)->Compress(on);
    }

    EXPORT void kwxConnection_SetOnAdvise(void* self, void* _fnc)
    {
        ((kwxConnection*) self)->SetOnAdvise(_fnc);
    }

    EXPORT void kwxConnection_SetOnExecute(void* self, void* _fnc)
    {
        ((kwxConnection*) self)->SetOnExecute(_fnc);
    }

    EXPORT void kwxConnection_SetOnRequest(void* self, void* _fnc)
    {
        ((kwxConnection*) self)->SetOnRequest(_fnc);
    }

    EXPORT void kwxConnection_SetOnPoke(void* self, void* _fnc)
    {
        ((kwxConnection*) self)->SetOnPoke(_fnc);
    }

    EXPORT void kwxConnection_SetOnStartAdvise(void* self, void* _fnc)
    {
        ((kwxConnection*) self)->SetOnStartAdvise(_fnc);
    }

    EXPORT void kwxConnection_SetOnStopAdvise(void* self, void* _fnc)
    {
        ((kwxConnection*) self)->SetOnStopAdvise(_fnc);
    }

    EXPORT void kwxConnection_SetOnDisconnect(void* self, void* _fnc)
    {
        ((kwxConnection*) self)->SetOnDisconnect(_fnc);
    }

    EXPORT void* kwxServer_Create(void* _eobj, void* _cnct)
    {
        return new kwxServer(_eobj, _cnct);
    }

    EXPORT void kwxServer_Delete(void* self)
    {
        delete (kwxServer*) self;
    }

    EXPORT int kwxServer_Initialize(void* self, wxString* name)
    {
        return ((kwxServer*) self)->Create(*name);
    }

    EXPORT void* kwxClient_Create(void* _eobj, void* _cnct)
    {
        return new kwxClient(_eobj, _cnct);
    }

    EXPORT void kwxClient_Delete(void* self)
    {
        delete (kwxClient*) self;
    }

    EXPORT void kwxClient_MakeConnection(void* self, wxString* host, wxString* server,
                                         wxString* topic)
    {
        ((kwxClient*) self)->MakeConnection(*host, *server, *topic);
    }
}
