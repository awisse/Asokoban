#include <Arduboy2.h>
#include "game.h"
#include "controller.h"

Arduboy2Base arduboy;


void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(20);

#ifdef DEBUG
  Serial.begin(9600);
#endif

  InitGame();

}

void loop() {
  // put your main code here, to run repeatedly:
  if (arduboy.nextFrame()) {
    StepGame();
    arduboy.display();
  }
}

// interface.h
uint8_t GetButtons() {
  uint8_t buttons = arduboy.buttonsState();
  // Debounce
  arduboy.waitNoButtons();
}

// draw.h
void DrawBitmap(const uint8_t* bmp, int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour) {
  arduboy.drawBitmap(x, y, bmp, w, h, colour);
}

void FillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour) {
  arduboy.drawBitmap(x, y, w, h, colour);
}
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
