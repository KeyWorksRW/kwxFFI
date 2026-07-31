# kwxFFI/kwxgen

## ⚠️ Warning: Not Production Ready

**Do not use this library in production yet.**

Current status:
- No test suite
- No documentation
- Expect significant API churn as language bindings are developed

This library should not be used until the language ports that depend on it are fully implemented and stabilized.

---

The purpose of kwxFFI is to create language bindings for [wxWidgets](https://www.wxwidgets.org/) enabling cross-platform GUI applications that render with native controls on Windows, macOS, and Linux. Currently, five languages are under development which use kwxFFI to create the bindings:

- Fortran ([kwxFortran](https://github.com/KeyWorksRW/kwxFortran))
- Go ([kwxGO](https://github.com/KeyWorksRW/kwxGO))
- Julia ([kwxJulia](https://github.com/KeyWorksRW/kwxJulia))
- LuaJIT ([kwxLuaJIT](https://github.com/KeyWorksRW/kwxLuaJIT))
- TypeScript ([kwxTypeScript](https://github.com/KeyWorksRW/kwxTypeScript))

For information about the kwxgen tool, see [kwxgen/README.md](kwxgen/README.md)

# Credits

The original FFI code came from the wxHaskell (https://codeberg.org/wxHaskell/wxHaskell) team, which in turn was inspired by wxc project. A huge thanks go out to these teams for creating the original wxWidgets 3 interface!
