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

    // Phase 6: the typed-value virtuals.  typeName is a const wxString*.  The
    // Get* string returns must be UTF-8 and stay valid until the callback
    // returns; this class copies them.
    typedef void* (*TGridGetTypeName)(void* pObject, int row, int col);
    typedef int (*TGridCanTypeValueAs)(void* pObject, int row, int col, void* typeName);
    typedef int (*TGridGetValueAsLong)(void* pObject, int row, int col);
    typedef int (*TGridGetValueAsBool)(void* pObject, int row, int col);
    typedef void (*TGridSetValueAsLong)(void* pObject, int row, int col, long value);
    typedef void (*TGridSetValueAsBool)(void* pObject, int row, int col, int value);
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
    TGridGetTypeName m_fnGetTypeName;
    TGridCanTypeValueAs m_fnCanGetValueAs;
    TGridCanTypeValueAs m_fnCanSetValueAs;
    TGridGetValueAsLong m_fnGetValueAsLong;
    TGridGetValueAsBool m_fnGetValueAsBool;
    TGridSetValueAsLong m_fnSetValueAsLong;
    TGridSetValueAsBool m_fnSetValueAsBool;

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
        m_fnGetTypeName = nullptr;
        m_fnCanGetValueAs = nullptr;
        m_fnCanSetValueAs = nullptr;
        m_fnGetValueAsLong = nullptr;
        m_fnGetValueAsBool = nullptr;
        m_fnSetValueAsLong = nullptr;
        m_fnSetValueAsBool = nullptr;
    };

    // Phase 6: the seven typed-value virtuals (wx/generic/grid.h:1312-1322).
    // Each one is optional here: an unset callback keeps the wxGridTableBase
    // default, which is why these are setters rather than constructor arguments.

    void SetOnGetTypeName(void* pFunction) { m_fnGetTypeName = (TGridGetTypeName) pFunction; }
    void SetOnCanGetValueAs(void* pFunction)
    {
        m_fnCanGetValueAs = (TGridCanTypeValueAs) pFunction;
    }
    void SetOnCanSetValueAs(void* pFunction)
    {
        m_fnCanSetValueAs = (TGridCanTypeValueAs) pFunction;
    }
    void SetOnGetValueAsLong(void* pFunction)
    {
        m_fnGetValueAsLong = (TGridGetValueAsLong) pFunction;
    }
    void SetOnGetValueAsBool(void* pFunction)
    {
        m_fnGetValueAsBool = (TGridGetValueAsBool) pFunction;
    }
    void SetOnSetValueAsLong(void* pFunction)
    {
        m_fnSetValueAsLong = (TGridSetValueAsLong) pFunction;
    }
    void SetOnSetValueAsBool(void* pFunction)
    {
        m_fnSetValueAsBool = (TGridSetValueAsBool) pFunction;
    }

    // Phase 6: the virtuals the constructor already takes as callbacks.  The
    // portability matrix resolves an ovh row to <Base>_SetOn<method> and
    // kwx<Base-minus-wx>_SetOn<method>, so they need setters as well as the
    // constructor arguments.  Setting one after construction replaces the
    // constructor value.

    void SetOnGetNumberRows(void* pFunction) { m_fnGetNumberRows = (TGridGetInt) pFunction; }
    void SetOnGetNumberCols(void* pFunction) { m_fnGetNumberCols = (TGridGetInt) pFunction; }
    void SetOnGetValue(void* pFunction) { m_fnGetValue = (TGridGetValue) pFunction; }
    void SetOnSetValue(void* pFunction) { m_fnSetValue = (TGridSetValue) pFunction; }
    void SetOnIsEmptyCell(void* pFunction) { m_fnIsEmptyCell = (TGridIsEmpty) pFunction; }
    void SetOnGetColLabelValue(void* pFunction)
    {
        m_fnGetColLabelValue = (TGridGetLabel) pFunction;
    }
    void SetOnSetColLabelValue(void* pFunction)
    {
        m_fnSetColLabelValue = (TGridSetLabel) pFunction;
    }

    int GetNumberRows() override { return m_fnGetNumberRows(kwxObject); };
    int GetNumberCols() override { return m_fnGetNumberCols(kwxObject); };
    wxString GetValue(int row, int col) override
    {
        return (const char*) m_fnGetValue(kwxObject, row, col);
    };
    void SetValue(int row, int col, const wxString& s) override
    {
        m_fnSetValue(kwxObject, row, col, (void*) s.utf8_string().data());
    };
    bool IsEmptyCell(int row, int col) override
    {
        return m_fnIsEmptyCell(kwxObject, row, col) != 0;
    };

    void Clear() override { m_fnClear(kwxObject); };
    bool InsertRows(size_t pos, size_t numRows) override
    {
        return m_fnInsertRows(kwxObject, (int) pos, (int) numRows) != 0;
    };
    bool AppendRows(size_t numRows) override
    {
        return m_fnAppendRows(kwxObject, (int) numRows) != 0;
    };
    bool DeleteRows(size_t pos, size_t numRows) override
    {
        return m_fnDeleteRows(kwxObject, (int) pos, (int) numRows) != 0;
    };
    bool InsertCols(size_t pos, size_t numCols) override
    {
        return m_fnInsertCols(kwxObject, (int) pos, (int) numCols) != 0;
    };
    bool AppendCols(size_t numCols) override
    {
        return m_fnAppendCols(kwxObject, (int) numCols) != 0;
    };
    bool DeleteCols(size_t pos, size_t numCols) override
    {
        return m_fnDeleteCols(kwxObject, (int) pos, (int) numCols) != 0;
    };

    void SetRowLabelValue(int row, const wxString& s) override
    {
        m_fnSetRowLabelValue(kwxObject, row, (void*) s.utf8_string().data());
    };
    void SetColLabelValue(int col, const wxString& s) override
    {
        m_fnSetColLabelValue(kwxObject, col, (void*) s.utf8_string().data());
    };
    wxString GetRowLabelValue(int row) override
    {
        return (const char*) m_fnGetRowLabelValue(kwxObject, row);
    };
    wxString GetColLabelValue(int col) override
    {
        return (const char*) m_fnGetColLabelValue(kwxObject, col);
    };

    wxString GetTypeName(int row, int col) override
    {
        if (!m_fnGetTypeName)
        {
            return wxGridTableBase::GetTypeName(row, col);
        }
        const char* const type_name = (const char*) m_fnGetTypeName(kwxObject, row, col);
        return type_name ? wxString::FromUTF8(type_name) : wxString();
    }

    bool CanGetValueAs(int row, int col, const wxString& type_name) override
    {
        if (!m_fnCanGetValueAs)
        {
            return wxGridTableBase::CanGetValueAs(row, col, type_name);
        }
        return m_fnCanGetValueAs(kwxObject, row, col, (void*) &type_name) != 0;
    }

    bool CanSetValueAs(int row, int col, const wxString& type_name) override
    {
        if (!m_fnCanSetValueAs)
        {
            return wxGridTableBase::CanSetValueAs(row, col, type_name);
        }
        return m_fnCanSetValueAs(kwxObject, row, col, (void*) &type_name) != 0;
    }

    long GetValueAsLong(int row, int col) override
    {
        if (!m_fnGetValueAsLong)
        {
            return wxGridTableBase::GetValueAsLong(row, col);
        }
        return m_fnGetValueAsLong(kwxObject, row, col);
    }

    bool GetValueAsBool(int row, int col) override
    {
        if (!m_fnGetValueAsBool)
        {
            return wxGridTableBase::GetValueAsBool(row, col);
        }
        return m_fnGetValueAsBool(kwxObject, row, col) != 0;
    }

    void SetValueAsLong(int row, int col, long value) override
    {
        if (!m_fnSetValueAsLong)
        {
            wxGridTableBase::SetValueAsLong(row, col, value);
            return;
        }
        m_fnSetValueAsLong(kwxObject, row, col, value);
    }

    void SetValueAsBool(int row, int col, bool value) override
    {
        if (!m_fnSetValueAsBool)
        {
            wxGridTableBase::SetValueAsBool(row, col, value);
            return;
        }
        m_fnSetValueAsBool(kwxObject, row, col, value ? 1 : 0);
    }
};
