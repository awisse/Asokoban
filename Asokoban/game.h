#pragma once

#include <stdint.h>
#include "globals.h"
#include "defines.h"

void InitGame();
void StepGame();
void RestartLevel();
void Terminate();
void NextLevel();
void SelectLevel();
void Menu();
void MoveMenu(Event e);
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=cpp
