#pragma once

// Base-utility file, stream and compression classes: text files, temporary files,
// string tokenization, stream buffers, and the zip, zlib and tar archives.
//
// These classes are classified `base-utility` in `.private/coverage_expansion_inventory.md`
// and are therefore listed in `GuiExcludedClasses()` (`kwxgen/src/profile.cpp`), so the `gui`
// profile used by the Go and Julia bindings does not emit them.
//
// Sizes and offsets are returned as `int`. wxWidgets stores them in `wxFileOffset`, which is
// 64 bits on the supported platforms, so a size above 2 GB truncates. The 64-bit surface is
// deferred until the downstream TypeScript binding supports `TInt64` — see
// `.private/deferred_i64.md`.

// ---------------------------------------------------------------------------
// wxTextFile (and the inherited wxTextBuffer surface)
// ---------------------------------------------------------------------------

// Create() on wxTextBuffer would collide with the constructor convention, so the
// buffer-creating methods are named CreateOnDisk*.
TClassDef(wxTextFile) TClass(wxTextFile) wxTextFile_Create();
TClass(wxTextFile) wxTextFile_CreateFromFile(TClass(wxString) file_name);
void wxTextFile_Delete(TSelf(wxTextFile) pObject);
TBool wxTextFile_Exists(TSelf(wxTextFile) pObject);
TBool wxTextFile_CreateOnDisk(TSelf(wxTextFile) pObject);
TBool wxTextFile_CreateOnDiskNamed(TSelf(wxTextFile) pObject, TClass(wxString) file_name);
TBool wxTextFile_Open(TSelf(wxTextFile) pObject);
TBool wxTextFile_OpenNamed(TSelf(wxTextFile) pObject, TClass(wxString) file_name);
TBool wxTextFile_Close(TSelf(wxTextFile) pObject);
TBool wxTextFile_IsOpened(TSelf(wxTextFile) pObject);
int wxTextFile_GetLineCount(TSelf(wxTextFile) pObject);
TClass(wxString) wxTextFile_GetLine(TSelf(wxTextFile) pObject, int line_index);
int wxTextFile_GetCurrentLine(TSelf(wxTextFile) pObject);
void wxTextFile_GoToLine(TSelf(wxTextFile) pObject, int line_index);
TBool wxTextFile_Eof(TSelf(wxTextFile) pObject);
TClass(wxString) wxTextFile_GetFirstLine(TSelf(wxTextFile) pObject);
TClass(wxString) wxTextFile_GetNextLine(TSelf(wxTextFile) pObject);
TClass(wxString) wxTextFile_GetPrevLine(TSelf(wxTextFile) pObject);
TClass(wxString) wxTextFile_GetLastLine(TSelf(wxTextFile) pObject);
int wxTextFile_GetLineType(TSelf(wxTextFile) pObject, int line_index);
int wxTextFile_GuessType(TSelf(wxTextFile) pObject);
TClass(wxString) wxTextFile_GetName(TSelf(wxTextFile) pObject);
void wxTextFile_AddLine(TSelf(wxTextFile) pObject, TClass(wxString) line, int line_type);
void wxTextFile_InsertLine(TSelf(wxTextFile) pObject, TClass(wxString) line, int line_index,
                           int line_type);
void wxTextFile_RemoveLine(TSelf(wxTextFile) pObject, int line_index);
void wxTextFile_Clear(TSelf(wxTextFile) pObject);
// Write() with wxTextFileType_None keeps the existing line endings.
TBool wxTextFile_Write(TSelf(wxTextFile) pObject);
TBool wxTextFile_WriteAs(TSelf(wxTextFile) pObject, int line_type);
TClass(wxString) wxTextFile_Translate(TClass(wxString) text, int line_type);
TClass(wxString) wxTextFile_GetEol(int line_type);

// ---------------------------------------------------------------------------
// wxTempFile
// ---------------------------------------------------------------------------

// Closing semantics: Commit() replaces the original file, Discard() drops the changes and
// the destructor calls Discard() when neither was called.
TClassDef(wxTempFile) TClass(wxTempFile) wxTempFile_Create();
TClass(wxTempFile) wxTempFile_CreateForName(TClass(wxString) file_name);
void wxTempFile_Delete(TSelf(wxTempFile) pObject);
TBool wxTempFile_Open(TSelf(wxTempFile) pObject, TClass(wxString) file_name);
TBool wxTempFile_IsOpened(TSelf(wxTempFile) pObject);
int wxTempFile_Length(TSelf(wxTempFile) pObject);
int wxTempFile_Seek(TSelf(wxTempFile) pObject, int offset, int seek_mode);
int wxTempFile_Tell(TSelf(wxTempFile) pObject);
TBool wxTempFile_WriteBytes(TSelf(wxTempFile) pObject, void* buffer, int size);
TBool wxTempFile_WriteText(TSelf(wxTempFile) pObject, TClass(wxString) text);
TBool wxTempFile_Flush(TSelf(wxTempFile) pObject);
TBool wxTempFile_Commit(TSelf(wxTempFile) pObject);
void wxTempFile_Discard(TSelf(wxTempFile) pObject);

// ---------------------------------------------------------------------------
// wxTempFileOutputStream
// ---------------------------------------------------------------------------

// The constructor opens the temporary file.  Close() is Commit(); the original
// file is only replaced when Commit() succeeds.
TClassDefExtend(wxTempFileOutputStream, wxOutputStream) TClass(wxTempFileOutputStream)
    wxTempFileOutputStream_Create(TClass(wxString) file_name);
void wxTempFileOutputStream_Delete(TSelf(wxTempFileOutputStream) pObject);
TBool wxTempFileOutputStream_Commit(TSelf(wxTempFileOutputStream) pObject);
void wxTempFileOutputStream_Discard(TSelf(wxTempFileOutputStream) pObject);
TBool wxTempFileOutputStream_Close(TSelf(wxTempFileOutputStream) pObject);
int wxTempFileOutputStream_GetLength(TSelf(wxTempFileOutputStream) pObject);
TBool wxTempFileOutputStream_IsSeekable(TSelf(wxTempFileOutputStream) pObject);

// ---------------------------------------------------------------------------
// wxStringTokenizer
// ---------------------------------------------------------------------------

// Tokenizer modes are the wxStringTokenizerMode values (wxTOKEN_DEFAULT, wxTOKEN_RET_EMPTY,
// wxTOKEN_RET_EMPTY_ALL, wxTOKEN_RET_DELIMS, wxTOKEN_STRTOK).
TClassDefExtend(wxStringTokenizer, wxObject) TClass(wxStringTokenizer) wxStringTokenizer_Create();
TClass(wxStringTokenizer)
    wxStringTokenizer_CreateFor(TClass(wxString) str, TClass(wxString) delimiters, int mode);
void wxStringTokenizer_Delete(TSelf(wxStringTokenizer) pObject);
void wxStringTokenizer_SetString(TSelf(wxStringTokenizer) pObject, TClass(wxString) str,
                                 TClass(wxString) delimiters, int mode);
void wxStringTokenizer_Reinit(TSelf(wxStringTokenizer) pObject, TClass(wxString) str);
int wxStringTokenizer_CountTokens(TSelf(wxStringTokenizer) pObject);
TBool wxStringTokenizer_HasMoreTokens(TSelf(wxStringTokenizer) pObject);
TClass(wxString) wxStringTokenizer_GetNextToken(TSelf(wxStringTokenizer) pObject);
TChar wxStringTokenizer_GetLastDelimiter(TSelf(wxStringTokenizer) pObject);
TClass(wxString) wxStringTokenizer_GetString(TSelf(wxStringTokenizer) pObject);
int wxStringTokenizer_GetPosition(TSelf(wxStringTokenizer) pObject);
int wxStringTokenizer_GetMode(TSelf(wxStringTokenizer) pObject);
TBool wxStringTokenizer_AllowEmpty(TSelf(wxStringTokenizer) pObject);

// ---------------------------------------------------------------------------
// wxStreamBuffer
// ---------------------------------------------------------------------------

// A stream buffer is created over an existing wxInputStream or wxOutputStream; the stream
// must outlive the buffer. SetBufferIO() takes ownership of the buffer only when
// take_ownership is non-zero, and the buffer must then have been allocated with malloc().
TClassDef(wxStreamBuffer) TClass(wxStreamBuffer)
    wxStreamBuffer_CreateRead(TClass(wxInputStream) stream, int buffer_size);
TClass(wxStreamBuffer) wxStreamBuffer_CreateWrite(TClass(wxOutputStream) stream, int buffer_size);
void wxStreamBuffer_Delete(TSelf(wxStreamBuffer) pObject);
int wxStreamBuffer_Read(TSelf(wxStreamBuffer) pObject, void* buffer, int size);
int wxStreamBuffer_Write(TSelf(wxStreamBuffer) pObject, void* buffer, int size);
TChar wxStreamBuffer_Peek(TSelf(wxStreamBuffer) pObject);
TChar wxStreamBuffer_GetChar(TSelf(wxStreamBuffer) pObject);
void wxStreamBuffer_PutChar(TSelf(wxStreamBuffer) pObject, TChar character);
int wxStreamBuffer_Tell(TSelf(wxStreamBuffer) pObject);
int wxStreamBuffer_Seek(TSelf(wxStreamBuffer) pObject, int pos, int seek_mode);
void wxStreamBuffer_ResetBuffer(TSelf(wxStreamBuffer) pObject);
void wxStreamBuffer_Truncate(TSelf(wxStreamBuffer) pObject);
void wxStreamBuffer_SetBufferIO(TSelf(wxStreamBuffer) pObject, void* start, void* end,
                                TBool take_ownership);
void wxStreamBuffer_SetBufferSize(TSelf(wxStreamBuffer) pObject, int buffer_size);
void* wxStreamBuffer_GetBufferStart(TSelf(wxStreamBuffer) pObject);
void* wxStreamBuffer_GetBufferEnd(TSelf(wxStreamBuffer) pObject);
void* wxStreamBuffer_GetBufferPos(TSelf(wxStreamBuffer) pObject);
int wxStreamBuffer_GetBufferSize(TSelf(wxStreamBuffer) pObject);
int wxStreamBuffer_GetIntPosition(TSelf(wxStreamBuffer) pObject);
void wxStreamBuffer_SetIntPosition(TSelf(wxStreamBuffer) pObject, int pos);
int wxStreamBuffer_GetLastAccess(TSelf(wxStreamBuffer) pObject);
int wxStreamBuffer_GetBytesLeft(TSelf(wxStreamBuffer) pObject);
void wxStreamBuffer_Fixed(TSelf(wxStreamBuffer) pObject, TBool fixed);
void wxStreamBuffer_Flushable(TSelf(wxStreamBuffer) pObject, TBool flushable);
TBool wxStreamBuffer_FlushBuffer(TSelf(wxStreamBuffer) pObject);
TBool wxStreamBuffer_FillBuffer(TSelf(wxStreamBuffer) pObject);
int wxStreamBuffer_GetDataLeft(TSelf(wxStreamBuffer) pObject);
// Returns the stream the buffer is associated with; the buffer does not own it.
TClass(wxStreamBase) wxStreamBuffer_GetStream(TSelf(wxStreamBuffer) pObject);
TBool wxStreamBuffer_HasBuffer(TSelf(wxStreamBuffer) pObject);
TBool wxStreamBuffer_IsFixed(TSelf(wxStreamBuffer) pObject);
TBool wxStreamBuffer_IsFlushable(TSelf(wxStreamBuffer) pObject);

// ---------------------------------------------------------------------------
// wxFilterInputStream / wxFilterOutputStream
// ---------------------------------------------------------------------------

// The parent stream must outlive the filter stream.
void wxFilterInputStream_Delete(TSelf(wxFilterInputStream) pObject);
int wxFilterInputStream_GetLength(TSelf(wxFilterInputStream) pObject);
TClass(wxInputStream) wxFilterInputStream_GetFilterInputStream(TSelf(wxFilterInputStream) pObject);
int wxFilterOutputStream_GetLength(TSelf(wxFilterOutputStream) pObject);
TClass(wxOutputStream)
    wxFilterOutputStream_GetFilterOutputStream(TSelf(wxFilterOutputStream) pObject);
void wxFilterOutputStream_Delete(TSelf(wxFilterOutputStream) pObject);

// ---------------------------------------------------------------------------
// wxFilterClassFactoryBase / wxFilterClassFactory
// ---------------------------------------------------------------------------

// wxStreamProtocolType values: 0 = protocol, 1 = MIME type, 2 = encoding,
// 3 = file extension.
//
// GetProtocols() joins the registered values with ", " so the whole list can be
// copied by one FFI call; the wxWidgets function returns a null-terminated array
// of wxChar pointers.
TClassDef(wxFilterClassFactoryBase) TClass(wxString)
    wxFilterClassFactoryBase_GetProtocol(TSelf(wxFilterClassFactoryBase) pObject);
TClass(wxString)
    wxFilterClassFactoryBase_GetProtocols(TSelf(wxFilterClassFactoryBase) pObject, int type);
TBool wxFilterClassFactoryBase_CanHandle(TSelf(wxFilterClassFactoryBase) pObject,
                                         TClass(wxString) protocol, int type);
TClass(wxString) wxFilterClassFactoryBase_PopExtension(TSelf(wxFilterClassFactoryBase) pObject,
                                                       TClass(wxString) location);

// The returned factory is owned by wxWidgets and must not be deleted.
// NewStreamInput/NewStreamOutput are the two NewStream() overloads.
TClassDefExtend(wxFilterClassFactory, wxFilterClassFactoryBase) TClass(wxFilterInputStream)
    wxFilterClassFactory_NewStreamInput(TSelf(wxFilterClassFactory) pObject,
                                        TClass(wxInputStream) stream);
TClass(wxFilterOutputStream)
    wxFilterClassFactory_NewStreamOutput(TSelf(wxFilterClassFactory) pObject,
                                         TClass(wxOutputStream) stream);
TClass(wxFilterClassFactory) wxFilterClassFactory_Find(TClass(wxString) protocol, int type);
TClass(wxFilterClassFactory) wxFilterClassFactory_GetFirst();
TClass(wxFilterClassFactory) wxFilterClassFactory_GetNext(TSelf(wxFilterClassFactory) pObject);

// ---------------------------------------------------------------------------
// wxArchiveClassFactory
// ---------------------------------------------------------------------------

// A factory is owned by wxWidgets.  NewStreamInput/NewStreamOutput correspond to
// the two NewStream() overloads; NewEntry() returns a new entry owned by the
// caller.
TClassDefExtend(wxArchiveClassFactory, wxFilterClassFactoryBase) TClass(wxArchiveEntry)
    wxArchiveClassFactory_NewEntry(TSelf(wxArchiveClassFactory) pObject);
TClass(wxArchiveInputStream)
    wxArchiveClassFactory_NewStreamInput(TSelf(wxArchiveClassFactory) pObject,
                                         TClass(wxInputStream) stream);
TClass(wxArchiveOutputStream)
    wxArchiveClassFactory_NewStreamOutput(TSelf(wxArchiveClassFactory) pObject,
                                          TClass(wxOutputStream) stream);
TClass(wxString) wxArchiveClassFactory_GetInternalName(TSelf(wxArchiveClassFactory) pObject,
                                                       TClass(wxString) name, int format);
TClass(wxArchiveClassFactory) wxArchiveClassFactory_Find(TClass(wxString) protocol, int type);
TClass(wxArchiveClassFactory) wxArchiveClassFactory_GetFirst();
TClass(wxArchiveClassFactory) wxArchiveClassFactory_GetNext(TSelf(wxArchiveClassFactory) pObject);

// ---------------------------------------------------------------------------
// wxArchiveEntry
// ---------------------------------------------------------------------------

// Entries returned by GetNextEntry() are owned by the caller.  GetDateTime()
// returns a new wxDateTime the caller must delete.
TClassDefExtend(wxArchiveEntry, wxObject) TClass(wxDateTime)
    wxArchiveEntry_GetDateTime(TSelf(wxArchiveEntry) pObject);
int wxArchiveEntry_GetSize(TSelf(wxArchiveEntry) pObject);
int wxArchiveEntry_GetOffset(TSelf(wxArchiveEntry) pObject);
TBool wxArchiveEntry_IsDir(TSelf(wxArchiveEntry) pObject);
TBool wxArchiveEntry_IsReadOnly(TSelf(wxArchiveEntry) pObject);
TClass(wxString) wxArchiveEntry_GetInternalName(TSelf(wxArchiveEntry) pObject);
int wxArchiveEntry_GetInternalFormat(TSelf(wxArchiveEntry) pObject);
TClass(wxString) wxArchiveEntry_GetName(TSelf(wxArchiveEntry) pObject, int path_format);
TClass(wxArchiveEntry) wxArchiveEntry_Clone(TSelf(wxArchiveEntry) pObject);
// GetNextEntry() gives away ownership; delete the entry with this function.
void wxArchiveEntry_Delete(TSelf(wxArchiveEntry) pObject);
void wxArchiveEntry_SetDateTime(TSelf(wxArchiveEntry) pObject, TClass(wxDateTime) dt);
void wxArchiveEntry_SetSize(TSelf(wxArchiveEntry) pObject, int size);
void wxArchiveEntry_SetIsDir(TSelf(wxArchiveEntry) pObject, TBool is_dir);
void wxArchiveEntry_SetIsReadOnly(TSelf(wxArchiveEntry) pObject, TBool is_read_only);
void wxArchiveEntry_SetName(TSelf(wxArchiveEntry) pObject, TClass(wxString) entry_name,
                            int path_format);

// ---------------------------------------------------------------------------
// wxArchiveInputStream
// ---------------------------------------------------------------------------

// The parent stream must outlive the archive stream.  GetNextEntry() gives away
// ownership of the returned entry and returns null when there are no more.
TClassDefExtend(wxArchiveInputStream,
                wxFilterInputStream) void wxArchiveInputStream_Delete(TSelf(wxArchiveInputStream)
                                                                          pObject);
TClass(wxArchiveEntry) wxArchiveInputStream_GetNextEntry(TSelf(wxArchiveInputStream) pObject);
TBool wxArchiveInputStream_OpenEntry(TSelf(wxArchiveInputStream) pObject,
                                     TClass(wxArchiveEntry) entry);
TBool wxArchiveInputStream_CloseEntry(TSelf(wxArchiveInputStream) pObject);

// ---------------------------------------------------------------------------
// wxArchiveOutputStream
// ---------------------------------------------------------------------------

// PutNextEntry(wxArchiveEntry) and CopyEntry() take ownership of the entry.
// The ...Date variants accept an explicit timestamp; a null dt means
// wxDateTime::Now().  CloseEntry() and Close() finish the archive.
TClassDefExtend(wxArchiveOutputStream,
                wxFilterOutputStream) void wxArchiveOutputStream_Delete(TSelf(wxArchiveOutputStream)
                                                                            pObject);
TBool wxArchiveOutputStream_PutNextEntry(TSelf(wxArchiveOutputStream) pObject,
                                         TClass(wxArchiveEntry) entry);
TBool wxArchiveOutputStream_PutNextEntryDate(TSelf(wxArchiveOutputStream) pObject,
                                             TClass(wxString) entry_name, TClass(wxDateTime) dt,
                                             int size);
TBool wxArchiveOutputStream_PutNextDirEntryDate(TSelf(wxArchiveOutputStream) pObject,
                                                TClass(wxString) entry_name, TClass(wxDateTime) dt);
TBool wxArchiveOutputStream_CopyEntry(TSelf(wxArchiveOutputStream) pObject,
                                      TClass(wxArchiveEntry) entry,
                                      TClass(wxArchiveInputStream) input_stream);
TBool wxArchiveOutputStream_CopyArchiveMetaData(TSelf(wxArchiveOutputStream) pObject,
                                                TClass(wxArchiveInputStream) input_stream);
TBool wxArchiveOutputStream_CloseEntry(TSelf(wxArchiveOutputStream) pObject);

// ---------------------------------------------------------------------------
// wxZipEntry
// ---------------------------------------------------------------------------

// Entry objects returned by wxZipInputStream_GetNextEntry are owned by the caller.
TClassDefExtend(wxZipEntry, wxArchiveEntry) TClass(wxZipEntry) wxZipEntry_Create();
TClass(wxZipEntry) wxZipEntry_CreateNamed(TClass(wxString) entry_name);
void wxZipEntry_Delete(TSelf(wxZipEntry) pObject);
TClass(wxZipEntry) wxZipEntry_Clone(TSelf(wxZipEntry) pObject);
int wxZipEntry_GetSize(TSelf(wxZipEntry) pObject);
int wxZipEntry_GetOffset(TSelf(wxZipEntry) pObject);
int wxZipEntry_GetCompressedSize(TSelf(wxZipEntry) pObject);
TClass(wxString) wxZipEntry_GetName(TSelf(wxZipEntry) pObject, int path_format);
TClass(wxString) wxZipEntry_GetInternalName(TSelf(wxZipEntry) pObject);
int wxZipEntry_GetMethod(TSelf(wxZipEntry) pObject);
int wxZipEntry_GetFlags(TSelf(wxZipEntry) pObject);
TUInt32 wxZipEntry_GetCrc(TSelf(wxZipEntry) pObject);
int wxZipEntry_GetSystemMadeBy(TSelf(wxZipEntry) pObject);
TUInt32 wxZipEntry_GetExternalAttributes(TSelf(wxZipEntry) pObject);
int wxZipEntry_GetMode(TSelf(wxZipEntry) pObject);
TClass(wxString) wxZipEntry_GetComment(TSelf(wxZipEntry) pObject);
TBool wxZipEntry_IsDir(TSelf(wxZipEntry) pObject);
TBool wxZipEntry_IsText(TSelf(wxZipEntry) pObject);
TBool wxZipEntry_IsReadOnly(TSelf(wxZipEntry) pObject);
TBool wxZipEntry_IsMadeByUnix(TSelf(wxZipEntry) pObject);
void wxZipEntry_SetSize(TSelf(wxZipEntry) pObject, int size);
void wxZipEntry_SetMethod(TSelf(wxZipEntry) pObject, int method);
void wxZipEntry_SetComment(TSelf(wxZipEntry) pObject, TClass(wxString) comment);
void wxZipEntry_SetExternalAttributes(TSelf(wxZipEntry) pObject, TUInt32 attributes);
void wxZipEntry_SetSystemMadeBy(TSelf(wxZipEntry) pObject, int system);
void wxZipEntry_SetMode(TSelf(wxZipEntry) pObject, int mode);
void wxZipEntry_SetName(TSelf(wxZipEntry) pObject, TClass(wxString) entry_name, int path_format);
void wxZipEntry_SetIsDir(TSelf(wxZipEntry) pObject, TBool is_dir);
void wxZipEntry_SetIsReadOnly(TSelf(wxZipEntry) pObject, TBool is_read_only);
void wxZipEntry_SetIsText(TSelf(wxZipEntry) pObject, TBool is_text);

// ---------------------------------------------------------------------------
// wxZipInputStream
// ---------------------------------------------------------------------------

// The parent stream must outlive the archive stream.
TClassDefExtend(wxZipInputStream, wxArchiveInputStream) TClass(wxZipInputStream)
    wxZipInputStream_Create(TClass(wxInputStream) stream);
void wxZipInputStream_Delete(TSelf(wxZipInputStream) pObject);
TClass(wxZipEntry) wxZipInputStream_GetNextEntry(TSelf(wxZipInputStream) pObject);
TBool wxZipInputStream_OpenEntry(TSelf(wxZipInputStream) pObject, TClass(wxZipEntry) entry);
TBool wxZipInputStream_CloseEntry(TSelf(wxZipInputStream) pObject);
TClass(wxString) wxZipInputStream_GetComment(TSelf(wxZipInputStream) pObject);
int wxZipInputStream_GetTotalEntries(TSelf(wxZipInputStream) pObject);
int wxZipInputStream_GetLength(TSelf(wxZipInputStream) pObject);

// ---------------------------------------------------------------------------
// wxZipOutputStream
// ---------------------------------------------------------------------------

// PutNextEntry(wxZipEntry) and CopyEntry() take ownership of the entry and give away the
// caller's reference. Close() is also called by the destructor.
TClassDefExtend(wxZipOutputStream, wxArchiveOutputStream) TClass(wxZipOutputStream)
    wxZipOutputStream_Create(TClass(wxOutputStream) stream, int level);
void wxZipOutputStream_Delete(TSelf(wxZipOutputStream) pObject);
TBool wxZipOutputStream_PutNextEntry(TSelf(wxZipOutputStream) pObject, TClass(wxString) entry_name,
                                     int size);
// Explicit timestamp.  A null dt means wxDateTime::Now().
TBool wxZipOutputStream_PutNextEntryDate(TSelf(wxZipOutputStream) pObject,
                                         TClass(wxString) entry_name, TClass(wxDateTime) dt,
                                         int size);
TBool wxZipOutputStream_PutNextDirEntry(TSelf(wxZipOutputStream) pObject,
                                        TClass(wxString) entry_name);
TBool wxZipOutputStream_PutNextDirEntryDate(TSelf(wxZipOutputStream) pObject,
                                            TClass(wxString) entry_name, TClass(wxDateTime) dt);
TBool wxZipOutputStream_PutEntry(TSelf(wxZipOutputStream) pObject, TClass(wxZipEntry) entry);
TBool wxZipOutputStream_CopyEntry(TSelf(wxZipOutputStream) pObject, TClass(wxZipEntry) entry,
                                  TClass(wxZipInputStream) input_stream);
TBool wxZipOutputStream_CopyArchiveMetaData(TSelf(wxZipOutputStream) pObject,
                                            TClass(wxZipInputStream) input_stream);
void wxZipOutputStream_Write(TSelf(wxZipOutputStream) pObject, void* buffer, int size);
void wxZipOutputStream_Sync(TSelf(wxZipOutputStream) pObject);
TBool wxZipOutputStream_CloseEntry(TSelf(wxZipOutputStream) pObject);
TBool wxZipOutputStream_Close(TSelf(wxZipOutputStream) pObject);
void wxZipOutputStream_SetComment(TSelf(wxZipOutputStream) pObject, TClass(wxString) comment);
int wxZipOutputStream_GetLevel(TSelf(wxZipOutputStream) pObject);
void wxZipOutputStream_SetLevel(TSelf(wxZipOutputStream) pObject, int level);
void wxZipOutputStream_SetFormat(TSelf(wxZipOutputStream) pObject, int format);
int wxZipOutputStream_GetFormat(TSelf(wxZipOutputStream) pObject);

// ---------------------------------------------------------------------------
// wxZlibInputStream / wxZlibOutputStream
// ---------------------------------------------------------------------------

// Flags are the wxZLibFlags values (wxZLIB_NO_HEADER, wxZLIB_ZLIB, wxZLIB_GZIP, wxZLIB_AUTO);
// compression levels are the wxZlibCompressionLevels values.
TClassDefExtend(wxZlibInputStream, wxFilterInputStream) TClass(wxZlibInputStream)
    wxZlibInputStream_Create(TClass(wxInputStream) stream, int flags);
void wxZlibInputStream_Delete(TSelf(wxZlibInputStream) pObject);
TBool wxZlibInputStream_CanHandleGZip();
TBool wxZlibInputStream_SetDictionary(TSelf(wxZlibInputStream) pObject, void* data, int size);
int wxZlibInputStream_GetLength(TSelf(wxZlibInputStream) pObject);

TClassDefExtend(wxZlibOutputStream, wxFilterOutputStream) TClass(wxZlibOutputStream)
    wxZlibOutputStream_Create(TClass(wxOutputStream) stream, int level, int flags);
void wxZlibOutputStream_Delete(TSelf(wxZlibOutputStream) pObject);
TBool wxZlibOutputStream_CanHandleGZip();
TBool wxZlibOutputStream_SetDictionary(TSelf(wxZlibOutputStream) pObject, void* data, int size);
void wxZlibOutputStream_Sync(TSelf(wxZlibOutputStream) pObject);
TBool wxZlibOutputStream_Close(TSelf(wxZlibOutputStream) pObject);
int wxZlibOutputStream_GetLength(TSelf(wxZlibOutputStream) pObject);

// ---------------------------------------------------------------------------
// wxTarEntry
// ---------------------------------------------------------------------------

// Entry objects returned by wxTarInputStream_GetNextEntry are owned by the caller.
TClassDefExtend(wxTarEntry, wxArchiveEntry) TClass(wxTarEntry) wxTarEntry_Create();
TClass(wxTarEntry) wxTarEntry_CreateNamed(TClass(wxString) entry_name);
void wxTarEntry_Delete(TSelf(wxTarEntry) pObject);
TClass(wxTarEntry) wxTarEntry_Clone(TSelf(wxTarEntry) pObject);
TClass(wxString) wxTarEntry_GetName(TSelf(wxTarEntry) pObject, int path_format);
TClass(wxString) wxTarEntry_GetInternalName(TSelf(wxTarEntry) pObject);
int wxTarEntry_GetMode(TSelf(wxTarEntry) pObject);
int wxTarEntry_GetUserId(TSelf(wxTarEntry) pObject);
int wxTarEntry_GetGroupId(TSelf(wxTarEntry) pObject);
int wxTarEntry_GetSize(TSelf(wxTarEntry) pObject);
int wxTarEntry_GetOffset(TSelf(wxTarEntry) pObject);
int wxTarEntry_GetTypeFlag(TSelf(wxTarEntry) pObject);
TClass(wxString) wxTarEntry_GetLinkName(TSelf(wxTarEntry) pObject);
TClass(wxString) wxTarEntry_GetUserName(TSelf(wxTarEntry) pObject);
TClass(wxString) wxTarEntry_GetGroupName(TSelf(wxTarEntry) pObject);
int wxTarEntry_GetDevMajor(TSelf(wxTarEntry) pObject);
int wxTarEntry_GetDevMinor(TSelf(wxTarEntry) pObject);
TBool wxTarEntry_IsDir(TSelf(wxTarEntry) pObject);
TBool wxTarEntry_IsReadOnly(TSelf(wxTarEntry) pObject);
void wxTarEntry_SetName(TSelf(wxTarEntry) pObject, TClass(wxString) entry_name, int path_format);
void wxTarEntry_SetUserId(TSelf(wxTarEntry) pObject, int user_id);
void wxTarEntry_SetGroupId(TSelf(wxTarEntry) pObject, int group_id);
void wxTarEntry_SetMode(TSelf(wxTarEntry) pObject, int mode);
void wxTarEntry_SetSize(TSelf(wxTarEntry) pObject, int size);
void wxTarEntry_SetTypeFlag(TSelf(wxTarEntry) pObject, int type_flag);
void wxTarEntry_SetLinkName(TSelf(wxTarEntry) pObject, TClass(wxString) link_name);
void wxTarEntry_SetUserName(TSelf(wxTarEntry) pObject, TClass(wxString) user_name);
void wxTarEntry_SetGroupName(TSelf(wxTarEntry) pObject, TClass(wxString) group_name);
void wxTarEntry_SetDevMajor(TSelf(wxTarEntry) pObject, int dev_major);
void wxTarEntry_SetDevMinor(TSelf(wxTarEntry) pObject, int dev_minor);
void wxTarEntry_SetIsDir(TSelf(wxTarEntry) pObject, TBool is_dir);
void wxTarEntry_SetIsReadOnly(TSelf(wxTarEntry) pObject, TBool is_read_only);

// ---------------------------------------------------------------------------
// wxTarInputStream
// ---------------------------------------------------------------------------

// The parent stream must outlive the archive stream.
TClassDefExtend(wxTarInputStream, wxArchiveInputStream) TClass(wxTarInputStream)
    wxTarInputStream_Create(TClass(wxInputStream) stream);
void wxTarInputStream_Delete(TSelf(wxTarInputStream) pObject);
TClass(wxTarEntry) wxTarInputStream_GetNextEntry(TSelf(wxTarInputStream) pObject);
TBool wxTarInputStream_OpenEntry(TSelf(wxTarInputStream) pObject, TClass(wxTarEntry) entry);
TBool wxTarInputStream_CloseEntry(TSelf(wxTarInputStream) pObject);
int wxTarInputStream_GetLength(TSelf(wxTarInputStream) pObject);
int wxTarInputStream_GetMaxExtendedHeaderSize();
void wxTarInputStream_SetMaxExtendedHeaderSize(int size);

// ---------------------------------------------------------------------------
// wxTarOutputStream
// ---------------------------------------------------------------------------

// PutNextEntry(wxTarEntry) and CopyEntry() take ownership of the entry and give away the
// caller's reference. Close() is also called by the destructor when it is still open.
TClassDefExtend(wxTarOutputStream, wxArchiveOutputStream) TClass(wxTarOutputStream)
    wxTarOutputStream_Create(TClass(wxOutputStream) stream, int format);
void wxTarOutputStream_Delete(TSelf(wxTarOutputStream) pObject);
TBool wxTarOutputStream_PutNextEntry(TSelf(wxTarOutputStream) pObject, TClass(wxString) entry_name,
                                     int size);
// Explicit timestamp.  A null dt means wxDateTime::Now().
TBool wxTarOutputStream_PutNextEntryDate(TSelf(wxTarOutputStream) pObject,
                                         TClass(wxString) entry_name, TClass(wxDateTime) dt,
                                         int size);
TBool wxTarOutputStream_PutNextDirEntry(TSelf(wxTarOutputStream) pObject,
                                        TClass(wxString) entry_name);
TBool wxTarOutputStream_PutNextDirEntryDate(TSelf(wxTarOutputStream) pObject,
                                            TClass(wxString) entry_name, TClass(wxDateTime) dt);
TBool wxTarOutputStream_PutEntry(TSelf(wxTarOutputStream) pObject, TClass(wxTarEntry) entry);
TBool wxTarOutputStream_CopyEntry(TSelf(wxTarOutputStream) pObject, TClass(wxTarEntry) entry,
                                  TClass(wxTarInputStream) input_stream);
TBool wxTarOutputStream_CopyArchiveMetaData(TSelf(wxTarOutputStream) pObject,
                                            TClass(wxTarInputStream) input_stream);
void wxTarOutputStream_Write(TSelf(wxTarOutputStream) pObject, void* buffer, int size);
void wxTarOutputStream_Sync(TSelf(wxTarOutputStream) pObject);
TBool wxTarOutputStream_CloseEntry(TSelf(wxTarOutputStream) pObject);
TBool wxTarOutputStream_Close(TSelf(wxTarOutputStream) pObject);
TBool wxTarOutputStream_IsSeekable(TSelf(wxTarOutputStream) pObject);
void wxTarOutputStream_SetBlockingFactor(TSelf(wxTarOutputStream) pObject, int factor);
int wxTarOutputStream_GetBlockingFactor(TSelf(wxTarOutputStream) pObject);
