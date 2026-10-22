// Phase 15: implementations for the residual wxRuby3 spec entries declared in
// include/kwx_spec_residual.h.

#include "kwx_wrapper.h"

#include <wx/affinematrix2d.h>
#include <wx/dataobj.h>
#include <wx/dateevt.h>
#include <wx/editlbox.h>
#include <wx/help.h>
#include <wx/hyperlink.h>
#include <wx/mdi.h>
#include <wx/mediactrl.h>
#include <wx/overlay.h>
#include <wx/pickerbase.h>
#include <wx/sysopt.h>
#include <wx/taskbar.h>
#include <wx/tipdlg.h>
#include <wx/variant.h>

extern "C"
{
    // ---------------------------------------------------------------------------
    // Event classes
    // ---------------------------------------------------------------------------

#if wxUSE_SPINCTRL
    EXPORT wxSpinDoubleEvent* wxSpinDoubleEvent_Create(int command_type, int win_id, double value)
    {
        return new wxSpinDoubleEvent((wxEventType) command_type, win_id, value);
    }

    EXPORT void wxSpinDoubleEvent_Delete(wxSpinDoubleEvent* self)
    {
        delete self;
    }

    EXPORT double wxSpinDoubleEvent_GetValue(wxSpinDoubleEvent* self)
    {
        return self->GetValue();
    }

    EXPORT void wxSpinDoubleEvent_SetValue(wxSpinDoubleEvent* self, double value)
    {
        self->SetValue(value);
    }
#endif  // wxUSE_SPINCTRL

#if wxUSE_FONTPICKERCTRL
    EXPORT wxFontPickerEvent* wxFontPickerEvent_Create(wxObject* generator, int id, wxFont* font)
    {
        return new wxFontPickerEvent(generator, id, *font);
    }

    EXPORT void wxFontPickerEvent_Delete(wxFontPickerEvent* self)
    {
        delete self;
    }

    EXPORT wxFont* wxFontPickerEvent_GetFont(wxFontPickerEvent* self)
    {
        return new wxFont(self->GetFont());
    }

    EXPORT void wxFontPickerEvent_SetFont(wxFontPickerEvent* self, wxFont* font)
    {
        self->SetFont(*font);
    }
#endif  // wxUSE_FONTPICKERCTRL

#if wxUSE_COLOURPICKERCTRL
    EXPORT wxColourPickerEvent* wxColourPickerEvent_Create(wxObject* generator, int id,
                                                           wxColour* colour, int command_type)
    {
        return new wxColourPickerEvent(generator, id, *colour, (wxEventType) command_type);
    }

    EXPORT void wxColourPickerEvent_Delete(wxColourPickerEvent* self)
    {
        delete self;
    }

    EXPORT wxColour* wxColourPickerEvent_GetColour(wxColourPickerEvent* self)
    {
        return new wxColour(self->GetColour());
    }

    EXPORT void wxColourPickerEvent_SetColour(wxColourPickerEvent* self, wxColour* colour)
    {
        self->SetColour(*colour);
    }
#endif  // wxUSE_COLOURPICKERCTRL

#if wxUSE_FILEPICKERCTRL || wxUSE_DIRPICKERCTRL
    EXPORT wxFileDirPickerEvent* wxFileDirPickerEvent_Create(int event_type, wxObject* generator,
                                                             int id, wxString* path)
    {
        return new wxFileDirPickerEvent((wxEventType) event_type, generator, id, *path);
    }

    EXPORT void wxFileDirPickerEvent_Delete(wxFileDirPickerEvent* self)
    {
        delete self;
    }

    EXPORT wxString* wxFileDirPickerEvent_GetPath(wxFileDirPickerEvent* self)
    {
        return new wxString(self->GetPath());
    }

    EXPORT void wxFileDirPickerEvent_SetPath(wxFileDirPickerEvent* self, wxString* path)
    {
        self->SetPath(*path);
    }
#endif  // wxUSE_FILEPICKERCTRL || wxUSE_DIRPICKERCTRL

#if wxUSE_FILECTRL
    EXPORT wxFileCtrlEvent* wxFileCtrlEvent_Create(int event_type, wxObject* generator, int id)
    {
        return new wxFileCtrlEvent((wxEventType) event_type, generator, id);
    }

    EXPORT void wxFileCtrlEvent_Delete(wxFileCtrlEvent* self)
    {
        delete self;
    }

    EXPORT void wxFileCtrlEvent_SetFiles(wxFileCtrlEvent* self, wxArrayString* files)
    {
        self->SetFiles(*files);
    }

    EXPORT void wxFileCtrlEvent_SetDirectory(wxFileCtrlEvent* self, wxString* directory)
    {
        self->SetDirectory(*directory);
    }

    EXPORT void wxFileCtrlEvent_SetFilterIndex(wxFileCtrlEvent* self, int filter_index)
    {
        self->SetFilterIndex(filter_index);
    }

    EXPORT void wxFileCtrlEvent_GetFiles(wxFileCtrlEvent* self, wxArrayString* files)
    {
        *files = self->GetFiles();
    }

    EXPORT wxString* wxFileCtrlEvent_GetDirectory(wxFileCtrlEvent* self)
    {
        return new wxString(self->GetDirectory());
    }

    EXPORT int wxFileCtrlEvent_GetFilterIndex(wxFileCtrlEvent* self)
    {
        return self->GetFilterIndex();
    }

    EXPORT wxString* wxFileCtrlEvent_GetFile(wxFileCtrlEvent* self)
    {
        return new wxString(self->GetFile());
    }
#endif  // wxUSE_FILECTRL

#if wxUSE_HEADERCTRL
    EXPORT wxHeaderCtrlEvent* wxHeaderCtrlEvent_Create(int command_type, int win_id)
    {
        return new wxHeaderCtrlEvent((wxEventType) command_type, win_id);
    }

    EXPORT void wxHeaderCtrlEvent_Delete(wxHeaderCtrlEvent* self)
    {
        delete self;
    }

    EXPORT int wxHeaderCtrlEvent_GetColumn(wxHeaderCtrlEvent* self)
    {
        return self->GetColumn();
    }

    EXPORT void wxHeaderCtrlEvent_SetColumn(wxHeaderCtrlEvent* self, int column)
    {
        self->SetColumn(column);
    }

    EXPORT int wxHeaderCtrlEvent_GetWidth(wxHeaderCtrlEvent* self)
    {
        return self->GetWidth();
    }

    EXPORT void wxHeaderCtrlEvent_SetWidth(wxHeaderCtrlEvent* self, int width)
    {
        self->SetWidth(width);
    }

    EXPORT int wxHeaderCtrlEvent_GetNewOrder(wxHeaderCtrlEvent* self)
    {
        return (int) self->GetNewOrder();
    }

    EXPORT void wxHeaderCtrlEvent_SetNewOrder(wxHeaderCtrlEvent* self, int order)
    {
        self->SetNewOrder((unsigned int) order);
    }
#endif  // wxUSE_HEADERCTRL

    EXPORT wxDateEvent* wxDateEvent_Create()
    {
        return new wxDateEvent();
    }

    EXPORT void wxDateEvent_Delete(wxDateEvent* self)
    {
        delete self;
    }

    EXPORT void wxDateEvent_GetDate(wxDateEvent* self, wxDateTime* date)
    {
        *date = self->GetDate();
    }

    EXPORT void wxDateEvent_SetDate(wxDateEvent* self, wxDateTime* date)
    {
        self->SetDate(*date);
    }

#if wxUSE_TASKBARICON
    EXPORT wxTaskBarIconEvent* wxTaskBarIconEvent_Create(int event_type,
                                                         wxTaskBarIcon* task_bar_icon)
    {
        return new wxTaskBarIconEvent((wxEventType) event_type, task_bar_icon);
    }

    EXPORT void wxTaskBarIconEvent_Delete(wxTaskBarIconEvent* self)
    {
        delete self;
    }
#endif  // wxUSE_TASKBARICON

#if wxUSE_MEDIACTRL
    EXPORT wxMediaEvent* wxMediaEvent_Create(int command_type, int win_id)
    {
        return new wxMediaEvent((wxEventType) command_type, win_id);
    }

    EXPORT void wxMediaEvent_Delete(wxMediaEvent* self)
    {
        delete self;
    }
#endif  // wxUSE_MEDIACTRL

#if wxUSE_HYPERLINKCTRL
    EXPORT wxHyperlinkEvent* wxHyperlinkEvent_Create(wxObject* generator, int id, wxString* url)
    {
        return new wxHyperlinkEvent(generator, id, *url);
    }

    EXPORT void wxHyperlinkEvent_Delete(wxHyperlinkEvent* self)
    {
        delete self;
    }

    EXPORT wxString* wxHyperlinkEvent_GetURL(wxHyperlinkEvent* self)
    {
        return new wxString(self->GetURL());
    }

    EXPORT void wxHyperlinkEvent_SetURL(wxHyperlinkEvent* self, wxString* url)
    {
        self->SetURL(*url);
    }
#endif  // wxUSE_HYPERLINKCTRL

    EXPORT wxThreadEvent* wxThreadEvent_Create(int event_type, int id)
    {
        return new wxThreadEvent((wxEventType) event_type, id);
    }

    EXPORT void wxThreadEvent_Delete(wxThreadEvent* self)
    {
        delete self;
    }

    EXPORT wxString* wxThreadEvent_GetString(wxThreadEvent* self)
    {
        return new wxString(self->GetString());
    }

    EXPORT void wxThreadEvent_SetString(wxThreadEvent* self, wxString* text)
    {
        self->SetString(*text);
    }

    EXPORT int wxThreadEvent_GetInt(wxThreadEvent* self)
    {
        return self->GetInt();
    }

    EXPORT void wxThreadEvent_SetInt(wxThreadEvent* self, int value)
    {
        self->SetInt(value);
    }

    EXPORT long wxThreadEvent_GetExtraLong(wxThreadEvent* self)
    {
        return self->GetExtraLong();
    }

    EXPORT void wxThreadEvent_SetExtraLong(wxThreadEvent* self, long value)
    {
        self->SetExtraLong(value);
    }

    EXPORT wxSplitterEvent* wxSplitterEvent_Create(int event_type, wxSplitterWindow* splitter)
    {
        return new wxSplitterEvent((wxEventType) event_type, splitter);
    }

    EXPORT void wxSplitterEvent_Delete(wxSplitterEvent* self)
    {
        delete self;
    }

    EXPORT void wxSplitterEvent_SetSashPosition(wxSplitterEvent* self, int position)
    {
        self->SetSashPosition(position);
    }

    EXPORT int wxSplitterEvent_GetSashPosition(wxSplitterEvent* self)
    {
        return self->GetSashPosition();
    }

    EXPORT void wxSplitterEvent_SetSize(wxSplitterEvent* self, int old_size, int new_size)
    {
        self->SetSize(old_size, new_size);
    }

    EXPORT int wxSplitterEvent_GetOldSize(wxSplitterEvent* self)
    {
        return self->GetOldSize();
    }

    EXPORT int wxSplitterEvent_GetNewSize(wxSplitterEvent* self)
    {
        return self->GetNewSize();
    }

    EXPORT wxWindow* wxSplitterEvent_GetWindowBeingRemoved(wxSplitterEvent* self)
    {
        return self->GetWindowBeingRemoved();
    }

    EXPORT int wxSplitterEvent_GetX(wxSplitterEvent* self)
    {
        return self->GetX();
    }

    EXPORT int wxSplitterEvent_GetY(wxSplitterEvent* self)
    {
        return self->GetY();
    }

    // ---------------------------------------------------------------------------
    // wxPickerBase
    // ---------------------------------------------------------------------------

    EXPORT void wxPickerBase_SetInternalMargin(wxPickerBase* self, int margin)
    {
        self->SetInternalMargin(margin);
    }

    EXPORT int wxPickerBase_GetInternalMargin(wxPickerBase* self)
    {
        return self->GetInternalMargin();
    }

    EXPORT void wxPickerBase_SetTextCtrlProportion(wxPickerBase* self, int proportion)
    {
        self->SetTextCtrlProportion(proportion);
    }

    EXPORT int wxPickerBase_GetTextCtrlProportion(wxPickerBase* self)
    {
        return self->GetTextCtrlProportion();
    }

    EXPORT void wxPickerBase_SetPickerCtrlProportion(wxPickerBase* self, int proportion)
    {
        self->SetPickerCtrlProportion(proportion);
    }

    EXPORT int wxPickerBase_GetPickerCtrlProportion(wxPickerBase* self)
    {
        return self->GetPickerCtrlProportion();
    }

    EXPORT bool wxPickerBase_IsTextCtrlGrowable(wxPickerBase* self)
    {
        return self->IsTextCtrlGrowable();
    }

    EXPORT void wxPickerBase_SetTextCtrlGrowable(wxPickerBase* self, bool grow)
    {
        self->SetTextCtrlGrowable(grow);
    }

    EXPORT bool wxPickerBase_IsPickerCtrlGrowable(wxPickerBase* self)
    {
        return self->IsPickerCtrlGrowable();
    }

    EXPORT void wxPickerBase_SetPickerCtrlGrowable(wxPickerBase* self, bool grow)
    {
        self->SetPickerCtrlGrowable(grow);
    }

    EXPORT bool wxPickerBase_HasTextCtrl(wxPickerBase* self)
    {
        return self->HasTextCtrl();
    }

    EXPORT wxTextCtrl* wxPickerBase_GetTextCtrl(wxPickerBase* self)
    {
        return self->GetTextCtrl();
    }

    EXPORT wxControl* wxPickerBase_GetPickerCtrl(wxPickerBase* self)
    {
        return self->GetPickerCtrl();
    }

    // ---------------------------------------------------------------------------
    // wxEditableListBox
    // ---------------------------------------------------------------------------

#if wxUSE_EDITABLELISTBOX
    EXPORT wxEditableListBox* wxEditableListBox_Create(wxWindow* parent, int id, wxString* label,
                                                       int x, int y, int width, int height,
                                                       int style)
    {
        return new wxEditableListBox(parent, id, *label, wxPoint(x, y), wxSize(width, height),
                                     style);
    }

    EXPORT void wxEditableListBox_Delete(wxEditableListBox* self)
    {
        delete self;
    }

    EXPORT void wxEditableListBox_SetStrings(wxEditableListBox* self, wxArrayString* strings)
    {
        self->SetStrings(*strings);
    }

    EXPORT void wxEditableListBox_GetStrings(wxEditableListBox* self, wxArrayString* strings)
    {
        self->GetStrings(*strings);
    }

    EXPORT wxListCtrl* wxEditableListBox_GetListCtrl(wxEditableListBox* self)
    {
        return self->GetListCtrl();
    }

    EXPORT wxBitmapButton* wxEditableListBox_GetDelButton(wxEditableListBox* self)
    {
        return self->GetDelButton();
    }

    EXPORT wxBitmapButton* wxEditableListBox_GetNewButton(wxEditableListBox* self)
    {
        return self->GetNewButton();
    }

    EXPORT wxBitmapButton* wxEditableListBox_GetUpButton(wxEditableListBox* self)
    {
        return self->GetUpButton();
    }

    EXPORT wxBitmapButton* wxEditableListBox_GetDownButton(wxEditableListBox* self)
    {
        return self->GetDownButton();
    }

    EXPORT wxBitmapButton* wxEditableListBox_GetEditButton(wxEditableListBox* self)
    {
        return self->GetEditButton();
    }
#endif  // wxUSE_EDITABLELISTBOX

    // ---------------------------------------------------------------------------
    // wxRearrangeList
    // ---------------------------------------------------------------------------

#if wxUSE_REARRANGECTRL
    EXPORT wxRearrangeList* wxRearrangeList_Create(wxWindow* parent, int id, int x, int y,
                                                   int width, int height, wxArrayInt* order,
                                                   wxArrayString* items, int style)
    {
        return new wxRearrangeList(parent, id, wxPoint(x, y), wxSize(width, height), *order, *items,
                                   style);
    }

    EXPORT void wxRearrangeList_Delete(wxRearrangeList* self)
    {
        delete self;
    }

    EXPORT wxArrayInt* wxRearrangeList_GetCurrentOrder(wxRearrangeList* self)
    {
        return new wxArrayInt(self->GetCurrentOrder());
    }

    EXPORT bool wxRearrangeList_CanMoveCurrentUp(wxRearrangeList* self)
    {
        return self->CanMoveCurrentUp();
    }

    EXPORT bool wxRearrangeList_CanMoveCurrentDown(wxRearrangeList* self)
    {
        return self->CanMoveCurrentDown();
    }

    EXPORT bool wxRearrangeList_MoveCurrentUp(wxRearrangeList* self)
    {
        return self->MoveCurrentUp();
    }

    EXPORT bool wxRearrangeList_MoveCurrentDown(wxRearrangeList* self)
    {
        return self->MoveCurrentDown();
    }

    EXPORT void wxRearrangeList_Check(wxRearrangeList* self, unsigned int item, bool check)
    {
        self->Check(item, check);
    }
#endif  // wxUSE_REARRANGECTRL

    // ---------------------------------------------------------------------------
    // wxTipProvider
    // ---------------------------------------------------------------------------

#if wxUSE_STARTUP_TIPS
    EXPORT wxTipProvider* wxTipProvider_CreateFile(wxString* filename, int current_tip)
    {
        return wxCreateFileTipProvider(*filename, (size_t) current_tip);
    }

    EXPORT void wxTipProvider_Delete(wxTipProvider* self)
    {
        delete self;
    }

    EXPORT wxString* wxTipProvider_GetTip(wxTipProvider* self)
    {
        return new wxString(self->GetTip());
    }

    EXPORT int wxTipProvider_GetCurrentTip(wxTipProvider* self)
    {
        return (int) self->GetCurrentTip();
    }
#endif  // wxUSE_STARTUP_TIPS

    // ---------------------------------------------------------------------------
    // wxGBSizerItem
    // ---------------------------------------------------------------------------

    EXPORT wxGBSizerItem* wxGBSizerItem_Create()
    {
        return new wxGBSizerItem();
    }

    EXPORT wxGBSizerItem* wxGBSizerItem_CreateSpacer(int width, int height, int row, int col,
                                                     int rowspan, int colspan, int flag, int border,
                                                     wxObject* user_data)
    {
        return new wxGBSizerItem(width, height, wxGBPosition(row, col), wxGBSpan(rowspan, colspan),
                                 flag, border, user_data);
    }

    EXPORT void wxGBSizerItem_Delete(wxGBSizerItem* self)
    {
        delete self;
    }

    EXPORT void wxGBSizerItem_GetPos(wxGBSizerItem* self, int* row, int* col)
    {
        self->GetPos(*row, *col);
    }

    EXPORT void wxGBSizerItem_SetPos(wxGBSizerItem* self, int row, int col)
    {
        self->SetPos(wxGBPosition(row, col));
    }

    EXPORT void wxGBSizerItem_GetSpan(wxGBSizerItem* self, int* rowspan, int* colspan)
    {
        self->GetSpan(*rowspan, *colspan);
    }

    EXPORT bool wxGBSizerItem_SetSpan(wxGBSizerItem* self, int rowspan, int colspan)
    {
        return self->SetSpan(wxGBSpan(rowspan, colspan));
    }

    EXPORT bool wxGBSizerItem_Intersects(wxGBSizerItem* self, wxGBSizerItem* other)
    {
        return self->Intersects(*other);
    }

    EXPORT bool wxGBSizerItem_IntersectsPos(wxGBSizerItem* self, int row, int col, int rowspan,
                                            int colspan)
    {
        return self->Intersects(wxGBPosition(row, col), wxGBSpan(rowspan, colspan));
    }

    EXPORT void wxGBSizerItem_GetEndPos(wxGBSizerItem* self, int* row, int* col)
    {
        self->GetEndPos(*row, *col);
    }

    EXPORT wxGridBagSizer* wxGBSizerItem_GetGBSizer(wxGBSizerItem* self)
    {
        return self->GetGBSizer();
    }

    EXPORT void wxGBSizerItem_SetGBSizer(wxGBSizerItem* self, wxGridBagSizer* sizer)
    {
        self->SetGBSizer(sizer);
    }

    // ---------------------------------------------------------------------------
    // wxDCOverlay
    // ---------------------------------------------------------------------------

    EXPORT wxDCOverlay* wxDCOverlay_Create(wxOverlay* overlay, wxDC* dc, int x, int y, int width,
                                           int height)
    {
        return new wxDCOverlay(*overlay, dc, x, y, width, height);
    }

    EXPORT wxDCOverlay* wxDCOverlay_CreateFull(wxOverlay* overlay, wxDC* dc)
    {
        return new wxDCOverlay(*overlay, dc);
    }

    EXPORT void wxDCOverlay_Delete(wxDCOverlay* self)
    {
        delete self;
    }

    EXPORT void wxDCOverlay_Clear(wxDCOverlay* self)
    {
        self->Clear();
    }

    // ---------------------------------------------------------------------------
    // wxAffineMatrix2D
    // ---------------------------------------------------------------------------

    EXPORT wxAffineMatrix2D* wxAffineMatrix2D_Create()
    {
        return new wxAffineMatrix2D();
    }

    EXPORT void wxAffineMatrix2D_Delete(wxAffineMatrix2D* self)
    {
        delete self;
    }

    EXPORT void wxAffineMatrix2D_Set(wxAffineMatrix2D* self, double m11, double m12, double m21,
                                     double m22, double tr_x, double tr_y)
    {
        const wxMatrix2D matrix(m11, m12, m21, m22);
        self->Set(matrix, wxPoint2DDouble(tr_x, tr_y));
    }

    EXPORT void wxAffineMatrix2D_Get(wxAffineMatrix2D* self, double* m11, double* m12, double* m21,
                                     double* m22, double* tr_x, double* tr_y)
    {
        wxMatrix2D matrix;
        wxPoint2DDouble translation;
        self->Get(&matrix, &translation);
        *m11 = matrix.m_11;
        *m12 = matrix.m_12;
        *m21 = matrix.m_21;
        *m22 = matrix.m_22;
        *tr_x = translation.m_x;
        *tr_y = translation.m_y;
    }

    EXPORT void wxAffineMatrix2D_Concat(wxAffineMatrix2D* self, wxAffineMatrix2D* other)
    {
        self->Concat(*other);
    }

    EXPORT bool wxAffineMatrix2D_Invert(wxAffineMatrix2D* self)
    {
        return self->Invert();
    }

    EXPORT bool wxAffineMatrix2D_IsIdentity(wxAffineMatrix2D* self)
    {
        return self->IsIdentity();
    }

    EXPORT bool wxAffineMatrix2D_IsEqual(wxAffineMatrix2D* self, wxAffineMatrix2D* other)
    {
        return self->IsEqual(*other);
    }

    EXPORT void wxAffineMatrix2D_Translate(wxAffineMatrix2D* self, double dx, double dy)
    {
        self->Translate(dx, dy);
    }

    EXPORT void wxAffineMatrix2D_Scale(wxAffineMatrix2D* self, double x_scale, double y_scale)
    {
        self->Scale(x_scale, y_scale);
    }

    EXPORT void wxAffineMatrix2D_Rotate(wxAffineMatrix2D* self, double radians)
    {
        self->Rotate(radians);
    }

    EXPORT void wxAffineMatrix2D_Mirror(wxAffineMatrix2D* self, int direction)
    {
        self->Mirror(direction);
    }

    EXPORT void wxAffineMatrix2D_TransformPoint(wxAffineMatrix2D* self, double* x, double* y)
    {
        self->TransformPoint(x, y);
    }

    EXPORT void wxAffineMatrix2D_TransformDistance(wxAffineMatrix2D* self, double* x, double* y)
    {
        self->TransformDistance(x, y);
    }

    // ---------------------------------------------------------------------------
    // wxArtProvider
    // ---------------------------------------------------------------------------

    EXPORT wxBitmap* wxArtProvider_GetBitmap(wxString* id, wxString* client, int width, int height)
    {
        return new wxBitmap(wxArtProvider::GetBitmap(*id, *client, wxSize(width, height)));
    }

    EXPORT wxBitmapBundle* wxArtProvider_GetBitmapBundle(wxString* id, wxString* client, int width,
                                                         int height)
    {
        return new wxBitmapBundle(
            wxArtProvider::GetBitmapBundle(*id, *client, wxSize(width, height)));
    }

    EXPORT wxIcon* wxArtProvider_GetIcon(wxString* id, wxString* client, int width, int height)
    {
        return new wxIcon(wxArtProvider::GetIcon(*id, *client, wxSize(width, height)));
    }

    EXPORT wxIconBundle* wxArtProvider_GetIconBundle(wxString* id, wxString* client)
    {
        return new wxIconBundle(wxArtProvider::GetIconBundle(*id, *client));
    }

    EXPORT wxSize* wxArtProvider_GetNativeSizeHint(wxString* client, wxWindow* window)
    {
        return new wxSize(wxArtProvider::GetNativeSizeHint(*client, window));
    }

    EXPORT wxSize* wxArtProvider_GetSizeHint(wxString* client, wxWindow* window)
    {
        return new wxSize(wxArtProvider::GetSizeHint(*client, window));
    }

    EXPORT bool wxArtProvider_HasNativeProvider()
    {
        return wxArtProvider::HasNativeProvider();
    }

    EXPORT void wxArtProvider_PushBack(wxArtProvider* provider)
    {
        wxArtProvider::PushBack(provider);
    }

    EXPORT bool wxArtProvider_DeleteProvider(wxArtProvider* provider)
    {
        return wxArtProvider::Delete(provider);
    }

    // ---------------------------------------------------------------------------
    // wxSystemOptions
    // ---------------------------------------------------------------------------

    EXPORT void wxSystemOptions_SetOption(wxString* name, wxString* value)
    {
        wxSystemOptions::SetOption(*name, *value);
    }

    EXPORT void wxSystemOptions_SetOptionInt(wxString* name, int value)
    {
        wxSystemOptions::SetOption(*name, value);
    }

    EXPORT wxString* wxSystemOptions_GetOption(wxString* name)
    {
        return new wxString(wxSystemOptions::GetOption(*name));
    }

    EXPORT int wxSystemOptions_GetOptionInt(wxString* name)
    {
        return wxSystemOptions::GetOptionInt(*name);
    }

    EXPORT bool wxSystemOptions_HasOption(wxString* name)
    {
        return wxSystemOptions::HasOption(*name);
    }

    EXPORT bool wxSystemOptions_IsFalse(wxString* name)
    {
        return wxSystemOptions::IsFalse(*name);
    }

    // ---------------------------------------------------------------------------
    // wxSingleChoiceDialog
    // ---------------------------------------------------------------------------

    EXPORT wxSingleChoiceDialog* wxSingleChoiceDialog_Create(wxWindow* parent, wxString* message,
                                                             wxString* caption,
                                                             wxArrayString* choices, int style)
    {
        return new wxSingleChoiceDialog(parent, *message, *caption, *choices, nullptr, style);
    }

    EXPORT void wxSingleChoiceDialog_Delete(wxSingleChoiceDialog* self)
    {
        delete self;
    }

    EXPORT void wxSingleChoiceDialog_SetSelection(wxSingleChoiceDialog* self, int selection)
    {
        self->SetSelection(selection);
    }

    EXPORT int wxSingleChoiceDialog_GetSelection(wxSingleChoiceDialog* self)
    {
        return self->GetSelection();
    }

    EXPORT wxString* wxSingleChoiceDialog_GetStringSelection(wxSingleChoiceDialog* self)
    {
        return new wxString(self->GetStringSelection());
    }

    EXPORT void* wxSingleChoiceDialog_GetSelectionData(wxSingleChoiceDialog* self)
    {
        return self->GetSelectionData();
    }

    // ---------------------------------------------------------------------------
    // wxHelpController
    // ---------------------------------------------------------------------------

#if wxUSE_HELP
    EXPORT bool wxHelpController_Initialize(wxHelpController* self, wxString* file)
    {
        return self->Initialize(*file);
    }

    EXPORT bool wxHelpController_LoadFile(wxHelpController* self, wxString* file)
    {
        return self->LoadFile(*file);
    }

    EXPORT bool wxHelpController_DisplayContents(wxHelpController* self)
    {
        return self->DisplayContents();
    }

    EXPORT bool wxHelpController_DisplaySection(wxHelpController* self, int section)
    {
        return self->DisplaySection(section);
    }

    EXPORT bool wxHelpController_DisplaySectionName(wxHelpController* self, wxString* section)
    {
        return self->DisplaySection(*section);
    }

    EXPORT bool wxHelpController_DisplayBlock(wxHelpController* self, int block)
    {
        return self->DisplayBlock(block);
    }

    EXPORT bool wxHelpController_KeywordSearch(wxHelpController* self, wxString* keyword, int mode)
    {
        return self->KeywordSearch(*keyword, (wxHelpSearchMode) mode);
    }

    EXPORT bool wxHelpController_Quit(wxHelpController* self)
    {
        return self->Quit();
    }

    EXPORT wxWindow* wxHelpController_GetParentWindow(wxHelpController* self)
    {
        return self->GetParentWindow();
    }

    EXPORT void wxHelpController_SetParentWindow(wxHelpController* self, wxWindow* window)
    {
        self->SetParentWindow(window);
    }
#endif  // wxUSE_HELP

    // ---------------------------------------------------------------------------
    // wxWizardPage
    // ---------------------------------------------------------------------------

    EXPORT wxWizardPage* wxWizardPage_GetPrev(wxWizardPage* self)
    {
        return self->GetPrev();
    }

    EXPORT wxWizardPage* wxWizardPage_GetNext(wxWizardPage* self)
    {
        return self->GetNext();
    }

    EXPORT wxBitmap* wxWizardPage_GetBitmap(wxWizardPage* self)
    {
        return new wxBitmap(self->GetBitmap());
    }

    // ---------------------------------------------------------------------------
    // wxMDIClientWindow
    // ---------------------------------------------------------------------------

#if wxUSE_MDI
    EXPORT wxMDIClientWindow* wxMDIClientWindow_Create()
    {
        return new wxMDIClientWindow();
    }

    EXPORT void wxMDIClientWindow_Delete(wxMDIClientWindow* self)
    {
        delete self;
    }

    EXPORT bool wxMDIClientWindow_CreateClient(wxMDIClientWindow* self, wxMDIParentFrame* parent,
                                               int style)
    {
        return self->CreateClient(parent, style);
    }
#endif  // wxUSE_MDI

    // ---------------------------------------------------------------------------
    // wxGridTableBase
    // ---------------------------------------------------------------------------

#if wxUSE_GRID
    EXPORT int wxGridTableBase_GetNumberRows(wxGridTableBase* self)
    {
        return self->GetNumberRows();
    }

    EXPORT int wxGridTableBase_GetNumberCols(wxGridTableBase* self)
    {
        return self->GetNumberCols();
    }

    EXPORT int wxGridTableBase_GetRowsCount(wxGridTableBase* self)
    {
        return self->GetRowsCount();
    }

    EXPORT int wxGridTableBase_GetColsCount(wxGridTableBase* self)
    {
        return self->GetColsCount();
    }

    EXPORT bool wxGridTableBase_IsEmptyCell(wxGridTableBase* self, int row, int col)
    {
        return self->IsEmptyCell(row, col);
    }

    EXPORT wxString* wxGridTableBase_GetValue(wxGridTableBase* self, int row, int col)
    {
        return new wxString(self->GetValue(row, col));
    }

    EXPORT void wxGridTableBase_SetValue(wxGridTableBase* self, int row, int col, wxString* value)
    {
        self->SetValue(row, col, *value);
    }

    EXPORT wxString* wxGridTableBase_GetTypeName(wxGridTableBase* self, int row, int col)
    {
        return new wxString(self->GetTypeName(row, col));
    }

    EXPORT bool wxGridTableBase_CanGetValueAs(wxGridTableBase* self, int row, int col,
                                              wxString* type_name)
    {
        return self->CanGetValueAs(row, col, *type_name);
    }

    EXPORT bool wxGridTableBase_CanSetValueAs(wxGridTableBase* self, int row, int col,
                                              wxString* type_name)
    {
        return self->CanSetValueAs(row, col, *type_name);
    }

    EXPORT long wxGridTableBase_GetValueAsLong(wxGridTableBase* self, int row, int col)
    {
        return self->GetValueAsLong(row, col);
    }

    EXPORT double wxGridTableBase_GetValueAsDouble(wxGridTableBase* self, int row, int col)
    {
        return self->GetValueAsDouble(row, col);
    }

    EXPORT bool wxGridTableBase_GetValueAsBool(wxGridTableBase* self, int row, int col)
    {
        return self->GetValueAsBool(row, col);
    }

    EXPORT void wxGridTableBase_SetValueAsLong(wxGridTableBase* self, int row, int col, long value)
    {
        self->SetValueAsLong(row, col, value);
    }

    EXPORT void wxGridTableBase_SetValueAsDouble(wxGridTableBase* self, int row, int col,
                                                 double value)
    {
        self->SetValueAsDouble(row, col, value);
    }

    EXPORT void wxGridTableBase_SetValueAsBool(wxGridTableBase* self, int row, int col, bool value)
    {
        self->SetValueAsBool(row, col, value);
    }

    EXPORT wxGrid* wxGridTableBase_GetView(wxGridTableBase* self)
    {
        return self->GetView();
    }

    EXPORT void wxGridTableBase_SetView(wxGridTableBase* self, wxGrid* grid)
    {
        self->SetView(grid);
    }

    EXPORT void wxGridTableBase_Clear(wxGridTableBase* self)
    {
        self->Clear();
    }

    EXPORT bool wxGridTableBase_InsertRows(wxGridTableBase* self, int pos, int num_rows)
    {
        return self->InsertRows((size_t) pos, (size_t) num_rows);
    }

    EXPORT bool wxGridTableBase_AppendRows(wxGridTableBase* self, int num_rows)
    {
        return self->AppendRows((size_t) num_rows);
    }

    EXPORT bool wxGridTableBase_DeleteRows(wxGridTableBase* self, int pos, int num_rows)
    {
        return self->DeleteRows((size_t) pos, (size_t) num_rows);
    }

    EXPORT bool wxGridTableBase_InsertCols(wxGridTableBase* self, int pos, int num_cols)
    {
        return self->InsertCols((size_t) pos, (size_t) num_cols);
    }

    EXPORT bool wxGridTableBase_AppendCols(wxGridTableBase* self, int num_cols)
    {
        return self->AppendCols((size_t) num_cols);
    }

    EXPORT bool wxGridTableBase_DeleteCols(wxGridTableBase* self, int pos, int num_cols)
    {
        return self->DeleteCols((size_t) pos, (size_t) num_cols);
    }

    EXPORT wxString* wxGridTableBase_GetRowLabelValue(wxGridTableBase* self, int row)
    {
        return new wxString(self->GetRowLabelValue(row));
    }

    EXPORT wxString* wxGridTableBase_GetColLabelValue(wxGridTableBase* self, int col)
    {
        return new wxString(self->GetColLabelValue(col));
    }

    EXPORT void wxGridTableBase_SetRowLabelValue(wxGridTableBase* self, int row, wxString* label)
    {
        self->SetRowLabelValue(row, *label);
    }

    EXPORT void wxGridTableBase_SetColLabelValue(wxGridTableBase* self, int col, wxString* label)
    {
        self->SetColLabelValue(col, *label);
    }

    EXPORT wxString* wxGridTableBase_GetCornerLabelValue(wxGridTableBase* self)
    {
        return new wxString(self->GetCornerLabelValue());
    }

    EXPORT void wxGridTableBase_SetCornerLabelValue(wxGridTableBase* self, wxString* label)
    {
        self->SetCornerLabelValue(*label);
    }

    EXPORT bool wxGridTableBase_CanHaveAttributes(wxGridTableBase* self)
    {
        return self->CanHaveAttributes();
    }

    // ---------------------------------------------------------------------------
    // Grid cell renderers
    // ---------------------------------------------------------------------------

    EXPORT void wxGridCellRenderer_Draw(wxGridCellRenderer* self, wxGrid* grid,
                                        wxGridCellAttr* attr, wxDC* dc, int x, int y, int width,
                                        int height, int row, int col, bool is_selected)
    {
        self->Draw(*grid, *attr, *dc, wxRect(x, y, width, height), row, col, is_selected);
    }

    EXPORT wxSize* wxGridCellRenderer_GetPreferredSize(wxGridCellRenderer* self, wxGrid* grid,
                                                       wxGridCellAttr* attr, wxDC* dc, int row,
                                                       int col)
    {
        return new wxSize(self->GetPreferredSize(*grid, *attr, *dc, row, col));
    }

    EXPORT int wxGridCellRenderer_GetPreferredHeight(wxGridCellRenderer* self, wxGrid* grid,
                                                     wxGridCellAttr* attr, wxDC* dc, int row,
                                                     int col, int width)
    {
        return self->GetPreferredHeight(*grid, *attr, *dc, row, col, width);
    }

    EXPORT int wxGridCellRenderer_GetPreferredWidth(wxGridCellRenderer* self, wxGrid* grid,
                                                    wxGridCellAttr* attr, wxDC* dc, int row,
                                                    int col, int height)
    {
        return self->GetPreferredWidth(*grid, *attr, *dc, row, col, height);
    }

    EXPORT void wxGridCellBoolRenderer_Draw(wxGridCellBoolRenderer* self, wxGrid* grid,
                                            wxGridCellAttr* attr, wxDC* dc, int x, int y, int width,
                                            int height, int row, int col, bool is_selected)
    {
        self->Draw(*grid, *attr, *dc, wxRect(x, y, width, height), row, col, is_selected);
    }

    EXPORT wxSize* wxGridCellBoolRenderer_GetPreferredSize(wxGridCellBoolRenderer* self,
                                                           wxGrid* grid, wxGridCellAttr* attr,
                                                           wxDC* dc, int row, int col)
    {
        return new wxSize(self->GetPreferredSize(*grid, *attr, *dc, row, col));
    }

    EXPORT wxSize* wxGridCellBoolRenderer_GetMaxBestSize(wxGridCellBoolRenderer* self, wxGrid* grid,
                                                         wxGridCellAttr* attr, wxDC* dc)
    {
        return new wxSize(self->GetMaxBestSize(*grid, *attr, *dc));
    }

    EXPORT void wxGridCellStringRenderer_Draw(wxGridCellStringRenderer* self, wxGrid* grid,
                                              wxGridCellAttr* attr, wxDC* dc, int x, int y,
                                              int width, int height, int row, int col,
                                              bool is_selected)
    {
        self->Draw(*grid, *attr, *dc, wxRect(x, y, width, height), row, col, is_selected);
    }

    EXPORT wxSize* wxGridCellStringRenderer_GetPreferredSize(wxGridCellStringRenderer* self,
                                                             wxGrid* grid, wxGridCellAttr* attr,
                                                             wxDC* dc, int row, int col)
    {
        return new wxSize(self->GetPreferredSize(*grid, *attr, *dc, row, col));
    }

    EXPORT wxGridCellFloatRenderer* wxGridCellFloatRenderer_Create(int width, int precision,
                                                                   int format)
    {
        return new wxGridCellFloatRenderer(width, precision, format);
    }

    EXPORT void wxGridCellFloatRenderer_Delete(wxGridCellFloatRenderer* self)
    {
        delete self;
    }

    EXPORT int wxGridCellFloatRenderer_GetWidth(wxGridCellFloatRenderer* self)
    {
        return self->GetWidth();
    }

    EXPORT void wxGridCellFloatRenderer_SetWidth(wxGridCellFloatRenderer* self, int width)
    {
        self->SetWidth(width);
    }

    EXPORT int wxGridCellFloatRenderer_GetPrecision(wxGridCellFloatRenderer* self)
    {
        return self->GetPrecision();
    }

    EXPORT void wxGridCellFloatRenderer_SetPrecision(wxGridCellFloatRenderer* self, int precision)
    {
        self->SetPrecision(precision);
    }

    EXPORT int wxGridCellFloatRenderer_GetFormat(wxGridCellFloatRenderer* self)
    {
        return self->GetFormat();
    }

    EXPORT void wxGridCellFloatRenderer_SetFormat(wxGridCellFloatRenderer* self, int format)
    {
        self->SetFormat(format);
    }

    EXPORT void wxGridCellFloatRenderer_SetParameters(wxGridCellFloatRenderer* self,
                                                      wxString* params)
    {
        self->SetParameters(*params);
    }
#endif  // wxUSE_GRID

    // ---------------------------------------------------------------------------
    // wxVariant
    // ---------------------------------------------------------------------------

#if wxUSE_VARIANT
    EXPORT wxVariant* wxVariant_Create()
    {
        return new wxVariant();
    }

    EXPORT void wxVariant_Delete(wxVariant* self)
    {
        delete self;
    }

    EXPORT wxString* wxVariant_GetType(wxVariant* self)
    {
        return new wxString(self->GetType());
    }

    EXPORT wxString* wxVariant_MakeString(wxVariant* self)
    {
        return new wxString(self->MakeString());
    }

    EXPORT wxString* wxVariant_GetString(wxVariant* self)
    {
        return new wxString(self->GetString());
    }

    EXPORT bool wxVariant_GetBool(wxVariant* self)
    {
        return self->GetBool();
    }

    EXPORT long wxVariant_GetLong(wxVariant* self)
    {
        return self->GetLong();
    }

    EXPORT double wxVariant_GetDouble(wxVariant* self)
    {
        return self->GetDouble();
    }
#endif  // wxUSE_VARIANT

    // ---------------------------------------------------------------------------
    // wxDataObject
    // ---------------------------------------------------------------------------

#if wxUSE_DRAG_AND_DROP
    EXPORT wxDataFormat* wxDataObject_GetPreferredFormat(wxDataObject* self, int direction)
    {
        return new wxDataFormat(self->GetPreferredFormat((wxDataObjectBase::Direction) direction));
    }

    EXPORT int wxDataObject_GetFormatCount(wxDataObject* self, int direction)
    {
        return (int) self->GetFormatCount((wxDataObjectBase::Direction) direction);
    }

    EXPORT bool wxDataObject_IsSupported(wxDataObject* self, wxDataFormat* format, int direction)
    {
        return self->IsSupported(*format, (wxDataObjectBase::Direction) direction);
    }

    EXPORT size_t wxDataObject_GetDataSize(wxDataObject* self, wxDataFormat* format)
    {
        return self->GetDataSize(*format);
    }

    EXPORT bool wxDataObject_GetDataHere(wxDataObject* self, wxDataFormat* format, void* buffer)
    {
        return self->GetDataHere(*format, buffer);
    }

    EXPORT bool wxDataObject_SetData(wxDataObject* self, wxDataFormat* format, int length,
                                     void* buffer)
    {
        return self->SetData(*format, (size_t) length, buffer);
    }
#endif  // wxUSE_DRAG_AND_DROP

    // ---------------------------------------------------------------------------
    // wxPGProperty
    // ---------------------------------------------------------------------------

#if wxUSE_PROPGRID
    EXPORT wxString* wxPGProperty_GetBaseName(wxPGProperty* self)
    {
        return new wxString(self->GetBaseName());
    }

    EXPORT int wxPGProperty_GetY(wxPGProperty* self)
    {
        return self->GetY();
    }

    EXPORT wxVariant* wxPGProperty_GetValue(wxPGProperty* self)
    {
        return new wxVariant(self->GetValue());
    }

    EXPORT wxString* wxPGProperty_GetHintText(wxPGProperty* self)
    {
        return new wxString(self->GetHintText());
    }

    EXPORT wxPropertyGrid* wxPGProperty_GetGrid(wxPGProperty* self)
    {
        return self->GetGrid();
    }

    EXPORT wxPropertyGrid* wxPGProperty_GetGridIfDisplayed(wxPGProperty* self)
    {
        return self->GetGridIfDisplayed();
    }

    EXPORT wxPGProperty* wxPGProperty_GetMainParent(wxPGProperty* self)
    {
        return self->GetMainParent();
    }

    EXPORT wxPGProperty* wxPGProperty_GetParent(wxPGProperty* self)
    {
        return self->GetParent();
    }

    EXPORT wxPGProperty* wxPGProperty_Item(wxPGProperty* self, unsigned int index)
    {
        return self->Item(index);
    }

    EXPORT int wxPGProperty_GetChildCount(wxPGProperty* self)
    {
        return (int) self->GetChildCount();
    }

    EXPORT int wxPGProperty_GetChoiceSelection(wxPGProperty* self)
    {
        return self->GetChoiceSelection();
    }

    EXPORT void wxPGProperty_SetChoiceSelection(wxPGProperty* self, int selection)
    {
        self->SetChoiceSelection(selection);
    }

    EXPORT void wxPGProperty_Enable(wxPGProperty* self, bool enable)
    {
        self->Enable(enable);
    }

    EXPORT bool wxPGProperty_AreChildrenComponents(wxPGProperty* self)
    {
        return self->AreChildrenComponents();
    }

    EXPORT int wxPGProperty_GetDisplayedCommonValueCount(wxPGProperty* self)
    {
        return self->GetDisplayedCommonValueCount();
    }

    EXPORT void wxPGProperty_SetLabel(wxPGProperty* self, wxString* label)
    {
        self->SetLabel(*label);
    }

    EXPORT void wxPGProperty_SetName(wxPGProperty* self, wxString* name)
    {
        self->SetName(*name);
    }

    // ---------------------------------------------------------------------------
    // wxPropertyGrid
    // ---------------------------------------------------------------------------

    EXPORT wxVariant* wxPropertyGrid_GetPropertyValue(wxPropertyGrid* self, wxPGProperty* id)
    {
        return new wxVariant(self->GetPropertyValue(id));
    }

    EXPORT void wxPropertyGrid_SetPropertyValue(wxPropertyGrid* self, wxPGProperty* id,
                                                wxVariant* value)
    {
        self->SetPropertyValue(id, *value);
    }

    EXPORT void wxPropertyGrid_SetPropertyValueUnspecified(wxPropertyGrid* self, wxPGProperty* id)
    {
        self->SetPropertyValueUnspecified(id);
    }

    EXPORT wxString* wxPropertyGrid_GetPropertyHelpString(wxPropertyGrid* self, wxPGProperty* id)
    {
        return new wxString(self->GetPropertyHelpString(id));
    }

    EXPORT void wxPropertyGrid_SetPropertyHelpString(wxPropertyGrid* self, wxPGProperty* id,
                                                     wxString* help)
    {
        self->SetPropertyHelpString(id, *help);
    }

    EXPORT bool wxPropertyGrid_IsPropertyModified(wxPropertyGrid* self, wxPGProperty* id)
    {
        return self->IsPropertyModified(id);
    }

    EXPORT wxVariant* wxPropertyGrid_GetUncommittedPropertyValue(wxPropertyGrid* self)
    {
        return new wxVariant(self->GetUncommittedPropertyValue());
    }
#endif  // wxUSE_PROPGRID

    // ---------------------------------------------------------------------------
    // wxPrintAbortDialog
    // ---------------------------------------------------------------------------

#if wxUSE_PRINTING_ARCHITECTURE
    EXPORT wxPrintAbortDialog* wxPrintAbortDialog_Create(wxWindow* parent, wxString* document_title,
                                                         int x, int y, int width, int height,
                                                         int style)
    {
        return new wxPrintAbortDialog(parent, *document_title, wxPoint(x, y), wxSize(width, height),
                                      style);
    }

    EXPORT void wxPrintAbortDialog_Delete(wxPrintAbortDialog* self)
    {
        delete self;
    }

    EXPORT void wxPrintAbortDialog_SetProgress(wxPrintAbortDialog* self, int current_page,
                                               int total_pages, int current_copy, int total_copies)
    {
        self->SetProgress(current_page, total_pages, current_copy, total_copies);
    }
#endif  // wxUSE_PRINTING_ARCHITECTURE
}
