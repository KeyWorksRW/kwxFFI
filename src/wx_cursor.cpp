#include "wrapper.h"

extern "C"
{
    EXPORT wxCursor* Cursor_CreateFromStock(wxStockCursor id)
    {
        return new wxCursor(id);
    }

    EXPORT wxCursor* Cursor_CreateFromImage(wxImage* image)
    {
        return new wxCursor(*image);
    }

    EXPORT wxCursor* Cursor_CreateLoad(wxString* name, long type, int width, int height)
    {
        wxBitmapType bm_type = (wxBitmapType) type;
#if defined(__WXGTK__)
        return nullptr;
#else
        return new wxCursor(*name, bm_type, width, height);
#endif
    }
}
