#ifndef SCENE_H
#define SCENE_H
#include "SDL.h"
#include "screen.h"

typedef struct {
    screen_t* screen;
} scene_t;

scene_t* scene_create(int w, int h, SDL_Renderer*);
void scene_update(scene_t*, float delta_time);
void scene_destroy(scene_t*);

#endif //SCENE_H