// Drawing/display functions
#pragma once
#include <stdint.h>
#include "globals.h"
#include "defines.h"

// Sprite indexes


// Local Functions
void EraseTile(int16_t x, int16_t y);
void Draw(Piece board[HDIM][VDIM], Player worker);
//
// vim:ft=cpp
