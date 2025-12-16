#include "menu_ui.hpp"
#include "menu_engine.hpp"
#include "menu_render.hpp"
#include "menu_settings.hpp"
#include "drivers/display_gme12864.hpp"

extern MenuEngine   menu;
extern MenuRenderer renderer;

MenuUI::MenuUI()
  : mode(UI_MENU),
    editingSetting(SET_NONE),
    navTop(0)
{}

void MenuUI::pushNav()
{
  if (navTop < NAV_DEPTH) {
    navPage[navTop]   = menu.currentPage();
    navCursor[navTop] = menu.cursor();
    navTop++;
  }
}

void MenuUI::popNav()
{
  if (navTop > 0) {
    navTop--;
    menu.setPage(navPage[navTop]);
    menu.setCursor(navCursor[navTop]);
  }
}

static uint16_t pow10_u16(uint8_t n)
{
  static const uint16_t p[] = { 1, 10, 100, 1000 };
  return (n < 4) ? p[n] : 1;
}

static void timerApplyDigits(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint16_t &sec)
{
  uint8_t mm = d0 * 10 + d1;
  uint8_t ss = d2 * 10 + d3;
  sec = (uint16_t)mm * 60u + (uint16_t)ss;
}

static void timerGetDigits(uint16_t sec, uint8_t &d0, uint8_t &d1, uint8_t &d2, uint8_t &d3)
{
  uint8_t mm = sec / 60;
  uint8_t ss = sec % 60;
  d0 = mm / 10; d1 = mm % 10;
  d2 = ss / 10; d3 = ss % 10;
}

static void timerIncrementDigit(uint8_t digit, uint16_t &sec)
{
  uint8_t d0, d1, d2, d3;
  timerGetDigits(sec, d0, d1, d2, d3);

  uint8_t *d = (digit == 0) ? &d0 :
               (digit == 1) ? &d1 :
               (digit == 2) ? &d2 : &d3;

  *d = (*d + 1) % 10;
  timerApplyDigits(d0, d1, d2, d3, sec);
}

static void timerDecrementDigit(uint8_t digit, uint16_t &sec)
{
  uint8_t d0, d1, d2, d3;
  timerGetDigits(sec, d0, d1, d2, d3);

  uint8_t *d = (digit == 0) ? &d0 :
               (digit == 1) ? &d1 :
               (digit == 2) ? &d2 : &d3;

  *d = (*d + 9) % 10;
  timerApplyDigits(d0, d1, d2, d3, sec);
}

void MenuUI::handleEvent(MenuEvent e)
{
  if (mode == UI_EDIT_TIMER) {
    uint16_t &sec = cfg.timerSeconds;

    uint8_t mm = sec / 60;
    uint8_t ss = sec % 60;

    uint8_t digits[4] = {
      mm / 10, mm % 10,
      ss / 10, ss % 10
    };

    switch (e) {
      case EVT_UP:
        timerIncrementDigit(timerDigit, sec);
        break;

      case EVT_DOWN:
        timerDecrementDigit(timerDigit, sec);
        break;

      case EVT_ENTER:   // RIGHT
        if (timerDigit < 3) timerDigit++;
        break;

      case EVT_BACK:    // LEFT
        if (timerDigit > 0) 
        {
          timerDigit--;
        } 
        else 
        {
          // leftmost → apply + exit
          mode = UI_MENU;
        }
        break;

      default:
        break;
    }

    return;
  }

  // BACK always pops if possible
  if (e == EVT_BACK) {
    if (editingSetting != SET_NONE) {
      editingSetting = SET_NONE;
      popNav();
      return;
    }
    popNav();
    return;
  }

  if (e == EVT_ENTER) {
    MenuItemDesc item;
    menu.getCurrentItem(item);

    if (item.type == MENU_SUBMENU || item.type == MENU_ENUM_SUB) {
      pushNav();
    }

    if (item.type == MENU_ENUM_SUB) {
      editingSetting = (SettingId)item.valueId;
      menu.setPage((MenuPageId)item.target);
      menu.setCursor(menuGetSettingValue(editingSetting));
      return;
    }

    if (item.type == MENU_SETTING_OP) {
      applySettingOp(item);
      popNav();
      return;
    }
  }

  menu.handleEvent(e);
}

void MenuUI::applySettingOp(const MenuItemDesc &item)
{
  // 1) Editor entry
  if ((SettingOp)item.valueId == OP_ENTER_EDITOR) {
    mode = UI_EDIT_TIMER;
    timerDigit = 0;
    return;
  }

  // 2) Preset apply
  const SettingDefinition &sd = SETTING_DEFINITIONS[item.target];
  const SettingPreset *presets = (const SettingPreset *)sd.data;

  SettingPreset p;
  memcpy_P(&p, &presets[item.param], sizeof(p));

  switch (sd.type) {
    case SETTYPE_TIME:
    case SETTYPE_UINT16:
      *(uint16_t*)sd.storage = p.raw;
      break;

    case SETTYPE_UINT8:
    case SETTYPE_ENUM:
      *(uint8_t*)sd.storage = (uint8_t)p.raw;
      break;

    default:
      break;
  }

  editingSetting = SET_NONE;
}


void MenuUI::draw()
{
  if (mode == UI_EDIT_TIMER) {
    renderer.drawTimerEditor(timerDigit, cfg.timerSeconds);
    return;
  }

  renderer.draw(menu);
}
