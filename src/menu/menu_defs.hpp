#pragma once

#include <stdint.h>

/* ===== Menu input events ===== */
enum MenuEvent : uint8_t {
  EVT_NONE = 0,
  EVT_UP,
  EVT_DOWN,
  EVT_ENTER,
  EVT_BACK
};

enum MenuItemType : uint8_t 
{
  MENU_SUBMENU = 0,
  MENU_ENUM_SUB,
  MENU_VALUE_TOGGLE,
  MENU_ACTION,
  MENU_SETTING_OP,
  MENU_LABEL
};

enum SettingOp : uint8_t 
{
  OP_NONE = 0,
  OP_PRESET,     // apply preset index
  OP_ENTER_EDITOR
};

struct MenuItemDesc
{
  const char *label;   // PROGMEM
  MenuItemType type;
  uint8_t target;      // pageId OR actionId OR settingId
  uint8_t valueId;     // SettingId for inline display (0 if none)
  uint8_t param;       // NEW: preset index / toggle value / unused
};


struct MenuPageDesc {
  const char *title;   // PROGMEM
  uint8_t firstItem;
  uint8_t itemCount;
};
