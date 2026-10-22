#pragma once

// kwxAccessible — callback-based wxAccessible implementation.
//
// wxWidgets only declares wxAccessible on MSW (wx/access.h includes
// wx/msw/ole/access.h there). Every other platform exposes only
// wxAccessibleBase, so the alias below mirrors the one in kwx_accessible.h and
// keeps this header compiling on GTK and macOS builds.
//
// kwxgen skips preprocessor lines, so the guard does not hide the declarations
// from the binding generator. With wxUSE_ACCESSIBILITY off the class compiles to
// nothing and src/wx_accessible.cpp contains no code.

#if wxUSE_ACCESSIBILITY

    #if !defined(__WXMSW__)
using wxAccessible = wxAccessibleBase;
    #endif

extern "C"
{
    // Each callback receives the pObject passed to wxAccessible_Create and
    // returns one of the wxAccStatus values (wxACC_OK, wxACC_FALSE, wxACC_FAIL,
    // wxACC_NOT_SUPPORTED, ...).

    // x and y are screen coordinates. childObject receives a wxAccessible*.
    typedef int (*AccHitTestFunc)(void* pObject, int x, int y, int* childId, void** childObject);

    // rect is a wxRect* in screen coordinates; the callback fills it in.
    typedef int (*AccGetLocationFunc)(void* pObject, void* rect, int elementId);

    typedef int (*AccNavigateFunc)(void* pObject, int navDir, int fromId, int* toId,
                                   void** toObject);

    // The callback stores a UTF-8 string in *name; the wrapper copies it into
    // the wxString that wxWidgets supplied.
    typedef int (*AccStringFunc)(void* pObject, int childId, void* name);

    typedef int (*AccGetChildCountFunc)(void* pObject, int* childCount);

    // child receives a wxAccessible*. A null child with wxACC_OK means the
    // child is a simple element rather than an accessible object.
    typedef int (*AccGetChildFunc)(void* pObject, int childId, void** child);

    typedef int (*AccGetParentFunc)(void* pObject, void** parent);
    typedef int (*AccDoDefaultActionFunc)(void* pObject, int childId);

    // role receives a wxAccRole value.
    typedef int (*AccGetRoleFunc)(void* pObject, int childId, int* role);

    // state receives a combination of wxACC_STATE_SYSTEM_* values.
    typedef int (*AccGetStateFunc)(void* pObject, int childId, long* state);

    // selectFlags is a combination of wxACC_SEL_* values.
    typedef int (*AccSelectFunc)(void* pObject, int childId, int selectFlags);

    typedef int (*AccGetFocusFunc)(void* pObject, int* childId, void** child);
}

class kwxAccessible : public wxAccessible
{
private:
    void* m_object;
    AccHitTestFunc m_hit_test_func;
    AccGetLocationFunc m_get_location_func;
    AccNavigateFunc m_navigate_func;
    AccStringFunc m_get_name_func;
    AccGetChildCountFunc m_get_child_count_func;
    AccGetChildFunc m_get_child_func;
    AccGetParentFunc m_get_parent_func;
    AccDoDefaultActionFunc m_do_default_action_func;
    AccStringFunc m_get_default_action_func;
    AccStringFunc m_get_description_func;
    AccStringFunc m_get_help_text_func;
    AccStringFunc m_get_keyboard_shortcut_func;
    AccGetRoleFunc m_get_role_func;
    AccGetStateFunc m_get_state_func;
    AccStringFunc m_get_value_func;
    AccSelectFunc m_select_func;
    AccGetFocusFunc m_get_focus_func;

public:
    kwxAccessible(wxWindow* window, void* pObject);

    void SetOnHitTest(void* pFunction) { m_hit_test_func = (AccHitTestFunc) pFunction; }
    void SetOnGetLocation(void* pFunction) { m_get_location_func = (AccGetLocationFunc) pFunction; }
    void SetOnNavigate(void* pFunction) { m_navigate_func = (AccNavigateFunc) pFunction; }
    void SetOnGetName(void* pFunction) { m_get_name_func = (AccStringFunc) pFunction; }
    void SetOnGetChildCount(void* pFunction)
    {
        m_get_child_count_func = (AccGetChildCountFunc) pFunction;
    }
    void SetOnGetChild(void* pFunction) { m_get_child_func = (AccGetChildFunc) pFunction; }
    void SetOnGetParent(void* pFunction) { m_get_parent_func = (AccGetParentFunc) pFunction; }
    void SetOnDoDefaultAction(void* pFunction)
    {
        m_do_default_action_func = (AccDoDefaultActionFunc) pFunction;
    }
    void SetOnGetDefaultAction(void* pFunction)
    {
        m_get_default_action_func = (AccStringFunc) pFunction;
    }
    void SetOnGetDescription(void* pFunction)
    {
        m_get_description_func = (AccStringFunc) pFunction;
    }
    void SetOnGetHelpText(void* pFunction) { m_get_help_text_func = (AccStringFunc) pFunction; }
    void SetOnGetKeyboardShortcut(void* pFunction)
    {
        m_get_keyboard_shortcut_func = (AccStringFunc) pFunction;
    }
    void SetOnGetRole(void* pFunction) { m_get_role_func = (AccGetRoleFunc) pFunction; }
    void SetOnGetState(void* pFunction) { m_get_state_func = (AccGetStateFunc) pFunction; }
    void SetOnGetValue(void* pFunction) { m_get_value_func = (AccStringFunc) pFunction; }
    void SetOnSelect(void* pFunction) { m_select_func = (AccSelectFunc) pFunction; }
    void SetOnGetFocus(void* pFunction) { m_get_focus_func = (AccGetFocusFunc) pFunction; }

    wxAccStatus HitTest(const wxPoint& pt, int* childId, wxAccessible** childObject) override;
    wxAccStatus GetLocation(wxRect& rect, int elementId) override;
    wxAccStatus Navigate(wxNavDir navDir, int fromId, int* toId, wxAccessible** toObject) override;
    wxAccStatus GetName(int childId, wxString* name) override;
    wxAccStatus GetChildCount(int* childCount) override;
    wxAccStatus GetChild(int childId, wxAccessible** child) override;
    wxAccStatus GetParent(wxAccessible** parent) override;
    wxAccStatus DoDefaultAction(int childId) override;
    wxAccStatus GetDefaultAction(int childId, wxString* actionName) override;
    wxAccStatus GetDescription(int childId, wxString* description) override;
    wxAccStatus GetHelpText(int childId, wxString* helpText) override;
    wxAccStatus GetKeyboardShortcut(int childId, wxString* shortcut) override;
    wxAccStatus GetRole(int childId, wxAccRole* role) override;
    wxAccStatus GetState(int childId, long* state) override;
    wxAccStatus GetValue(int childId, wxString* strValue) override;
    wxAccStatus Select(int childId, wxAccSelectionFlags selectFlags) override;
    wxAccStatus GetFocus(int* childId, wxAccessible** child) override;
};

#endif  // wxUSE_ACCESSIBILITY
