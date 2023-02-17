#include "rastering_color.h"
#include "rastering_math.h"

color_t color_interpolate(color_t *c1, color_t *c2, float gradient) {
    return (color_t) {
        (uint8_t)interpolate_scalar((float)c1->r, (float)c2->r, gradient),
            (uint8_t)interpolate_scalar((float)c1->g, (float)c2->g, gradient),
            (uint8_t)interpolate_scalar((float)c1->b, (float)c2->b, gradient),
    };
}
