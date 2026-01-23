#include "wrapper.h"

extern "C"
{
    EXPORT void* wxFontData_Create()
    {
        return (void*) new wxFontData();
    }

    EXPORT void wxFontData_Delete(void* self)
    {
        delete (wxFontData*) self;
    }

    EXPORT void wxFontData_SetAllowSymbols(void* self, bool flag)
    {
        ((wxFontData*) self)->SetAllowSymbols(flag);
    }

    EXPORT bool wxFontData_GetAllowSymbols(wxFontData* self)
    {
        return self->GetAllowSymbols();
    }

    EXPORT void wxFontData_SetColour(void* self, wxColour* colour)
    {
        ((wxFontData*) self)->SetColour(*colour);
    }

    EXPORT void wxFontData_GetColour(void* self, wxColour* _ref)
    {
        *_ref = ((wxFontData*) self)->GetColour();
    }

    EXPORT void wxFontData_SetShowHelp(void* self, bool flag)
    {
        ((wxFontData*) self)->SetShowHelp(flag);
    }

    EXPORT bool wxFontData_GetShowHelp(wxFontData* self)
    {
        return self->GetShowHelp();
    }

    EXPORT void wxFontData_EnableEffects(void* self, bool flag)
    {
        ((wxFontData*) self)->EnableEffects(flag);
    }

    EXPORT bool wxFontData_GetEnableEffects(wxFontData* self)
    {
        return self->GetEnableEffects();
    }

    EXPORT void wxFontData_SetInitialFont(void* self, wxFont* font)
    {
        ((wxFontData*) self)->SetInitialFont(*font);
    }

    EXPORT void wxFontData_GetInitialFont(void* self, wxFont* ref)
    {
        *ref = ((wxFontData*) self)->GetInitialFont();
    }

    EXPORT void wxFontData_SetChosenFont(void* self, wxFont* font)
    {
        ((wxFontData*) self)->SetChosenFont(*font);
    }

    EXPORT void wxFontData_GetChosenFont(void* self, wxFont* ref)
    {
        *ref = ((wxFontData*) self)->GetChosenFont();
    }

    EXPORT void wxFontData_SetRange(void* self, int minRange, int maxRange)
    {
        ((wxFontData*) self)->SetRange(minRange, maxRange);
    }

    EXPORT int wxFontData_GetEncoding(wxFontData* self)
    {
        return (int) self->GetEncoding();
    }

    EXPORT void wxFontData_SetEncoding(void* self, int encoding)
    {
        ((wxFontData*) self)->SetEncoding((wxFontEncoding) encoding);
    }
}
