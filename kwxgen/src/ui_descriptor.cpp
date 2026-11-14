/////////////////////////////////////////////////////////////////////////////
// Purpose:   Language-neutral UI descriptor shared by emit-ui and check-ui
// Author:    Ralph Walden
// Copyright: Copyright (c) 2026 KeyWorks Software (Ralph Walden)
// License:   Apache License -- see LICENSE
/////////////////////////////////////////////////////////////////////////////

#include "ui_descriptor.h"

#include "lang/lang_common.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <set>
#include <sstream>
#include <system_error>
#include <utility>

#include <glaze/json.hpp>

namespace fs = std::filesystem;

// -------------------------------------------------------------------------
// JSON key renames.  The C++ member names avoid the JSON reserved-ish spellings, so the
// wire names are fixed here.  Keeping these in the .cpp is deliberate: only this
// translation unit serializes a descriptor, and the language backends build one in memory
// through the public API instead of touching the JSON themselves.
// -------------------------------------------------------------------------

template <>
struct glz::meta<UiBitmap>
{
    static constexpr std::string_view rename_key(const std::string_view key)
    {
        if (key == "delete_fn")
        {
            return "delete";
        }
        return key;
    }
};

template <>
struct glz::meta<UiFont>
{
    static constexpr std::string_view rename_key(const std::string_view key)
    {
        if (key == "delete_fn")
        {
            return "delete";
        }
        return key;
    }
};

template <>
struct glz::meta<UiSizersBlock>
{
    static constexpr std::string_view rename_key(const std::string_view key)
    {
        if (key == "wx_box_sizer")
        {
            return "wxBoxSizer";
        }
        return key;
    }
};

template <>
struct glz::meta<UiUnsupported>
{
    static constexpr std::string_view rename_key(const std::string_view key)
    {
        if (key == "class_name")
        {
            return "class";
        }
        return key;
    }
};

namespace ui_detail
{

    // The tolerantly parsed project IR consumed by `check-ui`.  Every field defaults so that a
    // form or child that omits one still validates against the descriptor.
    struct IrChild
    {
        std::string node_class;
        std::string var_name;
        std::vector<std::string> roles_used;
        bool in_sizer = false;
    };

    struct IrForm
    {
        std::string class_name;
        std::string node_class;
        std::vector<IrChild> children;
    };

    struct IrDocument
    {
        int schema = 0;
        std::string project;
        std::vector<IrForm> forms;
    };

    struct LabeledCallable
    {
        std::string label;
        const UiCallable* callable = nullptr;
    };

    static constexpr std::uint64_t FNV_OFFSET_BASIS = 14695981039346656037ULL;
    static constexpr std::uint64_t FNV_PRIME = 1099511628211ULL;

    [[nodiscard]] static std::uint64_t Fnv1aUpdate(std::uint64_t hash_value, std::string_view bytes)
    {
        for (const char character: bytes)
        {
            hash_value ^= static_cast<std::uint64_t>(static_cast<unsigned char>(character));
            hash_value *= FNV_PRIME;
        }
        return hash_value;
    }

    [[nodiscard]] static std::string ToHexString(std::uint64_t value)
    {
        static constexpr std::string_view HEX_DIGITS = "0123456789abcdef";
        std::string result(16, '0');
        for (int i = 15; i >= 0; --i)
        {
            const std::size_t slot = static_cast<std::size_t>(i);
            result[slot] = HEX_DIGITS[static_cast<std::size_t>(value & 0x0FU)];
            value >>= 4U;
        }
        return result;
    }

    [[nodiscard]] static std::string ReadFileBytes(const fs::path& file_path)
    {
        std::ifstream input(file_path, std::ios::binary);
        if (!input.is_open())
        {
            return {};
        }
        std::ostringstream buffer;
        buffer << input.rdbuf();
        return buffer.str();
    }

    // The path a file is hashed under: relative to headers_dir where possible, otherwise just
    // the filename so the hash stays independent of where the tree lives.
    [[nodiscard]] static std::string RelativeGenericPath(const fs::path& file_path,
                                                         const fs::path& base_dir)
    {
        std::error_code relative_error;
        const fs::path relative_path = fs::relative(file_path, base_dir, relative_error);
        if (relative_error || relative_path.empty())
        {
            return file_path.filename().generic_string();
        }
        return relative_path.generic_string();
    }

    // A callable actually renders code only when it names a symbol and is not the explicit
    // "unsupported" marker.
    [[nodiscard]] static bool IsUsable(const UiCallable& callable)
    {
        return !callable.symbol.empty() && callable.idiom != "unsupported";
    }

    [[nodiscard]] static bool IsSizerClass(const std::string& class_name)
    {
        return class_name == "wxBoxSizer" || class_name.ends_with("Sizer");
    }

    [[nodiscard]] static bool IsSizerRole(const std::string& role)
    {
        return role == "add_window" || role == "add_sizer" || role == "add_spacer";
    }

    [[nodiscard]] static bool IsFlagRole(const std::string& role)
    {
        return role == "proportion" || role == "expand" || role == "border" || role == "left" ||
               role == "right" || role == "top" || role == "bottom" || role == "align_h" ||
               role == "align_v";
    }

    [[nodiscard]] static const UiCallable* SizerOpsCallable(const UiDescriptor& descriptor,
                                                            const std::string& role)
    {
        const UiSizerOps& ops = descriptor.sizers.wx_box_sizer;
        if (role == "ctor")
        {
            return &ops.ctor;
        }
        if (role == "add_window")
        {
            return &ops.add_window;
        }
        if (role == "add_sizer")
        {
            return &ops.add_sizer;
        }
        if (role == "add_spacer")
        {
            return &ops.add_spacer;
        }
        return nullptr;
    }

    [[nodiscard]] static const UiCallable* FlagsCallable(const UiDescriptor& descriptor,
                                                         const std::string& role)
    {
        const UiFlags& flags = descriptor.sizers.flags;
        if (role == "ctor")
        {
            return &flags.ctor;
        }
        if (role == "proportion")
        {
            return &flags.proportion;
        }
        if (role == "expand")
        {
            return &flags.expand;
        }
        if (role == "border")
        {
            return &flags.border;
        }
        if (role == "left")
        {
            return &flags.left;
        }
        if (role == "right")
        {
            return &flags.right;
        }
        if (role == "top")
        {
            return &flags.top;
        }
        if (role == "bottom")
        {
            return &flags.bottom;
        }
        if (role == "align_h")
        {
            return &flags.align_h;
        }
        if (role == "align_v")
        {
            return &flags.align_v;
        }
        return nullptr;
    }

    // Resolve one (class, role) pair to the callable that implements it, in the documented
    // order.  Returns nullptr when the descriptor cannot express the pair.
    [[nodiscard]] static const UiCallable* ResolveCallable(const UiDescriptor& descriptor,
                                                           const std::string& class_name,
                                                           const std::string& role)
    {
        const std::map<std::string, UiClass>::const_iterator class_iter =
            descriptor.classes.find(class_name);
        if (class_iter != descriptor.classes.end())
        {
            // A class that names this role owns the answer: an unusable callable here means the
            // pair is unresolved, because the later rules describe other classes and blocks.
            if (role == "ctor")
            {
                return IsUsable(class_iter->second.ctor) ? &class_iter->second.ctor : nullptr;
            }
            const std::map<std::string, UiCallable>::const_iterator role_iter =
                class_iter->second.roles.find(role);
            if (role_iter != class_iter->second.roles.end())
            {
                return IsUsable(role_iter->second) ? &role_iter->second : nullptr;
            }
        }

        if (IsSizerClass(class_name) && (role == "ctor" || IsSizerRole(role)))
        {
            const UiCallable* const callable = SizerOpsCallable(descriptor, role);
            if (callable != nullptr && IsUsable(*callable))
            {
                return callable;
            }
        }

        if (IsFlagRole(role))
        {
            const UiCallable* const callable = FlagsCallable(descriptor, role);
            if (callable != nullptr && IsUsable(*callable))
            {
                return callable;
            }
        }

        if (role == "bind")
        {
            return IsUsable(descriptor.events.bind) ? &descriptor.events.bind : nullptr;
        }
        if (role == "bind_id")
        {
            return IsUsable(descriptor.events.bind_id) ? &descriptor.events.bind_id : nullptr;
        }
        if (role == "from_base64")
        {
            return IsUsable(descriptor.bitmap.from_base64) ? &descriptor.bitmap.from_base64 :
                                                             nullptr;
        }
        if (role == "get_bitmap")
        {
            return IsUsable(descriptor.bitmap.get_bitmap) ? &descriptor.bitmap.get_bitmap : nullptr;
        }
        if (role == "add_button")
        {
            return IsUsable(descriptor.std_buttons.add_button) ?
                       &descriptor.std_buttons.add_button :
                       nullptr;
        }
        if (role == "realize")
        {
            return IsUsable(descriptor.std_buttons.realize) ? &descriptor.std_buttons.realize :
                                                              nullptr;
        }
        if (role == "create")
        {
            if (class_name == "wxFont")
            {
                return IsUsable(descriptor.font.create) ? &descriptor.font.create : nullptr;
            }
            if (class_name == "wxStdDialogButtonSizer")
            {
                return IsUsable(descriptor.std_buttons.create) ? &descriptor.std_buttons.create :
                                                                 nullptr;
            }
            if (IsUsable(descriptor.font.create))
            {
                return &descriptor.font.create;
            }
            if (IsUsable(descriptor.std_buttons.create))
            {
                return &descriptor.std_buttons.create;
            }
            return nullptr;
        }
        if (role == "delete")
        {
            if (class_name == "wxFont")
            {
                return IsUsable(descriptor.font.delete_fn) ? &descriptor.font.delete_fn : nullptr;
            }
            if (class_name == "wxBitmap")
            {
                return IsUsable(descriptor.bitmap.delete_fn) ? &descriptor.bitmap.delete_fn :
                                                               nullptr;
            }
            return nullptr;
        }

        // Generic sizer fallback: any class can be handed to a box sizer.
        if (IsSizerRole(role))
        {
            const UiCallable* const callable = SizerOpsCallable(descriptor, role);
            if (callable != nullptr && IsUsable(*callable))
            {
                return callable;
            }
        }

        return nullptr;
    }

    [[nodiscard]] static bool ReadIrDocument(const std::string& json, IrDocument& out,
                                             std::string& error)
    {
        IrDocument parsed {};
        const glz::error_ctx errc =
            glz::read<glz::opts { .error_on_unknown_keys = false }>(parsed, json);
        if (errc)
        {
            error = "IR JSON parse error: " + glz::format_error(errc, json);
            return false;
        }
        out = std::move(parsed);
        error.clear();
        return true;
    }

    // Every callable in the descriptor, labelled with its JSON path fragments, so the
    // vocabulary and shape checks can walk them all in one place.
    static void CollectCallables(const UiDescriptor& descriptor, std::vector<LabeledCallable>& out)
    {
        const auto add = [&out](const std::string& label, const UiCallable& callable)
        {
            out.push_back(LabeledCallable { .label = label, .callable = &callable });
        };

        for (const auto& [class_name, class_info]: descriptor.classes)
        {
            add(class_name + ".ctor", class_info.ctor);
            for (const auto& [role, callable]: class_info.roles)
            {
                add(class_name + "." + role, callable);
            }
        }

        const UiSizerOps& ops = descriptor.sizers.wx_box_sizer;
        add("sizers.wxBoxSizer.ctor", ops.ctor);
        add("sizers.wxBoxSizer.add_window", ops.add_window);
        add("sizers.wxBoxSizer.add_sizer", ops.add_sizer);
        add("sizers.wxBoxSizer.add_spacer", ops.add_spacer);

        const UiFlags& flags = descriptor.sizers.flags;
        add("sizers.flags.ctor", flags.ctor);
        add("sizers.flags.proportion", flags.proportion);
        add("sizers.flags.expand", flags.expand);
        add("sizers.flags.border", flags.border);
        add("sizers.flags.left", flags.left);
        add("sizers.flags.right", flags.right);
        add("sizers.flags.top", flags.top);
        add("sizers.flags.bottom", flags.bottom);
        add("sizers.flags.align_h", flags.align_h);
        add("sizers.flags.align_v", flags.align_v);

        add("events.bind", descriptor.events.bind);
        add("events.bind_id", descriptor.events.bind_id);
        add("bitmap.from_base64", descriptor.bitmap.from_base64);
        add("bitmap.get_bitmap", descriptor.bitmap.get_bitmap);
        add("bitmap.delete", descriptor.bitmap.delete_fn);
        add("font.create", descriptor.font.create);
        add("font.delete", descriptor.font.delete_fn);
        add("std_buttons.create", descriptor.std_buttons.create);
        add("std_buttons.add_button", descriptor.std_buttons.add_button);
        add("std_buttons.realize", descriptor.std_buttons.realize);
        add("app.set_top_window", descriptor.app.set_top_window);
    }

    // The blocks a backend must always account for, whatever language it targets.
    [[nodiscard]] static bool RequireBlockCallable(const UiCallable& callable,
                                                   const std::string& label, std::string& error)
    {
        if (IsUsable(callable))
        {
            return true;
        }
        if (callable.reason.has_value() && !callable.reason->empty() &&
            UiIsKnownReason(callable.reason.value()))
        {
            return true;
        }
        error = "required mapping '" + label + "' has neither a symbol nor a valid reason code";
        return false;
    }

    [[nodiscard]] static bool ValidateCallableShape(const UiCallable& callable,
                                                    const std::string& label, std::string& error)
    {
        if (callable.symbol.empty())
        {
            if (!callable.reason.has_value() || callable.reason->empty())
            {
                error = label + ": callable has no symbol and no reason code";
                return false;
            }
            return true;
        }

        if (callable.idiom.empty())
        {
            error = label + ": callable '" + callable.symbol + "' has no idiom";
            return false;
        }
        if (callable.idiom == "unsupported")
        {
            error = label + ": callable '" + callable.symbol + "' uses the unsupported idiom";
            return false;
        }
        if (callable.idiom == "method-on-parent" && !callable.owner.has_value())
        {
            error = label + ": method-on-parent callable '" + callable.symbol + "' has no owner";
            return false;
        }
        return true;
    }

    [[nodiscard]] static bool ValidateRequiredClass(const UiDescriptor& descriptor,
                                                    const std::string& class_name,
                                                    std::string& error)
    {
        const std::map<std::string, UiClass>::const_iterator class_iter =
            descriptor.classes.find(class_name);

        bool listed_as_whole_class = false;
        std::set<std::string> unsupported_roles;
        for (const UiUnsupported& entry: descriptor.unsupported)
        {
            if (entry.class_name != class_name)
            {
                continue;
            }
            if (entry.role.empty())
            {
                listed_as_whole_class = true;
            }
            else
            {
                unsupported_roles.insert(entry.role);
            }
        }

        if (class_iter == descriptor.classes.end())
        {
            if (!listed_as_whole_class)
            {
                error = "required class '" + class_name +
                        "' is neither implemented nor listed in unsupported";
                return false;
            }
            return true;
        }

        if (listed_as_whole_class)
        {
            error = "required class '" + class_name +
                    "' appears in classes and is also listed in unsupported with an empty role";
            return false;
        }

        if (class_iter->second.ctor.symbol.empty())
        {
            error = "required class '" + class_name + "' has no constructor symbol";
            return false;
        }

        for (const std::string_view required_role: UiRequiredRolesForClass(class_name))
        {
            if (required_role == "ctor")
            {
                // The constructor is carried by UiClass::ctor, which the check above covers.
                continue;
            }
            const std::string role(required_role);
            const std::map<std::string, UiCallable>::const_iterator role_iter =
                class_iter->second.roles.find(role);
            const bool usable =
                role_iter != class_iter->second.roles.end() && IsUsable(role_iter->second);
            if (!usable && !unsupported_roles.contains(role))
            {
                error = "required class '" + class_name + "' role '" + role +
                        "' is neither usable nor listed in unsupported";
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] static bool MatchesMethodName(const FunctionDecl& func,
                                                std::string_view method_name)
    {
        return func.method_name == method_name;
    }

    // A TBool-returning constructor is the two-phase Create() pattern, not an allocation.
    [[nodiscard]] static bool IsTrueConstructor(const FunctionDecl& func,
                                                [[maybe_unused]] std::string_view unused)
    {
        return func.is_constructor && func.return_type != "TBool";
    }

    // The allocating constructor: named exactly Create, not the two-phase TBool form.  Any other
    // Create* method is a factory (wxWindow_CreateAccessible), which no backend emits as a
    // constructor of the class it belongs to.
    [[nodiscard]] static bool IsCanonicalConstructor(const FunctionDecl& func,
                                                     [[maybe_unused]] std::string_view unused)
    {
        return func.method_name == "Create" && func.return_type != "TBool";
    }

    using FunctionPredicate = bool (*)(const FunctionDecl&, std::string_view);

    // Walks a class's own valid methods, then its mixins, then its ancestors, and returns the
    // first declaration the predicate accepts.
    [[nodiscard]] static const FunctionDecl* FindInHierarchy(const ParsedFFI& ffi,
                                                             std::string_view class_name,
                                                             FunctionPredicate predicate,
                                                             std::string_view needle)
    {
        std::string current(class_name);
        std::set<std::string> visited;
        while (!current.empty() && visited.insert(current).second)
        {
            const ClassInfo* const class_info = UiFindClass(ffi, current);
            if (class_info != nullptr)
            {
                for (const FunctionDecl& func: class_info->methods)
                {
                    if (IsValidFunction(func) && predicate(func, needle))
                    {
                        return &func;
                    }
                }
            }

            const std::unordered_map<std::string, std::vector<std::string>>::const_iterator
                mixin_iter = ffi.mixin_map.find(current);
            if (mixin_iter != ffi.mixin_map.end())
            {
                for (const std::string& mixin_name: mixin_iter->second)
                {
                    const ClassInfo* const mixin_class = UiFindClass(ffi, mixin_name);
                    if (mixin_class == nullptr)
                    {
                        continue;
                    }
                    for (const FunctionDecl& func: mixin_class->methods)
                    {
                        if (IsValidFunction(func) && predicate(func, needle))
                        {
                            return &func;
                        }
                    }
                }
            }

            const std::unordered_map<std::string, std::string>::const_iterator parent_iter =
                ffi.parent_map.find(current);
            if (parent_iter == ffi.parent_map.end())
            {
                break;
            }
            current = parent_iter->second;
        }
        return nullptr;
    }

}  // namespace ui_detail

// -------------------------------------------------------------------------
// Vocabularies
// -------------------------------------------------------------------------

const std::vector<std::string_view>& UiRoleVocabulary()
{
    static const std::vector<std::string_view> ROLES {
        "ctor",
        "show",
        "hide",
        "set_title",
        "set_label",
        "set_value",
        "set_size",
        "set_min_size",
        "center",
        "set_sizer",
        "set_size_hints",
        "set_font",
        "set_icon",
        "set_bitmap",
        "create_statusbar",
        "set_menubar",
        "show_modal",
        "end_modal",
        "set_escape_id",
        "set_affirmative_id",
        "bind",
        "bind_id",
        "destroy",
        "ptr",
        "delete",
        "add_window",
        "add_sizer",
        "add_spacer",
        "realize",
        "add_button",
        "proportion",
        "expand",
        "border",
        "left",
        "right",
        "top",
        "bottom",
        "align_h",
        "align_v",
        "create",
        "get_bitmap",
        "from_base64",
    };
    return ROLES;
}

bool UiIsKnownRole(std::string_view role)
{
    const std::vector<std::string_view>& roles = UiRoleVocabulary();
    return std::ranges::find(roles, role) != roles.end();
}

const std::vector<std::string_view>& UiIdiomVocabulary()
{
    static const std::vector<std::string_view> IDIOMS {
        "constructor", "builder", "procedure", "method-on-self", "method-on-parent", "unsupported",
    };
    return IDIOMS;
}

bool UiIsKnownIdiom(std::string_view idiom)
{
    const std::vector<std::string_view>& idioms = UiIdiomVocabulary();
    return std::ranges::find(idioms, idiom) != idioms.end();
}

const std::vector<std::string_view>& UiReasonCodeVocabulary()
{
    static const std::vector<std::string_view> REASONS {
        "no_method", "no_naming", "not_supported", "not_in_profile", "ambiguous", "hand_maintained",
    };
    return REASONS;
}

bool UiIsKnownReason(std::string_view reason)
{
    const std::vector<std::string_view>& reasons = UiReasonCodeVocabulary();
    return std::ranges::find(reasons, reason) != reasons.end();
}

const std::vector<std::string_view>& UiRequiredClasses()
{
    static const std::vector<std::string_view> CLASSES {
        "wxFrame",      "wxDialog",       "wxTextCtrl",
        "wxBoxSizer",   "wxStaticBitmap", "wxStdDialogButtonSizer",
        "wxSizerFlags",
    };
    return CLASSES;
}

const std::vector<std::string_view>& UiRequiredRolesForClass(std::string_view wx_class)
{
    static const std::vector<std::string_view> FRAME_ROLES {
        "ctor",   "show",      "hide",     "set_title", "set_size",         "set_min_size",
        "center", "set_sizer", "set_font", "set_icon",  "create_statusbar", "set_menubar",
        "bind",   "bind_id",   "destroy",  "ptr",       "delete",
    };
    static const std::vector<std::string_view> DIALOG_ROLES {
        "ctor",          "show",
        "hide",          "set_title",
        "set_size",      "set_min_size",
        "center",        "set_sizer",
        "set_font",      "set_icon",
        "show_modal",    "end_modal",
        "set_escape_id", "set_affirmative_id",
        "bind",          "bind_id",
        "destroy",       "ptr",
        "delete",
    };
    static const std::vector<std::string_view> TEXT_CTRL_ROLES {
        "ctor",     "show",           "hide", "set_value", "set_label", "set_size", "set_min_size",
        "set_font", "set_size_hints", "bind", "bind_id",   "destroy",   "ptr",      "delete",
    };
    static const std::vector<std::string_view> BOX_SIZER_ROLES {
        "ctor", "add_window", "add_sizer", "add_spacer", "destroy", "ptr", "delete",
    };
    static const std::vector<std::string_view> STATIC_BITMAP_ROLES {
        "ctor", "set_bitmap", "set_size", "set_min_size", "show",
        "hide", "destroy",    "ptr",      "delete",
    };
    static const std::vector<std::string_view> STD_BUTTON_ROLES {
        "ctor", "add_button", "realize", "add_window", "destroy", "ptr", "delete",
    };
    static const std::vector<std::string_view> SIZER_FLAGS_ROLES {
        "ctor", "proportion", "expand",  "border",  "left",   "right",
        "top",  "bottom",     "align_h", "align_v", "delete",
    };

    if (wx_class == "wxFrame")
    {
        return FRAME_ROLES;
    }
    if (wx_class == "wxDialog")
    {
        return DIALOG_ROLES;
    }
    if (wx_class == "wxTextCtrl")
    {
        return TEXT_CTRL_ROLES;
    }
    if (wx_class == "wxBoxSizer")
    {
        return BOX_SIZER_ROLES;
    }
    if (wx_class == "wxStaticBitmap")
    {
        return STATIC_BITMAP_ROLES;
    }
    if (wx_class == "wxStdDialogButtonSizer")
    {
        return STD_BUTTON_ROLES;
    }
    if (wx_class == "wxSizerFlags")
    {
        return SIZER_FLAGS_ROLES;
    }

    static const std::vector<std::string_view> NO_ROLES {};
    return NO_ROLES;
}

// -------------------------------------------------------------------------
// Header hash
// -------------------------------------------------------------------------

std::string UiHeadersHash(const fs::path& headers_dir, const fs::path& defs_file)
{
    std::vector<fs::path> header_files;
    if (fs::exists(headers_dir))
    {
        for (const auto& entry: fs::recursive_directory_iterator(
                 headers_dir, fs::directory_options::skip_permission_denied))
        {
            std::error_code status_error;
            if (!entry.is_regular_file(status_error) || status_error)
            {
                continue;
            }
            header_files.push_back(entry.path());
        }
    }

    std::ranges::sort(header_files,
                      [&headers_dir](const fs::path& lhs, const fs::path& rhs)
                      {
                          return ui_detail::RelativeGenericPath(lhs, headers_dir) <
                                 ui_detail::RelativeGenericPath(rhs, headers_dir);
                      });

    std::uint64_t hash_value = ui_detail::FNV_OFFSET_BASIS;
    static constexpr std::string_view NUL_SEPARATOR { "\0", 1 };

    for (const fs::path& header_file: header_files)
    {
        hash_value = ui_detail::Fnv1aUpdate(
            hash_value, ui_detail::RelativeGenericPath(header_file, headers_dir));
        hash_value = ui_detail::Fnv1aUpdate(hash_value, NUL_SEPARATOR);
        hash_value = ui_detail::Fnv1aUpdate(hash_value, ui_detail::ReadFileBytes(header_file));
    }

    hash_value = ui_detail::Fnv1aUpdate(hash_value, defs_file.filename().generic_string());
    hash_value = ui_detail::Fnv1aUpdate(hash_value, NUL_SEPARATOR);
    hash_value = ui_detail::Fnv1aUpdate(hash_value, ui_detail::ReadFileBytes(defs_file));

    return ui_detail::ToHexString(hash_value);
}

// -------------------------------------------------------------------------
// Serialization
// -------------------------------------------------------------------------

std::string UiDescriptorToJson(const UiDescriptor& descriptor)
{
    std::string buffer {};
    const glz::error_ctx errc = glz::write<glz::opts { .prettify = true }>(descriptor, buffer);
    if (errc)
    {
        return {};
    }
    return buffer;
}

bool UiDescriptorFromJson(const std::string& json, UiDescriptor& out, std::string& error)
{
    UiDescriptor parsed {};
    const glz::error_ctx errc =
        glz::read<glz::opts { .error_on_unknown_keys = false }>(parsed, json);
    if (errc)
    {
        error = "descriptor JSON parse error: " + glz::format_error(errc, json);
        return false;
    }
    out = std::move(parsed);
    error.clear();
    return true;
}

// -------------------------------------------------------------------------
// Validation
// -------------------------------------------------------------------------

bool UiValidateDescriptor(const UiDescriptor& descriptor, std::string& error)
{
    if (descriptor.schema != UI_SCHEMA_VERSION)
    {
        error = "schema must be " + std::to_string(UI_SCHEMA_VERSION);
        return false;
    }
    if (descriptor.lang.empty())
    {
        error = "lang must not be empty";
        return false;
    }

    const UiGeneratedBy& generated_by = descriptor.generated_by;
    if (generated_by.tool.empty() || generated_by.version.empty() ||
        generated_by.headers_hash.empty() || generated_by.profile.empty())
    {
        error = "generated_by requires tool, version, headers_hash and profile";
        return false;
    }

    // Required-class coverage is checked before the structural rules because it is the
    // descriptor's primary contract: a missing class means the backend cannot build a
    // project at all, which is a more useful diagnostic than a stray missing idiom.
    for (const std::string_view required_class: UiRequiredClasses())
    {
        if (!ui_detail::ValidateRequiredClass(descriptor, std::string(required_class), error))
        {
            return false;
        }
    }

    static constexpr std::string_view NAMING_KEYS[] {
        "class_type", "constructor", "method", "constant", "module",
    };
    for (const std::string_view naming_key: NAMING_KEYS)
    {
        const std::map<std::string, std::string>::const_iterator naming_iter =
            descriptor.naming.find(std::string(naming_key));
        if (naming_iter == descriptor.naming.end())
        {
            error = "naming is missing '" + std::string(naming_key) + "'";
            return false;
        }
        if (naming_iter->second.empty())
        {
            error = "naming entry '" + std::string(naming_key) + "' must not be empty";
            return false;
        }
    }

    for (const auto& [class_name, class_info]: descriptor.classes)
    {
        for (const auto& [role, callable]: class_info.roles)
        {
            std::ignore = callable;
            if (!UiIsKnownRole(role))
            {
                error = "class '" + class_name + "' uses the unknown role '" + role + "'";
                return false;
            }
        }
    }
    for (const UiUnsupported& entry: descriptor.unsupported)
    {
        if (!entry.role.empty() && !UiIsKnownRole(entry.role))
        {
            error = "unsupported entry '" + entry.class_name + "' uses the unknown role '" +
                    entry.role + "'";
            return false;
        }
    }

    std::vector<ui_detail::LabeledCallable> callables;
    ui_detail::CollectCallables(descriptor, callables);
    for (const ui_detail::LabeledCallable& labeled: callables)
    {
        if (!labeled.callable->idiom.empty() && !UiIsKnownIdiom(labeled.callable->idiom))
        {
            error = labeled.label + ": unknown idiom '" + labeled.callable->idiom + "'";
            return false;
        }
        if (labeled.callable->reason.has_value() && !labeled.callable->reason->empty() &&
            !UiIsKnownReason(labeled.callable->reason.value()))
        {
            error =
                labeled.label + ": unknown reason code '" + labeled.callable->reason.value() + "'";
            return false;
        }
    }

    for (const ui_detail::LabeledCallable& labeled: callables)
    {
        if (!ui_detail::ValidateCallableShape(*labeled.callable, labeled.label, error))
        {
            return false;
        }
    }

    const UiSizerOps& ops = descriptor.sizers.wx_box_sizer;
    const UiFlags& flags = descriptor.sizers.flags;
    if (!ui_detail::RequireBlockCallable(ops.ctor, "sizers.wxBoxSizer.ctor", error) ||
        !ui_detail::RequireBlockCallable(ops.add_window, "sizers.wxBoxSizer.add_window", error) ||
        !ui_detail::RequireBlockCallable(ops.add_sizer, "sizers.wxBoxSizer.add_sizer", error) ||
        !ui_detail::RequireBlockCallable(ops.add_spacer, "sizers.wxBoxSizer.add_spacer", error) ||
        !ui_detail::RequireBlockCallable(descriptor.events.bind, "events.bind", error) ||
        !ui_detail::RequireBlockCallable(descriptor.events.bind_id, "events.bind_id", error) ||
        !ui_detail::RequireBlockCallable(descriptor.bitmap.from_base64, "bitmap.from_base64",
                                         error) ||
        !ui_detail::RequireBlockCallable(descriptor.bitmap.get_bitmap, "bitmap.get_bitmap",
                                         error) ||
        !ui_detail::RequireBlockCallable(descriptor.bitmap.delete_fn, "bitmap.delete", error) ||
        !ui_detail::RequireBlockCallable(descriptor.font.create, "font.create", error) ||
        !ui_detail::RequireBlockCallable(descriptor.font.delete_fn, "font.delete", error) ||
        !ui_detail::RequireBlockCallable(descriptor.std_buttons.create, "std_buttons.create",
                                         error) ||
        !ui_detail::RequireBlockCallable(descriptor.std_buttons.add_button,
                                         "std_buttons.add_button", error) ||
        !ui_detail::RequireBlockCallable(descriptor.std_buttons.realize, "std_buttons.realize",
                                         error) ||
        !ui_detail::RequireBlockCallable(descriptor.app.set_top_window, "app.set_top_window",
                                         error))
    {
        return false;
    }

    if (!ui_detail::RequireBlockCallable(flags.ctor, "sizers.flags.ctor", error) ||
        !ui_detail::RequireBlockCallable(flags.proportion, "sizers.flags.proportion", error) ||
        !ui_detail::RequireBlockCallable(flags.expand, "sizers.flags.expand", error) ||
        !ui_detail::RequireBlockCallable(flags.border, "sizers.flags.border", error) ||
        !ui_detail::RequireBlockCallable(flags.left, "sizers.flags.left", error) ||
        !ui_detail::RequireBlockCallable(flags.right, "sizers.flags.right", error) ||
        !ui_detail::RequireBlockCallable(flags.top, "sizers.flags.top", error) ||
        !ui_detail::RequireBlockCallable(flags.bottom, "sizers.flags.bottom", error) ||
        !ui_detail::RequireBlockCallable(flags.align_h, "sizers.flags.align_h", error) ||
        !ui_detail::RequireBlockCallable(flags.align_v, "sizers.flags.align_v", error))
    {
        return false;
    }

    error.clear();
    return true;
}

// -------------------------------------------------------------------------
// check-ui
// -------------------------------------------------------------------------

int UiCheckIr(const std::string& descriptor_json, const std::string& ir_json, std::ostream& out,
              std::ostream& err)
{
    UiDescriptor descriptor;
    std::string error;
    if (!UiDescriptorFromJson(descriptor_json, descriptor, error))
    {
        err << "Error: " << error << "\n";
        return 1;
    }

    if (!UiValidateDescriptor(descriptor, error))
    {
        err << "Error: invalid descriptor: " << error << "\n";
        return 1;
    }

    ui_detail::IrDocument ir;
    if (!ui_detail::ReadIrDocument(ir_json, ir, error))
    {
        err << "Error: " << error << "\n";
        return 1;
    }

    if (ir.schema != UI_SCHEMA_VERSION)
    {
        err << "Error: IR schema must be " << UI_SCHEMA_VERSION << ", found " << ir.schema << "\n";
        return 1;
    }

    for (const ui_detail::IrForm& form: ir.forms)
    {
        for (const ui_detail::IrChild& child: form.children)
        {
            for (const std::string& role: child.roles_used)
            {
                if (!UiIsKnownRole(role))
                {
                    err << "Error: IR uses the unknown role '" << role << "' on the node class '"
                        << child.node_class << "'\n";
                    return 1;
                }
            }
        }
    }

    std::vector<std::pair<std::string, std::string>> missing;
    std::set<std::pair<std::string, std::string>> seen;
    const auto require =
        [&descriptor, &missing, &seen](const std::string& class_name, const std::string& role)
    {
        if (ui_detail::ResolveCallable(descriptor, class_name, role) != nullptr)
        {
            return;
        }
        if (seen.insert(std::pair { class_name, role }).second)
        {
            missing.emplace_back(class_name, role);
        }
    };

    for (const ui_detail::IrForm& form: ir.forms)
    {
        require(form.node_class, "ctor");
        for (const ui_detail::IrChild& child: form.children)
        {
            for (const std::string& role: child.roles_used)
            {
                require(child.node_class, role);
            }
            if (child.in_sizer)
            {
                if (ui_detail::IsSizerClass(child.node_class))
                {
                    require(child.node_class, "add_sizer");
                }
                else
                {
                    require(child.node_class, "add_window");
                }
            }
        }
    }

    for (const auto& [class_name, role]: missing)
    {
        out << "MISSING " << descriptor.lang << ' ' << class_name << ' ' << role << '\n';
    }

    return missing.empty() ? 0 : 2;
}

// -------------------------------------------------------------------------
// Class selection (emit-ui)
// -------------------------------------------------------------------------

bool UiIsRequiredClass(std::string_view wx_class)
{
    const std::vector<std::string_view>& required_classes = UiRequiredClasses();
    return std::ranges::find(required_classes, wx_class) != required_classes.end();
}

std::vector<std::string> UiResolveClassSelection(const ParsedFFI& ffi,
                                                 const UiClassSelection& selection,
                                                 std::vector<std::string>& missing)
{
    missing.clear();
    std::vector<std::string> selected;

    if (selection.mode == UiClassMode::Form)
    {
        for (const std::string_view required_class: UiRequiredClasses())
        {
            selected.emplace_back(required_class);
        }
        return selected;
    }

    if (selection.mode == UiClassMode::File)
    {
        for (const std::string& class_name: selection.class_names)
        {
            if (class_name.empty())
            {
                continue;
            }
            if (std::ranges::find(selected, class_name) != selected.end() ||
                std::ranges::find(missing, class_name) != missing.end())
            {
                continue;
            }
            if (UiFindClass(ffi, class_name) == nullptr)
            {
                missing.push_back(class_name);
                continue;
            }
            selected.push_back(class_name);
        }
        return selected;
    }

    // Auto: every class the profiled model carries, de-duplicated and sorted ascending.
    std::set<std::string> resolved_names;
    for (const ClassInfo& class_info: ffi.classes)
    {
        if (!class_info.name.empty())
        {
            resolved_names.insert(class_info.name);
        }
    }
    return { resolved_names.begin(), resolved_names.end() };
}

void UiAccountForRequiredClasses(UiDescriptor& descriptor, const std::vector<std::string>& selected)
{
    for (const std::string_view required_class: UiRequiredClasses())
    {
        const std::string class_name(required_class);
        if (std::ranges::find(selected, class_name) != selected.end())
        {
            continue;
        }
        descriptor.unsupported.push_back(
            UiUnsupported { .class_name = class_name, .role = {}, .reason = "not_in_profile" });
    }
}

// -------------------------------------------------------------------------
// Model lookups
// -------------------------------------------------------------------------

const ClassInfo* UiFindClass(const ParsedFFI& ffi, std::string_view class_name)
{
    for (const ClassInfo& class_info: ffi.classes)
    {
        if (class_info.name == class_name)
        {
            return &class_info;
        }
    }
    return nullptr;
}

const FunctionDecl* UiFindMethod(const ParsedFFI& ffi, std::string_view class_name,
                                 std::string_view method_name)
{
    return ui_detail::FindInHierarchy(ffi, class_name, ui_detail::MatchesMethodName, method_name);
}

const FunctionDecl* UiFindConstructor(const ParsedFFI& ffi, std::string_view class_name)
{
    return ui_detail::FindInHierarchy(ffi, class_name, ui_detail::IsTrueConstructor, {});
}

const FunctionDecl* UiFindCanonicalConstructor(const ParsedFFI& ffi, std::string_view class_name)
{
    return ui_detail::FindInHierarchy(ffi, class_name, ui_detail::IsCanonicalConstructor, {});
}
