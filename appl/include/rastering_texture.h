#ifndef __RASTERING_TEXTURE_H
#define __RASTERING_TEXTURE_H

#include "SDL.h"

typedef struct texture {
    uint8_t* data;
    int width;
    int heigth;
    int pixel_size;
} texture_t;

texture_t* texture_load(const char* path);

void texture_destroy(texture_t*);

#endif //__RASTERING_TEXTURE_H