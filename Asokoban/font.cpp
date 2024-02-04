// Compact font taken from
// https://hackaday.io/project/6309-vga-graphics-over-spi-and-serial-vgatonic/log/20759-a-tiny-4x6-pixel-font-that-will-fit-on-almost-any-microcontroller-license-mit

#include <stdint.h>
#include "defines.h"
#include "font.h"
#include "platform.h"

uint16_t Font::CharIdx(const uint8_t c) {

  uint16_t idx;

  switch (c) {

    case CHAR_LETTER_A ... CHAR_LETTER_Z:
      idx = c - CHAR_LETTER_A;
      break;

    case CHAR_LETTER_A_LOWER ... CHAR_LETTER_Z_LOWER:
      idx = c - CHAR_LETTER_A_LOWER + 26;
      break;

    case CHAR_NUMBER_0 ... CHAR_NUMBER_9:
      idx = c - CHAR_NUMBER_0 + FONT_NUMBER_INDEX;
      break;

    case '!':
      idx = FONT_EXCLAMATION_INDEX;
      break;

    case '.':
      idx = FONT_PERIOD_INDEX;
      break;

    case ' ':
      idx = FONT_SPACE_INDEX;
      break;

    case 0x27:
      idx = FONT_APOSTROPHE_INDEX;
      break;

    case 0xA9:
      idx = FONT_EACUTE_INDEX;
      break;

    case 0xAA:
      idx = FONT_ECIRCONFLEX_INDEX;
      break;

    case 0x3A:
      idx = FONT_COLON_INDEX;
      break;

    default:
      idx = FONT_BIDON_INDEX;
  }

  return idx * FONT_WIDTH;
}


