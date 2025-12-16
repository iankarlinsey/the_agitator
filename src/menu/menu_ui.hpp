#pragma once

#include "menu_defs.hpp"
#include "menu_config.hpp"

// menu_ui.hpp

class MenuUI {
public:
  MenuUI();
  void handleEvent(MenuEvent e);
  void draw();

private:
  enum UiMode : uint8_t {
    UI_MENU,
    UI_EDIT_TIMER
  };

  UiMode mode;
  SettingId editingSetting;

  static constexpr uint8_t NAV_DEPTH = 6;
  MenuPageId navPage[NAV_DEPTH];
  uint8_t    navCursor[NAV_DEPTH];
  uint8_t    navTop;
  uint8_t timerDigit;

  void pushNav();
  void popNav();
  void applySettingOp(const MenuItemDesc &item);
};
