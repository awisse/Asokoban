#include "defines.h"
#include "globals.h"
#include "draw.h"
#include "platform.h"
#include "sprites.h"

const uint16_t sprite_ix[] = {
  0, 0x20, 0x30, 0xB0, 0x10, 0x08, 0x18, 0};

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

void EraseTile(int16_t x, int16_t y) {
  Platform::DrawFilledRect(x, y, TILE_SZ, TILE_SZ, COLOUR_BLACK);
}

void Draw(Piece board[HDIM][VDIM], Player worker) {
  Platform::Clear();
  DrawBoard(board, worker);

}

// vim:fdm=syntax
