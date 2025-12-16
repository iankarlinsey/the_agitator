#include "menu_render.hpp"
#include "menu_settings.hpp"
#include <avr/pgmspace.h>

MenuRenderer::MenuRenderer(DisplayGME12864 &d)
  : disp(d) {}


static uint8_t digitToScreenPos(uint8_t d)
{
  // 00:00
  // 01234
  static const uint8_t map[4] = { 0, 1, 3, 4 };
  return map[d];
}

void MenuRenderer::draw(const MenuEngine &engine) {
  disp.beginFrame();
  drawPage(engine);

  disp.endFrame();
}

void MenuRenderer::drawPage(const MenuEngine &engine)
{
  MenuPageId page = engine.currentPage();
  uint8_t cursor  = engine.cursor();
  uint8_t scroll  = engine.scroll();   // <-- now valid

  MenuPageDesc pg;
  memcpy_P(&pg, &MENU_PAGES[page], sizeof(pg));

  char title[16];
  strcpy_P(title, pg.title);
  disp.drawTitle(title);

  const uint8_t rows = disp.visibleRows();

  for (uint8_t row = 0;
       row < rows && (row + scroll) < pg.itemCount;
       row++)
  {
    uint8_t itemIndex = pg.firstItem + scroll + row;

    MenuItemDesc item;
    memcpy_P(&item, &MENU_ITEMS[itemIndex], sizeof(item));

    char label[16];
    strcpy_P(label, item.label);

    bool selected = ((scroll + row) == cursor);
    bool hasSub   = (item.type == MENU_SUBMENU ||
                     item.type == MENU_ENUM_SUB);

    const char *value = nullptr;
    if (item.valueId != SET_NONE) 
    {
      value = menuGetSettingValueString((SettingId)item.valueId);
    }

    disp.drawRow(row, label, value, selected, hasSub);
  }
}

void MenuRenderer::drawTimerEditor(uint8_t digit, uint16_t seconds)
{
  disp.beginFrame();
  disp.clearBody();

  char buf[6];
  uint8_t mm = seconds / 60;
  uint8_t ss = seconds % 60;
  snprintf(buf, sizeof(buf), "%02u:%02u", mm, ss);

  // draw centered text
  disp.d.setFont(u8g2_font_6x10_tr);
  uint8_t w = disp.d.getStrWidth(buf);
  uint8_t x = (DisplayGME12864::WIDTH - w) / 2;
  uint8_t y = DisplayGME12864::BODY_Y + 24;

  disp.d.drawStr(x, y, buf);

  // underline selected digit (mapped)
  uint8_t screenPos = digitToScreenPos(digit);
  uint8_t ux = x + screenPos * 6;   // 6px per char for this font
  disp.d.drawHLine(ux, y + 2, 6);

  disp.endFrame();
}

