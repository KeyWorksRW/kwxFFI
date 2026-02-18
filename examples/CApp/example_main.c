/*
 * example_main.c - Example of using kwxApp from pure C
 *
 * This demonstrates how a foreign language binding would use kwxApp.
 * The same pattern applies to Fortran, Lua, etc.
 *
 * Compile with:
 *   - Link against kwxApp (which links against wxWidgets)
 *   - Link against kwxFFI for the widget wrappers
 */

#include "kwxApp.h"
#include <stdio.h>

/* Forward declarations from kwxFFI - you'd include kwx_glue.h in practice */
extern void* wxFrame_Create(void* parent, int id, const char* title,
                            int x, int y, int width, int height, int style);
extern void* wxButton_Create(void* parent, int id, const char* label,
                             int x, int y, int width, int height, int style);
extern void wxWindow_Show(void* window, int show);
extern void wxWindow_Centre(void* window);

/* Event binding - simplified example */
extern void wxEvtHandler_Bind(void* handler, int eventType, void* callback, int id);
extern int expEVT_BUTTON(void);

/* Our button click handler */
void on_button_click(void* event)
{
    printf("Button clicked! Exiting...\n");
    kwxApp_ExitMainLoop();
}

int main(int argc, char** argv)
{
    void* frame;
    void* button;

    /* Initialize wxWidgets */
    if (!kwxApp_Initialize(argc, argv))
    {
        fprintf(stderr, "Failed to initialize wxWidgets\n");
        return 1;
    }

    /* Set application info */
    kwxApp_SetAppName("CExample");
    kwxApp_SetVendorName("kwxFFI");

    /* Initialize image handlers if you'll use images */
    kwxApp_InitAllImageHandlers();

    /* Create a frame (main window) */
    frame = wxFrame_Create(
        NULL,           /* parent */
        -1,             /* id = wxID_ANY */
        "Hello from C", /* title */
        -1, -1,         /* position = default */
        400, 300,       /* size */
        0               /* style = default */
    );

    /* Create a button */
    button = wxButton_Create(
        frame,          /* parent */
        100,            /* id */
        "Click Me!",    /* label */
        50, 50,         /* position */
        100, 30,        /* size */
        0               /* style */
    );

    /* Bind button click event (pseudo-code - actual binding depends on kwxFFI API) */
    /* wxEvtHandler_Bind(button, expEVT_BUTTON(), on_button_click, 100); */

    /* Center and show the frame */
    wxWindow_Centre(frame);
    wxWindow_Show(frame, 1);

    /* Set as top window so app exits when it's closed */
    kwxApp_SetTopWindow(frame);

    /* Run the event loop */
    printf("Starting main loop...\n");
    int result = kwxApp_MainLoop();

    /* Cleanup (optional - happens automatically) */
    kwxApp_Shutdown();

    return result;
}
