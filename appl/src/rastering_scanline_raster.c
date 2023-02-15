#include "rastering_scanline_raster.h"
#include "rastering_math.h"

void _interpolate_row(screen_t *screen, int y, vector2_t *left_edge_v1, vector2_t *left_edge_v2, vector2_t *right_edge_v1, vector2_t *right_edge_v2, color_t *color) {
    float left_gradient_y = 1.f;
    if (left_edge_v1->y != left_edge_v2->y) {
        left_gradient_y = (float)(y - left_edge_v1->y) / (float)(left_edge_v2->y - left_edge_v1->y);
    }

    float right_gradient_y = 1.f;
    if (right_edge_v1->y != right_edge_v2->y) {
        right_gradient_y = (float)(y - right_edge_v1->y) / (float)(right_edge_v2->y - right_edge_v1->y);
    }

    int left_x = (int)interpolate_scalar((float)left_edge_v1->x, (float)left_edge_v2->x, left_gradient_y);
    int right_x = (int)interpolate_scalar((float)right_edge_v1->x, (float)right_edge_v2->x, right_gradient_y);

    vector2_t pixel;
    for (int x = left_x; x <= right_x; ++x) {
        pixel = (vector2_t){x, y};
        screen_put_pixel(screen, &pixel, color);
    }
}

void scanline_raster(screen_t *screen, vector2_t *p1, vector2_t *p2, vector2_t *p3, color_t *color) {
    vector2_sort_by_y(&p1, &p2, &p3);

    float inv_slope_p1p2 = (float)(p2->x - p1->x) / (float)(p2->y - p1->y);
    float inv_slope_p1p3 = (float)(p3->x - p1->x) / (float)(p3->y - p1->y);

    // <|
    if (inv_slope_p1p2 < inv_slope_p1p3) {
        for (int y = p1->y; y <= p3->y; ++y) {
            if (y < p2->y) {
                //phase1: upper triangle: left: p1p2 right p1p3
                _interpolate_row(screen, y, p1, p2, p1, p3, color);
            } else {
                //phase2: lower triangle: left: p2p3 right p1p3
                _interpolate_row(screen, y, p2, p3, p1, p3, color);
            }
        }
    } else // |>
    {
        for (int y = p1->y; y <= p3->y; ++y) {
            if (y < p2->y) {
                //phase1: upper triangle: left: p1p3 right p1p2
                _interpolate_row(screen, y, p1, p3, p1, p2, color);
            } else {
                //phase2: lower triangle: left: p1p3 right p2p3
                _interpolate_row(screen, y, p1, p3, p2, p3, color);
            }
        }
    }
}