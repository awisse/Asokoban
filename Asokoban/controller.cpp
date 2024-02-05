#include "controller.h"
#include "game.h"
#include "defines.h"
#include "platform.h"

uint8_t previousButtons, currentButtons;
uint8_t DebouncedButtons();

bool JustPressed(uint8_t buttons) {
  return ((buttons & currentButtons) && !(buttons & previousButtons));
}

bool JustReleased(uint8_t buttons) {
  return (!(buttons & currentButtons) && (buttons & previousButtons));
}

void HandleInput() {

  static unsigned long startAPress, startBPress;
  static bool AButtonDown, BButtonDown;
  static int BButtonLongPressCycles;

  previousButtons = currentButtons;
  currentButtons = Platform::ButtonState();

  if (JustPressed(INPUT_A)) {
    AButtonDown = true;
    startAPress = Platform::Millis();
    NextLevel();
  }

  if (JustReleased(INPUT_A)) {
    AButtonDown = false;
    startAPress = Platform::Millis();
  }

  if (AButtonDown && (Platform::Millis() - startAPress) > LONG_PRESS) {
    startAPress = Platform::Millis();
    // Handle Long Press Event
    LoadGame();
  }

  if (JustPressed(INPUT_B)) {
    BButtonDown = true;
    startBPress = Platform::Millis();
    // Handle Button Down Event
    SaveGame();
  }

  if (JustReleased(INPUT_B)) {
    BButtonDown = false;
    startBPress = Platform::Millis();
    BButtonLongPressCycles = 0;
    // Handle Button Up Event
  }

  if (BButtonDown && (Platform::Millis() - startBPress) > LONG_PRESS) {
    startBPress = Platform::Millis();
    BButtonLongPressCycles++;
    // Handle Long Press Event
    RestartLevel();
  }

  uint8_t buttons = DebouncedButtons();
  if (buttons & (INPUT_UP | INPUT_DOWN | INPUT_LEFT | INPUT_RIGHT)) {
    ExecuteMove(buttons);
  }
}

uint8_t DebouncedButtons() {
  // Wait for release
  static bool pressed;

  if (!currentButtons) {
    pressed = false;
    return 0;
  } else if (pressed) {
    return 0;
  }

  pressed = true;
  return currentButtons;
}

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab
