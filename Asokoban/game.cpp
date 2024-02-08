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
Piece board[HDIM][VDIM];
uint16_t results[MAX_LEVELS]; // Holds results for each level
// Game State variables
// Global variable
State state;   // startup, running, menu, success, over
// Local to game.cpp
bool stuck; // True if box stuck in corner
bool modified; // True if screen needs to be redrawn
bool saved; // True if Game saved to EEPROM
uint32_t start; // Milliseconds at start of game
uint32_t best_time; // Shortest time for this level
uint16_t moves; // Number of moves since the beginning of the game
uint8_t BoxCount; // How many boxes not on target


// Functions
void FindLevel();
void LoadLevel();
void Success();
void GameOver();

void InitGame() {

  state = startup;
  for (uint16_t i=0; i<PLACES; i++) {
    *(*board + i) = Empty;
  }

  Platform::Clear();
  LoadGame();
  LoadLevel();
}

void StepGame() {

  HandleInput();

  if (modified) {
    if (state == running) {
      DrawBoard(board, worker);
    } else if (state == menu) {
      DrawMenu(GameState.level, results);
    }
    modified = false;
  }

  if ((BoxCount == 0) && (state == running)) {
    Success();
  }

  if (stuck) {
    GameOver();
    stuck = false;
  }
}

void RestartLevel() {
  if ((state == success) || (state == running) || (state == over)) {
    LoadLevel();
  }
}

void Terminate() {
  if (state == running) {
    LoadLevel();
  }
}

void NextLevel() {
  if (state == success) {
    GameState.level++;
    LoadLevel();
  }
}

void SelectLevel() {
  if (state == menu) {
    LoadLevel();
  }
}

void LoadGame() {
  // TODO: Load data for display of results.
  // For now: Delete result array
  for (uint16_t i=0; i<MAX_LEVELS; i++) {
    results[i] = 0;
  }
  GameState.level = 1;
  GameState.max_level = 1;
  GameState.level_ix = 0;
  best_time = 0; // This is what we are loading

}

void SaveGame() {
  // TODO: Save after each level.
  // Save level with time and moves.
  Platform::DebugPrint((uint8_t*)"Saving game ... TODO!!");
}

void Menu() {
  // Display the menu at GameState.level
  if ((state == success) || (state == over)) {
    DrawMenu(GameState.level, results);
    state = menu;
  }
}

void MoveMenu(Event e) {
  if (state != menu) return;
  switch (e) {
    case Up:
      if (GameState.level > 5)
        GameState.level -= 4;
      break;
    case Left:
      if (GameState.level > 1)
        GameState.level--;
      break;
    case Down:
      if (GameState.level < GameState.max_level - 4)
        GameState.level += 4;
      break;
    case Right:
      if (GameState.level < GameState.max_level)
        GameState.level++;
    default:
      return;
  }
  modified = true;
}

void FindLevel() {
  uint16_t idx = 0, nextIdx;
  uint16_t i = 1; // Level counter

  while ((i < GameState.level) &&
      ((nextIdx=idx+(uint16_t)pgm_read_byte(&Levels[idx])+1) <
       sizeof(Levels))) {
    idx = nextIdx;
    i++;
  }

  // In case GameState.level > highest level available:
  GameState.level = i;
  GameState.level_ix = idx;
}

void LoadLevel() {
  uint8_t c; // char from array
  Piece p; // current piece from board
  int i,j; // i : array counter, j : repeat counter
  uint8_t rpt; // repeat count
  FindLevel();
  uint8_t row=0, column=0;

  BoxCount = 0;
  for (i=GameState.level_ix + 1; i <= GameState.level_ix +
        (int16_t)pgm_read_byte(&Levels[GameState.level_ix]); i++) {
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
  modified = true;
  start = Platform::Millis();
  moves = 0;
  saved = false;
  stuck = false;
  state = running;
}

void GameOver() {

  uint32_t elapsed = Platform::Millis() - start;

  DrawResult(U8"Vous êtes coincé!", 2, GameState.level, moves, elapsed);
  state = over;
}

void Success () {
  // Show result.
  uint8_t stars;
  uint32_t elapsed = Platform::Millis() - start;

  state = success;
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
  DrawResult(U8"Vous avez réussi!", 4, GameState.level, moves, elapsed);

  // Update time
  if (elapsed < best_time) {
    best_time = elapsed;
  }

  // Update highest succeeded level
  if (GameState.level > GameState.max_level) {
    GameState.max_level = GameState.level;
  }
  saved = false;
  state = success;

}

// vim:fdm=syntax:tabstop=2:softtabstop=2:shiftwidth=2:expandtab
