#pragma once

// Dialogs, validators, and platform helpers.
//
// Declarations for the classes implemented in:
//   src/wx_numvalidator.cpp, src/wx_numberdlg.cpp, src/wx_choicedlg.cpp,
//   src/wx_aboutdlg.cpp, src/wx_credentialdlg.cpp, src/wx_richtooltip.cpp,
//   src/wx_filedlgcustomize.cpp, src/wx_exthelp.cpp, src/wx_genericdirctrl.cpp,
//   src/wx_genericdialogs.cpp, src/wx_taskbarbutton.cpp

TClassDefExtend(wxCredentialEntryDialog, wxDialog) TClass(wxCredentialEntryDialog)
    wxCredentialEntryDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                                   TClass(wxString) title, TClass(wxString) user,
                                   TClass(wxString) password);
TClass(wxString) wxCredentialEntryDialog_GetPassword(TSelf(wxCredentialEntryDialog) pObject);
TClass(wxString) wxCredentialEntryDialog_GetUser(TSelf(wxCredentialEntryDialog) pObject);
void wxCredentialEntryDialog_SetPassword(TSelf(wxCredentialEntryDialog) pObject,
                                         TClass(wxString) password);
void wxCredentialEntryDialog_SetUser(TSelf(wxCredentialEntryDialog) pObject, TClass(wxString) user);
void wxCredentialEntryDialog_Delete(TSelf(wxCredentialEntryDialog) pObject);

TClassDefExtend(wxDirFilterListCtrl, wxChoice) TClass(wxDirFilterListCtrl)
    wxDirFilterListCtrl_Create(TClass(wxGenericDirCtrl) parent, int id, TPoint(x, y),
                               TSize(width, height), long style);
void wxDirFilterListCtrl_FillFilterList(TSelf(wxDirFilterListCtrl) pObject, TClass(wxString) filter,
                                        int default_filter);
void wxDirFilterListCtrl_Delete(TSelf(wxDirFilterListCtrl) pObject);

TClassDefExtend(wxExtHelpController, wxHelpControllerBase) TClass(wxExtHelpController)
    wxExtHelpController_Create(TClass(wxWindow) parent_window);
TBool wxExtHelpController_DisplayBlock(TSelf(wxExtHelpController) pObject, long block_no);
TBool wxExtHelpController_DisplayContents(TSelf(wxExtHelpController) pObject);
TBool wxExtHelpController_DisplaySection(TSelf(wxExtHelpController) pObject, int section_no);
TBool wxExtHelpController_DisplaySectionName(TSelf(wxExtHelpController) pObject,
                                             TClass(wxString) section);
TBool wxExtHelpController_Initialize(TSelf(wxExtHelpController) pObject, TClass(wxString) dir);
TBool wxExtHelpController_KeywordSearch(TSelf(wxExtHelpController) pObject,
                                        TClass(wxString) keyword, int mode);
TBool wxExtHelpController_LoadFile(TSelf(wxExtHelpController) pObject, TClass(wxString) file);
TBool wxExtHelpController_Quit(TSelf(wxExtHelpController) pObject);
void wxExtHelpController_SetViewer(TSelf(wxExtHelpController) pObject, TClass(wxString) viewer,
                                   long flags);
void wxExtHelpController_Delete(TSelf(wxExtHelpController) pObject);

TClassDefExtend(wxFileDialogCustomControl, wxEvtHandler) void wxFileDialogCustomControl_Disable(
    TSelf(wxFileDialogCustomControl) pObject);
void wxFileDialogCustomControl_Enable(TSelf(wxFileDialogCustomControl) pObject, TBool enable);
int wxFileDialogCustomControl_GetSelection(TSelf(wxFileDialogCustomControl) pObject);
TClass(wxString) wxFileDialogCustomControl_GetTextValue(TSelf(wxFileDialogCustomControl) pObject);
TBool wxFileDialogCustomControl_GetValue(TSelf(wxFileDialogCustomControl) pObject);
void wxFileDialogCustomControl_Hide(TSelf(wxFileDialogCustomControl) pObject);
void wxFileDialogCustomControl_SetLabelText(TSelf(wxFileDialogCustomControl) pObject,
                                            TClass(wxString) text);
void wxFileDialogCustomControl_SetSelection(TSelf(wxFileDialogCustomControl) pObject,
                                            int selection);
void wxFileDialogCustomControl_SetTextValue(TSelf(wxFileDialogCustomControl) pObject,
                                            TClass(wxString) text);
void wxFileDialogCustomControl_SetValue(TSelf(wxFileDialogCustomControl) pObject, TBool value);
void wxFileDialogCustomControl_Show(TSelf(wxFileDialogCustomControl) pObject, TBool show);

TClassDef(wxFileDialogCustomize) TClass(wxFileDialogCustomControl)
    wxFileDialogCustomize_AddButton(TSelf(wxFileDialogCustomize) pObject, TClass(wxString) label);
TClass(wxFileDialogCustomControl)
    wxFileDialogCustomize_AddCheckBox(TSelf(wxFileDialogCustomize) pObject, TClass(wxString) label);
TClass(wxFileDialogCustomControl)
    wxFileDialogCustomize_AddChoice(TSelf(wxFileDialogCustomize) pObject, TArrayString(n, strings));
TClass(wxFileDialogCustomControl)
    wxFileDialogCustomize_AddRadioButton(TSelf(wxFileDialogCustomize) pObject,
                                         TClass(wxString) label);
TClass(wxFileDialogCustomControl)
    wxFileDialogCustomize_AddStaticText(TSelf(wxFileDialogCustomize) pObject,
                                        TClass(wxString) label);
TClass(wxFileDialogCustomControl)
    wxFileDialogCustomize_AddTextCtrl(TSelf(wxFileDialogCustomize) pObject, TClass(wxString) label);

TClassDef(wxFileDialogCustomizeHook) TClass(wxFileDialogCustomizeHook)
    wxFileDialogCustomizeHook_Create(void* pObject, void* add_custom_controls_func,
                                     void* update_custom_controls_func, void* transfer_data_func);
void wxFileDialogCustomizeHook_Delete(TSelf(wxFileDialogCustomizeHook) pObject);

TClassDefExtend(wxGenericAboutDialog, wxDialog) TClass(wxGenericAboutDialog)
    wxGenericAboutDialog_Create(TClass(wxAboutDialogInfo) info, TClass(wxWindow) parent);
TBool wxGenericAboutDialog_AddControl(TSelf(wxGenericAboutDialog) pObject, TClass(wxWindow) win);
TClass(wxWindow) wxGenericAboutDialog_GetCustomControlParent(TSelf(wxGenericAboutDialog) pObject);
TBool wxGenericAboutDialog_AddText(TSelf(wxGenericAboutDialog) pObject, TClass(wxString) text);
int wxGenericAboutDialog_ShowModal(TSelf(wxGenericAboutDialog) pObject);
void wxGenericAboutDialog_Delete(TSelf(wxGenericAboutDialog) pObject);

TClassDefExtend(wxGenericColourDialog, wxDialog) TClass(wxGenericColourDialog)
    wxGenericColourDialog_Create(TClass(wxWindow) parent, TClass(wxColourData) data);
void wxGenericColourDialog_GetColourData(TSelf(wxGenericColourDialog) pObject,
                                         TClassRef(wxColourData) ref);
void wxGenericColourDialog_Delete(TSelf(wxGenericColourDialog) pObject);

TClassDefExtend(wxGenericDirDialog, wxDialog) TClass(wxGenericDirDialog)
    wxGenericDirDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                              TClass(wxString) directory, int style);
TClass(wxString) wxGenericDirDialog_GetMessage(TSelf(wxGenericDirDialog) pObject);
TClass(wxString) wxGenericDirDialog_GetPath(TSelf(wxGenericDirDialog) pObject);
TArrayLen wxGenericDirDialog_GetPaths(TSelf(wxGenericDirDialog) pObject, TArrayStringOutVoid paths);
void wxGenericDirDialog_SetMessage(TSelf(wxGenericDirDialog) pObject, TClass(wxString) msg);
void wxGenericDirDialog_SetPath(TSelf(wxGenericDirDialog) pObject, TClass(wxString) pth);
void wxGenericDirDialog_Delete(TSelf(wxGenericDirDialog) pObject);

TClassDefExtend(wxGenericFileDialog, wxDialog) TClass(wxGenericFileDialog)
    wxGenericFileDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                               TClass(wxString) directory, TClass(wxString) filename,
                               TClass(wxString) wildcard, int style);
TClass(wxString) wxGenericFileDialog_GetPath(TSelf(wxGenericFileDialog) pObject);
void wxGenericFileDialog_SetPath(TSelf(wxGenericFileDialog) pObject, TClass(wxString) path);
TArrayLen wxGenericFileDialog_GetPaths(TSelf(wxGenericFileDialog) pObject,
                                       TArrayStringOutVoid paths);
TArrayLen wxGenericFileDialog_GetFilenames(TSelf(wxGenericFileDialog) pObject,
                                           TArrayStringOutVoid paths);
TClass(wxString) wxGenericFileDialog_GetDirectory(TSelf(wxGenericFileDialog) pObject);
TClass(wxString) wxGenericFileDialog_GetFilename(TSelf(wxGenericFileDialog) pObject);
void wxGenericFileDialog_SetFilename(TSelf(wxGenericFileDialog) pObject, TClass(wxString) name);
TClass(wxString) wxGenericFileDialog_GetWildcard(TSelf(wxGenericFileDialog) pObject);
void wxGenericFileDialog_SetWildcard(TSelf(wxGenericFileDialog) pObject, TClass(wxString) wildCard);
int wxGenericFileDialog_GetFilterIndex(TSelf(wxGenericFileDialog) pObject);
void wxGenericFileDialog_SetFilterIndex(TSelf(wxGenericFileDialog) pObject, int filterIndex);
TBool wxGenericFileDialog_SetCustomizeHook(TSelf(wxGenericFileDialog) pObject,
                                           TClass(wxFileDialogCustomizeHook) customizeHook);
void wxGenericFileDialog_Delete(TSelf(wxGenericFileDialog) pObject);

TClassDefExtend(wxGenericFontDialog, wxDialog) TClass(wxGenericFontDialog)
    wxGenericFontDialog_Create(TClass(wxWindow) parent, TClass(wxFontData) data);
void wxGenericFontDialog_GetFontData(TSelf(wxGenericFontDialog) pObject, TClassRef(wxFontData) ref);
void wxGenericFontDialog_Delete(TSelf(wxGenericFontDialog) pObject);

TClassDefExtend(wxMultiChoiceDialog, wxDialog) TClass(wxMultiChoiceDialog)
    wxMultiChoiceDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                               TClass(wxString) caption, TArrayString(n, choices), long style,
                               TPoint(x, y));
void wxMultiChoiceDialog_GetSelections(TSelf(wxMultiChoiceDialog) pObject,
                                       TClass(wxArrayInt) selections);
void wxMultiChoiceDialog_SetSelections(TSelf(wxMultiChoiceDialog) pObject,
                                       TClass(wxArrayInt) selections);
int wxMultiChoiceDialog_ShowModal(TSelf(wxMultiChoiceDialog) pObject);
void wxMultiChoiceDialog_Delete(TSelf(wxMultiChoiceDialog) pObject);

TClassDefExtend(wxNumberEntryDialog, wxDialog) TClass(wxNumberEntryDialog)
    wxNumberEntryDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                               TClass(wxString) prompt, TClass(wxString) caption, long value,
                               long min_value, long max_value, TPoint(x, y));
long wxNumberEntryDialog_GetValue(TSelf(wxNumberEntryDialog) pObject);
void wxNumberEntryDialog_Delete(TSelf(wxNumberEntryDialog) pObject);

TClassDefExtend(wxNumValidator, wxValidator) TClass(wxNumValidator)
    wxNumValidator_Create(TBool is_double, int style);
double wxNumValidator_GetMaxDouble(TSelf(wxNumValidator) pObject);
long wxNumValidator_GetMax(TSelf(wxNumValidator) pObject);
double wxNumValidator_GetMinDouble(TSelf(wxNumValidator) pObject);
long wxNumValidator_GetMin(TSelf(wxNumValidator) pObject);
int wxNumValidator_GetStyle(TSelf(wxNumValidator) pObject);
double wxNumValidator_GetValueDouble(TSelf(wxNumValidator) pObject);
long wxNumValidator_GetValue(TSelf(wxNumValidator) pObject);
TBool wxNumValidator_IsInRange(TSelf(wxNumValidator) pObject, long value);
TBool wxNumValidator_IsInRangeDouble(TSelf(wxNumValidator) pObject, double value);
void wxNumValidator_SetMax(TSelf(wxNumValidator) pObject, long max_value);
void wxNumValidator_SetMaxDouble(TSelf(wxNumValidator) pObject, double max_value);
void wxNumValidator_SetMin(TSelf(wxNumValidator) pObject, long min_value);
void wxNumValidator_SetMinDouble(TSelf(wxNumValidator) pObject, double min_value);
void wxNumValidator_SetRange(TSelf(wxNumValidator) pObject, long min_value, long max_value);
void wxNumValidator_SetRangeDouble(TSelf(wxNumValidator) pObject, double min_value,
                                   double max_value);
void wxNumValidator_SetStyle(TSelf(wxNumValidator) pObject, int style);
void wxNumValidator_SetValue(TSelf(wxNumValidator) pObject, long value);
void wxNumValidator_SetValueDouble(TSelf(wxNumValidator) pObject, double value);
void wxNumValidator_Delete(TSelf(wxNumValidator) pObject);

TClassDef(wxRichToolTip) TClass(wxRichToolTip)
    wxRichToolTip_Create(TClass(wxString) title, TClass(wxString) message);
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
void wxRichToolTip_SetTipKind(TSelf(wxRichToolTip) pObject, int tipKind);
void wxRichToolTip_SetBackgroundColour(TSelf(wxRichToolTip) pObject, TClass(wxColour) colour,
                                       TClass(wxColour) colour_end);
void wxRichToolTip_SetBackgroundColourSingle(TSelf(wxRichToolTip) pObject, TClass(wxColour) colour);
void wxRichToolTip_SetIcon(TSelf(wxRichToolTip) pObject, int icon);
void wxRichToolTip_SetIconBitmap(TSelf(wxRichToolTip) pObject, TClass(wxBitmap) icon);
void wxRichToolTip_SetTimeout(TSelf(wxRichToolTip) pObject, unsigned milliseconds,
                              unsigned show_delay);
void wxRichToolTip_ShowFor(TSelf(wxRichToolTip) pObject, TClass(wxWindow) win, TClass(wxRect) rect);
void wxRichToolTip_Delete(TSelf(wxRichToolTip) pObject);

TClassDef(wxTaskBarButton) TClass(wxTaskBarButton) wxTaskBarButton_New(TClass(wxWindow) parent);
// ---- Phase 3: methods on already-wrapped classes (.private/port/fix_worklist.json) ----
TBool wxTaskBarButton_AppendThumbBarButton(TSelf(wxTaskBarButton) pObject, void* button);
void* wxTaskBarButton_RemoveThumbBarButton(TSelf(wxTaskBarButton) pObject, void* button);
void wxTaskBarButton_Hide(TSelf(wxTaskBarButton) pObject);
void wxTaskBarButton_PulseProgress(TSelf(wxTaskBarButton) pObject);
void wxTaskBarButton_Realize(TSelf(wxTaskBarButton) pObject);
void wxTaskBarButton_SetOverlayIcon(TSelf(wxTaskBarButton) pObject, TClass(wxIcon) icon,
                                    TClass(wxString) description);
void wxTaskBarButton_SetProgressRange(TSelf(wxTaskBarButton) pObject, int range);
void wxTaskBarButton_SetProgressState(TSelf(wxTaskBarButton) pObject, int state);
void wxTaskBarButton_SetProgressValue(TSelf(wxTaskBarButton) pObject, int value);
void wxTaskBarButton_SetThumbnailClip(TSelf(wxTaskBarButton) pObject, TRect(x, y, width, height));
void wxTaskBarButton_SetThumbnailTooltip(TSelf(wxTaskBarButton) pObject, TClass(wxString) tooltip);
void wxTaskBarButton_Show(TSelf(wxTaskBarButton) pObject, TBool show);
void wxTaskBarButton_Delete(TSelf(wxTaskBarButton) pObject);

TClassDefExtend(wxRichMessageDialog, wxMessageDialog) TClass(wxRichMessageDialog)
    wxRichMessageDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                               TClass(wxString) caption, int style);
void wxRichMessageDialog_ShowCheckBox(TSelf(wxRichMessageDialog) pObject,
                                      TClass(wxString) checkBoxText, TBool checked);
TBool wxRichMessageDialog_IsCheckBoxChecked(TSelf(wxRichMessageDialog) pObject);
void wxRichMessageDialog_ShowDetailedText(TSelf(wxRichMessageDialog) pObject,
                                          TClass(wxString) text);
void wxRichMessageDialog_SetFooterText(TSelf(wxRichMessageDialog) pObject, TClass(wxString) text);
void wxRichMessageDialog_SetFooterIcon(TSelf(wxRichMessageDialog) pObject, int icon);
void wxRichMessageDialog_Delete(TSelf(wxRichMessageDialog) pObject);

TClassDefExtend(wxAddRemoveCtrl, wxPanel) TClass(wxAddRemoveCtrl)
    wxAddRemoveCtrl_Create(TClass(wxWindow) parent, int id, TPoint(x, y), TSize(width, height),
                           int style);
void wxAddRemoveCtrl_SetAdaptor(TSelf(wxAddRemoveCtrl) pObject, void* adaptor);
void wxAddRemoveCtrl_SetButtonsToolTips(TSelf(wxAddRemoveCtrl) pObject, TClass(wxString) addtip,
                                        TClass(wxString) removetip);
void wxAddRemoveCtrl_Delete(TSelf(wxAddRemoveCtrl) pObject);

TClassDef(wxAppProgressIndicator) TClass(wxAppProgressIndicator)
    wxAppProgressIndicator_Create(TClass(wxWindow) parent, int maxValue);
TBool wxAppProgressIndicator_IsAvailable(TSelf(wxAppProgressIndicator) pObject);
void wxAppProgressIndicator_SetValue(TSelf(wxAppProgressIndicator) pObject, int value);
void wxAppProgressIndicator_SetRange(TSelf(wxAppProgressIndicator) pObject, int range);
void wxAppProgressIndicator_Pulse(TSelf(wxAppProgressIndicator) pObject);
void wxAppProgressIndicator_Delete(TSelf(wxAppProgressIndicator) pObject);

TClassDefExtend(wxRearrangeDialog, wxDialog) TClass(wxRearrangeDialog)
    wxRearrangeDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                             TClass(wxString) title, TClass(wxArrayInt) order,
                             TClass(wxArrayString) items, TPoint(x, y));
TClass(wxArrayInt) wxRearrangeDialog_GetOrder(TSelf(wxRearrangeDialog) pObject);
TClass(wxRearrangeList) wxRearrangeDialog_GetList(TSelf(wxRearrangeDialog) pObject);
void wxRearrangeDialog_AddExtraControls(TSelf(wxRearrangeDialog) pObject, TClass(wxWindow) win);
void wxRearrangeDialog_Delete(TSelf(wxRearrangeDialog) pObject);

TClassDefExtend(wxColourDialogEvent, wxCommandEvent) TClass(wxColourDialogEvent)
    wxColourDialogEvent_Create(int id, TClass(wxColourDialog) dialog, TClass(wxColour) colour);
TClass(wxColour) wxColourDialogEvent_GetColour(TSelf(wxColourDialogEvent) pObject);
TClass(wxColourDialog) wxColourDialogEvent_GetDialog(TSelf(wxColourDialogEvent) pObject);
void wxColourDialogEvent_Delete(TSelf(wxColourDialogEvent) pObject);
void wxColourDialog_Delete(TSelf(wxColourDialog) pObject);

TClassDefExtend(wxWindowModalDialogEvent, wxCommandEvent) TClass(wxWindowModalDialogEvent)
    wxWindowModalDialogEvent_Create(int id, TClass(wxDialog) dialog);
TClass(wxDialog) wxWindowModalDialogEvent_GetDialog(TSelf(wxWindowModalDialogEvent) pObject);
void wxWindowModalDialogEvent_Delete(TSelf(wxWindowModalDialogEvent) pObject);

// The creator callback must return the wxWindow* it creates.  The FFI callback
// ABI is void-only, so the callback must create its panel with the parent it
// receives as pObject; the wrapper returns the child the callback added.
TBool wxFileDialog_SetExtraControlCreator(TSelf(wxFileDialog) pObject, void* pFunction);
void wxFontDialog_Delete(TSelf(wxFontDialog) pObject);
