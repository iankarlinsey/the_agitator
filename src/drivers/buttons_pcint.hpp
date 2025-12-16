#pragma once
#include <Arduino.h>

/*
  ButtonsPCINT (compile-time mapped)
  ---------------------------------
  - 4 buttons, PCINT only
  - Compile-time pin mapping
  - ISR latches events into 1 byte
  - No debounce, no hold semantics
*/

/* ===== Compile-time pin mapping =====
   These MUST be PCINT-capable pins
*/

#define BTN0_PIN  A0   // UP
#define BTN1_PIN  A3   // DOWN
#define BTN2_PIN  A2   // ENTER (RIGHT)
#define BTN3_PIN  A1   // BACK  (LEFT)

class ButtonsPCINT {
public:
  ButtonsPCINT();

  void begin();

  // Atomically snapshot and clear latched button events
  uint8_t snapshotAndClear();

  void clearAll();

  // Called from PCINT ISRs
  static void handlePCINT();

private:
  static volatile uint8_t pendingBits;

  static void enablePCINT(uint8_t pin);
};
