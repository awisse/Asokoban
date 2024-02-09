#pragma once
// Loading and saving game data
//
#include "globals.h"
void LoadState(GameStateStruct* game, uint16_t* results);
void SaveState(const GameStateStruct* game, const uint16_t* results);

// vim:ft=cpp
