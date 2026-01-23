#include "wrapper.h"

extern "C"
{
    EXPORT void* wxScrollBar_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                    int style)
    {
        return new wxScrollBar(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT int wxScrollBar_GetThumbPosition(wxScrollBar* self)
    {
        return self->GetThumbPosition();
    }

    EXPORT int wxScrollBar_GetThumbSize(wxScrollBar* self)
    {
        return self->GetThumbSize();
    }

    EXPORT int wxScrollBar_GetPageSize(wxScrollBar* self)
    {
        return self->GetPageSize();
    }

    EXPORT int wxScrollBar_GetRange(wxScrollBar* self)
    {
        return self->GetRange();
    }

    EXPORT void wxScrollBar_SetThumbPosition(wxScrollBar* self, int viewStart)
    {
        self->SetThumbPosition(viewStart);
    }

    EXPORT void wxScrollBar_SetScrollbar(wxScrollBar* self, int position, int thumbSize, int range,
                                         int pageSize, bool refresh)
    {
        self->SetScrollbar(position, thumbSize, range, pageSize, refresh);
    }
}
