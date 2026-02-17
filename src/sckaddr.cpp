// update checked 100% with 2.8.9 manual
#include "wrapper.h"

extern "C"
{
#if wxUSE_SOCKETS

    // wxSockAddress
    // EWXWEXPORT(wxSockAddress*,wxSockAddress_wxSockAddress)() disabled because it has virtual
    // function
    EXPORT void wxSockAddress_Delete(wxSockAddress* self)
    {
        delete self;
    }
    EXPORT void wxSockAddress_Clear(wxSockAddress* self)
    {
        self->Clear();
    }

    // wxIPaddress
    EXPORT wxString* wxIPaddress_Hostname(wxIPaddress* self)
    {
        return new wxString(self->Hostname());
    }
    EXPORT bool wxIPaddress_HostnameSet(wxIPaddress* self, wxString* hostname)
    {
        return self->Hostname(*hostname);
    }
    EXPORT wxString* wxIPaddress_IPAddress(wxIPaddress* self)
    {
        return new wxString(self->IPAddress());
    }
    EXPORT wxUint16 wxIPaddress_Service(wxIPaddress* self)
    {
        return self->Service();
    }
    EXPORT bool wxIPaddress_ServiceSet(wxIPaddress* self, wxString* service)
    {
        return self->Service(*service);
    }
    EXPORT bool wxIPaddress_ServiceSetPort(wxIPaddress* self, wxUint16 service)
    {
        return self->Service(service);
    }

    EXPORT bool wxIPaddress_AnyAddress(wxIPaddress* self)
    {
        return self->AnyAddress();
    }
    EXPORT bool wxIPaddress_LocalHost(wxIPaddress* self)
    {
        return self->LocalHost();
    }
    EXPORT bool wxIPaddress_IsLocalHost(wxIPaddress* self)
    {
        return self->IsLocalHost();
    }

    // wxIPV4address
    EXPORT wxIPV4address* wxIPV4address_Create()
    {
        return new wxIPV4address();
    }
    EXPORT void wxIPV4address_Delete(wxIPV4address* self)
    {
        delete self;
    }

#endif  // wxUSE_SOCKETS
}
