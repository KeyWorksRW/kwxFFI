// Layout serialization for wxAuiManager and wxAuiNotebook.
//
// wxWidgets 3.3 saves and restores layouts through the abstract
// wxAuiSerializer / wxAuiDeserializer classes.  A foreign language cannot
// derive from them, so the classes below forward every virtual to a void*
// callback, following the same shape as the override hooks in
// src/kwx_hooks.cpp.  The exported functions are declared in
// include/kwx_aui_serializer.h.
//
// Licensed under Apache 2.0. This file is not subject to copyright.

#include "kwx_wrapper.h"

#include <wx/aui/serializer.h>

#include <utility>
#include <vector>

using wxAuiPaneLayoutInfoArray = std::vector<wxAuiPaneLayoutInfo>;
using wxAuiTabLayoutInfoArray = std::vector<wxAuiTabLayoutInfo>;

// Every callback has the fixed three-pointer void shape the language runtimes
// provide.  The pane, tab, name and helper arguments are borrowed handles that
// are valid only while the callback runs.
using SerializerVoidFunc = void (*)(void*, void*, void*);
using SerializerStringFunc = void (*)(void*, void*, void*);
using SerializerPaneFunc = void (*)(void*, void*, void*);
using SerializerTabFunc = void (*)(void*, void*, void*);
using DeserializerPanesFunc = void (*)(void*, void*, void*);
using DeserializerTabsFunc = void (*)(void*, void*, void*);
using DeserializerPaneWindowFunc = void (*)(void*, void*, void*);
using DeserializerOrphanedPageFunc = void (*)(void*, void*, void*);

// A callback that has to return a pointer writes it through this object.
struct kwxAuiCallbackResult
{
    void* pointer = nullptr;
};

// The HandleOrphanedPage() inputs and outputs, passed as one callback argument.
struct kwxAuiOrphanedPage
{
    wxAuiNotebook* book;
    int page;
    wxAuiTabCtrl** tab_ctrl;
    int* tab_index;
    bool result;
};

class kwxAuiSerializer : public wxAuiSerializer
{
public:
    explicit kwxAuiSerializer(void* pObject);

    void SetOnBeforeSave(void* pFunction)
    {
        m_before_save_func = reinterpret_cast<SerializerVoidFunc>(pFunction);
    }
    void SetOnBeforeSavePanes(void* pFunction)
    {
        m_before_save_panes_func = reinterpret_cast<SerializerVoidFunc>(pFunction);
    }
    void SetOnSavePane(void* pFunction)
    {
        m_save_pane_func = reinterpret_cast<SerializerPaneFunc>(pFunction);
    }
    void SetOnAfterSavePanes(void* pFunction)
    {
        m_after_save_panes_func = reinterpret_cast<SerializerVoidFunc>(pFunction);
    }
    void SetOnBeforeSaveNotebooks(void* pFunction)
    {
        m_before_save_notebooks_func = reinterpret_cast<SerializerVoidFunc>(pFunction);
    }
    void SetOnAfterSaveNotebooks(void* pFunction)
    {
        m_after_save_notebooks_func = reinterpret_cast<SerializerVoidFunc>(pFunction);
    }
    void SetOnAfterSave(void* pFunction)
    {
        m_after_save_func = reinterpret_cast<SerializerVoidFunc>(pFunction);
    }
    void SetOnBeforeSaveNotebook(void* pFunction)
    {
        m_before_save_notebook_func = reinterpret_cast<SerializerStringFunc>(pFunction);
    }
    void SetOnSaveNotebookTabControl(void* pFunction)
    {
        m_save_notebook_tab_control_func = reinterpret_cast<SerializerTabFunc>(pFunction);
    }
    void SetOnAfterSaveNotebook(void* pFunction)
    {
        m_after_save_notebook_func = reinterpret_cast<SerializerVoidFunc>(pFunction);
    }

    void BeforeSave() override;
    void BeforeSavePanes() override;
    void SavePane(const wxAuiPaneLayoutInfo& pane) override;
    void AfterSavePanes() override;
    void BeforeSaveNotebooks() override;
    void AfterSaveNotebooks() override;
    void AfterSave() override;
    void BeforeSaveNotebook(const wxString& name) override;
    void SaveNotebookTabControl(const wxAuiTabLayoutInfo& tab_info) override;
    void AfterSaveNotebook() override;

private:
    void* m_object;
    SerializerVoidFunc m_before_save_func;
    SerializerVoidFunc m_before_save_panes_func;
    SerializerPaneFunc m_save_pane_func;
    SerializerVoidFunc m_after_save_panes_func;
    SerializerVoidFunc m_before_save_notebooks_func;
    SerializerVoidFunc m_after_save_notebooks_func;
    SerializerVoidFunc m_after_save_func;
    SerializerStringFunc m_before_save_notebook_func;
    SerializerTabFunc m_save_notebook_tab_control_func;
    SerializerVoidFunc m_after_save_notebook_func;
};

class kwxAuiDeserializer : public wxAuiDeserializer
{
public:
    kwxAuiDeserializer(wxAuiManager* manager, void* pObject);

    void SetOnBeforeLoad(void* pFunction)
    {
        m_before_load_func = reinterpret_cast<SerializerVoidFunc>(pFunction);
    }
    void SetOnLoadPanes(void* pFunction)
    {
        m_load_panes_func = reinterpret_cast<DeserializerPanesFunc>(pFunction);
    }
    void SetOnLoadNotebookTabs(void* pFunction)
    {
        m_load_notebook_tabs_func = reinterpret_cast<DeserializerTabsFunc>(pFunction);
    }
    void SetOnCreatePaneWindow(void* pFunction)
    {
        m_create_pane_window_func = reinterpret_cast<DeserializerPaneWindowFunc>(pFunction);
    }
    void SetOnHandleOrphanedPage(void* pFunction)
    {
        m_handle_orphaned_page_func = reinterpret_cast<DeserializerOrphanedPageFunc>(pFunction);
    }
    void SetOnAfterLoad(void* pFunction)
    {
        m_after_load_func = reinterpret_cast<SerializerVoidFunc>(pFunction);
    }

    void BeforeLoad() override;
    std::vector<wxAuiPaneLayoutInfo> LoadPanes() override;
    wxWindow* CreatePaneWindow(wxAuiPaneInfo& pane) override;
    bool HandleOrphanedPage(wxAuiNotebook& book, int page, wxAuiTabCtrl** tabCtrl,
                            int* tabIndex) override;
    std::vector<wxAuiTabLayoutInfo> LoadNotebookTabs(const wxString& name) override;
    void AfterLoad() override;

private:
    void* m_object;
    SerializerVoidFunc m_before_load_func;
    DeserializerPanesFunc m_load_panes_func;
    DeserializerTabsFunc m_load_notebook_tabs_func;
    DeserializerPaneWindowFunc m_create_pane_window_func;
    DeserializerOrphanedPageFunc m_handle_orphaned_page_func;
    SerializerVoidFunc m_after_load_func;
};

// ---------------------------------------------------------------------------
// kwxAuiSerializer
// ---------------------------------------------------------------------------

kwxAuiSerializer::kwxAuiSerializer(void* pObject) :
    m_object(pObject), m_before_save_func(nullptr), m_before_save_panes_func(nullptr),
    m_save_pane_func(nullptr), m_after_save_panes_func(nullptr),
    m_before_save_notebooks_func(nullptr), m_after_save_notebooks_func(nullptr),
    m_after_save_func(nullptr), m_before_save_notebook_func(nullptr),
    m_save_notebook_tab_control_func(nullptr), m_after_save_notebook_func(nullptr)
{
}

void kwxAuiSerializer::BeforeSave()
{
    if (m_before_save_func)
    {
        m_before_save_func(m_object, nullptr, nullptr);
    }
}

void kwxAuiSerializer::BeforeSavePanes()
{
    if (m_before_save_panes_func)
    {
        m_before_save_panes_func(m_object, nullptr, nullptr);
    }
}

void kwxAuiSerializer::SavePane(const wxAuiPaneLayoutInfo& pane)
{
    if (m_save_pane_func)
    {
        m_save_pane_func(m_object, const_cast<wxAuiPaneLayoutInfo*>(&pane), nullptr);
    }
}

void kwxAuiSerializer::AfterSavePanes()
{
    if (m_after_save_panes_func)
    {
        m_after_save_panes_func(m_object, nullptr, nullptr);
    }
}

void kwxAuiSerializer::BeforeSaveNotebooks()
{
    if (m_before_save_notebooks_func)
    {
        m_before_save_notebooks_func(m_object, nullptr, nullptr);
    }
}

void kwxAuiSerializer::AfterSaveNotebooks()
{
    if (m_after_save_notebooks_func)
    {
        m_after_save_notebooks_func(m_object, nullptr, nullptr);
    }
}

void kwxAuiSerializer::AfterSave()
{
    if (m_after_save_func)
    {
        m_after_save_func(m_object, nullptr, nullptr);
    }
}

void kwxAuiSerializer::BeforeSaveNotebook(const wxString& name)
{
    if (m_before_save_notebook_func)
    {
        m_before_save_notebook_func(m_object, const_cast<wxString*>(&name), nullptr);
    }
}

void kwxAuiSerializer::SaveNotebookTabControl(const wxAuiTabLayoutInfo& tab_info)
{
    if (m_save_notebook_tab_control_func)
    {
        m_save_notebook_tab_control_func(m_object, const_cast<wxAuiTabLayoutInfo*>(&tab_info),
                                         nullptr);
    }
}

void kwxAuiSerializer::AfterSaveNotebook()
{
    if (m_after_save_notebook_func)
    {
        m_after_save_notebook_func(m_object, nullptr, nullptr);
    }
}

// ---------------------------------------------------------------------------
// kwxAuiDeserializer
// ---------------------------------------------------------------------------

kwxAuiDeserializer::kwxAuiDeserializer(wxAuiManager* manager, void* pObject) :
    wxAuiDeserializer(*manager), m_object(pObject), m_before_load_func(nullptr),
    m_load_panes_func(nullptr), m_load_notebook_tabs_func(nullptr),
    m_create_pane_window_func(nullptr), m_handle_orphaned_page_func(nullptr),
    m_after_load_func(nullptr)
{
}

void kwxAuiDeserializer::BeforeLoad()
{
    if (m_before_load_func)
    {
        m_before_load_func(m_object, nullptr, nullptr);
    }
}

std::vector<wxAuiPaneLayoutInfo> kwxAuiDeserializer::LoadPanes()
{
    if (!m_load_panes_func)
    {
        return {};
    }

    kwxAuiCallbackResult result;
    m_load_panes_func(m_object, &result, nullptr);

    wxAuiPaneLayoutInfoArray* array = static_cast<wxAuiPaneLayoutInfoArray*>(result.pointer);
    if (!array)
    {
        return {};
    }

    std::vector<wxAuiPaneLayoutInfo> panes = std::move(*array);
    delete array;
    return panes;
}

wxWindow* kwxAuiDeserializer::CreatePaneWindow(wxAuiPaneInfo& pane)
{
    if (!m_create_pane_window_func)
    {
        return wxAuiDeserializer::CreatePaneWindow(pane);
    }

    kwxAuiCallbackResult result;
    m_create_pane_window_func(m_object, &pane, &result);
    return static_cast<wxWindow*>(result.pointer);
}

bool kwxAuiDeserializer::HandleOrphanedPage(wxAuiNotebook& book, int page, wxAuiTabCtrl** tabCtrl,
                                            int* tabIndex)
{
    if (!m_handle_orphaned_page_func)
    {
        return wxAuiDeserializer::HandleOrphanedPage(book, page, tabCtrl, tabIndex);
    }

    kwxAuiOrphanedPage info { &book, page, tabCtrl, tabIndex, true };
    m_handle_orphaned_page_func(m_object, &info, nullptr);
    return info.result;
}

std::vector<wxAuiTabLayoutInfo> kwxAuiDeserializer::LoadNotebookTabs(const wxString& name)
{
    if (!m_load_notebook_tabs_func)
    {
        return {};
    }

    kwxAuiCallbackResult result;
    m_load_notebook_tabs_func(m_object, const_cast<wxString*>(&name), &result);

    wxAuiTabLayoutInfoArray* array = static_cast<wxAuiTabLayoutInfoArray*>(result.pointer);
    if (!array)
    {
        return {};
    }

    std::vector<wxAuiTabLayoutInfo> tabs = std::move(*array);
    delete array;
    return tabs;
}

void kwxAuiDeserializer::AfterLoad()
{
    if (m_after_load_func)
    {
        m_after_load_func(m_object, nullptr, nullptr);
        return;
    }

    wxAuiDeserializer::AfterLoad();
}

extern "C"
{
    // -----------------------------------------------------------------------
    // wxAuiPaneLayoutInfo
    // -----------------------------------------------------------------------

    EXPORT wxAuiPaneLayoutInfo* wxAuiPaneLayoutInfo_Create(wxString* name)
    {
        return new wxAuiPaneLayoutInfo(*name);
    }

    EXPORT void wxAuiPaneLayoutInfo_Delete(wxAuiPaneLayoutInfo* self)
    {
        delete self;
    }

    EXPORT wxString* wxAuiPaneLayoutInfo_GetName(wxAuiPaneLayoutInfo* self)
    {
        return new wxString(self->name);
    }

    EXPORT int wxAuiPaneLayoutInfo_GetDockDirection(wxAuiPaneLayoutInfo* self)
    {
        return self->dock_direction;
    }

    EXPORT int wxAuiPaneLayoutInfo_GetDockLayer(wxAuiPaneLayoutInfo* self)
    {
        return self->dock_layer;
    }

    EXPORT int wxAuiPaneLayoutInfo_GetDockRow(wxAuiPaneLayoutInfo* self)
    {
        return self->dock_row;
    }

    EXPORT int wxAuiPaneLayoutInfo_GetDockPos(wxAuiPaneLayoutInfo* self)
    {
        return self->dock_pos;
    }

    EXPORT int wxAuiPaneLayoutInfo_GetDockProportion(wxAuiPaneLayoutInfo* self)
    {
        return self->dock_proportion;
    }

    EXPORT int wxAuiPaneLayoutInfo_GetDockSize(wxAuiPaneLayoutInfo* self)
    {
        return self->dock_size;
    }

    EXPORT void wxAuiPaneLayoutInfo_SetDockDirection(wxAuiPaneLayoutInfo* self, int direction)
    {
        self->dock_direction = direction;
    }

    EXPORT void wxAuiPaneLayoutInfo_SetDockLayer(wxAuiPaneLayoutInfo* self, int layer)
    {
        self->dock_layer = layer;
    }

    EXPORT void wxAuiPaneLayoutInfo_SetDockRow(wxAuiPaneLayoutInfo* self, int row)
    {
        self->dock_row = row;
    }

    EXPORT void wxAuiPaneLayoutInfo_SetDockPos(wxAuiPaneLayoutInfo* self, int pos)
    {
        self->dock_pos = pos;
    }

    EXPORT void wxAuiPaneLayoutInfo_SetDockProportion(wxAuiPaneLayoutInfo* self, int proportion)
    {
        self->dock_proportion = proportion;
    }

    EXPORT void wxAuiPaneLayoutInfo_SetDockSize(wxAuiPaneLayoutInfo* self, int size)
    {
        self->dock_size = size;
    }

    EXPORT wxPoint* wxAuiPaneLayoutInfo_GetFloatingPos(wxAuiPaneLayoutInfo* self)
    {
        return new wxPoint(self->floating_pos);
    }

    EXPORT void wxAuiPaneLayoutInfo_SetFloatingPos(wxAuiPaneLayoutInfo* self, int pos_x, int pos_y)
    {
        self->floating_pos = wxPoint(pos_x, pos_y);
    }

    EXPORT wxSize* wxAuiPaneLayoutInfo_GetFloatingSize(wxAuiPaneLayoutInfo* self)
    {
        return new wxSize(self->floating_size);
    }

    EXPORT void wxAuiPaneLayoutInfo_SetFloatingSize(wxAuiPaneLayoutInfo* self, int width,
                                                    int height)
    {
        self->floating_size = wxSize(width, height);
    }

    EXPORT wxSize* wxAuiPaneLayoutInfo_GetFloatingClientSize(wxAuiPaneLayoutInfo* self)
    {
        return new wxSize(self->floating_client_size);
    }

    EXPORT void wxAuiPaneLayoutInfo_SetFloatingClientSize(wxAuiPaneLayoutInfo* self, int width,
                                                          int height)
    {
        self->floating_client_size = wxSize(width, height);
    }

    EXPORT int wxAuiPaneLayoutInfo_IsMaximized(wxAuiPaneLayoutInfo* self)
    {
        return self->is_maximized ? 1 : 0;
    }

    EXPORT void wxAuiPaneLayoutInfo_SetMaximized(wxAuiPaneLayoutInfo* self, int maximized)
    {
        self->is_maximized = maximized != 0;
    }

    EXPORT int wxAuiPaneLayoutInfo_IsHidden(wxAuiPaneLayoutInfo* self)
    {
        return self->is_hidden ? 1 : 0;
    }

    EXPORT void wxAuiPaneLayoutInfo_SetHidden(wxAuiPaneLayoutInfo* self, int hidden)
    {
        self->is_hidden = hidden != 0;
    }

    // -----------------------------------------------------------------------
    // wxAuiTabLayoutInfo
    // -----------------------------------------------------------------------

    EXPORT wxAuiTabLayoutInfo* wxAuiTabLayoutInfo_Create()
    {
        return new wxAuiTabLayoutInfo();
    }

    EXPORT void wxAuiTabLayoutInfo_Delete(wxAuiTabLayoutInfo* self)
    {
        delete self;
    }

    EXPORT int wxAuiTabLayoutInfo_GetDockDirection(wxAuiTabLayoutInfo* self)
    {
        return self->dock_direction;
    }

    EXPORT int wxAuiTabLayoutInfo_GetDockLayer(wxAuiTabLayoutInfo* self)
    {
        return self->dock_layer;
    }

    EXPORT int wxAuiTabLayoutInfo_GetDockRow(wxAuiTabLayoutInfo* self)
    {
        return self->dock_row;
    }

    EXPORT int wxAuiTabLayoutInfo_GetDockPos(wxAuiTabLayoutInfo* self)
    {
        return self->dock_pos;
    }

    EXPORT int wxAuiTabLayoutInfo_GetDockProportion(wxAuiTabLayoutInfo* self)
    {
        return self->dock_proportion;
    }

    EXPORT int wxAuiTabLayoutInfo_GetDockSize(wxAuiTabLayoutInfo* self)
    {
        return self->dock_size;
    }

    EXPORT void wxAuiTabLayoutInfo_SetDockDirection(wxAuiTabLayoutInfo* self, int direction)
    {
        self->dock_direction = direction;
    }

    EXPORT void wxAuiTabLayoutInfo_SetDockLayer(wxAuiTabLayoutInfo* self, int layer)
    {
        self->dock_layer = layer;
    }

    EXPORT void wxAuiTabLayoutInfo_SetDockRow(wxAuiTabLayoutInfo* self, int row)
    {
        self->dock_row = row;
    }

    EXPORT void wxAuiTabLayoutInfo_SetDockPos(wxAuiTabLayoutInfo* self, int pos)
    {
        self->dock_pos = pos;
    }

    EXPORT void wxAuiTabLayoutInfo_SetDockProportion(wxAuiTabLayoutInfo* self, int proportion)
    {
        self->dock_proportion = proportion;
    }

    EXPORT void wxAuiTabLayoutInfo_SetDockSize(wxAuiTabLayoutInfo* self, int size)
    {
        self->dock_size = size;
    }

    EXPORT wxArrayInt* wxAuiTabLayoutInfo_GetPages(wxAuiTabLayoutInfo* self)
    {
        wxArrayInt* pages = new wxArrayInt();
        for (const int page: self->pages)
        {
            pages->Add(page);
        }
        return pages;
    }

    EXPORT void wxAuiTabLayoutInfo_SetPages(wxAuiTabLayoutInfo* self, wxArrayInt* pages)
    {
        self->pages.clear();
        for (size_t index = 0; index < pages->GetCount(); ++index)
        {
            self->pages.push_back(pages->Item(index));
        }
    }

    EXPORT wxArrayInt* wxAuiTabLayoutInfo_GetPinned(wxAuiTabLayoutInfo* self)
    {
        wxArrayInt* pinned = new wxArrayInt();
        for (const int page: self->pinned)
        {
            pinned->Add(page);
        }
        return pinned;
    }

    EXPORT void wxAuiTabLayoutInfo_SetPinned(wxAuiTabLayoutInfo* self, wxArrayInt* pinned)
    {
        self->pinned.clear();
        for (size_t index = 0; index < pinned->GetCount(); ++index)
        {
            self->pinned.push_back(pinned->Item(index));
        }
    }

    EXPORT int wxAuiTabLayoutInfo_GetActive(wxAuiTabLayoutInfo* self)
    {
        return self->active;
    }

    EXPORT void wxAuiTabLayoutInfo_SetActive(wxAuiTabLayoutInfo* self, int active)
    {
        self->active = active;
    }

    // -----------------------------------------------------------------------
    // Layout info arrays
    // -----------------------------------------------------------------------

    EXPORT wxAuiPaneLayoutInfoArray* wxAuiPaneLayoutInfoArray_Create()
    {
        return new wxAuiPaneLayoutInfoArray();
    }

    EXPORT void wxAuiPaneLayoutInfoArray_Delete(wxAuiPaneLayoutInfoArray* self)
    {
        delete self;
    }

    EXPORT int wxAuiPaneLayoutInfoArray_GetCount(wxAuiPaneLayoutInfoArray* self)
    {
        return static_cast<int>(self->size());
    }

    EXPORT void wxAuiPaneLayoutInfoArray_Add(wxAuiPaneLayoutInfoArray* self,
                                             wxAuiPaneLayoutInfo* item)
    {
        self->push_back(*item);
    }

    EXPORT wxAuiPaneLayoutInfo* wxAuiPaneLayoutInfoArray_Item(wxAuiPaneLayoutInfoArray* self,
                                                              int index)
    {
        return new wxAuiPaneLayoutInfo((*self)[static_cast<size_t>(index)]);
    }

    EXPORT wxAuiTabLayoutInfoArray* wxAuiTabLayoutInfoArray_Create()
    {
        return new wxAuiTabLayoutInfoArray();
    }

    EXPORT void wxAuiTabLayoutInfoArray_Delete(wxAuiTabLayoutInfoArray* self)
    {
        delete self;
    }

    EXPORT int wxAuiTabLayoutInfoArray_GetCount(wxAuiTabLayoutInfoArray* self)
    {
        return static_cast<int>(self->size());
    }

    EXPORT void wxAuiTabLayoutInfoArray_Add(wxAuiTabLayoutInfoArray* self, wxAuiTabLayoutInfo* item)
    {
        self->push_back(*item);
    }

    EXPORT wxAuiTabLayoutInfo* wxAuiTabLayoutInfoArray_Item(wxAuiTabLayoutInfoArray* self,
                                                            int index)
    {
        return new wxAuiTabLayoutInfo((*self)[static_cast<size_t>(index)]);
    }

    // -----------------------------------------------------------------------
    // Callback result and orphaned-page helpers
    // -----------------------------------------------------------------------

    EXPORT void kwxAuiCallbackResult_SetPointer(kwxAuiCallbackResult* self, void* value)
    {
        self->pointer = value;
    }

    EXPORT void* kwxAuiCallbackResult_GetPointer(kwxAuiCallbackResult* self)
    {
        return self->pointer;
    }

    EXPORT wxAuiNotebook* kwxAuiOrphanedPage_GetNotebook(kwxAuiOrphanedPage* self)
    {
        return self->book;
    }

    EXPORT int kwxAuiOrphanedPage_GetPage(kwxAuiOrphanedPage* self)
    {
        return self->page;
    }

    EXPORT wxAuiTabCtrl* kwxAuiOrphanedPage_GetTabCtrl(kwxAuiOrphanedPage* self)
    {
        return self->tab_ctrl ? *self->tab_ctrl : nullptr;
    }

    EXPORT void kwxAuiOrphanedPage_SetTabCtrl(kwxAuiOrphanedPage* self, wxAuiTabCtrl* tabCtrl)
    {
        if (self->tab_ctrl)
        {
            *self->tab_ctrl = tabCtrl;
        }
    }

    EXPORT int kwxAuiOrphanedPage_GetTabIndex(kwxAuiOrphanedPage* self)
    {
        return self->tab_index ? *self->tab_index : 0;
    }

    EXPORT void kwxAuiOrphanedPage_SetTabIndex(kwxAuiOrphanedPage* self, int tabIndex)
    {
        if (self->tab_index)
        {
            *self->tab_index = tabIndex;
        }
    }

    EXPORT int kwxAuiOrphanedPage_GetResult(kwxAuiOrphanedPage* self)
    {
        return self->result ? 1 : 0;
    }

    EXPORT void kwxAuiOrphanedPage_SetResult(kwxAuiOrphanedPage* self, int result)
    {
        self->result = result != 0;
    }

    // -----------------------------------------------------------------------
    // kwxAuiSerializer
    // -----------------------------------------------------------------------

    EXPORT void* kwxAuiSerializer_Create(void* pObject)
    {
        return new kwxAuiSerializer(pObject);
    }

    EXPORT void kwxAuiSerializer_Delete(kwxAuiSerializer* self)
    {
        delete self;
    }

    EXPORT void kwxAuiSerializer_SetOnBeforeSave(kwxAuiSerializer* self, void* pFunction)
    {
        self->SetOnBeforeSave(pFunction);
    }

    EXPORT void kwxAuiSerializer_SetOnBeforeSavePanes(kwxAuiSerializer* self, void* pFunction)
    {
        self->SetOnBeforeSavePanes(pFunction);
    }

    EXPORT void kwxAuiSerializer_SetOnSavePane(kwxAuiSerializer* self, void* pFunction)
    {
        self->SetOnSavePane(pFunction);
    }

    EXPORT void kwxAuiSerializer_SetOnAfterSavePanes(kwxAuiSerializer* self, void* pFunction)
    {
        self->SetOnAfterSavePanes(pFunction);
    }

    EXPORT void kwxAuiSerializer_SetOnBeforeSaveNotebooks(kwxAuiSerializer* self, void* pFunction)
    {
        self->SetOnBeforeSaveNotebooks(pFunction);
    }

    EXPORT void kwxAuiSerializer_SetOnAfterSaveNotebooks(kwxAuiSerializer* self, void* pFunction)
    {
        self->SetOnAfterSaveNotebooks(pFunction);
    }

    EXPORT void kwxAuiSerializer_SetOnAfterSave(kwxAuiSerializer* self, void* pFunction)
    {
        self->SetOnAfterSave(pFunction);
    }

    EXPORT void kwxAuiSerializer_SetOnBeforeSaveNotebook(kwxAuiSerializer* self, void* pFunction)
    {
        self->SetOnBeforeSaveNotebook(pFunction);
    }

    EXPORT void kwxAuiSerializer_SetOnSaveNotebookTabControl(kwxAuiSerializer* self,
                                                             void* pFunction)
    {
        self->SetOnSaveNotebookTabControl(pFunction);
    }

    EXPORT void kwxAuiSerializer_SetOnAfterSaveNotebook(kwxAuiSerializer* self, void* pFunction)
    {
        self->SetOnAfterSaveNotebook(pFunction);
    }

    EXPORT void kwxAuiSerializer_BeforeSave(kwxAuiSerializer* self)
    {
        self->BeforeSave();
    }

    EXPORT void kwxAuiSerializer_BeforeSavePanes(kwxAuiSerializer* self)
    {
        self->BeforeSavePanes();
    }

    EXPORT void kwxAuiSerializer_AfterSavePanes(kwxAuiSerializer* self)
    {
        self->AfterSavePanes();
    }

    EXPORT void kwxAuiSerializer_BeforeSaveNotebooks(kwxAuiSerializer* self)
    {
        self->BeforeSaveNotebooks();
    }

    EXPORT void kwxAuiSerializer_AfterSaveNotebooks(kwxAuiSerializer* self)
    {
        self->AfterSaveNotebooks();
    }

    EXPORT void kwxAuiSerializer_AfterSave(kwxAuiSerializer* self)
    {
        self->AfterSave();
    }

    // -----------------------------------------------------------------------
    // kwxAuiDeserializer
    // -----------------------------------------------------------------------

    EXPORT void* kwxAuiDeserializer_Create(wxAuiManager* manager, void* pObject)
    {
        return new kwxAuiDeserializer(manager, pObject);
    }

    EXPORT void kwxAuiDeserializer_Delete(kwxAuiDeserializer* self)
    {
        delete self;
    }

    EXPORT void kwxAuiDeserializer_SetOnBeforeLoad(kwxAuiDeserializer* self, void* pFunction)
    {
        self->SetOnBeforeLoad(pFunction);
    }

    EXPORT void kwxAuiDeserializer_SetOnLoadPanes(kwxAuiDeserializer* self, void* pFunction)
    {
        self->SetOnLoadPanes(pFunction);
    }

    EXPORT void kwxAuiDeserializer_SetOnLoadNotebookTabs(kwxAuiDeserializer* self, void* pFunction)
    {
        self->SetOnLoadNotebookTabs(pFunction);
    }

    EXPORT void kwxAuiDeserializer_SetOnCreatePaneWindow(kwxAuiDeserializer* self, void* pFunction)
    {
        self->SetOnCreatePaneWindow(pFunction);
    }

    EXPORT void kwxAuiDeserializer_SetOnHandleOrphanedPage(kwxAuiDeserializer* self,
                                                           void* pFunction)
    {
        self->SetOnHandleOrphanedPage(pFunction);
    }

    EXPORT void kwxAuiDeserializer_SetOnAfterLoad(kwxAuiDeserializer* self, void* pFunction)
    {
        self->SetOnAfterLoad(pFunction);
    }

    EXPORT void kwxAuiDeserializer_BeforeLoad(kwxAuiDeserializer* self)
    {
        self->BeforeLoad();
    }

    EXPORT void kwxAuiDeserializer_AfterLoad(kwxAuiDeserializer* self)
    {
        self->AfterLoad();
    }

    // -----------------------------------------------------------------------
    // wxAuiManager / wxAuiNotebook layout entry points
    // -----------------------------------------------------------------------

    EXPORT void wxAuiManager_SaveLayout(wxAuiManager* self, kwxAuiSerializer* serializer)
    {
        self->SaveLayout(*serializer);
    }

    EXPORT void wxAuiManager_LoadLayout(wxAuiManager* self, kwxAuiDeserializer* deserializer)
    {
        self->LoadLayout(*deserializer);
    }

    EXPORT void wxAuiNotebook_SaveLayout(wxAuiNotebook* self, wxString* name,
                                         kwxAuiSerializer* serializer)
    {
        self->SaveLayout(*name, *serializer);
    }

    EXPORT void wxAuiNotebook_LoadLayout(wxAuiNotebook* self, wxString* name,
                                         kwxAuiDeserializer* deserializer)
    {
        self->LoadLayout(*name, *deserializer);
    }
}
