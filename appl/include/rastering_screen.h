#ifndef __RASTERING_SCREEN_H
#define __RASTERING_SCREEN_H

#include "SDL.h"
#include "rastering_vector.h"
#include "rastering_color.h"

typedef struct {
    int width;
    int height;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Uint8 *color_buffer;
    size_t color_buffer_size;
} screen_t;

screen_t *screen_create(int width, int height, SDL_Renderer *);
void screen_destroy(screen_t *);
void screen_put_pixel(screen_t *, vector2_t *pixel, color_t *);
void screen_blit(screen_t *);
void screen_clear(screen_t *);

#endif //__RASTERING_SCREEN_H