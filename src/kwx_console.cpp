// Console application lifecycle.
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include "kwx_helper_hooks.h"

#include <wx/app.h>
#include <wx/build.h>
#include <wx/cmdline.h>
#include <wx/init.h>

#include <cstdio>
#include <string>
#include <vector>

extern "C"
{
    namespace
    {
        bool g_consoleInitialized = false;

        // wxAppConsoleBase keeps the argc/argv it was started with for the whole
        // lifetime of the application (GetAppName() and the wxCmdLineParser usage
        // synopsis read argv[0]), so an argument list a binding hands in has to
        // outlive kwxConsoleInitialize(). Released in kwxConsoleShutdown().
        std::vector<std::string> g_ownedArgs;
        std::vector<char*> g_ownedArgv;
    }  // namespace

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

    EXPORT int kwxConsoleInitializeFromArgs(int argc, TString* argv)
    {
        if (argc <= 0 || argv == nullptr)
            return kwxConsoleInitialize(0, nullptr);

        if (g_consoleInitialized)
            return 1;

        g_ownedArgs.clear();
        g_ownedArgv.clear();
        g_ownedArgs.reserve(static_cast<size_t>(argc));
        for (int i = 0; i < argc; ++i)
            g_ownedArgs.emplace_back(argv[i] != nullptr ? argv[i] : "");

        // Build the pointer array only after every string exists: a small string
        // lives inside its own std::string object, so a later vector growth would
        // invalidate pointers taken earlier.
        g_ownedArgv.reserve(static_cast<size_t>(argc) + 1);
        for (std::string& arg: g_ownedArgs)
            g_ownedArgv.push_back(&arg[0]);
        g_ownedArgv.push_back(nullptr);

        return kwxConsoleInitialize(argc, g_ownedArgv.data());
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
        g_ownedArgv.clear();
        g_ownedArgs.clear();
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

    EXPORT void kwxConsoleOnInitCmdLineBase(wxCmdLineParser* parser)
    {
        wxAppConsole* app = wxAppConsole::GetInstance();
        if (app == nullptr)
            return;

        // Qualified call: a virtual call would re-enter the kwxAppConsole override
        // that installed the foreign hook and recurse forever.
        app->wxAppConsoleBase::OnInitCmdLine(*parser);
    }

    EXPORT int kwxConsoleOnCmdLineParsedBase(wxCmdLineParser* parser)
    {
        wxAppConsole* app = wxAppConsole::GetInstance();
        if (app == nullptr)
            return 1;
        return app->wxAppConsoleBase::OnCmdLineParsed(*parser) ? 1 : 0;
    }

    EXPORT void* kwxStdin()
    {
        return static_cast<void*>(stdin);
    }

    EXPORT void* kwxStdout()
    {
        return static_cast<void*>(stdout);
    }

    EXPORT void* kwxStderr()
    {
        return static_cast<void*>(stderr);
    }

    EXPORT int kwxConsoleCheckBuildOptions(char* componentName)
    {
        // The signature half is this library's own, so the comparison can only
        // fail if kwxFFI itself was built against different wxWidgets headers.
        return wxAppConsole::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE,
                                               componentName ? componentName : "program") ?
                   1 :
                   0;
    }
}
