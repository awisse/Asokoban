/*
Helper functions to unclutter main .ino file
 */
#include "game.h"
#include "levels.h"
#include "draw.h"
#include "controller.h"
#include "objects.h"
#include "platform.h"

GameStateStruct GameState;
uint8_t AnimationStep;
Piece board[HDIM][VDIM];

/* void InitLevels(); */
uint16_t FindLevel();
void LoadLevel();
void MoveWorker();
void UpdateAnimation();
void GameOver();
void BoardMask(Piece mask);

void InitGame() {

  BoardMask(Empty);
  GameState.running = true;
  GameState.animating = false;
  GameState.level = 0;
  GameState.direction = up;
  AnimationStep = 0;

  Platform::Clear();
  LoadLevel();
}

void NewGame() {
  LoadLevel();
}

void StepGame() {

  if (GameState.animating) {
    UpdateAnimation();
  } else {
    HandleInput();    
  }

  Draw(board);
}

void LoadGame() {
}

void SaveGame() {
}

uint16_t FindLevel() {
  uint16_t idx = 0, nextIdx;
  uint16_t i = 0; // Level counter

  while ((i < GameState.level) && 
      ((nextIdx=idx+(uint16_t)Levels[idx]+1) < sizeof(Levels))) {
    idx = nextIdx;
    i++;
  }

  // In case GameState.level > highest level available:
  GameState.level = i;

  return idx;
}

void LoadLevel() {
  uint8_t c; // char from array
  int i,j; // i : array counter, j : repeat counter
  uint8_t rpt; // repeat count
  uint16_t index = FindLevel();
  uint8_t row=0, column=0;

  for (i=index + 1; i <= index + (int16_t)Levels[index]; i++) {
    c = Levels[i];
    rpt = (c >> 4) + 1;
    for (j = 0; j < rpt; j++) {
      board[column++][row] = (Piece)(c & 0x07);
    }
    row += column >= 0x10 ? 1 : 0;
    column %= 0x10;
  }
}

void GameOver() {
  GameState.running = false;
}

void UpdateAnimation() {

}

void ExecuteMove(Direction direction) {
  
  // For starters: Board drawing
  GameState.direction = direction;

  MoveWorker();
}


void MoveWorker() { // Universal move in all directions
  // Move tiles in any direction
  // Reminder: board[x-axis][y-axis]

}

void BoardMask(Piece mask) {
  // Set Whole Board to mask
  unsigned int i;
  for (i=0; i<PLACES; i++) {
    *(*board + i) = mask;
  }
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab
