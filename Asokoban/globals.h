// Wall, Target, Box, Box on Target
#pragma once
#include "defines.h"
/* typedef enum Piece Piece; */
typedef enum {
  Empty,
  Wall,
  Worker,
  WorkerOnTarget,
  Box,
  BoxOnTarget,
  Target,
  Floor
} Piece;

enum Direction {
  down,
  left,
  right,
  up
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
  uint8_t x;
  uint8_t y;
  Direction direction; // Direction the player is facing
} Player;

typedef struct {
  uint8_t minutes;
  uint8_t seconds;
  uint8_t mdigits; // How many digits in minutes
  uint8_t sdigits; // How many digits in seconds
} Duration;
// vim:ft=cpp
