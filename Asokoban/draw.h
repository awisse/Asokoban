// Drawing/display functions
#pragma once
#include <stdint.h>
#include "globals.h"
#include "defines.h"

// Sprite indexes


// Local Functions
void DrawBoard(Piece board[HDIM][VDIM], Player worker);
void DrawMenu(uint16_t level, uint16_t* results);
void DrawResult(const uint8_t* text, const uint8_t row, const uint16_t
    level, const uint16_t moves, const uint32_t elapsed);
void DrawStars(uint8_t set);
//
// vim:ft=cpp
