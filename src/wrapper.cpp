#include "wrapper.h"

#include <wx/quantize.h>

/*-----------------------------------------------------------------------------
    Miscellaneous helper functions
-----------------------------------------------------------------------------*/

int copyStrToBuf(void* dst, wxString& src)
{
    if (dst)
        strcpy((char*) dst, src.utf8_str().data());
    return src.Length();
}

/*-----------------------------------------------------------------------------
    Closures
-----------------------------------------------------------------------------*/
wxClosure::wxClosure(ClosureFun fun, void* data)
{
    m_refcount = 0;
    m_fun = fun;
    m_data = data;
}

wxClosure::~wxClosure()
{
    /* call for the last time with a nullptr event. Give opportunity to clean up resources */
    if (m_fun)
    {
        m_fun((void*) m_fun, m_data, nullptr);
    }
}

void wxClosure::IncRef()
{
    m_refcount++;
}

void wxClosure::DecRef()
{
    m_refcount--;
    if (m_refcount <= 0)
    {
        delete this;
    }
}

void wxClosure::Invoke(wxEvent* event)
{
    if (event && m_fun)
    {
        m_fun((void*) m_fun, m_data, event);
    }
};

void* wxClosure::GetData()
{
    return m_data;
}

/*-----------------------------------------------------------------------------
    callback: a reference counting wrapper for a closure
-----------------------------------------------------------------------------*/
wxCallback::wxCallback(wxClosure* closure)
{
    m_closure = closure;
    m_closure->IncRef();
}

wxCallback::~wxCallback()
{
    m_closure->DecRef();
}

void wxCallback::Invoke(wxEvent* event)
{
    m_closure->Invoke(event);
}

wxClosure* wxCallback::GetClosure()
{
    return m_closure;
}

/*-----------------------------------------------------------------------------
    Generic event handler for all language ports
-----------------------------------------------------------------------------*/
void kwxEventHandler::HandleEvent(wxEvent& evt)
{
    wxCallback* callback = (wxCallback*) (evt.m_callbackUserData);
    if (callback)
    {
        callback->Invoke(&evt);
    }
}

/*-----------------------------------------------------------------------------
    wrapper for objectRefData
-----------------------------------------------------------------------------*/
class wxcClosureRefData : public wxObjectRefData
{
private:
    wxClosure* m_closure;

public:
    wxcClosureRefData(wxClosure* closure);
    ~wxcClosureRefData();

    wxClosure* GetClosure();
};

wxcClosureRefData::wxcClosureRefData(wxClosure* closure)
{
    m_closure = closure;
}

wxcClosureRefData::~wxcClosureRefData()
{
    /* printf("delete wxc-ClosureRefData\n");  */
    if (m_closure)
    {
        delete m_closure;
        m_closure = nullptr;
    }
}

wxClosure* wxcClosureRefData::GetClosure()
{
    return m_closure;
}

/*-----------------------------------------------------------------------------
    C interface to closures.
-----------------------------------------------------------------------------*/
extern "C"
{
    /* closures */
    EXPORT wxClosure* wxClosure_Create(ClosureFun fun, void* data)
    {
        return new wxClosure(fun, data);
    }

    EXPORT void* wxClosure_GetData(wxClosure* closure)
    {
        return closure->GetData();
    }

    /* client data */
    EXPORT void* wxEvtHandler_GetClientClosure(void* _obj)
    {
        return (void*) ((wxEvtHandler*) _obj)->GetClientObject();
    }

    EXPORT void wxEvtHandler_SetClientClosure(void* _obj, wxClosure* closure)
    {
        ((wxEvtHandler*) _obj)->SetClientObject(closure);
    }

    EXPORT wxClosure* wxObject_GetClientClosure(wxObject* _obj)
    {
        wxcClosureRefData* refData = (wxcClosureRefData*) _obj->GetRefData();
        if (refData)
            return refData->GetClosure();
        else
            return nullptr;
    }

    EXPORT void wxObject_SetClientClosure(wxObject* _obj, wxClosure* closure)
    {
        wxcClosureRefData* refData;
        /* wxASSERT(_obj->GetRefData() == nullptr); */
        _obj->UnRef();
        wxASSERT(_obj->GetRefData() == nullptr);
        refData = new wxcClosureRefData(closure);
        _obj->SetRefData(
            refData);  // set new data -- ref count must be 1 as setRefData doesn't increase it.
    }

    EXPORT int QuantizePalette(void* src, void* dest, void* pPalette, int desiredNoColours,
                               void* eightBitData, int flags)
    {
        return (int) wxQuantize::Quantize(*((wxImage*) src), *((wxImage*) dest),
                                          (wxPalette**) pPalette, desiredNoColours,
                                          (unsigned char**) eightBitData, flags);
    }

    EXPORT int Quantize(void* src, void* dest, int desiredNoColours, void* eightBitData, int flags)
    {
        return (int) wxQuantize::Quantize(*((wxImage*) src), *((wxImage*) dest), desiredNoColours,
                                          (unsigned char**) eightBitData, flags);
    }

    EXPORT void* wxEvtHandler_Create()
    {
        return (void*) new wxEvtHandler();
    }

    EXPORT void wxEvtHandler_Delete(wxEvtHandler* self)
    {
        delete self;
    }

    EXPORT void* wxEvtHandler_GetNextHandler(wxEvtHandler* self)
    {
        return (void*) self->GetNextHandler();
    }

    EXPORT void* wxEvtHandler_GetPreviousHandler(wxEvtHandler* self)
    {
        return (void*) self->GetPreviousHandler();
    }

    EXPORT void wxEvtHandler_SetNextHandler(wxEvtHandler* self, void* handler)
    {
        self->SetNextHandler((wxEvtHandler*) handler);
    }

    EXPORT void wxEvtHandler_SetPreviousHandler(wxEvtHandler* self, void* handler)
    {
        self->SetPreviousHandler((wxEvtHandler*) handler);
    }

    EXPORT void wxEvtHandler_SetEvtHandlerEnabled(wxEvtHandler* self, bool enabled)
    {
        self->SetEvtHandlerEnabled(enabled);
    }

    EXPORT bool wxEvtHandler_GetEvtHandlerEnabled(wxEvtHandler* self)
    {
        return self->GetEvtHandlerEnabled();
    }

    EXPORT bool wxEvtHandler_ProcessEvent(wxEvtHandler* self, wxEvent* event)
    {
        return self->ProcessEvent(*event);
    }

    EXPORT void wxEvtHandler_AddPendingEvent(wxEvtHandler* self, wxEvent* event)
    {
        self->AddPendingEvent(*event);
    }

    EXPORT void wxEvtHandler_ProcessPendingEvents(wxEvtHandler* self)
    {
        self->ProcessPendingEvents();
    }

    /*-------------------------------------------------------------------------
        Generic event connection — used by all language ports.
        Creates a wxCallback wrapping the closure and connects it using
        kwxEventHandler::HandleEvent as the event handler function.
    -------------------------------------------------------------------------*/
    EXPORT int wxEvtHandler_Connect(wxEvtHandler* obj, int first, int last, int type,
                                    wxClosure* closure)
    {
        wxCallback* callback = new wxCallback(closure);
        obj->Connect(first, last, type, (wxObjectEventFunction) &kwxEventHandler::HandleEvent,
                     callback);
        return 0;
    }

    EXPORT int wxEvtHandler_Disconnect(wxEvtHandler* self, int first, int last, int type,
                                       wxObject* data)
    {
        return (int) self->Disconnect(first, last, type,
                                      (wxObjectEventFunction) &kwxEventHandler::HandleEvent, data);
    }

    EXPORT void* Null_AcceleratorTable()
    {
        return (void*) &wxNullAcceleratorTable;
    }

    EXPORT void* Null_Bitmap()
    {
        return (void*) &wxNullBitmap;
    }

    EXPORT void* Null_Icon()
    {
        return (void*) &wxNullIcon;
    }

    EXPORT void* Null_Cursor()
    {
        return (void*) &wxNullCursor;
    }

    EXPORT void* Null_Pen()
    {
        return (void*) &wxNullPen;
    }

    EXPORT void* Null_Brush()
    {
        return (void*) &wxNullBrush;
    }

    EXPORT void* Null_Palette()
    {
        return (void*) &wxNullPalette;
    }

    EXPORT void* Null_Font()
    {
        return (void*) &wxNullFont;
    }

    EXPORT void* Null_Colour()
    {
        return (void*) &wxNullColour;
    }

    EXPORT void wxCFree(void* _ptr)
    {
        free(_ptr);
    }

    EXPORT void* wxClassInfo_CreateClassByName(wxString* _inf)
    {
        wxClassInfo* inf = wxClassInfo::FindClass(*_inf);
        if (inf)
            return inf->CreateObject();
        return nullptr;
    }

    EXPORT void* wxClassInfo_GetClassName(wxObject* self)
    {
        wxClassInfo* inf = self->GetClassInfo();
        if (inf)
            return (void*) inf->GetClassName();
        return nullptr;
    }

    EXPORT bool wxClassInfo_IsKindOf(wxObject* self, wxString* _name)
    {
        wxClassInfo* inf = wxClassInfo::FindClass(*_name);
        if (inf)
            return self->IsKindOf(inf);
        return false;
    }

    EXPORT int wxEvent_NewEventType()
    {
        return (int) wxNewEventType();
    }
}
