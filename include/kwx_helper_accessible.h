#pragma once

// kwxAccessible — callback-based window accessibility object.
//
// The hook derives from wxWindowAccessible, not from wxAccessible directly.
// wxAccessible (MSW wx/msw/ole/access.h) inherits wxAccessibleBase, whose
// HitTest/GetLocation/Navigate/GetName/GetChildCount/GetChild/GetParent/
// GetFocus all return wxACC_NOT_IMPLEMENTED. wxWindowAccessible (wx/window.h)
// overrides every one of them with real implementations that enumerate
// GetWindow()->GetChildren() and navigate that tree. Deriving from it is what
// makes a partial hook useful: any method without a callback falls back to real
// window enumeration instead of reporting "not implemented", so a binding that
// installs only a GetName callback still gets a navigable accessible object.
//
// Construction installs the object on the window, exactly as
// wxWindowAccessible's own constructor does (it calls win->SetAccessible(this)),
// so the window owns the object from then on -- wxAccessible_Delete relies on
// that ownership to avoid a double free.
//
// wxWidgets only declares wxAccessible on MSW (wx/access.h includes
// wx/msw/ole/access.h there). Every other platform exposes only
// wxAccessibleBase, so the alias below mirrors the one in kwx_accessible.h and
// keeps this header compiling on GTK and macOS builds. wxUSE_ACCESSIBILITY is 0
// on those platforms, so the whole guarded block, alias included, compiles to
// nothing there.
//
// kwxgen skips preprocessor lines, so the guard does not hide the declarations
// from the binding generator. With wxUSE_ACCESSIBILITY off the class compiles to
// nothing and src/wx_accessible.cpp contains no code.

#if wxUSE_ACCESSIBILITY

// wxWindowAccessible is declared in wx/window.h. kwx_wrapper.h already pulls
// that in, but the base class is this header's central dependency, so name it
// instead of relying on transitive inclusion.
    #include <wx/window.h>

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

    // The callback stores a UTF-8 string in *name; the wrapper copies it into the
    // wxString that wxWidgets supplied. The copy is made immediately, so a buffer passed
    // to kwxAccString_SetValue only has to stay valid for the duration of that call and
    // may be freed as soon as it returns.
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

    // selections receives a wxVariant* the callback fills in: leave it untouched for
    // "no selection", or set it to a "long" holding one selected child id, or build a
    // list of ids with wxVariant_NullList / wxVariant_Append. wxWidgets' own MSW
    // bridge is the authority for those three shapes (src/msw/ole/access.cpp).
    typedef int (*AccGetSelectionsFunc)(void* pObject, void* selections);

    // Uniform single-thunk form: a runtime with exactly one native 3-argument
    // void thunk installs every accessibility hook by handing each SetOn…WithData
    // setter that one thunk plus a distinct token.
    typedef void (*AccWithDataFunc)(void* data, void* arg1, void* arg2);
}

class kwxAccessible : public wxWindowAccessible
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
    AccGetSelectionsFunc m_get_selections_func;

    // Uniform single-thunk form: one thunk plus one per-hook token per hook, so a
    // runtime with a single native void thunk can install every hook.
    AccWithDataFunc m_hit_test_hook;
    void* m_hit_test_hook_data;
    AccWithDataFunc m_get_location_hook;
    void* m_get_location_hook_data;
    AccWithDataFunc m_navigate_hook;
    void* m_navigate_hook_data;
    AccWithDataFunc m_get_name_hook;
    void* m_get_name_hook_data;
    AccWithDataFunc m_get_child_count_hook;
    void* m_get_child_count_hook_data;
    AccWithDataFunc m_get_child_hook;
    void* m_get_child_hook_data;
    AccWithDataFunc m_get_parent_hook;
    void* m_get_parent_hook_data;
    AccWithDataFunc m_do_default_action_hook;
    void* m_do_default_action_hook_data;
    AccWithDataFunc m_get_default_action_hook;
    void* m_get_default_action_hook_data;
    AccWithDataFunc m_get_description_hook;
    void* m_get_description_hook_data;
    AccWithDataFunc m_get_help_text_hook;
    void* m_get_help_text_hook_data;
    AccWithDataFunc m_get_keyboard_shortcut_hook;
    void* m_get_keyboard_shortcut_hook_data;
    AccWithDataFunc m_get_role_hook;
    void* m_get_role_hook_data;
    AccWithDataFunc m_get_state_hook;
    void* m_get_state_hook_data;
    AccWithDataFunc m_get_value_hook;
    void* m_get_value_hook_data;
    AccWithDataFunc m_select_hook;
    void* m_select_hook_data;
    AccWithDataFunc m_get_focus_hook;
    void* m_get_focus_hook_data;
    AccWithDataFunc m_get_selections_hook;
    void* m_get_selections_hook_data;

    // Result published by the hook callback that is running right now. The status pair
    // is cleared before every hook invocation, so a callback that publishes nothing
    // falls back to the base-class implementation, and the out-value fields below are
    // read only when the published status is wxACC_OK.
    int m_hook_status;
    bool m_hook_status_published;
    int m_hit_test_child_id;
    void* m_hit_test_child_object;
    int m_location_x;
    int m_location_y;
    int m_location_width;
    int m_location_height;
    int m_navigate_to_id;
    void* m_navigate_to_object;
    int m_child_count_result;
    void* m_child_result;
    void* m_parent_result;
    int m_role_result;
    int m_state_result;
    int m_focus_child_id;
    void* m_focus_child_object;

    void ResetHookResult();
    void CallStringHook(AccWithDataFunc pFunction, void* data, int childId, wxString* result);

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
    void SetOnGetSelections(void* pFunction)
    {
        m_get_selections_func = (AccGetSelectionsFunc) pFunction;
    }

    // Uniform single-thunk form. Each setter stores the one thunk plus the token the
    // callback receives as its first argument; a NULL pFunction clears the hook.
    void SetOnHitTestWithData(void* pFunction, void* data)
    {
        m_hit_test_hook = (AccWithDataFunc) pFunction;
        m_hit_test_hook_data = data;
    }
    void SetOnGetLocationWithData(void* pFunction, void* data)
    {
        m_get_location_hook = (AccWithDataFunc) pFunction;
        m_get_location_hook_data = data;
    }
    void SetOnNavigateWithData(void* pFunction, void* data)
    {
        m_navigate_hook = (AccWithDataFunc) pFunction;
        m_navigate_hook_data = data;
    }
    void SetOnGetNameWithData(void* pFunction, void* data)
    {
        m_get_name_hook = (AccWithDataFunc) pFunction;
        m_get_name_hook_data = data;
    }
    void SetOnGetChildCountWithData(void* pFunction, void* data)
    {
        m_get_child_count_hook = (AccWithDataFunc) pFunction;
        m_get_child_count_hook_data = data;
    }
    void SetOnGetChildWithData(void* pFunction, void* data)
    {
        m_get_child_hook = (AccWithDataFunc) pFunction;
        m_get_child_hook_data = data;
    }
    void SetOnGetParentWithData(void* pFunction, void* data)
    {
        m_get_parent_hook = (AccWithDataFunc) pFunction;
        m_get_parent_hook_data = data;
    }
    void SetOnDoDefaultActionWithData(void* pFunction, void* data)
    {
        m_do_default_action_hook = (AccWithDataFunc) pFunction;
        m_do_default_action_hook_data = data;
    }
    void SetOnGetDefaultActionWithData(void* pFunction, void* data)
    {
        m_get_default_action_hook = (AccWithDataFunc) pFunction;
        m_get_default_action_hook_data = data;
    }
    void SetOnGetDescriptionWithData(void* pFunction, void* data)
    {
        m_get_description_hook = (AccWithDataFunc) pFunction;
        m_get_description_hook_data = data;
    }
    void SetOnGetHelpTextWithData(void* pFunction, void* data)
    {
        m_get_help_text_hook = (AccWithDataFunc) pFunction;
        m_get_help_text_hook_data = data;
    }
    void SetOnGetKeyboardShortcutWithData(void* pFunction, void* data)
    {
        m_get_keyboard_shortcut_hook = (AccWithDataFunc) pFunction;
        m_get_keyboard_shortcut_hook_data = data;
    }
    void SetOnGetRoleWithData(void* pFunction, void* data)
    {
        m_get_role_hook = (AccWithDataFunc) pFunction;
        m_get_role_hook_data = data;
    }
    void SetOnGetStateWithData(void* pFunction, void* data)
    {
        m_get_state_hook = (AccWithDataFunc) pFunction;
        m_get_state_hook_data = data;
    }
    void SetOnGetValueWithData(void* pFunction, void* data)
    {
        m_get_value_hook = (AccWithDataFunc) pFunction;
        m_get_value_hook_data = data;
    }
    void SetOnSelectWithData(void* pFunction, void* data)
    {
        m_select_hook = (AccWithDataFunc) pFunction;
        m_select_hook_data = data;
    }
    void SetOnGetFocusWithData(void* pFunction, void* data)
    {
        m_get_focus_hook = (AccWithDataFunc) pFunction;
        m_get_focus_hook_data = data;
    }
    void SetOnGetSelectionsWithData(void* pFunction, void* data)
    {
        m_get_selections_hook = (AccWithDataFunc) pFunction;
        m_get_selections_hook_data = data;
    }

    void SetHookResult(int result)
    {
        m_hook_status = result;
        m_hook_status_published = true;
    }
    void SetHitTestResult(int childId, void* childObject)
    {
        m_hit_test_child_id = childId;
        m_hit_test_child_object = childObject;
    }
    void SetGetLocationResult(int xPos, int yPos, int rectWidth, int rectHeight)
    {
        m_location_x = xPos;
        m_location_y = yPos;
        m_location_width = rectWidth;
        m_location_height = rectHeight;
    }
    void SetNavigateResult(int toId, void* toObject)
    {
        m_navigate_to_id = toId;
        m_navigate_to_object = toObject;
    }
    void SetGetChildCountResult(int childCount) { m_child_count_result = childCount; }
    void SetGetChildResult(void* child) { m_child_result = child; }
    void SetGetParentResult(void* parent) { m_parent_result = parent; }
    void SetGetRoleResult(int role) { m_role_result = role; }
    void SetGetStateResult(int state) { m_state_result = state; }
    void SetGetFocusResult(int childId, void* child)
    {
        m_focus_child_id = childId;
        m_focus_child_object = child;
    }

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
    wxAccStatus GetSelections(wxVariant* selections) override;
};

#endif  // wxUSE_ACCESSIBILITY
