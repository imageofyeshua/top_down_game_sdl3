#ifndef COMMON_H
#define COMMON_H

#include "../character.h"
#include <SDL3/SDL.h>

typedef struct _AppState {
  SDL_Window *window;
  SDL_Renderer *renderer;
  float last_tick;
  float current_tick;
  float delta_time;
} AppState;

#endif
