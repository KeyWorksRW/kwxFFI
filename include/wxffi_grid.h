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
    TGridGetInt m_fnGetNumberRows;
    TGridGetInt m_fnGetNumberCols;
    TGridGetValue m_fnGetValue;
    TGridSetValue m_fnSetValue;
    TGridIsEmpty m_fnIsEmptyCell;
    TGridClear m_fnClear;
    TGridModify m_fnInsertRows;
    TGridMultiModify m_fnAppendRows;
    TGridModify m_fnDeleteRows;
    TGridModify m_fnInsertCols;
    TGridMultiModify m_fnAppendCols;
    TGridModify m_fnDeleteCols;
    TGridSetLabel m_fnSetRowLabelValue;
    TGridSetLabel m_fnSetColLabelValue;
    TGridGetLabel m_fnGetRowLabelValue;
    TGridGetLabel m_fnGetColLabelValue;

public:
    kwxGridTable(void* pObject, void* fnGetNumberRows, void* fnGetNumberCols, void* fnGetValue,
                 void* fnSetValue, void* fnIsEmptyCell, void* fnClear, void* fnInsertRows,
                 void* fnAppendRows, void* fnDeleteRows, void* fnInsertCols, void* fnAppendCols,
                 void* fnDeleteCols, void* fnSetRowLabelValue, void* fnSetColLabelValue,
                 void* fnGetRowLabelValue, void* fnGetColLabelValue) : wxGridTableBase()
    {
        kwxObject = pObject;
        m_fnGetNumberRows = (TGridGetInt) fnGetNumberRows;
        m_fnGetNumberCols = (TGridGetInt) fnGetNumberCols;
        m_fnGetValue = (TGridGetValue) fnGetValue;
        m_fnSetValue = (TGridSetValue) fnSetValue;
        m_fnIsEmptyCell = (TGridIsEmpty) fnIsEmptyCell;
        m_fnClear = (TGridClear) fnClear;
        m_fnInsertRows = (TGridModify) fnInsertRows;
        m_fnAppendRows = (TGridMultiModify) fnAppendRows;
        m_fnDeleteRows = (TGridModify) fnDeleteRows;
        m_fnInsertCols = (TGridModify) fnInsertCols;
        m_fnAppendCols = (TGridMultiModify) fnAppendCols;
        m_fnDeleteCols = (TGridModify) fnDeleteCols;
        m_fnSetRowLabelValue = (TGridSetLabel) fnSetRowLabelValue;
        m_fnSetColLabelValue = (TGridSetLabel) fnSetColLabelValue;
        m_fnGetRowLabelValue = (TGridGetLabel) fnGetRowLabelValue;
        m_fnGetColLabelValue = (TGridGetLabel) fnGetColLabelValue;
    };

    int GetNumberRows() { return m_fnGetNumberRows(kwxObject); };
    int GetNumberCols() { return m_fnGetNumberCols(kwxObject); };
    wxString GetValue(int row, int col) { return (const char*) m_fnGetValue(kwxObject, row, col); };
    void SetValue(int row, int col, const wxString& s)
    {
        m_fnSetValue(kwxObject, row, col, (void*) s.utf8_str().data());
    };
    bool IsEmptyCell(int row, int col) { return m_fnIsEmptyCell(kwxObject, row, col) != 0; };

    void Clear() { m_fnClear(kwxObject); };
    bool InsertRows(size_t pos, size_t numRows)
    {
        return m_fnInsertRows(kwxObject, (int) pos, (int) numRows) != 0;
    };
    bool AppendRows(size_t numRows) { return m_fnAppendRows(kwxObject, (int) numRows) != 0; };
    bool DeleteRows(size_t pos, size_t numRows)
    {
        return m_fnDeleteRows(kwxObject, (int) pos, (int) numRows) != 0;
    };
    bool InsertCols(size_t pos, size_t numCols)
    {
        return m_fnInsertCols(kwxObject, (int) pos, (int) numCols) != 0;
    };
    bool AppendCols(size_t numCols) { return m_fnAppendCols(kwxObject, (int) numCols) != 0; };
    bool DeleteCols(size_t pos, size_t numCols)
    {
        return m_fnDeleteCols(kwxObject, (int) pos, (int) numCols) != 0;
    };

    void SetRowLabelValue(int row, const wxString& s)
    {
        m_fnSetRowLabelValue(kwxObject, row, (void*) s.utf8_str().data());
    };
    void SetColLabelValue(int col, const wxString& s)
    {
        m_fnSetColLabelValue(kwxObject, col, (void*) s.utf8_str().data());
    };
    wxString GetRowLabelValue(int row)
    {
        return (const char*) m_fnGetRowLabelValue(kwxObject, row);
    };
    wxString GetColLabelValue(int col)
    {
        return (const char*) m_fnGetColLabelValue(kwxObject, col);
    };
};
