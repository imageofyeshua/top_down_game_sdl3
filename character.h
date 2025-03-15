#ifndef CHARACTER_H
#define CHARACTER_H
#define MAX_CHARACTERS 100
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

typedef struct {
  void (*quit)(void);
  void (*handle_events)(SDL_Event *);
  void (*update)(void);
  void (*render)(SDL_Renderer *);
} Character;

#endif // !ENTITY_H
