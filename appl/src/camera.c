#include "camera.h"
#include "SDL.h"

#define M_PI 3.14159265358979323846264338327950288

camera_t* camera_create(float fov, int screen_width, int screen_height) {
    camera_t *camera = SDL_malloc(sizeof(camera_t));
    if (!camera) {
        return NULL;
    }
    camera->fov = fov;
    camera->position = (vector3f_t){0, 0, 0};
    c->width = screen_width;
    c->height = screen_height;
    return camera;
}

vector2_t camera_world_to_screen_space(camera_t* camera, vector3f_t world_point) {
    vector3f_t camera_point = vector3f_sub(wp, camera->position);

    float plane_x = camera_point.x / -camera_point.z;
    float plane_y = camera_point.y / -camera_point.z;


    float half_fov_degrees = camera->vertical_fov_degrees * 0.5f;
    float half_for_radiants = half_fov_degrees * M_PI / 180.f;
    float tan_fov = tanf(half_for_radiants);

    plane_x /= tan_fov;
    plane_y /= tan_fov;

    float aspect = (float)camera->width / (float)camera->height;
    plane_x /= aspect;

    //-1, 1  => w, h
    int screen_x =  (int) ( (plane_x + 1.f) * 0.5f * (float)camera->width );
    int screen_y =  (int) ( (1.f - (plane_y + 1.f) * 0.5f) * (float)camera->height );

    return (vector2_t){screen_x, screen_y};
}

void camera_destroy(camera_t* camera) {
    SDL_free(camera);         
}