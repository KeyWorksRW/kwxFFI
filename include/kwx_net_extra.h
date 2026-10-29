#pragma once

// Base-utility socket, HTTP, FTP and URL wrappers.
//
// These classes are classified `base-utility` in `.private/coverage_expansion_inventory.md`
// and are therefore listed in `GuiExcludedClasses()` (`kwxgen/src/profile.cpp`), so the `gui`
// profile used by the Go and Julia bindings does not emit them.
//
// Only the methods that are missing from the existing blocks in `include/kwx_classes.h`,
// `include/kwx_classes_sync.h` and the definitions in `src/kwx_socket.cpp` /
// `src/kwx_sckaddr.cpp` are declared here. kwxgen merges repeated `TClassDef` blocks by class
// name, so each block below adds methods to the class instead of redefining it. wxProtocol,
// wxHTTP, wxFTP and wxURL had no wrapped methods at all before this header.
//
// The declarations are not guarded: every export exists on every platform. The implementations
// in `src/wx_net_extra.cpp` guard the bodies on the corresponding `wxUSE_*` feature instead,
// following the `src/wx_taskbarbutton.cpp` pattern.
//
// Strings are returned as `TClass(wxString)` (a `wxString*` the caller owns). Socket options are
// passed as `void*` plus an `int` byte length, matching the existing wxSocketBase block.
// `wxSocketBase::GetSocket()` returns `wxSOCKET_T`, which is `wxUIntPtr` on Windows, and
// `wxSockAddress`'s raw `sockaddr` accessor has no stable FFI spelling; both are skipped and
// recorded in `.private/deferred_i64.md`.

// ---------------------------------------------------------------------------
// wxSocketBase — methods missing from the block in include/kwx_classes_sync.h
// ---------------------------------------------------------------------------

// Options are the platform SO_* level/name values; `option_length` is the byte length of
// `option_value` on input and the returned length on output. Initialize() and Shutdown() are
// process-wide and are called automatically, so they are only needed when the first socket is
// created outside the main thread.
TClassDef(wxSocketBase) int wxSocketBase_GetTimeout(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_IsClosed(TSelf(wxSocketBase) pObject);
TUInt32 wxSocketBase_LastReadCount(TSelf(wxSocketBase) pObject);
TUInt32 wxSocketBase_LastWriteCount(TSelf(wxSocketBase) pObject);
TUInt32 wxSocketBase_GetLastIOSize(TSelf(wxSocketBase) pObject);
TUInt32 wxSocketBase_GetLastIOReadSize(TSelf(wxSocketBase) pObject);
TUInt32 wxSocketBase_GetLastIOWriteSize(TSelf(wxSocketBase) pObject);
void wxSocketBase_ShutdownOutput(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_GetOption(TSelf(wxSocketBase) pObject, int level, int option_name,
                             void* option_value, int* option_length);
TBool wxSocketBase_SetOption(TSelf(wxSocketBase) pObject, int level, int option_name,
                             void* option_value, int option_length);
TClass(wxEvtHandler) wxSocketBase_GetEventHandler(TSelf(wxSocketBase) pObject);
TBool wxSocketBase_Initialize();
void wxSocketBase_Shutdown();
TBool wxSocketBase_IsInitialized();

// ---------------------------------------------------------------------------
// wxSocketClient — method missing from the block in include/kwx_classes_sync.h
// ---------------------------------------------------------------------------

// Buffer sizes are applied with SO_RCVBUF / SO_SNDBUF before connecting; pass -1 to leave one
// of them unchanged.
TClassDef(wxSocketClient) void wxSocketClient_SetInitialSocketBuffers(TSelf(wxSocketClient) pObject,
                                                                      int receive_size,
                                                                      int send_size);

// ---------------------------------------------------------------------------
// wxSockAddress — methods missing from the block in include/kwx_classes_sync.h
// ---------------------------------------------------------------------------

// GetType() returns a wxSockAddress::Family value (0 = NONE, 1 = IPV4, 2 = IPV6, 3 = UNIX).
TClassDef(wxSockAddress) int wxSockAddress_GetType(TSelf(wxSockAddress) pObject);
int wxSockAddress_GetAddressDataLen(TSelf(wxSockAddress) pObject);

// ---------------------------------------------------------------------------
// wxIPaddress — method missing from the block in include/kwx_classes_sync.h
// ---------------------------------------------------------------------------

TClassDef(wxIPaddress) TClass(wxString) wxIPaddress_OrigHostname(TSelf(wxIPaddress) pObject);

// ---------------------------------------------------------------------------
// wxIPV4address — methods missing from the block in include/kwx_classes_sync.h
// ---------------------------------------------------------------------------

// BroadcastAddress() sets the address to the IPv4 broadcast address of the local network.
// HostnameAddr() sets the address from a packed 32-bit IPv4 value (network byte order, as
// returned by inet_addr()); the wxWidgets parameter is `unsigned long` and is narrowed to
// TUInt32 because the packed address is 32 bits wide, so no value is lost.
TClassDef(wxIPV4address) TBool
    wxIPV4address_HostnameAddr(TSelf(wxIPV4address) pObject, TUInt32 address);
TBool wxIPV4address_BroadcastAddress(TSelf(wxIPV4address) pObject);

// ---------------------------------------------------------------------------
// wxProtocol
// ---------------------------------------------------------------------------

// wxProtocol is abstract: there is no constructor wrapper, but every derived protocol handle
// can be used through this surface. ReadLine() fills `result` and returns a wxProtocolError
// value. The logger surface is not wrapped (`wxProtocolLog` has no stable FFI spelling).
TClassDef(wxProtocol) void wxProtocol_Delete(TSelf(wxProtocol) pObject);
TBool wxProtocol_Reconnect(TSelf(wxProtocol) pObject);
TBool wxProtocol_Connect(TSelf(wxProtocol) pObject, TClass(wxString) host);
TBool wxProtocol_ConnectAddr(TSelf(wxProtocol) pObject, TClass(wxSockAddress) address, TBool wait);
int wxProtocol_ReadLine(TSelf(wxProtocol) pObject, TClass(wxString) result);
TBool wxProtocol_Abort(TSelf(wxProtocol) pObject);
TClass(wxInputStream) wxProtocol_GetInputStream(TSelf(wxProtocol) pObject, TClass(wxString) path);
TClass(wxString) wxProtocol_GetContentType(TSelf(wxProtocol) pObject);
int wxProtocol_GetError(TSelf(wxProtocol) pObject);
void wxProtocol_SetUser(TSelf(wxProtocol) pObject, TClass(wxString) user);
void wxProtocol_SetPassword(TSelf(wxProtocol) pObject, TClass(wxString) password);
void wxProtocol_SetDefaultTimeout(TSelf(wxProtocol) pObject, TUInt32 seconds);
void wxProtocol_LogRequest(TSelf(wxProtocol) pObject, TClass(wxString) text);
void wxProtocol_LogResponse(TSelf(wxProtocol) pObject, TClass(wxString) text);

// ---------------------------------------------------------------------------
// wxHTTP
// ---------------------------------------------------------------------------

// ConnectPort() is the (host, port) overload; Connect() uses the default port. SetPostText()
// uses the default UTF-8 conversion. SetPostBuffer() takes a wxMemoryBuffer handle.
TClassDef(wxHTTP) TClass(wxHTTP) wxHTTP_Create();
void wxHTTP_Delete(TSelf(wxHTTP) pObject);
TBool wxHTTP_Connect(TSelf(wxHTTP) pObject, TClass(wxString) host);
TBool wxHTTP_ConnectPort(TSelf(wxHTTP) pObject, TClass(wxString) host, unsigned short port);
TBool wxHTTP_ConnectAddr(TSelf(wxHTTP) pObject, TClass(wxSockAddress) address, TBool wait);
TBool wxHTTP_Abort(TSelf(wxHTTP) pObject);
TClass(wxInputStream) wxHTTP_GetInputStream(TSelf(wxHTTP) pObject, TClass(wxString) path);
TClass(wxString) wxHTTP_GetContentType(TSelf(wxHTTP) pObject);
TClass(wxString) wxHTTP_GetHeader(TSelf(wxHTTP) pObject, TClass(wxString) header);
int wxHTTP_GetResponse(TSelf(wxHTTP) pObject);
void wxHTTP_SetMethod(TSelf(wxHTTP) pObject, TClass(wxString) method);
void wxHTTP_SetHeader(TSelf(wxHTTP) pObject, TClass(wxString) header, TClass(wxString) header_data);
TBool wxHTTP_SetPostText(TSelf(wxHTTP) pObject, TClass(wxString) content_type,
                         TClass(wxString) text);
TBool wxHTTP_SetPostBuffer(TSelf(wxHTTP) pObject, TClass(wxString) content_type,
                           TClass(wxMemoryBuffer) buffer);
void wxHTTP_SetProxyMode(TSelf(wxHTTP) pObject, TBool enable_proxy);
TClass(wxString) wxHTTP_GetCookie(TSelf(wxHTTP) pObject, TClass(wxString) cookie);
TBool wxHTTP_HasCookies(TSelf(wxHTTP) pObject);

// ---------------------------------------------------------------------------
// wxFTP
// ---------------------------------------------------------------------------

// Transfer modes are the wxFTP::TransferMode values (0 = NONE, 1 = ASCII, 2 = BINARY).
// SendCommand() returns the first character of the server reply or 0 on failure. GetList()
// fills the caller's wxArrayString with one entry per line; `details` selects the raw
// server-dependent form.
TClassDef(wxFTP) TClass(wxFTP) wxFTP_Create();
void wxFTP_Delete(TSelf(wxFTP) pObject);
TBool wxFTP_Connect(TSelf(wxFTP) pObject, TClass(wxString) host);
TBool wxFTP_ConnectPort(TSelf(wxFTP) pObject, TClass(wxString) host, unsigned short port);
TBool wxFTP_ConnectAddr(TSelf(wxFTP) pObject, TClass(wxSockAddress) address, TBool wait);
TBool wxFTP_Close(TSelf(wxFTP) pObject);
void wxFTP_SetPassive(TSelf(wxFTP) pObject, TBool passive);
TBool wxFTP_SetBinary(TSelf(wxFTP) pObject);
TBool wxFTP_SetAscii(TSelf(wxFTP) pObject);
TBool wxFTP_SetTransferMode(TSelf(wxFTP) pObject, int mode);
TClass(wxString) wxFTP_GetContentType(TSelf(wxFTP) pObject);
TClass(wxString) wxFTP_GetLastResult(TSelf(wxFTP) pObject);
int wxFTP_SendCommand(TSelf(wxFTP) pObject, TClass(wxString) command);
TBool wxFTP_CheckCommand(TSelf(wxFTP) pObject, TClass(wxString) command, int expected_result);
TBool wxFTP_ChDir(TSelf(wxFTP) pObject, TClass(wxString) directory);
TBool wxFTP_MkDir(TSelf(wxFTP) pObject, TClass(wxString) directory);
TBool wxFTP_RmDir(TSelf(wxFTP) pObject, TClass(wxString) directory);
TClass(wxString) wxFTP_Pwd(TSelf(wxFTP) pObject);
TBool wxFTP_Rename(TSelf(wxFTP) pObject, TClass(wxString) source, TClass(wxString) destination);
TBool wxFTP_RmFile(TSelf(wxFTP) pObject, TClass(wxString) path);
int wxFTP_GetFileSize(TSelf(wxFTP) pObject, TClass(wxString) file_name);
TBool wxFTP_FileExists(TSelf(wxFTP) pObject, TClass(wxString) file_name);
TBool wxFTP_Abort(TSelf(wxFTP) pObject);
TClass(wxInputStream) wxFTP_GetInputStream(TSelf(wxFTP) pObject, TClass(wxString) path);
TClass(wxOutputStream) wxFTP_GetOutputStream(TSelf(wxFTP) pObject, TClass(wxString) path);
TBool wxFTP_GetList(TSelf(wxFTP) pObject, TClass(wxArrayString) files, TClass(wxString) wildcard,
                    TBool details);

// ---------------------------------------------------------------------------
// wxURL
// ---------------------------------------------------------------------------

// wxURLError values are returned as `int` (0 = wxURL_NOERR). The protocol handle returned by
// GetProtocol() is owned by the wxURL object. The proxy helpers require wxUSE_PROTOCOL_HTTP;
// the implementation makes them inert when HTTP is compiled out.
TClassDef(wxURL) TClass(wxURL) wxURL_Create();
TClass(wxURL) wxURL_CreateFromString(TClass(wxString) url);
void wxURL_Delete(TSelf(wxURL) pObject);
TClass(wxProtocol) wxURL_GetProtocol(TSelf(wxURL) pObject);
int wxURL_GetError(TSelf(wxURL) pObject);
TClass(wxString) wxURL_GetURL(TSelf(wxURL) pObject);
int wxURL_SetURL(TSelf(wxURL) pObject, TClass(wxString) url);
TBool wxURL_IsOk(TSelf(wxURL) pObject);
TClass(wxInputStream) wxURL_GetInputStream(TSelf(wxURL) pObject);
void wxURL_SetDefaultProxy(TClass(wxString) proxy_url);
void wxURL_SetProxy(TSelf(wxURL) pObject, TClass(wxString) proxy_url);
