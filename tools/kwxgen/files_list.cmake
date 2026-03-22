set( KWXGEN_SRC_FILES
    main.cpp               # Entry point, orchestrates parsing and generation
    class_parser.cpp       # Parses class methods from header files
    events_parser.cpp      # Extracts wxWidgets event declarations
    keys_parser.cpp        # Parses keyboard key code declarations
    defs_parser.cpp        # Parses constant/define declarations
    constants_parser.cpp   # Parses free function declarations
    exports_gen.cpp        # Generates platform-specific export files
    parser_utils.cpp       # Common parsing utilities: trim, split, macros
    json_dump.cpp          # Serializes parsed data to JSON
    verify.cpp             # Validates generated files against references
    lang/lang_fortran.cpp  # Generates Fortran FFI bindings
    lang/lang_go.cpp       # Generates Go FFI bindings
    lang/lang_julia.cpp    # Generates Julia FFI wrappers
    lang/lang_luajit.cpp   # Generates LuaJIT FFI declarations
    lang/lang_perl.cpp     # Generates Perl FFI bindings
    lang/lang_rust.cpp     # Generates Rust FFI bindings
)
