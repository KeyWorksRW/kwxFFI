#include "wrapper.h"
#include <wx/encconv.h>
#include <wx/fontenum.h>
#include <wx/fontmap.h>

extern "C"
{
    typedef int (*TTextEnum)(void* self, void* _txt);
}

class kwxFontEnumerator : public wxFontEnumerator
{
private:
    TTextEnum func;
    void* EiffelObject;

public:
    kwxFontEnumerator(void* self, void* _fnc) : wxFontEnumerator()
    {
        func = (TTextEnum) _fnc;
        EiffelObject = self;
    }

    virtual bool OnFacename(const wxString& facename)
    {
        return func(EiffelObject, (void*) facename.wchar_str()) != 0;
    }
    virtual bool OnFontEncoding(const wxString& WXUNUSED(facename), const wxString& encoding)
    {
        return func(EiffelObject, (void*) encoding.wchar_str()) != 0;
    }
};

extern "C"
{
    EXPORT wxFont* wxFont_Create(int pointSize, int family, int style, int weight, bool underlined,
                                 wxString* face, int enc)
    {
        return new wxFont(pointSize, (wxFontFamily) family, (wxFontStyle) style,
                          (wxFontWeight) weight, underlined, *face, (wxFontEncoding) enc);
    }

    EXPORT wxFont* wxFont_CreateDefault()
    {
        return new wxFont();
    }

    EXPORT void* wxFont_CreateFromStock(int id)
    {
        switch (id)
        {
            case 0:
                return (void*) wxITALIC_FONT;
            case 1:
                return (void*) wxNORMAL_FONT;
            case 2:
                return (void*) wxSMALL_FONT;
            case 3:
                return (void*) wxSWISS_FONT;
        }

        return nullptr;
    }

    EXPORT void wxFont_Delete(wxFont* self)
    {
        delete self;
    }

    EXPORT bool wxFont_IsOk(wxFont* self)
    {
        return self->IsOk();
    }

    EXPORT int wxFont_GetPointSize(wxFont* self)
    {
        return self->GetPointSize();
    }

    EXPORT int wxFont_GetFamily(wxFont* self)
    {
        return self->GetFamily();
    }

    EXPORT int wxFont_GetStyle(wxFont* self)
    {
        return self->GetStyle();
    }

    EXPORT int wxFont_GetWeight(wxFont* self)
    {
        return self->GetWeight();
    }

    EXPORT bool wxFont_GetUnderlined(wxFont* self)
    {
        return self->GetUnderlined();
    }

    EXPORT wxString* wxFont_GetFaceName(wxFont* self)
    {
        wxString* result = new wxString();
        *result = self->GetFaceName();
        return result;
    }

    EXPORT int wxFont_GetEncoding(wxFont* self)
    {
        return (int) self->GetEncoding();
    }

    EXPORT void wxFont_SetPointSize(wxFont* self, int pointSize)
    {
        self->SetPointSize(pointSize);
    }

    EXPORT void wxFont_SetFamily(wxFont* self, int family)
    {
        self->SetFamily((wxFontFamily) family);
    }

    EXPORT void wxFont_SetStyle(wxFont* self, int style)
    {
        self->SetStyle((wxFontStyle) style);
    }

    EXPORT void wxFont_SetWeight(wxFont* self, int weight)
    {
        self->SetWeight((wxFontWeight) weight);
    }

    EXPORT void wxFont_SetFaceName(wxFont* self, wxString* faceName)
    {
        self->SetFaceName(*faceName);
    }

    EXPORT void wxFont_SetUnderlined(wxFont* self, bool underlined)
    {
        self->SetUnderlined(underlined);
    }

    EXPORT void wxFont_SetEncoding(wxFont* self, int encoding)
    {
        self->SetEncoding((wxFontEncoding) encoding);
    }

    EXPORT wxString* wxFont_GetFamilyString(wxFont* self)
    {
        wxString* result = new wxString();
        *result = self->GetFamilyString();
        return result;
    }

    EXPORT wxString* wxFont_GetStyleString(wxFont* self)
    {
        wxString* result = new wxString();
        *result = self->GetStyleString();
        return result;
    }

    EXPORT wxString* wxFont_GetWeightString(wxFont* self)
    {
        wxString* result = new wxString();
        *result = self->GetWeightString();
        return result;
    }

    EXPORT int wxFont_GetDefaultEncoding(wxFont* self)
    {
        return (int) self->GetDefaultEncoding();
    }

    EXPORT void wxFont_SetDefaultEncoding(wxFont* self, int encoding)
    {
        self->SetDefaultEncoding((wxFontEncoding) encoding);
    }

    EXPORT void* wxFontEnumerator_Create(void* self, void* _fnc)
    {
        return (void*) new kwxFontEnumerator(self, _fnc);
    }

    EXPORT void wxFontEnumerator_Delete(kwxFontEnumerator* self)
    {
        delete self;
    }

    EXPORT bool wxFontEnumerator_EnumerateFacenames(kwxFontEnumerator* self, int encoding,
                                                    bool fixedWidthOnly)
    {
        return self->EnumerateFacenames((wxFontEncoding) encoding, fixedWidthOnly);
    }

    EXPORT bool wxFontEnumerator_EnumerateEncodings(kwxFontEnumerator* self, wxString* facename)
    {
        return self->EnumerateEncodings(*facename);
    }

    EXPORT void* wxFontMapper_Create()
    {
        return wxTheFontMapper;
    }

    EXPORT bool wxFontMapper_GetAltForEncoding(wxFontMapper* self, int encoding, void* alt_encoding,
                                               wxString* facename)
    {
        return self->GetAltForEncoding((wxFontEncoding) encoding, (wxFontEncoding*) alt_encoding,
                                       *facename, false);
    }

    EXPORT bool wxFontMapper_IsEncodingAvailable(wxFontMapper* self, int encoding, wxString* _buf)
    {
        return self->IsEncodingAvailable((wxFontEncoding) encoding, *_buf);
    }

    EXPORT void* wxEncodingConverter_Create()
    {
        return (void*) new wxEncodingConverter();
    }

    EXPORT void wxEncodingConverter_Delete(void* self)
    {
        delete (wxEncodingConverter*) self;
    }

    EXPORT bool wxEncodingConverter_Init(wxEncodingConverter* self, int input_enc, int output_enc,
                                         int method)
    {
        return self->Init((wxFontEncoding) input_enc, (wxFontEncoding) output_enc, method);
    }

    EXPORT void wxEncodingConverter_Convert(void* self, void* input, void* output)
    {
        ((wxEncodingConverter*) self)->Convert((const char*) input, (char*) output);
    }

    EXPORT int wxEncodingConverter_GetPlatformEquivalents(void* self, int enc, int platform,
                                                          void* _lst)
    {
        wxFontEncodingArray arr =
            ((wxEncodingConverter*) self)->GetPlatformEquivalents((wxFontEncoding) enc, platform);
        if (_lst)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((int*) _lst)[i] = (int) arr.Item(i);
        }
        return (int) arr.GetCount();
    }

    EXPORT int wxEncodingConverter_GetAllEquivalents(void* self, int enc, void* _lst)
    {
        wxFontEncodingArray arr =
            ((wxEncodingConverter*) self)->GetAllEquivalents((wxFontEncoding) enc);
        if (_lst)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((int*) _lst)[i] = (int) arr.Item(i);
        }
        return (int) arr.GetCount();
    }
}
