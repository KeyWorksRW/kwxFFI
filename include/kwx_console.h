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
//     kwxMessageOutputUseStderr();                 // optional: GUI-subsystem hosts only
//     if (!kwxConsoleInitialize(argc, argv))
//         return 1;
//     // do the work, or call kwxConsoleRun() for an event loop
//     kwxConsoleShutdown();
//
// The default wxAppConsole::OnInit() parses the command line through
// wxCmdLineParser; help and syntax errors are written to the active
// wxMessageOutput. A GUI-subsystem executable should call
// kwxMessageOutputUseStderr() (include/kwx_log.h) so they still reach the
// inherited console; a console application does not need it. A console
// application also installs a wxLogStderr log target, so LogError() and
// LogWarning() use wx log formatting instead of raw stderr writes.
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

// Initializes a console application from an argument list a binding has already
// split into strings (a Go []string, a Fortran array, a Julia Vector{String}).
// Element 0 must be the program name, exactly like the argv a C main()
// receives. wxWidgets uses it for GetAppName() and for the usage synopsis
// (wxFileName(argv[0]).GetName()), so passing the executable path makes -h print
// "Usage: archive" instead of the synthetic "kwxConsoleApp" name of the
// no-argument path. wxAppConsoleBase::OnInit() also parses this list, so the
// OnInitCmdLine/OnCmdLineParsed hooks see the real arguments.
// wxWidgets keeps argc/argv for the whole lifetime of the application, so the
// wrapper copies every string into storage released by kwxConsoleShutdown(); the
// caller may free its own strings as soon as the call returns.
// An empty list (argc <= 0, or a null array) forwards to
// kwxConsoleInitialize(0, null) and its synthetic program name.
// Returns 1 on success and 0 on failure, exactly like kwxConsoleInitialize().
EXPORT int kwxConsoleInitializeFromArgs(TArrayString(argc, argv));

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

// Calls the wxAppConsoleBase implementation of OnInitCmdLine() on the process
// application object. That implementation installs the standard -h/--help and
// --verbose switches through wxCmdLineParser::SetDesc(), which REPLACES the
// parser's descriptor; a port must therefore call this FIRST inside its
// OnInitCmdLine hook, before any AddParam(), AddSwitch() or AddUsageText() call,
// or those entries are discarded. The application object comes from
// wxAppConsole::GetInstance() because a hook callback only receives the port's
// own opaque token, never the kwxAppConsole helper. The call is qualified on the
// base class, so it bypasses the kwxAppConsole override: a plain virtual call
// would re-enter the port's hook and recurse forever.
EXPORT void kwxConsoleOnInitCmdLineBase(TClass(wxCmdLineParser) parser);

// Calls the wxAppConsoleBase implementation of OnCmdLineParsed() on the process
// application object. That implementation turns verbose logging on when
// --verbose was given and returns 1 to continue. A port calls this from its
// OnCmdLineParsed hook and returns its value (TBool is int, see
// include/kwx_types.h). Like kwxConsoleOnInitCmdLineBase(), it acts on
// wxAppConsole::GetInstance() and uses a qualified base member call so the
// kwxAppConsole override is bypassed instead of re-entering the hook.
EXPORT TBool kwxConsoleOnCmdLineParsedBase(TClass(wxCmdLineParser) parser);

// ---------------------------------------------------------------------------
// Standard streams
// ---------------------------------------------------------------------------
// wxFgets() / wxFputs() (include/kwx_constants.h) take the C runtime's FILE* as
// an opaque void*.  wxWidgets has no wxStdin/wxStdout/wxStderr object, so a
// binding has no way to name the process's streams; these three getters are the
// only accessor.  The handles belong to the C runtime -- never close them.
EXPORT void* kwxStdin();
EXPORT void* kwxStdout();
EXPORT void* kwxStderr();

// Calls wxAppConsole::CheckBuildOptions(WX_BUILD_OPTIONS_SIGNATURE, componentName)
// -- the first statement of every wxWidgets sample's main(), which compares the
// wxUSE_* options the library was built with against the ones the caller was
// compiled with.  A binding has no wxUSE_* headers to build that signature from
// and WX_BUILD_OPTIONS_SIGNATURE is a macro that only exists inside the library,
// so the signature half is supplied here and the caller passes only the component
// name ("program" in the console sample).  Returns 1 when the options match,
// which is always the case for a binding that links this very library, and 0
// otherwise (wxWidgets has then already logged a fatal error).
EXPORT TBool kwxConsoleCheckBuildOptions(TString componentName);
