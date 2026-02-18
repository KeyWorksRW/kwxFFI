#include "kwx_wrapper.h"

#include <wx/print.h>
#include <wx/printdlg.h>
#include <wx/wx.h>

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_LOCAL_EVENT_TYPE(wxEVT_PRINT_BEGIN, 2000)
DECLARE_LOCAL_EVENT_TYPE(wxEVT_PRINT_END, 2001)
DECLARE_LOCAL_EVENT_TYPE(wxEVT_PRINT_BEGIN_DOC, 1002)
DECLARE_LOCAL_EVENT_TYPE(wxEVT_PRINT_END_DOC, 1003)
DECLARE_LOCAL_EVENT_TYPE(wxEVT_PRINT_PREPARE, 1004)
DECLARE_LOCAL_EVENT_TYPE(wxEVT_PRINT_PAGE, 1005)
END_DECLARE_EVENT_TYPES()

DEFINE_LOCAL_EVENT_TYPE(wxEVT_PRINT_BEGIN)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_PRINT_END)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_PRINT_BEGIN_DOC)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_PRINT_END_DOC)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_PRINT_PREPARE)
DEFINE_LOCAL_EVENT_TYPE(wxEVT_PRINT_PAGE)

extern "C"
{
    EXPORT int expEVT_PRINT_BEGIN()
    {
        return (int) wxEVT_PRINT_BEGIN;
    }

    EXPORT int expEVT_PRINT_BEGIN_DOC()
    {
        return (int) wxEVT_PRINT_BEGIN_DOC;
    }

    EXPORT int expEVT_PRINT_END()
    {
        return (int) wxEVT_PRINT_END;
    }

    EXPORT int expEVT_PRINT_END_DOC()
    {
        return (int) wxEVT_PRINT_END_DOC;
    }

    EXPORT int expEVT_PRINT_PREPARE()
    {
        return (int) wxEVT_PRINT_PREPARE;
    }

    EXPORT int expEVT_PRINT_PAGE()
    {
        return (int) wxEVT_PRINT_PAGE;
    }
}


class wxcPrintout : public wxPrintout
{
private:
    DECLARE_DYNAMIC_CLASS(wxcPrintout)

protected:
    int m_startPage;
    int m_endPage;
    int m_fromPage;
    int m_toPage;
    wxEvtHandler* m_evtHandler;

public:
    wxcPrintout() : wxPrintout() {};
    wxcPrintout(const wxString& title);
    ~wxcPrintout();

    void SetPageLimits(int startPage, int endPage, int fromPage, int toPage);
    wxEvtHandler* GetEvtHandler();

    // virtual members
    void GetPageInfo(int* startPage, int* endPage, int* fromPage, int* toPage);
    bool OnBeginDocument(int startPage, int endPage);
    void OnEndDocument();
    void OnBeginPrinting();
    void OnEndPrinting();
    void OnPreparePrinting();
    bool OnPrintPage(int page);
    bool HasPage(int page);
};

IMPLEMENT_DYNAMIC_CLASS(wxcPrintout, wxPrintout)

class wxcPrintEvent : public wxEvent
{
private:
    DECLARE_DYNAMIC_CLASS(wxcPrintEvent)
private:
    wxcPrintout* m_printOut;
    int m_page;
    int m_lastPage;
    bool m_continue;

public:
    wxcPrintEvent() : wxEvent() {};
    wxcPrintEvent(const wxcPrintEvent& printEvent);  // copy constructor
    wxcPrintEvent(wxEventType evtType, int id, wxcPrintout* printOut, int page, int lastPage);
    wxEvent* Clone() const { return new wxcPrintEvent(*this); }

    wxcPrintout* GetPrintout();
    int GetPage();
    int GetEndPage();
    bool GetContinue();
    void SetContinue(bool cont);
    void SetPageLimits(int startPage, int endPage, int fromPage, int toPage);
};

IMPLEMENT_DYNAMIC_CLASS(wxcPrintEvent, wxEvent)

wxcPrintEvent::wxcPrintEvent(wxEventType evtType, int id, wxcPrintout* printOut, int page,
                             int lastPage) : wxEvent(id, evtType)
{
    m_printOut = printOut;
    m_page = page;
    m_lastPage = lastPage;
    m_continue = true;
}

wxcPrintEvent::wxcPrintEvent(const wxcPrintEvent& printEvent) : wxEvent(printEvent)
{
    m_printOut = printEvent.m_printOut;
    m_page = printEvent.m_page;
    m_lastPage = printEvent.m_lastPage;
    m_continue = printEvent.m_continue;
}

wxcPrintout* wxcPrintEvent::GetPrintout()
{
    return m_printOut;
}

int wxcPrintEvent::GetPage()
{
    return m_page;
}

int wxcPrintEvent::GetEndPage()
{
    return m_lastPage;
}

bool wxcPrintEvent::GetContinue()
{
    return m_continue;
}

void wxcPrintEvent::SetContinue(bool cont)
{
    m_continue = cont;
}

void wxcPrintEvent::SetPageLimits(int startPage, int endPage, int fromPage, int toPage)
{
    if (m_printOut)
    {
        m_printOut->SetPageLimits(startPage, endPage, fromPage, toPage);
    }
}

wxcPrintout::wxcPrintout(const wxString& title) : wxPrintout(title)
{
    m_startPage = 1;
    m_endPage = 32000;
    m_fromPage = 1;
    m_toPage = 1;
    m_evtHandler = new wxEvtHandler();
}

wxcPrintout::~wxcPrintout()
{
    if (m_evtHandler)
        delete m_evtHandler;
}

wxEvtHandler* wxcPrintout::GetEvtHandler()
{
    return m_evtHandler;
}

void wxcPrintout::SetPageLimits(int startPage, int endPage, int fromPage, int toPage)
{
    m_startPage = startPage;
    m_endPage = endPage;
    m_fromPage = fromPage;
    m_toPage = toPage;
}

void wxcPrintout::GetPageInfo(int* startPage, int* endPage, int* fromPage, int* toPage)
{
    if (startPage)
        *startPage = m_startPage;
    if (endPage)
        *endPage = m_endPage;
    if (fromPage)
        *fromPage = m_fromPage;
    if (toPage)
        *toPage = m_toPage;
}

bool wxcPrintout::OnBeginDocument(int startPage, int endPage)
{
    bool cont = wxPrintout::OnBeginDocument(startPage, endPage);
    if (cont)
    {
        wxcPrintEvent printEvent(wxEVT_PRINT_BEGIN_DOC, 0, this, startPage, endPage);
        m_evtHandler->ProcessEvent(printEvent);
        cont = printEvent.GetContinue();
    }
    return cont;
}

void wxcPrintout::OnEndDocument()
{
    wxcPrintEvent printEvent(wxEVT_PRINT_END_DOC, 0, this, 0, 0);
    m_evtHandler->ProcessEvent(printEvent);
    wxPrintout::OnEndDocument();
}

void wxcPrintout::OnBeginPrinting()
{
    wxcPrintEvent printEvent(wxEVT_PRINT_BEGIN, 0, this, 0, 0);
    wxPrintout::OnBeginPrinting();
    m_evtHandler->ProcessEvent(printEvent);
}

void wxcPrintout::OnEndPrinting()
{
    wxcPrintEvent printEvent(wxEVT_PRINT_END, 0, this, 0, 0);
    m_evtHandler->ProcessEvent(printEvent);
    wxPrintout::OnEndPrinting();
}

void wxcPrintout::OnPreparePrinting()
{
    wxcPrintEvent printEvent(wxEVT_PRINT_PREPARE, 0, this, 0, 0);
    wxPrintout::OnPreparePrinting();
    m_evtHandler->ProcessEvent(printEvent);
}

bool wxcPrintout::OnPrintPage(int page)
{
    wxcPrintEvent printEvent(wxEVT_PRINT_PAGE, 0, this, page, page);
    m_evtHandler->ProcessEvent(printEvent);
    return printEvent.GetContinue();
}

bool wxcPrintout::HasPage(int page)
{
    return (page >= m_fromPage && page <= m_toPage);
}

extern "C"
{
    EXPORT wxPrintDialogData* wxPrintDialog_GetPrintDialogData(wxPrintDialog* pObject)
    {
        return &(pObject->GetPrintDialogData());
    }

    EXPORT wxcPrintout* wxcPrintout_Create(wxString* title)
    {
        return new wxcPrintout(*title);
    }

    EXPORT void wxcPrintout_Delete(wxcPrintout* self)
    {
        if (self)
            delete self;
    }

    EXPORT void wxcPrintout_SetPageLimits(wxcPrintout* self, int startPage, int endPage,
                                          int fromPage, int toPage)
    {
        self->SetPageLimits(startPage, endPage, fromPage, toPage);
    }

    EXPORT wxEvtHandler* wxcPrintout_GetEvtHandler(wxcPrintout* self)
    {
        return self->GetEvtHandler();
    }

    EXPORT wxcPrintout* wxcPrintEvent_GetPrintout(wxcPrintEvent* self)
    {
        return self->GetPrintout();
    }

    EXPORT int wxcPrintEvent_GetPage(wxcPrintEvent* self)
    {
        return self->GetPage();
    }

    EXPORT int wxcPrintEvent_GetEndPage(wxcPrintEvent* self)
    {
        return self->GetEndPage();
    }

    EXPORT bool wxcPrintEvent_GetContinue(wxcPrintEvent* self)
    {
        return self->GetContinue();
    }

    EXPORT void wxcPrintEvent_SetContinue(wxcPrintEvent* self, bool cont)
    {
        self->SetContinue(cont);
    }

    EXPORT void wxcPrintEvent_SetPageLimits(wxcPrintEvent* self, int startPage, int endPage,
                                            int fromPage, int toPage)
    {
        self->SetPageLimits(startPage, endPage, fromPage, toPage);
    }

    EXPORT wxString* wxPrintout_GetTitle(void* pObject)
    {
        wxString title = ((wxPrintout*) pObject)->GetTitle();
        return new wxString(title);
    }

    EXPORT void* wxPrintout_GetDC(void* pObject)
    {
        return (void*) ((wxPrintout*) pObject)->GetDC();
    }

    EXPORT void wxPrintout_SetDC(void* pObject, void* dc)
    {
        ((wxPrintout*) pObject)->SetDC((wxDC*) dc);
    }

    EXPORT void wxPrintout_SetPageSizePixels(void* pObject, int width, int height)
    {
        ((wxPrintout*) pObject)->SetPageSizePixels(width, height);
    }

    EXPORT void wxPrintout_GetPageSizePixels(void* pObject, int* width, int* height)
    {
        ((wxPrintout*) pObject)->GetPageSizePixels(width, height);
    }

    EXPORT void wxPrintout_SetPageSizeMM(void* pObject, int width, int height)
    {
        ((wxPrintout*) pObject)->SetPageSizeMM(width, height);
    }

    EXPORT void wxPrintout_GetPageSizeMM(void* pObject, int* width, int* height)
    {
        ((wxPrintout*) pObject)->GetPageSizeMM(width, height);
    }

    EXPORT void wxPrintout_SetPPIScreen(void* pObject, int x, int y)
    {
        ((wxPrintout*) pObject)->SetPPIScreen(x, y);
    }

    EXPORT void wxPrintout_GetPPIScreen(void* pObject, int* x, int* y)
    {
        ((wxPrintout*) pObject)->GetPPIScreen(x, y);
    }

    EXPORT void wxPrintout_SetPPIPrinter(void* pObject, int x, int y)
    {
        ((wxPrintout*) pObject)->SetPPIPrinter(x, y);
    }

    EXPORT void wxPrintout_GetPPIPrinter(void* pObject, int* x, int* y)
    {
        ((wxPrintout*) pObject)->GetPPIPrinter(x, y);
    }

    EXPORT bool wxPrintout_IsPreview(wxPrintout* pObject)
    {
        return pObject->IsPreview();
    }
}