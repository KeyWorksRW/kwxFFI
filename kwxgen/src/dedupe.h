/////////////////////////////////////////////////////////////////////////////
// Purpose:   Remove repeated C symbols from the parsed model
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

// A C library has a single namespace, so an exported symbol can have only one binding. The
// FFI headers do not always honour that: kwx_classes.h declares a symbol inside its class
// block and an included header (kwx_hook_exports.h) declares the same symbol again, so the
// class parser records both. Emitters that key generated code on the symbol name then emit
// the definition twice — a hard compile error in Fortran, a silent overwrite in the others.
//
// Removing the repeats once, here, keeps every emitter honest without each one having to
// carry its own duplicate guard.

#pragma once

#include "model.h"

#include <cstddef>

// Drops every repeat of an already-seen C symbol from ffi_data, keeping the first
// declaration. Class methods take precedence over free functions, so a method binding is
// never replaced by a bare function binding. Returns the number of declarations removed.
std::size_t RemoveDuplicateFunctions(ParsedFFI& ffi_data);
