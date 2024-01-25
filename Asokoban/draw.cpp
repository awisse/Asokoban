#include "draw.h"

void Clear() {
  FillRect(0, 0, WIDTH, HEIGHT, BLACK);
}
void EraseTile(int16_t x, int16_t y) {
  FillRect(x, y, TILE_SZ, TILE_SZ, BLACK);
}

void Draw() {

}