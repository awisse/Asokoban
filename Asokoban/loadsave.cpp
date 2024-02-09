#include "globals.h"
#include "platform.h"
#include "loadsave.h"
#include "globals.h"

SavedState CheckSignature(const uint8_t* signature, int offset) {
  uint8_t id[4];
  int i;
  SavedState savedState = Platform::FromEEPROM(id, offset, 4);

  if (savedState != Saved) {
    return savedState;
  }

  if (*(uint32_t*)id == 0xFFFFFFFF) {
    return NotSaved;
  }

  for (i=0; i<4; i++) {
    if (id[i] != signature[i]) {
      return WrongSignature;
    }
  }

  return Saved;
}

void LoadState(GameStateStruct* game, uint16_t* results) {
  uint16_t i;
  // TODO: Load results, last level played, highest level reached
  // Find saved data
  uint16_t next = 0;
  uint16_t step;
  SavedState sstate;

  for (;;) {
    sstate = CheckSignature((uint8_t*)"ASOK", next);
    if (sstate == WrongSignature) {
      Platform::FromEEPROM((uint8_t*)&step, next + 4, 2);
      next += step;
    } else {
      break;
    }
  }

  // Never saved:
  if (sstate == NotSaved) {
    for (i = 0; i<MAX_LEVELS; i++) {
      results[i] = 0;
    }
    game->level = 1;
    game->max_level = 1;
    game->level_ix = 0;
    return;
  }

  // TODO: Load saved data
}

void SaveState(const GameStateStruct* game, const uint16_t* results) {
  // TODO: Save after each level.
  // Save level with time and moves.
  Platform::DebugPrint((uint8_t*)"Saving game ... TODO!!");
}

