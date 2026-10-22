#pragma once

// Core infrastructure classes: platform information, secret storage, string
// conversion, XML nodes, virtual file systems, persistence, dial-up management,
// event filtering, and icon locations.

// ---------------------------------------------------------------------------
// wxPlatformInfo
// ---------------------------------------------------------------------------

TClassDef(wxPlatformInfo) TClass(wxPlatformInfo) wxPlatformInfo_Create();
void wxPlatformInfo_Delete(TSelf(wxPlatformInfo) pObject);
TClass(wxPlatformInfo) wxPlatformInfo_Get();
TClass(wxPlatformInfo) wxPlatformInfo_GetCurrent();
int wxPlatformInfo_GetOperatingSystemIdFromName(TClass(wxString) name);
int wxPlatformInfo_GetPortIdFromName(TClass(wxString) port_name);
int wxPlatformInfo_GetBitnessFromName(TClass(wxString) bitness);
int wxPlatformInfo_GetEndiannessFromName(TClass(wxString) endianness);
TClass(wxString) wxPlatformInfo_GetOperatingSystemFamilyNameFromId(int os_id);
TClass(wxString) wxPlatformInfo_GetOperatingSystemIdNameFromId(int os_id);
TClass(wxString) wxPlatformInfo_GetPortIdNameFromValues(int port_id, TBool using_universal);
TClass(wxString) wxPlatformInfo_GetPortIdShortNameFromValues(int port_id, TBool using_universal);
TClass(wxString) wxPlatformInfo_GetBitnessNameFromValue(int bitness);
TClass(wxString) wxPlatformInfo_GetEndiannessNameFromValue(int endianness);
TClass(wxString) wxPlatformInfo_GetOperatingSystemDirectory();
int wxPlatformInfo_GetOSMajorVersion(TSelf(wxPlatformInfo) pObject);
int wxPlatformInfo_GetOSMinorVersion(TSelf(wxPlatformInfo) pObject);
int wxPlatformInfo_GetOSMicroVersion(TSelf(wxPlatformInfo) pObject);
int wxPlatformInfo_GetToolkitMajorVersion(TSelf(wxPlatformInfo) pObject);
int wxPlatformInfo_GetToolkitMinorVersion(TSelf(wxPlatformInfo) pObject);
int wxPlatformInfo_GetToolkitMicroVersion(TSelf(wxPlatformInfo) pObject);
int wxPlatformInfo_GetOperatingSystemId(TSelf(wxPlatformInfo) pObject);
int wxPlatformInfo_GetPortId(TSelf(wxPlatformInfo) pObject);
int wxPlatformInfo_GetBitness(TSelf(wxPlatformInfo) pObject);
int wxPlatformInfo_GetEndianness(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetPlatformDescription(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetOperatingSystemFamilyName(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetOperatingSystemIdName(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetPortIdName(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetPortIdShortName(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetBitnessName(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetEndiannessName(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetCpuArchitectureName(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetNativeCpuArchitectureName(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetOperatingSystemDescription(TSelf(wxPlatformInfo) pObject);
TClass(wxString) wxPlatformInfo_GetDesktopEnvironment(TSelf(wxPlatformInfo) pObject);
TBool wxPlatformInfo_IsOk(TSelf(wxPlatformInfo) pObject);
TBool wxPlatformInfo_IsUsingUniversalWidgets(TSelf(wxPlatformInfo) pObject);
void wxPlatformInfo_SetOSVersion(TSelf(wxPlatformInfo) pObject, int major, int minor, int micro);
void wxPlatformInfo_SetToolkitVersion(TSelf(wxPlatformInfo) pObject, int major, int minor,
                                      int micro);
void wxPlatformInfo_SetOperatingSystemId(TSelf(wxPlatformInfo) pObject, int os_id);
void wxPlatformInfo_SetOperatingSystemDescription(TSelf(wxPlatformInfo) pObject,
                                                  TClass(wxString) description);
void wxPlatformInfo_SetPortId(TSelf(wxPlatformInfo) pObject, int port_id);
void wxPlatformInfo_SetBitness(TSelf(wxPlatformInfo) pObject, int bitness);
void wxPlatformInfo_SetEndianness(TSelf(wxPlatformInfo) pObject, int endianness);
void wxPlatformInfo_SetCpuArchitectureName(TSelf(wxPlatformInfo) pObject,
                                           TClass(wxString) cpu_architecture);
void wxPlatformInfo_SetNativeCpuArchitectureName(TSelf(wxPlatformInfo) pObject,
                                                 TClass(wxString) cpu_architecture);
void wxPlatformInfo_SetDesktopEnvironment(TSelf(wxPlatformInfo) pObject,
                                          TClass(wxString) desktop_environment);

// ---------------------------------------------------------------------------
// wxSecretValue / wxSecretStore
// ---------------------------------------------------------------------------

TClassDef(wxSecretValue) TClass(wxSecretValue) wxSecretValue_Create(TClass(wxString) secret);
TClass(wxSecretValue) wxSecretValue_CreateDefault();
void wxSecretValue_Delete(TSelf(wxSecretValue) pObject);
TBool wxSecretValue_IsOk(TSelf(wxSecretValue) pObject);
TClass(wxString) wxSecretValue_GetAsString(TSelf(wxSecretValue) pObject);

// wxSecretStore_DeleteSecret deletes a stored secret; wxSecretStore_Delete
// destroys the store itself.
TClassDef(wxSecretStore) TClass(wxSecretStore) wxSecretStore_GetDefault();
void wxSecretStore_Delete(TSelf(wxSecretStore) pObject);
TBool wxSecretStore_IsOk(TSelf(wxSecretStore) pObject);
TBool wxSecretStore_IsOkWithError(TSelf(wxSecretStore) pObject, TClass(wxString) error_message);
TBool wxSecretStore_Save(TSelf(wxSecretStore) pObject, TClass(wxString) service,
                         TClass(wxString) username, TClass(wxSecretValue) password);
TBool wxSecretStore_Load(TSelf(wxSecretStore) pObject, TClass(wxString) service,
                         TClass(wxString) username, TClass(wxSecretValue) password);
TBool wxSecretStore_DeleteSecret(TSelf(wxSecretStore) pObject, TClass(wxString) service);

// ---------------------------------------------------------------------------
// wxMBConv
// ---------------------------------------------------------------------------

// MB2WC writes wchar_t data to output; WC2MB reads wchar_t data from input.
TClassDef(wxMBConv) TClass(wxMBConv) wxMBConvUTF8_Create(int options);
void wxMBConv_Delete(TSelf(wxMBConv) pObject);
int wxMBConv_GetMaxCharLen(TSelf(wxMBConv) pObject);
int wxMBConv_MB2WC(TSelf(wxMBConv) pObject, void* output, TString input, int output_size);
int wxMBConv_WC2MB(TSelf(wxMBConv) pObject, TStringOut output, void* input, int output_size);

// ---------------------------------------------------------------------------
// wxXmlAttribute / wxXmlNode
// ---------------------------------------------------------------------------

TClassDef(wxXmlAttribute) TClass(wxXmlAttribute)
    wxXmlAttribute_Create(TClass(wxString) name, TClass(wxString) value);
void wxXmlAttribute_Delete(TSelf(wxXmlAttribute) pObject);
TClass(wxString) wxXmlAttribute_GetName(TSelf(wxXmlAttribute) pObject);
TClass(wxString) wxXmlAttribute_GetValue(TSelf(wxXmlAttribute) pObject);
TClass(wxXmlAttribute) wxXmlAttribute_GetNext(TSelf(wxXmlAttribute) pObject);
void wxXmlAttribute_SetName(TSelf(wxXmlAttribute) pObject, TClass(wxString) name);
void wxXmlAttribute_SetValue(TSelf(wxXmlAttribute) pObject, TClass(wxString) value);
void wxXmlAttribute_SetNext(TSelf(wxXmlAttribute) pObject, TClass(wxXmlAttribute) next_attribute);

TClassDef(wxXmlNode) TClass(wxXmlNode) wxXmlNode_Create(int node_type, TClass(wxString) name,
                                                        TClass(wxString) content, int line_number);
void wxXmlNode_Delete(TSelf(wxXmlNode) pObject);
int wxXmlNode_GetType(TSelf(wxXmlNode) pObject);
void wxXmlNode_SetType(TSelf(wxXmlNode) pObject, int node_type);
TClass(wxString) wxXmlNode_GetName(TSelf(wxXmlNode) pObject);
void wxXmlNode_SetName(TSelf(wxXmlNode) pObject, TClass(wxString) name);
TClass(wxString) wxXmlNode_GetContent(TSelf(wxXmlNode) pObject);
TClass(wxString) wxXmlNode_GetNodeContent(TSelf(wxXmlNode) pObject);
void wxXmlNode_SetContent(TSelf(wxXmlNode) pObject, TClass(wxString) content);
TBool wxXmlNode_GetAttribute(TSelf(wxXmlNode) pObject, TClass(wxString) attribute_name,
                             TClass(wxString) value);
TClass(wxString)
    wxXmlNode_GetAttributeWithDefault(TSelf(wxXmlNode) pObject, TClass(wxString) attribute_name,
                                      TClass(wxString) default_value);
TBool wxXmlNode_HasAttribute(TSelf(wxXmlNode) pObject, TClass(wxString) attribute_name);
void wxXmlNode_AddAttribute(TSelf(wxXmlNode) pObject, TClass(wxString) name,
                            TClass(wxString) value);
void wxXmlNode_AddAttributeObject(TSelf(wxXmlNode) pObject, TClass(wxXmlAttribute) attribute);
TBool wxXmlNode_DeleteAttribute(TSelf(wxXmlNode) pObject, TClass(wxString) attribute_name);
TClass(wxXmlAttribute) wxXmlNode_GetAttributes(TSelf(wxXmlNode) pObject);
TClass(wxXmlNode) wxXmlNode_GetChildren(TSelf(wxXmlNode) pObject);
void wxXmlNode_AddChild(TSelf(wxXmlNode) pObject, TClass(wxXmlNode) child);
TBool wxXmlNode_InsertChild(TSelf(wxXmlNode) pObject, TClass(wxXmlNode) child,
                            TClass(wxXmlNode) following_node);
TBool wxXmlNode_InsertChildAfter(TSelf(wxXmlNode) pObject, TClass(wxXmlNode) child,
                                 TClass(wxXmlNode) preceding_node);
TBool wxXmlNode_RemoveChild(TSelf(wxXmlNode) pObject, TClass(wxXmlNode) child);
TClass(wxXmlNode) wxXmlNode_GetNext(TSelf(wxXmlNode) pObject);
void wxXmlNode_SetNext(TSelf(wxXmlNode) pObject, TClass(wxXmlNode) next_node);
TClass(wxXmlNode) wxXmlNode_GetParent(TSelf(wxXmlNode) pObject);
void wxXmlNode_SetParent(TSelf(wxXmlNode) pObject, TClass(wxXmlNode) parent);
int wxXmlNode_GetLineNumber(TSelf(wxXmlNode) pObject);
TBool wxXmlNode_GetNoConversion(TSelf(wxXmlNode) pObject);
void wxXmlNode_SetNoConversion(TSelf(wxXmlNode) pObject, TBool no_conversion);

// ---------------------------------------------------------------------------
// wxFSFile / wxFileSystem
// ---------------------------------------------------------------------------

// URLToFileName and FileNameToURL exchange wxFileName objects with the caller
// as plain strings, because wxFileName has no other FFI representation.
TClassDefExtend(wxFSFile, wxObject) void wxFSFile_Delete(TSelf(wxFSFile) pObject);
TClass(wxInputStream) wxFSFile_GetStream(TSelf(wxFSFile) pObject);
TClass(wxInputStream) wxFSFile_DetachStream(TSelf(wxFSFile) pObject);
TClass(wxString) wxFSFile_GetLocation(TSelf(wxFSFile) pObject);
TClass(wxString) wxFSFile_GetMimeType(TSelf(wxFSFile) pObject);
TClass(wxString) wxFSFile_GetAnchor(TSelf(wxFSFile) pObject);
TClass(wxDateTime) wxFSFile_GetModificationTime(TSelf(wxFSFile) pObject);

TClassDefExtend(wxFileSystem, wxObject) TClass(wxFileSystem) wxFileSystem_Create();
void wxFileSystem_Delete(TSelf(wxFileSystem) pObject);
void wxFileSystem_ChangePathTo(TSelf(wxFileSystem) pObject, TClass(wxString) location,
                               TBool is_dir);
TClass(wxString) wxFileSystem_GetPath(TSelf(wxFileSystem) pObject);
TClass(wxFSFile)
    wxFileSystem_OpenFile(TSelf(wxFileSystem) pObject, TClass(wxString) location, int flags);
TClass(wxString)
    wxFileSystem_FindFirst(TSelf(wxFileSystem) pObject, TClass(wxString) spec, int flags);
TClass(wxString) wxFileSystem_FindNext(TSelf(wxFileSystem) pObject);
TClass(wxString)
    wxFileSystem_FileNameToURL(TSelf(wxFileSystem) pObject, TClass(wxString) file_name);
TClass(wxString) wxFileSystem_URLToFileName(TSelf(wxFileSystem) pObject, TClass(wxString) url);

// ---------------------------------------------------------------------------
// wxPersistenceManager / wxPersistentObject / wxPersistentWindow
// ---------------------------------------------------------------------------

// Get returns the global manager and must not be deleted by the caller.
TClassDef(wxPersistenceManager) TClass(wxPersistenceManager) wxPersistenceManager_Get();
void wxPersistenceManager_Set(TSelf(wxPersistenceManager) pObject,
                              TClass(wxPersistenceManager) manager);
TClass(wxPersistentObject)
    wxPersistenceManager_Register(TSelf(wxPersistenceManager) pObject, void* object,
                                  TClass(wxPersistentObject) persistent_object);
TClass(wxPersistentObject)
    wxPersistenceManager_Find(TSelf(wxPersistenceManager) pObject, void* object);
void wxPersistenceManager_Unregister(TSelf(wxPersistenceManager) pObject, void* object);
void wxPersistenceManager_Save(TSelf(wxPersistenceManager) pObject, void* object);
TBool wxPersistenceManager_Restore(TSelf(wxPersistenceManager) pObject, void* object);
void wxPersistenceManager_SaveAndUnregister(TSelf(wxPersistenceManager) pObject, void* object);
TBool wxPersistenceManager_RegisterAndRestore(TSelf(wxPersistenceManager) pObject, void* object,
                                              TClass(wxPersistentObject) persistent_object);
void wxPersistenceManager_DisableSaving(TSelf(wxPersistenceManager) pObject);
void wxPersistenceManager_DisableRestoring(TSelf(wxPersistenceManager) pObject);

// wxPersistentObject is abstract; instances are obtained from
// wxPersistenceManager_Find.
TClassDef(wxPersistentObject) TClass(wxString)
    wxPersistentObject_GetName(TSelf(wxPersistentObject) pObject);
TClass(wxString) wxPersistentObject_GetKind(TSelf(wxPersistentObject) pObject);
void* wxPersistentObject_GetObject(TSelf(wxPersistentObject) pObject);
void wxPersistentObject_Save(TSelf(wxPersistentObject) pObject);
TBool wxPersistentObject_Restore(TSelf(wxPersistentObject) pObject);

// wxPersistentWindow is a template class, so only its non-template base is
// reachable from the FFI; the class is declared to keep the model complete.
TClassDefExtend(wxPersistentWindow, wxPersistentObject)

    // ---------------------------------------------------------------------------
    // wxDialUpManager / wxDialUpEvent
    // ---------------------------------------------------------------------------

    TClassDef(wxDialUpManager) TClass(wxDialUpManager) wxDialUpManager_Create();
void wxDialUpManager_Delete(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_IsOk(TSelf(wxDialUpManager) pObject);
TArrayLen wxDialUpManager_GetISPNames(TSelf(wxDialUpManager) pObject, TArrayStringOutVoid names);
TBool wxDialUpManager_Dial(TSelf(wxDialUpManager) pObject, TClass(wxString) isp_name,
                           TClass(wxString) username, TClass(wxString) password, TBool async);
TBool wxDialUpManager_IsDialing(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_CancelDialing(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_HangUp(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_IsAlwaysOnline(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_IsOnline(TSelf(wxDialUpManager) pObject);
void wxDialUpManager_SetOnlineStatus(TSelf(wxDialUpManager) pObject, TBool is_online);
TBool wxDialUpManager_EnableAutoCheckOnlineStatus(TSelf(wxDialUpManager) pObject, int seconds);
void wxDialUpManager_DisableAutoCheckOnlineStatus(TSelf(wxDialUpManager) pObject);
void wxDialUpManager_SetWellKnownHost(TSelf(wxDialUpManager) pObject, TClass(wxString) host_name,
                                      int port_number);
void wxDialUpManager_SetConnectCommand(TSelf(wxDialUpManager) pObject,
                                       TClass(wxString) dial_command,
                                       TClass(wxString) hangup_command);

TClassDefExtend(wxDialUpEvent, wxEvent) TBool
    wxDialUpEvent_IsConnectedEvent(TSelf(wxDialUpEvent) pObject);
TBool wxDialUpEvent_IsOwnEvent(TSelf(wxDialUpEvent) pObject);

// ---------------------------------------------------------------------------
// wxEventFilter / wxEventBlocker / wxEvtHandler filters
// ---------------------------------------------------------------------------

// wxEventFilter_Create returns a kwxEventFilter (see kwx_helper_eventfilter.h)
// that forwards FilterEvent to pFunction.
TClassDef(wxEventFilter) TClass(wxEventFilter) wxEventFilter_Create(void* pObject, void* pFunction);
void wxEventFilter_Delete(TSelf(wxEventFilter) pObject);

TClassDefExtend(wxEventBlocker, wxEvtHandler) TClass(wxEventBlocker)
    wxEventBlocker_Create(TClass(wxWindow) window, int event_type);
void wxEventBlocker_Delete(TSelf(wxEventBlocker) pObject);
void wxEventBlocker_Block(TSelf(wxEventBlocker) pObject, int event_type);

TClassDefExtend(wxEvtHandler, wxObject) void wxEvtHandler_AddFilter(TClass(wxEventFilter) filter);
void wxEvtHandler_RemoveFilter(TClass(wxEventFilter) filter);

// ---------------------------------------------------------------------------
// wxIconLocation
// ---------------------------------------------------------------------------

TClassDef(wxIconLocation) TClass(wxIconLocation)
    wxIconLocation_Create(TClass(wxString) file_name, int index);
void wxIconLocation_Delete(TSelf(wxIconLocation) pObject);
TBool wxIconLocation_IsOk(TSelf(wxIconLocation) pObject);
TClass(wxString) wxIconLocation_GetFileName(TSelf(wxIconLocation) pObject);
void wxIconLocation_SetFileName(TSelf(wxIconLocation) pObject, TClass(wxString) file_name);

// ---------------------------------------------------------------------------
// wxEventFilter return values (wxEventFilter::Event_Skip, Event_Ignore,
// Event_Processed) are fixed by wxWidgets and are exported as plain integers.
