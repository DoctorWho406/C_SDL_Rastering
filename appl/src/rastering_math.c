#include "rastering_math.h"

int det(vector2_t *p, vector2_t *v1, vector2_t *v2) {
    vector2_t a = vector2_get_size_from_origin_and_end(v1, v2);
    vector2_t b = vector2_get_size_from_origin_and_end(v1, p);

    return a.x * b.y - a.y * b.x;
}

float interpolate_scalar(float v1, float v2, float gradient) {
    return v1 + gradient * (v2 - v1);
}