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

/* Forward declarations from kwxFFI - you'd include kwx_glue.h in practice
 *
 * Note the key differences from a naive C API:
 *  - String arguments are void* (opaque wxString*), not const char*.
 *    Use wxString_CreateUTF8() to allocate and wxString_Delete() to free.
 *  - wxFrame/wxButton_Create take position+size as four separate ints
 *    (TRect expands to left, top, width, height).
 *  - wxWindow_Show takes only the window pointer (no 'show' flag).
 *  - Event binding uses wxEvtHandler_Connect + wxClosure_Create.
 *  - Event id constants come from exp_wxEVT_*() functions, not macros.
 */

/* wxString helpers */
extern void* wxString_CreateUTF8(const char* buffer);
extern void  wxString_Delete(void* pObject);

/* Window creation */
extern void* wxFrame_Create(void* parent, int id, void* text,
                             int left, int top, int width, int height, int style);
extern void* wxButton_Create(void* parent, int id, void* text,
                              int left, int top, int width, int height, int style);

/* Window methods */
extern void wxWindow_Show(void* pObject);
extern void wxWindow_Center(void* pObject, int direction);

/* Event binding */
extern void* wxClosure_Create(void* fun, void* data);
extern int   wxEvtHandler_Connect(void* pObject, int first, int last, int type, void* data);

/* Event type constants */
extern int exp_wxEVT_BUTTON(void);

/* wxWidgets style constants */
extern int expwxDEFAULT_FRAME_STYLE(void);
extern int expwxID_ANY(void);
extern int expwxBOTH(void);  /* wxBOTH = wxHORIZONTAL | wxVERTICAL, used for Center() */

/* Our button click handler -- signature must match TClosureFun (void*) */
void on_button_click(void* event)
{
    printf("Button clicked! Exiting...\n");
    kwxApp_ExitMainLoop();
}

int main(int argc, char** argv)
{
    void* frame;
    void* button;
    void* frame_title;
    void* button_label;
    void* closure;

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

    /* Create wxString objects for titles/labels.
     * kwxFFI uses opaque wxString* pointers -- strings are NOT raw char*. */
    frame_title  = wxString_CreateUTF8("Hello from C");
    button_label = wxString_CreateUTF8("Click Me!");

    /* Create a frame with the default style (min/max/close system buttons).
     * expwxDEFAULT_FRAME_STYLE() returns wxDEFAULT_FRAME_STYLE at runtime. */
    frame = wxFrame_Create(
        NULL,                        /* parent */
        expwxID_ANY(),               /* id */
        frame_title,                 /* title (wxString*) */
        -1, -1,                      /* position: x, y (-1 = default) */
        400, 300,                    /* size: width, height */
        expwxDEFAULT_FRAME_STYLE()   /* style: caption + system buttons */
    );

    /* Create a button */
    button = wxButton_Create(
        frame,          /* parent */
        100,            /* id */
        button_label,   /* label (wxString*) */
        50, 50,         /* position: x, y */
        100, 30,        /* size: width, height */
        0               /* style = default */
    );

    /* Free the wxString objects now that the widgets have been created */
    wxString_Delete(frame_title);
    wxString_Delete(button_label);

    /* Bind button click event via wxClosure + wxEvtHandler_Connect.
     * wxClosure wraps a C function pointer so the event system can call it. */
    closure = wxClosure_Create(on_button_click, NULL);
    wxEvtHandler_Connect(button, 100, 100, exp_wxEVT_BUTTON(), closure);

    /* Center the frame on screen before showing it */
    wxWindow_Center(frame, expwxBOTH());

    /* Show the frame (no 'show' flag needed -- always shows) */
    wxWindow_Show(frame);

    /* Set as top window so app exits when it's closed */
    kwxApp_SetTopWindow(frame);

    /* Run the event loop */
    printf("Starting main loop...\n");
    int result = kwxApp_MainLoop();

    /* Cleanup (optional - happens automatically) */
    kwxApp_Shutdown();

    return result;
}
