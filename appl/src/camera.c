#include "camera.h"
#include "SDL.h"

camera_t *camera_create(float fov) {
    camera_t *camera = SDL_malloc(sizeof(camera_t));
    if (!camera) {
        return NULL;
    }
    camera->fov = fov;
    camera->position = (vector3f_t){0, 0, 0};
    
    return camera;
}

vector2_t camera_world_to_screen_space(camera_t* camera, vector3f_t world_point) {
}


void camera_destroy(camera_t* camera) {
    SDL_free(camera);         
}