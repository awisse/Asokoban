#pragma once

#define _BV(bit) (1U << (bit))
#define LEFT_BUTTON _BV(5)  
#define RIGHT_BUTTON _BV(6) 
#define UP_BUTTON _BV(7)    
#define DOWN_BUTTON _BV(4)  
#define A_BUTTON _BV(3)     
#define B_BUTTON _BV(2)     
#include <stdint.h>

uint8_t GetButtons();
void HandleInput();
//void Delay(uint16_t milliseconds);

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
