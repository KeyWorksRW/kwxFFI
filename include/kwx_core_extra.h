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
// as plain strings. The wxFileName class itself is exported below as an opaque
// handle class; these two functions are kept for backward compatibility.
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
// wxFileName
// ---------------------------------------------------------------------------
//
// Path format values (wxPathFormat): 0 = native, 1 = Unix, 2 = Mac,
// 3 = DOS/Windows, 5 = VMS.
//
// GetPath flags: 0x0001 = include volume, 0x0002 = trailing separator.
// Normalize flags: 0x0001 = env vars, 0x0002 = dots, 0x0004 = tilde,
// 0x0008 = case, 0x0010 = absolute, 0x0020 = long, 0x0040 = shortcut.
// Exists flags: 0x0001 = regular file, 0x0002 = directory, 0x0008 = device,
// 0x0010 = FIFO, 0x0020 = socket, 0x1000 = don't follow links,
// 0x1004 = symlink, 0x1FFF = anything.
//
// Optional string parameters accept null, which is treated as an empty string.

TClassDef(wxFileName) TClass(wxFileName) wxFileName_Create();
TClass(wxFileName) wxFileName_CreateFromPath(TClass(wxString) full_path, int format);
TClass(wxFileName)
    wxFileName_CreateWithName(TClass(wxString) path, TClass(wxString) name, int format);
TClass(wxFileName) wxFileName_CreateWithExt(TClass(wxString) path, TClass(wxString) name,
                                            TClass(wxString) ext, int format);
TClass(wxFileName) wxFileName_CreateFull(TClass(wxString) volume, TClass(wxString) path,
                                         TClass(wxString) name, TClass(wxString) ext, int format);
void wxFileName_Delete(TSelf(wxFileName) pObject);

// Static pseudo-constructors - the returned object is owned by the caller.
TClass(wxFileName) wxFileName_DirName(TClass(wxString) dir, int format);
TClass(wxFileName) wxFileName_FileName(TClass(wxString) file, int format);
TClass(wxFileName) wxFileName_URLToFileName(TClass(wxString) url);

// Components.
TClass(wxString) wxFileName_GetFullPath(TSelf(wxFileName) pObject, int format);
TClass(wxString) wxFileName_GetPath(TSelf(wxFileName) pObject, int flags, int format);
TClass(wxString) wxFileName_GetPathWithSep(TSelf(wxFileName) pObject, int format);
TClass(wxString) wxFileName_GetFullName(TSelf(wxFileName) pObject);
TClass(wxString) wxFileName_GetName(TSelf(wxFileName) pObject);
TClass(wxString) wxFileName_GetExt(TSelf(wxFileName) pObject);
TClass(wxString) wxFileName_GetVolume(TSelf(wxFileName) pObject);
size_t wxFileName_GetDirCount(TSelf(wxFileName) pObject);
TArrayLen wxFileName_GetDirs(TSelf(wxFileName) pObject, TArrayStringOutVoid dirs);
TBool wxFileName_HasName(TSelf(wxFileName) pObject);
TBool wxFileName_HasExt(TSelf(wxFileName) pObject);
TBool wxFileName_HasVolume(TSelf(wxFileName) pObject);

void wxFileName_SetPath(TSelf(wxFileName) pObject, TClass(wxString) path, int format);
void wxFileName_SetName(TSelf(wxFileName) pObject, TClass(wxString) name);
void wxFileName_SetFullName(TSelf(wxFileName) pObject, TClass(wxString) full_name);
void wxFileName_SetExt(TSelf(wxFileName) pObject, TClass(wxString) ext);
void wxFileName_SetEmptyExt(TSelf(wxFileName) pObject);
void wxFileName_ClearExt(TSelf(wxFileName) pObject);
void wxFileName_SetVolume(TSelf(wxFileName) pObject, TClass(wxString) volume);
void wxFileName_Assign(TSelf(wxFileName) pObject, TClass(wxString) full_path, int format);
void wxFileName_AssignDir(TSelf(wxFileName) pObject, TClass(wxString) dir, int format);
void wxFileName_AssignCwd(TSelf(wxFileName) pObject, TClass(wxString) volume);
void wxFileName_AssignHomeDir(TSelf(wxFileName) pObject);
void wxFileName_Clear(TSelf(wxFileName) pObject);

// Directory components of the path.
TBool wxFileName_AppendDir(TSelf(wxFileName) pObject, TClass(wxString) dir);
void wxFileName_PrependDir(TSelf(wxFileName) pObject, TClass(wxString) dir);
TBool wxFileName_InsertDir(TSelf(wxFileName) pObject, size_t before, TClass(wxString) dir);
void wxFileName_RemoveDir(TSelf(wxFileName) pObject, size_t position);
void wxFileName_RemoveLastDir(TSelf(wxFileName) pObject);

// Path manipulation.
TBool wxFileName_Normalize(TSelf(wxFileName) pObject, int flags, TClass(wxString) cwd, int format);
TBool wxFileName_MakeAbsolute(TSelf(wxFileName) pObject, TClass(wxString) cwd, int format);
TBool wxFileName_MakeRelativeTo(TSelf(wxFileName) pObject, TClass(wxString) path_base, int format);
TClass(wxString)
    wxFileName_GetAbsolutePath(TSelf(wxFileName) pObject, TClass(wxString) cwd, int format);
TBool wxFileName_ReplaceEnvVariable(TSelf(wxFileName) pObject, TClass(wxString) env_name,
                                    TClass(wxString) replacement_format, int format);
TBool wxFileName_ReplaceHomeDir(TSelf(wxFileName) pObject, int format);

// Tests, comparisons and file system operations.
TBool wxFileName_IsOk(TSelf(wxFileName) pObject);
TBool wxFileName_IsDir(TSelf(wxFileName) pObject);
TBool wxFileName_IsAbsolute(TSelf(wxFileName) pObject, int format);
TBool wxFileName_IsRelative(TSelf(wxFileName) pObject, int format);
TBool wxFileName_FileExists(TSelf(wxFileName) pObject);
TBool wxFileName_DirExists(TSelf(wxFileName) pObject);
TBool wxFileName_Exists(TSelf(wxFileName) pObject, int flags);
TBool wxFileName_IsFileReadable(TSelf(wxFileName) pObject);
TBool wxFileName_IsFileWritable(TSelf(wxFileName) pObject);
TBool wxFileName_IsFileExecutable(TSelf(wxFileName) pObject);
TBool wxFileName_IsDirReadable(TSelf(wxFileName) pObject);
TBool wxFileName_IsDirWritable(TSelf(wxFileName) pObject);
TBool wxFileName_SameAs(TSelf(wxFileName) pObject, TClass(wxFileName) other, int format);
TBool wxFileName_ShouldFollowLink(TSelf(wxFileName) pObject);
void wxFileName_DontFollowLink(TSelf(wxFileName) pObject);
TClass(wxFileName) wxFileName_ResolveLink(TSelf(wxFileName) pObject);
TBool wxFileName_Mkdir(TSelf(wxFileName) pObject, int perm, int flags);
TBool wxFileName_Rmdir(TSelf(wxFileName) pObject, int flags);
TBool wxFileName_SetPermissions(TSelf(wxFileName) pObject, int permissions);
TBool wxFileName_Touch(TSelf(wxFileName) pObject);
TBool wxFileName_GetTimes(TSelf(wxFileName) pObject, TClass(wxDateTime) access_time,
                          TClass(wxDateTime) mod_time, TClass(wxDateTime) create_time);
TClass(wxDateTime) wxFileName_GetModificationTime(TSelf(wxFileName) pObject);
// Returns the file size in bytes, or -1.0 if it cannot be determined.
double wxFileName_GetSize(TSelf(wxFileName) pObject);
TClass(wxString)
    wxFileName_GetHumanReadableSize(TSelf(wxFileName) pObject, TClass(wxString) fail_message,
                                    int precision, int convention);
TClass(wxString) wxFileName_FileNameToURL(TSelf(wxFileName) pObject);

// Static helpers that operate on a path string instead of an instance. The
// instance testers use the same names without the ForPath suffix.
TBool wxFileName_FileExistsForPath(TClass(wxString) file);
TBool wxFileName_DirExistsForPath(TClass(wxString) dir);
TBool wxFileName_ExistsForPath(TClass(wxString) path, int flags);
TBool wxFileName_IsFileReadableForPath(TClass(wxString) file);
TBool wxFileName_IsFileWritableForPath(TClass(wxString) file);
TBool wxFileName_IsFileExecutableForPath(TClass(wxString) file);
TBool wxFileName_IsDirReadableForPath(TClass(wxString) dir);
TBool wxFileName_IsDirWritableForPath(TClass(wxString) dir);
TBool wxFileName_MkdirForPath(TClass(wxString) dir, int perm, int flags);
TBool wxFileName_RmdirForPath(TClass(wxString) dir, int flags);
TBool wxFileName_SetCwdForPath(TClass(wxString) cwd);
TClass(wxString) wxFileName_GetCwd(TClass(wxString) volume);
TClass(wxString) wxFileName_GetHomeDir();
TClass(wxString) wxFileName_GetTempDir();
TClass(wxString) wxFileName_GetTempFileName(TClass(wxString) prefix);
TClass(wxString) wxFileName_GetForbiddenChars(int format);
TClass(wxString) wxFileName_StripExtension(TClass(wxString) full_name);
TBool wxFileName_IsCaseSensitive(int format);

// ---------------------------------------------------------------------------
// wxDir / wxDirTraverser
// ---------------------------------------------------------------------------
//
// Enumeration flags (wxDirFlags): 0x0001 = files, 0x0002 = directories,
// 0x0004 = hidden entries, 0x0008 = '.' and '..', 0x0010 = don't follow
// symlinks. wxWidgets 3.3 defines wxDIR_DEFAULT as 0x0007. The named values
// are exported as expwxDIR_* accessors (see src/kwx_defs.cpp), including the
// wxDIR_IGNORE/STOP/CONTINUE traversal results used by wxDir_Traverse.

TClassDef(wxDir) TClass(wxDir) wxDir_Create();
TClass(wxDir) wxDir_CreateFromPath(TClass(wxString) directory);
void wxDir_Delete(TSelf(wxDir) pObject);
TBool wxDir_Open(TSelf(wxDir) pObject, TClass(wxString) directory);
void wxDir_Close(TSelf(wxDir) pObject);
TBool wxDir_IsOpened(TSelf(wxDir) pObject);
TClass(wxString) wxDir_GetName(TSelf(wxDir) pObject);
TClass(wxString) wxDir_GetNameWithSep(TSelf(wxDir) pObject);
// GetFirst/GetNext write the next entry into the caller-supplied filename.
TBool wxDir_GetFirst(TSelf(wxDir) pObject, TClass(wxString) filename, TClass(wxString) spec,
                     int flags);
TBool wxDir_GetNext(TSelf(wxDir) pObject, TClass(wxString) filename);
TBool wxDir_HasFiles(TSelf(wxDir) pObject, TClass(wxString) spec);
TBool wxDir_HasSubDirs(TSelf(wxDir) pObject, TClass(wxString) spec);
size_t wxDir_Traverse(TSelf(wxDir) pObject, TClass(wxDirTraverser) sink, TClass(wxString) spec,
                      int flags);
// GetAllFiles appends to the caller-supplied array and returns the total count.
size_t wxDir_GetAllFiles(TClass(wxString) dir_name, TArrayStringOutVoid files,
                         TClass(wxString) spec, int flags);
TClass(wxString) wxDir_FindFirst(TClass(wxString) dir_name, TClass(wxString) spec, int flags);
// Returns the total size in bytes, or -1.0 if it cannot be determined.
double wxDir_GetTotalSize(TClass(wxString) dir_name);
TBool wxDir_Exists(TClass(wxString) dir);
TBool wxDir_Make(TClass(wxString) dir, int perm, int flags);
TBool wxDir_Remove(TClass(wxString) dir, int flags);

// kwxDirTraverser forwards the wxDirTraverser virtuals to a C callback with the
// signature: int callback(void* pObject, int action, wxString* path).
// action is 0 for a file, 1 for a directory and 2 for an open error. The return
// value is a wxDirTraverseResult: -1 = ignore, 0 = stop, 1 = continue.
TClassDef(wxDirTraverser) TClass(wxDirTraverser)
    wxDirTraverser_Create(void* pObject, void* pFunction);
void wxDirTraverser_Delete(TSelf(wxDirTraverser) pObject);

// ---------------------------------------------------------------------------
// wxStandardPaths
// ---------------------------------------------------------------------------
//
// Dir values: 0 = cache, 1 = config, 2 = documents, 3 = desktop,
// 4 = downloads, 5 = music, 6 = pictures, 7 = videos.
// ResourceCat: 0 = none, 1 = messages.
// FileLayout: 0 = classic, 1 = XDG.  ConfigFileConv: 0 = dot, 1 = .conf.
// UseAppInfo flags: 0 = none, 1 = app name, 2 = vendor name.

// Returns the global singleton - the caller must not delete it.
TClassDef(wxStandardPaths) TClass(wxStandardPaths) wxStandardPaths_Get();
TClass(wxString) wxStandardPaths_GetConfigDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetUserConfigDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetDataDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetLocalDataDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetUserDataDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetUserLocalDataDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetDocumentsDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetAppDocumentsDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetExecutablePath(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetPluginsDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetResourcesDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetSharedLibrariesDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetTempDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_GetUserDir(TSelf(wxStandardPaths) pObject, int user_dir);
TClass(wxString) wxStandardPaths_GetLocalizedResourcesDir(TSelf(wxStandardPaths) pObject,
                                                          TClass(wxString) lang, int category);
TClass(wxString)
    wxStandardPaths_AppendAppInfo(TSelf(wxStandardPaths) pObject, TClass(wxString) dir);
TClass(wxString) wxStandardPaths_MakeConfigFileName(TSelf(wxStandardPaths) pObject,
                                                    TClass(wxString) base_name, int convention);
int wxStandardPaths_GetFileLayout(TSelf(wxStandardPaths) pObject);
void wxStandardPaths_SetFileLayout(TSelf(wxStandardPaths) pObject, int layout);
void wxStandardPaths_UseAppInfo(TSelf(wxStandardPaths) pObject, int info);

// Both groups below are exported on every platform; a platform that does not
// implement a wrapper returns an empty string or performs no operation.

TClass(wxString) wxStandardPaths_GetInstallPrefix(TSelf(wxStandardPaths) pObject);
void wxStandardPaths_SetInstallPrefix(TSelf(wxStandardPaths) pObject, TClass(wxString) prefix);
void wxStandardPaths_IgnoreAppSubDir(TSelf(wxStandardPaths) pObject,
                                     TClass(wxString) subdir_pattern);
void wxStandardPaths_IgnoreAppBuildSubDirs(TSelf(wxStandardPaths) pObject);
void wxStandardPaths_DontIgnoreAppSubDir(TSelf(wxStandardPaths) pObject);
TClass(wxString) wxStandardPaths_MSWGetShellDir(int csidl);

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
