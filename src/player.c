#include "character.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

static SDL_Texture *player_texture;
static SDL_FRect sprite_portion = {17, 14, 15, 18};

typedef struct {
  float x;
  float y;
} Position;

Position position = {0, 0};

static void quit() {}

static void handle_events(SDL_Event *event) {}

static void update(float delta_time) {
  const bool *keyboard_state = SDL_GetKeyboardState(NULL);

  if (keyboard_state[SDL_SCANCODE_W]) {
    position.y -= 50 * delta_time;
  }
  if (keyboard_state[SDL_SCANCODE_S]) {
    position.y += 50 * delta_time;
  }
  if (keyboard_state[SDL_SCANCODE_A]) {
    position.x -= 50 * delta_time;
  }
  if (keyboard_state[SDL_SCANCODE_D]) {
    position.x += 50 * delta_time;
  }
}

static void render(SDL_Renderer *renderer) {
  SDL_FRect player_position = {position.x, position.y, 15, 18};
  SDL_SetTextureScaleMode(player_texture, SDL_SCALEMODE_NEAREST);
  SDL_RenderTexture(renderer, player_texture, &sprite_portion,
                    &player_position);
}

Character init_player(SDL_Renderer *renderer) {
  const char path[] = "./char_spritesheet.png";
  player_texture = IMG_LoadTexture(renderer, path);

  Character player = {.quit = quit,
                      .handle_events = handle_events,
                      .update = update,
                      .render = render};
  return player;
}
