#include "wrapper.h"

extern "C"
{
    EXPORT bool wxTopLevelWindow_EnableCloseButton(wxTopLevelWindow* self, bool enable)
    {
        return self->EnableCloseButton(enable);
    }

    EXPORT void* wxTopLevelWindow_GetDefaultButton(wxTopLevelWindow* self)
    {
        return (void*) self->GetDefaultItem();
    }

    EXPORT void* wxTopLevelWindow_GetDefaultItem(wxTopLevelWindow* self)
    {
        return (void*) self->GetDefaultItem();
    }

    EXPORT void* wxTopLevelWindow_GetIcon(wxTopLevelWindow* self)
    {
        static wxIcon tmp = self->GetIcon();
        return (void*) &tmp;
    }

    EXPORT wxString* wxTopLevelWindow_GetTitle(wxTopLevelWindow* self)
    {
        wxString* result = new wxString();
        *result = self->GetTitle();
        return result;
    }

    EXPORT void wxTopLevelWindow_Iconize(wxTopLevelWindow* self, bool iconize)
    {
        ((wxTopLevelWindow*) self)->Iconize(iconize);
    }

    EXPORT bool wxTopLevelWindow_IsActive(wxTopLevelWindow* self)
    {
        return self->IsActive();
    }

    EXPORT bool wxTopLevelWindow_IsIconized(wxTopLevelWindow* self)
    {
        return self->IsIconized();
    }

    EXPORT bool wxTopLevelWindow_IsMaximized(wxTopLevelWindow* self)
    {
        return self->IsMaximized();
    }

    EXPORT void wxTopLevelWindow_Maximize(void* self, bool iconize)
    {
        ((wxTopLevelWindow*) self)->Maximize(iconize);
    }

    EXPORT void wxTopLevelWindow_RequestUserAttention(void* self, int flags)
    {
        ((wxTopLevelWindow*) self)->RequestUserAttention(flags);
    }

    EXPORT void wxTopLevelWindow_SetDefaultButton(void* self, void* item)
    {
        ((wxTopLevelWindow*) self)->SetDefaultItem((wxButton*) item);
    }

    EXPORT void wxTopLevelWindow_SetDefaultItem(void* self, wxWindow* item)
    {
        ((wxTopLevelWindow*) self)->SetDefaultItem(item);
    }

    EXPORT void wxTopLevelWindow_SetIcon(void* self, wxIcon* icons)
    {
        ((wxTopLevelWindow*) self)->SetIcon(*icons);
    }

    EXPORT void wxTopLevelWindow_SetIcons(void* self, void* icons)
    {
        ((wxTopLevelWindow*) self)->SetIcons(*((wxIconBundle*) icons));
    }

    EXPORT void wxTopLevelWindow_SetMaxSize(void* self, int width, int height)
    {
        ((wxTopLevelWindow*) self)->SetMaxSize(wxSize(width, height));
    }

    EXPORT void wxTopLevelWindow_SetMinSize(void* self, int width, int height)
    {
        ((wxTopLevelWindow*) self)->SetMinSize(wxSize(width, height));
    }

    EXPORT void wxTopLevelWindow_SetTitle(void* self, wxString* title)
    {
        ((wxTopLevelWindow*) self)->SetTitle(*title);
    }

    EXPORT wxFrame* wxFrame_Create(wxWindow* parent, int id, wxString* title, int x, int y,
                                   int width, int height, int style)
    {
        return new wxFrame(parent, id, *title, wxPoint(x, y), wxSize(width, height), style);
    }

    EXPORT wxStatusBar* wxFrame_CreateStatusBar(wxFrame* self, int number, int style)
    {
        return self->CreateStatusBar(number, style, 1);
    }

    EXPORT void wxFrame_Maximize(wxFrame* self)
    {
        self->Maximize();
    }

    EXPORT void wxFrame_Restore(wxFrame* self)
    {
        self->Restore();
    }

    EXPORT void wxFrame_Iconize(wxFrame* self)
    {
        self->Iconize();
    }

    EXPORT bool wxFrame_IsMaximized(wxFrame* self)
    {
        return self->IsMaximized();
    }

    EXPORT bool wxFrame_IsIconized(wxFrame* self)
    {
        return self->IsIconized();
    }

    EXPORT void* wxFrame_GetIcon(wxFrame* self)
    {
        static wxIcon icon;
        icon = self->GetIcon();
        return (void*) &icon;
    }

    EXPORT void wxFrame_SetIcon(wxFrame* self, wxIcon* icon)
    {
        self->SetIcon(*icon);
    }

    EXPORT int wxFrame_GetClientAreaOrigin_left(wxFrame* self)
    {
        return self->GetClientAreaOrigin().x;
    }

    EXPORT int wxFrame_GetClientAreaOrigin_top(wxFrame* self)
    {
        return self->GetClientAreaOrigin().y;
    }

    EXPORT void wxFrame_SetMenuBar(wxFrame* self, wxMenuBar* menubar)
    {
        self->SetMenuBar(menubar);
    }

    EXPORT wxMenuBar* wxFrame_GetMenuBar(wxFrame* self)
    {
        return self->GetMenuBar();
    }

    EXPORT wxStatusBar* wxFrame_GetStatusBar(wxFrame* self)
    {
        return self->GetStatusBar();
    }

    EXPORT void wxFrame_SetStatusBar(wxFrame* self, wxStatusBar* statBar)
    {
        self->SetStatusBar(statBar);
    }

    EXPORT void wxFrame_SetStatusText(wxFrame* self, wxString* text, int number)
    {
        self->SetStatusText(*text, number);
    }

    EXPORT void wxFrame_SetStatusWidths(wxFrame* self, int count, void* widths)
    {
        self->SetStatusWidths(count, (int*) widths);
    }

    EXPORT void* wxFrame_CreateToolBar(wxFrame* self, long style)
    {
        return (void*) self->CreateToolBar(style, 1);
    }

    EXPORT void* wxFrame_GetToolBar(wxFrame* self)
    {
        return (void*) self->GetToolBar();
    }

    EXPORT void wxFrame_SetToolBar(wxFrame* self, wxToolBar* toolbar)
    {
        self->SetToolBar(toolbar);
    }

    EXPORT void wxTopLevelWindow_CenterOnScreen(wxTopLevelWindow* self, int direction)
    {
        self->CentreOnScreen(direction);
    }
}
