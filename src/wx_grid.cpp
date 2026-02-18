// #include "kwx_wrapper.h"

// wxGrid inherits from wxWindow (via wxScrolledCanvas). Additional methods available via:
// wxWindow_* — base window methods (see wx_window.cpp)

#include "kwx_grid.h"

extern "C"
{
    EXPORT wxGridCellCoordsArray* wxGridCellCoordsArray_Create()
    {
        return new wxGridCellCoordsArray();
    }

    EXPORT void wxGridCellCoordsArray_Delete(wxGridCellCoordsArray* self)
    {
        delete self;
    }

    EXPORT int wxGridCellCoordsArray_GetCount(wxGridCellCoordsArray* self)
    {
        return self->GetCount();
    }

    EXPORT void wxGridCellCoordsArray_Item(wxGridCellCoordsArray* self, int index, int* col,
                                           int* row)
    {
        *col = self->Item(index).GetCol();
        *row = self->Item(index).GetRow();
    }

    EXPORT bool wxGridCellEditor_IsCreated(wxGridCellEditor* self)
    {
        return self->IsCreated();
    }

    EXPORT void* wxGridCellEditor_GetControl(wxGridCellEditor* self)
    {
        return (void*) self->GetControl();
    }

    EXPORT void wxGridCellEditor_SetControl(wxGridCellEditor* self, wxControl* control)
    {
        self->SetControl(control);
    }

    EXPORT void wxGridCellEditor_Create(wxGridCellEditor* self, wxWindow* parent, int id,
                                        wxEvtHandler* evtHandler)
    {
        self->Create(parent, (wxWindowID) id, evtHandler);
    }

    EXPORT void wxGridCellEditor_SetSize(wxGridCellEditor* self, int x, int y, int width,
                                         int height)
    {
        self->SetSize(wxRect(x, y, width, height));
    }

    EXPORT void wxGridCellEditor_Show(wxGridCellEditor* self, bool show, void* attr)
    {
        self->Show(show, (wxGridCellAttr*) attr);
    }

    EXPORT void wxGridCellEditor_PaintBackground(wxGridCellEditor* self, wxDC* dc, int x, int y,
                                                 int width, int height, wxGridCellAttr* attr)
    {
        self->PaintBackground(*dc, wxRect(x, y, width, height), *attr);
    }

    EXPORT void wxGridCellEditor_BeginEdit(wxGridCellEditor* self, int row, int col, void* grid)
    {
        self->BeginEdit(row, col, (wxGrid*) grid);
    }

    EXPORT bool wxGridCellEditor_EndEdit(wxGridCellEditor* self, int row, int col, wxGrid* grid,
                                         wxString* oldCell, wxString* newCell)
    {
        return self->EndEdit(row, col, grid, *oldCell, newCell);
    }

    EXPORT void wxGridCellEditor_Reset(wxGridCellEditor* self)
    {
        self->Reset();
    }

    EXPORT bool wxGridCellEditor_IsAcceptedKey(wxGridCellEditor* self, wxKeyEvent* event)
    {
        return self->IsAcceptedKey(*event);
    }

    EXPORT void wxGridCellEditor_StartingKey(wxGridCellEditor* self, wxKeyEvent* event)
    {
        self->StartingKey(*event);
    }

    EXPORT void wxGridCellEditor_StartingClick(wxGridCellEditor* self)
    {
        self->StartingClick();
    }

    EXPORT void wxGridCellEditor_HandleReturn(wxGridCellEditor* self, wxKeyEvent* event)
    {
        self->HandleReturn(*event);
    }

    EXPORT void wxGridCellEditor_Destroy(wxGridCellEditor* self)
    {
        self->Destroy();
    }

    EXPORT void wxGridCellEditor_SetParameters(wxGridCellEditor* self, wxString* params)
    {
        self->SetParameters(*params);
    }

    EXPORT void* wxGridCellTextEditor_Ctor()
    {
        return (void*) new wxGridCellTextEditor();
    }

    EXPORT void* wxGridCellNumberEditor_Ctor(int min, int max)
    {
        return (void*) new wxGridCellNumberEditor(min, max);
    }

    EXPORT void* wxGridCellFloatEditor_Ctor(int width, int precision)
    {
        return (void*) new wxGridCellFloatEditor(width, precision);
    }

    EXPORT void* wxGridCellBoolEditor_Ctor()
    {
        return (void*) new wxGridCellBoolEditor();
    }

    EXPORT void* wxGridCellChoiceEditor_Ctor(int count, void* choices, bool allowOthers)
    {
        wxString items[256];

        for (int i = 0; i < count; i++)
            items[i] = ((char**) choices)[i];

        return (void*) new wxGridCellChoiceEditor(count, items, allowOthers);
    }

    EXPORT void* wxGridCellNumberRenderer_Ctor()
    {
        return (void*) new wxGridCellNumberRenderer();
    }

    EXPORT void* wxGridCellAutoWrapStringRenderer_Ctor()
    {
        return (void*) new wxGridCellAutoWrapStringRenderer();
    }

    EXPORT void* wxGridCellAttr_Ctor()
    {
        return (void*) new wxGridCellAttr();
    }

    EXPORT void wxGridCellAttr_IncRef(wxGridCellAttr* self)
    {
        self->IncRef();
    }

    EXPORT void wxGridCellAttr_DecRef(wxGridCellAttr* self)
    {
        self->DecRef();
    }

    EXPORT void wxGridCellAttr_SetTextColour(wxGridCellAttr* self, wxColour* colText)
    {
        self->SetTextColour(*colText);
    }

    EXPORT void wxGridCellAttr_SetBackgroundColour(wxGridCellAttr* self, wxColour* colBack)
    {
        self->SetBackgroundColour(*colBack);
    }

    EXPORT void wxGridCellAttr_SetFont(wxGridCellAttr* self, wxFont* font)
    {
        self->SetFont(*font);
    }

    EXPORT void wxGridCellAttr_SetAlignment(wxGridCellAttr* self, int hAlign, int vAlign)
    {
        self->SetAlignment(hAlign, vAlign);
    }

    EXPORT void wxGridCellAttr_SetReadOnly(wxGridCellAttr* self, bool isReadOnly)
    {
        self->SetReadOnly(isReadOnly);
    }

    EXPORT void wxGridCellAttr_SetRenderer(wxGridCellAttr* self, void* renderer)
    {
        self->SetRenderer((wxGridCellRenderer*) renderer);
    }

    EXPORT void wxGridCellAttr_SetEditor(wxGridCellAttr* self, wxGridCellEditor* editor)
    {
        self->SetEditor(editor);
    }

    EXPORT bool wxGridCellAttr_HasTextColour(wxGridCellAttr* self)
    {
        return self->HasTextColour();
    }

    EXPORT bool wxGridCellAttr_HasBackgroundColour(wxGridCellAttr* self)
    {
        return self->HasBackgroundColour();
    }

    EXPORT bool wxGridCellAttr_HasFont(wxGridCellAttr* self)
    {
        return self->HasFont();
    }

    EXPORT bool wxGridCellAttr_HasAlignment(wxGridCellAttr* self)
    {
        return self->HasAlignment();
    }

    EXPORT bool wxGridCellAttr_HasRenderer(wxGridCellAttr* self)
    {
        return self->HasRenderer();
    }

    EXPORT bool wxGridCellAttr_HasEditor(wxGridCellAttr* self)
    {
        return self->HasEditor();
    }

    EXPORT void wxGridCellAttr_GetTextColour(wxGridCellAttr* self, wxColour* colour)
    {
        *colour = self->GetTextColour();
    }

    EXPORT void wxGridCellAttr_GetBackgroundColour(wxGridCellAttr* self, wxColour* colour)
    {
        *colour = self->GetBackgroundColour();
    }

    EXPORT void wxGridCellAttr_GetFont(wxGridCellAttr* self, wxFont* font)
    {
        *font = self->GetFont();
    }

    EXPORT void wxGridCellAttr_GetAlignment(wxGridCellAttr* self, int* hAlign, int* vAlign)
    {
        self->GetAlignment(hAlign, vAlign);
    }

    EXPORT void* wxGridCellAttr_GetRenderer(wxGridCellAttr* self, wxGrid* grid, int row, int col)
    {
        return (void*) self->GetRenderer(grid, row, col);
    }

    EXPORT void* wxGridCellAttr_GetEditor(wxGridCellAttr* self, wxGrid* grid, int row, int col)
    {
        return (void*) self->GetEditor(grid, row, col);
    }

    EXPORT bool wxGridCellAttr_IsReadOnly(wxGridCellAttr* self)
    {
        return self->IsReadOnly();
    }

    EXPORT void wxGridCellAttr_SetDefAttr(wxGridCellAttr* self, wxGridCellAttr* defAttr)
    {
        self->SetDefAttr(defAttr);
    }

    EXPORT void* wxGrid_Create(wxWindow* parent, int id, int x, int y, int width, int height,
                               int style)
    {
        return new wxGrid(parent, id, wxPoint(x, y), wxSize(width, height), style | wxWANTS_CHARS);
    }

    EXPORT void wxGrid_CreateGrid(wxGrid* self, int rows, int cols, int selmode)
    {
        self->CreateGrid(rows, cols, (wxGrid::wxGridSelectionModes) selmode);
    }

    EXPORT void wxGrid_SetSelectionMode(wxGrid* self, int selmode)
    {
        self->SetSelectionMode((wxGrid::wxGridSelectionModes) selmode);
    }

    EXPORT int wxGrid_GetNumberRows(wxGrid* self)
    {
        return self->GetNumberRows();
    }

    EXPORT int wxGrid_GetNumberCols(wxGrid* self)
    {
        return self->GetNumberCols();
    }

    EXPORT bool wxGrid_ProcessTableMessage(wxGrid* self, wxGridTableMessage* evt)
    {
        return self->ProcessTableMessage(*evt);
    }

    EXPORT void* wxGrid_GetTable(wxGrid* self)
    {
        return (void*) self->GetTable();
    }

    EXPORT bool wxGrid_SetTable(wxGrid* self, wxGridTableBase* table, bool takeOwnership,
                                int selmode)
    {
        return self->SetTable(table, takeOwnership, (wxGrid::wxGridSelectionModes) selmode);
    }

    EXPORT void wxGrid_ClearGrid(wxGrid* self)
    {
        self->ClearGrid();
    }

    EXPORT bool wxGrid_InsertRows(wxGrid* self, int pos, int numRows, bool updateLabels)
    {
        return self->InsertRows(pos, numRows, updateLabels);
    }

    EXPORT bool wxGrid_AppendRows(wxGrid* self, int numRows, bool updateLabels)
    {
        return self->AppendRows(numRows, updateLabels);
    }

    EXPORT bool wxGrid_DeleteRows(wxGrid* self, int pos, int numRows, bool updateLabels)
    {
        return self->DeleteRows(pos, numRows, updateLabels);
    }

    EXPORT bool wxGrid_InsertCols(wxGrid* self, int pos, int numCols, bool updateLabels)
    {
        return self->InsertCols(pos, numCols, updateLabels);
    }

    EXPORT bool wxGrid_AppendCols(wxGrid* self, int numCols, int updateLabels)
    {
        return self->AppendCols(numCols, updateLabels);
    }

    EXPORT bool wxGrid_DeleteCols(wxGrid* self, int pos, int numCols, bool updateLabels)
    {
        return self->DeleteCols(pos, numCols, updateLabels);
    }

    EXPORT void wxGrid_DrawGridSpace(wxGrid* self, wxDC* dc, wxGridWindow* gridWindow)
    {
        self->DrawGridSpace(*dc, gridWindow);
    }

    EXPORT void wxGrid_DrawCellBorder(wxGrid* self, wxDC* dc, int row, int col)
    {
        self->DrawCellBorder(*dc, wxGridCellCoords(row, col));
    }

    EXPORT void wxGrid_DrawAllGridLines(wxGrid* self)
    {
        self->DrawAllGridLines();
    }

    EXPORT void wxGrid_DrawCell(wxGrid* self, wxDC* dc, int row, int col)
    {
        self->DrawCell(*dc, wxGridCellCoords(row, col));
    }

    EXPORT void wxGrid_DrawCellHighlight(wxGrid* self, wxDC* dc, void* attr)
    {
        self->DrawCellHighlight(*dc, (const wxGridCellAttr*) attr);
    }

    EXPORT void wxGrid_DrawRowLabels(wxGrid* self, wxDC* dc)
    {
        wxArrayInt arr;
        self->DrawRowLabels(*dc, arr);
    }

    EXPORT void wxGrid_DrawRowLabel(wxGrid* self, wxDC* dc, int row)
    {
        self->DrawRowLabel(*dc, row);
    }

    EXPORT void wxGrid_DrawColLabels(wxGrid* self, wxDC* dc)
    {
        wxArrayInt arr;
        self->DrawColLabels(*dc, arr);
    }

    EXPORT void wxGrid_DrawColLabel(wxGrid* self, wxDC* dc, int col)
    {
        self->DrawColLabel(*dc, col);
    }

    EXPORT void wxGrid_DrawTextRectangle(wxGrid* self, wxDC* dc, wxString* txt, int x, int y,
                                         int width, int height, int horizontalAlignment,
                                         int verticalAlignment)
    {
        self->DrawTextRectangle(*dc, *txt, wxRect(x, y, width, height), horizontalAlignment,
                                verticalAlignment);
    }

    EXPORT int wxGrid_StringToLines(wxGrid* self, wxString* value, void* lines)
    {
        int result = 0;
        wxArrayString arr;

        self->StringToLines(*value, arr);

        result = arr.GetCount();

        if (lines)
        {
            for (int i = 0; i < result; i++)
                ((const char**) lines)[i] = strdup(arr[i].utf8_str().data());
        }
        return result;
    }

    EXPORT void wxGrid_GetTextBoxSize(wxGrid* self, wxDC* dc, int count, void* lines, void* width,
                                      void* height)
    {
        wxArrayString arr;

        for (int i = 0; i < count; i++)
            arr[i] = ((char**) lines)[i];

        self->GetTextBoxSize(*dc, arr, (long*) width, (long*) height);
    }

    EXPORT void wxGrid_BeginBatch(wxGrid* self)
    {
        self->BeginBatch();
    }

    EXPORT void wxGrid_EndBatch(wxGrid* self)
    {
        self->EndBatch();
    }

    EXPORT int wxGrid_GetBatchCount(wxGrid* self)
    {
        return self->GetBatchCount();
    }

    EXPORT bool wxGrid_IsEditable(wxGrid* self)
    {
        return self->IsEditable();
    }

    EXPORT void wxGrid_EnableEditing(wxGrid* self, bool edit)
    {
        self->EnableEditing(edit);
    }

    EXPORT void wxGrid_EnableCellEditControl(wxGrid* self, bool enable)
    {
        self->EnableCellEditControl(enable);
    }

    EXPORT void wxGrid_DisableCellEditControl(wxGrid* self)
    {
        self->DisableCellEditControl();
    }

    EXPORT bool wxGrid_CanEnableCellControl(wxGrid* self)
    {
        return self->CanEnableCellControl();
    }

    EXPORT bool wxGrid_IsCellEditControlEnabled(wxGrid* self)
    {
        return self->IsCellEditControlEnabled();
    }

    EXPORT bool wxGrid_IsCellEditControlShown(wxGrid* self)
    {
        return self->IsCellEditControlShown();
    }

    EXPORT bool wxGrid_IsCurrentCellReadOnly(wxGrid* self)
    {
        return self->IsCurrentCellReadOnly();
    }

    EXPORT void wxGrid_ShowCellEditControl(wxGrid* self)
    {
        self->ShowCellEditControl();
    }

    EXPORT void wxGrid_HideCellEditControl(wxGrid* self)
    {
        self->HideCellEditControl();
    }

    EXPORT void wxGrid_SaveEditControlValue(wxGrid* self)
    {
        self->SaveEditControlValue();
    }

    EXPORT void wxGrid_XYToCell(wxGrid* self, int x, int y, int* r, int* c)
    {
        wxGridCellCoords cds;
        self->XYToCell(x, y, cds);
        *r = cds.GetRow();
        *c = cds.GetCol();
    }

    EXPORT int wxGrid_YToRow(wxGrid* self, int y, bool clipToMinMax)
    {
        return self->YToRow(y, clipToMinMax);
    }

    EXPORT int wxGrid_XToCol(wxGrid* self, int x, bool clipToMinMax)
    {
        return self->XToCol(x, clipToMinMax);
    }

    EXPORT int wxGrid_YToEdgeOfRow(wxGrid* self, int y)
    {
        return self->YToEdgeOfRow(y);
    }

    EXPORT int wxGrid_XToEdgeOfCol(wxGrid* self, int x)
    {
        return self->XToEdgeOfCol(x);
    }

    EXPORT wxRect* wxGrid_CellToRect(wxGrid* self, int top, int left, int bottom, int right)
    {
        wxRect* rct = new wxRect();
        *rct =
            self->BlockToDeviceRect(wxGridCellCoords(top, left), wxGridCellCoords(bottom, right));
        return rct;
    }

    EXPORT int wxGrid_GetGridCursorRow(wxGrid* self)
    {
        return self->GetGridCursorRow();
    }

    EXPORT int wxGrid_GetGridCursorCol(wxGrid* self)
    {
        return self->GetGridCursorCol();
    }

    EXPORT bool wxGrid_IsVisible(wxGrid* self, int row, int col, bool wholeCellVisible)
    {
        return self->IsVisible(row, col, wholeCellVisible);
    }

    EXPORT void wxGrid_MakeCellVisible(wxGrid* self, int row, int col)
    {
        self->MakeCellVisible(row, col);
    }

    EXPORT void wxGrid_SetGridCursor(wxGrid* self, int row, int col)
    {
        self->SetGridCursor(row, col);
    }

    EXPORT bool wxGrid_MoveCursorUp(wxGrid* self, bool expandSelection)
    {
        return self->MoveCursorUp(expandSelection);
    }

    EXPORT bool wxGrid_MoveCursorDown(wxGrid* self, bool expandSelection)
    {
        return self->MoveCursorDown(expandSelection);
    }

    EXPORT bool wxGrid_MoveCursorLeft(wxGrid* self, bool expandSelection)
    {
        return self->MoveCursorLeft(expandSelection);
    }

    EXPORT bool wxGrid_MoveCursorRight(wxGrid* self, bool expandSelection)
    {
        return self->MoveCursorRight(expandSelection);
    }

    EXPORT bool wxGrid_MovePageDown(wxGrid* self)
    {
        return self->MovePageDown();
    }

    EXPORT bool wxGrid_MovePageUp(wxGrid* self)
    {
        return self->MovePageUp();
    }

    EXPORT bool wxGrid_MoveCursorUpBlock(wxGrid* self, bool expandSelection)
    {
        return self->MoveCursorUpBlock(expandSelection);
    }

    EXPORT bool wxGrid_MoveCursorDownBlock(wxGrid* self, bool expandSelection)
    {
        return self->MoveCursorDownBlock(expandSelection);
    }

    EXPORT bool wxGrid_MoveCursorLeftBlock(wxGrid* self, bool expandSelection)
    {
        return self->MoveCursorLeftBlock(expandSelection);
    }

    EXPORT bool wxGrid_MoveCursorRightBlock(wxGrid* self, bool expandSelection)
    {
        return self->MoveCursorRightBlock(expandSelection);
    }

    EXPORT int wxGrid_GetDefaultRowLabelSize(wxGrid* self)
    {
        return self->GetDefaultRowLabelSize();
    }

    EXPORT int wxGrid_GetRowLabelSize(wxGrid* self)
    {
        return self->GetRowLabelSize();
    }

    EXPORT int wxGrid_GetDefaultColLabelSize(wxGrid* self)
    {
        return self->GetDefaultColLabelSize();
    }

    EXPORT int wxGrid_GetColLabelSize(wxGrid* self)
    {
        return self->GetColLabelSize();
    }

    EXPORT void wxGrid_GetLabelBackgroundColour(wxGrid* self, wxColour* colour)
    {
        *colour = self->GetLabelBackgroundColour();
    }

    EXPORT void wxGrid_GetLabelTextColour(wxGrid* self, wxColour* colour)
    {
        *colour = self->GetLabelTextColour();
    }

    EXPORT void wxGrid_GetLabelFont(wxGrid* self, wxFont* font)
    {
        *font = self->GetLabelFont();
    }

    EXPORT void wxGrid_GetRowLabelAlignment(wxGrid* self, int* horiz, int* vert)
    {
        self->GetRowLabelAlignment(horiz, vert);
    }

    EXPORT void wxGrid_GetColLabelAlignment(wxGrid* self, int* horiz, int* vert)
    {
        self->GetColLabelAlignment(horiz, vert);
    }

    EXPORT wxString* wxGrid_GetRowLabelValue(wxGrid* self, int row)
    {
        wxString* result = new wxString();
        *result = self->GetRowLabelValue(row);
        return result;
    }

    EXPORT wxString* wxGrid_GetColLabelValue(wxGrid* self, int col)
    {
        wxString* result = new wxString();
        *result = self->GetColLabelValue(col);
        return result;
    }

    EXPORT void wxGrid_GetGridLineColour(wxGrid* self, wxColour* colour)
    {
        *colour = self->GetGridLineColour();
    }

    EXPORT void wxGrid_GetCellHighlightColour(wxGrid* self, wxColour* colour)
    {
        *colour = self->GetCellHighlightColour();
    }

    EXPORT void wxGrid_SetRowLabelSize(wxGrid* self, int width)
    {
        self->SetRowLabelSize(width);
    }

    EXPORT void wxGrid_SetColLabelSize(wxGrid* self, int height)
    {
        self->SetColLabelSize(height);
    }

    EXPORT void wxGrid_SetLabelBackgroundColour(wxGrid* self, wxColour* colour)
    {
        self->SetLabelBackgroundColour(*colour);
    }

    EXPORT void wxGrid_SetLabelTextColour(wxGrid* self, wxColour* colour)
    {
        self->SetLabelTextColour(*colour);
    }

    EXPORT void wxGrid_SetLabelFont(wxGrid* self, wxFont* font)
    {
        self->SetLabelFont(*font);
    }

    EXPORT void wxGrid_SetRowLabelAlignment(wxGrid* self, int horiz, int vert)
    {
        self->SetRowLabelAlignment(horiz, vert);
    }

    EXPORT void wxGrid_SetColLabelAlignment(wxGrid* self, int horiz, int vert)
    {
        self->SetColLabelAlignment(horiz, vert);
    }

    EXPORT void wxGrid_SetRowLabelValue(wxGrid* self, int row, wxString* label)
    {
        self->SetRowLabelValue(row, *label);
    }

    EXPORT void wxGrid_SetColLabelValue(wxGrid* self, int col, wxString* label)
    {
        self->SetColLabelValue(col, *label);
    }

    EXPORT void wxGrid_SetGridLineColour(wxGrid* self, wxColour* col)
    {
        self->SetGridLineColour(*col);
    }

    EXPORT void wxGrid_SetCellHighlightColour(wxGrid* self, wxColour* col)
    {
        self->SetCellHighlightColour(*col);
    }

    EXPORT void wxGrid_EnableDragRowSize(wxGrid* self, bool enable)
    {
        self->EnableDragRowSize(enable);
    }

    EXPORT void wxGrid_DisableDragRowSize(wxGrid* self)
    {
        self->DisableDragRowSize();
    }

    EXPORT bool wxGrid_CanDragRowSize(wxGrid* self, int row)
    {
        return self->CanDragRowSize(row);
    }

    EXPORT void wxGrid_EnableDragColSize(wxGrid* self, bool enable)
    {
        self->EnableDragColSize(enable);
    }

    EXPORT void wxGrid_DisableDragColSize(wxGrid* self)
    {
        self->DisableDragColSize();
    }

    EXPORT bool wxGrid_CanDragColSize(wxGrid* self, int col)
    {
        return self->CanDragColSize(col);
    }

    EXPORT void wxGrid_EnableDragGridSize(wxGrid* self, bool enable)
    {
        self->EnableDragGridSize(enable);
    }

    EXPORT void wxGrid_DisableDragGridSize(wxGrid* self)
    {
        self->DisableDragGridSize();
    }

    EXPORT bool wxGrid_CanDragGridSize(wxGrid* self)
    {
        return self->CanDragGridSize();
    }

    EXPORT void wxGrid_SetRowAttr(wxGrid* self, int row, wxGridCellAttr* attr)
    {
        self->SetRowAttr(row, attr);
    }

    EXPORT void wxGrid_SetColAttr(wxGrid* self, int col, wxGridCellAttr* attr)
    {
        self->SetColAttr(col, attr);
    }

    EXPORT void wxGrid_SetColFormatBool(wxGrid* self, int col)
    {
        self->SetColFormatBool(col);
    }

    EXPORT void wxGrid_SetColFormatNumber(wxGrid* self, int col)
    {
        self->SetColFormatNumber(col);
    }

    EXPORT void wxGrid_SetColFormatFloat(wxGrid* self, int col, int width, int precision)
    {
        self->SetColFormatFloat(col, width, precision);
    }

    EXPORT void wxGrid_SetColFormatCustom(wxGrid* self, int col, wxString* typeName)
    {
        self->SetColFormatCustom(col, *typeName);
    }

    EXPORT void wxGrid_EnableGridLines(wxGrid* self, bool enable)
    {
        self->EnableGridLines(enable);
    }

    EXPORT bool wxGrid_GridLinesEnabled(wxGrid* self)
    {
        return self->GridLinesEnabled();
    }

    EXPORT int wxGrid_GetDefaultRowSize(wxGrid* self)
    {
        return self->GetDefaultRowSize();
    }

    EXPORT int wxGrid_GetRowSize(wxGrid* self, int row)
    {
        return self->GetRowSize(row);
    }

    EXPORT int wxGrid_GetDefaultColSize(wxGrid* self)
    {
        return self->GetDefaultColSize();
    }

    EXPORT int wxGrid_GetColSize(wxGrid* self, int col)
    {
        return self->GetColSize(col);
    }

    EXPORT void wxGrid_GetDefaultCellBackgroundColour(wxGrid* self, wxColour* colour)
    {
        *colour = self->GetDefaultCellBackgroundColour();
    }

    EXPORT void wxGrid_GetCellBackgroundColour(wxGrid* self, int row, int col, wxColour* colour)
    {
        *colour = self->GetCellBackgroundColour(row, col);
    }

    EXPORT void wxGrid_GetDefaultCellTextColour(wxGrid* self, wxColour* colour)
    {
        *colour = self->GetDefaultCellTextColour();
    }

    EXPORT void wxGrid_GetCellTextColour(wxGrid* self, int row, int col, wxColour* colour)
    {
        *colour = self->GetCellTextColour(row, col);
    }

    EXPORT void wxGrid_GetDefaultCellFont(wxGrid* self, wxFont* font)
    {
        *font = self->GetDefaultCellFont();
    }

    EXPORT void wxGrid_GetCellFont(wxGrid* self, int row, int col, wxFont* font)
    {
        *font = self->GetCellFont(row, col);
    }

    EXPORT void wxGrid_GetDefaultCellAlignment(wxGrid* self, int* horiz, int* vert)
    {
        self->GetDefaultCellAlignment(horiz, vert);
    }

    EXPORT void wxGrid_GetCellAlignment(wxGrid* self, int row, int col, int* horiz, int* vert)
    {
        self->GetCellAlignment(row, col, horiz, vert);
    }

    EXPORT void wxGrid_SetDefaultRowSize(wxGrid* self, int height, bool resizeExistingRows)
    {
        self->SetDefaultRowSize(height, resizeExistingRows);
    }

    EXPORT void wxGrid_SetRowSize(wxGrid* self, int row, int height)
    {
        self->SetRowSize(row, height);
    }

    EXPORT void wxGrid_SetDefaultColSize(wxGrid* self, int width, bool resizeExistingCols)
    {
        self->SetDefaultColSize(width, resizeExistingCols);
    }

    EXPORT void wxGrid_SetColSize(wxGrid* self, int col, int width)
    {
        self->SetColSize(col, width);
    }

    EXPORT void wxGrid_AutoSizeColumn(wxGrid* self, int col, bool setAsMin)
    {
        self->AutoSizeColumn(col, setAsMin);
    }

    EXPORT void wxGrid_AutoSizeRow(wxGrid* self, int row, bool setAsMin)
    {
        self->AutoSizeRow(row, setAsMin);
    }

    EXPORT void wxGrid_AutoSizeColumns(wxGrid* self, bool setAsMin)
    {
        self->AutoSizeColumns(setAsMin);
    }

    EXPORT void wxGrid_AutoSizeRows(wxGrid* self, bool setAsMin)
    {
        self->AutoSizeRows(setAsMin);
    }

    EXPORT void wxGrid_AutoSize(wxGrid* self)
    {
        self->AutoSize();
    }

    EXPORT void wxGrid_SetColMinimalWidth(wxGrid* self, int col, int width)
    {
        self->SetColMinimalWidth(col, width);
    }

    EXPORT void wxGrid_SetRowMinimalHeight(wxGrid* self, int row, int width)
    {
        self->SetRowMinimalHeight(row, width);
    }

    EXPORT void wxGrid_SetDefaultCellBackgroundColour(wxGrid* self, wxColour* colour)
    {
        self->SetDefaultCellBackgroundColour(*colour);
    }

    EXPORT void wxGrid_SetCellBackgroundColour(wxGrid* self, int row, int col, wxColour* colour)
    {
        self->SetCellBackgroundColour(row, col, *colour);
    }

    EXPORT void wxGrid_SetDefaultCellTextColour(wxGrid* self, wxColour* colour)
    {
        self->SetDefaultCellTextColour(*colour);
    }

    EXPORT void wxGrid_SetCellTextColour(wxGrid* self, int row, int col, wxColour* colour)
    {
        self->SetCellTextColour(row, col, *colour);
    }

    EXPORT void wxGrid_SetDefaultCellFont(wxGrid* self, wxFont* font)
    {
        self->SetDefaultCellFont(*font);
    }

    EXPORT void wxGrid_SetCellFont(wxGrid* self, int row, int col, wxFont* font)
    {
        self->SetCellFont(row, col, *font);
    }

    EXPORT void wxGrid_SetDefaultCellAlignment(wxGrid* self, int horiz, int vert)
    {
        self->SetDefaultCellAlignment(horiz, vert);
    }

    EXPORT void wxGrid_SetCellAlignment(wxGrid* self, int row, int col, int horiz, int vert)
    {
        self->SetCellAlignment(row, col, horiz, vert);
    }

    EXPORT void wxGrid_SetDefaultRenderer(wxGrid* self, void* renderer)
    {
        self->SetDefaultRenderer((wxGridCellRenderer*) renderer);
    }

    EXPORT void wxGrid_SetCellRenderer(wxGrid* self, int row, int col, void* renderer)
    {
        self->SetCellRenderer(row, col, (wxGridCellRenderer*) renderer);
    }

    EXPORT void* wxGrid_GetDefaultRenderer(wxGrid* self)
    {
        return (void*) self->GetDefaultRenderer();
    }

    EXPORT void* wxGrid_GetCellRenderer(wxGrid* self, int row, int col)
    {
        return (void*) self->GetCellRenderer(row, col);
    }

    EXPORT void wxGrid_SetDefaultEditor(wxGrid* self, wxGridCellEditor* editor)
    {
        self->SetDefaultEditor(editor);
    }

    EXPORT void wxGrid_SetCellEditor(wxGrid* self, int row, int col, wxGridCellEditor* editor)
    {
        self->SetCellEditor(row, col, editor);
    }

    EXPORT void* wxGrid_GetDefaultEditor(wxGrid* self)
    {
        return (void*) self->GetDefaultEditor();
    }

    EXPORT void* wxGrid_GetCellEditor(wxGrid* self, int row, int col)
    {
        return (void*) self->GetCellEditor(row, col);
    }

    EXPORT wxString* wxGrid_GetCellValue(wxGrid* self, int row, int col)
    {
        wxString* result = new wxString();
        *result = self->GetCellValue(row, col);
        return result;
    }

    EXPORT void wxGrid_SetCellValue(wxGrid* self, int row, int col, wxString* str)
    {
        self->SetCellValue(row, col, *str);
    }

    EXPORT bool wxGrid_IsReadOnly(wxGrid* self, int row, int col)
    {
        return self->IsReadOnly(row, col);
    }

    EXPORT void wxGrid_SetReadOnly(wxGrid* self, int row, int col, bool isReadOnly)
    {
        self->SetReadOnly(row, col, isReadOnly);
    }

    EXPORT void wxGrid_SelectRow(wxGrid* self, int row, bool addToSelected)
    {
        self->SelectRow(row, addToSelected);
    }

    EXPORT void wxGrid_SelectCol(wxGrid* self, int col, bool addToSelected)
    {
        self->SelectCol(col, addToSelected);
    }

    EXPORT void wxGrid_SelectBlock(wxGrid* self, int topRow, int leftCol, int bottomRow,
                                   int rightCol, bool addToSelected)
    {
        self->SelectBlock(topRow, leftCol, bottomRow, rightCol, addToSelected);
    }

    EXPORT void wxGrid_SelectAll(wxGrid* self)
    {
        self->SelectAll();
    }

    EXPORT bool wxGrid_IsSelection(wxGrid* self)
    {
        return self->IsSelection();
    }

    EXPORT void wxGrid_ClearSelection(wxGrid* self)
    {
        self->ClearSelection();
    }

    EXPORT bool wxGrid_IsInSelection(wxGrid* self, int row, int col)
    {
        return self->IsInSelection(row, col);
    }

    EXPORT wxRect* wxGrid_BlockToDeviceRect(wxGrid* self, int top, int left, int bottom, int right)
    {
        wxRect* rct = new wxRect();
        *rct =
            self->BlockToDeviceRect(wxGridCellCoords(top, left), wxGridCellCoords(bottom, right));
        return rct;
    }

    EXPORT void wxGrid_GetSelectionBackground(wxGrid* self, wxColour* colour)
    {
        *colour = self->GetSelectionBackground();
    }

    EXPORT void wxGrid_GetSelectionForeground(wxGrid* self, wxColour* colour)
    {
        *colour = self->GetSelectionForeground();
    }

    EXPORT void wxGrid_SetSelectionBackground(wxGrid* self, wxColour* colour)
    {
        self->SetSelectionBackground(*colour);
    }

    EXPORT void wxGrid_SetSelectionForeground(wxGrid* self, wxColour* colour)
    {
        self->SetSelectionForeground(*colour);
    }

    EXPORT void wxGrid_RegisterDataType(wxGrid* self, wxString* typeName, void* renderer,
                                        wxGridCellEditor* editor)
    {
        self->RegisterDataType(*typeName, (wxGridCellRenderer*) renderer, editor);
    }

    EXPORT void* wxGrid_GetDefaultEditorForCell(wxGrid* self, int row, int col)
    {
        return (void*) self->GetDefaultEditorForCell(row, col);
    }

    EXPORT void* wxGrid_GetDefaultRendererForCell(wxGrid* self, int row, int col)
    {
        return (void*) self->GetDefaultRendererForCell(row, col);
    }

    EXPORT void* wxGrid_GetDefaultEditorForType(wxGrid* self, wxString* typeName)
    {
        return (void*) self->GetDefaultEditorForType(*typeName);
    }

    EXPORT void* wxGrid_GetDefaultRendererForType(wxGrid* self, wxString* typeName)
    {
        return (void*) self->GetDefaultRendererForType(*typeName);
    }

    EXPORT void wxGrid_SetMargins(wxGrid* self, int extraWidth, int extraHeight)
    {
        self->SetMargins(extraWidth, extraHeight);
    }

    EXPORT void wxGrid_GetSelectedCells(wxGrid* self, wxGridCellCoordsArray* array)
    {
        *array = self->GetSelectedCells();
    }

    EXPORT void wxGrid_GetSelectionBlockTopLeft(wxGrid* self, wxGridCellCoordsArray* array)
    {
        *array = self->GetSelectionBlockTopLeft();
    }

    EXPORT void wxGrid_GetSelectionBlockBottomRight(wxGrid* self, wxGridCellCoordsArray* array)
    {
        *array = self->GetSelectionBlockBottomRight();
    }

    EXPORT int wxGrid_GetSelectedRows(wxGrid* self, void* array)
    {
        wxArrayInt arr = self->GetSelectedRows();
        if (array)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((int*) array)[i] = arr.Item(i);
        }
        return arr.GetCount();
    }

    EXPORT int wxGrid_GetSelectedCols(wxGrid* self, void* array)
    {
        wxArrayInt arr = self->GetSelectedCols();
        if (array)
        {
            for (unsigned int i = 0; i < arr.GetCount(); i++)
                ((int*) array)[i] = arr.Item(i);
        }
        return arr.GetCount();
    }

    EXPORT void wxGrid_GetCellSize(wxGrid* self, int row, int col, int* srow, int* scol)
    {
        self->GetCellSize(row, col, srow, scol);
    }
    EXPORT void wxGrid_SetCellSize(wxGrid* self, int row, int col, int srow, int scol)
    {
        self->SetCellSize(row, col, srow, scol);
    }

    EXPORT void* kwxGridTable_Create(void* self, void* fnGetNumberRows, void* fnGetNumberCols,
                                     void* fnGetValue, void* fnSetValue, void* fnIsEmptyCell,
                                     void* fnClear, void* fnInsertRows, void* fnAppendRows,
                                     void* fnDeleteRows, void* fnInsertCols, void* fnAppendCols,
                                     void* fnDeleteCols, void* fnSetRowLabelValue,
                                     void* fnSetColLabelValue, void* fnGetRowLabelValue,
                                     void* fnGetColLabelValue)
    {
        return (void*) new kwxGridTable(
            self, fnGetNumberRows, fnGetNumberCols, fnGetValue, fnSetValue, fnIsEmptyCell, fnClear,
            fnInsertRows, fnAppendRows, fnDeleteRows, fnInsertCols, fnAppendCols, fnDeleteCols,
            fnSetRowLabelValue, fnSetColLabelValue, fnGetRowLabelValue, fnGetColLabelValue);
    }

    EXPORT void kwxGridTable_Delete(kwxGridTable* self)
    {
        delete self;
    }

    EXPORT void* kwxGridTable_GetView(kwxGridTable* self)
    {
        return (void*) self->GetView();
    }

    EXPORT void kwxGridTable_SendTableMessage(kwxGridTable* self, int id, int val1, int val2)
    {
        wxGridTableMessage msg(self, id, val1, val2);
        self->GetView()->ProcessTableMessage(msg);
    }

    EXPORT int wxGridEvent_GetRow(wxGridEvent* self)
    {
        return self->GetRow();
    }

    EXPORT int wxGridEvent_GetCol(wxGridEvent* self)
    {
        return self->GetCol();
    }

    EXPORT wxPoint* wxGridEvent_GetPosition(wxGridEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT bool wxGridEvent_Selecting(wxGridEvent* self)
    {
        return self->Selecting();
    }

    EXPORT bool wxGridEvent_ControlDown(wxGridEvent* self)
    {
        return self->ControlDown();
    }

    EXPORT bool wxGridEvent_MetaDown(wxGridEvent* self)
    {
        return self->MetaDown();
    }

    EXPORT bool wxGridEvent_ShiftDown(wxGridEvent* self)
    {
        return self->ShiftDown();
    }

    EXPORT bool wxGridEvent_AltDown(wxGridEvent* self)
    {
        return self->AltDown();
    }

    EXPORT int wxGridSizeEvent_GetRowOrCol(wxGridSizeEvent* self)
    {
        return self->GetRowOrCol();
    }

    EXPORT wxPoint* wxGridSizeEvent_GetPosition(wxGridSizeEvent* self)
    {
        wxPoint* pt = new wxPoint();
        *pt = self->GetPosition();
        return pt;
    }

    EXPORT bool wxGridSizeEvent_ControlDown(wxGridSizeEvent* self)
    {
        return self->ControlDown();
    }

    EXPORT bool wxGridSizeEvent_MetaDown(wxGridSizeEvent* self)
    {
        return self->MetaDown();
    }

    EXPORT bool wxGridSizeEvent_ShiftDown(wxGridSizeEvent* self)
    {
        return self->ShiftDown();
    }

    EXPORT bool wxGridSizeEvent_AltDown(wxGridSizeEvent* self)
    {
        return self->AltDown();
    }

    EXPORT void wxGridRangeSelectEvent_GetTopLeftCoords(wxGridRangeSelectEvent* self, int* col,
                                                        int* row)
    {
        wxGridCellCoords crd = self->GetTopLeftCoords();
        *col = crd.GetRow();
        *row = crd.GetCol();
    }

    EXPORT void wxGridRangeSelectEvent_GetBottomRightCoords(wxGridRangeSelectEvent* self, int* col,
                                                            int* row)
    {
        wxGridCellCoords crd = self->GetBottomRightCoords();
        *col = crd.GetRow();
        *row = crd.GetCol();
    }

    EXPORT int wxGridRangeSelectEvent_GetTopRow(wxGridRangeSelectEvent* self)
    {
        return self->GetTopRow();
    }

    EXPORT int wxGridRangeSelectEvent_GetBottomRow(wxGridRangeSelectEvent* self)
    {
        return self->GetBottomRow();
    }

    EXPORT int wxGridRangeSelectEvent_GetLeftCol(wxGridRangeSelectEvent* self)
    {
        return self->GetLeftCol();
    }

    EXPORT int wxGridRangeSelectEvent_GetRightCol(wxGridRangeSelectEvent* self)
    {
        return self->GetRightCol();
    }

    EXPORT bool wxGridRangeSelectEvent_Selecting(wxGridRangeSelectEvent* self)
    {
        return self->Selecting();
    }

    EXPORT bool wxGridRangeSelectEvent_ControlDown(wxGridRangeSelectEvent* self)
    {
        return self->ControlDown();
    }

    EXPORT bool wxGridRangeSelectEvent_MetaDown(wxGridRangeSelectEvent* self)
    {
        return self->MetaDown();
    }

    EXPORT bool wxGridRangeSelectEvent_ShiftDown(wxGridRangeSelectEvent* self)
    {
        return self->ShiftDown();
    }

    EXPORT bool wxGridRangeSelectEvent_AltDown(wxGridRangeSelectEvent* self)
    {
        return self->AltDown();
    }

    EXPORT int wxGridEditorCreatedEvent_GetRow(wxGridEditorCreatedEvent* self)
    {
        return self->GetRow();
    }

    EXPORT int wxGridEditorCreatedEvent_GetCol(wxGridEditorCreatedEvent* self)
    {
        return self->GetCol();
    }

    EXPORT void* wxGridEditorCreatedEvent_GetControl(wxGridEditorCreatedEvent* self)
    {
        return (void*) self->GetControl();
    }

    EXPORT void wxGridEditorCreatedEvent_SetRow(wxGridEditorCreatedEvent* self, int row)
    {
        self->SetRow(row);
    }

    EXPORT void wxGridEditorCreatedEvent_SetCol(wxGridEditorCreatedEvent* self, int col)
    {
        self->SetCol(col);
    }

    EXPORT void wxGridEditorCreatedEvent_SetControl(wxGridEditorCreatedEvent* self, wxControl* ctrl)
    {
        self->SetControl(ctrl);
    }
}
