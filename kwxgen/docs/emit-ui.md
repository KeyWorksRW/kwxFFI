# `emit-ui` and `check-ui`

Two `kwxgen` subcommands that describe — and then validate — the way a language backend
expresses the wxWidgets **UI idioms** a generated application needs: building a frame or
dialog, sizing and centering it, adding children to a sizer, binding an event, loading a
bitmap from an embedded base64 string, creating a font, and assembling a standard button
sizer.

`emit-ui` produces a **UI descriptor** — a language-neutral JSON document (schema `1`) whose
values are target-language symbols. `check-ui` consumes that descriptor plus a project IR and
reports every `(wx class, role)` pair the backend cannot satisfy. Because the descriptor is
language neutral, `check-ui` can validate any project's IR against any backend's descriptor
without knowing that backend.

---

## 1. Synopsis

```text
kwxgen emit-ui  --headers <dir> --defs <file> --lang <lang> [--profile <name>] [--classes auto|<file>|form] [--out <file>|-] [--verify]
kwxgen check-ui --lang <lang> --ir <file> --descriptor <file>
```

Supported `--lang` values: `fortran`, `go`, `julia`, `lua`, `rust`, `typescript`. The string
must equal the backend's `LanguageEmitter::Name()` (`lua` is implemented by the LuaJIT
backend, whose `Name()` is `"lua"`). An unrecognised value prints `Error: unknown language
'<lang>'`, lists the available names, and exits `1`.

### `emit-ui`

| Argument | Required | Meaning |
|---|---|---|
| `--headers <dir>` | yes | kwxFFI `include/` directory. Parsed, and hashed into `generated_by.headers_hash`. |
| `--defs <file>` | yes | `src/kwx_defs.cpp`. Parsed, and hashed into `generated_by.headers_hash`. |
| `--lang <lang>` | yes | Backend that builds the descriptor. Becomes the `lang` field. |
| `--profile <name>` | no | Surface profile (`full` or `gui`). Default: `gui` for `emit-ui`, which keeps the descriptor to a reviewable size; `generate`, `verify` and `coverage` still default to `full`. An unknown profile prints `Error: unknown profile '<name>'` plus the available names and exits `1`. |
| `--classes auto\|<file>\|form` | no | Which classes the descriptor describes. Default: `auto` (every class in the profiled model); `<file>` reads one wx class name per line; `form` restricts the descriptor to the seven required classes. See §1.1. |
| `--out <file>` \| `-` | no | Output path. Omitted or `-` writes the descriptor to **stdout**. Any other value truncates that file (binary mode). |
| `--verify` | no | After writing the descriptor, verify every declared symbol against a freshly generated tree (see §9). |

The command parses the headers (`Parsing...` on stderr), applies `--profile`, selects classes
(§1.1), asks the backend for a descriptor, stamps `schema`, `lang` and `generated_by`, validates
it, serialises it as prettified JSON, and appends one trailing newline. On success it prints one
stderr line when it finishes: `Emitted <N> classes for <lang> (<U> unsupported)`.

### 1.1 Class selection

`--classes` decides which classes the descriptor describes:

| Value | Meaning |
|---|---|
| `auto` | Every class in the parsed model after `--profile` filtering — not only the classes a form happened to use. A class the backend cannot express is listed in `unsupported[]` (§4) instead of omitted. |
| `<file>` | A path to a text file naming the classes to describe, one wx class name per line. |
| `form` | Exactly the seven required classes (§4) — the behaviour before `--classes` existed. Use this mode to reproduce an already-published descriptor byte for byte. |

In a `--classes <file>` file, blank lines and lines whose first non-space character is `#` are
ignored. A name that is not in the parsed model is an error and exits `1`:

```text
Error: --classes file names unknown classes: <comma-separated>
```

An unreadable file prints `Error: cannot read classes file '<path>'` and exits `1`.

If the file leaves out one of the seven required classes, the class is recorded in
`unsupported[]` with an empty `role` and reason `not_in_profile`, so the descriptor still
validates.

The default is `auto`.

### `check-ui`

| Argument | Required | Meaning |
|---|---|---|
| `--lang <lang>` | yes | Must equal the descriptor's `lang`; otherwise `Error: descriptor language '<a>' does not match --lang '<b>'` and exit `1`. |
| `--ir <file>` | yes | Project IR (see §7). |
| `--descriptor <file>` | yes | Descriptor produced by `emit-ui` (or hand-maintained). |

`MISSING` lines go to **stdout**; diagnostics go to **stderr**.

---

## 2. The descriptor (schema `1`)

The file is JSON produced by `glz` with `prettify = true`. When a document is **read**, unknown
keys are tolerated (`error_on_unknown_keys = false`) and every field not present takes its
default — so a truncated descriptor usually fails validation rather than parsing.

### 2.1 Complete example

The document below is structurally valid: it names all seven required classes, covers every
required role either with a usable callable or with an `unsupported` entry, and satisfies the
mandatory global blocks. Symbol names are illustrative Go wrapper names; run
`kwxgen emit-ui --lang go --headers include --defs src/kwx_defs.cpp` for the authoritative
descriptor.

```json
{
  "schema": 1,
  "lang": "go",
  "generated_by": {
    "tool": "kwxgen",
    "version": "1.0.0",
    "headers_hash": "1f0c6a5e9b3d2748",
    "profile": "gui"
  },
  "naming": {
    "class_type": "PascalCase handle type, e.g. Frame",
    "constructor": "New<Class>, e.g. NewDialog",
    "method": "PascalCase, e.g. ShowModal",
    "constant": "UPPER_SNAKE_CASE, e.g. wxOK",
    "module": "package wx"
  },
  "classes": {
    "wxFrame": {
      "type": "Frame",
      "idiom": "constructor",
      "ctor": {
        "symbol": "NewFrame",
        "params": [
          {"name": "parent", "type": "Frame"},
          {"name": "id", "type": "int"},
          {"name": "title", "type": "string"}
        ],
        "idiom": "constructor",
        "returns": "Frame",
        "sentinels": {"parent": "nil"}
      },
      "roles": {
        "show": {"symbol": "Show", "params": [], "idiom": "method-on-self"},
        "hide": {"symbol": "Hide", "params": [], "idiom": "method-on-self"},
        "set_title": {"symbol": "SetTitle", "params": [{"name": "title", "type": "string"}], "idiom": "method-on-self"},
        "set_size": {"symbol": "SetSize", "params": [{"name": "width", "type": "int"}, {"name": "height", "type": "int"}], "idiom": "method-on-self"},
        "set_min_size": {"symbol": "SetMinSize", "params": [{"name": "width", "type": "int"}, {"name": "height", "type": "int"}], "idiom": "method-on-self"},
        "center": {"symbol": "Centre", "params": [], "idiom": "method-on-self"},
        "set_sizer": {"symbol": "SetSizer", "params": [{"name": "sizer", "type": "Sizer"}], "idiom": "method-on-self"},
        "set_font": {"symbol": "SetFont", "params": [{"name": "font", "type": "Font"}], "idiom": "method-on-self"},
        "set_icon": {"symbol": "SetIcon", "params": [{"name": "icon", "type": "Icon"}], "idiom": "method-on-self"},
        "create_statusbar": {"symbol": "CreateStatusBar", "params": [], "idiom": "method-on-self"},
        "set_menubar": {"symbol": "SetMenuBar", "params": [{"name": "bar", "type": "MenuBar"}], "idiom": "method-on-self"},
        "bind": {"symbol": "Bind", "params": [{"name": "event", "type": "EventType"}, {"name": "handler", "type": "func(Event)"}], "idiom": "method-on-self"},
        "bind_id": {"symbol": "BindById", "params": [{"name": "id", "type": "int"}, {"name": "event", "type": "EventType"}, {"name": "handler", "type": "func(Event)"}], "idiom": "method-on-self"},
        "destroy": {"symbol": "Destroy", "params": [], "idiom": "method-on-self"},
        "ptr": {"symbol": "Ptr", "params": [], "idiom": "method-on-self"},
        "delete": {"symbol": "DeleteFrame", "params": [{"name": "frame", "type": "Frame"}], "idiom": "procedure"}
      },
      "constants": {}
    },
    "wxDialog": {
      "type": "Dialog",
      "idiom": "constructor",
      "ctor": {
        "symbol": "NewDialog",
        "params": [{"name": "parent", "type": "Frame"}, {"name": "id", "type": "int"}, {"name": "title", "type": "string"}],
        "idiom": "constructor",
        "returns": "Dialog"
      },
      "roles": {
        "show": {"symbol": "Show", "params": [], "idiom": "method-on-self"},
        "hide": {"symbol": "Hide", "params": [], "idiom": "method-on-self"},
        "set_title": {"symbol": "SetTitle", "params": [{"name": "title", "type": "string"}], "idiom": "method-on-self"},
        "set_size": {"symbol": "SetSize", "params": [{"name": "width", "type": "int"}, {"name": "height", "type": "int"}], "idiom": "method-on-self"},
        "set_min_size": {"symbol": "SetMinSize", "params": [{"name": "width", "type": "int"}, {"name": "height", "type": "int"}], "idiom": "method-on-self"},
        "center": {"symbol": "Centre", "params": [], "idiom": "method-on-self"},
        "set_sizer": {"symbol": "SetSizer", "params": [{"name": "sizer", "type": "Sizer"}], "idiom": "method-on-self"},
        "set_font": {"symbol": "SetFont", "params": [{"name": "font", "type": "Font"}], "idiom": "method-on-self"},
        "set_icon": {"symbol": "SetIcon", "params": [{"name": "icon", "type": "Icon"}], "idiom": "method-on-self"},
        "show_modal": {"symbol": "ShowModal", "params": [], "idiom": "method-on-self", "returns": "int"},
        "end_modal": {"symbol": "EndModal", "params": [{"name": "result", "type": "int"}], "idiom": "method-on-self"},
        "bind": {"symbol": "Bind", "params": [{"name": "event", "type": "EventType"}, {"name": "handler", "type": "func(Event)"}], "idiom": "method-on-self"},
        "bind_id": {"symbol": "BindById", "params": [{"name": "id", "type": "int"}, {"name": "event", "type": "EventType"}, {"name": "handler", "type": "func(Event)"}], "idiom": "method-on-self"},
        "destroy": {"symbol": "Destroy", "params": [], "idiom": "method-on-self"},
        "ptr": {"symbol": "Ptr", "params": [], "idiom": "method-on-self"},
        "delete": {"symbol": "DeleteDialog", "params": [{"name": "dialog", "type": "Dialog"}], "idiom": "procedure"}
      },
      "constants": {}
    },
    "wxTextCtrl": {
      "type": "TextCtrl",
      "idiom": "constructor",
      "ctor": {
        "symbol": "NewTextCtrl",
        "params": [{"name": "parent", "type": "Window"}, {"name": "id", "type": "int"}, {"name": "value", "type": "string"}],
        "idiom": "constructor",
        "returns": "TextCtrl"
      },
      "roles": {
        "show": {"symbol": "Show", "params": [], "idiom": "method-on-self"},
        "hide": {"symbol": "Hide", "params": [], "idiom": "method-on-self"},
        "set_value": {"symbol": "SetValue", "params": [{"name": "value", "type": "string"}], "idiom": "method-on-self"},
        "set_label": {"symbol": "SetLabel", "params": [{"name": "label", "type": "string"}], "idiom": "method-on-self"},
        "set_size": {"symbol": "SetSize", "params": [{"name": "width", "type": "int"}, {"name": "height", "type": "int"}], "idiom": "method-on-self"},
        "set_min_size": {"symbol": "SetMinSize", "params": [{"name": "width", "type": "int"}, {"name": "height", "type": "int"}], "idiom": "method-on-self"},
        "set_font": {"symbol": "SetFont", "params": [{"name": "font", "type": "Font"}], "idiom": "method-on-self"},
        "set_size_hints": {"symbol": "SetSizeHints", "params": [], "idiom": "method-on-self"},
        "bind": {"symbol": "Bind", "params": [{"name": "event", "type": "EventType"}, {"name": "handler", "type": "func(Event)"}], "idiom": "method-on-self"},
        "bind_id": {"symbol": "BindById", "params": [{"name": "id", "type": "int"}, {"name": "event", "type": "EventType"}, {"name": "handler", "type": "func(Event)"}], "idiom": "method-on-self"},
        "destroy": {"symbol": "Destroy", "params": [], "idiom": "method-on-self"},
        "ptr": {"symbol": "Ptr", "params": [], "idiom": "method-on-self"},
        "delete": {"symbol": "DeleteTextCtrl", "params": [{"name": "ctrl", "type": "TextCtrl"}], "idiom": "procedure"}
      },
      "constants": {}
    },
    "wxBoxSizer": {
      "type": "BoxSizer",
      "idiom": "constructor",
      "ctor": {"symbol": "NewBoxSizer", "params": [{"name": "orient", "type": "int"}], "idiom": "constructor", "returns": "BoxSizer"},
      "roles": {
        "add_window": {"symbol": "AddWindow", "params": [{"name": "window", "type": "Window"}, {"name": "proportion", "type": "int"}, {"name": "flags", "type": "SizerFlags"}], "idiom": "method-on-self"},
        "add_sizer": {"symbol": "AddSizer", "params": [{"name": "sizer", "type": "Sizer"}, {"name": "proportion", "type": "int"}, {"name": "flags", "type": "SizerFlags"}], "idiom": "method-on-self"},
        "add_spacer": {"symbol": "AddSpacer", "params": [{"name": "size", "type": "int"}], "idiom": "method-on-self"},
        "destroy": {"symbol": "Destroy", "params": [], "idiom": "method-on-self"},
        "ptr": {"symbol": "Ptr", "params": [], "idiom": "method-on-self"},
        "delete": {"symbol": "DeleteBoxSizer", "params": [{"name": "sizer", "type": "BoxSizer"}], "idiom": "procedure"}
      },
      "constants": {}
    },
    "wxStdDialogButtonSizer": {
      "type": "StdDialogButtonSizer",
      "idiom": "method-on-parent",
      "ctor": {
        "symbol": "CreateStdDialogButtonSizer",
        "params": [{"name": "flags", "type": "int"}],
        "idiom": "method-on-parent",
        "owner": "wxDialog",
        "returns": "StdDialogButtonSizer"
      },
      "roles": {
        "add_button": {"symbol": "AddButton", "params": [{"name": "button", "type": "Window"}], "idiom": "method-on-self"},
        "realize": {"symbol": "Realize", "params": [], "idiom": "method-on-self"},
        "add_window": {"symbol": "AddWindow", "params": [{"name": "window", "type": "Window"}, {"name": "proportion", "type": "int"}, {"name": "flags", "type": "SizerFlags"}], "idiom": "method-on-self"},
        "destroy": {"symbol": "Destroy", "params": [], "idiom": "method-on-self"},
        "ptr": {"symbol": "Ptr", "params": [], "idiom": "method-on-self"},
        "delete": {"symbol": "DeleteStdButtonSizer", "params": [{"name": "sizer", "type": "StdDialogButtonSizer"}], "idiom": "procedure"}
      },
      "constants": {}
    },
    "wxStaticBitmap": {
      "type": "StaticBitmap",
      "idiom": "constructor",
      "ctor": {"symbol": "NewStaticBitmap", "params": [{"name": "parent", "type": "Window"}, {"name": "bitmap", "type": "Bitmap"}], "idiom": "constructor", "returns": "StaticBitmap"},
      "roles": {
        "set_bitmap": {"symbol": "SetBitmap", "params": [{"name": "bitmap", "type": "Bitmap"}], "idiom": "method-on-self"},
        "set_size": {"symbol": "SetSize", "params": [{"name": "width", "type": "int"}, {"name": "height", "type": "int"}], "idiom": "method-on-self"},
        "set_min_size": {"symbol": "SetMinSize", "params": [{"name": "width", "type": "int"}, {"name": "height", "type": "int"}], "idiom": "method-on-self"},
        "show": {"symbol": "Show", "params": [], "idiom": "method-on-self"},
        "hide": {"symbol": "Hide", "params": [], "idiom": "method-on-self"},
        "destroy": {"symbol": "Destroy", "params": [], "idiom": "method-on-self"},
        "ptr": {"symbol": "Ptr", "params": [], "idiom": "method-on-self"},
        "delete": {"symbol": "DeleteStaticBitmap", "params": [{"name": "bitmap", "type": "StaticBitmap"}], "idiom": "procedure"}
      },
      "constants": {}
    },
    "wxSizerFlags": {
      "type": "SizerFlags",
      "idiom": "constructor",
      "ctor": {"symbol": "NewSizerFlags", "params": [{"name": "proportion", "type": "int"}], "idiom": "constructor", "returns": "SizerFlags"},
      "roles": {
        "proportion": {"symbol": "Proportion", "params": [{"name": "value", "type": "int"}], "idiom": "builder"},
        "expand": {"symbol": "Expand", "params": [], "idiom": "builder"},
        "border": {"symbol": "Border", "params": [{"name": "flags", "type": "int"}], "idiom": "builder"},
        "left": {"symbol": "Left", "params": [], "idiom": "builder"},
        "right": {"symbol": "Right", "params": [], "idiom": "builder"},
        "top": {"symbol": "Top", "params": [], "idiom": "builder"},
        "bottom": {"symbol": "Bottom", "params": [], "idiom": "builder"},
        "align_h": {"symbol": "CenterHorizontal", "params": [], "idiom": "builder"},
        "align_v": {"symbol": "CenterVertical", "params": [], "idiom": "builder"},
        "delete": {"symbol": "DeleteSizerFlags", "params": [{"name": "flags", "type": "SizerFlags"}], "idiom": "procedure"}
      },
      "constants": {}
    }
  },
  "sizers": {
    "wxBoxSizer": {
      "ctor": {"symbol": "NewBoxSizer", "params": [{"name": "orient", "type": "int"}], "idiom": "constructor", "returns": "BoxSizer"},
      "add_window": {"symbol": "AddWindow", "params": [{"name": "window", "type": "Window"}, {"name": "proportion", "type": "int"}, {"name": "flags", "type": "SizerFlags"}], "idiom": "method-on-self"},
      "add_sizer": {"symbol": "AddSizer", "params": [{"name": "sizer", "type": "Sizer"}, {"name": "proportion", "type": "int"}, {"name": "flags", "type": "SizerFlags"}], "idiom": "method-on-self"},
      "add_spacer": {"symbol": "AddSpacer", "params": [{"name": "size", "type": "int"}], "idiom": "method-on-self"}
    },
    "flags": {
      "ctor": {"symbol": "NewSizerFlags", "params": [{"name": "proportion", "type": "int"}], "idiom": "constructor", "returns": "SizerFlags"},
      "proportion": {"symbol": "Proportion", "params": [{"name": "value", "type": "int"}], "idiom": "builder"},
      "expand": {"symbol": "Expand", "params": [], "idiom": "builder"},
      "border": {"symbol": "Border", "params": [{"name": "flags", "type": "int"}], "idiom": "builder"},
      "left": {"symbol": "Left", "params": [], "idiom": "builder"},
      "right": {"symbol": "Right", "params": [], "idiom": "builder"},
      "top": {"symbol": "Top", "params": [], "idiom": "builder"},
      "bottom": {"symbol": "Bottom", "params": [], "idiom": "builder"},
      "align_h": {"symbol": "CenterHorizontal", "params": [], "idiom": "builder"},
      "align_v": {"symbol": "CenterVertical", "params": [], "idiom": "builder"}
    }
  },
  "events": {
    "bind": {"symbol": "Bind", "params": [{"name": "event", "type": "EventType"}, {"name": "handler", "type": "func(Event)"}], "idiom": "procedure"},
    "bind_id": {"symbol": "BindById", "params": [{"name": "id", "type": "int"}, {"name": "event", "type": "EventType"}, {"name": "handler", "type": "func(Event)"}], "idiom": "procedure"},
    "handler_type": "func(Event)"
  },
  "bitmap": {
    "from_base64": {"symbol": "BitmapFromBase64", "params": [{"name": "data", "type": "string"}], "idiom": "procedure", "returns": "Bitmap"},
    "get_bitmap": {"symbol": "GetBitmap", "params": [], "idiom": "method-on-self"},
    "delete": {"symbol": "DeleteBitmap", "params": [{"name": "bitmap", "type": "Bitmap"}], "idiom": "procedure"}
  },
  "font": {
    "create": {"symbol": "NewFont", "params": [{"name": "point_size", "type": "int"}, {"name": "family", "type": "int"}, {"name": "style", "type": "int"}, {"name": "weight", "type": "int"}], "idiom": "procedure", "returns": "Font"},
    "delete": {"symbol": "DeleteFont", "params": [{"name": "font", "type": "Font"}], "idiom": "procedure"}
  },
  "std_buttons": {
    "create": {"symbol": "CreateStdDialogButtonSizer", "params": [{"name": "flags", "type": "int"}], "idiom": "method-on-parent", "owner": "wxDialog", "returns": "StdDialogButtonSizer"},
    "add_button": {"symbol": "AddButton", "params": [{"name": "button", "type": "Window"}], "idiom": "method-on-self"},
    "realize": {"symbol": "Realize", "params": [], "idiom": "method-on-self"}
  },
  "app": {
    "entry": "main",
    "entry_signature": "func main()",
    "set_top_window": {"symbol": "SetTopWindow", "params": [{"name": "window", "type": "Window"}], "idiom": "procedure"},
    "emit_entry": true
  },
  "unsupported": [
    {"class": "wxDialog", "role": "set_escape_id", "reason": "no_method"},
    {"class": "wxDialog", "role": "set_affirmative_id", "reason": "no_method"}
  ]
}
```

### 2.2 Annotated callable

Every entry inside `classes.<cls>.ctor`, `classes.<cls>.roles`, `sizers.*`, `events.*`,
`bitmap.*`, `font.*`, `std_buttons.*` and `app.set_top_window` is a **callable** with the same
five (optionally six) keys. The fence below is JSON-with-comments — the comments are not part of
the document.

```jsonc
{
  "symbol": "SetTitle",              // target-language symbol; empty => backend cannot express this idiom
  "params": [                        // call-site arguments, receiver EXCLUDED
    {"name": "title", "type": "string"}
  ],
  "idiom": "method-on-self",         // one of the six idioms in §5
  "owner": "wxDialog",               // method-on-parent only: the class that carries the method
  "returns": "Frame",                // set when the call yields a new handle
  "reason": "no_method"              // required when symbol is empty; one of the codes in §6
}
```

**`params` are the arguments written at the call site, after the implicitly bound receiver.**
For a `method-on-self` callable the receiver is therefore *not* listed — `{"symbol": "SetTitle",
"params": [{"name": "title", "type": "string"}], "idiom": "method-on-self"}` means
`receiver.SetTitle(title)`. For a `procedure` (free function) every argument *is* listed, which
is why the `delete` entries above repeat the handle as a parameter.

**`sentinels`** is a `param → default-literal` map, and is meaningful for a **constructor** only.
It records the literal a backend must emit for a parameter the caller omits, e.g.
`"sentinels": {"parent": "nil"}` on `wxFrame.ctor` means "pass `nil` when no parent is given".
Keys are `params[].name` values; values are literal source text in the target language, not
JSON values. Validation does not reject `sentinels` on a non-ctor callable, but backends
should not populate it there.

### 2.3 Key reference

| Key | Type | Meaning / validation |
|---|---|---|
| `schema` | integer | Must be exactly `1`. Any other value fails validation with `schema must be 1`. |
| `lang` | string | Must be non-empty. `emit-ui` sets it from `LanguageEmitter::Name()`; `check-ui` requires it to equal `--lang`. |
| `generated_by.tool` | string | Non-empty. `emit-ui` writes `kwxgen`. |
| `generated_by.version` | string | Non-empty. `emit-ui` writes `1.0.0`. |
| `generated_by.headers_hash` | string | Non-empty. 16 lowercase hex characters produced by `emit-ui` — see §10. |
| `generated_by.profile` | string | Non-empty. The **resolved** profile (explicit `--profile`, or `emit-ui`'s default `gui`). |
| `naming.class_type` | string | Non-empty, required. How a class handle type is spelled. |
| `naming.constructor` | string | Non-empty, required. How a constructor is spelled. |
| `naming.method` | string | Non-empty, required. How a method is spelled. |
| `naming.constant` | string | Non-empty, required. How a constant is spelled. |
| `naming.module` | string | Non-empty, required. Module / package / unit naming. |
| `classes` | object | Map of `wxClass → class object`. Any class, not just the required seven. |
| `classes.<cls>.type` | string | Target-language handle type name. Not validated. |
| `classes.<cls>.idiom` | string | How an instance is obtained. Not validated; see §5. |
| `classes.<cls>.ctor` | callable | Required for a listed required class: `ctor.symbol` must be non-empty. |
| `classes.<cls>.roles` | object | Map of `role → callable`. Every role key must be in the closed vocabulary (§3). |
| `classes.<cls>.constants` | object | Map of `name → value` string constants. Not validated. |
| `sizers.wxBoxSizer.ctor` | callable | Required (usable or a valid reason). |
| `sizers.wxBoxSizer.add_window` | callable | Required. |
| `sizers.wxBoxSizer.add_sizer` | callable | Required. |
| `sizers.wxBoxSizer.add_spacer` | callable | Required. |
| `sizers.flags.ctor` | callable | Required. |
| `sizers.flags.proportion` | callable | Required. |
| `sizers.flags.expand` | callable | Required. |
| `sizers.flags.border` | callable | Required. |
| `sizers.flags.left` | callable | Required. |
| `sizers.flags.right` | callable | Required. |
| `sizers.flags.top` | callable | Required. |
| `sizers.flags.bottom` | callable | Required. |
| `sizers.flags.align_h` | callable | Required. |
| `sizers.flags.align_v` | callable | Required. |
| `events.bind` | callable | Required. |
| `events.bind_id` | callable | Required. |
| `events.handler_type` | string | Target-language handler signature. Not validated. |
| `bitmap.from_base64` | callable | Required. |
| `bitmap.get_bitmap` | callable | Required. |
| `bitmap.delete` | callable | Required. (JSON key `delete`; the C++ member is `delete_fn`.) |
| `font.create` | callable | Required. |
| `font.delete` | callable | Required. (JSON key `delete`.) |
| `std_buttons.create` | callable | Required. |
| `std_buttons.add_button` | callable | Required. |
| `std_buttons.realize` | callable | Required. |
| `app.entry` | string | Entry-point symbol name. Not validated. |
| `app.entry_signature` | string | Full entry-point signature as source text. Not validated. |
| `app.set_top_window` | callable | Required. |
| `app.emit_entry` | boolean | Whether the UI layer owns the entry point. Defaults to `false`. Not validated. |
| `unsupported` | array | Each item `{"class": <wxClass>, "role": <role>, "reason": <code>}`. An **empty** `role` marks the whole class as unsupported; a non-empty `role` must be in the closed vocabulary. `emit-ui` lists every selected class it cannot express here (§4); whole-class reasons are the four codes in §6.1. |

"Required" in the table means the field must be *usable* — non-empty `symbol` and an idiom
other than `unsupported` — or carry a non-empty, known `reason` code. A required entry with
neither fails with `required mapping '<label>' has neither a symbol nor a valid reason code`,
where `<label>` is the dotted path (e.g. `sizers.flags.expand`, `events.bind`,
`std_buttons.realize`, `app.set_top_window`).

Validation also enforces callable shape: a symbol-less callable **must** carry a reason
(`<label>: callable has no symbol and no reason code`); a callable with a symbol **must** carry
an idiom (`<label>: callable '<symbol>' has no idiom`), must not use the `unsupported` idiom
(`... uses the unsupported idiom`), and if its idiom is `method-on-parent` it **must** carry
`owner` (`... has no owner`).

A class that is not one of the seven required classes is described by its constructor only:
`classes.<cls>` carries `ctor`, because per-class `roles` exist only where the descriptor schema
defines required roles for that class.

---

## 3. Closed role vocabulary

Roles name an idiom, not a method. Anything outside this list — in `classes.<cls>.roles`,
in an `unsupported[].role`, or in an IR `roles_used` entry — is a usage error and fails the run.

```text
ctor              show                hide               set_title
set_label         set_value           set_size           set_min_size
center            set_sizer           set_size_hints     set_font
set_icon          set_bitmap          create_statusbar   set_menubar
show_modal        end_modal           set_escape_id      set_affirmative_id
bind              bind_id             destroy            ptr
delete            add_window          add_sizer          add_spacer
realize           add_button          proportion         expand
border            left                right              top
bottom            align_h             align_v            create
get_bitmap        from_base64
```

42 roles in total. A descriptor role key outside the list fails `emit-ui` with
`class '<cls>' uses the unknown role '<role>'`; an `unsupported[].role` outside the list fails
with `unsupported entry '<cls>' uses the unknown role '<role>'`; an IR role outside the list
fails `check-ui` with `Error: IR uses the unknown role '<role>' on the node class '<cls>'`
and exit `1`.

---

## 4. Required classes

A UI-capable backend must account for exactly these classes; each is either **fully described**
in `classes` or **explicitly listed** in `unsupported` with an empty `role`
(`{"class": "wxFrame", "role": "", "reason": "not_supported"}`).

`emit-ui` never silently drops a class: every selected class the backend cannot express is
listed in `unsupported[]`, because an omitted class is indistinguishable from an unmodelled one.
An empty `role` means the whole class is unsupported; a non-empty `role` means that role only.
Whole-class entries use one of the four class-level reason codes in §6.1.

| Class | Required roles |
|---|---|
| `wxFrame` | `ctor` `show` `hide` `set_title` `set_size` `set_min_size` `center` `set_sizer` `set_font` `set_icon` `create_statusbar` `set_menubar` `bind` `bind_id` `destroy` `ptr` `delete` |
| `wxDialog` | `ctor` `show` `hide` `set_title` `set_size` `set_min_size` `center` `set_sizer` `set_font` `set_icon` `show_modal` `end_modal` `set_escape_id` `set_affirmative_id` `bind` `bind_id` `destroy` `ptr` `delete` |
| `wxTextCtrl` | `ctor` `show` `hide` `set_value` `set_label` `set_size` `set_min_size` `set_font` `set_size_hints` `bind` `bind_id` `destroy` `ptr` `delete` |
| `wxBoxSizer` | `ctor` `add_window` `add_sizer` `add_spacer` `destroy` `ptr` `delete` |
| `wxStaticBitmap` | `ctor` `set_bitmap` `set_size` `set_min_size` `show` `hide` `destroy` `ptr` `delete` |
| `wxStdDialogButtonSizer` | `ctor` `add_button` `realize` `add_window` `destroy` `ptr` `delete` |
| `wxSizerFlags` | `ctor` `proportion` `expand` `border` `left` `right` `top` `bottom` `align_h` `align_v` `delete` |

Coverage rules:

- A class absent from `classes` and not listed with an empty `role` fails with
  `required class '<cls>' is neither implemented nor listed in unsupported`.
- A class present in `classes` **and** also listed with an empty `role` fails with
  `required class '<cls>' appears in classes and is also listed in unsupported with an empty role`.
- A class present in `classes` with an empty `ctor.symbol` fails with
  `required class '<cls>' has no constructor symbol`.
- A required role that is neither usable nor listed in `unsupported` fails with
  `required class '<cls>' role '<role>' is neither usable nor listed in unsupported`.

Coverage is validated **before** the structural rules, so a missing class is reported in
preference to a stray bad idiom — a class the backend cannot build at all is the more useful
diagnostic.

---

## 5. Idioms

`idiom` appears on every callable and on `classes.<cls>.idiom`. The vocabulary is closed:

| Idiom | Meaning at the call site |
|---|---|
| `constructor` | A symbol that allocates and returns a new handle. `params` are the constructor's arguments; `returns` names the produced handle type. |
| `builder` | A symbol that returns the receiver (or a new flags object) so calls can be chained. Used for the `sizers.flags.*` operations. |
| `procedure` | A free function with no implicit receiver. Every argument appears in `params` — including the handle being operated on, which is how `delete` is expressed above. |
| `method-on-self` | A method invoked on the handle of the class itself: `handle.Symbol(args)`. The receiver is implicit, so it is absent from `params`. |
| `method-on-parent` | A method that lives on an **ancestor**; `owner` names the class that carries it, and `returns` names the produced handle. `owner` is mandatory — a `method-on-parent` callable without it fails validation. |
| `unsupported` | The backend has no way to express this idiom. The callable is treated as unusable and must carry a `reason`. |

`unsupported` is also legal as `classes.<cls>.idiom`, meaning the whole class has no wrapper
idiom; such a class belongs in the `unsupported` array with an empty `role`.

### wxStdDialogButtonSizer

`wxStdDialogButtonSizer` is not constructed. Go, TypeScript and Lua emit it as a method on
`wxDialog`:

```text
dlg.CreateStdDialogButtonSizer(flags)
```

so its callable is `{"symbol": "CreateStdDialogButtonSizer", "params": [{"name": "flags",
"type": "int"}], "idiom": "method-on-parent", "owner": "wxDialog", "returns":
"StdDialogButtonSizer"}` — both as `classes.wxStdDialogButtonSizer.ctor` and as
`std_buttons.create`. Marking it `constructor` would tell a consumer to emit
`NewStdDialogButtonSizer(...)`, which does not exist.

---

## 6. Reason codes

Closed vocabulary, used in `reason` (on a symbol-less callable) and in `unsupported[].reason`.
For the entries it writes, `emit-ui` uses only `not_supported`, `no_method`, `no_naming` and
`not_in_profile`; §6.1 gives their class-level meaning. The remaining codes are for
hand-maintained descriptors.

| Code | When it applies |
|---|---|
| `no_method` | kwxFFI exposes no method for the idiom — the C surface itself is missing, so no backend can wrap it. Use for a role like `set_escape_id` where the underlying FFI call is absent. |
| `no_naming` | The method exists but the backend has no defensible name for it (collides with a reserved word, duplicates an existing member, or falls outside the backend's naming scheme). |
| `not_supported` | The target language genuinely cannot express the idiom — no builder pattern, no function-pointer handler, no native handle type. |
| `not_in_profile` | The symbol is excluded by the surface profile the descriptor was generated for (e.g. a `gui`-profile descriptor that drops base-utility classes), or a required class was excluded by an explicit `--classes <file>` selection. |
| `ambiguous` | Two or more candidate methods map to the same role and the backend cannot pick one deterministically. |
| `hand_maintained` | The symbol is written by hand in the consumer repository, outside the generated tree, so the generator must not claim or verify it. |

Unknown codes fail validation twice over: once while walking the descriptor
(`<label>: unknown reason code '<code>'`) and once for required global blocks
(`required mapping '<label>' has neither a symbol nor a valid reason code`).

### 6.1 Class-level reason codes

For a whole-class entry (empty `role`) in `unsupported[]`, `emit-ui` uses only these codes:

| Code | Meaning |
|---|---|
| `not_supported` | The backend deliberately does not wrap this class — a skipped struct, or a class provided by the target runtime's standard library. |
| `no_method` | The parsed model has no usable true constructor for the class; a two-phase `Create()` pattern counts as no constructor. |
| `no_naming` | A constructor exists, but the backend cannot spell an idiomatic symbol for it. |
| `not_in_profile` | A required class was excluded by an explicit `--classes <file>` selection. |

---

## 7. The project IR consumed by `check-ui`

`check-ui` reads a small, tolerantly parsed document. Unknown keys are ignored and every field
defaults, so an omitted field is not a parse error.

```json
{
  "schema": 1,
  "project": "myapp",
  "forms": [
    {
      "class_name": "MainFrame",
      "node_class": "wxFrame",
      "children": [
        {
          "node_class": "wxTextCtrl",
          "var_name": "name_input",
          "roles_used": ["set_value", "bind"],
          "in_sizer": true
        },
        {
          "node_class": "wxBoxSizer",
          "var_name": "row_sizer",
          "roles_used": ["add_window"],
          "in_sizer": true
        }
      ]
    }
  ]
}
```

| Key | Meaning |
|---|---|
| `schema` | Must be `1`; otherwise `Error: IR schema must be 1, found <n>` and exit `1`. |
| `project` | Project name. Not used in any check. |
| `forms[]` | Top-level windows. |
| `forms[].class_name` | Generated class name. Not used in any check. |
| `forms[].node_class` | wx class of the form. Its `ctor` is always required. |
| `forms[].children[]` | Child nodes. |
| `children[].node_class` | wx class of the child. |
| `children[].var_name` | Variable name. Not used in any check. |
| `children[].roles_used[]` | Roles the generated code calls on this child. Every entry must be in the closed vocabulary (§3). |
| `children[].in_sizer` | `true` when the child is added to a sizer; adds a placement requirement (below). |

### Resolution order

For a `(node_class, role)` pair, `check-ui` uses `ResolveCallable` in this order and stops at
the first applicable rule:

1. **The class itself owns the answer.** If `classes[node_class]` exists:
   - `role == "ctor"` → `classes[node_class].ctor`, usable or the pair is **unresolved**. There
     is no fallthrough — a listed class that names its constructor is authoritative.
   - else if `classes[node_class].roles[role]` exists → that callable, usable or
     **unresolved**, again with no fallthrough.
   - else (the class exists but does not name this role) → continue to step 2.
2. **Box-sizer operations.** If `node_class` is a sizer class — `wxBoxSizer`, or any name
   ending in `Sizer` — and `role` is `ctor`, `add_window`, `add_sizer` or `add_spacer`, the
   corresponding entry under `sizers.wxBoxSizer` answers.
3. **Sizer flags.** If `role` is one of `proportion`, `expand`, `border`, `left`, `right`,
   `top`, `bottom`, `align_h`, `align_v`, the corresponding entry under `sizers.flags` answers.
4. `role == "bind"` → `events.bind`; `role == "bind_id"` → `events.bind_id`.
5. `role == "from_base64"` → `bitmap.from_base64`; `role == "get_bitmap"` →
   `bitmap.get_bitmap`.
6. `role == "add_button"` → `std_buttons.add_button`; `role == "realize"` →
   `std_buttons.realize`.
7. `role == "create"` → `font.create` when `node_class` is `wxFont`, `std_buttons.create` when
   it is `wxStdDialogButtonSizer`; for any other class, `font.create` if usable, otherwise
   `std_buttons.create` if usable.
8. `role == "delete"` → `font.delete` when `node_class` is `wxFont`, `bitmap.delete` when it is
   `wxBitmap`, otherwise unresolved.
9. **Generic sizer fallback.** Any `add_window` / `add_sizer` / `add_spacer` role resolves to
   the matching `sizers.wxBoxSizer` entry, whatever the class — every widget can be handed to a
   box sizer.
10. Otherwise the pair is unresolved.

"Usable" throughout means non-empty `symbol` **and** an idiom other than `unsupported`.

### What is required

- Every form's `node_class` + `ctor`.
- Every role listed in a child's `roles_used`.
- When a child has `in_sizer: true`: `add_sizer` if the child is a sizer class (`wxBoxSizer`
  or a name ending in `Sizer`, which includes `wxStdDialogButtonSizer`), otherwise
  `add_window`.

Each unresolved pair produces exactly one line on **stdout**, in discovery order, deduplicated
by `(class, role)`:

```text
MISSING <lang> <class> <role>
```

`<lang>` is taken from the **descriptor**, not from `--lang`. Example:

```text
MISSING go wxStaticBitmap set_bitmap
MISSING go wxStdDialogButtonSizer add_sizer
```

---

## 8. Exit codes

### `emit-ui`

| Code | Meaning |
|---|---|
| `0` | Descriptor written (and, with `--verify`, no mismatches). |
| `1` | Usage error (`missing --headers/--defs`, `missing --lang`, unknown language, unknown profile, unknown class in a `--classes` file, unreadable `--classes` file), parse-profile failure, invalid descriptor, serialization failure, unopenable `--out` file, or at least one `--verify` mismatch. |

### `check-ui`

| Code | Meaning |
|---|---|
| `0` | Every `(class, role)` pair the IR needs is supported. |
| `2` | At least one `MISSING` line was printed. |
| `1` | Usage error, unreadable input file, descriptor or IR parse error, IR `schema` not `1`, unknown role in `roles_used`, or `descriptor.lang != --lang`. |

`2` versus `1` is deliberate: a consumer can treat `2` as "this project needs work" and `1` as
"the inputs are wrong".

---

## 9. The `--verify` contract

With `--verify`, `emit-ui` proves the descriptor describes code the backend actually generates:

1. A temporary directory `<temp>/kwxgen_emit_ui_<lang>` is removed if it exists, then created.
2. `emit-ui` runs the backend's `Generate()` into that directory, then calls
   `VerifyUiDescriptor(descriptor, temp_dir)`, which inspects the generated files and checks
   every declared symbol.
3. The temporary directory is removed — on both the matching and the mismatching path.
4. Each failure is printed to **stderr** as one line:

   ```text
   MISMATCH <class>.<role> <symbol>
   ```

   For example `MISMATCH wxTextCtrl.set_value SetValue` or
   `MISMATCH sizers.flags.align_h CenterHorizontal`.

5. The command exits `1` if any mismatch was reported, `0` otherwise.

What is checked:

- **Existence** — every declared `symbol` must appear in the generated tree.
- **Arity** — the declared `params` count must match the emitted parameter count, **excluding**
  the language's implicit receiver. A `method-on-self` callable declaring one parameter must
  emit one parameter besides the receiver; a `procedure` declares all of them.

Global blocks are verified under **pseudo-class names**, because they are not wx classes:

| Label prefix | Block |
|---|---|
| `events.*` | `events.bind`, `events.bind_id` |
| `bitmap.*` | `bitmap.from_base64`, `bitmap.get_bitmap`, `bitmap.delete` |
| `font.*` | `font.create`, `font.delete` |
| `std_buttons.*` | `std_buttons.create`, `std_buttons.add_button`, `std_buttons.realize` |
| `app.*` | `app.set_top_window` |
| `sizers.wxBoxSizer.*` | `ctor`, `add_window`, `add_sizer`, `add_spacer` |
| `sizers.flags.*` | `ctor`, `proportion`, `expand`, `border`, `left`, `right`, `top`, `bottom`, `align_h`, `align_v` |

Class-owned entries use the plain `wxClass.role` form, with `ctor` for the constructor.

Note that `--verify` runs **after** the descriptor has been written, so the output file or
stdout already contains the descriptor when a mismatch is reported. The default
`VerifyUiDescriptor` implementation reports nothing, which is why a backend that has not
implemented it silently passes `--verify` — implement it whenever `BuildUiDescriptor` is
implemented.

---

## 10. `headers_hash`

`generated_by.headers_hash` is computed by `UiHeadersHash(headers_dir, defs_file)`:

1. Walk `headers_dir` recursively, skipping permission-denied entries, and keep every **regular
   file** (directories and special files are skipped).
2. Sort those files by their **generic, relative** path (`relative` to `headers_dir`, falling
   back to the bare filename when a relative path cannot be formed) so the result is independent
   of where the tree lives and of filesystem enumeration order.
3. Starting from the FNV-1a 64-bit offset basis `14695981039346656037`, fold in, for each file
   in sorted order: the relative path bytes, a single `NUL` byte, then the file's bytes.
4. Then fold in the **defs file's filename** (not its path), a `NUL` byte, then the defs file's
   bytes.
5. Render the 64-bit value as **16 lowercase hexadecimal characters** (zero-padded).

The prime is `1099511628211`.

Why: the hash identifies the exact header + defs surface a descriptor was built from, so a
descriptor checked into a consumer repository can be compared against a fresh run without
storing the headers themselves. Because it hashes relative paths and sorted content, an
identical source tree produces an identical hash on any machine and in any checkout location;
a single changed header byte changes it. (FNV-1a is used rather than a cryptographic digest
because the hash is a change detector, not a security primitive, and must stay dependency-free
and fast.)

---

## 11. Adding a backend

1. Override the two virtuals on your `LanguageEmitter` subclass:

   ```cpp
   [[nodiscard]] UiDescriptor BuildUiDescriptor(const ParsedFFI& ffi) const override;
   [[nodiscard]] std::vector<std::string>
       VerifyUiDescriptor(const UiDescriptor& descriptor,
                          const std::filesystem::path& generated_dir) const override;
   ```

   The defaults return an empty descriptor and an empty mismatch list, so `emit-ui` reports
   `Error: invalid descriptor: ...` until `BuildUiDescriptor` is implemented.

2. Populate `UiDescriptor` from the **profiled** `ParsedFFI` you are given — `emit-ui` calls
   `ApplyProfile` before `BuildUiDescriptor`, so do not re-apply the profile. Do not set
   `schema`, `lang` or `generated_by`: `emit-ui` stamps them after the call (which is why
   `descriptor.lang` always matches `Name()`).

3. Reuse the backend's existing naming helpers instead of re-deriving names — e.g.
   `GoConstructorName` / `GoMemberName`, `RustSafeMethodName` / `RustWrapperMethodName`,
   `JuliaEscapeName`, `TsEscapeName`, `FortranClassName` / `FortranClassModuleName`,
   `LuaEmittedMemberName` — so a declared symbol is spelled exactly the way `Generate()` spells
   it.

4. Resolve FFI declarations with the shared lookups: `UiFindClass`, `UiFindMethod` and
   `UiFindConstructor` walk the class's own valid methods, then its mixins, then its parent
   chain, first match wins. `UiFindConstructor` skips a `TBool`-returning constructor, because
   that is the two-phase `Create()` pattern rather than an allocation.

5. Choose the idiom honestly. A method inherited from an ancestor is `method-on-parent` with an
   `owner`; a free function is `procedure` (and repeats the handle in `params`); a chained
   flags operation is `builder`. Where you cannot express something, leave `symbol` empty and
   supply a reason code — do not omit the entry, and do not list a class in both `classes` and
   `unsupported`.

6. Build and validate with `kwxgen emit-ui --lang <lang> --headers <dir> --defs <file>
   --out -`; the command refuses to write an invalid descriptor.

7. Implement `VerifyUiDescriptor` by generating the UI layer into the supplied directory and
   returning `MISMATCH <class>.<role> <symbol>` lines for every symbol that is missing or whose
   arity disagrees. Never write into `generated_dir`'s parent, and never assume the directory
   survives the call — `emit-ui` deletes it.

8. `Generate()` must not change. The descriptor describes the layer `Generate()` already
   produces; if verification disagrees, the descriptor is wrong, not the generated code.
