#pragma once

// kwxCustomBackgroundWindow -- wxCustomBackgroundWindow<wxScrolledWindow>.
//
// wxWidgets' wx/custombgwin.h provides wxCustomBackgroundWindow<W>, a template mixin that puts a
// tiled bitmap behind a window of any wxWindow-derived class. A C++ template cannot appear in the
// generated model, so the scrolled-window instantiation is declared here under its own name; it
// derives from wxScrolledWindow and therefore carries the whole scrolled-window and window API.
//
// SetBackgroundBitmap() hands the bitmap to wxWidgets, which keeps its own copy: on MSW the bitmap
// becomes the window's native background brush, so it paints the whole client area and shows
// through transparent children; on the other platforms the mixin paints it from an
// EVT_ERASE_BACKGROUND handler it installs. A window that binds its own EVT_ERASE_BACKGROUND
// handler must call event.Skip() for the bitmap to reach the screen -- that is what the wxWidgets
// erase sample does. ClearBackgroundBitmap() removes the custom background.
TClassDefExtend(kwxCustomBackgroundWindow, wxScrolledWindow) TClass(kwxCustomBackgroundWindow)
    kwxCustomBackgroundWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                                     int style);
// The same constructor with wxWidgets' own defaults: unset position and size, and
// style = wxHSCROLL | wxVSCROLL (wxScrolledWindow::Create's defaults).
TClass(kwxCustomBackgroundWindow)
    kwxCustomBackgroundWindow_CreateDefault(TClass(wxWindow) parent, int id);
void kwxCustomBackgroundWindow_SetBackgroundBitmap(TSelf(kwxCustomBackgroundWindow) pObject,
                                                   TClass(wxBitmap) bitmap);
void kwxCustomBackgroundWindow_ClearBackgroundBitmap(TSelf(kwxCustomBackgroundWindow) pObject);
