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
    void* kwxObject;
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
        kwxObject = pObject;
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

    int GetNumberRows() { return EifGetNumberRows(kwxObject); };
    int GetNumberCols() { return EifGetNumberCols(kwxObject); };
    wxString GetValue(int row, int col)
    {
        return (const char*) EifGetValue(kwxObject, row, col);
    };
    void SetValue(int row, int col, const wxString& s)
    {
        EifSetValue(kwxObject, row, col, (void*) s.utf8_str().data());
    };
    bool IsEmptyCell(int row, int col) { return EifIsEmptyCell(kwxObject, row, col) != 0; };

    void Clear() { EifClear(kwxObject); };
    bool InsertRows(size_t pos, size_t numRows)
    {
        return EifInsertRows(kwxObject, (int) pos, (int) numRows) != 0;
    };
    bool AppendRows(size_t numRows) { return EifAppendRows(kwxObject, (int) numRows) != 0; };
    bool DeleteRows(size_t pos, size_t numRows)
    {
        return EifDeleteRows(kwxObject, (int) pos, (int) numRows) != 0;
    };
    bool InsertCols(size_t pos, size_t numCols)
    {
        return EifInsertCols(kwxObject, (int) pos, (int) numCols) != 0;
    };
    bool AppendCols(size_t numCols) { return EifAppendCols(kwxObject, (int) numCols) != 0; };
    bool DeleteCols(size_t pos, size_t numCols)
    {
        return EifDeleteCols(kwxObject, (int) pos, (int) numCols) != 0;
    };

    void SetRowLabelValue(int row, const wxString& s)
    {
        EifSetRowLabelValue(kwxObject, row, (void*) s.utf8_str().data());
    };
    void SetColLabelValue(int col, const wxString& s)
    {
        EifSetColLabelValue(kwxObject, col, (void*) s.utf8_str().data());
    };
    wxString GetRowLabelValue(int row)
    {
        return (const char*) EifGetRowLabelValue(kwxObject, row);
    };
    wxString GetColLabelValue(int col)
    {
        return (const char*) EifGetColLabelValue(kwxObject, col);
    };
};
