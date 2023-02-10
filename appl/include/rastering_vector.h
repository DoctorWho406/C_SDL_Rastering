#ifndef __RASTERING_VECTOR_H
#define __RASTERING_VECTOR_H

typedef struct vector2 {
    int x;
    int y;
} vector2_t;

typedef struct vector2f {
    float x;
    float y;
} vector2f_t;

typedef struct vector3 {
    int x;
    int y;
    int z;
} vector3_t;

typedef struct vector3f {
    float x;
    float y;
    float z;
} vector3f_t;

vector2_t vector2_get_size_from_origin_and_end(vector2_t origin, vector2_t end);

vector3f_t vector3f_sub(vector3f_t, vector3f_t);

#endif //__RASTERING_VECTOR_H
