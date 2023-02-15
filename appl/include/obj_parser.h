#ifndef __OBJ_PARSER_H
#define __OBJ_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct obj_parser_float3 {
    float x;
    float y;
    float z;
} obj_parser_float3_t;

typedef struct obj_parser_float2 {
    float x;
    float y;
} obj_parser_float2_t;

typedef struct obj_parser_vertex {
    obj_parser_float3_t position;
    obj_parser_float2_t uv;
    obj_parser_float3_t normal;
} obj_parser_vertex;

typedef struct obj_parser_triangle {
    obj_parser_vertex v1;
    obj_parser_vertex v2;
    obj_parser_vertex v3;
} obj_parser_triangle_t;

typedef struct obj {
    size_t vertex_count;
    size_t vertex_texture_count;
    size_t vertex_normal_count;
    size_t face_count;
    obj_parser_triangle_t *triangles;
} obj_t;

int obj_parser_parse(obj_t **, const char *obj_path);
void obj_parser_destroy(obj_t *);

#ifdef OBJ_PARSER_IMPLEMENTATION
int obj_parser_parse(obj_t **mesh, const char *obj_path) {
    int return_value = -1;
    FILE *file;
    errno_t result = fopen_s(&file, obj_path, "r");
    if (result != 0) {
        char error_buffer[94];
        strerror_s(error_buffer, 94, result);
        printf("Unable to open file\n%s", error_buffer);
        return result;
    }

    *mesh = (obj_t *)calloc(1, sizeof(obj_t));
    if (*mesh == NULL) {
        printf("Error while allocate memory for mesh\n");
        fclose(file);
        return -1;
    }

    const int buffer_size = 1024;
    char buffer[1024];

    while (fgets(buffer, buffer_size, file)) {
        if (strncmp(buffer, "v ", 2) == 0) {
            // Vertex
            (*mesh)->vertex_count++;
        }
        if (strncmp(buffer, "vt ", 3) == 0) {
            // Vertex texture
            (*mesh)->vertex_texture_count++;
        }
        if (strncmp(buffer, "vn ", 3) == 0) {
            // Vertex normal
            (*mesh)->vertex_normal_count++;
        }
        if (strncmp(buffer, "f ", 2) == 0) {
            // Face
            (*mesh)->face_count++;
        }
    }

    rewind(file);

    obj_parser_float3_t *vertexes = (obj_parser_float3_t *)malloc(sizeof(obj_parser_float3_t) * (*mesh)->vertex_count);
    if (vertexes == NULL) {
        printf("Error while allocate memory for vertexes\n");
        free(*mesh);
        fclose(file);
        return -1;
    }
    obj_parser_float2_t *vertexes_texture = (obj_parser_float2_t *)malloc(sizeof(obj_parser_float2_t) * (*mesh)->vertex_texture_count);
    if (vertexes_texture == NULL) {
        printf("Error while allocate memory for vertexes\n");
        free(vertexes);
        free(*mesh);
        fclose(file);
        return -1;
    }
    obj_parser_float3_t *vertexes_normals = (obj_parser_float3_t *)malloc(sizeof(obj_parser_float3_t) * (*mesh)->vertex_normal_count);
    if (vertexes_normals == NULL) {
        printf("Error while allocate memory for vertexes\n");
        free(vertexes_texture);
        free(vertexes);
        free(*mesh);
        fclose(file);
        return -1;
    }
    int *faces = (int *)malloc(sizeof(int) * 9 * (*mesh)->face_count);
    if (faces == NULL) {
        printf("Error while allocate memory for vertexes\n");
        free(vertexes_normals);
        free(vertexes_texture);
        free(vertexes);
        free(*mesh);
        fclose(file);
        return -1;
    }

    size_t current_vertex = 0;
    size_t current_vertex_texture = 0;
    size_t current_vertex_normal = 0;
    size_t current_face = 0;
    while (fgets(buffer, buffer_size, file)) {
        char *context;
        char *token = strtok_s(buffer, " ", &context);
        if (strcmp(token, "v") == 0) {
            // Vertex
            token = strtok_s(NULL, " ", &context);
            vertexes[current_vertex].x = atof(token);
            token = strtok_s(NULL, " ", &context);
            vertexes[current_vertex].y = atof(token);
            token = strtok_s(NULL, " ", &context);
            vertexes[current_vertex].z = atof(token);
            // printf("Vertex %zu: [%f/%f/%f]\n", current_vertex, vertexes[current_vertex].x, vertexes[current_vertex].y, vertexes[current_vertex].z);

            current_vertex++;
        }
        if (strcmp(token, "vt") == 0) {
            // Vertex texture
            token = strtok_s(NULL, " ", &context);
            vertexes_texture[current_vertex_texture].x = atof(token);
            token = strtok_s(NULL, " ", &context);
            vertexes_texture[current_vertex_texture].y = atof(token);

            current_vertex_texture++;
        }
        if (strcmp(token, "vn") == 0) {
            // Vertex normal
            token = strtok_s(NULL, " ", &context);
            vertexes_normals[current_vertex_normal].x = atof(token);
            token = strtok_s(NULL, " ", &context);
            vertexes_normals[current_vertex_normal].y = atof(token);
            token = strtok_s(NULL, " ", &context);
            vertexes_normals[current_vertex_normal].z = atof(token);

            current_vertex_normal++;
        }
        if (strcmp(token, "f") == 0) {
            // Face
            int index;
            for (size_t i = 0; i < 3; ++i) {
                index = 9 * current_face + 3 * i;
                //v
                token = strtok_s(NULL, "/", &context);
                faces[index + 0] = atoi(token) - 1;
                //vt
                token = strtok_s(NULL, "/", &context);
                faces[index + 1] = atoi(token) - 1;
                //vn
                token = strtok_s(NULL, " ", &context);
                faces[index + 2] = atoi(token) - 1;
            }
            current_face++;
        }
    }

    fclose(file);

    (*mesh)->triangles = (obj_parser_triangle_t *)malloc(sizeof(obj_parser_triangle_t) * (*mesh)->face_count);
    if ((*mesh)->triangles == NULL) {
        printf("Error while allocate memory for vertexes\n");
        free(faces);
        free(vertexes_normals);
        free(vertexes_texture);
        free(vertexes);
        free(*mesh);
        return -1;
    }

    int face_index;
    for (size_t i = 0; i < (*mesh)->face_count; ++i) {
        face_index = i * 9;
        // printf("Face %zu:\n", i);
        // printf("Tuple 1 [%d/%d/%d]\n", faces[face_index + 0], faces[face_index + 1], faces[face_index + 2]);
        // printf("Tuple 2 [%d/%d/%d]\n", faces[face_index + 3], faces[face_index + 4], faces[face_index + 5]);
        // printf("Tuple 3 [%d/%d/%d]\n", faces[face_index + 6], faces[face_index + 7], faces[face_index + 8]);
        //V1
        //Position
        (*mesh)->triangles[i].v1.position = vertexes[faces[face_index + 0]];
        // printf("Vertex %d: [%f/%f/%f]\n", faces[face_index + 0], vertexes[faces[face_index + 0]].x, vertexes[faces[face_index + 0]].y, vertexes[faces[face_index + 0]].z);
        //UV
        (*mesh)->triangles[i].v1.uv = vertexes_texture[faces[face_index + 1]];
        //Normal
        (*mesh)->triangles[i].v1.normal = vertexes_normals[faces[face_index + 2]];
        //V2
        //Position
        (*mesh)->triangles[i].v2.position = vertexes[faces[face_index + 3]];
        //UV
        (*mesh)->triangles[i].v2.uv = vertexes_texture[faces[face_index + 4]];
        //Normal
        (*mesh)->triangles[i].v2.normal = vertexes_normals[faces[face_index + 5]];
        //V3
        //Position
        (*mesh)->triangles[i].v3.position = vertexes[faces[face_index + 6]];
        //UV
        (*mesh)->triangles[i].v3.uv = vertexes_texture[faces[face_index + 7]];
        //Normal
        (*mesh)->triangles[i].v3.normal = vertexes_normals[faces[face_index + 8]];
    }

    free(faces);
    free(vertexes_normals);
    free(vertexes_texture);
    free(vertexes);

    return 0;
}

void obj_parser_destroy(obj_t *mesh) {
    free(mesh->triangles);
    free(mesh);
}
#endif //OBJ_PARSER_IMPLEMENTATION

#endif //__OBJ_PARSER_H