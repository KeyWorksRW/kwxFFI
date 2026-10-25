// Fixture for the guard-insensitive constants parser.
//
// The preprocessor guards below are deliberately never evaluated by the parser,
// so both the plain and the guarded declaration must land in the parsed model.

#pragma once

TBool wxPlainFn(int flags);

#if defined(__WINDOWS__)
TBool wxGuardedFn(int flags);
#endif

WXFFI_EXPORT(int, expFIXTURE_CONST)();
