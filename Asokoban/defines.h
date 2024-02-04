#pragma once

// Platform dependant definitions
#ifndef ARDUINO
#include <stdint.h>
#include <string.h>
#define PROGMEM
#define PSTR
#define pgm_read_byte(x) *(x)
#define pgm_read_word(x) (*((uint16_t*)x))
#define pgm_read_ptr(x) (*((uintptr_t*)x))
#define strlen_P(x) strlen(x)
#else
#include <avr/pgmspace.h>
//#define pgm_read_ptr pgm_read_word
#endif

#define _DEBUG

// Conversions
#define U8 (uint8_t*)

// Board Dimensions
#define HDIM 16
#define VDIM 8
#define PLACES HDIM * VDIM

// Screen Dimensions
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define TILE_SZ 8

#define COLOUR_WHITE 1
#define COLOUR_BLACK 0
#define INVERT 2

// Buttons
#define INPUT_LEFT 32u
#define INPUT_RIGHT 64u
#define INPUT_UP 128u
#define INPUT_DOWN 16u
#define INPUT_A 8u
#define INPUT_B 4u

// Time
#define LONG_PRESS 2000
// To obtain reward stars
#define STAR_STEP 3000
