#pragma once

#include <bit>

/*
    kwxEventFilter forwards wxEventFilter::FilterEvent to a foreign callback.
    The callback must return one of the wxEventFilter values: Event_Skip (-1),
    Event_Ignore (0), or Event_Processed (1).

    The filter must be removed with wxEvtHandler::RemoveFilter before it is
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
    }

    int FilterEvent(wxEvent& event) override;

private:
    void* kwxObject;
    FilterFunc filter_func;
};
