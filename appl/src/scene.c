#include "scene.h"
#include "SDL.h"
#include <stdlib.h>



void dda_line_raster(screen_t* screen, int x1, int y1, int x2, int y2, color_t color) 
{
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    int steps = (dx > dy) ? dx : dy;

    int sx = (x1 > x2) ? -1 : 1;
    int sy = (y1 > y2) ? -1 : 1;

    float step_x = (float)dx * (float)sx / (float)steps;
    float step_y = (float)dy * (float)sy / (float)steps;

    float x = x1;
    float y = y1;

    SDL_SetRenderDrawColor(screen->renderer, color.r, color.g, color.b, color.a);
    for(int i=0; i <= steps; ++i) 
    {
        if (x < 0 || x >= screen->width) continue;
        if (y < 0 || y >= screen->height) continue;

        SDL_RenderDrawPoint(screen->renderer, x, y);
        x += step_x;
        y += step_y;
    }
}

scene_t* scene_create(int screen_width, int screen_height, SDL_Renderer* r) {
    scene_t* scene = (scene_t*)malloc(sizeof(scene_t));
    scene->screen = (screen_t*)malloc(sizeof(screen_t));
    scene->screen->width = screen_width;
    scene->screen->height = screen_height;
    scene->screen->renderer = r;
    return scene;
}

void scene_update(scene_t* s, float delta_time) {
    color_t red = {255, 0, 0, 255};

    int x1 = 50;
    int y1 = 50;
    int x2 = 200;
    int y2 = 250;

    dda_line_raster(s->screen, x1, y1, x2, y2, red);
}

void scene_destroy(scene_t* s) {
    free(s->screen);
    free(s);
}