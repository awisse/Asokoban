// Dispatching user events to the appropriate functions,
// depending on the global State type variable state.
// Emulates "registring listeners"
#include "controller.h"
#include "game.h"
#include "worker.h"
#include "defines.h"
#include "platform.h"

uint8_t previousButtons, currentButtons;
uint8_t DebouncedButtons();


void Dispatch(Event e) {
/* For each event, call all "listeners" that subscribe to that event.
 * The listeners decide whether to act on the event. */
  switch (e) {
    case Short_A:
      NextLevel();
      SelectLevel();
      break;

    case Long_A:
      RestartLevel();
      break;

    case Short_B:
      Menu();
      break;

    case Long_B:
      Terminate();
      break;

    case Left:
    case Right:
    case Up:
    case Down:
      MoveWorker(e);
      MoveMenu(e);
      break;
  }
}

bool JustPressed(uint8_t buttons) {
  return ((buttons & currentButtons) && !(buttons & previousButtons));
}

bool JustReleased(uint8_t buttons) {
  return (!(buttons & currentButtons) && (buttons & previousButtons));
}

void HandleInput() {

  static uint32_t startAPress;
  static bool AButtonDown;
  static uint32_t startBPress;
  static bool BButtonDown;
  static int BButtonLongPressCycles;

  previousButtons = currentButtons;
  currentButtons = Platform::ButtonState();

  if (JustPressed(INPUT_A)) {
    AButtonDown = true;
    startAPress = Platform::Millis();
    Dispatch(Short_A);
  }

  if (JustReleased(INPUT_A)) {
    AButtonDown = false;
    startAPress = Platform::Millis();
  }

  if (AButtonDown && (Platform::Millis() - startAPress) > LONG_PRESS) {
    startAPress = Platform::Millis();
    Dispatch(Long_A);
  }

  // These events available for now:
  if (JustPressed(INPUT_B)) {
    BButtonDown = true;
    startBPress = Platform::Millis();
  }

  if (JustReleased(INPUT_B)) {
    BButtonDown = false;
    startBPress = Platform::Millis();
    BButtonLongPressCycles = 0;
  }

  if (BButtonDown && (Platform::Millis() - startBPress) > LONG_PRESS) {
    startBPress = Platform::Millis();
    BButtonLongPressCycles++;
  }

  uint8_t buttons = DebouncedButtons();
  if (buttons & INPUT_UP) Dispatch(Up);
  else if (buttons & INPUT_DOWN) Dispatch(Down);
  else if (buttons & INPUT_LEFT) Dispatch(Left);
  else if (buttons & INPUT_RIGHT) Dispatch(Right);

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
