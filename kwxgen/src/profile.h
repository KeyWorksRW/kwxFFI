/////////////////////////////////////////////////////////////////////////////
// Purpose:   Generation profiles that filter the parsed FFI surface
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

// A profile decides which part of the kwxFFI surface a language binding exposes.
//
//   full — every parsed class, free function, event, key and constant.
//   gui  — the base-utility classes are dropped because the target runtime already
//          supplies equivalent functionality in its standard library, but every class
//          still referenced by a retained signature (ancestor, mixin, parameter or
//          return type) is kept so the generated bindings still compile.
//
// Go and Julia default to `gui`; Fortran, LuaJIT and TypeScript default to `full`.

#pragma once

#include "model.h"

#include <string>
#include <string_view>
#include <vector>

// Every profile name, in the order they should be presented to the user.
std::vector<std::string_view> ProfileNames();

// True if profile_name is one of ProfileNames().
bool IsKnownProfile(std::string_view profile_name);

// Default profile for a language name: "go" and "julia" return "gui"; "fortran",
// "luajit", "typescript" and any unknown name return "full".
std::string DefaultProfileForLanguage(std::string_view lang);

// Return a copy of ffi_data narrowed to the requested profile. "full" (and any profile
// other than "gui") returns the input unchanged; "gui" drops the excluded classes and
// then adds back every class reachable from a retained signature. Class order follows
// the parsed order, and events, keys, constants, free functions, parent_map, mixin_map
// and lib_name are copied verbatim.
ParsedFFI ApplyProfile(const ParsedFFI& ffi_data, std::string_view profile);
