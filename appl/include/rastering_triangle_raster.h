#ifndef __RASTERING_TRIANGLE_RASTER_H
#define __RASTERING_TRIANGLE_RASTER_H

#include <stdbool.h>

#include "rastering_screen.h"
#include "rastering_vector.h"
#include "rastering_color.h"

void bbox_triangle_raster(screen_t*, vector2_t p1, vector2_t p2, vector2_t p3, color_t *);

bool bbox_is_point_in_tirangle(vector2_t point, vector2_t p1, vector2_t p2, vector2_t p3);
 
#endif //__RASTERING_TRIANGLE_RASTER_H