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

    EXPORT void kwxConnection_SetOnAdvise(void* self, void* pFunction)
    {
        ((kwxConnection*) self)->SetOnAdvise(pFunction);
    }

    EXPORT void kwxConnection_SetOnExecute(void* self, void* pFunction)
    {
        ((kwxConnection*) self)->SetOnExecute(pFunction);
    }

    EXPORT void kwxConnection_SetOnRequest(void* self, void* pFunction)
    {
        ((kwxConnection*) self)->SetOnRequest(pFunction);
    }

    EXPORT void kwxConnection_SetOnPoke(void* self, void* pFunction)
    {
        ((kwxConnection*) self)->SetOnPoke(pFunction);
    }

    EXPORT void kwxConnection_SetOnStartAdvise(void* self, void* pFunction)
    {
        ((kwxConnection*) self)->SetOnStartAdvise(pFunction);
    }

    EXPORT void kwxConnection_SetOnStopAdvise(void* self, void* pFunction)
    {
        ((kwxConnection*) self)->SetOnStopAdvise(pFunction);
    }

    EXPORT void kwxConnection_SetOnDisconnect(void* self, void* pFunction)
    {
        ((kwxConnection*) self)->SetOnDisconnect(pFunction);
    }

    EXPORT void* kwxServer_Create(void* eiffelObject, void* connectFunc)
    {
        return new kwxServer(eiffelObject, connectFunc);
    }

    EXPORT void kwxServer_Delete(void* self)
    {
        delete (kwxServer*) self;
    }

    EXPORT int kwxServer_Initialize(void* self, wxString* name)
    {
        return ((kwxServer*) self)->Create(*name);
    }

    EXPORT void* kwxClient_Create(void* eiffelObject, void* connectFunc)
    {
        return new kwxClient(eiffelObject, connectFunc);
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
