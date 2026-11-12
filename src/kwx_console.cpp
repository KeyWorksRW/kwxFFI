// Console application lifecycle.
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include "kwx_helper_hooks.h"

#include <wx/init.h>

extern "C"
{
    namespace
    {
        bool g_consoleInitialized = false;
    }

    EXPORT int kwxConsoleInitialize(int argc, void* argv)
    {
        if (g_consoleInitialized)
            return 1;

        // wxEntryStart() needs a mutable argc and a real argv. A synthetic
        // program name is enough for a binding that does not pass arguments.
        static char* s_dummyArgv[] = { const_cast<char*>("kwxConsoleApp"), nullptr };
        char** args = static_cast<char**>(argv);
        if (argc <= 0 || args == nullptr)
        {
            argc = 1;
            args = s_dummyArgv;
        }

        // wxEntryStart() adopts the existing process application object. Create
        // a console application first so a GUI initializer the binding linked
        // through wxIMPLEMENT_APP_NO_MAIN cannot turn this into a GUI app.
        if (wxAppConsole::GetInstance() == nullptr)
            new kwxAppConsole(nullptr);

        int mutableArgc = argc;
        if (!wxEntryStart(mutableArgc, args))
            return 0;  // wxEntryStart() released the application object

        wxAppConsole* app = wxAppConsole::GetInstance();
        if (app == nullptr || !app->CallOnInit())
        {
            wxEntryCleanup();
            return 0;
        }

        g_consoleInitialized = true;
        return 1;
    }

    EXPORT int kwxConsoleRun()
    {
        wxAppConsole* app = wxAppConsole::GetInstance();
        if (!g_consoleInitialized || app == nullptr)
            return -1;
        return app->OnRun();
    }

    EXPORT void kwxConsoleExitMainLoop()
    {
        if (wxAppConsole* app = wxAppConsole::GetInstance())
            app->ExitMainLoop();
    }

    EXPORT void kwxConsoleShutdown()
    {
        if (!g_consoleInitialized)
            return;
        g_consoleInitialized = false;
        if (wxAppConsole* app = wxAppConsole::GetInstance())
            app->CallOnExit();
        wxEntryCleanup();
    }

    EXPORT int kwxConsoleIsInitialized()
    {
        return g_consoleInitialized ? 1 : 0;
    }

    EXPORT wxAppConsole* kwxConsoleGetApp()
    {
        return wxAppConsole::GetInstance();
    }

    EXPORT void kwxConsoleProcessPendingEvents()
    {
        if (wxAppConsole* app = wxAppConsole::GetInstance())
            app->ProcessPendingEvents();
    }

    EXPORT int kwxConsoleYield()
    {
        wxAppConsole* app = wxAppConsole::GetInstance();
        return (app != nullptr && app->Yield()) ? 1 : 0;
    }
}
