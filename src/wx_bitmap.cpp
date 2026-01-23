#include "wrapper.h"

extern "C"
{
    EXPORT void* wxBitmap_Create(void* _data, int _width, int _height, int _depth)
    {
        return (void*) new wxBitmap((const char*) _data, _width, _height, _depth);
    }

    EXPORT void* wxBitmap_CreateFromXPM(void* _data)
    {
        return (void*) new wxBitmap((const char**) _data);
    }

    EXPORT void* wxBitmap_CreateEmpty(int _width, int _height, int _depth)
    {
        return (void*) new wxBitmap(_width, _height, _depth);
    }

    EXPORT void* wxBitmap_CreateLoad(wxString* name, int type)
    {
        return (void*) new wxBitmap(*name, (wxBitmapType) type);
    }

    EXPORT void* wxBitmap_CreateDefault()
    {
        return (void*) new wxBitmap();
    }

    EXPORT void wxBitmap_Delete(wxBitmap* self)
    {
        delete self;
    }

    EXPORT void wxBitmap_GetSubBitmap(wxBitmap* self, int x, int y, int w, int h, wxBitmap* bitmap)
    {
        *bitmap = self->GetSubBitmap(wxRect(x, y, w, h));
    }

    EXPORT bool wxBitmap_LoadFile(wxBitmap* self, wxString* name, int type)
    {
        return self->LoadFile(*name, (wxBitmapType) type);
    }

    EXPORT bool wxBitmap_SaveFile(wxBitmap* self, wxString* name, int type, wxPalette* cmap)
    {
        return self->SaveFile(*name, (wxBitmapType) type, cmap);
    }

    EXPORT wxMask* wxBitmap_GetMask(wxBitmap* self)
    {
        return self->GetMask();
    }

    EXPORT void wxBitmap_SetMask(wxBitmap* self, wxMask* mask)
    {
        self->SetMask(mask);
    }

    /**/
    EXPORT void wxBitmap_AddHandler(void* handler)
    {
#ifdef __WIN32__
        wxBitmap::AddHandler((wxGDIImageHandler*) handler);
#endif
    }

    EXPORT void wxBitmap_InsertHandler(void* handler)
    {
#ifdef __WIN32__
        wxBitmap::InsertHandler((wxGDIImageHandler*) handler);
#endif
    }

    EXPORT bool wxBitmap_RemoveHandler(wxString* name)
    {
#ifdef __WIN32__
        return wxBitmap::RemoveHandler(*name);
#else
        return false;
#endif
    }

    EXPORT void* wxBitmap_FindHandlerByName(wxString* name)
    {
#ifdef __WIN32__
        return (void*) wxBitmap::FindHandler(*name);
#else
        return nullptr;
#endif
    }

    EXPORT void* wxBitmap_FindHandlerByExtension(wxString* extension, int type)
    {
#ifdef __WIN32__
        return (void*) wxBitmap::FindHandler(*extension, (long) type);
#else
        return nullptr;
#endif
    }

    EXPORT void* wxBitmap_FindHandlerByType(int type)
    {
#ifdef __WIN32__
        return (void*) wxBitmap::FindHandler((long) type);
#else
        return nullptr;
#endif
    }

    EXPORT void wxBitmap_InitStandardHandlers()
    {
#ifdef __WIN32__
        wxBitmap::InitStandardHandlers();
#endif
    }

    EXPORT void wxBitmap_CleanUpHandlers()
    {
#ifdef __WIN32__
        wxBitmap::CleanUpHandlers();
#endif
    }

    /**/
    EXPORT bool wxBitmap_IsOk(wxBitmap* self)
    {
        return self->IsOk();
    }

    EXPORT int wxBitmap_GetWidth(wxBitmap* self)
    {
        return self->GetWidth();
    }

    EXPORT int wxBitmap_GetHeight(wxBitmap* self)
    {
        return self->GetHeight();
    }

    EXPORT int wxBitmap_GetDepth(wxBitmap* self)
    {
        return self->GetDepth();
    }

    EXPORT void* wxStaticBitmap_Create(wxWindow* parent, int id, wxBitmap* bitmap, int x, int y,
                                       int width, int height, int style)
    {
        return (void*) new wxStaticBitmap(parent, id, *bitmap, wxPoint(x, y), wxSize(width, height),
                                          style);
    }

    EXPORT void wxStaticBitmap_SetIcon(wxStaticBitmap* self, wxIcon* icon)
    {
        self->SetIcon(*icon);
    }

    EXPORT void wxStaticBitmap_SetBitmap(wxStaticBitmap* self, wxBitmap* bitmap)
    {
        self->SetBitmap(*bitmap);
    }

    EXPORT void wxStaticBitmap_GetIcon(wxStaticBitmap* self, wxIcon* _ref)
    {
        *_ref = self->GetIcon();
    }

    EXPORT void wxStaticBitmap_GetBitmap(wxStaticBitmap* self, wxBitmap* _ref)
    {
        *_ref = self->GetBitmap();
    }

    EXPORT void wxStaticBitmap_Delete(wxStaticBitmap* self)
    {
        delete self;
    }
}
