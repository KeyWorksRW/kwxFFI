#include "kwx_wrapper.h"

extern "C"
{
    EXPORT wxPlatformInfo* wxPlatformInfo_Create()
    {
        return new wxPlatformInfo();
    }

    EXPORT void wxPlatformInfo_Delete(wxPlatformInfo* self)
    {
        delete self;
    }

    EXPORT wxPlatformInfo* wxPlatformInfo_Get()
    {
        return new wxPlatformInfo(wxPlatformInfo::Get());
    }

    // Returns a copy of the information for the currently running platform.
    EXPORT wxPlatformInfo* wxPlatformInfo_GetCurrent()
    {
        return new wxPlatformInfo(wxPlatformInfo::Get());
    }

    EXPORT int wxPlatformInfo_GetOperatingSystemIdFromName(wxString* name)
    {
        return static_cast<int>(wxPlatformInfo::GetOperatingSystemId(*name));
    }

    EXPORT int wxPlatformInfo_GetPortIdFromName(wxString* port_name)
    {
        return static_cast<int>(wxPlatformInfo::GetPortId(*port_name));
    }

    EXPORT int wxPlatformInfo_GetBitnessFromName(wxString* bitness)
    {
        return static_cast<int>(wxPlatformInfo::GetBitness(*bitness));
    }

    EXPORT int wxPlatformInfo_GetEndiannessFromName(wxString* endianness)
    {
        return static_cast<int>(wxPlatformInfo::GetEndianness(*endianness));
    }

    EXPORT wxString* wxPlatformInfo_GetOperatingSystemFamilyNameFromId(int os_id)
    {
        return new wxString(
            wxPlatformInfo::GetOperatingSystemFamilyName(static_cast<wxOperatingSystemId>(os_id)));
    }

    EXPORT wxString* wxPlatformInfo_GetOperatingSystemIdNameFromId(int os_id)
    {
        return new wxString(
            wxPlatformInfo::GetOperatingSystemIdName(static_cast<wxOperatingSystemId>(os_id)));
    }

    EXPORT wxString* wxPlatformInfo_GetPortIdNameFromValues(int port_id, bool using_universal)
    {
        return new wxString(
            wxPlatformInfo::GetPortIdName(static_cast<wxPortId>(port_id), using_universal));
    }

    EXPORT wxString* wxPlatformInfo_GetPortIdShortNameFromValues(int port_id, bool using_universal)
    {
        return new wxString(
            wxPlatformInfo::GetPortIdShortName(static_cast<wxPortId>(port_id), using_universal));
    }

    EXPORT wxString* wxPlatformInfo_GetBitnessNameFromValue(int bitness)
    {
        return new wxString(wxPlatformInfo::GetBitnessName(static_cast<wxBitness>(bitness)));
    }

    EXPORT wxString* wxPlatformInfo_GetEndiannessNameFromValue(int endianness)
    {
        return new wxString(
            wxPlatformInfo::GetEndiannessName(static_cast<wxEndianness>(endianness)));
    }

    EXPORT wxString* wxPlatformInfo_GetOperatingSystemDirectory()
    {
        return new wxString(wxPlatformInfo::GetOperatingSystemDirectory());
    }

    EXPORT int wxPlatformInfo_GetOSMajorVersion(wxPlatformInfo* self)
    {
        return self->GetOSMajorVersion();
    }

    EXPORT int wxPlatformInfo_GetOSMinorVersion(wxPlatformInfo* self)
    {
        return self->GetOSMinorVersion();
    }

    EXPORT int wxPlatformInfo_GetOSMicroVersion(wxPlatformInfo* self)
    {
        return self->GetOSMicroVersion();
    }

    EXPORT int wxPlatformInfo_GetToolkitMajorVersion(wxPlatformInfo* self)
    {
        return self->GetToolkitMajorVersion();
    }

    EXPORT int wxPlatformInfo_GetToolkitMinorVersion(wxPlatformInfo* self)
    {
        return self->GetToolkitMinorVersion();
    }

    EXPORT int wxPlatformInfo_GetToolkitMicroVersion(wxPlatformInfo* self)
    {
        return self->GetToolkitMicroVersion();
    }

    EXPORT int wxPlatformInfo_GetOperatingSystemId(wxPlatformInfo* self)
    {
        return static_cast<int>(self->GetOperatingSystemId());
    }

    EXPORT int wxPlatformInfo_GetPortId(wxPlatformInfo* self)
    {
        return static_cast<int>(self->GetPortId());
    }

    EXPORT int wxPlatformInfo_GetBitness(wxPlatformInfo* self)
    {
        return static_cast<int>(self->GetBitness());
    }

    EXPORT int wxPlatformInfo_GetEndianness(wxPlatformInfo* self)
    {
        return static_cast<int>(self->GetEndianness());
    }

    EXPORT wxString* wxPlatformInfo_GetPlatformDescription(wxPlatformInfo* self)
    {
        return new wxString(self->GetPlatformDescription());
    }

    EXPORT wxString* wxPlatformInfo_GetOperatingSystemFamilyName(wxPlatformInfo* self)
    {
        return new wxString(self->GetOperatingSystemFamilyName());
    }

    EXPORT wxString* wxPlatformInfo_GetOperatingSystemIdName(wxPlatformInfo* self)
    {
        return new wxString(self->GetOperatingSystemIdName());
    }

    EXPORT wxString* wxPlatformInfo_GetPortIdName(wxPlatformInfo* self)
    {
        return new wxString(self->GetPortIdName());
    }

    EXPORT wxString* wxPlatformInfo_GetPortIdShortName(wxPlatformInfo* self)
    {
        return new wxString(self->GetPortIdShortName());
    }

    EXPORT wxString* wxPlatformInfo_GetBitnessName(wxPlatformInfo* self)
    {
        return new wxString(self->GetBitnessName());
    }

    EXPORT wxString* wxPlatformInfo_GetEndiannessName(wxPlatformInfo* self)
    {
        return new wxString(self->GetEndiannessName());
    }

    EXPORT wxString* wxPlatformInfo_GetCpuArchitectureName(wxPlatformInfo* self)
    {
        return new wxString(self->GetCpuArchitectureName());
    }

    EXPORT wxString* wxPlatformInfo_GetNativeCpuArchitectureName(wxPlatformInfo* self)
    {
        return new wxString(self->GetNativeCpuArchitectureName());
    }

    EXPORT wxString* wxPlatformInfo_GetOperatingSystemDescription(wxPlatformInfo* self)
    {
        return new wxString(self->GetOperatingSystemDescription());
    }

    EXPORT wxString* wxPlatformInfo_GetDesktopEnvironment(wxPlatformInfo* self)
    {
        return new wxString(self->GetDesktopEnvironment());
    }

    EXPORT bool wxPlatformInfo_IsOk(wxPlatformInfo* self)
    {
        return self->IsOk();
    }

    EXPORT bool wxPlatformInfo_IsUsingUniversalWidgets(wxPlatformInfo* self)
    {
        return self->IsUsingUniversalWidgets();
    }

    EXPORT void wxPlatformInfo_SetOSVersion(wxPlatformInfo* self, int major, int minor, int micro)
    {
        self->SetOSVersion(major, minor, micro);
    }

    EXPORT void wxPlatformInfo_SetToolkitVersion(wxPlatformInfo* self, int major, int minor,
                                                 int micro)
    {
        self->SetToolkitVersion(major, minor, micro);
    }

    EXPORT void wxPlatformInfo_SetOperatingSystemId(wxPlatformInfo* self, int os_id)
    {
        self->SetOperatingSystemId(static_cast<wxOperatingSystemId>(os_id));
    }

    EXPORT void wxPlatformInfo_SetOperatingSystemDescription(wxPlatformInfo* self,
                                                             wxString* description)
    {
        self->SetOperatingSystemDescription(*description);
    }

    EXPORT void wxPlatformInfo_SetPortId(wxPlatformInfo* self, int port_id)
    {
        self->SetPortId(static_cast<wxPortId>(port_id));
    }

    EXPORT void wxPlatformInfo_SetBitness(wxPlatformInfo* self, int bitness)
    {
        self->SetBitness(static_cast<wxBitness>(bitness));
    }

    EXPORT void wxPlatformInfo_SetEndianness(wxPlatformInfo* self, int endianness)
    {
        self->SetEndianness(static_cast<wxEndianness>(endianness));
    }

    EXPORT void wxPlatformInfo_SetCpuArchitectureName(wxPlatformInfo* self,
                                                      wxString* cpu_architecture)
    {
        self->SetCpuArchitectureName(*cpu_architecture);
    }

    EXPORT void wxPlatformInfo_SetNativeCpuArchitectureName(wxPlatformInfo* self,
                                                            wxString* cpu_architecture)
    {
        self->SetNativeCpuArchitectureName(*cpu_architecture);
    }

    EXPORT void wxPlatformInfo_SetDesktopEnvironment(wxPlatformInfo* self,
                                                     wxString* desktop_environment)
    {
        self->SetDesktopEnvironment(*desktop_environment);
    }
}
