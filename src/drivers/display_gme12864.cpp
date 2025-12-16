#include "display_gme12864.hpp"

DisplayGME12864::DisplayGME12864(U8G2 &u8g2)
  : d(u8g2) {}

void DisplayGME12864::begin() {
  d.begin();
}

void DisplayGME12864::beginFrame() {
  d.clearBuffer();
}

void DisplayGME12864::endFrame() {
  d.sendBuffer();
}

uint8_t DisplayGME12864::visibleRows() const {
  return BODY_H / ROW_H;
}

uint8_t DisplayGME12864::rowTopY(uint8_t rowIndex) const {
  return BODY_Y + (rowIndex * ROW_H);
}

uint8_t DisplayGME12864::rowBaselineY(uint8_t rowIndex) const {
  // Baseline near bottom of the row; tune if you change BODY_FONT
  return rowTopY(rowIndex) + (ROW_H - 2);
}

U8G2& DisplayGME12864::u8g2()
{
  return d;
}

void DisplayGME12864::drawInvertedRowBackground(uint8_t yTop) {
  // Invert the whole row area in the blue region
  d.setDrawColor(1);
  d.drawBox(0, yTop, WIDTH, ROW_H);
  d.setDrawColor(0); // text will be drawn in "cleared" color (inverted look)
}

void DisplayGME12864::drawTitle(const char *title) {
  // Clear title band
  d.setDrawColor(0);
  d.drawBox(0, 0, WIDTH, TITLE_H);

  // Draw title text within title band
  d.setDrawColor(1);
  d.setFont(TITLE_FONT);

  // Baseline inside title band
  const uint8_t baselineY = TITLE_H - 3;
  d.drawStr(ROW_PAD_X, baselineY, title);
}

void DisplayGME12864::clearBody() {
  d.setDrawColor(0);
  d.drawBox(0, BODY_Y, WIDTH, BODY_H);
  d.setDrawColor(1);
}

void DisplayGME12864::drawRow(uint8_t rowIndex,
                              const char *label,
                              const char *value,
                              bool selected,
                              bool showSubmenuGlyph) {
  if (rowIndex >= visibleRows()) return;

  const uint8_t yTop = rowTopY(rowIndex);
  const uint8_t yBase = rowBaselineY(rowIndex);

  // Clear row area first (in blue region)
  d.setDrawColor(0);
  d.drawBox(0, yTop, WIDTH, ROW_H);

  d.setFont(BODY_FONT);

  if (selected) {
    drawInvertedRowBackground(yTop);
  } else {
    d.setDrawColor(1);
  }

  // Left label
  d.drawStr(ROW_PAD_X, yBase, label ? label : "");

  // Optional value (render after label, simple spacing)
  if (value && value[0] != '\0') {
    // A simple, low-cost layout: draw value starting at mid-screen.
    // (If you want tight packing, we can add a tiny fixed column system.)
    const uint8_t valueX = 72;
    d.drawStr(valueX, yBase, value);
  }

  // Submenu affordance glyph at far right
  if (showSubmenuGlyph) {
    char glyph[2] = { SUBMENU_GLYPH, '\0' };

    // Right align roughly: WIDTH - (glyphWidth + padding)
    // U8g2 gives string width; avoids guessing per font.
    const uint8_t gw = d.getStrWidth(glyph);
    const uint8_t gx = (WIDTH > (gw + ROW_PAD_X)) ? (WIDTH - gw - ROW_PAD_X) : 0;
    d.drawStr(gx, yBase, glyph);
  }

  // If selected, restore draw color for next operations
  d.setDrawColor(1);
}
