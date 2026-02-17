// update checked 100% with 2.8.9 manual
#include "wrapper.h"

#include <wx/socket.h>

extern "C"
{
# // wxSocket errors
    EXPORT int expwxSOCKET_NOERROR()
    {
        return (int) wxSOCKET_NOERROR;
    }
    EXPORT int expwxSOCKET_INVOP()
    {
        return (int) wxSOCKET_INVOP;
    }
    EXPORT int expwxSOCKET_IOERR()
    {
        return (int) wxSOCKET_IOERR;
    }
    EXPORT int expwxSOCKET_INVADDR()
    {
        return (int) wxSOCKET_INVADDR;
    }
    EXPORT int expwxSOCKET_INVSOCK()
    {
        return (int) wxSOCKET_INVSOCK;
    }
    EXPORT int expwxSOCKET_NOHOST()
    {
        return (int) wxSOCKET_NOHOST;
    }
    EXPORT int expwxSOCKET_INVPORT()
    {
        return (int) wxSOCKET_INVPORT;
    }
    EXPORT int expwxSOCKET_WOULDBLOCK()
    {
        return (int) wxSOCKET_WOULDBLOCK;
    }
    EXPORT int expwxSOCKET_TIMEDOUT()
    {
        return (int) wxSOCKET_TIMEDOUT;
    }
    EXPORT int expwxSOCKET_MEMERR()
    {
        return (int) wxSOCKET_MEMERR;
    }
    // wxSocket events
    EXPORT int expwxSOCKET_INPUT()
    {
        return (int) wxSOCKET_INPUT;
    }
    EXPORT int expwxSOCKET_OUTPUT()
    {
        return (int) wxSOCKET_OUTPUT;
    }
    EXPORT int expwxSOCKET_CONNECTION()
    {
        return (int) wxSOCKET_CONNECTION;
    }
    EXPORT int expwxSOCKET_LOST()
    {
        return (int) wxSOCKET_LOST;
    }
    // wxSocketFlags
    EXPORT int expwxSOCKET_NONE()
    {
        return (int) wxSOCKET_NONE;
    }
    EXPORT int expwxSOCKET_NOWAIT()
    {
        return (int) wxSOCKET_NOWAIT;
    }
    EXPORT int expwxSOCKET_WAITALL()
    {
        return (int) wxSOCKET_WAITALL;
    }
    EXPORT int expwxSOCKET_BLOCK()
    {
        return (int) wxSOCKET_BLOCK;
    }
    EXPORT int expwxSOCKET_REUSEADDR()
    {
        return (int) wxSOCKET_REUSEADDR;
    }
    // wxSocketEventFlags
    EXPORT int expwxSOCKET_INPUT_FLAG()
    {
        return (int) wxSOCKET_INPUT_FLAG;
    }
    EXPORT int expwxSOCKET_OUTPUT_FLAG()
    {
        return (int) wxSOCKET_OUTPUT_FLAG;
    }
    EXPORT int expwxSOCKET_CONNECTION_FLAG()
    {
        return (int) wxSOCKET_CONNECTION_FLAG;
    }
    EXPORT int expwxSOCKET_LOST_FLAG()
    {
        return (int) wxSOCKET_LOST_FLAG;
    }

    // wxSocketBase
    // wxSocketBase::wxSocketBase
    EXPORT void wxSocketBase_Delete(wxSocketBase* self)
    {
        delete self;
    }
    EXPORT void wxSocketBase_Close(wxSocketBase* self)
    {
        self->Close();
    }
    EXPORT bool wxSocketBase_Destroy(wxSocketBase* self)
    {
        return self->Destroy();
    }
    EXPORT wxSocketBase* wxSocketBase_Discard(wxSocketBase* self)
    {
        return &self->Discard();
    }
    EXPORT bool wxSocketBase_Error(wxSocketBase* self)
    {
        return self->Error();
    }
    EXPORT void* wxSocketBase_GetClientData(wxSocketBase* self)
    {
        return self->GetClientData();
    }
    EXPORT bool wxSocketBase_GetLocal(wxSocketBase* self, wxSockAddress* addr)
    {
        return self->GetLocal(*addr);
    }
    // note gsocket = int
    EXPORT int wxSocketBase_GetFlags(wxSocketBase* self)
    {
        return self->GetFlags();
    }
    EXPORT bool wxSocketBase_GetPeer(wxSocketBase* self, wxSockAddress* addr)
    {
        return self->GetPeer(*addr);
    }
    EXPORT void wxSocketBase_InterruptWait(wxSocketBase* self)
    {
        self->InterruptWait();
    }
    EXPORT bool wxSocketBase_IsConnected(wxSocketBase* self)
    {
        return self->IsConnected();
    }
    EXPORT bool wxSocketBase_IsData(wxSocketBase* self)
    {
        return self->IsData();
    }
    EXPORT bool wxSocketBase_IsDisconnected(wxSocketBase* self)
    {
        return self->IsDisconnected();
    }
    EXPORT wxUint32 wxSocketBase_LastCount(wxSocketBase* self)
    {
        return self->LastCount();
    }
    EXPORT int wxSocketBase_LastError(wxSocketBase* self)
    {
        return self->LastError();
    }
    EXPORT void wxSocketBase_Notify(wxSocketBase* self, bool notify)
    {
        self->Notify(notify);
    }
    EXPORT bool wxSocketBase_IsOk(wxSocketBase* self)
    {
        return self->IsOk();
    }
    EXPORT void wxSocketBase_RestoreState(wxSocketBase* self)
    {
        self->RestoreState();
    }
    EXPORT void wxSocketBase_SaveState(wxSocketBase* self)
    {
        self->SaveState();
    }
    EXPORT void wxSocketBase_SetClientData(wxSocketBase* self, void* data)
    {
        self->SetClientData(data);
    }
    EXPORT void wxSocketBase_SetEventHandler(wxSocketBase* self, wxEvtHandler* handler, int id)
    {
        self->SetEventHandler(*handler, id);
    }
    EXPORT void wxSocketBase_SetFlags(wxSocketBase* self, int flags)
    {
        self->SetFlags(flags);
    }
    EXPORT bool wxSocketBase_SetLocal(wxSocketBase* self, wxIPV4address* local)
    {
        return self->SetLocal(*local);
    }
    EXPORT void wxSocketBase_SetNotify(wxSocketBase* self, int flags)
    {
        self->SetNotify(flags);
    }
    EXPORT void wxSocketBase_SetTimeout(wxSocketBase* self, int seconds)
    {
        self->SetTimeout(seconds);
    }
    EXPORT wxSocketBase* wxSocketBase_Peek(wxSocketBase* self, void* buffer, wxUint32 nbytes)
    {
        return &self->Peek(buffer, nbytes);
    }
    EXPORT wxSocketBase* wxSocketBase_Read(wxSocketBase* self, void* buffer, wxUint32 nbytes)
    {
        return &self->Read(buffer, nbytes);
    }
    EXPORT wxSocketBase* wxSocketBase_ReadMsg(wxSocketBase* self, void* buffer, wxUint32 nbytes)
    {
        return &self->ReadMsg(buffer, nbytes);
    }
    EXPORT wxSocketBase* wxSocketBase_Unread(wxSocketBase* self, void* buffer, wxUint32 nbytes)
    {
        return &self->Unread(buffer, nbytes);
    }
    EXPORT bool wxSocketBase_Wait(wxSocketBase* self, long seconds, long millisecond)
    {
        return self->Wait(seconds, millisecond);
    }
    EXPORT bool wxSocketBase_WaitForLost(wxSocketBase* self, long seconds, long millisecond)
    {
        return self->WaitForLost(seconds, millisecond);
    }
    EXPORT bool wxSocketBase_WaitForRead(wxSocketBase* self, long seconds, long millisecond)
    {
        return self->WaitForRead(seconds, millisecond);
    }
    EXPORT bool wxSocketBase_WaitForWrite(wxSocketBase* self, long seconds, long millisecond)
    {
        return self->WaitForWrite(seconds, millisecond);
    }
    EXPORT wxSocketBase* wxSocketBase_Write(wxSocketBase* self, void* buffer, wxUint32 nbytes)
    {
        return &self->Write(buffer, nbytes);
    }
    EXPORT wxSocketBase* wxSocketBase_WriteMsg(wxSocketBase* self, void* buffer, wxUint32 nbytes)
    {
        return &self->WriteMsg(buffer, nbytes);
    }
    // wxSocketEvent
    EXPORT wxSocketEvent* wxSocketEvent_Create(int id)
    {
        return new wxSocketEvent(id);
    }
    EXPORT void wxSocketEvent_Delete(wxSocketEvent* self)
    {
        delete self;
    }
    EXPORT void* wxSocketEvent_GetClientData(wxSocketEvent* self)
    {
        return self->GetClientData();
    }
    EXPORT wxSocketBase* wxSocketEvent_GetSocket(wxSocketEvent* self)
    {
        return self->GetSocket();
    }
    EXPORT int wxSocketEvent_GetSocketEvent(wxSocketEvent* self)
    {
        return self->GetSocketEvent();
    }
    // wxSocketClient
    EXPORT wxSocketClient* wxSocketClient_Create(int flags)
    {
        return new wxSocketClient(flags);
    }
    EXPORT void wxSocketClient_Delete(wxSocketClient* self)
    {
        delete self;
    }
    EXPORT bool wxSocketClient_Connect(wxSocketClient* self, wxSockAddress* address, bool wait)
    {
        return self->Connect(*address, wait);
    }
    EXPORT bool wxSocketClient_ConnectLocal(wxSocketClient* self, wxSockAddress* address,
                                            wxSockAddress* local, bool wait)
    {
        return self->Connect(*address, *local, wait);
    }
    EXPORT bool wxSocketClient_WaitOnConnect(wxSocketClient* self, long seconds, long millisecond)
    {
        return self->WaitOnConnect(seconds, millisecond);
    }

    // wxSocketServer
    EXPORT wxSocketServer* wxSocketServer_Create(wxSockAddress* address, int flags)
    {
        return new wxSocketServer(*address, flags);
    }
    EXPORT void wxSocketServer_Delete(wxSocketServer* self)
    {
        delete self;
    }
    EXPORT wxSocketBase* wxSocketServer_Accept(wxSocketServer* self, bool wait)
    {
        return self->Accept(wait);
    }
    EXPORT bool wxSocketServer_AcceptWith(wxSocketServer* self, wxSocketBase* socket, bool wait)
    {
        return self->AcceptWith(*socket, wait);
    }
    EXPORT bool wxSocketServer_WaitForAccept(wxSocketServer* self, long seconds, long millisecond)
    {
        return self->WaitForAccept(seconds, millisecond);
    }
}