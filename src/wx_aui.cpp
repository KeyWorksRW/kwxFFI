#include "wrapper.h"
#include <wx/tooltip.h>

extern "C"
{
    /* wxAuiDefaultTabArt */

    EXPORT void* wxAuiDefaultTabArt_Create()
    {
        return (void*) new wxAuiDefaultTabArt();
    }

    EXPORT void* wxAuiDefaultTabArt_Clone(wxAuiDefaultTabArt* self)
    {
        return (void*) self->Clone();
    }

    EXPORT void wxAuiDefaultTabArt_SetFlags(wxAuiDefaultTabArt* self, int _flags)
    {
        self->SetFlags(_flags);
    }

    EXPORT void wxAuiDefaultTabArt_SetSizingInfo(wxAuiDefaultTabArt* self, int width, int height,
                                                 size_t tabCount)
    {
        self->SetSizingInfo(wxSize(width, height), tabCount);
    }

    EXPORT void wxAuiDefaultTabArt_SetNormalFont(wxAuiDefaultTabArt* self, wxFont* font)
    {
        self->SetNormalFont(*font);
    }

    EXPORT void wxAuiDefaultTabArt_SetSelectedFont(wxAuiDefaultTabArt* self, wxFont* font)
    {
        self->SetSelectedFont(*font);
    }

    EXPORT void wxAuiDefaultTabArt_SetMeasuringFont(wxAuiDefaultTabArt* self, wxFont* font)
    {
        self->SetMeasuringFont(*font);
    }

    EXPORT void wxAuiDefaultTabArt_SetColour(wxAuiDefaultTabArt* self, wxColour* _colour)
    {
        self->SetColour(*_colour);
    }

    EXPORT void wxAuiDefaultTabArt_SetActiveColour(wxAuiDefaultTabArt* self, wxColour* _colour)
    {
        self->SetActiveColour(*_colour);
    }

    EXPORT void wxAuiDefaultTabArt_DrawBackground(wxAuiDefaultTabArt* self, wxDC* _dc,
                                                  wxWindow* _wnd, wxRect* _rect)
    {
        return self->DrawBackground(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiDefaultTabArt_DrawTab(wxAuiDefaultTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                           wxAuiNotebookPage* _pane, wxRect* _inRect,
                                           int closeButtonState, wxRect* _outTabRect,
                                           wxRect* _outButtonRect, int* xExtent)
    {
        self->DrawTab(*_dc, _wnd, *_pane, *_inRect, closeButtonState, _outTabRect, _outButtonRect,
                      xExtent);
    }

    EXPORT void wxAuiDefaultTabArt_DrawButton(wxAuiDefaultTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                              wxRect* _inRect, int bitmapId, int buttonState,
                                              int orientation, wxRect* _outRect)
    {
        self->DrawButton(*_dc, _wnd, *_inRect, bitmapId, buttonState, orientation, _outRect);
    }

    EXPORT int wxAuiDefaultTabArt_GetIndentSize(wxAuiDefaultTabArt* self)
    {
        return self->GetIndentSize();
    }

    EXPORT wxSize* wxAuiDefaultTabArt_GetTabSize(wxAuiDefaultTabArt* self, wxDC* _dc,
                                                 wxWindow* _wnd, wxString* _caption,
                                                 wxBitmap* _bitmap, bool active,
                                                 int closeButtonState, int* xExtent)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetTabSize(*_dc, _wnd, *_caption, *_bitmap, active, closeButtonState, xExtent);
        return sz;
    }

    EXPORT int wxAuiDefaultTabArt_ShowDropDown(wxAuiDefaultTabArt* self, wxWindow* _wnd,
                                               wxAuiNotebookPageArray* _items, int activeIdx)
    {
        return self->ShowDropDown(_wnd, *_items, activeIdx);
    }

    EXPORT int wxAuiDefaultTabArt_GetBestTabCtrlSize(wxAuiDefaultTabArt* self, wxWindow* wnd,
                                                     wxAuiNotebookPageArray* pages, int width,
                                                     int height)
    {
        return self->GetBestTabCtrlSize(wnd, *pages, wxSize(width, height));
    }

    /* wxAuiToolBarEvent */

    EXPORT bool wxAuiToolBarEvent_IsDropDownClicked(wxAuiToolBarEvent* self)
    {
        return self->IsDropDownClicked();
    }

    EXPORT wxPoint* wxAuiToolBarEvent_GetClickPoint(wxAuiToolBarEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetClickPoint();
        return pt;
    }

    EXPORT wxRect* wxAuiToolBarEvent_GetItemRect(wxAuiToolBarEvent* self)
    {
        wxRect* rect = new wxRect();
        *rect = self->GetItemRect();
        return rect;
    }

    EXPORT int wxAuiToolBarEvent_GetToolId(wxAuiToolBarEvent* self)
    {
        return self->GetToolId();
    }

    /* wxAuiToolBarItem */

    EXPORT void* wxAuiToolBarItem_CreateDefault()
    {
        return (void*) new wxAuiToolBarItem();
    }

    EXPORT void* wxAuiToolBarItem_Create(wxAuiToolBarItem* _c)
    {
        return (void*) new wxAuiToolBarItem(*_c);
    }

    EXPORT wxAuiToolBarItem* wxAuiToolBarItem_Copy(wxAuiToolBarItem* self, wxAuiToolBarItem* _c)
    {
        wxAuiToolBarItem* result = new wxAuiToolBarItem();
        *result = self->operator=(*_c);
        return result;
    }

    EXPORT void wxAuiToolBarItem_Assign(wxAuiToolBarItem* self, wxAuiToolBarItem* _c)
    {
        self->Assign(*_c);
    }

    EXPORT void wxAuiToolBarItem_SetWindow(wxAuiToolBarItem* self, wxWindow* _w)
    {
        self->SetWindow(_w);
    }

    EXPORT void* wxAuiToolBarItem_GetWindow(wxAuiToolBarItem* self)
    {
        return (void*) self->GetWindow();
    }

    EXPORT void wxAuiToolBarItem_SetId(wxAuiToolBarItem* self, int new_id)
    {
        self->SetId(new_id);
    }

    EXPORT int wxAuiToolBarItem_GetId(wxAuiToolBarItem* self)
    {
        return self->GetId();
    }

    EXPORT void wxAuiToolBarItem_SetKind(wxAuiToolBarItem* self, int new_kind)
    {
        self->SetKind(new_kind);
    }

    EXPORT int wxAuiToolBarItem_GetKind(wxAuiToolBarItem* self)
    {
        return self->GetKind();
    }

    EXPORT void wxAuiToolBarItem_SetState(wxAuiToolBarItem* self, int new_state)
    {
        self->SetState(new_state);
    }

    EXPORT int wxAuiToolBarItem_GetState(wxAuiToolBarItem* self)
    {
        return self->GetState();
    }

    EXPORT void wxAuiToolBarItem_SetSizerItem(wxAuiToolBarItem* self, wxSizerItem* _s)
    {
        self->SetSizerItem(_s);
    }

    EXPORT void* wxAuiToolBarItem_GetSizerItem(wxAuiToolBarItem* self)
    {
        return (void*) self->GetSizerItem();
    }

    EXPORT void wxAuiToolBarItem_SetLabel(wxAuiToolBarItem* self, wxString* _s)
    {
        self->SetLabel(*_s);
    }

    EXPORT wxString* wxAuiToolBarItem_GetLabel(wxAuiToolBarItem* self)
    {
        wxString* result = new wxString();
        *result = self->GetLabel();
        return result;
    }

    EXPORT void wxAuiToolBarItem_SetBitmap(wxAuiToolBarItem* self, wxBitmap* _bmp)
    {
        self->SetBitmap(*_bmp);
    }

    EXPORT void wxAuiToolBarItem_GetBitmap(wxAuiToolBarItem* self, wxBitmap* _bmp)
    {
        *_bmp = self->GetBitmap();
    }

    EXPORT void wxAuiToolBarItem_SetDisabledBitmap(wxAuiToolBarItem* self, wxBitmap* _bmp)
    {
        self->SetDisabledBitmap(*_bmp);
    }

    EXPORT void wxAuiToolBarItem_GetDisabledBitmap(wxAuiToolBarItem* self, wxBitmap* _bmp)
    {
        *_bmp = self->GetDisabledBitmap();
    }

    EXPORT void wxAuiToolBarItem_SetHoverBitmap(wxAuiToolBarItem* self, wxBitmap* _bmp)
    {
        self->SetHoverBitmap(*_bmp);
    }

    EXPORT void wxAuiToolBarItem_GetHoverBitmap(wxAuiToolBarItem* self, wxBitmap* _bmp)
    {
        *_bmp = self->GetHoverBitmap();
    }

    EXPORT void wxAuiToolBarItem_SetShortHelp(wxAuiToolBarItem* self, wxString* _s)
    {
        self->SetShortHelp(*_s);
    }

    EXPORT wxString* wxAuiToolBarItem_GetShortHelp(wxAuiToolBarItem* self)
    {
        wxString* result = new wxString();
        *result = self->GetShortHelp();
        return result;
    }

    EXPORT void wxAuiToolBarItem_SetLongHelp(wxAuiToolBarItem* self, wxString* _s)
    {
        self->SetLongHelp(*_s);
    }

    EXPORT wxString* wxAuiToolBarItem_GetLongHelp(wxAuiToolBarItem* self)
    {
        wxString* result = new wxString();
        *result = self->GetLongHelp();
        return result;
    }

    EXPORT void wxAuiToolBarItem_SetMinSize(wxAuiToolBarItem* self, int width, int height)
    {
        self->SetMinSize(wxSize(width, height));
    }

    EXPORT wxSize* wxAuiToolBarItem_GetMinSize(wxAuiToolBarItem* self)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetMinSize();
        return sz;
    }

    EXPORT void wxAuiToolBarItem_SetSpacerPixels(wxAuiToolBarItem* self, int s)
    {
        self->SetSpacerPixels(s);
    }

    EXPORT int wxAuiToolBarItem_GetSpacerPixels(wxAuiToolBarItem* self)
    {
        return self->GetSpacerPixels();
    }

    EXPORT void wxAuiToolBarItem_SetProportion(wxAuiToolBarItem* self, int p)
    {
        self->SetProportion(p);
    }

    EXPORT int wxAuiToolBarItem_GetProportion(wxAuiToolBarItem* self)
    {
        return self->GetProportion();
    }

    EXPORT void wxAuiToolBarItem_SetActive(wxAuiToolBarItem* self, bool b)
    {
        self->SetActive(b);
    }

    EXPORT bool wxAuiToolBarItem_IsActive(wxAuiToolBarItem* self)
    {
        return self->IsActive();
    }

    EXPORT void wxAuiToolBarItem_SetHasDropDown(wxAuiToolBarItem* self, bool b)
    {
        self->SetHasDropDown(b);
    }

    EXPORT bool wxAuiToolBarItem_HasDropDown(wxAuiToolBarItem* self)
    {
        return self->HasDropDown();
    }

    EXPORT void wxAuiToolBarItem_SetSticky(wxAuiToolBarItem* self, bool b)
    {
        self->SetSticky(b);
    }

    EXPORT bool wxAuiToolBarItem_IsSticky(wxAuiToolBarItem* self)
    {
        return self->IsSticky();
    }

    EXPORT void wxAuiToolBarItem_SetUserData(wxAuiToolBarItem* self, long l)
    {
        self->SetUserData(l);
    }

    EXPORT long wxAuiToolBarItem_GetUserData(wxAuiToolBarItem* self)
    {
        return self->GetUserData();
    }

    EXPORT void wxAuiToolBarItem_SetAlignment(wxAuiToolBarItem* self, int l)
    {
        self->SetAlignment(l);
    }

    EXPORT int wxAuiToolBarItem_GetAlignment(wxAuiToolBarItem* self)
    {
        return self->GetAlignment();
    }

    /* wxAuiToolBarArt */

    EXPORT void* wxAuiToolBarArt_Clone(wxAuiToolBarArt* self)
    {
        return (void*) self->Clone();
    }

    EXPORT void wxAuiToolBarArt_SetFlags(wxAuiToolBarArt* self, int _flags)
    {
        self->SetFlags(_flags);
    }

    EXPORT int wxAuiToolBarArt_GetFlags(wxAuiToolBarArt* self)
    {
        return self->GetFlags();
    }

    EXPORT void wxAuiToolBarArt_SetFont(wxAuiToolBarArt* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT wxFont* wxAuiToolBarArt_GetFont(wxAuiToolBarArt* self)
    {
        wxFont* font = new wxFont();
        *font = self->GetFont();
        return font;
    }

    EXPORT void wxAuiToolBarArt_SetTextOrientation(wxAuiToolBarArt* self, int orientation)
    {
        self->SetTextOrientation(orientation);
    }

    EXPORT int wxAuiToolBarArt_GetTextOrientation(wxAuiToolBarArt* self)
    {
        return self->GetTextOrientation();
    }

    EXPORT void wxAuiToolBarArt_DrawBackground(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                               wxRect* _rect)
    {
        return self->DrawBackground(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiToolBarArt_DrawPlainBackground(wxAuiToolBarArt* self, wxDC* _dc,
                                                    wxWindow* _wnd, wxRect* _rect)
    {
        return self->DrawPlainBackground(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiToolBarArt_DrawLabel(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                          wxAuiToolBarItem* _item, wxRect* _rect)
    {
        self->DrawLabel(*_dc, _wnd, *_item, *_rect);
    }

    EXPORT void wxAuiToolBarArt_DrawButton(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                           wxAuiToolBarItem* _item, wxRect* _rect)
    {
        self->DrawButton(*_dc, _wnd, *_item, *_rect);
    }

    EXPORT void wxAuiToolBarArt_DrawDropDownButton(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                                   wxAuiToolBarItem* _item, wxRect* _rect)
    {
        self->DrawDropDownButton(*_dc, _wnd, *_item, *_rect);
    }

    EXPORT void wxAuiToolBarArt_DrawControlLabel(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                                 wxAuiToolBarItem* _item, wxRect* _rect)
    {
        self->DrawControlLabel(*_dc, _wnd, *_item, *_rect);
    }

    EXPORT void wxAuiToolBarArt_DrawSeparator(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                              wxRect* _rect)
    {
        return self->DrawSeparator(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiToolBarArt_DrawGripper(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                            wxRect* _rect)
    {
        return self->DrawGripper(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiToolBarArt_DrawOverflowButton(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                                   wxRect* _rect, int state)
    {
        self->DrawOverflowButton(*_dc, _wnd, *_rect, state);
    }

    EXPORT wxSize* wxAuiToolBarArt_GetLabelSize(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                                wxAuiToolBarItem* _item)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetLabelSize(*_dc, _wnd, *_item);
        return sz;
    }

    EXPORT wxSize* wxAuiToolBarArt_GetToolSize(wxAuiToolBarArt* self, wxDC* _dc, wxWindow* _wnd,
                                               wxAuiToolBarItem* _item)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetToolSize(*_dc, _wnd, *_item);
        return sz;
    }

    EXPORT int wxAuiToolBarArt_GetElementSize(wxAuiToolBarArt* self, int element_id)
    {
        return self->GetElementSize(element_id);
    }

    EXPORT void wxAuiToolBarArt_SetElementSize(wxAuiToolBarArt* self, int element_id, int size)
    {
        self->SetElementSize(element_id, size);
    }

    EXPORT int wxAuiToolBarArt_ShowDropDown(wxAuiToolBarArt* self, wxWindow* _wnd,
                                            wxAuiToolBarItemArray* _items)
    {
        return self->ShowDropDown(_wnd, *_items);
    }

    /* wxAuiDefaultToolBarArt */

    EXPORT void* wxAuiDefaultToolBarArt_Create()
    {
        return (void*) new wxAuiDefaultToolBarArt();
    }

    EXPORT void* wxAuiDefaultToolBarArt_Clone(wxAuiDefaultToolBarArt* self)
    {
        return (void*) self->Clone();
    }

    EXPORT void wxAuiDefaultToolBarArt_SetFlags(wxAuiDefaultToolBarArt* self, int _flags)
    {
        self->SetFlags(_flags);
    }

    EXPORT int wxAuiDefaultToolBarArt_GetFlags(wxAuiDefaultToolBarArt* self)
    {
        return self->GetFlags();
    }

    EXPORT void wxAuiDefaultToolBarArt_SetFont(wxAuiDefaultToolBarArt* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT wxFont* wxAuiDefaultToolBarArt_GetFont(wxAuiDefaultToolBarArt* self)
    {
        wxFont* font = new wxFont();
        *font = self->GetFont();
        return font;
    }

    EXPORT void wxAuiDefaultToolBarArt_SetTextOrientation(wxAuiDefaultToolBarArt* self,
                                                          int orientation)
    {
        self->SetTextOrientation(orientation);
    }

    EXPORT int wxAuiDefaultToolBarArt_GetTextOrientation(wxAuiDefaultToolBarArt* self)
    {
        return self->GetTextOrientation();
    }

    EXPORT void wxAuiDefaultToolBarArt_DrawBackground(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                      wxWindow* _wnd, wxRect* _rect)
    {
        return self->DrawBackground(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiDefaultToolBarArt_DrawPlainBackground(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                           wxWindow* _wnd, wxRect* _rect)
    {
        return self->DrawPlainBackground(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiDefaultToolBarArt_DrawLabel(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                 wxWindow* _wnd, wxAuiToolBarItem* _item,
                                                 wxRect* _rect)
    {
        self->DrawLabel(*_dc, _wnd, *_item, *_rect);
    }

    EXPORT void wxAuiDefaultToolBarArt_DrawButton(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                  wxWindow* _wnd, wxAuiToolBarItem* _item,
                                                  wxRect* _rect)
    {
        self->DrawButton(*_dc, _wnd, *_item, *_rect);
    }

    EXPORT void wxAuiDefaultToolBarArt_DrawDropDownButton(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                          wxWindow* _wnd, wxAuiToolBarItem* _item,
                                                          wxRect* _rect)
    {
        self->DrawDropDownButton(*_dc, _wnd, *_item, *_rect);
    }

    EXPORT void wxAuiDefaultToolBarArt_DrawControlLabel(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                        wxWindow* _wnd, wxAuiToolBarItem* _item,
                                                        wxRect* _rect)
    {
        self->DrawControlLabel(*_dc, _wnd, *_item, *_rect);
    }

    EXPORT void wxAuiDefaultToolBarArt_DrawSeparator(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                     wxWindow* _wnd, wxRect* _rect)
    {
        return self->DrawSeparator(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiDefaultToolBarArt_DrawGripper(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                   wxWindow* _wnd, wxRect* _rect)
    {
        return self->DrawGripper(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiDefaultToolBarArt_DrawOverflowButton(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                          wxWindow* _wnd, wxRect* _rect, int state)
    {
        self->DrawOverflowButton(*_dc, _wnd, *_rect, state);
    }

    EXPORT wxSize* wxAuiDefaultToolBarArt_GetLabelSize(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                       wxWindow* _wnd, wxAuiToolBarItem* _item)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetLabelSize(*_dc, _wnd, *_item);
        return sz;
    }

    EXPORT wxSize* wxAuiDefaultToolBarArt_GetToolSize(wxAuiDefaultToolBarArt* self, wxDC* _dc,
                                                      wxWindow* _wnd, wxAuiToolBarItem* _item)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetToolSize(*_dc, _wnd, *_item);
        return sz;
    }

    EXPORT int wxAuiDefaultToolBarArt_GetElementSize(wxAuiDefaultToolBarArt* self, int element)
    {
        return self->GetElementSize(element);
    }

    EXPORT void wxAuiDefaultToolBarArt_SetElementSize(wxAuiDefaultToolBarArt* self, int element_id,
                                                      int size)
    {
        self->SetElementSize(element_id, size);
    }

    EXPORT int wxAuiDefaultToolBarArt_ShowDropDown(wxAuiDefaultToolBarArt* self, wxWindow* _wnd,
                                                   wxAuiToolBarItemArray* _items)
    {
        return self->ShowDropDown(_wnd, *_items);
    }

    /* wxAuiToolBar */

    EXPORT void* wxAuiToolBar_CreateDefault()
    {
        return (void*) new wxAuiToolBar();
    }

    EXPORT void* wxAuiToolBar_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                     long style)
    {
        return (void*) new wxAuiToolBar(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT bool wxAuiToolBar_CreateFromDefault(wxAuiToolBar* self, wxWindow* parent, int id, int x,
                                               int y, int width, int height, long style)
    {
        return self->Create(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxAuiToolBar_SetWindowStyleFlag(wxAuiToolBar* self, long style)
    {
        self->SetWindowStyleFlag(style);
    }

    EXPORT long wxAuiToolBar_GetWindowStyleFlag(wxAuiToolBar* self)
    {
        return self->GetWindowStyleFlag();
    }

    EXPORT void wxAuiToolBar_SetArtProvider(wxAuiToolBar* self, wxAuiToolBarArt* _art)
    {
        self->SetArtProvider(_art);
    }

    EXPORT void* wxAuiToolBar_GetArtProvider(wxAuiToolBar* self)
    {
        return (void*) self->GetArtProvider();
    }

    EXPORT bool wxAuiToolBar_SetFont(wxAuiToolBar* self, wxFont* _font)
    {
        return self->SetFont(*_font);
    }

    EXPORT void* wxAuiToolBar_AddToolByLabel(wxAuiToolBar* self, int tool_id, wxString* _label,
                                             wxBitmap* _bitmap, wxString* _short_help_string,
                                             int kind)
    {
        return (void*) self->AddTool(tool_id, *_label, *_bitmap, *_short_help_string,
                                     static_cast<wxItemKind>(kind));
    }

    EXPORT void* wxAuiToolBar_AddTool(wxAuiToolBar* self, int tool_id, wxString* _label,
                                      wxBitmap* _bitmap, wxBitmap* _disabled_bitmap, int kind,
                                      wxString* _short_help_string, wxString* _long_help_string,
                                      wxObject* _client_data)
    {
        return (void*) self->AddTool(tool_id, *_label, *_bitmap, *_disabled_bitmap,
                                     static_cast<wxItemKind>(kind), *_short_help_string,
                                     *_long_help_string, _client_data);
    }

    EXPORT void* wxAuiToolBar_AddToolByBitmap(wxAuiToolBar* self, int tool_id, wxBitmap* _bitmap,
                                              wxBitmap* _disabled_bitmap, bool toggle,
                                              wxObject* _client_data, wxString* _short_help_string,
                                              wxString* _long_help_string)
    {
        return (void*) self->AddTool(tool_id, *_bitmap, *_disabled_bitmap, toggle, _client_data,
                                     *_short_help_string, *_long_help_string);
    }

    EXPORT void* wxAuiToolBar_AddLabel(wxAuiToolBar* self, int tool_id, wxString* _label, int width)
    {
        return (void*) self->AddLabel(tool_id, *_label, width);
    }

    EXPORT void* wxAuiToolBar_AddControl(wxAuiToolBar* self, wxControl* _control, wxString* _label)
    {
        return (void*) self->AddControl(_control, *_label);
    }

    EXPORT void* wxAuiToolBar_AddSeparator(wxAuiToolBar* self)
    {
        return (void*) self->AddSeparator();
    }

    EXPORT void* wxAuiToolBar_AddSpacer(wxAuiToolBar* self, int pixels)
    {
        return (void*) self->AddSpacer(pixels);
    }

    EXPORT void* wxAuiToolBar_AddStretchSpacer(wxAuiToolBar* self, int proportion)
    {
        return (void*) self->AddStretchSpacer(proportion);
    }

    EXPORT bool wxAuiToolBar_Realize(wxAuiToolBar* self)
    {
        return self->Realize();
    }

    EXPORT void* wxAuiToolBar_FindControl(wxAuiToolBar* self, int window_id)
    {
        return (void*) self->FindControl(window_id);
    }

    EXPORT void* wxAuiToolBar_FindToolByPosition(wxAuiToolBar* self, int x, int y)
    {
        return (void*) self->FindToolByPosition(x, y);
    }

    EXPORT void* wxAuiToolBar_FindToolByIndex(wxAuiToolBar* self, int idx)
    {
        return (void*) self->FindToolByIndex(idx);
    }

    EXPORT void* wxAuiToolBar_FindTool(wxAuiToolBar* self, int tool_id)
    {
        return (void*) self->FindTool(tool_id);
    }

    EXPORT void wxAuiToolBar_ClearTools(wxAuiToolBar* self)
    {
        self->ClearTools();
    }

    EXPORT void wxAuiToolBar_Clear(wxAuiToolBar* self)
    {
        self->Clear();
    }

    EXPORT bool wxAuiToolBar_DeleteTool(wxAuiToolBar* self, int tool_id)
    {
        return self->DeleteTool(tool_id);
    }

    EXPORT bool wxAuiToolBar_DeleteByIndex(wxAuiToolBar* self, int tool_id)
    {
        return self->DeleteByIndex(tool_id);
    }

    EXPORT size_t wxAuiToolBar_GetToolCount(wxAuiToolBar* self)
    {
        return self->GetToolCount();
    }

    EXPORT int wxAuiToolBar_GetToolPos(wxAuiToolBar* self, int tool_id)
    {
        return self->GetToolPos(tool_id);
    }

    EXPORT int wxAuiToolBar_GetToolIndex(wxAuiToolBar* self, int tool_id)
    {
        return self->GetToolIndex(tool_id);
    }

    EXPORT bool wxAuiToolBar_GetToolFits(wxAuiToolBar* self, int tool_id)
    {
        return self->GetToolFits(tool_id);
    }

    EXPORT wxRect* wxAuiToolBar_GetToolRect(wxAuiToolBar* self, int tool_id)
    {
        wxRect* rect = new wxRect();
        *rect = self->GetToolRect(tool_id);
        return rect;
    }

    EXPORT bool wxAuiToolBar_GetToolFitsByIndex(wxAuiToolBar* self, int tool_id)
    {
        return self->GetToolFitsByIndex(tool_id);
    }

    EXPORT bool wxAuiToolBar_GetToolBarFits(wxAuiToolBar* self)
    {
        return self->GetToolBarFits();
    }

    EXPORT void wxAuiToolBar_SetMargins(wxAuiToolBar* self, int width, int height)
    {
        self->SetMargins(wxSize(width, height));
    }

    EXPORT void wxAuiToolBar_SetMarginsXY(wxAuiToolBar* self, int x, int y)
    {
        self->SetMargins(x, y);
    }

    EXPORT void wxAuiToolBar_SetMarginsDetailed(wxAuiToolBar* self, int left, int right, int top,
                                                int bottom)
    {
        self->SetMargins(left, right, top, bottom);
    }

    EXPORT void wxAuiToolBar_SetToolBitmapSize(wxAuiToolBar* self, int width, int height)
    {
        self->SetToolBitmapSize(wxSize(width, height));
    }

    EXPORT wxSize* wxAuiToolBar_GetToolBitmapSize(wxAuiToolBar* self)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetToolBitmapSize();
        return sz;
    }

    EXPORT bool wxAuiToolBar_GetOverflowVisible(wxAuiToolBar* self)
    {
        return self->GetOverflowVisible();
    }

    EXPORT void wxAuiToolBar_SetOverflowVisible(wxAuiToolBar* self, bool visible)
    {
        self->SetOverflowVisible(visible);
    }

    EXPORT bool wxAuiToolBar_GetGripperVisible(wxAuiToolBar* self)
    {
        return self->GetGripperVisible();
    }

    EXPORT void wxAuiToolBar_SetGripperVisible(wxAuiToolBar* self, bool visible)
    {
        self->SetGripperVisible(visible);
    }

    EXPORT void wxAuiToolBar_ToggleTool(wxAuiToolBar* self, int tool_id, bool state)
    {
        self->ToggleTool(tool_id, state);
    }

    EXPORT bool wxAuiToolBar_GetToolToggled(wxAuiToolBar* self, int tool_id)
    {
        return self->GetToolToggled(tool_id);
    }

    EXPORT void wxAuiToolBar_EnableTool(wxAuiToolBar* self, int tool_id, bool state)
    {
        self->EnableTool(tool_id, state);
    }

    EXPORT bool wxAuiToolBar_GetToolEnabled(wxAuiToolBar* self, int tool_id)
    {
        return self->GetToolEnabled(tool_id);
    }

    EXPORT void wxAuiToolBar_SetToolDropDown(wxAuiToolBar* self, int tool_id, bool dropdown)
    {
        self->SetToolDropDown(tool_id, dropdown);
    }

    EXPORT bool wxAuiToolBar_GetToolDropDown(wxAuiToolBar* self, int tool_id)
    {
        return self->GetToolDropDown(tool_id);
    }

    EXPORT void wxAuiToolBar_SetToolBorderPadding(wxAuiToolBar* self, int padding)
    {
        self->SetToolBorderPadding(padding);
    }

    EXPORT int wxAuiToolBar_GetToolBorderPadding(wxAuiToolBar* self)
    {
        return self->GetToolBorderPadding();
    }

    EXPORT void wxAuiToolBar_SetToolTextOrientation(wxAuiToolBar* self, int orientation)
    {
        self->SetToolTextOrientation(orientation);
    }

    EXPORT int wxAuiToolBar_GetToolTextOrientation(wxAuiToolBar* self)
    {
        return self->GetToolTextOrientation();
    }

    EXPORT void wxAuiToolBar_SetToolPacking(wxAuiToolBar* self, int packing)
    {
        self->SetToolPacking(packing);
    }

    EXPORT int wxAuiToolBar_GetToolPacking(wxAuiToolBar* self)
    {
        return self->GetToolPacking();
    }

    EXPORT void wxAuiToolBar_SetToolProportion(wxAuiToolBar* self, int tool_id, int proportion)
    {
        self->SetToolProportion(tool_id, proportion);
    }

    EXPORT int wxAuiToolBar_GetToolProportion(wxAuiToolBar* self, int tool_id)
    {
        return self->GetToolProportion(tool_id);
    }

    EXPORT void wxAuiToolBar_SetToolSeparation(wxAuiToolBar* self, int separation)
    {
        self->SetToolSeparation(separation);
    }

    EXPORT int wxAuiToolBar_GetToolSeparation(wxAuiToolBar* self)
    {
        return self->GetToolSeparation();
    }

    EXPORT void wxAuiToolBar_SetToolSticky(wxAuiToolBar* self, int tool_id, bool sticky)
    {
        self->SetToolSticky(tool_id, sticky);
    }

    EXPORT bool wxAuiToolBar_GetToolSticky(wxAuiToolBar* self, int tool_id)
    {
        return self->GetToolSticky(tool_id);
    }

    EXPORT wxString* wxAuiToolBar_GetToolLabel(wxAuiToolBar* self, int tool_id)
    {
        wxString* result = new wxString();
        *result = self->GetToolLabel(tool_id);
        return result;
    }

    EXPORT void wxAuiToolBar_SetToolLabel(wxAuiToolBar* self, int tool_id, wxString* _label)
    {
        self->SetToolLabel(tool_id, *_label);
    }

    EXPORT void wxAuiToolBar_GetToolBitmap(wxAuiToolBar* self, int tool_id, wxBitmap* bmp)
    {
        *bmp = self->GetToolBitmap(tool_id);
    }

    EXPORT void wxAuiToolBar_SetToolBitmap(wxAuiToolBar* self, int tool_id, wxBitmap* _bitmap)
    {
        self->SetToolBitmap(tool_id, *_bitmap);
    }

    EXPORT wxString* wxAuiToolBar_GetToolShortHelp(wxAuiToolBar* self, int tool_id)
    {
        wxString* result = new wxString();
        *result = self->GetToolShortHelp(tool_id);
        return result;
    }

    EXPORT void wxAuiToolBar_SetToolShortHelp(wxAuiToolBar* self, int tool_id,
                                              wxString* _help_string)
    {
        self->SetToolShortHelp(tool_id, *_help_string);
    }

    EXPORT wxString* wxAuiToolBar_GetToolLongHelp(wxAuiToolBar* self, int tool_id)
    {
        wxString* result = new wxString();
        *result = self->GetToolLongHelp(tool_id);
        return result;
    }

    EXPORT void wxAuiToolBar_SetToolLongHelp(wxAuiToolBar* self, int tool_id,
                                             wxString* _help_string)
    {
        self->SetToolLongHelp(tool_id, *_help_string);
    }

    EXPORT void wxAuiToolBar_SetCustomOverflowItems(wxAuiToolBar* self,
                                                    wxAuiToolBarItemArray* _prepend,
                                                    wxAuiToolBarItemArray* _append)
    {
        self->SetCustomOverflowItems(*_prepend, *_append);
    }

    EXPORT wxSize* wxAuiToolBar_GetHintSize(wxAuiToolBar* self, int dock_direction)
    {
        wxSize* sz = new wxSize();
        *sz = self->GetHintSize(dock_direction);
        return sz;
    }

    EXPORT bool wxAuiToolBar_IsPaneValid(wxAuiToolBar* self, wxAuiPaneInfo* _pane)
    {
        return self->IsPaneValid(*_pane);
    }

    /* wxAuiNotebook */

    EXPORT void* wxAuiNotebook_CreateDefault()
    {
        return (void*) new wxAuiNotebook();
    }

    EXPORT void* wxAuiNotebook_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                                      long style)
    {
        return (void*) new wxAuiNotebook(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT bool wxAuiNotebook_CreateFromDefault(wxAuiNotebook* self, wxWindow* parent, int id,
                                                int x, int y, int width, int height, long style)
    {
        return self->Create(parent, id, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT bool wxAuiNotebook_AddPageWithBitmap(wxAuiNotebook* self, wxWindow* _page,
                                                wxString* _caption, bool select, wxBitmap* _bitmap)
    {
        return self->AddPage(_page, *_caption, select, *_bitmap);
    }

    EXPORT bool wxAuiNotebook_AddPage(wxAuiNotebook* self, wxWindow* _page, wxString* _text,
                                      bool select, int imageId)
    {
        return self->AddPage(_page, *_text, select, imageId);
    }

    EXPORT void wxAuiNotebook_AdvanceSelection(wxAuiNotebook* self, bool forward)
    {
        self->AdvanceSelection(forward);
    }

    EXPORT int wxAuiNotebook_ChangeSelection(wxAuiNotebook* self, size_t n)
    {
        return self->ChangeSelection(n);
    }

    EXPORT bool wxAuiNotebook_DeleteAllPages(wxAuiNotebook* self)
    {
        return self->DeleteAllPages();
    }

    EXPORT bool wxAuiNotebook_DeletePage(wxAuiNotebook* self, size_t page)
    {
        return self->DeletePage(page);
    }

    EXPORT void* wxAuiNotebook_GetArtProvider(wxAuiNotebook* self)
    {
        return (void*) self->GetArtProvider();
    }

    EXPORT void* wxAuiNotebook_GetCurrentPage(wxAuiNotebook* self)
    {
        return (void*) self->GetCurrentPage();
    }

    EXPORT int wxAuiNotebook_GetHeightForPageHeight(wxAuiNotebook* self, int pageHeight)
    {
        return self->GetHeightForPageHeight(pageHeight);
    }

    EXPORT void* wxAuiNotebook_GetPage(wxAuiNotebook* self, size_t page_idx)
    {
        return (void*) self->GetPage(page_idx);
    }

    EXPORT void wxAuiNotebook_GetPageBitmap(wxAuiNotebook* self, size_t page, wxBitmap* bmp)
    {
        *bmp = self->GetPageBitmap(page);
    }

    EXPORT size_t wxAuiNotebook_GetPageCount(wxAuiNotebook* self)
    {
        return self->GetPageCount();
    }

    EXPORT int wxAuiNotebook_GetPageIndex(wxAuiNotebook* self, wxWindow* _page_wnd)
    {
        return self->GetPageIndex(_page_wnd);
    }

    EXPORT wxString* wxAuiNotebook_GetPageText(wxAuiNotebook* self, size_t page)
    {
        wxString* result = new wxString();
        *result = self->GetPageText(page);
        return result;
    }

    EXPORT wxString* wxAuiNotebook_GetPageToolTip(wxAuiNotebook* self, size_t pageIdx)
    {
        wxString* result = new wxString();
        *result = self->GetPageToolTip(pageIdx);
        return result;
    }

    EXPORT int wxAuiNotebook_GetSelection(wxAuiNotebook* self)
    {
        return self->GetSelection();
    }

    EXPORT int wxAuiNotebook_GetTabCtrlHeight(wxAuiNotebook* self)
    {
        return self->GetTabCtrlHeight();
    }

    EXPORT bool wxAuiNotebook_InsertPageWithBitmap(wxAuiNotebook* self, size_t page_idx,
                                                   wxWindow* _page, wxString* _caption, bool select,
                                                   wxBitmap* _bitmap)
    {
        return self->InsertPage(page_idx, _page, *_caption, select, *_bitmap);
    }

    EXPORT bool wxAuiNotebook_InsertPage(wxAuiNotebook* self, size_t index, wxWindow* _page,
                                         wxString* _text, bool select, int imageId)
    {
        return self->InsertPage(index, _page, *_text, select, imageId);
    }

    EXPORT bool wxAuiNotebook_RemovePage(wxAuiNotebook* self, size_t page)
    {
        return self->RemovePage(page);
    }

    EXPORT void wxAuiNotebook_SetArtProvider(wxAuiNotebook* self, wxAuiTabArt* _art)
    {
        self->SetArtProvider(_art);
    }

    EXPORT bool wxAuiNotebook_SetFont(wxAuiNotebook* self, wxFont* _font)
    {
        return self->SetFont(*_font);
    }

    EXPORT void wxAuiNotebook_SetMeasuringFont(wxAuiNotebook* self, wxFont* font)
    {
        self->SetMeasuringFont(*font);
    }

    EXPORT void wxAuiNotebook_SetNormalFont(wxAuiNotebook* self, wxFont* font)
    {
        self->SetNormalFont(*font);
    }

    EXPORT bool wxAuiNotebook_SetPageBitmap(wxAuiNotebook* self, size_t page, wxBitmap* _bitmap)
    {
        return self->SetPageBitmap(page, *_bitmap);
    }

    EXPORT bool wxAuiNotebook_SetPageImage(wxAuiNotebook* self, size_t n, int imageId)
    {
        return self->SetPageImage(n, imageId);
    }

    EXPORT bool wxAuiNotebook_SetPageText(wxAuiNotebook* self, size_t page, wxString* _text)
    {
        return self->SetPageText(page, *_text);
    }

    EXPORT bool wxAuiNotebook_SetPageToolTip(wxAuiNotebook* self, size_t page, wxString* _text)
    {
        return self->SetPageToolTip(page, *_text);
    }

    EXPORT void wxAuiNotebook_SetSelectedFont(wxAuiNotebook* self, wxFont* font)
    {
        self->SetSelectedFont(*font);
    }

    EXPORT size_t wxAuiNotebook_SetSelection(wxAuiNotebook* self, size_t new_page)
    {
        return self->SetSelection(new_page);
    }

    EXPORT void wxAuiNotebook_SetTabCtrlHeight(wxAuiNotebook* self, int height)
    {
        self->SetTabCtrlHeight(height);
    }

    EXPORT bool wxAuiNotebook_ShowWindowMenu(wxAuiNotebook* self)
    {
        return self->ShowWindowMenu();
    }

    EXPORT void wxAuiNotebook_SetUniformBitmapSize(wxAuiNotebook* self, int width, int height)
    {
        self->SetUniformBitmapSize(wxSize(width, height));
    }

    EXPORT void wxAuiNotebook_Split(wxAuiNotebook* self, size_t page, int direction)
    {
        self->Split(page, direction);
    }

    /* wxAuiNotebookEvent */

    EXPORT void* wxAuiNotebookEvent_Create(int commandType, int winid)
    {
        return (void*) new wxAuiNotebookEvent(commandType, winid);
    }

    EXPORT wxAuiNotebook* wxAuiNotebookEvent_GetDragSource(wxAuiNotebookEvent* self)
    {
        return self->GetDragSource();
    }

    /* wxBookCtrlEvent */

    EXPORT void* wxBookCtrlEvent_Create(int commandType, int winid, int nSel, int nOldSel)
    {
        return (void*) new wxBookCtrlEvent(commandType, winid, nSel, nOldSel);
    }

    EXPORT int wxBookCtrlEvent_GetSelection(wxBookCtrlEvent* self)
    {
        return self->GetSelection();
    }

    EXPORT int wxBookCtrlEvent_GetOldSelection(wxBookCtrlEvent* self)
    {
        return self->GetOldSelection();
    }

    /* wxAuiTabContainerButton */

    EXPORT int wxAuiTabContainerButton_Id(wxAuiTabContainerButton* self)
    {
        return self->id;
    }

    EXPORT int wxAuiTabContainerButton_CurState(wxAuiTabContainerButton* self)
    {
        return self->curState;
    }

    EXPORT int wxAuiTabContainerButton_Location(wxAuiTabContainerButton* self)
    {
        return self->location;
    }

    EXPORT void wxAuiTabContainerButton_Bitmap(wxAuiTabContainerButton* self, wxBitmapBundle* _bmp)
    {
        *_bmp = self->bitmap;
    }

    EXPORT void wxAuiTabContainerButton_DisBitmap(wxAuiTabContainerButton* self,
                                                  wxBitmapBundle* _bmp)
    {
        *_bmp = self->disBitmap;
    }

    EXPORT wxRect* wxAuiTabContainerButton_Rect(wxAuiTabContainerButton* self)
    {
        wxRect* rect = new wxRect();
        *rect = self->rect;
        return rect;
    }

    /* wxAuiTabContainer */

    EXPORT void* wxAuiTabContainer_Create()
    {
        return (void*) new wxAuiTabContainer();
    }

    EXPORT void wxAuiTabContainer_SetArtProvider(wxAuiTabContainer* self, wxAuiTabArt* _art)
    {
        self->SetArtProvider(_art);
    }

    EXPORT void* wxAuiTabContainer_GetArtProvider(wxAuiTabContainer* self)
    {
        return (void*) self->GetArtProvider();
    }

    EXPORT void wxAuiTabContainer_SetFlags(wxAuiTabContainer* self, int _flags)
    {
        self->SetFlags(_flags);
    }

    EXPORT int wxAuiTabContainer_GetFlags(wxAuiTabContainer* self)
    {
        return self->GetFlags();
    }

    EXPORT bool wxAuiTabContainer_AddPage(wxAuiTabContainer* self, wxWindow* _page,
                                          wxAuiNotebookPage* _info)
    {
        return self->AddPage(_page, *_info);
    }

    EXPORT bool wxAuiTabContainer_InsertPage(wxAuiTabContainer* self, wxWindow* _page,
                                             wxAuiNotebookPage* _info, size_t idx)
    {
        return self->InsertPage(_page, *_info, idx);
    }

    EXPORT bool wxAuiTabContainer_MovePage(wxAuiTabContainer* self, wxWindow* _page, size_t newIdx)
    {
        return self->MovePage(_page, newIdx);
    }

    EXPORT bool wxAuiTabContainer_RemovePage(wxAuiTabContainer* self, wxWindow* _page)
    {
        return self->RemovePage(_page);
    }

    EXPORT bool wxAuiTabContainer_SetActivePageByWindow(wxAuiTabContainer* self, wxWindow* _page)
    {
        return self->SetActivePage(_page);
    }

    EXPORT bool wxAuiTabContainer_SetActivePage(wxAuiTabContainer* self, size_t page)
    {
        return self->SetActivePage(page);
    }

    EXPORT void wxAuiTabContainer_SetNoneActive(wxAuiTabContainer* self)
    {
        self->SetNoneActive();
    }

    EXPORT int wxAuiTabContainer_GetActivePage(wxAuiTabContainer* self)
    {
        return self->GetActivePage();
    }

    EXPORT void* wxAuiTabContainer_GetWindowFromIdx(wxAuiTabContainer* self, size_t idx)
    {
        return (void*) self->GetWindowFromIdx(idx);
    }

    EXPORT int wxAuiTabContainer_GetIdxFromWindow(wxAuiTabContainer* self, wxWindow* _page)
    {
        return self->GetIdxFromWindow(_page);
    }

    EXPORT size_t wxAuiTabContainer_GetPageCount(wxAuiTabContainer* self)
    {
        return self->GetPageCount();
    }

    EXPORT wxAuiNotebookPage* wxAuiTabContainer_GetPage(wxAuiTabContainer* self, size_t idx)
    {
        wxAuiNotebookPage* page = new wxAuiNotebookPage();
        *page = self->GetPage(idx);
        return page;
    }

    EXPORT wxAuiNotebookPageArray* wxAuiTabContainer_GetPages(wxAuiTabContainer* self)
    {
        wxAuiNotebookPageArray* pages = new wxAuiNotebookPageArray();
        *pages = self->GetPages();
        return pages;
    }

    EXPORT void wxAuiTabContainer_SetNormalFont(wxAuiTabContainer* self, wxFont* normalFont)
    {
        self->SetNormalFont(*normalFont);
    }

    EXPORT void wxAuiTabContainer_SetSelectedFont(wxAuiTabContainer* self, wxFont* selectedFont)
    {
        self->SetSelectedFont(*selectedFont);
    }

    EXPORT void wxAuiTabContainer_SetMeasuringFont(wxAuiTabContainer* self, wxFont* measuringFont)
    {
        self->SetMeasuringFont(*measuringFont);
    }

    EXPORT void wxAuiTabContainer_SetColour(wxAuiTabContainer* self, wxColour* _colour)
    {
        self->SetColour(*_colour);
    }

    EXPORT void wxAuiTabContainer_SetActiveColour(wxAuiTabContainer* self, wxColour* _colour)
    {
        self->SetActiveColour(*_colour);
    }

    EXPORT void wxAuiTabContainer_DoShowHide(wxAuiTabContainer* self)
    {
        self->DoShowHide();
    }

    EXPORT void wxAuiTabContainer_SetRect(wxAuiTabContainer* self, wxRect* _rect)
    {
        self->SetRect(*_rect);
    }

    EXPORT void wxAuiTabContainer_RemoveButton(wxAuiTabContainer* self, int id)
    {
        self->RemoveButton(id);
    }

    EXPORT void wxAuiTabContainer_AddButton(wxAuiTabContainer* self, int id, int location,
                                            wxBitmap* _normalBitmap, wxBitmap* _disabledBitmap)
    {
        self->AddButton(id, location, *_normalBitmap, *_disabledBitmap);
    }

    EXPORT size_t wxAuiTabContainer_GetTabOffset(wxAuiTabContainer* self)
    {
        return self->GetTabOffset();
    }

    EXPORT void wxAuiTabContainer_SetTabOffset(wxAuiTabContainer* self, size_t offset)
    {
        self->SetTabOffset(offset);
    }

    EXPORT bool wxAuiTabContainer_IsTabVisible(wxAuiTabContainer* self, int tabPage, int tabOffset,
                                               wxDC* _dc, wxWindow* _wnd)
    {
        return self->IsTabVisible(tabPage, tabOffset, _dc, _wnd);
    }

    EXPORT void wxAuiTabContainer_MakeTabVisible(wxAuiTabContainer* self, int tabPage,
                                                 wxWindow* _win)
    {
        self->MakeTabVisible(tabPage, _win);
    }

    /* wxAuiTabCtrl */

    EXPORT void wxAuiTabCtrl_SetArtProvider(wxAuiTabCtrl* self, wxAuiTabArt* _art)
    {
        self->SetArtProvider(_art);
    }

    EXPORT void* wxAuiTabCtrl_GetArtProvider(wxAuiTabCtrl* self)
    {
        return (void*) self->GetArtProvider();
    }

    EXPORT void wxAuiTabCtrl_SetFlags(wxAuiTabCtrl* self, int _flags)
    {
        self->SetFlags(_flags);
    }

    EXPORT int wxAuiTabCtrl_GetFlags(wxAuiTabCtrl* self)
    {
        return self->GetFlags();
    }

    EXPORT bool wxAuiTabCtrl_AddPage(wxAuiTabCtrl* self, wxWindow* _page, wxAuiNotebookPage* _info)
    {
        return self->AddPage(_page, *_info);
    }

    EXPORT bool wxAuiTabCtrl_InsertPage(wxAuiTabCtrl* self, wxWindow* _page,
                                        wxAuiNotebookPage* _info, size_t idx)
    {
        return self->InsertPage(_page, *_info, idx);
    }

    EXPORT bool wxAuiTabCtrl_MovePage(wxAuiTabCtrl* self, wxWindow* _page, size_t newIdx)
    {
        return self->MovePage(_page, newIdx);
    }

    EXPORT bool wxAuiTabCtrl_RemovePage(wxAuiTabCtrl* self, wxWindow* _page)
    {
        return self->RemovePage(_page);
    }

    EXPORT bool wxAuiTabCtrl_SetActivePageByWindow(wxAuiTabCtrl* self, wxWindow* _page)
    {
        return self->SetActivePage(_page);
    }

    EXPORT bool wxAuiTabCtrl_SetActivePage(wxAuiTabCtrl* self, size_t page)
    {
        return self->SetActivePage(page);
    }

    EXPORT void wxAuiTabCtrl_SetNoneActive(wxAuiTabCtrl* self)
    {
        self->SetNoneActive();
    }

    EXPORT int wxAuiTabCtrl_GetActivePage(wxAuiTabCtrl* self)
    {
        return self->GetActivePage();
    }

    EXPORT void* wxAuiTabCtrl_GetWindowFromIdx(wxAuiTabCtrl* self, size_t idx)
    {
        return (void*) self->GetWindowFromIdx(idx);
    }

    EXPORT int wxAuiTabCtrl_GetIdxFromWindow(wxAuiTabCtrl* self, wxWindow* _page)
    {
        return self->GetIdxFromWindow(_page);
    }

    EXPORT size_t wxAuiTabCtrl_GetPageCount(wxAuiTabCtrl* self)
    {
        return self->GetPageCount();
    }

    EXPORT wxAuiNotebookPage* wxAuiTabCtrl_GetPage(wxAuiTabCtrl* self, size_t idx)
    {
        wxAuiNotebookPage* page = new wxAuiNotebookPage();
        *page = self->GetPage(idx);
        return page;
    }

    EXPORT wxAuiNotebookPageArray* wxAuiTabCtrl_GetPages(wxAuiTabCtrl* self)
    {
        wxAuiNotebookPageArray* pages = new wxAuiNotebookPageArray();
        *pages = self->GetPages();
        return pages;
    }

    EXPORT void wxAuiTabCtrl_SetNormalFont(wxAuiTabCtrl* self, wxFont* normalFont)
    {
        self->SetNormalFont(*normalFont);
    }

    EXPORT void wxAuiTabCtrl_SetSelectedFont(wxAuiTabCtrl* self, wxFont* selectedFont)
    {
        self->SetSelectedFont(*selectedFont);
    }

    EXPORT void wxAuiTabCtrl_SetMeasuringFont(wxAuiTabCtrl* self, wxFont* measuringFont)
    {
        self->SetMeasuringFont(*measuringFont);
    }

    EXPORT void wxAuiTabCtrl_SetColour(wxAuiTabCtrl* self, wxColour* _colour)
    {
        self->SetColour(*_colour);
    }

    EXPORT void wxAuiTabCtrl_SetActiveColour(wxAuiTabCtrl* self, wxColour* _colour)
    {
        self->SetActiveColour(*_colour);
    }

    EXPORT void wxAuiTabCtrl_DoShowHide(wxAuiTabCtrl* self)
    {
        self->DoShowHide();
    }

    EXPORT void wxAuiTabCtrl_SetRect(wxAuiTabCtrl* self, wxRect* _rect)
    {
        self->SetRect(*_rect);
    }

    EXPORT void wxAuiTabCtrl_RemoveButton(wxAuiTabCtrl* self, int id)
    {
        self->RemoveButton(id);
    }

    EXPORT void wxAuiTabCtrl_AddButton(wxAuiTabCtrl* self, int id, int location,
                                       wxBitmap* _normalBitmap, wxBitmap* _disabledBitmap)
    {
        self->AddButton(id, location, *_normalBitmap, *_disabledBitmap);
    }

    EXPORT size_t wxAuiTabCtrl_GetTabOffset(wxAuiTabCtrl* self)
    {
        return self->GetTabOffset();
    }

    EXPORT void wxAuiTabCtrl_SetTabOffset(wxAuiTabCtrl* self, size_t offset)
    {
        self->SetTabOffset(offset);
    }

    EXPORT bool wxAuiTabCtrl_IsTabVisible(wxAuiTabCtrl* self, int tabPage, int tabOffset, wxDC* _dc,
                                          wxWindow* _wnd)
    {
        return self->IsTabVisible(tabPage, tabOffset, _dc, _wnd);
    }

    EXPORT void wxAuiTabCtrl_MakeTabVisible(wxAuiTabCtrl* self, int tabPage, wxWindow* _win)
    {
        self->MakeTabVisible(tabPage, _win);
    }

    /* wxAuiTabArt */

    EXPORT void* wxAuiTabArt_Clone(wxAuiTabArt* self)
    {
        return (void*) self->Clone();
    }

    EXPORT void wxAuiTabArt_DrawBackground(wxAuiTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                           wxRect* _rect)
    {
        return self->DrawBackground(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiTabArt_DrawButton(wxAuiTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                       wxRect* _in_rect, int bitmap_id, int button_state,
                                       int orientation, wxRect* _out_rect)
    {
        self->DrawButton(*_dc, _wnd, *_in_rect, bitmap_id, button_state, orientation, _out_rect);
    }

    EXPORT void wxAuiTabArt_DrawTab(wxAuiTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                    wxAuiNotebookPage* _page, wxRect* _rect, int close_button_state,
                                    wxRect* _out_tab_rect, wxRect* _out_button_rect, int* x_extent)
    {
        self->DrawTab(*_dc, _wnd, *_page, *_rect, close_button_state, _out_tab_rect,
                      _out_button_rect, x_extent);
    }

    EXPORT int wxAuiTabArt_GetBestTabCtrlSize(wxAuiTabArt* self, wxWindow* wnd,
                                              wxAuiNotebookPageArray* pages, int width, int height)
    {
        return self->GetBestTabCtrlSize(wnd, *pages, wxSize(width, height));
    }

    EXPORT int wxAuiTabArt_GetIndentSize(wxAuiTabArt* self)
    {
        return self->GetIndentSize();
    }

    EXPORT wxSize* wxAuiTabArt_GetTabSize(wxAuiTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                          wxString* _caption, wxBitmap* _bitmap, bool active,
                                          int close_button_state, int* x_extent)
    {
        wxSize* sz = new wxSize();
        *sz =
            self->GetTabSize(*_dc, _wnd, *_caption, *_bitmap, active, close_button_state, x_extent);
        return sz;
    }

    EXPORT void wxAuiTabArt_SetFlags(wxAuiTabArt* self, int _flags)
    {
        self->SetFlags(_flags);
    }

    EXPORT void wxAuiTabArt_SetMeasuringFont(wxAuiTabArt* self, wxFont* font)
    {
        self->SetMeasuringFont(*font);
    }

    EXPORT void wxAuiTabArt_SetNormalFont(wxAuiTabArt* self, wxFont* font)
    {
        self->SetNormalFont(*font);
    }

    EXPORT void wxAuiTabArt_SetSelectedFont(wxAuiTabArt* self, wxFont* font)
    {
        self->SetSelectedFont(*font);
    }

    EXPORT void wxAuiTabArt_SetColour(wxAuiTabArt* self, wxColour* _colour)
    {
        self->SetColour(*_colour);
    }

    EXPORT void wxAuiTabArt_SetActiveColour(wxAuiTabArt* self, wxColour* _colour)
    {
        self->SetActiveColour(*_colour);
    }

    EXPORT void wxAuiTabArt_SetSizingInfo(wxAuiTabArt* self, int width, int height,
                                          size_t tab_count)
    {
        self->SetSizingInfo(wxSize(width, height), tab_count);
    }

    /* wxAuiTabCtrll */

    /* wxAuiSimpleTabArt */

    EXPORT void* wxAuiSimpleTabArt_Create()
    {
        return (void*) new wxAuiSimpleTabArt();
    }

    EXPORT void* wxAuiSimpleTabArt_Clone(wxAuiSimpleTabArt* self)
    {
        return (void*) self->Clone();
    }

    EXPORT void wxAuiSimpleTabArt_SetFlags(wxAuiSimpleTabArt* self, int _flags)
    {
        self->SetFlags(_flags);
    }

    EXPORT void wxAuiSimpleTabArt_SetSizingInfo(wxAuiSimpleTabArt* self, int width, int height,
                                                size_t tabCount)
    {
        self->SetSizingInfo(wxSize(width, height), tabCount);
    }

    EXPORT void wxAuiSimpleTabArt_SetNormalFont(wxAuiSimpleTabArt* self, wxFont* font)
    {
        self->SetNormalFont(*font);
    }

    EXPORT void wxAuiSimpleTabArt_SetSelectedFont(wxAuiSimpleTabArt* self, wxFont* font)
    {
        self->SetSelectedFont(*font);
    }

    EXPORT void wxAuiSimpleTabArt_SetMeasuringFont(wxAuiSimpleTabArt* self, wxFont* font)
    {
        self->SetMeasuringFont(*font);
    }

    EXPORT void wxAuiSimpleTabArt_SetColour(wxAuiSimpleTabArt* self, wxColour* _colour)
    {
        self->SetColour(*_colour);
    }

    EXPORT void wxAuiSimpleTabArt_SetActiveColour(wxAuiSimpleTabArt* self, wxColour* _colour)
    {
        self->SetActiveColour(*_colour);
    }

    EXPORT void wxAuiSimpleTabArt_DrawBackground(wxAuiSimpleTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                                 wxRect* _rect)
    {
        return self->DrawBackground(*_dc, _wnd, *_rect);
    }

    EXPORT void wxAuiSimpleTabArt_DrawTab(wxAuiSimpleTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                          wxAuiNotebookPage* _pane, wxRect* _inRect,
                                          int closeButtonState, wxRect* _outTabRect,
                                          wxRect* _outButtonRect, int* xExtent)
    {
        self->DrawTab(*_dc, _wnd, *_pane, *_inRect, closeButtonState, _outTabRect, _outButtonRect,
                      xExtent);
    }

    EXPORT void wxAuiSimpleTabArt_DrawButton(wxAuiSimpleTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                             wxRect* _inRect, int bitmapId, int buttonState,
                                             int orientation, wxRect* _outRect)
    {
        self->DrawButton(*_dc, _wnd, *_inRect, bitmapId, buttonState, orientation, _outRect);
    }

    EXPORT int wxAuiSimpleTabArt_GetIndentSize(wxAuiSimpleTabArt* self)
    {
        return self->GetIndentSize();
    }

    EXPORT wxSize* wxAuiSimpleTabArt_GetTabSize(wxAuiSimpleTabArt* self, wxDC* _dc, wxWindow* _wnd,
                                                wxString* _caption, wxBitmap* _bitmap, bool active,
                                                int close_button_state, int* x_extent)
    {
        wxSize* sz = new wxSize();
        *sz =
            self->GetTabSize(*_dc, _wnd, *_caption, *_bitmap, active, close_button_state, x_extent);
        return sz;
    }

    EXPORT int wxAuiSimpleTabArt_ShowDropDown(wxAuiSimpleTabArt* self, wxWindow* _wnd,
                                              wxAuiNotebookPageArray* _items, int activeIdx)
    {
        return self->ShowDropDown(_wnd, *_items, activeIdx);
    }

    EXPORT int wxAuiSimpleTabArt_GetBestTabCtrlSize(wxAuiSimpleTabArt* self, wxWindow* wnd,
                                                    wxAuiNotebookPageArray* pages, int width,
                                                    int height)
    {
        return self->GetBestTabCtrlSize(wnd, *pages, wxSize(width, height));
    }

    /* wxAuiManager - public member */

    EXPORT void* wxAuiManager_Create(wxWindow* _managed_wnd, int _flags)
    {
        return (void*) new wxAuiManager(_managed_wnd, _flags);
    }

    EXPORT bool wxAuiManager_DetachPane(wxAuiManager* self, wxWindow* _window)
    {
        return self->DetachPane(_window);
    }

// BUGBUG: [Randalphwa - 10-13-2024] C functions cannot return a class.
#if 0
    EXPORT wxAuiPaneInfoArray wxAuiManager_GetAllPanes(wxAuiManager* self)
    {
        return self->GetAllPanes();
    }
#endif

    EXPORT void* wxAuiManager_GetArtProvider(wxAuiManager* self)
    {
        return (void*) self->GetArtProvider();
    }

    EXPORT void wxAuiManager_GetDockSizeConstraint(wxAuiManager* self, double* widthpct,
                                                   double* heightpct)
    {
        self->GetDockSizeConstraint(widthpct, heightpct);
    }

    EXPORT int wxAuiManager_GetFlags(wxAuiManager* self)
    {
        return self->GetFlags();
    }

    EXPORT void* wxAuiManager_GetManagedWindow(wxAuiManager* self)
    {
        return (void*) self->GetManagedWindow();
    }

    EXPORT void wxAuiManager_HideHint(wxAuiManager* self)
    {
        self->HideHint();
    }

    EXPORT bool wxAuiManager_InsertPane(wxAuiManager* self, wxWindow* _window,
                                        wxAuiPaneInfo* _insert_location, int _insert_level)
    {
        return self->InsertPane(_window, *_insert_location, _insert_level);
    }

    EXPORT void wxAuiManager_LoadPaneInfo(wxAuiManager* self, wxString* _pane_part,
                                          wxAuiPaneInfo* _pane)
    {
        self->LoadPaneInfo(*_pane_part, *_pane);
    }

    EXPORT bool wxAuiManager_LoadPerspective(wxAuiManager* self, wxString* _perspective,
                                             bool update)
    {
        return self->LoadPerspective(*_perspective, update);
    }

    EXPORT wxString* wxAuiManager_SavePaneInfo(wxAuiManager* self, wxAuiPaneInfo* _pane)
    {
        wxString* result = new wxString();
        *result = self->SavePaneInfo(*_pane);
        return result;
    }

    EXPORT wxString* wxAuiManager_SavePerspective(wxAuiManager* self)
    {
        wxString* result = new wxString();
        *result = self->SavePerspective();
        return result;
    }

    EXPORT void wxAuiManager_SetArtProvider(wxAuiManager* self, wxAuiDockArt* _art_provider)
    {
        self->SetArtProvider(_art_provider);
    }

    EXPORT void wxAuiManager_SetDockSizeConstraint(wxAuiManager* self, double widthpct,
                                                   double heightpct)
    {
        self->SetDockSizeConstraint(widthpct, heightpct);
    }

    EXPORT void wxAuiManager_SetFlags(wxAuiManager* self, int flags)
    {
        self->SetFlags(flags);
    }

    EXPORT void wxAuiManager_SetManagedWindow(wxAuiManager* self, wxWindow* _managed_wnd)
    {
        self->SetManagedWindow(_managed_wnd);
    }

    EXPORT void wxAuiManager_ShowHint(wxAuiManager* self, wxRect* _rect)
    {
        self->ShowHint(*_rect);
    }

    EXPORT void wxAuiManager_UnInit(wxAuiManager* self)
    {
        self->UnInit();
    }

    EXPORT void wxAuiManager_Update(wxAuiManager* self)
    {
        self->Update();
    }

    EXPORT bool wxAuiManager_AddPane(wxAuiManager* self, wxWindow* _window, int _direction,
                                     wxString* _caption)
    {
        return self->AddPane(_window, _direction, *_caption);
    }

    EXPORT bool wxAuiManager_AddPaneByPaneInfo(wxAuiManager* self, wxWindow* _window,
                                               wxAuiPaneInfo* _pane_info)
    {
        return self->AddPane(_window, *_pane_info);
    }

    EXPORT bool wxAuiManager_AddPaneByPaneInfoAndDropPosition(wxAuiManager* self, wxWindow* window,
                                                              wxAuiPaneInfo* paneInfo, int x, int y)
    {
        return self->AddPane(window, *paneInfo, wxPoint(x, y));
    }

    EXPORT wxAuiPaneInfo* wxAuiManager_GetPaneByWindow(wxAuiManager* self, wxWindow* _window)
    {
        wxAuiPaneInfo* info = new wxAuiPaneInfo();
        *info = self->GetPane(_window);
        return info;
    }

    EXPORT wxAuiPaneInfo* wxAuiManager_GetPaneByName(wxAuiManager* self, wxString* id)
    {
        wxAuiPaneInfo* info = new wxAuiPaneInfo();
        *info = self->GetPane(*id);
        return info;
    }

    EXPORT void* wxAuiManager_GetManager(wxWindow* _window)
    {
        return wxAuiManager::GetManager(_window);
    }

    /* wxAuiDockArt */

    EXPORT void wxAuiDockArt_DrawBackground(wxAuiDockArt* self, wxDC* _dc, wxWindow* _window,
                                            int orientation, wxRect* _rect)
    {
        self->DrawBackground(*_dc, _window, orientation, *_rect);
    }

    EXPORT void wxAuiDockArt_DrawBorder(wxAuiDockArt* self, wxDC* _dc, wxWindow* _window,
                                        wxRect* _rect, wxAuiPaneInfo* _pane)
    {
        self->DrawBorder(*_dc, _window, *_rect, *_pane);
    }

    EXPORT void wxAuiDockArt_DrawCaption(wxAuiDockArt* self, wxDC* _dc, wxWindow* _window,
                                         wxString* _text, wxRect* _rect, wxAuiPaneInfo* _pane)
    {
        self->DrawCaption(*_dc, _window, *_text, *_rect, *_pane);
    }

    EXPORT void wxAuiDockArt_DrawGripper(wxAuiDockArt* self, wxDC* _dc, wxWindow* _window,
                                         wxRect* _rect, wxAuiPaneInfo* _pane)
    {
        self->DrawGripper(*_dc, _window, *_rect, *_pane);
    }

    EXPORT void wxAuiDockArt_DrawPaneButton(wxAuiDockArt* self, wxDC* _dc, wxWindow* _window,
                                            int button, int button_state, wxRect* _rect,
                                            wxAuiPaneInfo* _pane)
    {
        self->DrawPaneButton(*_dc, _window, button, button_state, *_rect, *_pane);
    }

    EXPORT void wxAuiDockArt_DrawSash(wxAuiDockArt* self, wxDC* _dc, wxWindow* _window,
                                      int orientation, wxRect* _rect)
    {
        self->DrawSash(*_dc, _window, orientation, *_rect);
    }

    EXPORT wxColour* wxAuiDockArt_GetColour(wxAuiDockArt* self, int id)
    {
        wxColour* colr = new wxColour();
        *colr = self->GetColour(id);
        return colr;
    }

    EXPORT wxFont* wxAuiDockArt_GetFont(wxAuiDockArt* self, int id)
    {
        wxFont* font = new wxFont();
        *font = self->GetFont(id);
        return font;
    }

    EXPORT int wxAuiDockArt_GetMetric(wxAuiDockArt* self, int id)
    {
        return self->GetMetric(id);
    }

    EXPORT void wxAuiDockArt_SetColour(wxAuiDockArt* self, int id, wxColour* _colour)
    {
        self->SetColour(id, *_colour);
    }

    EXPORT void wxAuiDockArt_SetFont(wxAuiDockArt* self, int id, wxFont* _font)
    {
        self->SetFont(id, *_font);
    }

    EXPORT void wxAuiDockArt_SetMetric(wxAuiDockArt* self, int id, int new_val)
    {
        self->SetMetric(id, new_val);
    }

    /* wxAuiPaneInfo */

    EXPORT void* wxAuiPaneInfo_CreateDefault()
    {
        return (void*) new wxAuiPaneInfo();
    }

    EXPORT void* wxAuiPaneInfo_Create(wxAuiPaneInfo* _c)
    {
        return (void*) new wxAuiPaneInfo(*_c);
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Bottom(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Bottom();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_BottomDockable(wxAuiPaneInfo* self, bool b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->BottomDockable(b);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Caption(wxAuiPaneInfo* self, wxString* _c)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Caption(*_c);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_CaptionVisible(wxAuiPaneInfo* self, bool visible)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->CaptionVisible(visible);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_CloseButton(wxAuiPaneInfo* self, bool visible)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->CloseButton(visible);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_DefaultPane(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->DefaultPane();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_DestroyOnClose(wxAuiPaneInfo* self, bool b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->DestroyOnClose(b);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Direction(wxAuiPaneInfo* self, int direction)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Direction(direction);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Dock(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Dock();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_DockFixed(wxAuiPaneInfo* self, bool b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->DockFixed(b);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Dockable(wxAuiPaneInfo* self, bool b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Dockable(b);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Fixed(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Fixed();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Float(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Float();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Floatable(wxAuiPaneInfo* self, bool b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Floatable(b);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Gripper(wxAuiPaneInfo* self, bool visible)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Gripper(visible);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_GripperTop(wxAuiPaneInfo* self, bool attop)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->GripperTop(attop);
        return out;
    }

    EXPORT bool wxAuiPaneInfo_HasBorder(wxAuiPaneInfo* self)
    {
        return self->HasBorder();
    }

    EXPORT bool wxAuiPaneInfo_HasCaption(wxAuiPaneInfo* self)
    {
        return self->HasCaption();
    }

    EXPORT bool wxAuiPaneInfo_HasCloseButton(wxAuiPaneInfo* self)
    {
        return self->HasCloseButton();
    }

    EXPORT bool wxAuiPaneInfo_HasFlag(wxAuiPaneInfo* self, int flag)
    {
        return self->HasFlag(flag);
    }

    EXPORT bool wxAuiPaneInfo_HasGripper(wxAuiPaneInfo* self)
    {
        return self->HasGripper();
    }

    EXPORT bool wxAuiPaneInfo_HasGripperTop(wxAuiPaneInfo* self)
    {
        return self->HasGripperTop();
    }

    EXPORT bool wxAuiPaneInfo_HasMaximizeButton(wxAuiPaneInfo* self)
    {
        return self->HasMaximizeButton();
    }

    EXPORT bool wxAuiPaneInfo_HasMinimizeButton(wxAuiPaneInfo* self)
    {
        return self->HasMinimizeButton();
    }

    EXPORT bool wxAuiPaneInfo_HasPinButton(wxAuiPaneInfo* self)
    {
        return self->HasPinButton();
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Hide(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Hide();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Icon(wxAuiPaneInfo* self, wxBitmap* _b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Icon(*_b);
        return out;
    }

    EXPORT bool wxAuiPaneInfo_IsBottomDockable(wxAuiPaneInfo* self)
    {
        return self->IsBottomDockable();
    }

    EXPORT bool wxAuiPaneInfo_IsDockable(wxAuiPaneInfo* self)
    {
        return self->IsDockable();
    }

    EXPORT bool wxAuiPaneInfo_IsDocked(wxAuiPaneInfo* self)
    {
        return self->IsDocked();
    }

    EXPORT bool wxAuiPaneInfo_IsFixed(wxAuiPaneInfo* self)
    {
        return self->IsFixed();
    }

    EXPORT bool wxAuiPaneInfo_IsFloatable(wxAuiPaneInfo* self)
    {
        return self->IsFloatable();
    }

    EXPORT bool wxAuiPaneInfo_IsFloating(wxAuiPaneInfo* self)
    {
        return self->IsFloating();
    }

    EXPORT bool wxAuiPaneInfo_IsLeftDockable(wxAuiPaneInfo* self)
    {
        return self->IsLeftDockable();
    }

    EXPORT bool wxAuiPaneInfo_IsMovable(wxAuiPaneInfo* self)
    {
        return self->IsMovable();
    }

    EXPORT bool wxAuiPaneInfo_IsOk(wxAuiPaneInfo* self)
    {
        return self->IsOk();
    }

    EXPORT bool wxAuiPaneInfo_IsResizable(wxAuiPaneInfo* self)
    {
        return self->IsResizable();
    }

    EXPORT bool wxAuiPaneInfo_IsRightDockable(wxAuiPaneInfo* self)
    {
        return self->IsRightDockable();
    }

    EXPORT bool wxAuiPaneInfo_IsShown(wxAuiPaneInfo* self)
    {
        return self->IsShown();
    }

    EXPORT bool wxAuiPaneInfo_IsToolbar(wxAuiPaneInfo* self)
    {
        return self->IsToolbar();
    }

    EXPORT bool wxAuiPaneInfo_IsTopDockable(wxAuiPaneInfo* self)
    {
        return self->IsTopDockable();
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Layer(wxAuiPaneInfo* self, int layer)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Layer(layer);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Left(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Left();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_LeftDockable(wxAuiPaneInfo* self, bool b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->LeftDockable(b);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_MaximizeButton(wxAuiPaneInfo* self, bool visible)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->MaximizeButton(visible);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_MinimizeButton(wxAuiPaneInfo* self, bool visible)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->MinimizeButton(visible);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Movable(wxAuiPaneInfo* self, bool b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Movable(b);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Name(wxAuiPaneInfo* self, wxString* _n)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Name(*_n);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_PaneBorder(wxAuiPaneInfo* self, bool visible)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->PaneBorder(visible);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_PinButton(wxAuiPaneInfo* self, bool visible)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->PinButton(visible);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Position(wxAuiPaneInfo* self, int pos)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Position(pos);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Resizable(wxAuiPaneInfo* self, bool resizable)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Resizable(resizable);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Right(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Right();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_RightDockable(wxAuiPaneInfo* self, bool b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->RightDockable(b);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Row(wxAuiPaneInfo* self, int row)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Row(row);
        return out;
    }

    EXPORT void wxAuiPaneInfo_SafeSet(wxAuiPaneInfo* self, wxAuiPaneInfo* source)
    {
        self->SafeSet(*source);
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_SetFlag(wxAuiPaneInfo* self, int flag, bool option_state)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->SetFlag(flag, option_state);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Show(wxAuiPaneInfo* self, bool show)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Show(show);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_ToolbarPane(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->ToolbarPane();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Top(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Top();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_TopDockable(wxAuiPaneInfo* self, bool b)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->TopDockable(b);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Window(wxAuiPaneInfo* self, wxWindow* _w)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Window(_w);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Copy(wxAuiPaneInfo* self, wxAuiPaneInfo* _c)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->operator=(*_c);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_BestSize(wxAuiPaneInfo* self, int width, int height)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->BestSize(wxSize(width, height));
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_BestSizeXY(wxAuiPaneInfo* self, int x, int y)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->BestSize(x, y);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Centre(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Centre();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_Center(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->Center();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_CentrePane(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->CentrePane();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_CenterPane(wxAuiPaneInfo* self)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->CenterPane();
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_FloatingPosition(wxAuiPaneInfo* self, int x, int y)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->FloatingPosition(wxPoint(x, y));
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_FloatingPositionXY(wxAuiPaneInfo* self, int x, int y)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->FloatingPosition(x, y);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_FloatingSize(wxAuiPaneInfo* self, int width, int height)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->FloatingSize(wxSize(width, height));
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_FloatingSizeXY(wxAuiPaneInfo* self, int x, int y)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->FloatingSize(x, y);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_MaxSize(wxAuiPaneInfo* self, int width, int height)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->MaxSize(wxSize(width, height));
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_MaxSizeXY(wxAuiPaneInfo* self, int x, int y)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->MaxSize(x, y);
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_MinSize(wxAuiPaneInfo* self, int width, int height)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->MinSize(wxSize(width, height));
        return out;
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfo_MinSizeXY(wxAuiPaneInfo* self, int x, int y)
    {
        wxAuiPaneInfo* out = new wxAuiPaneInfo();
        *out = self->MinSize(x, y);
        return out;
    }

    /* wxAuiManagerEvent */

    EXPORT void* wxAuiManagerEvent_Create(int type)
    {
        return (void*) new wxAuiManagerEvent(type);
    }

    EXPORT bool wxAuiManagerEvent_CanVeto(wxAuiManagerEvent* self)
    {
        return self->CanVeto();
    }

    EXPORT int wxAuiManagerEvent_GetButton(wxAuiManagerEvent* self)
    {
        return self->GetButton();
    }

    EXPORT wxDC* wxAuiManagerEvent_GetDC(wxAuiManagerEvent* self)
    {
        return self->GetDC();
    }

    EXPORT bool wxAuiManagerEvent_GetVeto(wxAuiManagerEvent* self)
    {
        return self->GetVeto();
    }

    EXPORT void* wxAuiManagerEvent_GetManager(wxAuiManagerEvent* self)
    {
        return (void*) self->GetManager();
    }

    EXPORT void* wxAuiManagerEvent_GetPane(wxAuiManagerEvent* self)
    {
        return (void*) self->GetPane();
    }

    EXPORT void wxAuiManagerEvent_SetButton(wxAuiManagerEvent* self, int button)
    {
        self->SetButton(button);
    }

    EXPORT void wxAuiManagerEvent_SetCanVeto(wxAuiManagerEvent* self, bool can_veto)
    {
        self->SetCanVeto(can_veto);
    }

    EXPORT void wxAuiManagerEvent_SetDC(wxAuiManagerEvent* self, wxDC* pdc)
    {
        self->SetDC(pdc);
    }

    EXPORT void wxAuiManagerEvent_SetManager(wxAuiManagerEvent* self, wxAuiManager* _manager)
    {
        self->SetManager(_manager);
    }

    EXPORT void wxAuiManagerEvent_SetPane(wxAuiManagerEvent* self, wxAuiPaneInfo* _pane)
    {
        self->SetPane(_pane);
    }

    EXPORT void wxAuiManagerEvent_Veto(wxAuiManagerEvent* self, bool veto)
    {
        self->Veto(veto);
    }

    /* wxBookCtrlBase */

    EXPORT bool wxBookCtrlBase_CreateFromDefault(wxAuiNotebook* self, wxWindow* parent, int winid,
                                                 int x, int y, int width, int height, long style)
    {
        return self->Create(parent, winid, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT void wxBookCtrlBase_SetPageSize(wxBookCtrlBase* self, int width, int height)
    {
        self->SetPageSize(wxSize(width, height));
    }

    EXPORT int wxBookCtrlBase_HitTest(wxBookCtrlBase* self, int x, int y, long* flags)
    {
        return self->HitTest(wxPoint(x, y), flags);
    }

    EXPORT int wxBookCtrlBase_GetPageImage(wxBookCtrlBase* self, size_t nPage)
    {
        return self->GetPageImage(nPage);
    }

    EXPORT bool wxBookCtrlBase_SetPageImage(wxBookCtrlBase* self, size_t page, int image)
    {
        return self->SetPageImage(page, image);
    }

    EXPORT wxString* wxBookCtrlBase_GetPageText(wxBookCtrlBase* self, size_t nPage)
    {
        wxString* result = new wxString();
        *result = self->GetPageText(nPage);
        return result;
    }

    EXPORT bool wxBookCtrlBase_SetPageText(wxBookCtrlBase* self, size_t page, wxString* _text)
    {
        return self->SetPageText(page, *_text);
    }

    EXPORT int wxBookCtrlBase_GetSelection(wxBookCtrlBase* self)
    {
        return self->GetSelection();
    }

    EXPORT void* wxBookCtrlBase_GetCurrentPage(wxBookCtrlBase* self)
    {
        return (void*) self->GetCurrentPage();
    }

    EXPORT int wxBookCtrlBase_SetSelection(wxBookCtrlBase* self, size_t page)
    {
        return self->SetSelection(page);
    }

    EXPORT void wxBookCtrlBase_AdvanceSelection(wxBookCtrlBase* self, bool forward)
    {
        self->AdvanceSelection(forward);
    }

    EXPORT int wxBookCtrlBase_ChangeSelection(wxBookCtrlBase* self, size_t page)
    {
        return self->ChangeSelection(page);
    }

    EXPORT int wxBookCtrlBase_FindPage(wxBookCtrlBase* self, wxWindow* _page)
    {
        return self->FindPage(_page);
    }

    EXPORT bool wxBookCtrlBase_AddPage(wxBookCtrlBase* self, wxWindow* _page, wxString* _text,
                                       bool select, int imageId)
    {
        return self->AddPage(_page, *_text, select, imageId);
    }

    EXPORT bool wxBookCtrlBase_DeleteAllPages(wxBookCtrlBase* self)
    {
        return self->DeleteAllPages();
    }

    EXPORT bool wxBookCtrlBase_DeletePage(wxBookCtrlBase* self, size_t page)
    {
        return self->DeletePage(page);
    }

    EXPORT bool wxBookCtrlBase_InsertPage(wxBookCtrlBase* self, size_t index, wxWindow* _page,
                                          wxString* _text, bool select, int imageId)
    {
        return self->InsertPage(index, _page, *_text, select, imageId);
    }

    EXPORT bool wxBookCtrlBase_RemovePage(wxBookCtrlBase* self, size_t page)
    {
        return self->RemovePage(page);
    }

    EXPORT size_t wxBookCtrlBase_GetPageCount(wxBookCtrlBase* self)
    {
        return self->GetPageCount();
    }

    EXPORT void* wxBookCtrlBase_GetPage(wxBookCtrlBase* self, size_t page)
    {
        return (void*) self->GetPage(page);
    }

    EXPORT void wxBookCtrlBase_AssignImageList(wxBookCtrlBase* self, wxImageList* imageList)
    {
        self->AssignImageList(imageList);
    }

    EXPORT void wxBookCtrlBase_SetImageList(wxBookCtrlBase* self, wxImageList* imageList)
    {
        self->SetImageList(imageList);
    }

    EXPORT void* wxBookCtrlBase_GetImageList(wxBookCtrlBase* self)
    {
        return (void*) self->GetImageList();
    }

    /** wxAuiNotebookPage **/
    EXPORT wxWindow* wxAuiNotebookPage_Window(wxAuiNotebookPage* self)
    {
        return self->window;
    }

    EXPORT wxString* wxAuiNotebookPage_Caption(wxAuiNotebookPage* self)
    {
        wxString* result = new wxString();
        *result = self->caption;
        return result;
    }

    EXPORT wxString* wxAuiNotebookPage_Tooltip(wxAuiNotebookPage* self)
    {
        wxString* result = new wxString();
        *result = self->tooltip;
        return result;
    }

    EXPORT wxBitmapBundle* wxAuiNotebookPage_Bitmap(wxAuiNotebookPage* self)
    {
        wxBitmapBundle* result = new wxBitmapBundle();
        *result = self->bitmap;
        return result;
    }

    EXPORT wxRect* wxAuiNotebookPage_Rect(wxAuiNotebookPage* self)
    {
        wxRect* rect = new wxRect();
        *rect = self->rect;
        return rect;
    }

    EXPORT bool wxAuiNotebookPage_Active(wxAuiNotebookPage* self)
    {
        return self->active;
    }

    /** wxAuiNotebookPageArray **/
    /** see wxWidgets dynarray.h for additional array functions **/

    EXPORT wxAuiNotebookPageArray* wxAuiNotebookPageArray_Create()
    {
        return new wxAuiNotebookPageArray();
    }

    EXPORT void wxAuiNotebookPageArray_Delete(wxAuiNotebookPageArray* self)
    {
        delete self;
    }

    EXPORT int wxAuiNotebookPageArray_GetCount(wxAuiNotebookPageArray* self)
    {
        return self->GetCount();
    }

    EXPORT wxAuiNotebookPage* wxAuiNotebookPageArray_Item(wxAuiNotebookPageArray* self, int _idx)
    {
        wxAuiNotebookPage* page = new wxAuiNotebookPage();
        *page = self->Item(_idx);
        return page;
    }

    /** wxAuiToolBarItemArray **/
    /** see wxWidgets dynarray.h for additional array functions **/
    EXPORT wxAuiToolBarItemArray* wxAuiToolBarItemArray_Create()
    {
        return new wxAuiToolBarItemArray();
    }

    EXPORT void wxAuiToolBarItemArray_Delete(wxAuiToolBarItemArray* self)
    {
        delete self;
    }

    EXPORT int wxAuiToolBarItemArray_GetCount(wxAuiToolBarItemArray* self)
    {
        return self->GetCount();
    }

    EXPORT wxAuiToolBarItem* wxAuiToolBarItemArray_Item(wxAuiToolBarItemArray* self, int _idx)
    {
        wxAuiToolBarItem* item = new wxAuiToolBarItem();
        *item = self->Item(_idx);
        return item;
    }
    /** wxAuiPaneInfoArray **/
    /** see wxWidgets dynarray.h for additional array functions **/
    EXPORT wxAuiPaneInfoArray* wxAuiPaneInfoArray_Create()
    {
        return new wxAuiPaneInfoArray();
    }

    EXPORT void wxAuiPaneInfoArray_Delete(wxAuiPaneInfoArray* self)
    {
        delete self;
    }

    EXPORT int wxAuiPaneInfoArray_GetCount(wxAuiPaneInfoArray* self)
    {
        return self->GetCount();
    }

    EXPORT wxAuiPaneInfo* wxAuiPaneInfoArray_Item(wxAuiPaneInfoArray* self, int _idx)
    {
        wxAuiPaneInfo* info = new wxAuiPaneInfo();
        *info = self->Item(_idx);
        return info;
    }
}
