#pragma once

// Base-utility regular expression, XML, URI, base64 and memory-buffer wrappers.
//
// These classes are classified `base-utility` in `.private/coverage_expansion_inventory.md`
// and are therefore listed in `GuiExcludedClasses()` (`kwxgen/src/profile.cpp`), so the `gui`
// profile used by the Go and Julia bindings does not emit them.
//
// wxRegEx is wrapped unconditionally: `CMakeLists.txt` sets `wxUSE_REGEX=builtin` on every
// platform and links `wxregex` everywhere (Phase 3).
//
// Deprecated node APIs (`GetPropVal`, `FindPropVal`, `wxXmlProperty`) are not wrapped, and
// `wxXmlNode::GetPrevious` does not exist in wxWidgets 3.3 — a node only stores `m_next`.
//
// Byte buffers returned by this module are allocated with `malloc()` and must be released by
// the caller with `wxCFree()` (`include/kwx_constants.h`). Sizes and indexes are returned as
// `int`; wxWidgets stores them in `size_t`, so a value above 2 GB truncates. The 64-bit surface
// is deferred until the downstream TypeScript binding supports `TInt64` — see
// `.private/deferred_i64.md`.

// ---------------------------------------------------------------------------
// wxRegEx
// ---------------------------------------------------------------------------

// Flags are the wxRE_* compile values (wxRE_EXTENDED, wxRE_ADVANCED, wxRE_BASIC, wxRE_ICASE,
// wxRE_NOSUB, wxRE_NEWLINE, wxRE_DEFAULT) and the wxRE_NOTBOL / wxRE_NOTEOL / wxRE_NOTEMPTY
// match values. Matches() tests the whole string; MatchesFrom() tests the tail that starts at
// `start` (a negative `start` is clamped to 0). Replace/ReplaceAll/ReplaceFirst update `text`
// in place and return the number of replacements, or -1 on error.
TClassDef(wxRegEx) TClass(wxRegEx) wxRegEx_Create();
TClass(wxRegEx) wxRegEx_CreateCompiled(TClass(wxString) pattern, int flags);
void wxRegEx_Delete(TSelf(wxRegEx) pObject);
TBool wxRegEx_Compile(TSelf(wxRegEx) pObject, TClass(wxString) pattern, int flags);
TBool wxRegEx_IsValid(TSelf(wxRegEx) pObject);
TBool wxRegEx_Matches(TSelf(wxRegEx) pObject, TClass(wxString) text, int flags);
TBool wxRegEx_MatchesFrom(TSelf(wxRegEx) pObject, TClass(wxString) text, int start, int flags);
int wxRegEx_GetMatchCount(TSelf(wxRegEx) pObject);
TClass(wxString) wxRegEx_GetMatch(TSelf(wxRegEx) pObject, TClass(wxString) text, int index);
int wxRegEx_GetMatchStart(TSelf(wxRegEx) pObject, int index);
int wxRegEx_GetMatchEnd(TSelf(wxRegEx) pObject, int index);
int wxRegEx_Replace(TSelf(wxRegEx) pObject, TClass(wxString) text, TClass(wxString) replacement);
int wxRegEx_ReplaceAll(TSelf(wxRegEx) pObject, TClass(wxString) text, TClass(wxString) replacement);
int wxRegEx_ReplaceFirst(TSelf(wxRegEx) pObject, TClass(wxString) text,
                         TClass(wxString) replacement);

// ---------------------------------------------------------------------------
// wxXmlDocument
// ---------------------------------------------------------------------------

// Load flags are the wxXmlDocumentLoadFlag values (wxXMLDOC_NONE,
// wxXMLDOC_KEEP_WHITESPACE_NODES); file types are the wxTextFileType values. SaveToString()
// serialises the document into a UTF-8 string. AppendChild() appends to the root element and
// returns false when the document has no root.
TClassDefExtend(wxXmlDocument, wxObject) TClass(wxXmlDocument) wxXmlDocument_Create();
TClass(wxXmlDocument) wxXmlDocument_CreateFromFile(TClass(wxString) file_name, int flags);
TClass(wxXmlDocument) wxXmlDocument_CreateFromString(TClass(wxString) text, int flags);
void wxXmlDocument_Delete(TSelf(wxXmlDocument) pObject);
TBool wxXmlDocument_Load(TSelf(wxXmlDocument) pObject, TClass(wxString) file_name, int flags);
TBool wxXmlDocument_LoadFromString(TSelf(wxXmlDocument) pObject, TClass(wxString) text, int flags);
TBool wxXmlDocument_Save(TSelf(wxXmlDocument) pObject, TClass(wxString) file_name, int indent_step);
TClass(wxString) wxXmlDocument_SaveToString(TSelf(wxXmlDocument) pObject, int indent_step);
TClass(wxXmlNode) wxXmlDocument_GetRoot(TSelf(wxXmlDocument) pObject);
void wxXmlDocument_SetRoot(TSelf(wxXmlDocument) pObject, TClass(wxXmlNode) root);
TClass(wxXmlNode) wxXmlDocument_DetachRoot(TSelf(wxXmlDocument) pObject);
TClass(wxString) wxXmlDocument_GetVersion(TSelf(wxXmlDocument) pObject);
void wxXmlDocument_SetVersion(TSelf(wxXmlDocument) pObject, TClass(wxString) version);
TClass(wxString) wxXmlDocument_GetFileEncoding(TSelf(wxXmlDocument) pObject);
void wxXmlDocument_SetFileEncoding(TSelf(wxXmlDocument) pObject, TClass(wxString) encoding);
int wxXmlDocument_GetFileType(TSelf(wxXmlDocument) pObject);
void wxXmlDocument_SetFileType(TSelf(wxXmlDocument) pObject, int file_type);
void wxXmlDocument_AppendToProlog(TSelf(wxXmlDocument) pObject, TClass(wxXmlNode) node);
TBool wxXmlDocument_AppendChild(TSelf(wxXmlDocument) pObject, TClass(wxXmlNode) child);
TBool wxXmlDocument_IsOk(TSelf(wxXmlDocument) pObject);

// wxXmlNode already has a complete block in `include/kwx_core_extra.h` (create/delete, type,
// name, content, attributes, children, siblings, parent, line number and conversion flags).
// No method from the Phase 7 list is missing, so no additional block is declared here.

// ---------------------------------------------------------------------------
// wxURI
// ---------------------------------------------------------------------------

// Host types are the wxURIHostType values (wxURI_REGNAME, wxURI_IPV4ADDRESS,
// wxURI_IPV6ADDRESS, wxURI_IPVFUTURE); Resolve() flags are the wxURIFlags values
// (wxURI_STRICT). Parse() is the name used for wxURI::Create() because the parser treats a
// `Create` prefix as a constructor.
TClassDefExtend(wxURI, wxObject) TClass(wxURI) wxURI_Create();
TClass(wxURI) wxURI_CreateFromString(TClass(wxString) uri_text);
void wxURI_Delete(TSelf(wxURI) pObject);
TBool wxURI_Parse(TSelf(wxURI) pObject, TClass(wxString) uri_text);
TBool wxURI_IsEmpty(TSelf(wxURI) pObject);
TBool wxURI_HasScheme(TSelf(wxURI) pObject);
TBool wxURI_HasUserInfo(TSelf(wxURI) pObject);
TBool wxURI_HasServer(TSelf(wxURI) pObject);
TBool wxURI_HasPort(TSelf(wxURI) pObject);
TBool wxURI_HasPath(TSelf(wxURI) pObject);
TBool wxURI_HasQuery(TSelf(wxURI) pObject);
TBool wxURI_HasFragment(TSelf(wxURI) pObject);
TClass(wxString) wxURI_GetScheme(TSelf(wxURI) pObject);
TClass(wxString) wxURI_GetPath(TSelf(wxURI) pObject);
TClass(wxString) wxURI_GetQuery(TSelf(wxURI) pObject);
TClass(wxString) wxURI_GetFragment(TSelf(wxURI) pObject);
TClass(wxString) wxURI_GetPort(TSelf(wxURI) pObject);
TClass(wxString) wxURI_GetUserInfo(TSelf(wxURI) pObject);
TClass(wxString) wxURI_GetServer(TSelf(wxURI) pObject);
TClass(wxString) wxURI_GetUser(TSelf(wxURI) pObject);
TClass(wxString) wxURI_GetPassword(TSelf(wxURI) pObject);
int wxURI_GetHostType(TSelf(wxURI) pObject);
void wxURI_SetUserAndPassword(TSelf(wxURI) pObject, TClass(wxString) user,
                              TClass(wxString) password);
TClass(wxString) wxURI_BuildURI(TSelf(wxURI) pObject);
TClass(wxString) wxURI_BuildUnescapedURI(TSelf(wxURI) pObject);
TClass(wxString) wxURI_Unescape(TClass(wxString) escaped_uri);
void wxURI_Resolve(TSelf(wxURI) pObject, TClass(wxURI) base, int flags);
TBool wxURI_IsReference(TSelf(wxURI) pObject);
TBool wxURI_IsRelative(TSelf(wxURI) pObject);

// ---------------------------------------------------------------------------
// wxMemoryBuffer
// ---------------------------------------------------------------------------

// GetData() returns the internal buffer; it stays valid only while the wxMemoryBuffer is alive
// and is not owned by the caller. AppendData() copies `length` bytes from `data`.
TClassDef(wxMemoryBuffer) TClass(wxMemoryBuffer) wxMemoryBuffer_Create();
void wxMemoryBuffer_Delete(TSelf(wxMemoryBuffer) pObject);
void* wxMemoryBuffer_GetData(TSelf(wxMemoryBuffer) pObject);
size_t wxMemoryBuffer_GetDataLen(TSelf(wxMemoryBuffer) pObject);
size_t wxMemoryBuffer_GetBufSize(TSelf(wxMemoryBuffer) pObject);
void wxMemoryBuffer_AppendData(TSelf(wxMemoryBuffer) pObject, void* data, size_t length);
void wxMemoryBuffer_AppendByte(TSelf(wxMemoryBuffer) pObject, TChar value);
void wxMemoryBuffer_SetDataLen(TSelf(wxMemoryBuffer) pObject, size_t length);
void wxMemoryBuffer_Clear(TSelf(wxMemoryBuffer) pObject);

// ---------------------------------------------------------------------------
// base64 free functions
// ---------------------------------------------------------------------------

// Decode modes are the wxBase64DecodeMode values (wxBase64DecodeMode_Strict = 0,
// wxBase64DecodeMode_SkipWS = 1, wxBase64DecodeMode_Relaxed = 2); an out-of-range mode falls
// back to strict. DecodeBuffer() returns nullptr when the input is invalid; otherwise the
// returned buffer is NUL-terminated, `decoded_length` receives the byte count, and the caller
// releases the buffer with wxCFree().
TClass(wxString) wxBase64EncodeBuffer(void* source, size_t src_length);
void* wxBase64DecodeBuffer(TClass(wxString) text, int mode, size_t* decoded_length);
size_t wxBase64EncodedSizeOf(size_t src_length);
size_t wxBase64DecodedSizeOf(size_t encoded_length);
