#ifndef __LINE_RASTER_H
#define __LINE_RASTER_H

#include "screen.h"
#include "color.h"

void dda_line_raster(screen_t *, int x1, int y1, int x2, int y2, color_t *);

#endif //__LINE_RASTER_H