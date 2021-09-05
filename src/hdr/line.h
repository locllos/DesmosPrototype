#include "display.h"

struct Line
{
    SDL_Point point_a;
    SDL_Point point_b;

    size_t thickness;
};