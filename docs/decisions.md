# Design Decisions

This document records key architectural and design decisions made for the kwxFFI project.

---

## Decision: Use AI Instead of Code Generation Tools

**Date**: 2024 (project inception)

**Context**: The original wxHaskell/wtc project used a Haskell-based tool to generate C wrapper functions. This approach:
- Required a working Haskell installation (non-trivial to set up)
- Used complex macros that were difficult to read and maintain
- Made customization difficult without understanding the generation tool

**Decision**: Use AI coding agents with proper instructions to generate and maintain C wrappers, rather than a traditional code generation tool.

**Rationale**:

1. **Zero setup overhead**: Any developer with access to AI coding agents can contribute. No need to install Haskell, learn the generation tool, or configure complex build dependencies.

2. **Easier customization**: Changes to wrapper patterns can be described in natural language instructions rather than modifying a code generator.

3. **Better readability**: Generated code can be expanded and cleaned up to be human-readable. The original wxHaskell code used heavy macro usage that obscured the actual logic.

4. **Faster iteration**: When implementing the 5 target language ports (Fortran, Go, Julia, LuaJIT, Rust), it's easier to adjust the FFI layer by updating instructions than by modifying a code generator.

5. **Self-documenting**: AI agents can add comments and structure code in ways that make the codebase more approachable to newcomers.

**Implications**:

- Copilot instructions (`.github/copilot-instructions.md`) must be kept accurate and comprehensive
- Wrapper patterns should be consistent so AI can learn from existing code
- Documentation becomes more important since there's no "source of truth" generator
- Code reviews matter more to catch AI-generated errors

**Status**: Accepted and in use

---

## Decision: Require wxWidgets 3.3+ with UTF-8 Mode

**Date**: 2024 (project inception)

**Context**: Before wxWidgets 3.3, `wxString` used UTF-16 on Windows and UTF-32 on some Unix systems. This required constant string conversion when interfacing with modern languages that use UTF-8.

**Decision**: Require wxWidgets 3.3+ built with `wxUSE_UNICODE_UTF8=1`.

**Rationale**:
- All target languages (Fortran, Go, Julia, LuaJIT, Rust) work with UTF-8
- Eliminates conversion overhead and complexity
- Simplifies the FFI layer
- wxWidgets 3.3 handles OS API conversion internally

**Implications**:
- Cannot use this FFI with wxWidgets 3.2 or earlier
- Build system must configure wxWidgets with UTF-8 mode
- Some legacy code patterns that assumed UTF-16 won't work

**Status**: Accepted

---

## Decision: Drop Deprecated API Support

**Date**: 2024 (project inception)

**Context**: wxHaskell wrapped many deprecated wxWidgets functions for backward compatibility.

**Decision**: Do not wrap deprecated functions, events, or constants.

**Rationale**:
- Reduces maintenance burden
- Encourages use of modern APIs
- Smaller library size
- Cleaner documentation

**Implications**:
- Code using deprecated APIs cannot be directly ported
- Must use current wxWidgets documentation as reference

**Status**: Accepted

---

## Decision: No Null Pointer Checking at the FFI Boundary

**Date**: 2026-02-18

**Context**: kwxFFI exports ~7,500 `extern "C"` wrapper functions consumed by up to 6 language bindings (Fortran, Go, Julia, LuaJIT, Perl, Rust). All wrapper functions take opaque pointer parameters (`void*` or typed `wxClass*`). The question arose whether every function should validate pointer parameters for null before dereferencing.

**Decision**: Do not add null pointer guards (`if (ptr == nullptr) return;`) to production kwxFFI wrapper functions.

**Rationale**:

1. **No security boundary exists**: kwxFFI is a same-process, user-mode library. The caller already executes code at the same privilege level. A null dereference crash gives the caller nothing they couldn't already do. Raymond Chen's "airtight hatchway" principle applies: a bug is only a security vulnerability if it crosses a defined security boundary (kernel↔user-mode, process↔process, network). MSRC's Windows Security Servicing Criteria formalizes this — same-process crashes are not vulnerabilities.

2. **Not exploitable on target platforms**: On Windows x64, Linux x64, and macOS, virtual address 0 is never mapped. A null dereference produces a guaranteed process crash (access violation / SIGSEGV), never code execution. The CVEs involving null-deref exploits (e.g., CVE-2009-2692) required kernel-mode code or the ability to mmap address 0 on pre-2009 Linux — neither applies here.

3. **Industry standard for C FFI libraries**: The Lua C API manual explicitly documents *"the Lua API functions do not check their arguments for validity or consistency"*, with opt-in checking via `LUA_USE_APICHECK` for debug builds. CPython, Win32, and JNI all follow the same contract model. GLib/GTK is the outlier that checks, specifically because it targets raw-C application authors with no type safety.

4. **Silent returns are worse than crashes**: `if (self == nullptr) return;` implies the operation succeeded. The caller observes no error, state is silently wrong, and the program blows up later in a completely unrelated place. A clean crash at the null dereference is more honest and easier to debug.

5. **Caller type systems should enforce this**: Rust's `NonNull<T>` / `Option`, Go's GC-managed pointers, and Julia's `Ptr` type all provide mechanisms to prevent null from being passed. Validation belongs in each language binding layer, not in the C wrapper.

6. **Compiler optimization hazard**: Modern compilers (MSVC /O2, Clang -O2, GCC -O2) treat null dereference as undefined behavior and may eliminate *downstream* null checks on the assumption that a pointer was valid when dereferenced. A guarding `return` added *after* a method call on a null `self` may be optimized away entirely.

**Implications**:

- All pointer parameters are documented as requiring non-null values; passing null is undefined behavior
- Each language binding (kwxRust, kwxGo, etc.) is responsible for enforcing pointer validity before calling into kwxFFI
- CWE-476 scanner findings against kwxFFI should be assessed with the above rationale — the severity on these platforms is "low" (crash/DoS only), per CERT's own severity notes
- A `KWX_DEBUG` assertion macro may be introduced in the future as an opt-in diagnostic aid for binding authors during development, following the Lua `LUA_USE_APICHECK` pattern

**Status**: Accepted

---

<!-- Template for future decisions:

## Decision: [Title]

**Date**: [YYYY-MM-DD]

**Context**: [What situation led to this decision?]

**Decision**: [What was decided?]

**Rationale**: [Why was this decision made?]

**Implications**: [What are the consequences?]

**Status**: [Proposed | Accepted | Deprecated | Superseded by...]

-->
