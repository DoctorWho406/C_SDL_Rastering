#include "SDL.h"
#include "line_raster.h"

void dda_line_raster(screen_t *screen, vector2_t p1, vector2_t p2, color_t *color) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps = SDL_max(abs(dx), abs(dy));

    float step_x = (float)dx / (float)steps;
    float step_y = (float)dy / (float)steps;

    vector2_t point = {p1.x, p1.y};
    for (int i = 0; i <= steps; i++) {
        screen_put_pixel(screen, point, color);

        point.x += step_x;
        point.y += step_y;
    }
}