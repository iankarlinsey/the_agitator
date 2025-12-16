#include "drivers/buttons_pcint.hpp"

// ===== Static storage =====
volatile uint8_t ButtonsPCINT::pendingBits = 0;

ButtonsPCINT::ButtonsPCINT() {
  // nothing to do
}

void ButtonsPCINT::begin() {
  pinMode(BTN0_PIN, INPUT_PULLUP);
  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(BTN2_PIN, INPUT_PULLUP);
  pinMode(BTN3_PIN, INPUT_PULLUP);

  enablePCINT(BTN0_PIN);
  enablePCINT(BTN1_PIN);
  enablePCINT(BTN2_PIN);
  enablePCINT(BTN3_PIN);

  pendingBits = 0;
}

uint8_t ButtonsPCINT::snapshotAndClear() {
  uint8_t snapshot;
  noInterrupts();
  snapshot = pendingBits;
  pendingBits = 0;
  interrupts();
  return snapshot;
}

void ButtonsPCINT::clearAll() {
  noInterrupts();
  pendingBits = 0;
  interrupts();
}

void ButtonsPCINT::handlePCINT() {
  // LOW = pressed (INPUT_PULLUP)
  if (digitalRead(BTN0_PIN) == LOW) pendingBits |= (1 << 0);
  if (digitalRead(BTN1_PIN) == LOW) pendingBits |= (1 << 1);
  if (digitalRead(BTN2_PIN) == LOW) pendingBits |= (1 << 2);
  if (digitalRead(BTN3_PIN) == LOW) pendingBits |= (1 << 3);
}

void ButtonsPCINT::enablePCINT(uint8_t pin) {
  volatile uint8_t *pcmsk = digitalPinToPCMSK(pin);
  uint8_t pcicrBit = digitalPinToPCICRbit(pin);
  uint8_t pcmskBit = digitalPinToPCMSKbit(pin);

  if (!pcmsk) return; // not PCINT-capable

  *pcmsk |= _BV(pcmskBit);
  PCICR |= _BV(pcicrBit);
}


// ===== PCINT vectors =====
ISR(PCINT0_vect) { ButtonsPCINT::handlePCINT(); }
ISR(PCINT1_vect) { ButtonsPCINT::handlePCINT(); }
ISR(PCINT2_vect) { ButtonsPCINT::handlePCINT(); }
