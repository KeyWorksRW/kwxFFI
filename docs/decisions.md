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

<!-- Template for future decisions:

## Decision: [Title]

**Date**: [YYYY-MM-DD]

**Context**: [What situation led to this decision?]

**Decision**: [What was decided?]

**Rationale**: [Why was this decision made?]

**Implications**: [What are the consequences?]

**Status**: [Proposed | Accepted | Deprecated | Superseded by...]

-->
