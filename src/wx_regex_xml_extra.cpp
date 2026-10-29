// Base-utility regular expression, XML, URI, base64 and memory-buffer wrappers: wxRegEx,
// wxXmlDocument, wxURI, wxMemoryBuffer and the base64 free functions.
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <wx/mstream.h>
#include <wx/regex.h>
#include <wx/uri.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>

#include <cstdlib>
#include <tuple>

// The base64 decoder returns a malloc()-allocated buffer so the caller can release it with
// wxCFree() from another translation unit; see the allocator contract in
// include/kwx_regex_xml_extra.h.

// Clamp a negative index coming from a foreign runtime to the first match.
[[nodiscard]] static size_t ClampMatchIndex(int index)
{
    return (index < 0) ? 0U : static_cast<size_t>(index);
}

extern "C"
{
    // -----------------------------------------------------------------------
    // wxRegEx
    // -----------------------------------------------------------------------

    EXPORT wxRegEx* wxRegEx_Create()
    {
        return new wxRegEx();
    }

    EXPORT wxRegEx* wxRegEx_CreateCompiled(wxString* pattern, int flags)
    {
        return new wxRegEx(*pattern, flags);
    }

    EXPORT void wxRegEx_Delete(wxRegEx* self)
    {
        delete self;
    }

    EXPORT bool wxRegEx_Compile(wxRegEx* self, wxString* pattern, int flags)
    {
        return self->Compile(*pattern, flags);
    }

    EXPORT bool wxRegEx_IsValid(wxRegEx* self)
    {
        return self->IsValid();
    }

    EXPORT bool wxRegEx_Matches(wxRegEx* self, wxString* text, int flags)
    {
        return self->Matches(*text, flags);
    }

    EXPORT bool wxRegEx_MatchesFrom(wxRegEx* self, wxString* text, int start, int flags)
    {
        const size_t offset = (start < 0) ? 0U : static_cast<size_t>(start);
        return self->Matches(text->Mid(offset), flags);
    }

    EXPORT int wxRegEx_GetMatchCount(wxRegEx* self)
    {
        return static_cast<int>(self->GetMatchCount());
    }

    EXPORT wxString* wxRegEx_GetMatch(wxRegEx* self, wxString* text, int index)
    {
        return new wxString(self->GetMatch(*text, ClampMatchIndex(index)));
    }

    EXPORT int wxRegEx_GetMatchStart(wxRegEx* self, int index)
    {
        size_t start = 0;
        size_t length = 0;
        if (!self->GetMatch(&start, &length, ClampMatchIndex(index)))
        {
            return -1;
        }
        return static_cast<int>(start);
    }

    EXPORT int wxRegEx_GetMatchEnd(wxRegEx* self, int index)
    {
        size_t start = 0;
        size_t length = 0;
        if (!self->GetMatch(&start, &length, ClampMatchIndex(index)))
        {
            return -1;
        }
        return static_cast<int>(start + length);
    }

    EXPORT int wxRegEx_Replace(wxRegEx* self, wxString* text, wxString* replacement)
    {
        return self->Replace(text, *replacement);
    }

    EXPORT int wxRegEx_ReplaceAll(wxRegEx* self, wxString* text, wxString* replacement)
    {
        return self->ReplaceAll(text, *replacement);
    }

    EXPORT int wxRegEx_ReplaceFirst(wxRegEx* self, wxString* text, wxString* replacement)
    {
        return self->ReplaceFirst(text, *replacement);
    }

    // -----------------------------------------------------------------------
    // wxXmlDocument
    // -----------------------------------------------------------------------

    EXPORT wxXmlDocument* wxXmlDocument_Create()
    {
        return new wxXmlDocument();
    }

    EXPORT wxXmlDocument* wxXmlDocument_CreateFromFile(wxString* file_name, int flags)
    {
        wxXmlDocument* document = new wxXmlDocument();
        std::ignore = document->Load(*file_name, flags);
        return document;
    }

    EXPORT wxXmlDocument* wxXmlDocument_CreateFromString(wxString* text, int flags)
    {
        const wxScopedCharBuffer utf8_text = text->utf8_str();
        wxMemoryInputStream stream(utf8_text.data(), utf8_text.length());
        wxXmlDocument* document = new wxXmlDocument();
        std::ignore = document->Load(stream, flags);
        return document;
    }

    EXPORT void wxXmlDocument_Delete(wxXmlDocument* self)
    {
        delete self;
    }

    EXPORT bool wxXmlDocument_Load(wxXmlDocument* self, wxString* file_name, int flags)
    {
        return self->Load(*file_name, flags);
    }

    EXPORT bool wxXmlDocument_LoadFromString(wxXmlDocument* self, wxString* text, int flags)
    {
        const wxScopedCharBuffer utf8_text = text->utf8_str();
        wxMemoryInputStream stream(utf8_text.data(), utf8_text.length());
        return self->Load(stream, flags);
    }

    EXPORT bool wxXmlDocument_Save(wxXmlDocument* self, wxString* file_name, int indent_step)
    {
        return self->Save(*file_name, indent_step);
    }

    EXPORT wxString* wxXmlDocument_SaveToString(wxXmlDocument* self, int indent_step)
    {
        wxMemoryOutputStream stream;
        if (!self->Save(stream, indent_step))
        {
            return new wxString();
        }

        const size_t size = static_cast<size_t>(stream.GetSize());
        if (size == 0)
        {
            return new wxString();
        }

        wxCharBuffer buffer(size);
        std::ignore = stream.CopyTo(buffer.data(), size);
        return new wxString(wxString::FromUTF8(buffer.data(), size));
    }

    EXPORT wxXmlNode* wxXmlDocument_GetRoot(wxXmlDocument* self)
    {
        return self->GetRoot();
    }

    EXPORT void wxXmlDocument_SetRoot(wxXmlDocument* self, wxXmlNode* root)
    {
        self->SetRoot(root);
    }

    EXPORT wxXmlNode* wxXmlDocument_DetachRoot(wxXmlDocument* self)
    {
        return self->DetachRoot();
    }

    EXPORT wxString* wxXmlDocument_GetVersion(wxXmlDocument* self)
    {
        return new wxString(self->GetVersion());
    }

    EXPORT void wxXmlDocument_SetVersion(wxXmlDocument* self, wxString* version)
    {
        self->SetVersion(*version);
    }

    EXPORT wxString* wxXmlDocument_GetFileEncoding(wxXmlDocument* self)
    {
        return new wxString(self->GetFileEncoding());
    }

    EXPORT void wxXmlDocument_SetFileEncoding(wxXmlDocument* self, wxString* encoding)
    {
        self->SetFileEncoding(*encoding);
    }

    EXPORT int wxXmlDocument_GetFileType(wxXmlDocument* self)
    {
        return static_cast<int>(self->GetFileType());
    }

    EXPORT void wxXmlDocument_SetFileType(wxXmlDocument* self, int file_type)
    {
        self->SetFileType(static_cast<wxTextFileType>(file_type));
    }

    EXPORT void wxXmlDocument_AppendToProlog(wxXmlDocument* self, wxXmlNode* node)
    {
        self->AppendToProlog(node);
    }

    EXPORT bool wxXmlDocument_AppendChild(wxXmlDocument* self, wxXmlNode* child)
    {
        wxXmlNode* root = self->GetRoot();
        if (root == nullptr)
        {
            return false;
        }
        root->AddChild(child);
        return true;
    }

    EXPORT bool wxXmlDocument_IsOk(wxXmlDocument* self)
    {
        return self->IsOk();
    }

    // -----------------------------------------------------------------------
    // wxURI
    // -----------------------------------------------------------------------

    EXPORT wxURI* wxURI_Create()
    {
        return new wxURI();
    }

    EXPORT wxURI* wxURI_CreateFromString(wxString* uri_text)
    {
        return new wxURI(*uri_text);
    }

    EXPORT void wxURI_Delete(wxURI* self)
    {
        delete self;
    }

    EXPORT bool wxURI_Parse(wxURI* self, wxString* uri_text)
    {
        return self->Create(*uri_text);
    }

    EXPORT bool wxURI_IsEmpty(wxURI* self)
    {
        return self->IsEmpty();
    }

    EXPORT bool wxURI_HasScheme(wxURI* self)
    {
        return self->HasScheme();
    }

    EXPORT bool wxURI_HasUserInfo(wxURI* self)
    {
        return self->HasUserInfo();
    }

    EXPORT bool wxURI_HasServer(wxURI* self)
    {
        return self->HasServer();
    }

    EXPORT bool wxURI_HasPort(wxURI* self)
    {
        return self->HasPort();
    }

    EXPORT bool wxURI_HasPath(wxURI* self)
    {
        return self->HasPath();
    }

    EXPORT bool wxURI_HasQuery(wxURI* self)
    {
        return self->HasQuery();
    }

    EXPORT bool wxURI_HasFragment(wxURI* self)
    {
        return self->HasFragment();
    }

    EXPORT wxString* wxURI_GetScheme(wxURI* self)
    {
        return new wxString(self->GetScheme());
    }

    EXPORT wxString* wxURI_GetPath(wxURI* self)
    {
        return new wxString(self->GetPath());
    }

    EXPORT wxString* wxURI_GetQuery(wxURI* self)
    {
        return new wxString(self->GetQuery());
    }

    EXPORT wxString* wxURI_GetFragment(wxURI* self)
    {
        return new wxString(self->GetFragment());
    }

    EXPORT wxString* wxURI_GetPort(wxURI* self)
    {
        return new wxString(self->GetPort());
    }

    EXPORT wxString* wxURI_GetUserInfo(wxURI* self)
    {
        return new wxString(self->GetUserInfo());
    }

    EXPORT wxString* wxURI_GetServer(wxURI* self)
    {
        return new wxString(self->GetServer());
    }

    EXPORT wxString* wxURI_GetUser(wxURI* self)
    {
        return new wxString(self->GetUser());
    }

    EXPORT wxString* wxURI_GetPassword(wxURI* self)
    {
        return new wxString(self->GetPassword());
    }

    EXPORT int wxURI_GetHostType(wxURI* self)
    {
        return static_cast<int>(self->GetHostType());
    }

    EXPORT void wxURI_SetUserAndPassword(wxURI* self, wxString* user, wxString* password)
    {
        self->SetUserAndPassword(*user, *password);
    }

    EXPORT wxString* wxURI_BuildURI(wxURI* self)
    {
        return new wxString(self->BuildURI());
    }

    EXPORT wxString* wxURI_BuildUnescapedURI(wxURI* self)
    {
        return new wxString(self->BuildUnescapedURI());
    }

    EXPORT wxString* wxURI_Unescape(wxString* escaped_uri)
    {
        return new wxString(wxURI::Unescape(*escaped_uri));
    }

    EXPORT void wxURI_Resolve(wxURI* self, wxURI* base, int flags)
    {
        self->Resolve(*base, flags);
    }

    EXPORT bool wxURI_IsReference(wxURI* self)
    {
        return self->IsReference();
    }

    EXPORT bool wxURI_IsRelative(wxURI* self)
    {
        return self->IsRelative();
    }

    // -----------------------------------------------------------------------
    // wxMemoryBuffer
    // -----------------------------------------------------------------------

    EXPORT wxMemoryBuffer* wxMemoryBuffer_Create()
    {
        return new wxMemoryBuffer();
    }

    EXPORT void wxMemoryBuffer_Delete(wxMemoryBuffer* self)
    {
        delete self;
    }

    EXPORT void* wxMemoryBuffer_GetData(wxMemoryBuffer* self)
    {
        return self->GetData();
    }

    EXPORT size_t wxMemoryBuffer_GetDataLen(wxMemoryBuffer* self)
    {
        return self->GetDataLen();
    }

    EXPORT size_t wxMemoryBuffer_GetBufSize(wxMemoryBuffer* self)
    {
        return self->GetBufSize();
    }

    EXPORT void wxMemoryBuffer_AppendData(wxMemoryBuffer* self, void* data, size_t length)
    {
        self->AppendData(data, length);
    }

    EXPORT void wxMemoryBuffer_AppendByte(wxMemoryBuffer* self, char value)
    {
        self->AppendByte(value);
    }

    EXPORT void wxMemoryBuffer_SetDataLen(wxMemoryBuffer* self, size_t length)
    {
        self->SetDataLen(length);
    }

    EXPORT void wxMemoryBuffer_Clear(wxMemoryBuffer* self)
    {
        self->Clear();
    }

    // -----------------------------------------------------------------------
    // base64 free functions
    // -----------------------------------------------------------------------

    EXPORT wxString* wxBase64EncodeBuffer(void* source, size_t src_length)
    {
        if (source == nullptr)
        {
            return new wxString();
        }
        return new wxString(wxBase64Encode(source, src_length));
    }

    EXPORT void* wxBase64DecodeBuffer(wxString* text, int mode, size_t* decoded_length)
    {
        if (decoded_length != nullptr)
        {
            *decoded_length = 0;
        }

        const wxBase64DecodeMode decode_mode =
            (mode >= static_cast<int>(wxBase64DecodeMode_Strict) &&
             mode <= static_cast<int>(wxBase64DecodeMode_Relaxed)) ?
                static_cast<wxBase64DecodeMode>(mode) :
                wxBase64DecodeMode_Strict;

        const size_t buffer_size = wxBase64DecodedSize(text->length());
        char* buffer = static_cast<char*>(malloc(buffer_size + 1));
        if (buffer == nullptr)
        {
            return nullptr;
        }

        const size_t decoded_size = wxBase64Decode(buffer, buffer_size, *text, decode_mode);
        if (decoded_size == wxCONV_FAILED)
        {
            free(buffer);
            return nullptr;
        }

        buffer[decoded_size] = '\0';
        if (decoded_length != nullptr)
        {
            *decoded_length = decoded_size;
        }
        return buffer;
    }

    EXPORT size_t wxBase64EncodedSizeOf(size_t src_length)
    {
        return wxBase64EncodedSize(src_length);
    }

    EXPORT size_t wxBase64DecodedSizeOf(size_t encoded_length)
    {
        return wxBase64DecodedSize(encoded_length);
    }
}
