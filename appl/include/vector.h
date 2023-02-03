#pragma once

typedef struct {
    int x;
    int y;
} vector2_t;

typedef struct {
    float x;
    float y;
    float z;
} vector3f_t;

vector3f_t vector3f_sub(vector3f_t v1, vector3f_t v2);