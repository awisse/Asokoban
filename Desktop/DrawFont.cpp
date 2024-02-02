#include "../Asokoban/defines.h"
#include "../Asokoban/platform.h"
#include "../Asokoban/font.h"

struct CharPosition {
  uint8_t line;
  uint8_t x;
};

Platform p;

void Font::PrintString(const char* str, uint8_t line, uint8_t x, uint8_t colour)
{
	uint8_t xorMask = colour == COLOUR_BLACK ? 0xFF : 0;
  struct CharPosition pos;

  pos.line = line;
  pos.x = x;

	for (;;)
	{
		char c = *str++;
		if (!c)
			break;

    // We are cheating with type conversion here in order
    // to remain compatible with the Arduboy version
		DrawChar((uint8_t*)&pos, c, xorMask);
    if (pos.x > DISPLAY_WIDTH - glyphWidth - 1) {
      pos.line++;
    }
    pos.x += glyphWidth; // uint8_t. Wraps around automatically.
	}
}

void Font::PrintInt(uint16_t val, uint8_t line, uint8_t x, uint8_t colour)
{
	uint8_t xorMask = colour == COLOUR_BLACK ? 0xFF : 0;
  struct CharPosition pos;

  pos.line = line;
  pos.x = x;

	if (val == 0)
	{
		DrawChar((uint8_t*)&pos, '0', xorMask);
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
		DrawChar((uint8_t*)&pos, buffer[n], xorMask);
    if (pos.x > DISPLAY_WIDTH - glyphWidth - 1) {
      pos.line++;
    }
    pos.x += glyphWidth;
	}

}

void Font::DrawChar(uint8_t* screenPtr, char c, uint8_t xorMask)
{
  uint16_t idx = CharIdx(c);
	const uint8_t* fontPtr;
  uint8_t glyphPtr[4];

  struct CharPosition* pos = (CharPosition*)screenPtr;

  fontPtr = font_images + idx;

	glyphPtr[0] = xorMask ^ fontPtr[0];
	glyphPtr[1] = xorMask ^ fontPtr[1];
	glyphPtr[2] = xorMask ^ fontPtr[2];
	glyphPtr[3] = xorMask ^ fontPtr[3];

  p.DrawBitmap(glyphPtr, pos->x, 8 * (pos->line), FONT_WIDTH, FONT_HEIGHT, COLOUR_WHITE);


}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab
