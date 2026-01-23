# SampleApp - Example wxApp for kwxFFI

This directory contains an example wxApp implementation demonstrating how a foreign language port might structure its application initialization using kwxFFI.

## Purpose

This code is provided as a **reference example only**. It is **NOT** built as part of the kwxFFI library.

Each language port (wxFortran, wxGO, wxJulia, wxLuaJit, wxRust3, etc.) will need to create its own main application appropriate for that language's runtime and initialization requirements.

## Historical Note

The original class was named `ELJApp`, which came from the Eiffel-wxWidgets (wxEiffel) project. It has been renamed to `SampleApp` to be more descriptive for new developers.

## Key Components

### SampleApp Class

A custom `wxApp` subclass that demonstrates:
- **OnInit/OnExit**: Custom initialization and cleanup hooks
- **HandleEvent**: Routes wxWidgets events through the closure/callback system to foreign function callbacks
- **InitZipFileSystem**: Optional helper for ZIP archive support
- **InitImageHandlers**: Optional helper for image format support
- **OnInitCmdLine/OnCmdLineParsed**: Overrides to prevent wxWidgets from interfering with foreign language command line parsing

### wxIdleTimer

Some foreign language runtimes need regular idle events to:
- Perform garbage collection
- Process pending operations
- Update UI state

This timer wakes up the event loop at configurable intervals.

### C Interface Functions

The `SampleApp_*` functions provide a C API for:
- Application lifecycle (MainLoop, Exit, etc.)
- Configuration (app name, vendor name, etc.)
- System utilities (display size, mouse position, etc.)
- Idle timer management

## Usage

To use this as a reference:

1. Study the structure of `SampleApp.h` and `SampleApp.cpp`
2. Adapt the patterns to your target language's requirements
3. Create your own app class with the initialization your language runtime needs
4. Connect event handlers using your language's callback mechanism

## Files

- `SampleApp.h` - Header with class declarations
- `SampleApp.cpp` - Implementation with C interface functions
- `README.md` - This file
