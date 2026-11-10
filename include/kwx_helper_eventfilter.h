#pragma once

#include <bit>

/*
    kwxEventFilter forwards wxEventFilter::FilterEvent to a foreign callback.

    FilterEvent must return one of the wxEventFilter values: Event_Skip (-1),
    Event_Ignore (0), or Event_Processed (1).  Some runtimes can only create
    void-returning callbacks, so the verdict does not come back through the
    callback's return value: the callback calls wxEventFilter_SetResult with
    the value it wants, and FilterEvent returns whatever was stored.  The
    stored value starts at Event_Skip, so a callback that never sets a result —
    or a runtime that cannot express the call — lets the event through instead
    of silently swallowing it.

    wxEventFilter_SetResult takes no receiver: the foreign caller does not know
    the filter pointer when it builds the callback, so the verdict is applied to
    the filter whose FilterEvent() is on the stack.  Filters run only on the
    thread that dispatches events (the GUI thread), so there is never more than
    one active filter per thread.

    A filter registered with wxEvtHandler_AddFilter runs before every handler in
    the process, whichever wxApp instance the runtime created, which is how an
    application-level FilterEvent override is reproduced without deriving a new
    wxApp subclass.

    The filter must be removed with wxEvtHandler_RemoveFilter before it is
    deleted; wxEventFilter asserts that it is unlinked when destroyed.
*/
class kwxEventFilter : public wxEventFilter
{
public:
    typedef int (*FilterFunc)(void* pObject, wxEvent* event);

    kwxEventFilter(void* pObject, void* pFunction) : wxEventFilter()
    {
        kwxObject = pObject;
        filter_func = std::bit_cast<FilterFunc>(pFunction);
        m_result = Event_Skip;
    }

    // The verdict the callback stored for the event it is currently handling.
    void SetResult(int result) { m_result = result; }

    int FilterEvent(wxEvent& event) override;

    // The filter whose FilterEvent() is running on this thread, so an exported
    // setter can reach it without the caller holding the pointer.  Set and
    // cleared by FilterEvent() itself.
    static kwxEventFilter*& Current();

private:
    void* kwxObject;
    FilterFunc filter_func;
    int m_result;
};
