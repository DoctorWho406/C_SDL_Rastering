#include "rastering_scanline_raster.h"
#include "rastering_math.h"

void _vertex_sort_by_y(vertex_t **v1, vertex_t **v2, vertex_t **v3) {
    vertex_t *temp;
    if ((*v1)->screen_position->y > (*v2)->screen_position->y) {
        temp = *v1;
        *v1 = *v2;
        *v2 = temp;
    }

    if ((*v2)->screen_position->y > (*v3)->screen_position->y) {
        temp = *v2;
        *v2 = *v3;
        *v3 = temp;
    }

    if ((*v1)->screen_position->y > (*v2)->screen_position->y) {
        temp = *v1;
        *v1 = *v2;
        *v2 = temp;
    }
}

void _interpolate_row(vgpu_t *vgpu, int y, vertex_t *left_edge_v1, vertex_t *left_edge_v2, vertex_t *right_edge_v1, vertex_t *right_edge_v2) {
    float left_gradient_y = 1.f;
    if (left_edge_v1->screen_position->y != left_edge_v2->screen_position->y) {
        left_gradient_y = (float)(y - left_edge_v1->screen_position->y) / (float)(left_edge_v2->screen_position->y - left_edge_v1->screen_position->y);
    }

    float right_gradient_y = 1.f;
    if (right_edge_v1->screen_position->y != right_edge_v2->screen_position->y) {
        right_gradient_y = (float)(y - right_edge_v1->screen_position->y) / (float)(right_edge_v2->screen_position->y - right_edge_v1->screen_position->y);
    }

    int left_x = (int)interpolate_scalar((float)left_edge_v1->screen_position->x, (float)left_edge_v2->screen_position->x, left_gradient_y);
    int right_x = (int)interpolate_scalar((float)right_edge_v1->screen_position->x, (float)right_edge_v2->screen_position->x, right_gradient_y);

    float left_z = interpolate_scalar((float)left_edge_v1->z_position, (float)left_edge_v2->z_position, left_gradient_y);
    float right_z = interpolate_scalar((float)right_edge_v1->z_position, (float)right_edge_v2->z_position, right_gradient_y);

    color_t left_color;
    color_t right_color;
    vector2f_t left_uv_cordinate;
    vector2f_t right_uv_cordinate;
    if (vgpu->flags & VGPU_FLAG_COLOR) {
        left_color = color_interpolate(left_edge_v1->color, left_edge_v2->color, left_gradient_y);
        right_color = color_interpolate(right_edge_v1->color, right_edge_v2->color, right_gradient_y);
    } else if (vgpu->flags & VGPU_FLAG_TEXTURE) {
        left_uv_cordinate = vector2f_interpolate(left_edge_v1->uv_coordinates, left_edge_v2->uv_coordinates, left_gradient_y);
        right_uv_cordinate = vector2f_interpolate(right_edge_v1->uv_coordinates, right_edge_v2->uv_coordinates, left_gradient_y);
    }


    vector2_t pixel;
    color_t color;
    float gradient_x;
    float z_position;
    vector2f_t uv_coordinate;
    int texture_x;
    int texture_y;
    int texture_index;
    for (int x = left_x; x <= right_x; ++x) {
        gradient_x = 1;
        if (left_x != right_x) {
            gradient_x = (x - left_x) / (right_x - left_x);
        }
        z_position = interpolate_scalar(left_z, right_z, gradient_x);

        if (vgpu->flags & VGPU_FLAG_COLOR) {
            color = color_interpolate(&left_color, &right_color, gradient_x);
        } else if (vgpu->flags & VGPU_FLAG_TEXTURE) {
            uv_coordinate = vector2f_interpolate(&left_uv_cordinate, &right_uv_cordinate, gradient_x);
            texture_x = (int)((float)vgpu->texture->width * uv_coordinate.x);
            texture_y = (int)((float)vgpu->texture->heigth * (1 - uv_coordinate.y));
            texture_index = (texture_y * vgpu->texture->heigth + texture_x) * vgpu->texture->pixel_size;
            color.r = vgpu->texture->data[texture_index + 0];
            color.g = vgpu->texture->data[texture_index + 1];
            color.b = vgpu->texture->data[texture_index + 2];
            color.a = vgpu->texture->data[texture_index + 3];
        }
        pixel = (vector2_t){x, y};
        screen_put_pixel(vgpu->screen, &pixel, z_position, &color);
    }
}

void scanline_raster(vgpu_t *vgpu, vertex_t *v1, vertex_t *v2, vertex_t *v3) {
    _vertex_sort_by_y(&v1, &v2, &v3);

    float inv_slope_p1p2 = (float)(v2->screen_position->x - v1->screen_position->x) / (float)(v2->screen_position->y - v1->screen_position->y);
    float inv_slope_p1p3 = (float)(v3->screen_position->x - v1->screen_position->x) / (float)(v3->screen_position->y - v1->screen_position->y);

    // <|
    if (inv_slope_p1p2 < inv_slope_p1p3) {
        for (int y = v1->screen_position->y; y <= v3->screen_position->y; ++y) {
            if (y < v2->screen_position->y) {
                //phase1: upper triangle: left: p1p2 right p1p3
                _interpolate_row(vgpu, y, v1, v2, v1, v3);
            } else {
                //phase2: lower triangle: left: p2p3 right p1p3
                _interpolate_row(vgpu, y, v2, v3, v1, v3);
            }
        }
    } else // |>
    {
        for (int y = v1->screen_position->y; y <= v3->screen_position->y; ++y) {
            if (y < v2->screen_position->y) {
                //phase1: upper triangle: left: p1p3 right p1p2
                _interpolate_row(vgpu, y, v1, v3, v1, v2);
            } else {
                //phase2: lower triangle: left: p1p3 right p2p3
                _interpolate_row(vgpu, y, v1, v3, v2, v3);
            }
        }
    }
}