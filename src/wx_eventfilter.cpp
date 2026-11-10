#include "kwx_wrapper.h"

#include <tuple>

// The filter currently dispatching on this thread.  A static data member is
// per-process, not per-thread; filters only run while an event is being
// dispatched, and wxWidgets dispatches on the GUI thread, so one slot is enough
// and keeps the type free of a thread_local initialisation helper.
static kwxEventFilter* s_current_filter = nullptr;

kwxEventFilter*& kwxEventFilter::Current()
{
    return s_current_filter;
}

int kwxEventFilter::FilterEvent(wxEvent& event)
{
    if (!filter_func)
    {
        return Event_Skip;
    }

    // The callback reports its verdict through wxEventFilter_SetResult(); the
    // value it returns is ignored so a void-returning runtime thunk suffices.
    m_result = Event_Skip;
    kwxEventFilter* const previous = Current();
    Current() = this;
    std::ignore = filter_func(kwxObject, &event);
    Current() = previous;
    return m_result;
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

    // Stores the verdict the current filter callback wants FilterEvent() to
    // return.  The callback runs inside FilterEvent, so the filter is on the
    // stack and needs no receiver; the event sample's FilterEvent always lets
    // the event through, which is what an unset verdict already means.
    EXPORT void wxEventFilter_SetResult(int result)
    {
        if (kwxEventFilter* filter = kwxEventFilter::Current())
        {
            filter->SetResult(result);
        }
    }
}
