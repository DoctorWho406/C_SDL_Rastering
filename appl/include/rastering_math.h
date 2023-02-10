#include "SDL.h"
#include "vector.h"

#define RASTERING_max3(x, y, z) (SDL_max(SDL_max(x, y), z))
#define RASTERING_min3(x, y, z) (SDL_min(SDL_min(x, y), z))


int det(vector2_t p, vector2_t v1, vector2_t v2);