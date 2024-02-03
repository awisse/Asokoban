#include <Arduboy2.h>
#include "game.h"
#include "controller.h"
#include "defines.h"
#include "platform.h"

Arduboy2Base arduboy;
int counter;

void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(20);

#ifdef _DEBUG
  Serial.begin(9600);
  counter = 0;
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

// platform.h
uint8_t Platform::ButtonState() {
  uint8_t buttons = arduboy.buttonsState();
  return buttons;
  // Debounce
}

void Platform::PutPixel(uint8_t x, uint8_t y, uint8_t colour) {
  arduboy.drawPixel(x, y, colour);
}

uint8_t Platform::GetPixel(uint8_t x, uint8_t y) {
  return arduboy.get(x, y);
}

void Platform::DrawBitmap(const uint8_t* bmp, int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour) {
  arduboy.drawBitmap(x, y, bmp, w, h, colour);
}

void Platform::DrawFilledRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t colour) {
  arduboy.fillRect(x, y, w, h, colour);
}

void Platform::Clear() {
  arduboy.clear();
}

unsigned long Platform::Millis() {
  return millis();
}

#ifdef _DEBUG
void Platform::DebugPrint(uint16_t value) {
  Serial.print(value);
  if (++counter % 8 == 0) {
    Serial.println();
  }
}

void Platform::DebugPrint(char* text) {
  Serial.println(text);
}
#endif
// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=arduino
