#ifndef __LINE_RASTER_H
#define __LINE_RASTER_H

#include "screen.h"
#include "color.h"
#include "vector.h"

void dda_line_raster(screen_t *, vector2_t p1, vector2_t p2, color_t *);

#endif //__LINE_RASTER_H