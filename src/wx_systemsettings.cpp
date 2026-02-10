#include "wrapper.h"

extern "C"
{
    EXPORT void wxSystemSettings_GetColour(wxSystemColour index, void* ref)
    {
        *((wxColour*) ref) = wxSystemSettings::GetColour(index);
    }

    EXPORT void wxSystemSettings_GetFont(wxSystemFont index, void* ref)
    {
        *((wxFont*) ref) = wxSystemSettings::GetFont(index);
    }

    EXPORT int wxSystemSettings_GetMetric(wxSystemMetric index)
    {
        return wxSystemSettings::GetMetric(index);
    }

    EXPORT int wxSystemSettings_GetScreenType()
    {
        return (int) wxSystemSettings::GetScreenType();
    }
}
