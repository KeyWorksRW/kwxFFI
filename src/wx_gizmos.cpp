#include <wx/string.h>

#include "kwx_wrapper.h"
#include <wx/gizmos/dynamicsash.h>
#include <wx/gizmos/editlbox.h>
#include <wx/gizmos/ledctrl.h>
#include <wx/gizmos/multicell.h>
#include <wx/gizmos/splittree.h>

class kwxSCTreeControl : public wxRemotelyScrolledTreeCtrl
{
private:
    TreeCompareFunc compare_func;
    void* kwxObject;

public:
    kwxSCTreeControl(void* pObject, void* compareFunc, wxWindow* parent, wxWindowID id = -1,
                     const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                     long style = wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT) :
        wxRemotelyScrolledTreeCtrl(parent, id, pos, size, style)
    {
        kwxObject = pObject;
        compare_func = (TreeCompareFunc) compareFunc;
    };

    virtual int OnCompareItems(const wxTreeItemId& item1, const wxTreeItemId& item2)
    {
        return kwxObject ? compare_func(kwxObject, (void*) &item1, (void*) &item2) :
                           wxRemotelyScrolledTreeCtrl::OnCompareItems(item1, item2);
    }
};

extern "C"
{
    EXPORT void* wxDynamicSashWindow_Create(void* parent, int id, int x, int y, int width,
                                            int height, int style)
    {
        return (void*) new wxDynamicSashWindow((wxWindow*) parent, (wxWindowID) id, wxPoint(x, y),
                                               wxSize(width, height), (long) style);
    }

    EXPORT void wxDynamicSashWindow_Delete(void* pObject)
    {
        delete (wxDynamicSashWindow*) pObject;
    }

    EXPORT void* wxDynamicSashWindow_GetHScrollBar(void* pObject, void* child)
    {
        return (void*) ((wxDynamicSashWindow*) pObject)->GetHScrollBar((wxWindow*) child);
    }

    EXPORT void* wxDynamicSashWindow_GetVScrollBar(void* pObject, void* child)
    {
        return (void*) ((wxDynamicSashWindow*) pObject)->GetVScrollBar((wxWindow*) child);
    }

    EXPORT void* wxEditableListBox_Create(void* parent, int id, void* label, int x, int y,
                                          int width, int height, int style)
    {
        return (void*) new wxEditableListBox((wxWindow*) parent, (wxWindowID) id,
                                             wxString::FromAscii((char*) label), wxPoint(x, y),
                                             wxSize(width, height), (long) style);
    }

    EXPORT void wxEditableListBox_SetStrings(void* pObject, void* strings, int count)
    {
        wxArrayString list;

        for (int i = 0; i < count; i++)
        {
            wxString s = wxString::FromAscii(((char**) strings)[i]);
            list.Add(s);
        }

        ((wxEditableListBox*) pObject)->SetStrings(list);
    }

    EXPORT int wxEditableListBox_GetStrings(void* pObject, void* ref)
    {
        wxArrayString list;
        ((wxEditableListBox*) pObject)->GetStrings(list);

        if (ref)
        {
            for (unsigned int i = 0; i < list.GetCount(); i++)
                ((char**) ref)[i] = strdup(list.Item(i).utf8_str());
        }

        return list.GetCount();
    }

    EXPORT void* wxEditableListBox_GetListCtrl(void* pObject)
    {
        return (void*) ((wxEditableListBox*) pObject)->GetListCtrl();
    }

    EXPORT void* wxEditableListBox_GetDelButton(void* pObject)
    {
        return (void*) ((wxEditableListBox*) pObject)->GetDelButton();
    }

    EXPORT void* wxEditableListBox_GetNewButton(void* pObject)
    {
        return (void*) ((wxEditableListBox*) pObject)->GetNewButton();
    }

    EXPORT void* wxEditableListBox_GetUpButton(void* pObject)
    {
        return (void*) ((wxEditableListBox*) pObject)->GetUpButton();
    }

    EXPORT void* wxEditableListBox_GetDownButton(void* pObject)
    {
        return (void*) ((wxEditableListBox*) pObject)->GetDownButton();
    }

    EXPORT void* wxEditableListBox_GetEditButton(void* pObject)
    {
        return (void*) ((wxEditableListBox*) pObject)->GetEditButton();
    }

    EXPORT void* wxLEDNumberCtrl_Create(void* parent, int id, int x, int y, int width, int height,
                                        int style)
    {
        return (void*) new wxLEDNumberCtrl((wxWindow*) parent, (wxWindowID) id, wxPoint(x, y),
                                           wxSize(width, height), (long) style);
    }

    EXPORT int wxLEDNumberCtrl_GetAlignment(void* pObject)
    {
        return (int) ((wxLEDNumberCtrl*) pObject)->GetAlignment();
    }

    EXPORT int wxLEDNumberCtrl_GetDrawFaded(void* pObject)
    {
        return (int) ((wxLEDNumberCtrl*) pObject)->GetDrawFaded();
    }

    EXPORT int wxLEDNumberCtrl_GetValue(void* pObject, void* ref)
    {
        wxString res = ((wxLEDNumberCtrl*) pObject)->GetValue();
        return copyStrToBuf(ref, res);
    }

    EXPORT void wxLEDNumberCtrl_SetAlignment(void* pObject, int Alignment, int Redraw)
    {
        ((wxLEDNumberCtrl*) pObject)->SetAlignment((wxLEDValueAlign) Alignment, Redraw != 0);
    }

    EXPORT void wxLEDNumberCtrl_SetDrawFaded(void* pObject, int DrawFaded, int Redraw)
    {
        ((wxLEDNumberCtrl*) pObject)->SetDrawFaded(DrawFaded != 0, Redraw != 0);
    }

    EXPORT void wxLEDNumberCtrl_SetValue(void* pObject, void* Value, int Redraw)
    {
        ((wxLEDNumberCtrl*) pObject)->SetValue(wxString::FromAscii((char*) Value), Redraw != 0);
    }

    EXPORT void* wxMultiCellItemHandle_Create(int row, int column, int height, int width, int sizeX,
                                              int sizeY, int style, int wx, int wy, int align)
    {
        return (void*) new wxMultiCellItemHandle(row, column, height, width, wxSize(sizeX, sizeY),
                                                 (wxResizable) style, wxSize(wx, wy), align);
    }

    EXPORT void* wxMultiCellItemHandle_CreateWithSize(void* pObject, int row, int column, int sizeX,
                                                      int sizeY, int style, int wx, int wy,
                                                      int align)
    {
        return (void*) new wxMultiCellItemHandle(row, column, wxSize(sizeX, sizeY),
                                                 (wxResizable) style, wxSize(wx, wy), align);
    }

    EXPORT void* wxMultiCellItemHandle_CreateWithStyle(void* pObject, int row, int column,
                                                       int style, int wx, int wy, int align)
    {
        return (void*) new wxMultiCellItemHandle(row, column, (wxResizable) style, wxSize(wx, wy),
                                                 align);
    }

    EXPORT int wxMultiCellItemHandle_GetColumn(void* pObject)
    {
        return ((wxMultiCellItemHandle*) pObject)->GetColumn();
    }

    EXPORT int wxMultiCellItemHandle_GetRow(void* pObject)
    {
        return ((wxMultiCellItemHandle*) pObject)->GetRow();
    }

    EXPORT int wxMultiCellItemHandle_GetWidth(void* pObject)
    {
        return ((wxMultiCellItemHandle*) pObject)->GetWidth();
    }

    EXPORT int wxMultiCellItemHandle_GetHeight(void* pObject)
    {
        return ((wxMultiCellItemHandle*) pObject)->GetHeight();
    }

    EXPORT int wxMultiCellItemHandle_GetStyle(void* pObject)
    {
        return (int) ((wxMultiCellItemHandle*) pObject)->GetStyle();
    }

    EXPORT void wxMultiCellItemHandle_GetLocalSize(void* pObject, void* width, void* height)
    {
        wxSize size = ((wxMultiCellItemHandle*) pObject)->GetLocalSize();
        *((int*) width) = size.x;
        *((int*) height) = size.y;
    }

    EXPORT int wxMultiCellItemHandle_GetAlignment(void* pObject)
    {
        return ((wxMultiCellItemHandle*) pObject)->GetAlignment();
    }

    EXPORT void wxMultiCellItemHandle_GetWeight(void* pObject, void* width, void* height)
    {
        wxSize size = ((wxMultiCellItemHandle*) pObject)->GetWeight();
        *((int*) width) = size.x;
        *((int*) height) = size.y;
    }

    EXPORT void* wxMultiCellSizer_Create(int rows, int cols)
    {
        return (void*) new wxMultiCellSizer(rows, cols);
    }

    EXPORT void wxMultiCellSizer_Delete(void* pObject)
    {
        delete (wxMultiCellSizer*) pObject;
    }

    EXPORT void wxMultiCellSizer_RecalcSizes(void* pObject)
    {
        ((wxMultiCellSizer*) pObject)->RecalcSizes();
    }

    EXPORT void wxMultiCellSizer_CalcMin(void* pObject, void* width, void* height)
    {
        wxSize size = ((wxMultiCellSizer*) pObject)->CalcMin();
        *((int*) width) = size.x;
        *((int*) height) = size.y;
    }

    EXPORT int wxMultiCellSizer_SetDefaultCellSize(void* pObject, int width, int height)
    {
        return (int) ((wxMultiCellSizer*) pObject)->SetDefaultCellSize(wxSize(width, height));
    }

    EXPORT int wxMultiCellSizer_SetColumnWidth(void* pObject, int column, int colSize,
                                               int expandable)
    {
        return (int) ((wxMultiCellSizer*) pObject)
            ->SetColumnWidth(column, colSize, expandable != 0);
    }

    EXPORT int wxMultiCellSizer_SetRowHeight(void* pObject, int row, int rowSize, int expandable)
    {
        return (int) ((wxMultiCellSizer*) pObject)->SetRowHeight(row, rowSize, expandable != 0);
    }

    EXPORT int wxMultiCellSizer_EnableGridLines(void* pObject, void* win)
    {
        return (int) ((wxMultiCellSizer*) pObject)->EnableGridLines((wxWindow*) win);
    }

    EXPORT int wxMultiCellSizer_SetGridPen(void* pObject, void* pen)
    {
        return (int) ((wxMultiCellSizer*) pObject)->SetGridPen((wxPen*) pen);
    }

    EXPORT void* wxMultiCellCanvas_Create(void* parent, int numRows, int numCols)
    {
        return (void*) new wxMultiCellCanvas((wxWindow*) parent, numRows, numCols);
    }

    EXPORT void wxMultiCellCanvas_Add(void* pObject, void* win, int row, int col)
    {
        ((wxMultiCellCanvas*) pObject)
            ->Add((wxWindow*) win, (unsigned int) row, (unsigned int) col);
    }

    EXPORT int wxMultiCellCanvas_MaxRows(void* pObject)
    {
        return ((wxMultiCellCanvas*) pObject)->MaxRows();
    }

    EXPORT int wxMultiCellCanvas_MaxCols(void* pObject)
    {
        return ((wxMultiCellCanvas*) pObject)->MaxCols();
    }

    EXPORT void wxMultiCellCanvas_CalculateConstraints(void* pObject)
    {
        ((wxMultiCellCanvas*) pObject)->CalculateConstraints();
    }

    EXPORT void wxMultiCellCanvas_SetMinCellSize(void* pObject, int width, int height)
    {
        ((wxMultiCellCanvas*) pObject)->SetMinCellSize(wxSize(width, height));
    }

    EXPORT void* wxSplitterScrolledWindow_Create(void* parent, int id, int x, int y, int width,
                                                 int height, int style)
    {
        return (void*) new wxSplitterScrolledWindow((wxWindow*) parent, (wxWindowID) id,
                                                    wxPoint(x, y), wxSize(width, height),
                                                    (long) style);
    }

    EXPORT void* wxThinSplitterWindow_Create(void* parent, int id, int x, int y, int width,
                                             int height, int style)
    {
        return (void*) new wxThinSplitterWindow((wxWindow*) parent, (wxWindowID) id, wxPoint(x, y),
                                                wxSize(width, height), (long) style);
    }

    EXPORT void wxThinSplitterWindow_SizeWindows(void* pObject)
    {
        ((wxThinSplitterWindow*) pObject)->SizeWindows();
    }

    EXPORT int wxThinSplitterWindow_SashHitTest(void* pObject, int x, int y, int tolerance)
    {
        return (int) ((wxThinSplitterWindow*) pObject)->SashHitTest(x, y, tolerance);
    }

    EXPORT void wxThinSplitterWindow_DrawSash(void* pObject, void* dc)
    {
        ((wxThinSplitterWindow*) pObject)->DrawSash(*((wxDC*) dc));
    }

    EXPORT void* wxTreeCompanionWindow_Create(void* parent, int id, int x, int y, int width,
                                              int height, int style)
    {
        return (void*) new wxTreeCompanionWindow((wxWindow*) parent, (wxWindowID) id, wxPoint(x, y),
                                                 wxSize(width, height), (long) style);
    }

    EXPORT void wxTreeCompanionWindow_DrawItem(void* pObject, void* dc, void* id, int x, int y,
                                               int width, int height)
    {
        ((wxTreeCompanionWindow*) pObject)
            ->DrawItem(*((wxDC*) dc), *((wxTreeItemId*) id), wxRect(x, y, width, height));
    }

    EXPORT void* wxTreeCompanionWindow_GetTreeCtrl(void* pObject)
    {
        return (void*) ((wxTreeCompanionWindow*) pObject)->GetTreeCtrl();
    }

    EXPORT void wxTreeCompanionWindow_SetTreeCtrl(void* pObject, void* treeCtrl)
    {
        ((wxTreeCompanionWindow*) pObject)->SetTreeCtrl((wxRemotelyScrolledTreeCtrl*) treeCtrl);
    }

    EXPORT void* wxRemotelyScrolledTreeCtrl_Create(void* pObject, void* compareFunc, void* parent,
                                                   int id, int x, int y, int width, int height,
                                                   int style)
    {
        return (void*) new kwxSCTreeControl(pObject, compareFunc, (wxWindow*) parent,
                                            (wxWindowID) id, wxPoint(x, y), wxSize(width, height),
                                            (long) style);
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_Delete(void* pObject)
    {
        delete (kwxSCTreeControl*) pObject;
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_SetScrollbars(void* pObject, int pixelsPerUnitX,
                                                         int pixelsPerUnitY, int noUnitsX,
                                                         int noUnitsY, int xPos, int yPos,
                                                         int noRefresh)
    {
        ((kwxSCTreeControl*) pObject)
            ->SetScrollbars(pixelsPerUnitX, pixelsPerUnitY, noUnitsX, noUnitsY, xPos, yPos,
                            noRefresh != 0);
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_GetViewStart(void* pObject, void* x, void* y)
    {
        ((kwxSCTreeControl*) pObject)->GetViewStart((int*) x, (int*) y);
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_PrepareDC(void* pObject, void* dc)
    {
        ((kwxSCTreeControl*) pObject)->PrepareDC(*((wxDC*) dc));
    }

    EXPORT int wxRemotelyScrolledTreeCtrl_GetScrollPos(void* pObject, int orient)
    {
        return ((kwxSCTreeControl*) pObject)->GetScrollPos(orient);
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_HideVScrollbar(void* pObject)
    {
        ((kwxSCTreeControl*) pObject)->HideVScrollbar();
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_CalcTreeSize(void* pObject, void* x, void* y,
                                                        void* width, void* height)
    {
        wxRect rect;
        ((kwxSCTreeControl*) pObject)->CalcTreeSize(rect);
        *((int*) x) = rect.x;
        *((int*) y) = rect.y;
        *((int*) width) = rect.width;
        *((int*) height) = rect.height;
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_CalcTreeSizeItem(void* pObject, void* id, void* x,
                                                            void* y, void* width, void* height)
    {
        wxRect rect;
        ((kwxSCTreeControl*) pObject)->CalcTreeSize(*((wxTreeItemId*) id), rect);
        *((int*) x) = rect.x;
        *((int*) y) = rect.y;
        *((int*) width) = rect.width;
        *((int*) height) = rect.height;
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_AdjustRemoteScrollbars(void* pObject)
    {
        ((kwxSCTreeControl*) pObject)->AdjustRemoteScrollbars();
    }

    EXPORT void* wxRemotelyScrolledTreeCtrl_GetScrolledWindow(void* pObject)
    {
        return (void*) ((kwxSCTreeControl*) pObject)->GetScrolledWindow();
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_ScrollToLine(void* pObject, int posHoriz, int posVert)
    {
        ((kwxSCTreeControl*) pObject)->ScrollToLine(posHoriz, posVert);
    }

    EXPORT void wxRemotelyScrolledTreeCtrl_SetCompanionWindow(void* pObject, void* companion)
    {
        ((kwxSCTreeControl*) pObject)->SetCompanionWindow((wxWindow*) companion);
    }

    EXPORT void* wxRemotelyScrolledTreeCtrl_GetCompanionWindow(void* pObject)
    {
        return (void*) ((kwxSCTreeControl*) pObject)->GetCompanionWindow();
    }
}
