/*
Helper functions to unclutter main .ino file
 */
#include "game.h"
#include "draw.h"
#include "controller.h"
#include "objects.h"

GameStateStruct GameState;
uint8_t AnimationStep;
Piece board[HDIM][VDIM];

void MoveWorker(uint8_t direction);
void UpdateAnimation();
void GameOver();
void BoardMask(uint8_t mask);

void InitGame() {

  BoardMask(0);
  GameState.running = true;
  GameState.animating = false;
  AnimationStep = 0;

  Clear();
}

void StepGame() {

  if (GameState.animating) {
    UpdateAnimation();
  } else {
    HandleInput();    
  }

  Draw();
}

void GameOver() {
  GameState.running = false;
}

void UpdateAnimation() {

}

void ExecuteMove(int direction) {

  MoveWorker(direction);
}


void MoveWorker(uint8_t direction) { // Universal move in all directions
  // Move tiles in any direction
  // Reminder: board[x-axis][y-axis]
}

void BoardMask(uint8_t mask) {
  // Logical and of all board values with mask;
  unsigned int i;
  for (i=0; i<PLACES; i++) {
    *(*board + i) &= mask;
  }
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
