#include "rastering_vector.h"
#include "rastering_math.h"

vector2_t vector2_get_size_from_origin_and_end(vector2_t *start, vector2_t *end) {
    return (vector2_t) { end->x - start->x, end->y - start->y };
}

void vector2_sort_by_y(vector2_t **p1, vector2_t **p2, vector2_t **p3) {
    vector2_t *temp;
    if ((*p1)->y > (*p2)->y) {
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }

    if ((*p2)->y > (*p3)->y) {
        temp = *p2;
        *p2 = *p3;
        *p3 = temp;
    }

    if ((*p1)->y > (*p2)->y) {
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
}

vector2f_t vector2f_interpolate(vector2f_t* v1, vector2f_t* v2, float gradient) {
    return (vector2f_t) {
        interpolate_scalar(v1->x, v1->y, gradient),
        interpolate_scalar(v2->x, v2->y, gradient),
    };
}

vector3f_t vector3f_sub(vector3f_t *a, vector3f_t *b) {
    return (vector3f_t) { b->x - a->x, b->y - a->y, b->z - a->z };
}

vector3f_t vector3f_mul(vector3f_t *a, float b) {
    return (vector3f_t) { a->x *b, a->y *b, a->z *b };
}

vector3f_t vector3f_rotate_y(vector3f_t *vector, float degrees) {
    float radiants = degrees * M_PI / 180.f;

    return (vector3f_t) {
        (cosf(radiants) * vector->x) - (sinf(radiants) * vector->z),
            vector->y,
            (sinf(radiants) * vector->x) + (cosf(radiants) * vector->z),
    };
}