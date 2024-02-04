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

void DrawResult(const uint8_t* text, const uint16_t level,
    const uint16_t moves, const unsigned long elapsed) {
  /* Draw a box in the middle of the screen with :
     Text on top
     Pas: xxx   Temps: xxx
  */
  uint8_t x, w;

  w = 5 * len(text);

  // Text x-position
  x = (DISPLAY_WIDTH - w) / 2;

  // Draw Text
  font.PrintString(text, 4, x);

  // Draw Result
  font.PrintString(U8"Pas: ", 5, x);
  font.PrintInt(moves, 5, x + 25);

#ifdef _DEBUG
  Platform::DebugPrint(level);
  Platform::DebugPrint(U8" Level");
  Platform::DebugPrint((float)(elapsed/1000.0));
  Platform::DebugPrint(U8" Seconds");
  Platform::DebugPrint(moves);
  Platform::DebugPrint(U8" Moves");
  Platform::DebugPrint((uint16_t)w);
  Platform::DebugPrint(U8" Text Width");
#endif
}

// vim:fdm=syntax
