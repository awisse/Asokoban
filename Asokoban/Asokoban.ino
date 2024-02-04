#include <Arduboy2.h>
#include "game.h"
#include "controller.h"
#include "defines.h"
#include "font.h"
#include "platform.h"

Arduboy2Base arduboy;
int counter;

void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(20);

#ifdef _DEBUG
  Serial.begin(9600);
  counter = 0;
#endif

  InitGame();

}

void loop() {
  // put your main code here, to run repeatedly:
  if (arduboy.nextFrame()) {
    StepGame();
    arduboy.display();
  }
}

// platform.h
// General
uint8_t Platform::GetBuffer() {
  return arduboy.sBuffer;
}

uint8_t Platform::ButtonState() {
  uint8_t buttons = arduboy.buttonsState();
  return buttons;
  // Debounce
}

// Drawing
void Platform::DrawBuffer() {}

void Platform::PutPixel(uint8_t x, uint8_t y, uint8_t colour) {
  arduboy.drawPixel(x, y, colour);
}

void Platform::DrawBitmap(const uint8_t* bmp, int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour) {
  arduboy.drawBitmap(x, y, bmp, w, h, colour);
}

void Platform::DrawFilledRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour) {
  arduboy.fillRect(x, y, w, h, colour);
}

void Platform::Clear() {
  arduboy.clear();
}

unsigned long Platform::Millis() {
  return millis();
}

// From font.cpp
void Font::PrintString(const uint8_t* str, uint8_t line, uint8_t x, uint8_t colour)
{
	uint8_t* screenPtr = arduboy.getBuffer();
	uint8_t xorMask = colour == COLOUR_BLACK ? 0xFF : 0;
	screenPtr += DISPLAY_WIDTH * line + x;

	for (;;)
	{
		uint8_t c = *str++;
		if (!c)
			break;
    if (c == 0xC3)
      c = *str++;

		DrawChar(screenPtr, c, xorMask);
		screenPtr += glyphWidth;
	}
}

void Font::PrintInt(uint16_t val, uint8_t line, uint8_t x, uint8_t colour)
{
	uint8_t* screenPtr = arduboy.getBuffer();
	uint8_t xorMask = colour == COLOUR_BLACK ? 0xFF : 0;
	screenPtr += DISPLAY_WIDTH * line + x;

	if (val == 0)
	{
		DrawChar(screenPtr, '0', xorMask);
		return;
	}

	constexpr int maxDigits = 5;
	char buffer[maxDigits];
	int bufCount = 0;

	for (int n = 0; n < maxDigits && val != 0; n++)
	{
		unsigned char c = val % 10;
		buffer[bufCount++] = '0' + c;
		val = val / 10;
	}

	for (int n = bufCount - 1; n >= 0; n--)
	{
		DrawChar(screenPtr, buffer[n], xorMask);
    screenPtr += glyphWidth;
	}

}

void Font::DrawChar(uint8_t* screenPtr, uint8_t c, uint8_t xorMask)
{
  uint16_t idx = CharIdx(c);
	const uint8_t* fontPtr;

  fontPtr = font_images + idx;

	screenPtr[0] = xorMask ^ pgm_read_byte(&fontPtr[0]);
	screenPtr[1] = xorMask ^ pgm_read_byte(&fontPtr[1]);
	screenPtr[2] = xorMask ^ pgm_read_byte(&fontPtr[2]);
	screenPtr[3] = xorMask ^ pgm_read_byte(&fontPtr[3]);

}
#ifdef _DEBUG
void Platform::DebugPrint(uint16_t value) {
  Serial.print(value);
  if (++counter % 8 == 0) {
    Serial.println();
  }
}

void Platform::DebugPrint(unsigned long value) {
  Serial.print(value);
  if (++counter % 8 == 0) {
    Serial.println();
  }
}

void Platform::DebugPrint(float value) {
  Serial.print(value);
  if (++counter % 8 == 0) {
    Serial.println();
  }
}

void Platform::DebugPrint(const uint8_t* text) {
  Serial.println((char*)text);
}
#endif
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
