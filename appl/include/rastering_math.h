#ifndef __RASTERING_MATH_H
#define __RASTERING_MATH_H

#define M_PI 3.14159265358979323846264338327950288

#include "SDL.h"
#include "rastering_vector.h"

#define RASTERING_max3(x, y, z) (SDL_max(SDL_max(x, y), z))
#define RASTERING_min3(x, y, z) (SDL_min(SDL_min(x, y), z))

int det(vector2_t *p, vector2_t *v1, vector2_t *v2);

float interpolate_scalar(float v1, float v2, float gradient);

#endif //__RASTERING_MATH_H