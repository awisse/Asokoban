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

SavedState FindSignature(uint16_t* offset) {
  uint16_t saved_length;
  SavedState sstate;

  for (;;) {
    sstate = CheckSignature(signature, *offset);
    if (sstate != WrongSignature) {
      break;
    }
    Platform::FromEEPROM((uint8_t*)&saved_length, *offset + 4, 2);
    *offset += saved_length;
  }
  return sstate;
}

SavedState LoadState(GameStateStruct* game, uint16_t* results) {
  uint16_t i;
  // TODO: Load results, last level played, highest level reached
  // Find saved data
  uint16_t offset = 0;
  SavedState sstate = FindSignature(&offset);

  // Never saved or no room
  // Create default data and return
  if (sstate != Saved) {
    for (i = 0; i<MAX_LEVELS; i++) {
      results[i] = 0;
    }
    game->level = 1;
    game->max_level = 1;
    game->level_ix = 0;
    return sstate;
  }

  // Load saved data
  offset += 6;
  sstate = Platform::FromEEPROM((uint8_t*)game, offset,
      sizeof(GameStateStruct));
  if (sstate != Saved) {
    return sstate;
  }

  offset += sizeof(GameStateStruct);
  sstate = Platform::FromEEPROM((uint8_t*)results, offset,
      MAX_LEVELS * 2);

  // Don't really need return value. But it is available
  // for error messages.
  return sstate;
}

SavedState SaveState(const GameStateStruct* game,
                     const uint16_t* results) {
  // TODO: Save after each level if new information.
  // Save level with time and moves.
  uint16_t offset = 0;
  SavedState sstate = FindSignature(&offset);

  if (!((sstate == Saved) || (sstate == NotSaved))) {
    // Can't save. No room or other problem
    return sstate;
  }

  if (sstate == NotSaved) {
    // First time saved. Write signature and eeprom_sz.
    sstate = Platform::ToEEPROM(signature, offset, 4);
    if (sstate != Saved) return sstate;
    offset += 4;

    sstate = Platform::ToEEPROM((uint8_t*)&eeprom_sz, offset, 2);
    if (sstate != Saved) return sstate;
    offset += 2;
  } else {
    offset += 6;
  }

  sstate = Platform::ToEEPROM((uint8_t*)game, offset, sizeof(*game));
  if (sstate != Saved) return sstate;
  offset += sizeof(*game);

  sstate = Platform::ToEEPROM((uint8_t*)results, offset, 2 * MAX_LEVELS);

  return sstate;
}

