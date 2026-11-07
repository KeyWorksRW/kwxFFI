// Base-utility file, stream and compression wrappers: wxTextFile, wxTempFile,
// wxStringTokenizer, wxStreamBuffer and the zip, zlib and tar archive streams.
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <wx/archive.h>
#include <wx/stream.h>
#include <wx/tarstrm.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>

// The wxWidgets protocol APIs return a null-terminated array of wxChar
// pointers; the FFI returns one joined string instead of an array.
static wxString JoinProtocols(const wxChar* const* protocols)
{
    wxString joined;
    if (!protocols)
    {
        return joined;
    }

    for (const wxChar* const* item = protocols; *item; ++item)
    {
        if (!joined.empty())
        {
            joined += ", ";
        }
        joined += *item;
    }

    return joined;
}

extern "C"
{
    // -----------------------------------------------------------------------
    // wxTextFile
    // -----------------------------------------------------------------------

    EXPORT wxTextFile* wxTextFile_Create()
    {
        return new wxTextFile();
    }

    EXPORT wxTextFile* wxTextFile_CreateFromFile(wxString* file_name)
    {
        return new wxTextFile(*file_name);
    }

    EXPORT void wxTextFile_Delete(wxTextFile* self)
    {
        delete self;
    }

    EXPORT int wxTextFile_Exists(wxTextFile* self)
    {
        return self->Exists();
    }

    EXPORT int wxTextFile_CreateOnDisk(wxTextFile* self)
    {
        return self->Create();
    }

    EXPORT int wxTextFile_CreateOnDiskNamed(wxTextFile* self, wxString* file_name)
    {
        return self->Create(*file_name);
    }

    EXPORT int wxTextFile_Open(wxTextFile* self)
    {
        return self->Open();
    }

    EXPORT int wxTextFile_OpenNamed(wxTextFile* self, wxString* file_name)
    {
        return self->Open(*file_name);
    }

    EXPORT int wxTextFile_Close(wxTextFile* self)
    {
        return self->Close();
    }

    EXPORT int wxTextFile_IsOpened(wxTextFile* self)
    {
        return self->IsOpened();
    }

    EXPORT int wxTextFile_GetLineCount(wxTextFile* self)
    {
        return static_cast<int>(self->GetLineCount());
    }

    EXPORT wxString* wxTextFile_GetLine(wxTextFile* self, int line_index)
    {
        return new wxString(self->GetLine(static_cast<size_t>(line_index)));
    }

    EXPORT int wxTextFile_GetCurrentLine(wxTextFile* self)
    {
        return static_cast<int>(self->GetCurrentLine());
    }

    EXPORT void wxTextFile_GoToLine(wxTextFile* self, int line_index)
    {
        self->GoToLine(static_cast<size_t>(line_index));
    }

    EXPORT int wxTextFile_Eof(wxTextFile* self)
    {
        return self->Eof();
    }

    EXPORT wxString* wxTextFile_GetFirstLine(wxTextFile* self)
    {
        return new wxString(self->GetFirstLine());
    }

    EXPORT wxString* wxTextFile_GetNextLine(wxTextFile* self)
    {
        return new wxString(self->GetNextLine());
    }

    EXPORT wxString* wxTextFile_GetPrevLine(wxTextFile* self)
    {
        return new wxString(self->GetPrevLine());
    }

    EXPORT wxString* wxTextFile_GetLastLine(wxTextFile* self)
    {
        return new wxString(self->GetLastLine());
    }

    EXPORT int wxTextFile_GetLineType(wxTextFile* self, int line_index)
    {
        return static_cast<int>(self->GetLineType(static_cast<size_t>(line_index)));
    }

    EXPORT int wxTextFile_GuessType(wxTextFile* self)
    {
        return static_cast<int>(self->GuessType());
    }

    EXPORT wxString* wxTextFile_GetName(wxTextFile* self)
    {
        return new wxString(self->GetName());
    }

    EXPORT void wxTextFile_AddLine(wxTextFile* self, wxString* line, int line_type)
    {
        self->AddLine(*line, static_cast<wxTextFileType>(line_type));
    }

    EXPORT void wxTextFile_InsertLine(wxTextFile* self, wxString* line, int line_index,
                                      int line_type)
    {
        self->InsertLine(*line, static_cast<size_t>(line_index),
                         static_cast<wxTextFileType>(line_type));
    }

    EXPORT void wxTextFile_RemoveLine(wxTextFile* self, int line_index)
    {
        self->RemoveLine(static_cast<size_t>(line_index));
    }

    EXPORT void wxTextFile_Clear(wxTextFile* self)
    {
        self->Clear();
    }

    EXPORT int wxTextFile_Write(wxTextFile* self)
    {
        return self->Write();
    }

    EXPORT int wxTextFile_WriteAs(wxTextFile* self, int line_type)
    {
        return self->Write(static_cast<wxTextFileType>(line_type));
    }

    EXPORT wxString* wxTextFile_Translate(wxString* text, int line_type)
    {
        return new wxString(wxTextBuffer::Translate(*text, static_cast<wxTextFileType>(line_type)));
    }

    EXPORT wxString* wxTextFile_GetEol(int line_type)
    {
        return new wxString(wxTextBuffer::GetEOL(static_cast<wxTextFileType>(line_type)));
    }

    // -----------------------------------------------------------------------
    // wxTempFile
    // -----------------------------------------------------------------------

    EXPORT wxTempFile* wxTempFile_Create()
    {
        return new wxTempFile();
    }

    EXPORT wxTempFile* wxTempFile_CreateForName(wxString* file_name)
    {
        return new wxTempFile(*file_name);
    }

    EXPORT void wxTempFile_Delete(wxTempFile* self)
    {
        delete self;
    }

    EXPORT int wxTempFile_Open(wxTempFile* self, wxString* file_name)
    {
        return self->Open(*file_name);
    }

    EXPORT int wxTempFile_IsOpened(wxTempFile* self)
    {
        return self->IsOpened();
    }

    EXPORT int wxTempFile_Length(wxTempFile* self)
    {
        return static_cast<int>(self->Length());
    }

    EXPORT int wxTempFile_Seek(wxTempFile* self, int offset, int seek_mode)
    {
        return static_cast<int>(
            self->Seek(static_cast<wxFileOffset>(offset), static_cast<wxSeekMode>(seek_mode)));
    }

    EXPORT int wxTempFile_Tell(wxTempFile* self)
    {
        return static_cast<int>(self->Tell());
    }

    EXPORT int wxTempFile_WriteBytes(wxTempFile* self, void* buffer, int size)
    {
        return self->Write(buffer, static_cast<size_t>(size));
    }

    EXPORT int wxTempFile_WriteText(wxTempFile* self, wxString* text)
    {
        return self->Write(*text);
    }

    EXPORT int wxTempFile_Flush(wxTempFile* self)
    {
        return self->Flush();
    }

    EXPORT int wxTempFile_Commit(wxTempFile* self)
    {
        return self->Commit();
    }

    EXPORT void wxTempFile_Discard(wxTempFile* self)
    {
        self->Discard();
    }

    // -----------------------------------------------------------------------
    // wxTempFileOutputStream
    // -----------------------------------------------------------------------

    EXPORT wxTempFileOutputStream* wxTempFileOutputStream_Create(wxString* file_name)
    {
        return new wxTempFileOutputStream(*file_name);
    }

    EXPORT void wxTempFileOutputStream_Delete(wxTempFileOutputStream* self)
    {
        delete self;
    }

    EXPORT int wxTempFileOutputStream_Commit(wxTempFileOutputStream* self)
    {
        return self->Commit();
    }

    EXPORT void wxTempFileOutputStream_Discard(wxTempFileOutputStream* self)
    {
        self->Discard();
    }

    EXPORT int wxTempFileOutputStream_Close(wxTempFileOutputStream* self)
    {
        return self->Close();
    }

    EXPORT int wxTempFileOutputStream_GetLength(wxTempFileOutputStream* self)
    {
        return static_cast<int>(self->GetLength());
    }

    EXPORT int wxTempFileOutputStream_IsSeekable(wxTempFileOutputStream* self)
    {
        return self->IsSeekable();
    }

    // -----------------------------------------------------------------------
    // wxStringTokenizer
    // -----------------------------------------------------------------------

    EXPORT wxStringTokenizer* wxStringTokenizer_Create()
    {
        return new wxStringTokenizer();
    }

    EXPORT wxStringTokenizer* wxStringTokenizer_CreateFor(wxString* str, wxString* delimiters,
                                                          int mode)
    {
        return new wxStringTokenizer(*str, *delimiters, static_cast<wxStringTokenizerMode>(mode));
    }

    EXPORT void wxStringTokenizer_Delete(wxStringTokenizer* self)
    {
        delete self;
    }

    EXPORT void wxStringTokenizer_SetString(wxStringTokenizer* self, wxString* str,
                                            wxString* delimiters, int mode)
    {
        self->SetString(*str, *delimiters, static_cast<wxStringTokenizerMode>(mode));
    }

    EXPORT void wxStringTokenizer_Reinit(wxStringTokenizer* self, wxString* str)
    {
        self->Reinit(*str);
    }

    EXPORT int wxStringTokenizer_CountTokens(wxStringTokenizer* self)
    {
        return static_cast<int>(self->CountTokens());
    }

    EXPORT int wxStringTokenizer_HasMoreTokens(wxStringTokenizer* self)
    {
        return self->HasMoreTokens();
    }

    EXPORT wxString* wxStringTokenizer_GetNextToken(wxStringTokenizer* self)
    {
        return new wxString(self->GetNextToken());
    }

    EXPORT char wxStringTokenizer_GetLastDelimiter(wxStringTokenizer* self)
    {
        return static_cast<char>(self->GetLastDelimiter());
    }

    EXPORT wxString* wxStringTokenizer_GetString(wxStringTokenizer* self)
    {
        return new wxString(self->GetString());
    }

    EXPORT int wxStringTokenizer_GetPosition(wxStringTokenizer* self)
    {
        return static_cast<int>(self->GetPosition());
    }

    EXPORT int wxStringTokenizer_GetMode(wxStringTokenizer* self)
    {
        return static_cast<int>(self->GetMode());
    }

    EXPORT int wxStringTokenizer_AllowEmpty(wxStringTokenizer* self)
    {
        return self->AllowEmpty();
    }

    // -----------------------------------------------------------------------
    // wxStreamBuffer
    // -----------------------------------------------------------------------

    EXPORT wxStreamBuffer* wxStreamBuffer_CreateRead(wxInputStream* stream, int buffer_size)
    {
        return new wxStreamBuffer(static_cast<size_t>(buffer_size), *stream);
    }

    EXPORT wxStreamBuffer* wxStreamBuffer_CreateWrite(wxOutputStream* stream, int buffer_size)
    {
        return new wxStreamBuffer(static_cast<size_t>(buffer_size), *stream);
    }

    EXPORT void wxStreamBuffer_Delete(wxStreamBuffer* self)
    {
        delete self;
    }

    EXPORT int wxStreamBuffer_Read(wxStreamBuffer* self, void* buffer, int size)
    {
        return static_cast<int>(self->Read(buffer, static_cast<size_t>(size)));
    }

    EXPORT int wxStreamBuffer_Write(wxStreamBuffer* self, void* buffer, int size)
    {
        return static_cast<int>(self->Write(buffer, static_cast<size_t>(size)));
    }

    EXPORT char wxStreamBuffer_Peek(wxStreamBuffer* self)
    {
        return self->Peek();
    }

    EXPORT char wxStreamBuffer_GetChar(wxStreamBuffer* self)
    {
        return self->GetChar();
    }

    EXPORT void wxStreamBuffer_PutChar(wxStreamBuffer* self, char character)
    {
        self->PutChar(character);
    }

    EXPORT int wxStreamBuffer_Tell(wxStreamBuffer* self)
    {
        return static_cast<int>(self->Tell());
    }

    EXPORT int wxStreamBuffer_Seek(wxStreamBuffer* self, int pos, int seek_mode)
    {
        return static_cast<int>(
            self->Seek(static_cast<wxFileOffset>(pos), static_cast<wxSeekMode>(seek_mode)));
    }

    EXPORT void wxStreamBuffer_ResetBuffer(wxStreamBuffer* self)
    {
        self->ResetBuffer();
    }

    EXPORT void wxStreamBuffer_Truncate(wxStreamBuffer* self)
    {
        self->Truncate();
    }

    EXPORT void wxStreamBuffer_SetBufferIO(wxStreamBuffer* self, void* start, void* end,
                                           bool take_ownership)
    {
        self->SetBufferIO(start, end, take_ownership);
    }

    EXPORT void wxStreamBuffer_SetBufferSize(wxStreamBuffer* self, int buffer_size)
    {
        self->SetBufferIO(static_cast<size_t>(buffer_size));
    }

    EXPORT void* wxStreamBuffer_GetBufferStart(wxStreamBuffer* self)
    {
        return self->GetBufferStart();
    }

    EXPORT void* wxStreamBuffer_GetBufferEnd(wxStreamBuffer* self)
    {
        return self->GetBufferEnd();
    }

    EXPORT void* wxStreamBuffer_GetBufferPos(wxStreamBuffer* self)
    {
        return self->GetBufferPos();
    }

    EXPORT int wxStreamBuffer_GetBufferSize(wxStreamBuffer* self)
    {
        return static_cast<int>(self->GetBufferSize());
    }

    EXPORT int wxStreamBuffer_GetIntPosition(wxStreamBuffer* self)
    {
        return static_cast<int>(self->GetIntPosition());
    }

    EXPORT void wxStreamBuffer_SetIntPosition(wxStreamBuffer* self, int pos)
    {
        self->SetIntPosition(static_cast<size_t>(pos));
    }

    EXPORT int wxStreamBuffer_GetLastAccess(wxStreamBuffer* self)
    {
        return static_cast<int>(self->GetLastAccess());
    }

    EXPORT int wxStreamBuffer_GetBytesLeft(wxStreamBuffer* self)
    {
        return static_cast<int>(self->GetBytesLeft());
    }

    EXPORT void wxStreamBuffer_Fixed(wxStreamBuffer* self, bool fixed)
    {
        self->Fixed(fixed);
    }

    EXPORT void wxStreamBuffer_Flushable(wxStreamBuffer* self, bool flushable)
    {
        self->Flushable(flushable);
    }

    EXPORT int wxStreamBuffer_FlushBuffer(wxStreamBuffer* self)
    {
        return self->FlushBuffer();
    }

    EXPORT int wxStreamBuffer_FillBuffer(wxStreamBuffer* self)
    {
        return self->FillBuffer();
    }

    EXPORT int wxStreamBuffer_GetDataLeft(wxStreamBuffer* self)
    {
        return static_cast<int>(self->GetDataLeft());
    }

    EXPORT wxStreamBase* wxStreamBuffer_GetStream(wxStreamBuffer* self)
    {
        return self->GetStream();
    }

    EXPORT int wxStreamBuffer_HasBuffer(wxStreamBuffer* self)
    {
        return self->HasBuffer();
    }

    EXPORT int wxStreamBuffer_IsFixed(wxStreamBuffer* self)
    {
        return self->IsFixed();
    }

    EXPORT int wxStreamBuffer_IsFlushable(wxStreamBuffer* self)
    {
        return self->IsFlushable();
    }

    // -----------------------------------------------------------------------
    // wxFilterInputStream / wxFilterOutputStream
    // -----------------------------------------------------------------------

    EXPORT void wxFilterInputStream_Delete(wxFilterInputStream* self)
    {
        delete self;
    }

    EXPORT int wxFilterInputStream_GetLength(wxFilterInputStream* self)
    {
        return static_cast<int>(self->GetLength());
    }

    EXPORT wxInputStream* wxFilterInputStream_GetFilterInputStream(wxFilterInputStream* self)
    {
        return self->GetFilterInputStream();
    }

    EXPORT int wxFilterOutputStream_GetLength(wxFilterOutputStream* self)
    {
        return static_cast<int>(self->GetLength());
    }

    EXPORT wxOutputStream* wxFilterOutputStream_GetFilterOutputStream(wxFilterOutputStream* self)
    {
        return self->GetFilterOutputStream();
    }

    EXPORT void wxFilterOutputStream_Delete(wxFilterOutputStream* self)
    {
        delete self;
    }

    // -----------------------------------------------------------------------
    // wxFilterClassFactoryBase / wxFilterClassFactory
    // -----------------------------------------------------------------------

    EXPORT wxString* wxFilterClassFactoryBase_GetProtocol(wxFilterClassFactoryBase* self)
    {
        return new wxString(self->GetProtocol());
    }

    EXPORT wxString* wxFilterClassFactoryBase_GetProtocols(wxFilterClassFactoryBase* self, int type)
    {
        return new wxString(
            JoinProtocols(self->GetProtocols(static_cast<wxStreamProtocolType>(type))));
    }

    EXPORT int wxFilterClassFactoryBase_CanHandle(wxFilterClassFactoryBase* self,
                                                  wxString* protocol, int type)
    {
        return self->CanHandle(*protocol, static_cast<wxStreamProtocolType>(type));
    }

    EXPORT wxString* wxFilterClassFactoryBase_PopExtension(wxFilterClassFactoryBase* self,
                                                           wxString* location)
    {
        return new wxString(self->PopExtension(*location));
    }

    EXPORT wxFilterInputStream* wxFilterClassFactory_NewStreamInput(wxFilterClassFactory* self,
                                                                    wxInputStream* stream)
    {
        return self->NewStream(*stream);
    }

    EXPORT wxFilterOutputStream* wxFilterClassFactory_NewStreamOutput(wxFilterClassFactory* self,
                                                                      wxOutputStream* stream)
    {
        return self->NewStream(*stream);
    }

    EXPORT wxFilterClassFactory* wxFilterClassFactory_Find(wxString* protocol, int type)
    {
        return const_cast<wxFilterClassFactory*>(
            wxFilterClassFactory::Find(*protocol, static_cast<wxStreamProtocolType>(type)));
    }

    EXPORT wxFilterClassFactory* wxFilterClassFactory_GetFirst()
    {
        return const_cast<wxFilterClassFactory*>(wxFilterClassFactory::GetFirst());
    }

    EXPORT wxFilterClassFactory* wxFilterClassFactory_GetNext(wxFilterClassFactory* self)
    {
        return const_cast<wxFilterClassFactory*>(self->GetNext());
    }

    // -----------------------------------------------------------------------
    // wxArchiveClassFactory
    // -----------------------------------------------------------------------

    EXPORT wxArchiveEntry* wxArchiveClassFactory_NewEntry(wxArchiveClassFactory* self)
    {
        return self->NewEntry();
    }

    EXPORT wxArchiveInputStream* wxArchiveClassFactory_NewStreamInput(wxArchiveClassFactory* self,
                                                                      wxInputStream* stream)
    {
        return self->NewStream(*stream);
    }

    EXPORT wxArchiveOutputStream* wxArchiveClassFactory_NewStreamOutput(wxArchiveClassFactory* self,
                                                                        wxOutputStream* stream)
    {
        return self->NewStream(*stream);
    }

    EXPORT wxString* wxArchiveClassFactory_GetInternalName(wxArchiveClassFactory* self,
                                                           wxString* name, int format)
    {
        return new wxString(self->GetInternalName(*name, static_cast<wxPathFormat>(format)));
    }

    EXPORT wxArchiveClassFactory* wxArchiveClassFactory_Find(wxString* protocol, int type)
    {
        return const_cast<wxArchiveClassFactory*>(
            wxArchiveClassFactory::Find(*protocol, static_cast<wxStreamProtocolType>(type)));
    }

    EXPORT wxArchiveClassFactory* wxArchiveClassFactory_GetFirst()
    {
        return const_cast<wxArchiveClassFactory*>(wxArchiveClassFactory::GetFirst());
    }

    EXPORT wxArchiveClassFactory* wxArchiveClassFactory_GetNext(wxArchiveClassFactory* self)
    {
        return const_cast<wxArchiveClassFactory*>(self->GetNext());
    }

    // -----------------------------------------------------------------------
    // wxArchiveEntry
    // -----------------------------------------------------------------------

    EXPORT wxDateTime* wxArchiveEntry_GetDateTime(wxArchiveEntry* self)
    {
        return new wxDateTime(self->GetDateTime());
    }

    EXPORT int wxArchiveEntry_GetSize(wxArchiveEntry* self)
    {
        return static_cast<int>(self->GetSize());
    }

    EXPORT int wxArchiveEntry_GetOffset(wxArchiveEntry* self)
    {
        return static_cast<int>(self->GetOffset());
    }

    EXPORT int wxArchiveEntry_IsDir(wxArchiveEntry* self)
    {
        return self->IsDir();
    }

    EXPORT int wxArchiveEntry_IsReadOnly(wxArchiveEntry* self)
    {
        return self->IsReadOnly();
    }

    EXPORT wxString* wxArchiveEntry_GetInternalName(wxArchiveEntry* self)
    {
        return new wxString(self->GetInternalName());
    }

    EXPORT int wxArchiveEntry_GetInternalFormat(wxArchiveEntry* self)
    {
        return static_cast<int>(self->GetInternalFormat());
    }

    EXPORT wxString* wxArchiveEntry_GetName(wxArchiveEntry* self, int path_format)
    {
        return new wxString(self->GetName(static_cast<wxPathFormat>(path_format)));
    }

    EXPORT wxArchiveEntry* wxArchiveEntry_Clone(wxArchiveEntry* self)
    {
        return self->Clone();
    }

    EXPORT void wxArchiveEntry_Delete(wxArchiveEntry* self)
    {
        delete self;
    }

    EXPORT void wxArchiveEntry_SetDateTime(wxArchiveEntry* self, wxDateTime* dt)
    {
        self->SetDateTime(dt ? *dt : wxDateTime::Now());
    }

    EXPORT void wxArchiveEntry_SetSize(wxArchiveEntry* self, int size)
    {
        self->SetSize(static_cast<wxFileOffset>(size));
    }

    EXPORT void wxArchiveEntry_SetIsDir(wxArchiveEntry* self, bool is_dir)
    {
        self->SetIsDir(is_dir);
    }

    EXPORT void wxArchiveEntry_SetIsReadOnly(wxArchiveEntry* self, bool is_read_only)
    {
        self->SetIsReadOnly(is_read_only);
    }

    EXPORT void wxArchiveEntry_SetName(wxArchiveEntry* self, wxString* entry_name, int path_format)
    {
        self->SetName(*entry_name, static_cast<wxPathFormat>(path_format));
    }

    // -----------------------------------------------------------------------
    // wxArchiveInputStream
    // -----------------------------------------------------------------------

    EXPORT void wxArchiveInputStream_Delete(wxArchiveInputStream* self)
    {
        delete self;
    }

    EXPORT wxArchiveEntry* wxArchiveInputStream_GetNextEntry(wxArchiveInputStream* self)
    {
        return self->GetNextEntry();
    }

    EXPORT int wxArchiveInputStream_OpenEntry(wxArchiveInputStream* self, wxArchiveEntry* entry)
    {
        return self->OpenEntry(*entry);
    }

    EXPORT int wxArchiveInputStream_CloseEntry(wxArchiveInputStream* self)
    {
        return self->CloseEntry();
    }

    // -----------------------------------------------------------------------
    // wxArchiveOutputStream
    // -----------------------------------------------------------------------

    EXPORT void wxArchiveOutputStream_Delete(wxArchiveOutputStream* self)
    {
        delete self;
    }

    EXPORT int wxArchiveOutputStream_PutNextEntry(wxArchiveOutputStream* self,
                                                  wxArchiveEntry* entry)
    {
        return self->PutNextEntry(entry);
    }

    EXPORT int wxArchiveOutputStream_PutNextEntryDate(wxArchiveOutputStream* self,
                                                      wxString* entry_name, wxDateTime* dt,
                                                      int size)
    {
        return self->PutNextEntry(*entry_name, dt ? *dt : wxDateTime::Now(),
                                  static_cast<wxFileOffset>(size));
    }

    EXPORT int wxArchiveOutputStream_PutNextDirEntryDate(wxArchiveOutputStream* self,
                                                         wxString* entry_name, wxDateTime* dt)
    {
        return self->PutNextDirEntry(*entry_name, dt ? *dt : wxDateTime::Now());
    }

    EXPORT int wxArchiveOutputStream_CopyEntry(wxArchiveOutputStream* self, wxArchiveEntry* entry,
                                               wxArchiveInputStream* input_stream)
    {
        return self->CopyEntry(entry, *input_stream);
    }

    EXPORT int wxArchiveOutputStream_CopyArchiveMetaData(wxArchiveOutputStream* self,
                                                         wxArchiveInputStream* input_stream)
    {
        return self->CopyArchiveMetaData(*input_stream);
    }

    EXPORT int wxArchiveOutputStream_CloseEntry(wxArchiveOutputStream* self)
    {
        return self->CloseEntry();
    }

    // -----------------------------------------------------------------------
    // wxZipEntry
    // -----------------------------------------------------------------------

    EXPORT wxZipEntry* wxZipEntry_Create()
    {
        return new wxZipEntry();
    }

    EXPORT wxZipEntry* wxZipEntry_CreateNamed(wxString* entry_name)
    {
        return new wxZipEntry(*entry_name);
    }

    EXPORT void wxZipEntry_Delete(wxZipEntry* self)
    {
        delete self;
    }

    EXPORT wxZipEntry* wxZipEntry_Clone(wxZipEntry* self)
    {
        return self->Clone();
    }

    EXPORT int wxZipEntry_GetSize(wxZipEntry* self)
    {
        return static_cast<int>(self->GetSize());
    }

    EXPORT int wxZipEntry_GetOffset(wxZipEntry* self)
    {
        return static_cast<int>(self->GetOffset());
    }

    EXPORT int wxZipEntry_GetCompressedSize(wxZipEntry* self)
    {
        return static_cast<int>(self->GetCompressedSize());
    }

    EXPORT wxString* wxZipEntry_GetName(wxZipEntry* self, int path_format)
    {
        return new wxString(self->GetName(static_cast<wxPathFormat>(path_format)));
    }

    EXPORT wxString* wxZipEntry_GetInternalName(wxZipEntry* self)
    {
        return new wxString(self->GetInternalName());
    }

    EXPORT int wxZipEntry_GetMethod(wxZipEntry* self)
    {
        return self->GetMethod();
    }

    EXPORT int wxZipEntry_GetFlags(wxZipEntry* self)
    {
        return self->GetFlags();
    }

    EXPORT wxUint32 wxZipEntry_GetCrc(wxZipEntry* self)
    {
        return self->GetCrc();
    }

    EXPORT int wxZipEntry_GetSystemMadeBy(wxZipEntry* self)
    {
        return self->GetSystemMadeBy();
    }

    EXPORT wxUint32 wxZipEntry_GetExternalAttributes(wxZipEntry* self)
    {
        return self->GetExternalAttributes();
    }

    EXPORT int wxZipEntry_GetMode(wxZipEntry* self)
    {
        return self->GetMode();
    }

    EXPORT wxString* wxZipEntry_GetComment(wxZipEntry* self)
    {
        return new wxString(self->GetComment());
    }

    EXPORT int wxZipEntry_IsDir(wxZipEntry* self)
    {
        return self->IsDir();
    }

    EXPORT int wxZipEntry_IsText(wxZipEntry* self)
    {
        return self->IsText();
    }

    EXPORT int wxZipEntry_IsReadOnly(wxZipEntry* self)
    {
        return self->IsReadOnly();
    }

    EXPORT int wxZipEntry_IsMadeByUnix(wxZipEntry* self)
    {
        return self->IsMadeByUnix();
    }

    EXPORT void wxZipEntry_SetSize(wxZipEntry* self, int size)
    {
        self->SetSize(static_cast<wxFileOffset>(size));
    }

    EXPORT void wxZipEntry_SetMethod(wxZipEntry* self, int method)
    {
        self->SetMethod(method);
    }

    EXPORT void wxZipEntry_SetComment(wxZipEntry* self, wxString* comment)
    {
        self->SetComment(*comment);
    }

    EXPORT void wxZipEntry_SetExternalAttributes(wxZipEntry* self, wxUint32 attributes)
    {
        self->SetExternalAttributes(attributes);
    }

    EXPORT void wxZipEntry_SetSystemMadeBy(wxZipEntry* self, int system)
    {
        self->SetSystemMadeBy(system);
    }

    EXPORT void wxZipEntry_SetMode(wxZipEntry* self, int mode)
    {
        self->SetMode(mode);
    }

    EXPORT void wxZipEntry_SetName(wxZipEntry* self, wxString* entry_name, int path_format)
    {
        self->SetName(*entry_name, static_cast<wxPathFormat>(path_format));
    }

    EXPORT void wxZipEntry_SetIsDir(wxZipEntry* self, bool is_dir)
    {
        self->SetIsDir(is_dir);
    }

    EXPORT void wxZipEntry_SetIsReadOnly(wxZipEntry* self, bool is_read_only)
    {
        self->SetIsReadOnly(is_read_only);
    }

    EXPORT void wxZipEntry_SetIsText(wxZipEntry* self, bool is_text)
    {
        self->SetIsText(is_text);
    }

    // -----------------------------------------------------------------------
    // wxZipInputStream
    // -----------------------------------------------------------------------

    EXPORT wxZipInputStream* wxZipInputStream_Create(wxInputStream* stream)
    {
        return new wxZipInputStream(*stream);
    }

    EXPORT void wxZipInputStream_Delete(wxZipInputStream* self)
    {
        delete self;
    }

    EXPORT wxZipEntry* wxZipInputStream_GetNextEntry(wxZipInputStream* self)
    {
        return self->GetNextEntry();
    }

    EXPORT int wxZipInputStream_OpenEntry(wxZipInputStream* self, wxZipEntry* entry)
    {
        return self->OpenEntry(*entry);
    }

    EXPORT int wxZipInputStream_CloseEntry(wxZipInputStream* self)
    {
        return self->CloseEntry();
    }

    EXPORT wxString* wxZipInputStream_GetComment(wxZipInputStream* self)
    {
        return new wxString(self->GetComment());
    }

    EXPORT int wxZipInputStream_GetTotalEntries(wxZipInputStream* self)
    {
        return self->GetTotalEntries();
    }

    EXPORT int wxZipInputStream_GetLength(wxZipInputStream* self)
    {
        return static_cast<int>(self->GetLength());
    }

    // -----------------------------------------------------------------------
    // wxZipOutputStream
    // -----------------------------------------------------------------------

    EXPORT wxZipOutputStream* wxZipOutputStream_Create(wxOutputStream* stream, int level)
    {
        return new wxZipOutputStream(*stream, level);
    }

    EXPORT void wxZipOutputStream_Delete(wxZipOutputStream* self)
    {
        delete self;
    }

    EXPORT int wxZipOutputStream_PutNextEntry(wxZipOutputStream* self, wxString* entry_name,
                                              int size)
    {
        return self->PutNextEntry(*entry_name, wxDateTime::Now(), static_cast<wxFileOffset>(size));
    }

    EXPORT int wxZipOutputStream_PutNextEntryDate(wxZipOutputStream* self, wxString* entry_name,
                                                  wxDateTime* dt, int size)
    {
        return self->PutNextEntry(*entry_name, dt ? *dt : wxDateTime::Now(),
                                  static_cast<wxFileOffset>(size));
    }

    EXPORT int wxZipOutputStream_PutNextDirEntry(wxZipOutputStream* self, wxString* entry_name)
    {
        return self->PutNextDirEntry(*entry_name, wxDateTime::Now());
    }

    EXPORT int wxZipOutputStream_PutNextDirEntryDate(wxZipOutputStream* self, wxString* entry_name,
                                                     wxDateTime* dt)
    {
        return self->PutNextDirEntry(*entry_name, dt ? *dt : wxDateTime::Now());
    }

    EXPORT int wxZipOutputStream_PutEntry(wxZipOutputStream* self, wxZipEntry* entry)
    {
        return self->PutNextEntry(entry);
    }

    EXPORT int wxZipOutputStream_CopyEntry(wxZipOutputStream* self, wxZipEntry* entry,
                                           wxZipInputStream* input_stream)
    {
        return self->CopyEntry(entry, *input_stream);
    }

    EXPORT int wxZipOutputStream_CopyArchiveMetaData(wxZipOutputStream* self,
                                                     wxZipInputStream* input_stream)
    {
        return self->CopyArchiveMetaData(*input_stream);
    }

    EXPORT void wxZipOutputStream_Write(wxZipOutputStream* self, void* buffer, int size)
    {
        self->Write(buffer, static_cast<size_t>(size));
    }

    EXPORT void wxZipOutputStream_Sync(wxZipOutputStream* self)
    {
        self->Sync();
    }

    EXPORT int wxZipOutputStream_CloseEntry(wxZipOutputStream* self)
    {
        return self->CloseEntry();
    }

    EXPORT int wxZipOutputStream_Close(wxZipOutputStream* self)
    {
        return self->Close();
    }

    EXPORT void wxZipOutputStream_SetComment(wxZipOutputStream* self, wxString* comment)
    {
        self->SetComment(*comment);
    }

    EXPORT int wxZipOutputStream_GetLevel(wxZipOutputStream* self)
    {
        return self->GetLevel();
    }

    EXPORT void wxZipOutputStream_SetLevel(wxZipOutputStream* self, int level)
    {
        self->SetLevel(level);
    }

    EXPORT void wxZipOutputStream_SetFormat(wxZipOutputStream* self, int format)
    {
        self->SetFormat(static_cast<wxZipArchiveFormat>(format));
    }

    EXPORT int wxZipOutputStream_GetFormat(wxZipOutputStream* self)
    {
        return static_cast<int>(self->GetFormat());
    }

    // -----------------------------------------------------------------------
    // wxZlibInputStream / wxZlibOutputStream
    // -----------------------------------------------------------------------

    EXPORT wxZlibInputStream* wxZlibInputStream_Create(wxInputStream* stream, int flags)
    {
        return new wxZlibInputStream(*stream, flags);
    }

    EXPORT void wxZlibInputStream_Delete(wxZlibInputStream* self)
    {
        delete self;
    }

    EXPORT int wxZlibInputStream_CanHandleGZip()
    {
        return wxZlibInputStream::CanHandleGZip();
    }

    EXPORT int wxZlibInputStream_SetDictionary(wxZlibInputStream* self, void* data, int size)
    {
        return self->SetDictionary(static_cast<const char*>(data), static_cast<size_t>(size));
    }

    EXPORT int wxZlibInputStream_GetLength(wxZlibInputStream* self)
    {
        return static_cast<int>(self->GetLength());
    }

    EXPORT wxZlibOutputStream* wxZlibOutputStream_Create(wxOutputStream* stream, int level,
                                                         int flags)
    {
        return new wxZlibOutputStream(*stream, level, flags);
    }

    EXPORT void wxZlibOutputStream_Delete(wxZlibOutputStream* self)
    {
        delete self;
    }

    EXPORT int wxZlibOutputStream_CanHandleGZip()
    {
        return wxZlibOutputStream::CanHandleGZip();
    }

    EXPORT int wxZlibOutputStream_SetDictionary(wxZlibOutputStream* self, void* data, int size)
    {
        return self->SetDictionary(static_cast<const char*>(data), static_cast<size_t>(size));
    }

    EXPORT void wxZlibOutputStream_Sync(wxZlibOutputStream* self)
    {
        self->Sync();
    }

    EXPORT int wxZlibOutputStream_Close(wxZlibOutputStream* self)
    {
        return self->Close();
    }

    EXPORT int wxZlibOutputStream_GetLength(wxZlibOutputStream* self)
    {
        return static_cast<int>(self->GetLength());
    }

    // -----------------------------------------------------------------------
    // wxTarEntry
    // -----------------------------------------------------------------------

    EXPORT wxTarEntry* wxTarEntry_Create()
    {
        return new wxTarEntry();
    }

    EXPORT wxTarEntry* wxTarEntry_CreateNamed(wxString* entry_name)
    {
        return new wxTarEntry(*entry_name);
    }

    EXPORT void wxTarEntry_Delete(wxTarEntry* self)
    {
        delete self;
    }

    EXPORT wxTarEntry* wxTarEntry_Clone(wxTarEntry* self)
    {
        return self->Clone();
    }

    EXPORT wxString* wxTarEntry_GetName(wxTarEntry* self, int path_format)
    {
        return new wxString(self->GetName(static_cast<wxPathFormat>(path_format)));
    }

    EXPORT wxString* wxTarEntry_GetInternalName(wxTarEntry* self)
    {
        return new wxString(self->GetInternalName());
    }

    EXPORT int wxTarEntry_GetMode(wxTarEntry* self)
    {
        return self->GetMode();
    }

    EXPORT int wxTarEntry_GetUserId(wxTarEntry* self)
    {
        return self->GetUserId();
    }

    EXPORT int wxTarEntry_GetGroupId(wxTarEntry* self)
    {
        return self->GetGroupId();
    }

    EXPORT int wxTarEntry_GetSize(wxTarEntry* self)
    {
        return static_cast<int>(self->GetSize());
    }

    EXPORT int wxTarEntry_GetOffset(wxTarEntry* self)
    {
        return static_cast<int>(self->GetOffset());
    }

    EXPORT int wxTarEntry_GetTypeFlag(wxTarEntry* self)
    {
        return self->GetTypeFlag();
    }

    EXPORT wxString* wxTarEntry_GetLinkName(wxTarEntry* self)
    {
        return new wxString(self->GetLinkName());
    }

    EXPORT wxString* wxTarEntry_GetUserName(wxTarEntry* self)
    {
        return new wxString(self->GetUserName());
    }

    EXPORT wxString* wxTarEntry_GetGroupName(wxTarEntry* self)
    {
        return new wxString(self->GetGroupName());
    }

    EXPORT int wxTarEntry_GetDevMajor(wxTarEntry* self)
    {
        return self->GetDevMajor();
    }

    EXPORT int wxTarEntry_GetDevMinor(wxTarEntry* self)
    {
        return self->GetDevMinor();
    }

    EXPORT int wxTarEntry_IsDir(wxTarEntry* self)
    {
        return self->IsDir();
    }

    EXPORT int wxTarEntry_IsReadOnly(wxTarEntry* self)
    {
        return self->IsReadOnly();
    }

    EXPORT void wxTarEntry_SetName(wxTarEntry* self, wxString* entry_name, int path_format)
    {
        self->SetName(*entry_name, static_cast<wxPathFormat>(path_format));
    }

    EXPORT void wxTarEntry_SetUserId(wxTarEntry* self, int user_id)
    {
        self->SetUserId(user_id);
    }

    EXPORT void wxTarEntry_SetGroupId(wxTarEntry* self, int group_id)
    {
        self->SetGroupId(group_id);
    }

    EXPORT void wxTarEntry_SetMode(wxTarEntry* self, int mode)
    {
        self->SetMode(mode);
    }

    EXPORT void wxTarEntry_SetSize(wxTarEntry* self, int size)
    {
        self->SetSize(static_cast<wxFileOffset>(size));
    }

    EXPORT void wxTarEntry_SetTypeFlag(wxTarEntry* self, int type_flag)
    {
        self->SetTypeFlag(type_flag);
    }

    EXPORT void wxTarEntry_SetLinkName(wxTarEntry* self, wxString* link_name)
    {
        self->SetLinkName(*link_name);
    }

    EXPORT void wxTarEntry_SetUserName(wxTarEntry* self, wxString* user_name)
    {
        self->SetUserName(*user_name);
    }

    EXPORT void wxTarEntry_SetGroupName(wxTarEntry* self, wxString* group_name)
    {
        self->SetGroupName(*group_name);
    }

    EXPORT void wxTarEntry_SetDevMajor(wxTarEntry* self, int dev_major)
    {
        self->SetDevMajor(dev_major);
    }

    EXPORT void wxTarEntry_SetDevMinor(wxTarEntry* self, int dev_minor)
    {
        self->SetDevMinor(dev_minor);
    }

    EXPORT void wxTarEntry_SetIsDir(wxTarEntry* self, bool is_dir)
    {
        self->SetIsDir(is_dir);
    }

    EXPORT void wxTarEntry_SetIsReadOnly(wxTarEntry* self, bool is_read_only)
    {
        self->SetIsReadOnly(is_read_only);
    }

    // -----------------------------------------------------------------------
    // wxTarInputStream
    // -----------------------------------------------------------------------

    EXPORT wxTarInputStream* wxTarInputStream_Create(wxInputStream* stream)
    {
        return new wxTarInputStream(*stream);
    }

    EXPORT void wxTarInputStream_Delete(wxTarInputStream* self)
    {
        delete self;
    }

    EXPORT wxTarEntry* wxTarInputStream_GetNextEntry(wxTarInputStream* self)
    {
        return self->GetNextEntry();
    }

    EXPORT int wxTarInputStream_OpenEntry(wxTarInputStream* self, wxTarEntry* entry)
    {
        return self->OpenEntry(*entry);
    }

    EXPORT int wxTarInputStream_CloseEntry(wxTarInputStream* self)
    {
        return self->CloseEntry();
    }

    EXPORT int wxTarInputStream_GetLength(wxTarInputStream* self)
    {
        return static_cast<int>(self->GetLength());
    }

    EXPORT int wxTarInputStream_GetMaxExtendedHeaderSize()
    {
        return static_cast<int>(wxTarInputStream::GetMaxExtendedHeaderSize());
    }

    EXPORT void wxTarInputStream_SetMaxExtendedHeaderSize(int size)
    {
        wxTarInputStream::SetMaxExtendedHeaderSize(static_cast<size_t>(size));
    }

    // -----------------------------------------------------------------------
    // wxTarOutputStream
    // -----------------------------------------------------------------------

    EXPORT wxTarOutputStream* wxTarOutputStream_Create(wxOutputStream* stream, int format)
    {
        return new wxTarOutputStream(*stream, static_cast<wxTarFormat>(format));
    }

    EXPORT void wxTarOutputStream_Delete(wxTarOutputStream* self)
    {
        delete self;
    }

    EXPORT int wxTarOutputStream_PutNextEntry(wxTarOutputStream* self, wxString* entry_name,
                                              int size)
    {
        return self->PutNextEntry(*entry_name, wxDateTime::Now(), static_cast<wxFileOffset>(size));
    }

    EXPORT int wxTarOutputStream_PutNextEntryDate(wxTarOutputStream* self, wxString* entry_name,
                                                  wxDateTime* dt, int size)
    {
        return self->PutNextEntry(*entry_name, dt ? *dt : wxDateTime::Now(),
                                  static_cast<wxFileOffset>(size));
    }

    EXPORT int wxTarOutputStream_PutNextDirEntry(wxTarOutputStream* self, wxString* entry_name)
    {
        return self->PutNextDirEntry(*entry_name, wxDateTime::Now());
    }

    EXPORT int wxTarOutputStream_PutNextDirEntryDate(wxTarOutputStream* self, wxString* entry_name,
                                                     wxDateTime* dt)
    {
        return self->PutNextDirEntry(*entry_name, dt ? *dt : wxDateTime::Now());
    }

    EXPORT int wxTarOutputStream_PutEntry(wxTarOutputStream* self, wxTarEntry* entry)
    {
        return self->PutNextEntry(entry);
    }

    EXPORT int wxTarOutputStream_CopyEntry(wxTarOutputStream* self, wxTarEntry* entry,
                                           wxTarInputStream* input_stream)
    {
        return self->CopyEntry(entry, *input_stream);
    }

    EXPORT int wxTarOutputStream_CopyArchiveMetaData(wxTarOutputStream* self,
                                                     wxTarInputStream* input_stream)
    {
        return self->CopyArchiveMetaData(*input_stream);
    }

    EXPORT void wxTarOutputStream_Write(wxTarOutputStream* self, void* buffer, int size)
    {
        self->Write(buffer, static_cast<size_t>(size));
    }

    EXPORT void wxTarOutputStream_Sync(wxTarOutputStream* self)
    {
        self->Sync();
    }

    EXPORT int wxTarOutputStream_CloseEntry(wxTarOutputStream* self)
    {
        return self->CloseEntry();
    }

    EXPORT int wxTarOutputStream_Close(wxTarOutputStream* self)
    {
        return self->Close();
    }

    EXPORT int wxTarOutputStream_IsSeekable(wxTarOutputStream* self)
    {
        return self->IsSeekable();
    }

    EXPORT void wxTarOutputStream_SetBlockingFactor(wxTarOutputStream* self, int factor)
    {
        self->SetBlockingFactor(factor);
    }

    EXPORT int wxTarOutputStream_GetBlockingFactor(wxTarOutputStream* self)
    {
        return self->GetBlockingFactor();
    }

    // ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
    EXPORT int wxFFile_IsOpened(void* pObject)
    {
        return ((wxFFile*) pObject)->IsOpened();
    }

    EXPORT int wxFFile_ReadAll(void* pObject, void* str, void* conv)
    {
        return ((wxFFile*) pObject)->ReadAll((wxString*) str, *(wxMBConv*) conv);
    }

    EXPORT int wxFilterOutputStream_Close(void* pObject)
    {
        return ((wxFilterOutputStream*) pObject)->Close();
    }
}
