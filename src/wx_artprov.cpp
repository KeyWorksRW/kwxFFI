#include "kwx_wrapper.h"
#include <wx/artprov.h>

extern "C"
{
    typedef void* (*TCreateBmp)(void* pObject, void* id, void* clt, int width, int height);
}

class kwxArtProv : public wxArtProvider
{
private:
    void* kwxObject;
    TCreateBmp cb;

protected:
    virtual wxBitmap CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size)
    {
        if (kwxObject)
        {
            void* res = cb(kwxObject, (void*) id.utf8_str().data(),
                           (void*) client.utf8_str().data(), size.GetWidth(), size.GetHeight());

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
        kwxObject = obj;
        cb = (TCreateBmp) clb;
    };
    void Release()
    {
        kwxObject = nullptr;
        cb = nullptr;
    };
};

extern "C"
{
    EXPORT void* kwxArtProv_Create(void* pObject, void* callback)
    {
        return (void*) new kwxArtProv(pObject, callback);
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
