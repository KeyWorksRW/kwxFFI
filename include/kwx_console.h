#pragma once

// Console application lifecycle.
//
// A console program uses wxAppConsole instead of the GUI wxApp. Create the
// application object first with kwxAppConsole_Create() when the program needs
// OnInitCmdLine/OnCmdLineParsed/OnRun/OnExit callbacks; if no application
// object exists, kwxConsoleInitialize() installs a plain wxAppConsole, so a GUI
// initializer registered by a binding is not used.
//
// Typical use:
//
//     void* app = kwxAppConsole_Create(NULL);      // optional
//     kwxAppConsole_SetOnOnInitCmdLine(app, ...);  // add descriptor entries
//     kwxAppConsole_SetOnOnCmdLineParsed(app, ...);
//     kwxMessageOutputUseStderr();                 // keep text on stderr
//     if (!kwxConsoleInitialize(argc, argv))
//         return 1;
//     // do the work, or call kwxConsoleRun() for an event loop
//     kwxConsoleShutdown();
//
// The default wxAppConsole::OnInit() parses the command line through
// wxCmdLineParser; help and syntax errors are written to the active
// wxMessageOutput. Call kwxMessageOutputUseStderr() (include/kwx_log.h) so a
// GUI-subsystem executable still writes them to the inherited console. A
// console application also installs a wxLogStderr log target, so LogError()
// and LogWarning() use wx log formatting instead of raw stderr writes.
//
// Ownership: as soon as kwxConsoleInitialize() is called, wxWidgets owns the
// application object. Do not call kwxAppConsole_Delete() on it afterwards;
// kwxConsoleShutdown() destroys it through wxEntryCleanup().

#include "kwx_def.h"
#include "kwx_types.h"

// Starts the wxWidgets library for a console application and calls
// wxTheApp->CallOnInit() (the console instance). argc/argv are the process
// arguments; passing argc <= 0 with a null argv uses a synthetic program name.
// Returns 1 on success and 0 on failure; on failure the library is already
// cleaned up.
EXPORT int kwxConsoleInitialize(int argc, void* argv);

// Runs the console application's OnRun() and returns its exit code. Returns -1
// when the console application is not initialized. Omit it for a program that
// does all its work in OnInit.
EXPORT int kwxConsoleRun();

// Requests the running main loop to exit.
EXPORT void kwxConsoleExitMainLoop();

// Calls the console application's CallOnExit() and wxEntryCleanup(). Safe to
// call when the console application was never initialized (it does nothing).
EXPORT void kwxConsoleShutdown();

// Returns 1 between a successful kwxConsoleInitialize() and kwxConsoleShutdown().
EXPORT int kwxConsoleIsInitialized();

// Returns the wxAppConsole installed as the process application object, or null
// before initialization. The pointer is borrowed; wxWidgets owns it.
EXPORT TClass(wxAppConsole) kwxConsoleGetApp();

// Processes pending events on the console application.
EXPORT void kwxConsoleProcessPendingEvents();

// Yields to pending events; returns non-zero if events were processed.
EXPORT int kwxConsoleYield();
