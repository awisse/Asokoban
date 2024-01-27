#include <SDL.h>
#include <stdio.h>
#include "../Asokoban/defines.h"
#include "../Asokoban/controller.h"
/* #include "Game.h" */
/* #include "Interface.h" */
/* #include "Simulation.h" */

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define WHITE 1
#define BLACK 0

#define ZOOM_SCALE 4

SDL_Window* AppWindow;
SDL_Renderer* AppRenderer;

uint8_t InputMask;
void cleanup();

void DrawPixel(uint8_t x, uint8_t y, uint8_t colour) {

  if (colour == WHITE) {
    SDL_SetRenderDrawColor(AppRenderer, 255, 255, 255, 255);
  } else {
    SDL_SetRenderDrawColor(AppRenderer, 0, 0, 0, 255);
  }

  SDL_RenderDrawPoint(AppRenderer, x, y);
}

void DrawBitmap(const uint8_t* data, uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
  for (int j = 0; j < h; j++)
  {
    for (int i = 0; i < w; i++)
    {
      int blockX = i / 8;
      int blockY = j / 8;
      int blocksPerWidth = w / 8;
      int blockIndex = blockY * blocksPerWidth + blockX;
      uint8_t pixels = data[blockIndex * 8 + i % 8];
      uint8_t mask = 1 << (j % 8);
      if (pixels & mask)
      {
        DrawPixel(x + i, y + j, 1);
      }
    }
  }
}

uint8_t GetInput()
{
  return InputMask;
}

int main(int argc, char* argv[])
{
  bool leftmousebuttondown;
  int mousex, mousey;

  SDL_Init(SDL_INIT_VIDEO);

  SDL_CreateWindowAndRenderer(DISPLAY_WIDTH * ZOOM_SCALE, DISPLAY_HEIGHT * ZOOM_SCALE,
      SDL_WINDOW_RESIZABLE, &AppWindow, &AppRenderer);
  SDL_RenderSetLogicalSize(AppRenderer, DISPLAY_WIDTH, DISPLAY_HEIGHT);

  /* InitGame(); */

  bool running = true;
  InputMask = 0;

  while (running)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {

        case SDL_MOUSEBUTTONUP:
          if (event.button.button == SDL_BUTTON_LEFT) {
            leftmousebuttondown = false;
          }
          break;

        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            leftmousebuttondown = true;
            mousex = event.motion.x;
            mousey = event.motion.y;
            DrawPixel(mousex, mousey, WHITE);
          }
          break;

        case SDL_MOUSEMOTION:
          if (leftmousebuttondown) {
            mousex = event.motion.x;
            mousey = event.motion.y;
            DrawPixel(mousex, mousey, WHITE);
          }
        break;

        case SDL_QUIT:
          running = false;
          break;

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {

            case SDLK_a:
              InputMask |= A_BUTTON;
              break;

            case SDLK_LEFT:
              InputMask |= LEFT_BUTTON;
              break;

            case SDLK_RIGHT:
              InputMask |= RIGHT_BUTTON;
              break;

            case SDLK_UP:
              InputMask |= UP_BUTTON;
              break;

            case SDLK_DOWN:
              InputMask |= DOWN_BUTTON;
              break;

            case SDLK_ESCAPE:
              running = false;
              break;
          }
          break;

        case SDL_KEYUP:
          switch (event.key.keysym.sym) {

            case SDLK_a:
              InputMask |= A_BUTTON;
              break;

            case SDLK_LEFT:
              InputMask |= LEFT_BUTTON;
              break;

            case SDLK_RIGHT:
              InputMask |= RIGHT_BUTTON;
              break;

            case SDLK_UP:
              InputMask |= UP_BUTTON;
              break;

            case SDLK_DOWN:
              InputMask |= DOWN_BUTTON;
              break;

            case SDLK_ESCAPE:
              running = false;
              break;

          }
          break;
        }
      }

    SDL_RenderPresent(AppRenderer);

    // FrameRate
    SDL_Delay(1000 / 20);

  }

  cleanup();
  return 0;
}

void cleanup() {
  SDL_DestroyRenderer(AppRenderer);
  SDL_DestroyWindow(AppWindow);
  SDL_Quit();
}

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab:filetype=cpp
