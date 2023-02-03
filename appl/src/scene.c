#include "scene.h"
#include "SDL.h"
#include <stdlib.h>
#include "screen.h"
#include "line-raster.h"
#include "vector.h"
#include "triangle-raster.h"

scene_t* scene_create(int screen_width, int screen_height, SDL_Renderer* r) {
    scene_t* scene = (scene_t*)malloc(sizeof(scene_t));
    scene->screen = screen_new(screen_width, screen_height, r);
    scene->camera = camera_new(60, screen_width, screen_height);
    //scene->camera->position = (vector3f_t){-5, 0, 0};
    return scene;
}

void scene_update(scene_t* s, float delta_time) {
    screen_clear(s->screen);
   
    color_t red = {255, 0, 0, 255};

    static float x1 = 50;
    static float y1 = 50;
    static float x2 = 200;
    static float y2 = 250;

    dda_line_raster(s->screen, (int)x1, (int)y1, (int)x2, (int)y2, red);
    //dda_line_raster(s->screen, x1+10, y1, x2+10, y2, red);
    float speed = 1;
    x1 += speed * delta_time;
    x2 += speed * delta_time;


    //Draw Triangle Edges
    dda_line_raster(s->screen, 320, 240, 240, 460, red);  //left
    dda_line_raster(s->screen, 320, 240, 400, 460, red); //right
    dda_line_raster(s->screen, 240, 460, 400, 460, red); //base

    /*
    vector2_t p1 = { 320, 240 };
    vector2_t p2 = { 240, 460 };
    vector2_t p3 = { 400, 460 };
    */
    vector3f_t wp1 = { 0.f, 0.f,   -10 };
    vector3f_t wp2 = { -4.f, -4.f, -10 };
    vector3f_t wp3 = { 4.f, -4.f,  -10 };

    color_t green = {0, 255, 0, 255};


    vector2_t p1 = camera_world_to_screen_space(s->camera, wp1);
    vector2_t p2 = camera_world_to_screen_space(s->camera, wp2);
    vector2_t p3 = camera_world_to_screen_space(s->camera, wp3);
    bbox_triangle_raster(s->screen, p1, p2, p3, green);

    screen_blit(s->screen);
}

void scene_destroy(scene_t* s) {
    screen_free(s->screen);
    free(s);
}