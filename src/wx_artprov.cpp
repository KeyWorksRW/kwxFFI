#include "wrapper.h"
#include <wx/artprov.h>

extern "C"
{
    typedef void* (*TCreateBmp)(void* _obj, void* id, void* clt, int w, int h);
}

class kwxArtProv : public wxArtProvider
{
private:
    void* EiffelObject;
    TCreateBmp cb;

protected:
    virtual wxBitmap CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size)
    {
        if (EiffelObject)
        {
            void* res = cb(EiffelObject, (void*) id.wchar_str(), (void*) client.wchar_str(),
                           size.GetWidth(), size.GetHeight());

            if (res)
                return (*((wxBitmap*) res));
            else
                return wxNullBitmap;
        }
        return wxNullBitmap;
    }

public:
    kwxArtProv(void* obj, void* clb)
    {
        EiffelObject = obj;
        cb = (TCreateBmp) clb;
    };
    void Release()
    {
        EiffelObject = nullptr;
        cb = nullptr;
    };
};

extern "C"
{
    EXPORT void* kwxArtProv_Create(void* _obj, void* _clb)
    {
        return (void*) new kwxArtProv(_obj, _clb);
    }

    EXPORT void kwxArtProv_Release(kwxArtProv* self)
    {
        self->Release();
        delete self;
    }

    EXPORT void PushProvider(wxArtProvider* provider)
    {
#if WXWIN_COMPATIBILITY_2_6
        wxArtProvider::PushProvider(provider);
#else
        wxArtProvider::Push(provider);
#endif
    }

    EXPORT bool PopProvider()
    {
#if WXWIN_COMPATIBILITY_2_6
        return wxArtProvider::PopProvider();
#else
        return wxArtProvider::Pop();
#endif
    }

    EXPORT bool RemoveProvider(wxArtProvider* provider)
    {
#if WXWIN_COMPATIBILITY_2_6
        return wxArtProvider::RemoveProvider(provider);
#else
        return wxArtProvider::Remove(provider);
#endif
    }
}
