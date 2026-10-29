// Base-utility file, stream and compression wrappers: wxTextFile, wxTempFile,
// wxStringTokenizer, wxStreamBuffer and the zip, zlib and tar archive streams.
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <wx/stream.h>
#include <wx/tarstrm.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>

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

    EXPORT bool wxTextFile_Exists(wxTextFile* self)
    {
        return self->Exists();
    }

    EXPORT bool wxTextFile_CreateOnDisk(wxTextFile* self)
    {
        return self->Create();
    }

    EXPORT bool wxTextFile_CreateOnDiskNamed(wxTextFile* self, wxString* file_name)
    {
        return self->Create(*file_name);
    }

    EXPORT bool wxTextFile_Open(wxTextFile* self)
    {
        return self->Open();
    }

    EXPORT bool wxTextFile_OpenNamed(wxTextFile* self, wxString* file_name)
    {
        return self->Open(*file_name);
    }

    EXPORT bool wxTextFile_Close(wxTextFile* self)
    {
        return self->Close();
    }

    EXPORT bool wxTextFile_IsOpened(wxTextFile* self)
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

    EXPORT bool wxTextFile_Eof(wxTextFile* self)
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

    EXPORT bool wxTextFile_Write(wxTextFile* self)
    {
        return self->Write();
    }

    EXPORT bool wxTextFile_WriteAs(wxTextFile* self, int line_type)
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

    EXPORT bool wxTempFile_Open(wxTempFile* self, wxString* file_name)
    {
        return self->Open(*file_name);
    }

    EXPORT bool wxTempFile_IsOpened(wxTempFile* self)
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

    EXPORT bool wxTempFile_WriteBytes(wxTempFile* self, void* buffer, int size)
    {
        return self->Write(buffer, static_cast<size_t>(size));
    }

    EXPORT bool wxTempFile_WriteText(wxTempFile* self, wxString* text)
    {
        return self->Write(*text);
    }

    EXPORT bool wxTempFile_Flush(wxTempFile* self)
    {
        return self->Flush();
    }

    EXPORT bool wxTempFile_Commit(wxTempFile* self)
    {
        return self->Commit();
    }

    EXPORT void wxTempFile_Discard(wxTempFile* self)
    {
        self->Discard();
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

    EXPORT bool wxStringTokenizer_HasMoreTokens(wxStringTokenizer* self)
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

    EXPORT bool wxStringTokenizer_AllowEmpty(wxStringTokenizer* self)
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

    EXPORT bool wxStreamBuffer_FlushBuffer(wxStreamBuffer* self)
    {
        return self->FlushBuffer();
    }

    EXPORT bool wxStreamBuffer_FillBuffer(wxStreamBuffer* self)
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

    EXPORT bool wxStreamBuffer_HasBuffer(wxStreamBuffer* self)
    {
        return self->HasBuffer();
    }

    EXPORT bool wxStreamBuffer_IsFixed(wxStreamBuffer* self)
    {
        return self->IsFixed();
    }

    EXPORT bool wxStreamBuffer_IsFlushable(wxStreamBuffer* self)
    {
        return self->IsFlushable();
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

    EXPORT bool wxZipEntry_IsDir(wxZipEntry* self)
    {
        return self->IsDir();
    }

    EXPORT bool wxZipEntry_IsText(wxZipEntry* self)
    {
        return self->IsText();
    }

    EXPORT bool wxZipEntry_IsReadOnly(wxZipEntry* self)
    {
        return self->IsReadOnly();
    }

    EXPORT bool wxZipEntry_IsMadeByUnix(wxZipEntry* self)
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

    EXPORT bool wxZipInputStream_OpenEntry(wxZipInputStream* self, wxZipEntry* entry)
    {
        return self->OpenEntry(*entry);
    }

    EXPORT bool wxZipInputStream_CloseEntry(wxZipInputStream* self)
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

    EXPORT bool wxZipOutputStream_PutNextEntry(wxZipOutputStream* self, wxString* entry_name,
                                               int size)
    {
        return self->PutNextEntry(*entry_name, wxDateTime::Now(), static_cast<wxFileOffset>(size));
    }

    EXPORT bool wxZipOutputStream_PutNextDirEntry(wxZipOutputStream* self, wxString* entry_name)
    {
        return self->PutNextDirEntry(*entry_name, wxDateTime::Now());
    }

    EXPORT bool wxZipOutputStream_PutEntry(wxZipOutputStream* self, wxZipEntry* entry)
    {
        return self->PutNextEntry(entry);
    }

    EXPORT bool wxZipOutputStream_CopyEntry(wxZipOutputStream* self, wxZipEntry* entry,
                                            wxZipInputStream* input_stream)
    {
        return self->CopyEntry(entry, *input_stream);
    }

    EXPORT bool wxZipOutputStream_CopyArchiveMetaData(wxZipOutputStream* self,
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

    EXPORT bool wxZipOutputStream_CloseEntry(wxZipOutputStream* self)
    {
        return self->CloseEntry();
    }

    EXPORT bool wxZipOutputStream_Close(wxZipOutputStream* self)
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

    EXPORT bool wxZlibInputStream_CanHandleGZip()
    {
        return wxZlibInputStream::CanHandleGZip();
    }

    EXPORT bool wxZlibInputStream_SetDictionary(wxZlibInputStream* self, void* data, int size)
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

    EXPORT bool wxZlibOutputStream_CanHandleGZip()
    {
        return wxZlibOutputStream::CanHandleGZip();
    }

    EXPORT bool wxZlibOutputStream_SetDictionary(wxZlibOutputStream* self, void* data, int size)
    {
        return self->SetDictionary(static_cast<const char*>(data), static_cast<size_t>(size));
    }

    EXPORT void wxZlibOutputStream_Sync(wxZlibOutputStream* self)
    {
        self->Sync();
    }

    EXPORT bool wxZlibOutputStream_Close(wxZlibOutputStream* self)
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

    EXPORT bool wxTarEntry_IsDir(wxTarEntry* self)
    {
        return self->IsDir();
    }

    EXPORT bool wxTarEntry_IsReadOnly(wxTarEntry* self)
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

    EXPORT bool wxTarInputStream_OpenEntry(wxTarInputStream* self, wxTarEntry* entry)
    {
        return self->OpenEntry(*entry);
    }

    EXPORT bool wxTarInputStream_CloseEntry(wxTarInputStream* self)
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

    EXPORT bool wxTarOutputStream_PutNextEntry(wxTarOutputStream* self, wxString* entry_name,
                                               int size)
    {
        return self->PutNextEntry(*entry_name, wxDateTime::Now(), static_cast<wxFileOffset>(size));
    }

    EXPORT bool wxTarOutputStream_PutNextDirEntry(wxTarOutputStream* self, wxString* entry_name)
    {
        return self->PutNextDirEntry(*entry_name, wxDateTime::Now());
    }

    EXPORT bool wxTarOutputStream_PutEntry(wxTarOutputStream* self, wxTarEntry* entry)
    {
        return self->PutNextEntry(entry);
    }

    EXPORT bool wxTarOutputStream_CopyEntry(wxTarOutputStream* self, wxTarEntry* entry,
                                            wxTarInputStream* input_stream)
    {
        return self->CopyEntry(entry, *input_stream);
    }

    EXPORT bool wxTarOutputStream_CopyArchiveMetaData(wxTarOutputStream* self,
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

    EXPORT bool wxTarOutputStream_CloseEntry(wxTarOutputStream* self)
    {
        return self->CloseEntry();
    }

    EXPORT bool wxTarOutputStream_Close(wxTarOutputStream* self)
    {
        return self->Close();
    }

    EXPORT bool wxTarOutputStream_IsSeekable(wxTarOutputStream* self)
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
}
