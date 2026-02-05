/*
 * SampleApp - Example wxApp subclass for kwxFFI
 *
 * This file demonstrates how a foreign language port might structure its
 * wxApp implementation using kwxFFI. See SampleApp.h for overview.
 *
 * NOTE: This code is provided as a reference example only. It is NOT built
 * as part of the kwxFFI library.
 */

#include "SampleApp.h"

#include <wx/cmdline.h>
#include <wx/dynlib.h>
#include <wx/fs_zip.h>
#include <wx/quantize.h>
#include <wx/tooltip.h>

/*-----------------------------------------------------------------------------
    The global idle timer
-----------------------------------------------------------------------------*/
constexpr int MIN_IDLE_INTERVAL_MS = 100;  // Minimum 100ms (10 times per second)
static wxIdleTimer* idleTimer = nullptr;

void initIdleTimer()
{
    idleTimer = new wxIdleTimer();
}

void doneIdleTimer()
{
    if (idleTimer)
    {
        idleTimer->Stop();
        delete idleTimer;
        idleTimer = nullptr;
    }
}

/*-----------------------------------------------------------------------------
    The main application
-----------------------------------------------------------------------------*/
static wxClosure* initClosure = nullptr;
static int APPTerminating = 0;

IMPLEMENT_APP_NO_MAIN(SampleApp);

bool SampleApp::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }

    initIdleTimer();
    if (initClosure)
    {
        delete initClosure; /* special: init is only called once with a nullptr event */
        initClosure = nullptr;
    }
    return true;
}

int SampleApp::OnExit()
{
    doneIdleTimer();
    return wxApp::OnExit();
}

void SampleApp::InitZipFileSystem()
{
    static int InitZIPFileSystem_done = 0;

    if (!InitZIPFileSystem_done)
    {
        InitZIPFileSystem_done = 1;
        wxFileSystem::AddHandler(new wxZipFSHandler());
    }
}

void SampleApp::InitImageHandlers()
{
    wxInitAllImageHandlers();
}

// "getCallback" is a hack to retrieve the callback object for a certain event
// see also "wxEvtHandler_FindClosure"
static wxCallback** getCallback = nullptr;

void SampleApp::HandleEvent(wxEvent& evt)
{
    wxCallback* callback = (wxCallback*) (evt.m_callbackUserData);
    if (getCallback)
    {
        *getCallback = callback; /* retrieve the callback */
    }
    else if (callback)
    {
        callback->Invoke(&evt); /* normal: invoke the callback function */
    }
}

/* override to prevent parent wxApp failing to parse foreign language cmdline args */
void SampleApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.SetCmdLine("");
}

/* override to prevent parent wxApp from further processing of parsed cmdline */
bool SampleApp::OnCmdLineParsed([[maybe_unused]] wxCmdLineParser& parser)
{
    return true;
}

/*-----------------------------------------------------------------------------
    C interface to the idle timer
-----------------------------------------------------------------------------*/
extern "C"
{
    EXPORT int SampleApp_GetIdleInterval()
    {
        if (!idleTimer)
        {
            return 0;
        }

        if (idleTimer->IsRunning())
        {
            return idleTimer->GetInterval();
        }
        return 0;
    }

    EXPORT void SampleApp_SetIdleInterval(int interval)
    {
        if (idleTimer)
        {
            if (idleTimer->IsRunning())
            {
                idleTimer->Stop();
            }
            if (interval >= MIN_IDLE_INTERVAL_MS)
            {
                idleTimer->Start(interval, false);
            }
        }
    }

    /*-----------------------------------------------------------------------------
        C interface to the application.
    -----------------------------------------------------------------------------*/

    EXPORT int SampleApp_MainLoop()
    {
        return wxGetApp().MainLoop();
    }

    EXPORT bool SampleApp_Initialized()
    {
        return true;
    }

    EXPORT int SampleApp_Pending()
    {
        return (int) wxGetApp().Pending();
    }

    EXPORT void SampleApp_Dispatch()
    {
        wxGetApp().Dispatch();
    }

    EXPORT wxString* SampleApp_GetAppName()
    {
        auto* result = new wxString();
        *result = wxGetApp().GetAppName();
        return result;
    }

    EXPORT void SampleApp_SetAppName(wxString* name)
    {
        wxGetApp().SetAppName(*name);
    }

    EXPORT wxString* SampleApp_GetClassName()
    {
        auto* result = new wxString();
        *result = wxGetApp().GetClassName();
        return result;
    }

    EXPORT void SampleApp_SetClassName(wxString* name)
    {
        wxGetApp().SetClassName(*name);
    }

    EXPORT wxString* SampleApp_GetVendorName()
    {
        auto* result = new wxString();
        *result = wxGetApp().GetVendorName();
        return result;
    }

    EXPORT void SampleApp_SetVendorName(wxString* name)
    {
        wxGetApp().SetVendorName(*name);
    }

    EXPORT void* SampleApp_GetTopWindow()
    {
        return wxGetApp().GetTopWindow();
    }

    EXPORT void SampleApp_SetExitOnFrameDelete(bool flag)
    {
        wxGetApp().SetExitOnFrameDelete(flag);
    }

    EXPORT int SampleApp_GetExitOnFrameDelete()
    {
        return (int) wxGetApp().GetExitOnFrameDelete();
    }

    EXPORT void* SampleApp_CreateLogTarget()
    {
        wxAppTraits* appTraits = wxGetApp().GetTraits();
        return appTraits->CreateLogTarget();
    }

    EXPORT void SampleApp_SetUseBestVisual(bool flag)
    {
        wxGetApp().SetUseBestVisual(flag);
    }

    EXPORT int SampleApp_GetUseBestVisual()
    {
        return (int) wxGetApp().GetUseBestVisual();
    }

    EXPORT void SampleApp_SetPrintMode(int mode)
    {
        wxGetApp().SetPrintMode(mode);
    }

    EXPORT void SampleApp_ExitMainLoop()
    {
        wxGetApp().ExitMainLoop();
    }

    EXPORT void SampleApp_SetTopWindow(wxWindow* wnd)
    {
        wxGetApp().SetTopWindow(wnd);
    }

    EXPORT void SampleApp_EnableTooltips(bool enable)
    {
        wxToolTip::Enable(enable);
    }

    EXPORT void SampleApp_SetTooltipDelay(int milliseconds)
    {
        wxToolTip::SetDelay(milliseconds);
    }

    EXPORT void SampleApp_InitAllImageHandlers()
    {
        wxInitAllImageHandlers();
    }

    EXPORT void SampleApp_Bell()
    {
        wxBell();
    }

    EXPORT wxSize* SampleApp_DisplaySize()
    {
        wxSize* size = new wxSize();
        *size = wxGetDisplaySize();
        return size;
    }

    EXPORT void SampleApp_EnableTopLevelWindows(bool enable)
    {
        wxEnableTopLevelWindows(enable);
    }

    EXPORT void SampleApp_Exit()
    {
        wxExit();
    }

    EXPORT wxPoint* SampleApp_MousePosition()
    {
        auto* pos = new wxPoint();
        *pos = wxGetMousePosition();
        return pos;
    }

    EXPORT void* SampleApp_FindWindowByLabel(wxString* label, wxWindow* parent)
    {
        return (void*) wxFindWindowByLabel(*label, parent);
    }

    EXPORT void* SampleApp_FindWindowByName(wxString* name, wxWindow* parent)
    {
        return (void*) wxFindWindowByName(*name, parent);
    }

    EXPORT void* SampleApp_FindWindowById(int winID, wxWindow* parent)
    {
        return (void*) wxWindow::FindWindowById((long) winID, parent);
    }

    EXPORT void* SampleApp_GetApp()
    {
        return (void*) wxTheApp;
    }

    EXPORT wxString* SampleApp_GetUserId()
    {
        wxString* result = new wxString();
        *result = wxGetUserId();
        return result;
    }

    EXPORT wxString* SampleApp_GetUserName()
    {
        wxString* result = new wxString();
        *result = wxGetUserName();
        return result;
    }

    EXPORT wxString* SampleApp_GetUserHome(wxString* user)
    {
        wxString* result = new wxString();
        *result = wxGetUserHome(*user);
        return result;
    }

    EXPORT int SampleApp_ExecuteProcess(wxString* cmd, bool sync, void* process)
    {
        return (int) wxExecute(*cmd, sync, static_cast<wxProcess*>(process));
    }

    EXPORT int SampleApp_Yield()
    {
        return (int) wxYield();
    }

    EXPORT int SampleApp_SafeYield(wxWindow* win)
    {
        return (int) wxSafeYield(win);
    }

    EXPORT int SampleApp_GetOsVersion(int* major, int* minor)
    {
        return wxGetOsVersion(major, minor);
    }

    EXPORT wxString* SampleApp_GetOsDescription()
    {
        wxString* result = new wxString();
        *result = wxGetOsDescription();
        return result;
    }

    EXPORT void SampleApp_Sleep(int seconds)
    {
        wxSleep(seconds);
    }

    EXPORT void SampleApp_MilliSleep(int milliseconds)
    {
        wxMilliSleep(milliseconds);
    }

    EXPORT bool SampleApp_IsTerminating()
    {
        return APPTerminating;
    }

    /*-----------------------------------------------------------------------------
        Event handler connection using SampleApp::HandleEvent
    -----------------------------------------------------------------------------*/
    EXPORT int wxEvtHandler_ConnectSampleApp(void* obj, int first, int last, int type,
                                             wxClosure* closure)
    {
        wxCallback* callback = new wxCallback(closure);
        ((wxEvtHandler*) obj)
            ->Connect(first, last, type, (wxObjectEventFunction) &SampleApp::HandleEvent, callback);
        return 0;
    }

    EXPORT int wxEvtHandler_DisconnectSampleApp(wxEvtHandler* self, int first, int last, int type,
                                                wxObject* data)
    {
        return (int) self->Disconnect(first, last, type,
                                      (wxObjectEventFunction) &SampleApp::HandleEvent, data);
    }
}
