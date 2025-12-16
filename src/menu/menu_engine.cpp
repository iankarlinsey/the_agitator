#include "menu_engine.hpp"
#include <avr/pgmspace.h>
#include <string.h>

MenuEngine::MenuEngine()
  : page(PAGE_MAIN), cursorIndex(0), m_scrollOffset(0) {}


void MenuEngine::handleEvent(MenuEvent e) {
  MenuPageDesc pg;
  memcpy_P(&pg, &MENU_PAGES[page], sizeof(pg));

  switch (e) {
    case EVT_UP:
      if (cursorIndex > 0) cursorIndex--;
      break;

    case EVT_DOWN:
      if (cursorIndex + 1 < pg.itemCount) cursorIndex++;
      break;

    case EVT_ENTER:
      enterItem();
      break;

    case EVT_BACK:
      goBack();
      break;

    default:
      break;
  }

  const uint8_t rows = MENU_VISIBLE_ROWS;  // define once (e.g. 6)

  if (cursorIndex < m_scrollOffset) {
    m_scrollOffset = cursorIndex;
  }
  else if (cursorIndex >= m_scrollOffset + rows) {
    m_scrollOffset = cursorIndex - rows + 1;
  }
}

void MenuEngine::enterItem() {
  MenuPageDesc pg;
  memcpy_P(&pg, &MENU_PAGES[page], sizeof(pg));

  MenuItemDesc item;
  memcpy_P(&item,
           &MENU_ITEMS[pg.firstItem + cursorIndex],
           sizeof(item));

  switch (item.type) 
  {
    case MENU_SUBMENU:
    case MENU_ENUM_SUB:
    page = (MenuPageId)item.target;
    cursorIndex = 0;
    break;

    case MENU_ACTION:
      menuRunAction((ActionId)item.target);
    break;

    case MENU_LABEL:
    default:
      break;
  }
}

void MenuEngine::goBack() 
{
  if (page != PAGE_MAIN) {
    page = PAGE_MAIN;
    cursorIndex = 0;
  }
}

const MenuItemDesc* MenuEngine::currentItem() const
{
  MenuPageDesc pg;
  memcpy_P(&pg, &MENU_PAGES[page], sizeof(pg));

  return &MENU_ITEMS[pg.firstItem + cursorIndex];
}

void MenuEngine::setPage(MenuPageId p)
{
  page = p;
  cursorIndex = 0;
}

void MenuEngine::setCursor(uint8_t c)
{
  cursorIndex = c;
}

void MenuEngine::getCurrentItem(MenuItemDesc &out) const
{
  MenuPageDesc pg;
  memcpy_P(&pg, &MENU_PAGES[page], sizeof(pg));

  memcpy_P(&out,
           &MENU_ITEMS[pg.firstItem + cursorIndex],
           sizeof(out));
}
