#include "rastering_vector.h"

vector2_t vector2_get_size_from_origin_and_end(vector2_t start, vector2_t end) {
    return (vector2_t) { end.x - start.x, end.y - start.y };
}

vector3f_t vector3f_sub(vector3f_t a, vector3f_t b) {
    return (vector3f_t) { b.x - a.x, b.y - a.y, b.z - a.z };
}