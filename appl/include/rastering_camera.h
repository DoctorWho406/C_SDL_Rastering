#ifndef __RASTERING_CAMERA_H
#define __RASTERING_CAMERA_H

#include "rastering_vector.h"
#include <stdlib.h>

typedef struct camera {
    vector3f_t position;
    float fov;
    int width;
    int height;
} camera_t;

camera_t *camera_create(float fov, int screen_width, int screen_height);

vector2_t camera_world_to_screen_space(camera_t *, vector3f_t world_point);

void camera_destroy(camera_t *);

#endif //__RASTERING_CAMERA_H
