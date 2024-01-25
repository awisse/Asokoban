#include "controller.h"
#include "game.h"

void HandleInput() {
  uint8_t buttons;

  buttons = GetButtons();
  if (buttons & (LEFT_BUTTON | RIGHT_BUTTON | UP_BUTTON | DOWN_BUTTON)) {
    ExecuteMove(buttons);
  }

}

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
