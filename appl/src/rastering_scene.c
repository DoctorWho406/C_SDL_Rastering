#include "rastering_scene.h"
#include "rastering_color.h"
#include "rastering_line_raster.h"
#include "rastering_vector.h"
#include "rastering_triangle_raster.h"
#include "rastering_scanline_raster.h"

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

    camera_t *camera = camera_create(fov, screen_width, screen_height);
    if (!screen) {
        SDL_free(screen);
        SDL_free(scene);
        return NULL;
    }
    scene->camera = camera;

    obj_t *quad;
    obj_parser_parse(&quad, "bin/appl/resources/quad.obj");
    if (!quad) {
        SDL_free(camera);
        SDL_free(screen);
        SDL_free(scene);
        return NULL;
    }
    scene->quad = quad;

    obj_t *suzanne;
    obj_parser_parse(&suzanne, "bin/appl/resources/suzanne.obj");
    if (!suzanne) {
        SDL_free(quad);
        SDL_free(camera);
        SDL_free(screen);
        SDL_free(scene);
        return NULL;
    }
    scene->suzanne = suzanne;

    return scene;
}

void _scene_draw_line(scene_t *scene) {
    color_t red = {255, 0, 0, 255};

    vector2_t p1 = {50, 50};
    vector2_t p2 = {200, 200};

    dda_line_raster(scene->screen, &p1, &p2, &red);
}

void _scene_draw_triangle(scene_t *scene) {
    color_t green = {0, 255, 0, 255};

    vector2_t p1 = {320, 240};
    vector2_t p2 = {240, 460};
    vector2_t p3 = {400, 460};

    bbox_triangle_raster(scene->screen, &p1, &p2, &p3, &green);
}

void _scene_draw_quad(scene_t *scene) {
    color_t blue = {0, 0, 255, 255};

    vector3f_t cw_p1;
    vector3f_t cw_p2;
    vector3f_t cw_p3;

    vector2_t ss_p1;
    vector2_t ss_p2;
    vector2_t ss_p3;

    for (int i = 0; i < scene->quad->face_count; ++i) {
        cw_p1 = *((vector3f_t *)&(scene->quad->triangles[i].v1.position));
        cw_p2 = *((vector3f_t *)&(scene->quad->triangles[i].v2.position));
        cw_p3 = *((vector3f_t *)&(scene->quad->triangles[i].v3.position));

        //Move all points 3 unit back to Z
        vector3f_t translation = {0, 0, 5.0f};

        cw_p1 = vector3f_sub(&cw_p1, &translation);
        cw_p2 = vector3f_sub(&cw_p2, &translation);
        cw_p3 = vector3f_sub(&cw_p3, &translation);

        ss_p1 = camera_world_to_screen_space(scene->camera, &cw_p1);
        ss_p2 = camera_world_to_screen_space(scene->camera, &cw_p2);
        ss_p3 = camera_world_to_screen_space(scene->camera, &cw_p3);
        bbox_triangle_raster(scene->screen, &ss_p1, &ss_p2, &ss_p3, &blue);
    }
}

void _scene_draw_rotate_suzanne(scene_t *scene, float delta_time, bool wireframe) {
    color_t red = {255, 0, 0, 255};

    static float rotation = 0.f;
    rotation += 2.f * delta_time;

    vector3f_t cw_p1;
    vector3f_t cw_p2;
    vector3f_t cw_p3;

    vector2_t ss_p1;
    vector2_t ss_p2;
    vector2_t ss_p3;

    //SCALE - ROTATE - TRANSLATE
    for (int i = 0; i < scene->suzanne->face_count; ++i) {
        cw_p1 = *((vector3f_t *)&(scene->suzanne->triangles[i].v1.position));
        cw_p2 = *((vector3f_t *)&(scene->suzanne->triangles[i].v2.position));
        cw_p3 = *((vector3f_t *)&(scene->suzanne->triangles[i].v3.position));

        //SCALE
        cw_p1 = vector3f_mul(&cw_p1, 1);
        cw_p2 = vector3f_mul(&cw_p2, 1);
        cw_p3 = vector3f_mul(&cw_p3, 1);

        //ROTATE
        cw_p1 = vector3f_rotate_y(&cw_p1, rotation);
        cw_p2 = vector3f_rotate_y(&cw_p2, rotation);
        cw_p3 = vector3f_rotate_y(&cw_p3, rotation);

        //TRANSLATE
        vector3f_t translation = {0, 0, 5.0f};
        cw_p1 = vector3f_sub(&cw_p1, &translation);
        cw_p2 = vector3f_sub(&cw_p2, &translation);
        cw_p3 = vector3f_sub(&cw_p3, &translation);

        ss_p1 = camera_world_to_screen_space(scene->camera, &cw_p1);
        ss_p2 = camera_world_to_screen_space(scene->camera, &cw_p2);
        ss_p3 = camera_world_to_screen_space(scene->camera, &cw_p3);

        if (wireframe) {
            dda_line_raster(scene->screen, &ss_p1, &ss_p2, &red);
            dda_line_raster(scene->screen, &ss_p1, &ss_p3, &red);
            dda_line_raster(scene->screen, &ss_p2, &ss_p3, &red);
        } else {
            bbox_triangle_raster(scene->screen, &ss_p1, &ss_p2, &ss_p3, &red);
        }
    }
}

void _scene_draw_rotate_suzanne_with_scanline(scene_t *scene, float delta_time) {
    color_t color = {255, 0, 255, 255};

    static float rotation = 0.f;
    rotation += 2.f * delta_time;

    vector3f_t cw_p1;
    vector3f_t cw_p2;
    vector3f_t cw_p3;

    vector2_t ss_p1;
    vector2_t ss_p2;
    vector2_t ss_p3;

    //SCALE - ROTATE - TRANSLATE
    for (int i = 0; i < scene->suzanne->face_count; ++i) {
        cw_p1 = *((vector3f_t *)&(scene->suzanne->triangles[i].v1.position));
        cw_p2 = *((vector3f_t *)&(scene->suzanne->triangles[i].v2.position));
        cw_p3 = *((vector3f_t *)&(scene->suzanne->triangles[i].v3.position));

        //SCALE
        cw_p1 = vector3f_mul(&cw_p1, 1);
        cw_p2 = vector3f_mul(&cw_p2, 1);
        cw_p3 = vector3f_mul(&cw_p3, 1);

        //ROTATE
        cw_p1 = vector3f_rotate_y(&cw_p1, rotation);
        cw_p2 = vector3f_rotate_y(&cw_p2, rotation);
        cw_p3 = vector3f_rotate_y(&cw_p3, rotation);

        //TRANSLATE
        vector3f_t translation = {0, 0, 5.0f};
        cw_p1 = vector3f_sub(&cw_p1, &translation);
        cw_p2 = vector3f_sub(&cw_p2, &translation);
        cw_p3 = vector3f_sub(&cw_p3, &translation);

        ss_p1 = camera_world_to_screen_space(scene->camera, &cw_p1);
        ss_p2 = camera_world_to_screen_space(scene->camera, &cw_p2);
        ss_p3 = camera_world_to_screen_space(scene->camera, &cw_p3);

        scanline_raster(scene->screen, &ss_p1, &ss_p2, &ss_p3, &color);
    }
}

void scene_update(scene_t *scene, float delta_time) {
    screen_clear(scene->screen);

    ///LINE
    // _scene_draw_line(scene);

    ///TRIANGLE
    // _scene_draw_triangle(scene);

    ///QUAD
    // _scene_draw_quad(scene);

    ///SUZANNE
    _scene_draw_rotate_suzanne(scene, delta_time, true);
    // _scene_draw_rotate_suzanne_with_scanline(scene, delta_time);

    screen_blit(scene->screen);
}

void scene_destroy(scene_t *scene) {
    screen_destroy(scene->screen);
    camera_destroy(scene->camera);
    obj_parser_destroy(scene->quad);
    obj_parser_destroy(scene->suzanne);
    SDL_free(scene);
}