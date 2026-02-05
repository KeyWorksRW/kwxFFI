# kwxApp - Pure C Interface for wxWidgets

This directory provides a pure C interface for initializing and running wxWidgets applications. Foreign language bindings (Fortran, Lua, Perl, etc.) use this instead of trying to subclass `wxApp` in C++.

## Files

- **kwxApp.h** - The C header that foreign languages include
- **kwxApp.cpp** - The C++ implementation (foreign languages never see this)
- **example_main.c** - Example showing usage from pure C

## How It Works

The C++ implementation (`kwxApp.cpp`) contains a `wxApp` subclass that handles all the wxWidgets initialization. The C interface (`kwxApp.h`) exposes only C-callable functions that foreign languages can easily bind to.

## Usage Pattern

```c
#include "kwxApp.h"

int main(int argc, char** argv)
{
    // 1. Initialize wxWidgets
    if (!kwxApp_Initialize(argc, argv))
        return 1;

    // 2. Set application properties
    kwxApp_SetAppName("MyApp");
    kwxApp_InitAllImageHandlers();

    // 3. Create your UI using kwxFFI functions
    void* frame = wxFrame_Create(...);
    wxWindow_Show(frame, 1);
    kwxApp_SetTopWindow(frame);

    // 4. Run the event loop
    return kwxApp_MainLoop();
}
```

## For Fortran

Fortran code would use ISO_C_BINDING to call these functions:

```fortran
program hello_wx
    use iso_c_binding
    implicit none

    interface
        integer(c_int) function kwxApp_Initialize(argc, argv) bind(C)
            import :: c_int, c_ptr
            integer(c_int), value :: argc
            type(c_ptr), value :: argv
        end function

        integer(c_int) function kwxApp_MainLoop() bind(C)
            import :: c_int
        end function

        ! ... more bindings ...
    end interface

    integer(c_int) :: result

    result = kwxApp_Initialize(0, c_null_ptr)
    if (result == 0) stop "Failed to initialize"

    ! Create UI...

    result = kwxApp_MainLoop()
end program
```

## Building

This example is not built automatically. To build:

1. Compile `kwxApp.cpp` with your C++ compiler, linking against wxWidgets
2. Link the resulting object with your C/Fortran code

The kwxFFI library could optionally include kwxApp as part of its build.

## String Handling

- Functions returning `const char*` (like `kwxApp_GetAppName`) return pointers to internal buffers - do not free them
- Functions returning `char*` (like `kwxApp_GetOsDescription`) allocate new strings - call `kwxApp_FreeString()` when done

## Idle Callbacks

For periodic background tasks:

```c
void my_idle_handler(void* data)
{
    // Called every N milliseconds
}

// Set up 200ms idle callback
kwxApp_SetIdleCallback(200, my_idle_handler, NULL);

// Disable
kwxApp_SetIdleCallback(0, NULL, NULL);
```

Minimum interval is 100ms to prevent excessive CPU usage.
