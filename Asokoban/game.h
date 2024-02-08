#pragma once

#include <stdint.h>
#include "globals.h"
#include "defines.h"
// This structure is to be saved to EEPROM
typedef struct {
  uint16_t level; // Game level
  uint16_t max_level; // Highest level reached
  uint16_t level_ix;  // Index of level in Levels
} GameStateStruct;

void InitGame();
void StepGame();
void RestartLevel();
void Terminate();
void NextLevel();
void SelectLevel();
void LoadGame();
void SaveGame();
void Menu();
void MoveMenu(Event e);
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=cpp
