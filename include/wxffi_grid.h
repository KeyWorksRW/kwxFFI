#pragma once

#include "wx/grid.h"

extern "C"
{
    typedef int (*TGridGetInt)(void* pObject);
    typedef int (*TGridIsEmpty)(void* pObject, int row, int col);
    typedef void* (*TGridGetValue)(void* pObject, int row, int col);
    typedef void (*TGridSetValue)(void* pObject, int row, int col, void* val);
    typedef void (*TGridClear)(void* pObject);
    typedef int (*TGridModify)(void* pObject, int pos, int num);
    typedef int (*TGridMultiModify)(void* pObject, int num);
    typedef void (*TGridSetLabel)(void* pObject, int idx, void* val);
    typedef void* (*TGridGetLabel)(void* pObject, int idx);
}

class kwxGridTable : public wxGridTableBase
{
private:
    void* EiffelObject;
    TGridGetInt EifGetNumberRows;
    TGridGetInt EifGetNumberCols;
    TGridGetValue EifGetValue;
    TGridSetValue EifSetValue;
    TGridIsEmpty EifIsEmptyCell;
    TGridClear EifClear;
    TGridModify EifInsertRows;
    TGridMultiModify EifAppendRows;
    TGridModify EifDeleteRows;
    TGridModify EifInsertCols;
    TGridMultiModify EifAppendCols;
    TGridModify EifDeleteCols;
    TGridSetLabel EifSetRowLabelValue;
    TGridSetLabel EifSetColLabelValue;
    TGridGetLabel EifGetRowLabelValue;
    TGridGetLabel EifGetColLabelValue;

public:
    kwxGridTable(void* pObject, void* fnGetNumberRows, void* fnGetNumberCols, void* fnGetValue,
                 void* fnSetValue, void* fnIsEmptyCell, void* fnClear, void* fnInsertRows,
                 void* fnAppendRows, void* fnDeleteRows, void* fnInsertCols,
                 void* fnAppendCols, void* fnDeleteCols, void* fnSetRowLabelValue,
                 void* fnSetColLabelValue, void* fnGetRowLabelValue,
                 void* fnGetColLabelValue) : wxGridTableBase()
    {
        EiffelObject = pObject;
        EifGetNumberRows = (TGridGetInt) fnGetNumberRows;
        EifGetNumberCols = (TGridGetInt) fnGetNumberCols;
        EifGetValue = (TGridGetValue) fnGetValue;
        EifSetValue = (TGridSetValue) fnSetValue;
        EifIsEmptyCell = (TGridIsEmpty) fnIsEmptyCell;
        EifClear = (TGridClear) fnClear;
        EifInsertRows = (TGridModify) fnInsertRows;
        EifAppendRows = (TGridMultiModify) fnAppendRows;
        EifDeleteRows = (TGridModify) fnDeleteRows;
        EifInsertCols = (TGridModify) fnInsertCols;
        EifAppendCols = (TGridMultiModify) fnAppendCols;
        EifDeleteCols = (TGridModify) fnDeleteCols;
        EifSetRowLabelValue = (TGridSetLabel) fnSetRowLabelValue;
        EifSetColLabelValue = (TGridSetLabel) fnSetColLabelValue;
        EifGetRowLabelValue = (TGridGetLabel) fnGetRowLabelValue;
        EifGetColLabelValue = (TGridGetLabel) fnGetColLabelValue;
    };

    int GetNumberRows() { return EifGetNumberRows(EiffelObject); };
    int GetNumberCols() { return EifGetNumberCols(EiffelObject); };
    wxString GetValue(int row, int col)
    {
        return (const char*) EifGetValue(EiffelObject, row, col);
    };
    void SetValue(int row, int col, const wxString& s)
    {
        EifSetValue(EiffelObject, row, col, (void*) s.utf8_str().data());
    };
    bool IsEmptyCell(int row, int col) { return EifIsEmptyCell(EiffelObject, row, col) != 0; };

    void Clear() { EifClear(EiffelObject); };
    bool InsertRows(size_t pos, size_t numRows)
    {
        return EifInsertRows(EiffelObject, (int) pos, (int) numRows) != 0;
    };
    bool AppendRows(size_t numRows) { return EifAppendRows(EiffelObject, (int) numRows) != 0; };
    bool DeleteRows(size_t pos, size_t numRows)
    {
        return EifDeleteRows(EiffelObject, (int) pos, (int) numRows) != 0;
    };
    bool InsertCols(size_t pos, size_t numCols)
    {
        return EifInsertCols(EiffelObject, (int) pos, (int) numCols) != 0;
    };
    bool AppendCols(size_t numCols) { return EifAppendCols(EiffelObject, (int) numCols) != 0; };
    bool DeleteCols(size_t pos, size_t numCols)
    {
        return EifDeleteCols(EiffelObject, (int) pos, (int) numCols) != 0;
    };

    void SetRowLabelValue(int row, const wxString& s)
    {
        EifSetRowLabelValue(EiffelObject, row, (void*) s.utf8_str().data());
    };
    void SetColLabelValue(int col, const wxString& s)
    {
        EifSetColLabelValue(EiffelObject, col, (void*) s.utf8_str().data());
    };
    wxString GetRowLabelValue(int row)
    {
        return (const char*) EifGetRowLabelValue(EiffelObject, row);
    };
    wxString GetColLabelValue(int col)
    {
        return (const char*) EifGetColLabelValue(EiffelObject, col);
    };
};
