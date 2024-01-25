#pragma once

#define HDIM 16
#define VDIM 8
#define PLACES HDIM * VDIM

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

typedef struct {
  bool running;   // true if running, false if not.
  bool animating; // True if animation running. No input processed.
  Direction direction; // Direction the player is facing
  } GameStateStruct;

void InitGame();
void StepGame();

void ExecuteMove(int direction);

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
