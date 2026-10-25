// Fixture implementation for tests/checks/checker_self_test.py.
//
// The guard shapes mirror tests/fixtures/lint_tree/include/kwx_fixture.h.

#include "kwx_fixture.h"

// 1. wxFixtureGuardedFn is deliberately left undefined.

// 2. Unguarded declaration, guarded definition: guard_parity must report the
//    mismatch. The definition itself spans two lines so the scanner is exercised
//    on both sides of the comparison.
#if defined(__WXMSW__)
EXPORT TBool wxFixtureMultilineFn(TClass(wxString) first_argument,
                                  TClass(wxString) second_argument)
{
    wxUnusedVar(first_argument);
    wxUnusedVar(second_argument);
    return false;
}
#endif

// 3. Matching guard: identical to the declaration in the header.
#ifdef __APPLE__
EXPORT TBool wxFixtureMatchedFn(int flags)
{
    wxUnusedVar(flags);
    return false;
}
#endif

// 4. Feature-guarded declaration with an unguarded definition: neither side
//    carries a platform guard, so guard_parity reports nothing.
EXPORT TBool wxFixtureGuiFn(int flags)
{
    wxUnusedVar(flags);
    return false;
}
