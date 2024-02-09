#include "defines.h"
/* #include "globals.h" */
#include "draw.h"
#include "platform.h"
#include "font.h"
#include "fmt.h"
#include "sprites.h"

Font font;
uint16_t displayed_lvl = 1; // Level displayed in upper left corner

void Draw1MenuItem(uint8_t x, uint8_t y, uint16_t level, uint16_t result,
    bool selected);
void DrawDashedRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h,
    uint8_t dashlen);
void DrawMenuStars(uint8_t x, uint8_t y, uint16_t seconds);

uint8_t len(const uint8_t* text) {
  // Compute length of utf-8 string
  uint8_t length=0;

  while (*text++) {
    if ((*text & 0xC0) != 0xC0)
      length++;
  }
  return length;
}

void DrawBoard(Piece board[HDIM][VDIM], Player worker) {
  uint8_t row, column;
  uint16_t ix;
  Piece tile;

  Platform::Clear();
  for (column = 0; column < HDIM; column++)
    for (row = 0; row < VDIM; row++) {
      tile = board[column][row];
      ix = sprite_ix[tile];
      switch (tile) {
        case Worker:
          ix += (uint16_t)worker.direction * 0x20;
          break;
        case WorkerOnTarget:
          ix += (uint16_t)worker.direction * 8;
          break;
        default:
          {}
      }
      Platform::DrawBitmap(&sprites[ix],
        column * TILE_SZ, row * TILE_SZ, TILE_SZ, TILE_SZ, COLOUR_WHITE);
    }
}

void DrawMenu(uint16_t level, uint16_t* results) {
  /* Levels are displayed in blocks of eight, in two rows of four.
   * When selecting down and the current selection is in the second row,
   * the next four levels are scrolling in from the bottom.
   * When selecting up and the current selection is in the first row,
   * the previous four levels are scrolling in from the top. */
  uint16_t i, result, draw_lvl;
  Platform::Clear();

  // Compute levels to display as a function of `displayed_lvl` and `level`.
  if (level < displayed_lvl) { // Scroll up
    displayed_lvl -= 4;
  } else if (level >= displayed_lvl + 8) { // Scroll down
    displayed_lvl += 4;
  }

  // Display the 8 squares
  for (i = 0; i < 8; i++) {
    draw_lvl = displayed_lvl + i;
    result = results[draw_lvl - 1];
    Draw1MenuItem((i & 3) * 32, (i >> 2) * 32, draw_lvl, result, draw_lvl==level);
  }
}

void Draw1MenuItem(uint8_t x, uint8_t y, uint16_t level, uint16_t result, bool selected) {
  uint8_t level_digits = 1;
  uint8_t tm_str[6];

  if (selected) {
    DrawDashedRect(x, y, 32, 32, 3);
  } else {
    Platform::DrawRect(x, y, 32, 32);
  }
  if (result > 0) {
    DrawMenuStars(x + 3, y + 5, result);
  }
  if (level > 9) {
    level_digits++;
  }
  if (level > 99) {
    level_digits++;
  }

  font.PrintInt(level, x + (32 - level_digits * FONT_WIDTH) / 2, y + 13);
  if (result > 0) {
    FmtMMSS(result, tm_str, false);
    uint8_t tm_offset = result < 600 ? 9 : 4;
    font.PrintString(tm_str, x + tm_offset, y + 22);
  }
}

void DrawStars(uint8_t set) {
  /* Draw four stars at the top of the screen.
   * the 4 lower order bits of set determine whether
   * the star is filled (1) or empty (0).
   * The lowest order bit is the left star.*/
  uint8_t i;
  for (i=0; i<4; i++) {
    Platform::DrawBitmap(sprites + STAR_IX +
        2 * ((set >> i) & 1) * STAR_SZ,
        0x14 + 0x18 * i, 8, STAR_SZ, STAR_SZ, COLOUR_WHITE);
  }
}

void DrawResult(const uint8_t* text, const uint8_t row, const uint16_t level, const uint16_t moves, const uint16_t elapsed) {
  /* Draw a box in the middle of the screen with :
     Text on top
     Pas: xxx
     Temps: xxx
  */
  uint8_t x, y, w, h;
  uint8_t time[12];

  if (row > 7) {
    return; // Nothing to draw. Off screen.
  }

  FmtTime(elapsed, time);

  w = 5 * len(text);

  // Text x-position
  x = (DISPLAY_WIDTH - w) / 2;

  // Make room on screen
  y = row ? row * FONT_HEIGHT : 0;
  h = row > 3 ? DISPLAY_HEIGHT - row * FONT_HEIGHT : 4 * FONT_HEIGHT;
  Platform::DrawFilledRect(x, y - 1, w, h, COLOUR_BLACK);

  // Draw Text
  font.PrintString(text, x, y);

  // Draw Result
  y += FONT_HEIGHT;
  font.PrintString(U8"Niveau:", x, y);
  font.PrintInt(level, x + 8 * FONT_WIDTH, y);
  y += 8;
  font.PrintString(U8"Pas:", x, y);
  font.PrintInt(moves, x + 8 * FONT_WIDTH, y);
  y += 8;
  font.PrintString(U8"Temps:", x, y);
  font.PrintString(time, x + 8 * FONT_WIDTH, y);
}

void DrawDashedHLine(uint8_t x, uint8_t y, uint8_t w, uint8_t dashlen) {

  uint8_t len = 0;

  while (len + dashlen < w) {
    Platform::DrawLine(x + len, y, x + len + dashlen - 1, y, COLOUR_WHITE);
    len += 2 * dashlen;
  }
  if (len < w) {
    Platform::DrawLine(x + len, y, x + w, y, COLOUR_WHITE);
  }
}

void DrawDashedVLine(uint8_t x, uint8_t y, uint8_t h, uint8_t dashlen) {

  uint8_t len = 0;

  while (len + dashlen < h) {
    Platform::DrawLine(x, y + len, x, y + len + dashlen - 1, COLOUR_WHITE);
    len += 2 * dashlen;
  }
  if (len < h) {
    Platform::DrawLine(x, y + len, x, y + h, COLOUR_WHITE);
  }
}

void DrawDashedRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t dashlen) {

  DrawDashedHLine(x, y, w, dashlen);
  DrawDashedHLine(x, y + 1, w, dashlen);
  DrawDashedHLine(x, y + h - 1, w, dashlen);
  DrawDashedHLine(x, y + h - 2, w, dashlen);
  DrawDashedVLine(x, y, h, dashlen);
  DrawDashedVLine(x + 1, y, h, dashlen);
  DrawDashedVLine(x + w - 1, y, h, dashlen);
  DrawDashedVLine(x + w - 2, y, h, dashlen);
}

void DrawMenuStars(uint8_t x, uint8_t y, uint16_t seconds) {

  uint8_t i;

  for (i=0; i < 4; i++) {
    if (seconds < (4 - i) * STAR_STEP) {
      Platform::DrawFilledCircle(x + 3 + 6 * i, y + 2, 2, COLOUR_WHITE);
    } else {
      Platform::DrawCircle(x + 3 + 6 * i, y + 2, 2, COLOUR_WHITE);
    }
  }
}

// vim:fdm=syntax
