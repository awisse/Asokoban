#pragma once

#include <stdint.h>
#include "globals.h"
#include "defines.h"
typedef struct {
  bool running;   // True if running, false if not.
  bool modified;  // True after board is modified.
  bool animating; // True if animation running. No input processed.
  uint16_t level; // Game level
  unsigned long start; // Milliseconds at start
  uint16_t moves; // Number of moves since level started
  bool saved;
} GameStateStruct;

void InitGame();
void RestartLevel();
void NextLevel();
void StepGame();
void LoadGame();
void SaveGame();

void ExecuteMove(uint8_t button);

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=cpp
