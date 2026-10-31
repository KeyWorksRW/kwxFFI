/////////////////////////////////////////////////////////////////////////////
// Purpose:   Dump the kwxFFI integer constant table as NAME<TAB>VALUE lines
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include <print>
#include <tuple>

#ifdef _WIN32
    #include <cstdio>
    #include <fcntl.h>
    #include <io.h>
#endif

extern "C"
{
    int kwxConstants_IntCount();
    const int* kwxConstants_IntTable();
    const char* const* kwxConstants_NameTable();
}

int main()
{
#ifdef _WIN32
    // Force LF line endings so tools/constants_values.txt is platform-stable.
    std::ignore = _setmode(_fileno(stdout), _O_BINARY);
#endif

    const int count = kwxConstants_IntCount();
    const int* const values = kwxConstants_IntTable();
    const char* const* const names = kwxConstants_NameTable();
    for (int i = 0; i < count; ++i)
    {
        std::println("{}\t{}", names[i], values[i]);
    }
    return 0;
}
