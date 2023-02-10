#include "triangle_raster.h"
#include "rastering_math.h"

bool bbox_is_point_in_tirangle(vector2_t point, vector2_t p1, vector2_t p2, vector2_t p3) {
    int det1 = det(point, p1, p2);
    int det2 = det(point, p2, p3);
    int det3 = det(point, p3, p1);

    return (det1 ^ det2) >= 0 && (det2 ^ det3) >= 0;
}

void bbox_triangle_raster(screen_t *screen, vector2_t p1, vector2_t p2, vector2_t p3, color_t *color) {
    vector2_t min = {
        RASTERING_min3(p1.x, p2.x, p3.x),
        RASTERING_min3(p1.y, p2.y, p3.y),
    };

    vector2_t max = {
        RASTERING_max3(p1.x, p2.x, p3.x),
        RASTERING_max3(p1.y, p2.y, p3.y),
    };

    for (size_t x = min.x; x <= max.x; ++x) {
        for (size_t y = min.y; y <= max.y; ++y) {
            vector2_t point = {x, y};
            if (bbox_is_point_in_tirangle(point, p1, p2, p3)) {
                screen_put_pixel(screen, point, color);
            }
        }
    }

}