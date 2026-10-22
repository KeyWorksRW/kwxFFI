#include "kwx_wrapper.h"

#include <limits>

// wxWidgets exposes numeric validation only through the wxIntegerValidator<>
// and wxFloatingPointValidator<> class templates (wx/valnum.h), so a concrete
// class is required for a stable C ABI type. It forwards validation and data
// transfer to the appropriate template and stores the value that template
// points at, mirroring the wxRuby3 IntegerValidator and FloatValidator classes.
class wxNumValidator : public wxValidator
{
public:
    wxNumValidator(bool use_double, int style) :
        m_use_double(use_double), m_style(style), m_min_long(std::numeric_limits<long>::min()),
        m_max_long(std::numeric_limits<long>::max()),
        m_min_double(-std::numeric_limits<double>::max()),
        m_max_double(std::numeric_limits<double>::max()), m_value_long(0), m_value_double(0.0),
        m_integer_validator(nullptr), m_float_validator(nullptr)
    {
        CreateDelegate();
    }

    wxNumValidator(const wxNumValidator& other) :
        wxValidator(other), m_use_double(other.m_use_double), m_style(other.m_style),
        m_min_long(other.m_min_long), m_max_long(other.m_max_long),
        m_min_double(other.m_min_double), m_max_double(other.m_max_double),
        m_value_long(other.m_value_long), m_value_double(other.m_value_double),
        m_integer_validator(nullptr), m_float_validator(nullptr)
    {
        CreateDelegate();
    }

    ~wxNumValidator() override
    {
        delete m_integer_validator;
        delete m_float_validator;
    }

    wxObject* Clone() const override { return new wxNumValidator(*this); }

    bool Validate(wxWindow* parent) override
    {
        if (m_integer_validator)
        {
            return m_integer_validator->Validate(parent);
        }
        return m_float_validator->Validate(parent);
    }

    bool TransferToWindow() override
    {
        if (m_integer_validator)
        {
            return m_integer_validator->TransferToWindow();
        }
        return m_float_validator->TransferToWindow();
    }

    bool TransferFromWindow() override
    {
        if (m_integer_validator)
        {
            return m_integer_validator->TransferFromWindow();
        }
        return m_float_validator->TransferFromWindow();
    }

    void SetWindow(wxWindow* window) override
    {
        wxValidator::SetWindow(window);
        if (m_integer_validator)
        {
            m_integer_validator->SetWindow(window);
        }
        else
        {
            m_float_validator->SetWindow(window);
        }
    }

    void SetStyle(int style)
    {
        m_style = style;
        if (m_integer_validator)
        {
            m_integer_validator->SetStyle(style);
        }
        else
        {
            m_float_validator->SetStyle(style);
        }
    }

    int GetStyle() const { return m_style; }

    void SetMinLong(long min_value)
    {
        m_min_long = min_value;
        if (m_integer_validator)
        {
            m_integer_validator->SetMin(min_value);
        }
    }

    long GetMinLong() const { return m_min_long; }

    void SetMaxLong(long max_value)
    {
        m_max_long = max_value;
        if (m_integer_validator)
        {
            m_integer_validator->SetMax(max_value);
        }
    }

    long GetMaxLong() const { return m_max_long; }

    void SetMinDouble(double min_value)
    {
        m_min_double = min_value;
        if (m_float_validator)
        {
            m_float_validator->SetMin(min_value);
        }
    }

    double GetMinDouble() const { return m_min_double; }

    void SetMaxDouble(double max_value)
    {
        m_max_double = max_value;
        if (m_float_validator)
        {
            m_float_validator->SetMax(max_value);
        }
    }

    double GetMaxDouble() const { return m_max_double; }

    void SetValueLong(long value) { m_value_long = value; }

    long GetValueLong() const { return m_value_long; }

    void SetValueDouble(double value) { m_value_double = value; }

    double GetValueDouble() const { return m_value_double; }

    bool IsInRangeLong(long value) const { return value >= m_min_long && value <= m_max_long; }

    bool IsInRangeDouble(double value) const
    {
        return value >= m_min_double && value <= m_max_double;
    }

private:
    void CreateDelegate()
    {
        if (m_use_double)
        {
            m_float_validator = new wxFloatingPointValidator<double>(&m_value_double, m_style);
            m_float_validator->SetRange(m_min_double, m_max_double);
        }
        else
        {
            m_integer_validator =
                new wxIntegerValidator<long>(&m_value_long, m_min_long, m_max_long, m_style);
        }
    }

    bool m_use_double;
    int m_style;
    long m_min_long;
    long m_max_long;
    double m_min_double;
    double m_max_double;
    long m_value_long;
    double m_value_double;
    wxIntegerValidator<long>* m_integer_validator;
    wxFloatingPointValidator<double>* m_float_validator;
};

extern "C"
{
    EXPORT void* wxNumValidator_Create(bool use_double, int style)
    {
        return static_cast<void*>(new wxNumValidator(use_double, style));
    }

    EXPORT void wxNumValidator_Delete(wxNumValidator* self)
    {
        delete self;
    }

    EXPORT void wxNumValidator_SetStyle(wxNumValidator* self, int style)
    {
        self->SetStyle(style);
    }

    EXPORT int wxNumValidator_GetStyle(wxNumValidator* self)
    {
        return self->GetStyle();
    }

    EXPORT void wxNumValidator_SetMin(wxNumValidator* self, long min_value)
    {
        self->SetMinLong(min_value);
    }

    EXPORT long wxNumValidator_GetMin(wxNumValidator* self)
    {
        return self->GetMinLong();
    }

    EXPORT void wxNumValidator_SetMax(wxNumValidator* self, long max_value)
    {
        self->SetMaxLong(max_value);
    }

    EXPORT long wxNumValidator_GetMax(wxNumValidator* self)
    {
        return self->GetMaxLong();
    }

    EXPORT void wxNumValidator_SetRange(wxNumValidator* self, long min_value, long max_value)
    {
        self->SetMinLong(min_value);
        self->SetMaxLong(max_value);
    }

    EXPORT void wxNumValidator_SetMinDouble(wxNumValidator* self, double min_value)
    {
        self->SetMinDouble(min_value);
    }

    EXPORT double wxNumValidator_GetMinDouble(wxNumValidator* self)
    {
        return self->GetMinDouble();
    }

    EXPORT void wxNumValidator_SetMaxDouble(wxNumValidator* self, double max_value)
    {
        self->SetMaxDouble(max_value);
    }

    EXPORT double wxNumValidator_GetMaxDouble(wxNumValidator* self)
    {
        return self->GetMaxDouble();
    }

    EXPORT void wxNumValidator_SetRangeDouble(wxNumValidator* self, double min_value,
                                              double max_value)
    {
        self->SetMinDouble(min_value);
        self->SetMaxDouble(max_value);
    }

    EXPORT void wxNumValidator_SetValue(wxNumValidator* self, long value)
    {
        self->SetValueLong(value);
    }

    EXPORT long wxNumValidator_GetValue(wxNumValidator* self)
    {
        return self->GetValueLong();
    }

    EXPORT void wxNumValidator_SetValueDouble(wxNumValidator* self, double value)
    {
        self->SetValueDouble(value);
    }

    EXPORT double wxNumValidator_GetValueDouble(wxNumValidator* self)
    {
        return self->GetValueDouble();
    }

    EXPORT bool wxNumValidator_IsInRange(wxNumValidator* self, long value)
    {
        return self->IsInRangeLong(value);
    }

    EXPORT bool wxNumValidator_IsInRangeDouble(wxNumValidator* self, double value)
    {
        return self->IsInRangeDouble(value);
    }
}
