#include "wrapper.h"
#include <wx/vscroll.h>

extern "C"
{
    // For wxVScrolledWindow, the user needs to override OnGetRowHeight().
    // We'll provide base class wrappers for the common functionality.

    // wxVScrolledWindow - Note: This is an abstract class in wxWidgets
    // Users typically subclass it. We provide the basic navigation methods.

    EXPORT bool wxVScrolledWindow_Create(wxVScrolledWindow* self, wxWindow* parent, int id, int x,
                                         int y, int width, int height, long style, wxString* name)
    {
        return self->Create(parent, id, wxPoint(x, y), wxSize(width, height), style,
                            name ? *name : wxString(wxPanelNameStr));
    }

    EXPORT size_t wxVScrolledWindow_GetRowCount(wxVScrolledWindow* self)
    {
        return self->GetRowCount();
    }

    EXPORT size_t wxVScrolledWindow_GetVisibleRowsBegin(wxVScrolledWindow* self)
    {
        return self->GetVisibleRowsBegin();
    }

    EXPORT size_t wxVScrolledWindow_GetVisibleRowsEnd(wxVScrolledWindow* self)
    {
        return self->GetVisibleRowsEnd();
    }

    EXPORT bool wxVScrolledWindow_IsRowVisible(wxVScrolledWindow* self, size_t row)
    {
        return self->IsRowVisible(row);
    }

    EXPORT void wxVScrolledWindow_RefreshRow(wxVScrolledWindow* self, size_t row)
    {
        self->RefreshRow(row);
    }

    EXPORT void wxVScrolledWindow_RefreshRows(wxVScrolledWindow* self, size_t from, size_t to)
    {
        self->RefreshRows(from, to);
    }

    EXPORT bool wxVScrolledWindow_ScrollRowPages(wxVScrolledWindow* self, int pages)
    {
        return self->ScrollRowPages(pages);
    }

    EXPORT bool wxVScrolledWindow_ScrollRows(wxVScrolledWindow* self, int rows)
    {
        return self->ScrollRows(rows);
    }

    EXPORT bool wxVScrolledWindow_ScrollToRow(wxVScrolledWindow* self, size_t row)
    {
        return self->ScrollToRow(row);
    }

    EXPORT void wxVScrolledWindow_SetRowCount(wxVScrolledWindow* self, size_t rowCount)
    {
        self->SetRowCount(rowCount);
    }

    // wxHScrolledWindow

    EXPORT bool wxHScrolledWindow_Create(wxHScrolledWindow* self, wxWindow* parent, int id, int x,
                                         int y, int width, int height, long style, wxString* name)
    {
        return self->Create(parent, id, wxPoint(x, y), wxSize(width, height), style,
                            name ? *name : wxString(wxPanelNameStr));
    }

    EXPORT size_t wxHScrolledWindow_GetColumnCount(wxHScrolledWindow* self)
    {
        return self->GetColumnCount();
    }

    EXPORT size_t wxHScrolledWindow_GetVisibleColumnsBegin(wxHScrolledWindow* self)
    {
        return self->GetVisibleColumnsBegin();
    }

    EXPORT size_t wxHScrolledWindow_GetVisibleColumnsEnd(wxHScrolledWindow* self)
    {
        return self->GetVisibleColumnsEnd();
    }

    EXPORT bool wxHScrolledWindow_IsColumnVisible(wxHScrolledWindow* self, size_t column)
    {
        return self->IsColumnVisible(column);
    }

    EXPORT void wxHScrolledWindow_RefreshColumn(wxHScrolledWindow* self, size_t column)
    {
        self->RefreshColumn(column);
    }

    EXPORT void wxHScrolledWindow_RefreshColumns(wxHScrolledWindow* self, size_t from, size_t to)
    {
        self->RefreshColumns(from, to);
    }

    EXPORT bool wxHScrolledWindow_ScrollColumnPages(wxHScrolledWindow* self, int pages)
    {
        return self->ScrollColumnPages(pages);
    }

    EXPORT bool wxHScrolledWindow_ScrollColumns(wxHScrolledWindow* self, int columns)
    {
        return self->ScrollColumns(columns);
    }

    EXPORT bool wxHScrolledWindow_ScrollToColumn(wxHScrolledWindow* self, size_t column)
    {
        return self->ScrollToColumn(column);
    }

    EXPORT void wxHScrolledWindow_SetColumnCount(wxHScrolledWindow* self, size_t columnCount)
    {
        self->SetColumnCount(columnCount);
    }

    // wxHVScrolledWindow combines both

    EXPORT bool wxHVScrolledWindow_Create(wxHVScrolledWindow* self, wxWindow* parent, int id, int x,
                                          int y, int width, int height, long style, wxString* name)
    {
        return self->Create(parent, id, wxPoint(x, y), wxSize(width, height), style,
                            name ? *name : wxString(wxPanelNameStr));
    }

    EXPORT void wxHVScrolledWindow_RefreshRowColumn(wxHVScrolledWindow* self, size_t row,
                                                    size_t column)
    {
        self->RefreshRowColumn(wxPosition(row, column));
    }

    EXPORT void wxHVScrolledWindow_RefreshRowsColumns(wxHVScrolledWindow* self, size_t fromRow,
                                                      size_t toRow, size_t fromCol, size_t toCol)
    {
        self->RefreshRowsColumns(wxPosition(fromRow, fromCol), wxPosition(toRow, toCol));
    }

    EXPORT bool wxHVScrolledWindow_ScrollToRowColumn(wxHVScrolledWindow* self, size_t row,
                                                     size_t column)
    {
        return self->ScrollToRowColumn(wxPosition(row, column));
    }
}
