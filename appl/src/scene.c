#include "scene.h"
#include "color.h"
#include "line_raster.h"
#include "vector.h"
#include "triangle_raster.h"

scene_t *scene_create(int screen_width, int screen_height, float fov, SDL_Renderer *renderer) {
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

    camera_t *camera = camera_create(fov);
    if (!screen) {
        SDL_free(screen);
        SDL_free(scene);
        return NULL;
    }
    scene->camera = camera;
    return scene;
}

void scene_update(scene_t *scene, float delta_time) {
    screen_clear(scene->screen);

    color_t red = {255, 0, 0, 255};

    vector2_t pl1 = {50, 200};
    vector2_t pl2 = {50, 250};

    dda_line_raster(scene->screen, pl1, pl2, &red);

    color_t green = {0, 255, 0, 255};

    vector2_t pt1 = {320, 240};
    vector2_t pt2 = {240, 460};
    vector2_t pt3 = {400, 460};

    bbox_triangle_raster(scene->screen, pt1, pt2, pt3, &green);

    screen_blit(scene->screen);
}

void scene_destroy(scene_t *scene) {
    screen_destroy(scene->screen);
    camera_destroy(scene->camera);
    SDL_free(scene);
}