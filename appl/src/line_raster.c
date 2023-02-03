#include "SDL.h"
#include "line_raster.h"
#include "screen.h"

void dda_line_raster(screen_t *screen, int x1, int y1, int x2, int y2, color_t *color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = SDL_max(abs(dx), abs(dy));

    float step_x = (float)dx / (float)steps;
    float step_y = (float)dy / (float)steps;

    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        screen_put_pixel(screen, x, y, color);

        x += step_x;
        y += step_y;
    }
}