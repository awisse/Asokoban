#pragma once

#include <stdint.h>
#include "defines.h"

class Platform
{
public:
	static uint8_t ButtonState();
  // Drawing
  static void PutPixel(uint8_t x, uint8_t y, uint8_t colour);
  static void DrawBitmap(const uint8_t* bitmap, int16_t x, int16_t y,
                  uint8_t w, uint8_t h, uint8_t colour);
  static void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t colour);
  static void DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h);
  static void DrawFilledRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour);
  static void DrawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t colour);
  static void FillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t colour);
  static void FillScreen(uint8_t colour);
  static void Clear();
  // Timer
  static unsigned long Millis();

  // EEPROM
  static uint8_t ToEEPROM(uint8_t *bytes, int offset, int length);
  static uint8_t FromEEPROM(uint8_t *bytes, int offset, int length);
	/* static void PlaySound(const uint16_t* audioPattern); */
	/* static bool IsAudioEnabled(); */
	/* static void SetAudioEnabled(bool isEnabled); */

	/* static void ExpectLoadDelay(); */

  // Debug
#ifdef _DEBUG
  static void DebugPrint(uint16_t value);
  static void DebugPrint(char* text);
#endif
	
};
// vim:ft=cpp
