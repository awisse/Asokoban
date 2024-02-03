// Drawing/display functions
#pragma once
#include <stdint.h>
#include "globals.h"
#include "defines.h"

// Sprite indexes


// Local Functions
void Draw(Piece board[HDIM][VDIM], Player worker);
void DrawWin(uint16_t moves, unsigned long time);
void DrawStars(unsigned long time);
void DroolScreen(unsigned long time);
//
// vim:ft=cpp
