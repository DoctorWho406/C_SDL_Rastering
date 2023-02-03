#include "screen.h"

screen_t *screen_new(int w, int h, SDL_Renderer *r) {
    screen_t *screen = (screen_t *)SDL_malloc(sizeof(screen_t));
    screen->width = w;
    screen->height = h;
    screen->renderer = r;
    screen->texture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, w, h);
    screen->color_buffer_size = w * h * 4 * sizeof(Uint8);
    screen->color_buffer = (Uint8 *)SDL_malloc(screen->color_buffer_size);

    return screen;
}

void screen_free(screen_t *s) {
    SDL_DestroyTexture(s->texture);
    SDL_free(s->color_buffer);
    SDL_free(s);
}

void screen_put_pixel(screen_t *screen, int x, int y, color_t* color) {
    if (x < 0 || x >= screen->width) return;
    if (y < 0 || y >= screen->height) return;

    int index = (y * screen->width + x) * 4;
    screen->color_buffer[index + 0] = color->r;
    screen->color_buffer[index + 1] = color->g;
    screen->color_buffer[index + 2] = color->b;
    screen->color_buffer[index + 3] = color->a;
}

void screen_blit(screen_t *screen) {
    SDL_UpdateTexture(screen->texture, NULL, screen->color_buffer, screen->width * 4);
    SDL_RenderCopy(screen->renderer, screen->texture, NULL, NULL);
}

void screen_clear(screen_t *screen) {
    SDL_memset(screen->color_buffer, 0, screen->color_buffer_size);
}