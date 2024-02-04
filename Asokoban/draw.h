// Drawing/display functions
#pragma once
#include <stdint.h>
#include "globals.h"
#include "defines.h"

// Sprite indexes


// Local Functions
void Draw(Piece board[HDIM][VDIM], Player worker);
void DrawResult(const uint8_t* text, const uint16_t level,
    const uint16_t moves, const unsigned long elapsed);
void DrawStars(uint8_t set);
void DroolScreen(unsigned long time);
//
// vim:ft=cpp
