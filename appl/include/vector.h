#ifndef __VECTOR_H
#define __VECTOR_H

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
    int x;
} vector3_t; 

typedef struct vector3f {
    float x;
    float y;
    float z;
} vector3f_t; 

vector2_t vector_get_size_from_origin_and_end(vector2_t origin, vector2_t end);

#endif //__VECTOR_H