#include "SDL.h"
#include "color.h"
#include "scene.h"
#include "screen.h"
#include "line_raster.h"

scene_t *scene_create(int screen_width, int screen_height, SDL_Renderer *renderer) {
    scene_t *scene = (scene_t *)SDL_malloc(sizeof(scene_t));
    if (!scene) {
        return NULL;
    }
    screen_t *screen = screen_create(screen_width, screen_height, renderer);
    if (!screen) {
        SDL_free(scene);
        return NULL;
    }
    scene->screen = screen;
    return scene;
}

void scene_update(scene_t *scene, float delta_time) {
    screen_clear(scene->screen);

    color_t red = {255, 0, 0, 255};

    int x1 = 50;
    int y1 = 200;
    int x2 = 125;
    int y2 = 50;
    int x3 = 200;
    int y3 = 200;

    dda_line_raster(scene->screen, x1, y1, x2, y2, &red);
    dda_line_raster(scene->screen, x2, y2, x3, y3, &red);
    dda_line_raster(scene->screen, x3, y3, x1, y1, &red);

    screen_blit(scene->screen);
}

void scene_destroy(scene_t *scene) {
    screen_destroy(scene->screen);
    SDL_free(scene);
}