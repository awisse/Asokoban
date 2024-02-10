// Wall, Target, Box, Box on Target
#pragma once
#include "defines.h"
/* typedef enum Piece Piece; */
typedef enum {
  Short_A,
  Long_A,
  Short_B,
  Long_B,
  /* VeryLong_B, */
  Left,
  Right,
  Up,
  Down
} Event;

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

// Game States
typedef enum {
  startup, // Application starts
  running, // Game is played
  menu,    // Menu is open
  success, // Level successful finished
  over     // Game Over: Box stuck in corner
} State;

// Result codes for (To|From)EEPROM
typedef enum {
  Saved,
  NotSaved, // Never been saved.
  WrongOffset,
  TooBig,
  WrongSignature
} SavedState;

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

// This structure is to be saved to EEPROM
typedef struct {
  uint16_t level; // Game level
  uint16_t max_level; // Highest level reached
  uint16_t level_ix;  // Index of level in Levels
} GameStateStruct;


// Signature of saved data in EEPROM
constexpr uint8_t signature[] = "ASOK";
// Number of bytes used in EEPROM
constexpr uint16_t eeprom_sz = 6 + 2 * MAX_LEVELS;

extern State state;
extern Player worker;
extern Piece board[HDIM][VDIM];
extern uint8_t BoxCount; // How many boxes not on target
extern uint16_t moves; // Number of moves since the beginning of the game
extern bool modified; // True if screen needs to be redrawn
extern bool stuck; // True if box stuck in corner
// vim:ft=cpp
