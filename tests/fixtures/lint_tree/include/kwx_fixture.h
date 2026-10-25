// Fixture header for tests/checks/checker_self_test.py.
//
// Four guard shapes that the checkers must classify. Nothing in this tree is
// compiled; guard_lint and guard_parity read it as text.

#pragma once

// 1. Platform-guarded declaration with no definition anywhere: guard_lint
//    reports an error, guard_parity a no-definition-found note.
#if defined(__WINDOWS__)
TBool wxFixtureGuardedFn(int flags);
#endif

// 2. Multi-line unguarded declaration whose definition is platform-guarded:
//    guard_lint stays silent and guard_parity reports the mismatch. The
//    declaration is only visible when the scanner joins both physical lines.
TBool wxFixtureMultilineFn(TClass(wxString) first_argument,
                           TClass(wxString) second_argument);

// 3. Matching pair: the declaration and the definition carry the same guard.
//    guard_parity stays silent; guard_lint still reports the declaration,
//    because the generated binding cannot see the guard.
#ifdef __APPLE__
TBool wxFixtureMatchedFn(int flags);
#endif

// 4. Feature guard only: a note for guard_lint, no parity finding, because the
//    generator deliberately exposes the union of feature-gated declarations.
#if wxUSE_GUI
TBool wxFixtureGuiFn(int flags);
#endif
