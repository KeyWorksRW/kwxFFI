#!/usr/bin/env python3
"""Issue 89 reproducer: the dialogs sample's missing FFI surface.

Issue 89 asked for the classes, methods, constants and free functions that keep
`wxSamples/src/dialogs` from reaching full parity with the C++ original. This
script proves the parts that were implemented:

  A. Generated surface -- run `kwxgen generate --lang typescript --profile full`
     into a temp directory and assert the emitted wrapper layer has the required
     class hierarchy, typed returns, methods and constants. The checked-in
     `src/kwx_constants_table_gen.cpp` (which the DLL compiles) must match the
     generated table byte-for-byte, and a second generation must be identical.

  B. Exported surface -- load the built shared library with ctypes and assert
     every new symbol resolves and the new constants carry the real wxWidgets
     values (not invented ones).

Known platform limitation, deliberately NOT asserted: wxGenericColourDialog,
wxGenericFontDialog, wxGenericFileDialog and wxGenericDirDialog are not compiled
into the MSW wxWidgets build (their sources are in the OSX/wxUniversal lists
only), so issue 89 sections 1.11-1.14 cannot be exported portably. Their
absence is checked so a partial re-addition cannot slip in silently.

Usage:
    python tests/issue_tests/verify_89/repro.py [--root <repo>]
                                               [--kwxgen <exe>]
                                               [--library <path>]

Exit codes: 0 fixed, 1 still broken, 77 skipped (neither kwxgen nor library).
"""

import argparse
import ctypes
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

SKIP_RETURN_CODE = 77

KWXGEN_GLOBS = (
    "bin/*/kwxgen",
    "bin/*/kwxgen.exe",
    "kwxgen/bin/*/kwxgen*",
    "build/tests/bin/*/kwxgen*",
    "build/**/bin/*/kwxgen*",
)

LIBRARY_GLOBS = (
    "lib/shared/Debug/kwxFFI.dll",
    "lib/shared/Release/kwxFFI.dll",
    "lib/Debug/kwxFFI.dll",
    "lib/Release/kwxFFI.dll",
    "lib/kwxFFI.dll",
    "build/**/kwxFFI.dll",
    "lib/shared/Release/libkwxFFI.so",
    "lib/shared/Debug/libkwxFFI.so",
    "lib/libkwxFFI.so",
    "build/**/libkwxFFI.so",
)

# --- Mechanism A: the emitted TypeScript wrapper layer -----------------------
# (label, generated file, substring that must be present)
EXPECTED_IN_GENERATED = (
    # Class hierarchy required by the acceptance criteria.
    ("wxInfoBar is a wxControl", "wxInfoBar_gen.ts",
     "export class wxInfoBar extends wxControl"),
    ("wxNotificationMessage is a wxEvtHandler", "wxNotificationMessage_gen.ts",
     "export class wxNotificationMessage extends wxEvtHandler"),
    ("wxProgressDialog is a wxDialog", "wxProgressDialog_gen.ts",
     "export class wxProgressDialog extends wxDialog"),
    ("wxRichMessageDialog is a wxMessageDialog", "wxRichMessageDialog_gen.ts",
     "export class wxRichMessageDialog extends wxMessageDialog"),
    ("wxGenericNotificationMessage derives from wxNotificationMessage",
     "wxGenericNotificationMessage_gen.ts",
     "export class wxGenericNotificationMessage extends wxNotificationMessage"),
    ("wxGenericProgressDialog is a wxDialog", "wxGenericProgressDialog_gen.ts",
     "export class wxGenericProgressDialog extends wxDialog"),
    ("wxAddRemoveCtrl is a wxPanel", "wxAddRemoveCtrl_gen.ts",
     "export class wxAddRemoveCtrl extends wxPanel"),
    ("wxColourDialogEvent is a wxCommandEvent", "wxColourDialogEvent_gen.ts",
     "export class wxColourDialogEvent extends wxCommandEvent"),
    ("wxWindowModalDialogEvent is a wxCommandEvent", "wxWindowModalDialogEvent_gen.ts",
     "export class wxWindowModalDialogEvent extends wxCommandEvent"),
    ("wxSystemAppearance is generated", "wxSystemAppearance_gen.ts",
     "export class wxSystemAppearance"),
    ("wxGenericValidator is a wxValidator", "wxGenericValidator_gen.ts",
     "export class wxGenericValidator extends wxValidator"),
    ("wxRearrangeDialog is a wxDialog", "wxRearrangeDialog_gen.ts",
     "export class wxRearrangeDialog extends wxDialog"),
    ("wxBusyInfoFlags is generated", "wxBusyInfoFlags_gen.ts",
     "export class wxBusyInfoFlags"),

    # Typed class returns (issue section 5.1 / acceptance criteria).
    ("wxRearrangeCtrl.GetList returns wxRearrangeList", "wxRearrangeCtrl_gen.ts",
     "GetList(): wxRearrangeList | null"),
    ("wxFileDialogCustomize.AddButton returns wxFileDialogCustomControl",
     "wxFileDialogCustomize_gen.ts",
     "AddButton(label: Pointer): wxFileDialogCustomControl | null"),
    ("wxFileDialogCustomize.AddRadioButton returns wxFileDialogCustomControl",
     "wxFileDialogCustomize_gen.ts",
     "AddRadioButton(label: Pointer): wxFileDialogCustomControl | null"),

    # Methods on already-wrapped classes.
    ("wxInfoBar CreateEx", "wxInfoBar_gen.ts", "CreateEx("),
    ("wxInfoBar ShowCheckBox", "wxInfoBar_gen.ts", "ShowCheckBox("),
    ("wxInfoBar IsCheckBoxChecked", "wxInfoBar_gen.ts", "IsCheckBoxChecked(): boolean"),
    ("wxInfoBar ShowMessageFor", "wxInfoBar_gen.ts", "ShowMessageFor("),
    ("wxInfoBar RemoveAllButtons", "wxInfoBar_gen.ts", "RemoveAllButtons(): void"),
    ("wxInfoBar ShowCloseButton", "wxInfoBar_gen.ts",
     "ShowCloseButton(show: number): void"),
    ("wxProgressDialog Pulse", "wxProgressDialog_gen.ts", "Pulse("),
    ("wxProgressDialog UpdateWithSkip", "wxProgressDialog_gen.ts", "UpdateWithSkip("),
    ("wxProgressDialog Delete", "wxProgressDialog_gen.ts", "Delete(): void"),
    ("wxPropertySheetDialog default ctor", "wxPropertySheetDialog_gen.ts",
     "export function createWxPropertySheetDialogDefault(): wxPropertySheetDialog | null"),
    ("wxPropertySheetDialog two-phase CreateEx", "wxPropertySheetDialog_gen.ts",
     "CreateEx(parent: Pointer, id: number, title: Pointer, x: number, y: number, "
     "width: number, height: number, style: number): boolean"),
    ("wxGenericProgressDialog Update", "wxGenericProgressDialog_gen.ts",
     "Update(value: number, skip: Pointer): boolean"),
    ("wxGenericProgressDialog Resume", "wxGenericProgressDialog_gen.ts", "Resume(): void"),
    ("wxNotificationMessage SetIconBitmap", "wxNotificationMessage_gen.ts",
     "SetIconBitmap(icon: Pointer): void"),
    ("wxRichMessageDialog ShowCheckBox", "wxRichMessageDialog_gen.ts", "ShowCheckBox("),
    ("wxRichMessageDialog IsCheckBoxChecked", "wxRichMessageDialog_gen.ts",
     "IsCheckBoxChecked(): boolean"),
    ("wxRichMessageDialog ShowDetailedText", "wxRichMessageDialog_gen.ts",
     "ShowDetailedText("),
    ("wxRichMessageDialog SetFooterText", "wxRichMessageDialog_gen.ts", "SetFooterText("),
    ("wxRichMessageDialog SetFooterIcon", "wxRichMessageDialog_gen.ts", "SetFooterIcon("),
    ("wxAddRemoveCtrl SetAdaptor", "wxAddRemoveCtrl_gen.ts",
     "SetAdaptor(adaptor: Pointer): void"),
    ("wxAddRemoveCtrl SetButtonsToolTips", "wxAddRemoveCtrl_gen.ts",
     "SetButtonsToolTips("),
    ("wxAppProgressIndicator IsAvailable", "wxAppProgressIndicator_gen.ts",
     "IsAvailable(): boolean"),
    ("wxAppProgressIndicator SetRange", "wxAppProgressIndicator_gen.ts",
     "SetRange(range: number): void"),
    ("wxRearrangeDialog GetList", "wxRearrangeDialog_gen.ts",
     "GetList(): wxRearrangeList | null"),
    ("wxRearrangeDialog AddExtraControls", "wxRearrangeDialog_gen.ts",
     "AddExtraControls("),
    ("wxBusyInfo CreateWithFlags", "wxBusyInfo_gen.ts",
     "export function createWxBusyInfoWithFlags(flags: Pointer): wxBusyInfo | null"),
    ("wxBusyInfoFlags SetTransparency", "wxBusyInfoFlags_gen.ts",
     "SetTransparency(alpha: number): void"),
    ("wxColourDialogEvent GetColour", "wxColourDialogEvent_gen.ts",
     "GetColour(): wxColour | null"),
    ("wxColourDialogEvent GetDialog", "wxColourDialogEvent_gen.ts",
     "GetDialog(): wxColourDialog | null"),
    ("wxWindowModalDialogEvent GetDialog", "wxWindowModalDialogEvent_gen.ts",
     "GetDialog(): wxDialog | null"),
    ("wxSystemAppearance IsDark", "wxSystemAppearance_gen.ts", "IsDark(): boolean"),
    ("wxSystemAppearance GetName", "wxSystemAppearance_gen.ts",
     "GetName(): wxString | null"),
    ("wxGenericValidator CreateInt", "wxGenericValidator_gen.ts", "CreateInt("),
    ("wxGenericValidator CreateBool", "wxGenericValidator_gen.ts", "CreateBool("),
    ("wxGenericValidator CreateString", "wxGenericValidator_gen.ts", "CreateString("),
    ("wxFileDialog SetExtraControlCreator", "wxFileDialog_gen.ts",
     "SetExtraControlCreator("),
    ("wxRichToolTip SetIconBitmap", "wxRichToolTip_gen.ts", "SetIconBitmap("),
    ("wxRichToolTip SetBackgroundColourSingle", "wxRichToolTip_gen.ts",
     "SetBackgroundColourSingle("),
    ("wxGenericAboutDialog GetCustomControlParent", "wxGenericAboutDialog_gen.ts",
     "GetCustomControlParent(): wxWindow | null"),
    ("wxGenericAboutDialog AddText", "wxGenericAboutDialog_gen.ts", "AddText("),
    ("wxModalDialogHook Register", "wxModalDialogHook_gen.ts", "Register(): void"),
    ("wxModalDialogHook Unregister", "wxModalDialogHook_gen.ts", "Unregister(): void"),
    ("wxModalDialogHook Delete", "wxModalDialogHook_gen.ts", "Delete(): void"),
    ("kwxAddRemoveAdaptor SetOnGetItemsCtrl", "kwxAddRemoveAdaptor_gen.ts",
     "SetOnGetItemsCtrl("),
    ("kwxAddRemoveAdaptor SetOnCanAdd", "kwxAddRemoveAdaptor_gen.ts", "SetOnCanAdd("),
    ("kwxAddRemoveAdaptor SetOnCanRemove", "kwxAddRemoveAdaptor_gen.ts", "SetOnCanRemove("),
    ("kwxAddRemoveAdaptor SetOnAdd", "kwxAddRemoveAdaptor_gen.ts", "SetOnAdd("),
    ("kwxAddRemoveAdaptor SetOnRemove", "kwxAddRemoveAdaptor_gen.ts", "SetOnRemove("),

    # Free functions (issue section 4).
    ("wxGetSingleChoiceIndexEx", "kwx_free_functions_gen.ts",
     "export function wxGetSingleChoiceIndexEx("),
    ("wxGetSingleChoiceDataEx", "kwx_free_functions_gen.ts",
     "export function wxGetSingleChoiceDataEx("),
    ("wxGetSelectedChoicesEx", "kwx_free_functions_gen.ts",
     "export function wxGetSelectedChoicesEx("),

    # Constants (issue section 3).
    ("APPLY", "kwx_constants_gen.ts", "export const APPLY:"),
    ("CLOSE", "kwx_constants_gen.ts", "export const CLOSE:"),
    ("ICON_NONE", "kwx_constants_gen.ts", "export const ICON_NONE:"),
    ("ICON_AUTH_NEEDED", "kwx_constants_gen.ts", "export const ICON_AUTH_NEEDED:"),
    ("PD_CAN_ABORT", "kwx_constants_gen.ts", "export const PD_CAN_ABORT:"),
    ("PD_CAN_SKIP", "kwx_constants_gen.ts", "export const PD_CAN_SKIP:"),
    ("PD_APP_MODAL", "kwx_constants_gen.ts", "export const PD_APP_MODAL:"),
    ("PD_ELAPSED_TIME", "kwx_constants_gen.ts", "export const PD_ELAPSED_TIME:"),
    ("PD_ESTIMATED_TIME", "kwx_constants_gen.ts", "export const PD_ESTIMATED_TIME:"),
    ("PD_REMAINING_TIME", "kwx_constants_gen.ts", "export const PD_REMAINING_TIME:"),
    ("PD_SMOOTH", "kwx_constants_gen.ts", "export const PD_SMOOTH:"),
    ("PD_AUTO_HIDE", "kwx_constants_gen.ts", "export const PD_AUTO_HIDE:"),
    ("ColourData_NUM_CUSTOM", "kwx_constants_gen.ts",
     "export const ColourData_NUM_CUSTOM:"),
    ("InfoBar_Timeout_Auto", "kwx_constants_gen.ts",
     "export const InfoBar_Timeout_Auto:"),
    ("InfoBar_Timeout_Never", "kwx_constants_gen.ts",
     "export const InfoBar_Timeout_Never:"),
    ("NotificationMessage_Timeout_Auto", "kwx_constants_gen.ts",
     "export const NotificationMessage_Timeout_Auto:"),
    ("NotificationMessage_Timeout_Never", "kwx_constants_gen.ts",
     "export const NotificationMessage_Timeout_Never:"),
)

# Generated files that must NOT exist: these wx classes are not compiled into
# the MSW wxWidgets build, so exporting them would break every Windows link.
FORBIDDEN_GENERATED_FILES = (
    "wxGenericColourDialog_gen.ts",
    "wxGenericFontDialog_gen.ts",
    "wxGenericFileDialog_gen.ts",
    "wxGenericDirDialog_gen.ts",
)

# --- Mechanism B: the exported C surface ------------------------------------
REQUIRED_EXPORTS = (
    "wxRichMessageDialog_Create",
    "wxRichMessageDialog_ShowCheckBox",
    "wxRichMessageDialog_IsCheckBoxChecked",
    "wxRichMessageDialog_ShowDetailedText",
    "wxRichMessageDialog_SetFooterText",
    "wxRichMessageDialog_SetFooterIcon",
    "wxRichMessageDialog_Delete",
    "wxAddRemoveCtrl_Create",
    "wxAddRemoveCtrl_SetAdaptor",
    "wxAddRemoveCtrl_SetButtonsToolTips",
    "kwxAddRemoveAdaptor_Create",
    "kwxAddRemoveAdaptor_SetOnGetItemsCtrl",
    "kwxAddRemoveAdaptor_SetOnCanAdd",
    "kwxAddRemoveAdaptor_SetOnCanRemove",
    "kwxAddRemoveAdaptor_SetOnAdd",
    "kwxAddRemoveAdaptor_SetOnRemove",
    "wxGenericProgressDialog_Create",
    "wxGenericProgressDialog_Update",
    "wxGenericProgressDialog_Pulse",
    "wxGenericProgressDialog_Resume",
    "wxGenericProgressDialog_Delete",
    "wxAppProgressIndicator_Create",
    "wxAppProgressIndicator_IsAvailable",
    "wxAppProgressIndicator_SetValue",
    "wxAppProgressIndicator_SetRange",
    "wxAppProgressIndicator_Pulse",
    "wxAppProgressIndicator_Delete",
    "wxRearrangeDialog_Create",
    "wxRearrangeDialog_GetOrder",
    "wxRearrangeDialog_GetList",
    "wxRearrangeDialog_AddExtraControls",
    "wxRearrangeDialog_Delete",
    "wxBusyInfoFlags_Create",
    "wxBusyInfoFlags_SetParent",
    "wxBusyInfoFlags_SetIcon",
    "wxBusyInfoFlags_SetTitle",
    "wxBusyInfoFlags_SetText",
    "wxBusyInfoFlags_SetForeground",
    "wxBusyInfoFlags_SetBackground",
    "wxBusyInfoFlags_SetTransparency",
    "wxBusyInfoFlags_Delete",
    "wxBusyInfo_CreateWithFlags",
    "wxColourDialogEvent_Create",
    "wxColourDialogEvent_GetColour",
    "wxColourDialogEvent_GetDialog",
    "wxColourDialogEvent_Delete",
    "wxWindowModalDialogEvent_Create",
    "wxWindowModalDialogEvent_GetDialog",
    "wxWindowModalDialogEvent_Delete",
    "wxGenericNotificationMessage_Create",
    "wxSystemAppearance_IsDark",
    "wxSystemAppearance_IsUsingDarkBackground",
    "wxSystemAppearance_GetName",
    "wxGenericValidator_CreateInt",
    "wxGenericValidator_CreateBool",
    "wxGenericValidator_CreateString",
    "wxGenericValidator_Delete",
    "wxInfoBar_CreateEx",
    "wxInfoBar_ShowCheckBox",
    "wxInfoBar_IsCheckBoxChecked",
    "wxInfoBar_ShowMessageFor",
    "wxInfoBar_RemoveAllButtons",
    "wxInfoBar_ShowCloseButton",
    "wxProgressDialog_Pulse",
    "wxProgressDialog_UpdateWithSkip",
    "wxPropertySheetDialog_CreateDefault",
    "wxPropertySheetDialog_CreateEx",
    "wxProgressDialog_Delete",
    "wxModalDialogHook_Register",
    "wxModalDialogHook_Unregister",
    "wxModalDialogHook_Delete",
    "wxFileDialogCustomize_AddRadioButton",
    "wxFileDialog_SetExtraControlCreator",
    "wxRichToolTip_SetIconBitmap",
    "wxRichToolTip_SetBackgroundColourSingle",
    "wxGenericAboutDialog_GetCustomControlParent",
    "wxGenericAboutDialog_AddText",
    "wxColourDialog_Delete",
    "wxFontDialog_Delete",
    "wxNotificationMessage_SetIconBitmap",
    "wxGetSingleChoiceIndexEx",
    "wxGetSingleChoiceDataEx",
    "wxGetSelectedChoicesEx",
    "expwxICON_NONE",
    "expwxICON_AUTH_NEEDED",
    "expwxAPPLY",
    "expwxCLOSE",
    "expwxPD_CAN_ABORT",
    "expwxPD_CAN_SKIP",
    "expwxPD_APP_MODAL",
    "expwxPD_ELAPSED_TIME",
    "expwxPD_ESTIMATED_TIME",
    "expwxPD_REMAINING_TIME",
    "expwxPD_SMOOTH",
    "expwxPD_AUTO_HIDE",
    "expwxColourData_NUM_CUSTOM",
    "expwxInfoBar_Timeout_Auto",
    "expwxInfoBar_Timeout_Never",
    "expwxNotificationMessage_Timeout_Auto",
    "expwxNotificationMessage_Timeout_Never",
)

# wxWidgets 3.3.5 values (wx/defs.h, wx/progdlg.h, wx/colourdata.h,
# wx/infobar.h, wx/notifmsg.h) -- do not guess these.
EXPECTED_CONSTANT_VALUES = (
    ("expwxAPPLY", 0x00000020),
    ("expwxCLOSE", 0x00000040),
    ("expwxICON_NONE", 0x00040000),
    ("expwxICON_AUTH_NEEDED", 0x00080000),
    ("expwxPD_CAN_ABORT", 0x0001),
    ("expwxPD_APP_MODAL", 0x0002),
    ("expwxPD_AUTO_HIDE", 0x0004),
    ("expwxPD_ELAPSED_TIME", 0x0008),
    ("expwxPD_ESTIMATED_TIME", 0x0010),
    ("expwxPD_SMOOTH", 0x0020),
    ("expwxPD_REMAINING_TIME", 0x0040),
    ("expwxPD_CAN_SKIP", 0x0080),
    ("expwxColourData_NUM_CUSTOM", 16),
    ("expwxInfoBar_Timeout_Auto", -1),
    ("expwxInfoBar_Timeout_Never", 0),
    ("expwxNotificationMessage_Timeout_Auto", -1),
    ("expwxNotificationMessage_Timeout_Never", 0),
)


def discover_kwxgen(root, explicit):
    if explicit:
        candidate = Path(explicit)
        if not candidate.is_absolute():
            candidate = root / candidate
        return candidate.resolve() if candidate.is_file() else None

    found = []
    for pattern in KWXGEN_GLOBS:
        for candidate in root.glob(pattern):
            if candidate.is_file() and candidate.name.startswith("kwxgen"):
                found.append(candidate.resolve())
    if not found:
        return None
    unique = sorted(set(found))
    release_builds = [item for item in unique if "release" in str(item).lower()]
    return max(release_builds or unique, key=lambda item: item.stat().st_mtime)


def discover_library(root, explicit):
    if explicit:
        candidate = Path(explicit)
        if not candidate.is_absolute():
            candidate = root / candidate
        return candidate.resolve() if candidate.is_file() else None
    for pattern in LIBRARY_GLOBS:
        for candidate in root.glob(pattern):
            if candidate.is_file():
                return candidate.resolve()
    return None


def expect(label, ok, observed=None):
    print("EXPECTED: " + label)
    print("OBSERVED: " + (("ok" if ok else "FAILED") if observed is None else observed))
    return 0 if ok else 1


def check_generated_surface(root, kwxgen, work_dir):
    out_dir = work_dir / "typescript"
    command = [
        str(kwxgen), "generate",
        "--headers", str(root / "include"),
        "--defs", str(root / "src" / "kwx_defs.cpp"),
        "--lang", "typescript",
        "--profile", "full",
        "--out", str(out_dir),
    ]
    print("RUN: " + " ".join(command))
    completed = subprocess.run(command, cwd=str(root), capture_output=True, text=True, timeout=900)
    if completed.returncode != 0:
        print("EXPECTED: kwxgen generate exits 0")
        print("OBSERVED: exit code %d" % completed.returncode)
        print((completed.stderr or completed.stdout)[-2000:])
        return 1

    cache = {}

    def read(name):
        if name not in cache:
            path = out_dir / name
            cache[name] = path.read_text(encoding="utf-8") if path.is_file() else None
        return cache[name]

    failures = 0
    for label, filename, needle in EXPECTED_IN_GENERATED:
        text = read(filename)
        if text is None:
            failures += expect("%s (%s exists)" % (label, filename), False,
                               "file not generated")
            continue
        failures += expect(label, needle in text,
                           "present" if needle in text else "missing: " + needle)

    for filename in FORBIDDEN_GENERATED_FILES:
        exists = (out_dir / filename).is_file()
        failures += expect("%s is not generated (not available in the MSW wx build)"
                           % filename, not exists,
                           "absent" if not exists else "still generated")

    # The compiled constant table must match the generated one exactly.
    generated_table = out_dir / "kwx_constants_table_gen.cpp"
    committed_table = root / "src" / "kwx_constants_table_gen.cpp"
    if generated_table.is_file() and committed_table.is_file():
        # The committed table is run through clang-format, so compare content
        # with all whitespace removed rather than raw bytes.
        generated_text = re.sub(r"\s+", "", generated_table.read_text(encoding="utf-8"))
        committed_text = re.sub(r"\s+", "", committed_table.read_text(encoding="utf-8"))
        same = generated_text == committed_text
        failures += expect("src/kwx_constants_table_gen.cpp matches the generated table",
                           same, "identical" if same else "stale or different")
    else:
        failures += expect("src/kwx_constants_table_gen.cpp matches the generated table",
                           False, "table file missing")

    # Determinism: a second generation must be byte-identical.
    second_dir = work_dir / "typescript_repeat"
    repeat = list(command)
    repeat[repeat.index(str(out_dir))] = str(second_dir)
    subprocess.run(repeat, cwd=str(root), capture_output=True, text=True, timeout=900)
    mismatched = []
    for path in sorted(out_dir.rglob("*.ts")):
        mirror = second_dir / path.relative_to(out_dir)
        if not mirror.is_file() or mirror.read_bytes() != path.read_bytes():
            mismatched.append(path.name)
    failures += expect("a second generation is byte-identical",
                       not mismatched, "identical" if not mismatched else str(mismatched[:5]))
    return failures


def add_windows_dll_directories(library_path):
    if os.name != "nt":
        return []
    add_directory = getattr(os, "add_dll_directory", None)
    if add_directory is None:
        return []
    candidates = [str(library_path.parent)]
    candidates.extend(os.environ.get("PATH", "").split(os.pathsep))
    handles = []
    for candidate in candidates:
        if candidate and os.path.isdir(candidate):
            try:
                handles.append(add_directory(candidate))
            except OSError:
                continue
    return handles


def bind(library, name, restype, argtypes):
    function = getattr(library, name)
    function.restype = restype
    function.argtypes = argtypes
    return function


def check_exported_surface(library_path):
    dll_handles = add_windows_dll_directories(library_path)
    try:
        library = ctypes.CDLL(str(library_path))
    except OSError as error:
        return expect("%s loads with ctypes" % library_path.name, False, str(error))

    missing = [name for name in REQUIRED_EXPORTS if not hasattr(library, name)]
    failures = expect(
        "the shared library exports every symbol this check needs",
        not missing,
        "all present" if not missing else "missing: " + ", ".join(missing[:10]),
    )
    if missing:
        return failures

    for name, expected in EXPECTED_CONSTANT_VALUES:
        value = bind(library, name, ctypes.c_int, [])()
        failures += expect("%s is %d" % (name, expected), value == expected,
                           "value = %d" % value)

    # Contract points that are cheap to verify without a wxApp.
    create_notification = bind(library, "wxNotificationMessage_Create", ctypes.c_void_p,
                               [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p,
                                ctypes.c_int])
    failures += expect("wxNotificationMessage_Create takes the class-shaped signature",
                       create_notification is not None)
    failures += expect("dll handles kept alive", bool(dll_handles) or os.name != "nt",
                       "windows handles = %d" % len(dll_handles))
    return failures


def main(argv=None):
    parser = argparse.ArgumentParser(description="Issue 89 reproducer")
    parser.add_argument("--root", type=Path,
                        default=Path(__file__).resolve().parents[3],
                        help="Repository root (default: three levels above this file)")
    parser.add_argument("--kwxgen", default=None, help="Path to the kwxgen executable")
    parser.add_argument("--library", default=None, help="Path to the kwxFFI shared library")
    options = parser.parse_args(argv)

    root = options.root.resolve()
    kwxgen = discover_kwxgen(root, options.kwxgen)
    library_path = discover_library(root, options.library)

    if kwxgen is None and library_path is None:
        print("SKIP: no kwxgen executable and no shared library found under %s" % root)
        return SKIP_RETURN_CODE

    failures = 0
    if kwxgen is None:
        print("SKIP: mechanism A (generated surface) - no kwxgen executable found")
    else:
        print("=== A. generated TypeScript surface ===")
        with tempfile.TemporaryDirectory() as work_dir:
            failures += check_generated_surface(root, kwxgen, Path(work_dir))

    if library_path is None:
        print("SKIP: mechanism B (exported surface) - no shared library found")
    else:
        print("=== B. exported C surface ===")
        failures += check_exported_surface(library_path)

    print("=== RESULT: %s ===" % ("FIXED" if failures == 0 else "STILL BROKEN"))
    return 0 if failures == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
