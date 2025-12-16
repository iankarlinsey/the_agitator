#include "menu_render.hpp"
#include "menu_settings.hpp"
#include <avr/pgmspace.h>

MenuRenderer::MenuRenderer(DisplayGME12864 &d)
  : disp(d) {}



  
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

void MenuRenderer::drawTimerEditor(uint8_t digit, uint16_t sec)
{
  disp.beginFrame();

  // Clear title + body
  disp.drawTitle("Set Timer");
  disp.clearBody();

  uint8_t mm = sec / 60;
  uint8_t ss = sec % 60;

  char buf[6];
  snprintf(buf, sizeof(buf), "%02u:%02u", mm, ss);

  // Draw centered text manually
  U8G2 &d = disp.u8g2();

  d.setFont(u8g2_font_6x10_tr);

  uint8_t textW = d.getStrWidth(buf);
  uint8_t x = (DisplayGME12864::WIDTH - textW) / 2;
  uint8_t y = DisplayGME12864::BODY_Y + DisplayGME12864::BODY_H / 2 + 4;

  d.drawStr(x, y, buf);

  // Underline selected digit
  uint8_t digitX = x;
  uint8_t underlineW = 0;
  uint8_t digitCount = 0;
  for (uint8_t i = 0; buf[i] != '\0'; i++)
  {
    if (buf[i] == ':')
    {
      continue;
    }

    if (digitCount == digit)
    {
      char saved = buf[i];
      buf[i] = '\0';
      digitX = x + d.getStrWidth(buf);
      buf[i] = saved;

      char tmp[2] = { saved, '\0' };
      underlineW = d.getStrWidth(tmp);
      break;
    }

    digitCount++;
  }
  d.drawHLine(digitX, y + 2, underlineW);

  disp.endFrame();
}

