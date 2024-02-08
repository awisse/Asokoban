#include <stdint.h>
#include "globals.h"
#include "worker.h"

bool MoveBox(uint16_t from_x, uint16_t from_y);
void BoxInCorner(uint16_t x, uint16_t y, int16_t dx, int16_t dy);

void MoveWorker(Event e) {

  uint16_t from_x = worker.x;
  uint16_t from_y = worker.y;
  uint16_t delta_x = 0, delta_y = 0;

  if (state != running) {
    return;
  }
  switch (e) {
    case Up:
      worker.direction=up;
      delta_y = -1;
      break;
    case Left:
      worker.direction=left;
      delta_x = -1;
      break;
    case Down:
      worker.direction=down;
      delta_y = 1;
      break;
    case Right:
      worker.direction=right;
      delta_x = 1;
      break;
    default:
      return;
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
    moves++;
    modified = true;
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
                    (y + 1 == VDIM) || (board[x][y + 1] == Wall));

  neighbour[left] = (dx != 1) && (
                    (x == 0) || (board[x - 1][y] == Wall));

  neighbour[right] = (dx != -1) && (
                     (x + 1 == HDIM) || (board[x + 1][y] == Wall));

  neighbour[up] = (dy != 1) && (
                  (y == 0) || (board[x][y - 1] == Wall));


  if ((neighbour[down] && neighbour[left]) ||
      (neighbour[down] && neighbour[right]) ||
      (neighbour[up] && neighbour[left]) ||
      (neighbour[up] && neighbour[right])) {
    stuck = true;
  }
}
