#pragma once

// kwxComboCtrl / kwxOwnerDrawnComboBox / popup helpers.
//
// wxComboCtrl and wxOwnerDrawnComboBox dispatch their customisation through
// protected virtuals that a foreign language cannot override, so these classes
// forward them to C callbacks stored as void*. This is the same shape as
// kwxAccessible in kwx_helper_accessible.h.
//
// The two popup classes are concrete wxComboPopup implementations: Create() is
// pure virtual in wxComboPopup, so a binding cannot supply a popup of its own.
// Each popup owns the control it shows (GetControl() returns it) and the class
// itself is the wxComboPopup, which keeps the handle valid for
// wxComboCtrl_SetPopupControl().

// Called when the drop-down button is clicked. pObject is the value passed to
// kwxComboCtrl_CreateDefault() / kwxComboCtrl_CreateWith().
typedef void (*ComboCtrlVoidFunc)(void* pObject);

// AnimateShow(): rect is in screen coordinates. Return 1 when the popup has
// finished showing immediately, 0 when the caller has to call DoShowPopup().
typedef int (*ComboCtrlAnimateShowFunc)(void* pObject, int x, int y, int width, int height,
                                        int flags);

typedef void (*ComboCtrlDoShowPopupFunc)(void* pObject, int x, int y, int width, int height,
                                         int flags);

// popup is a wxComboPopup*. An empty callback is the supported way to suppress
// the wxWidgets assertion for a combo with a custom button action.
typedef void (*ComboCtrlSetPopupControlFunc)(void* pObject, void* popup);

// dc is a wxDC* and rect a wxRect*; both are only valid for the duration of the
// call — a caller must not retain them. item may be wxNOT_FOUND when painting
// the control itself.
typedef void (*ComboDrawItemFunc)(void* pObject, void* dc, void* rect, int item, int flags);

// Returns the item height/width; return -1 for the wxWidgets default.
typedef int (*ComboMeasureItemFunc)(void* pObject, size_t item);

class kwxComboCtrl : public wxComboCtrl
{
private:
    void* m_object;
    ComboCtrlVoidFunc m_button_click_func;
    ComboCtrlAnimateShowFunc m_animate_show_func;
    ComboCtrlSetPopupControlFunc m_set_popup_control_func;
    ComboCtrlDoShowPopupFunc m_do_show_popup_func;

public:
    kwxComboCtrl(void* pObject);
    kwxComboCtrl(void* pObject, wxWindow* parent, wxWindowID id, const wxString& value,
                 const wxPoint& pos, const wxSize& size, long style);

    void SetOnButtonClick(void* pFunction) { m_button_click_func = (ComboCtrlVoidFunc) pFunction; }
    void SetOnAnimateShow(void* pFunction)
    {
        m_animate_show_func = (ComboCtrlAnimateShowFunc) pFunction;
    }
    void SetOnDoSetPopupControl(void* pFunction)
    {
        m_set_popup_control_func = (ComboCtrlSetPopupControlFunc) pFunction;
    }
    void SetOnDoShowPopup(void* pFunction)
    {
        m_do_show_popup_func = (ComboCtrlDoShowPopupFunc) pFunction;
    }

protected:
    void OnButtonClick() override;
    bool AnimateShow(const wxRect& rect, int flags) override;
    void DoSetPopupControl(wxComboPopup* popup) override;
    void DoShowPopup(const wxRect& rect, int flags) override;
};

class kwxOwnerDrawnComboBox : public wxOwnerDrawnComboBox
{
private:
    void* m_object;
    ComboDrawItemFunc m_draw_item_func;
    ComboDrawItemFunc m_draw_background_func;
    ComboMeasureItemFunc m_measure_item_func;
    ComboMeasureItemFunc m_measure_item_width_func;

public:
    kwxOwnerDrawnComboBox(void* pObject);
    kwxOwnerDrawnComboBox(void* pObject, wxWindow* parent, wxWindowID id, const wxString& value,
                          const wxPoint& pos, const wxSize& size, long style);

    void SetOnDrawItem(void* pFunction) { m_draw_item_func = (ComboDrawItemFunc) pFunction; }
    void SetOnDrawBackground(void* pFunction)
    {
        m_draw_background_func = (ComboDrawItemFunc) pFunction;
    }
    void SetOnMeasureItem(void* pFunction)
    {
        m_measure_item_func = (ComboMeasureItemFunc) pFunction;
    }
    void SetOnMeasureItemWidth(void* pFunction)
    {
        m_measure_item_width_func = (ComboMeasureItemFunc) pFunction;
    }

protected:
    void OnDrawItem(wxDC& dc, const wxRect& rect, int item, int flags) const override;
    void OnDrawBackground(wxDC& dc, const wxRect& rect, int item, int flags) const override;
    wxCoord OnMeasureItem(size_t item) const override;
    wxCoord OnMeasureItemWidth(size_t item) const override;
};

class kwxListViewComboPopup : public wxComboPopup
{
public:
    kwxListViewComboPopup();

    void Init() override;
    bool Create(wxWindow* parent) override;
    wxWindow* GetControl() override;
    void SetStringValue(const wxString& value) override;
    wxString GetStringValue() const override;

    // Item helpers. The wrapped wxListView is reachable only through these.
    void AddString(const wxString& item);
    int GetItemCount() const;

protected:
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseLeftDown(wxMouseEvent& event);

    wxListView* m_listView;
    int m_value;    // selected item
    int m_itemHere; // hot item
};

class kwxTreeCtrlComboPopup : public wxComboPopup
{
public:
    kwxTreeCtrlComboPopup();

    void Init() override;
    bool Create(wxWindow* parent) override;
    wxWindow* GetControl() override;
    void OnPopup() override;
    wxSize GetAdjustedSize(int minWidth, int prefHeight, int maxHeight) override;
    void SetStringValue(const wxString& value) override;
    wxString GetStringValue() const override;

    wxTreeItemId FindItemByText(wxTreeItemId parent, const wxString& text);

    // Item helpers. The wrapped wxTreeCtrl is reachable only through these.
    wxTreeItemId AddRoot(const wxString& text);
    wxTreeItemId AppendItem(wxTreeItemId parent, const wxString& text);

protected:
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseLeftDown(wxMouseEvent& event);

    wxTreeCtrl* m_treeCtrl;
    wxTreeItemId m_value;    // selected item
    wxTreeItemId m_itemHere; // hot item
};
