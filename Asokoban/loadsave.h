#pragma once
// Loading and saving game data
//
#include "globals.h"
SavedState LoadState(GameStateStruct* game, uint16_t* results);
SavedState SaveState(const GameStateStruct* game, const uint16_t* results);

// vim:ft=cpp
