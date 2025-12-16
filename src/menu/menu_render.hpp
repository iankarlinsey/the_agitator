#pragma once
#include <Arduino.h>
#include "menu_engine.hpp"
#include "drivers/display_gme12864.hpp"

class MenuRenderer 
{
  public:
    explicit MenuRenderer(DisplayGME12864 &d);

    void draw(const MenuEngine &engine);
    void drawTimerEditor(uint8_t digit, uint16_t seconds);

  private:
    DisplayGME12864 &disp;

    void drawPage(const MenuEngine &engine);
    
};
