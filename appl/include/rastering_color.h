#ifndef __RASTERING_COLOR_H
#define __RASTERING_COLOR_H
#include "SDL.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} color_t;

static color_t COLOR_RED = {255, 0, 0, 255};
static color_t COLOR_GREEN = {0, 255, 0, 255};
static color_t COLOR_BLUE = {0, 0, 255, 255};

color_t color_interpolate(color_t* c1, color_t* c2, float gradient);

#endif //__RASTERING_COLOR_H