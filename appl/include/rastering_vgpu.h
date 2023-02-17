#ifndef __RASTERING_VGPU_H
#define __RASTERING_VGPU_H

#include "rastering_scene.h"
#include "rastering_texture.h"

typedef enum {
    VGPU_FLAG_NONE = 0,
    VGPU_FLAG_COLOR = 1 << 1,
    VGPU_FLAG_TEXTURE = 1 << 2,
    VGPU_FLAG_BLENDING = 1 << 3,
} vgpu_flags_e;

typedef struct vgpu {
    screen_t* screen;
    texture_t* texture;
    unsigned int flags;
} vgpu_t;

#endif //__RASTERING_VGPU_H