#ifndef __RASTERING_SCENE_H
#define __RASTERING_SCENE_H

#include "SDL.h"
#include "rastering_screen.h"
#include "rastering_camera.h"

typedef struct {
    screen_t *screen;
    camera_t *camera;
} scene_t;


scene_t *scene_create(int width, int heigth, float fov, SDL_Renderer *);
void scene_update(scene_t *, float delta_time);
void scene_destroy(scene_t *);

#endif //__RASTERING_SCENE_H