#include "kwx_wrapper.h"

int kwxEventFilter::FilterEvent(wxEvent& event)
{
    if (!filter_func)
    {
        return Event_Skip;
    }

    return filter_func(kwxObject, &event);
}

extern "C"
{
    EXPORT wxEventFilter* wxEventFilter_Create(void* pObject, void* pFunction)
    {
        return new kwxEventFilter(pObject, pFunction);
    }

    EXPORT void wxEventFilter_Delete(wxEventFilter* self)
    {
        delete self;
    }

    EXPORT wxEventBlocker* wxEventBlocker_Create(wxWindow* window, int event_type)
    {
        return new wxEventBlocker(window, static_cast<wxEventType>(event_type));
    }

    EXPORT void wxEventBlocker_Delete(wxEventBlocker* self)
    {
        delete self;
    }

    EXPORT void wxEventBlocker_Block(wxEventBlocker* self, int event_type)
    {
        self->Block(static_cast<wxEventType>(event_type));
    }

    EXPORT void wxEvtHandler_AddFilter(wxEventFilter* filter)
    {
        wxEvtHandler::AddFilter(filter);
    }

    EXPORT void wxEvtHandler_RemoveFilter(wxEventFilter* filter)
    {
        wxEvtHandler::RemoveFilter(filter);
    }
}
