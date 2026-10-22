#pragma once

// Ribbon event classes, the ribbon art provider and control base class, the AUI floating
// frame and MDI client window, and the WebView scheme handler.
//
// kwxgen merges repeated TClassDef/TClassDefExtend blocks by class name, so the blocks here
// extend the wxRibbonBar/wxAui*/wxWebView blocks in kwx_classes.h rather than replacing them.

// wxRibbonBarEvent

TClassDefExtend(wxRibbonBarEvent, wxNotifyEvent) TClass(wxRibbonPage)
    wxRibbonBarEvent_GetPage(TSelf(wxRibbonBarEvent) pObject);
void wxRibbonBarEvent_SetPage(TSelf(wxRibbonBarEvent) pObject, TClass(wxRibbonPage) page);

// wxRibbonButtonBarEvent

TClassDefExtend(wxRibbonButtonBarEvent, wxCommandEvent) TClass(wxRibbonButtonBar)
    wxRibbonButtonBarEvent_GetBar(TSelf(wxRibbonButtonBarEvent) pObject);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBarEvent_GetButton(TSelf(wxRibbonButtonBarEvent) pObject);
TBool wxRibbonButtonBarEvent_PopupMenu(TSelf(wxRibbonButtonBarEvent) pObject, TClass(wxMenu) menu);
void wxRibbonButtonBarEvent_SetBar(TSelf(wxRibbonButtonBarEvent) pObject,
                                   TClass(wxRibbonButtonBar) bar);
void wxRibbonButtonBarEvent_SetButton(TSelf(wxRibbonButtonBarEvent) pObject,
                                      TClass(wxRibbonButtonBarButtonBase) button);

// wxRibbonGalleryEvent

TClassDefExtend(wxRibbonGalleryEvent, wxCommandEvent) TClass(wxRibbonGallery)
    wxRibbonGalleryEvent_GetGallery(TSelf(wxRibbonGalleryEvent) pObject);
TClass(wxRibbonGalleryItem)
    wxRibbonGalleryEvent_GetGalleryItem(TSelf(wxRibbonGalleryEvent) pObject);
void wxRibbonGalleryEvent_SetGallery(TSelf(wxRibbonGalleryEvent) pObject,
                                     TClass(wxRibbonGallery) gallery);
void wxRibbonGalleryEvent_SetGalleryItem(TSelf(wxRibbonGalleryEvent) pObject,
                                         TClass(wxRibbonGalleryItem) item);

// wxRibbonPanelEvent

TClassDefExtend(wxRibbonPanelEvent, wxCommandEvent) TClass(wxRibbonPanel)
    wxRibbonPanelEvent_GetPanel(TSelf(wxRibbonPanelEvent) pObject);
void wxRibbonPanelEvent_SetPanel(TSelf(wxRibbonPanelEvent) pObject, TClass(wxRibbonPanel) panel);

// wxRibbonToolBarEvent

TClassDefExtend(wxRibbonToolBarEvent, wxCommandEvent) TClass(wxRibbonToolBar)
    wxRibbonToolBarEvent_GetBar(TSelf(wxRibbonToolBarEvent) pObject);
TBool wxRibbonToolBarEvent_PopupMenu(TSelf(wxRibbonToolBarEvent) pObject, TClass(wxMenu) menu);
void wxRibbonToolBarEvent_SetBar(TSelf(wxRibbonToolBarEvent) pObject, TClass(wxRibbonToolBar) bar);

// wxRibbonArtProvider

TClassDef(wxRibbonArtProvider) TClass(wxRibbonArtProvider)
    wxRibbonArtProvider_Clone(TSelf(wxRibbonArtProvider) pObject);
void wxRibbonArtProvider_Delete(TSelf(wxRibbonArtProvider) pObject);
TClass(wxColour) wxRibbonArtProvider_GetColour(TSelf(wxRibbonArtProvider) pObject, int id);
TClass(wxFont) wxRibbonArtProvider_GetFont(TSelf(wxRibbonArtProvider) pObject, int id);
void wxRibbonArtProvider_SetColour(TSelf(wxRibbonArtProvider) pObject, int id,
                                   TClass(wxColour) colour);
void wxRibbonArtProvider_SetFont(TSelf(wxRibbonArtProvider) pObject, int id, TClass(wxFont) font);

// wxRibbonControl

TClassDefExtend(wxRibbonControl, wxControl) TClass(wxRibbonArtProvider)
    wxRibbonControl_GetArtProvider(TSelf(wxRibbonControl) pObject);
void wxRibbonControl_SetArtProvider(TSelf(wxRibbonControl) pObject,
                                    TClass(wxRibbonArtProvider) art);
void wxRibbonControl_DismissKeyTips(TSelf(wxRibbonControl) pObject);
TClass(wxRibbonBar) wxRibbonControl_GetAncestorRibbonBar(TSelf(wxRibbonControl) pObject);
TClass(wxSize)
    wxRibbonControl_GetBestSizeForParentSize(TSelf(wxRibbonControl) pObject, TSize(width, height));
TClass(wxSize) wxRibbonControl_GetNextLargerSize(TSelf(wxRibbonControl) pObject, int direction);
TClass(wxSize) wxRibbonControl_GetNextLargerSize_Relative(TSelf(wxRibbonControl) pObject,
                                                          int direction, TSize(width, height));
TClass(wxSize) wxRibbonControl_GetNextSmallerSize(TSelf(wxRibbonControl) pObject, int direction);
TClass(wxSize) wxRibbonControl_GetNextSmallerSize_Relative(TSelf(wxRibbonControl) pObject,
                                                           int direction, TSize(width, height));
TBool wxRibbonControl_IsSizingContinuous(TSelf(wxRibbonControl) pObject);
TBool wxRibbonControl_Realize(TSelf(wxRibbonControl) pObject);
TBool wxRibbonControl_Realise(TSelf(wxRibbonControl) pObject);

// wxAuiFloatingFrame

TClassDefExtend(wxAuiFloatingFrame, wxFrame) TClass(wxAuiFloatingFrame)
    wxAuiFloatingFrame_Create(TClass(wxWindow) parent, TClass(wxAuiManager) ownerMgr,
                              TClass(wxAuiPaneInfo) pane, int id, int style);
void wxAuiFloatingFrame_Delete(TSelf(wxAuiFloatingFrame) pObject);
TClass(wxAuiManager) wxAuiFloatingFrame_GetOwnerManager(TSelf(wxAuiFloatingFrame) pObject);

// wxAuiMDIClientWindow

TClassDefExtend(wxAuiMDIClientWindow, wxAuiNotebook) TClass(wxAuiMDIChildFrame)
    wxAuiMDIClientWindow_GetActiveChild(TSelf(wxAuiMDIClientWindow) pObject);
TBool wxAuiMDIClientWindow_CreateClient(TSelf(wxAuiMDIClientWindow) pObject,
                                        TClass(wxAuiMDIParentFrame) parent, int style);
void wxAuiMDIClientWindow_Delete(TSelf(wxAuiMDIClientWindow) pObject);
void wxAuiMDIClientWindow_SetActiveChild(TSelf(wxAuiMDIClientWindow) pObject,
                                         TClass(wxAuiMDIChildFrame) child);
int wxAuiMDIClientWindow_SetSelection(TSelf(wxAuiMDIClientWindow) pObject, size_t page);

// wxWebViewHandler

TClassDef(wxWebViewHandler) TClass(wxWebViewHandler)
    wxWebViewHandler_Create(TClass(wxString) scheme);
void wxWebViewHandler_Delete(TSelf(wxWebViewHandler) pObject);
TClass(wxFSFile) wxWebViewHandler_GetFile(TSelf(wxWebViewHandler) pObject, TClass(wxString) uri);
TClass(wxString) wxWebViewHandler_GetName(TSelf(wxWebViewHandler) pObject);

// wxWebView handler registration (extends the wxWebView block in kwx_classes.h).
// The handler is owned by the web view after registration, matching the wxWidgets contract.

TClassDefExtend(wxWebView, wxControl)
    wxWebView_RegisterHandler(TSelf(wxWebView) pObject, TClass(wxWebViewHandler) handler);
