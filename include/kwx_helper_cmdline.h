#pragma once

// kwxCmdLineDesc — owning storage for a wxCmdLineEntryDesc table.
//
// wxCmdLineParser::SetDesc() takes a pointer to a wxCMD_LINE_NONE-terminated table of
// wxCmdLineEntryDesc records whose name and description fields are plain `const char*`. A
// foreign runtime cannot keep that table and those strings alive across the FFI call, so this
// helper owns both: it copies the UTF-8 text into stable storage and keeps the table
// terminated.
//
// The pointer returned by GetDesc() stays valid until the next Add*() call, so add every entry
// before handing the table to wxCmdLineParser_SetDesc(). wxWidgets copies the entries into
// wxString values inside SetDesc(), so the helper may be destroyed once that call returns.
//
// Entry kinds are the wxCmdLineEntryType values (wxCMD_LINE_SWITCH, wxCMD_LINE_OPTION,
// wxCMD_LINE_PARAM), value types are the wxCmdLineParamType values, and flags are combinations
// of the wxCmdLineEntryFlags values.

#include <wx/cmdline.h>
#include <wx/string.h>

#include <deque>
#include <string>
#include <vector>

// The descriptor kinds share the FFI spelling of a handle and two strings, so every Add*()
// necessarily takes several adjacent parameters of the same type; the wxWidgets entry model
// dictates the shape.
// NOLINTBEGIN(bugprone-identical-type-multi-param)
class kwxCmdLineDesc
{
public:
    kwxCmdLineDesc();
    ~kwxCmdLineDesc() = default;

    kwxCmdLineDesc(const kwxCmdLineDesc&) = delete;
    kwxCmdLineDesc& operator=(const kwxCmdLineDesc&) = delete;

    kwxCmdLineDesc(kwxCmdLineDesc&&) = delete;
    kwxCmdLineDesc& operator=(kwxCmdLineDesc&&) = delete;

    void AddSwitch(const wxString& short_name, const wxString& long_name,
                   const wxString& description, int flags);
    void AddOption(const wxString& short_name, const wxString& long_name,
                   const wxString& description, int type, int flags);
    void AddParam(const wxString& description, int type, int flags);

    // Returns the wxCMD_LINE_NONE terminated table. Valid until the next Add*() call.
    const wxCmdLineEntryDesc* GetDesc() const;

private:
    // Copies the text into stable storage and returns a pointer to it. Callers pass nullptr for
    // an absent short or long name, which is how wxWidgets spells "no name".
    const char* StoreText(const wxString& text);

    void AppendEntry(wxCmdLineEntryType kind, const wxString& short_name, const wxString& long_name,
                     const wxString& description, wxCmdLineParamType type, int flags);

    std::deque<std::string> m_text;
    std::vector<wxCmdLineEntryDesc> m_entries;
};
// NOLINTEND(bugprone-identical-type-multi-param)
