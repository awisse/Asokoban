#pragma once

#include <stdint.h>
#include "defines.h"
enum Direction {
  down = INPUT_DOWN >> 4,
  up = INPUT_UP >> 4,
  left = INPUT_LEFT >> 4,
  right = INPUT_RIGHT >> 4
};

// Result codes for (To|From)EEPROM
enum {
  Saved,
  NotSaved, // Never been saved.
  WrongOffset,
  TooBig,
  WrongSignature
};

typedef struct {
  bool running;   // True if running, false if not.
  bool modified;  // True after board is modified. 
  bool animating; // True if animation running. No input processed.
  uint16_t level; // Game level
  unsigned long elapsed; // Time elapsed since level started
  uint16_t moves; // Number of moves since level started
  Direction direction; // Direction the player is facing
  bool saved;
} GameStateStruct;

void InitGame();
void NewGame();
void StepGame();
void LoadGame();
void SaveGame();

void ExecuteMove(Direction direction);

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=cpp
