#include "wrapper.h"

extern "C"
{
    EXPORT void* ELJConnection_CreateDefault()
    {
        return new ELJConnection();
    }

    EXPORT void* ELJConnection_Create(char* buffer, int size)
    {
        return new ELJConnection(buffer, size);
    }

    EXPORT void ELJConnection_Delete(void* self)
    {
        delete (ELJConnection*) self;
    }

    EXPORT bool ELJConnection_Execute(ELJConnection* self, wxString* data, int size, int format)
    {
        return self->Execute(*data, size, (wxIPCFormat) format);
    }

    EXPORT void* ELJConnection_Request(void* self, wxString* item, void* size, int format)
    {
        return (void*) ((ELJConnection*) self)
            ->Request(*item, (size_t*) size, (wxIPCFormat) format);
    }

    EXPORT bool ELJConnection_Poke(ELJConnection* self, wxString* item, char* data, int size,
                                   int format)
    {
        return self->Poke(*item, data, size, (wxIPCFormat) format);
    }

    EXPORT bool ELJConnection_StartAdvise(ELJConnection* self, wxString* item)
    {
        return self->StartAdvise(*item);
    }

    EXPORT bool ELJConnection_StopAdvise(ELJConnection* self, wxString* item)
    {
        return self->StopAdvise(*item);
    }

    EXPORT bool ELJConnection_Advise(ELJConnection* self, wxString* item, char* data, int size,
                                     int format)
    {
        return self->Advise(*item, data, size, (wxIPCFormat) format);
    }

    EXPORT bool ELJConnection_Disconnect(ELJConnection* self)
    {
        return self->Disconnect();
    }

    EXPORT void ELJConnection_Compress(void* self, bool on)
    {
        ((ELJConnection*) self)->Compress(on);
    }

    EXPORT void ELJConnection_SetOnAdvise(void* self, void* _fnc)
    {
        ((ELJConnection*) self)->SetOnAdvise(_fnc);
    }

    EXPORT void ELJConnection_SetOnExecute(void* self, void* _fnc)
    {
        ((ELJConnection*) self)->SetOnExecute(_fnc);
    }

    EXPORT void ELJConnection_SetOnRequest(void* self, void* _fnc)
    {
        ((ELJConnection*) self)->SetOnRequest(_fnc);
    }

    EXPORT void ELJConnection_SetOnPoke(void* self, void* _fnc)
    {
        ((ELJConnection*) self)->SetOnPoke(_fnc);
    }

    EXPORT void ELJConnection_SetOnStartAdvise(void* self, void* _fnc)
    {
        ((ELJConnection*) self)->SetOnStartAdvise(_fnc);
    }

    EXPORT void ELJConnection_SetOnStopAdvise(void* self, void* _fnc)
    {
        ((ELJConnection*) self)->SetOnStopAdvise(_fnc);
    }

    EXPORT void ELJConnection_SetOnDisconnect(void* self, void* _fnc)
    {
        ((ELJConnection*) self)->SetOnDisconnect(_fnc);
    }

    EXPORT void* ELJServer_Create(void* _eobj, void* _cnct)
    {
        return new ELJServer(_eobj, _cnct);
    }

    EXPORT void ELJServer_Delete(void* self)
    {
        delete (ELJServer*) self;
    }

    EXPORT int ELJServer_Initialize(void* self, wxString* name)
    {
        return ((ELJServer*) self)->Create(*name);
    }

    EXPORT void* ELJClient_Create(void* _eobj, void* _cnct)
    {
        return new ELJClient(_eobj, _cnct);
    }

    EXPORT void ELJClient_Delete(void* self)
    {
        delete (ELJClient*) self;
    }

    EXPORT void ELJClient_MakeConnection(void* self, wxString* host, wxString* server,
                                         wxString* topic)
    {
        ((ELJClient*) self)->MakeConnection(*host, *server, *topic);
    }
}
