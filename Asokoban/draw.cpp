#include "defines.h"
#include "globals.h"
#include "draw.h"
#include "platform.h"
#include "sprites.h"

const uint16_t sprite_ix[] PROGMEM = {
  0, 0x20, 0x30, 0x50, 0x10, 0x08, 0x18, 0};

void DrawBoard(Piece board[HDIM][VDIM], Player worker) {
  uint8_t row, column;
  uint16_t ix;
  Piece tile;

  for (column = 0; column < HDIM; column++)
    for (row = 0; row < VDIM; row++) {
      tile = board[column][row];
      switch (tile) {
        case Worker:
        case WorkerOnTarget:
          ix = sprite_ix[tile] + (uint16_t)worker.direction * 8;
          break;
        default:
          ix = sprite_ix[tile];
      }
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
