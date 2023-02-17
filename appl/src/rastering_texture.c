#include "rastering_texture.h"
#include "SDL_image.h"

texture_t *texture_load(const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        SDL_Log("Errore creating surface");
        return NULL;
    }

    texture_t *texture = SDL_malloc(sizeof(texture_t));
    texture->heigth = surface->h;
    texture->width = surface->w;
    texture->pixel_size = surface->format->BytesPerPixel;
    texture->data = SDL_malloc(texture->width * texture->heigth * texture->pixel_size * sizeof(Uint8));
    if (!texture->data) {
        SDL_Log("Errore creating data");
        free(texture);
        SDL_FreeSurface(surface);
        return NULL;
    }
    SDL_memcmp(texture->data, surface->pixels, texture->width * texture->heigth * texture->pixel_size * sizeof(Uint8));
    SDL_FreeSurface(surface);
    return texture;
}

void texture_destroy(texture_t *texture) {
    free(texture->data);
    free(texture);
}