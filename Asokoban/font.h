#pragma once

#include <stdint.h>
#include "defines.h"
#include "font4x6.h"

#define FONT_WIDTH 4
#define FONT_HEIGHT 6

class Font
{
public:
	static constexpr int glyphWidth = 5;

	static void PrintString(const uint8_t* str, uint8_t line,
      uint8_t x, uint8_t colour = COLOUR_WHITE);
	static void PrintInt(uint16_t value, uint8_t line,
      uint8_t x, uint8_t xorMask = COLOUR_WHITE);

private:
  static uint16_t CharIdx(const uint8_t c);
	static void DrawChar(uint8_t* screenPtr, uint8_t c, uint8_t xorMask);
};
// vim:ft=cpp
