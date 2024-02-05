#include "defines.h"
#include "font.h"
#include "globals.h"
#include "draw.h"
#include "platform.h"
#include "font.h"
#include "sprites.h"

Font font;

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
/* #ifdef 0 */
/*       Platform::DebugPrint(ix); */
/* #endif */
      Platform::DrawBitmap(&sprites[ix],
        column * TILE_SZ, row * TILE_SZ, TILE_SZ, TILE_SZ, COLOUR_WHITE);
    }
}

void Draw(Piece board[HDIM][VDIM], Player worker) {
  // Can potentially optimize by drawing only changed  parts.
  Platform::Clear();
  DrawBoard(board, worker);
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

void DrawResult(const uint8_t* text, const uint8_t row,
    const uint16_t level, const uint16_t moves,
    const unsigned long elapsed) {
  /* Draw a box in the middle of the screen with :
     Text on top
     Pas: xxx   Temps: xxx
  */
  uint8_t x, y, w, h;
  uint8_t time[12];

  if (row > 7) {
    return; // Nothing to draw. Off screen.
  }

  Platform::FmtTime(elapsed, time);

  w = 5 * len(text);

  // Text x-position
  x = (DISPLAY_WIDTH - w) / 2;


  // Make room on screen
  y = row ? row * 8 - 1 : 0;
  h = row > 3 ? DISPLAY_HEIGHT - row * 8 : 32;
  Platform::DrawFilledRect(x - 1, y, w + 2, h, COLOUR_BLACK);

  // Draw Text
  font.PrintString(text, row, x);

  // Draw Result
  font.PrintString(U8"Niveau:", row + 1, x);
  font.PrintInt(level, row + 1, x + 8 * font.glyphWidth);
  font.PrintString(U8"Pas:", row + 2, x);
  font.PrintInt(moves, row + 2, x + 8 * font.glyphWidth);
  font.PrintString(U8"Temps:", row + 3, x);
  font.PrintString(time, row + 3, x + 8 * font.glyphWidth);

}

// vim:fdm=syntax
