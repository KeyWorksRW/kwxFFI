// Base-utility socket, HTTP, FTP and URL wrappers: the methods missing from wxSocketBase,
// wxSocketClient, wxSockAddress, wxIPaddress and wxIPV4address, plus the whole wrapped surface
// of wxProtocol, wxHTTP, wxFTP and wxURL.
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <wx/buffer.h>
#include <wx/protocol/ftp.h>
#include <wx/protocol/http.h>
#include <wx/protocol/protocol.h>
#include <wx/url.h>

// Each class is wrapped only when its wxWidgets feature is enabled. The declarations in
// include/kwx_net_extra.h are unguarded, following the src/wx_taskbarbutton.cpp pattern; the
// supported builds enable sockets, protocols and URL, and an unsupported build does not define
// the class at all, so a section guard is the only way to keep the translation unit
// compilable. `wxProtocol` is built on `wxSocketClient` when `wxUSE_SOCKETS` is on, and
// `wxHTTP` / `wxFTP` build on `wxProtocol`, so their guards include the prerequisites.
extern "C"
{
#if wxUSE_SOCKETS
    // -----------------------------------------------------------------------
    // wxSocketBase
    // -----------------------------------------------------------------------

    EXPORT int wxSocketBase_GetTimeout(wxSocketBase* self)
    {
        return static_cast<int>(self->GetTimeout());
    }

    EXPORT bool wxSocketBase_IsClosed(wxSocketBase* self)
    {
        return self->IsClosed();
    }

    EXPORT wxUint32 wxSocketBase_LastReadCount(wxSocketBase* self)
    {
        return self->LastReadCount();
    }

    EXPORT wxUint32 wxSocketBase_LastWriteCount(wxSocketBase* self)
    {
        return self->LastWriteCount();
    }

    EXPORT wxUint32 wxSocketBase_GetLastIOSize(wxSocketBase* self)
    {
        return self->GetLastIOSize();
    }

    EXPORT wxUint32 wxSocketBase_GetLastIOReadSize(wxSocketBase* self)
    {
        return self->GetLastIOReadSize();
    }

    EXPORT wxUint32 wxSocketBase_GetLastIOWriteSize(wxSocketBase* self)
    {
        return self->GetLastIOWriteSize();
    }

    EXPORT void wxSocketBase_ShutdownOutput(wxSocketBase* self)
    {
        self->ShutdownOutput();
    }

    EXPORT bool wxSocketBase_GetOption(wxSocketBase* self, int level, int option_name,
                                       void* option_value, int* option_length)
    {
        return self->GetOption(level, option_name, option_value, option_length);
    }

    EXPORT bool wxSocketBase_SetOption(wxSocketBase* self, int level, int option_name,
                                       void* option_value, int option_length)
    {
        return self->SetOption(level, option_name, option_value, option_length);
    }

    EXPORT wxEvtHandler* wxSocketBase_GetEventHandler(wxSocketBase* self)
    {
        return self->GetEventHandler();
    }

    EXPORT bool wxSocketBase_Initialize()
    {
        return wxSocketBase::Initialize();
    }

    EXPORT void wxSocketBase_Shutdown()
    {
        wxSocketBase::Shutdown();
    }

    EXPORT bool wxSocketBase_IsInitialized()
    {
        return wxSocketBase::IsInitialized();
    }

    // -----------------------------------------------------------------------
    // wxSocketClient
    // -----------------------------------------------------------------------

    EXPORT void wxSocketClient_SetInitialSocketBuffers(wxSocketClient* self, int receive_size,
                                                       int send_size)
    {
        self->SetInitialSocketBuffers(receive_size, send_size);
    }

    // -----------------------------------------------------------------------
    // wxSockAddress
    // -----------------------------------------------------------------------

    EXPORT int wxSockAddress_GetType(wxSockAddress* self)
    {
        return static_cast<int>(self->Type());
    }

    EXPORT int wxSockAddress_GetAddressDataLen(wxSockAddress* self)
    {
        return self->GetAddressDataLen();
    }

    // -----------------------------------------------------------------------
    // wxIPaddress
    // -----------------------------------------------------------------------

    EXPORT wxString* wxIPaddress_OrigHostname(wxIPaddress* self)
    {
        return new wxString(self->OrigHostname());
    }

    // -----------------------------------------------------------------------
    // wxIPV4address
    // -----------------------------------------------------------------------

    EXPORT bool wxIPV4address_HostnameAddr(wxIPV4address* self, wxUint32 address)
    {
        return self->Hostname(static_cast<unsigned long>(address));
    }

    EXPORT bool wxIPV4address_BroadcastAddress(wxIPV4address* self)
    {
        return self->BroadcastAddress();
    }
#endif  // wxUSE_SOCKETS

// wxHTTP and wxFTP build on wxProtocol, whose Connect(wxSockAddress&) overload only exists when
// sockets are enabled. The guard therefore repeats the prerequisites.
#if wxUSE_SOCKETS && wxUSE_PROTOCOL
    // -----------------------------------------------------------------------
    // wxProtocol
    // -----------------------------------------------------------------------

    EXPORT void wxProtocol_Delete(wxProtocol* self)
    {
        delete self;
    }

    EXPORT bool wxProtocol_Reconnect(wxProtocol* self)
    {
        return self->Reconnect();
    }

    EXPORT bool wxProtocol_Connect(wxProtocol* self, wxString* host)
    {
        return self->Connect(*host);
    }

    EXPORT bool wxProtocol_ConnectAddr(wxProtocol* self, wxSockAddress* address, bool wait)
    {
        return self->Connect(*address, wait);
    }

    EXPORT int wxProtocol_ReadLine(wxProtocol* self, wxString* result)
    {
        wxString line;
        const wxProtocolError error = self->ReadLine(line);
        *result = line;
        return static_cast<int>(error);
    }

    EXPORT bool wxProtocol_Abort(wxProtocol* self)
    {
        return self->Abort();
    }

    EXPORT wxInputStream* wxProtocol_GetInputStream(wxProtocol* self, wxString* path)
    {
        return self->GetInputStream(*path);
    }

    EXPORT wxString* wxProtocol_GetContentType(wxProtocol* self)
    {
        return new wxString(self->GetContentType());
    }

    EXPORT int wxProtocol_GetError(wxProtocol* self)
    {
        return static_cast<int>(self->GetError());
    }

    EXPORT void wxProtocol_SetUser(wxProtocol* self, wxString* user)
    {
        self->SetUser(*user);
    }

    EXPORT void wxProtocol_SetPassword(wxProtocol* self, wxString* password)
    {
        self->SetPassword(*password);
    }

    EXPORT void wxProtocol_SetDefaultTimeout(wxProtocol* self, wxUint32 seconds)
    {
        self->SetDefaultTimeout(seconds);
    }

    EXPORT void wxProtocol_LogRequest(wxProtocol* self, wxString* text)
    {
        self->LogRequest(*text);
    }

    EXPORT void wxProtocol_LogResponse(wxProtocol* self, wxString* text)
    {
        self->LogResponse(*text);
    }
#endif  // wxUSE_SOCKETS && wxUSE_PROTOCOL

#if wxUSE_SOCKETS && wxUSE_PROTOCOL && wxUSE_PROTOCOL_HTTP
    // -----------------------------------------------------------------------
    // wxHTTP
    // -----------------------------------------------------------------------

    EXPORT wxHTTP* wxHTTP_Create()
    {
        return new wxHTTP();
    }

    EXPORT void wxHTTP_Delete(wxHTTP* self)
    {
        delete self;
    }

    EXPORT bool wxHTTP_Connect(wxHTTP* self, wxString* host)
    {
        return self->Connect(*host);
    }

    EXPORT bool wxHTTP_ConnectPort(wxHTTP* self, wxString* host, unsigned short port)
    {
        return self->Connect(*host, port);
    }

    EXPORT bool wxHTTP_ConnectAddr(wxHTTP* self, wxSockAddress* address, bool wait)
    {
    #if wxUSE_SOCKETS
        return self->Connect(*address, wait);
    #else
        wxUnusedVar(self);
        wxUnusedVar(address);
        wxUnusedVar(wait);
        return false;
    #endif
    }

    EXPORT bool wxHTTP_Abort(wxHTTP* self)
    {
        return self->Abort();
    }

    EXPORT wxInputStream* wxHTTP_GetInputStream(wxHTTP* self, wxString* path)
    {
        return self->GetInputStream(*path);
    }

    EXPORT wxString* wxHTTP_GetContentType(wxHTTP* self)
    {
        return new wxString(self->GetContentType());
    }

    EXPORT wxString* wxHTTP_GetHeader(wxHTTP* self, wxString* header)
    {
        return new wxString(self->GetHeader(*header));
    }

    EXPORT int wxHTTP_GetResponse(wxHTTP* self)
    {
        return self->GetResponse();
    }

    EXPORT void wxHTTP_SetMethod(wxHTTP* self, wxString* method)
    {
        self->SetMethod(*method);
    }

    EXPORT void wxHTTP_SetHeader(wxHTTP* self, wxString* header, wxString* header_data)
    {
        self->SetHeader(*header, *header_data);
    }

    EXPORT bool wxHTTP_SetPostText(wxHTTP* self, wxString* content_type, wxString* text)
    {
        return self->SetPostText(*content_type, *text);
    }

    EXPORT bool wxHTTP_SetPostBuffer(wxHTTP* self, wxString* content_type, wxMemoryBuffer* buffer)
    {
        return self->SetPostBuffer(*content_type, *buffer);
    }

    EXPORT void wxHTTP_SetProxyMode(wxHTTP* self, bool enable_proxy)
    {
        self->SetProxyMode(enable_proxy);
    }

    EXPORT wxString* wxHTTP_GetCookie(wxHTTP* self, wxString* cookie)
    {
        return new wxString(self->GetCookie(*cookie));
    }

    EXPORT bool wxHTTP_HasCookies(wxHTTP* self)
    {
        return self->HasCookies();
    }
#endif  // wxUSE_SOCKETS && wxUSE_PROTOCOL && wxUSE_PROTOCOL_HTTP

#if wxUSE_SOCKETS && wxUSE_PROTOCOL && wxUSE_PROTOCOL_FTP
    // -----------------------------------------------------------------------
    // wxFTP
    // -----------------------------------------------------------------------

    EXPORT wxFTP* wxFTP_Create()
    {
        return new wxFTP();
    }

    EXPORT void wxFTP_Delete(wxFTP* self)
    {
        delete self;
    }

    EXPORT bool wxFTP_Connect(wxFTP* self, wxString* host)
    {
        return self->Connect(*host);
    }

    EXPORT bool wxFTP_ConnectPort(wxFTP* self, wxString* host, unsigned short port)
    {
        return self->Connect(*host, port);
    }

    EXPORT bool wxFTP_ConnectAddr(wxFTP* self, wxSockAddress* address, bool wait)
    {
        return self->Connect(*address, wait);
    }

    EXPORT bool wxFTP_Close(wxFTP* self)
    {
        return self->Close();
    }

    EXPORT void wxFTP_SetPassive(wxFTP* self, bool passive)
    {
        self->SetPassive(passive);
    }

    EXPORT bool wxFTP_SetBinary(wxFTP* self)
    {
        return self->SetBinary();
    }

    EXPORT bool wxFTP_SetAscii(wxFTP* self)
    {
        return self->SetAscii();
    }

    EXPORT bool wxFTP_SetTransferMode(wxFTP* self, int mode)
    {
        return self->SetTransferMode(static_cast<wxFTP::TransferMode>(mode));
    }

    EXPORT wxString* wxFTP_GetContentType(wxFTP* self)
    {
        return new wxString(self->GetContentType());
    }

    EXPORT wxString* wxFTP_GetLastResult(wxFTP* self)
    {
        return new wxString(self->GetLastResult());
    }

    EXPORT int wxFTP_SendCommand(wxFTP* self, wxString* command)
    {
        return static_cast<int>(self->SendCommand(*command));
    }

    EXPORT bool wxFTP_CheckCommand(wxFTP* self, wxString* command, int expected_result)
    {
        return self->CheckCommand(*command, static_cast<char>(expected_result));
    }

    EXPORT bool wxFTP_ChDir(wxFTP* self, wxString* directory)
    {
        return self->ChDir(*directory);
    }

    EXPORT bool wxFTP_MkDir(wxFTP* self, wxString* directory)
    {
        return self->MkDir(*directory);
    }

    EXPORT bool wxFTP_RmDir(wxFTP* self, wxString* directory)
    {
        return self->RmDir(*directory);
    }

    EXPORT wxString* wxFTP_Pwd(wxFTP* self)
    {
        return new wxString(self->Pwd());
    }

    EXPORT bool wxFTP_Rename(wxFTP* self, wxString* source, wxString* destination)
    {
        return self->Rename(*source, *destination);
    }

    EXPORT bool wxFTP_RmFile(wxFTP* self, wxString* path)
    {
        return self->RmFile(*path);
    }

    EXPORT int wxFTP_GetFileSize(wxFTP* self, wxString* file_name)
    {
        return self->GetFileSize(*file_name);
    }

    EXPORT bool wxFTP_FileExists(wxFTP* self, wxString* file_name)
    {
        return self->FileExists(*file_name);
    }

    EXPORT bool wxFTP_Abort(wxFTP* self)
    {
        return self->Abort();
    }

    EXPORT wxInputStream* wxFTP_GetInputStream(wxFTP* self, wxString* path)
    {
        return self->GetInputStream(*path);
    }

    EXPORT wxOutputStream* wxFTP_GetOutputStream(wxFTP* self, wxString* path)
    {
        return self->GetOutputStream(*path);
    }

    EXPORT bool wxFTP_GetList(wxFTP* self, wxArrayString* files, wxString* wildcard, bool details)
    {
        return self->GetList(*files, *wildcard, details);
    }
#endif  // wxUSE_SOCKETS && wxUSE_PROTOCOL && wxUSE_PROTOCOL_FTP

// wxURL exposes wxProtocol and includes wx/protocol/protocol.h, so it depends on
// wxUSE_PROTOCOL as well as wxUSE_URL.
#if wxUSE_URL && wxUSE_PROTOCOL
    // -----------------------------------------------------------------------
    // wxURL
    // -----------------------------------------------------------------------

    EXPORT wxURL* wxURL_Create()
    {
        return new wxURL();
    }

    EXPORT wxURL* wxURL_CreateFromString(wxString* url)
    {
        return new wxURL(*url);
    }

    EXPORT void wxURL_Delete(wxURL* self)
    {
        delete self;
    }

    EXPORT wxProtocol* wxURL_GetProtocol(wxURL* self)
    {
        return &self->GetProtocol();
    }

    EXPORT int wxURL_GetError(wxURL* self)
    {
        return static_cast<int>(self->GetError());
    }

    EXPORT wxString* wxURL_GetURL(wxURL* self)
    {
        return new wxString(self->GetURL());
    }

    EXPORT int wxURL_SetURL(wxURL* self, wxString* url)
    {
        return static_cast<int>(self->SetURL(*url));
    }

    EXPORT bool wxURL_IsOk(wxURL* self)
    {
        return self->IsOk();
    }

    EXPORT wxInputStream* wxURL_GetInputStream(wxURL* self)
    {
        return self->GetInputStream();
    }

    EXPORT void wxURL_SetDefaultProxy(wxString* proxy_url)
    {
    #if wxUSE_PROTOCOL_HTTP
        wxURL::SetDefaultProxy(*proxy_url);
    #else
        wxUnusedVar(proxy_url);
    #endif
    }

    EXPORT void wxURL_SetProxy(wxURL* self, wxString* proxy_url)
    {
    #if wxUSE_PROTOCOL_HTTP
        self->SetProxy(*proxy_url);
    #else
        wxUnusedVar(self);
        wxUnusedVar(proxy_url);
    #endif
    }
#endif  // wxUSE_URL && wxUSE_PROTOCOL
}
