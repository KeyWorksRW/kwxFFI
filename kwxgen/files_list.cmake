set(KWXGEN_SRC_FILES
    src/main.cpp               # Entry point, orchestrates parsing and generation
    src/class_parser.cpp       # Parses class methods from header files
    src/events_parser.cpp      # Extracts wxWidgets event declarations
    src/keys_parser.cpp        # Parses keyboard key code declarations
    src/defs_parser.cpp        # Parses constant/define declarations
    src/constants_parser.cpp   # Parses free function declarations
    src/exports_gen.cpp        # Generates platform-specific export files
    src/file_writer.cpp        # ConditionalFileWriter — writes only if content changed
    src/parser_utils.cpp       # Common parsing utilities: trim, split, macros
    src/json_dump.cpp          # Serializes parsed data to JSON
    src/md_files_gen.cpp        # Generates agent-oriented markdown docs for all languages
    src/verify.cpp             # Validates generated files against references
    src/lang/lang_fortran.cpp  # Generates Fortran FFI bindings
    src/lang/lang_go.cpp       # Generates Go FFI bindings
    src/lang/lang_julia.cpp    # Generates Julia FFI wrappers
    src/lang/lang_luajit.cpp   # Generates LuaJIT FFI declarations
    # src/lang/lang_perl.cpp     # Generates Perl FFI bindings
    src/lang/lang_typescript.cpp # Generates Deno TypeScript FFI bindings

    src/emitter.h              # Base class for language-specific code emitters
    src/model.h                # Data structures representing parsed classes, events, keys, etc.
    src/lang/lang_common.h     # Common definitions and utilities for language bindings
    src/md_files_gen.h          # Header for agent-oriented markdown doc generation

)
