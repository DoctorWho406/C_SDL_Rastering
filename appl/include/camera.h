#ifndef __CAMERA_H
#define __CAMERA_H

#include "vector.h"

typedef struct camera {
    vector3f_t position;
    float fov;
} camera_t;

camera_t *camera_create(float fov);

vector2_t camera_world_to_screen_space(camera_t *, vector3f_t world_point);

camera_t *camera_destroy(camera_t*);

#endif //__CAMERA_H