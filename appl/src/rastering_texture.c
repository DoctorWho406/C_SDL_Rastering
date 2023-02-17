#include "rastering_texture.h"
#include "SDL_image.h"

texture_t *texture_load(const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        return NULL;
    }

    texture_t *texture = SDL_malloc(sizeof(texture_t));
    texture->heigth = surface->h;
    texture->width = surface->w;
    texture->pixel_size = surface->format->BytesPerPixel;
    texture->data = SDL_malloc(texture->width * texture->heigth * texture->pixel_size * sizeof(Uint8));
    if (!texture->data) {
        free(texture);
        SDL_FreeSurface(surface);
        return NULL;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void texture_destroy(texture_t *texture) {
    free(texture->data);
    free(texture);
}