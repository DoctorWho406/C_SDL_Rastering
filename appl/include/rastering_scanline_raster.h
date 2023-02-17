#ifndef __RASTERING_SCANLINE_RASTER_H
#define __RASTERING_SCANLINE_RASTER_H

#include "rastering_screen.h"
#include "rastering_vector.h"
#include "rastering_color.h"
#include "rastering_vgpu.h"

typedef struct vertex {
    vector2_t* screen_position;
    color_t* color;
    float z_position;
    vector2f_t* uv_coordinates;
} vertex_t;

void scanline_raster(vgpu_t *, vertex_t *, vertex_t *, vertex_t *);

#endif //__RASTERING_SCANLINE_RASTER_H
