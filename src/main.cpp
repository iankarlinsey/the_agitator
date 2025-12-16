#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#include "drivers/buttons_pcint.hpp"
#include "drivers/display_gme12864.hpp"

#include "menu/menu_defs.hpp"
#include "menu/menu_config.hpp"
#include "menu/menu_engine.hpp"
#include "menu/menu_render.hpp"
#include "menu/menu_ui.hpp"


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
DisplayGME12864 display(u8g2);
ButtonsPCINT buttons;
MenuEngine menu;
MenuRenderer renderer(display);
MachineConfig cfg = DEFAULT_CFG;
MenuUI ui;

void menuRunAction(ActionId id)
{
  switch (id)
  {
    case ACTION_RUN:
      // TODO: start timer + motor
      break;

    default:
      // TEMP: ignore all other actions for now
      break;
  }
}

void setup() {
  display.begin();
  buttons.begin();
  sei();
  renderer.draw(menu);
}

void loop() {
  uint8_t bits = buttons.snapshotAndClear();
  if (!bits) return;

  if (bits & (1 << 0)) ui.handleEvent(EVT_UP);     // BTN0
  if (bits & (1 << 1)) ui.handleEvent(EVT_DOWN);   // BTN1
  if (bits & (1 << 2)) ui.handleEvent(EVT_ENTER);  // BTN2 (RIGHT)
  if (bits & (1 << 3)) ui.handleEvent(EVT_BACK);   // BTN3 (LEFT)

  ui.draw();
}

