#include "kwx_wrapper.h"

extern "C"
{
    EXPORT void wxHtmlListBox_RefreshRow(wxHtmlListBox* self, size_t line)
    {
        self->RefreshRow(line);
    }

    EXPORT void wxHtmlListBox_RefreshRows(wxHtmlListBox* self, size_t from, size_t toPos)
    {
        self->RefreshRows(from, toPos);
    }

    EXPORT void wxHtmlListBox_RefreshAll(wxHtmlListBox* self)
    {
        self->RefreshAll();
    }

    EXPORT void wxHtmlListBox_SetItemCount(wxHtmlListBox* self, size_t count)
    {
        self->SetItemCount(count);
    }

    EXPORT wxFileSystem* wxHtmlListBox_GetFileSystem(wxHtmlListBox* self)
    {
        return &self->GetFileSystem();
    }

    EXPORT wxHTMLDataObject* wxHTMLDataObject_Create(wxString* html)
    {
        return new wxHTMLDataObject(*html);
    }

    EXPORT void wxHTMLDataObject_Delete(wxHTMLDataObject* self)
    {
        delete self;
    }

    EXPORT wxString* wxHTMLDataObject_GetHTML(wxHTMLDataObject* self)
    {
        return new wxString(self->GetHTML());
    }

    EXPORT void wxHTMLDataObject_SetHTML(wxHTMLDataObject* self, wxString* html)
    {
        self->SetHTML(*html);
    }

    EXPORT size_t wxHTMLDataObject_GetLength(wxHTMLDataObject* self)
    {
        return self->GetLength();
    }

    EXPORT wxHtmlCell* wxHtmlCell_Create()
    {
        return new wxHtmlCell();
    }

    EXPORT void wxHtmlCell_Delete(wxHtmlCell* self)
    {
        delete self;
    }

    EXPORT void wxHtmlCell_SetParent(wxHtmlCell* self, void* parent)
    {
        self->SetParent(static_cast<wxHtmlContainerCell*>(parent));
    }

    EXPORT void* wxHtmlCell_GetParent(wxHtmlCell* self)
    {
        return self->GetParent();
    }

    EXPORT int wxHtmlCell_GetPosX(wxHtmlCell* self)
    {
        return self->GetPosX();
    }

    EXPORT int wxHtmlCell_GetPosY(wxHtmlCell* self)
    {
        return self->GetPosY();
    }

    EXPORT int wxHtmlCell_GetWidth(wxHtmlCell* self)
    {
        return self->GetWidth();
    }

    EXPORT int wxHtmlCell_GetMaxTotalWidth(wxHtmlCell* self)
    {
        return self->GetMaxTotalWidth();
    }

    EXPORT int wxHtmlCell_GetHeight(wxHtmlCell* self)
    {
        return self->GetHeight();
    }

    EXPORT int wxHtmlCell_GetDescent(wxHtmlCell* self)
    {
        return self->GetDescent();
    }

    EXPORT void wxHtmlCell_SetCanLiveOnPagebreak(wxHtmlCell* self, bool can)
    {
        self->SetCanLiveOnPagebreak(can);
    }

    EXPORT bool wxHtmlCell_IsLinebreakAllowed(wxHtmlCell* self)
    {
        return self->IsLinebreakAllowed();
    }

    EXPORT bool wxHtmlCell_IsTerminalCell(wxHtmlCell* self)
    {
        return self->IsTerminalCell();
    }

    EXPORT void wxHtmlCell_SetScriptMode(wxHtmlCell* self, int mode, long previousBase)
    {
        self->SetScriptMode(static_cast<wxHtmlScriptMode>(mode), previousBase);
    }

    EXPORT int wxHtmlCell_GetScriptMode(wxHtmlCell* self)
    {
        return static_cast<int>(self->GetScriptMode());
    }

    EXPORT long wxHtmlCell_GetScriptBaseline(wxHtmlCell* self)
    {
        return self->GetScriptBaseline();
    }

    EXPORT bool wxHtmlCell_IsFormattingCell(wxHtmlCell* self)
    {
        return self->IsFormattingCell();
    }

    EXPORT wxString* wxHtmlCell_GetId(wxHtmlCell* self)
    {
        return new wxString(self->GetId());
    }

    EXPORT bool wxHtmlCell_HasId(wxHtmlCell* self)
    {
        return self->HasId();
    }

    EXPORT void wxHtmlCell_SetId(wxHtmlCell* self, wxString* id)
    {
        self->SetId(*id);
    }

    EXPORT void* wxHtmlCell_GetLink(wxHtmlCell* self, int x, int y)
    {
        return self->GetLink(x, y);
    }

    EXPORT void* wxHtmlCell_GetNext(wxHtmlCell* self)
    {
        return self->GetNext();
    }

    EXPORT void* wxHtmlCell_GetFirstChild(wxHtmlCell* self)
    {
        return self->GetFirstChild();
    }

    EXPORT void wxHtmlCell_SetPos(wxHtmlCell* self, int x, int y)
    {
        self->SetPos(x, y);
    }

    EXPORT void wxHtmlCell_SetLink(wxHtmlCell* self, void* link)
    {
        self->SetLink(*static_cast<const wxHtmlLinkInfo*>(link));
    }

    EXPORT void wxHtmlCell_SetNext(wxHtmlCell* self, void* cell)
    {
        self->SetNext(static_cast<wxHtmlCell*>(cell));
    }

    EXPORT void wxHtmlCell_Layout(wxHtmlCell* self, int width)
    {
        self->Layout(width);
    }

    EXPORT void* wxHtmlCell_FindCellByPos(wxHtmlCell* self, int x, int y, unsigned flags)
    {
        return self->FindCellByPos(x, y, flags);
    }

    EXPORT wxPoint* wxHtmlCell_GetAbsPos(wxHtmlCell* self, void* rootCell)
    {
        return new wxPoint(self->GetAbsPos(static_cast<const wxHtmlCell*>(rootCell)));
    }

    EXPORT wxRect* wxHtmlCell_GetRect(wxHtmlCell* self, void* rootCell)
    {
        return new wxRect(self->GetRect(static_cast<const wxHtmlCell*>(rootCell)));
    }

    EXPORT void* wxHtmlCell_GetRootCell(wxHtmlCell* self)
    {
        return self->GetRootCell();
    }

    EXPORT void* wxHtmlCell_GetFirstTerminal(wxHtmlCell* self)
    {
        return self->GetFirstTerminal();
    }

    EXPORT void* wxHtmlCell_GetLastTerminal(wxHtmlCell* self)
    {
        return self->GetLastTerminal();
    }

    EXPORT unsigned wxHtmlCell_GetDepth(wxHtmlCell* self)
    {
        return self->GetDepth();
    }

    EXPORT bool wxHtmlCell_IsBefore(wxHtmlCell* self, void* cell)
    {
        return self->IsBefore(static_cast<wxHtmlCell*>(cell));
    }

    EXPORT wxString* wxHtmlCell_ConvertToText(wxHtmlCell* self, void* sel)
    {
        return new wxString(self->ConvertToText(static_cast<wxHtmlSelection*>(sel)));
    }

    EXPORT wxString* wxHtmlCell_Dump(wxHtmlCell* self, int indent)
    {
        return new wxString(self->Dump(indent));
    }

    EXPORT void* wxHtmlCellEvent_GetCell(wxHtmlCellEvent* self)
    {
        return self->GetCell();
    }

    EXPORT wxPoint* wxHtmlCellEvent_GetPoint(wxHtmlCellEvent* self)
    {
        return new wxPoint(self->GetPoint());
    }

    EXPORT wxMouseEvent* wxHtmlCellEvent_GetMouseEvent(wxHtmlCellEvent* self)
    {
        return new wxMouseEvent(self->GetMouseEvent());
    }

    EXPORT void wxHtmlCellEvent_SetLinkClicked(wxHtmlCellEvent* self, bool linkClicked)
    {
        self->SetLinkClicked(linkClicked);
    }

    EXPORT bool wxHtmlCellEvent_GetLinkClicked(wxHtmlCellEvent* self)
    {
        return self->GetLinkClicked();
    }

    EXPORT void* wxHtmlLinkEvent_GetLinkInfo(wxHtmlLinkEvent* self)
    {
        return const_cast<wxHtmlLinkInfo*>(&self->GetLinkInfo());
    }
}
