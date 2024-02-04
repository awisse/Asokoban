/*
Helper functions to unclutter main .ino file
 */
#include "game.h"
#include "levels.h"
#include "draw.h"
#include "controller.h"
#include "globals.h"
#include "platform.h"

GameStateStruct GameState;
Player worker;
uint8_t AnimationStep;
Piece board[HDIM][VDIM];
bool stuck; // True if box stuck in corner
uint8_t BoxCount; // How many boxes not on target

/* void InitLevels(); */
uint16_t FindLevel();
void LoadLevel();
bool MoveBox(uint16_t from_x, uint16_t from_y);
void UpdateAnimation();
void Winning();
void GameOver();
// Check whether a box is in a corner:
void BoxInCorner(uint16_t x, uint16_t y, int16_t dx, int16_t dy);
void BoardMask(Piece mask);

void InitGame() {

  BoardMask(Empty);
  GameState.running = true;
  GameState.animating = false;
  GameState.level = 0;
  GameState.modified = true;
  GameState.start = Platform::Millis();
  GameState.moves = 0;
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

  if (GameState.modified) {
    Draw(board, worker);
    GameState.modified = false;
  }

  if ((BoxCount == 0) && (GameState.running)) {
    GameState.running = false;
    Winning();
  }

  if (stuck) {
    GameOver();
    stuck = false;
  }

}

void LoadGame() {
}

void SaveGame() {
}

uint16_t FindLevel() {
  uint16_t idx = 0, nextIdx;
  uint16_t i = 0; // Level counter

  while ((i < GameState.level) &&
      ((nextIdx=idx+(uint16_t)pgm_read_byte(&Levels[idx])+1) <
       sizeof(Levels))) {
    idx = nextIdx;
    i++;
  }

  // In case GameState.level > highest level available:
  GameState.level = i;

  return idx;
}

void LoadLevel() {
  uint8_t c; // char from array
  Piece p; // current piece from board
  int i,j; // i : array counter, j : repeat counter
  uint8_t rpt; // repeat count
  uint16_t index = FindLevel();
  uint8_t row=0, column=0;

  for (i=index + 1;
      i <= index + (int16_t)pgm_read_byte(&Levels[index]); i++) {
    c = pgm_read_byte(&Levels[i]);
    rpt = (c >> 4) + 1;
    for (j = 0; j < rpt; j++) {
      p = (Piece)(c & 0x07);
      board[column][row] = p;
      if ((p == Worker) || (p == WorkerOnTarget)) {
        worker.x = column;
        worker.y = row;
        worker.direction = up;
      } else if (p == Box) {
        BoxCount++;
      }
      column++;
    }
    row += column >= 0x10 ? 1 : 0;
    column %= 0x10;
  }
  GameState.modified = true;
  stuck = false;
}

void GameOver() {
  GameState.running = false;
  unsigned long elapsed = Platform::Millis() - GameState.start;

  DrawResult(U8"Vous êtes coincé!", 2, GameState.level, GameState.moves,
      elapsed);
}

void Winning () {
  // Show result.
  uint8_t stars;

  unsigned long elapsed = Platform::Millis() - GameState.start;
  if (elapsed < STAR_STEP) {
    stars = 0x0F;
  } else if (elapsed < 2 * STAR_STEP) {
    stars = 0x07;
  } else if (elapsed < 3 * STAR_STEP) {
    stars = 0x03;
  } else if (elapsed < 4 * STAR_STEP) {
    stars = 0x01;
  } else {
    stars = 0;
  }
  Platform::Clear();
  DrawStars(stars);
  DrawResult(U8"Vous avez réussi!", 4, GameState.level, GameState.moves,
      elapsed);
}

void UpdateAnimation() {

}

void ExecuteMove(uint8_t button) {

  uint16_t from_x = worker.x;
  uint16_t from_y = worker.y;
  uint16_t delta_x = 0, delta_y = 0;

  switch (button) {
    case INPUT_UP:
      worker.direction=up;
      delta_y = -1;
      break;
    case INPUT_LEFT:
      worker.direction=left;
      delta_x = -1;
      break;
    case INPUT_DOWN:
      worker.direction=down;
      delta_y = 1;
      break;
    case INPUT_RIGHT:
      worker.direction=right;
      delta_x = 1;
  }
  uint16_t to_x = from_x + delta_x;
  uint16_t to_y = from_y + delta_y;

  // Check whether the move will proceed
  // We are hitting a wall: No move possible.
  if ((to_x < 0) || (to_x > HDIM-1) || (to_y < 0) || (to_y > VDIM-1)) {
    return;
  }
  // Check whether there are obstacles: Wall, Box, BoxOnTarget
  bool moved = true;
  // Decide which piece will be on the target worker position
  Piece to_piece = board[to_x][to_y];
  switch (to_piece) {
    case Wall:
      moved = false;
      break;
    case Target:
      to_piece = WorkerOnTarget;
      break;
    case BoxOnTarget:
    case Box:
      moved = MoveBox(to_x, to_y);
      if (to_piece == BoxOnTarget) {
        to_piece = WorkerOnTarget;
        break;
      }
    default:
      to_piece = Worker;
  }
  // Nothing moves if the movement is blocked by a wall or box
  if (moved) {
    worker.x = to_x;
    worker.y = to_y;
    board[to_x][to_y] = to_piece;
    switch (board[from_x][from_y]) {
      case BoxOnTarget:
        BoxCount++;
      case WorkerOnTarget:
        board[from_x][from_y] = Target;
        break;
      default:
        board[from_x][from_y] = Floor;
    }
    GameState.moves++;
    GameState.modified = true;
  }
}

bool MoveBox(uint16_t from_x, uint16_t from_y) {
  int16_t delta_x=0, delta_y=0;
  uint16_t to_x, to_y;

  switch (worker.direction) {
    case up:
      delta_y = -1;
      break;
    case down:
      delta_y = 1;
      break;
    case left:
      delta_x = -1;
      break;
    case right:
      delta_x = 1;
  }
  to_x = from_x + delta_x;
  to_y = from_y + delta_y;
  if ((to_x > 0) && (to_x < HDIM - 1) &&
      (to_y > 0) && (to_y < VDIM - 1) &&
      (board[to_x][to_y] != Wall) &&
      (board[to_x][to_y] != Box) &&
      (board[to_x][to_y] != BoxOnTarget)) {
    if (board[to_x][to_y] == Target) {
      board[to_x][to_y] = BoxOnTarget;
      BoxCount--;
    } else {
      board[to_x][to_y] = Box;
      BoxInCorner(to_x, to_y, delta_x, delta_y);
    }
    if (board[from_x][from_y] == BoxOnTarget) {
      BoxCount++;
    }
    return true;
  }
  return false;
}

void BoxInCorner(uint16_t x, uint16_t y, int16_t dx, int16_t dy) {
  bool neighbour[4];

  neighbour[down] = (dy != -1) && (
                    (y + 1 == VDIM) || (board[x][y + 1] == Box) ||
                    (board[x][y + 1] == BoxOnTarget) ||
                    (board[x][y + 1] == Wall));

  neighbour[left] = (dx != 1) && (
                    (x == 0) || (board[x - 1][y] == Box) ||
                    (board[x - 1][y] == BoxOnTarget) ||
                    (board[x - 1][y] == Wall));

  neighbour[right] = (dx != -1) && (
                     (x + 1 == HDIM) || (board[x + 1][y] == Box) ||
                     (board[x + 1][y] == BoxOnTarget) ||
                     (board[x + 1][y] == Wall));

  neighbour[up] = (dy != 1) && (
                  (y == 0) || (board[x][y - 1] == Box) ||
                  (board[x][y - 1] == BoxOnTarget) ||
                  (board[x][y - 1] == Wall));


  if ((neighbour[down] && neighbour[left]) ||
      (neighbour[down] && neighbour[right]) ||
      (neighbour[up] && neighbour[left]) ||
      (neighbour[up] && neighbour[right])) {
    stuck = true;
  }
}

void BoardMask(Piece mask) {
  // Set Whole Board to mask
  unsigned int i;
  for (i=0; i<PLACES; i++) {
    *(*board + i) = mask;
  }
}
// vim:fdm=syntax:tabstop=2:softtabstop=2:shiftwidth=2:expandtab
