#ifndef SCENE_H
#define SCENE_H
#include "SDL.h"

typedef struct {
    int width;
    int height;
    SDL_Renderer* renderer;
} screen_t;

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} color_t;


typedef struct {
    screen_t* screen;
} scene_t;

scene_t* scene_create(int w, int h, SDL_Renderer*);
void scene_update(scene_t*, float delta_time);
void scene_destroy(scene_t*);

#endif //SCENE_H