#pragma once
#include <Arduino.h>
#include "menu_config.hpp"
#include "menu_defs.hpp"

#define MENU_VISIBLE_ROWS 4

void menuRunAction(ActionId id);

class MenuEngine 
{
  public:
    MenuEngine();

    void handleEvent(MenuEvent e);
    MenuPageId currentPage() const { return page; }
    uint8_t cursor() const { return cursorIndex; }
    void getCurrentItem(MenuItemDesc &out) const;

    const MenuItemDesc* currentItem() const;
    void setPage(MenuPageId p);
    void setCursor(uint8_t c);
    uint8_t scroll() const { return m_scrollOffset; }

  private:
    MenuPageId page;
    uint8_t cursorIndex;
    uint8_t m_scrollOffset;

    void enterItem();
    void goBack();
};
