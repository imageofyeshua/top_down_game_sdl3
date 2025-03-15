#ifndef CHARACTER_H
#define CHARACTER_H
#define MAX_CHARACTERS 100
#include <SDL3/SDL.h>

typedef struct _Character {
  void (*quit)(void);
  void (*handle_events)(SDL_Event *);
  void (*update)(float);
  void (*render)(SDL_Renderer *);
} Character;

extern Character characters[MAX_CHARACTERS];
extern int characters_count;

#endif
