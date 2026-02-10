#pragma once

#include "wxffi_types.h"

#include <wx/version.h>

// TODO: [Randalphwa - 10-07-2024] I removed the nullptr classes until I find why
// they generate a compiler error
#if 0
/* nullptr */
TClass(wxAcceleratorTable) Null_AcceleratorTable();
TClass(wxBitmap) Null_Bitmap();
TClass(wxBrush) Null_Brush();
TClass(wxColour) Null_Colour();
TClass(wxCursor) Null_Cursor();
TClass(wxFont) Null_Font();
TClass(wxIcon) Null_Icon();
TClass(wxPalette) Null_Palette();
TClass(wxPen) Null_Pen();
#endif

/* Events */
int expEVT_AUITOOLBAR_TOOL_DROPDOWN();
int expEVT_AUITOOLBAR_OVERFLOW_CLICK();
int expEVT_AUITOOLBAR_RIGHT_CLICK();
int expEVT_AUITOOLBAR_MIDDLE_CLICK();
int expEVT_AUITOOLBAR_BEGIN_DRAG();
int expEVT_AUINOTEBOOK_PAGE_CLOSE();
int expEVT_AUINOTEBOOK_PAGE_CHANGED();
int expEVT_AUINOTEBOOK_PAGE_CHANGING();
int expEVT_AUINOTEBOOK_PAGE_CLOSED();
int expEVT_AUINOTEBOOK_BUTTON();
int expEVT_AUINOTEBOOK_BEGIN_DRAG();
int expEVT_AUINOTEBOOK_END_DRAG();
int expEVT_AUINOTEBOOK_DRAG_MOTION();
int expEVT_AUINOTEBOOK_ALLOW_DND();
int expEVT_AUINOTEBOOK_TAB_MIDDLE_DOWN();
int expEVT_AUINOTEBOOK_TAB_MIDDLE_UP();
int expEVT_AUINOTEBOOK_TAB_RIGHT_DOWN();
int expEVT_AUINOTEBOOK_TAB_RIGHT_UP();
int expEVT_AUINOTEBOOK_DRAG_DONE();
int expEVT_AUINOTEBOOK_BG_DCLICK();
int expEVT_AUI_PANE_BUTTON();
int expEVT_AUI_PANE_CLOSE();
int expEVT_AUI_PANE_MAXIMIZE();
int expEVT_AUI_PANE_RESTORE();
int expEVT_AUI_RENDER();
int expEVT_AUI_FIND_MANAGER();
int expEVT_CALENDAR_SEL_CHANGED();
int expEVT_CALENDAR_PAGE_CHANGED();
int expEVT_CALENDAR_DOUBLECLICKED();
int expEVT_CALENDAR_WEEKDAY_CLICKED();
int expEVT_CALENDAR_WEEK_CLICKED();
int expEVT_CALENDAR_DAY_CHANGED();
int expEVT_CALENDAR_MONTH_CHANGED();
int expEVT_CALENDAR_YEAR_CHANGED();
int expEVT_COMMAND_CHOICEBOOK_PAGE_CHANGED();
int expEVT_COMMAND_CHOICEBOOK_PAGE_CHANGING();
int expEVT_CLIPBOARD_CHANGED();
int expEVT_COMMAND_COLOURPICKER_CHANGED();
int expEVT_COMMAND_COLLPANE_CHANGED();
int expEVT_COMMAND_BUTTON_CLICKED();
int expEVT_COMMAND_DATAVIEW_SELECTION_CHANGED();
int expEVT_COMMAND_DATAVIEW_ITEM_ACTIVATED();
int expEVT_COMMAND_DATAVIEW_ITEM_COLLAPSED();
int expEVT_COMMAND_DATAVIEW_ITEM_EXPANDED();
int expEVT_COMMAND_DATAVIEW_ITEM_COLLAPSING();
int expEVT_COMMAND_DATAVIEW_ITEM_EXPANDING();
int expEVT_COMMAND_DATAVIEW_ITEM_START_EDITING();
int expEVT_COMMAND_DATAVIEW_ITEM_EDITING_STARTED();
int expEVT_COMMAND_DATAVIEW_ITEM_EDITING_DONE();
int expEVT_COMMAND_DATAVIEW_ITEM_VALUE_CHANGED();
int expEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU();
int expEVT_COMMAND_DATAVIEW_COLUMN_HEADER_CLICK();
int expEVT_COMMAND_DATAVIEW_COLUMN_HEADER_RIGHT_CLICK();
int expEVT_COMMAND_DATAVIEW_COLUMN_SORTED();
int expEVT_COMMAND_DATAVIEW_COLUMN_REORDERED();
int expEVT_COMMAND_DATAVIEW_CACHE_HINT();
int expEVT_COMMAND_DATAVIEW_ITEM_BEGIN_DRAG();
int expEVT_COMMAND_DATAVIEW_ITEM_DROP_POSSIBLE();
int expEVT_COMMAND_DATAVIEW_ITEM_DROP();
int expEVT_DATE_CHANGED();
int expEVT_WINDOW_MODAL_DIALOG_CLOSED();
int expEVT_COMMAND_BUTTON_CLICKED();
int expEVT_COMMAND_CHECKBOX_CLICKED();
int expEVT_COMMAND_CHOICE_SELECTED();
int expEVT_COMMAND_LISTBOX_SELECTED();
int expEVT_COMMAND_LISTBOX_DOUBLECLICKED();
int expEVT_COMMAND_CHECKLISTBOX_TOGGLED();
int expEVT_COMMAND_MENU_SELECTED();
int expEVT_COMMAND_SLIDER_UPDATED();
int expEVT_COMMAND_RADIOBOX_SELECTED();
int expEVT_COMMAND_RADIOBUTTON_SELECTED();
int expEVT_COMMAND_VLBOX_SELECTED();
int expEVT_COMMAND_COMBOBOX_SELECTED();
int expEVT_COMMAND_TOOL_RCLICKED();
int expEVT_COMMAND_TOOL_DROPDOWN_CLICKED();
int expEVT_COMMAND_TOOL_ENTER();
int expEVT_COMMAND_COMBOBOX_DROPDOWN();
int expEVT_COMMAND_COMBOBOX_CLOSEUP();
int expEVT_COMMAND_THREAD();
int expEVT_LEFT_DOWN();
int expEVT_LEFT_UP();
int expEVT_MIDDLE_DOWN();
int expEVT_MIDDLE_UP();
int expEVT_RIGHT_DOWN();
int expEVT_RIGHT_UP();
int expEVT_MOTION();
int expEVT_ENTER_WINDOW();
int expEVT_LEAVE_WINDOW();
int expEVT_LEFT_DCLICK();
int expEVT_MIDDLE_DCLICK();
int expEVT_RIGHT_DCLICK();
int expEVT_SET_FOCUS();
int expEVT_KILL_FOCUS();
int expEVT_CHILD_FOCUS();
int expEVT_MOUSEWHEEL();
int expEVT_AUX1_DOWN();
int expEVT_AUX1_UP();
int expEVT_AUX1_DCLICK();
int expEVT_AUX2_DOWN();
int expEVT_AUX2_UP();
int expEVT_AUX2_DCLICK();
int expEVT_CHAR();
int expEVT_CHAR_HOOK();
int expEVT_NAVIGATION_KEY();
int expEVT_KEY_DOWN();
int expEVT_KEY_UP();
int expEVT_HOTKEY();
int expEVT_SET_CURSOR();
int expEVT_SCROLL_TOP();
int expEVT_SCROLL_BOTTOM();
int expEVT_SCROLL_LINEUP();
int expEVT_SCROLL_LINEDOWN();
int expEVT_SCROLL_PAGEUP();
int expEVT_SCROLL_PAGEDOWN();
int expEVT_SCROLL_THUMBTRACK();
int expEVT_SCROLL_THUMBRELEASE();
int expEVT_SCROLL_CHANGED();
int expEVT_SPIN_UP();
int expEVT_SPIN_DOWN();
int expEVT_SPIN();
int expEVT_SCROLLWIN_TOP();
int expEVT_SCROLLWIN_BOTTOM();
int expEVT_SCROLLWIN_LINEUP();
int expEVT_SCROLLWIN_LINEDOWN();
int expEVT_SCROLLWIN_PAGEUP();
int expEVT_SCROLLWIN_PAGEDOWN();
int expEVT_SCROLLWIN_THUMBTRACK();
int expEVT_SCROLLWIN_THUMBRELEASE();
int expEVT_SIZE();
int expEVT_MOVE();
int expEVT_CLOSE_WINDOW();
int expEVT_END_SESSION();
int expEVT_QUERY_END_SESSION();
int expEVT_ACTIVATE_APP();
int expEVT_ACTIVATE();
int expEVT_CREATE();
int expEVT_DESTROY();
int expEVT_SHOW();
int expEVT_ICONIZE();
int expEVT_MAXIMIZE();
int expEVT_MOUSE_CAPTURE_CHANGED();
int expEVT_MOUSE_CAPTURE_LOST();
int expEVT_PAINT();
int expEVT_ERASE_BACKGROUND();
int expEVT_NC_PAINT();
int expEVT_MENU_OPEN();
int expEVT_MENU_CLOSE();
int expEVT_MENU_HIGHLIGHT();
int expEVT_CONTEXT_MENU();
int expEVT_SYS_COLOUR_CHANGED();
int expEVT_DISPLAY_CHANGED();
int expEVT_QUERY_NEW_PALETTE();
int expEVT_PALETTE_CHANGED();
int expEVT_JOY_BUTTON_DOWN();
int expEVT_JOY_BUTTON_UP();
int expEVT_JOY_MOVE();
int expEVT_JOY_ZMOVE();
int expEVT_DROP_FILES();
int expEVT_INIT_DIALOG();
int expEVT_IDLE();
int expEVT_UPDATE_UI();
int expEVT_SIZING();
int expEVT_MOVING();
int expEVT_MOVE_START();
int expEVT_MOVE_END();
int expEVT_HIBERNATE();
int expEVT_COMMAND_TEXT_COPY();
int expEVT_COMMAND_TEXT_CUT();
int expEVT_COMMAND_TEXT_PASTE();
int expEVT_COMMAND_LEFT_CLICK();
int expEVT_COMMAND_LEFT_DCLICK();
int expEVT_COMMAND_RIGHT_CLICK();
int expEVT_COMMAND_RIGHT_DCLICK();
int expEVT_COMMAND_SET_FOCUS();
int expEVT_COMMAND_KILL_FOCUS();
int expEVT_COMMAND_ENTER();
int expEVT_HELP();
int expEVT_DETAILED_HELP();
int expEVT_COMMAND_TOOL_CLICKED();

/* Short-form event type aliases (wx 3.0+ style) */
int expEVT_BUTTON();
int expEVT_CHECKBOX();
int expEVT_CHOICE();
int expEVT_LISTBOX();
int expEVT_LISTBOX_DCLICK();
int expEVT_CHECKLISTBOX();
int expEVT_MENU();
int expEVT_SLIDER();
int expEVT_RADIOBOX();
int expEVT_RADIOBUTTON();
int expEVT_COMBOBOX();
int expEVT_TOOL();
int expEVT_TOOL_RCLICKED();
int expEVT_TOOL_DROPDOWN();
int expEVT_TOOL_ENTER();
int expEVT_COMBOBOX_DROPDOWN();
int expEVT_COMBOBOX_CLOSEUP();
int expEVT_TEXT();
int expEVT_TEXT_ENTER();
int expEVT_TEXT_URL();
int expEVT_TEXT_MAXLEN();
int expEVT_SPINCTRL();
int expEVT_SPINCTRLDOUBLE();
int expEVT_TOGGLEBUTTON();
int expEVT_VLBOX();
int expEVT_THREAD();
int expEVT_TEXT_COPY();
int expEVT_TEXT_CUT();
int expEVT_TEXT_PASTE();
int expEVT_SEARCHCTRL_SEARCH_BTN();
int expEVT_SEARCHCTRL_CANCEL_BTN();
int expEVT_SPLITTER_SASH_POS_CHANGED();
int expEVT_SPLITTER_SASH_POS_CHANGING();
int expEVT_SPLITTER_UNSPLIT();
int expEVT_SPLITTER_DOUBLECLICKED();
int expEVT_NOTEBOOK_PAGE_CHANGED();
int expEVT_NOTEBOOK_PAGE_CHANGING();
int expEVT_LISTBOOK_PAGE_CHANGED();
int expEVT_LISTBOOK_PAGE_CHANGING();
int expEVT_CHOICEBOOK_PAGE_CHANGED();
int expEVT_CHOICEBOOK_PAGE_CHANGING();
int expEVT_TREEBOOK_PAGE_CHANGED();
int expEVT_TREEBOOK_PAGE_CHANGING();
int expEVT_TREEBOOK_NODE_COLLAPSED();
int expEVT_TREEBOOK_NODE_EXPANDED();
int expEVT_TOOLBOOK_PAGE_CHANGED();
int expEVT_TOOLBOOK_PAGE_CHANGING();
int expEVT_COLOURPICKER_CHANGED();
int expEVT_FILEPICKER_CHANGED();
int expEVT_DIRPICKER_CHANGED();
int expEVT_FONTPICKER_CHANGED();
int expEVT_HYPERLINK();
int expEVT_DATAVIEW_SELECTION_CHANGED();
int expEVT_DATAVIEW_ITEM_ACTIVATED();
int expEVT_DATAVIEW_ITEM_COLLAPSED();
int expEVT_DATAVIEW_ITEM_EXPANDED();
int expEVT_DATAVIEW_ITEM_COLLAPSING();
int expEVT_DATAVIEW_ITEM_EXPANDING();
int expEVT_DATAVIEW_ITEM_EDITING_STARTED();
int expEVT_DATAVIEW_ITEM_EDITING_DONE();
int expEVT_DATAVIEW_ITEM_VALUE_CHANGED();

/* kwxfindrepldlg.h */
int expEVT_COMMAND_FIND();
int expEVT_COMMAND_FIND_NEXT();
int expEVT_COMMAND_FIND_REPLACE();
int expEVT_COMMAND_FIND_REPLACE_ALL();
int expEVT_COMMAND_FIND_CLOSE();

int expEVT_FILECTRL_SELECTIONCHANGED();
int expEVT_FILECTRL_FILEACTIVATED();
int expEVT_FILECTRL_FOLDERCHANGED();
int expEVT_FILECTRL_FILTERCHANGED();
int expEVT_COMMAND_FILEPICKER_CHANGED();
int expEVT_COMMAND_DIRPICKER_CHANGED();
int expEVT_COMMAND_FONTPICKER_CHANGED();
int expEVT_FSWATCHER();
int expEVT_GRID_CELL_LEFT_CLICK();
int expEVT_GRID_CELL_RIGHT_CLICK();
int expEVT_GRID_CELL_LEFT_DCLICK();
int expEVT_GRID_CELL_RIGHT_DCLICK();
int expEVT_GRID_LABEL_LEFT_CLICK();
int expEVT_GRID_LABEL_RIGHT_CLICK();
int expEVT_GRID_LABEL_LEFT_DCLICK();
int expEVT_GRID_LABEL_RIGHT_DCLICK();
int expEVT_GRID_ROW_SIZE();
int expEVT_GRID_COL_SIZE();
int expEVT_GRID_RANGE_SELECT();
int expEVT_GRID_CELL_CHANGING();
int expEVT_GRID_CELL_CHANGED();
int expEVT_GRID_SELECT_CELL();
int expEVT_GRID_EDITOR_SHOWN();
int expEVT_GRID_EDITOR_HIDDEN();
int expEVT_GRID_EDITOR_CREATED();
int expEVT_GRID_CELL_BEGIN_DRAG();
int expEVT_GRID_COL_MOVE();
int expEVT_GRID_COL_SORT();
int expEVT_QUERY_LAYOUT_INFO();
int expEVT_CALCULATE_LAYOUT();
int expEVT_SASH_DRAGGED();
int expEVT_COMMAND_HEADER_CLICK();
int expEVT_COMMAND_HEADER_RIGHT_CLICK();
int expEVT_COMMAND_HEADER_MIDDLE_CLICK();
int expEVT_COMMAND_HEADER_DCLICK();
int expEVT_COMMAND_HEADER_RIGHT_DCLICK();
int expEVT_COMMAND_HEADER_MIDDLE_DCLICK();
int expEVT_COMMAND_HEADER_SEPARATOR_DCLICK();
int expEVT_COMMAND_HEADER_BEGIN_RESIZE();
int expEVT_COMMAND_HEADER_RESIZING();
int expEVT_COMMAND_HEADER_END_RESIZE();
int expEVT_COMMAND_HEADER_BEGIN_REORDER();
int expEVT_COMMAND_HEADER_END_REORDER();
int expEVT_COMMAND_HEADER_DRAGGING_CANCELLED();
int expEVT_COMMAND_HTML_CELL_CLICKED();
int expEVT_COMMAND_HTML_CELL_HOVER();
int expEVT_COMMAND_HTML_LINK_CLICKED();
int expEVT_COMMAND_HYPERLINK();
int expEVT_COMMAND_LIST_BEGIN_DRAG();
int expEVT_COMMAND_LIST_BEGIN_RDRAG();
int expEVT_COMMAND_LIST_BEGIN_LABEL_EDIT();
int expEVT_COMMAND_LIST_END_LABEL_EDIT();
int expEVT_COMMAND_LIST_DELETE_ITEM();
int expEVT_COMMAND_LIST_DELETE_ALL_ITEMS();
int expEVT_COMMAND_LIST_ITEM_SELECTED();
int expEVT_COMMAND_LIST_ITEM_DESELECTED();
int expEVT_COMMAND_LIST_KEY_DOWN();
int expEVT_COMMAND_LIST_INSERT_ITEM();
int expEVT_COMMAND_LIST_COL_CLICK();
int expEVT_COMMAND_LIST_ITEM_RIGHT_CLICK();
int expEVT_COMMAND_LIST_ITEM_MIDDLE_CLICK();
int expEVT_COMMAND_LIST_ITEM_ACTIVATED();
int expEVT_COMMAND_LIST_CACHE_HINT();
int expEVT_COMMAND_LIST_COL_RIGHT_CLICK();
int expEVT_COMMAND_LIST_COL_BEGIN_DRAG();
int expEVT_COMMAND_LIST_COL_DRAGGING();
int expEVT_COMMAND_LIST_COL_END_DRAG();
int expEVT_COMMAND_LIST_ITEM_FOCUSED();
int expEVT_COMMAND_LISTBOOK_PAGE_CHANGED();
int expEVT_COMMAND_LISTBOOK_PAGE_CHANGING();

int expEVT_COMMAND_NOTEBOOK_PAGE_CHANGED();
int expEVT_COMMAND_NOTEBOOK_PAGE_CHANGING();
int expEVT_POWER_SUSPENDING();
int expEVT_POWER_SUSPENDED();
int expEVT_POWER_SUSPEND_CANCEL();
int expEVT_POWER_RESUME();
int expEVT_END_PROCESS();
int expEVT_PG_SELECTED();
int expEVT_PG_CHANGING();
int expEVT_PG_CHANGED();
int expEVT_PG_HIGHLIGHTED();
int expEVT_PG_RIGHT_CLICK();
int expEVT_PG_PAGE_CHANGED();
int expEVT_PG_ITEM_COLLAPSED();
int expEVT_PG_ITEM_EXPANDED();
int expEVT_PG_DOUBLE_CLICK();
int expEVT_COMMAND_RIBBONBAR_PAGE_CHANGED();
int expEVT_COMMAND_RIBBONBAR_PAGE_CHANGING();
int expEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_DOWN();
int expEVT_COMMAND_RIBBONBAR_TAB_MIDDLE_UP();
int expEVT_COMMAND_RIBBONBAR_TAB_RIGHT_DOWN();
int expEVT_COMMAND_RIBBONBAR_TAB_RIGHT_UP();
int expEVT_COMMAND_RIBBONBUTTON_CLICKED();
int expEVT_COMMAND_RIBBONBUTTON_DROPDOWN_CLICKED();
int expEVT_COMMAND_RIBBONGALLERY_HOVER_CHANGED();
int expEVT_COMMAND_RIBBONGALLERY_SELECTED();
int expEVT_COMMAND_RIBBONTOOL_CLICKED();
int expEVT_COMMAND_RIBBONTOOL_DROPDOWN_CLICKED();
int expEVT_COMMAND_RICHTEXT_LEFT_CLICK();
int expEVT_COMMAND_RICHTEXT_RIGHT_CLICK();
int expEVT_COMMAND_RICHTEXT_MIDDLE_CLICK();
int expEVT_COMMAND_RICHTEXT_LEFT_DCLICK();
int expEVT_COMMAND_RICHTEXT_RETURN();
int expEVT_COMMAND_RICHTEXT_CHARACTER();
int expEVT_COMMAND_RICHTEXT_DELETE();
int expEVT_COMMAND_RICHTEXT_STYLESHEET_CHANGING();
int expEVT_COMMAND_RICHTEXT_STYLESHEET_CHANGED();
int expEVT_COMMAND_RICHTEXT_STYLESHEET_REPLACING();
int expEVT_COMMAND_RICHTEXT_STYLESHEET_REPLACED();
int expEVT_COMMAND_RICHTEXT_CONTENT_INSERTED();
int expEVT_COMMAND_RICHTEXT_CONTENT_DELETED();
int expEVT_COMMAND_RICHTEXT_STYLE_CHANGED();
int expEVT_COMMAND_RICHTEXT_SELECTION_CHANGED();
int expEVT_COMMAND_RICHTEXT_BUFFER_RESET();
int expEVT_SOCKET();
int expEVT_COMMAND_SPINCTRL_UPDATED();
int expEVT_COMMAND_SPINCTRLDOUBLE_UPDATED();
int expEVT_COMMAND_SPLITTER_SASH_POS_CHANGED();
int expEVT_COMMAND_SPLITTER_SASH_POS_CHANGING();
int expEVT_COMMAND_SPLITTER_DOUBLECLICKED();
int expEVT_COMMAND_SPLITTER_UNSPLIT();
int expEVT_COMMAND_SEARCHCTRL_CANCEL_BTN();
int expEVT_COMMAND_SEARCHCTRL_SEARCH_BTN();

/* taskbaricon.cpp */
int expEVT_TASKBAR_MOVE();
int expEVT_TASKBAR_LEFT_DOWN();
int expEVT_TASKBAR_LEFT_UP();
int expEVT_TASKBAR_RIGHT_DOWN();
int expEVT_TASKBAR_RIGHT_UP();
int expEVT_TASKBAR_LEFT_DCLICK();
int expEVT_TASKBAR_RIGHT_DCLICK();
int expEVT_TASKBAR_BALLOON_TIMEOUT();
int expEVT_TASKBAR_BALLOON_CLICK();

int expEVT_COMMAND_TEXT_UPDATED();
int expEVT_COMMAND_TEXT_ENTER();
int expEVT_COMMAND_TEXT_URL();
int expEVT_COMMAND_TEXT_MAXLEN();
int expEVT_COMMAND_TOGGLEBUTTON_CLICKED();
int expEVT_TIMER();
int expEVT_COMMAND_TOOLBOOK_PAGE_CHANGED();
int expEVT_COMMAND_TOOLBOOK_PAGE_CHANGING();
int expEVT_COMMAND_TREE_BEGIN_DRAG();
int expEVT_COMMAND_TREE_BEGIN_RDRAG();
int expEVT_COMMAND_TREE_BEGIN_LABEL_EDIT();
int expEVT_COMMAND_TREE_END_LABEL_EDIT();
int expEVT_COMMAND_TREE_DELETE_ITEM();
int expEVT_COMMAND_TREE_GET_INFO();
int expEVT_COMMAND_TREE_SET_INFO();
int expEVT_COMMAND_TREE_ITEM_EXPANDED();
int expEVT_COMMAND_TREE_ITEM_EXPANDING();
int expEVT_COMMAND_TREE_ITEM_COLLAPSED();
int expEVT_COMMAND_TREE_ITEM_COLLAPSING();
int expEVT_COMMAND_TREE_SEL_CHANGED();
int expEVT_COMMAND_TREE_SEL_CHANGING();
int expEVT_COMMAND_TREE_KEY_DOWN();
int expEVT_COMMAND_TREE_ITEM_ACTIVATED();
int expEVT_COMMAND_TREE_ITEM_RIGHT_CLICK();
int expEVT_COMMAND_TREE_ITEM_MIDDLE_CLICK();
int expEVT_COMMAND_TREE_END_DRAG();
int expEVT_COMMAND_TREE_STATE_IMAGE_CLICK();
int expEVT_COMMAND_TREE_ITEM_GETTOOLTIP();
int expEVT_COMMAND_TREE_ITEM_MENU();
int expEVT_COMMAND_TREEBOOK_PAGE_CHANGED();
int expEVT_COMMAND_TREEBOOK_PAGE_CHANGING();
int expEVT_COMMAND_TREEBOOK_NODE_COLLAPSED();
int expEVT_COMMAND_TREEBOOK_NODE_EXPANDED();
int expEVT_COLLAPSIBLEPANE_CHANGED();
int expEVT_TREELIST_SELECTION_CHANGED();
int expEVT_TREELIST_ITEM_EXPANDING();
int expEVT_TREELIST_ITEM_EXPANDED();
int expEVT_TREELIST_ITEM_CHECKED();
int expEVT_TREELIST_ITEM_ACTIVATED();
int expEVT_TREELIST_ITEM_CONTEXT_MENU();
int expEVT_TREELIST_COLUMN_SORTED();
int expEVT_WEBVIEW_NAVIGATING();
int expEVT_WEBVIEW_NAVIGATED();
int expEVT_WEBVIEW_LOADED();
int expEVT_WEBVIEW_ERROR();
int expEVT_WEBVIEW_NEWWINDOW();
int expEVT_WEBVIEW_TITLE_CHANGED();
int expEVT_WEBVIEW_FULLSCREEN_CHANGED();
int expEVT_WEBVIEW_SCRIPT_MESSAGE_RECEIVED();
int expEVT_WEBVIEW_SCRIPT_RESULT();
int expEVT_WIZARD_PAGE_CHANGED();
int expEVT_WIZARD_PAGE_CHANGING();
int expEVT_WIZARD_CANCEL();
int expEVT_WIZARD_HELP();
int expEVT_WIZARD_FINISHED();
int expEVT_WIZARD_PAGE_SHOWN();
int expEVT_DELETE();
int expEVT_HTML_CELL_CLICKED();
int expEVT_HTML_CELL_MOUSE_HOVER();
int expEVT_HTML_LINK_CLICKED();
int expEVT_HTML_SET_TITLE();
int expEVT_INPUT_SINK();
int expEVT_SORT();

/* Keys */
int expK_BACK();
int expK_TAB();
int expK_RETURN();
int expK_ESCAPE();
int expK_SPACE();
int expK_DELETE();
int expK_START();
int expK_LBUTTON();
int expK_RBUTTON();
int expK_CANCEL();
int expK_MBUTTON();
int expK_CLEAR();
int expK_SHIFT();
int expK_ALT();
int expK_CONTROL();
int expK_MENU();
int expK_PAUSE();
int expK_CAPITAL();
int expK_END();
int expK_HOME();
int expK_LEFT();
int expK_UP();
int expK_RIGHT();
int expK_DOWN();
int expK_SELECT();
int expK_PRINT();
int expK_EXECUTE();
int expK_SNAPSHOT();
int expK_INSERT();
int expK_HELP();
int expK_NUMPAD0();
int expK_NUMPAD1();
int expK_NUMPAD2();
int expK_NUMPAD3();
int expK_NUMPAD4();
int expK_NUMPAD5();
int expK_NUMPAD6();
int expK_NUMPAD7();
int expK_NUMPAD8();
int expK_NUMPAD9();
int expK_MULTIPLY();
int expK_ADD();
int expK_SEPARATOR();
int expK_SUBTRACT();
int expK_DECIMAL();
int expK_DIVIDE();
int expK_F1();
int expK_F2();
int expK_F3();
int expK_F4();
int expK_F5();
int expK_F6();
int expK_F7();
int expK_F8();
int expK_F9();
int expK_F10();
int expK_F11();
int expK_F12();
int expK_F13();
int expK_F14();
int expK_F15();
int expK_F16();
int expK_F17();
int expK_F18();
int expK_F19();
int expK_F20();
int expK_F21();
int expK_F22();
int expK_F23();
int expK_F24();
int expK_NUMLOCK();
int expK_SCROLL();
int expK_PAGEUP();
int expK_PAGEDOWN();
int expK_NUMPAD_SPACE();
int expK_NUMPAD_TAB();
int expK_NUMPAD_ENTER();
int expK_NUMPAD_F1();
int expK_NUMPAD_F2();
int expK_NUMPAD_F3();
int expK_NUMPAD_F4();
int expK_NUMPAD_HOME();
int expK_NUMPAD_LEFT();
int expK_NUMPAD_UP();
int expK_NUMPAD_RIGHT();
int expK_NUMPAD_DOWN();
int expK_NUMPAD_PAGEUP();
int expK_NUMPAD_PAGEDOWN();
int expK_NUMPAD_END();
int expK_NUMPAD_BEGIN();
int expK_NUMPAD_INSERT();
int expK_NUMPAD_DELETE();
int expK_NUMPAD_EQUAL();
int expK_NUMPAD_MULTIPLY();
int expK_NUMPAD_ADD();
int expK_NUMPAD_SEPARATOR();
int expK_NUMPAD_SUBTRACT();
int expK_NUMPAD_DECIMAL();
int expK_NUMPAD_DIVIDE();

/* Misc. */
int kwxSysErrorCode();
void* kwxSysErrorMsg(int nErrCode);
void LogErrorMsg(TClass(wxString) message);
void LogFatalErrorMsg(TClass(wxString) message);
void LogMessageMsg(TClass(wxString) message);
void LogWarningMsg(TClass(wxString) message);
void expSetDefaultAssertHandler();
TBool Quantize(TClass(wxImage) src, TClass(wxImage) dest, int desiredNoColours, void* eightBitData,
               int flags);
TBool QuantizePalette(TClass(wxImage) src, TClass(wxImage) dest, void* pPalette,
                      int desiredNoColours, void* eightBitData, int flags);
void wxCFree(void* pointer);
TClass(kwxLocale) wxGetkwxLocale();
void* wxGetkwxTranslation(TStringVoid text);
void wxMutexGui_Enter();
void wxMutexGui_Leave();

/* kwxArtProv */
TClassDefExtend(kwxArtProv, wxArtProvider) TClass(kwxArtProv)
    kwxArtProv_Create(void* pObject, void* callback);
void kwxArtProv_Release(TSelf(kwxArtProv) pObject);

/* kwxClient */
TClassDefExtend(kwxClient, wxClient) TClass(kwxClient)
    kwxClient_Create(void* kwxObject, void* connectFunc);
void kwxClient_Delete(TSelf(kwxClient) pObject);
void kwxClient_MakeConnection(TSelf(kwxClient) pObject, TClass(wxString) host,
                              TClass(wxServer) server, TClass(wxString) topic);

/* kwxCommand */
TClassDefExtend(kwxCommand, wxCommand) TBool kwxCommand_CanUndo(TSelf(kwxCommand) pObject);
TClass(kwxCommand)
    kwxCommand_Create(int canUndo, TClass(wxString) name, void* pObject, void* callback);
void kwxCommand_Delete(TSelf(kwxCommand) pObject);
TClass(wxString) kwxCommand_GetName(TSelf(kwxCommand) pObject);

/* kwxConnection */
TClassDefExtend(kwxConnection, wxConnection) int kwxConnection_Advise(TSelf(kwxConnection) pObject,
                                                                      TClass(wxString) item,
                                                                      void* data, int size,
                                                                      int format);
void kwxConnection_Compress(TSelf(kwxConnection) pObject, int enable);
TClass(kwxConnection) kwxConnection_Create(void* pObject, void* buffer, int size);
TClass(kwxConnection) kwxConnection_CreateDefault(TSelf(kwxConnection) pObject);
void kwxConnection_Delete(TSelf(kwxConnection) pObject);
TBool kwxConnection_Disconnect(TSelf(kwxConnection) pObject);
TBool kwxConnection_Execute(TSelf(kwxConnection) pObject, TClass(wxString) data, int size,
                            int format);
TBool kwxConnection_Poke(TSelf(kwxConnection) pObject, TClass(wxString) item, void* data, int size,
                         int format);
void* kwxConnection_Request(TSelf(kwxConnection) pObject, TClass(wxString) item,
                            TClass(wxSize) size, int format);
void kwxConnection_SetOnAdvise(TSelf(kwxConnection) pObject, void* pFunction);
void kwxConnection_SetOnDisconnect(TSelf(kwxConnection) pObject, void* pFunction);
void kwxConnection_SetOnExecute(TSelf(kwxConnection) pObject, void* pFunction);
void kwxConnection_SetOnPoke(TSelf(kwxConnection) pObject, void* pFunction);
void kwxConnection_SetOnRequest(TSelf(kwxConnection) pObject, void* pFunction);
void kwxConnection_SetOnStartAdvise(TSelf(kwxConnection) pObject, void* pFunction);
void kwxConnection_SetOnStopAdvise(TSelf(kwxConnection) pObject, void* pFunction);
TBool kwxConnection_StartAdvise(TSelf(kwxConnection) pObject, TClass(wxString) item);
TBool kwxConnection_StopAdvise(TSelf(kwxConnection) pObject, TClass(wxString) item);

/* kwxDragDataObject */
TClassDef(kwxDragDataObject) TClass(kwxDragDataObject)
    kwxDragDataObject_Create(void* pObject, TClass(wxString) format, void* fnGetDataSize,
                             void* fnGetDataHere, void* fnSetData);
void kwxDragDataObject_Delete(TSelf(kwxDragDataObject) pObject);

/* kwxDropTarget */
TClassDefExtend(kwxDropTarget, wxDropTarget) TClass(kwxDropTarget)
    kwxDropTarget_Create(void* pObject);
void kwxDropTarget_Delete(TSelf(kwxDropTarget) pObject);
void kwxDropTarget_SetOnData(TSelf(kwxDropTarget) pObject, void* pFunction);
void kwxDropTarget_SetOnDragOver(TSelf(kwxDropTarget) pObject, void* pFunction);
void kwxDropTarget_SetOnDrop(TSelf(kwxDropTarget) pObject, void* pFunction);
void kwxDropTarget_SetOnEnter(TSelf(kwxDropTarget) pObject, void* pFunction);
void kwxDropTarget_SetOnLeave(TSelf(kwxDropTarget) pObject, void* pFunction);

/* kwxFileDropTarget */
TClassDefExtend(kwxFileDropTarget, wxFileDropTarget) TClass(kwxFileDropTarget)
    kwxFileDropTarget_Create(void* pObject, void* pFunction);
void kwxFileDropTarget_Delete(TSelf(kwxFileDropTarget) pObject);
void kwxFileDropTarget_SetOnData(TSelf(kwxFileDropTarget) pObject, void* pFunction);
void kwxFileDropTarget_SetOnDragOver(TSelf(kwxFileDropTarget) pObject, void* pFunction);
void kwxFileDropTarget_SetOnDrop(TSelf(kwxFileDropTarget) pObject, void* pFunction);
void kwxFileDropTarget_SetOnEnter(TSelf(kwxFileDropTarget) pObject, void* pFunction);
void kwxFileDropTarget_SetOnLeave(TSelf(kwxFileDropTarget) pObject, void* pFunction);

/* kwxGridTable */
TClassDefExtend(kwxGridTable, wxGridTableBase) TClass(kwxGridTable)
    kwxGridTable_Create(void* pObject, void* fnGetNumberRows, void* fnGetNumberCols,
                        void* fnGetValue, void* fnSetValue, void* fnIsEmptyCell, void* fnClear,
                        void* fnInsertRows, void* fnAppendRows, void* fnDeleteRows,
                        void* fnInsertCols, void* fnAppendCols, void* fnDeleteCols,
                        void* fnSetRowLabelValue, void* fnSetColLabelValue,
                        void* fnGetRowLabelValue, void* fnGetColLabelValue);
void kwxGridTable_Delete(TSelf(kwxGridTable) pObject);
TClass(wxView) kwxGridTable_GetView(TSelf(kwxGridTable) pObject);
void* kwxGridTable_SendTableMessage(TSelf(kwxGridTable) pObject, int id, int val1, int val2);

/* kwxLocale */
TClassDefExtend(kwxLocale, wxLocale)

    /* kwxLog */
    TClassDefExtend(kwxLog, wxLog) void kwxLog_AddTraceMask(TSelf(kwxLog) pObject, TStringVoid str);
TClass(kwxLog) kwxLog_Create(void* pObject, void* pFunction);
void kwxLog_Delete(TSelf(kwxLog) pObject);
void kwxLog_DontCreateOnDemand(TSelf(kwxLog) pObject);
int kwxLog_EnableLogging(TSelf(kwxLog) pObject, TBool doIt);
void kwxLog_Flush(TSelf(kwxLog) pObject);
void kwxLog_FlushActive(TSelf(kwxLog) pObject);
void* kwxLog_GetActiveTarget();
void* kwxLog_GetTimestamp(TSelf(kwxLog) pObject);
int kwxLog_GetVerbose(TSelf(kwxLog) pObject);
TBool kwxLog_HasPendingMessages(TSelf(kwxLog) pObject);
TBool kwxLog_IsAllowedTraceMask(TSelf(kwxLog) pObject, TClass(wxMask) mask);
TBool kwxLog_IsEnabled(TSelf(kwxLog) pObject);
void kwxLog_OnLog(TSelf(kwxLog) pObject, int level, void* szString, int timestamp);
void kwxLog_RemoveTraceMask(TSelf(kwxLog) pObject, TStringVoid str);
void kwxLog_Resume(TSelf(kwxLog) pObject);
void* kwxLog_SetActiveTarget(TSelf(kwxLog) pLogger);
void kwxLog_SetTimestamp(TSelf(kwxLog) pObject, void* timestamp);
// Deprecated:
// void       kwxLog_SetTraceMask( TSelf(kwxLog) pObject, int ulMask );
void kwxLog_SetVerbose(TSelf(kwxLog) pObject, int bVerbose);
void kwxLog_Suspend(TSelf(kwxLog) pObject);

/* kwxMessageParameters */
TClassDef(kwxMessageParameters) TClass(kwxMessageParameters)
    wxMessageParameters_Create(TStringVoid filePath, TStringVoid type, void* pObject,
                               void* pFunction);
void wxMessageParameters_Delete(TSelf(kwxMessageParameters) pObject);

/* kwxPlotCurve */
TClassDefExtend(kwxPlotCurve, wxPlotCurve) TClass(kwxPlotCurve)
    kwxPlotCurve_Create(void* pObject, void* fnGetStartX, void* endVal, void* y, int offsetY,
                        double startY, double endY);
void kwxPlotCurve_Delete(TSelf(kwxPlotCurve) pObject);
double kwxPlotCurve_GetEndY(TSelf(kwxPlotCurve) pObject);
int kwxPlotCurve_GetOffsetY(TSelf(kwxPlotCurve) pObject);
double kwxPlotCurve_GetStartY(TSelf(kwxPlotCurve) pObject);
void kwxPlotCurve_SetEndY(TSelf(kwxPlotCurve) pObject, double endY);
void kwxPlotCurve_SetOffsetY(TSelf(kwxPlotCurve) pObject, int offsetY);
void kwxPlotCurve_SetPenNormal(TSelf(kwxPlotCurve) pObject, TClass(wxPen) pen);
void kwxPlotCurve_SetPenSelected(TSelf(kwxPlotCurve) pObject, TClass(wxPen) pen);
void kwxPlotCurve_SetStartY(TSelf(kwxPlotCurve) pObject, double startY);

/* kwxPreviewControlBar */
TClassDefExtend(kwxPreviewControlBar, wxPreviewControlBar) TClass(kwxPreviewControlBar)
    kwxPreviewControlBar_Create(void* preview, int buttons, TClass(wxWindow) parent, void* title,
                                TRect(x, y, width, height), int style);

/* kwxPreviewFrame */
TClassDefExtend(kwxPreviewFrame, wxPreviewFrame) TClass(kwxPreviewFrame)
    kwxPreviewFrame_Create(void* pObject, void* init, void* createCanvas, void* createToolbar,
                           void* preview, TClass(wxWindow) parent, void* title,
                           TRect(x, y, width, height), int style);
void* kwxPreviewFrame_GetControlBar(TSelf(kwxPreviewFrame) pObject);
TClass(wxPreviewCanvas) kwxPreviewFrame_GetPreviewCanvas(TSelf(kwxPreviewFrame) pObject);
TClass(wxPrintPreview) kwxPreviewFrame_GetPrintPreview(TSelf(kwxPreviewFrame) pObject);
void kwxPreviewFrame_Initialize(TSelf(kwxPreviewFrame) pObject);
void kwxPreviewFrame_SetControlBar(TSelf(kwxPreviewFrame) pObject, void* obj);
void kwxPreviewFrame_SetPreviewCanvas(TSelf(kwxPreviewFrame) pObject, TClass(wxPreviewCanvas) obj);
void kwxPreviewFrame_SetPrintPreview(TSelf(kwxPreviewFrame) pObject, TClass(wxPrintPreview) obj);

/* kwxServer */
TClassDefExtend(kwxServer, wxServer) TClass(kwxServer)
    kwxServer_Create(void* kwxObject, void* connectFunc);
void kwxServer_Delete(TSelf(kwxServer) pObject);
int kwxServer_Initialize(TSelf(kwxServer) pObject, TClass(wxString) name);

/* kwxTextDropTarget */
TClassDefExtend(kwxTextDropTarget, wxTextDropTarget) TClass(kwxTextDropTarget)
    kwxTextDropTarget_Create(void* pObject, void* pFunction);
void kwxTextDropTarget_Delete(TSelf(kwxTextDropTarget) pObject);
void kwxTextDropTarget_SetOnData(TSelf(kwxTextDropTarget) pObject, void* pFunction);
void kwxTextDropTarget_SetOnDragOver(TSelf(kwxTextDropTarget) pObject, void* pFunction);
void kwxTextDropTarget_SetOnDrop(TSelf(kwxTextDropTarget) pObject, void* pFunction);
void kwxTextDropTarget_SetOnEnter(TSelf(kwxTextDropTarget) pObject, void* pFunction);
void kwxTextDropTarget_SetOnLeave(TSelf(kwxTextDropTarget) pObject, void* pFunction);

/* kwxTextValidator */
TClassDefExtend(kwxTextValidator, wxTextValidator) TClass(kwxTextValidator)
    kwxTextValidator_Create(void* pObject, void* pFunction, TStringVoid text, int style);

/* cbAntiflickerPlugin */
TClassDefExtend(cbAntiflickerPlugin, cbPluginBase) TClass(cbAntiflickerPlugin)
    cbAntiflickerPlugin_Create(void* pPanel, int paneMask);
TClass(cbAntiflickerPlugin) cbAntiflickerPlugin_CreateDefault();
void cbAntiflickerPlugin_Delete(TSelf(cbAntiflickerPlugin) pObject);

/* cbBarDragPlugin */
TClassDefExtend(cbBarDragPlugin, cbPluginBase) TClass(cbBarDragPlugin)
    cbBarDragPlugin_Create(void* pPanel, int paneMask);
TClass(cbBarDragPlugin) cbBarDragPlugin_CreateDefault();
void cbBarDragPlugin_Delete(TSelf(cbBarDragPlugin) pObject);

/* cbBarHintsPlugin */
TClassDefExtend(cbBarHintsPlugin, cbPluginBase) TClass(cbBarHintsPlugin)
    cbBarHintsPlugin_Create(void* pPanel, int paneMask);
TClass(cbBarHintsPlugin) cbBarHintsPlugin_CreateDefault();
void cbBarHintsPlugin_Delete(TSelf(cbBarHintsPlugin) pObject);
void cbBarHintsPlugin_SetGrooveCount(TSelf(cbBarHintsPlugin) pObject, int nGrooves);

/* cbBarInfo */
TClassDefExtend(cbBarInfo, wxObject) TClass(cbBarInfo) cbBarInfo_Create();
void cbBarInfo_Delete(TSelf(cbBarInfo) pObject);
TBool cbBarInfo_IsExpanded(TSelf(cbBarInfo) pObject);
TBool cbBarInfo_IsFixed(TSelf(cbBarInfo) pObject);

/* cbBarSpy */
TClassDefExtend(cbBarSpy, wxEvtHandler) TClass(cbBarSpy) cbBarSpy_Create(void* pPanel);
TClass(cbBarSpy) cbBarSpy_CreateDefault();
void cbBarSpy_Delete(TSelf(cbBarSpy) pObject);
int cbBarSpy_ProcessEvent(TSelf(cbBarSpy) pObject, TClass(wxEvent) event);
void cbBarSpy_SetBarWindow(TSelf(cbBarSpy) pObject, void* pWnd);

/* cbCloseBox */
TClassDefExtend(cbCloseBox, cbMiniButton) TClass(cbCloseBox) cbCloseBox_Create();

/* cbCollapseBox */
TClassDefExtend(cbCollapseBox, cbMiniButton) TClass(cbCollapseBox) cbCollapseBox_Create();

/* cbCommonPaneProperties */
TClassDefExtend(cbCommonPaneProperties,
                wxObject) void cbCommonPaneProperties_Assign(TSelf(cbCommonPaneProperties) pObject,
                                                             void* other);
int cbCommonPaneProperties_BarCollapseIconsOn(TSelf(cbCommonPaneProperties) pObject);
int cbCommonPaneProperties_BarDragHintsOn(TSelf(cbCommonPaneProperties) pObject);
int cbCommonPaneProperties_BarFloatingOn(TSelf(cbCommonPaneProperties) pObject);
int cbCommonPaneProperties_ColProportionsOn(TSelf(cbCommonPaneProperties) pObject);
TClass(cbCommonPaneProperties) cbCommonPaneProperties_CreateDefault();
void cbCommonPaneProperties_Delete(TSelf(cbCommonPaneProperties) pObject);
int cbCommonPaneProperties_ExactDockPredictionOn(TSelf(cbCommonPaneProperties) pObject);
void cbCommonPaneProperties_MinCBarDim(TSelf(cbCommonPaneProperties) pObject,
                                       TSizeOutVoid(width, height));
int cbCommonPaneProperties_NonDestructFrictionOn(TSelf(cbCommonPaneProperties) pObject);
int cbCommonPaneProperties_OutOfPaneDragOn(TSelf(cbCommonPaneProperties) pObject);
int cbCommonPaneProperties_RealTimeUpdatesOn(TSelf(cbCommonPaneProperties) pObject);
int cbCommonPaneProperties_ResizeHandleSize(TSelf(cbCommonPaneProperties) pObject);
int cbCommonPaneProperties_RowProportionsOn(TSelf(cbCommonPaneProperties) pObject);
void cbCommonPaneProperties_SetBarCollapseIconsOn(TSelf(cbCommonPaneProperties) pObject, int value);
void cbCommonPaneProperties_SetBarDragHintsOn(TSelf(cbCommonPaneProperties) pObject, int value);
void cbCommonPaneProperties_SetBarFloatingOn(TSelf(cbCommonPaneProperties) pObject, int value);
void cbCommonPaneProperties_SetColProportionsOn(TSelf(cbCommonPaneProperties) pObject, int value);
void cbCommonPaneProperties_SetExactDockPredictionOn(TSelf(cbCommonPaneProperties) pObject,
                                                     int value);
void cbCommonPaneProperties_SetMinCBarDim(TSelf(cbCommonPaneProperties) pObject,
                                          TSize(width, height));
void cbCommonPaneProperties_SetNonDestructFrictionOn(TSelf(cbCommonPaneProperties) pObject,
                                                     int value);
void cbCommonPaneProperties_SetOutOfPaneDragOn(TSelf(cbCommonPaneProperties) pObject, int value);
void cbCommonPaneProperties_SetRealTimeUpdatesOn(TSelf(cbCommonPaneProperties) pObject, int value);
void cbCommonPaneProperties_SetResizeHandleSize(TSelf(cbCommonPaneProperties) pObject, int value);
void cbCommonPaneProperties_SetRowProportionsOn(TSelf(cbCommonPaneProperties) pObject, int value);
void cbCommonPaneProperties_SetShow3DPaneBorderOn(TSelf(cbCommonPaneProperties) pObject, int value);
int cbCommonPaneProperties_Show3DPaneBorderOn(TSelf(cbCommonPaneProperties) pObject);

/* cbCustomizeBarEvent */
TClassDefExtend(cbCustomizeBarEvent,
                cbPluginEvent) void* cbCustomizeBarEvent_Bar(TSelf(cbCustomizeBarEvent) pObject);
void cbCustomizeBarEvent_ClickPos(TSelf(cbCustomizeBarEvent) pObject, TPointOutVoid(x, y));

/* cbCustomizeLayoutEvent */
TClassDefExtend(cbCustomizeLayoutEvent,
                cbPluginEvent) void cbCustomizeLayoutEvent_ClickPos(TSelf(cbCustomizeLayoutEvent)
                                                                        pObject,
                                                                    TPointOutVoid(x, y));

/* cbDimHandlerBase */
TClassDefExtend(cbDimHandlerBase, wxObject)

    /* cbDimInfo */
    TClassDefExtend(cbDimInfo, wxObject) void cbDimInfo_Assign(TSelf(cbDimInfo) pObject,
                                                               void* other);
TClass(cbDimInfo) cbDimInfo_Create(TPoint(x, y), TBool isFixed, int gap, void* pDimHandler);
TClass(cbDimInfo) cbDimInfo_CreateDefault();
void* cbDimInfo_CreateWithHandler(TSelf(cbDimInfo) pDimHandler, TBool isFixed);
void* cbDimInfo_CreateWithInfo(int dh_x, int dh_y, int dv_x, int dv_y, int f_x, int f_y,
                               TBool isFixed, int horizGap, int vertGap, void* pDimHandler);
void cbDimInfo_Delete(TSelf(cbDimInfo) pObject);
void* cbDimInfo_GetDimHandler(TSelf(cbDimInfo) pObject);

/* cbDockBox */
TClassDefExtend(cbDockBox, cbMiniButton) TClass(cbDockBox) cbDockBox_Create();

/* cbDockPane */
TClassDefExtend(cbDockPane, wxObject) int cbDockPane_BarPresent(TSelf(cbDockPane) pObject,
                                                                void* pBar);
TClass(cbDockPane) cbDockPane_Create(int alignment, void* pPanel);
TClass(cbDockPane) cbDockPane_CreateDefault();
void cbDockPane_Delete(TSelf(cbDockPane) pObject);
int cbDockPane_GetAlignment(TSelf(cbDockPane) pObject);
void* cbDockPane_GetBarInfoByWindow(TSelf(cbDockPane) pObject, void* pBarWnd);
void cbDockPane_GetBarResizeRange(TSelf(cbDockPane) pObject, void* pBar, void* from, void* till,
                                  int forLeftHandle);
int cbDockPane_GetDockingState(TSelf(cbDockPane) pObject);
void* cbDockPane_GetFirstRow(TSelf(cbDockPane) pObject);
int cbDockPane_GetPaneHeight(TSelf(cbDockPane) pObject);
void cbDockPane_GetRealRect(TSelf(cbDockPane) pObject, TRectOutVoid(x, y, width, height));
int cbDockPane_GetRowList(TSelf(cbDockPane) pObject, void* ref);
void cbDockPane_GetRowResizeRange(TSelf(cbDockPane) pObject, void* pRow, void* from, void* till,
                                  int forUpperHandle);
int cbDockPane_HitTestPaneItems(TSelf(cbDockPane) pObject, TPoint(x, y), void* ppRow, void* ppBar);
void cbDockPane_InsertBarByCoord(TSelf(cbDockPane) pObject, void* pBar, TRect(x, y, width, height));
void cbDockPane_InsertBarByInfo(TSelf(cbDockPane) pObject, void* pBarInfo);
void cbDockPane_InsertBarToRow(TSelf(cbDockPane) pObject, void* pBar, void* pIntoRow);
void cbDockPane_InsertRow(TSelf(cbDockPane) pObject, void* pRow, void* pBeforeRow);
TBool cbDockPane_IsHorizontal(TSelf(cbDockPane) pObject);
int cbDockPane_MatchesMask(TSelf(cbDockPane) pObject, int paneMask);
void cbDockPane_RemoveBar(TSelf(cbDockPane) pObject, void* pBar);
void cbDockPane_RemoveRow(TSelf(cbDockPane) pObject, void* pRow);
void cbDockPane_SetBoundsInParent(TSelf(cbDockPane) pObject, TRect(x, y, width, height));
void cbDockPane_SetMargins(TSelf(cbDockPane) pObject, int top, int bottom, int left, int right);
void cbDockPane_SetPaneWidth(TSelf(cbDockPane) pObject, int width);

/* cbDrawBarDecorEvent */
TClassDefExtend(cbDrawBarDecorEvent,
                cbPluginEvent) void* cbDrawBarDecorEvent_Bar(TSelf(cbDrawBarDecorEvent) pObject);
void cbDrawBarDecorEvent_BoundsInParent(TSelf(cbDrawBarDecorEvent) pObject,
                                        TRectOutVoid(x, y, width, height));
void* cbDrawBarDecorEvent_Dc(TSelf(cbDrawBarDecorEvent) pObject);

/* cbDrawBarHandlesEvent */
TClassDefExtend(cbDrawBarHandlesEvent,
                cbPluginEvent) void* cbDrawBarHandlesEvent_Bar(TSelf(cbDrawBarHandlesEvent)
                                                                   pObject);
void* cbDrawBarHandlesEvent_Dc(TSelf(cbDrawBarHandlesEvent) pObject);

/* cbDrawHintRectEvent */
TClassDefExtend(cbDrawHintRectEvent,
                cbPluginEvent) int cbDrawHintRectEvent_EraseRect(TSelf(cbDrawHintRectEvent)
                                                                     pObject);
TBool cbDrawHintRectEvent_IsInClient(TSelf(cbDrawHintRectEvent) pObject);
int cbDrawHintRectEvent_LastTime(TSelf(cbDrawHintRectEvent) pObject);
void cbDrawHintRectEvent_Rect(TSelf(cbDrawHintRectEvent) pObject,
                              TRectOutVoid(x, y, width, height));

/* cbDrawPaneBkGroundEvent */
TClassDefExtend(cbDrawPaneBkGroundEvent,
                cbPluginEvent) void* cbDrawPaneBkGroundEvent_Dc(TSelf(cbDrawPaneBkGroundEvent)
                                                                    pObject);

/* cbDrawPaneDecorEvent */
TClassDefExtend(cbDrawPaneDecorEvent,
                cbPluginEvent) void* cbDrawPaneDecorEvent_Dc(TSelf(cbDrawPaneDecorEvent) pObject);

/* cbDrawRowBkGroundEvent */
TClassDefExtend(cbDrawRowBkGroundEvent,
                cbPluginEvent) void* cbDrawRowBkGroundEvent_Dc(TSelf(cbDrawRowBkGroundEvent)
                                                                   pObject);
void* cbDrawRowBkGroundEvent_Row(TSelf(cbDrawRowBkGroundEvent) pObject);

/* cbDrawRowDecorEvent */
TClassDefExtend(cbDrawRowDecorEvent,
                cbPluginEvent) void* cbDrawRowDecorEvent_Dc(TSelf(cbDrawRowDecorEvent) pObject);
void* cbDrawRowDecorEvent_Row(TSelf(cbDrawRowDecorEvent) pObject);

/* cbDrawRowHandlesEvent */
TClassDefExtend(cbDrawRowHandlesEvent,
                cbPluginEvent) void* cbDrawRowHandlesEvent_Dc(TSelf(cbDrawRowHandlesEvent) pObject);
void* cbDrawRowHandlesEvent_Row(TSelf(cbDrawRowHandlesEvent) pObject);

/* cbDynToolBarDimHandler */
TClassDefExtend(cbDynToolBarDimHandler, cbDimHandlerBase) TClass(cbDynToolBarDimHandler)
    cbDynToolBarDimHandler_Create();
void cbDynToolBarDimHandler_Delete(TSelf(cbDynToolBarDimHandler) pObject);

/* cbFinishDrawInAreaEvent */
TClassDefExtend(cbFinishDrawInAreaEvent,
                cbPluginEvent) void cbFinishDrawInAreaEvent_Area(TSelf(cbFinishDrawInAreaEvent)
                                                                     pObject,
                                                                 TRectOutVoid(x, y, width, height));

/* cbFloatedBarWindow */
TClassDefExtend(cbFloatedBarWindow, wxToolWindow) TClass(cbFloatedBarWindow)
    cbFloatedBarWindow_Create(void* pObject);
void* cbFloatedBarWindow_GetBar(TSelf(cbFloatedBarWindow) pObject);
void cbFloatedBarWindow_PositionFloatedWnd(TSelf(cbFloatedBarWindow) pObject,
                                           TRect(x, y, width, height));
void cbFloatedBarWindow_SetBar(TSelf(cbFloatedBarWindow) pObject, void* bar);
void cbFloatedBarWindow_SetLayout(TSelf(cbFloatedBarWindow) pObject, void* layout);

/* cbGCUpdatesMgr */
TClassDefExtend(cbGCUpdatesMgr, cbSimpleUpdatesMgr) TClass(cbGCUpdatesMgr)
    cbGCUpdatesMgr_Create(void* pPanel);
TClass(cbGCUpdatesMgr) cbGCUpdatesMgr_CreateDefault();
void cbGCUpdatesMgr_Delete(TSelf(cbGCUpdatesMgr) pObject);
void cbGCUpdatesMgr_UpdateNow(TSelf(cbGCUpdatesMgr) pObject);

/* cbHintAnimationPlugin */
TClassDefExtend(cbHintAnimationPlugin, cbPluginBase) TClass(cbHintAnimationPlugin)
    cbHintAnimationPlugin_Create(void* pPanel, int paneMask);
TClass(cbHintAnimationPlugin) cbHintAnimationPlugin_CreateDefault();
void cbHintAnimationPlugin_Delete(TSelf(cbHintAnimationPlugin) pObject);

/* cbInsertBarEvent */
TClassDefExtend(cbInsertBarEvent,
                cbPluginEvent) void* cbInsertBarEvent_Bar(TSelf(cbInsertBarEvent) pObject);
void* cbInsertBarEvent_Row(TSelf(cbInsertBarEvent) pObject);

/* cbLayoutRowEvent */
TClassDefExtend(cbLayoutRowEvent,
                cbPluginEvent) void* cbLayoutRowEvent_Row(TSelf(cbLayoutRowEvent) pObject);

/* cbLeftDClickEvent */
TClassDefExtend(cbLeftDClickEvent,
                cbPluginEvent) void cbLeftDClickEvent_Pos(TSelf(cbLeftDClickEvent) pObject,
                                                          TPointOutVoid(x, y));

/* cbLeftDownEvent */
TClassDefExtend(cbLeftDownEvent, cbPluginEvent) void cbLeftDownEvent_Pos(TSelf(cbLeftDownEvent)
                                                                             pObject,
                                                                         TPointOutVoid(x, y));

/* cbLeftUpEvent */
TClassDefExtend(cbLeftUpEvent, cbPluginEvent) void cbLeftUpEvent_Pos(TSelf(cbLeftUpEvent) pObject,
                                                                     TPointOutVoid(x, y));

/* cbMiniButton */
TClassDefExtend(cbMiniButton, wxObject) TClass(cbMiniButton) cbMiniButton_Create();
void cbMiniButton_Delete(TSelf(cbMiniButton) pObject);
void cbMiniButton_Dim(TSelf(cbMiniButton) pObject, TSizeOutVoid(width, height));
int cbMiniButton_DragStarted(TSelf(cbMiniButton) pObject);
void cbMiniButton_Enable(TSelf(cbMiniButton) pObject, TBool enable);
int cbMiniButton_Enabled(TSelf(cbMiniButton) pObject);
int cbMiniButton_HitTest(TSelf(cbMiniButton) pObject, TPoint(x, y));
TBool cbMiniButton_IsPressed(TSelf(cbMiniButton) pObject);
void* cbMiniButton_Layout(TSelf(cbMiniButton) pObject);
void* cbMiniButton_Pane(TSelf(cbMiniButton) pObject);
void* cbMiniButton_Plugin(TSelf(cbMiniButton) pObject);
void cbMiniButton_Pos(TSelf(cbMiniButton) pObject, TPointOutVoid(x, y));
int cbMiniButton_Pressed(TSelf(cbMiniButton) pObject);
void cbMiniButton_Refresh(TSelf(cbMiniButton) pObject);
void cbMiniButton_Reset(TSelf(cbMiniButton) pObject);
void cbMiniButton_SetPos(TSelf(cbMiniButton) pObject, TPoint(x, y));
int cbMiniButton_Visible(TSelf(cbMiniButton) pObject);
int cbMiniButton_WasClicked(TSelf(cbMiniButton) pObject);
void* cbMiniButton_Wnd(TSelf(cbMiniButton) pObject);

/* cbMotionEvent */
TClassDefExtend(cbMotionEvent, cbPluginEvent) void cbMotionEvent_Pos(TSelf(cbMotionEvent) pObject,
                                                                     TPointOutVoid(x, y));

/* cbPaneDrawPlugin */
TClassDefExtend(cbPaneDrawPlugin, cbPluginBase) TClass(cbPaneDrawPlugin)
    cbPaneDrawPlugin_Create(void* pPanel, int paneMask);
TClass(cbPaneDrawPlugin) cbPaneDrawPlugin_CreateDefault();
void cbPaneDrawPlugin_Delete(TSelf(cbPaneDrawPlugin) pObject);

/* cbPluginBase */
TClassDefExtend(cbPluginBase, wxEvtHandler) void cbPluginBase_Delete(TSelf(cbPluginBase) pObject);
int cbPluginBase_GetPaneMask(TSelf(cbPluginBase) pObject);
TBool cbPluginBase_IsReady(TSelf(cbPluginBase) pObject);
void* cbPluginBase_Plugin(int switchVal);
int cbPluginBase_ProcessEvent(TSelf(cbPluginBase) pObject, TClass(wxEvent) event);

/* cbPluginEvent */
TClassDefExtend(cbPluginEvent, wxEvent) void* cbPluginEvent_Pane(TSelf(cbPluginEvent) pObject);

/* cbRemoveBarEvent */
TClassDefExtend(cbRemoveBarEvent,
                cbPluginEvent) void* cbRemoveBarEvent_Bar(TSelf(cbRemoveBarEvent) pObject);

/* cbResizeBarEvent */
TClassDefExtend(cbResizeBarEvent,
                cbPluginEvent) void* cbResizeBarEvent_Bar(TSelf(cbResizeBarEvent) pObject);
void* cbResizeBarEvent_Row(TSelf(cbResizeBarEvent) pObject);

/* cbResizeRowEvent */
TClassDefExtend(cbResizeRowEvent,
                cbPluginEvent) int cbResizeRowEvent_ForUpperHandle(TSelf(cbResizeRowEvent) pObject);
int cbResizeRowEvent_HandleOfs(TSelf(cbResizeRowEvent) pObject);
void* cbResizeRowEvent_Row(TSelf(cbResizeRowEvent) pObject);

/* cbRightDownEvent */
TClassDefExtend(cbRightDownEvent, cbPluginEvent) void cbRightDownEvent_Pos(TSelf(cbRightDownEvent)
                                                                               pObject,
                                                                           TPointOutVoid(x, y));

/* cbRightUpEvent */
TClassDefExtend(cbRightUpEvent, cbPluginEvent) void cbRightUpEvent_Pos(TSelf(cbRightUpEvent)
                                                                           pObject,
                                                                       TPointOutVoid(x, y));

/* cbRowDragPlugin */
TClassDefExtend(cbRowDragPlugin, cbPluginBase) TClass(cbRowDragPlugin)
    cbRowDragPlugin_Create(void* pPanel, int paneMask);
TClass(cbRowDragPlugin) cbRowDragPlugin_CreateDefault();
void cbRowDragPlugin_Delete(TSelf(cbRowDragPlugin) pObject);

/* cbRowInfo */
TClassDefExtend(cbRowInfo, wxObject) TClass(cbRowInfo) cbRowInfo_Create();
void cbRowInfo_Delete(TSelf(cbRowInfo) pObject);
void* cbRowInfo_GetFirstBar(TSelf(cbRowInfo) pObject);

/* cbRowLayoutPlugin */
TClassDefExtend(cbRowLayoutPlugin, cbPluginBase) TClass(cbRowLayoutPlugin)
    cbRowLayoutPlugin_Create(void* pPanel, int paneMask);
TClass(cbRowLayoutPlugin) cbRowLayoutPlugin_CreateDefault();
void cbRowLayoutPlugin_Delete(TSelf(cbRowLayoutPlugin) pObject);

/* cbSimpleCustomizationPlugin */
TClassDefExtend(cbSimpleCustomizationPlugin, cbPluginBase) TClass(cbSimpleCustomizationPlugin)
    cbSimpleCustomizationPlugin_Create(void* pPanel, int paneMask);
TClass(cbSimpleCustomizationPlugin) cbSimpleCustomizationPlugin_CreateDefault();
void cbSimpleCustomizationPlugin_Delete(TSelf(cbSimpleCustomizationPlugin) pObject);

/* cbSimpleUpdatesMgr */
TClassDefExtend(cbSimpleUpdatesMgr, cbUpdatesManagerBase)

    /* cbSizeBarWndEvent */
    TClassDefExtend(cbSizeBarWndEvent,
                    cbPluginEvent) void* cbSizeBarWndEvent_Bar(TSelf(cbSizeBarWndEvent) pObject);
void cbSizeBarWndEvent_BoundsInParent(TSelf(cbSizeBarWndEvent) pObject,
                                      TRectOutVoid(x, y, width, height));

/* cbStartBarDraggingEvent */
TClassDefExtend(cbStartBarDraggingEvent,
                cbPluginEvent) void* cbStartBarDraggingEvent_Bar(TSelf(cbStartBarDraggingEvent)
                                                                     pObject);
void cbStartBarDraggingEvent_Pos(TSelf(cbStartBarDraggingEvent) pObject, TPointOutVoid(x, y));

/* cbStartDrawInAreaEvent */
TClassDefExtend(cbStartDrawInAreaEvent,
                cbPluginEvent) void cbStartDrawInAreaEvent_Area(TSelf(cbStartDrawInAreaEvent)
                                                                    pObject,
                                                                TRectOutVoid(x, y, width, height));

/* cbUpdatesManagerBase */
TClassDefExtend(cbUpdatesManagerBase, wxObject)

    /* wxAcceleratorEntry */
    TClassDef(wxAcceleratorEntry) TClass(wxAcceleratorEntry)
        wxAcceleratorEntry_Create(int flags, int keyCode, int cmd);
void wxAcceleratorEntry_Delete(TSelf(wxAcceleratorEntry) pObject);
int wxAcceleratorEntry_GetCommand(TSelf(wxAcceleratorEntry) pObject);
int wxAcceleratorEntry_GetFlags(TSelf(wxAcceleratorEntry) pObject);
int wxAcceleratorEntry_GetKeyCode(TSelf(wxAcceleratorEntry) pObject);
void wxAcceleratorEntry_Set(TSelf(wxAcceleratorEntry) pObject, int flags, int keyCode, int cmd,
                            void* item);

/* wxAcceleratorTable */
TClassDef(wxAcceleratorTable) TClass(wxAcceleratorTable)
    wxAcceleratorTable_Create(int count, void* entries);
void wxAcceleratorTable_Delete(TSelf(wxAcceleratorTable) pObject);

/* wxActivityIndicator */
TClassDef(wxActivityIndicator) TClass(wxActivityIndicator)
    wxActivityIndicator_Create(TClass(wxWindow) parent, int id, int x, int y, int width, int height,
                               int style);
TBool wxActivityIndicator_IsRunning(TSelf(wxActivityIndicator) self);
void wxActivityIndicator_Start(TSelf(wxActivityIndicator) self);
void wxActivityIndicator_Stop(TSelf(wxActivityIndicator) self);

/* wxAnimation */
TClassDef(wxAnimation) TClass(wxAnimation) wxAnimation_Create();
TClass(wxAnimation) wxAnimation_CreateFromFile(TClass(wxString) filename, int type);
void wxAnimation_Delete(TSelf(wxAnimation) self);
int wxAnimation_GetDelay(TSelf(wxAnimation) self, int frame);
int wxAnimation_GetFrameCount(TSelf(wxAnimation) self);
void wxAnimation_GetFrame(TSelf(wxAnimation) self, int frame, TClass(wxImage) image);
void wxAnimation_GetSize(TSelf(wxAnimation) self, int* width, int* height);
TBool wxAnimation_IsOk(TSelf(wxAnimation) self);
TBool wxAnimation_LoadFile(TSelf(wxAnimation) self, TClass(wxString) filename, int type);
TBool wxAnimation_Load(TSelf(wxAnimation) self, TClass(wxInputStream) stream, int type);

/* wxAnimationCtrl */
TClassDef(wxAnimationCtrl) TClass(wxAnimationCtrl)
    wxAnimationCtrl_Create(TClass(wxWindow) parent, int id, int x, int y, int width, int height,
                           int style);
TClass(wxAnimationCtrl)
    wxAnimationCtrl_CreateWithAnimation(TClass(wxWindow) parent, int id, TClass(wxAnimation) anim,
                                        int x, int y, int width, int height, int style);
void wxAnimationCtrl_GetAnimation(TSelf(wxAnimationCtrl) self, TClass(wxAnimation) anim);
void wxAnimationCtrl_GetInactiveBitmap(TSelf(wxAnimationCtrl) self, TClass(wxBitmap) bmp);
TBool wxAnimationCtrl_IsPlaying(TSelf(wxAnimationCtrl) self);
TBool wxAnimationCtrl_LoadFile(TSelf(wxAnimationCtrl) self, TClass(wxString) filename, int type);
TBool wxAnimationCtrl_Load(TSelf(wxAnimationCtrl) self, TClass(wxInputStream) stream, int type);
TBool wxAnimationCtrl_Play(TSelf(wxAnimationCtrl) self);
void wxAnimationCtrl_SetAnimation(TSelf(wxAnimationCtrl) self, TClass(wxAnimation) anim);
void wxAnimationCtrl_SetInactiveBitmap(TSelf(wxAnimationCtrl) self, TClass(wxBitmap) bmp);
void wxAnimationCtrl_Stop(TSelf(wxAnimationCtrl) self);

/* wxActivateEvent */
TClassDefExtend(wxActivateEvent,
                wxEvent) void wxActivateEvent_CopyObject(TSelf(wxActivateEvent) pObject, void* obj);
TBool wxActivateEvent_GetActive(TSelf(wxActivateEvent) pObject);

/* wxApp */
TClassDefExtend(wxApp, wxEvtHandler)

    /* wxArray */
    TClassDef(wxArray)

    /* wxArrayString */
    TClassDefExtend(wxArrayString, wxArray)

    /* wxArtProvider */
    TClassDefExtend(wxArtProvider, wxObject) TBool PopProvider();
void PushProvider(TClass(wxArtProvider) provider);
TBool RemoveProvider(TClass(wxArtProvider) provider);

/* wxAuiDefaultTabArt */
TClassDefExtend(wxAuiDefaultTabArt, wxAuiTabArt) TClass(wxAuiDefaultTabArt)
    wxAuiDefaultTabArt_Create();
TClass(wxAuiTabArt) wxAuiDefaultTabArt_Clone(TSelf(wxAuiDefaultTabArt) pObject);
void wxAuiDefaultTabArt_SetFlags(TSelf(wxAuiDefaultTabArt) pObject, int flags);
void wxAuiDefaultTabArt_SetSizingInfo(TSelf(wxAuiDefaultTabArt) pObject, TSize(width, height),
                                      size_t tabCount);
void wxAuiDefaultTabArt_SetNormalFont(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxFont) font);
void wxAuiDefaultTabArt_SetSelectedFont(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxFont) font);
void wxAuiDefaultTabArt_SetMeasuringFont(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxFont) font);
void wxAuiDefaultTabArt_SetColour(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxColour) colour);
void wxAuiDefaultTabArt_SetActiveColour(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxColour) colour);
void wxAuiDefaultTabArt_DrawBackground(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxDC) dc,
                                       TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiDefaultTabArt_DrawTab(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxDC) dc,
                                TClass(wxWindow) window, TClass(wxAuiNotebookPage) pane,
                                TClass(wxRect) inRect, int closeButtonState,
                                TClass(wxRect) outTabRect, TClass(wxRect) outButtonRect,
                                int* xExtent);
void wxAuiDefaultTabArt_DrawButton(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxDC) dc,
                                   TClass(wxWindow) window, TClass(wxRect) inRect, int bitmapId,
                                   int buttonState, int orientation, TClass(wxRect) outRect);
int wxAuiDefaultTabArt_GetIndentSize(TSelf(wxAuiDefaultTabArt) pObject);
TClass(wxSize) wxAuiDefaultTabArt_GetTabSize(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxDC) dc,
                                             TClass(wxWindow) window, TClass(wxString) caption,
                                             TClass(wxBitmap) bitmap, TBool active,
                                             int closeButtonState, int* xExtent);
int wxAuiDefaultTabArt_ShowDropDown(TSelf(wxAuiDefaultTabArt) pObject, TClass(wxWindow) window,
                                    TClass(wxAuiNotebookPageArray) items, int activeIdx);
int wxAuiDefaultTabArt_GetBestTabCtrlSize(TSelf(wxAuiDefaultTabArt) pObject,
                                          TClass(wxWindow) window,
                                          TClass(wxAuiNotebookPageArray) pages,
                                          TSize(width, height));

/* wxAuiToolBarEvent */
TClassDefExtend(wxAuiToolBarEvent, wxNotifyEvent) TBool
    wxAuiToolBarEvent_IsDropDownClicked(TSelf(wxAuiToolBarEvent) pObject);
TClass(wxPoint) wxAuiToolBarEvent_GetClickPoint(TSelf(wxAuiToolBarEvent) pObject);
TClass(wxRect) wxAuiToolBarEvent_GetItemRect(TSelf(wxAuiToolBarEvent) pObject);
int wxAuiToolBarEvent_GetToolId(TSelf(wxAuiToolBarEvent) pObject);

/* wxAuiToolBarItem */
TClassDef(wxAuiToolBarItem) TClass(wxAuiToolBarItem) wxAuiToolBarItem_CreateDefault();
TClass(wxAuiToolBarItem) wxAuiToolBarItem_Create(TClass(wxAuiToolBarItem) source);
TClass(wxAuiToolBarItem)
    wxAuiToolBarItem_Copy(TSelf(wxAuiToolBarItem) pObject, TClass(wxAuiToolBarItem) source);
void wxAuiToolBarItem_Assign(TSelf(wxAuiToolBarItem) pObject, TClass(wxAuiToolBarItem) source);
void wxAuiToolBarItem_SetWindow(TSelf(wxAuiToolBarItem) pObject, TClass(wxWindow) window);
TClass(wxWindow) wxAuiToolBarItem_GetWindow(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetId(TSelf(wxAuiToolBarItem) pObject, int new_id);
int wxAuiToolBarItem_GetId(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetKind(TSelf(wxAuiToolBarItem) pObject, int new_kind);
int wxAuiToolBarItem_GetKind(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetState(TSelf(wxAuiToolBarItem) pObject, int new_state);
int wxAuiToolBarItem_GetState(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetSizerItem(TSelf(wxAuiToolBarItem) pObject, TClass(wxSizerItem) sizerItem);
TClass(wxSizerItem) wxAuiToolBarItem_GetSizerItem(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetLabel(TSelf(wxAuiToolBarItem) pObject, TClass(wxString) label);
TClass(wxString) wxAuiToolBarItem_GetLabel(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetBitmap(TSelf(wxAuiToolBarItem) pObject, TClass(wxBitmap) bitmap);
void wxAuiToolBarItem_GetBitmap(TSelf(wxAuiToolBarItem) pObject, TClassRef(wxBitmap) ref);
void wxAuiToolBarItem_SetDisabledBitmap(TSelf(wxAuiToolBarItem) pObject, TClass(wxBitmap) bitmap);
void wxAuiToolBarItem_GetDisabledBitmap(TSelf(wxAuiToolBarItem) pObject, TClassRef(wxBitmap) ref);
void wxAuiToolBarItem_SetHoverBitmap(TSelf(wxAuiToolBarItem) pObject, TClass(wxBitmap) bitmap);
void wxAuiToolBarItem_GetHoverBitmap(TSelf(wxAuiToolBarItem) pObject, TClassRef(wxBitmap) ref);
void wxAuiToolBarItem_SetShortHelp(TSelf(wxAuiToolBarItem) pObject, TClass(wxString) helpString);
TClass(wxString) wxAuiToolBarItem_GetShortHelp(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetLongHelp(TSelf(wxAuiToolBarItem) pObject, TClass(wxString) helpString);
TClass(wxString) wxAuiToolBarItem_GetLongHelp(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetMinSize(TSelf(wxAuiToolBarItem) pObject, TSize(width, height));
TClass(wxSize) wxAuiToolBarItem_GetMinSize(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetSpacerPixels(TSelf(wxAuiToolBarItem) pObject, int spacerPixels);
int wxAuiToolBarItem_GetSpacerPixels(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetProportion(TSelf(wxAuiToolBarItem) pObject, int proportion);
int wxAuiToolBarItem_GetProportion(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetActive(TSelf(wxAuiToolBarItem) pObject, TBool enable);
TBool wxAuiToolBarItem_IsActive(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetHasDropDown(TSelf(wxAuiToolBarItem) pObject, TBool enable);
TBool wxAuiToolBarItem_HasDropDown(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetSticky(TSelf(wxAuiToolBarItem) pObject, TBool enable);
TBool wxAuiToolBarItem_IsSticky(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetUserData(TSelf(wxAuiToolBarItem) pObject, long userData);
long wxAuiToolBarItem_GetUserData(TSelf(wxAuiToolBarItem) pObject);
void wxAuiToolBarItem_SetAlignment(TSelf(wxAuiToolBarItem) pObject, int alignment);
int wxAuiToolBarItem_GetAlignment(TSelf(wxAuiToolBarItem) pObject);

/* wxAuiToolBarArt */
TClassDef(wxAuiToolBarArt) TClass(wxAuiToolBarArt)
    wxAuiToolBarArt_Clone(TSelf(wxAuiToolBarArt) pObject);
void wxAuiToolBarArt_SetFlags(TSelf(wxAuiToolBarArt) pObject, int flags);
int wxAuiToolBarArt_GetFlags(TSelf(wxAuiToolBarArt) pObject);
void wxAuiToolBarArt_SetFont(TSelf(wxAuiToolBarArt) pObject, TClass(wxFont) font);
TClass(wxFont) wxAuiToolBarArt_GetFont(TSelf(wxAuiToolBarArt) pObject);
void wxAuiToolBarArt_SetTextOrientation(TSelf(wxAuiToolBarArt) pObject, int orientation);
int wxAuiToolBarArt_GetTextOrientation(TSelf(wxAuiToolBarArt) pObject);
void wxAuiToolBarArt_DrawBackground(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                    TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiToolBarArt_DrawPlainBackground(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                         TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiToolBarArt_DrawLabel(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                               TClass(wxWindow) window, TClass(wxAuiToolBarItem) item,
                               TClass(wxRect) rect);
void wxAuiToolBarArt_DrawButton(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                TClass(wxWindow) window, TClass(wxAuiToolBarItem) item,
                                TClass(wxRect) rect);
void wxAuiToolBarArt_DrawDropDownButton(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                        TClass(wxWindow) window, TClass(wxAuiToolBarItem) item,
                                        TClass(wxRect) rect);
void wxAuiToolBarArt_DrawControlLabel(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                      TClass(wxWindow) window, TClass(wxAuiToolBarItem) item,
                                      TClass(wxRect) rect);
void wxAuiToolBarArt_DrawSeparator(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                   TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiToolBarArt_DrawGripper(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                 TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiToolBarArt_DrawOverflowButton(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                        TClass(wxWindow) window, TClass(wxRect) rect, int state);
TClass(wxSize) wxAuiToolBarArt_GetLabelSize(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                            TClass(wxWindow) window, TClass(wxAuiToolBarItem) item);
TClass(wxSize) wxAuiToolBarArt_GetToolSize(TSelf(wxAuiToolBarArt) pObject, TClass(wxDC) dc,
                                           TClass(wxWindow) window, TClass(wxAuiToolBarItem) item);
int wxAuiToolBarArt_GetElementSize(TSelf(wxAuiToolBarArt) pObject, int element_id);
void wxAuiToolBarArt_SetElementSize(TSelf(wxAuiToolBarArt) pObject, int element_id, int size);
int wxAuiToolBarArt_ShowDropDown(TSelf(wxAuiToolBarArt) pObject, TClass(wxWindow) window,
                                 TClass(wxAuiToolBarItemArray) items);

/* wxAuiDefaultToolBarArt */
TClassDefExtend(wxAuiDefaultToolBarArt, wxAuiToolBarArt) TClass(wxAuiDefaultToolBarArt)
    wxAuiDefaultToolBarArt_Create();
TClass(wxAuiToolBarArt) wxAuiDefaultToolBarArt_Clone(TSelf(wxAuiDefaultToolBarArt) pObject);
void wxAuiDefaultToolBarArt_SetFlags(TSelf(wxAuiDefaultToolBarArt) pObject, int flags);
int wxAuiDefaultToolBarArt_GetFlags(TSelf(wxAuiDefaultToolBarArt) pObject);
void wxAuiDefaultToolBarArt_SetFont(TSelf(wxAuiDefaultToolBarArt) pObject, TClass(wxFont) font);
TClass(wxFont) wxAuiDefaultToolBarArt_GetFont(TSelf(wxAuiDefaultToolBarArt) pObject);
void wxAuiDefaultToolBarArt_SetTextOrientation(TSelf(wxAuiDefaultToolBarArt) pObject,
                                               int orientation);
int wxAuiDefaultToolBarArt_GetTextOrientation(TSelf(wxAuiDefaultToolBarArt) pObject);
void wxAuiDefaultToolBarArt_DrawBackground(TSelf(wxAuiDefaultToolBarArt) pObject, TClass(wxDC) dc,
                                           TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiDefaultToolBarArt_DrawPlainBackground(TSelf(wxAuiDefaultToolBarArt) pObject,
                                                TClass(wxDC) dc, TClass(wxWindow) window,
                                                TClass(wxRect) rect);
void wxAuiDefaultToolBarArt_DrawLabel(TSelf(wxAuiDefaultToolBarArt) pObject, TClass(wxDC) dc,
                                      TClass(wxWindow) window, TClass(wxAuiToolBarItem) item,
                                      TClass(wxRect) rect);
void wxAuiDefaultToolBarArt_DrawButton(TSelf(wxAuiDefaultToolBarArt) pObject, TClass(wxDC) dc,
                                       TClass(wxWindow) window, TClass(wxAuiToolBarItem) item,
                                       TClass(wxRect) rect);
void wxAuiDefaultToolBarArt_DrawDropDownButton(TSelf(wxAuiDefaultToolBarArt) pObject,
                                               TClass(wxDC) dc, TClass(wxWindow) window,
                                               TClass(wxAuiToolBarItem) item, TClass(wxRect) rect);
void wxAuiDefaultToolBarArt_DrawControlLabel(TSelf(wxAuiDefaultToolBarArt) pObject, TClass(wxDC) dc,
                                             TClass(wxWindow) window, TClass(wxAuiToolBarItem) item,
                                             TClass(wxRect) rect);
void wxAuiDefaultToolBarArt_DrawSeparator(TSelf(wxAuiDefaultToolBarArt) pObject, TClass(wxDC) dc,
                                          TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiDefaultToolBarArt_DrawGripper(TSelf(wxAuiDefaultToolBarArt) pObject, TClass(wxDC) dc,
                                        TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiDefaultToolBarArt_DrawOverflowButton(TSelf(wxAuiDefaultToolBarArt) pObject,
                                               TClass(wxDC) dc, TClass(wxWindow) window,
                                               TClass(wxRect) rect, int state);
TClass(wxSize)
    wxAuiDefaultToolBarArt_GetLabelSize(TSelf(wxAuiDefaultToolBarArt) pObject, TClass(wxDC) dc,
                                        TClass(wxWindow) window, TClass(wxAuiToolBarItem) item);
TClass(wxSize)
    wxAuiDefaultToolBarArt_GetToolSize(TSelf(wxAuiDefaultToolBarArt) pObject, TClass(wxDC) dc,
                                       TClass(wxWindow) window, TClass(wxAuiToolBarItem) item);
int wxAuiDefaultToolBarArt_GetElementSize(TSelf(wxAuiDefaultToolBarArt) pObject, int element);
void wxAuiDefaultToolBarArt_SetElementSize(TSelf(wxAuiDefaultToolBarArt) pObject, int element_id,
                                           int size);
int wxAuiDefaultToolBarArt_ShowDropDown(TSelf(wxAuiDefaultToolBarArt) pObject,
                                        TClass(wxWindow) window,
                                        TClass(wxAuiToolBarItemArray) items);

/* wxAuiToolBar */
TClassDefExtend(wxAuiToolBar, wxControl) TClass(wxAuiToolBar) wxAuiToolBar_CreateDefault();
TClass(wxAuiToolBar) wxAuiToolBar_Create(TClass(wxWindow) parent, int id, TPoint(x, y),
                                         TSize(width, height), long style);
TBool wxAuiToolBar_CreateFromDefault(TSelf(wxAuiToolBar) pObject, TClass(wxWindow) parent, int id,
                                     TPoint(x, y), TSize(width, height), long style);
void wxAuiToolBar_Delete(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_SetWindowStyleFlag(TSelf(wxAuiToolBar) pObject, long style);
long wxAuiToolBar_GetWindowStyleFlag(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_SetArtProvider(TSelf(wxAuiToolBar) pObject, TClass(wxAuiToolBarArt) artId);
TClass(wxAuiToolBarArt) wxAuiToolBar_GetArtProvider(TSelf(wxAuiToolBar) pObject);
TBool wxAuiToolBar_SetFont(TSelf(wxAuiToolBar) pObject, TClass(wxFont) font);
TClass(wxAuiToolBarItem)
    wxAuiToolBar_AddToolByLabel(TSelf(wxAuiToolBar) pObject, int tool_id, TClass(wxString) label,
                                TClass(wxBitmap) bitmap, TClass(wxString) shortHelpString,
                                int kind);
TClass(wxAuiToolBarItem)
    wxAuiToolBar_AddTool(TSelf(wxAuiToolBar) pObject, int tool_id, TClass(wxString) label,
                         TClass(wxBitmap) bitmap, TClass(wxBitmap) disabledBitmap, int kind,
                         TClass(wxString) shortHelpString, TClass(wxString) longHelpString,
                         TClass(wxObject) clientData);
TClass(wxAuiToolBarItem)
    wxAuiToolBar_AddToolByBitmap(TSelf(wxAuiToolBar) pObject, int tool_id, TClass(wxBitmap) bitmap,
                                 TClass(wxBitmap) disabledBitmap, TBool toggle,
                                 TClass(wxObject) clientData, TClass(wxString) shortHelpString,
                                 TClass(wxString) longHelpString);
TClass(wxAuiToolBarItem) wxAuiToolBar_AddLabel(TSelf(wxAuiToolBar) pObject, int tool_id,
                                               TClass(wxString) label, int width);
TClass(wxAuiToolBarItem) wxAuiToolBar_AddControl(TSelf(wxAuiToolBar) pObject,
                                                 TClass(wxControl) control, TClass(wxString) label);
TClass(wxAuiToolBarItem) wxAuiToolBar_AddSeparator(TSelf(wxAuiToolBar) pObject);
TClass(wxAuiToolBarItem) wxAuiToolBar_AddSpacer(TSelf(wxAuiToolBar) pObject, int pixels);
TClass(wxAuiToolBarItem) wxAuiToolBar_AddStretchSpacer(TSelf(wxAuiToolBar) pObject, int proportion);
TBool wxAuiToolBar_Realize(TSelf(wxAuiToolBar) pObject);
TClass(wxControl) wxAuiToolBar_FindControl(TSelf(wxAuiToolBar) pObject, int window_id);
TClass(wxAuiToolBarItem) wxAuiToolBar_FindToolByPosition(TSelf(wxAuiToolBar) pObject, int x, int y);
TClass(wxAuiToolBarItem) wxAuiToolBar_FindToolByIndex(TSelf(wxAuiToolBar) pObject, int idx);
TClass(wxAuiToolBarItem) wxAuiToolBar_FindTool(TSelf(wxAuiToolBar) pObject, int tool_id);
void wxAuiToolBar_ClearTools(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_Clear(TSelf(wxAuiToolBar) pObject);
TBool wxAuiToolBar_DeleteTool(TSelf(wxAuiToolBar) pObject, int tool_id);
TBool wxAuiToolBar_DeleteByIndex(TSelf(wxAuiToolBar) pObject, int tool_id);
size_t wxAuiToolBar_GetToolCount(TSelf(wxAuiToolBar) pObject);
int wxAuiToolBar_GetToolPos(TSelf(wxAuiToolBar) pObject, int tool_id);
int wxAuiToolBar_GetToolIndex(TSelf(wxAuiToolBar) pObject, int tool_id);
TBool wxAuiToolBar_GetToolFits(TSelf(wxAuiToolBar) pObject, int tool_id);
TClass(wxRect) wxAuiToolBar_GetToolRect(TSelf(wxAuiToolBar) pObject, int tool_id);
TBool wxAuiToolBar_GetToolFitsByIndex(TSelf(wxAuiToolBar) pObject, int tool_id);
TBool wxAuiToolBar_GetToolBarFits(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_SetMargins(TSelf(wxAuiToolBar) pObject, TSize(width, height));
void wxAuiToolBar_SetMarginsXY(TSelf(wxAuiToolBar) pObject, int x, int y);
void wxAuiToolBar_SetMarginsDetailed(TSelf(wxAuiToolBar) pObject, int left, int right, int top,
                                     int bottom);
void wxAuiToolBar_SetToolBitmapSize(TSelf(wxAuiToolBar) pObject, TSize(width, height));
TClass(wxSize) wxAuiToolBar_GetToolBitmapSize(TSelf(wxAuiToolBar) pObject);
TBool wxAuiToolBar_GetOverflowVisible(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_SetOverflowVisible(TSelf(wxAuiToolBar) pObject, TBool visible);
TBool wxAuiToolBar_GetGripperVisible(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_SetGripperVisible(TSelf(wxAuiToolBar) pObject, TBool visible);
void wxAuiToolBar_ToggleTool(TSelf(wxAuiToolBar) pObject, int tool_id, TBool state);
TBool wxAuiToolBar_GetToolToggled(TSelf(wxAuiToolBar) pObject, int tool_id);
void wxAuiToolBar_EnableTool(TSelf(wxAuiToolBar) pObject, int tool_id, TBool state);
TBool wxAuiToolBar_GetToolEnabled(TSelf(wxAuiToolBar) pObject, int tool_id);
void wxAuiToolBar_SetToolDropDown(TSelf(wxAuiToolBar) pObject, int tool_id, TBool dropdown);
TBool wxAuiToolBar_GetToolDropDown(TSelf(wxAuiToolBar) pObject, int tool_id);
void wxAuiToolBar_SetToolBorderPadding(TSelf(wxAuiToolBar) pObject, int padding);
int wxAuiToolBar_GetToolBorderPadding(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_SetToolTextOrientation(TSelf(wxAuiToolBar) pObject, int orientation);
int wxAuiToolBar_GetToolTextOrientation(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_SetToolPacking(TSelf(wxAuiToolBar) pObject, int packing);
int wxAuiToolBar_GetToolPacking(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_SetToolProportion(TSelf(wxAuiToolBar) pObject, int tool_id, int proportion);
int wxAuiToolBar_GetToolProportion(TSelf(wxAuiToolBar) pObject, int tool_id);
void wxAuiToolBar_SetToolSeparation(TSelf(wxAuiToolBar) pObject, int separation);
int wxAuiToolBar_GetToolSeparation(TSelf(wxAuiToolBar) pObject);
void wxAuiToolBar_SetToolSticky(TSelf(wxAuiToolBar) pObject, int tool_id, TBool sticky);
TBool wxAuiToolBar_GetToolSticky(TSelf(wxAuiToolBar) pObject, int tool_id);
TClass(wxString) wxAuiToolBar_GetToolLabel(TSelf(wxAuiToolBar) pObject, int tool_id);
void wxAuiToolBar_SetToolLabel(TSelf(wxAuiToolBar) pObject, int tool_id, TClass(wxString) label);
void wxAuiToolBar_GetToolBitmap(TSelf(wxAuiToolBar) pObject, int tool_id,
                                TClassRef(wxBitmap) bitmap);
void wxAuiToolBar_SetToolBitmap(TSelf(wxAuiToolBar) pObject, int tool_id, TClass(wxBitmap) bitmap);
TClass(wxString) wxAuiToolBar_GetToolShortHelp(TSelf(wxAuiToolBar) pObject, int tool_id);
void wxAuiToolBar_SetToolShortHelp(TSelf(wxAuiToolBar) pObject, int tool_id,
                                   TClass(wxString) helpString);
TClass(wxString) wxAuiToolBar_GetToolLongHelp(TSelf(wxAuiToolBar) pObject, int tool_id);
void wxAuiToolBar_SetToolLongHelp(TSelf(wxAuiToolBar) pObject, int tool_id,
                                  TClass(wxString) helpString);
void wxAuiToolBar_SetCustomOverflowItems(TSelf(wxAuiToolBar) pObject,
                                         TClass(wxAuiToolBarItemArray) prepend,
                                         TClass(wxAuiToolBarItemArray) append);
TClass(wxSize) wxAuiToolBar_GetHintSize(TSelf(wxAuiToolBar) pObject, int dock_direction);
TBool wxAuiToolBar_IsPaneValid(TSelf(wxAuiToolBar) pObject, TClass(wxAuiPaneInfo) pane);

/* wxAuiNotebook */
TClassDefExtend(wxAuiNotebook, wxBookCtrlBase) TClass(wxAuiNotebook) wxAuiNotebook_CreateDefault();
TClass(wxAuiNotebook) wxAuiNotebook_Create(TClass(wxWindow) parent, int id, TPoint(x, y),
                                           TSize(width, height), long style);
TBool wxAuiNotebook_CreateFromDefault(TSelf(wxAuiNotebook) pObject, TClass(wxWindow) parent, int id,
                                      TPoint(x, y), TSize(width, height), long style);
TBool wxAuiNotebook_AddPageWithBitmap(TSelf(wxAuiNotebook) pObject, TClass(wxWindow) page,
                                      TClass(wxString) caption, TBool select,
                                      TClass(wxBitmap) bitmap);
TBool wxAuiNotebook_AddPage(TSelf(wxAuiNotebook) pObject, TClass(wxWindow) page,
                            TClass(wxString) text, TBool select, int imageId);
void wxAuiNotebook_AdvanceSelection(TSelf(wxAuiNotebook) pObject, TBool forward);
int wxAuiNotebook_ChangeSelection(TSelf(wxAuiNotebook) pObject, size_t index);
TBool wxAuiNotebook_DeleteAllPages(TSelf(wxAuiNotebook) pObject);
TBool wxAuiNotebook_DeletePage(TSelf(wxAuiNotebook) pObject, size_t page);
TClass(wxAuiTabArt) wxAuiNotebook_GetArtProvider(TSelf(wxAuiNotebook) pObject);
TClass(wxWindow) wxAuiNotebook_GetCurrentPage(TSelf(wxAuiNotebook) pObject);
int wxAuiNotebook_GetHeightForPageHeight(TSelf(wxAuiNotebook) pObject, int pageHeight);
TClass(wxWindow) wxAuiNotebook_GetPage(TSelf(wxAuiNotebook) pObject, size_t page_idx);
void wxAuiNotebook_GetPageBitmap(TSelf(wxAuiNotebook) pObject, size_t page,
                                 TClassRef(wxBitmap) bmp);
size_t wxAuiNotebook_GetPageCount(TSelf(wxAuiNotebook) pObject);
int wxAuiNotebook_GetPageIndex(TSelf(wxAuiNotebook) pObject, TClass(wxWindow) pageWnd);
TClass(wxString) wxAuiNotebook_GetPageText(TSelf(wxAuiNotebook) pObject, size_t page);
TClass(wxString) wxAuiNotebook_GetPageToolTip(TSelf(wxAuiNotebook) pObject, size_t pageIdx);
int wxAuiNotebook_GetSelection(TSelf(wxAuiNotebook) pObject);
int wxAuiNotebook_GetTabCtrlHeight(TSelf(wxAuiNotebook) pObject);
TBool wxAuiNotebook_InsertPageWithBitmap(TSelf(wxAuiNotebook) pObject, size_t page_idx,
                                         TClass(wxWindow) page, TClass(wxString) caption,
                                         TBool select, TClass(wxBitmap) bitmap);
TBool wxAuiNotebook_InsertPage(TSelf(wxAuiNotebook) pObject, size_t index, TClass(wxWindow) page,
                               TClass(wxString) text, TBool select, int imageId);
TBool wxAuiNotebook_RemovePage(TSelf(wxAuiNotebook) pObject, size_t page);
void wxAuiNotebook_SetArtProvider(TSelf(wxAuiNotebook) pObject, TClass(wxAuiTabArt) artId);
TBool wxAuiNotebook_SetFont(TSelf(wxAuiNotebook) pObject, TClass(wxFont) font);
void wxAuiNotebook_SetMeasuringFont(TSelf(wxAuiNotebook) pObject, TClass(wxFont) font);
void wxAuiNotebook_SetNormalFont(TSelf(wxAuiNotebook) pObject, TClass(wxFont) font);
TBool wxAuiNotebook_SetPageBitmap(TSelf(wxAuiNotebook) pObject, size_t page,
                                  TClass(wxBitmap) bitmap);
TBool wxAuiNotebook_SetPageImage(TSelf(wxAuiNotebook) pObject, size_t index, int imageId);
TBool wxAuiNotebook_SetPageText(TSelf(wxAuiNotebook) pObject, size_t page, TClass(wxString) text);
TBool wxAuiNotebook_SetPageToolTip(TSelf(wxAuiNotebook) pObject, size_t page,
                                   TClass(wxString) text);
void wxAuiNotebook_SetSelectedFont(TSelf(wxAuiNotebook) pObject, TClass(wxFont) font);
size_t wxAuiNotebook_SetSelection(TSelf(wxAuiNotebook) pObject, size_t new_page);
void wxAuiNotebook_SetTabCtrlHeight(TSelf(wxAuiNotebook) pObject, int height);
TBool wxAuiNotebook_ShowWindowMenu(TSelf(wxAuiNotebook) pObject);
void wxAuiNotebook_SetUniformBitmapSize(TSelf(wxAuiNotebook) pObject, TSize(width, height));
void wxAuiNotebook_Split(TSelf(wxAuiNotebook) pObject, size_t page, int direction);

/* wxAuiTabContainerButton */
TClassDef(wxAuiTabContainerButton) int wxAuiTabContainerButton_Id(TSelf(wxAuiTabContainerButton)
                                                                      pObject);
int wxAuiTabContainerButton_CurState(TSelf(wxAuiTabContainerButton) pObject);
int wxAuiTabContainerButton_Location(TSelf(wxAuiTabContainerButton) pObject);
void wxAuiTabContainerButton_Bitmap(TSelf(wxAuiTabContainerButton) pObject,
                                    TClassRef(wxBitmap) bitmap);
void wxAuiTabContainerButton_DisBitmap(TSelf(wxAuiTabContainerButton) pObject,
                                       TClassRef(wxBitmap) bitmap);
TClass(wxRect) wxAuiTabContainerButton_Rect(TSelf(wxAuiTabContainerButton) pObject);

/* wxAuiTabContainer */
TClassDef(wxAuiTabContainer) TClass(wxAuiTabContainer) wxAuiTabContainer_Create();
void wxAuiTabContainer_SetArtProvider(TSelf(wxAuiTabContainer) pObject, TClass(wxAuiTabArt) artId);
TClass(wxAuiTabArt) wxAuiTabContainer_GetArtProvider(TSelf(wxAuiTabContainer) pObject);
void wxAuiTabContainer_SetFlags(TSelf(wxAuiTabContainer) pObject, int flags);
int wxAuiTabContainer_GetFlags(TSelf(wxAuiTabContainer) pObject);
TBool wxAuiTabContainer_AddPage(TSelf(wxAuiTabContainer) pObject, TClass(wxWindow) page,
                                TClass(wxAuiNotebookPage) info);
TBool wxAuiTabContainer_InsertPage(TSelf(wxAuiTabContainer) pObject, TClass(wxWindow) page,
                                   TClass(wxAuiNotebookPage) info, size_t idx);
TBool wxAuiTabContainer_MovePage(TSelf(wxAuiTabContainer) pObject, TClass(wxWindow) page,
                                 size_t newIdx);
TBool wxAuiTabContainer_RemovePage(TSelf(wxAuiTabContainer) pObject, TClass(wxWindow) page);
TBool wxAuiTabContainer_SetActivePageByWindow(TSelf(wxAuiTabContainer) pObject,
                                              TClass(wxWindow) page);
TBool wxAuiTabContainer_SetActivePage(TSelf(wxAuiTabContainer) pObject, size_t page);
void wxAuiTabContainer_SetNoneActive(TSelf(wxAuiTabContainer) pObject);
int wxAuiTabContainer_GetActivePage(TSelf(wxAuiTabContainer) pObject);
// TBool 	 wxAuiTabContainer_TabHitTest (TSelf(wxAuiTabContainer) pObject,
// int x, int y, TClassRef(wxWindow) hitResult ); TBool
// wxAuiTabContainer_ButtonHitTest (TSelf(wxAuiTabContainer) pObject, int x, int y,
// TClassRef(wxAuiTabContainerButton) hitResult );
TClass(wxWindow) wxAuiTabContainer_GetWindowFromIdx(TSelf(wxAuiTabContainer) pObject, size_t idx);
int wxAuiTabContainer_GetIdxFromWindow(TSelf(wxAuiTabContainer) pObject, TClass(wxWindow) page);
size_t wxAuiTabContainer_GetPageCount(TSelf(wxAuiTabContainer) pObject);
TClass(wxAuiNotebookPage) wxAuiTabContainer_GetPage(TSelf(wxAuiTabContainer) pObject, size_t idx);
TClass(wxAuiNotebookPageArray) wxAuiTabContainer_GetPages(TSelf(wxAuiTabContainer) pObject);
void wxAuiTabContainer_SetNormalFont(TSelf(wxAuiTabContainer) pObject, TClass(wxFont) normalFont);
void wxAuiTabContainer_SetSelectedFont(TSelf(wxAuiTabContainer) pObject,
                                       TClass(wxFont) selectedFont);
void wxAuiTabContainer_SetMeasuringFont(TSelf(wxAuiTabContainer) pObject,
                                        TClass(wxFont) measuringFont);
void wxAuiTabContainer_SetColour(TSelf(wxAuiTabContainer) pObject, TClass(wxColour) colour);
void wxAuiTabContainer_SetActiveColour(TSelf(wxAuiTabContainer) pObject, TClass(wxColour) colour);
void wxAuiTabContainer_DoShowHide(TSelf(wxAuiTabContainer) pObject);
void wxAuiTabContainer_SetRect(TSelf(wxAuiTabContainer) pObject, TClass(wxRect) rect);
void wxAuiTabContainer_RemoveButton(TSelf(wxAuiTabContainer) pObject, int id);
void wxAuiTabContainer_AddButton(TSelf(wxAuiTabContainer) pObject, int id, int location,
                                 TClass(wxBitmap) normalBitmap, TClass(wxBitmap) disabledBitmap);
size_t wxAuiTabContainer_GetTabOffset(TSelf(wxAuiTabContainer) pObject);
void wxAuiTabContainer_SetTabOffset(TSelf(wxAuiTabContainer) pObject, size_t offset);
TBool wxAuiTabContainer_IsTabVisible(TSelf(wxAuiTabContainer) pObject, int tabPage, int tabOffset,
                                     TClass(wxDC) dc, TClass(wxWindow) window);
void wxAuiTabContainer_MakeTabVisible(TSelf(wxAuiTabContainer) pObject, int tabPage,
                                      TClass(wxWindow) win);

/* wxAuiTabCtrl */
TClassDefExtend(wxAuiTabCtrl,
                wxControl) void wxAuiTabCtrl_SetArtProvider(TSelf(wxAuiTabCtrl) pObject,
                                                            TClass(wxAuiTabArt) artId);
TClass(wxAuiTabArt) wxAuiTabCtrl_GetArtProvider(TSelf(wxAuiTabCtrl) pObject);
void wxAuiTabCtrl_SetFlags(TSelf(wxAuiTabCtrl) pObject, int flags);
int wxAuiTabCtrl_GetFlags(TSelf(wxAuiTabCtrl) pObject);
TBool wxAuiTabCtrl_AddPage(TSelf(wxAuiTabCtrl) pObject, TClass(wxWindow) page,
                           TClass(wxAuiNotebookPage) info);
TBool wxAuiTabCtrl_InsertPage(TSelf(wxAuiTabCtrl) pObject, TClass(wxWindow) page,
                              TClass(wxAuiNotebookPage) info, size_t idx);
TBool wxAuiTabCtrl_MovePage(TSelf(wxAuiTabCtrl) pObject, TClass(wxWindow) page, size_t newIdx);
TBool wxAuiTabCtrl_RemovePage(TSelf(wxAuiTabCtrl) pObject, TClass(wxWindow) page);
TBool wxAuiTabCtrl_SetActivePageByWindow(TSelf(wxAuiTabCtrl) pObject, TClass(wxWindow) page);
TBool wxAuiTabCtrl_SetActivePage(TSelf(wxAuiTabCtrl) pObject, size_t page);
void wxAuiTabCtrl_SetNoneActive(TSelf(wxAuiTabCtrl) pObject);
int wxAuiTabCtrl_GetActivePage(TSelf(wxAuiTabCtrl) pObject);
// TBool 	 wxAuiTabCtrl_TabHitTest (TSelf(wxAuiTabCtrl) pObject, int x, int
// y, TClassRef(wxWindow) hitResult ); TBool 	 wxAuiTabCtrl_ButtonHitTest
// (TSelf(wxAuiTabCtrl) pObject, int x, int y, TClassRef(wxAuiTabCtrlButton) hitResult
// );
TClass(wxWindow) wxAuiTabCtrl_GetWindowFromIdx(TSelf(wxAuiTabCtrl) pObject, size_t idx);
int wxAuiTabCtrl_GetIdxFromWindow(TSelf(wxAuiTabCtrl) pObject, TClass(wxWindow) page);
size_t wxAuiTabCtrl_GetPageCount(TSelf(wxAuiTabCtrl) pObject);
TClass(wxAuiNotebookPage) wxAuiTabCtrl_GetPage(TSelf(wxAuiTabCtrl) pObject, size_t idx);
TClass(wxAuiNotebookPageArray) wxAuiTabCtrl_GetPages(TSelf(wxAuiTabCtrl) pObject);
void wxAuiTabCtrl_SetNormalFont(TSelf(wxAuiTabCtrl) pObject, TClass(wxFont) normalFont);
void wxAuiTabCtrl_SetSelectedFont(TSelf(wxAuiTabCtrl) pObject, TClass(wxFont) selectedFont);
void wxAuiTabCtrl_SetMeasuringFont(TSelf(wxAuiTabCtrl) pObject, TClass(wxFont) measuringFont);
void wxAuiTabCtrl_SetColour(TSelf(wxAuiTabCtrl) pObject, TClass(wxColour) colour);
void wxAuiTabCtrl_SetActiveColour(TSelf(wxAuiTabCtrl) pObject, TClass(wxColour) colour);
void wxAuiTabCtrl_DoShowHide(TSelf(wxAuiTabCtrl) pObject);
void wxAuiTabCtrl_SetRect(TSelf(wxAuiTabCtrl) pObject, TClass(wxRect) rect);
void wxAuiTabCtrl_RemoveButton(TSelf(wxAuiTabCtrl) pObject, int id);
void wxAuiTabCtrl_AddButton(TSelf(wxAuiTabCtrl) pObject, int id, int location,
                            TClass(wxBitmap) normalBitmap, TClass(wxBitmap) disabledBitmap);
size_t wxAuiTabCtrl_GetTabOffset(TSelf(wxAuiTabCtrl) pObject);
void wxAuiTabCtrl_SetTabOffset(TSelf(wxAuiTabCtrl) pObject, size_t offset);
TBool wxAuiTabCtrl_IsTabVisible(TSelf(wxAuiTabCtrl) pObject, int tabPage, int tabOffset,
                                TClass(wxDC) dc, TClass(wxWindow) window);
void wxAuiTabCtrl_MakeTabVisible(TSelf(wxAuiTabCtrl) pObject, int tabPage, TClass(wxWindow) win);

/* wxAuiTabArt */
TClassDef(wxAuiTabArt) TClass(wxAuiTabArt) wxAuiTabArt_Clone(TSelf(wxAuiTabArt) pObject);
void wxAuiTabArt_DrawBackground(TSelf(wxAuiTabArt) pObject, TClass(wxDC) dc,
                                TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiTabArt_DrawButton(TSelf(wxAuiTabArt) pObject, TClass(wxDC) dc, TClass(wxWindow) window,
                            TClass(wxRect) inRect, int bitmap_id, int button_state, int orientation,
                            TClass(wxRect) outRect);
void wxAuiTabArt_DrawTab(TSelf(wxAuiTabArt) pObject, TClass(wxDC) dc, TClass(wxWindow) window,
                         TClass(wxAuiNotebookPage) page, TClass(wxRect) rect,
                         int close_button_state, TClass(wxRect) outTabRect,
                         TClass(wxRect) outButtonRect, int* x_extent);
int wxAuiTabArt_GetBestTabCtrlSize(TSelf(wxAuiTabArt) pObject, TClass(wxWindow) window,
                                   TClass(wxAuiNotebookPageArray) pages, TSize(width, height));
int wxAuiTabArt_GetIndentSize(TSelf(wxAuiTabArt) pObject);
TClass(wxSize)
    wxAuiTabArt_GetTabSize(TSelf(wxAuiTabArt) pObject, TClass(wxDC) dc, TClass(wxWindow) window,
                           TClass(wxString) caption, TClass(wxBitmap) bitmap, TBool active,
                           int close_button_state, int* x_extent);
void wxAuiTabArt_SetFlags(TSelf(wxAuiTabArt) pObject, int flags);
void wxAuiTabArt_SetMeasuringFont(TSelf(wxAuiTabArt) pObject, TClass(wxFont) font);
void wxAuiTabArt_SetNormalFont(TSelf(wxAuiTabArt) pObject, TClass(wxFont) font);
void wxAuiTabArt_SetSelectedFont(TSelf(wxAuiTabArt) pObject, TClass(wxFont) font);
void wxAuiTabArt_SetColour(TSelf(wxAuiTabArt) pObject, TClass(wxColour) colour);
void wxAuiTabArt_SetActiveColour(TSelf(wxAuiTabArt) pObject, TClass(wxColour) colour);
void wxAuiTabArt_SetSizingInfo(TSelf(wxAuiTabArt) pObject, TSize(width, height), size_t tab_count);

/* wxAuiSimpleTabArt */
TClassDefExtend(wxAuiSimpleTabArt, wxAuiTabArt) TClass(wxAuiSimpleTabArt)
    wxAuiSimpleTabArt_Create();
TClass(wxAuiTabArt) wxAuiSimpleTabArt_Clone(TSelf(wxAuiSimpleTabArt) pObject);
void wxAuiSimpleTabArt_SetFlags(TSelf(wxAuiSimpleTabArt) pObject, int flags);
void wxAuiSimpleTabArt_SetSizingInfo(TSelf(wxAuiSimpleTabArt) pObject, TSize(width, height),
                                     size_t tabCount);
void wxAuiSimpleTabArt_SetNormalFont(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxFont) font);
void wxAuiSimpleTabArt_SetSelectedFont(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxFont) font);
void wxAuiSimpleTabArt_SetMeasuringFont(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxFont) font);
void wxAuiSimpleTabArt_SetColour(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxColour) colour);
void wxAuiSimpleTabArt_SetActiveColour(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxColour) colour);
void wxAuiSimpleTabArt_DrawBackground(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxDC) dc,
                                      TClass(wxWindow) window, TClass(wxRect) rect);
void wxAuiSimpleTabArt_DrawTab(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxDC) dc,
                               TClass(wxWindow) window, TClass(wxAuiNotebookPage) pane,
                               TClass(wxRect) inRect, int closeButtonState,
                               TClass(wxRect) outTabRect, TClass(wxRect) outButtonRect,
                               int* xExtent);
void wxAuiSimpleTabArt_DrawButton(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxDC) dc,
                                  TClass(wxWindow) window, TClass(wxRect) inRect, int bitmapId,
                                  int buttonState, int orientation, TClass(wxRect) outRect);
int wxAuiSimpleTabArt_GetIndentSize(TSelf(wxAuiSimpleTabArt) pObject);
TClass(wxSize) wxAuiSimpleTabArt_GetTabSize(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxDC) dc,
                                            TClass(wxWindow) window, TClass(wxString) caption,
                                            TClass(wxBitmap) bitmap, TBool active,
                                            int closeButtonState, int* xExtent);
int wxAuiSimpleTabArt_ShowDropDown(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxWindow) window,
                                   TClass(wxAuiNotebookPageArray) items, int activeIdx);
int wxAuiSimpleTabArt_GetBestTabCtrlSize(TSelf(wxAuiSimpleTabArt) pObject, TClass(wxWindow) window,
                                         TClass(wxAuiNotebookPageArray) pages,
                                         TSize(width, height));

/* wxAuiManager - public member */
TClassDefExtend(wxAuiManager, wxEvtHandler) TClass(wxAuiManager)
    wxAuiManager_Create(TClass(wxWindow) managedWnd, int flags);
void wxAuiManager_Delete(TSelf(wxAuiManager) pObject);
TBool wxAuiManager_DetachPane(TSelf(wxAuiManager) pObject, TClass(wxWindow) window);
TClass(wxAuiPaneInfoArray) wxAuiManager_GetAllPanes(TSelf(wxAuiManager) pObject);
TClass(wxAuiDockArt) wxAuiManager_GetArtProvider(TSelf(wxAuiManager) pObject);
void wxAuiManager_GetDockSizeConstraint(TSelf(wxAuiManager) pObject, double* widthPct,
                                        double* heightPct);
int wxAuiManager_GetFlags(TSelf(wxAuiManager) pObject);
TClass(wxWindow) wxAuiManager_GetManagedWindow(TSelf(wxAuiManager) pObject);
void wxAuiManager_HideHint(TSelf(wxAuiManager) pObject);
TBool wxAuiManager_InsertPane(TSelf(wxAuiManager) pObject, TClass(wxWindow) window,
                              TClass(wxAuiPaneInfo) insertLocation, int insertLevel);
void wxAuiManager_LoadPaneInfo(TSelf(wxAuiManager) pObject, TClass(wxString) panePart,
                               TClass(wxAuiPaneInfo) pane);
TBool wxAuiManager_LoadPerspective(TSelf(wxAuiManager) pObject, TClass(wxString) perspective,
                                   TBool update);
TClass(wxString) wxAuiManager_SavePaneInfo(TSelf(wxAuiManager) pObject, TClass(wxAuiPaneInfo) pane);
TClass(wxString) wxAuiManager_SavePerspective(TSelf(wxAuiManager) pObject);
void wxAuiManager_SetArtProvider(TSelf(wxAuiManager) pObject, TClass(wxAuiDockArt) artProvider);
void wxAuiManager_SetDockSizeConstraint(TSelf(wxAuiManager) pObject, double widthpct,
                                        double heightpct);
void wxAuiManager_SetFlags(TSelf(wxAuiManager) pObject, int flags);
void wxAuiManager_SetManagedWindow(TSelf(wxAuiManager) pObject, TClass(wxWindow) managedWnd);
void wxAuiManager_ShowHint(TSelf(wxAuiManager) pObject, TClass(wxRect) rect);
void wxAuiManager_UnInit(TSelf(wxAuiManager) pObject);
void wxAuiManager_Update(TSelf(wxAuiManager) pObject);
TBool wxAuiManager_AddPane(TSelf(wxAuiManager) pObject, TClass(wxWindow) window, int direction,
                           TClass(wxString) caption);
TBool wxAuiManager_AddPaneByPaneInfo(TSelf(wxAuiManager) pObject, TClass(wxWindow) window,
                                     TClass(wxAuiPaneInfo) paneInfo);
TBool wxAuiManager_AddPaneByPaneInfoAndDropPosition(TSelf(wxAuiManager) pObject,
                                                    TClass(wxWindow) window,
                                                    TClass(wxAuiPaneInfo) paneInfo, TPoint(x, y));
TClass(wxAuiPaneInfo)
    wxAuiManager_GetPaneByWindow(TSelf(wxAuiManager) pObject, TClass(wxWindow) window);
TClass(wxAuiPaneInfo)
    wxAuiManager_GetPaneByName(TSelf(wxAuiManager) pObject, TClass(wxString) name);
TClass(wxAuiManager) wxAuiManager_GetManager(TClass(wxWindow) window);

/* wxAuiDockArt */
TClassDef(wxAuiDockArt) void wxAuiDockArt_DrawBackground(TSelf(wxAuiDockArt) pObject,
                                                         TClass(wxDC) dc, TClass(wxWindow) window,
                                                         int orientation, TClass(wxRect) rect);
void wxAuiDockArt_DrawBorder(TSelf(wxAuiDockArt) pObject, TClass(wxDC) dc, TClass(wxWindow) window,
                             TClass(wxRect) rect, TClass(wxAuiPaneInfo) pane);
void wxAuiDockArt_DrawCaption(TSelf(wxAuiDockArt) pObject, TClass(wxDC) dc, TClass(wxWindow) window,
                              TClass(wxString) text, TClass(wxRect) rect,
                              TClass(wxAuiPaneInfo) pane);
void wxAuiDockArt_DrawGripper(TSelf(wxAuiDockArt) pObject, TClass(wxDC) dc, TClass(wxWindow) window,
                              TClass(wxRect) rect, TClass(wxAuiPaneInfo) pane);
void wxAuiDockArt_DrawPaneButton(TSelf(wxAuiDockArt) pObject, TClass(wxDC) dc,
                                 TClass(wxWindow) window, int button, int button_state,
                                 TClass(wxRect) rect, TClass(wxAuiPaneInfo) pane);
void wxAuiDockArt_DrawSash(TSelf(wxAuiDockArt) pObject, TClass(wxDC) dc, TClass(wxWindow) window,
                           int orientation, TClass(wxRect) rect);
TClass(wxColour) wxAuiDockArt_GetColour(TSelf(wxAuiDockArt) pObject, int id);
TClass(wxFont) wxAuiDockArt_GetFont(TSelf(wxAuiDockArt) pObject, int id);
int wxAuiDockArt_GetMetric(TSelf(wxAuiDockArt) pObject, int id);
void wxAuiDockArt_SetColour(TSelf(wxAuiDockArt) pObject, int id, TClass(wxColour) colour);
void wxAuiDockArt_SetFont(TSelf(wxAuiDockArt) pObject, int id, TClass(wxFont) font);
void wxAuiDockArt_SetMetric(TSelf(wxAuiDockArt) pObject, int id, int new_val);

/* wxAuiPaneInfo */
TClassDef(wxAuiPaneInfo) TClass(wxAuiPaneInfo) wxAuiPaneInfo_CreateDefault();
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Create(TClass(wxAuiPaneInfo) source);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Bottom(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_BottomDockable(TSelf(wxAuiPaneInfo) pObject, TBool enable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Caption(TSelf(wxAuiPaneInfo) pObject, TClass(wxString) caption);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_CaptionVisible(TSelf(wxAuiPaneInfo) pObject, TBool visible);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_CloseButton(TSelf(wxAuiPaneInfo) pObject, TBool visible);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_DefaultPane(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_DestroyOnClose(TSelf(wxAuiPaneInfo) pObject, TBool enable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Direction(TSelf(wxAuiPaneInfo) pObject, int direction);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Dock(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_DockFixed(TSelf(wxAuiPaneInfo) pObject, TBool enable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Dockable(TSelf(wxAuiPaneInfo) pObject, TBool enable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Fixed(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Float(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Floatable(TSelf(wxAuiPaneInfo) pObject, TBool enable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Gripper(TSelf(wxAuiPaneInfo) pObject, TBool visible);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_GripperTop(TSelf(wxAuiPaneInfo) pObject, TBool attop);
TBool wxAuiPaneInfo_HasBorder(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_HasCaption(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_HasCloseButton(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_HasFlag(TSelf(wxAuiPaneInfo) pObject, int flag);
TBool wxAuiPaneInfo_HasGripper(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_HasGripperTop(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_HasMaximizeButton(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_HasMinimizeButton(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_HasPinButton(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Hide(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Icon(TSelf(wxAuiPaneInfo) pObject, TClass(wxBitmap) bitmap);
TBool wxAuiPaneInfo_IsBottomDockable(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsDockable(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsDocked(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsFixed(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsFloatable(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsFloating(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsLeftDockable(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsMovable(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsOk(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsResizable(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsRightDockable(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsShown(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsToolbar(TSelf(wxAuiPaneInfo) pObject);
TBool wxAuiPaneInfo_IsTopDockable(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Layer(TSelf(wxAuiPaneInfo) pObject, int layer);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Left(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_LeftDockable(TSelf(wxAuiPaneInfo) pObject, TBool enable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_MaximizeButton(TSelf(wxAuiPaneInfo) pObject, TBool visible);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_MinimizeButton(TSelf(wxAuiPaneInfo) pObject, TBool visible);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Movable(TSelf(wxAuiPaneInfo) pObject, TBool enable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Name(TSelf(wxAuiPaneInfo) pObject, TClass(wxString) name);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_PaneBorder(TSelf(wxAuiPaneInfo) pObject, TBool visible);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_PinButton(TSelf(wxAuiPaneInfo) pObject, TBool visible);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Position(TSelf(wxAuiPaneInfo) pObject, int pos);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Resizable(TSelf(wxAuiPaneInfo) pObject, TBool resizable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Right(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_RightDockable(TSelf(wxAuiPaneInfo) pObject, TBool enable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Row(TSelf(wxAuiPaneInfo) pObject, int row);
void wxAuiPaneInfo_SafeSet(TSelf(wxAuiPaneInfo) pObject, TClass(wxAuiPaneInfo) source);
TClass(wxAuiPaneInfo)
    wxAuiPaneInfo_SetFlag(TSelf(wxAuiPaneInfo) pObject, int flag, TBool option_state);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Show(TSelf(wxAuiPaneInfo) pObject, TBool show);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_ToolbarPane(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Top(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_TopDockable(TSelf(wxAuiPaneInfo) pObject, TBool enable);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Window(TSelf(wxAuiPaneInfo) pObject, TClass(wxWindow) window);
TClass(wxAuiPaneInfo)
    wxAuiPaneInfo_Copy(TSelf(wxAuiPaneInfo) pObject, TClass(wxAuiPaneInfo) source);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_BestSize(TSelf(wxAuiPaneInfo) pObject, TSize(width, height));
TClass(wxAuiPaneInfo) wxAuiPaneInfo_BestSizeXY(TSelf(wxAuiPaneInfo) pObject, int x, int y);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Centre(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_Center(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_CentrePane(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_CenterPane(TSelf(wxAuiPaneInfo) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_FloatingPosition(TSelf(wxAuiPaneInfo) pObject, TPoint(x, y));
TClass(wxAuiPaneInfo) wxAuiPaneInfo_FloatingPositionXY(TSelf(wxAuiPaneInfo) pObject, int x, int y);
TClass(wxAuiPaneInfo)
    wxAuiPaneInfo_FloatingSize(TSelf(wxAuiPaneInfo) pObject, TSize(width, height));
TClass(wxAuiPaneInfo) wxAuiPaneInfo_FloatingSizeXY(TSelf(wxAuiPaneInfo) pObject, int x, int y);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_MaxSize(TSelf(wxAuiPaneInfo) pObject, TSize(width, height));
TClass(wxAuiPaneInfo) wxAuiPaneInfo_MaxSizeXY(TSelf(wxAuiPaneInfo) pObject, int x, int y);
TClass(wxAuiPaneInfo) wxAuiPaneInfo_MinSize(TSelf(wxAuiPaneInfo) pObject, TSize(width, height));
TClass(wxAuiPaneInfo) wxAuiPaneInfo_MinSizeXY(TSelf(wxAuiPaneInfo) pObject, int x, int y);

/* wxAuiManagerEvent */
TClassDefExtend(wxAuiManagerEvent, wxEvtHandler) TClass(wxAuiManagerEvent)
    wxAuiManagerEvent_Create(int type);
TBool wxAuiManagerEvent_CanVeto(TSelf(wxAuiManagerEvent) pObject);
int wxAuiManagerEvent_GetButton(TSelf(wxAuiManagerEvent) pObject);
TClass(wxDC) wxAuiManagerEvent_GetDC(TSelf(wxAuiManagerEvent) pObject);
TBool wxAuiManagerEvent_GetVeto(TSelf(wxAuiManagerEvent) pObject);
TClass(wxAuiManager) wxAuiManagerEvent_GetManager(TSelf(wxAuiManagerEvent) pObject);
TClass(wxAuiPaneInfo) wxAuiManagerEvent_GetPane(TSelf(wxAuiManagerEvent) pObject);
void wxAuiManagerEvent_SetButton(TSelf(wxAuiManagerEvent) pObject, int button);
void wxAuiManagerEvent_SetCanVeto(TSelf(wxAuiManagerEvent) pObject, TBool can_veto);
void wxAuiManagerEvent_SetDC(TSelf(wxAuiManagerEvent) pObject, TClass(wxDC) paintDC);
void wxAuiManagerEvent_SetManager(TSelf(wxAuiManagerEvent) pObject, TClass(wxAuiManager) manager);
void wxAuiManagerEvent_SetPane(TSelf(wxAuiManagerEvent) pObject, TClass(wxAuiPaneInfo) pane);
void wxAuiManagerEvent_Veto(TSelf(wxAuiManagerEvent) pObject, TBool veto);

/* wxAuiNotebookEvent */
TClassDefExtend(wxAuiNotebookEvent, wxBookCtrlEvent) TClass(wxAuiNotebookEvent)
    wxAuiNotebookEvent_Create(int command_type, int win_id);
TClass(wxAuiNotebook) wxAuiNotebookEvent_GetDragSource(TSelf(wxAuiNotebookEvent) pObject);
/* void SetDragSource(wxAuiNotebook* s) { m_dragSource = s; } */

/* wxBookCtrlEvent */
TClassDefExtend(wxBookCtrlEvent, wxNotifyEvent) TClass(wxBookCtrlEvent)
    wxBookCtrlEvent_Create(int commandType, int winid, int nSel, int nOldSel);
int wxBookCtrlEvent_GetSelection(TSelf(wxBookCtrlEvent) pObject);
int wxBookCtrlEvent_GetOldSelection(TSelf(wxBookCtrlEvent) pObject);
/* void    wxBookCtrlEvent_SetSelection(int nSel); */
/* void    wxBookCtrlEvent_SetOldSelection(int nOldSel); */

/* wxBookCtrlBase */
TClassDefExtend(wxBookCtrlBase, wxControl) TBool
    wxBookCtrlBase_CreateFromDefault(TSelf(wxBookCtrlBase) pObject, TClass(wxWindow) parent,
                                     int winid, TPoint(x, y), TSize(width, height), long style,
                                     TClass(wxString) name);
void wxBookCtrlBase_SetPageSize(TSelf(wxBookCtrlBase) pObject, TSize(width, height));
int wxBookCtrlBase_HitTest(TSelf(wxBookCtrlBase) pObject, TPoint(x, y), long* flags);
int wxBookCtrlBase_GetPageImage(TSelf(wxBookCtrlBase) pObject, size_t nPage);
TBool wxBookCtrlBase_SetPageImage(TSelf(wxBookCtrlBase) pObject, size_t page, int image);
TClass(wxString) wxBookCtrlBase_GetPageText(TSelf(wxBookCtrlBase) pObject, size_t nPage);
TBool wxBookCtrlBase_SetPageText(TSelf(wxBookCtrlBase) pObject, size_t page, TClass(wxString) text);
int wxBookCtrlBase_GetSelection(TSelf(wxBookCtrlBase) pObject);
TClass(wxWindow) wxBookCtrlBase_GetCurrentPage(TSelf(wxBookCtrlBase) pObject);
int wxBookCtrlBase_SetSelection(TSelf(wxBookCtrlBase) pObject, size_t page);
void wxBookCtrlBase_AdvanceSelection(TSelf(wxBookCtrlBase) pObject, TBool forward);
int wxBookCtrlBase_ChangeSelection(TSelf(wxBookCtrlBase) pObject, size_t page);
int wxBookCtrlBase_FindPage(TSelf(wxBookCtrlBase) pObject, TClass(wxWindow) page);
TBool wxBookCtrlBase_AddPage(TSelf(wxBookCtrlBase) pObject, TClass(wxWindow) page,
                             TClass(wxString) text, TBool select, int imageId);
TBool wxBookCtrlBase_DeleteAllPages(TSelf(wxBookCtrlBase) pObject);
TBool wxBookCtrlBase_DeletePage(TSelf(wxBookCtrlBase) pObject, size_t page);
TBool wxBookCtrlBase_InsertPage(TSelf(wxBookCtrlBase) pObject, size_t index, TClass(wxWindow) page,
                                TClass(wxString) text, TBool select, int imageId);
TBool wxBookCtrlBase_RemovePage(TSelf(wxBookCtrlBase) pObject, size_t page);
size_t wxBookCtrlBase_GetPageCount(TSelf(wxBookCtrlBase) pObject);
TClass(wxWindow) wxBookCtrlBase_GetPage(TSelf(wxBookCtrlBase) pObject, size_t page);
void wxBookCtrlBase_AssignImageList(TSelf(wxBookCtrlBase) pObject, TClass(wxImageList) imageList);
void wxBookCtrlBase_SetImageList(TSelf(wxBookCtrlBase) pObject, TClass(wxImageList) imageList);
TClass(wxImageList) wxBookCtrlBase_GetImageList(TSelf(wxBookCtrlBase) pObject);

TClassDef(wxAuiNotebookPage) TClass(wxWindow)
    wxAuiNotebookPage_Window(TSelf(wxAuiNotebookPage) pObject);
TClass(wxString) wxAuiNotebookPage_Caption(TSelf(wxAuiNotebookPage) pObject);
TClass(wxString) wxAuiNotebookPage_Tooltip(TSelf(wxAuiNotebookPage) pObject);
TClass(wxBitmap) wxAuiNotebookPage_Bitmap(TSelf(wxAuiNotebookPage) pObject);
TClass(wxRect) wxAuiNotebookPage_Rect(TSelf(wxAuiNotebookPage) pObject);
TBool wxAuiNotebookPage_Active(TSelf(wxAuiNotebookPage) pObject);

/** wxAuiNotebookPageArray **/
/** see wxWidgets dynarray.height for additional array functions **/
TClassDef(wxAuiNotebookPageArray) TClass(wxAuiNotebookPageArray) wxAuiNotebookPageArray_Create();
void wxAuiNotebookPageArray_Delete(TSelf(wxAuiNotebookPageArray) pObject);
int wxAuiNotebookPageArray_GetCount(TSelf(wxAuiNotebookPageArray) pObject);
TClass(wxAuiNotebookPage)
    wxAuiNotebookPageArray_Item(TSelf(wxAuiNotebookPageArray) pObject, int index);

/** wxAuiToolBarItemArray **/
/** see wxWidgets dynarray.height for additional array functions **/
TClassDef(wxAuiToolBarItemArray) TClass(wxAuiToolBarItemArray) wxAuiToolBarItemArray_Create();
void wxAuiToolBarItemArray_Delete(TSelf(wxAuiToolBarItemArray) pObject);
int wxAuiToolBarItemArray_GetCount(TSelf(wxAuiToolBarItemArray) pObject);
TClass(wxAuiToolBarItem)
    wxAuiToolBarItemArray_Item(TSelf(wxAuiToolBarItemArray) pObject, int index);

/** wxAuiPaneInfoArray **/
/** see wxWidgets dynarray.height for additional array functions **/
TClassDef(wxAuiPaneInfoArray) TClass(wxAuiPaneInfoArray) wxAuiPaneInfoArray_Create();
void wxAuiPaneInfoArray_Delete(TSelf(wxAuiPaneInfoArray) pObject);
int wxAuiPaneInfoArray_GetCount(TSelf(wxAuiPaneInfoArray) pObject);
TClass(wxAuiPaneInfo) wxAuiPaneInfoArray_Item(TSelf(wxAuiPaneInfoArray) pObject, int index);

/* wxAutoBufferedPaintDC */
TClassDefExtend(wxAutoBufferedPaintDC, wxDC) TClass(wxAutoBufferedPaintDC)
    wxAutoBufferedPaintDC_Create(TClass(wxWindow) window);
void wxAutoBufferedPaintDC_Delete(TSelf(wxAutoBufferedPaintDC) self);

/* wxAutomationObject */
TClassDefExtend(wxAutomationObject, wxObject)

    /* wxBitmap */
    TClassDefExtend(wxBitmap, wxGDIObject) void wxBitmap_AddHandler(TClass(wxEvtHandler) handler);
void wxBitmap_CleanUpHandlers();
TClass(wxBitmap) wxBitmap_Create(void* data, int type, TSize(width, height), int depth);
TClass(wxBitmap) wxBitmap_CreateDefault();
TClass(wxBitmap) wxBitmap_CreateEmpty(TSize(width, height), int depth);
TClass(wxBitmap) wxBitmap_CreateFromXPM(TSelf(wxBitmap) data);
TClass(wxBitmap) wxBitmap_CreateLoad(TClass(wxString) name, int type);
void wxBitmap_Delete(TSelf(wxBitmap) pObject);
void* wxBitmap_FindHandlerByExtension(TSelf(wxBitmap) extension, int type);
void* wxBitmap_FindHandlerByName(TClass(wxString) name);
void* wxBitmap_FindHandlerByType(int type);
int wxBitmap_GetDepth(TSelf(wxBitmap) pObject);
int wxBitmap_GetHeight(TSelf(wxBitmap) pObject);
TClass(wxMask) wxBitmap_GetMask(TSelf(wxBitmap) pObject);
void wxBitmap_GetSubBitmap(TSelf(wxBitmap) pObject, TRect(x, y, width, height),
                           TClassRef(wxBitmap) ref);
int wxBitmap_GetWidth(TSelf(wxBitmap) pObject);
void wxBitmap_InitStandardHandlers();
void wxBitmap_InsertHandler(TClass(wxEvtHandler) handler);
int wxBitmap_LoadFile(TSelf(wxBitmap) pObject, TClass(wxString) name, int type);
TBool wxBitmap_IsOk(TSelf(wxBitmap) pObject);
TBool wxBitmap_RemoveHandler(TClass(wxString) name);
int wxBitmap_SaveFile(TSelf(wxBitmap) pObject, TClass(wxString) name, int type,
                      TClass(wxPalette) cmap);
void wxBitmap_SetDepth(TSelf(wxBitmap) pObject, int depth);
void wxBitmap_SetHeight(TSelf(wxBitmap) pObject, int height);
void wxBitmap_SetMask(TSelf(wxBitmap) pObject, TClass(wxMask) mask);
void wxBitmap_SetWidth(TSelf(wxBitmap) pObject, int width);

/* wxBitmapButton */
TClassDefExtend(wxBitmapButton, wxButton) TClass(wxBitmapButton)
    wxBitmapButton_Create(TClass(wxWindow) parent, int id, TClass(wxBitmap) bitmap,
                          TRect(left, top, width, height), int style);
void wxBitmapButton_GetBitmapDisabled(TSelf(wxBitmapButton) pObject, TClassRef(wxBitmap) ref);
void wxBitmapButton_GetBitmapFocus(TSelf(wxBitmapButton) pObject, TClassRef(wxBitmap) ref);
void wxBitmapButton_GetBitmapLabel(TSelf(wxBitmapButton) pObject, TClassRef(wxBitmap) ref);
void wxBitmapButton_GetBitmapSelected(TSelf(wxBitmapButton) pObject, TClassRef(wxBitmap) ref);
int wxBitmapButton_GetMarginX(TSelf(wxBitmapButton) pObject);
int wxBitmapButton_GetMarginY(TSelf(wxBitmapButton) pObject);
void wxBitmapButton_SetBitmapDisabled(TSelf(wxBitmapButton) pObject, TClass(wxBitmap) disabled);
void wxBitmapButton_SetBitmapFocus(TSelf(wxBitmapButton) pObject, TClass(wxBitmap) focus);
void wxBitmapButton_SetBitmapLabel(TSelf(wxBitmapButton) pObject, TClass(wxBitmap) bitmap);
void wxBitmapButton_SetBitmapSelected(TSelf(wxBitmapButton) pObject, TClass(wxBitmap) sel);
void wxBitmapButton_SetMargins(TSelf(wxBitmapButton) pObject, TPoint(x, y));

/* wxBitmapComboBox */
TClassDefExtend(wxBitmapComboBox, wxComboBox) TClass(wxBitmapComboBox)
    wxBitmapComboBox_Create(TClass(wxWindow) parent, int id, TClass(wxString) value,
                            TRect(x, y, width, height), TArrayString(n, str), int style);
void wxBitmapComboBox_Append(TSelf(wxBitmapComboBox) self, TClass(wxString) item,
                             TClass(wxBitmap) bitmap);
void wxBitmapComboBox_AppendWithClientData(TSelf(wxBitmapComboBox) self, TClass(wxString) item,
                                           TClass(wxBitmap) bitmap, void* data);
void wxBitmapComboBox_Insert(TSelf(wxBitmapComboBox) self, TClass(wxString) item,
                             TClass(wxBitmap) bitmap, int pos);
void wxBitmapComboBox_InsertWithClientData(TSelf(wxBitmapComboBox) self, TClass(wxString) item,
                                           TClass(wxBitmap) bitmap, int pos, void* data);
TClass(wxBitmap) wxBitmapComboBox_GetItemBitmap(TSelf(wxBitmapComboBox) self, int index);
void wxBitmapComboBox_SetItemBitmap(TSelf(wxBitmapComboBox) self, int index,
                                    TClass(wxBitmap) bitmap);
TClass(wxSize) wxBitmapComboBox_GetBitmapSize(TSelf(wxBitmapComboBox) self);

/* wxBitmapToggleButton */
TClassDefExtend(wxBitmapToggleButton, wxToggleButton) TClass(wxBitmapToggleButton)
    wxBitmapToggleButton_Create(TClass(wxWindow) parent, int id, TClass(wxBitmap) bitmap,
                                TRect(x, y, width, height), int style);
TBool wxBitmapToggleButton_Enable(TSelf(wxBitmapToggleButton) pObject, TBool enable);
TBool wxBitmapToggleButton_GetValue(TSelf(wxBitmapToggleButton) pObject);
void wxBitmapToggleButton_SetValue(TSelf(wxBitmapToggleButton) pObject, TBool state);
void wxBitmapToggleButton_SetBitmapLabel(TSelf(wxBitmapToggleButton) pObject,
                                         TClass(wxBitmap) bitmap);

/* wxBitmapDataObject */
TClassDefExtend(wxBitmapDataObject, wxDataObjectSimple) TClass(wxBitmapDataObject)
    BitmapDataObject_Create(TClass(wxBitmap) bitmap);
TClass(wxBitmapDataObject) BitmapDataObject_CreateEmpty();
void BitmapDataObject_Delete(TSelf(wxBitmapDataObject) pObject);
void BitmapDataObject_GetBitmap(TSelf(wxBitmapDataObject) pObject, TClassRef(wxBitmap) bitmap);
void BitmapDataObject_SetBitmap(TSelf(wxBitmapDataObject) pObject, TClass(wxBitmap) bitmap);

/* wxBitmapHandler */
TClassDefExtend(wxBitmapHandler, wxObject)

    /* wxBoxSizer */
    TClassDefExtend(wxBoxSizer, wxSizer) TClass(wxSize)
        wxBoxSizer_CalcMin(TSelf(wxBoxSizer) pObject);
TClass(wxBoxSizer) wxBoxSizer_Create(int orient);
int wxBoxSizer_GetOrientation(TSelf(wxBoxSizer) pObject);
void wxBoxSizer_RecalcSizes(TSelf(wxBoxSizer) pObject);

/* wxBrush */
TClassDefExtend(wxBrush, wxGDIObject) void wxBrush_Assign(TSelf(wxBrush) pObject,
                                                          TClass(wxBrush) brush);
TClass(wxBrush) wxBrush_CreateDefault();
TClass(wxBrush) wxBrush_CreateFromBitmap(TClass(wxBitmap) bitmap);
TClass(wxBrush) wxBrush_CreateFromColour(TClass(wxColour) col, int style);
TClass(wxBrush) wxBrush_CreateFromStock(int id);
void wxBrush_Delete(TSelf(wxBrush) pObject);
void wxBrush_GetColour(TSelf(wxBrush) pObject, TClassRef(wxColour) ref);
void wxBrush_GetStipple(TSelf(wxBrush) pObject, TClassRef(wxBitmap) ref);
int wxBrush_GetStyle(TSelf(wxBrush) pObject);
TBool wxBrush_IsEqual(TSelf(wxBrush) pObject, TClass(wxBrush) brush);
TBool wxBrush_IsOk(TSelf(wxBrush) pObject);
void wxBrush_SetColour(TSelf(wxBrush) pObject, TClass(wxColour) col);
void wxBrush_SetColourSingle(TSelf(wxBrush) pObject, TChar red, TChar green, TChar blue);
void wxBrush_SetStipple(TSelf(wxBrush) pObject, TClass(wxBitmap) stipple);
void wxBrush_SetStyle(TSelf(wxBrush) pObject, int style);

/* wxBrushList */
TClassDefExtend(wxBrushList, wxList)

    /* wxBufferedDC */
    TClassDefExtend(wxBufferedDC, wxDC) TClass(wxBufferedDC)
        wxBufferedDC_CreateByDCAndSize(TClass(wxDC) dc, TSize(width, hight), int style);
TClass(wxBufferedDC)
    wxBufferedDC_CreateByDCAndBitmap(TClass(wxDC) dc, TClass(wxBitmap) bitmap, int style);
void wxBufferedDC_Delete(TSelf(wxBufferedDC) self);

/* wxBufferedPaintDC */
TClassDefExtend(wxBufferedPaintDC, wxDC) TClass(wxBufferedPaintDC)
    wxBufferedPaintDC_Create(TClass(wxWindow) window, int style);
TClass(wxBufferedPaintDC)
    wxBufferedPaintDC_CreateWithBitmap(TClass(wxWindow) window, TClass(wxBitmap) bitmap, int style);
void wxBufferedPaintDC_Delete(TSelf(wxBufferedPaintDC) self);

/* wxBufferedInputStream */
TClassDefExtend(wxBufferedInputStream, wxFilterInputStream)

    /* wxBufferedOutputStream */
    TClassDefExtend(wxBufferedOutputStream, wxFilterOutputStream)

    /* wxBusyCursor */
    TClassDef(wxBusyCursor) TClass(wxBusyCursor) wxBusyCursor_Create();
void* wxBusyCursor_CreateWithCursor(TSelf(wxBusyCursor) cursor);
void wxBusyCursor_Delete(TSelf(wxBusyCursor) pObject);

/* wxBusyInfo */
TClassDef(wxBusyInfo) TClass(wxBusyInfo)
    wxBusyInfo_Create(TClass(wxString) text, TClass(wxWindow) parent);
void wxBusyInfo_Delete(TSelf(wxBusyInfo) pObject);

/* wxBannerWindow */
TClassDefExtend(wxBannerWindow, wxWindow) TClass(wxBannerWindow)
    wxBannerWindow_Create(TClass(wxWindow) parent, int id, int dir, TRect(x, y, width, height),
                          int style);
void wxBannerWindow_SetBitmap(TSelf(wxBannerWindow) self, TClass(wxBitmap) bmp);
void wxBannerWindow_SetText(TSelf(wxBannerWindow) self, TClass(wxString) title,
                            TClass(wxString) message);
void wxBannerWindow_SetGradient(TSelf(wxBannerWindow) self, TClass(wxColour) start,
                                TClass(wxColour) end);

/* wxButton */
TClassDefExtend(wxButton, wxControl) TClass(wxButton)
    wxButton_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                    TRect(left, top, width, height), int style);
int wxButton_SetBackgroundColour(TSelf(wxButton) pObject, TClass(wxColour) colour);
void wxButton_SetDefault(TSelf(wxButton) pObject);

/* wxCSConv */
TClassDefExtend(wxCSConv, wxMBConv)

    /* wxCalculateLayoutEvent */
    TClassDefExtend(wxCalculateLayoutEvent, wxEvent) TClass(wxCalculateLayoutEvent)
        wxCalculateLayoutEvent_Create(int id);
int wxCalculateLayoutEvent_GetFlags(TSelf(wxCalculateLayoutEvent) pObject);
TClass(wxRect) wxCalculateLayoutEvent_GetRect(TSelf(wxCalculateLayoutEvent) pObject);
void wxCalculateLayoutEvent_SetFlags(TSelf(wxCalculateLayoutEvent) pObject, int flags);
void wxCalculateLayoutEvent_SetRect(TSelf(wxCalculateLayoutEvent) pObject,
                                    TRect(x, y, width, height));

/* wxCalendarCtrl */
TClassDefExtend(wxCalendarCtrl, wxControl) TClass(wxCalendarCtrl)
    wxCalendarCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxDateTime) date,
                          TRect(left, top, width, height), int style);
void wxCalendarCtrl_EnableHolidayDisplay(TSelf(wxCalendarCtrl) pObject, int display);
void wxCalendarCtrl_EnableMonthChange(TSelf(wxCalendarCtrl) pObject, TBool enable);
void* wxCalendarCtrl_GetAttr(TSelf(wxCalendarCtrl) pObject, int day);
void wxCalendarCtrl_GetDate(TSelf(wxCalendarCtrl) pObject, void* date);
void wxCalendarCtrl_GetHeaderColourBg(TSelf(wxCalendarCtrl) pObject, TClassRef(wxColour) ref);
void wxCalendarCtrl_GetHeaderColourFg(TSelf(wxCalendarCtrl) pObject, TClassRef(wxColour) ref);
void wxCalendarCtrl_GetHighlightColourBg(TSelf(wxCalendarCtrl) pObject, TClassRef(wxColour) ref);
void wxCalendarCtrl_GetHighlightColourFg(TSelf(wxCalendarCtrl) pObject, TClassRef(wxColour) ref);
void wxCalendarCtrl_GetHolidayColourBg(TSelf(wxCalendarCtrl) pObject, TClassRef(wxColour) ref);
void wxCalendarCtrl_GetHolidayColourFg(TSelf(wxCalendarCtrl) pObject, TClassRef(wxColour) ref);
int wxCalendarCtrl_HitTest(TSelf(wxCalendarCtrl) pObject, TPoint(x, y), void* date, void* weekday);
void wxCalendarCtrl_ResetAttr(TSelf(wxCalendarCtrl) pObject, int day);
void wxCalendarCtrl_SetAttr(TSelf(wxCalendarCtrl) pObject, int day, void* attr);
void wxCalendarCtrl_SetDate(TSelf(wxCalendarCtrl) pObject, void* date);
void wxCalendarCtrl_SetHeaderColours(TSelf(wxCalendarCtrl) pObject, void* colFg, void* colBg);
void wxCalendarCtrl_SetHighlightColours(TSelf(wxCalendarCtrl) pObject, void* colFg, void* colBg);
void wxCalendarCtrl_SetHoliday(TSelf(wxCalendarCtrl) pObject, int day);
void wxCalendarCtrl_SetHolidayColours(TSelf(wxCalendarCtrl) pObject, void* colFg, void* colBg);

/* wxCalendarDateAttr */
TClassDef(wxCalendarDateAttr) TClass(wxCalendarDateAttr)
    wxCalendarDateAttr_Create(void* textColour, void* backColour, void* borderColour, void* font,
                              int border);
TClass(wxCalendarDateAttr) wxCalendarDateAttr_CreateDefault();
void wxCalendarDateAttr_Delete(TSelf(wxCalendarDateAttr) pObject);
void wxCalendarDateAttr_GetBackgroundColour(TSelf(wxCalendarDateAttr) pObject,
                                            TClassRef(wxColour) ref);
int wxCalendarDateAttr_GetBorder(TSelf(wxCalendarDateAttr) pObject);
void wxCalendarDateAttr_GetBorderColour(TSelf(wxCalendarDateAttr) pObject, TClassRef(wxColour) ref);
void wxCalendarDateAttr_GetFont(TSelf(wxCalendarDateAttr) pObject, TClassRef(wxFont) ref);
void wxCalendarDateAttr_GetTextColour(TSelf(wxCalendarDateAttr) pObject, TClassRef(wxColour) ref);
TBool wxCalendarDateAttr_HasBackgroundColour(TSelf(wxCalendarDateAttr) pObject);
TBool wxCalendarDateAttr_HasBorder(TSelf(wxCalendarDateAttr) pObject);
TBool wxCalendarDateAttr_HasBorderColour(TSelf(wxCalendarDateAttr) pObject);
TBool wxCalendarDateAttr_HasFont(TSelf(wxCalendarDateAttr) pObject);
TBool wxCalendarDateAttr_HasTextColour(TSelf(wxCalendarDateAttr) pObject);
TBool wxCalendarDateAttr_IsHoliday(TSelf(wxCalendarDateAttr) pObject);
void wxCalendarDateAttr_SetBackgroundColour(TSelf(wxCalendarDateAttr) pObject,
                                            TClass(wxColour) col);
void wxCalendarDateAttr_SetBorder(TSelf(wxCalendarDateAttr) pObject, int border);
void wxCalendarDateAttr_SetBorderColour(TSelf(wxCalendarDateAttr) pObject, TClass(wxColour) col);
void wxCalendarDateAttr_SetFont(TSelf(wxCalendarDateAttr) pObject, TClass(wxFont) font);
void wxCalendarDateAttr_SetHoliday(TSelf(wxCalendarDateAttr) pObject, int holiday);
void wxCalendarDateAttr_SetTextColour(TSelf(wxCalendarDateAttr) pObject, TClass(wxColour) col);

/* wxCalendarEvent */
TClassDefExtend(wxCalendarEvent, wxCommandEvent) void wxCalendarEvent_GetDate(TSelf(wxCalendarEvent)
                                                                                  pObject,
                                                                              void* date);
int wxCalendarEvent_GetWeekDay(TSelf(wxCalendarEvent) pObject);

/* wxCaret */
TClassDef(wxCaret) TClass(wxCaret) wxCaret_Create(TClass(wxWindow) window, int width, int height);
int wxCaret_GetBlinkTime();
TClass(wxPoint) wxCaret_GetPosition(TSelf(wxCaret) pObject);
TClass(wxSize) wxCaret_GetSize(TSelf(wxCaret) pObject);
TClass(wxWindow) wxCaret_GetWindow(TSelf(wxCaret) pObject);
void wxCaret_Hide(TSelf(wxCaret) pObject);
TBool wxCaret_IsOk(TSelf(wxCaret) pObject);
TBool wxCaret_IsVisible(TSelf(wxCaret) pObject);
void wxCaret_Move(TSelf(wxCaret) pObject, TPoint(x, y));
void wxCaret_SetBlinkTime(int milliseconds);
void wxCaret_SetSize(TSelf(wxCaret) pObject, TSize(width, height));
void wxCaret_Show(TSelf(wxCaret) pObject);

/* wxCheckBox */
TClassDefExtend(wxCheckBox, wxControl) TClass(wxCheckBox)
    wxCheckBox_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                      TRect(left, top, width, height), int style);
void wxCheckBox_Delete(TSelf(wxCheckBox) pObject);
TBool wxCheckBox_GetValue(TSelf(wxCheckBox) pObject);
void wxCheckBox_SetValue(TSelf(wxCheckBox) pObject, TBoolInt value);
int wxCheckBox_Get3StateValue(TSelf(wxCheckBox) pObject);
TBool wxCheckBox_Is3State(TSelf(wxCheckBox) pObject);
void wxCheckBox_Set3StateValue(TSelf(wxCheckBox) pObject, int state);

/* wxCheckListBox */
TClassDefExtend(wxCheckListBox, wxListBox) void wxCheckListBox_Check(TSelf(wxCheckListBox) pObject,
                                                                     int item, TBool check);
TClass(wxCheckListBox)
    wxCheckListBox_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height),
                          TArrayString(n, str), int style);
void wxCheckListBox_Delete(TSelf(wxCheckListBox) pObject);
TBool wxCheckListBox_IsChecked(TSelf(wxCheckListBox) pObject, int item);

/* wxChoice */
TClassDefExtend(wxChoice, wxControl) void wxChoice_Append(TSelf(wxChoice) pObject,
                                                          TClass(wxString) item);
void wxChoice_Clear(TSelf(wxChoice) pObject);
TClass(wxChoice) wxChoice_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height),
                                 TArrayString(n, str), int style);
void wxChoice_Delete(TSelf(wxChoice) pObject, int index);
int wxChoice_FindString(TSelf(wxChoice) pObject, TClass(wxString) str);
int wxChoice_GetCount(TSelf(wxChoice) pObject);
int wxChoice_GetSelection(TSelf(wxChoice) pObject);
TClass(wxString) wxChoice_GetString(TSelf(wxChoice) pObject, int index);
void wxChoice_SetSelection(TSelf(wxChoice) pObject, int index);
void wxChoice_SetString(TSelf(wxChoice) pObject, int index, TClass(wxString) str);

/* wxClassInfo */
TClassDef(wxClassInfo) void* wxClassInfo_CreateClassByName(TSelf(wxClassInfo) info);
void* wxClassInfo_GetClassName(TSelf(wxClassInfo) info);
TBool wxClassInfo_IsKindOf(TSelf(wxClassInfo) pObject, TClass(wxString) name);

/* wxClient */
TClassDefExtend(wxClient, wxClientBase)

    /* wxClientBase */
    TClassDefExtend(wxClientBase, wxObject)

    /* wxClientDC */
    TClassDefExtend(wxClientDC, wxWindowDC) TClass(wxClientDC)
        wxClientDC_Create(TClass(wxWindow) win);
void wxClientDC_Delete(TSelf(wxClientDC) pObject);

/* wxClientData */
TClassDef(wxClientData)

    /* wxClientDataContainer */
    TClassDef(wxClientDataContainer)

    /* wxClipboard */
    TClassDefExtend(wxClipboard, wxObject) TBool
    wxClipboard_AddData(TSelf(wxClipboard) pObject, TClass(wxDataObject) data);
void wxClipboard_Clear(TSelf(wxClipboard) pObject);
void wxClipboard_Close(TSelf(wxClipboard) pObject);
TClass(wxClipboard) wxClipboard_Create();
TBool wxClipboard_Flush(TSelf(wxClipboard) pObject);
TBool wxClipboard_GetData(TSelf(wxClipboard) pObject, TClass(wxDataObject) data);
TBool wxClipboard_IsOpened(TSelf(wxClipboard) pObject);
TBool wxClipboard_IsSupported(TSelf(wxClipboard) pObject, TClass(wxDataFormat) format);
TBool wxClipboard_Open(TSelf(wxClipboard) pObject);
TBool wxClipboard_SetData(TSelf(wxClipboard) pObject, TClass(wxDataObject) data);
void wxClipboard_UsePrimarySelection(TSelf(wxClipboard) pObject, TBool primary);

/* wxCollapsiblePane */
TClassDefExtend(wxCollapsiblePane, wxControl) TClass(wxCollapsiblePane)
    wxCollapsiblePane_Create(TClass(wxWindow) parent, int id, TClass(wxString) label,
                             TRect(x, y, width, height), int style);
void wxCollapsiblePane_Collapse(TSelf(wxCollapsiblePane) pObject, TBool collapse);
void wxCollapsiblePane_Expand(TSelf(wxCollapsiblePane) pObject);
TBool wxCollapsiblePane_IsCollapsed(TSelf(wxCollapsiblePane) pObject);
TBool wxCollapsiblePane_IsExpanded(TSelf(wxCollapsiblePane) pObject);
TClass(wxWindow) wxCollapsiblePane_GetPane(TSelf(wxCollapsiblePane) pObject);
TClass(wxString) wxCollapsiblePane_GetLabel(TSelf(wxCollapsiblePane) pObject);
void wxCollapsiblePane_SetLabel(TSelf(wxCollapsiblePane) pObject, TClass(wxString) label);

/* wxCollapsiblePaneEvent */
TClassDefExtend(wxCollapsiblePaneEvent, wxCommandEvent) TBool
    wxCollapsiblePaneEvent_GetCollapsed(TSelf(wxCollapsiblePaneEvent) pObject);
void wxCollapsiblePaneEvent_SetCollapsed(TSelf(wxCollapsiblePaneEvent) pObject, TBool collapsed);

// Style constants
int expCP_DEFAULT_STYLE();
int expCP_NO_TLW_RESIZE();

/* wxCloseEvent */
TClassDefExtend(wxCloseEvent, wxEvent) TBool wxCloseEvent_CanVeto(TSelf(wxCloseEvent) pObject);
void wxCloseEvent_CopyObject(TSelf(wxCloseEvent) pObject, TClass(wxObject) obj);
TBool wxCloseEvent_GetLoggingOff(TSelf(wxCloseEvent) pObject);
TBool wxCloseEvent_GetVeto(TSelf(wxCloseEvent) pObject);
void wxCloseEvent_SetCanVeto(TSelf(wxCloseEvent) pObject, TBool canVeto);
void wxCloseEvent_SetLoggingOff(TSelf(wxCloseEvent) pObject, TBool logOff);
void wxCloseEvent_Veto(TSelf(wxCloseEvent) pObject, TBool veto);

/* wxClosure */
TClassDefExtend(wxClosure, wxObject)

    /* wxColour */
    TClassDefExtend(wxColour, wxObject) TUInt8 wxColour_Alpha(TSelf(wxColour) pObject);
void wxColour_Assign(TSelf(wxColour) pObject, void* other);
TUInt8 wxColour_Blue(TSelf(wxColour) pObject);
void wxColour_Copy(TSelf(wxColour) pObject, void* other);
TClass(wxColour) wxColour_CreateByName(TClass(wxString) name);
TClass(wxColour) wxColour_CreateEmpty();
TClass(wxColour) wxColour_CreateFromStock(int id);
TClass(wxColour) wxColour_CreateRGB(TUInt8 red, TUInt8 green, TUInt8 blue, TUInt8 alpha);
void wxColour_Delete(TSelf(wxColour) pObject);
TUInt8 wxColour_Green(TSelf(wxColour) pObject);
TBool wxColour_IsOk(TSelf(wxColour) pObject);
TUInt8 wxColour_Red(TSelf(wxColour) pObject);
void wxColour_Set(TSelf(wxColour) pObject, TUInt8 red, TUInt8 green, TUInt8 blue, TUInt8 alpha);
void wxColour_SetByName(TSelf(wxColour) pObject, TClass(wxString) name);
TBool wxColour_ValidName(TStringVoid name);

/* wxColourData */
TClassDefExtend(wxColourData, wxObject) TClass(wxColourData) wxColourData_Create();
void wxColourData_Delete(TSelf(wxColourData) pObject);
TBool wxColourData_GetChooseFull(TSelf(wxColourData) pObject);
void wxColourData_GetColour(TSelf(wxColourData) pObject, TClassRef(wxColour) ref);
void wxColourData_GetCustomColour(TSelf(wxColourData) pObject, int index, TClassRef(wxColour) ref);
void wxColourData_SetChooseFull(TSelf(wxColourData) pObject, TBool flag);
void wxColourData_SetColour(TSelf(wxColourData) pObject, TClass(wxColour) colour);
void wxColourData_SetCustomColour(TSelf(wxColourData) pObject, int index, TClass(wxColour) colour);

/* wxColourDatabase */
TClassDefExtend(wxColourDatabase, wxList)

    /* wxColourDialog */
    TClassDefExtend(wxColourDialog, wxDialog) TClass(wxColourDialog)
        wxColourDialog_Create(TClass(wxWindow) parent, TClass(wxColourData) col);
void wxColourDialog_GetColourData(TSelf(wxColourDialog) pObject, TClassRef(wxColourData) ref);

/* wxCommandLinkButton */
TClassDefExtend(wxCommandLinkButton, wxButton) TClass(wxCommandLinkButton)
    wxCommandLinkButton_Create(TClass(wxWindow) parent, int id, TClass(wxString) mainLabel,
                               TClass(wxString) note, TRect(x, y, width, height), int style);
void wxCommandLinkButton_SetMainLabel(TSelf(wxCommandLinkButton) self, TClass(wxString) mainLabel);
void wxCommandLinkButton_SetNote(TSelf(wxCommandLinkButton) self, TClass(wxString) note);
TClass(wxString) wxCommandLinkButton_GetMainLabel(TSelf(wxCommandLinkButton) self);
TClass(wxString) wxCommandLinkButton_GetNote(TSelf(wxCommandLinkButton) self);

/* wxComboBox */
TClassDefExtend(wxComboBox, wxChoice) void wxComboBox_Append(TSelf(wxComboBox) pObject,
                                                             TClass(wxString) item);
void wxComboBox_AppendData(TSelf(wxComboBox) pObject, TClass(wxString) item, void* clientData);
void wxComboBox_Clear(TSelf(wxComboBox) pObject);
void wxComboBox_Copy(TSelf(wxComboBox) pObject);
TClass(wxComboBox)
    wxComboBox_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                      TRect(left, top, width, height), TArrayString(n, str), int style);
void wxComboBox_Cut(TSelf(wxComboBox) pObject);
void wxComboBox_Delete(TSelf(wxComboBox) pObject, int index);
int wxComboBox_FindString(TSelf(wxComboBox) pObject, TClass(wxString) str);
TClass(wxClientData) wxComboBox_GetClientData(TSelf(wxComboBox) pObject, int index);
int wxComboBox_GetCount(TSelf(wxComboBox) pObject);
int wxComboBox_GetInsertionPoint(TSelf(wxComboBox) pObject);
int wxComboBox_GetLastPosition(TSelf(wxComboBox) pObject);
int wxComboBox_GetSelection(TSelf(wxComboBox) pObject);
TClass(wxString) wxComboBox_GetString(TSelf(wxComboBox) pObject, int index);
TClass(wxString) wxComboBox_GetStringSelection(TSelf(wxComboBox) pObject);
TClass(wxString) wxComboBox_GetValue(TSelf(wxComboBox) pObject);
void wxComboBox_SetValue(TSelf(wxComboBox) pObject, TClass(wxString) value);
void wxComboBox_Paste(TSelf(wxComboBox) pObject);
void wxComboBox_Remove(TSelf(wxComboBox) pObject, int from, int toPos);
void wxComboBox_Replace(TSelf(wxComboBox) pObject, int from, int toPos, TClass(wxString) value);
void wxComboBox_SetClientData(TSelf(wxComboBox) pObject, int index,
                              TClass(wxClientData) clientData);
void wxComboBox_SetEditable(TSelf(wxComboBox) pObject, TBool editable);
void wxComboBox_SetInsertionPoint(TSelf(wxComboBox) pObject, int pos);
void wxComboBox_SetInsertionPointEnd(TSelf(wxComboBox) pObject);
void wxComboBox_SetSelection(TSelf(wxComboBox) pObject, int index);
void wxComboBox_SetTextSelection(TSelf(wxComboBox) pObject, int from, int toPos);

/* wxCommand */
TClassDefExtend(wxCommand, wxObject)

    /* wxCommandEvent */
    TClassDefExtend(wxCommandEvent, wxEvent) void wxCommandEvent_CopyObject(TSelf(wxCommandEvent)
                                                                                pObject,
                                                                            void* object_dest);
TClass(wxCommandEvent) wxCommandEvent_Create(int type, int id);
void wxCommandEvent_Delete(TSelf(wxCommandEvent) pObject);
TClass(wxClientData) wxCommandEvent_GetClientData(TSelf(wxCommandEvent) pObject);
TClass(wxClientData) wxCommandEvent_GetClientObject(TSelf(wxCommandEvent) pObject);
long wxCommandEvent_GetExtraLong(TSelf(wxCommandEvent) pObject);
long wxCommandEvent_GetInt(TSelf(wxCommandEvent) pObject);
int wxCommandEvent_GetSelection(TSelf(wxCommandEvent) pObject);
TClass(wxString) wxCommandEvent_GetString(TSelf(wxCommandEvent) pObject);
TBool wxCommandEvent_IsChecked(TSelf(wxCommandEvent) pObject);
TBool wxCommandEvent_IsSelection(TSelf(wxCommandEvent) pObject);
void wxCommandEvent_SetClientData(TSelf(wxCommandEvent) pObject, TClass(wxClientData) clientData);
void wxCommandEvent_SetClientObject(TSelf(wxCommandEvent) pObject,
                                    TClass(wxClientData) clientObject);
void wxCommandEvent_SetExtraLong(TSelf(wxCommandEvent) pObject, long extraLong);
void wxCommandEvent_SetInt(TSelf(wxCommandEvent) pObject, int intValue);
void wxCommandEvent_SetString(TSelf(wxCommandEvent) pObject, TClass(wxString) str);

/* wxCommandLineParser */
TClassDef(wxCommandLineParser)

    /* wxCommandProcessor */
    TClassDefExtend(wxCommandProcessor, wxObject) TBool
    wxCommandProcessor_CanRedo(TSelf(wxCommandProcessor) pObject);
TBool wxCommandProcessor_CanUndo(TSelf(wxCommandProcessor) pObject);
void wxCommandProcessor_ClearCommands(TSelf(wxCommandProcessor) pObject);
void wxCommandProcessor_Delete(TSelf(wxCommandProcessor) pObject);
int wxCommandProcessor_GetCommands(TSelf(wxCommandProcessor) pObject, void* ref);
void* wxCommandProcessor_GetEditMenu(TSelf(wxCommandProcessor) pObject);
int wxCommandProcessor_GetMaxCommands(TSelf(wxCommandProcessor) pObject);
void wxCommandProcessor_Initialize(TSelf(wxCommandProcessor) pObject);
int wxCommandProcessor_Redo(TSelf(wxCommandProcessor) pObject);
void wxCommandProcessor_SetEditMenu(TSelf(wxCommandProcessor) pObject, TClass(wxMenu) menu);
void wxCommandProcessor_SetMenuStrings(TSelf(wxCommandProcessor) pObject);
int wxCommandProcessor_Submit(TSelf(wxCommandProcessor) pObject, TClass(wxCommand) command,
                              int storeIt);
int wxCommandProcessor_Undo(TSelf(wxCommandProcessor) pObject);
void* wxCommandProcessor_wxCommandProcessor(int maxCommands);

/* wxCondition */
TClassDef(wxCondition) void wxCondition_Broadcast(TSelf(wxCondition) pObject);
TClass(wxCondition) wxCondition_Create(void* mutex);
void wxCondition_Delete(TSelf(wxCondition) pObject);
void wxCondition_Signal(TSelf(wxCondition) pObject);
void wxCondition_Wait(TSelf(wxCondition) pObject);
int wxCondition_WaitFor(TSelf(wxCondition) pObject, int sec, int nsec);

/* wxConfigBase */
TClassDef(wxConfigBase) TClass(wxConfigBase) wxConfigBase_Create();
void wxConfigBase_Delete(TSelf(wxConfigBase) pObject);
TBool wxConfigBase_DeleteAll(TSelf(wxConfigBase) pObject);
TBool wxConfigBase_DeleteEntry(TSelf(wxConfigBase) pObject, TClass(wxString) key,
                               TBool bDeleteGroupIfEmpty);
TBool wxConfigBase_DeleteGroup(TSelf(wxConfigBase) pObject, TClass(wxString) key);
TBool wxConfigBase_Exists(TSelf(wxConfigBase) pObject, TClass(wxString) strName);
TClass(wxString) wxConfigBase_ExpandEnvVars(TSelf(wxConfigBase) pObject, TClass(wxString) str);
TBool wxConfigBase_Flush(TSelf(wxConfigBase) pObject, TBool bCurrentOnly);
TClass(wxString) wxConfigBase_GetAppName(TSelf(wxConfigBase) pObject);
int wxConfigBase_GetEntryType(TSelf(wxConfigBase) pObject, TClass(wxString) name);
TClass(wxString) wxConfigBase_GetFirstEntry(TSelf(wxConfigBase) pObject, void* lIndex);
TClass(wxString) wxConfigBase_GetFirstGroup(TSelf(wxConfigBase) pObject, void* lIndex);
TClass(wxString) wxConfigBase_GetNextEntry(TSelf(wxConfigBase) pObject, void* lIndex);
TClass(wxString) wxConfigBase_GetNextGroup(TSelf(wxConfigBase) pObject, void* lIndex);
int wxConfigBase_GetNumberOfEntries(TSelf(wxConfigBase) pObject, TBool bRecursive);
int wxConfigBase_GetNumberOfGroups(TSelf(wxConfigBase) pObject, TBool bRecursive);
TClass(wxString) wxConfigBase_GetPath(TSelf(wxConfigBase) pObject);
int wxConfigBase_GetStyle(TSelf(wxConfigBase) pObject);
TClass(wxString) wxConfigBase_GetVendorName(TSelf(wxConfigBase) pObject);
TBool wxConfigBase_HasEntry(TSelf(wxConfigBase) pObject, TClass(wxString) strName);
TBool wxConfigBase_HasGroup(TSelf(wxConfigBase) pObject, TClass(wxString) strName);
TBool wxConfigBase_IsExpandingEnvVars(TSelf(wxConfigBase) pObject);
TBool wxConfigBase_IsRecordingDefaults(TSelf(wxConfigBase) pObject);
TBool wxConfigBase_ReadBool(TSelf(wxConfigBase) pObject, TClass(wxString) key, TBool defVal);
double wxConfigBase_ReadDouble(TSelf(wxConfigBase) pObject, TClass(wxString) key, double defVal);
int wxConfigBase_ReadInteger(TSelf(wxConfigBase) pObject, TClass(wxString) key, int defVal);
TClass(wxString) wxConfigBase_ReadString(TSelf(wxConfigBase) pObject, TClass(wxString) key,
                                         TClass(wxString) defVal);
TBool wxConfigBase_RenameEntry(TSelf(wxConfigBase) pObject, TClass(wxString) oldName,
                               TClass(wxString) newName);
TBool wxConfigBase_RenameGroup(TSelf(wxConfigBase) pObject, TClass(wxString) oldName,
                               TClass(wxString) newName);
void wxConfigBase_SetAppName(TSelf(wxConfigBase) pObject, TClass(wxString) appName);
void wxConfigBase_SetExpandEnvVars(TSelf(wxConfigBase) pObject, TBool bDoIt);
void wxConfigBase_SetPath(TSelf(wxConfigBase) pObject, TClass(wxString) strPath);
void wxConfigBase_SetRecordDefaults(TSelf(wxConfigBase) pObject, TBool bDoIt);
void wxConfigBase_SetStyle(TSelf(wxConfigBase) pObject, int style);
void wxConfigBase_SetVendorName(TSelf(wxConfigBase) pObject, TClass(wxString) vendorName);
TBool wxConfigBase_WriteBool(TSelf(wxConfigBase) pObject, TClass(wxString) key, TBool value);
TBool wxConfigBase_WriteDouble(TSelf(wxConfigBase) pObject, TClass(wxString) key, double value);
TBool wxConfigBase_WriteInteger(TSelf(wxConfigBase) pObject, TClass(wxString) key, int value);
TBool wxConfigBase_WriteLong(TSelf(wxConfigBase) pObject, TClass(wxString) key, long value);
TBool wxConfigBase_WriteString(TSelf(wxConfigBase) pObject, TClass(wxString) key,
                               TClass(wxString) value);

/* wxConnection */
TClassDefExtend(wxConnection, wxConnectionBase)

    /* wxConnectionBase */
    TClassDefExtend(wxConnectionBase, wxObject)

    /* wxContextHelp */
    TClassDefExtend(wxContextHelp, wxObject) TBool
    wxContextHelp_BeginContextHelp(TSelf(wxContextHelp) pObject, TClass(wxWindow) win);
TClass(wxContextHelp) wxContextHelp_Create(TClass(wxWindow) win, TBool beginHelp);
void wxContextHelp_Delete(TSelf(wxContextHelp) pObject);
TBool wxContextHelp_EndContextHelp(TSelf(wxContextHelp) pObject);

/* wxContextHelpButton */
TClassDefExtend(wxContextHelpButton, wxBitmapButton) TClass(wxContextHelpButton)
    wxContextHelpButton_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                               long style);

/* wxControl */
TClassDefExtend(wxControl, wxWindow) void wxControl_Command(TSelf(wxControl) pObject,
                                                            TClass(wxEvent) event);
TClass(wxString) wxControl_GetLabel(TSelf(wxControl) pObject);
void wxControl_SetLabel(TSelf(wxControl) pObject, TClass(wxString) text);

/* wxCountingOutputStream */
TClassDefExtend(wxCountingOutputStream, wxOutputStream)

    /* wxCriticalSection */
    TClassDef(wxCriticalSection) TClass(wxCriticalSection) wxCriticalSection_Create();
void wxCriticalSection_Delete(TSelf(wxCriticalSection) pObject);
void wxCriticalSection_Enter(TSelf(wxCriticalSection) pObject);
void wxCriticalSection_Leave(TSelf(wxCriticalSection) pObject);

/* wxCriticalSectionLocker */
TClassDef(wxCriticalSectionLocker)

    /* wxCursor */
    TClassDefExtend(wxCursor, wxBitmap) TClass(wxCursor) Cursor_CreateFromStock(int id);
TClass(wxCursor) Cursor_CreateFromImage(TClass(wxImage) image);
TClass(wxCursor) Cursor_CreateLoad(TClass(wxString) name, long type, TSize(width, height));

/* wxCustomDataObject */
TClassDefExtend(wxCustomDataObject, wxDataObjectSimple)

    /* wxDC */
    TClassDefExtend(wxDC, wxObject) TBool
    wxDC_Blit(TSelf(wxDC) pObject, TRect(xdest, ydest, width, height), TClass(wxDC) source,
              TPoint(xsrc, ysrc), int rop, TBool useMask, TPoint(xsrcMask, ysrcMask));
void wxDC_CalcBoundingBox(TSelf(wxDC) pObject, TPoint(x, y));
TBool wxDC_CanDrawBitmap(TSelf(wxDC) pObject);
TBool wxDC_CanGetTextExtent(TSelf(wxDC) pObject);
void wxDC_Clear(TSelf(wxDC) pObject);
void wxDC_ComputeScaleAndOrigin(TSelf(wxDC) obj);
void wxDC_CrossHair(TSelf(wxDC) pObject, TPoint(x, y));
void wxDC_Delete(TSelf(wxDC) pObject);
void wxDC_DestroyClippingRegion(TSelf(wxDC) pObject);
int wxDC_DeviceToLogicalX(TSelf(wxDC) pObject, int x);
int wxDC_DeviceToLogicalXRel(TSelf(wxDC) pObject, int x);
int wxDC_DeviceToLogicalY(TSelf(wxDC) pObject, int y);
int wxDC_DeviceToLogicalYRel(TSelf(wxDC) pObject, int y);
void wxDC_DrawArc(TSelf(wxDC) pObject, TPoint(x1, y1), TPoint(x2, y2), TPoint(xc, yc));
void wxDC_DrawBitmap(TSelf(wxDC) pObject, TClass(wxBitmap) bmp, TPoint(x, y), TBool useMask);
void wxDC_DrawCheckMark(TSelf(wxDC) pObject, TRect(x, y, width, height));
void wxDC_DrawCircle(TSelf(wxDC) pObject, TPoint(x, y), int radius);
void wxDC_DrawEllipse(TSelf(wxDC) pObject, TRect(x, y, width, height));
void wxDC_DrawEllipticArc(TSelf(wxDC) pObject, TRect(x, y, width, height), double startAngle,
                          double endAngle);
void wxDC_DrawIcon(TSelf(wxDC) pObject, TClass(wxIcon) icon, TPoint(x, y));
void wxDC_DrawLabel(TSelf(wxDC) pObject, TClass(wxString) str, TRect(x, y, width, height),
                    int align, int indexAccel);
TClass(wxRect) wxDC_DrawLabelBitmap(TSelf(wxDC) pObject, TClass(wxString) str, TClass(wxBitmap) bmp,
                                    TRect(x, y, width, height), int align, int indexAccel);
void wxDC_DrawLine(TSelf(wxDC) pObject, TPoint(x1, y1), TPoint(x2, y2));
void wxDC_DrawLines(TSelf(wxDC) pObject, int count, void* x, void* y, TPoint(xoffset, yoffset));
void wxDC_DrawPoint(TSelf(wxDC) pObject, TPoint(x, y));
void wxDC_DrawPolygon(TSelf(wxDC) pObject, int count, void* x, void* y, TPoint(xoffset, yoffset),
                      int fillStyle);
void wxDC_DrawPolyPolygon(TSelf(wxDC) pObject, int numPolygons, void* count, void* x, void* y,
                          TPoint(xoffset, yoffset), int fillStyle);
void wxDC_DrawRectangle(TSelf(wxDC) pObject, TRect(x, y, width, height));
void wxDC_DrawRotatedText(TSelf(wxDC) pObject, TClass(wxString) text, TPoint(x, y), double angle);
void wxDC_DrawRoundedRectangle(TSelf(wxDC) pObject, TRect(x, y, width, height), double radius);
void wxDC_DrawText(TSelf(wxDC) pObject, TClass(wxString) text, TPoint(x, y));
void wxDC_EndDoc(TSelf(wxDC) pObject);
void wxDC_EndPage(TSelf(wxDC) pObject);
void wxDC_FloodFill(TSelf(wxDC) pObject, TPoint(x, y), TClass(wxColour) col, int style);
void wxDC_GetBackground(TSelf(wxDC) pObject, TClassRef(wxBrush) ref);
int wxDC_GetBackgroundMode(TSelf(wxDC) pObject);
void wxDC_GetBrush(TSelf(wxDC) pObject, TClassRef(wxBrush) ref);
int wxDC_GetCharHeight(TSelf(wxDC) pObject);
int wxDC_GetCharWidth(TSelf(wxDC) pObject);
void wxDC_GetClippingBox(TSelf(wxDC) pObject, TRectOutVoid(x, y, width, height));
int wxDC_GetDepth(TSelf(wxDC) pObject);
void wxDC_GetDeviceOrigin(TSelf(wxDC) pObject, TPointOutVoid(x, y));
void wxDC_GetFont(TSelf(wxDC) pObject, TClassRef(wxFont) ref);
int wxDC_GetLogicalFunction(TSelf(wxDC) pObject);
void wxDC_GetLogicalOrigin(TSelf(wxDC) pObject, TPointOutVoid(x, y));
void wxDC_GetLogicalScale(TSelf(wxDC) pObject, TSizeOutDouble(x, y));
int wxDC_GetMapMode(TSelf(wxDC) pObject);
TClass(wxSize) wxDC_GetPPI(TSelf(wxDC) pObject);
void wxDC_GetPen(TSelf(wxDC) pObject, TClassRef(wxPen) ref);
TBool wxDC_GetPixel(TSelf(wxDC) pObject, TPoint(x, y), TClass(wxColour) col);
TClass(wxSize) wxDC_GetSize(TSelf(wxDC) pObject);
TClass(wxSize) wxDC_GetSizeMM(TSelf(wxDC) pObject);
void wxDC_GetTextBackground(TSelf(wxDC) pObject, TClassRef(wxColour) ref);
void wxDC_GetTextExtent(TSelf(wxDC) self, TClass(wxString) string, void* width, void* height,
                        void* descent, void* externalLeading, TClass(wxFont) theFont);
void wxDC_GetMultiLineTextExtent(TSelf(wxDC) self, TClass(wxString) string, void* width,
                                 void* height, void* heightLine, TClass(wxFont) theFont);
void wxDC_GetTextForeground(TSelf(wxDC) pObject, TClassRef(wxColour) ref);
void wxDC_GetUserScale(TSelf(wxDC) pObject, TSizeOutDouble(x, y));
int wxDC_LogicalToDeviceX(TSelf(wxDC) pObject, int x);
int wxDC_LogicalToDeviceXRel(TSelf(wxDC) pObject, int x);
int wxDC_LogicalToDeviceY(TSelf(wxDC) pObject, int y);
int wxDC_LogicalToDeviceYRel(TSelf(wxDC) pObject, int y);
int wxDC_MaxX(TSelf(wxDC) pObject);
int wxDC_MaxY(TSelf(wxDC) pObject);
int wxDC_MinX(TSelf(wxDC) pObject);
int wxDC_MinY(TSelf(wxDC) pObject);
TBool wxDC_IsOk(TSelf(wxDC) pObject);
void wxDC_ResetBoundingBox(TSelf(wxDC) pObject);
void wxDC_SetAxisOrientation(TSelf(wxDC) pObject, TBool xLeftRight, TBool yBottomUp);
void wxDC_SetBackground(TSelf(wxDC) pObject, TClass(wxBrush) brush);
void wxDC_SetBackgroundMode(TSelf(wxDC) pObject, int mode);
void wxDC_SetBrush(TSelf(wxDC) pObject, TClass(wxBrush) brush);
void wxDC_SetClippingRegion(TSelf(wxDC) pObject, TRect(x, y, width, height));
void wxDC_SetClippingRegionFromRegion(TSelf(wxDC) pObject, TClass(wxRegion) region);
void wxDC_SetDeviceClippingRegion(TSelf(wxDC) pObject, TClass(wxRegion) region);
void wxDC_SetDeviceOrigin(TSelf(wxDC) pObject, TPoint(x, y));
void wxDC_SetFont(TSelf(wxDC) pObject, TClass(wxFont) font);
void wxDC_SetLogicalFunction(TSelf(wxDC) pObject, int function);
void wxDC_SetLogicalOrigin(TSelf(wxDC) pObject, TPoint(x, y));
void wxDC_SetLogicalScale(TSelf(wxDC) pObject, double x, double y);
void wxDC_SetMapMode(TSelf(wxDC) pObject, int mode);
void wxDC_SetPalette(TSelf(wxDC) pObject, TClass(wxPalette) palette);
void wxDC_SetPen(TSelf(wxDC) pObject, TClass(wxPen) pen);
void wxDC_SetTextBackground(TSelf(wxDC) pObject, TClass(wxColour) colour);
void wxDC_SetTextForeground(TSelf(wxDC) pObject, TClass(wxColour) colour);
void wxDC_SetUserScale(TSelf(wxDC) pObject, double x, double y);
TBool wxDC_StartDoc(TSelf(wxDC) pObject, TClass(wxString) msg);
void wxDC_StartPage(TSelf(wxDC) pObject);

/* wxDCClipper */
TClassDef(wxDCClipper)

    /* wxDDEClient */
    TClassDefExtend(wxDDEClient, wxClientBase)

    /* wxDDEConnection */
    TClassDefExtend(wxDDEConnection, wxConnectionBase)

    /* wxDDEServer */
    TClassDefExtend(wxDDEServer, wxServerBase)

    /* wxDataFormat */
    TClassDef(wxDataFormat) TClass(wxDataFormat) wxDataFormat_CreateFromId(TClass(wxString) name);
TClass(wxDataFormat) wxDataFormat_CreateFromType(int typ);
void wxDataFormat_Delete(TSelf(wxDataFormat) pObject);
TClass(wxString) wxDataFormat_GetId(TSelf(wxDataFormat) pObject);
int wxDataFormat_GetType(TSelf(wxDataFormat) pObject);
TBool wxDataFormat_IsEqual(TSelf(wxDataFormat) pObject, void* other);
void wxDataFormat_SetId(TSelf(wxDataFormat) pObject, void* id);
void wxDataFormat_SetType(TSelf(wxDataFormat) pObject, int typ);

/* wxDataInputStream */
TClassDef(wxDataInputStream)

    /* wxDataObject */
    TClassDef(wxDataObject)

    /* wxDataObjectComposite */
    TClassDefExtend(wxDataObjectComposite,
                    wxDataObject) void wxDataObjectComposite_Add(TSelf(wxDataObjectComposite)
                                                                     pObject,
                                                                 void* data, int preferred);
TClass(wxDataObjectComposite) wxDataObjectComposite_Create();
void wxDataObjectComposite_Delete(TSelf(wxDataObjectComposite) pObject);

/* wxDataObjectSimple */
TClassDefExtend(wxDataObjectSimple, wxDataObject)

    /* wxDataOutputStream */
    TClassDef(wxDataOutputStream)

    /* wxDatabase */
    TClassDefExtend(wxDatabase, wxObject)

    /* wxDateTime */
    TClassDef(wxDateTime) void wxDateTime_AddDate(TSelf(wxDateTime) pObject, void* diff,
                                                  TClassRef(wxDateTime) ref);
void wxDateTime_AddDateValues(TSelf(wxDateTime) pObject, int years, int month, int week, int day);
void wxDateTime_AddTime(TSelf(wxDateTime) pObject, void* diff, TClassRef(wxDateTime) ref);
void wxDateTime_AddTimeValues(TSelf(wxDateTime) pObject, int hours, int minVal, int seconds,
                              int milliseconds);
int wxDateTime_ConvertYearToBC(int year);
TClass(wxDateTime) wxDateTime_Create();
TClass(wxString) wxDateTime_Format(TSelf(wxDateTime) pObject, void* format, int timeZone);
TClass(wxString) wxDateTime_FormatDate(TSelf(wxDateTime) pObject);
TClass(wxString) wxDateTime_FormatISODate(TSelf(wxDateTime) pObject);
TClass(wxString) wxDateTime_FormatISOTime(TSelf(wxDateTime) pObject);
TClass(wxString) wxDateTime_FormatTime(TSelf(wxDateTime) pObject);
TClass(wxString) wxDateTime_GetAmString();
void wxDateTime_GetBeginDST(int year, int country, TClass(wxDateTime) dateTime);
int wxDateTime_GetCentury(int year);
int wxDateTime_GetCountry();
int wxDateTime_GetCurrentMonth(int cal);
int wxDateTime_GetCurrentYear(int cal);
int wxDateTime_GetDay(TSelf(wxDateTime) pObject, int timeZone);
int wxDateTime_GetDayOfYear(TSelf(wxDateTime) pObject, int timeZone);
void wxDateTime_GetEndDST(int year, int country, TClass(wxDateTime) dateTime);
int wxDateTime_GetHour(TSelf(wxDateTime) pObject, int timeZone);
void wxDateTime_GetLastMonthDay(TSelf(wxDateTime) pObject, int month, int year,
                                TClassRef(wxDateTime) ref);
void wxDateTime_GetLastWeekDay(TSelf(wxDateTime) pObject, int weekday, int month, int year,
                               TClassRef(wxDateTime) ref);
int wxDateTime_GetMillisecond(TSelf(wxDateTime) pObject, int timeZone);
int wxDateTime_GetMinute(TSelf(wxDateTime) pObject, int timeZone);
int wxDateTime_GetMonth(TSelf(wxDateTime) pObject, int timeZone);
TClass(wxString) wxDateTime_GetMonthName(int month, int flags);
void wxDateTime_GetNextWeekDay(TSelf(wxDateTime) pObject, int weekday, TClassRef(wxDateTime) ref);
int wxDateTime_GetNumberOfDays(int year, int cal);
int wxDateTime_GetNumberOfDaysMonth(int month, int year, int cal);
TClass(wxString) wxDateTime_GetPmString();
void wxDateTime_GetPrevWeekDay(TSelf(wxDateTime) pObject, int weekday, TClassRef(wxDateTime) ref);
int wxDateTime_GetSecond(TSelf(wxDateTime) pObject, int timeZone);
time_t wxDateTime_GetTicks(TSelf(wxDateTime) pObject);
int wxDateTime_GetTimeNow();
void wxDateTime_GetValue(TSelf(wxDateTime) pObject, void* hi_long, void* lo_long);
void wxDateTime_GetWeekDay(TSelf(wxDateTime) pObject, int weekday, int nthWeek, int month, int year,
                           TClassRef(wxDateTime) ref);
void wxDateTime_GetWeekDayInSameWeek(TSelf(wxDateTime) pObject, int weekday, int flags,
                                     TClassRef(wxDateTime) ref);
TClass(wxString) wxDateTime_GetWeekDayName(int weekday, int flags);
int wxDateTime_GetWeekDayTZ(TSelf(wxDateTime) pObject, int timeZone);
int wxDateTime_GetWeekOfMonth(TSelf(wxDateTime) pObject, int flags, int timeZone);
int wxDateTime_GetWeekOfYear(TSelf(wxDateTime) pObject, int flags, int timeZone);
int wxDateTime_GetYear(TSelf(wxDateTime) pObject, int timeZone);
TBool wxDateTime_IsBetween(TSelf(wxDateTime) pObject, TClass(wxDateTime) t1, TClass(wxDateTime) t2);
TBool wxDateTime_IsDST(TSelf(wxDateTime) pObject, int country);
TBool wxDateTime_IsDSTApplicable(int year, int country);
TBool wxDateTime_IsEarlierThan(TSelf(wxDateTime) pObject, void* datetime);
TBool wxDateTime_IsEqualTo(TSelf(wxDateTime) pObject, void* datetime);
TBool wxDateTime_IsEqualUpTo(TSelf(wxDateTime) pObject, TClass(wxDateTime) dateTime,
                             void* timeSpan);
TBool wxDateTime_IsGregorianDate(TSelf(wxDateTime) pObject, int country);
TBool wxDateTime_IsLaterThan(TSelf(wxDateTime) pObject, void* datetime);
TBool wxDateTime_IsLeapYear(int year, int cal);
TBool wxDateTime_IsSameDate(TSelf(wxDateTime) pObject, TClass(wxDateTime) dateTime);
TBool wxDateTime_IsSameTime(TSelf(wxDateTime) pObject, TClass(wxDateTime) dateTime);
TBool wxDateTime_IsStrictlyBetween(TSelf(wxDateTime) pObject, TClass(wxDateTime) t1,
                                   TClass(wxDateTime) t2);
TBool wxDateTime_IsValid(TSelf(wxDateTime) pObject);
TBool wxDateTime_IsWestEuropeanCountry(int country);
TBool wxDateTime_IsWorkDay(TSelf(wxDateTime) pObject, int country);
void wxDateTime_MakeGMT(TSelf(wxDateTime) pObject, int noDST);
void wxDateTime_MakeTimezone(TSelf(wxDateTime) pObject, int timeZone, int noDST);
void wxDateTime_Now(TSelf(wxDateTime) dateTime);
void* wxDateTime_ParseDate(TSelf(wxDateTime) pObject, void* date);
void* wxDateTime_ParseDateTime(TSelf(wxDateTime) pObject, void* datetime);
void* wxDateTime_ParseFormat(TSelf(wxDateTime) pObject, void* date, void* format, void* dateDef);
void* wxDateTime_ParseRfc822Date(TSelf(wxDateTime) pObject, void* date);
void* wxDateTime_ParseTime(TSelf(wxDateTime) pObject, TClass(wxTime) time);
void wxDateTime_ResetTime(TSelf(wxDateTime) pObject);
void wxDateTime_Set(TSelf(wxDateTime) pObject, int day, int month, int year, int hour, int minute,
                    int second, int millisec);
void wxDateTime_SetCountry(int country);
void wxDateTime_SetDay(TSelf(wxDateTime) pObject, int day);
void wxDateTime_SetHour(TSelf(wxDateTime) pObject, int hour);
void wxDateTime_SetMillisecond(TSelf(wxDateTime) pObject, int millisecond);
void wxDateTime_SetMinute(TSelf(wxDateTime) pObject, int minute);
void wxDateTime_SetMonth(TSelf(wxDateTime) pObject, int month);
void wxDateTime_SetSecond(TSelf(wxDateTime) pObject, int second);
void wxDateTime_SetTime(TSelf(wxDateTime) pObject, int hour, int minute, int second, int millisec);
void wxDateTime_SetToCurrent(TSelf(wxDateTime) pObject);
void wxDateTime_SetToLastMonthDay(TSelf(wxDateTime) pObject, int month, int year);
TBool wxDateTime_SetToLastWeekDay(TSelf(wxDateTime) pObject, int weekday, int month, int year);
void wxDateTime_SetToNextWeekDay(TSelf(wxDateTime) pObject, int weekday);
void wxDateTime_SetToPrevWeekDay(TSelf(wxDateTime) pObject, int weekday);
TBool wxDateTime_SetToWeekDay(TSelf(wxDateTime) pObject, int weekday, int nthWeek, int month,
                              int year);
void wxDateTime_SetToWeekDayInSameWeek(TSelf(wxDateTime) pObject, int weekday, int flags);
void wxDateTime_SetYear(TSelf(wxDateTime) pObject, int year);
void wxDateTime_SubtractDate(TSelf(wxDateTime) pObject, void* diff, TClassRef(wxDateTime) ref);
void wxDateTime_SubtractTime(TSelf(wxDateTime) pObject, void* diff, TClassRef(wxDateTime) ref);
void wxDateTime_ToGMT(TSelf(wxDateTime) pObject, int noDST);
void wxDateTime_ToTimezone(TSelf(wxDateTime) pObject, int timeZone, int noDST);
void wxDateTime_Today(TSelf(wxDateTime) dateTime);
void wxDateTime_UNow(TSelf(wxDateTime) dateTime);
void* wxDateTime_wxDateTime(int hi_long, int lo_long);

/* wxDb */
TClassDef(wxDb)

    /* wxDbColDef */
    TClassDef(wxDbColDef)

    /* wxDbColFor */
    TClassDef(wxDbColFor)

    /* wxDbColInf */
    TClassDef(wxDbColInf)

    /* wxDbConnectInf */
    TClassDef(wxDbConnectInf)

    /* wxDbInf */
    TClassDef(wxDbInf)

    /* wxDbSqlTypeInfo */
    TClassDef(wxDbSqlTypeInfo)

    /* wxDbTable */
    TClassDef(wxDbTable)

    /* wxDbTableInfo */
    TClassDef(wxDbTableInfo)

    /* wxDebugContext */
    TClassDef(wxDebugContext)

    /* wxDialUpEvent */
    TClassDefExtend(wxDialUpEvent, wxEvent) TBool
    wxDialUpEvent_IsConnectedEvent(TSelf(wxDialUpEvent) pObject);
TBool wxDialUpEvent_IsOwnEvent(TSelf(wxDialUpEvent) pObject);

/* wxDialUpManager */
TClassDef(wxDialUpManager) TBool wxDialUpManager_CancelDialing(TSelf(wxDialUpManager) pObject);
TClass(wxDialUpManager) wxDialUpManager_Create();
void wxDialUpManager_Delete(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_Dial(TSelf(wxDialUpManager) pObject, TClass(wxString) nameOfISP,
                           TClass(wxString) username, TClass(wxString) password, TBool async);
void wxDialUpManager_DisableAutoCheckOnlineStatus(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_EnableAutoCheckOnlineStatus(TSelf(wxDialUpManager) pObject, int nSeconds);
int wxDialUpManager_GetISPNames(TSelf(wxDialUpManager) pObject, TClass(wxList) list);
TBool wxDialUpManager_HangUp(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_IsAlwaysOnline(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_IsDialing(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_IsOk(TSelf(wxDialUpManager) pObject);
TBool wxDialUpManager_IsOnline(TSelf(wxDialUpManager) pObject);
void wxDialUpManager_SetConnectCommand(TSelf(wxDialUpManager) pObject, TClass(wxString) commandDial,
                                       TClass(wxString) commandHangup);
void wxDialUpManager_SetOnlineStatus(TSelf(wxDialUpManager) pObject, TBool isOnline);
void wxDialUpManager_SetWellKnownHost(TSelf(wxDialUpManager) pObject, TClass(wxString) hostname,
                                      int portno);

/* wxDialog */
TClassDefExtend(wxDialog, wxTopLevelWindow) TClass(wxDialog)
    wxDialog_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                    TRect(left, top, width, height), int style);
void wxDialog_EndModal(TSelf(wxDialog) pObject, int retCode);
int wxDialog_GetReturnCode(TSelf(wxDialog) pObject);
TBool wxDialog_IsModal(TSelf(wxDialog) pObject);
void wxDialog_SetReturnCode(TSelf(wxDialog) pObject, int returnCode);
int wxDialog_ShowModal(TSelf(wxDialog) pObject);

/* wxDirDialog */
TClassDefExtend(wxDirDialog, wxDialog) TClass(wxDirDialog)
    wxDirDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                       TClass(wxString) directory, TPoint(left, top), int style);
TClass(wxString) wxDirDialog_GetMessage(TSelf(wxDirDialog) pObject);
TClass(wxString) wxDirDialog_GetPath(TSelf(wxDirDialog) pObject);
int wxDirDialog_GetStyle(TSelf(wxDirDialog) pObject);
void wxDirDialog_SetMessage(TSelf(wxDirDialog) pObject, TClass(wxString) msg);
void wxDirDialog_SetPath(TSelf(wxDirDialog) pObject, TClass(wxString) pth);
void wxDirDialog_SetStyle(TSelf(wxDirDialog) pObject, int style);

/* wxDirTraverser */
TClassDef(wxDirTraverser)

    /* wxDllLoader */
    TClassDef(wxDllLoader)
    /*
    void*      wxDllLoader_GetSymbol( int handle, TStringVoid name );
    int        wxDllLoader_LoadLibrary( TStringVoid name, void* success );
    void       wxDllLoader_UnloadLibrary( int handle );
    */

    /* wxDocChildFrame */
    TClassDefExtend(wxDocChildFrame, wxFrame) TClass(wxDocChildFrame)
        wxDocChildFrame_Create(TClass(wxDocument) doc, TClass(wxView) view, TClass(wxFrame) parent,
                               int id, TClass(wxString) title, TRect(x, y, width, height),
                               int style);
TClass(wxDocument) wxDocChildFrame_GetDocument(TSelf(wxDocChildFrame) self);
TClass(wxView) wxDocChildFrame_GetView(TSelf(wxDocChildFrame) self);
void wxDocChildFrame_SetDocument(TSelf(wxDocChildFrame) self, TClass(wxDocument) doc);
void wxDocChildFrame_SetView(TSelf(wxDocChildFrame) self, TClass(wxView) view);

/* wxDocMDIChildFrame */
TClassDefExtend(wxDocMDIChildFrame, wxMDIChildFrame) TClass(wxDocMDIChildFrame)
    wxDocMDIChildFrame_Create(TClass(wxDocument) doc, TClass(wxView) view,
                              TClass(wxMDIParentFrame) parent, int id, TClass(wxString) title,
                              TRect(x, y, width, height), int style);
TClass(wxDocument) wxDocMDIChildFrame_GetDocument(TSelf(wxDocMDIChildFrame) self);
TClass(wxView) wxDocMDIChildFrame_GetView(TSelf(wxDocMDIChildFrame) self);
void wxDocMDIChildFrame_SetDocument(TSelf(wxDocMDIChildFrame) self, TClass(wxDocument) doc);
void wxDocMDIChildFrame_SetView(TSelf(wxDocMDIChildFrame) self, TClass(wxView) view);

/* wxDocMDIParentFrame */
TClassDefExtend(wxDocMDIParentFrame, wxMDIParentFrame) TClass(wxDocMDIParentFrame)
    wxDocMDIParentFrame_Create(TClass(wxDocManager) manager, TClass(wxFrame) parent, int id,
                               TClass(wxString) title, TRect(x, y, width, height), int style);
TClass(wxDocManager) wxDocMDIParentFrame_GetDocumentManager(TSelf(wxDocMDIParentFrame) self);

/* wxAuiMDIParentFrame */
TClassDefExtend(wxAuiMDIParentFrame, wxFrame) TClass(wxAuiMDIParentFrame)
    wxAuiMDIParentFrame_Create(TClass(wxWindow) parent, int id, TClass(wxString) title,
                               TRect(x, y, width, height), int style);
TClass(wxAuiMDIChildFrame) wxAuiMDIParentFrame_GetActiveChild(TSelf(wxAuiMDIParentFrame) self);
void wxAuiMDIParentFrame_SetActiveChild(TSelf(wxAuiMDIParentFrame) self,
                                        TClass(wxAuiMDIChildFrame) child);
void wxAuiMDIParentFrame_ActivateNext(TSelf(wxAuiMDIParentFrame) self);
void wxAuiMDIParentFrame_ActivatePrevious(TSelf(wxAuiMDIParentFrame) self);
void wxAuiMDIParentFrame_Cascade(TSelf(wxAuiMDIParentFrame) self);
void wxAuiMDIParentFrame_Tile(TSelf(wxAuiMDIParentFrame) self, int orient);
TClass(wxMenuBar) wxAuiMDIParentFrame_GetMenuBar(TSelf(wxAuiMDIParentFrame) self);
void wxAuiMDIParentFrame_SetMenuBar(TSelf(wxAuiMDIParentFrame) self, TClass(wxMenuBar) menuBar);
TClass(wxStatusBar) wxAuiMDIParentFrame_GetStatusBar(TSelf(wxAuiMDIParentFrame) self);
TClass(wxStatusBar) wxAuiMDIParentFrame_CreateStatusBar(TSelf(wxAuiMDIParentFrame) self, int number,
                                                        int style, int id);
TClass(wxToolBar) wxAuiMDIParentFrame_GetToolBar(TSelf(wxAuiMDIParentFrame) self);
TClass(wxToolBar)
    wxAuiMDIParentFrame_CreateToolBar(TSelf(wxAuiMDIParentFrame) self, int style, int id);
TClass(wxAuiNotebook) wxAuiMDIParentFrame_GetNotebook(TSelf(wxAuiMDIParentFrame) self);

/* wxAuiMDIChildFrame */
TClassDefExtend(wxAuiMDIChildFrame, wxFrame) TClass(wxAuiMDIChildFrame)
    wxAuiMDIChildFrame_Create(TClass(wxAuiMDIParentFrame) parent, int id, TClass(wxString) title,
                              TRect(x, y, width, height), int style);
void wxAuiMDIChildFrame_Activate(TSelf(wxAuiMDIChildFrame) self);
TClass(wxMenuBar) wxAuiMDIChildFrame_GetMenuBar(TSelf(wxAuiMDIChildFrame) self);
void wxAuiMDIChildFrame_SetMenuBar(TSelf(wxAuiMDIChildFrame) self, TClass(wxMenuBar) menuBar);
TClass(wxStatusBar) wxAuiMDIChildFrame_GetStatusBar(TSelf(wxAuiMDIChildFrame) self);
TClass(wxStatusBar) wxAuiMDIChildFrame_CreateStatusBar(TSelf(wxAuiMDIChildFrame) self, int number,
                                                       int style, int id);
TClass(wxToolBar) wxAuiMDIChildFrame_GetToolBar(TSelf(wxAuiMDIChildFrame) self);
TClass(wxToolBar)
    wxAuiMDIChildFrame_CreateToolBar(TSelf(wxAuiMDIChildFrame) self, int style, int id);
void wxAuiMDIChildFrame_SetTitle(TSelf(wxAuiMDIChildFrame) self, TClass(wxString) title);
TClass(wxString) wxAuiMDIChildFrame_GetTitle(TSelf(wxAuiMDIChildFrame) self);
void wxAuiMDIChildFrame_SetIcons(TSelf(wxAuiMDIChildFrame) self, TClass(wxIconBundle) icons);
TClass(wxIconBundle) wxAuiMDIChildFrame_GetIcons(TSelf(wxAuiMDIChildFrame) self);
void wxAuiMDIChildFrame_SetIcon(TSelf(wxAuiMDIChildFrame) self, TClass(wxIcon) icon);
TClass(wxIcon) wxAuiMDIChildFrame_GetIcon(TSelf(wxAuiMDIChildFrame) self);
TClass(wxWindow) wxAuiMDIChildFrame_GetMDIParent(TSelf(wxAuiMDIChildFrame) self);

/* wxDocManager */
TClassDefExtend(wxDocManager, wxEvtHandler)

    /* wxDocParentFrame */
    TClassDefExtend(wxDocParentFrame, wxFrame) TClass(wxDocParentFrame)
        wxDocParentFrame_Create(TClass(wxDocManager) manager, TClass(wxFrame) parent, int id,
                                TClass(wxString) title, TRect(x, y, width, height), int style);
TClass(wxDocManager) wxDocParentFrame_GetDocumentManager(TSelf(wxDocParentFrame) self);

/* wxDocTemplate */
TClassDefExtend(wxDocTemplate, wxObject)

    /* wxDocument */
    TClassDefExtend(wxDocument, wxEvtHandler)

    /* wxDragImage */
    TClassDefExtend(wxDragImage, wxObject)

    /* wxDrawControl */
    TClassDefExtend(wxDrawControl, wxControl) TClass(wxDrawControl)
        wxDrawControl_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height),
                             int style);

/* wxDrawWindow */
TClassDefExtend(wxDrawWindow, wxWindow) TClass(wxDrawWindow)
    wxDrawWindow_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height),
                        int style);

/* wxDropFilesEvent */
TClassDefExtend(wxDropFilesEvent, wxEvent)

    /* wxDropSource */
    TClassDef(wxDropSource) TClass(wxDropSource)
        DropSource_Create(TClass(wxDataObject) data, TClass(wxWindow) win, void* copy, void* move,
                          void* none);
void DropSource_Delete(TSelf(wxDropSource) pObject);
int DropSource_DoDragDrop(TSelf(wxDropSource) pObject, int move);

/* wxDropTarget */
TClassDef(wxDropTarget) void wxDropTarget_GetData(TSelf(wxDropTarget) pObject);
void wxDropTarget_SetDataObject(TSelf(wxDropTarget) pObject, TClass(wxDataObject) dataObject);

/* wxDynToolInfo */
TClassDefExtend(wxDynToolInfo,
                wxToolLayoutItem) int wxDynToolInfo_Index(TSelf(wxDynToolInfo) pObject);
void wxDynToolInfo_RealSize(TSelf(wxDynToolInfo) pObject, TSizeOutVoid(width, height));
void* wxDynToolInfo_pToolWnd(TSelf(wxDynToolInfo) pObject);

/* wxDynamicLibrary */
TClassDef(wxDynamicLibrary)

    /* wxDynamicSashWindow */
    TClassDefExtend(wxDynamicSashWindow, wxWindow) TClass(wxDynamicSashWindow)
        wxDynamicSashWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                                   int style);
void wxDynamicSashWindow_Delete(TSelf(wxDynamicSashWindow) pObject);
void* wxDynamicSashWindow_GetHScrollBar(TSelf(wxDynamicSashWindow) pObject, TClass(wxWindow) child);
void* wxDynamicSashWindow_GetVScrollBar(TSelf(wxDynamicSashWindow) pObject, TClass(wxWindow) child);

/* wxDynamicToolBar */
TClassDefExtend(wxDynamicToolBar,
                wxToolBarBase) void wxDynamicToolBar_AddSeparator(TSelf(wxDynamicToolBar) pObject,
                                                                  void* pSepartorWnd);
void wxDynamicToolBar_AddTool(TSelf(wxDynamicToolBar) pObject, int toolIndex, void* pToolWindow,
                              TSize(width, height));
void* wxDynamicToolBar_AddToolBitmap(TSelf(wxDynamicToolBar) pObject, int toolIndex,
                                     TClass(wxBitmap) bitmap, void* pushedBitmap, int toggle,
                                     TPoint(x, y), TClass(wxClientData) clientData,
                                     void* helpString1, void* helpString2);
void wxDynamicToolBar_AddToolImage(TSelf(wxDynamicToolBar) pObject, int toolIndex,
                                   void* imageFileName, int imageFileType, void* labelText,
                                   int alignTextRight, TBool isFlat);
void wxDynamicToolBar_AddToolLabel(TSelf(wxDynamicToolBar) pObject, int toolIndex, void* labelBmp,
                                   void* labelText, int alignTextRight, TBool isFlat);
TClass(wxDynamicToolBar)
    wxDynamicToolBar_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style,
                            int orientation, int RowsOrColumns);
TClass(wxDynamicToolBar) wxDynamicToolBar_CreateDefault();
void* wxDynamicToolBar_CreateDefaultLayout(TSelf(wxDynamicToolBar) pObject);
int wxDynamicToolBar_CreateParams(TSelf(wxDynamicToolBar) pObject, TClass(wxWindow) parent, int id,
                                  TRect(x, y, width, height), int style, int orientation,
                                  int RowsOrColumns);
void* wxDynamicToolBar_CreateTool(TSelf(wxDynamicToolBar) pObject, int id, void* label,
                                  void* bmpNormal, void* bmpDisabled, int kind,
                                  TClass(wxClientData) clientData, void* shortHelp, void* longHelp);
void* wxDynamicToolBar_CreateToolControl(TSelf(wxDynamicToolBar) pObject,
                                         TClass(wxControl) control);
void wxDynamicToolBar_Delete(TSelf(wxDynamicToolBar) pObject);
int wxDynamicToolBar_DoDeleteTool(TSelf(wxDynamicToolBar) pObject, int pos, void* tool);
void wxDynamicToolBar_DoEnableTool(TSelf(wxDynamicToolBar) pObject, void* tool, TBool enable);
int wxDynamicToolBar_DoInsertTool(TSelf(wxDynamicToolBar) pObject, int pos, void* tool);
void wxDynamicToolBar_DoSetToggle(TSelf(wxDynamicToolBar) pObject, void* tool, int toggle);
void wxDynamicToolBar_DoToggleTool(TSelf(wxDynamicToolBar) pObject, void* tool, int toggle);
void wxDynamicToolBar_DrawSeparator(TSelf(wxDynamicToolBar) pObject, void* info, TClass(wxDC) dc);
void wxDynamicToolBar_EnableTool(TSelf(wxDynamicToolBar) pObject, int toolIndex, TBool enable);
void* wxDynamicToolBar_FindToolForPosition(TSelf(wxDynamicToolBar) pObject, TPoint(x, y));
void wxDynamicToolBar_GetPreferredDim(TSelf(wxDynamicToolBar) pObject, int givenWidth,
                                      int givenHeight, void* preferredWidth, void* preferredHeight);
void* wxDynamicToolBar_GetToolInfo(TSelf(wxDynamicToolBar) pObject, int toolIndex);
int wxDynamicToolBar_Layout(TSelf(wxDynamicToolBar) pObject);
void wxDynamicToolBar_RemoveTool(TSelf(wxDynamicToolBar) pObject, int toolIndex);
void wxDynamicToolBar_SetLayout(TSelf(wxDynamicToolBar) pObject, void* pLayout);

/* wxEditableListBox */
TClassDefExtend(wxEditableListBox, wxPanel) TClass(wxEditableListBox)
    wxEditableListBox_Create(TClass(wxWindow) parent, int id, TStringVoid label,
                             TRect(x, y, width, height), int style);
void* wxEditableListBox_GetDelButton(TSelf(wxEditableListBox) pObject);
void* wxEditableListBox_GetDownButton(TSelf(wxEditableListBox) pObject);
void* wxEditableListBox_GetEditButton(TSelf(wxEditableListBox) pObject);
TClass(wxListCtrl) wxEditableListBox_GetListCtrl(TSelf(wxEditableListBox) pObject);
void* wxEditableListBox_GetNewButton(TSelf(wxEditableListBox) pObject);
TArrayLen wxEditableListBox_GetStrings(TSelf(wxEditableListBox) pObject, TArrayStringOutVoid ref);
void* wxEditableListBox_GetUpButton(TSelf(wxEditableListBox) pObject);
void wxEditableListBox_SetStrings(TSelf(wxEditableListBox) pObject, void* strings, int count);

/* wxEncodingConverter */
TClassDefExtend(wxEncodingConverter,
                wxObject) void wxEncodingConverter_Convert(TSelf(wxEncodingConverter) pObject,
                                                           void* input, void* output);
TClass(wxEncodingConverter) wxEncodingConverter_Create();
void wxEncodingConverter_Delete(TSelf(wxEncodingConverter) pObject);
int wxEncodingConverter_GetAllEquivalents(TSelf(wxEncodingConverter) pObject, int enc,
                                          TClass(wxList) list);
int wxEncodingConverter_GetPlatformEquivalents(TSelf(wxEncodingConverter) pObject, int enc,
                                               int platform, TClass(wxList) list);
int wxEncodingConverter_Init(TSelf(wxEncodingConverter) pObject, int input_enc, int output_enc,
                             int method);

/* wxEraseEvent */
TClassDefExtend(wxEraseEvent, wxEvent) void wxEraseEvent_CopyObject(TSelf(wxEraseEvent) pObject,
                                                                    void* obj);
TClass(wxDC) wxEraseEvent_GetDC(TSelf(wxEraseEvent) pObject);

/* wxEvent */
TClassDefExtend(wxEvent, wxObject) void wxEvent_CopyObject(TSelf(wxEvent) pObject,
                                                           void* object_dest);
TClass(wxObject) wxEvent_GetEventObject(TSelf(wxEvent) pObject);
int wxEvent_GetEventType(TSelf(wxEvent) pObject);
int wxEvent_GetId(TSelf(wxEvent) pObject);
TBool wxEvent_GetSkipped(TSelf(wxEvent) pObject);
int wxEvent_GetTimestamp(TSelf(wxEvent) pObject);
TBool wxEvent_IsCommandEvent(TSelf(wxEvent) pObject);
int wxEvent_NewEventType();
void wxEvent_SetEventObject(TSelf(wxEvent) pObject, TClass(wxObject) obj);
void wxEvent_SetEventType(TSelf(wxEvent) pObject, int typ);
void wxEvent_SetId(TSelf(wxEvent) pObject, int Id);
void wxEvent_SetTimestamp(TSelf(wxEvent) pObject, int timestamp);
void wxEvent_Skip(TSelf(wxEvent) pObject, TBool skip);

/* wxEvtHandler */
TClassDefExtend(wxEvtHandler, wxObject) void wxEvtHandler_AddPendingEvent(TSelf(wxEvtHandler)
                                                                              pObject,
                                                                          TClass(wxEvent) event);
int wxEvtHandler_Connect(TSelf(wxEvtHandler) pObject, int first, int last, int type, void* data);
TClass(wxEvtHandler) wxEvtHandler_Create();
void wxEvtHandler_Delete(TSelf(wxEvtHandler) pObject);
int wxEvtHandler_Disconnect(TSelf(wxEvtHandler) pObject, int first, int last, int type, int id);
TBool wxEvtHandler_GetEvtHandlerEnabled(TSelf(wxEvtHandler) pObject);
TClass(wxEvtHandler) wxEvtHandler_GetNextHandler(TSelf(wxEvtHandler) pObject);
TClass(wxEvtHandler) wxEvtHandler_GetPreviousHandler(TSelf(wxEvtHandler) pObject);
TBool wxEvtHandler_ProcessEvent(TSelf(wxEvtHandler) pObject, TClass(wxEvent) event);
void wxEvtHandler_ProcessPendingEvents(TSelf(wxEvtHandler) pObject);
void wxEvtHandler_SetEvtHandlerEnabled(TSelf(wxEvtHandler) pObject, TBool enabled);
void wxEvtHandler_SetNextHandler(TSelf(wxEvtHandler) pObject, TClass(wxEvtHandler) handler);
void wxEvtHandler_SetPreviousHandler(TSelf(wxEvtHandler) pObject, TClass(wxEvtHandler) handler);

/* wxExpr */
TClassDef(wxExpr)

    /* wxExprDatabase */
    TClassDefExtend(wxExprDatabase, wxList)

    /* wxFFile */
    TClassDef(wxFFile)

    /* wxFFileInputStream */
    TClassDefExtend(wxFFileInputStream, wxInputStream)

    /* wxFFileOutputStream */
    TClassDefExtend(wxFFileOutputStream, wxOutputStream)

    /* wxFSFile */
    TClassDefExtend(wxFSFile, wxObject)

    /* wxFTP */
    TClassDefExtend(wxFTP, wxProtocol)

    /* wxFileDataObject */
    TClassDefExtend(wxFileDataObject,
                    wxDataObjectSimple) void FileDataObject_AddFile(TSelf(wxFileDataObject) pObject,
                                                                    TClass(wxString) files);
TClass(wxFileDataObject) FileDataObject_Create(TArrayString(count, list));
void FileDataObject_Delete(TSelf(wxFileDataObject) pObject);
TArrayLen FileDataObject_GetFilenames(TSelf(wxFileDataObject) pObject, TArrayStringOutVoid list);

/* wxFileDialog */
TClassDefExtend(wxFileDialog, wxDialog) TClass(wxFileDialog)
    wxFileDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                        TClass(wxString) directory, TClass(wxString) files,
                        TClass(wxString) weekday, TPoint(left, top), int style, TSize(sz_w, sz_h));
TClass(wxString) wxFileDialog_GetDirectory(TSelf(wxFileDialog) pObject);
TClass(wxString) wxFileDialog_GetFilename(TSelf(wxFileDialog) pObject);
TArrayLen wxFileDialog_GetFilenames(TSelf(wxFileDialog) pObject, TArrayStringOutVoid paths);
int wxFileDialog_GetFilterIndex(TSelf(wxFileDialog) pObject);
TClass(wxString) wxFileDialog_GetMessage(TSelf(wxFileDialog) pObject);
TClass(wxString) wxFileDialog_GetPath(TSelf(wxFileDialog) pObject);
TArrayLen wxFileDialog_GetPaths(TSelf(wxFileDialog) pObject, TArrayStringOutVoid paths);
int wxFileDialog_GetStyle(TSelf(wxFileDialog) pObject);
TClass(wxString) wxFileDialog_GetWildcard(TSelf(wxFileDialog) pObject);
void wxFileDialog_SetDirectory(TSelf(wxFileDialog) pObject, TClass(wxString) dir);
void wxFileDialog_SetFilename(TSelf(wxFileDialog) pObject, TClass(wxString) name);
void wxFileDialog_SetFilterIndex(TSelf(wxFileDialog) pObject, int filterIndex);
void wxFileDialog_SetMessage(TSelf(wxFileDialog) pObject, TClass(wxString) message);
void wxFileDialog_SetPath(TSelf(wxFileDialog) pObject, TClass(wxString) path);
void wxFileDialog_SetStyle(TSelf(wxFileDialog) pObject, int style);
void wxFileDialog_SetWildcard(TSelf(wxFileDialog) pObject, TClass(wxString) wildCard);

/* wxFileCtrl */
TClassDefExtend(wxFileCtrl, wxControl) TClass(wxFileCtrl)
    wxFileCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxString) defaultDirectory,
                      TClass(wxString) defaultFilename, TClass(wxString) wildCard,
                      TRect(x, y, width, height), int style);
TClass(wxString) wxFileCtrl_GetDirectory(TSelf(wxFileCtrl) self);
TClass(wxString) wxFileCtrl_GetFilename(TSelf(wxFileCtrl) self);
void wxFileCtrl_GetFilenames(TSelf(wxFileCtrl) self, TClass(wxArrayString) filenames);
int wxFileCtrl_GetFilterIndex(TSelf(wxFileCtrl) self);
TClass(wxString) wxFileCtrl_GetPath(TSelf(wxFileCtrl) self);
void wxFileCtrl_GetPaths(TSelf(wxFileCtrl) self, TClass(wxArrayString) paths);
TClass(wxString) wxFileCtrl_GetWildcard(TSelf(wxFileCtrl) self);
TBool wxFileCtrl_SetDirectory(TSelf(wxFileCtrl) self, TClass(wxString) directory);
TBool wxFileCtrl_SetFilename(TSelf(wxFileCtrl) self, TClass(wxString) filename);
TBool wxFileCtrl_SetPath(TSelf(wxFileCtrl) self, TClass(wxString) path);
void wxFileCtrl_SetFilterIndex(TSelf(wxFileCtrl) self, int filterIndex);
void wxFileCtrl_SetWildcard(TSelf(wxFileCtrl) self, TClass(wxString) wildCard);
void wxFileCtrl_ShowHidden(TSelf(wxFileCtrl) self, TBool show);

/* wxFileDropTarget */
TClassDefExtend(wxFileDropTarget, wxDropTarget)

    /* wxFileHistory */
    TClassDefExtend(wxFileHistory,
                    wxObject) void wxFileHistory_AddFileToHistory(TSelf(wxFileHistory) pObject,
                                                                  TClass(wxString) file);
void wxFileHistory_AddFilesToMenu(TSelf(wxFileHistory) pObject, TClass(wxMenu) menu);
TClass(wxFileHistory) wxFileHistory_Create(int maxFiles);
void wxFileHistory_Delete(TSelf(wxFileHistory) pObject);
int wxFileHistory_GetCount(TSelf(wxFileHistory) pObject);
TClass(wxString) wxFileHistory_GetHistoryFile(TSelf(wxFileHistory) pObject, int index);
int wxFileHistory_GetMaxFiles(TSelf(wxFileHistory) pObject);
TArrayLen wxFileHistory_GetMenus(TSelf(wxFileHistory) pObject, TArrayObjectOutVoid(wxMenu) ref);
void wxFileHistory_Load(TSelf(wxFileHistory) pObject, TClass(wxConfigBase) config);
void wxFileHistory_RemoveFileFromHistory(TSelf(wxFileHistory) pObject, int index);
void wxFileHistory_RemoveMenu(TSelf(wxFileHistory) pObject, TClass(wxMenu) menu);
void wxFileHistory_Save(TSelf(wxFileHistory) pObject, TClass(wxConfigBase) config);
void wxFileHistory_UseMenu(TSelf(wxFileHistory) pObject, TClass(wxMenu) menu);

/* wxFileInputStream */
TClassDefExtend(wxFileInputStream, wxInputStream)

    /* wxFileName */
    TClassDef(wxFileName)

    /* wxFileOutputStream */
    TClassDefExtend(wxFileOutputStream, wxOutputStream)

    /* wxFileSystem */
    TClassDefExtend(wxFileSystem, wxObject)

    /* wxFileSystemHandler */
    TClassDefExtend(wxFileSystemHandler, wxObject)

    /* wxFileType */
    TClassDef(wxFileType) void wxFileType_Delete(TSelf(wxFileType) pObject);
TClass(wxString) wxFileType_ExpandCommand(TSelf(wxFileType) pObject, void* command, void* params);
TClass(wxString) wxFileType_GetDescription(TSelf(wxFileType) pObject);
int wxFileType_GetExtensions(TSelf(wxFileType) pObject, TClass(wxList) list);
int wxFileType_GetIcon(TSelf(wxFileType) pObject, TClass(wxIcon) icon);
TClass(wxString) wxFileType_GetMimeType(TSelf(wxFileType) pObject);
int wxFileType_GetMimeTypes(TSelf(wxFileType) pObject, TClass(wxList) list);
int wxFileType_GetOpenCommand(TSelf(wxFileType) pObject, void* buffer, void* params);
int wxFileType_GetPrintCommand(TSelf(wxFileType) pObject, void* buffer, void* params);

/* wxFilterInputStream */
TClassDefExtend(wxFilterInputStream, wxInputStream)

    /* wxFilterOutputStream */
    TClassDefExtend(wxFilterOutputStream, wxOutputStream)

    /* wxFindDialogEvent */
    TClassDefExtend(wxFindDialogEvent,
                    wxCommandEvent) int wxFindDialogEvent_GetFindString(TSelf(wxFindDialogEvent)
                                                                            pObject,
                                                                        void* ref);
int wxFindDialogEvent_GetFlags(TSelf(wxFindDialogEvent) pObject);
int wxFindDialogEvent_GetReplaceString(TSelf(wxFindDialogEvent) pObject, void* ref);

/* wxFindReplaceData */
TClassDefExtend(wxFindReplaceData, wxObject) TClass(wxFindReplaceData)
    wxFindReplaceData_Create(int flags);
TClass(wxFindReplaceData) wxFindReplaceData_CreateDefault();
void wxFindReplaceData_Delete(TSelf(wxFindReplaceData) pObject);
TClass(wxString) wxFindReplaceData_GetFindString(TSelf(wxFindReplaceData) pObject);
int wxFindReplaceData_GetFlags(TSelf(wxFindReplaceData) pObject);
TClass(wxString) wxFindReplaceData_GetReplaceString(TSelf(wxFindReplaceData) pObject);
void wxFindReplaceData_SetFindString(TSelf(wxFindReplaceData) pObject, TClass(wxString) str);
void wxFindReplaceData_SetFlags(TSelf(wxFindReplaceData) pObject, int flags);
void wxFindReplaceData_SetReplaceString(TSelf(wxFindReplaceData) pObject, TClass(wxString) str);

/* wxFindReplaceDialog */
TClassDefExtend(wxFindReplaceDialog, wxDialog) TClass(wxFindReplaceDialog)
    wxFindReplaceDialog_Create(TClass(wxWindow) parent, TClass(wxFindReplaceData) data,
                               TClass(wxString) title, int style);
TClass(wxFindReplaceData) wxFindReplaceDialog_GetData(TSelf(wxFindReplaceDialog) pObject);
void wxFindReplaceDialog_SetData(TSelf(wxFindReplaceDialog) pObject,
                                 TClass(wxFindReplaceData) data);

/* wxFlexGridSizer */
TClassDefExtend(wxFlexGridSizer,
                wxGridSizer) void wxFlexGridSizer_AddGrowableCol(TSelf(wxFlexGridSizer) pObject,
                                                                 size_t idx, int proportion);
void wxFlexGridSizer_AddGrowableRow(TSelf(wxFlexGridSizer) pObject, size_t idx, int proportion);
TClass(wxSize) wxFlexGridSizer_CalcMin(TSelf(wxFlexGridSizer) pObject);
TClass(wxFlexGridSizer) wxFlexGridSizer_Create(int rows, int cols, int vgap, int hgap);
void wxFlexGridSizer_RecalcSizes(TSelf(wxFlexGridSizer) pObject);
void wxFlexGridSizer_RemoveGrowableCol(TSelf(wxFlexGridSizer) pObject, size_t idx);
void wxFlexGridSizer_RemoveGrowableRow(TSelf(wxFlexGridSizer) pObject, size_t idx);

/* wxFocusEvent */
TClassDefExtend(wxFocusEvent, wxEvent)

    /* wxFont */
    TClassDefExtend(wxFont, wxGDIObject) TClass(wxFont)
        wxFont_Create(int pointSize, int family, int style, int weight, TBool underlined,
                      TClass(wxString) face, int enc);
TClass(wxFont) wxFont_CreateFromStock(int id);
TClass(wxFont) wxFont_CreateDefault();
void wxFont_Delete(TSelf(wxFont) pObject);
int wxFont_GetDefaultEncoding(TSelf(wxFont) pObject);
int wxFont_GetEncoding(TSelf(wxFont) pObject);
TClass(wxString) wxFont_GetFaceName(TSelf(wxFont) pObject);
int wxFont_GetFamily(TSelf(wxFont) pObject);
TClass(wxString) wxFont_GetFamilyString(TSelf(wxFont) pObject);
int wxFont_GetPointSize(TSelf(wxFont) pObject);
int wxFont_GetStyle(TSelf(wxFont) pObject);
TClass(wxString) wxFont_GetStyleString(TSelf(wxFont) pObject);
int wxFont_GetUnderlined(TSelf(wxFont) pObject);
int wxFont_GetWeight(TSelf(wxFont) pObject);
TClass(wxString) wxFont_GetWeightString(TSelf(wxFont) pObject);
TBool wxFont_IsOk(TSelf(wxFont) pObject);
void wxFont_SetDefaultEncoding(TSelf(wxFont) pObject, int encoding);
void wxFont_SetEncoding(TSelf(wxFont) pObject, int encoding);
void wxFont_SetFaceName(TSelf(wxFont) pObject, TClass(wxString) faceName);
void wxFont_SetFamily(TSelf(wxFont) pObject, int family);
void wxFont_SetPointSize(TSelf(wxFont) pObject, int pointSize);
void wxFont_SetStyle(TSelf(wxFont) pObject, int style);
void wxFont_SetUnderlined(TSelf(wxFont) pObject, int underlined);
void wxFont_SetWeight(TSelf(wxFont) pObject, int weight);

/* wxFontData */
TClassDefExtend(wxFontData, wxObject) TClass(wxFontData) wxFontData_Create();
void wxFontData_Delete(TSelf(wxFontData) pObject);
void wxFontData_EnableEffects(TSelf(wxFontData) pObject, TBool flag);
TBool wxFontData_GetAllowSymbols(TSelf(wxFontData) pObject);
void wxFontData_GetChosenFont(TSelf(wxFontData) pObject, TClassRef(wxFont) ref);
void wxFontData_GetColour(TSelf(wxFontData) pObject, TClassRef(wxColour) ref);
TBool wxFontData_GetEnableEffects(TSelf(wxFontData) pObject);
int wxFontData_GetEncoding(TSelf(wxFontData) pObject);
void wxFontData_GetInitialFont(TSelf(wxFontData) pObject, TClassRef(wxFont) ref);
int wxFontData_GetShowHelp(TSelf(wxFontData) pObject);
void wxFontData_SetAllowSymbols(TSelf(wxFontData) pObject, TBool flag);
void wxFontData_SetChosenFont(TSelf(wxFontData) pObject, TClass(wxFont) font);
void wxFontData_SetColour(TSelf(wxFontData) pObject, TClass(wxColour) colour);
void wxFontData_SetEncoding(TSelf(wxFontData) pObject, int encoding);
void wxFontData_SetInitialFont(TSelf(wxFontData) pObject, TClass(wxFont) font);
void wxFontData_SetRange(TSelf(wxFontData) pObject, int minRange, int maxRange);
void wxFontData_SetShowHelp(TSelf(wxFontData) pObject, TBool flag);

/* wxFontDialog */
TClassDefExtend(wxFontDialog, wxDialog) TClass(wxFontDialog)
    wxFontDialog_Create(TClass(wxWindow) parent, TClass(wxFontData) fnt);
void wxFontDialog_GetFontData(TSelf(wxFontDialog) pObject, TClassRef(wxFontData) ref);

/* wxFontEnumerator */
TClassDef(wxFontEnumerator) TClass(wxFontEnumerator)
    wxFontEnumerator_Create(void* pObject, void* pFunction);
void wxFontEnumerator_Delete(TSelf(wxFontEnumerator) pObject);
TBool wxFontEnumerator_EnumerateEncodings(TSelf(wxFontEnumerator) pObject,
                                          TClass(wxString) facename);
TBool wxFontEnumerator_EnumerateFacenames(TSelf(wxFontEnumerator) pObject, int encoding,
                                          int fixedWidthOnly);

/* wxFontList */
TClassDefExtend(wxFontList, wxList)

    /* wxFontMapper */
    TClassDef(wxFontMapper) TClass(wxFontMapper) wxFontMapper_Create();
TBool wxFontMapper_GetAltForEncoding(TSelf(wxFontMapper) pObject, int encoding, void* alt_encoding,
                                     TClass(wxString) buffer);
TBool wxFontMapper_IsEncodingAvailable(TSelf(wxFontMapper) pObject, int encoding,
                                       TClass(wxString) buffer);

/* wxFrame */
TClassDefExtend(wxFrame, wxTopLevelWindow) TClass(wxFrame)
    wxFrame_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                   TRect(left, top, width, height), int style);
TClass(wxStatusBar) wxFrame_CreateStatusBar(TSelf(wxFrame) pObject, int number, int style);
TClass(wxToolBar) wxFrame_CreateToolBar(TSelf(wxFrame) pObject, long style);
int wxFrame_GetClientAreaOrigin_left(TSelf(wxFrame) pObject);
int wxFrame_GetClientAreaOrigin_top(TSelf(wxFrame) pObject);
TClass(wxMenuBar) wxFrame_GetMenuBar(TSelf(wxFrame) pObject);
TClass(wxStatusBar) wxFrame_GetStatusBar(TSelf(wxFrame) pObject);
TClass(wxToolBar) wxFrame_GetToolBar(TSelf(wxFrame) pObject);
void wxFrame_Restore(TSelf(wxFrame) pObject);
void wxFrame_SetMenuBar(TSelf(wxFrame) pObject, TClass(wxMenuBar) menubar);
void wxFrame_SetStatusBar(TSelf(wxFrame) pObject, TClass(wxStatusBar) statBar);
void wxFrame_SetStatusText(TSelf(wxFrame) pObject, TClass(wxString) text, int number);
void wxFrame_SetStatusWidths(TSelf(wxFrame) pObject, int count, void* widths);
void wxFrame_SetToolBar(TSelf(wxFrame) pObject, TClass(wxToolBar) toolbar);

/* wxFrameLayout */
TClassDefExtend(wxFrameLayout,
                wxEvtHandler) void wxFrameLayout_Activate(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_AddBar(TSelf(wxFrameLayout) pObject, void* pBarWnd, void* dimInfo, int alignment,
                          int rowNo, int columnPos, TStringVoid name, int spyEvents, int state);
void wxFrameLayout_AddPlugin(TSelf(wxFrameLayout) pObject, void* pPlInfo, int paneMask);
void wxFrameLayout_AddPluginBefore(TSelf(wxFrameLayout) pObject, void* pNextPlInfo, void* pPlInfo,
                                   int paneMask);
void wxFrameLayout_ApplyBarProperties(TSelf(wxFrameLayout) pObject, void* pBar);
void wxFrameLayout_CaptureEventsForPane(TSelf(wxFrameLayout) pObject, void* toPane);
void wxFrameLayout_CaptureEventsForPlugin(TSelf(wxFrameLayout) pObject, void* pPlugin);
TClass(wxFrameLayout) wxFrameLayout_Create(void* pParentFrame, void* pFrameClient, int activateNow);
void wxFrameLayout_Deactivate(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_Delete(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_DestroyBarWindows(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_EnableFloating(TSelf(wxFrameLayout) pObject, TBool enable);
void* wxFrameLayout_FindBarByName(TSelf(wxFrameLayout) pObject, TStringVoid name);
void* wxFrameLayout_FindBarByWindow(TSelf(wxFrameLayout) pObject, void* pWnd);
void* wxFrameLayout_FindPlugin(TSelf(wxFrameLayout) pObject, void* pPlInfo);
void wxFrameLayout_FirePluginEvent(TSelf(wxFrameLayout) pObject, TClass(wxEvent) event);
int wxFrameLayout_GetBars(TSelf(wxFrameLayout) pObject, void* ref);
int wxFrameLayout_GetClientHeight(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_GetClientRect(TSelf(wxFrameLayout) pObject, TRectOutVoid(x, y, width, height));
int wxFrameLayout_GetClientWidth(TSelf(wxFrameLayout) pObject);
void* wxFrameLayout_GetFrameClient(TSelf(wxFrameLayout) pObject);
void* wxFrameLayout_GetPane(TSelf(wxFrameLayout) pObject, int alignment);
void wxFrameLayout_GetPaneProperties(TSelf(wxFrameLayout) pObject, void* props, int alignment);
void* wxFrameLayout_GetParentFrame(TSelf(wxFrameLayout) pObject);
void* wxFrameLayout_GetTopPlugin(TSelf(wxFrameLayout) pObject);
void* wxFrameLayout_GetUpdatesManager(TSelf(wxFrameLayout) pObject);
TBool wxFrameLayout_HasTopPlugin(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_HideBarWindows(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_InverseVisibility(TSelf(wxFrameLayout) pObject, void* pBar);
void wxFrameLayout_OnLButtonDown(TSelf(wxFrameLayout) pObject, TClass(wxEvent) event);
void wxFrameLayout_OnLButtonUp(TSelf(wxFrameLayout) pObject, TClass(wxEvent) event);
void wxFrameLayout_OnLDblClick(TSelf(wxFrameLayout) pObject, TClass(wxEvent) event);
void wxFrameLayout_OnMouseMove(TSelf(wxFrameLayout) pObject, TClass(wxEvent) event);
void wxFrameLayout_OnRButtonDown(TSelf(wxFrameLayout) pObject, TClass(wxEvent) event);
void wxFrameLayout_OnRButtonUp(TSelf(wxFrameLayout) pObject, TClass(wxEvent) event);
void wxFrameLayout_OnSize(TSelf(wxFrameLayout) pObject, TClass(wxEvent) event);
void wxFrameLayout_PopAllPlugins(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_PopPlugin(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_PushDefaultPlugins(TSelf(wxFrameLayout) pObject);
void wxFrameLayout_PushPlugin(TSelf(wxFrameLayout) pObject, void* pPugin);
void wxFrameLayout_RecalcLayout(TSelf(wxFrameLayout) pObject, int repositionBarsNow);
int wxFrameLayout_RedockBar(TSelf(wxFrameLayout) pObject, void* pBar, TRect(x, y, width, height),
                            void* pToPane, int updateNow);
void wxFrameLayout_RefreshNow(TSelf(wxFrameLayout) pObject, int recalcLayout);
void wxFrameLayout_ReleaseEventsFromPane(TSelf(wxFrameLayout) pObject, void* fromPane);
void wxFrameLayout_ReleaseEventsFromPlugin(TSelf(wxFrameLayout) pObject, void* pPlugin);
void wxFrameLayout_RemoveBar(TSelf(wxFrameLayout) pObject, void* pBar);
void wxFrameLayout_RemovePlugin(TSelf(wxFrameLayout) pObject, void* pPlInfo);
void wxFrameLayout_SetBarState(TSelf(wxFrameLayout) pObject, void* pBar, int newStatem,
                               int updateNow);
void wxFrameLayout_SetFrameClient(TSelf(wxFrameLayout) pObject, void* pFrameClient);
void wxFrameLayout_SetMargins(TSelf(wxFrameLayout) pObject, int top, int bottom, int left,
                              int right, int paneMask);
void wxFrameLayout_SetPaneBackground(TSelf(wxFrameLayout) pObject, TClass(wxColour) colour);
void wxFrameLayout_SetPaneProperties(TSelf(wxFrameLayout) pObject, void* props, int paneMask);
void wxFrameLayout_SetTopPlugin(TSelf(wxFrameLayout) pObject, void* pPlugin);
void wxFrameLayout_SetUpdatesManager(TSelf(wxFrameLayout) pObject, void* pUMgr);

/* wxGDIObject */
TClassDefExtend(wxGDIObject, wxObject)

    /* wxGLCanvas */
    TClassDefExtend(wxGLCanvas, wxScrolledWindow)

    /* wxGauge */
    TClassDefExtend(wxGauge, wxControl) TClass(wxGauge)
        wxGauge_Create(TClass(wxWindow) parent, int id, int range, TRect(left, top, width, height),
                       int style);
int wxGauge_GetRange(TSelf(wxGauge) pObject);
int wxGauge_GetValue(TSelf(wxGauge) pObject);
void wxGauge_SetRange(TSelf(wxGauge) pObject, int range);
void wxGauge_SetValue(TSelf(wxGauge) pObject, int pos);

/* wxGenericDirCtrl */
TClassDefExtend(wxGenericDirCtrl, wxControl)

    /* wxGenericValidator */
    TClassDefExtend(wxGenericValidator, wxValidator)

    /* wxGrid */
    TClassDefExtend(wxGrid, wxScrolledWindow) TBool
    wxGrid_AppendCols(TSelf(wxGrid) pObject, int numCols, TBool updateLabels);
TBool wxGrid_AppendRows(TSelf(wxGrid) pObject, int numRows, TBool updateLabels);
void wxGrid_AutoSize(TSelf(wxGrid) pObject);
void wxGrid_AutoSizeColumn(TSelf(wxGrid) pObject, int col, TBoolInt setAsMin);
void wxGrid_AutoSizeColumns(TSelf(wxGrid) pObject, TBoolInt setAsMin);
void wxGrid_AutoSizeRow(TSelf(wxGrid) pObject, int row, TBoolInt setAsMin);
void wxGrid_AutoSizeRows(TSelf(wxGrid) pObject, TBoolInt setAsMin);
void wxGrid_BeginBatch(TSelf(wxGrid) pObject);
TClass(wxRect)
    wxGrid_BlockToDeviceRect(TSelf(wxGrid) pObject, int top, int left, int bottom, int right);
TBool wxGrid_CanDragColSize(TSelf(wxGrid) pObject, int col);
TBool wxGrid_CanDragGridSize(TSelf(wxGrid) pObject);
TBool wxGrid_CanDragRowSize(TSelf(wxGrid) pObject, int row);
TBool wxGrid_CanEnableCellControl(TSelf(wxGrid) pObject);
TClass(wxRect) wxGrid_CellToRect(TSelf(wxGrid) pObject, int row, int col);
void wxGrid_ClearGrid(TSelf(wxGrid) pObject);
void wxGrid_ClearSelection(TSelf(wxGrid) pObject);
TClass(wxGrid)
    wxGrid_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height), int style);
void wxGrid_CreateGrid(TSelf(wxGrid) pObject, int rows, int cols, int selmode);
TBool wxGrid_DeleteCols(TSelf(wxGrid) pObject, int pos, int numCols, TBool updateLabels);
TBool wxGrid_DeleteRows(TSelf(wxGrid) pObject, int pos, int numRows, TBool updateLabels);
void wxGrid_DisableCellEditControl(TSelf(wxGrid) pObject);
void wxGrid_DisableDragColSize(TSelf(wxGrid) pObject);
void wxGrid_DisableDragGridSize(TSelf(wxGrid) pObject);
void wxGrid_DisableDragRowSize(TSelf(wxGrid) pObject);
void wxGrid_DrawAllGridLines(TSelf(wxGrid) pObject, TClass(wxDC) dc, TClass(wxRegion) reg);
void wxGrid_DrawCell(TSelf(wxGrid) pObject, TClass(wxDC) dc, int row, int col);
void wxGrid_DrawCellBorder(TSelf(wxGrid) pObject, TClass(wxDC) dc, int row, int col);
void wxGrid_DrawCellHighlight(TSelf(wxGrid) pObject, TClass(wxDC) dc, TClass(wxGridCellAttr) attr);
void wxGrid_DrawColLabel(TSelf(wxGrid) pObject, TClass(wxDC) dc, int col);
void wxGrid_DrawColLabels(TSelf(wxGrid) pObject, TClass(wxDC) dc);
void wxGrid_DrawGridSpace(TSelf(wxGrid) pObject, TClass(wxDC) dc);
void wxGrid_DrawRowLabel(TSelf(wxGrid) pObject, TClass(wxDC) dc, int row);
void wxGrid_DrawRowLabels(TSelf(wxGrid) pObject, TClass(wxDC) dc);
void wxGrid_DrawTextRectangle(TSelf(wxGrid) pObject, TClass(wxDC) dc, TClass(wxString) txt,
                              TRect(x, y, width, height), int horizontalAlignment,
                              int verticalAlignment);
void wxGrid_EnableCellEditControl(TSelf(wxGrid) pObject, TBool enable);
void wxGrid_EnableDragColSize(TSelf(wxGrid) pObject, TBool enable);
void wxGrid_EnableDragGridSize(TSelf(wxGrid) pObject, TBool enable);
void wxGrid_EnableDragRowSize(TSelf(wxGrid) pObject, TBool enable);
void wxGrid_EnableEditing(TSelf(wxGrid) pObject, TBoolInt edit);
void wxGrid_EnableGridLines(TSelf(wxGrid) pObject, TBool enable);
void wxGrid_EndBatch(TSelf(wxGrid) pObject);
int wxGrid_GetBatchCount(TSelf(wxGrid) pObject);
void wxGrid_GetCellAlignment(TSelf(wxGrid) pObject, int row, int col, TSizeOut(horiz, vert));
void wxGrid_GetCellBackgroundColour(TSelf(wxGrid) pObject, int row, int col,
                                    TClass(wxColour) colour);
TClass(wxGridCellEditor) wxGrid_GetCellEditor(TSelf(wxGrid) pObject, int row, int col);
void wxGrid_GetCellFont(TSelf(wxGrid) pObject, int row, int col, TClass(wxFont) font);
void wxGrid_GetCellHighlightColour(TSelf(wxGrid) pObject, TClassRef(wxColour) ref);
TClass(wxGridCellRenderer) wxGrid_GetCellRenderer(TSelf(wxGrid) pObject, int row, int col);
void wxGrid_GetCellTextColour(TSelf(wxGrid) pObject, int row, int col, TClass(wxColour) colour);
TClass(wxString) wxGrid_GetCellValue(TSelf(wxGrid) pObject, int row, int col);
void wxGrid_GetColLabelAlignment(TSelf(wxGrid) pObject, TSizeOut(horiz, vert));
int wxGrid_GetColLabelSize(TSelf(wxGrid) pObject);
TClass(wxString) wxGrid_GetColLabelValue(TSelf(wxGrid) pObject, int col);
int wxGrid_GetColSize(TSelf(wxGrid) pObject, int col);
void wxGrid_GetDefaultCellAlignment(TSelf(wxGrid) pObject, TSizeOut(horiz, vert));
void wxGrid_GetDefaultCellBackgroundColour(TSelf(wxGrid) pObject, TClassRef(wxColour) ref);
void wxGrid_GetDefaultCellFont(TSelf(wxGrid) pObject, TClassRef(wxFont) ref);
void wxGrid_GetDefaultCellTextColour(TSelf(wxGrid) pObject, TClassRef(wxColour) ref);
int wxGrid_GetDefaultColLabelSize(TSelf(wxGrid) pObject);
int wxGrid_GetDefaultColSize(TSelf(wxGrid) pObject);
TClass(wxGridCellEditor) wxGrid_GetDefaultEditor(TSelf(wxGrid) pObject);
TClass(wxGridCellEditor) wxGrid_GetDefaultEditorForCell(TSelf(wxGrid) pObject, int row, int col);
TClass(wxGridCellEditor)
    wxGrid_GetDefaultEditorForType(TSelf(wxGrid) pObject, TClass(wxString) typeName);
TClass(wxGridCellRenderer) wxGrid_GetDefaultRenderer(TSelf(wxGrid) pObject);
TClass(wxGridCellRenderer)
    wxGrid_GetDefaultRendererForCell(TSelf(wxGrid) pObject, int row, int col);
TClass(wxGridCellRenderer)
    wxGrid_GetDefaultRendererForType(TSelf(wxGrid) pObject, TClass(wxString) typeName);
int wxGrid_GetDefaultRowLabelSize(TSelf(wxGrid) pObject);
int wxGrid_GetDefaultRowSize(TSelf(wxGrid) pObject);
int wxGrid_GetGridCursorCol(TSelf(wxGrid) pObject);
int wxGrid_GetGridCursorRow(TSelf(wxGrid) pObject);
void wxGrid_GetGridLineColour(TSelf(wxGrid) pObject, TClassRef(wxColour) ref);
void wxGrid_GetLabelBackgroundColour(TSelf(wxGrid) pObject, TClassRef(wxColour) ref);
void wxGrid_GetLabelFont(TSelf(wxGrid) pObject, TClassRef(wxFont) ref);
void wxGrid_GetLabelTextColour(TSelf(wxGrid) pObject, TClassRef(wxColour) ref);
int wxGrid_GetNumberCols(TSelf(wxGrid) pObject);
int wxGrid_GetNumberRows(TSelf(wxGrid) pObject);
void wxGrid_GetRowLabelAlignment(TSelf(wxGrid) pObject, TSizeOut(horiz, vert));
int wxGrid_GetRowLabelSize(TSelf(wxGrid) pObject);
TClass(wxString) wxGrid_GetRowLabelValue(TSelf(wxGrid) pObject, int row);
int wxGrid_GetRowSize(TSelf(wxGrid) pObject, int row);
void wxGrid_GetSelectionBackground(TSelf(wxGrid) pObject, TClassRef(wxColour) ref);
void wxGrid_GetSelectionForeground(TSelf(wxGrid) pObject, TClassRef(wxColour) ref);
TClass(wxGridTableBase) wxGrid_GetTable(TSelf(wxGrid) pObject);
void wxGrid_GetTextBoxSize(TSelf(wxGrid) pObject, TClass(wxDC) dc, TArrayString(count, lines),
                           TSizeOutVoid(width, height));
int wxGrid_GridLinesEnabled(TSelf(wxGrid) pObject);
void wxGrid_HideCellEditControl(TSelf(wxGrid) pObject);
TBool wxGrid_InsertCols(TSelf(wxGrid) pObject, int pos, int numCols, TBool updateLabels);
TBool wxGrid_InsertRows(TSelf(wxGrid) pObject, int pos, int numRows, TBool updateLabels);
TBool wxGrid_IsCellEditControlEnabled(TSelf(wxGrid) pObject);
TBool wxGrid_IsCellEditControlShown(TSelf(wxGrid) pObject);
TBool wxGrid_IsCurrentCellReadOnly(TSelf(wxGrid) pObject);
TBool wxGrid_IsEditable(TSelf(wxGrid) pObject);
TBool wxGrid_IsInSelection(TSelf(wxGrid) pObject, int row, int col);
TBool wxGrid_IsReadOnly(TSelf(wxGrid) pObject, int row, int col);
TBool wxGrid_IsSelection(TSelf(wxGrid) pObject);
TBool wxGrid_IsVisible(TSelf(wxGrid) pObject, int row, int col, TBool wholeCellVisible);
void wxGrid_MakeCellVisible(TSelf(wxGrid) pObject, int row, int col);
TBool wxGrid_MoveCursorDown(TSelf(wxGrid) pObject, TBool expandSelection);
TBool wxGrid_MoveCursorDownBlock(TSelf(wxGrid) pObject, TBool expandSelection);
TBool wxGrid_MoveCursorLeft(TSelf(wxGrid) pObject, TBool expandSelection);
TBool wxGrid_MoveCursorLeftBlock(TSelf(wxGrid) pObject, TBool expandSelection);
TBool wxGrid_MoveCursorRight(TSelf(wxGrid) pObject, TBool expandSelection);
TBool wxGrid_MoveCursorRightBlock(TSelf(wxGrid) pObject, TBool expandSelection);
TBool wxGrid_MoveCursorUp(TSelf(wxGrid) pObject, TBool expandSelection);
TBool wxGrid_MoveCursorUpBlock(TSelf(wxGrid) pObject, TBool expandSelection);
TBool wxGrid_MovePageDown(TSelf(wxGrid) pObject);
TBool wxGrid_MovePageUp(TSelf(wxGrid) pObject);
TBool wxGrid_ProcessTableMessage(TSelf(wxGrid) pObject, TClass(wxEvent) evt);
void wxGrid_RegisterDataType(TSelf(wxGrid) pObject, TClass(wxString) typeName,
                             TClass(wxGridCellRenderer) renderer, TClass(wxGridCellEditor) editor);
void wxGrid_SaveEditControlValue(TSelf(wxGrid) pObject);
void wxGrid_SelectAll(TSelf(wxGrid) pObject);
void wxGrid_SelectBlock(TSelf(wxGrid) pObject, int topRow, int leftCol, int bottomRow, int rightCol,
                        TBoolInt addToSelected);
void wxGrid_SelectCol(TSelf(wxGrid) pObject, int col, TBoolInt addToSelected);
void wxGrid_SelectRow(TSelf(wxGrid) pObject, int row, TBoolInt addToSelected);
void wxGrid_SetCellAlignment(TSelf(wxGrid) pObject, int row, int col, int horiz, int vert);
void wxGrid_SetCellBackgroundColour(TSelf(wxGrid) pObject, int row, int col,
                                    TClass(wxColour) colour);
void wxGrid_SetCellEditor(TSelf(wxGrid) pObject, int row, int col, TClass(wxGridCellEditor) editor);
void wxGrid_SetCellFont(TSelf(wxGrid) pObject, int row, int col, TClass(wxFont) font);
void wxGrid_SetCellHighlightColour(TSelf(wxGrid) pObject, TClass(wxColour) col);
void wxGrid_SetCellRenderer(TSelf(wxGrid) pObject, int row, int col,
                            TClass(wxGridCellRenderer) renderer);
void wxGrid_SetCellTextColour(TSelf(wxGrid) pObject, int row, int col, TClass(wxColour) colour);
void wxGrid_SetCellValue(TSelf(wxGrid) pObject, int row, int col, TClass(wxString) str);
void wxGrid_SetColAttr(TSelf(wxGrid) pObject, int col, TClass(wxGridCellAttr) attr);
void wxGrid_SetColFormatBool(TSelf(wxGrid) pObject, int col);
void wxGrid_SetColFormatCustom(TSelf(wxGrid) pObject, int col, TClass(wxString) typeName);
void wxGrid_SetColFormatFloat(TSelf(wxGrid) pObject, int col, int width, int precision);
void wxGrid_SetColFormatNumber(TSelf(wxGrid) pObject, int col);
void wxGrid_SetColLabelAlignment(TSelf(wxGrid) pObject, int horiz, int vert);
void wxGrid_SetColLabelSize(TSelf(wxGrid) pObject, int height);
void wxGrid_SetColLabelValue(TSelf(wxGrid) pObject, int col, TClass(wxString) label);
void wxGrid_SetColMinimalWidth(TSelf(wxGrid) pObject, int col, int width);
void wxGrid_SetColSize(TSelf(wxGrid) pObject, int col, int width);
void wxGrid_SetDefaultCellAlignment(TSelf(wxGrid) pObject, int horiz, int vert);
void wxGrid_SetDefaultCellBackgroundColour(TSelf(wxGrid) pObject, TClass(wxColour) colour);
void wxGrid_SetDefaultCellFont(TSelf(wxGrid) pObject, TClass(wxFont) font);
void wxGrid_SetDefaultCellTextColour(TSelf(wxGrid) pObject, TClass(wxColour) colour);
void wxGrid_SetDefaultColSize(TSelf(wxGrid) pObject, int width, TBoolInt resizeExistingCols);
void wxGrid_SetDefaultEditor(TSelf(wxGrid) pObject, TClass(wxGridCellEditor) editor);
void wxGrid_SetDefaultRenderer(TSelf(wxGrid) pObject, TClass(wxGridCellRenderer) renderer);
void wxGrid_SetDefaultRowSize(TSelf(wxGrid) pObject, int height, TBoolInt resizeExistingRows);
void wxGrid_SetGridCursor(TSelf(wxGrid) pObject, int row, int col);
void wxGrid_SetGridLineColour(TSelf(wxGrid) pObject, TClass(wxColour) col);
void wxGrid_SetLabelBackgroundColour(TSelf(wxGrid) pObject, TClass(wxColour) colour);
void wxGrid_SetLabelFont(TSelf(wxGrid) pObject, TClass(wxFont) font);
void wxGrid_SetLabelTextColour(TSelf(wxGrid) pObject, TClass(wxColour) colour);
void wxGrid_SetMargins(TSelf(wxGrid) pObject, int extraWidth, int extraHeight);
void wxGrid_SetReadOnly(TSelf(wxGrid) pObject, int row, int col, TBool isReadOnly);
void wxGrid_SetRowAttr(TSelf(wxGrid) pObject, int row, TClass(wxGridCellAttr) attr);
void wxGrid_SetRowLabelAlignment(TSelf(wxGrid) pObject, int horiz, int vert);
void wxGrid_SetRowLabelSize(TSelf(wxGrid) pObject, int width);
void wxGrid_SetRowLabelValue(TSelf(wxGrid) pObject, int row, TClass(wxString) label);
void wxGrid_SetRowMinimalHeight(TSelf(wxGrid) pObject, int row, int width);
void wxGrid_SetRowSize(TSelf(wxGrid) pObject, int row, int height);
void wxGrid_SetSelectionBackground(TSelf(wxGrid) pObject, TClass(wxColour) colour);
void wxGrid_SetSelectionForeground(TSelf(wxGrid) pObject, TClass(wxColour) colour);
void wxGrid_SetSelectionMode(TSelf(wxGrid) pObject, int selmode);
TBool wxGrid_SetTable(TSelf(wxGrid) pObject, TClass(wxGridTableBase) table, TBool takeOwnership,
                      int selmode);
void wxGrid_ShowCellEditControl(TSelf(wxGrid) pObject);
int wxGrid_StringToLines(TSelf(wxGrid) pObject, TClass(wxString) value, void* lines);
int wxGrid_XToCol(TSelf(wxGrid) pObject, int x, TBool clipToMinMax);
int wxGrid_XToEdgeOfCol(TSelf(wxGrid) pObject, int x);
void wxGrid_XYToCell(TSelf(wxGrid) pObject, TPoint(x, y), TPointOut(row, col));
int wxGrid_YToEdgeOfRow(TSelf(wxGrid) pObject, int y);
int wxGrid_YToRow(TSelf(wxGrid) pObject, int y, TBool clipToMinMax);
void wxGrid_GetSelectedCells(TSelf(wxGrid) pObject, TClassRef(wxGridCellCoordsArray) array);
void wxGrid_GetSelectionBlockTopLeft(TSelf(wxGrid) pObject, TClassRef(wxGridCellCoordsArray) array);
void wxGrid_GetSelectionBlockBottomRight(TSelf(wxGrid) pObject,
                                         TClassRef(wxGridCellCoordsArray) array);
TArrayLen wxGrid_GetSelectedRows(TSelf(wxGrid) pObject, TArrayIntOutVoid array);
TArrayLen wxGrid_GetSelectedCols(TSelf(wxGrid) pObject, TArrayIntOutVoid array);
void wxGrid_GetCellSize(TSelf(wxGrid) pObject, int row, int col, TSizeOut(srow, scol));
void wxGrid_SetCellSize(TSelf(wxGrid) pObject, int row, int col, TSize(srow, scol));

/* wxGridCellAttr */
TClassDef(wxGridCellAttr) TClass(wxGridCellAttr) wxGridCellAttr_Ctor();
void wxGridCellAttr_DecRef(TSelf(wxGridCellAttr) pObject);
void wxGridCellAttr_GetAlignment(TSelf(wxGridCellAttr) pObject, TSizeOut(hAlign, vAlign));
void wxGridCellAttr_GetBackgroundColour(TSelf(wxGridCellAttr) pObject, TClassRef(wxColour) ref);
TClass(wxGridCellEditor)
    wxGridCellAttr_GetEditor(TSelf(wxGridCellAttr) pObject, TClass(wxGrid) grid, int row, int col);
void wxGridCellAttr_GetFont(TSelf(wxGridCellAttr) pObject, TClassRef(wxFont) ref);
TClass(wxGridCellRenderer) wxGridCellAttr_GetRenderer(TSelf(wxGridCellAttr) pObject,
                                                      TClass(wxGrid) grid, int row, int col);
void wxGridCellAttr_GetTextColour(TSelf(wxGridCellAttr) pObject, TClassRef(wxColour) ref);
TBool wxGridCellAttr_HasAlignment(TSelf(wxGridCellAttr) pObject);
TBool wxGridCellAttr_HasBackgroundColour(TSelf(wxGridCellAttr) pObject);
TBool wxGridCellAttr_HasEditor(TSelf(wxGridCellAttr) pObject);
TBool wxGridCellAttr_HasFont(TSelf(wxGridCellAttr) pObject);
TBool wxGridCellAttr_HasRenderer(TSelf(wxGridCellAttr) pObject);
TBool wxGridCellAttr_HasTextColour(TSelf(wxGridCellAttr) pObject);
void wxGridCellAttr_IncRef(TSelf(wxGridCellAttr) pObject);
TBool wxGridCellAttr_IsReadOnly(TSelf(wxGridCellAttr) pObject);
void wxGridCellAttr_SetAlignment(TSelf(wxGridCellAttr) pObject, int hAlign, int vAlign);
void wxGridCellAttr_SetBackgroundColour(TSelf(wxGridCellAttr) pObject, TClass(wxColour) colBack);
void wxGridCellAttr_SetDefAttr(TSelf(wxGridCellAttr) pObject, TClass(wxGridCellAttr) defAttr);
void wxGridCellAttr_SetEditor(TSelf(wxGridCellAttr) pObject, TClass(wxGridCellEditor) editor);
void wxGridCellAttr_SetFont(TSelf(wxGridCellAttr) pObject, TClass(wxFont) font);
void wxGridCellAttr_SetReadOnly(TSelf(wxGridCellAttr) pObject, TBool isReadOnly);
void wxGridCellAttr_SetRenderer(TSelf(wxGridCellAttr) pObject, TClass(wxGridCellRenderer) renderer);
void wxGridCellAttr_SetTextColour(TSelf(wxGridCellAttr) pObject, TClass(wxColour) colText);

/* wxGridCellBoolEditor */
TClassDefExtend(wxGridCellBoolEditor, wxGridCellEditor) TClass(wxGridCellBoolEditor)
    wxGridCellBoolEditor_Ctor();

/* wxGridCellBoolRenderer */
TClassDefExtend(wxGridCellBoolRenderer, wxGridCellRenderer)

    /* wxGridCellChoiceEditor */
    TClassDefExtend(wxGridCellChoiceEditor, wxGridCellEditor) TClass(wxGridCellChoiceEditor)
        wxGridCellChoiceEditor_Ctor(TArrayString(count, choices), TBoolInt allowOthers);

/* wxGridCellCoordsArray */
TClassDef(wxGridCellCoordsArray) TClass(wxGridCellCoordsArray) wxGridCellCoordsArray_Create();
void wxGridCellCoordsArray_Delete(TSelf(wxGridCellCoordsArray) pObject);
int wxGridCellCoordsArray_GetCount(TSelf(wxGridCellCoordsArray) pObject);
void wxGridCellCoordsArray_Item(TSelf(wxGridCellCoordsArray) pObject, int index,
                                TPointOut(col, row));

/* wxGridCellEditor */
TClassDefExtend(wxGridCellEditor,
                wxGridCellWorker) void wxGridCellEditor_BeginEdit(TSelf(wxGridCellEditor) pObject,
                                                                  int row, int col,
                                                                  TClass(wxGrid) grid);
void wxGridCellEditor_Create(TSelf(wxGridCellEditor) pObject, TClass(wxWindow) parent, int id,
                             TClass(wxEvtHandler) evtHandler);
void wxGridCellEditor_Destroy(TSelf(wxGridCellEditor) pObject);
int wxGridCellEditor_EndEdit(TSelf(wxGridCellEditor) pObject, int row, int col, TClass(wxGrid) grid,
                             TClass(wxString) oldStr, TClass(wxString) newStr);
TClass(wxControl) wxGridCellEditor_GetControl(TSelf(wxGridCellEditor) pObject);
void wxGridCellEditor_HandleReturn(TSelf(wxGridCellEditor) pObject, TClass(wxEvent) event);
TBool wxGridCellEditor_IsAcceptedKey(TSelf(wxGridCellEditor) pObject, TClass(wxEvent) event);
TBool wxGridCellEditor_IsCreated(TSelf(wxGridCellEditor) pObject);
void wxGridCellEditor_PaintBackground(TSelf(wxGridCellEditor) pObject, TClass(wxDC) dc,
                                      TRect(x, y, width, height), TClass(wxGridCellAttr) attr);
void wxGridCellEditor_Reset(TSelf(wxGridCellEditor) pObject);
void wxGridCellEditor_SetControl(TSelf(wxGridCellEditor) pObject, TClass(wxControl) control);
void wxGridCellEditor_SetParameters(TSelf(wxGridCellEditor) pObject, TClass(wxString) params);
void wxGridCellEditor_SetSize(TSelf(wxGridCellEditor) pObject, TRect(x, y, width, height));
void wxGridCellEditor_Show(TSelf(wxGridCellEditor) pObject, TBoolInt show,
                           TClass(wxGridCellAttr) attr);
void wxGridCellEditor_StartingClick(TSelf(wxGridCellEditor) pObject);
void wxGridCellEditor_StartingKey(TSelf(wxGridCellEditor) pObject, TClass(wxEvent) event);

/* wxGridCellFloatEditor */
TClassDefExtend(wxGridCellFloatEditor, wxGridCellTextEditor) TClass(wxGridCellFloatEditor)
    wxGridCellFloatEditor_Ctor(int width, int precision);

/* wxGridCellFloatRenderer */
TClassDefExtend(wxGridCellFloatRenderer, wxGridCellStringRenderer)

    /* wxGridCellNumberEditor */
    TClassDefExtend(wxGridCellNumberEditor, wxGridCellTextEditor) TClass(wxGridCellNumberEditor)
        wxGridCellNumberEditor_Ctor(int min, int max);

/* wxGridCellNumberRenderer */
TClassDefExtend(wxGridCellNumberRenderer, wxGridCellStringRenderer) TClass(wxGridCellNumberRenderer)
    wxGridCellNumberRenderer_Ctor();

/* wxGridCellAutoWrapStringRenderer */
TClassDefExtend(wxGridCellAutoWrapStringRenderer, wxGridCellStringRenderer)
    TClass(wxGridCellAutoWrapStringRenderer) wxGridCellAutoWrapStringRenderer_Ctor();

/* wxGridCellRenderer */
TClassDefExtend(wxGridCellRenderer, wxGridCellWorker)

    /* wxGridCellStringRenderer */
    TClassDefExtend(wxGridCellStringRenderer, wxGridCellRenderer)

    /* wxGridCellTextEditor */
    TClassDefExtend(wxGridCellTextEditor, wxGridCellEditor) TClass(wxGridCellTextEditor)
        wxGridCellTextEditor_Ctor();

/* wxGridCellWorker */
TClassDef(wxGridCellWorker)

    /* wxGridEditorCreatedEvent */
    TClassDefExtend(wxGridEditorCreatedEvent, wxCommandEvent) int wxGridEditorCreatedEvent_GetCol(
        TSelf(wxGridEditorCreatedEvent) pObject);
TClass(wxControl) wxGridEditorCreatedEvent_GetControl(TSelf(wxGridEditorCreatedEvent) pObject);
int wxGridEditorCreatedEvent_GetRow(TSelf(wxGridEditorCreatedEvent) pObject);
void wxGridEditorCreatedEvent_SetCol(TSelf(wxGridEditorCreatedEvent) pObject, int col);
void wxGridEditorCreatedEvent_SetControl(TSelf(wxGridEditorCreatedEvent) pObject,
                                         TClass(wxControl) ctrl);
void wxGridEditorCreatedEvent_SetRow(TSelf(wxGridEditorCreatedEvent) pObject, int row);

/* wxGridEvent */
TClassDefExtend(wxGridEvent, wxNotifyEvent) TBool wxGridEvent_AltDown(TSelf(wxGridEvent) pObject);
TBool wxGridEvent_ControlDown(TSelf(wxGridEvent) pObject);
int wxGridEvent_GetCol(TSelf(wxGridEvent) pObject);
TClass(wxPoint) wxGridEvent_GetPosition(TSelf(wxGridEvent) pObject);
int wxGridEvent_GetRow(TSelf(wxGridEvent) pObject);
TBool wxGridEvent_MetaDown(TSelf(wxGridEvent) pObject);
TBool wxGridEvent_Selecting(TSelf(wxGridEvent) pObject);
TBool wxGridEvent_ShiftDown(TSelf(wxGridEvent) pObject);

/* wxGridRangeSelectEvent */
TClassDefExtend(wxGridRangeSelectEvent, wxNotifyEvent) void wxGridRangeSelectEvent_GetTopLeftCoords(
    TSelf(wxGridRangeSelectEvent) pObject, TPointOutVoid(col, row));
void wxGridRangeSelectEvent_GetBottomRightCoords(TSelf(wxGridRangeSelectEvent) pObject,
                                                 TPointOutVoid(col, row));
int wxGridRangeSelectEvent_GetTopRow(TSelf(wxGridRangeSelectEvent) pObject);
int wxGridRangeSelectEvent_GetBottomRow(TSelf(wxGridRangeSelectEvent) pObject);
int wxGridRangeSelectEvent_GetLeftCol(TSelf(wxGridRangeSelectEvent) pObject);
int wxGridRangeSelectEvent_GetRightCol(TSelf(wxGridRangeSelectEvent) pObject);
TBool wxGridRangeSelectEvent_Selecting(TSelf(wxGridRangeSelectEvent) pObject);
TBool wxGridRangeSelectEvent_ControlDown(TSelf(wxGridRangeSelectEvent) pObject);
TBool wxGridRangeSelectEvent_MetaDown(TSelf(wxGridRangeSelectEvent) pObject);
TBool wxGridRangeSelectEvent_ShiftDown(TSelf(wxGridRangeSelectEvent) pObject);
TBool wxGridRangeSelectEvent_AltDown(TSelf(wxGridRangeSelectEvent) pObject);

/* wxGridSizeEvent */
TClassDefExtend(wxGridSizeEvent,
                wxNotifyEvent) int wxGridSizeEvent_GetRowOrCol(TSelf(wxGridSizeEvent) pObject);
TClass(wxPoint) wxGridSizeEvent_GetPosition(TSelf(wxGridSizeEvent) pObject);
TBool wxGridSizeEvent_ControlDown(TSelf(wxGridSizeEvent) pObject);
TBool wxGridSizeEvent_MetaDown(TSelf(wxGridSizeEvent) pObject);
TBool wxGridSizeEvent_ShiftDown(TSelf(wxGridSizeEvent) pObject);
TBool wxGridSizeEvent_AltDown(TSelf(wxGridSizeEvent) pObject);

/* wxGridSizer */
TClassDefExtend(wxGridSizer, wxSizer) TClass(wxSize)
    wxGridSizer_CalcMin(TSelf(wxGridSizer) pObject);
TClass(wxGridSizer) wxGridSizer_Create(int rows, int cols, int vgap, int hgap);
int wxGridSizer_GetCols(TSelf(wxGridSizer) pObject);
int wxGridSizer_GetHGap(TSelf(wxGridSizer) pObject);
int wxGridSizer_GetRows(TSelf(wxGridSizer) pObject);
int wxGridSizer_GetVGap(TSelf(wxGridSizer) pObject);
void wxGridSizer_RecalcSizes(TSelf(wxGridSizer) pObject);
void wxGridSizer_SetCols(TSelf(wxGridSizer) pObject, int cols);
void wxGridSizer_SetHGap(TSelf(wxGridSizer) pObject, int gap);
void wxGridSizer_SetRows(TSelf(wxGridSizer) pObject, int rows);
void wxGridSizer_SetVGap(TSelf(wxGridSizer) pObject, int gap);

/* wxGridBagSizer */
TClassDefExtend(wxGridBagSizer, wxGridSizer) TClass(wxGridBagSizer)
    wxGridBagSizer_Create(int vgap, int hgap);
TClass(wxSizerItem) wxGridBagSizer_AddWindow(TSelf(wxGridBagSizer) pObject, TClass(wxWindow) window,
                                             int row, int col, int rowspan, int colspan, int flag,
                                             int border, void* userData);
TClass(wxSizerItem)
    wxGridBagSizer_AddSizer(TSelf(wxGridBagSizer) pObject, TClass(wxSizer) sizer, int row, int col,
                            int rowspan, int colspan, int flag, int border, void* userData);
TClass(wxSizerItem)
    wxGridBagSizer_AddSpacer(TSelf(wxGridBagSizer) pObject, int width, int height, int row, int col,
                             int rowspan, int colspan, int flag, int border, void* userData);
void wxGridBagSizer_GetItemPosition(TSelf(wxGridBagSizer) pObject, TClass(wxWindow) window,
                                    int* row, int* col);
void wxGridBagSizer_GetItemPositionSizer(TSelf(wxGridBagSizer) pObject, TClass(wxSizer) sizer,
                                         int* row, int* col);
void wxGridBagSizer_GetItemPositionIndex(TSelf(wxGridBagSizer) pObject, size_t index, int* row,
                                         int* col);
TBool wxGridBagSizer_SetItemPosition(TSelf(wxGridBagSizer) pObject, TClass(wxWindow) window,
                                     int row, int col);
TBool wxGridBagSizer_SetItemPositionSizer(TSelf(wxGridBagSizer) pObject, TClass(wxSizer) sizer,
                                          int row, int col);
TBool wxGridBagSizer_SetItemPositionIndex(TSelf(wxGridBagSizer) pObject, size_t index, int row,
                                          int col);
void wxGridBagSizer_GetItemSpan(TSelf(wxGridBagSizer) pObject, TClass(wxWindow) window,
                                int* rowspan, int* colspan);
void wxGridBagSizer_GetItemSpanSizer(TSelf(wxGridBagSizer) pObject, TClass(wxSizer) sizer,
                                     int* rowspan, int* colspan);
void wxGridBagSizer_GetItemSpanIndex(TSelf(wxGridBagSizer) pObject, size_t index, int* rowspan,
                                     int* colspan);
TBool wxGridBagSizer_SetItemSpan(TSelf(wxGridBagSizer) pObject, TClass(wxWindow) window,
                                 int rowspan, int colspan);
TBool wxGridBagSizer_SetItemSpanSizer(TSelf(wxGridBagSizer) pObject, TClass(wxSizer) sizer,
                                      int rowspan, int colspan);
TBool wxGridBagSizer_SetItemSpanIndex(TSelf(wxGridBagSizer) pObject, size_t index, int rowspan,
                                      int colspan);
TClass(wxSizerItem)
    wxGridBagSizer_FindItemAtPosition(TSelf(wxGridBagSizer) pObject, int row, int col);
TBool wxGridBagSizer_CheckForIntersection(TSelf(wxGridBagSizer) pObject, TClass(wxGBSizerItem) item,
                                          TClass(wxGBSizerItem) excludeItem);
TBool wxGridBagSizer_CheckForIntersectionPos(TSelf(wxGridBagSizer) pObject, int row, int col,
                                             int rowspan, int colspan,
                                             TClass(wxGBSizerItem) excludeItem);
void wxGridBagSizer_GetEmptyCellSize(TSelf(wxGridBagSizer) pObject, int* width, int* height);
void wxGridBagSizer_SetEmptyCellSize(TSelf(wxGridBagSizer) pObject, int width, int height);

/* wxGridTableBase */
TClassDefExtend(wxGridTableBase, wxObject)

    /* wxHTTP */
    TClassDefExtend(wxHTTP, wxProtocol)

    /* wxHashMap */
    TClassDef(wxHashMap)

    /* wxHelpController */
    TClassDefExtend(wxHelpController, wxHelpControllerBase)

    /* wxHelpControllerBase */
    TClassDefExtend(wxHelpControllerBase, wxObject)

    /* wxHelpControllerHelpProvider */
    TClassDefExtend(wxHelpControllerHelpProvider, wxSimpleHelpProvider)
        TClass(wxHelpControllerHelpProvider)
            wxHelpControllerHelpProvider_Create(TClass(wxHelpControllerBase) ctr);
TClass(wxHelpControllerBase)
    wxHelpControllerHelpProvider_GetHelpController(TSelf(wxHelpControllerHelpProvider) pObject);
void wxHelpControllerHelpProvider_SetHelpController(TSelf(wxHelpControllerHelpProvider) pObject,
                                                    TClass(wxHelpController) helpController);

/* wxHelpEvent */
TClassDefExtend(wxHelpEvent, wxCommandEvent) TClass(wxString)
    wxHelpEvent_GetLink(TSelf(wxHelpEvent) pObject);
TClass(wxPoint) wxHelpEvent_GetPosition(TSelf(wxHelpEvent) pObject);
TClass(wxString) wxHelpEvent_GetTarget(TSelf(wxHelpEvent) pObject);
void wxHelpEvent_SetLink(TSelf(wxHelpEvent) pObject, TClass(wxString) link);
void wxHelpEvent_SetPosition(TSelf(wxHelpEvent) pObject, TPoint(x, y));
void wxHelpEvent_SetTarget(TSelf(wxHelpEvent) pObject, TClass(wxString) target);

/* wxHelpProvider */
TClassDef(wxHelpProvider) void wxHelpProvider_AddHelp(TSelf(wxHelpProvider) pObject,
                                                      TClass(wxWindow) window,
                                                      TClass(wxString) text);
void wxHelpProvider_AddHelpById(TSelf(wxHelpProvider) pObject, int id, TClass(wxString) text);
void wxHelpProvider_Delete(TSelf(wxHelpProvider) pObject);
TSelf(wxHelpProvider) wxHelpProvider_Get();
TClass(wxString) wxHelpProvider_GetHelp(TSelf(wxHelpProvider) pObject, TClass(wxWindow) window);
void wxHelpProvider_RemoveHelp(TSelf(wxHelpProvider) pObject, TClass(wxWindow) window);
TSelf(wxHelpProvider) wxHelpProvider_Set(TSelf(wxHelpProvider) helpProvider);
TBool wxHelpProvider_ShowHelp(TSelf(wxHelpProvider) pObject, TClass(wxWindow) window);

/* wxHtmlCell */
TClassDefExtend(wxHtmlCell, wxObject)

    /* wxHtmlColourCell */
    TClassDefExtend(wxHtmlColourCell, wxHtmlCell)

    /* wxHtmlContainerCell */
    TClassDefExtend(wxHtmlContainerCell, wxHtmlCell)

    /* wxHtmlDCRenderer */
    TClassDefExtend(wxHtmlDCRenderer, wxObject)

    /* wxHtmlEasyPrinting */
    TClassDefExtend(wxHtmlEasyPrinting, wxObject)

    /* wxHtmlFilter */
    TClassDefExtend(wxHtmlFilter, wxObject)

    /* wxHtmlHelpController */
    TClassDefExtend(wxHtmlHelpController, wxHelpControllerBase) TBool
    wxHtmlHelpController_AddBook(TSelf(wxHtmlHelpController) pObject, void* book,
                                 int show_wait_msg);
TClass(wxHtmlHelpController) wxHtmlHelpController_Create(int style, TClass(wxWindow) parentWindow);
void wxHtmlHelpController_Delete(TSelf(wxHtmlHelpController) pObject);
int wxHtmlHelpController_Display(TSelf(wxHtmlHelpController) pObject, void* x);
TBool wxHtmlHelpController_DisplayBlock(TSelf(wxHtmlHelpController) pObject, int blockNo);
int wxHtmlHelpController_DisplayContents(TSelf(wxHtmlHelpController) pObject);
int wxHtmlHelpController_DisplayIndex(TSelf(wxHtmlHelpController) pObject);
int wxHtmlHelpController_DisplayNumber(TSelf(wxHtmlHelpController) pObject, int id);
TBool wxHtmlHelpController_DisplaySection(TSelf(wxHtmlHelpController) pObject,
                                          TClass(wxString) section);
TBool wxHtmlHelpController_DisplaySectionNumber(TSelf(wxHtmlHelpController) pObject, int sectionNo);
TClass(wxFrame) wxHtmlHelpController_GetFrame(TSelf(wxHtmlHelpController) pObject);
void* wxHtmlHelpController_GetFrameParameters(TSelf(wxHtmlHelpController) pObject, void* title,
                                              int* width, int* height, int* pos_x, int* pos_y,
                                              int* newFrameEachTime);
TBool wxHtmlHelpController_Initialize(TSelf(wxHtmlHelpController) pObject, TClass(wxString) file);
TBool wxHtmlHelpController_KeywordSearch(TSelf(wxHtmlHelpController) pObject,
                                         TClass(wxString) keyword);
TBool wxHtmlHelpController_LoadFile(TSelf(wxHtmlHelpController) pObject, TClass(wxString) file);
TBool wxHtmlHelpController_Quit(TSelf(wxHtmlHelpController) pObject);
void wxHtmlHelpController_ReadCustomization(TSelf(wxHtmlHelpController) pObject,
                                            TClass(wxConfigBase) cfg, TClass(wxString) path);
void wxHtmlHelpController_SetFrameParameters(TSelf(wxHtmlHelpController) pObject, void* title,
                                             TSize(width, height), int pos_x, int pos_y,
                                             TBool newFrameEachTime);
void wxHtmlHelpController_SetTempDir(TSelf(wxHtmlHelpController) pObject, TClass(wxString) path);
void wxHtmlHelpController_SetTitleFormat(TSelf(wxHtmlHelpController) pObject, void* format);
void wxHtmlHelpController_SetViewer(TSelf(wxHtmlHelpController) pObject, TClass(wxString) viewer,
                                    int flags);
void wxHtmlHelpController_UseConfig(TSelf(wxHtmlHelpController) pObject,
                                    TClass(wxConfigBase) config, TClass(wxString) rootpath);
void wxHtmlHelpController_WriteCustomization(TSelf(wxHtmlHelpController) pObject,
                                             TClass(wxConfigBase) cfg, TClass(wxString) path);

/* wxHtmlHelpData */
TClassDefExtend(wxHtmlHelpData, wxObject)

    /* wxHtmlHelpFrame */
    TClassDefExtend(wxHtmlHelpFrame, wxFrame)

    /* wxHtmlLinkInfo */
    TClassDefExtend(wxHtmlLinkInfo, wxObject)

    /* wxHtmlParser */
    TClassDefExtend(wxHtmlParser, wxObject)

    /* wxHtmlPrintout */
    TClassDefExtend(wxHtmlPrintout, wxPrintout)

    /* wxHtmlTag */
    TClassDefExtend(wxHtmlTag, wxObject)

    /* wxHtmlTagHandler */
    TClassDefExtend(wxHtmlTagHandler, wxObject)

    /* wxHtmlTagsModule */
    TClassDefExtend(wxHtmlTagsModule, wxModule)

    /* wxHtmlWidgetCell */
    TClassDefExtend(wxHtmlWidgetCell, wxHtmlCell)

    /* wxHtmlWinParser */
    TClassDefExtend(wxHtmlWinParser, wxHtmlParser)

    /* wxHtmlWinTagHandler */
    TClassDefExtend(wxHtmlWinTagHandler, wxHtmlTagHandler)

    /* wxHtmlWindow */
    TClassDefExtend(wxHtmlWindow, wxScrolledWindow)

    /* wxIPV4address */
    TClassDefExtend(wxIPV4address, wxSockAddress)

    /* wxIcon */
    TClassDefExtend(wxIcon, wxBitmap) void wxIcon_Assign(TSelf(wxIcon) pObject, void* other);
void wxIcon_CopyFromBitmap(TSelf(wxIcon) pObject, TClass(wxBitmap) bmp);
TClass(wxIcon) wxIcon_CreateDefault();
TClass(wxIcon) wxIcon_CreateLoad(TClass(wxString) name, long type, TSize(width, height));
void wxIcon_Delete(TSelf(wxIcon) pObject);
TClass(wxIcon) wxIcon_FromRaw(TSelf(wxIcon) data, TSize(width, height));
TClass(wxIcon) wxIcon_FromXPM(TSelf(wxIcon) data);
int wxIcon_GetDepth(TSelf(wxIcon) pObject);
int wxIcon_GetHeight(TSelf(wxIcon) pObject);
int wxIcon_GetWidth(TSelf(wxIcon) pObject);
TBool wxIcon_IsEqual(TSelf(wxIcon) pObject, TSelf(wxIcon) other);
int wxIcon_Load(TSelf(wxIcon) pObject, TClass(wxString) name, long type, TSize(width, height));
TBool wxIcon_IsOk(TSelf(wxIcon) pObject);
void wxIcon_SetDepth(TSelf(wxIcon) pObject, int depth);
void wxIcon_SetHeight(TSelf(wxIcon) pObject, int height);
void wxIcon_SetWidth(TSelf(wxIcon) pObject, int width);

/* wxIconBundle */
TClassDef(wxIconBundle) void wxIconBundle_AddIcon(TSelf(wxIconBundle) pObject, TClass(wxIcon) icon);
void wxIconBundle_AddIconFromFile(TSelf(wxIconBundle) pObject, TClass(wxString) file, int type);
void wxIconBundle_Assign(TSelf(wxIconBundle) pObject, TClassRef(wxIconBundle) ref);
TClass(wxIconBundle) wxIconBundle_CreateDefault();
TClass(wxIconBundle) wxIconBundle_CreateFromFile(TClass(wxString) file, int type);
TClass(wxIconBundle) wxIconBundle_CreateFromIcon(TClass(wxIcon) icon);
void wxIconBundle_Delete(TSelf(wxIconBundle) pObject);
void wxIconBundle_GetIcon(TSelf(wxIconBundle) pObject, TSize(width, height), int flags,
                          TClassRef(wxIcon) ref);

/* wxIconizeEvent */
TClassDefExtend(wxIconizeEvent, wxEvent)

    /* wxIdleEvent */
    TClassDefExtend(wxIdleEvent, wxEvent) void wxIdleEvent_CopyObject(TSelf(wxIdleEvent) pObject,
                                                                      TClass(wxObject) object_dest);
TBool wxIdleEvent_MoreRequested(TSelf(wxIdleEvent) pObject);
void wxIdleEvent_RequestMore(TSelf(wxIdleEvent) pObject, TBool needMore);

/* wxImage */
TClassDefExtend(wxImage, wxObject) TBool wxImage_CanRead(TClass(wxString) name);
void wxImage_ConvertToBitmap(TSelf(wxImage) pObject, TClassRef(wxBitmap) bitmap);
TByteStringLen wxImage_ConvertToByteString(TSelf(wxImage) pObject, int type, TByteStringOut data);
TByteStringLen wxImage_ConvertToLazyByteString(TSelf(wxImage) pObject, int type,
                                               TByteStringLazyOut data);
int wxImage_CountColours(TSelf(wxImage) pObject, int stopafter);
void wxImage_Copy(TSelf(wxImage) pObject, TClassRef(wxImage) image);
TClass(wxImage) wxImage_CreateDefault();
TClass(wxImage) wxImage_CreateFromBitmap(TClass(wxBitmap) bitmap);
// TClass(wxImage) wxImage_CreateFromByteString( TByteString(data,length), int
// type );
TClass(wxImage) wxImage_CreateFromByteString(TSize(width, height), TByteString(data, length));
// TClass(wxImage) wxImage_CreateFromLazyByteString(
// TByteStringLazy(data,length), int type );
TClass(wxImage)
    wxImage_CreateFromLazyByteString(TSize(width, height), TByteStringLazy(data, length));
TClass(wxImage) wxImage_CreateFromData(TSize(width, height), void* data);
TClass(wxImage) wxImage_CreateFromFile(TClass(wxString) name);
TClass(wxImage) wxImage_CreateSized(TSize(width, height));
void wxImage_Destroy(TSelf(wxImage) pObject);
TChar wxImage_GetBlue(TSelf(wxImage) pObject, TPoint(x, y));
void* wxImage_GetData(TSelf(wxImage) pObject);
TChar wxImage_GetGreen(TSelf(wxImage) pObject, TPoint(x, y));
int wxImage_GetHeight(TSelf(wxImage) pObject);
TChar wxImage_GetMaskBlue(TSelf(wxImage) pObject);
TChar wxImage_GetMaskGreen(TSelf(wxImage) pObject);
TChar wxImage_GetMaskRed(TSelf(wxImage) pObject);
TChar wxImage_GetRed(TSelf(wxImage) pObject, TPoint(x, y));
void wxImage_GetSubImage(TSelf(wxImage) pObject, TRect(x, y, width, height),
                         TClassRef(wxImage) image);
int wxImage_GetType(TSelf(wxImage) pObject);
void wxImage_SetType(TSelf(wxImage) pObject, int type);
int wxImage_GetWidth(TSelf(wxImage) pObject);
TBool wxImage_HasMask(TSelf(wxImage) pObject);
TClass(wxString) wxImage_GetOption(TSelf(wxImage) pObject, TClass(wxString) name);
TBool wxImage_GetOptionInt(TSelf(wxImage) pObject, TClass(wxString) name);
TBool wxImage_HasOption(TSelf(wxImage) pObject, TClass(wxString) name);
void wxImage_Initialize(TSelf(wxImage) pObject, TSize(width, height), TBool clear);
void wxImage_InitializeFromData(TSelf(wxImage) pObject, TSize(width, height), void* data);
TBool wxImage_LoadFile(TSelf(wxImage) pObject, TClass(wxString) name, int type, int index);
TBool wxImage_LoadStream(TSelf(wxImage) pObject, TClass(wxInputStream) name, int type, int index);
void wxImage_Mirror(TSelf(wxImage) pObject, TBoolInt horizontally, TClassRef(wxImage) image);
TBool wxImage_IsOk(TSelf(wxImage) pObject);
void wxImage_Paste(TSelf(wxImage) pObject, TClass(wxImage) image, TPoint(x, y), int alphaBlend);
void wxImage_Replace(TSelf(wxImage) pObject, TColorRGB(r1, g1, b1), TColorRGB(r2, g2, b2));
void wxImage_Rescale(TSelf(wxImage) pObject, TSize(width, height));
void wxImage_RescaleEx(TSelf(wxImage) pObject, TSize(width, height), int quality);
void wxImage_Rotate(TSelf(wxImage) pObject, double angle, TPoint(c_x, c_y), TBoolInt interpolating,
                    void* offset_after_rotation, TClassRef(wxImage) image);
void wxImage_Rotate90(TSelf(wxImage) pObject, TBoolInt clockwise, TClassRef(wxImage) image);
TBool wxImage_SaveFile(TSelf(wxImage) pObject, TClass(wxString) name, int type);
TBool wxImage_SaveStream(TSelf(wxImage) pObject, TClass(wxOutputStream) stream, int type);
void wxImage_ScaleEx(TSelf(wxImage) pObject, TSize(width, height), int quality,
                     TClassRef(wxImage) image);
void wxImage_Scale(TSelf(wxImage) pObject, TSize(width, height), TClassRef(wxImage) image);
void wxImage_SetData(TSelf(wxImage) pObject, void* data, TBool static_data);
void wxImage_SetDataAndSize(TSelf(wxImage) pObject, void* data, TSize(new_width, new_height),
                            TBool static_data);
void wxImage_SetMask(TSelf(wxImage) pObject, int mask);
void wxImage_SetMaskColour(TSelf(wxImage) pObject, TColorRGB(r, g, b));
void wxImage_SetOption(TSelf(wxImage) pObject, TClass(wxString) name, TClass(wxString) value);
void wxImage_SetOptionInt(TSelf(wxImage) pObject, TClass(wxString) name, int value);
void wxImage_SetRGB(TSelf(wxImage) pObject, TPoint(x, y), TColorRGB(r, g, b));

/* wxImageHandler */
TClassDefExtend(wxImageHandler, wxObject)

    /* wxImageList */
    TClassDefExtend(wxImageList, wxObject) int wxImageList_AddBitmap(TSelf(wxImageList) pObject,
                                                                     TClass(wxBitmap) bitmap,
                                                                     TClass(wxBitmap) mask);
int wxImageList_AddIcon(TSelf(wxImageList) pObject, TClass(wxIcon) icon);
int wxImageList_AddMasked(TSelf(wxImageList) pObject, TClass(wxBitmap) bitmap,
                          TClass(wxColour) maskColour);
TClass(wxImageList) wxImageList_Create(TSize(width, height), TBoolInt mask, int initialCount);
void wxImageList_Delete(TSelf(wxImageList) pObject);
TBool wxImageList_Draw(TSelf(wxImageList) pObject, int index, TClass(wxDC) dc, TPoint(x, y),
                       int flags, TBool solidBackground);
int wxImageList_GetImageCount(TSelf(wxImageList) pObject);
void wxImageList_GetSize(TSelf(wxImageList) pObject, int index, TSizeOut(width, height));
TBool wxImageList_Remove(TSelf(wxImageList) pObject, int index);
TBool wxImageList_RemoveAll(TSelf(wxImageList) pObject);
TBool wxImageList_Replace(TSelf(wxImageList) pObject, int index, TClass(wxBitmap) bitmap,
                          TClass(wxBitmap) mask);
TBool wxImageList_ReplaceIcon(TSelf(wxImageList) pObject, int index, TClass(wxIcon) icon);

/* wxInfoBar */
TClassDef(wxInfoBar) TClass(wxInfoBar) wxInfoBar_Create(TClass(wxWindow) parent, int id);
void wxInfoBar_AddButton(TSelf(wxInfoBar) self, int btnid, TClass(wxString) label);
void wxInfoBar_Dismiss(TSelf(wxInfoBar) self);
size_t wxInfoBar_GetButtonCount(TSelf(wxInfoBar) self);
int wxInfoBar_GetButtonId(TSelf(wxInfoBar) self, int idx);
int wxInfoBar_GetEffectDuration(TSelf(wxInfoBar) self);
int wxInfoBar_GetShowEffect(TSelf(wxInfoBar) self);
int wxInfoBar_GetHideEffect(TSelf(wxInfoBar) self);
TBool wxInfoBar_HasFlag(TSelf(wxInfoBar) self, int flag);
void wxInfoBar_RemoveButton(TSelf(wxInfoBar) self, int btnid);
void wxInfoBar_SetEffectDuration(TSelf(wxInfoBar) self, int duration);
void wxInfoBar_SetShowHideEffects(TSelf(wxInfoBar) self, int showEffect, int hideEffect);
void wxInfoBar_ShowMessage(TSelf(wxInfoBar) self, TClass(wxString) msg, int flags);

/* wxIndividualLayoutConstraint */
TClassDefExtend(wxIndividualLayoutConstraint, wxObject) void wxIndividualLayoutConstraint_Above(
    TSelf(wxIndividualLayoutConstraint) pObject, TClass(wxWindow) sibling, int marg);
void wxIndividualLayoutConstraint_Absolute(TSelf(wxIndividualLayoutConstraint) pObject, int val);
void wxIndividualLayoutConstraint_AsIs(TSelf(wxIndividualLayoutConstraint) pObject);
void wxIndividualLayoutConstraint_Below(TSelf(wxIndividualLayoutConstraint) pObject,
                                        TClass(wxWindow) sibling, int marg);
TBool wxIndividualLayoutConstraint_GetDone(TSelf(wxIndividualLayoutConstraint) pObject);
int wxIndividualLayoutConstraint_GetEdge(TSelf(wxIndividualLayoutConstraint) pObject, int which,
                                         void* thisWin, void* other);
int wxIndividualLayoutConstraint_GetMargin(TSelf(wxIndividualLayoutConstraint) pObject);
int wxIndividualLayoutConstraint_GetMyEdge(TSelf(wxIndividualLayoutConstraint) pObject);
int wxIndividualLayoutConstraint_GetOtherEdge(TSelf(wxIndividualLayoutConstraint) pObject);
void* wxIndividualLayoutConstraint_GetOtherWindow(TSelf(wxIndividualLayoutConstraint) pObject);
int wxIndividualLayoutConstraint_GetPercent(TSelf(wxIndividualLayoutConstraint) pObject);
int wxIndividualLayoutConstraint_GetRelationship(TSelf(wxIndividualLayoutConstraint) pObject);
int wxIndividualLayoutConstraint_GetValue(TSelf(wxIndividualLayoutConstraint) pObject);
void wxIndividualLayoutConstraint_LeftOf(TSelf(wxIndividualLayoutConstraint) pObject,
                                         TClass(wxWindow) sibling, int marg);
void wxIndividualLayoutConstraint_PercentOf(TSelf(wxIndividualLayoutConstraint) pObject,
                                            TClass(wxWindow) otherW, int which, int per);
TBool wxIndividualLayoutConstraint_ResetIfWin(TSelf(wxIndividualLayoutConstraint) pObject,
                                              TClass(wxWindow) otherW);
void wxIndividualLayoutConstraint_RightOf(TSelf(wxIndividualLayoutConstraint) pObject,
                                          TClass(wxWindow) sibling, int marg);
void wxIndividualLayoutConstraint_SameAs(TSelf(wxIndividualLayoutConstraint) pObject,
                                         TClass(wxWindow) otherW, int edge, int marg);
TBool wxIndividualLayoutConstraint_SatisfyConstraint(TSelf(wxIndividualLayoutConstraint) pObject,
                                                     void* constraints, TClass(wxWindow) win);
void wxIndividualLayoutConstraint_Set(TSelf(wxIndividualLayoutConstraint) pObject, int rel,
                                      TClass(wxWindow) otherW, int otherE, int val, int marg);
void wxIndividualLayoutConstraint_SetDone(TSelf(wxIndividualLayoutConstraint) pObject, TBool done);
void wxIndividualLayoutConstraint_SetEdge(TSelf(wxIndividualLayoutConstraint) pObject, int which);
void wxIndividualLayoutConstraint_SetMargin(TSelf(wxIndividualLayoutConstraint) pObject,
                                            int margin);
void wxIndividualLayoutConstraint_SetRelationship(TSelf(wxIndividualLayoutConstraint) pObject,
                                                  int relationship);
void wxIndividualLayoutConstraint_SetValue(TSelf(wxIndividualLayoutConstraint) pObject, int value);
void wxIndividualLayoutConstraint_Unconstrained(TSelf(wxIndividualLayoutConstraint) pObject);

/* wxInitDialogEvent */
TClassDefExtend(wxInitDialogEvent, wxEvent)

    /* wxInputStream */
    TClassDefExtend(wxInputStream,
                    wxStreamBase) void wxInputStream_Delete(TSelf(wxInputStream) pObject);
TBool wxInputStream_Eof(TSelf(wxInputStream) pObject);
TChar wxInputStream_GetC(TSelf(wxInputStream) pObject);
int wxInputStream_LastRead(TSelf(wxInputStream) pObject);
TChar wxInputStream_Peek(TSelf(wxInputStream) pObject);
void wxInputStream_Read(TSelf(wxInputStream) pObject, void* buffer, int size);
int wxInputStream_SeekI(TSelf(wxInputStream) pObject, int pos, int mode);
int wxInputStream_Tell(TSelf(wxInputStream) pObject);
int wxInputStream_UngetBuffer(TSelf(wxInputStream) pObject, void* buffer, int size);
int wxInputStream_Ungetch(TSelf(wxInputStream) pObject, TChar character);

/* wxJoystick */
TClassDefExtend(wxJoystick, wxObject) TClass(wxJoystick) wxJoystick_Create(int joystick);
void wxJoystick_Delete(TSelf(wxJoystick) pObject);
int wxJoystick_GetButtonState(TSelf(wxJoystick) pObject);
int wxJoystick_GetManufacturerId(TSelf(wxJoystick) pObject);
int wxJoystick_GetMaxAxes(TSelf(wxJoystick) pObject);
int wxJoystick_GetMaxButtons(TSelf(wxJoystick) pObject);
int wxJoystick_GetMovementThreshold(TSelf(wxJoystick) pObject);
int wxJoystick_GetNumberAxes(TSelf(wxJoystick) pObject);
int wxJoystick_GetNumberButtons(TSelf(wxJoystick) pObject);
int wxJoystick_GetNumberJoysticks(TSelf(wxJoystick) pObject);
int wxJoystick_GetPOVCTSPosition(TSelf(wxJoystick) pObject);
int wxJoystick_GetPOVPosition(TSelf(wxJoystick) pObject);
int wxJoystick_GetPollingMax(TSelf(wxJoystick) pObject);
int wxJoystick_GetPollingMin(TSelf(wxJoystick) pObject);
TClass(wxPoint) wxJoystick_GetPosition(TSelf(wxJoystick) pObject);
int wxJoystick_GetProductId(TSelf(wxJoystick) pObject);
TClass(wxString) wxJoystick_GetProductName(TSelf(wxJoystick) pObject);
int wxJoystick_GetRudderMax(TSelf(wxJoystick) pObject);
int wxJoystick_GetRudderMin(TSelf(wxJoystick) pObject);
int wxJoystick_GetRudderPosition(TSelf(wxJoystick) pObject);
int wxJoystick_GetUMax(TSelf(wxJoystick) pObject);
int wxJoystick_GetUMin(TSelf(wxJoystick) pObject);
int wxJoystick_GetUPosition(TSelf(wxJoystick) pObject);
int wxJoystick_GetVMax(TSelf(wxJoystick) pObject);
int wxJoystick_GetVMin(TSelf(wxJoystick) pObject);
int wxJoystick_GetVPosition(TSelf(wxJoystick) pObject);
int wxJoystick_GetXMax(TSelf(wxJoystick) pObject);
int wxJoystick_GetXMin(TSelf(wxJoystick) pObject);
int wxJoystick_GetYMax(TSelf(wxJoystick) pObject);
int wxJoystick_GetYMin(TSelf(wxJoystick) pObject);
int wxJoystick_GetZMax(TSelf(wxJoystick) pObject);
int wxJoystick_GetZMin(TSelf(wxJoystick) pObject);
int wxJoystick_GetZPosition(TSelf(wxJoystick) pObject);
TBool wxJoystick_HasPOV(TSelf(wxJoystick) pObject);
TBool wxJoystick_HasPOV4Dir(TSelf(wxJoystick) pObject);
TBool wxJoystick_HasPOVCTS(TSelf(wxJoystick) pObject);
TBool wxJoystick_HasRudder(TSelf(wxJoystick) pObject);
TBool wxJoystick_HasU(TSelf(wxJoystick) pObject);
TBool wxJoystick_HasV(TSelf(wxJoystick) pObject);
TBool wxJoystick_HasZ(TSelf(wxJoystick) pObject);
TBool wxJoystick_IsOk(TSelf(wxJoystick) pObject);
int wxJoystick_ReleaseCapture(TSelf(wxJoystick) pObject);
int wxJoystick_SetCapture(TSelf(wxJoystick) pObject, TClass(wxWindow) win, int pollingFreq);
void wxJoystick_SetMovementThreshold(TSelf(wxJoystick) pObject, int threshold);

/* wxJoystickEvent */
TClassDefExtend(wxJoystickEvent, wxEvent) TBool
    wxJoystickEvent_ButtonDown(TSelf(wxJoystickEvent) pObject, int but);
TBool wxJoystickEvent_ButtonIsDown(TSelf(wxJoystickEvent) pObject, int but);
TBool wxJoystickEvent_ButtonUp(TSelf(wxJoystickEvent) pObject, int but);
void wxJoystickEvent_CopyObject(TSelf(wxJoystickEvent) pObject, void* obj);
int wxJoystickEvent_GetButtonChange(TSelf(wxJoystickEvent) pObject);
int wxJoystickEvent_GetButtonState(TSelf(wxJoystickEvent) pObject);
int wxJoystickEvent_GetJoystick(TSelf(wxJoystickEvent) pObject);
TClass(wxPoint) wxJoystickEvent_GetPosition(TSelf(wxJoystickEvent) pObject);
int wxJoystickEvent_GetZPosition(TSelf(wxJoystickEvent) pObject);
TBool wxJoystickEvent_IsButton(TSelf(wxJoystickEvent) pObject);
TBool wxJoystickEvent_IsMove(TSelf(wxJoystickEvent) pObject);
TBool wxJoystickEvent_IsZMove(TSelf(wxJoystickEvent) pObject);
void wxJoystickEvent_SetButtonChange(TSelf(wxJoystickEvent) pObject, int change);
void wxJoystickEvent_SetButtonState(TSelf(wxJoystickEvent) pObject, int state);
void wxJoystickEvent_SetJoystick(TSelf(wxJoystickEvent) pObject, int stick);
void wxJoystickEvent_SetPosition(TSelf(wxJoystickEvent) pObject, TPoint(x, y));
void wxJoystickEvent_SetZPosition(TSelf(wxJoystickEvent) pObject, int zPos);

/* wxKeyEvent */
TClassDefExtend(wxKeyEvent, wxEvent) TBool wxKeyEvent_AltDown(TSelf(wxKeyEvent) pObject);
TBool wxKeyEvent_ControlDown(TSelf(wxKeyEvent) pObject);
void wxKeyEvent_CopyObject(TSelf(wxKeyEvent) pObject, void* obj);
int wxKeyEvent_GetKeyCode(TSelf(wxKeyEvent) pObject);
TClass(wxPoint) wxKeyEvent_GetPosition(TSelf(wxKeyEvent) pObject);
int wxKeyEvent_GetX(TSelf(wxKeyEvent) pObject);
int wxKeyEvent_GetY(TSelf(wxKeyEvent) pObject);
int wxKeyEvent_GetModifiers(TSelf(wxKeyEvent) pObject);
TBool wxKeyEvent_HasModifiers(TSelf(wxKeyEvent) pObject);
TBool wxKeyEvent_MetaDown(TSelf(wxKeyEvent) pObject);
void wxKeyEvent_SetKeyCode(TSelf(wxKeyEvent) pObject, int code);
TBool wxKeyEvent_ShiftDown(TSelf(wxKeyEvent) pObject);

/* wxLEDNumberCtrl */
TClassDefExtend(wxLEDNumberCtrl, wxControl) TClass(wxLEDNumberCtrl)
    wxLEDNumberCtrl_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
int wxLEDNumberCtrl_GetAlignment(TSelf(wxLEDNumberCtrl) pObject);
int wxLEDNumberCtrl_GetDrawFaded(TSelf(wxLEDNumberCtrl) pObject);
int wxLEDNumberCtrl_GetValue(TSelf(wxLEDNumberCtrl) pObject, void* ref);
void wxLEDNumberCtrl_SetAlignment(TSelf(wxLEDNumberCtrl) pObject, int Alignment, int Redraw);
void wxLEDNumberCtrl_SetDrawFaded(TSelf(wxLEDNumberCtrl) pObject, int DrawFaded, int Redraw);
void wxLEDNumberCtrl_SetValue(TSelf(wxLEDNumberCtrl) pObject, void* Value, int Redraw);

/* wxLayoutAlgorithm */
TClassDefExtend(wxLayoutAlgorithm, wxObject) TClass(wxLayoutAlgorithm) wxLayoutAlgorithm_Create();
void wxLayoutAlgorithm_Delete(TSelf(wxLayoutAlgorithm) pObject);
TBool wxLayoutAlgorithm_LayoutFrame(TSelf(wxLayoutAlgorithm) pObject, TClass(wxFrame) frame,
                                    void* mainWindow);
TBool wxLayoutAlgorithm_LayoutMDIFrame(TSelf(wxLayoutAlgorithm) pObject, TClass(wxFrame) frame,
                                       TRect(x, y, width, height), int use);
TBool wxLayoutAlgorithm_LayoutWindow(TSelf(wxLayoutAlgorithm) pObject, TClass(wxFrame) frame,
                                     void* mainWindow);

/* wxLayoutConstraints */
TClassDefExtend(wxLayoutConstraints, wxObject) TClass(wxLayoutConstraints)
    wxLayoutConstraints_Create();
void* wxLayoutConstraints_bottom(TSelf(wxLayoutConstraints) pObject);
void* wxLayoutConstraints_centreX(TSelf(wxLayoutConstraints) pObject);
void* wxLayoutConstraints_centreY(TSelf(wxLayoutConstraints) pObject);
void* wxLayoutConstraints_height(TSelf(wxLayoutConstraints) pObject);
void* wxLayoutConstraints_left(TSelf(wxLayoutConstraints) pObject);
void* wxLayoutConstraints_right(TSelf(wxLayoutConstraints) pObject);
void* wxLayoutConstraints_top(TSelf(wxLayoutConstraints) pObject);
void* wxLayoutConstraints_width(TSelf(wxLayoutConstraints) pObject);

/* wxList */
TClassDefExtend(wxList, wxObject)

    /* wxListBox */
    TClassDefExtend(wxListBox, wxControl) void wxListBox_Append(TSelf(wxListBox) pObject,
                                                                TClass(wxString) item);
void wxListBox_AppendData(TSelf(wxListBox) pObject, TClass(wxString) item, void* data);
void wxListBox_Clear(TSelf(wxListBox) pObject);
TClass(wxListBox) wxListBox_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height),
                                   TArrayString(n, str), int style);
void wxListBox_Delete(TSelf(wxListBox) pObject, int index);
int wxListBox_FindString(TSelf(wxListBox) pObject, TClass(wxString) str);
TClass(wxClientData) wxListBox_GetClientData(TSelf(wxListBox) pObject, int index);
int wxListBox_GetCount(TSelf(wxListBox) pObject);
int wxListBox_GetSelection(TSelf(wxListBox) pObject);
int wxListBox_GetSelections(TSelf(wxListBox) pObject, int* aSelections, int allocated);
TClass(wxString) wxListBox_GetString(TSelf(wxListBox) pObject, int index);
void wxListBox_InsertItems(TSelf(wxListBox) pObject, void* items, int pos, int count);
TBool wxListBox_IsSelected(TSelf(wxListBox) pObject, int index);
void wxListBox_SetClientData(TSelf(wxListBox) pObject, int index, TClass(wxClientData) clientData);
void wxListBox_SetFirstItem(TSelf(wxListBox) pObject, int index);
void wxListBox_SetSelection(TSelf(wxListBox) pObject, int index, TBoolInt select);
void wxListBox_SetString(TSelf(wxListBox) pObject, int index, TClass(wxString) str);
void wxListBox_SetStringSelection(TSelf(wxListBox) pObject, TClass(wxString) str, TBool sel);

/* wxListCtrl */
TClassDefExtend(wxListCtrl, wxControl) TBool
    wxListCtrl_Arrange(TSelf(wxListCtrl) pObject, int flag);
void wxListCtrl_ClearAll(TSelf(wxListCtrl) pObject);
TClass(wxListCtrl)
    wxListCtrl_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height), int style);
TBool wxListCtrl_DeleteAllColumns(TSelf(wxListCtrl) pObject);
TBool wxListCtrl_DeleteAllItems(TSelf(wxListCtrl) pObject);
TBool wxListCtrl_DeleteColumn(TSelf(wxListCtrl) pObject, int col);
TBool wxListCtrl_DeleteItem(TSelf(wxListCtrl) pObject, int item);
void wxListCtrl_EditLabel(TSelf(wxListCtrl) pObject, int item);
TBool wxListCtrl_EndEditLabel(TSelf(wxListCtrl) pObject, int cancel);
TBool wxListCtrl_EnsureVisible(TSelf(wxListCtrl) pObject, int item);
int wxListCtrl_FindItem(TSelf(wxListCtrl) pObject, int start, TClass(wxString) str, TBool partial);
int wxListCtrl_FindItemByData(TSelf(wxListCtrl) pObject, int start, int data);
int wxListCtrl_FindItemByPosition(TSelf(wxListCtrl) pObject, int start, TPoint(x, y),
                                  int direction);
TBool wxListCtrl_GetColumn(TSelf(wxListCtrl) pObject, int col, TClass(wxListItem) item);
int wxListCtrl_GetColumnCount(TSelf(wxListCtrl) pObject);
int wxListCtrl_GetColumnWidth(TSelf(wxListCtrl) pObject, int col);
int wxListCtrl_GetCountPerPage(TSelf(wxListCtrl) pObject);
TClass(wxTextCtrl) wxListCtrl_GetEditControl(TSelf(wxListCtrl) pObject);
TClass(wxImageList) wxListCtrl_GetImageList(TSelf(wxListCtrl) pObject, int which);
TBool wxListCtrl_GetItem(TSelf(wxListCtrl) pObject, TClass(wxListItem) info);
int wxListCtrl_GetItemCount(TSelf(wxListCtrl) pObject);
int wxListCtrl_GetItemData(TSelf(wxListCtrl) pObject, int item);
TClass(wxFont) wxListCtrl_GetItemFont(TSelf(wxListCtrl) pObject, long item);
TClass(wxPoint) wxListCtrl_GetItemPosition(TSelf(wxListCtrl) pObject, int item);
TClass(wxRect) wxListCtrl_GetItemRect(TSelf(wxListCtrl) pObject, int item, int code);
TClass(wxSize) wxListCtrl_GetItemSpacing(TSelf(wxListCtrl) pObject, TBool isSmall);
int wxListCtrl_GetItemState(TSelf(wxListCtrl) pObject, int item, int stateMask);
TClass(wxString) wxListCtrl_GetItemText(TSelf(wxListCtrl) pObject, int item, int col);
int wxListCtrl_GetNextItem(TSelf(wxListCtrl) pObject, int item, int geometry, int state);
int wxListCtrl_GetSelectedItemCount(TSelf(wxListCtrl) pObject);
void wxListCtrl_GetTextColour(TSelf(wxListCtrl) pObject, TClassRef(wxColour) ref);
int wxListCtrl_GetTopItem(TSelf(wxListCtrl) pObject);
int wxListCtrl_HitTest(TSelf(wxListCtrl) pObject, TPoint(x, y), void* flags, long* pSubItem);
int wxListCtrl_InsertColumn(TSelf(wxListCtrl) pObject, int col, TClass(wxString) heading,
                            int format, int width);
int wxListCtrl_InsertColumnFromInfo(TSelf(wxListCtrl) pObject, int col, TClass(wxListItem) info);
int wxListCtrl_InsertItem(TSelf(wxListCtrl) pObject, TClass(wxListItem) info);
int wxListCtrl_InsertItemWithData(TSelf(wxListCtrl) pObject, int index, TClass(wxString) label);
int wxListCtrl_InsertItemWithImage(TSelf(wxListCtrl) pObject, int index, int imageIndex);
int wxListCtrl_InsertItemWithLabel(TSelf(wxListCtrl) pObject, int index, TClass(wxString) label,
                                   int imageIndex);
TBool wxListCtrl_IsVirtual(TSelf(wxListCtrl) pObject);
void wxListCtrl_RefreshItem(TSelf(wxListCtrl) pObject, long item);
TBool wxListCtrl_ScrollList(TSelf(wxListCtrl) pObject, TVector(dx, dy));
void wxListCtrl_SetBackgroundColour(TSelf(wxListCtrl) pObject, TClass(wxColour) col);
TBool wxListCtrl_SetColumn(TSelf(wxListCtrl) pObject, int col, TClass(wxListItem) item);
TBool wxListCtrl_SetColumnWidth(TSelf(wxListCtrl) pObject, int col, int width);
int wxListCtrl_SetForegroundColour(TSelf(wxListCtrl) pObject, TClass(wxColour) col);
void wxListCtrl_SetImageList(TSelf(wxListCtrl) pObject, TClass(wxImageList) imageList, int which);
TBool wxListCtrl_SetItem(TSelf(wxListCtrl) pObject, int index, int col, TClass(wxString) label,
                         int imageId);
TBool wxListCtrl_SetItemData(TSelf(wxListCtrl) pObject, int item, int data);
TBool wxListCtrl_SetItemFromInfo(TSelf(wxListCtrl) pObject, TClass(wxListItem) info);
TBool wxListCtrl_SetItemImage(TSelf(wxListCtrl) pObject, int item, int image, int selImage);
TBool wxListCtrl_SetItemPosition(TSelf(wxListCtrl) pObject, int item, TPoint(x, y));
TBool wxListCtrl_SetItemState(TSelf(wxListCtrl) pObject, int item, int state, int stateMask);
void wxListCtrl_SetItemText(TSelf(wxListCtrl) pObject, int item, TClass(wxString) str);
void wxListCtrl_SetSingleStyle(TSelf(wxListCtrl) pObject, int style, TBool add);
void wxListCtrl_SetTextColour(TSelf(wxListCtrl) pObject, TClass(wxColour) col);
void wxListCtrl_SetWindowStyleFlag(TSelf(wxListCtrl) pObject, int style);
TBool wxListCtrl_SortItems(TSelf(wxListCtrl) pObject, void* compareFunc, void* eif_obj);
void wxListCtrl_UpdateStyle(TSelf(wxListCtrl) pObject);

/* wxListEvent */
TClassDefExtend(wxListEvent, wxNotifyEvent) TBool wxListEvent_Cancelled(TSelf(wxListEvent) pObject);
int wxListEvent_GetCode(TSelf(wxListEvent) pObject);
int wxListEvent_GetColumn(TSelf(wxListEvent) pObject);
int wxListEvent_GetData(TSelf(wxListEvent) pObject);
int wxListEvent_GetImage(TSelf(wxListEvent) pObject);
int wxListEvent_GetIndex(TSelf(wxListEvent) pObject);
void wxListEvent_GetItem(TSelf(wxListEvent) pObject, TClassRef(wxListItem) ref);
TClass(wxString) wxListEvent_GetLabel(TSelf(wxListEvent) pObject);
int wxListEvent_GetMask(TSelf(wxListEvent) pObject);
/*
int        wxListEvent_GetOldIndex( TSelf(wxListEvent) pObject );
int        wxListEvent_GetOldItem( TSelf(wxListEvent) pObject );
*/
TClass(wxPoint) wxListEvent_GetPoint(TSelf(wxListEvent) pObject);
TClass(wxString) wxListEvent_GetText(TSelf(wxListEvent) pObject);

/* wxListItem */
TClassDefExtend(wxListItem, wxObject) void wxListItem_Clear(TSelf(wxListItem) pObject);
void wxListItem_ClearAttributes(TSelf(wxListItem) pObject);
TClass(wxListItem) wxListItem_Create();
void wxListItem_Delete(TSelf(wxListItem) pObject);
int wxListItem_GetAlign(TSelf(wxListItem) pObject);
void* wxListItem_GetAttributes(TSelf(wxListItem) pObject);
void wxListItem_GetBackgroundColour(TSelf(wxListItem) pObject, TClassRef(wxColour) ref);
int wxListItem_GetColumn(TSelf(wxListItem) pObject);
int wxListItem_GetData(TSelf(wxListItem) pObject);
void wxListItem_GetFont(TSelf(wxListItem) pObject, TClassRef(wxFont) ref);
int wxListItem_GetId(TSelf(wxListItem) pObject);
int wxListItem_GetImage(TSelf(wxListItem) pObject);
int wxListItem_GetMask(TSelf(wxListItem) pObject);
int wxListItem_GetState(TSelf(wxListItem) pObject);
TClass(wxString) wxListItem_GetText(TSelf(wxListItem) pObject);
void wxListItem_GetTextColour(TSelf(wxListItem) pObject, TClassRef(wxColour) ref);
int wxListItem_GetWidth(TSelf(wxListItem) pObject);
TBool wxListItem_HasAttributes(TSelf(wxListItem) pObject);
void wxListItem_SetAlign(TSelf(wxListItem) pObject, int align);
void wxListItem_SetBackgroundColour(TSelf(wxListItem) pObject, TClass(wxColour) colBack);
void wxListItem_SetColumn(TSelf(wxListItem) pObject, int col);
void wxListItem_SetData(TSelf(wxListItem) pObject, int data);
void wxListItem_SetDataPointer(TSelf(wxListItem) pObject, void* data);
void wxListItem_SetFont(TSelf(wxListItem) pObject, TClass(wxFont) font);
void wxListItem_SetId(TSelf(wxListItem) pObject, int id);
void wxListItem_SetImage(TSelf(wxListItem) pObject, int image);
void wxListItem_SetMask(TSelf(wxListItem) pObject, int mask);
void wxListItem_SetState(TSelf(wxListItem) pObject, int state);
void wxListItem_SetStateMask(TSelf(wxListItem) pObject, int stateMask);
void wxListItem_SetText(TSelf(wxListItem) pObject, TClass(wxString) text);
void wxListItem_SetTextColour(TSelf(wxListItem) pObject, TClass(wxColour) colText);
void wxListItem_SetWidth(TSelf(wxListItem) pObject, int width);

/* wxListView */
TClassDefExtend(wxListView, wxListCtrl) TClass(wxListView)
    wxListView_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
void wxListView_ClearColumnImage(TSelf(wxListView) self, int col);
void wxListView_Focus(TSelf(wxListView) self, long index);
long wxListView_GetFirstSelected(TSelf(wxListView) self);
long wxListView_GetFocusedItem(TSelf(wxListView) self);
long wxListView_GetNextSelected(TSelf(wxListView) self, long item);
TBool wxListView_IsSelected(TSelf(wxListView) self, long index);
void wxListView_Select(TSelf(wxListView) self, long index, TBool select);
void wxListView_SetColumnImage(TSelf(wxListView) self, int col, int image);

/* wxLocale */
TClassDef(wxLocale) int wxLocale_AddCatalog(TSelf(wxLocale) pObject, void* szDomain,
                                            int msgIdLanguage);
void wxLocale_AddCatalogLookupPathPrefix(TSelf(wxLocale) pObject, void* prefix);
TClass(wxLocale) wxLocale_Create(int name, int flags);
void wxLocale_Delete(TSelf(wxLocale) pObject);
TClass(wxLocale) wxLocale_GetLocale(TSelf(wxLocale) pObject);
TClass(wxString) wxLocale_GetName(TSelf(wxLocale) pObject);
TString wxLocale_GetString(TSelf(wxLocale) pObject, void* szOrigString, void* szDomain);
TBool wxLocale_IsLoaded(TSelf(wxLocale) pObject, void* szDomain);
TBool wxLocale_IsOk(TSelf(wxLocale) pObject);

/* wxLog */
TClassDef(wxLog)

    /* wxLogChain */
    TClassDefExtend(wxLogChain, wxLog) TClass(wxLogChain) wxLogChain_Create(TClass(wxLog) logger);
void wxLogChain_Delete(TSelf(wxLogChain) pObject);
TClass(wxLog) wxLogChain_GetOldLog(TSelf(wxLogChain) pObject);
TBool wxLogChain_IsPassingMessages(TSelf(wxLogChain) pObject);
void wxLogChain_PassMessages(TSelf(wxLogChain) pObject, TBool bDoPass);
void wxLogChain_SetLog(TSelf(wxLogChain) pObject, TClass(wxLog) logger);

/* wxLogGUI */
TClassDefExtend(wxLogGUI, wxLog)

    /* wxLogNull */
    TClassDefExtend(wxLogNull, wxLog)

    /* wxLogPassThrough */
    TClassDefExtend(wxLogPassThrough, wxLogChain)

    /* wxLogStderr */
    TClassDefExtend(wxLogStderr, wxLog)

    /* wxLogStream */
    TClassDefExtend(wxLogStream, wxLog)

    /* wxLogTextCtrl */
    TClassDefExtend(wxLogTextCtrl, wxLog)

    /* wxLogWindow */
    TClassDefExtend(wxLogWindow, wxLogPassThrough)

    /* wxLongLong */
    TClassDef(wxLongLong)

    /* wxMBConv */
    TClassDef(wxMBConv)

    /* wxMBConvFile */
    TClassDefExtend(wxMBConvFile, wxMBConv)

    /* wxMBConvUTF7 */
    TClassDefExtend(wxMBConvUTF7, wxMBConv)

    /* wxMBConvUTF8 */
    TClassDefExtend(wxMBConvUTF8, wxMBConv)

    /* wxMDIChildFrame */
    TClassDefExtend(wxMDIChildFrame,
                    wxFrame) void wxMDIChildFrame_Activate(TSelf(wxMDIChildFrame) pObject);
TClass(wxMDIChildFrame)
    wxMDIChildFrame_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                           TRect(left, top, width, height), int style);

/* wxMDIClientWindow */
TClassDefExtend(wxMDIClientWindow, wxWindow)

    /* wxMDIParentFrame */
    TClassDefExtend(wxMDIParentFrame,
                    wxFrame) void wxMDIParentFrame_ActivateNext(TSelf(wxMDIParentFrame) pObject);
void wxMDIParentFrame_ActivatePrevious(TSelf(wxMDIParentFrame) pObject);
void wxMDIParentFrame_ArrangeIcons(TSelf(wxMDIParentFrame) pObject);
void wxMDIParentFrame_Cascade(TSelf(wxMDIParentFrame) pObject);
TClass(wxMDIParentFrame)
    wxMDIParentFrame_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                            TRect(left, top, width, height), int style);
TClass(wxMDIChildFrame) wxMDIParentFrame_GetActiveChild(TSelf(wxMDIParentFrame) pObject);
TClass(wxMDIClientWindow) wxMDIParentFrame_GetClientWindow(TSelf(wxMDIParentFrame) pObject);
TClass(wxMenu) wxMDIParentFrame_GetWindowMenu(TSelf(wxMDIParentFrame) pObject);
TClass(wxMDIClientWindow) wxMDIParentFrame_OnCreateClient(TSelf(wxMDIParentFrame) pObject);
void wxMDIParentFrame_SetWindowMenu(TSelf(wxMDIParentFrame) pObject, TClass(wxMenu) menu);
void wxMDIParentFrame_Tile(TSelf(wxMDIParentFrame) pObject, int orient);

/* wxMask */
TClassDefExtend(wxMask, wxObject) TClass(wxMask) wxMask_Create(TClass(wxBitmap) bitmap);
void* wxMask_CreateColoured(TClass(wxBitmap) bitmap, TClass(wxColour) colour);

/* wxMaximizeEvent */
TClassDefExtend(wxMaximizeEvent, wxEvent)

    /* wxMemoryDC */
    TClassDefExtend(wxMemoryDC, wxDC) TClass(wxMemoryDC) wxMemoryDC_Create();
TClass(wxMemoryDC) wxMemoryDC_CreateCompatible(TClass(wxDC) dc);
TClass(wxMemoryDC) wxMemoryDC_CreateWithBitmap(TClass(wxBitmap) bitmap);
void wxMemoryDC_Delete(TSelf(wxMemoryDC) pObject);
void wxMemoryDC_SelectObject(TSelf(wxMemoryDC) pObject, TClass(wxBitmap) bitmap);

/* wxMemoryFSHandler */
TClassDefExtend(wxMemoryFSHandler, wxFileSystemHandler)

    /* wxMemoryInputStream */
    TClassDefExtend(wxMemoryInputStream, wxInputStream)

    /* wxMemoryOutputStream */
    TClassDefExtend(wxMemoryOutputStream, wxOutputStream)

    /* wxMenu */
    TClassDefExtend(wxMenu, wxEvtHandler) void wxMenu_Append(TSelf(wxMenu) pObject, int id,
                                                             TClass(wxString) text,
                                                             TClass(wxString) help,
                                                             TBool isCheckable);
void wxMenu_AppendItem(TSelf(wxMenu) pObject, TClass(wxMenuItem) item);
void wxMenu_AppendSeparator(TSelf(wxMenu) pObject);
void wxMenu_AppendSub(TSelf(wxMenu) pObject, int id, TClass(wxString) text, TClass(wxMenu) submenu,
                      TClass(wxString) help);
void wxMenu_Break(TSelf(wxMenu) pObject);
void wxMenu_Check(TSelf(wxMenu) pObject, int id, TBool check);
TClass(wxMenu) wxMenu_Create(TClass(wxString) title, long style);
void wxMenu_DeleteById(TSelf(wxMenu) pObject, int id);
void wxMenu_DeleteByItem(TSelf(wxMenu) pObject, TClass(wxMenuItem) item);
void wxMenu_DeletePointer(TSelf(wxMenu) pObject);
void wxMenu_DestroyById(TSelf(wxMenu) pObject, int id);
void wxMenu_DestroyByItem(TSelf(wxMenu) pObject, TClass(wxMenuItem) item);
void wxMenu_Enable(TSelf(wxMenu) pObject, int id, TBool enable);
TClass(wxMenuItem) wxMenu_FindItem(TSelf(wxMenu) pObject, int id);
int wxMenu_FindItemByLabel(TSelf(wxMenu) pObject, TClass(wxString) itemString);
TClass(wxClientData) wxMenu_GetClientData(TSelf(wxMenu) pObject);
TClass(wxString) wxMenu_GetHelpString(TSelf(wxMenu) pObject, int id);
TClass(wxWindow) wxMenu_GetInvokingWindow(TSelf(wxMenu) pObject);
// TClass(wxString) wxMenu_GetLabel( TSelf(wxMenu) pObject, int id );
TClass(wxString) wxMenu_GetLabelText(TSelf(wxMenu) pObject, int id);
size_t wxMenu_GetMenuItemCount(TSelf(wxMenu) pObject);
int wxMenu_GetMenuItems(TSelf(wxMenu) pObject, TClass(wxList) list);
TClass(wxMenu) wxMenu_GetParent(TSelf(wxMenu) pObject);
int wxMenu_GetStyle(TSelf(wxMenu) pObject);
TClass(wxString) wxMenu_GetTitle(TSelf(wxMenu) pObject);
void wxMenu_Insert(TSelf(wxMenu) pObject, size_t pos, int id, TClass(wxString) text,
                   TClass(wxString) help, TBool isCheckable);
void wxMenu_InsertItem(TSelf(wxMenu) pObject, size_t pos, TClass(wxMenuItem) item);
void wxMenu_InsertSub(TSelf(wxMenu) pObject, size_t pos, int id, TClass(wxString) text,
                      TClass(wxMenu) submenu, TClass(wxString) help);
TBool wxMenu_IsAttached(TSelf(wxMenu) pObject);
TBool wxMenu_IsChecked(TSelf(wxMenu) pObject, int id);
TBool wxMenu_IsEnabled(TSelf(wxMenu) pObject, int id);
void wxMenu_Prepend(TSelf(wxMenu) pObject, int id, TClass(wxString) text, TClass(wxString) help,
                    TBool isCheckable);
void wxMenu_PrependItem(TSelf(wxMenu) pObject, TClass(wxMenuItem) item);
void wxMenu_PrependSub(TSelf(wxMenu) pObject, int id, TClass(wxString) text, TClass(wxMenu) submenu,
                       TClass(wxString) help);
void wxMenu_RemoveById(TSelf(wxMenu) pObject, int id, TClass(wxMenuItem) item);
void wxMenu_RemoveByItem(TSelf(wxMenu) pObject, void* item);
void wxMenu_SetClientData(TSelf(wxMenu) pObject, TClass(wxClientData) clientData);
void wxMenu_SetEventHandler(TSelf(wxMenu) pObject, TClass(wxEvtHandler) handler);
void wxMenu_SetHelpString(TSelf(wxMenu) pObject, int id, TClass(wxString) helpString);
void wxMenu_SetInvokingWindow(TSelf(wxMenu) pObject, TClass(wxWindow) win);
void wxMenu_SetLabel(TSelf(wxMenu) pObject, int id, TClass(wxString) label);
void wxMenu_SetParent(TSelf(wxMenu) pObject, TClass(wxWindow) parent);
void wxMenu_SetTitle(TSelf(wxMenu) pObject, TClass(wxString) title);
void wxMenu_UpdateUI(TSelf(wxMenu) pObject, void* source);

/* wxMenuBar */
TClassDefExtend(wxMenuBar, wxEvtHandler) int wxMenuBar_Append(TSelf(wxMenuBar) pObject,
                                                              TClass(wxMenu) menu,
                                                              TClass(wxString) title);
void wxMenuBar_Check(TSelf(wxMenuBar) pObject, int id, TBool check);
TClass(wxMenuBar) wxMenuBar_Create(int style);
void wxMenuBar_DeletePointer(TSelf(wxMenuBar) pObject);
int wxMenuBar_Enable(TSelf(wxMenuBar) pObject, TBool enable);
void wxMenuBar_EnableItem(TSelf(wxMenuBar) pObject, int id, TBool enable);
void wxMenuBar_EnableTop(TSelf(wxMenuBar) pObject, int pos, TBool enable);
TClass(wxMenuItem) wxMenuBar_FindItem(TSelf(wxMenuBar) pObject, int id);
int wxMenuBar_FindMenu(TSelf(wxMenuBar) pObject, TClass(wxString) title);
int wxMenuBar_FindMenuItem(TSelf(wxMenuBar) pObject, TClass(wxString) menuString,
                           TClass(wxString) itemString);
TClass(wxString) wxMenuBar_GetHelpString(TSelf(wxMenuBar) pObject, int id);
TClass(wxString) wxMenuBar_GetLabel(TSelf(wxMenuBar) pObject, int id);
// TClass(wxString) wxMenuBar_GetLabelTop( TSelf(wxMenuBar) pObject, int pos );
TClass(wxString) wxMenuBar_GetMenuLabel(TSelf(wxMenuBar) pObject, int pos);
TClass(wxMenu) wxMenuBar_GetMenu(TSelf(wxMenuBar) pObject, int pos);
int wxMenuBar_GetMenuCount(TSelf(wxMenuBar) pObject);
int wxMenuBar_Insert(TSelf(wxMenuBar) pObject, int pos, TClass(wxMenu) menu,
                     TClass(wxString) title);
TBool wxMenuBar_IsChecked(TSelf(wxMenuBar) pObject, int id);
TBool wxMenuBar_IsEnabled(TSelf(wxMenuBar) pObject, int id);
TClass(wxMenu) wxMenuBar_Remove(TSelf(wxMenuBar) pObject, int pos);
TClass(wxMenu) wxMenuBar_Replace(TSelf(wxMenuBar) pObject, int pos, TClass(wxMenu) menu,
                                 TClass(wxString) title);
void wxMenuBar_SetHelpString(TSelf(wxMenuBar) pObject, int id, TClass(wxString) helpString);
void wxMenuBar_SetItemLabel(TSelf(wxMenuBar) pObject, int id, TClass(wxString) label);
void wxMenuBar_SetLabel(TSelf(wxMenuBar) pObject, TClass(wxString) str);
// void       wxMenuBar_SetLabelTop( TSelf(wxMenuBar) pObject, int pos,
// TClass(wxString) label );
void wxMenuBar_SetMenuLabel(TSelf(wxMenuBar) pObject, int pos, TClass(wxString) label);

/* wxMenuEvent */
TClassDefExtend(wxMenuEvent, wxEvent) void wxMenuEvent_CopyObject(TSelf(wxMenuEvent) pObject,
                                                                  void* obj);
int wxMenuEvent_GetMenuId(TSelf(wxMenuEvent) pObject);

/* wxMenuItem */
TClassDefExtend(wxMenuItem, wxObject) void wxMenuItem_Check(TSelf(wxMenuItem) pObject, TBool check);
TClass(wxMenuItem) wxMenuItem_Create();
void wxMenuItem_Delete(TSelf(wxMenuItem) pObject);
void wxMenuItem_Enable(TSelf(wxMenuItem) pObject, TBool enable);
TClass(wxString) wxMenuItem_GetHelp(TSelf(wxMenuItem) pObject);
int wxMenuItem_GetId(TSelf(wxMenuItem) pObject);
// TClass(wxString) wxMenuItem_GetLabel( TSelf(wxMenuItem) pObject );
TClass(wxString) wxMenuItem_GetItemLabelText(TSelf(wxMenuItem) pObject);
// TClass(wxString) wxMenuItem_GetLabelFromText( TStringVoid text );
TClass(wxString) wxMenuItem_GetLabelText(TStringVoid text);
TClass(wxMenu) wxMenuItem_GetMenu(TSelf(wxMenuItem) pObject);
TClass(wxMenu) wxMenuItem_GetSubMenu(TSelf(wxMenuItem) pObject);
// TClass(wxString) wxMenuItem_GetText( TSelf(wxMenuItem) pObject );
TClass(wxString) wxMenuItem_GetItemLabel(TSelf(wxMenuItem) pObject);
TBool wxMenuItem_IsCheckable(TSelf(wxMenuItem) pObject);
TBool wxMenuItem_IsChecked(TSelf(wxMenuItem) pObject);
TBool wxMenuItem_IsEnabled(TSelf(wxMenuItem) pObject);
TBool wxMenuItem_IsSeparator(TSelf(wxMenuItem) pObject);
TBool wxMenuItem_IsSubMenu(TSelf(wxMenuItem) pObject);
void wxMenuItem_SetCheckable(TSelf(wxMenuItem) pObject, TBool checkable);
void wxMenuItem_SetHelp(TSelf(wxMenuItem) pObject, TClass(wxString) str);
void wxMenuItem_SetId(TSelf(wxMenuItem) pObject, int id);
void wxMenuItem_SetSubMenu(TSelf(wxMenuItem) pObject, TClass(wxMenu) menu);
// void       wxMenuItem_SetText( TSelf(wxMenuItem) pObject, TClass(wxString) str
// );
void wxMenuItem_SetItemLabel(TSelf(wxMenuItem) pObject, TClass(wxString) str);

/* wxMessageDialog */
TClassDefExtend(wxMessageDialog, wxDialog) TClass(wxMessageDialog)
    wxMessageDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                           TClass(wxString) caption, int style);
void wxMessageDialog_Delete(TSelf(wxMessageDialog) pObject);
int wxMessageDialog_ShowModal(TSelf(wxMessageDialog) pObject);
int wxcMessageBox(TClass(wxString) message, TClass(wxString) caption, int style,
                  TClass(wxWindow) parent, int x, int y);

/* wxMetafile */
TClassDefExtend(wxMetafile, wxObject) TClass(wxMetafile)
    wxMetafile_Create(TClass(wxString) filePath);
void wxMetafile_Delete(TSelf(wxMetafile) pObject);
TBool wxMetafile_IsOk(TSelf(wxMetafile) pObject);
TBool wxMetafile_Play(TSelf(wxMetafile) pObject, TClass(wxDC) dc);
TBool wxMetafile_SetClipboard(TSelf(wxMetafile) pObject, TSize(width, height));

/* wxMetafileDC */
TClassDefExtend(wxMetafileDC, wxDC) void* wxMetafileDC_Close(TSelf(wxMetafileDC) pObject);
TClass(wxMetafileDC) wxMetafileDC_Create(TClass(wxString) filePath);
void wxMetafileDC_Delete(TSelf(wxMetafileDC) pObject);

/* wxMimeTypesManager */
TClassDef(wxMimeTypesManager) void wxMimeTypesManager_AddFallbacks(TSelf(wxMimeTypesManager)
                                                                       pObject,
                                                                   void* types);
TClass(wxMimeTypesManager) wxMimeTypesManager_Create();
int wxMimeTypesManager_EnumAllFileTypes(TSelf(wxMimeTypesManager) pObject, TClass(wxList) list);
TClass(wxFileType) wxMimeTypesManager_GetFileTypeFromExtension(TSelf(wxMimeTypesManager) pObject,
                                                               TClass(wxString) extension);
TClass(wxFileType) wxMimeTypesManager_GetFileTypeFromMimeType(TSelf(wxMimeTypesManager) pObject,
                                                              TClass(wxString) name);
TBool wxMimeTypesManager_IsOfType(TSelf(wxMimeTypesManager) pObject, TClass(wxString) type,
                                  TClass(wxString) wildcard);

/* wxMiniFrame */
TClassDefExtend(wxMiniFrame, wxFrame) TClass(wxMiniFrame)
    wxMiniFrame_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                       TRect(left, top, width, height), int style);

/* wxMirrorDC */
TClassDefExtend(wxMirrorDC, wxDC) TClass(wxMirrorDC) wxMirrorDC_Create(TClass(wxDC) dc);
void wxMirrorDC_Delete(TSelf(wxMemoryDC) pObject);

/* wxModule */
TClassDefExtend(wxModule, wxObject)

    /* wxMouseCaptureChangedEvent */
    TClassDefExtend(wxMouseCaptureChangedEvent, wxEvent)

    /* wxMouseEvent */
    TClassDefExtend(wxMouseEvent, wxEvent) TBool wxMouseEvent_AltDown(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_Button(TSelf(wxMouseEvent) pObject, int but);
TBool wxMouseEvent_ButtonDClick(TSelf(wxMouseEvent) pObject, int but);
TBool wxMouseEvent_ButtonDown(TSelf(wxMouseEvent) pObject, int but);
TBool wxMouseEvent_ButtonIsDown(TSelf(wxMouseEvent) pObject, int but);
TBool wxMouseEvent_ButtonUp(TSelf(wxMouseEvent) pObject, int but);
TBool wxMouseEvent_ControlDown(TSelf(wxMouseEvent) pObject);
void wxMouseEvent_CopyObject(TSelf(wxMouseEvent) pObject, void* object_dest);
TBool wxMouseEvent_Dragging(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_Entering(TSelf(wxMouseEvent) pObject);
TClass(wxPoint) wxMouseEvent_GetLogicalPosition(TSelf(wxMouseEvent) pObject, TClass(wxDC) dc);
TClass(wxPoint) wxMouseEvent_GetPosition(TSelf(wxMouseEvent) pObject);
int wxMouseEvent_GetX(TSelf(wxMouseEvent) pObject);
int wxMouseEvent_GetY(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_IsButton(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_Leaving(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_LeftDClick(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_LeftDown(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_LeftIsDown(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_LeftUp(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_MetaDown(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_MiddleDClick(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_MiddleDown(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_MiddleIsDown(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_MiddleUp(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_Moving(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_RightDClick(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_RightDown(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_RightIsDown(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_RightUp(TSelf(wxMouseEvent) pObject);
TBool wxMouseEvent_ShiftDown(TSelf(wxMouseEvent) pObject);

/* wxMoveEvent */
TClassDefExtend(wxMoveEvent, wxEvent) void wxMoveEvent_CopyObject(TSelf(wxMoveEvent) pObject,
                                                                  void* obj);
TClass(wxPoint) wxMoveEvent_GetPosition(TSelf(wxMoveEvent) pObject);

/* wxMultiCellCanvas */
TClassDefExtend(wxMultiCellCanvas,
                wxFlexGridSizer) void wxMultiCellCanvas_Add(TSelf(wxMultiCellCanvas) pObject,
                                                            TClass(wxWindow) win, int row, int col);
void wxMultiCellCanvas_CalculateConstraints(TSelf(wxMultiCellCanvas) pObject);
TClass(wxMultiCellCanvas)
    wxMultiCellCanvas_Create(TClass(wxWindow) parent, int numRows, int numCols);
int wxMultiCellCanvas_MaxCols(TSelf(wxMultiCellCanvas) pObject);
int wxMultiCellCanvas_MaxRows(TSelf(wxMultiCellCanvas) pObject);
void wxMultiCellCanvas_SetMinCellSize(TSelf(wxMultiCellCanvas) pObject, TSize(width, height));

/* wxMultiCellItemHandle */
TClassDefExtend(wxMultiCellItemHandle, wxObject) TClass(wxMultiCellItemHandle)
    wxMultiCellItemHandle_Create(int row, int column, int height, int width, int sizeX, int sizeY,
                                 int style, int weightX, int weightY, int align);
void* wxMultiCellItemHandle_CreateWithSize(TSelf(wxMultiCellItemHandle) pObject, int row,
                                           int column, int sizeX, int sizeY, int style, int weightX,
                                           int weightY, int align);
void* wxMultiCellItemHandle_CreateWithStyle(TSelf(wxMultiCellItemHandle) pObject, int row,
                                            int column, int style, int weightX, int weightY,
                                            int align);
int wxMultiCellItemHandle_GetAlignment(TSelf(wxMultiCellItemHandle) pObject);
int wxMultiCellItemHandle_GetColumn(TSelf(wxMultiCellItemHandle) pObject);
int wxMultiCellItemHandle_GetHeight(TSelf(wxMultiCellItemHandle) pObject);
void wxMultiCellItemHandle_GetLocalSize(TSelf(wxMultiCellItemHandle) pObject,
                                        TSizeOutVoid(width, height));
int wxMultiCellItemHandle_GetRow(TSelf(wxMultiCellItemHandle) pObject);
int wxMultiCellItemHandle_GetStyle(TSelf(wxMultiCellItemHandle) pObject);
void wxMultiCellItemHandle_GetWeight(TSelf(wxMultiCellItemHandle) pObject,
                                     TSizeOutVoid(width, height));
int wxMultiCellItemHandle_GetWidth(TSelf(wxMultiCellItemHandle) pObject);

/* wxMultiCellSizer */
TClassDefExtend(wxMultiCellSizer,
                wxSizer) void wxMultiCellSizer_CalcMin(TSelf(wxMultiCellSizer) pObject,
                                                       TSizeOutVoid(width, height));
TClass(wxMultiCellSizer) wxMultiCellSizer_Create(int rows, int cols);
void wxMultiCellSizer_Delete(TSelf(wxMultiCellSizer) pObject);
int wxMultiCellSizer_EnableGridLines(TSelf(wxMultiCellSizer) pObject, TClass(wxWindow) win);
void wxMultiCellSizer_RecalcSizes(TSelf(wxMultiCellSizer) pObject);
int wxMultiCellSizer_SetColumnWidth(TSelf(wxMultiCellSizer) pObject, int column, int colSize,
                                    int expandable);
int wxMultiCellSizer_SetDefaultCellSize(TSelf(wxMultiCellSizer) pObject, TSize(width, height));
int wxMultiCellSizer_SetGridPen(TSelf(wxMultiCellSizer) pObject, TClass(wxPen) pen);
int wxMultiCellSizer_SetRowHeight(TSelf(wxMultiCellSizer) pObject, int row, int rowSize,
                                  int expandable);

/* wxMutex */
TClassDef(wxMutex) TClass(wxMutex) wxMutex_Create();
void wxMutex_Delete(TSelf(wxMutex) pObject);
TBool wxMutex_IsLocked(TSelf(wxMutex) pObject);
int wxMutex_Lock(TSelf(wxMutex) pObject);
int wxMutex_TryLock(TSelf(wxMutex) pObject);
int wxMutex_Unlock(TSelf(wxMutex) pObject);

/* wxMutexLocker */
TClassDef(wxMutexLocker)

    /* wxNavigationKeyEvent */
    TClassDefExtend(wxNavigationKeyEvent,
                    wxEvent) void* wxNavigationKeyEvent_GetCurrentFocus(TSelf(wxNavigationKeyEvent)
                                                                            pObject);
TBool wxNavigationKeyEvent_GetDirection(TSelf(wxNavigationKeyEvent) pObject);
TBool wxNavigationKeyEvent_IsWindowChange(TSelf(wxNavigationKeyEvent) pObject);
void wxNavigationKeyEvent_SetCurrentFocus(TSelf(wxNavigationKeyEvent) pObject,
                                          TClass(wxWindow) win);
void wxNavigationKeyEvent_SetDirection(TSelf(wxNavigationKeyEvent) pObject, TBool bForward);
/* void       wxNavigationKeyEvent_SetPropagate( TSelf(wxNavigationKeyEvent)
 * pObject, int bDoIt );*/
void wxNavigationKeyEvent_SetWindowChange(TSelf(wxNavigationKeyEvent) pObject, TBool bIs);
int wxNavigationKeyEvent_ShouldPropagate(TSelf(wxNavigationKeyEvent) pObject);

/* wxNewBitmapButton */
TClassDefExtend(wxNewBitmapButton, wxPanel) TClass(wxNewBitmapButton)
    wxNewBitmapButton_Create(void* labelBitmap, void* labelText, int alignText, TBool isFlat,
                             int firedEventType, int marginX, int marginY, int textToLabelGap,
                             TBool isSticky);
TClass(wxNewBitmapButton)
    wxNewBitmapButton_CreateFromFile(TSelf(wxNewBitmapButton) bitmapFileName, int bitmapFileType,
                                     void* labelText, int alignText, TBool isFlat,
                                     int firedEventType, int marginX, int marginY,
                                     int textToLabelGap, TBool isSticky);
void wxNewBitmapButton_Delete(TSelf(wxNewBitmapButton) pObject);
void wxNewBitmapButton_DrawDecorations(TSelf(wxNewBitmapButton) pObject, TClass(wxDC) dc);
void wxNewBitmapButton_DrawLabel(TSelf(wxNewBitmapButton) pObject, TClass(wxDC) dc);
int wxNewBitmapButton_Enable(TSelf(wxNewBitmapButton) pObject, TBool enable);
void wxNewBitmapButton_Realize(TSelf(wxNewBitmapButton) pObject, TClass(wxWindow) parent, int id,
                               TRect(x, y, width, height));
void wxNewBitmapButton_RenderAllLabelImages(TSelf(wxNewBitmapButton) pObject);
void wxNewBitmapButton_RenderLabelImage(TSelf(wxNewBitmapButton) pObject, void* destBmp,
                                        void* srcBmp, TBool isEnabled, TBool isPressed);
void wxNewBitmapButton_RenderLabelImages(TSelf(wxNewBitmapButton) pObject);
void wxNewBitmapButton_Reshape(TSelf(wxNewBitmapButton) pObject);
void wxNewBitmapButton_SetAlignments(TSelf(wxNewBitmapButton) pObject, int alignText, int marginX,
                                     int marginY, int textToLabelGap);
void wxNewBitmapButton_SetLabel(TSelf(wxNewBitmapButton) pObject, void* labelBitmap,
                                void* labelText);

/* wxNodeBase */
TClassDef(wxNodeBase)

    /* wxNotebook */
    TClassDefExtend(wxNotebook, wxControl) TBool
    wxNotebook_AddPage(TSelf(wxNotebook) pObject, TClass(wxWindow) pPage, TClass(wxString) strText,
                       TBool bSelect, int imageId);
void wxNotebook_AdvanceSelection(TSelf(wxNotebook) pObject, TBool bForward);
TClass(wxNotebook)
    wxNotebook_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height), int style);
TBool wxNotebook_DeleteAllPages(TSelf(wxNotebook) pObject);
TBool wxNotebook_DeletePage(TSelf(wxNotebook) pObject, int nPage);
TClass(wxImageList) wxNotebook_GetImageList(TSelf(wxNotebook) pObject);
TClass(wxWindow) wxNotebook_GetPage(TSelf(wxNotebook) pObject, int nPage);
int wxNotebook_GetPageCount(TSelf(wxNotebook) pObject);
int wxNotebook_GetPageImage(TSelf(wxNotebook) pObject, int nPage);
TClass(wxString) wxNotebook_GetPageText(TSelf(wxNotebook) pObject, int nPage);
int wxNotebook_GetRowCount(TSelf(wxNotebook) pObject);
int wxNotebook_GetSelection(TSelf(wxNotebook) pObject);
int wxNotebook_HitTest(TSelf(wxNotebook) pObject, TPoint(x, y), long* flags);
TBool wxNotebook_InsertPage(TSelf(wxNotebook) pObject, int nPage, TClass(wxWindow) pPage,
                            TClass(wxString) strText, TBool bSelect, int imageId);
TBool wxNotebook_RemovePage(TSelf(wxNotebook) pObject, int nPage);
void wxNotebook_SetImageList(TSelf(wxNotebook) pObject, TClass(wxImageList) imageList);
void wxNotebook_SetPadding(TSelf(wxNotebook) pObject, TSize(width, height));
TBool wxNotebook_SetPageImage(TSelf(wxNotebook) pObject, int nPage, int nImage);
void wxNotebook_SetPageSize(TSelf(wxNotebook) pObject, TSize(width, height));
TBool wxNotebook_SetPageText(TSelf(wxNotebook) pObject, int nPage, TClass(wxString) strText);
int wxNotebook_SetSelection(TSelf(wxNotebook) pObject, int nPage);

int expNB_TOP();
int expNB_BOTTOM();
int expNB_LEFT();
int expNB_RIGHT();

int expBK_HITTEST_NOWHERE();
int expBK_HITTEST_ONICON();
int expBK_HITTEST_ONLABEL();
int expBK_HITTEST_ONITEM();
int expBK_HITTEST_ONPAGE();

/* wxChoicebook */
TClassDefExtend(wxChoicebook, wxBookCtrlBase) TBool
    wxChoicebook_AddPage(TSelf(wxChoicebook) pObject, TClass(wxWindow) pPage,
                         TClass(wxString) strText, TBool bSelect, int imageId);
void wxChoicebook_AdvanceSelection(TSelf(wxChoicebook) pObject, TBool bForward);
TClass(wxChoicebook)
    wxChoicebook_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
TBool wxChoicebook_DeleteAllPages(TSelf(wxChoicebook) pObject);
TBool wxChoicebook_DeletePage(TSelf(wxChoicebook) pObject, int nPage);
TClass(wxChoice) wxChoicebook_GetChoiceCtrl(TSelf(wxChoicebook) pObject);
TClass(wxImageList) wxChoicebook_GetImageList(TSelf(wxChoicebook) pObject);
TClass(wxWindow) wxChoicebook_GetPage(TSelf(wxChoicebook) pObject, int nPage);
int wxChoicebook_GetPageCount(TSelf(wxChoicebook) pObject);
int wxChoicebook_GetPageImage(TSelf(wxChoicebook) pObject, int nPage);
TClass(wxString) wxChoicebook_GetPageText(TSelf(wxChoicebook) pObject, int nPage);
int wxChoicebook_GetSelection(TSelf(wxChoicebook) pObject);
int wxChoicebook_HitTest(TSelf(wxChoicebook) pObject, TPoint(x, y), long* flags);
TBool wxChoicebook_InsertPage(TSelf(wxChoicebook) pObject, int nPage, TClass(wxWindow) pPage,
                              TClass(wxString) strText, TBool bSelect, int imageId);
TBool wxChoicebook_RemovePage(TSelf(wxChoicebook) pObject, int nPage);
void wxChoicebook_SetImageList(TSelf(wxChoicebook) pObject, TClass(wxImageList) imageList);
TBool wxChoicebook_SetPageImage(TSelf(wxChoicebook) pObject, int nPage, int nImage);
TBool wxChoicebook_SetPageText(TSelf(wxChoicebook) pObject, int nPage, TClass(wxString) strText);
int wxChoicebook_SetSelection(TSelf(wxChoicebook) pObject, int nPage);

int expCHB_DEFAULT();
int expCHB_TOP();
int expCHB_BOTTOM();
int expCHB_LEFT();
int expCHB_RIGHT();

/* wxListbook */
TClassDefExtend(wxListbook, wxBookCtrlBase) TBool
    wxListbook_AddPage(TSelf(wxListbook) pObject, TClass(wxWindow) pPage, TClass(wxString) strText,
                       TBool bSelect, int imageId);
void wxListbook_AdvanceSelection(TSelf(wxListbook) pObject, TBool bForward);
TClass(wxListbook)
    wxListbook_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
TBool wxListbook_DeleteAllPages(TSelf(wxListbook) pObject);
TBool wxListbook_DeletePage(TSelf(wxListbook) pObject, int nPage);
TClass(wxImageList) wxListbook_GetImageList(TSelf(wxListbook) pObject);
TClass(wxListView) wxListbook_GetListView(TSelf(wxListbook) pObject);
TClass(wxWindow) wxListbook_GetPage(TSelf(wxListbook) pObject, int nPage);
int wxListbook_GetPageCount(TSelf(wxListbook) pObject);
int wxListbook_GetPageImage(TSelf(wxListbook) pObject, int nPage);
TClass(wxString) wxListbook_GetPageText(TSelf(wxListbook) pObject, int nPage);
int wxListbook_GetSelection(TSelf(wxListbook) pObject);
int wxListbook_HitTest(TSelf(wxListbook) pObject, TPoint(x, y), long* flags);
TBool wxListbook_InsertPage(TSelf(wxListbook) pObject, int nPage, TClass(wxWindow) pPage,
                            TClass(wxString) strText, TBool bSelect, int imageId);
TBool wxListbook_RemovePage(TSelf(wxListbook) pObject, int nPage);
void wxListbook_SetImageList(TSelf(wxListbook) pObject, TClass(wxImageList) imageList);
TBool wxListbook_SetPageImage(TSelf(wxListbook) pObject, int nPage, int nImage);
TBool wxListbook_SetPageText(TSelf(wxListbook) pObject, int nPage, TClass(wxString) strText);
int wxListbook_SetSelection(TSelf(wxListbook) pObject, int nPage);

int expLB_DEFAULT();
int expLB_TOP();
int expLB_BOTTOM();
int expLB_LEFT();
int expLB_RIGHT();

/* wxSimplebook */
TClassDefExtend(wxSimplebook, wxBookCtrlBase) TBool
    wxSimplebook_AddPage(TSelf(wxSimplebook) pObject, TClass(wxWindow) pPage,
                         TClass(wxString) strText, TBool bSelect, int imageId);
int wxSimplebook_ChangeSelection(TSelf(wxSimplebook) pObject, int nPage);
TClass(wxSimplebook)
    wxSimplebook_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
TBool wxSimplebook_DeleteAllPages(TSelf(wxSimplebook) pObject);
TBool wxSimplebook_DeletePage(TSelf(wxSimplebook) pObject, int nPage);
TClass(wxImageList) wxSimplebook_GetImageList(TSelf(wxSimplebook) pObject);
TClass(wxWindow) wxSimplebook_GetPage(TSelf(wxSimplebook) pObject, int nPage);
int wxSimplebook_GetPageCount(TSelf(wxSimplebook) pObject);
int wxSimplebook_GetPageImage(TSelf(wxSimplebook) pObject, int nPage);
TClass(wxString) wxSimplebook_GetPageText(TSelf(wxSimplebook) pObject, int nPage);
int wxSimplebook_GetSelection(TSelf(wxSimplebook) pObject);
TBool wxSimplebook_InsertPage(TSelf(wxSimplebook) pObject, int nPage, TClass(wxWindow) pPage,
                              TClass(wxString) strText, TBool bSelect, int imageId);
TBool wxSimplebook_RemovePage(TSelf(wxSimplebook) pObject, int nPage);
void wxSimplebook_SetImageList(TSelf(wxSimplebook) pObject, TClass(wxImageList) imageList);
TBool wxSimplebook_SetPageImage(TSelf(wxSimplebook) pObject, int nPage, int nImage);
TBool wxSimplebook_SetPageText(TSelf(wxSimplebook) pObject, int nPage, TClass(wxString) strText);
int wxSimplebook_SetSelection(TSelf(wxSimplebook) pObject, int nPage);
void wxSimplebook_ShowNewPage(TSelf(wxSimplebook) pObject, TClass(wxWindow) page);

/* wxToolbook */
TClassDefExtend(wxToolbook, wxBookCtrlBase) TBool
    wxToolbook_AddPage(TSelf(wxToolbook) pObject, TClass(wxWindow) pPage, TClass(wxString) strText,
                       TBool bSelect, int imageId);
void wxToolbook_AdvanceSelection(TSelf(wxToolbook) pObject, TBool bForward);
TClass(wxToolbook)
    wxToolbook_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
TBool wxToolbook_DeleteAllPages(TSelf(wxToolbook) pObject);
TBool wxToolbook_DeletePage(TSelf(wxToolbook) pObject, int nPage);
TClass(wxImageList) wxToolbook_GetImageList(TSelf(wxToolbook) pObject);
TClass(wxWindow) wxToolbook_GetPage(TSelf(wxToolbook) pObject, int nPage);
int wxToolbook_GetPageCount(TSelf(wxToolbook) pObject);
int wxToolbook_GetPageImage(TSelf(wxToolbook) pObject, int nPage);
TClass(wxString) wxToolbook_GetPageText(TSelf(wxToolbook) pObject, int nPage);
int wxToolbook_GetSelection(TSelf(wxToolbook) pObject);
TClass(wxToolBarBase) wxToolbook_GetToolBar(TSelf(wxToolbook) pObject);
int wxToolbook_HitTest(TSelf(wxToolbook) pObject, TPoint(x, y), long* flags);
TBool wxToolbook_InsertPage(TSelf(wxToolbook) pObject, int nPage, TClass(wxWindow) pPage,
                            TClass(wxString) strText, TBool bSelect, int imageId);
TBool wxToolbook_RemovePage(TSelf(wxToolbook) pObject, int nPage);
void wxToolbook_SetImageList(TSelf(wxToolbook) pObject, TClass(wxImageList) imageList);
TBool wxToolbook_SetPageImage(TSelf(wxToolbook) pObject, int nPage, int nImage);
TBool wxToolbook_SetPageText(TSelf(wxToolbook) pObject, int nPage, TClass(wxString) strText);
int wxToolbook_SetSelection(TSelf(wxToolbook) pObject, int nPage);

int expTBK_BUTTONBAR();
int expTBK_HORZ_LAYOUT();

/* wxTreebook */
TClassDefExtend(wxTreebook, wxBookCtrlBase) TBool
    wxTreebook_AddPage(TSelf(wxTreebook) pObject, TClass(wxWindow) pPage, TClass(wxString) strText,
                       TBool bSelect, int imageId);
TBool wxTreebook_AddSubPage(TSelf(wxTreebook) pObject, TClass(wxWindow) pPage,
                            TClass(wxString) strText, TBool bSelect, int imageId);
void wxTreebook_AdvanceSelection(TSelf(wxTreebook) pObject, TBool bForward);
TClass(wxTreebook)
    wxTreebook_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
TBool wxTreebook_DeleteAllPages(TSelf(wxTreebook) pObject);
TBool wxTreebook_DeletePage(TSelf(wxTreebook) pObject, int nPage);
void wxTreebook_ExpandNode(TSelf(wxTreebook) pObject, int nPage, TBool expand);
TClass(wxImageList) wxTreebook_GetImageList(TSelf(wxTreebook) pObject);
TClass(wxWindow) wxTreebook_GetPage(TSelf(wxTreebook) pObject, int nPage);
int wxTreebook_GetPageCount(TSelf(wxTreebook) pObject);
int wxTreebook_GetPageImage(TSelf(wxTreebook) pObject, int nPage);
int wxTreebook_GetPageParent(TSelf(wxTreebook) pObject, int nPage);
TClass(wxString) wxTreebook_GetPageText(TSelf(wxTreebook) pObject, int nPage);
int wxTreebook_GetSelection(TSelf(wxTreebook) pObject);
TClass(wxTreeCtrl) wxTreebook_GetTreeCtrl(TSelf(wxTreebook) pObject);
int wxTreebook_HitTest(TSelf(wxTreebook) pObject, TPoint(x, y), long* flags);
TBool wxTreebook_InsertPage(TSelf(wxTreebook) pObject, int nPage, TClass(wxWindow) pPage,
                            TClass(wxString) strText, TBool bSelect, int imageId);
TBool wxTreebook_InsertSubPage(TSelf(wxTreebook) pObject, int nPage, TClass(wxWindow) pPage,
                               TClass(wxString) strText, TBool bSelect, int imageId);
TBool wxTreebook_IsNodeExpanded(TSelf(wxTreebook) pObject, int nPage);
TBool wxTreebook_RemovePage(TSelf(wxTreebook) pObject, int nPage);
void wxTreebook_SetImageList(TSelf(wxTreebook) pObject, TClass(wxImageList) imageList);
TBool wxTreebook_SetPageImage(TSelf(wxTreebook) pObject, int nPage, int nImage);
TBool wxTreebook_SetPageText(TSelf(wxTreebook) pObject, int nPage, TClass(wxString) strText);
int wxTreebook_SetSelection(TSelf(wxTreebook) pObject, int nPage);

/* wxDataViewCtrl */
TClass(wxDataViewCtrl) wxDataViewCtrl_Create(TClass(wxWindow) parent, int id, int x, int y,
                                             int width, int height, int style);
TBool wxDataViewCtrl_AssociateModel(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewModel) model);
TClass(wxDataViewModel) wxDataViewCtrl_GetModel(TSelf(wxDataViewCtrl) pObject);
TClass(wxDataViewColumn)
    wxDataViewCtrl_AppendTextColumn(TSelf(wxDataViewCtrl) pObject, TClass(wxString) label,
                                    unsigned int model_column, int mode, int width, int align,
                                    int flags);
TClass(wxDataViewColumn)
    wxDataViewCtrl_AppendToggleColumn(TSelf(wxDataViewCtrl) pObject, TClass(wxString) label,
                                      unsigned int model_column, int mode, int width, int align,
                                      int flags);
TClass(wxDataViewColumn)
    wxDataViewCtrl_AppendProgressColumn(TSelf(wxDataViewCtrl) pObject, TClass(wxString) label,
                                        unsigned int model_column, int mode, int width, int align,
                                        int flags);
TClass(wxDataViewColumn)
    wxDataViewCtrl_AppendBitmapColumn(TSelf(wxDataViewCtrl) pObject, TClass(wxString) label,
                                      unsigned int model_column, int mode, int width, int align,
                                      int flags);
TBool wxDataViewCtrl_AppendColumn(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewColumn) col);
TBool wxDataViewCtrl_PrependColumn(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewColumn) col);
TBool wxDataViewCtrl_InsertColumn(TSelf(wxDataViewCtrl) pObject, unsigned int pos,
                                  TClass(wxDataViewColumn) col);
unsigned int wxDataViewCtrl_GetColumnCount(TSelf(wxDataViewCtrl) pObject);
TClass(wxDataViewColumn) wxDataViewCtrl_GetColumn(TSelf(wxDataViewCtrl) pObject, unsigned int pos);
int wxDataViewCtrl_GetColumnPosition(TSelf(wxDataViewCtrl) pObject,
                                     TClass(wxDataViewColumn) column);
TBool wxDataViewCtrl_DeleteColumn(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewColumn) column);
TBool wxDataViewCtrl_ClearColumns(TSelf(wxDataViewCtrl) pObject);
void wxDataViewCtrl_SetExpanderColumn(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewColumn) col);
TClass(wxDataViewColumn) wxDataViewCtrl_GetExpanderColumn(TSelf(wxDataViewCtrl) pObject);
TClass(wxDataViewColumn) wxDataViewCtrl_GetSortingColumn(TSelf(wxDataViewCtrl) pObject);
void wxDataViewCtrl_SetIndent(TSelf(wxDataViewCtrl) pObject, int indent);
int wxDataViewCtrl_GetIndent(TSelf(wxDataViewCtrl) pObject);
void wxDataViewCtrl_GetCurrentItem(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item);
void wxDataViewCtrl_SetCurrentItem(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item);
TClass(wxDataViewColumn) wxDataViewCtrl_GetCurrentColumn(TSelf(wxDataViewCtrl) pObject);
int wxDataViewCtrl_GetSelectedItemsCount(TSelf(wxDataViewCtrl) pObject);
TBool wxDataViewCtrl_HasSelection(TSelf(wxDataViewCtrl) pObject);
void wxDataViewCtrl_GetSelection(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item);
int wxDataViewCtrl_GetSelections(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItemArray) sel);
void wxDataViewCtrl_SetSelections(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItemArray) sel);
void wxDataViewCtrl_Select(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item);
void wxDataViewCtrl_Unselect(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item);
TBool wxDataViewCtrl_IsSelected(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item);
void wxDataViewCtrl_SelectAll(TSelf(wxDataViewCtrl) pObject);
void wxDataViewCtrl_UnselectAll(TSelf(wxDataViewCtrl) pObject);
void wxDataViewCtrl_Expand(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item);
void wxDataViewCtrl_Collapse(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item);
TBool wxDataViewCtrl_IsExpanded(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item);
void wxDataViewCtrl_EnsureVisible(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item,
                                  TClass(wxDataViewColumn) column);
void wxDataViewCtrl_HitTest(TSelf(wxDataViewCtrl) pObject, int x, int y,
                            TClass(wxDataViewItem) item, TClass(wxDataViewColumn) * col);
void wxDataViewCtrl_GetItemRect(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item,
                                TClass(wxDataViewColumn) column, int* x, int* y, int* width,
                                int* height);
void wxDataViewCtrl_EditItem(TSelf(wxDataViewCtrl) pObject, TClass(wxDataViewItem) item,
                             TClass(wxDataViewColumn) column);
TClass(wxDataViewItem) wxDataViewItem_Create(void* id);
void wxDataViewItem_Delete(TClass(wxDataViewItem) item);
void* wxDataViewItem_GetID(TClass(wxDataViewItem) item);
TBool wxDataViewItem_IsOk(TClass(wxDataViewItem) item);
TClass(wxDataViewItemArray) wxDataViewItemArray_Create();
void wxDataViewItemArray_Delete(TClass(wxDataViewItemArray) arr);
size_t wxDataViewItemArray_GetCount(TClass(wxDataViewItemArray) arr);
void wxDataViewItemArray_Item(TClass(wxDataViewItemArray) arr, size_t index,
                              TClass(wxDataViewItem) item);
void wxDataViewItemArray_Add(TClass(wxDataViewItemArray) arr, TClass(wxDataViewItem) item);
void wxDataViewItemArray_Clear(TClass(wxDataViewItemArray) arr);

/* wxDataViewListCtrl */
TClass(wxDataViewListCtrl) wxDataViewListCtrl_Create(TClass(wxWindow) parent, int id, int x, int y,
                                                     int width, int height, int style);
TClass(wxDataViewListStore) wxDataViewListCtrl_GetStore(TSelf(wxDataViewListCtrl) pObject);
TClass(wxDataViewColumn)
    wxDataViewListCtrl_AppendTextColumn(TSelf(wxDataViewListCtrl) pObject, TClass(wxString) label,
                                        int mode, int width, int align, int flags);
TClass(wxDataViewColumn)
    wxDataViewListCtrl_AppendToggleColumn(TSelf(wxDataViewListCtrl) pObject, TClass(wxString) label,
                                          int mode, int width, int align, int flags);
TClass(wxDataViewColumn) wxDataViewListCtrl_AppendProgressColumn(TSelf(wxDataViewListCtrl) pObject,
                                                                 TClass(wxString) label, int mode,
                                                                 int width, int align, int flags);
TClass(wxDataViewColumn) wxDataViewListCtrl_AppendIconTextColumn(TSelf(wxDataViewListCtrl) pObject,
                                                                 TClass(wxString) label, int mode,
                                                                 int width, int align, int flags);
int wxDataViewListCtrl_ItemToRow(TSelf(wxDataViewListCtrl) pObject, TClass(wxDataViewItem) item);
void wxDataViewListCtrl_RowToItem(TSelf(wxDataViewListCtrl) pObject, int row,
                                  TClass(wxDataViewItem) item);
int wxDataViewListCtrl_GetSelectedRow(TSelf(wxDataViewListCtrl) pObject);
void wxDataViewListCtrl_SelectRow(TSelf(wxDataViewListCtrl) pObject, unsigned int row);
void wxDataViewListCtrl_UnselectRow(TSelf(wxDataViewListCtrl) pObject, unsigned int row);
void wxDataViewListCtrl_AppendItem(TSelf(wxDataViewListCtrl) pObject, void* values, wxUIntPtr data);
void wxDataViewListCtrl_PrependItem(TSelf(wxDataViewListCtrl) pObject, void* values,
                                    wxUIntPtr data);
void wxDataViewListCtrl_InsertItem(TSelf(wxDataViewListCtrl) pObject, unsigned int row,
                                   void* values, wxUIntPtr data);
void wxDataViewListCtrl_DeleteItem(TSelf(wxDataViewListCtrl) pObject, unsigned int row);
void wxDataViewListCtrl_DeleteAllItems(TSelf(wxDataViewListCtrl) pObject);
void wxDataViewListCtrl_SetValue(TSelf(wxDataViewListCtrl) pObject, TClass(wxVariant) value,
                                 unsigned int row, unsigned int col);
void wxDataViewListCtrl_GetValue(TSelf(wxDataViewListCtrl) pObject, TClass(wxVariant) value,
                                 unsigned int row, unsigned int col);
void wxDataViewListCtrl_SetTextValue(TSelf(wxDataViewListCtrl) pObject, TClass(wxString) value,
                                     unsigned int row, unsigned int col);
TClass(wxString) wxDataViewListCtrl_GetTextValue(TSelf(wxDataViewListCtrl) pObject,
                                                 unsigned int row, unsigned int col);
void wxDataViewListCtrl_SetToggleValue(TSelf(wxDataViewListCtrl) pObject, TBool value,
                                       unsigned int row, unsigned int col);
TBool wxDataViewListCtrl_GetToggleValue(TSelf(wxDataViewListCtrl) pObject, unsigned int row,
                                        unsigned int col);
void wxDataViewListCtrl_SetItemData(TSelf(wxDataViewListCtrl) pObject, TClass(wxDataViewItem) item,
                                    wxUIntPtr data);
wxUIntPtr wxDataViewListCtrl_GetItemData(TSelf(wxDataViewListCtrl) pObject,
                                         TClass(wxDataViewItem) item);
int wxDataViewListCtrl_GetItemCount(TSelf(wxDataViewListCtrl) pObject);
void* wxVariantVector_Create();
void wxVariantVector_Delete(void* vec);
void wxVariantVector_Add(void* vec, TClass(wxVariant) value);
void wxVariantVector_AddString(void* vec, TClass(wxString) value);
void wxVariantVector_AddLong(void* vec, long value);
void wxVariantVector_AddBool(void* vec, TBool value);
size_t wxVariantVector_GetCount(void* vec);
void wxVariantVector_Clear(void* vec);

/* wxDatePickerCtrl */
TClass(wxDatePickerCtrl) wxDatePickerCtrl_Create(TClass(wxWindow) parent, int id, int x, int y,
                                                 int width, int height, long style);
void wxDatePickerCtrl_SetValue(TSelf(wxDatePickerCtrl) pObject, TClass(wxDateTime) dateTime);
void wxDatePickerCtrl_GetValue(TSelf(wxDatePickerCtrl) pObject, TClass(wxDateTime) dateTime);
void wxDatePickerCtrl_SetRange(TSelf(wxDatePickerCtrl) pObject, TClass(wxDateTime) dt1,
                               TClass(wxDateTime) dt2);
TBool wxDatePickerCtrl_GetRange(TSelf(wxDatePickerCtrl) pObject, TClass(wxDateTime) dt1,
                                TClass(wxDateTime) dt2);

/* wxDirPickerCtrl */
TClass(wxDirPickerCtrl)
    wxDirPickerCtrl_Create(TClass(wxWindow) parent, int id, int x, int y, int width, int height,
                           TClass(wxString) path, TClass(wxString) message, long style);
TClass(wxString) wxDirPickerCtrl_GetPath(TSelf(wxDirPickerCtrl) pObject);
void wxDirPickerCtrl_SetPath(TSelf(wxDirPickerCtrl) pObject, TClass(wxString) path);

/* wxFilePickerCtrl */
TClass(wxFilePickerCtrl)
    wxFilePickerCtrl_Create(TClass(wxWindow) parent, int id, int x, int y, int width, int height,
                            TClass(wxString) path, TClass(wxString) message,
                            TClass(wxString) wildcard, long style);
TClass(wxString) wxFilePickerCtrl_GetPath(TSelf(wxFilePickerCtrl) pObject);
void wxFilePickerCtrl_SetPath(TSelf(wxFilePickerCtrl) pObject, TClass(wxString) path);

/* wxFontPickerCtrl */
TClass(wxFontPickerCtrl)
    wxFontPickerCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxFont) initial, int x, int y,
                            int width, int height, long style);
TClass(wxFont) wxFontPickerCtrl_GetSelectedFont(TSelf(wxFontPickerCtrl) pObject);
void wxFontPickerCtrl_SetSelectedFont(TSelf(wxFontPickerCtrl) pObject, TClass(wxFont) font);
int wxFontPickerCtrl_GetMaxPointSize(TSelf(wxFontPickerCtrl) pObject);
void wxFontPickerCtrl_SetMaxPointSize(TSelf(wxFontPickerCtrl) pObject, int maxSize);

/* wxTimePickerCtrl */
TClass(wxTimePickerCtrl) wxTimePickerCtrl_Create(TClass(wxWindow) parent, int id, int x, int y,
                                                 int width, int height, long style);
void wxTimePickerCtrl_SetValue(TSelf(wxTimePickerCtrl) pObject, TClass(wxDateTime) dateTime);
void wxTimePickerCtrl_GetValue(TSelf(wxTimePickerCtrl) pObject, TClass(wxDateTime) dateTime);
void wxTimePickerCtrl_SetTime(TSelf(wxTimePickerCtrl) pObject, int hour, int min, int sec);
TBool wxTimePickerCtrl_GetTime(TSelf(wxTimePickerCtrl) pObject, int* hour, int* min, int* sec);

/* wxNotebookEvent */
TClassDefExtend(wxNotebookEvent, wxNotifyEvent)

    /* wxNotebookSizer */
    /* Class removed from wxWidgets >= 2.8 */

    /* wxNotifyEvent */
    TClassDefExtend(wxNotifyEvent,
                    wxCommandEvent) void wxNotifyEvent_Allow(TSelf(wxNotifyEvent) pObject);
void wxNotifyEvent_CopyObject(TSelf(wxNotifyEvent) pObject, void* object_dest);
TBool wxNotifyEvent_IsAllowed(TSelf(wxNotifyEvent) pObject);
void wxNotifyEvent_Veto(TSelf(wxNotifyEvent) pObject);

/* wxObject */
TClassDef(wxObject)

    /* wxObjectRefData */
    TClassDef(wxObjectRefData)

    /* wxOutputStream */
    TClassDefExtend(wxOutputStream,
                    wxStreamBase) void wxOutputStream_Delete(TSelf(wxOutputStream) pObject);
int wxOutputStream_LastWrite(TSelf(wxOutputStream) pObject);
void wxOutputStream_PutC(TSelf(wxOutputStream) pObject, TChar character);
int wxOutputStream_Seek(TSelf(wxOutputStream) pObject, int pos, int mode);
void wxOutputStream_Sync(TSelf(wxOutputStream) pObject);
int wxOutputStream_Tell(TSelf(wxOutputStream) pObject);
void wxOutputStream_Write(TSelf(wxOutputStream) pObject, void* buffer, int size);

/* wxPageSetupDialog */
TClassDefExtend(wxPageSetupDialog, wxObject) TClass(wxPageSetupDialog)
    wxPageSetupDialog_Create(TClass(wxWindow) parent, TClass(wxPageSetupDialogData) data);
void wxPageSetupDialog_GetPageSetupData(TSelf(wxPageSetupDialog) pObject,
                                        TClassRef(wxPageSetupDialogData) ref);
int wxPageSetupDialog_ShowModal(TSelf(wxPageSetupDialog) pObject);

/* wxPageSetupDialogData */
TClassDefExtend(wxPageSetupDialogData,
                wxObject) void wxPageSetupDialogData_Assign(TSelf(wxPageSetupDialogData) pObject,
                                                            TClassRef(wxPageSetupDialogData) data);
void wxPageSetupDialogData_AssignData(TSelf(wxPageSetupDialogData) pObject,
                                      TClass(wxPrintData) printData);
void wxPageSetupDialogData_CalculateIdFromPaperSize(TSelf(wxPageSetupDialogData) pObject);
void wxPageSetupDialogData_CalculatePaperSizeFromId(TSelf(wxPageSetupDialogData) pObject);
TClass(wxPageSetupDialogData) wxPageSetupDialogData_Create();
TClass(wxPageSetupDialogData) wxPageSetupDialogData_CreateFromData(TClass(wxPrintData) printData);
void wxPageSetupDialogData_Delete(TSelf(wxPageSetupDialogData) pObject);
void wxPageSetupDialogData_EnableHelp(TSelf(wxPageSetupDialogData) pObject, TBool flag);
void wxPageSetupDialogData_EnableMargins(TSelf(wxPageSetupDialogData) pObject, TBool flag);
void wxPageSetupDialogData_EnableOrientation(TSelf(wxPageSetupDialogData) pObject, TBool flag);
void wxPageSetupDialogData_EnablePaper(TSelf(wxPageSetupDialogData) pObject, TBool flag);
void wxPageSetupDialogData_EnablePrinter(TSelf(wxPageSetupDialogData) pObject, TBool flag);
TBool wxPageSetupDialogData_GetDefaultInfo(TSelf(wxPageSetupDialogData) pObject);
TBool wxPageSetupDialogData_GetDefaultMinMargins(TSelf(wxPageSetupDialogData) pObject);
TBool wxPageSetupDialogData_GetEnableHelp(TSelf(wxPageSetupDialogData) pObject);
TBool wxPageSetupDialogData_GetEnableMargins(TSelf(wxPageSetupDialogData) pObject);
TBool wxPageSetupDialogData_GetEnableOrientation(TSelf(wxPageSetupDialogData) pObject);
TBool wxPageSetupDialogData_GetEnablePaper(TSelf(wxPageSetupDialogData) pObject);
TBool wxPageSetupDialogData_GetEnablePrinter(TSelf(wxPageSetupDialogData) pObject);
TClass(wxPoint) wxPageSetupDialogData_GetMarginBottomRight(TSelf(wxPageSetupDialogData) pObject);
TClass(wxPoint) wxPageSetupDialogData_GetMarginTopLeft(TSelf(wxPageSetupDialogData) pObject);
TClass(wxPoint) wxPageSetupDialogData_GetMinMarginBottomRight(TSelf(wxPageSetupDialogData) pObject);
TClass(wxPoint) wxPageSetupDialogData_GetMinMarginTopLeft(TSelf(wxPageSetupDialogData) pObject);
int wxPageSetupDialogData_GetPaperId(TSelf(wxPageSetupDialogData) pObject);
TClass(wxSize) wxPageSetupDialogData_GetPaperSize(TSelf(wxPageSetupDialogData) pObject);
void wxPageSetupDialogData_GetPrintData(TSelf(wxPageSetupDialogData) pObject,
                                        TClassRef(wxPrintData) ref);
void wxPageSetupDialogData_SetDefaultInfo(TSelf(wxPageSetupDialogData) pObject, TBool flag);
void wxPageSetupDialogData_SetDefaultMinMargins(TSelf(wxPageSetupDialogData) pObject, int flag);
void wxPageSetupDialogData_SetMarginBottomRight(TSelf(wxPageSetupDialogData) pObject, TPoint(x, y));
void wxPageSetupDialogData_SetMarginTopLeft(TSelf(wxPageSetupDialogData) pObject, TPoint(x, y));
void wxPageSetupDialogData_SetMinMarginBottomRight(TSelf(wxPageSetupDialogData) pObject,
                                                   TPoint(x, y));
void wxPageSetupDialogData_SetMinMarginTopLeft(TSelf(wxPageSetupDialogData) pObject, TPoint(x, y));
void wxPageSetupDialogData_SetPaperId(TSelf(wxPageSetupDialogData) pObject, void* id);
void wxPageSetupDialogData_SetPaperSize(TSelf(wxPageSetupDialogData) pObject, TSize(width, height));
void wxPageSetupDialogData_SetPaperSizeId(TSelf(wxPageSetupDialogData) pObject, int id);
void wxPageSetupDialogData_SetPrintData(TSelf(wxPageSetupDialogData) pObject,
                                        TClass(wxPrintData) printData);

/* wxPaintDC */
TClassDefExtend(wxPaintDC, wxWindowDC) TClass(wxPaintDC) wxPaintDC_Create(TClass(wxWindow) win);
void wxPaintDC_Delete(TSelf(wxPaintDC) pObject);

/* wxPaintEvent */
TClassDefExtend(wxPaintEvent, wxEvent)

    /* wxPalette */
    TClassDefExtend(wxPalette, wxGDIObject) void wxPalette_Assign(TSelf(wxPalette) pObject,
                                                                  TClass(wxPalette) palette);
TClass(wxPalette) wxPalette_CreateDefault();
TClass(wxPalette) wxPalette_CreateRGB(int count, void* red, void* green, void* blue);
void wxPalette_Delete(TSelf(wxPalette) pObject);
int wxPalette_GetPixel(TSelf(wxPalette) pObject, TColorRGB(red, green, blue));
TBool wxPalette_GetRGB(TSelf(wxPalette) pObject, int pixel, void* red, void* green, void* blue);
TBool wxPalette_IsEqual(TSelf(wxPalette) pObject, TClass(wxPalette) palette);
TBool wxPalette_IsOk(TSelf(wxPalette) pObject);

/* wxPaletteChangedEvent */
TClassDefExtend(wxPaletteChangedEvent,
                wxEvent) void wxPaletteChangedEvent_CopyObject(TSelf(wxPaletteChangedEvent) pObject,
                                                               void* obj);
void* wxPaletteChangedEvent_GetChangedWindow(TSelf(wxPaletteChangedEvent) pObject);
void wxPaletteChangedEvent_SetChangedWindow(TSelf(wxPaletteChangedEvent) pObject,
                                            TClass(wxWindow) win);

/* wxPanel */
TClassDefExtend(wxPanel, wxWindow) TClass(wxPanel)
    wxPanel_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height), int style);
void wxPanel_InitDialog(TSelf(wxPanel) pObject);
void wxPanel_SetFocus(TSelf(wxPanel) pObject);

/* wxPathList */
TClassDefExtend(wxPathList, wxList)

    /* wxPen */
    TClassDefExtend(wxPen, wxGDIObject) void wxPen_Assign(TSelf(wxPen) pObject, TClass(wxPen) pen);
TClass(wxPen) wxPen_CreateDefault();
TClass(wxPen) wxPen_CreateFromBitmap(TClass(wxBitmap) stipple, int width);
TClass(wxPen) wxPen_CreateFromColour(TClass(wxColour) col, int width, int style);
TClass(wxPen) wxPen_CreateFromStock(int id);
void wxPen_Delete(TSelf(wxPen) pObject);
int wxPen_GetCap(TSelf(wxPen) pObject);
void wxPen_GetColour(TSelf(wxPen) pObject, TClassRef(wxColour) ref);
int wxPen_GetDashes(TSelf(wxPen) pObject, void* ptr);
int wxPen_GetJoin(TSelf(wxPen) pObject);
void wxPen_GetStipple(TSelf(wxPen) pObject, TClassRef(wxBitmap) ref);
int wxPen_GetStyle(TSelf(wxPen) pObject);
int wxPen_GetWidth(TSelf(wxPen) pObject);
TBool wxPen_IsEqual(TSelf(wxPen) pObject, TClass(wxPen) pen);
TBool wxPen_IsOk(TSelf(wxPen) pObject);
void wxPen_SetCap(TSelf(wxPen) pObject, int cap);
void wxPen_SetColour(TSelf(wxPen) pObject, TClass(wxColour) col);
void wxPen_SetColourSingle(TSelf(wxPen) pObject, TChar red, TChar green, TChar blue);
void wxPen_SetDashes(TSelf(wxPen) pObject, int nb_dashes, void* dash);
void wxPen_SetJoin(TSelf(wxPen) pObject, int join);
void wxPen_SetStipple(TSelf(wxPen) pObject, TClass(wxBitmap) stipple);
void wxPen_SetStyle(TSelf(wxPen) pObject, int style);
void wxPen_SetWidth(TSelf(wxPen) pObject, int width);

/* wxPenList */
TClassDefExtend(wxPenList, wxList)

    /* wxPlotCurve */
    TClassDefExtend(wxPlotCurve, wxObject)

    /* wxPlotEvent */
    TClassDefExtend(wxPlotEvent,
                    wxNotifyEvent) void* wxPlotEvent_GetCurve(TSelf(wxPlotEvent) pObject);
int wxPlotEvent_GetPosition(TSelf(wxPlotEvent) pObject);
double wxPlotEvent_GetZoom(TSelf(wxPlotEvent) pObject);
void wxPlotEvent_SetPosition(TSelf(wxPlotEvent) pObject, int pos);
void wxPlotEvent_SetZoom(TSelf(wxPlotEvent) pObject, double zoom);

/* wxPlotOnOffCurve */
TClassDefExtend(wxPlotOnOffCurve,
                wxObject) void wxPlotOnOffCurve_Add(TSelf(wxPlotOnOffCurve) pObject, int onPos,
                                                    int offPos, TClass(wxClientData) clientData);
TClass(wxPlotOnOffCurve) wxPlotOnOffCurve_Create(int offsetY);
void wxPlotOnOffCurve_Delete(TSelf(wxPlotOnOffCurve) pObject);
void wxPlotOnOffCurve_DrawOffLine(TSelf(wxPlotOnOffCurve) pObject, TClass(wxDC) dc, int y,
                                  int start, int end);
void wxPlotOnOffCurve_DrawOnLine(TSelf(wxPlotOnOffCurve) pObject, TClass(wxDC) dc, int y, int start,
                                 int end, TClass(wxClientData) clientData);
void* wxPlotOnOffCurve_GetAt(TSelf(wxPlotOnOffCurve) pObject, int index);
TClass(wxClientData) wxPlotOnOffCurve_GetClientData(TSelf(wxPlotOnOffCurve) pObject, int index);
int wxPlotOnOffCurve_GetCount(TSelf(wxPlotOnOffCurve) pObject);
int wxPlotOnOffCurve_GetEndX(TSelf(wxPlotOnOffCurve) pObject);
int wxPlotOnOffCurve_GetOff(TSelf(wxPlotOnOffCurve) pObject, int index);
int wxPlotOnOffCurve_GetOffsetY(TSelf(wxPlotOnOffCurve) pObject);
int wxPlotOnOffCurve_GetOn(TSelf(wxPlotOnOffCurve) pObject, int index);
int wxPlotOnOffCurve_GetStartX(TSelf(wxPlotOnOffCurve) pObject);
void wxPlotOnOffCurve_SetOffsetY(TSelf(wxPlotOnOffCurve) pObject, int offsetY);

/* wxPlotWindow */
TClassDefExtend(wxPlotWindow, wxScrolledWindow) void wxPlotWindow_Add(TSelf(wxPlotWindow) pObject,
                                                                      TClass(wxPlotCurve) curve);
void wxPlotWindow_AddOnOff(TSelf(wxPlotWindow) pObject, TClass(wxPlotCurve) curve);
TClass(wxPlotWindow)
    wxPlotWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int flags);
void wxPlotWindow_Delete(TSelf(wxPlotWindow) pObject, TClass(wxPlotCurve) curve);
void wxPlotWindow_DeleteOnOff(TSelf(wxPlotWindow) pObject, TClass(wxPlotOnOffCurve) curve);
void wxPlotWindow_Enlarge(TSelf(wxPlotWindow) pObject, TClass(wxPlotCurve) curve, double factor);
TClass(wxPlotCurve) wxPlotWindow_GetAt(TSelf(wxPlotWindow) pObject, int index);
int wxPlotWindow_GetCount(TSelf(wxPlotWindow) pObject);
TClass(wxPlotCurve) wxPlotWindow_GetCurrent(TSelf(wxPlotWindow) pObject);
int wxPlotWindow_GetEnlargeAroundWindowCentre(TSelf(wxPlotWindow) pObject);
TClass(wxPlotOnOffCurve) wxPlotWindow_GetOnOffCurveAt(TSelf(wxPlotWindow) pObject, int index);
int wxPlotWindow_GetOnOffCurveCount(TSelf(wxPlotWindow) pObject);
int wxPlotWindow_GetScrollOnThumbRelease(TSelf(wxPlotWindow) pObject);
double wxPlotWindow_GetUnitsPerValue(TSelf(wxPlotWindow) pObject);
double wxPlotWindow_GetZoom(TSelf(wxPlotWindow) pObject);
void wxPlotWindow_Move(TSelf(wxPlotWindow) pObject, TClass(wxPlotCurve) curve, int pixels_up);
void wxPlotWindow_RedrawEverything(TSelf(wxPlotWindow) pObject);
void wxPlotWindow_RedrawXAxis(TSelf(wxPlotWindow) pObject);
void wxPlotWindow_RedrawYAxis(TSelf(wxPlotWindow) pObject);
void wxPlotWindow_ResetScrollbar(TSelf(wxPlotWindow) pObject);
void wxPlotWindow_SetCurrent(TSelf(wxPlotWindow) pObject, TClass(wxPlotCurve) current);
void wxPlotWindow_SetEnlargeAroundWindowCentre(TSelf(wxPlotWindow) pObject,
                                               int enlargeAroundWindowCentre);
void wxPlotWindow_SetScrollOnThumbRelease(TSelf(wxPlotWindow) pObject, int scrollOnThumbRelease);
void wxPlotWindow_SetUnitsPerValue(TSelf(wxPlotWindow) pObject, double upv);
void wxPlotWindow_SetZoom(TSelf(wxPlotWindow) pObject, double zoom);

/* wxPoint */
TClassDef(wxPoint) TClass(wxPoint) wxPoint_Create(TPoint(xx, yy));
void wxPoint_Destroy(TSelf(wxPoint) pObject);
int wxPoint_GetX(TSelf(wxPoint) pObject);
int wxPoint_GetY(TSelf(wxPoint) pObject);
void wxPoint_SetX(TSelf(wxPoint) pObject, int width);
void wxPoint_SetY(TSelf(wxPoint) pObject, int height);

/* wxPopupTransientWindow */
TClassDefExtend(wxPopupTransientWindow, wxPopupWindow)

    /* wxPopupWindow */
    TClassDefExtend(wxPopupWindow, wxWindow)

    /* wxPostScriptDC */
    TClassDefExtend(wxPostScriptDC, wxDC) TClass(wxPostScriptDC)
        wxPostScriptDC_Create(TClass(wxPrintData) data);
void wxPostScriptDC_Delete(TSelf(wxPostScriptDC) self);
void wxPostScriptDC_SetResolution(TSelf(wxPostScriptDC) self, int ppi);
int wxPostScriptDC_GetResolution(TSelf(wxPostScriptDC) self);

/* wxPreviewCanvas */
TClassDefExtend(wxPreviewCanvas, wxScrolledWindow) TClass(wxPreviewCanvas)
    wxPreviewCanvas_Create(TClass(wxPrintPreview) preview, TClass(wxWindow) parent,
                           TRect(x, y, width, height), int style);

/* wxPreviewControlBar */
TClassDefExtend(wxPreviewControlBar, wxPanel)

    /* wxPreviewFrame */
    TClassDefExtend(wxPreviewFrame, wxFrame)

    /* wxPrintData */
    TClassDefExtend(wxPrintData, wxObject) void wxPrintData_Assign(TSelf(wxPrintData) pObject,
                                                                   TClass(wxPrintData) data);
TClass(wxPrintData) wxPrintData_Create();
void wxPrintData_Delete(TSelf(wxPrintData) pObject);
TBool wxPrintData_GetCollate(TSelf(wxPrintData) pObject);
TBool wxPrintData_GetColour(TSelf(wxPrintData) pObject);
int wxPrintData_GetDuplex(TSelf(wxPrintData) pObject);
TClass(wxString) wxPrintData_GetFilename(TSelf(wxPrintData) pObject);
TClass(wxString) wxPrintData_GetFontMetricPath(TSelf(wxPrintData) pObject);
int wxPrintData_GetNoCopies(TSelf(wxPrintData) pObject);
int wxPrintData_GetOrientation(TSelf(wxPrintData) pObject);
int wxPrintData_GetPaperId(TSelf(wxPrintData) pObject);
TClass(wxSize) wxPrintData_GetPaperSize(TSelf(wxPrintData) pObject);
TClass(wxString) wxPrintData_GetPreviewCommand(TSelf(wxPrintData) pObject);
int wxPrintData_GetPrintMode(TSelf(wxPrintData) pObject);
TClass(wxString) wxPrintData_GetPrinterCommand(TSelf(wxPrintData) pObject);
TClass(wxString) wxPrintData_GetPrinterName(TSelf(wxPrintData) pObject);
TClass(wxString) wxPrintData_GetPrinterOptions(TSelf(wxPrintData) pObject);
double wxPrintData_GetPrinterScaleX(TSelf(wxPrintData) pObject);
double wxPrintData_GetPrinterScaleY(TSelf(wxPrintData) pObject);
int wxPrintData_GetPrinterTranslateX(TSelf(wxPrintData) pObject);
int wxPrintData_GetPrinterTranslateY(TSelf(wxPrintData) pObject);
int wxPrintData_GetQuality(TSelf(wxPrintData) pObject);
void wxPrintData_SetCollate(TSelf(wxPrintData) pObject, TBoolInt flag);
void wxPrintData_SetColour(TSelf(wxPrintData) pObject, TBoolInt colour);
void wxPrintData_SetDuplex(TSelf(wxPrintData) pObject, int duplex);
void wxPrintData_SetFilename(TSelf(wxPrintData) pObject, TClass(wxString) filename);
void wxPrintData_SetFontMetricPath(TSelf(wxPrintData) pObject, TClass(wxString) path);
void wxPrintData_SetNoCopies(TSelf(wxPrintData) pObject, int value);
// void       wxPrintData_SetOrientation( TSelf(wxPrintData) pObject,
// wxPrintOrientation orient );
void wxPrintData_SetOrientation(TSelf(wxPrintData) pObject, int orient);
void wxPrintData_SetPaperId(TSelf(wxPrintData) pObject, int sizeId);
void wxPrintData_SetPaperSize(TSelf(wxPrintData) pObject, TSize(width, height));
void wxPrintData_SetPreviewCommand(TSelf(wxPrintData) pObject, TClass(wxCommand) command);
void wxPrintData_SetPrintMode(TSelf(wxPrintData) pObject, int printMode);
void wxPrintData_SetPrinterCommand(TSelf(wxPrintData) pObject, TClass(wxCommand) command);
void wxPrintData_SetPrinterName(TSelf(wxPrintData) pObject, TClass(wxString) name);
void wxPrintData_SetPrinterOptions(TSelf(wxPrintData) pObject, TClass(wxString) options);
void wxPrintData_SetPrinterScaleX(TSelf(wxPrintData) pObject, double x);
void wxPrintData_SetPrinterScaleY(TSelf(wxPrintData) pObject, double y);
void wxPrintData_SetPrinterScaling(TSelf(wxPrintData) pObject, double x, double y);
void wxPrintData_SetPrinterTranslateX(TSelf(wxPrintData) pObject, int x);
void wxPrintData_SetPrinterTranslateY(TSelf(wxPrintData) pObject, int y);
void wxPrintData_SetPrinterTranslation(TSelf(wxPrintData) pObject, TPoint(x, y));
void wxPrintData_SetQuality(TSelf(wxPrintData) pObject, int quality);

/* wxPostScriptPrintNativeData */
TClassDefExtend(wxPostScriptPrintNativeData, wxObject) TClass(wxPostScriptPrintNativeData)
    wxPostScriptPrintNativeData_Create();
void wxPostScriptPrintNativeData_Delete(TSelf(wxPostScriptPrintNativeData) pObject);

/* wxPrintDialog */
TClassDefExtend(wxPrintDialog, wxDialog) TClass(wxPrintDialog)
    wxPrintDialog_Create(TClass(wxWindow) parent, TClass(wxPrintDialogData) data);
TClass(wxDC) wxPrintDialog_GetPrintDC(TSelf(wxPrintDialog) pObject);
void wxPrintDialog_GetPrintData(TSelf(wxPrintDialog) pObject, TClassRef(wxPrintData) ref);
TClass(wxPrintDialogData) wxPrintDialog_GetPrintDialogData(TSelf(wxPrintDialog) pObject);

/* wxPrintDialogData */
TClassDefExtend(wxPrintDialogData,
                wxObject) void wxPrintDialogData_Assign(TSelf(wxPrintDialogData) pObject,
                                                        TClass(wxPrintDialogData) data);
void wxPrintDialogData_AssignData(TSelf(wxPrintDialogData) pObject, TClass(wxPrintData) data);
TClass(wxPrintDialogData) wxPrintDialogData_CreateDefault();
TClass(wxPrintDialogData) wxPrintDialogData_CreateFromData(TClass(wxPrintData) printData);
void wxPrintDialogData_Delete(TSelf(wxPrintDialogData) pObject);
void wxPrintDialogData_EnableHelp(TSelf(wxPrintDialogData) pObject, TBool flag);
void wxPrintDialogData_EnablePageNumbers(TSelf(wxPrintDialogData) pObject, TBool flag);
void wxPrintDialogData_EnablePrintToFile(TSelf(wxPrintDialogData) pObject, TBool flag);
void wxPrintDialogData_EnableSelection(TSelf(wxPrintDialogData) pObject, TBool flag);
int wxPrintDialogData_GetAllPages(TSelf(wxPrintDialogData) pObject);
TBool wxPrintDialogData_GetCollate(TSelf(wxPrintDialogData) pObject);
TBool wxPrintDialogData_GetEnableHelp(TSelf(wxPrintDialogData) pObject);
TBool wxPrintDialogData_GetEnablePageNumbers(TSelf(wxPrintDialogData) pObject);
TBool wxPrintDialogData_GetEnablePrintToFile(TSelf(wxPrintDialogData) pObject);
TBool wxPrintDialogData_GetEnableSelection(TSelf(wxPrintDialogData) pObject);
int wxPrintDialogData_GetFromPage(TSelf(wxPrintDialogData) pObject);
int wxPrintDialogData_GetMaxPage(TSelf(wxPrintDialogData) pObject);
int wxPrintDialogData_GetMinPage(TSelf(wxPrintDialogData) pObject);
int wxPrintDialogData_GetNoCopies(TSelf(wxPrintDialogData) pObject);
void wxPrintDialogData_GetPrintData(TSelf(wxPrintDialogData) pObject, TClassRef(wxPrintData) ref);
TBool wxPrintDialogData_GetPrintToFile(TSelf(wxPrintDialogData) pObject);
TBool wxPrintDialogData_GetSelection(TSelf(wxPrintDialogData) pObject);
int wxPrintDialogData_GetToPage(TSelf(wxPrintDialogData) pObject);
void wxPrintDialogData_SetAllPages(TSelf(wxPrintDialogData) pObject, TBool flag);
void wxPrintDialogData_SetCollate(TSelf(wxPrintDialogData) pObject, TBool flag);
void wxPrintDialogData_SetFromPage(TSelf(wxPrintDialogData) pObject, int value);
void wxPrintDialogData_SetMaxPage(TSelf(wxPrintDialogData) pObject, int value);
void wxPrintDialogData_SetMinPage(TSelf(wxPrintDialogData) pObject, int value);
void wxPrintDialogData_SetNoCopies(TSelf(wxPrintDialogData) pObject, int value);
void wxPrintDialogData_SetPrintData(TSelf(wxPrintDialogData) pObject,
                                    TClass(wxPrintData) printData);
void wxPrintDialogData_SetPrintToFile(TSelf(wxPrintDialogData) pObject, TBool flag);
void wxPrintDialogData_SetSelection(TSelf(wxPrintDialogData) pObject, TBool flag);
void wxPrintDialogData_SetToPage(TSelf(wxPrintDialogData) pObject, int value);

/* wxPrintPreview */
TClassDefExtend(wxPrintPreview, wxObject) TClass(wxPrintPreview)
    wxPrintPreview_CreateFromData(TClass(wxPrintout) printout,
                                  TClass(wxPrintout) printoutForPrinting, TClass(wxPrintData) data);
TClass(wxPrintPreview) wxPrintPreview_CreateFromDialogData(TClass(wxPrintout) printout,
                                                           TClass(wxPrintout) printoutForPrinting,
                                                           TClass(wxPrintDialogData) data);
void wxPrintPreview_Delete(TSelf(wxPrintPreview) pObject);
void wxPrintPreview_DetermineScaling(TSelf(wxPrintPreview) pObject);
TBool wxPrintPreview_DrawBlankPage(TSelf(wxPrintPreview) pObject, TClass(wxPreviewCanvas) canvas,
                                   TClass(wxDC) dc);
TClass(wxPreviewCanvas) wxPrintPreview_GetCanvas(TSelf(wxPrintPreview) pObject);
int wxPrintPreview_GetCurrentPage(TSelf(wxPrintPreview) pObject);
TClass(wxFrame) wxPrintPreview_GetFrame(TSelf(wxPrintPreview) pObject);
int wxPrintPreview_GetMaxPage(TSelf(wxPrintPreview) pObject);
int wxPrintPreview_GetMinPage(TSelf(wxPrintPreview) pObject);
void wxPrintPreview_GetPrintDialogData(TSelf(wxPrintPreview) pObject,
                                       TClassRef(wxPrintDialogData) ref);
TClass(wxPrintout) wxPrintPreview_GetPrintout(TSelf(wxPrintPreview) pObject);
TClass(wxPrintout) wxPrintPreview_GetPrintoutForPrinting(TSelf(wxPrintPreview) pObject);
int wxPrintPreview_GetZoom(TSelf(wxPrintPreview) pObject);
TBool wxPrintPreview_IsOk(TSelf(wxPrintPreview) pObject);
TBool wxPrintPreview_PaintPage(TSelf(wxPrintPreview) pObject, TClass(wxPrintPreview) canvas,
                               TClass(wxDC) dc);
TBool wxPrintPreview_Print(TSelf(wxPrintPreview) pObject, TBool interactive);
TBool wxPrintPreview_RenderPage(TSelf(wxPrintPreview) pObject, int pageNum);
void wxPrintPreview_SetCanvas(TSelf(wxPrintPreview) pObject, TClass(wxPreviewCanvas) canvas);
TBool wxPrintPreview_SetCurrentPage(TSelf(wxPrintPreview) pObject, int pageNum);
void wxPrintPreview_SetFrame(TSelf(wxPrintPreview) pObject, TClass(wxFrame) frame);
void wxPrintPreview_SetOk(TSelf(wxPrintPreview) pObject, TBool isOk);
void wxPrintPreview_SetPrintout(TSelf(wxPrintPreview) pObject, TClass(wxPrintout) printout);
void wxPrintPreview_SetZoom(TSelf(wxPrintPreview) pObject, int percent);

/* wxPrinter */
TClassDefExtend(wxPrinter, wxObject) TClass(wxPrinter)
    wxPrinter_Create(TClass(wxPrintDialogData) data);
TClass(wxWindow) wxPrinter_CreateAbortWindow(TSelf(wxPrinter) pObject, TClass(wxWindow) parent,
                                             TClass(wxPrintout) printout);
void wxPrinter_Delete(TSelf(wxPrinter) pObject);
TBool wxPrinter_GetAbort(TSelf(wxPrinter) pObject);
int wxPrinter_GetLastError(TSelf(wxPrinter) pObject);
void wxPrinter_GetPrintDialogData(TSelf(wxPrinter) pObject, TClassRef(wxPrintDialogData) ref);
TBool wxPrinter_Print(TSelf(wxPrinter) pObject, TClass(wxWindow) parent,
                      TClass(wxPrintout) printout, TBool prompt);
TClass(wxDC) wxPrinter_PrintDialog(TSelf(wxPrinter) pObject, TClass(wxWindow) parent);
void wxPrinter_ReportError(TSelf(wxPrinter) pObject, TClass(wxWindow) parent,
                           TClass(wxPrintout) printout, TClass(wxString) message);
TBool wxPrinter_Setup(TSelf(wxPrinter) pObject, TClass(wxWindow) parent);

/* wxPrinterDC */
TClassDefExtend(wxPrinterDC, wxDC) TClass(wxPrinterDC) wxPrinterDC_Create(TClass(wxPrintData) data);
void wxPrinterDC_Delete(TSelf(wxPrinterDC) self);
TClass(wxRect) wxPrinterDC_GetPaperRect(TSelf(wxPrinterDC) self);

/* wxPrintout */
TClassDefExtend(wxPrintout, wxObject)

    /* wxPrivateDropTarget */
    TClassDefExtend(wxPrivateDropTarget, wxDropTarget)

    /* wxProcess */
    TClassDefExtend(wxProcess, wxEvtHandler) void wxProcess_CloseOutput(TSelf(wxProcess) pObject);
TClass(wxProcess) wxProcess_CreateDefault(TClass(wxWindow) parent, int id);
TClass(wxProcess) wxProcess_CreateRedirect(TClass(wxWindow) parent, TBool redirect);
void wxProcess_Delete(TSelf(wxProcess) pObject);
void wxProcess_Detach(TSelf(wxProcess) pObject);
TClass(wxInputStream) wxProcess_GetErrorStream(TSelf(wxProcess) pObject);
TClass(wxInputStream) wxProcess_GetInputStream(TSelf(wxProcess) pObject);
TClass(wxOutputStream) wxProcess_GetOutputStream(TSelf(wxProcess) pObject);
TBool wxProcess_IsRedirected(TSelf(wxProcess) pObject);
void wxProcess_Redirect(TSelf(wxProcess) pObject);

/* wxProcessEvent */
TClassDefExtend(wxProcessEvent,
                wxEvent) int wxProcessEvent_GetExitCode(TSelf(wxProcessEvent) pObject);
int wxProcessEvent_GetPid(TSelf(wxProcessEvent) pObject);

/* wxPropertyGridManager */
TClassDefExtend(wxPropertyGridManager, wxPanel) TClass(wxPropertyGridManager)
    wxPropertyGridManager_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                                 int style);
TClass(wxPropertyGridPage)
    wxPropertyGridManager_AddPage(TSelf(wxPropertyGridManager) pObject, TClass(wxString) label,
                                  TClass(wxBitmapBundle) bmp);
TClass(wxPropertyGridPage)
    wxPropertyGridManager_InsertPage(TSelf(wxPropertyGridManager) pObject, int index,
                                     TClass(wxString) label, TClass(wxBitmapBundle) bmp);
TBool wxPropertyGridManager_RemovePage(TSelf(wxPropertyGridManager) pObject, int page);
void wxPropertyGridManager_ClearPage(TSelf(wxPropertyGridManager) pObject, int page);
int wxPropertyGridManager_GetPageCount(TSelf(wxPropertyGridManager) pObject);
TClass(wxPropertyGridPage)
    wxPropertyGridManager_GetPage(TSelf(wxPropertyGridManager) pObject, unsigned int index);
int wxPropertyGridManager_GetPageByName(TSelf(wxPropertyGridManager) pObject,
                                        TClass(wxString) name);
TClass(wxString) wxPropertyGridManager_GetPageName(TSelf(wxPropertyGridManager) pObject, int index);
int wxPropertyGridManager_GetSelectedPage(TSelf(wxPropertyGridManager) pObject);
void wxPropertyGridManager_SelectPage(TSelf(wxPropertyGridManager) pObject, int index);
void wxPropertyGridManager_SelectPageByLabel(TSelf(wxPropertyGridManager) pObject,
                                             TClass(wxString) label);
TClass(wxPropertyGrid) wxPropertyGridManager_GetGrid(TSelf(wxPropertyGridManager) pObject);
TClass(wxPropertyGridPage)
    wxPropertyGridManager_GetCurrentPage(TSelf(wxPropertyGridManager) pObject);
TClass(wxToolBar) wxPropertyGridManager_GetToolBar(TSelf(wxPropertyGridManager) pObject);
void wxPropertyGridManager_SetDescBoxHeight(TSelf(wxPropertyGridManager) pObject, int descBoxHeight,
                                            TBool refresh);
int wxPropertyGridManager_GetDescBoxHeight(TSelf(wxPropertyGridManager) pObject);
void wxPropertyGridManager_ShowHeader(TSelf(wxPropertyGridManager) pObject, TBool show);
TBool wxPropertyGridManager_IsAnyModified(TSelf(wxPropertyGridManager) pObject);
TBool wxPropertyGridManager_IsPageModified(TSelf(wxPropertyGridManager) pObject, size_t index);
void wxPropertyGridManager_Clear(TSelf(wxPropertyGridManager) pObject);

/* wxPropertyGridPage */
TClassDefExtend(wxPropertyGridPage,
                wxEvtHandler) void wxPropertyGridPage_Clear(TSelf(wxPropertyGridPage) pObject);
int wxPropertyGridPage_GetIndex(TSelf(wxPropertyGridPage) pObject);
TClass(wxPGProperty) wxPropertyGridPage_GetRoot(TSelf(wxPropertyGridPage) pObject);
int wxPropertyGridPage_GetSplitterPosition(TSelf(wxPropertyGridPage) pObject, int col);
void wxPropertyGridPage_SetSplitterPosition(TSelf(wxPropertyGridPage) pObject, int splitterPos,
                                            int col);

// Style constants
int expPGMAN_DEFAULT_STYLE();

/* wxPropertySheetDialog */
TClassDefExtend(wxPropertySheetDialog, wxDialog) TClass(wxPropertySheetDialog)
    wxPropertySheetDialog_Create(TClass(wxWindow) parent, int id, TClass(wxString) title, int x,
                                 int y, int width, int height, int style);
void wxPropertySheetDialog_CreateButtons(TSelf(wxPropertySheetDialog) pObject, int flags);
TClass(wxBookCtrlBase) wxPropertySheetDialog_GetBookCtrl(TSelf(wxPropertySheetDialog) pObject);
TClass(wxSizer) wxPropertySheetDialog_GetInnerSizer(TSelf(wxPropertySheetDialog) pObject);
void wxPropertySheetDialog_SetInnerSizer(TSelf(wxPropertySheetDialog) pObject,
                                         TClass(wxSizer) sizer);
void wxPropertySheetDialog_LayoutDialog(TSelf(wxPropertySheetDialog) pObject, int centreFlags);
int wxPropertySheetDialog_GetSheetStyle(TSelf(wxPropertySheetDialog) pObject);
void wxPropertySheetDialog_SetSheetStyle(TSelf(wxPropertySheetDialog) pObject, int style);
int wxPropertySheetDialog_GetSheetOuterBorder(TSelf(wxPropertySheetDialog) pObject);
void wxPropertySheetDialog_SetSheetOuterBorder(TSelf(wxPropertySheetDialog) pObject, int border);
int wxPropertySheetDialog_GetSheetInnerBorder(TSelf(wxPropertySheetDialog) pObject);
void wxPropertySheetDialog_SetSheetInnerBorder(TSelf(wxPropertySheetDialog) pObject, int border);

// Style constants
int expPROPSHEET_DEFAULT();
int expPROPSHEET_NOTEBOOK();
int expPROPSHEET_TOOLBOOK();
int expPROPSHEET_CHOICEBOOK();
int expPROPSHEET_LISTBOOK();
int expPROPSHEET_BUTTONTOOLBOOK();
int expPROPSHEET_TREEBOOK();
int expPROPSHEET_SHRINKTOFIT();

/* wxProgressDialog */
TClassDefExtend(wxProgressDialog, wxFrame)

    /* wxProtocol */
    TClassDefExtend(wxProtocol, wxSocketClient)

    /* wxQuantize */
    TClassDefExtend(wxQuantize, wxObject)

    /* wxQueryCol */
    TClassDefExtend(wxQueryCol, wxObject)

    /* wxQueryField */
    TClassDefExtend(wxQueryField, wxObject)

    /* wxQueryLayoutInfoEvent */
    TClassDefExtend(wxQueryLayoutInfoEvent, wxEvent) TClass(wxQueryLayoutInfoEvent)
        wxQueryLayoutInfoEvent_Create(int id);
int wxQueryLayoutInfoEvent_GetAlignment(TSelf(wxQueryLayoutInfoEvent) pObject);
int wxQueryLayoutInfoEvent_GetFlags(TSelf(wxQueryLayoutInfoEvent) pObject);
int wxQueryLayoutInfoEvent_GetOrientation(TSelf(wxQueryLayoutInfoEvent) pObject);
int wxQueryLayoutInfoEvent_GetRequestedLength(TSelf(wxQueryLayoutInfoEvent) pObject);
TClass(wxSize) wxQueryLayoutInfoEvent_GetSize(TSelf(wxQueryLayoutInfoEvent) pObject);
void wxQueryLayoutInfoEvent_SetAlignment(TSelf(wxQueryLayoutInfoEvent) pObject, int align);
void wxQueryLayoutInfoEvent_SetFlags(TSelf(wxQueryLayoutInfoEvent) pObject, int flags);
void wxQueryLayoutInfoEvent_SetOrientation(TSelf(wxQueryLayoutInfoEvent) pObject, int orient);
void wxQueryLayoutInfoEvent_SetRequestedLength(TSelf(wxQueryLayoutInfoEvent) pObject, int length);
void wxQueryLayoutInfoEvent_SetSize(TSelf(wxQueryLayoutInfoEvent) pObject, TSize(width, height));

/* wxQueryNewPaletteEvent */
TClassDefExtend(wxQueryNewPaletteEvent,
                wxEvent) void wxQueryNewPaletteEvent_CopyObject(TSelf(wxQueryNewPaletteEvent)
                                                                    pObject,
                                                                TClass(wxObject) obj);
TBool wxQueryNewPaletteEvent_GetPaletteRealized(TSelf(wxQueryNewPaletteEvent) pObject);
void wxQueryNewPaletteEvent_SetPaletteRealized(TSelf(wxQueryNewPaletteEvent) pObject,
                                               TBool realized);

/* wxRadioBox */
TClassDefExtend(wxRadioBox, wxControl) TClass(wxRadioBox)
    wxRadioBox_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                      TRect(left, top, width, height), TArrayString(n, strings), int dimension,
                      int style);
void wxRadioBox_EnableItem(TSelf(wxRadioBox) pObject, int item, TBool enable);
int wxRadioBox_FindString(TSelf(wxRadioBox) pObject, TClass(wxString) str);
TClass(wxString) wxRadioBox_GetItemLabel(TSelf(wxRadioBox) pObject, int item);
int wxRadioBox_GetNumberOfRowsOrCols(TSelf(wxRadioBox) pObject);
int wxRadioBox_GetSelection(TSelf(wxRadioBox) pObject);
TClass(wxString) wxRadioBox_GetStringSelection(TSelf(wxRadioBox) pObject);
int wxRadioBox_Number(TSelf(wxRadioBox) pObject);
void wxRadioBox_SetItemBitmap(TSelf(wxRadioBox) pObject, int item, TClass(wxBitmap) bitmap);
void wxRadioBox_SetItemLabel(TSelf(wxRadioBox) pObject, int item, TClass(wxString) label);
void wxRadioBox_SetNumberOfRowsOrCols(TSelf(wxRadioBox) pObject, int count);
void wxRadioBox_SetSelection(TSelf(wxRadioBox) pObject, int selection);
void wxRadioBox_SetStringSelection(TSelf(wxRadioBox) pObject, TClass(wxString) str);
void wxRadioBox_ShowItem(TSelf(wxRadioBox) pObject, int item, TBool show);

/* wxRadioButton */
TClassDefExtend(wxRadioButton, wxControl) TClass(wxRadioButton)
    wxRadioButton_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                         TRect(left, top, width, height), int style);
TBool wxRadioButton_GetValue(TSelf(wxRadioButton) pObject);
void wxRadioButton_SetValue(TSelf(wxRadioButton) pObject, TBool value);

/* wxRearrangeCtrl */
TClassDefExtend(wxRearrangeCtrl, wxPanel) TClass(wxRearrangeCtrl)
    wxRearrangeCtrl_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                           TClass(wxArrayInt) order, TClass(wxArrayString) items, int style);
TClass(wxArrayInt) wxRearrangeCtrl_GetCurrentOrder(TSelf(wxRearrangeCtrl) self);
TClass(wxRearrangeList) wxRearrangeCtrl_GetList(TSelf(wxRearrangeCtrl) self);
TBool wxRearrangeCtrl_CanMoveCurrentUp(TSelf(wxRearrangeCtrl) self);
TBool wxRearrangeCtrl_CanMoveCurrentDown(TSelf(wxRearrangeCtrl) self);
TBool wxRearrangeCtrl_MoveCurrentUp(TSelf(wxRearrangeCtrl) self);
TBool wxRearrangeCtrl_MoveCurrentDown(TSelf(wxRearrangeCtrl) self);

/* wxRibbonBar */
TClassDefExtend(wxRibbonBar, wxRibbonControl) TClass(wxRibbonBar)
    wxRibbonBar_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
void wxRibbonBar_DismissExpandedPanel(TSelf(wxRibbonBar) self);
TClass(wxRibbonPage) wxRibbonBar_GetPage(TSelf(wxRibbonBar) self, int index);
size_t wxRibbonBar_GetPageCount(TSelf(wxRibbonBar) self);
TBool wxRibbonBar_DeletePage(TSelf(wxRibbonBar) self, size_t index);
void wxRibbonBar_ClearPages(TSelf(wxRibbonBar) self);
int wxRibbonBar_GetActivePage(TSelf(wxRibbonBar) self);
void wxRibbonBar_SetActivePage_ByIndex(TSelf(wxRibbonBar) self, size_t page);
void wxRibbonBar_SetActivePage_ByPtr(TSelf(wxRibbonBar) self, TClass(wxRibbonPage) page);
void wxRibbonBar_Realize(TSelf(wxRibbonBar) self);
void wxRibbonBar_SetArtProvider(TSelf(wxRibbonBar) self, TClass(wxRibbonArtProvider) art);
TClass(wxRibbonArtProvider) wxRibbonBar_GetArtProvider(TSelf(wxRibbonBar) self);
WXFFI_EXPORT(int, expEVT_RIBBONBAR_PAGE_CHANGED)();
WXFFI_EXPORT(int, expEVT_RIBBONBAR_PAGE_CHANGING)();
WXFFI_EXPORT(int, expEVT_RIBBONBAR_TAB_MIDDLE_DOWN)();
WXFFI_EXPORT(int, expEVT_RIBBONBAR_TAB_MIDDLE_UP)();
WXFFI_EXPORT(int, expEVT_RIBBONBAR_TAB_RIGHT_DOWN)();
WXFFI_EXPORT(int, expEVT_RIBBONBAR_TAB_RIGHT_UP)();
WXFFI_EXPORT(int, expEVT_RIBBONBAR_TAB_LEFT_DCLICK)();
WXFFI_EXPORT(int, expEVT_RIBBONBAR_TOGGLED)();
WXFFI_EXPORT(int, expEVT_RIBBONBAR_HELP_CLICK)();
WXFFI_EXPORT(int, expRIBBON_BAR_DEFAULT_STYLE)();
WXFFI_EXPORT(int, expRIBBON_BAR_FOLDBAR_STYLE)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PAGE_LABELS)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PAGE_ICONS)();
WXFFI_EXPORT(int, expRIBBON_BAR_FLOW_HORIZONTAL)();
WXFFI_EXPORT(int, expRIBBON_BAR_FLOW_VERTICAL)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_PANEL_MINIMISE_BUTTONS)();
WXFFI_EXPORT(int, expRIBBON_BAR_ALWAYS_SHOW_TABS)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_TOGGLE_BUTTON)();
WXFFI_EXPORT(int, expRIBBON_BAR_SHOW_HELP_BUTTON)();

/* wxRibbonPage */
TClassDefExtend(wxRibbonPage, wxRibbonControl) TClass(wxRibbonPage)
    wxRibbonPage_Create(TClass(wxRibbonBar) parent, int id, TClass(wxString) label,
                        TClass(wxBitmap) icon, int style);
void wxRibbonPage_DismissExpandedPanel(TSelf(wxRibbonPage) self);
TBool wxRibbonPage_ScrollLines(TSelf(wxRibbonPage) self, int lines);
TBool wxRibbonPage_ScrollPixels(TSelf(wxRibbonPage) self, int pixels);
TClass(wxString) wxRibbonPage_GetLabel(TSelf(wxRibbonPage) self);
void wxRibbonPage_Realize(TSelf(wxRibbonPage) self);
TClass(wxSize) wxRibbonPage_GetMinSize(TSelf(wxRibbonPage) self);
void wxRibbonPage_SetArtProvider(TSelf(wxRibbonPage) self, TClass(wxRibbonArtProvider) art);
TClass(wxRibbonArtProvider) wxRibbonPage_GetArtProvider(TSelf(wxRibbonPage) self);

/* wxRibbonPanel */
TClassDefExtend(wxRibbonPanel, wxRibbonControl) TClass(wxRibbonPanel)
    wxRibbonPanel_Create(TClass(wxWindow) parent, int id, TClass(wxString) label,
                         TClass(wxBitmap) icon, TRect(x, y, width, height), int style);
TClass(wxString) wxRibbonPanel_GetLabel(TSelf(wxRibbonPanel) self);
TBool wxRibbonPanel_IsMinimised(TSelf(wxRibbonPanel) self);
TBool wxRibbonPanel_IsMinimised_AtSize(TSelf(wxRibbonPanel) self, int width, int height);
TBool wxRibbonPanel_IsHovered(TSelf(wxRibbonPanel) self);
TBool wxRibbonPanel_IsExtButtonHovered(TSelf(wxRibbonPanel) self);
TBool wxRibbonPanel_CanAutoMinimise(TSelf(wxRibbonPanel) self);
TBool wxRibbonPanel_ShowExpanded(TSelf(wxRibbonPanel) self);
TBool wxRibbonPanel_HideExpanded(TSelf(wxRibbonPanel) self);
void wxRibbonPanel_Realize(TSelf(wxRibbonPanel) self);
TClass(wxSize) wxRibbonPanel_GetMinSize(TSelf(wxRibbonPanel) self);
void wxRibbonPanel_SetArtProvider(TSelf(wxRibbonPanel) self, TClass(wxRibbonArtProvider) art);
TClass(wxRibbonArtProvider) wxRibbonPanel_GetArtProvider(TSelf(wxRibbonPanel) self);
WXFFI_EXPORT(int, expEVT_RIBBONPANEL_EXTBUTTON_ACTIVATED)();
WXFFI_EXPORT(int, expRIBBON_PANEL_DEFAULT_STYLE)();
WXFFI_EXPORT(int, expRIBBON_PANEL_NO_AUTO_MINIMISE)();
WXFFI_EXPORT(int, expRIBBON_PANEL_EXT_BUTTON)();
WXFFI_EXPORT(int, expRIBBON_PANEL_MINIMISE_BUTTON)();
WXFFI_EXPORT(int, expRIBBON_PANEL_STRETCH)();
WXFFI_EXPORT(int, expRIBBON_PANEL_FLEXIBLE)();

/* wxRibbonButtonBar */
TClassDefExtend(wxRibbonButtonBar, wxRibbonControl) TClass(wxRibbonButtonBar)
    wxRibbonButtonBar_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                             int style);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_AddButton(TSelf(wxRibbonButtonBar) self, int button_id,
                                TClass(wxString) label, TClass(wxBitmap) bitmap,
                                TClass(wxString) help_string, int kind,
                                TClass(wxBitmap) bitmap_small, TClass(wxBitmap) bitmap_disabled,
                                TClass(wxBitmap) bitmap_small_disabled);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_AddDropdownButton(TSelf(wxRibbonButtonBar) self, int button_id,
                                        TClass(wxString) label, TClass(wxBitmap) bitmap,
                                        TClass(wxString) help_string);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_AddHybridButton(TSelf(wxRibbonButtonBar) self, int button_id,
                                      TClass(wxString) label, TClass(wxBitmap) bitmap,
                                      TClass(wxString) help_string);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_AddToggleButton(TSelf(wxRibbonButtonBar) self, int button_id,
                                      TClass(wxString) label, TClass(wxBitmap) bitmap,
                                      TClass(wxString) help_string);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_InsertButton(TSelf(wxRibbonButtonBar) self, size_t pos, int button_id,
                                   TClass(wxString) label, TClass(wxBitmap) bitmap,
                                   TClass(wxString) help_string, int kind,
                                   TClass(wxBitmap) bitmap_small, TClass(wxBitmap) bitmap_disabled,
                                   TClass(wxBitmap) bitmap_small_disabled);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_InsertDropdownButton(TSelf(wxRibbonButtonBar) self, size_t pos, int button_id,
                                           TClass(wxString) label, TClass(wxBitmap) bitmap,
                                           TClass(wxString) help_string);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_InsertHybridButton(TSelf(wxRibbonButtonBar) self, size_t pos, int button_id,
                                         TClass(wxString) label, TClass(wxBitmap) bitmap,
                                         TClass(wxString) help_string);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_InsertToggleButton(TSelf(wxRibbonButtonBar) self, size_t pos, int button_id,
                                         TClass(wxString) label, TClass(wxBitmap) bitmap,
                                         TClass(wxString) help_string);
void wxRibbonButtonBar_ClearButtons(TSelf(wxRibbonButtonBar) self);
TBool wxRibbonButtonBar_DeleteButton(TSelf(wxRibbonButtonBar) self, int button_id);
void wxRibbonButtonBar_EnableButton(TSelf(wxRibbonButtonBar) self, int button_id, TBool enable);
void wxRibbonButtonBar_SetButtonIcon(TSelf(wxRibbonButtonBar) self, int button_id,
                                     TClass(wxBitmap) bitmap, TClass(wxBitmap) bitmap_small,
                                     TClass(wxBitmap) bitmap_disabled,
                                     TClass(wxBitmap) bitmap_small_disabled);
void wxRibbonButtonBar_SetButtonText(TSelf(wxRibbonButtonBar) self, int button_id,
                                     TClass(wxString) label);
void wxRibbonButtonBar_SetButtonTextMinWidth_Int(TSelf(wxRibbonButtonBar) self, int button_id,
                                                 int min_width_medium, int min_width_large);
void wxRibbonButtonBar_SetButtonTextMinWidth_String(TSelf(wxRibbonButtonBar) self, int button_id,
                                                    TClass(wxString) label);
void wxRibbonButtonBar_SetButtonMinSizeClass(TSelf(wxRibbonButtonBar) self, int button_id,
                                             int min_class);
void wxRibbonButtonBar_SetButtonMaxSizeClass(TSelf(wxRibbonButtonBar) self, int button_id,
                                             int max_class);
size_t wxRibbonButtonBar_GetButtonCount(TSelf(wxRibbonButtonBar) self);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_GetItem(TSelf(wxRibbonButtonBar) self, size_t index);
TClass(wxRibbonButtonBarButtonBase)
    wxRibbonButtonBar_GetItemById(TSelf(wxRibbonButtonBar) self, int button_id);
int wxRibbonButtonBar_GetItemId(TSelf(wxRibbonButtonBar) self,
                                TClass(wxRibbonButtonBarButtonBase) button);
void wxRibbonButtonBar_GetItemRect(TSelf(wxRibbonButtonBar) self, int button_id, int* x, int* y,
                                   int* width, int* height);
TClass(wxRibbonButtonBarButtonBase) wxRibbonButtonBar_GetActiveItem(TSelf(wxRibbonButtonBar) self);
TClass(wxRibbonButtonBarButtonBase) wxRibbonButtonBar_GetHoveredItem(TSelf(wxRibbonButtonBar) self);
void wxRibbonButtonBar_SetItemClientData(TSelf(wxRibbonButtonBar) self,
                                         TClass(wxRibbonButtonBarButtonBase) item, void* data);
void* wxRibbonButtonBar_GetItemClientData(TSelf(wxRibbonButtonBar) self,
                                          TClass(wxRibbonButtonBarButtonBase) item);
void wxRibbonButtonBar_SetShowToolTipsForDisabled(TSelf(wxRibbonButtonBar) self, TBool show);
TBool wxRibbonButtonBar_GetShowToolTipsForDisabled(TSelf(wxRibbonButtonBar) self);
void wxRibbonButtonBar_Realize(TSelf(wxRibbonButtonBar) self);
void wxRibbonButtonBar_SetArtProvider(TSelf(wxRibbonButtonBar) self,
                                      TClass(wxRibbonArtProvider) art);
TClass(wxRibbonArtProvider) wxRibbonButtonBar_GetArtProvider(TSelf(wxRibbonButtonBar) self);
WXFFI_EXPORT(int, expEVT_RIBBONBUTTONBAR_CLICKED)();
WXFFI_EXPORT(int, expEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTON_NORMAL)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTON_DROPDOWN)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTON_HYBRID)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTON_TOGGLE)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTONBAR_BUTTON_SMALL)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTONBAR_BUTTON_MEDIUM)();
WXFFI_EXPORT(int, expwxRIBBON_BUTTONBAR_BUTTON_LARGE)();

/* wxRibbonGallery */
TClassDefExtend(wxRibbonGallery, wxRibbonControl) TClass(wxRibbonGallery)
    wxRibbonGallery_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
TClass(wxRibbonGalleryItem)
    wxRibbonGallery_Append(TSelf(wxRibbonGallery) self, TClass(wxBitmap) bitmap, int id);
TClass(wxRibbonGalleryItem)
    wxRibbonGallery_Append_WithClientData(TSelf(wxRibbonGallery) self, TClass(wxBitmap) bitmap,
                                          int id, void* clientData);
void wxRibbonGallery_Clear(TSelf(wxRibbonGallery) self);
TBool wxRibbonGallery_IsEmpty(TSelf(wxRibbonGallery) self);
unsigned int wxRibbonGallery_GetCount(TSelf(wxRibbonGallery) self);
TClass(wxRibbonGalleryItem)
    wxRibbonGallery_GetItem(TSelf(wxRibbonGallery) self, unsigned int index);
void wxRibbonGallery_SetSelection(TSelf(wxRibbonGallery) self, TClass(wxRibbonGalleryItem) item);
TClass(wxRibbonGalleryItem) wxRibbonGallery_GetSelection(TSelf(wxRibbonGallery) self);
TClass(wxRibbonGalleryItem) wxRibbonGallery_GetHoveredItem(TSelf(wxRibbonGallery) self);
TClass(wxRibbonGalleryItem) wxRibbonGallery_GetActiveItem(TSelf(wxRibbonGallery) self);
void wxRibbonGallery_SetItemClientData(TSelf(wxRibbonGallery) self,
                                       TClass(wxRibbonGalleryItem) item, void* data);
void* wxRibbonGallery_GetItemClientData(TSelf(wxRibbonGallery) self,
                                        TClass(wxRibbonGalleryItem) item);
TBool wxRibbonGallery_ScrollLines(TSelf(wxRibbonGallery) self, int lines);
TBool wxRibbonGallery_ScrollPixels(TSelf(wxRibbonGallery) self, int pixels);
void wxRibbonGallery_EnsureVisible(TSelf(wxRibbonGallery) self, TClass(wxRibbonGalleryItem) item);
int wxRibbonGallery_GetUpButtonState(TSelf(wxRibbonGallery) self);
int wxRibbonGallery_GetDownButtonState(TSelf(wxRibbonGallery) self);
int wxRibbonGallery_GetExtensionButtonState(TSelf(wxRibbonGallery) self);
TBool wxRibbonGallery_IsHovered(TSelf(wxRibbonGallery) self);
TBool wxRibbonGallery_IsSizingContinuous(TSelf(wxRibbonGallery) self);
void wxRibbonGallery_SetArtProvider(TSelf(wxRibbonGallery) self, TClass(wxRibbonArtProvider) art);
TClass(wxRibbonArtProvider) wxRibbonGallery_GetArtProvider(TSelf(wxRibbonGallery) self);
WXFFI_EXPORT(int, expEVT_RIBBONGALLERY_HOVER_CHANGED)();
WXFFI_EXPORT(int, expEVT_RIBBONGALLERY_SELECTED)();
WXFFI_EXPORT(int, expEVT_RIBBONGALLERY_CLICKED)();
WXFFI_EXPORT(int, expwxRIBBON_GALLERY_BUTTON_NORMAL)();
WXFFI_EXPORT(int, expwxRIBBON_GALLERY_BUTTON_HOVERED)();
WXFFI_EXPORT(int, expwxRIBBON_GALLERY_BUTTON_ACTIVE)();
WXFFI_EXPORT(int, expwxRIBBON_GALLERY_BUTTON_DISABLED)();

/* wxRibbonToolBar */
TClassDefExtend(wxRibbonToolBar, wxRibbonControl) TClass(wxRibbonToolBar)
    wxRibbonToolBar_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_AddTool(TSelf(wxRibbonToolBar) self, int tool_id, TClass(wxBitmap) bitmap,
                            TClass(wxString) help_string, int kind,
                            TClass(wxBitmap) bitmap_disabled, void* client_data);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_AddDropdownTool(TSelf(wxRibbonToolBar) self, int tool_id,
                                    TClass(wxBitmap) bitmap, TClass(wxString) help_string);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_AddHybridTool(TSelf(wxRibbonToolBar) self, int tool_id, TClass(wxBitmap) bitmap,
                                  TClass(wxString) help_string);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_AddToggleTool(TSelf(wxRibbonToolBar) self, int tool_id, TClass(wxBitmap) bitmap,
                                  TClass(wxString) help_string);
TClass(wxRibbonToolBarToolBase) wxRibbonToolBar_AddSeparator(TSelf(wxRibbonToolBar) self);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_InsertTool(TSelf(wxRibbonToolBar) self, size_t pos, int tool_id,
                               TClass(wxBitmap) bitmap, TClass(wxString) help_string, int kind,
                               TClass(wxBitmap) bitmap_disabled, void* client_data);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_InsertDropdownTool(TSelf(wxRibbonToolBar) self, size_t pos, int tool_id,
                                       TClass(wxBitmap) bitmap, TClass(wxString) help_string);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_InsertHybridTool(TSelf(wxRibbonToolBar) self, size_t pos, int tool_id,
                                     TClass(wxBitmap) bitmap, TClass(wxString) help_string);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_InsertToggleTool(TSelf(wxRibbonToolBar) self, size_t pos, int tool_id,
                                     TClass(wxBitmap) bitmap, TClass(wxString) help_string);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_InsertSeparator(TSelf(wxRibbonToolBar) self, size_t pos);
void wxRibbonToolBar_ClearTools(TSelf(wxRibbonToolBar) self);
TBool wxRibbonToolBar_DeleteTool(TSelf(wxRibbonToolBar) self, int tool_id);
TBool wxRibbonToolBar_DeleteToolByPos(TSelf(wxRibbonToolBar) self, size_t pos);
TClass(wxRibbonToolBarToolBase) wxRibbonToolBar_FindById(TSelf(wxRibbonToolBar) self, int tool_id);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_GetToolByPos(TSelf(wxRibbonToolBar) self, size_t pos);
TClass(wxRibbonToolBarToolBase)
    wxRibbonToolBar_GetToolByPos_Coords(TSelf(wxRibbonToolBar) self, int x, int y);
size_t wxRibbonToolBar_GetToolCount(TSelf(wxRibbonToolBar) self);
int wxRibbonToolBar_GetToolId(TSelf(wxRibbonToolBar) self, TClass(wxRibbonToolBarToolBase) tool);
TClass(wxRibbonToolBarToolBase) wxRibbonToolBar_GetActiveTool(TSelf(wxRibbonToolBar) self);
int wxRibbonToolBar_GetToolPos(TSelf(wxRibbonToolBar) self, int tool_id);
void wxRibbonToolBar_GetToolRect(TSelf(wxRibbonToolBar) self, int tool_id, int* x, int* y,
                                 int* width, int* height);
void wxRibbonToolBar_EnableTool(TSelf(wxRibbonToolBar) self, int tool_id, TBool enable);
TBool wxRibbonToolBar_GetToolEnabled(TSelf(wxRibbonToolBar) self, int tool_id);
TClass(wxString) wxRibbonToolBar_GetToolHelpString(TSelf(wxRibbonToolBar) self, int tool_id);
void wxRibbonToolBar_SetToolHelpString(TSelf(wxRibbonToolBar) self, int tool_id,
                                       TClass(wxString) help_string);
int wxRibbonToolBar_GetToolKind(TSelf(wxRibbonToolBar) self, int tool_id);
TBool wxRibbonToolBar_GetToolState(TSelf(wxRibbonToolBar) self, int tool_id);
void wxRibbonToolBar_SetToolNormalBitmap(TSelf(wxRibbonToolBar) self, int tool_id,
                                         TClass(wxBitmap) bitmap);
void wxRibbonToolBar_SetToolDisabledBitmap(TSelf(wxRibbonToolBar) self, int tool_id,
                                           TClass(wxBitmap) bitmap);
void wxRibbonToolBar_SetToolClientData(TSelf(wxRibbonToolBar) self, int tool_id,
                                       TClass(wxObject) clientData);
TClass(wxObject) wxRibbonToolBar_GetToolClientData(TSelf(wxRibbonToolBar) self, int tool_id);
void wxRibbonToolBar_SetRows(TSelf(wxRibbonToolBar) self, int nMin, int nMax);
void wxRibbonToolBar_Realize(TSelf(wxRibbonToolBar) self);
void wxRibbonToolBar_SetArtProvider(TSelf(wxRibbonToolBar) self, TClass(wxRibbonArtProvider) art);
TClass(wxRibbonArtProvider) wxRibbonToolBar_GetArtProvider(TSelf(wxRibbonToolBar) self);
WXFFI_EXPORT(int, expEVT_RIBBONTOOLBAR_CLICKED)();
WXFFI_EXPORT(int, expEVT_RIBBONTOOLBAR_DROPDOWN_CLICKED)();

/* wxRichTextCtrl */
TClassDefExtend(wxRichTextCtrl, wxControl) TClass(wxRichTextCtrl)
    wxRichTextCtrl_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
TClass(wxString) wxRichTextCtrl_GetValue(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetValue(TSelf(wxRichTextCtrl) self, TClass(wxString) value);
TClass(wxString) wxRichTextCtrl_GetRange(TSelf(wxRichTextCtrl) self, long from, long toPos);
int wxRichTextCtrl_GetLineLength(TSelf(wxRichTextCtrl) self, long lineNo);
TClass(wxString) wxRichTextCtrl_GetLineText(TSelf(wxRichTextCtrl) self, long lineNo);
int wxRichTextCtrl_GetNumberOfLines(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsModified(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_MarkDirty(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_DiscardEdits(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_IsEditable(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetEditable(TSelf(wxRichTextCtrl) self, TBool editable);
void wxRichTextCtrl_GetSelection(TSelf(wxRichTextCtrl) self, long* from, long* to);
void wxRichTextCtrl_SetSelection(TSelf(wxRichTextCtrl) self, long from, long toPos);
void wxRichTextCtrl_SelectAll(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SelectNone(TSelf(wxRichTextCtrl) self);
TClass(wxString) wxRichTextCtrl_GetStringSelection(TSelf(wxRichTextCtrl) self);
long wxRichTextCtrl_GetInsertionPoint(TSelf(wxRichTextCtrl) self);
long wxRichTextCtrl_GetLastPosition(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetInsertionPoint(TSelf(wxRichTextCtrl) self, long pos);
void wxRichTextCtrl_SetInsertionPointEnd(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_WriteText(TSelf(wxRichTextCtrl) self, TClass(wxString) text);
void wxRichTextCtrl_AppendText(TSelf(wxRichTextCtrl) self, TClass(wxString) text);
void wxRichTextCtrl_Clear(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_Replace(TSelf(wxRichTextCtrl) self, long from, long toPos,
                            TClass(wxString) value);
void wxRichTextCtrl_Remove(TSelf(wxRichTextCtrl) self, long from, long toPos);
TBool wxRichTextCtrl_LoadFile(TSelf(wxRichTextCtrl) self, TClass(wxString) file, int type);
TBool wxRichTextCtrl_SaveFile(TSelf(wxRichTextCtrl) self, TClass(wxString) file, int type);
TClass(wxString) wxRichTextCtrl_GetFilename(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_SetFilename(TSelf(wxRichTextCtrl) self, TClass(wxString) filename);
void wxRichTextCtrl_Undo(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_Redo(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_CanUndo(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_CanRedo(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_Copy(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_Cut(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_Paste(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_DeleteSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_CanCopy(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_CanCut(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_CanPaste(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_CanDeleteSelection(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_SetStyle(TSelf(wxRichTextCtrl) self, long start, long end,
                              TClass(wxTextAttr) style);
TBool wxRichTextCtrl_GetStyle(TSelf(wxRichTextCtrl) self, long position, TClass(wxTextAttr) style);
TBool wxRichTextCtrl_SetDefaultStyle(TSelf(wxRichTextCtrl) self, TClass(wxTextAttr) style);
TClass(wxTextAttr) wxRichTextCtrl_GetDefaultStyle(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_SetFont(TSelf(wxRichTextCtrl) self, TClass(wxFont) font);
TBool wxRichTextCtrl_SetFontStyle(TSelf(wxRichTextCtrl) self, long start, long end,
                                  TClass(wxFont) font);
long wxRichTextCtrl_XYToPosition(TSelf(wxRichTextCtrl) self, long x, long y);
TBool wxRichTextCtrl_PositionToXY(TSelf(wxRichTextCtrl) self, long pos, long* x, long* y);
void wxRichTextCtrl_ShowPosition(TSelf(wxRichTextCtrl) self, long position);
void wxRichTextCtrl_SetReadOnly(TSelf(wxRichTextCtrl) self, TBool readOnly);
TBool wxRichTextCtrl_IsReadOnly(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_LayoutContent(TSelf(wxRichTextCtrl) self, TBool onlyVisibleRect);
void wxRichTextCtrl_ForceDelayedLayout(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_ScrollIntoView(TSelf(wxRichTextCtrl) self, long position, int keyCode);
void wxRichTextCtrl_BeginBold(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_EndBold(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_BeginItalic(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_EndItalic(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_BeginUnderline(TSelf(wxRichTextCtrl) self);
void wxRichTextCtrl_EndUnderline(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginFontSize(TSelf(wxRichTextCtrl) self, int pointSize);
TBool wxRichTextCtrl_EndFontSize(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginFont(TSelf(wxRichTextCtrl) self, TClass(wxFont) font);
TBool wxRichTextCtrl_EndFont(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginTextColour(TSelf(wxRichTextCtrl) self, TClass(wxColour) colour);
TBool wxRichTextCtrl_EndTextColour(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginAlignment(TSelf(wxRichTextCtrl) self, int alignment);
TBool wxRichTextCtrl_EndAlignment(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginLeftIndent(TSelf(wxRichTextCtrl) self, int leftIndent, int leftSubIndent);
TBool wxRichTextCtrl_EndLeftIndent(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginRightIndent(TSelf(wxRichTextCtrl) self, int rightIndent);
TBool wxRichTextCtrl_EndRightIndent(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginParagraphSpacing(TSelf(wxRichTextCtrl) self, int before, int after);
TBool wxRichTextCtrl_EndParagraphSpacing(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginLineSpacing(TSelf(wxRichTextCtrl) self, int lineSpacing);
TBool wxRichTextCtrl_EndLineSpacing(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginNumberedBullet(TSelf(wxRichTextCtrl) self, int bulletNumber,
                                         int leftIndent, int leftSubIndent, int bulletStyle);
TBool wxRichTextCtrl_EndNumberedBullet(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginSymbolBullet(TSelf(wxRichTextCtrl) self, TClass(wxString) symbol,
                                       int leftIndent, int leftSubIndent, int bulletStyle);
TBool wxRichTextCtrl_EndSymbolBullet(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginStandardBullet(TSelf(wxRichTextCtrl) self, TClass(wxString) bulletName,
                                         int leftIndent, int leftSubIndent, int bulletStyle);
TBool wxRichTextCtrl_EndStandardBullet(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_BeginURL(TSelf(wxRichTextCtrl) self, TClass(wxString) url,
                              TClass(wxString) characterStyle);
TBool wxRichTextCtrl_EndURL(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_WriteImage(TSelf(wxRichTextCtrl) self, TClass(wxImage) image, int bitmapType,
                                TClass(wxRichTextAttr) textAttr);
TBool wxRichTextCtrl_WriteImageFile(TSelf(wxRichTextCtrl) self, TClass(wxString) filename,
                                    int bitmapType, TClass(wxRichTextAttr) textAttr);
TBool wxRichTextCtrl_Newline(TSelf(wxRichTextCtrl) self);
TBool wxRichTextCtrl_LineBreak(TSelf(wxRichTextCtrl) self);

/* wxSimpleHtmlListBox */
TClassDefExtend(wxSimpleHtmlListBox, wxHtmlListBox) TClass(wxSimpleHtmlListBox)
    wxSimpleHtmlListBox_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                               int style);
void wxSimpleHtmlListBox_Clear(TSelf(wxSimpleHtmlListBox) self);
void wxSimpleHtmlListBox_Delete(TSelf(wxSimpleHtmlListBox) self, int index);
int wxSimpleHtmlListBox_GetCount(TSelf(wxSimpleHtmlListBox) self);
TClass(wxString) wxSimpleHtmlListBox_GetString(TSelf(wxSimpleHtmlListBox) self, int index);
void wxSimpleHtmlListBox_SetString(TSelf(wxSimpleHtmlListBox) self, int index,
                                   TClass(wxString) str);
int wxSimpleHtmlListBox_GetSelection(TSelf(wxSimpleHtmlListBox) self);
void wxSimpleHtmlListBox_SetSelection(TSelf(wxSimpleHtmlListBox) self, int index);
int wxSimpleHtmlListBox_Append(TSelf(wxSimpleHtmlListBox) self, TClass(wxString) item);
int wxSimpleHtmlListBox_AppendData(TSelf(wxSimpleHtmlListBox) self, TClass(wxString) item,
                                   void* data);
int wxSimpleHtmlListBox_Insert(TSelf(wxSimpleHtmlListBox) self, TClass(wxString) item, int pos);
int wxSimpleHtmlListBox_InsertData(TSelf(wxSimpleHtmlListBox) self, TClass(wxString) item, int pos,
                                   void* data);
int wxSimpleHtmlListBox_FindString(TSelf(wxSimpleHtmlListBox) self, TClass(wxString) str,
                                   TBool caseSensitive);
void* wxSimpleHtmlListBox_GetClientData(TSelf(wxSimpleHtmlListBox) self, int index);
void wxSimpleHtmlListBox_SetClientData(TSelf(wxSimpleHtmlListBox) self, int index, void* data);
TBool wxSimpleHtmlListBox_IsEmpty(TSelf(wxSimpleHtmlListBox) self);
int wxSimpleHtmlListBox_GetItemCount(TSelf(wxSimpleHtmlListBox) self);

/* wxRealPoint */
TClassDef(wxRealPoint)

    /* wxRecordSet */
    TClassDefExtend(wxRecordSet, wxObject)

    /* wxRect */
    TClassDef(wxRect)

    /* wxRegEx */
    TClassDef(wxRegEx)

    /* wxRegion */
    TClassDefExtend(wxRegion, wxGDIObject) void wxRegion_Assign(TSelf(wxRegion) pObject,
                                                                TClass(wxRegion) region);
void wxRegion_Clear(TSelf(wxRegion) pObject);
TBool wxRegion_ContainsPoint(TSelf(wxRegion) pObject, TPoint(x, y));
TBool wxRegion_ContainsRect(TSelf(wxRegion) pObject, TRect(x, y, width, height));
TClass(wxRegion) wxRegion_CreateDefault();
TClass(wxRegion) wxRegion_CreateFromRect(TRect(x, y, width, height));
void wxRegion_Delete(TSelf(wxRegion) pObject);
TBool wxRegion_IsEmpty(TSelf(wxRegion) pObject);
void wxRegion_GetBox(TSelf(wxRegion) pObject, TRectOutVoid(x, y, width, height));
TBool wxRegion_IntersectRect(TSelf(wxRegion) pObject, TRect(x, y, width, height));
TBool wxRegion_IntersectRegion(TSelf(wxRegion) pObject, TClass(wxRegion) region);
TBool wxRegion_SubtractRect(TSelf(wxRegion) pObject, TRect(x, y, width, height));
TBool wxRegion_SubtractRegion(TSelf(wxRegion) pObject, TClass(wxRegion) region);
TBool wxRegion_UnionRect(TSelf(wxRegion) pObject, TRect(x, y, width, height));
TBool wxRegion_UnionRegion(TSelf(wxRegion) pObject, TClass(wxRegion) region);
TBool wxRegion_XorRect(TSelf(wxRegion) pObject, TRect(x, y, width, height));
TBool wxRegion_XorRegion(TSelf(wxRegion) pObject, TClass(wxRegion) region);

/* wxRegionIterator */
TClassDefExtend(wxRegionIterator, wxObject) TClass(wxRegionIterator) wxRegionIterator_Create();
TClass(wxRegionIterator) wxRegionIterator_CreateFromRegion(TClass(wxRegion) region);
void wxRegionIterator_Delete(TSelf(wxRegionIterator) pObject);
int wxRegionIterator_GetHeight(TSelf(wxRegionIterator) pObject);
int wxRegionIterator_GetWidth(TSelf(wxRegionIterator) pObject);
int wxRegionIterator_GetX(TSelf(wxRegionIterator) pObject);
int wxRegionIterator_GetY(TSelf(wxRegionIterator) pObject);
TBool wxRegionIterator_HaveRects(TSelf(wxRegionIterator) pObject);
void wxRegionIterator_Next(TSelf(wxRegionIterator) pObject);
void wxRegionIterator_Reset(TSelf(wxRegionIterator) pObject);
void wxRegionIterator_ResetToRegion(TSelf(wxRegionIterator) pObject, TClass(wxRegion) region);

/* wxRemotelyScrolledTreeCtrl */
TClassDefExtend(
    wxRemotelyScrolledTreeCtrl,
    wxTreeCtrl) void wxRemotelyScrolledTreeCtrl_AdjustRemoteScrollbars(TSelf(wxRemotelyScrolledTreeCtrl)
                                                                           pObject);
void wxRemotelyScrolledTreeCtrl_CalcTreeSize(TSelf(wxRemotelyScrolledTreeCtrl) pObject,
                                             TRectOutVoid(x, y, width, height));
void wxRemotelyScrolledTreeCtrl_CalcTreeSizeItem(TSelf(wxRemotelyScrolledTreeCtrl) pObject,
                                                 void* id, TRectOutVoid(x, y, width, height));
TClass(wxRemotelyScrolledTreeCtrl)
    wxRemotelyScrolledTreeCtrl_Create(void* pObject, void* compareFunc, TClass(wxWindow) parent,
                                      int id, TRect(x, y, width, height), int style);
void wxRemotelyScrolledTreeCtrl_Delete(TSelf(wxRemotelyScrolledTreeCtrl) pObject);
void* wxRemotelyScrolledTreeCtrl_GetCompanionWindow(TSelf(wxRemotelyScrolledTreeCtrl) pObject);
int wxRemotelyScrolledTreeCtrl_GetScrollPos(TSelf(wxRemotelyScrolledTreeCtrl) pObject, int orient);
TClass(wxScrolledWindow)
    wxRemotelyScrolledTreeCtrl_GetScrolledWindow(TSelf(wxRemotelyScrolledTreeCtrl) pObject);
void wxRemotelyScrolledTreeCtrl_GetViewStart(TSelf(wxRemotelyScrolledTreeCtrl) pObject,
                                             TPointOutVoid(x, y));
void wxRemotelyScrolledTreeCtrl_HideVScrollbar(TSelf(wxRemotelyScrolledTreeCtrl) pObject);
void wxRemotelyScrolledTreeCtrl_PrepareDC(TSelf(wxRemotelyScrolledTreeCtrl) pObject,
                                          TClass(wxDC) dc);
void wxRemotelyScrolledTreeCtrl_ScrollToLine(TSelf(wxRemotelyScrolledTreeCtrl) pObject,
                                             int posHoriz, int posVert);
void wxRemotelyScrolledTreeCtrl_SetCompanionWindow(TSelf(wxRemotelyScrolledTreeCtrl) pObject,
                                                   void* companion);
void wxRemotelyScrolledTreeCtrl_SetScrollbars(TSelf(wxRemotelyScrolledTreeCtrl) pObject,
                                              int pixelsPerUnitX, int pixelsPerUnitY, int noUnitsX,
                                              int noUnitsY, int xPos, int yPos, int noRefresh);

/* wxSVGFileDC */
TClassDefExtend(wxSVGFileDC, wxDC) TClass(wxSVGFileDC)
    wxSVGFileDC_Create(TClass(wxString) fileName);
TClass(wxSVGFileDC) wxSVGFileDC_CreateWithSize(TClass(wxString) fileName, TSize(width, height));
TClass(wxSVGFileDC) wxSVGFileDC_CreateWithSizeAndResolution(TClass(wxString) fileName,
                                                            TSize(width, height), float a_dpi);
void wxSVGFileDC_Delete(TSelf(wxSVGFileDC) obj);

/* wxSashEvent */
TClassDefExtend(wxSashEvent, wxEvent) TClass(wxSashEvent) wxSashEvent_Create(int id, int edge);
TClass(wxRect) wxSashEvent_GetDragRect(TSelf(wxSashEvent) pObject);
int wxSashEvent_GetDragStatus(TSelf(wxSashEvent) pObject);
int wxSashEvent_GetEdge(TSelf(wxSashEvent) pObject);
void wxSashEvent_SetDragRect(TSelf(wxSashEvent) pObject, TRect(x, y, width, height));
void wxSashEvent_SetDragStatus(TSelf(wxSashEvent) pObject, int status);
void wxSashEvent_SetEdge(TSelf(wxSashEvent) pObject, int edge);

/* wxSashLayoutWindow */
TClassDefExtend(wxSashLayoutWindow, wxSashWindow) TClass(wxSashLayoutWindow)
    wxSashLayoutWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                              int style);
int wxSashLayoutWindow_GetAlignment(TSelf(wxSashLayoutWindow) pObject);
int wxSashLayoutWindow_GetOrientation(TSelf(wxSashLayoutWindow) pObject);
void wxSashLayoutWindow_SetAlignment(TSelf(wxSashLayoutWindow) pObject, int align);
void wxSashLayoutWindow_SetDefaultSize(TSelf(wxSashLayoutWindow) pObject, TSize(width, height));
void wxSashLayoutWindow_SetOrientation(TSelf(wxSashLayoutWindow) pObject, int orient);

/* wxSashWindow */
TClassDefExtend(wxSashWindow, wxWindow) TClass(wxSashWindow)
    wxSashWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
int wxSashWindow_GetDefaultBorderSize(TSelf(wxSashWindow) pObject);
int wxSashWindow_GetEdgeMargin(TSelf(wxSashWindow) pObject, int edge);
int wxSashWindow_GetExtraBorderSize(TSelf(wxSashWindow) pObject);
int wxSashWindow_GetMaximumSizeX(TSelf(wxSashWindow) pObject);
int wxSashWindow_GetMaximumSizeY(TSelf(wxSashWindow) pObject);
int wxSashWindow_GetMinimumSizeX(TSelf(wxSashWindow) pObject);
int wxSashWindow_GetMinimumSizeY(TSelf(wxSashWindow) pObject);
TBool wxSashWindow_GetSashVisible(TSelf(wxSashWindow) pObject, int edge);
TBool wxSashWindow_HasBorder(TSelf(wxSashWindow) pObject, int edge);
void wxSashWindow_SetDefaultBorderSize(TSelf(wxSashWindow) pObject, int width);
void wxSashWindow_SetExtraBorderSize(TSelf(wxSashWindow) pObject, int width);
void wxSashWindow_SetMaximumSizeX(TSelf(wxSashWindow) pObject, int max);
void wxSashWindow_SetMaximumSizeY(TSelf(wxSashWindow) pObject, int max);
void wxSashWindow_SetMinimumSizeX(TSelf(wxSashWindow) pObject, int min);
void wxSashWindow_SetMinimumSizeY(TSelf(wxSashWindow) pObject, int min);
void wxSashWindow_SetSashBorder(TSelf(wxSashWindow) pObject, int edge, TBool border);
void wxSashWindow_SetSashVisible(TSelf(wxSashWindow) pObject, int edge, TBool sash);

/* wxScopedArray */
TClassDef(wxScopedArray)

    /* wxScopedPtr */
    TClassDef(wxScopedPtr)

    /* wxScreenDC */
    TClassDefExtend(wxScreenDC, wxDC) TClass(wxScreenDC) wxScreenDC_Create();
void wxScreenDC_Delete(TSelf(wxScreenDC) pObject);
TBool wxScreenDC_EndDrawingOnTop(TSelf(wxScreenDC) pObject);
TBool wxScreenDC_StartDrawingOnTop(TSelf(wxScreenDC) pObject, TRect(x, y, width, height));
TBool wxScreenDC_StartDrawingOnTopOfWin(TSelf(wxScreenDC) pObject, TClass(wxWindow) win);

/* wxScrollBar */
TClassDefExtend(wxScrollBar, wxControl) TClass(wxScrollBar)
    wxScrollBar_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height), int style);
int wxScrollBar_GetPageSize(TSelf(wxScrollBar) pObject);
int wxScrollBar_GetRange(TSelf(wxScrollBar) pObject);
int wxScrollBar_GetThumbPosition(TSelf(wxScrollBar) pObject);
int wxScrollBar_GetThumbSize(TSelf(wxScrollBar) pObject);
void wxScrollBar_SetScrollbar(TSelf(wxScrollBar) pObject, int position, int thumbSize, int range,
                              int pageSize, TBool refresh);
void wxScrollBar_SetThumbPosition(TSelf(wxScrollBar) pObject, int viewStart);

/* wxScrollEvent */
TClassDefExtend(wxScrollEvent,
                wxEvent) int wxScrollEvent_GetOrientation(TSelf(wxScrollEvent) pObject);
int wxScrollEvent_GetPosition(TSelf(wxScrollEvent) pObject);

/* wxScrollWinEvent */
TClassDefExtend(wxScrollWinEvent,
                wxEvent) int wxScrollWinEvent_GetOrientation(TSelf(wxScrollWinEvent) pObject);
int wxScrollWinEvent_GetPosition(TSelf(wxScrollWinEvent) pObject);
void wxScrollWinEvent_SetOrientation(TSelf(wxScrollWinEvent) pObject, int orient);
void wxScrollWinEvent_SetPosition(TSelf(wxScrollWinEvent) pObject, int pos);

/* wxScrolledWindow */
TClassDefExtend(wxScrolledWindow,
                wxPanel) void wxScrolledWindow_AdjustScrollbars(TSelf(wxScrolledWindow) pObject);
void wxScrolledWindow_CalcScrolledPosition(TSelf(wxScrolledWindow) pObject, TPoint(x, y),
                                           TPointOutVoid(xx, yy));
void wxScrolledWindow_CalcUnscrolledPosition(TSelf(wxScrolledWindow) pObject, TPoint(x, y),
                                             TPointOutVoid(xx, yy));
TClass(wxScrolledWindow) wxScrolledWindow_Create(TClass(wxWindow) parent, int id,
                                                 TRect(left, top, width, height), int style);
void wxScrolledWindow_EnableScrolling(TSelf(wxScrolledWindow) pObject, TBool x_scrolling,
                                      TBool y_scrolling);
double wxScrolledWindow_GetScaleX(TSelf(wxScrolledWindow) pObject);
double wxScrolledWindow_GetScaleY(TSelf(wxScrolledWindow) pObject);
int wxScrolledWindow_GetScrollPageSize(TSelf(wxScrolledWindow) pObject, int orient);
void wxScrolledWindow_GetScrollPixelsPerUnit(TSelf(wxScrolledWindow) pObject, TPointOutVoid(x, y));
TClass(wxWindow) wxScrolledWindow_GetTargetWindow(TSelf(wxScrolledWindow) pObject);
void wxScrolledWindow_GetViewStart(TSelf(wxScrolledWindow) pObject, TPointOutVoid(x, y));
void wxScrolledWindow_GetVirtualSize(TSelf(wxScrolledWindow) pObject, TSizeOutVoid(x, y));
void wxScrolledWindow_OnDraw(TSelf(wxScrolledWindow) pObject, TClass(wxDC) dc);
void wxScrolledWindow_PrepareDC(TSelf(wxScrolledWindow) pObject, TClass(wxDC) dc);
void wxScrolledWindow_Scroll(TSelf(wxScrolledWindow) pObject, TPoint(x_pos, y_pos));
void wxScrolledWindow_SetScale(TSelf(wxScrolledWindow) pObject, double xScale, double yScale);
void wxScrolledWindow_SetScrollPageSize(TSelf(wxScrolledWindow) pObject, int orient, int pageSize);
void wxScrolledWindow_SetScrollbars(TSelf(wxScrolledWindow) pObject, int pixelsPerUnitX,
                                    int pixelsPerUnitY, int noUnitsX, int noUnitsY, int xPos,
                                    int yPos, TBool noRefresh);
void wxScrolledWindow_ShowScrollbars(TSelf(wxScrolledWindow) pObject, int showh, int showv);
void wxScrolledWindow_SetTargetWindow(TSelf(wxScrolledWindow) pObject, TClass(wxWindow) target);
void wxScrolledWindow_ViewStart(TSelf(wxScrolledWindow) pObject, TPointOutVoid(x, y));

/* wxSearchCtrl */
TClassDefExtend(wxSearchCtrl, wxControl) TClass(wxSearchCtrl)
    wxSearchCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxString) value,
                        TRect(x, y, width, height), int style);
void wxSearchCtrl_SetMenu(TSelf(wxSearchCtrl) self, TClass(wxMenu) menu);
TClass(wxMenu) wxSearchCtrl_GetMenu(TSelf(wxSearchCtrl) self);
void wxSearchCtrl_ShowSearchButton(TSelf(wxSearchCtrl) self, TBool show);
TBool wxSearchCtrl_IsSearchButtonVisible(TSelf(wxSearchCtrl) self);
void wxSearchCtrl_ShowCancelButton(TSelf(wxSearchCtrl) self, TBool show);
TBool wxSearchCtrl_IsCancelButtonVisible(TSelf(wxSearchCtrl) self);
void wxSearchCtrl_SetDescriptiveText(TSelf(wxSearchCtrl) self, TClass(wxString) text);
TClass(wxString) wxSearchCtrl_GetDescriptiveText(TSelf(wxSearchCtrl) self);

/* wxSemaphore */
TClassDef(wxSemaphore)

    /* wxServer */
    TClassDefExtend(wxServer, wxServerBase)

    /* wxServerBase */
    TClassDefExtend(wxServerBase, wxObject)

    /* wxSetCursorEvent */
    TClassDefExtend(wxSetCursorEvent, wxEvent) TClass(wxCursor)
        wxSetCursorEvent_GetCursor(TSelf(wxSetCursorEvent) pObject);
int wxSetCursorEvent_GetX(TSelf(wxSetCursorEvent) pObject);
int wxSetCursorEvent_GetY(TSelf(wxSetCursorEvent) pObject);
TBool wxSetCursorEvent_HasCursor(TSelf(wxSetCursorEvent) pObject);
void wxSetCursorEvent_SetCursor(TSelf(wxSetCursorEvent) pObject, TClass(wxCursor) cursor);

/* wxShowEvent */
TClassDefExtend(wxShowEvent, wxEvent) void wxShowEvent_CopyObject(TSelf(wxShowEvent) pObject,
                                                                  TClass(wxObject) obj);
TBool wxShowEvent_IsShown(TSelf(wxShowEvent) pObject);
void wxShowEvent_SetShow(TSelf(wxShowEvent) pObject, TBool show);

/* wxSimpleHelpProvider */
TClassDefExtend(wxSimpleHelpProvider, wxHelpProvider) TClass(wxSimpleHelpProvider)
    wxSimpleHelpProvider_Create();

/* wxSingleChoiceDialog */
TClassDefExtend(wxSingleChoiceDialog, wxDialog)

    /* wxSingleInstanceChecker */
    TClassDef(wxSingleInstanceChecker) TBool
    wxSingleInstanceChecker_Create(void* pObject, TClass(wxString) name, TClass(wxString) path);
TClass(wxSingleInstanceChecker) wxSingleInstanceChecker_CreateDefault();
void wxSingleInstanceChecker_Delete(TSelf(wxSingleInstanceChecker) pObject);
TBool wxSingleInstanceChecker_IsAnotherRunning(TSelf(wxSingleInstanceChecker) pObject);

/* wxSize */
TClassDef(wxSize) TClass(wxSize) wxSize_Create(TSize(width, height));
void wxSize_Delete(TSelf(wxSize) pObject);
int wxSize_GetHeight(TSelf(wxSize) pObject);
int wxSize_GetWidth(TSelf(wxSize) pObject);
void wxSize_SetHeight(TSelf(wxSize) pObject, int height);
void wxSize_SetWidth(TSelf(wxSize) pObject, int width);

/* wxSizeEvent */
TClassDefExtend(wxSizeEvent, wxEvent) void wxSizeEvent_CopyObject(TSelf(wxSizeEvent) pObject,
                                                                  void* obj);
TClass(wxSize) wxSizeEvent_GetSize(TSelf(wxSizeEvent) pObject);

/* wxSizer */
TClassDefExtend(wxSizer, wxObject) void wxSizer_Add(TSelf(wxSizer) pObject, TSize(width, height),
                                                    int option, int flag, int border,
                                                    void* userData);
void wxSizer_AddSizer(TSelf(wxSizer) pObject, TClass(wxSizer) sizer, int option, int flag,
                      int border, void* userData);
void wxSizer_AddWindow(TSelf(wxSizer) pObject, TClass(wxWindow) window, int option, int flag,
                       int border, void* userData);
TClass(wxSize) wxSizer_CalcMin(TSelf(wxSizer) pObject);
void wxSizer_Fit(TSelf(wxSizer) pObject, TClass(wxWindow) window);
int wxSizer_GetChildren(TSelf(wxSizer) pObject, void* result, int count);
TClass(wxSize) wxSizer_GetMinSize(TSelf(wxSizer) pObject);

TClass(wxPoint) wxSizer_GetPosition(TSelf(wxSizer) pObject);

TClass(wxSize) wxSizer_GetSize(TSelf(wxSizer) pObject);
void wxSizer_Insert(TSelf(wxSizer) pObject, int before, TSize(width, height), int option, int flag,
                    int border, void* userData);
void wxSizer_InsertSizer(TSelf(wxSizer) pObject, int before, TClass(wxSizer) sizer, int option,
                         int flag, int border, void* userData);
void wxSizer_InsertWindow(TSelf(wxSizer) pObject, int before, TClass(wxWindow) window, int option,
                          int flag, int border, void* userData);
void wxSizer_Layout(TSelf(wxSizer) pObject);
void wxSizer_Prepend(TSelf(wxSizer) pObject, TSize(width, height), int option, int flag, int border,
                     void* userData);
void wxSizer_PrependSizer(TSelf(wxSizer) pObject, TClass(wxSizer) sizer, int option, int flag,
                          int border, void* userData);
void wxSizer_PrependWindow(TSelf(wxSizer) pObject, TClass(wxWindow) window, int option, int flag,
                           int border, void* userData);
void wxSizer_RecalcSizes(TSelf(wxSizer) pObject);
void wxSizer_SetDimension(TSelf(wxSizer) pObject, TRect(x, y, width, height));
void wxSizer_SetItemMinSize(TSelf(wxSizer) pObject, int pos, TSize(width, height));
void wxSizer_SetItemMinSizeSizer(TSelf(wxSizer) pObject, TClass(wxSizer) sizer,
                                 TSize(width, height));
void wxSizer_SetItemMinSizeWindow(TSelf(wxSizer) pObject, TClass(wxWindow) window,
                                  TSize(width, height));
void wxSizer_SetMinSize(TSelf(wxSizer) pObject, TSize(width, height));
void wxSizer_SetSizeHints(TSelf(wxSizer) pObject, TClass(wxWindow) window);
void wxSizer_AddSpacer(TSelf(wxSizer) pObject, int size);
void wxSizer_AddStretchSpacer(TSelf(wxSizer) pObject, int size);
void wxSizer_Clear(TSelf(wxSizer) pObject, TBool delete_windows);
TBool wxSizer_DetachWindow(TSelf(wxSizer) pObject, TClass(wxWindow) window);
TBool wxSizer_DetachSizer(TSelf(wxSizer) pObject, TClass(wxSizer) sizer);
TBool wxSizer_Detach(TSelf(wxSizer) pObject, int index);
void wxSizer_FitInside(TSelf(wxSizer) pObject, TClass(wxWindow) window);
TClass(wxWindow) wxSizer_GetContainingWindow(TSelf(wxSizer) pObject);
TClass(wxSizerItem)
    wxSizer_GetItemWindow(TSelf(wxSizer) pObject, TClass(wxWindow) window, TBool recursive);
TClass(wxSizerItem)
    wxSizer_GetItemSizer(TSelf(wxSizer) pObject, TClass(wxSizer) window, TBool recursive);
TClass(wxSizerItem) wxSizer_GetItem(TSelf(wxSizer) pObject, int index);
TBool wxSizer_HideWindow(TSelf(wxWindow) pObject, TClass(wxWindow) window);
TBool wxSizer_HideSizer(TSelf(wxWindow) pObject, TClass(wxSizer) sizer);
TBool wxSizer_Hide(TSelf(wxWindow) pObject, int index);
TClass(wxSizerItem) wxSizer_InsertSpacer(TSelf(wxSizer) pObject, int index, int size);
TClass(wxSizerItem) wxSizer_InsertStretchSpacer(TSelf(wxSizer) pObject, int index, int prop);
TBool wxSizer_IsShownWindow(TSelf(wxSizer) pObject, TClass(wxWindow) * window);
TBool wxSizer_IsShownSizer(TSelf(wxSizer) pObject, TClass(wxSizer) * sizer);
TBool wxSizer_IsShown(TSelf(wxSizer) pObject, int index);
TClass(wxSizerItem) wxSizer_PrependSpacer(TSelf(wxSizer) pObject, int size);
TClass(wxSizerItem) wxSizer_PrependStretchSpacer(TSelf(wxSizer) pObject, int prop);
TBool wxSizer_ReplaceWindow(TSelf(wxSizer) pObject, TClass(wxWindow) oldwin,
                            TClass(wxWindow) newwin, TBool recursive);
TBool wxSizer_ReplaceSizer(TSelf(wxSizer) pObject, TClass(wxSizer) oldsz, TClass(wxSizer) newsz,
                           TBool recursive);
TBool wxSizer_Replace(TSelf(wxSizer) pObject, int oldindex, TClass(wxSizerItem) newitem);
// The following is replaced with wxSizer_FitInside
// void       wxSizer_SetVirtualSizeHints( TSelf(wxSizer) pObject, TClass(wxWindow)
// window );
TBool wxSizer_ShowWindow(TSelf(wxSizer) pObject, TClass(wxWindow) window, TBool show,
                         TBool recursive);
TBool wxSizer_ShowSizer(TSelf(wxSizer) pObject, TClass(wxSizer) sizer, TBool show, TBool recursive);
TBool wxSizer_Show(TSelf(wxSizer) pObject, TClass(wxSizer) sizer, int index, TBool show);
/* wxSizerItem */
TClassDefExtend(wxSizerItem, wxObject) TClass(wxSize)
    wxSizerItem_CalcMin(TSelf(wxSizerItem) pObject);
TClass(wxSizerItem)
    wxSizerItem_Create(TSize(width, height), int option, int flag, int border, void* userData);
void* wxSizerItem_CreateInSizer(TClass(wxSizer) sizer, int option, int flag, int border,
                                void* userData);
void* wxSizerItem_CreateInWindow(TClass(wxWindow) window, int option, int flag, int border,
                                 void* userData);
int wxSizerItem_GetBorder(TSelf(wxSizerItem) pObject);
int wxSizerItem_GetFlag(TSelf(wxSizerItem) pObject);
TClass(wxSize) wxSizerItem_GetMinSize(TSelf(wxSizerItem) pObject);
TClass(wxPoint) wxSizerItem_GetPosition(TSelf(wxSizerItem) pObject);
float wxSizerItem_GetRatio(TSelf(wxSizerItem) pObject);
TClass(wxSize) wxSizerItem_GetSize(TSelf(wxSizerItem) pObject);
TClass(wxSizer) wxSizerItem_GetSizer(TSelf(wxSizerItem) pObject);
void* wxSizerItem_GetUserData(TSelf(wxSizerItem) pObject);
TClass(wxWindow) wxSizerItem_GetWindow(TSelf(wxSizerItem) pObject);
TBool wxSizerItem_IsSizer(TSelf(wxSizerItem) pObject);
TBool wxSizerItem_IsSpacer(TSelf(wxSizerItem) pObject);
TBool wxSizerItem_IsWindow(TSelf(wxSizerItem) pObject);
void wxSizerItem_SetBorder(TSelf(wxSizerItem) pObject, int border);
void wxSizerItem_SetDimension(TSelf(wxSizerItem) pObject, TRect(x, y, width, height));
void wxSizerItem_SetFlag(TSelf(wxSizerItem) pObject, int flag);
void wxSizerItem_SetFloatRatio(TSelf(wxSizerItem) pObject, float ratio);
void wxSizerItem_SetInitSize(TSelf(wxSizerItem) pObject, TPoint(x, y));
void wxSizerItem_SetRatio(TSelf(wxSizerItem) pObject, TSize(width, height));
// void       wxSizerItem_SetSizer( TSelf(wxSizerItem) pObject, TClass(wxSizer)
// sizer );
void wxSizerItem_AssignSizer(TSelf(wxSizerItem) pObject, TClass(wxSizer) sizer);
// void       wxSizerItem_SetWindow( TSelf(wxSizerItem) pObject, TClass(wxWindow)
// window );
void wxSizerItem_AssignWindow(TSelf(wxSizerItem) pObject, TClass(wxWindow) window);
void wxSizerItem_Delete(TSelf(wxSizerItem) pObject);
void wxSizerItem_DeleteWindows(TSelf(wxSizerItem) pObject);
void wxSizerItem_DetachSizer(TSelf(wxSizerItem) pObject);
int wxSizerItem_GetProportion(TSelf(wxSizerItem) pObject);
TClass(wxRect) wxSizerItem_GetRect(TSelf(wxSizerItem) pObject);
TClass(wxSize) wxSizerItem_GetSpacer(TSelf(wxSizerItem) pObject);
int wxSizerItem_IsShown(TSelf(wxSizerItem) pObject);
void wxSizerItem_SetProportion(TSelf(wxSizerItem) pObject, int proportion);
// void       wxSizerItem_SetSpacer( TSelf(wxSizerItem) pObject,
// TSize(width,height) );
void wxSizerItem_AssignSpacer(TSelf(wxSizerItem) pObject, TSize(width, height));
void wxSizerItem_Show(TSelf(wxSizerItem) pObject, int show);

/* wxSlider */
TClassDefExtend(wxSlider, wxControl) void wxSlider_ClearSel(TSelf(wxSlider) pObject);
void wxSlider_ClearTicks(TSelf(wxSlider) pObject);
TClass(wxSlider) wxSlider_Create(TClass(wxWindow) parent, int id, int init, int minVal, int maxVal,
                                 TRect(left, top, width, height), long style);
int wxSlider_GetLineSize(TSelf(wxSlider) pObject);
int wxSlider_GetMax(TSelf(wxSlider) pObject);
int wxSlider_GetMin(TSelf(wxSlider) pObject);
int wxSlider_GetPageSize(TSelf(wxSlider) pObject);
int wxSlider_GetSelEnd(TSelf(wxSlider) pObject);
int wxSlider_GetSelStart(TSelf(wxSlider) pObject);
int wxSlider_GetThumbLength(TSelf(wxSlider) pObject);
int wxSlider_GetTickFreq(TSelf(wxSlider) pObject);
int wxSlider_GetValue(TSelf(wxSlider) pObject);
void wxSlider_SetLineSize(TSelf(wxSlider) pObject, int lineSize);
void wxSlider_SetPageSize(TSelf(wxSlider) pObject, int pageSize);
void wxSlider_SetRange(TSelf(wxSlider) pObject, int minValue, int maxValue);
void wxSlider_SetSelection(TSelf(wxSlider) pObject, int minPos, int maxPos);
void wxSlider_SetThumbLength(TSelf(wxSlider) pObject, int len);
void wxSlider_SetTick(TSelf(wxSlider) pObject, int tickPos);
// Obsolete
// void       wxSlider_SetTickFreq( TSelf(wxSlider) pObject, int n, int pos );
void wxSlider_SetValue(TSelf(wxSlider) pObject, int value);

/* wxSockAddress */
TClassDefExtend(wxSockAddress, wxObject)

    /* wxSocketBase */
    TClassDefExtend(wxSocketBase, wxObject)

    /* wxSocketClient */
    TClassDefExtend(wxSocketClient, wxSocketBase)

    /* wxSocketEvent */
    TClassDefExtend(wxSocketEvent, wxEvent)

    /* wxSocketInputStream */
    TClassDefExtend(wxSocketInputStream, wxInputStream)

    /* wxSocketOutputStream */
    TClassDefExtend(wxSocketOutputStream, wxOutputStream)

    /* wxSocketServer */
    TClassDefExtend(wxSocketServer, wxSocketBase)

    /* wxSpinButton */
    TClassDefExtend(wxSpinButton, wxControl) TClass(wxSpinButton)
        wxSpinButton_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height),
                            long style);
int wxSpinButton_GetMax(TSelf(wxSpinButton) pObject);
int wxSpinButton_GetMin(TSelf(wxSpinButton) pObject);
int wxSpinButton_GetValue(TSelf(wxSpinButton) pObject);
void wxSpinButton_SetRange(TSelf(wxSpinButton) pObject, int minVal, int maxVal);
void wxSpinButton_SetValue(TSelf(wxSpinButton) pObject, int val);

/* wxSpinCtrl */
TClassDefExtend(wxSpinCtrl, wxControl) TClass(wxSpinCtrl)
    wxSpinCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                      TRect(left, top, width, height), long style, int minVal, int maxVal,
                      int init);
int wxSpinCtrl_GetMax(TSelf(wxSpinCtrl) pObject);
int wxSpinCtrl_GetMin(TSelf(wxSpinCtrl) pObject);
int wxSpinCtrl_GetValue(TSelf(wxSpinCtrl) pObject);
void wxSpinCtrl_SetRange(TSelf(wxSpinCtrl) pObject, int min_val, int max_val);
void wxSpinCtrl_SetValue(TSelf(wxSpinCtrl) pObject, int val);

/* wxSpinCtrlDouble */
TClassDefExtend(wxSpinCtrlDouble, wxControl) TClass(wxSpinCtrlDouble)
    wxSpinCtrlDouble_Create(TClass(wxWindow) parent, int id, TClass(wxString) value,
                            TRect(x, y, width, height), int style, double min, double max,
                            double initial, double inc);
double wxSpinCtrlDouble_GetValue(TSelf(wxSpinCtrlDouble) self);
void wxSpinCtrlDouble_SetValue(TSelf(wxSpinCtrlDouble) self, double value);
void wxSpinCtrlDouble_SetValueString(TSelf(wxSpinCtrlDouble) self, TClass(wxString) value);
void wxSpinCtrlDouble_SetRange(TSelf(wxSpinCtrlDouble) self, double minVal, double maxVal);
double wxSpinCtrlDouble_GetMin(TSelf(wxSpinCtrlDouble) self);
double wxSpinCtrlDouble_GetMax(TSelf(wxSpinCtrlDouble) self);
void wxSpinCtrlDouble_SetIncrement(TSelf(wxSpinCtrlDouble) self, double inc);
double wxSpinCtrlDouble_GetIncrement(TSelf(wxSpinCtrlDouble) self);
void wxSpinCtrlDouble_SetDigits(TSelf(wxSpinCtrlDouble) self, unsigned int digits);
unsigned int wxSpinCtrlDouble_GetDigits(TSelf(wxSpinCtrlDouble) self);

/* wxSpinEvent */
TClassDefExtend(wxSpinEvent, wxNotifyEvent) int wxSpinEvent_GetPosition(TSelf(wxSpinEvent) pObject);
void wxSpinEvent_SetPosition(TSelf(wxSpinEvent) pObject, int pos);

/* wxSplashScreen */
TClassDefExtend(wxSplashScreen, wxFrame) TClass(wxSplashScreen)
    wxSplashScreen_Create(TClass(wxBitmap) bitmap, long splashStyle, int milliseconds,
                          TClass(wxWindow) parent, int id, TRect(left, top, width, height),
                          long style);

long wxSplashScreen_GetSplashStyle(TSelf(wxSplashScreen) pObject);
int wxSplashScreen_GetTimeout(TSelf(wxSplashScreen) pObject);

/* wxSplitterEvent */
TClassDefExtend(wxSplitterEvent, wxNotifyEvent)

    /* wxSplitterScrolledWindow */
    TClassDefExtend(wxSplitterScrolledWindow, wxScrolledWindow) TClass(wxSplitterScrolledWindow)
        wxSplitterScrolledWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                                        int style);

/* wxSplitterWindow */
TClassDefExtend(wxSplitterWindow, wxWindow) TClass(wxSplitterWindow)
    wxSplitterWindow_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height),
                            int style);
int wxSplitterWindow_GetBorderSize(TSelf(wxSplitterWindow) pObject);
int wxSplitterWindow_GetMinimumPaneSize(TSelf(wxSplitterWindow) pObject);
int wxSplitterWindow_GetSashPosition(TSelf(wxSplitterWindow) pObject);
int wxSplitterWindow_GetSashSize(TSelf(wxSplitterWindow) pObject);
int wxSplitterWindow_GetSplitMode(TSelf(wxSplitterWindow) pObject);
TClass(wxWindow) wxSplitterWindow_GetWindow1(TSelf(wxSplitterWindow) pObject);
TClass(wxWindow) wxSplitterWindow_GetWindow2(TSelf(wxSplitterWindow) pObject);
void wxSplitterWindow_Initialize(TSelf(wxSplitterWindow) pObject, TClass(wxWindow) window);
TBool wxSplitterWindow_IsSplit(TSelf(wxSplitterWindow) pObject);
TBool wxSplitterWindow_ReplaceWindow(TSelf(wxSplitterWindow) pObject, TClass(wxWindow) winOld,
                                     TClass(wxWindow) winNew);
void wxSplitterWindow_SetBorderSize(TSelf(wxSplitterWindow) pObject, int width);
void wxSplitterWindow_SetMinimumPaneSize(TSelf(wxSplitterWindow) pObject, int min);
void wxSplitterWindow_SetSashPosition(TSelf(wxSplitterWindow) pObject, int position, TBool redraw);
// Obsolete
// void       wxSplitterWindow_SetSashSize( TSelf(wxSplitterWindow) pObject, int
// width );
void wxSplitterWindow_SetSplitMode(TSelf(wxSplitterWindow) pObject, int mode);
TBool wxSplitterWindow_SplitHorizontally(TSelf(wxSplitterWindow) pObject, TClass(wxWindow) window1,
                                         TClass(wxWindow) window2, int sashPosition);
TBool wxSplitterWindow_SplitVertically(TSelf(wxSplitterWindow) pObject, TClass(wxWindow) window1,
                                       TClass(wxWindow) window2, int sashPosition);
TBool wxSplitterWindow_Unsplit(TSelf(wxSplitterWindow) pObject, TClass(wxWindow) toRemove);
double wxSplitterWindow_GetSashGravity(TSelf(wxSplitterWindow) pObject);
void wxSplitterWindow_SetSashGravity(TSelf(wxSplitterWindow) pObject, double gravity);

/* wxStaticBitmap */
TClassDefExtend(wxStaticBitmap, wxControl) TClass(wxStaticBitmap)
    wxStaticBitmap_Create(TClass(wxWindow) parent, int id, TClass(wxBitmap) bitmap,
                          TRect(left, top, width, height), int style);
void wxStaticBitmap_Delete(TSelf(wxStaticBitmap) pObject);
void wxStaticBitmap_GetBitmap(TSelf(wxStaticBitmap) pObject, TClassRef(wxBitmap) ref);
void wxStaticBitmap_GetIcon(TSelf(wxStaticBitmap) pObject, TClassRef(wxIcon) ref);
void wxStaticBitmap_SetBitmap(TSelf(wxStaticBitmap) pObject, TClass(wxBitmap) bitmap);
void wxStaticBitmap_SetIcon(TSelf(wxStaticBitmap) pObject, TClass(wxIcon) icon);

/* wxStaticBox */
TClassDefExtend(wxStaticBox, wxControl) TClass(wxStaticBox)
    wxStaticBox_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                       TRect(left, top, width, height), int style);

/* wxStaticBoxSizer */
TClassDefExtend(wxStaticBoxSizer, wxBoxSizer) TClass(wxSize)
    wxStaticBoxSizer_CalcMin(TSelf(wxStaticBoxSizer) pObject);
TClass(wxStaticBoxSizer) wxStaticBoxSizer_Create(TClass(wxStaticBox) box, int orient);
TClass(wxStaticBox) wxStaticBoxSizer_GetStaticBox(TSelf(wxStaticBoxSizer) pObject);
void wxStaticBoxSizer_RecalcSizes(TSelf(wxStaticBoxSizer) pObject);

/* wxStdDialogButtonSizer */
TClassDefExtend(wxStdDialogButtonSizer, wxBoxSizer) TClass(wxStdDialogButtonSizer)
    wxStdDialogButtonSizer_Create();
void wxStdDialogButtonSizer_AddButton(TSelf(wxStdDialogButtonSizer) pObject,
                                      TClass(wxButton) button);
void wxStdDialogButtonSizer_SetAffirmativeButton(TSelf(wxStdDialogButtonSizer) pObject,
                                                 TClass(wxButton) button);
void wxStdDialogButtonSizer_SetNegativeButton(TSelf(wxStdDialogButtonSizer) pObject,
                                              TClass(wxButton) button);
void wxStdDialogButtonSizer_SetCancelButton(TSelf(wxStdDialogButtonSizer) pObject,
                                            TClass(wxButton) button);
void wxStdDialogButtonSizer_Realize(TSelf(wxStdDialogButtonSizer) pObject);
TClass(wxButton) wxStdDialogButtonSizer_GetAffirmativeButton(TSelf(wxStdDialogButtonSizer) pObject);
TClass(wxButton) wxStdDialogButtonSizer_GetApplyButton(TSelf(wxStdDialogButtonSizer) pObject);
TClass(wxButton) wxStdDialogButtonSizer_GetNegativeButton(TSelf(wxStdDialogButtonSizer) pObject);
TClass(wxButton) wxStdDialogButtonSizer_GetCancelButton(TSelf(wxStdDialogButtonSizer) pObject);
TClass(wxButton) wxStdDialogButtonSizer_GetHelpButton(TSelf(wxStdDialogButtonSizer) pObject);

/* wxStaticLine */
TClassDefExtend(wxStaticLine, wxControl) TClass(wxStaticLine)
    wxStaticLine_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height),
                        int style);
int wxStaticLine_GetDefaultSize(TSelf(wxStaticLine) pObject);
TBool wxStaticLine_IsVertical(TSelf(wxStaticLine) pObject);

/* wxStaticText */
TClassDefExtend(wxStaticText, wxControl) TClass(wxStaticText)
    wxStaticText_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                        TRect(left, top, width, height), int style);

/* wxStatusBar */
TClassDefExtend(wxStatusBar, wxWindow) TClass(wxStatusBar)
    wxStatusBar_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height), int style);
int wxStatusBar_GetBorderX(TSelf(wxStatusBar) pObject);
int wxStatusBar_GetBorderY(TSelf(wxStatusBar) pObject);
int wxStatusBar_GetFieldsCount(TSelf(wxStatusBar) pObject);
TClass(wxString) wxStatusBar_GetStatusText(TSelf(wxStatusBar) pObject, int number);
void wxStatusBar_SetFieldsCount(TSelf(wxStatusBar) pObject, int number, int* widths);
void wxStatusBar_SetMinHeight(TSelf(wxStatusBar) pObject, int height);
void wxStatusBar_SetStatusText(TSelf(wxStatusBar) pObject, TClass(wxString) text, int number);
void wxStatusBar_SetStatusWidths(TSelf(wxStatusBar) pObject, int count, int* widths);

/* wxStopWatch */
TClassDef(wxStopWatch) TClass(wxStopWatch) wxStopWatch_Create();
void wxStopWatch_Delete(TSelf(wxStopWatch) pObject);
void wxStopWatch_Start(TSelf(wxStopWatch) pObject, int msec);
void wxStopWatch_Pause(TSelf(wxStopWatch) pObject);
void wxStopWatch_Resume(TSelf(wxStopWatch) pObject);
int wxStopWatch_Time(TSelf(wxStopWatch) pObject);

/* wxStreamBase */
TClassDef(wxStreamBase) int wxStreamBase_GetLastError(TSelf(wxStreamBase) pObject);
int wxStreamBase_GetSize(TSelf(wxStreamBase) pObject);
TBool wxStreamBase_IsOk(TSelf(wxStreamBase) pObject);

/* wxStreamBuffer */
TClassDef(wxStreamBuffer)

    /* wxStreamToTextRedirector */
    TClassDef(wxStreamToTextRedirector)

    /* wxString */
    TClassDef(wxString)

    /* wxStringBuffer */
    TClassDef(wxStringBuffer)

    /* wxStringClientData */
    TClassDefExtend(wxStringClientData, wxClientData)

    /* wxStringList */
    TClassDefExtend(wxStringList, wxList)

    /* wxStringTokenizer */
    TClassDefExtend(wxStringTokenizer, wxObject)

    /* wxSysColourChangedEvent */
    TClassDefExtend(wxSysColourChangedEvent, wxEvent)

    /* wxSystemOptions */
    TClassDefExtend(wxSystemOptions, wxObject)

    /* wxSystemSettings */
    TClassDefExtend(wxSystemSettings,
                    wxObject) void wxSystemSettings_GetColour(int index, TClassRef(wxColour) ref);
void wxSystemSettings_GetFont(int index, TClassRef(wxFont) ref);
int wxSystemSettings_GetMetric(int index);
int wxSystemSettings_GetScreenType();

/* wxTabCtrl */
TClassDefExtend(wxTabCtrl, wxControl)

    /* wxTabEvent */
    TClassDefExtend(wxTabEvent, wxCommandEvent)

    /* wxTablesInUse */
    TClassDefExtend(wxTablesInUse, wxObject)

    /* wxTaskBarIcon */
    TClassDefExtend(wxTaskBarIcon, wxEvtHandler) TClass(wxTaskBarIcon) wxTaskBarIcon_Create();
void wxTaskBarIcon_Delete(TSelf(wxTaskBarIcon) pObject);
/* TClass(wxMenu)  wxTaskBarIcon_CreatePopupMenu( TSelf(wxTaskBarIcon) pObject );
 */
TBool wxTaskBarIcon_IsIconInstalled(TSelf(wxTaskBarIcon) pObject);
TBool wxTaskBarIcon_IsOk(TSelf(wxTaskBarIcon) pObject);
TBool wxTaskBarIcon_PopupMenu(TSelf(wxTaskBarIcon) pObject, TClass(wxMenu) menu);
TBool wxTaskBarIcon_RemoveIcon(TSelf(wxTaskBarIcon) pObject);
TBool wxTaskBarIcon_SetIcon(TSelf(wxTaskBarIcon) pObject, TClass(wxIcon) icon,
                            TClass(wxString) text);

/* wxTempFile */
TClassDef(wxTempFile)

    /* wxTextAttr */
    TClassDef(wxTextAttr)

    /* wxTextCtrl */
    TClassDefExtend(wxTextCtrl, wxControl) void wxTextCtrl_AppendText(TSelf(wxTextCtrl) pObject,
                                                                      TClass(wxString) text);
TBool wxTextCtrl_CanCopy(TSelf(wxTextCtrl) pObject);
TBool wxTextCtrl_CanCut(TSelf(wxTextCtrl) pObject);
TBool wxTextCtrl_CanPaste(TSelf(wxTextCtrl) pObject);
TBool wxTextCtrl_CanRedo(TSelf(wxTextCtrl) pObject);
TBool wxTextCtrl_CanUndo(TSelf(wxTextCtrl) pObject);
void wxTextCtrl_ChangeValue(TSelf(wxTextCtrl) pObject, TClass(wxString) text);
void wxTextCtrl_Clear(TSelf(wxTextCtrl) pObject);
void wxTextCtrl_Copy(TSelf(wxTextCtrl) pObject);
TClass(wxTextCtrl) wxTextCtrl_Create(TClass(wxWindow) parent, int id, TClass(wxString) text,
                                     TRect(left, top, width, height), long style);
void wxTextCtrl_Cut(TSelf(wxTextCtrl) pObject);
void wxTextCtrl_DiscardEdits(TSelf(wxTextCtrl) pObject);
long wxTextCtrl_GetInsertionPoint(TSelf(wxTextCtrl) pObject);
long wxTextCtrl_GetLastPosition(TSelf(wxTextCtrl) pObject);
int wxTextCtrl_GetLineLength(TSelf(wxTextCtrl) pObject, long lineNo);
TClass(wxString) wxTextCtrl_GetLineText(TSelf(wxTextCtrl) pObject, long lineNo);
int wxTextCtrl_GetNumberOfLines(TSelf(wxTextCtrl) pObject);
void wxTextCtrl_GetSelection(TSelf(wxTextCtrl) pObject, void* from, void* toPos);
TClass(wxString) wxTextCtrl_GetValue(TSelf(wxTextCtrl) pObject);
TBool wxTextCtrl_IsEditable(TSelf(wxTextCtrl) pObject);
TBool wxTextCtrl_IsModified(TSelf(wxTextCtrl) pObject);
TBool wxTextCtrl_LoadFile(TSelf(wxTextCtrl) pObject, TClass(wxString) file, int fileType);
void wxTextCtrl_Paste(TSelf(wxTextCtrl) pObject);
int wxTextCtrl_PositionToXY(TSelf(wxTextCtrl) pObject, long pos, long* x, long* y);
void wxTextCtrl_Redo(TSelf(wxTextCtrl) pObject);
void wxTextCtrl_Remove(TSelf(wxTextCtrl) pObject, long from, long toPos);
void wxTextCtrl_Replace(TSelf(wxTextCtrl) pObject, long from, long toPos, TClass(wxString) value);
TBool wxTextCtrl_SaveFile(TSelf(wxTextCtrl) pObject, TClass(wxString) file, int fileType);
void wxTextCtrl_SetEditable(TSelf(wxTextCtrl) pObject, TBool editable);
void wxTextCtrl_SetInsertionPoint(TSelf(wxTextCtrl) pObject, long pos);
void wxTextCtrl_SetInsertionPointEnd(TSelf(wxTextCtrl) pObject);
void wxTextCtrl_SetSelection(TSelf(wxTextCtrl) pObject, long from, long toPos);
void wxTextCtrl_SetValue(TSelf(wxTextCtrl) pObject, TClass(wxString) value);
void wxTextCtrl_ShowPosition(TSelf(wxTextCtrl) pObject, long pos);
void wxTextCtrl_Undo(TSelf(wxTextCtrl) pObject);
void wxTextCtrl_WriteText(TSelf(wxTextCtrl) pObject, TClass(wxString) text);
long wxTextCtrl_XYToPosition(TSelf(wxTextCtrl) pObject, TPointLong(x, y));

/* wxTextDataObject */
TClassDefExtend(wxTextDataObject, wxDataObjectSimple) TClass(TextDataObject)
    TextDataObject_Create(TClass(wxString) text);
void TextDataObject_Delete(TSelf(TextDataObject) pObject);
TClass(wxString) TextDataObject_GetText(TSelf(TextDataObject) pObject);
void TextDataObject_SetText(TSelf(TextDataObject) pObject, TClass(wxString) text);

/* wxTextDropTarget */
TClassDefExtend(wxTextDropTarget, wxDropTarget)

    /* wxTextEntryDialog */
    TClassDefExtend(wxTextEntryDialog, wxDialog) TClass(wxTextEntryDialog)
        wxTextEntryDialog_Create(TClass(wxWindow) parent, TClass(wxString) message,
                                 TClass(wxString) caption, TClass(wxString) value, long style,
                                 int x, int y, TSize(sz_w, sz_h));
TClass(wxString) wxTextEntryDialog_GetValue(TSelf(wxTextEntryDialog) pObject);
void wxTextEntryDialog_SetValue(TSelf(wxTextEntryDialog) pObject, TClass(wxString) value);

/* wxTextFile */
TClassDef(wxTextFile)

    /* wxTextInputStream */
    TClassDef(wxTextInputStream)

    /* wxTextOutputStream */
    TClassDef(wxTextOutputStream)

    /* wxTextValidator */
    TClassDefExtend(wxTextValidator, wxValidator) TClass(wxTextValidator)
        wxTextValidator_Create(int style, void* val);
TArrayLen wxTextValidator_GetExcludes(TSelf(wxTextValidator) pObject, TArrayStringOutVoid ref);
TArrayLen wxTextValidator_GetIncludes(TSelf(wxTextValidator) pObject, TArrayStringOutVoid ref);
void wxTextValidator_SetExcludes(TSelf(wxTextValidator) pObject, TStringVoid list, int count);
void wxTextValidator_SetIncludes(TSelf(wxTextValidator) pObject, TStringVoid list, int count);
TClass(wxValidator) wxTextValidator_Clone(TSelf(wxTextValidator) pObject);
TBool wxTextValidator_TransferToWindow(TSelf(wxTextValidator) pObject);
TBool wxTextValidator_TransferFromWindow(TSelf(wxTextValidator) pObject);
int wxTextValidator_GetStyle(TSelf(wxTextValidator) pObject);
void wxTextValidator_OnChar(TSelf(wxTextValidator) pObject, TClass(wxEvent) event);
void wxTextValidator_SetStyle(TSelf(wxTextValidator) pObject, int style);

/* wxThinSplitterWindow */
TClassDefExtend(wxThinSplitterWindow, wxSplitterWindow) TClass(wxThinSplitterWindow)
    wxThinSplitterWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                                int style);
void wxThinSplitterWindow_DrawSash(TSelf(wxThinSplitterWindow) pObject, TClass(wxDC) dc);
int wxThinSplitterWindow_SashHitTest(TSelf(wxThinSplitterWindow) pObject, TPoint(x, y),
                                     int tolerance);
void wxThinSplitterWindow_SizeWindows(TSelf(wxThinSplitterWindow) pObject);

/* wxThread */
TClassDef(wxThread)

    /* wxTime */
    TClassDefExtend(wxTime, wxObject)

    /* wxTimeSpan */
    TClassDef(wxTimeSpan)

    /* wxTimer */
    TClassDefExtend(wxTimer, wxObject) TClass(wxTimer)
        wxTimer_Create(TClass(wxWindow) parent, int id);
void wxTimer_Delete(TSelf(wxTimer) pObject);
int wxTimer_GetInterval(TSelf(wxTimer) pObject);
TBool wxTimer_IsOneShot(TSelf(wxTimer) pObject);
TBool wxTimer_IsRuning(TSelf(wxTimer) pObject);
TBool wxTimer_Start(TSelf(wxTimer) pObject, int interval, TBool oneShot);
void wxTimer_Stop(TSelf(wxTimer) pObject);

/* wxTimerBase */
TClassDefExtend(wxTimerBase, wxObject)

    /* wxTimerEvent */
    TClassDefExtend(wxTimerEvent,
                    wxEvent) int wxTimerEvent_GetInterval(TSelf(wxTimerEvent) pObject);

/* wxTimerEx */
TClassDefExtend(wxTimerEx, wxTimer)

    /* wxTimerRunner */
    TClassDef(wxTimerRunner)

    /* wxTipProvider */
    TClassDef(wxTipProvider)

    /* wxTipWindow */
    TClassDefExtend(wxTipWindow,
                    wxPopupTransientWindow) void wxTipWindow_Close(TSelf(wxTipWindow) pObject);
TClass(wxTipWindow)
    wxTipWindow_Create(TClass(wxWindow) parent, TClass(wxString) text, int maxLength);
void wxTipWindow_SetBoundingRect(TSelf(wxTipWindow) pObject, TRect(x, y, width, height));
void wxTipWindow_SetTipWindowPtr(TSelf(wxTipWindow) pObject, void* windowPtr);

/* wxToggleButton */
TClassDefExtend(wxToggleButton, wxControl) TClass(wxToggleButton)
    wxToggleButton_Create(TClass(wxWindow) parent, int id, TClass(wxString) label,
                          TRect(x, y, width, height), int style);
TBool wxToggleButton_Enable(TSelf(wxToggleButton) pObject, TBool enable);
TBool wxToggleButton_GetValue(TSelf(wxToggleButton) pObject);
void wxToggleButton_SetLabel(TSelf(wxToggleButton) pObject, TClass(wxString) label);
void wxToggleButton_SetValue(TSelf(wxToggleButton) pObject, TBool state);

/* wxToolBar */
TClassDefExtend(wxToolBar, wxToolBarBase) TBool
    wxToolBar_AddControl(TSelf(wxToolBar) pObject, TClass(wxControl) ctrl);
void wxToolBar_AddSeparator(TSelf(wxToolBar) pObject);
// void       wxToolBar_AddTool( TSelf(wxToolBar) pObject, int id, TClass(wxBitmap)
// bmp, TClass(wxString) shelp, TClass(wxString) lhelp );
void wxToolBar_AddTool(TSelf(wxToolBar) pObject, int toolid, TClass(wxString) label,
                       TClass(wxBitmap) bitmap, TClass(wxBitmap) bmpDisabled, int kind,
                       TClass(wxString) shortHelp, TClass(wxString) longHelp,
                       TClass(wxObject) data);
// Obsolete
// void    wxToolBar_AddToolEx( TSelf(wxToolBar) pObject, int id, TClass(wxBitmap)
// bmp1, TClass(wxBitmap) bmp2, TBool isToggle, TPoint(x,y), TClass(wxObject)
// data, TClass(wxString) shelp, TClass(wxString) lhelp );
TClass(wxToolBar)
    wxToolBar_Create(TClass(wxWindow) parent, int id, TRect(left, top, width, height), int style);
void wxToolBar_Delete(TSelf(wxToolBar) pObject);
TBool wxToolBar_DeleteTool(TSelf(wxToolBar) pObject, int id);
TBool wxToolBar_DeleteToolByPos(TSelf(wxToolBar) pObject, int pos);
void wxToolBar_EnableTool(TSelf(wxToolBar) pObject, int id, TBool enable);
TClass(wxPoint) wxToolBar_GetMargins(TSelf(wxToolBar) pObject);
TClass(wxSize) wxToolBar_GetToolBitmapSize(TSelf(wxToolBar) pObject);
TClass(wxObject) wxToolBar_GetToolClientData(TSelf(wxToolBar) pObject, int id);
TBool wxToolBar_GetToolEnabled(TSelf(wxToolBar) pObject, int id);
TClass(wxString) wxToolBar_GetToolLongHelp(TSelf(wxToolBar) pObject, int id);
int wxToolBar_GetToolPacking(TSelf(wxToolBar) pObject);
TClass(wxString) wxToolBar_GetToolShortHelp(TSelf(wxToolBar) pObject, int id);
TClass(wxSize) wxToolBar_GetToolSize(TSelf(wxToolBar) pObject);
TBool wxToolBar_GetToolState(TSelf(wxToolBar) pObject, int id);
void wxToolBar_InsertControl(TSelf(wxToolBar) pObject, int pos, TClass(wxControl) ctrl);
void wxToolBar_InsertSeparator(TSelf(wxToolBar) pObject, int pos);
// Obsolete
// void       wxToolBar_InsertTool( TSelf(wxToolBar) pObject, int pos, int id,
// TClass(wxBitmap) bmp1, TClass(wxBitmap) bmp2, TBool isToggle,
// TClass(wxObject) data, TClass(wxString) shelp, TClass(wxString) lhelp );
TBool wxToolBar_Realize(TSelf(wxToolBar) pObject);
void wxToolBar_RemoveTool(TSelf(wxToolBar) pObject, int id);
void wxToolBar_SetMargins(TSelf(wxToolBar) pObject, TPoint(x, y));
void wxToolBar_SetToolBitmapSize(TSelf(wxToolBar) pObject, TSize(x, y));
void wxToolBar_SetToolClientData(TSelf(wxToolBar) pObject, int id, TClass(wxObject) data);
void wxToolBar_SetToolLongHelp(TSelf(wxToolBar) pObject, int id, TClass(wxString) str);
void wxToolBar_SetToolPacking(TSelf(wxToolBar) pObject, int packing);
void wxToolBar_SetToolSeparation(TSelf(wxToolBar) pObject, int separation);
void wxToolBar_SetToolShortHelp(TSelf(wxToolBar) pObject, int id, TClass(wxString) str);
void wxToolBar_ToggleTool(TSelf(wxToolBar) pObject, int id, TBool toggle);

/* wxToolBarBase */
TClassDefExtend(wxToolBarBase, wxControl)

    /* wxToolLayoutItem */
    TClassDefExtend(wxToolLayoutItem, wxObject) TBool
    wxToolLayoutItem_IsSeparator(TSelf(wxToolLayoutItem) pObject);
void wxToolLayoutItem_Rect(TSelf(wxToolLayoutItem) pObject, TRectOutVoid(x, y, width, height));

/* wxToolTip */
TClassDefExtend(wxToolTip, wxObject)

    /* wxToolWindow */
    TClassDefExtend(wxToolWindow, wxFrame) void wxToolWindow_AddMiniButton(TSelf(wxToolWindow)
                                                                               pObject,
                                                                           void* button);
TClass(wxToolWindow) wxToolWindow_Create(void* pObject, void* button, void* title);
TClass(wxClient) wxToolWindow_GetClient(TSelf(wxToolWindow) pObject);
void wxToolWindow_SetClient(TSelf(wxToolWindow) pObject, TClass(wxWindow) window);
void wxToolWindow_SetTitleFont(TSelf(wxToolWindow) pObject, void* font);

/* wxTopLevelWindow */
TClassDefExtend(wxTopLevelWindow, wxWindow) TBool
    wxTopLevelWindow_EnableCloseButton(TSelf(wxTopLevelWindow) pObject, TBool enable);
TClass(wxButton) wxTopLevelWindow_GetDefaultButton(TSelf(wxTopLevelWindow) pObject);
TClass(wxWindow) wxTopLevelWindow_GetDefaultItem(TSelf(wxTopLevelWindow) pObject);
TClass(wxIcon) wxTopLevelWindow_GetIcon(TSelf(wxTopLevelWindow) pObject);
TClass(wxString) wxTopLevelWindow_GetTitle(TSelf(wxTopLevelWindow) pObject);
TBool wxTopLevelWindow_Iconize(TSelf(wxTopLevelWindow) pObject, TBool iconize);
TBool wxTopLevelWindow_IsActive(TSelf(wxTopLevelWindow) pObject);
TBool wxTopLevelWindow_IsIconized(TSelf(wxTopLevelWindow) pObject);
TBool wxTopLevelWindow_IsMaximized(TSelf(wxTopLevelWindow) pObject);
void wxTopLevelWindow_Maximize(TSelf(wxTopLevelWindow) pObject, TBool maximize);
void wxTopLevelWindow_RequestUserAttention(TSelf(wxTopLevelWindow) pObject, int flags);
void wxTopLevelWindow_SetDefaultButton(TSelf(wxTopLevelWindow) pObject, TClass(wxButton) pBut);
void wxTopLevelWindow_SetDefaultItem(TSelf(wxTopLevelWindow) pObject, TClass(wxWindow) pBut);
void wxTopLevelWindow_SetIcon(TSelf(wxTopLevelWindow) pObject, TClass(wxIcon) pIcon);
void wxTopLevelWindow_SetIcons(TSelf(wxTopLevelWindow) pObject, void* icons);
void wxTopLevelWindow_SetMaxSize(TSelf(wxTopLevelWindow) pObject, TSize(width, height));
void wxTopLevelWindow_SetMinSize(TSelf(wxTopLevelWindow) pObject, TSize(width, height));
void wxTopLevelWindow_SetTitle(TSelf(wxTopLevelWindow) pObject, TClass(wxString) pString);

/* wxTreeCompanionWindow */
TClassDefExtend(wxTreeCompanionWindow, wxWindow) TClass(wxTreeCompanionWindow)
    wxTreeCompanionWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height),
                                 int style);
void wxTreeCompanionWindow_DrawItem(TSelf(wxTreeCompanionWindow) pObject, TClass(wxDC) dc, void* id,
                                    TRect(x, y, width, height));
TClass(wxTreeCtrl) wxTreeCompanionWindow_GetTreeCtrl(TSelf(wxTreeCompanionWindow) pObject);
void wxTreeCompanionWindow_SetTreeCtrl(TSelf(wxTreeCompanionWindow) pObject,
                                       TClass(wxTreeCtrl) treeCtrl);

/* wxTreeCtrl */
TClassDefExtend(wxTreeCtrl, wxControl) void wxTreeCtrl_AddRoot(TSelf(wxTreeCtrl) pObject,
                                                               TClass(wxString) text, int image,
                                                               int selectedImage,
                                                               TClass(wxTreeItemData) data,
                                                               TClassRef(wxTreeItemId) item);
void wxTreeCtrl_AppendItem(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) parent,
                           TClass(wxString) text, int image, int selectedImage,
                           TClass(wxTreeItemData) data, TClassRef(wxTreeItemId) item);
void wxTreeCtrl_Collapse(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_CollapseAndReset(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
TClass(wxTreeCtrl) wxTreeCtrl_Create(void* pObject, void* compareFunc, TClass(wxWindow) parent,
                                     int id, TRect(left, top, width, height), int style);
void wxTreeCtrl_Delete(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_DeleteAllItems(TSelf(wxTreeCtrl) pObject);
void wxTreeCtrl_DeleteChildren(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_EditLabel(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_EndEditLabel(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                             TBool discardChanges);
void wxTreeCtrl_EnsureVisible(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_Expand(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
TClass(wxRect) wxTreeCtrl_GetBoundingRect(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                                          TBool textOnly);
int wxTreeCtrl_GetChildrenCount(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                                TBool recursively);
int wxTreeCtrl_GetCount(TSelf(wxTreeCtrl) pObject);
TClass(wxTextCtrl) wxTreeCtrl_GetEditControl(TSelf(wxTreeCtrl) pObject);
void wxTreeCtrl_GetFirstChild(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) inputItem,
                              int* cookie, TClassRef(wxTreeItemId) result);
void wxTreeCtrl_GetFirstVisibleItem(TSelf(wxTreeCtrl) pObject, TClassRef(wxTreeItemId) result);
TClass(wxImageList) wxTreeCtrl_GetImageList(TSelf(wxTreeCtrl) pObject);
int wxTreeCtrl_GetIndent(TSelf(wxTreeCtrl) pObject);
void* wxTreeCtrl_GetItemData(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
int wxTreeCtrl_GetItemImage(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item, int which);
TClass(wxString) wxTreeCtrl_GetItemText(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_GetLastChild(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) inputItem,
                             TClassRef(wxTreeItemId) result);
void wxTreeCtrl_GetNextChild(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) inputItem, int* cookie,
                             TClassRef(wxTreeItemId) result);
void wxTreeCtrl_GetNextSibling(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) inputItem,
                               TClassRef(wxTreeItemId) result);
void wxTreeCtrl_GetNextVisible(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) inputItem,
                               TClassRef(wxTreeItemId) result);
void wxTreeCtrl_GetParent(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) inputItem,
                          TClassRef(wxTreeItemId) result);
void wxTreeCtrl_GetPrevSibling(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) inputItem,
                               TClassRef(wxTreeItemId) result);
void wxTreeCtrl_GetPrevVisible(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) inputItem,
                               TClassRef(wxTreeItemId) result);
void wxTreeCtrl_GetRootItem(TSelf(wxTreeCtrl) pObject, TClassRef(wxTreeItemId) item);
void wxTreeCtrl_GetSelection(TSelf(wxTreeCtrl) pObject, TClassRef(wxTreeItemId) item);
TArrayLen wxTreeCtrl_GetSelections(TSelf(wxTreeCtrl) pObject, TArrayIntPtrOutVoid selections);
int wxTreeCtrl_GetSpacing(TSelf(wxTreeCtrl) pObject);
TClass(wxImageList) wxTreeCtrl_GetStateImageList(TSelf(wxTreeCtrl) pObject);
void wxTreeCtrl_HitTest(TSelf(wxTreeCtrl) pObject, TPoint(x, y), int* flags,
                        TClassRef(wxTreeItemId) item);
void wxTreeCtrl_InsertItem(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) parent,
                           TClass(wxTreeItemId) idPrevious, TClass(wxString) text, int image,
                           int selectedImage, void* data, TClassRef(wxTreeItemId) item);
void wxTreeCtrl_InsertItemByIndex(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) parent, int index,
                                  TClass(wxString) text, int image, int selectedImage, void* data,
                                  TClassRef(wxTreeItemId) item);
TBool wxTreeCtrl_IsBold(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
TBool wxTreeCtrl_IsExpanded(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
TBool wxTreeCtrl_IsSelected(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
TBool wxTreeCtrl_IsVisible(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
int wxTreeCtrl_ItemHasChildren(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
int wxTreeCtrl_OnCompareItems(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item1,
                              TClass(wxTreeItemId) item2);
void wxTreeCtrl_PrependItem(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) parent,
                            TClass(wxString) text, int image, int selectedImage, void* data,
                            TClassRef(wxTreeItemId) item);
void wxTreeCtrl_ScrollTo(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_SelectItem(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_SetImageList(TSelf(wxTreeCtrl) pObject, TClass(wxImageList) imageList);
void wxTreeCtrl_SetIndent(TSelf(wxTreeCtrl) pObject, int indent);
void wxTreeCtrl_SetItemBackgroundColour(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                                        TClass(wxColour) col);
void wxTreeCtrl_SetItemBold(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item, TBool bold);
void wxTreeCtrl_SetItemData(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item, void* data);
void wxTreeCtrl_SetItemDropHighlight(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                                     TBool highlight);
void wxTreeCtrl_SetItemFont(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                            TClass(wxFont) font);
void wxTreeCtrl_SetItemHasChildren(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                                   TBool hasChildren);
void wxTreeCtrl_SetItemImage(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item, int image,
                             int which);
void wxTreeCtrl_SetItemText(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                            TClass(wxString) text);
void wxTreeCtrl_SetItemTextColour(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item,
                                  TClass(wxColour) col);
void wxTreeCtrl_SetSpacing(TSelf(wxTreeCtrl) pObject, int spacing);
void wxTreeCtrl_SetStateImageList(TSelf(wxTreeCtrl) pObject, TClass(wxImageList) imageList);
void wxTreeCtrl_SortChildren(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_Toggle(TSelf(wxTreeCtrl) pObject, TClass(wxTreeItemId) item);
void wxTreeCtrl_Unselect(TSelf(wxTreeCtrl) pObject);
void wxTreeCtrl_UnselectAll(TSelf(wxTreeCtrl) pObject);

/* wxTreeEvent */
TClassDefExtend(wxTreeEvent, wxNotifyEvent) int wxTreeEvent_GetCode(TSelf(wxTreeEvent) pObject);
void wxTreeEvent_GetItem(TSelf(wxTreeEvent) pObject, TClassRef(wxTreeItemId) ref);
TClass(wxString) wxTreeEvent_GetLabel(TSelf(wxTreeEvent) pObject);
void wxTreeEvent_GetOldItem(TSelf(wxTreeEvent) pObject, TClassRef(wxTreeItemId) ref);
TClass(wxPoint) wxTreeEvent_GetPoint(TSelf(wxTreeEvent) pObject);

/* wxTreeItemData */
TClassDefExtend(wxTreeItemData, wxClientData)

    /* wxTreeItemId */
    TClassDef(wxTreeItemId) TClass(wxTreeItemId) wxTreeItemId_Create();
void wxTreeItemId_Delete(TSelf(wxTreeItemId) pObject);
TBool wxTreeItemId_IsOk(TSelf(wxTreeItemId) pObject);

/* wxTreeListItem */
TClassDef(wxTreeListItem) TClass(wxTreeListItem) wxTreeListItem_Create();
void wxTreeListItem_Delete(TSelf(wxTreeListItem) pObject);
TBool wxTreeListItem_IsOk(TSelf(wxTreeListItem) pObject);
TClass(wxTreeListItem) wxTreeListItem_Clone(TSelf(wxTreeListItem) pObject);

/* wxTreeListCtrl */
TClassDefExtend(wxTreeListCtrl, wxWindow) TClass(wxTreeListCtrl)
    wxTreeListCtrl_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);

// Column methods
int wxTreeListCtrl_AppendColumn(TSelf(wxTreeListCtrl) pObject, TClass(wxString) title, int width,
                                int align, int flags);
unsigned wxTreeListCtrl_GetColumnCount(TSelf(wxTreeListCtrl) pObject);
TBool wxTreeListCtrl_DeleteColumn(TSelf(wxTreeListCtrl) pObject, unsigned col);
void wxTreeListCtrl_ClearColumns(TSelf(wxTreeListCtrl) pObject);
void wxTreeListCtrl_SetColumnWidth(TSelf(wxTreeListCtrl) pObject, unsigned col, int width);
int wxTreeListCtrl_GetColumnWidth(TSelf(wxTreeListCtrl) pObject, unsigned col);
int wxTreeListCtrl_WidthFor(TSelf(wxTreeListCtrl) pObject, TClass(wxString) text);

// Item methods
void wxTreeListCtrl_AppendItem(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) parent,
                               TClass(wxString) text, int imageClosed, int imageOpened,
                               TClassRef(wxTreeListItem) result);
void wxTreeListCtrl_InsertItem(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) parent,
                               TClass(wxTreeListItem) previous, TClass(wxString) text,
                               int imageClosed, int imageOpened, TClassRef(wxTreeListItem) result);
void wxTreeListCtrl_PrependItem(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) parent,
                                TClass(wxString) text, int imageClosed, int imageOpened,
                                TClassRef(wxTreeListItem) result);
void wxTreeListCtrl_DeleteItem(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);
void wxTreeListCtrl_DeleteAllItems(TSelf(wxTreeListCtrl) pObject);

// Tree navigation
void wxTreeListCtrl_GetRootItem(TSelf(wxTreeListCtrl) pObject, TClassRef(wxTreeListItem) result);
void wxTreeListCtrl_GetItemParent(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item,
                                  TClassRef(wxTreeListItem) result);
void wxTreeListCtrl_GetFirstChild(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item,
                                  TClassRef(wxTreeListItem) result);
void wxTreeListCtrl_GetNextSibling(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item,
                                   TClassRef(wxTreeListItem) result);
void wxTreeListCtrl_GetFirstItem(TSelf(wxTreeListCtrl) pObject, TClassRef(wxTreeListItem) result);
void wxTreeListCtrl_GetNextItem(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item,
                                TClassRef(wxTreeListItem) result);

// Item attributes
TClass(wxString) wxTreeListCtrl_GetItemText(TSelf(wxTreeListCtrl) pObject,
                                            TClass(wxTreeListItem) item, unsigned col);
void wxTreeListCtrl_SetItemText(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item,
                                unsigned col, TClass(wxString) text);
void wxTreeListCtrl_SetItemImage(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item,
                                 int closed, int opened);

// Expanding and collapsing
void wxTreeListCtrl_Expand(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);
void wxTreeListCtrl_Collapse(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);
TBool wxTreeListCtrl_IsExpanded(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);

// Selection handling
void wxTreeListCtrl_GetSelection(TSelf(wxTreeListCtrl) pObject, TClassRef(wxTreeListItem) result);
void wxTreeListCtrl_Select(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);
void wxTreeListCtrl_Unselect(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);
TBool wxTreeListCtrl_IsSelected(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);
void wxTreeListCtrl_SelectAll(TSelf(wxTreeListCtrl) pObject);
void wxTreeListCtrl_UnselectAll(TSelf(wxTreeListCtrl) pObject);
void wxTreeListCtrl_EnsureVisible(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);

// Checkbox handling
void wxTreeListCtrl_CheckItem(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item,
                              int state);
void wxTreeListCtrl_UncheckItem(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);
void wxTreeListCtrl_CheckItemRecursively(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item,
                                         int state);
void wxTreeListCtrl_UpdateItemParentStateRecursively(TSelf(wxTreeListCtrl) pObject,
                                                     TClass(wxTreeListItem) item);
int wxTreeListCtrl_GetCheckedState(TSelf(wxTreeListCtrl) pObject, TClass(wxTreeListItem) item);
TBool wxTreeListCtrl_AreAllChildrenInState(TSelf(wxTreeListCtrl) pObject,
                                           TClass(wxTreeListItem) item, int state);

// Sorting
void wxTreeListCtrl_SetSortColumn(TSelf(wxTreeListCtrl) pObject, unsigned col,
                                  TBool ascendingOrder);
TBool wxTreeListCtrl_GetSortColumn(TSelf(wxTreeListCtrl) pObject, unsigned* col,
                                   TBool* ascendingOrder);

// View window
TClass(wxWindow) wxTreeListCtrl_GetView(TSelf(wxTreeListCtrl) pObject);
TClass(wxDataViewCtrl) wxTreeListCtrl_GetDataView(TSelf(wxTreeListCtrl) pObject);

/* wxTreeListEvent */
TClassDefExtend(wxTreeListEvent,
                wxNotifyEvent) void wxTreeListEvent_GetItem(TSelf(wxTreeListEvent) pObject,
                                                            TClassRef(wxTreeListItem) result);
int wxTreeListEvent_GetOldCheckedState(TSelf(wxTreeListEvent) pObject);
unsigned wxTreeListEvent_GetColumn(TSelf(wxTreeListEvent) pObject);
void wxTreeListEvent_Veto(TSelf(wxTreeListEvent) pObject);
void wxTreeListEvent_Allow(TSelf(wxTreeListEvent) pObject);
TBool wxTreeListEvent_IsAllowed(TSelf(wxTreeListEvent) pObject);

// Style constants
int expTL_SINGLE();
int expTL_MULTIPLE();
int expTL_CHECKBOX();
int expTL_3STATE();
int expTL_USER_3STATE();
int expTL_NO_HEADER();
int expTL_DEFAULT_STYLE();

// Event exports
int expEVT_TREELIST_SELECTION_CHANGED();
int expEVT_TREELIST_ITEM_EXPANDING();
int expEVT_TREELIST_ITEM_EXPANDED();
int expEVT_TREELIST_ITEM_CHECKED();
int expEVT_TREELIST_ITEM_ACTIVATED();
int expEVT_TREELIST_ITEM_CONTEXT_MENU();
int expEVT_TREELIST_COLUMN_SORTED();

/* wxTreeLayout */
TClassDefExtend(wxTreeLayout, wxObject)

    /* wxTreeLayoutStored */
    TClassDefExtend(wxTreeLayoutStored, wxTreeLayout)

    /* wxURL */
    TClassDefExtend(wxURL, wxObject)

    /* wxUpdateUIEvent */
    TClassDefExtend(wxUpdateUIEvent, wxEvent) void wxUpdateUIEvent_Check(TSelf(wxUpdateUIEvent)
                                                                             pObject,
                                                                         TBool check);
void wxUpdateUIEvent_CopyObject(TSelf(wxUpdateUIEvent) pObject, TClass(wxObject) obj);
void wxUpdateUIEvent_Enable(TSelf(wxUpdateUIEvent) pObject, TBool enable);
TBool wxUpdateUIEvent_GetChecked(TSelf(wxUpdateUIEvent) pObject);
TBool wxUpdateUIEvent_GetEnabled(TSelf(wxUpdateUIEvent) pObject);
TBool wxUpdateUIEvent_GetSetChecked(TSelf(wxUpdateUIEvent) pObject);
TBool wxUpdateUIEvent_GetSetEnabled(TSelf(wxUpdateUIEvent) pObject);
TBool wxUpdateUIEvent_GetSetText(TSelf(wxUpdateUIEvent) pObject);
TClass(wxString) wxUpdateUIEvent_GetText(TSelf(wxUpdateUIEvent) pObject);
void wxUpdateUIEvent_SetText(TSelf(wxUpdateUIEvent) pObject, TClass(wxString) text);

/* wxValidator */
TClassDefExtend(wxValidator, wxEvtHandler) TClass(wxValidator) wxValidator_Create();
void wxValidator_Delete(TSelf(wxValidator) pObject);
TClass(wxWindow) wxValidator_GetWindow(TSelf(wxValidator) pObject);
// Obsolete
// void       wxValidator_SetBellOnError( TBool doIt );
void wxValidator_SuppressBellOnError(TBool doIt);
void wxValidator_SetWindow(TSelf(wxValidator) pObject, TClass(wxWindow) win);
TBool wxValidator_TransferFromWindow(TSelf(wxValidator) pObject);
TBool wxValidator_TransferToWindow(TSelf(wxValidator) pObject);
TBool wxValidator_Validate(TSelf(wxValidator) pObject, TClass(wxWindow) parent);

/* wxVariant */
TClassDefExtend(wxVariant, wxObject)

    /* wxVariantData */
    TClassDefExtend(wxVariantData, wxObject)

    /* wxView */
    TClassDefExtend(wxView, wxEvtHandler)

    /* wxSound */
    TClassDefExtend(wxSound, wxEvtHandler)

    /* wxWebView */
    TClassDefExtend(wxWebView, wxControl) TClass(wxWebView)
        wxWebView_New(TClass(wxWindow) parent, int id, TClass(wxString) url,
                      TRect(x, y, width, height), TClass(wxString) backend, int style);
void wxWebView_LoadURL(TSelf(wxWebView) pObject, TClass(wxString) url);
void wxWebView_GoBack(TSelf(wxWebView) pObject);
void wxWebView_GoForward(TSelf(wxWebView) pObject);
void wxWebView_Stop(TSelf(wxWebView) pObject);
void wxWebView_Reload(TSelf(wxWebView) pObject, int flags);
TBool wxWebView_CanGoBack(TSelf(wxWebView) pObject);
TBool wxWebView_CanGoForward(TSelf(wxWebView) pObject);
TClass(wxString) wxWebView_GetCurrentURL(TSelf(wxWebView) pObject);
TClass(wxString) wxWebView_GetCurrentTitle(TSelf(wxWebView) pObject);
TClass(wxString) wxWebView_GetPageSource(TSelf(wxWebView) pObject);
TClass(wxString) wxWebView_GetPageText(TSelf(wxWebView) pObject);
TBool wxWebView_IsBusy(TSelf(wxWebView) pObject);
void wxWebView_SetPage(TSelf(wxWebView) pObject, TClass(wxString) html, TClass(wxString) baseUrl);
TBool wxWebView_RunScript(TSelf(wxWebView) pObject, TClass(wxString) javascript,
                          TClass(wxString) output);
void wxWebView_SetZoom(TSelf(wxWebView) pObject, int zoom);
int wxWebView_GetZoom(TSelf(wxWebView) pObject);
void wxWebView_SetZoomType(TSelf(wxWebView) pObject, int zoomType);
int wxWebView_GetZoomType(TSelf(wxWebView) pObject);
float wxWebView_GetZoomFactor(TSelf(wxWebView) pObject);
void wxWebView_SetZoomFactor(TSelf(wxWebView) pObject, float zoom);
void wxWebView_EnableContextMenu(TSelf(wxWebView) pObject, TBool enable);
TBool wxWebView_IsContextMenuEnabled(TSelf(wxWebView) pObject);
TBool wxWebView_CanCut(TSelf(wxWebView) pObject);
TBool wxWebView_CanCopy(TSelf(wxWebView) pObject);
TBool wxWebView_CanPaste(TSelf(wxWebView) pObject);
void wxWebView_Cut(TSelf(wxWebView) pObject);
void wxWebView_Copy(TSelf(wxWebView) pObject);
void wxWebView_Paste(TSelf(wxWebView) pObject);
TClass(wxString) wxWebView_GetSelectedText(TSelf(wxWebView) pObject);
TClass(wxString) wxWebView_GetSelectedSource(TSelf(wxWebView) pObject);
void wxWebView_ClearSelection(TSelf(wxWebView) pObject);
TBool wxWebView_HasSelection(TSelf(wxWebView) pObject);
long wxWebView_Find(TSelf(wxWebView) pObject, TClass(wxString) text, int flags);
void wxWebView_Print(TSelf(wxWebView) pObject);
TBool wxWebView_IsAccessToDevToolsEnabled(TSelf(wxWebView) pObject);
void wxWebView_EnableAccessToDevTools(TSelf(wxWebView) pObject, TBool enable);
TBool wxWebView_IsBackendAvailable(TClass(wxString) backend);
void wxWebView_SetEditable(TSelf(wxWebView) pObject, TBool enable);
TBool wxWebView_IsEditable(TSelf(wxWebView) pObject);

/* wxWebViewEvent */
TClassDefExtend(wxWebViewEvent, wxNotifyEvent) TClass(wxString)
    wxWebViewEvent_GetURL(TSelf(wxWebViewEvent) pObject);
TClass(wxString) wxWebViewEvent_GetTarget(TSelf(wxWebViewEvent) pObject);
int wxWebViewEvent_GetNavigationAction(TSelf(wxWebViewEvent) pObject);
int wxWebViewEvent_GetInt(TSelf(wxWebViewEvent) pObject);
TClass(wxString) wxWebViewEvent_GetString(TSelf(wxWebViewEvent) pObject);

// Zoom constants
int expWEBVIEW_ZOOM_TINY();
int expWEBVIEW_ZOOM_SMALL();
int expWEBVIEW_ZOOM_MEDIUM();
int expWEBVIEW_ZOOM_LARGE();
int expWEBVIEW_ZOOM_LARGEST();
int expWEBVIEW_ZOOM_TYPE_LAYOUT();
int expWEBVIEW_ZOOM_TYPE_TEXT();

// Reload flags
int expWEBVIEW_RELOAD_DEFAULT();
int expWEBVIEW_RELOAD_NO_CACHE();

// Find flags
int expWEBVIEW_FIND_WRAP();
int expWEBVIEW_FIND_ENTIRE_WORD();
int expWEBVIEW_FIND_MATCH_CASE();
int expWEBVIEW_FIND_HIGHLIGHT_RESULT();
int expWEBVIEW_FIND_BACKWARDS();
int expWEBVIEW_FIND_DEFAULT();

// Navigation error constants
int expWEBVIEW_NAV_ERR_CONNECTION();
int expWEBVIEW_NAV_ERR_CERTIFICATE();
int expWEBVIEW_NAV_ERR_AUTH();
int expWEBVIEW_NAV_ERR_SECURITY();
int expWEBVIEW_NAV_ERR_NOT_FOUND();
int expWEBVIEW_NAV_ERR_REQUEST();
int expWEBVIEW_NAV_ERR_USER_CANCELLED();
int expWEBVIEW_NAV_ERR_OTHER();

// Navigation action flags
int expWEBVIEW_NAV_ACTION_NONE();
int expWEBVIEW_NAV_ACTION_USER();
int expWEBVIEW_NAV_ACTION_OTHER();

/* wxWindow */
TClassDefExtend(wxWindow, wxEvtHandler) void wxWindow_AddChild(TSelf(wxWindow) pObject,
                                                               TClass(wxWindow) child);
void wxWindow_AddConstraintReference(TSelf(wxWindow) pObject, TClass(wxWindow) otherWin);
void wxWindow_CaptureMouse(TSelf(wxWindow) pObject);
void wxWindow_Center(TSelf(wxWindow) pObject, int direction);
void wxWindow_CenterOnParent(TSelf(wxWindow) pObject, int dir);
void wxWindow_ClearBackground(TSelf(wxWindow) pObject);
TClass(wxPoint) wxWindow_ClientToScreen(TSelf(wxWindow) pObject, TPoint(x, y));
TBool wxWindow_Close(TSelf(wxWindow) pObject, TBool force);
TClass(wxPoint) wxWindow_ConvertDialogToPixels(TSelf(wxWindow) pObject);
TClass(wxPoint) wxWindow_ConvertPixelsToDialog(TSelf(wxWindow) pObject);
TClass(wxWindow)
    wxWindow_Create(TClass(wxWindow) parent, int id, TRect(x, y, width, height), int style);
void wxWindow_DeleteRelatedConstraints(TSelf(wxWindow) pObject);
TBool wxWindow_Destroy(TSelf(wxWindow) pObject);
TBool wxWindow_DestroyChildren(TSelf(wxWindow) pObject);
TBool wxWindow_Disable(TSelf(wxWindow) pObject);
int wxWindow_DoPhase(TSelf(wxWindow) pObject, int phase);
TBool wxWindow_Enable(TSelf(wxWindow) pObject);
TClass(wxWindow) wxWindow_FindFocus(TSelf(wxWindow) pObject);
TClass(wxWindow) wxWindow_FindWindow(TSelf(wxWindow) pObject, TClass(wxString) name);
void wxWindow_Fit(TSelf(wxWindow) pObject);
void wxWindow_FitInside(TSelf(wxWindow) pObject);
void wxWindow_Freeze(TSelf(wxWindow) pObject);
TClass(wxSize) wxWindow_GetEffectiveMinSize(TSelf(wxWindow) pObject);
int wxWindow_GetAutoLayout(TSelf(wxWindow) pObject);
void wxWindow_GetBackgroundColour(TSelf(wxWindow) pObject, TClassRef(wxColour) ref);
TClass(wxSize) wxWindow_GetBestSize(TSelf(wxWindow) pObject);
TClass(wxCaret) wxWindow_GetCaret(TSelf(wxWindow) pObject);
int wxWindow_GetCharHeight(TSelf(wxWindow) pObject);
int wxWindow_GetCharWidth(TSelf(wxWindow) pObject);
int wxWindow_GetChildren(TSelf(wxWindow) pObject, void* result, int count);
TClass(wxClientData) wxWindow_GetClientData(TSelf(wxWindow) pObject);
TClass(wxSize) wxWindow_GetClientSize(TSelf(wxWindow) pObject);
void wxWindow_GetClientSizeConstraint(TSelf(wxWindow) pObject, TSizeOut(width, height));
TClass(wxLayoutConstraints) wxWindow_GetConstraints(TSelf(wxWindow) pObject);
void* wxWindow_GetConstraintsInvolvedIn(TSelf(wxWindow) pObject);
TClass(wxCursor) wxWindow_GetCursor(TSelf(wxWindow) pObject);
TClass(wxDropTarget) wxWindow_GetDropTarget(TSelf(wxWindow) pObject);
TClass(wxEvtHandler) wxWindow_GetEventHandler(TSelf(wxWindow) pObject);
void wxWindow_GetFont(TSelf(wxWindow) pObject, TClassRef(wxFont) ref);
void wxWindow_GetForegroundColour(TSelf(wxWindow) pObject, TClassRef(wxColour) ref);
void* wxWindow_GetHandle(TSelf(wxWindow) pObject);
int wxWindow_GetId(TSelf(wxWindow) pObject);
TClass(wxString) wxWindow_GetLabel(TSelf(wxWindow) pObject);
int wxWindow_GetLabelEmpty(TSelf(wxWindow) pObject);
int wxWindow_GetMaxHeight(TSelf(wxWindow) pObject);
int wxWindow_GetMaxWidth(TSelf(wxWindow) pObject);
int wxWindow_GetMinHeight(TSelf(wxWindow) pObject);
int wxWindow_GetMinWidth(TSelf(wxWindow) pObject);
TClass(wxString) wxWindow_GetName(TSelf(wxWindow) pObject);
TClass(wxWindow) wxWindow_GetParent(TSelf(wxWindow) pObject);
TClass(wxPoint) wxWindow_GetPosition(TSelf(wxWindow) pObject);
void wxWindow_GetPositionConstraint(TSelf(wxWindow) pObject, TPointOut(x, y));
TClass(wxRect) wxWindow_GetRect(TSelf(wxWindow) pObject);
int wxWindow_GetScrollPos(TSelf(wxWindow) pObject, int orient);
int wxWindow_GetScrollRange(TSelf(wxWindow) pObject, int orient);
int wxWindow_GetScrollThumb(TSelf(wxWindow) pObject, int orient);
TClass(wxSize) wxWindow_GetSize(TSelf(wxWindow) pObject);
void wxWindow_GetSizeConstraint(TSelf(wxWindow) pObject, TSizeOut(width, height));
TClass(wxSizer) wxWindow_GetSizer(TSelf(wxWindow) pObject);
void wxWindow_GetTextExtent(TSelf(wxWindow) pObject, TClass(wxString) string, int* x, int* y,
                            int* descent, int* externalLeading, TClass(wxFont) theFont);
TClass(wxString) wxWindow_GetToolTip(TSelf(wxWindow) pObject);
TClass(wxRegion) wxWindow_GetUpdateRegion(TSelf(wxWindow) pObject);
TClass(wxValidator) wxWindow_GetValidator(TSelf(wxWindow) pObject);
TClass(wxSize) wxWindow_GetVirtualSize(TSelf(wxWindow) pObject);
int wxWindow_GetWindowStyleFlag(TSelf(wxWindow) pObject);
TBool wxWindow_HasFlag(TSelf(wxWindow) pObject, int flag);
TBool wxWindow_HasFocus(TSelf(wxWindow) pObject);
TBool wxWindow_Hide(TSelf(wxWindow) pObject);
void wxWindow_InitDialog(TSelf(wxWindow) pObject);
TBool wxWindow_IsBeingDeleted(TSelf(wxWindow) pObject);
TBool wxWindow_IsEnabled(TSelf(wxWindow) pObject);
TBool wxWindow_IsExposed(TSelf(wxWindow) pObject, TRect(x, y, width, height));
TBool wxWindow_IsShown(TSelf(wxWindow) pObject);
TBool wxWindow_IsTopLevel(TSelf(wxWindow) pObject);
int wxWindow_Layout(TSelf(wxWindow) pObject);
int wxWindow_LayoutPhase1(TSelf(wxWindow) pObject, int* noChanges);
int wxWindow_LayoutPhase2(TSelf(wxWindow) pObject, int* noChanges);
void wxWindow_Lower(TSelf(wxWindow) pObject);
// Obsolete
// void       wxWindow_MakeModal( TSelf(wxWindow) pObject, TBool modal );
void wxWindow_Move(TSelf(wxWindow) pObject, TPoint(x, y), int flags);
void wxWindow_MoveConstraint(TSelf(wxWindow) pObject, TPoint(x, y));
void* wxWindow_PopEventHandler(TSelf(wxWindow) pObject, TBool deleteHandler);
int wxWindow_PopupMenu(TSelf(wxWindow) pObject, TClass(wxMenu) menu, TPoint(x, y));
void wxWindow_PrepareDC(TSelf(wxWindow) pObject, TClass(wxDC) dc);
void wxWindow_PushEventHandler(TSelf(wxWindow) pObject, TClass(wxEvtHandler) handler);
void wxWindow_Raise(TSelf(wxWindow) pObject);
void wxWindow_Refresh(TSelf(wxWindow) pObject, TBool eraseBackground);
void wxWindow_RefreshRect(TSelf(wxWindow) pObject, TBool eraseBackground,
                          TRect(x, y, width, height));
void wxWindow_ReleaseMouse(TSelf(wxWindow) pObject);
void wxWindow_RemoveChild(TSelf(wxWindow) pObject, TClass(wxWindow) child);
void wxWindow_RemoveConstraintReference(TSelf(wxWindow) pObject, TClass(wxWindow) otherWin);
int wxWindow_Reparent(TSelf(wxWindow) pObject, TClass(wxWindow) parent);
void wxWindow_ResetConstraints(TSelf(wxWindow) pObject);
TClass(wxPoint) wxWindow_ScreenToClient(TSelf(wxWindow) pObject, TPoint(x, y));
void wxWindow_ScrollWindow(TSelf(wxWindow) pObject, TVector(dx, dy));
void wxWindow_ScrollWindowRect(TSelf(wxWindow) pObject, TVector(dx, dy),
                               TRect(x, y, width, height));
void wxWindow_SetAcceleratorTable(TSelf(wxWindow) pObject, TClass(wxAcceleratorTable) accel);
void wxWindow_SetAutoLayout(TSelf(wxWindow) pObject, TBool autoLayout);
int wxWindow_SetBackgroundColour(TSelf(wxWindow) pObject, TClass(wxColour) colour);
void wxWindow_SetCaret(TSelf(wxWindow) pObject, TClass(wxCaret) caret);
void wxWindow_SetClientData(TSelf(wxWindow) pObject, TClass(wxClientData) data);
void wxWindow_SetClientObject(TSelf(wxWindow) pObject, TClass(wxClientData) data);
void wxWindow_SetClientSize(TSelf(wxWindow) pObject, TSize(width, height));
void wxWindow_SetConstraintSizes(TSelf(wxWindow) pObject, int recurse);
void wxWindow_SetConstraints(TSelf(wxWindow) pObject, TClass(wxLayoutConstraints) constraints);
int wxWindow_SetCursor(TSelf(wxWindow) pObject, TClass(wxCursor) cursor);
void wxWindow_SetDropTarget(TSelf(wxWindow) pObject, TClass(wxDropTarget) dropTarget);
void wxWindow_SetExtraStyle(TSelf(wxWindow) pObject, long exStyle);
void wxWindow_SetFocus(TSelf(wxWindow) pObject);
int wxWindow_SetFont(TSelf(wxWindow) pObject, TClass(wxFont) font);
int wxWindow_SetForegroundColour(TSelf(wxWindow) pObject, TClass(wxColour) colour);
void wxWindow_SetId(TSelf(wxWindow) pObject, int id);
void wxWindow_SetLabel(TSelf(wxWindow) pObject, TClass(wxString) title);
void wxWindow_SetName(TSelf(wxWindow) pObject, TClass(wxString) name);
void wxWindow_SetScrollPos(TSelf(wxWindow) pObject, int orient, int pos, TBool refresh);
void wxWindow_SetScrollbar(TSelf(wxWindow) pObject, int orient, int pos, int thumbVisible,
                           int range, TBool refresh);
void wxWindow_SetSize(TSelf(wxWindow) pObject, TRect(x, y, width, height), int sizeFlags);
void wxWindow_SetSizeConstraint(TSelf(wxWindow) pObject, TRect(x, y, width, height));
void wxWindow_SetSizeHints(TSelf(wxWindow) pObject, int minW, int minH, int maxW, int maxH,
                           int incW, int incH);
void wxWindow_SetSizer(TSelf(wxWindow) pObject, TClass(wxSizer) sizer, TBool deleteOld);
void wxWindow_SetSizerAndFit(TSelf(wxWindow) pObject, TClass(wxSizer) sizer, TBool deleteOld);
void wxWindow_SetToolTip(TSelf(wxWindow) pObject, TClass(wxString) tip);
void wxWindow_SetValidator(TSelf(wxWindow) pObject, TClass(wxValidator) validator);
void wxWindow_SetWindowStyleFlag(TSelf(wxWindow) pObject, long style);
TBool wxWindow_Show(TSelf(wxWindow) pObject);
void wxWindow_Thaw(TSelf(wxWindow) pObject);
TBool wxWindow_TransferDataFromWindow(TSelf(wxWindow) pObject);
TBool wxWindow_TransferDataToWindow(TSelf(wxWindow) pObject);
void wxWindow_UnsetConstraints(TSelf(wxWindow) pObject, void* constraints);
void wxWindow_Update(TSelf(wxWindow) pObject);
void wxWindow_UpdateWindowUI(TSelf(wxWindow) pObject, long flags);
TBool wxWindow_Validate(TSelf(wxWindow) pObject);
void wxWindow_SetVirtualSize(TSelf(wxWindow) pObject, TSize(width, height));
void wxWindow_WarpPointer(TSelf(wxWindow) pObject, TPoint(x, y));

/* wxWindowCreateEvent */
TClassDefExtend(wxWindowCreateEvent, wxCommandEvent) TClass(wxWindow)
    wxWindowCreateEvent_GetWindow(TSelf(wxWindowCreateEvent) pObject);

/* wxWindowDC */
TClassDefExtend(wxWindowDC, wxDC) TClass(wxWindowDC) wxWindowDC_Create(TClass(wxWindow) win);
void wxWindowDC_Delete(TSelf(wxWindowDC) pObject);

/* wxWindowDestroyEvent */
TClassDefExtend(wxWindowDestroyEvent, wxCommandEvent) TClass(wxWindow)
    wxWindowDestroyEvent_GetWindow(TSelf(wxWindowDestroyEvent) pObject);

/* wxWindowDisabler */
TClassDef(wxWindowDisabler)

    /* wxWrapSizer */
    TClassDefExtend(wxWrapSizer, wxBoxSizer) TClass(wxWrapSizer)
        wxWrapSizer_Create(int orient, int flags);
int wxWrapSizer_GetOrientation(TSelf(wxWrapSizer) pObject);
void wxWrapSizer_SetOrientation(TSelf(wxWrapSizer) pObject, int orient);
TBool wxWrapSizer_InformFirstDirection(TSelf(wxWrapSizer) pObject, int direction, int size,
                                       int availableOtherDir);

/* wxWizard */
TClassDefExtend(wxWizard, wxDialog) void wxWizard_Chain(TClass(wxWizardPageSimple) first,
                                                        TClass(wxWizardPageSimple) second);
TClass(wxWizard)
    wxWizard_Create(TClass(wxWindow) parent, int id, TClass(wxString) text, TClass(wxBitmap) bitmap,
                    TRect(left, top, width, height), long style);
TClass(wxWizardPage) wxWizard_GetCurrentPage(TSelf(wxWizard) pObject);
TClass(wxSize) wxWizard_GetPageSize(TSelf(wxWizard) pObject);
int wxWizard_RunWizard(TSelf(wxWizard) pObject, TClass(wxWizardPage) firstPage);
void wxWizard_SetPageSize(TSelf(wxWizard) pObject, TSize(width, height));

/* wxWizardEvent */
TClassDefExtend(wxWizardEvent,
                wxNotifyEvent) int wxWizardEvent_GetDirection(TSelf(wxWizardEvent) pObject);

/* wxWizardPage */
TClassDefExtend(wxWizardPage, wxPanel)

    /* wxWizardPageSimple */
    TClassDefExtend(wxWizardPageSimple, wxWizardPage) TClass(wxWizardPageSimple)
        wxWizardPageSimple_Create(TClass(wxWizard) parent, TClass(wxWizardPage) prev,
                                  TClass(wxWizardPage) next, TClass(wxBitmap) bitmap);
void wxWizardPageSimple_GetBitmap(TSelf(wxWizardPageSimple) pObject, TClassRef(wxBitmap) ref);
TClass(wxWizardPageSimple) wxWizardPageSimple_GetNext(TSelf(wxWizardPageSimple) pObject);
TClass(wxWizardPageSimple) wxWizardPageSimple_GetPrev(TSelf(wxWizardPageSimple) pObject);
void wxWizardPageSimple_SetNext(TSelf(wxWizardPageSimple) pObject, TClass(wxWizardPageSimple) next);
void wxWizardPageSimple_SetPrev(TSelf(wxWizardPageSimple) pObject, TClass(wxWizardPageSimple) prev);

/* wxXmlResource */
TClassDefExtend(wxXmlResource, wxObject) void wxXmlResource_AddHandler(TSelf(wxXmlResource) pObject,
                                                                       TClass(wxEvtHandler)
                                                                           handler);
void wxXmlResource_AddSubclassFactory(TSelf(wxXmlResource) pObject, void* factory);
int wxXmlResource_AttachUnknownControl(TSelf(wxXmlResource) pObject, TClass(wxControl) control,
                                       TClass(wxWindow) parent);
void wxXmlResource_ClearHandlers(TSelf(wxXmlResource) pObject);
int wxXmlResource_CompareVersion(TSelf(wxXmlResource) pObject, int major, int minor, int release,
                                 int revision);
TClass(wxXmlResource) wxXmlResource_Create(int flags);
TClass(wxXmlResource) wxXmlResource_CreateFromFile(TClass(wxString) filemask, int flags);
void wxXmlResource_Delete(TSelf(wxXmlResource) pObject);
TClass(wxXmlResource) wxXmlResource_Get();
TClass(wxString) wxXmlResource_GetDomain(TSelf(wxXmlResource) pObject);
int wxXmlResource_GetFlags(TSelf(wxXmlResource) pObject);
long wxXmlResource_GetVersion(TSelf(wxXmlResource) pObject);
int wxXmlResource_GetXRCID(TSelf(wxXmlResource) pObject, TClass(wxString) str_id,
                           int value_if_not_found);
void wxXmlResource_InitAllHandlers(TSelf(wxXmlResource) pObject);
void wxXmlResource_InsertHandler(TSelf(wxXmlResource) pObject, TClass(wxEvtHandler) handler);
TBool wxXmlResource_Load(TSelf(wxXmlResource) pObject, TClass(wxString) filemask);
void wxXmlResource_LoadBitmap(TSelf(wxXmlResource) pObject, TClass(wxString) name,
                              TClassRef(wxBitmap) ref);
TClass(wxDialog) wxXmlResource_LoadDialog(TSelf(wxXmlResource) pObject, TClass(wxWindow) parent,
                                          TClass(wxString) name);
TClass(wxFrame) wxXmlResource_LoadFrame(TSelf(wxXmlResource) pObject, TClass(wxWindow) parent,
                                        TClass(wxString) name);
void wxXmlResource_LoadIcon(TSelf(wxXmlResource) pObject, TClass(wxString) name,
                            TClassRef(wxIcon) ref);
TClass(wxMenu) wxXmlResource_LoadMenu(TSelf(wxXmlResource) pObject, TClass(wxString) name);
TClass(wxMenuBar) wxXmlResource_LoadMenuBar(TSelf(wxXmlResource) pObject, TClass(wxWindow) parent,
                                            TClass(wxString) name);
TClass(wxPanel) wxXmlResource_LoadPanel(TSelf(wxXmlResource) pObject, TClass(wxWindow) parent,
                                        TClass(wxString) name);
TClass(wxToolBar) wxXmlResource_LoadToolBar(TSelf(wxXmlResource) pObject, TClass(wxWindow) parent,
                                            TClass(wxString) name);
TClass(wxSizer) wxXmlResource_GetSizer(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxBoxSizer) wxXmlResource_GetBoxSizer(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxStaticBoxSizer)
    wxXmlResource_GetStaticBoxSizer(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxGridSizer) wxXmlResource_GetGridSizer(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxFlexGridSizer)
    wxXmlResource_GetFlexGridSizer(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxBitmapButton)
    wxXmlResource_GetBitmapButton(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxButton) wxXmlResource_GetButton(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxCalendarCtrl)
    wxXmlResource_GetCalendarCtrl(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxCheckBox) wxXmlResource_GetCheckBox(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxCheckListBox)
    wxXmlResource_GetCheckListBox(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxChoice) wxXmlResource_GetChoice(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxComboBox) wxXmlResource_GetComboBox(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxGauge) wxXmlResource_GetGauge(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxGrid) wxXmlResource_GetGrid(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxHtmlWindow) wxXmlResource_GetHtmlWindow(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxListBox) wxXmlResource_GetListBox(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxListCtrl) wxXmlResource_GetListCtrl(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxMDIChildFrame)
    wxXmlResource_GetMDIChildFrame(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxMDIParentFrame)
    wxXmlResource_GetMDIParentFrame(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxMenu) wxXmlResource_GetMenu(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxMenuBar) wxXmlResource_GetMenuBar(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxMenuItem) wxXmlResource_GetMenuItem(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxNotebook) wxXmlResource_GetNotebook(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxPanel) wxXmlResource_GetPanel(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxRadioButton)
    wxXmlResource_GetRadioButton(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxRadioBox) wxXmlResource_GetRadioBox(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxScrollBar) wxXmlResource_GetScrollBar(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxScrolledWindow)
    wxXmlResource_GetScrolledWindow(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxSlider) wxXmlResource_GetSlider(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxSpinButton) wxXmlResource_GetSpinButton(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxSpinCtrl) wxXmlResource_GetSpinCtrl(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxSplitterWindow)
    wxXmlResource_GetSplitterWindow(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxStaticBitmap)
    wxXmlResource_GetStaticBitmap(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxStaticBox) wxXmlResource_GetStaticBox(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxStaticLine) wxXmlResource_GetStaticLine(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxStaticText) wxXmlResource_GetStaticText(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxTextCtrl) wxXmlResource_GetTextCtrl(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TClass(wxTreeCtrl) wxXmlResource_GetTreeCtrl(TSelf(wxWindow) pObject, TClass(wxString) str_id);
TBool wxXmlResource_Unload(TSelf(wxXmlResource) pObject, TClass(wxString) filemask);
TClass(wxXmlResource) wxXmlResource_Set(TSelf(wxXmlResource) pObject, TSelf(wxXmlResource) res);
void wxXmlResource_SetDomain(TSelf(wxXmlResource) pObject, TClass(wxString) domain);
void wxXmlResource_SetFlags(TSelf(wxXmlResource) pObject, int flags);

TClassDefExtend(wxXmlResourceHandler, wxObject)

    TClassDefExtend(wxZipInputStream, wxInputStream)

        TClassDefExtend(wxZlibInputStream, wxFilterInputStream)

            TClassDefExtend(wxZlibOutputStream, wxFilterOutputStream)

                TClassDefExtend(wxPropertyGrid, wxControl) TClass(wxPGProperty)
                    wxPropertyGrid_Append(TSelf(wxPropertyGrid) pObject, TClass(wxPGProperty) prop);
TClass(wxPropertyGrid) wxPropertyGrid_Create(TClass(wxWindow) parent, int id,
                                             TRect(left, top, width, height), int style);
TBool wxPropertyGrid_DisableProperty(TSelf(wxPropertyGrid) pObject, TClass(wxString) propName);

TClassDefExtend(wxPropertyGridEvent, wxNotifyEvent) TBool
    wxPropertyGridEvent_HasProperty(TSelf(wxPropertyGridEvent) pObject);
TClass(wxPGProperty) wxPropertyGridEvent_GetProperty(TSelf(wxPropertyGridEvent) pObject);

TClassDefExtend(wxPGProperty, wxObject) TClass(wxString)
    wxPGProperty_GetLabel(TSelf(wxPGProperty) pObject);
TClass(wxString) wxPGProperty_GetName(TSelf(wxPGProperty) pObject);
TClass(wxString) wxPGProperty_GetValueAsString(TSelf(wxPGProperty) pObject);
TClass(wxString) wxPGProperty_GetValueType(TSelf(wxPGProperty) pObject);
void wxPGProperty_SetHelpString(TSelf(wxPGProperty) pObject, TClass(wxString) helpString);

TClassDefExtend(wxStringProperty, wxPGProperty) TClass(wxStringProperty)
    wxStringProperty_Create(TClass(wxString) label, TClass(wxString) name, TClass(wxString) value);

TClassDefExtend(wxIntProperty, wxPGProperty) TClass(wxIntProperty)
    wxIntProperty_Create(TClass(wxString) label, TClass(wxString) name, int value);

TClassDefExtend(wxBoolProperty, wxPGProperty) TClass(wxBoolProperty)
    wxBoolProperty_Create(TClass(wxString) label, TClass(wxString) name, TBool value);

TClassDefExtend(wxFloatProperty, wxPGProperty) TClass(wxFloatProperty)
    wxFloatProperty_Create(TClass(wxString) label, TClass(wxString) name, float value);

TClassDefExtend(wxDateProperty, wxPGProperty) TClass(wxDateProperty)
    wxDateProperty_Create(TClass(wxString) label, TClass(wxString) name, TClass(wxDateTime) value);

TClassDefExtend(wxFileProperty, wxPGProperty) TClass(wxFileProperty)
    wxFileProperty_Create(TClass(wxString) label, TClass(wxString) name, TClass(wxString) value);

TClassDefExtend(wxPropertyCategory, wxPGProperty) TClass(wxPropertyCategory)
    wxPropertyCategory_Create(TClass(wxString) label);
