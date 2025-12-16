#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

/*
  DisplayGME12864
  --------------
  UI/layout adapter for the GME12864-13 module with:
  - Yellow title band (top region)
  - Blue body region (below title)
  Constrains drawing to those regions so menu code never touches pixels directly.
*/

class DisplayGME12864 {
public:
  // ---- Physical layout (tweak if your module differs) ----
  static constexpr uint8_t WIDTH   = 126;
  static constexpr uint8_t HEIGHT  = 64;

  // Title band (yellow) height in pixels
  static constexpr uint8_t TITLE_H = 16;

  // Body region (blue) starts at TITLE_H
  static constexpr uint8_t BODY_Y  = TITLE_H;
  static constexpr uint8_t BODY_H  = HEIGHT - TITLE_H;

  // Row metrics in body region (tune fonts/spacing here)
  static constexpr uint8_t ROW_H   = 10;   // pixels per row
  static constexpr uint8_t ROW_PAD_X = 2;  // left padding

  // Right-side affordance glyph for "opens submenu"
  static constexpr char SUBMENU_GLYPH = '>';

  explicit DisplayGME12864(U8G2 &u8g2);
  U8G2& u8g2();

  void begin();

  // Frame lifecycle (full-buffer U8g2): draw everything between these calls
  void beginFrame();   // clears buffer
  void endFrame();     // sends buffer

  // Title in yellow band (constrained to [0..TITLE_H))
  void drawTitle(const char *title);

  // Draw a body row (0-based index within visible body rows)
  // - label: left text
  // - value: optional (may be nullptr)
  // - selected: highlight the row
  // - showSubmenuGlyph: if true, draws ">" aligned to the right edge
  void drawRow(uint8_t rowIndex,
               const char *label,
               const char *value,
               bool selected,
               bool showSubmenuGlyph);

  // Convenience: returns how many rows fit in blue body area with ROW_H
  uint8_t visibleRows() const;

  // Optional: clear only the body region (keeps title area)
  void clearBody();

private:
  U8G2 &d;

  // Fonts (override by editing these constants or swapping in your own)
  static constexpr const uint8_t *TITLE_FONT = u8g2_font_ncenB08_tr;
  static constexpr const uint8_t *BODY_FONT  = u8g2_font_6x10_tr;

  // Internal helpers
  uint8_t rowTopY(uint8_t rowIndex) const;
  uint8_t rowBaselineY(uint8_t rowIndex) const;
  void drawInvertedRowBackground(uint8_t yTop);
};
