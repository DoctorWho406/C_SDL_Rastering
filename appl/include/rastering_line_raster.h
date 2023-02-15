#ifndef __LINE_RASTER_H
#define __LINE_RASTER_H

#include "rastering_screen.h"
#include "rastering_color.h"
#include "rastering_vector.h"

void dda_line_raster(screen_t *, vector2_t* p1, vector2_t* p2, color_t *);

#endif //__LINE_RASTER_H