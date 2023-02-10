#ifndef __SCENE_H
#define __SCENE_H
#include "SDL.h"
#include "screen.h"
#include "camera.h"

typedef struct {
    screen_t* screen;
    camera_t* camera;
} scene_t;

scene_t* scene_create(int width, int heigth, SDL_Renderer*);
void scene_update(scene_t*, float delta_time);
void scene_destroy(scene_t*);

#endif //__SCENE_H