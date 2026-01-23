/*
 * SampleApp - Example wxApp subclass for kwxFFI
 *
 * This file demonstrates how a foreign language port might structure its
 * wxApp implementation using kwxFFI. It includes:
 * - A custom wxApp subclass with initialization and cleanup
 * - Idle timer support for sending idle events at regular intervals
 * - Event handling integration with the closure/callback system
 * - C interface functions for common wxApp operations
 *
 * NOTE: This code is provided as a reference example only. It is NOT built
 * as part of the kwxFFI library. Each language port (wxFortran, wxGO, wxJulia,
 * wxLuaJit, wxRust3, etc.) will need to create its own main application
 * appropriate for that language's runtime and initialization requirements.
 *
 * The original ELJApp name came from the Eiffel-wxWidgets (wxEiffel) project.
 */

#pragma once

#include "wrapper.h"

/*
 * wxIdleTimer - Sends periodic idle events
 *
 * Some foreign language runtimes need regular idle events to perform
 * garbage collection, process pending operations, or update UI state.
 * This timer wakes up the event loop at configurable intervals.
 */
class wxIdleTimer : public wxTimer
{
public:
    void Notify() { wxWakeUpIdle(); /* send idle events */ }
};

/*
 * SampleApp - Custom wxApp subclass for FFI initialization
 *
 * Demonstrates:
 * - Custom OnInit/OnExit for FFI-specific setup/teardown
 * - HandleEvent for routing wxWidgets events to foreign function callbacks
 * - Optional zip filesystem and image handler initialization
 * - Command line handling that doesn't interfere with foreign language args
 */
class SampleApp : public wxApp
{
public:
    bool OnInit() override;
    int OnExit() override;

    // Routes events through the closure/callback system to foreign functions
    void HandleEvent(wxEvent& evt);

    // Helper methods for optional wxWidgets features
    void InitZipFileSystem();
    void InitImageHandlers();

    // Override to prevent wxApp from parsing command line (foreign language handles this)
    void OnInitCmdLine(wxCmdLineParser& parser) override;
    bool OnCmdLineParsed(wxCmdLineParser& parser) override;
};

DECLARE_APP(SampleApp);

/*
 * Idle timer management
 */
void initIdleTimer();
void doneIdleTimer();

/*
 * Global state for the sample application
 */
extern wxIdleTimer* idleTimer;
extern wxClosure* initClosure;  // Optional closure called during OnInit
extern int APPTerminating;      // Flag indicating app is shutting down
