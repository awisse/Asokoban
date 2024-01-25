// Drawing/display functions
#define WHITE 1
#define BLACK 0
#define INVERT 2
#define WIDTH 128
#define HEIGHT 64
#define TILE_SZ 8

#include <stdint.h>

// Arduboy Functions
void DrawBitmap(const uint8_t* bmp, int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour);
void FillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour);

// Local Functions
void Clear();
void EraseTile(int16_t x, int16_t y);
void Draw();