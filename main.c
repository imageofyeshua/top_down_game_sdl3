#include <SDL3/SDL_timer.h>
#define SDL_MAIN_USE_CALLBACKS
#include "character.h"
#include "player.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>

#define HANDLE_EVENTS_CHARACTERS(characters, characters_count, event)          \
  for (int i = 0; i < characters_count; i++) {                                 \
    characters[i].handle_events(event);                                        \
  }

#define QUIT_CHARACTERS(characters, characters_count)                          \
  for (int i = 0; i < characters_count; i++) {                                 \
    characters[i].quit();                                                      \
  }

#define UPDATE_CHARACTERS(characters, characters_count, delta_time)            \
  for (int i = 0; i < characters_count; i++) {                                 \
    characters[i].update(delta_time);                                          \
  }

#define RENDER_CHARACTERS(characters, characters_count, renderer)              \
  for (int i = 0; i < characters_count; i++) {                                 \
    characters[i].render(renderer);                                            \
  }

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *player_texture;

Character characters[MAX_CHARACTERS];
int characters_count = 0;

Uint64 last_tick = 0;
Uint64 current_tick = 0;
float delta_time;

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  QUIT_CHARACTERS(characters, characters_count);
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }
  return SDL_APP_CONTINUE;
}

void update() {
  last_tick = current_tick;
  current_tick = SDL_GetTicks();
  delta_time = (current_tick - last_tick) / 1000.0f;

  UPDATE_CHARACTERS(characters, characters_count, delta_time);
}

void render() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  RENDER_CHARACTERS(characters, characters_count, renderer);

  SDL_RenderPresent(renderer);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  update();
  render();
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Error initializing SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  window = SDL_CreateWindow("SDL3 Game", 800, 600, 0);

  if (!window) {
    SDL_Log("Error creating window: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, NULL);

  if (!renderer) {
    SDL_Log("Error creating renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  characters[characters_count++] = init_player(renderer);

  return SDL_APP_CONTINUE;
}
