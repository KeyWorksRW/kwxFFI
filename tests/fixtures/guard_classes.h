// Fixture for the guard-insensitive class parser.
//
// The preprocessor guards below are deliberately never evaluated by the parser,
// so both the plain and the guarded class must land in the parsed model.

#pragma once

TClassDef(wxFixtureClass) TClass(wxFixtureClass) wxFixtureClass_Create();

void wxFixtureClass_Delete(TSelf(wxFixtureClass) pObject);

#if defined(__APPLE__)
TClassDef(wxGuardedClass) TClass(wxGuardedClass) wxGuardedClass_Create();
#endif
