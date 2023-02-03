#include "vector.h"

vector3f_t vector3f_sub(vector3f_t v1, vector3f_t v2) 
{
    vector3f_t r;
    r.x = v1.x - v2.x;
    r.y = v1.y - v2.y;
    r.z = v1.z - v2.z;
    return r;
}