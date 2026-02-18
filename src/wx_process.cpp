#include "kwx_wrapper.h"
#include <wx/process.h>

extern "C"
{
    EXPORT void* wxProcess_CreateDefault(wxEvtHandler* parent, int id)
    {
        return new wxProcess(parent, id);
    }

    EXPORT void* wxProcess_CreateRedirect(wxEvtHandler* parent, bool redirect)
    {
        return new wxProcess(parent, redirect);
    }

    EXPORT void wxProcess_Delete(wxProcess* self)
    {
        delete self;
    }

    EXPORT void wxProcess_Redirect(wxProcess* self)
    {
        self->Redirect();
    }

    EXPORT bool wxProcess_IsRedirected(wxProcess* self)
    {
        return self->IsRedirected();
    }

    EXPORT void wxProcess_Detach(wxProcess* self)
    {
        self->Detach();
    }

    EXPORT void* wxProcess_GetInputStream(wxProcess* self)
    {
        return (void*) self->GetInputStream();
    }

    EXPORT void* wxProcess_GetErrorStream(wxProcess* self)
    {
        return (void*) self->GetErrorStream();
    }

    EXPORT void* wxProcess_GetOutputStream(wxProcess* self)
    {
        return (void*) self->GetOutputStream();
    }

    EXPORT void wxProcess_CloseOutput(wxProcess* self)
    {
        self->CloseOutput();
    }

    EXPORT int wxProcessEvent_GetPid(wxProcessEvent* self)
    {
        return self->GetPid();
    }

    EXPORT int wxProcessEvent_GetExitCode(wxProcessEvent* self)
    {
        return self->GetExitCode();
    }

    EXPORT int wxStreamBase_GetLastError(wxStreamBase* self)
    {
        return (int) self->GetLastError();
    }

    EXPORT bool wxStreamBase_IsOk(wxStreamBase* self)
    {
        return self->IsOk();
    }

    EXPORT int wxStreamBase_GetSize(wxStreamBase* self)
    {
        return (int) self->GetSize();
    }

    EXPORT void wxOutputStream_Delete(wxOutputStream* self)
    {
        delete self;
    }

    EXPORT void wxOutputStream_PutC(wxOutputStream* self, char c)
    {
        self->PutC(c);
    }

    EXPORT void wxOutputStream_Write(wxOutputStream* self, void* buffer, int size)
    {
        self->Write((const void*) buffer, (size_t) size);
    }

    EXPORT int wxOutputStream_Seek(wxOutputStream* self, int pos, int mode)
    {
        return (int) self->SeekO((off_t) pos, (wxSeekMode) mode);
    }

    EXPORT int wxOutputStream_Tell(wxOutputStream* self)
    {
        return (int) self->TellO();
    }

    EXPORT int wxOutputStream_LastWrite(wxOutputStream* self)
    {
        return (int) self->LastWrite();
    }

    EXPORT void wxOutputStream_Sync(void* self)
    {
        ((wxOutputStream*) self)->Sync();
    }

    EXPORT void wxInputStream_Delete(wxInputStream* self)
    {
        delete self;
    }

    EXPORT bool wxInputStream_Eof(wxInputStream* self)
    {
        return self->Eof();
    }

    EXPORT char wxInputStream_Peek(wxInputStream* self)
    {
        return self->Peek();
    }

    EXPORT char wxInputStream_GetC(wxInputStream* self)
    {
        return self->GetC();
    }

    EXPORT void wxInputStream_Read(wxInputStream* self, void* buffer, int size)
    {
        self->Read(buffer, (size_t) size);
    }

    EXPORT int wxInputStream_SeekI(wxInputStream* self, int pos, int mode)
    {
        return (int) self->SeekI((off_t) pos, (wxSeekMode) mode);
    }

    EXPORT int wxInputStream_Tell(wxInputStream* self)
    {
        return (int) self->TellI();
    }

    EXPORT int wxInputStream_LastRead(wxInputStream* self)
    {
        return (int) self->LastRead();
    }

    EXPORT int wxInputStream_UngetBuffer(wxInputStream* self, void* buffer, int size)
    {
        return (int) self->Ungetch((const void*) buffer, (size_t) size);
    }

    EXPORT int wxInputStream_Ungetch(wxInputStream* self, char c)
    {
        return (int) self->Ungetch(c);
    }
}
