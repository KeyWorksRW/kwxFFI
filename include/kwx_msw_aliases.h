#pragma once

// MSW-only class aliases.
//
// kwxgen skips preprocessor lines, so every declaration in these headers is
// parsed on every platform -- including declarations for classes that only
// exist in a wxMSW build. The implementations in src/ keep the exported symbols
// on all platforms and make the unsupported branches inert (see
// src/wx_taskbarbutton.cpp), but the declarations themselves still need a type
// to name. The aliases below provide one, following the pattern in
// include/kwx_accessible.h:15-19.
//
// Only `using` statements belong in this header. tests/checks/guard_lint.py
// treats any other declaration under a platform guard as an error, and `using`
// declarations are not classified as declarations at all.

#if !defined(__WXMSW__)

using wxRegConfig = wxFileConfig;
using wxRegKey = wxObject;

// wxClient and wxServer are macros in wx/ipc.h that expand to wxTCPClient and
// wxTCPServer off MSW, and to wxDDEClient/wxDDEServer on MSW. That header is not
// part of the kwx_wrapper.h include set, so name the non-MSW targets directly.
using wxDDEClient = wxTCPClient;
using wxDDEServer = wxTCPServer;

// wxAuiDefaultToolBarArt is a macro that selects the native art class on MSW and
// the generic one elsewhere, so this alias resolves to wxAuiGenericToolBarArt.
using wxAuiMSWToolBarArt = wxAuiDefaultToolBarArt;

using wxWebViewIE = wxObject;
using wxWebViewEdge = wxObject;

#endif  // !defined(__WXMSW__)

// wx/taskbarbutton.h declares wxTaskBarButton on every platform, but only when
// wxUSE_TASKBARBUTTON is enabled. The guard below is the exact complement of
// that one, so the class is always nameable and is never redeclared.
#if !wxUSE_TASKBARBUTTON

using wxTaskBarButton = wxObject;

#endif  // !wxUSE_TASKBARBUTTON

// wx/webview.h declares nothing when web view support is disabled, so the
// wrapped classes are aliased to their nearest available base class.
#if !wxUSE_WEBVIEW

using wxWebView = wxControl;
using wxWebViewEvent = wxNotifyEvent;
using wxWebViewHandler = wxObject;
using wxWebViewFactory = wxObject;

#endif  // !wxUSE_WEBVIEW
