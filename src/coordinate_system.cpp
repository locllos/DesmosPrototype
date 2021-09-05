#include "hdr/coordinate_system.h"

void constructCoordinateSystem(CoordinateSystem* coord_system, 
                               int x_pos, int y_pos, 
                               int width, int height,
                               SDL_Point origin_point,
                               SDL_Point min_coord, SDL_Point max_coord)
{
    coord_system->area.x = x_pos;
    coord_system->area.y = y_pos;

    coord_system->area.h = height;
    coord_system->area.w = width;
    
    coord_system->abs_origin_point = { origin_point.x + coord_system->area.x, 
                                       origin_point.y + coord_system->area.y };

    coord_system->min_coord = min_coord;
    coord_system->max_coord = max_coord;

    coord_system->x_scale = (max_coord.x - min_coord.x) / width;
    coord_system->y_scale = (max_coord.y - min_coord.y) / height;
}

CoordinateSystem* newCoordinateSystem(int x_pos, int y_pos, 
                                      int width, int height,
                                      SDL_Point origin_point, 
                                      SDL_Point min_coord, SDL_Point max_coord)
{
    CoordinateSystem* coord_system = (CoordinateSystem*)calloc(1, sizeof(CoordinateSystem));

    constructCoordinateSystem(coord_system, x_pos, y_pos, width, height, origin_point, min_coord, max_coord);

    return coord_system;
}

SDL_Point getAbsCoordinatesFromRelative(CoordinateSystem* coord_system, Point rel_point)
{
    return { (int)(rel_point.x  * coord_system->x_scale) + coord_system->abs_origin_point.x,  
             (int)(-rel_point.y * coord_system->y_scale) + coord_system->abs_origin_point.y};
}

Point getRelativeCoordinatesFromAbs(CoordinateSystem* coord_system, SDL_Point abs_point)
{
    return {(double)(abs_point.x  - coord_system->abs_origin_point.x) / coord_system->x_scale, 
            (double)(-abs_point.y + coord_system->abs_origin_point.y) / coord_system->y_scale};
}

Point pointAdd(Point point_a, Point point_b)
{
    return {point_a.x + point_b.x, point_a.y + point_b.y};
}

bool isEqual(SDL_Point point_a, SDL_Point point_b)
{
    return (point_a.x == point_b.x) && (point_a.y == point_b.y);
}

bool isWithinCoordSystem(CoordinateSystem* coord_system, SDL_Point point)
{
    return coord_system->area.x <= point.x && (coord_system->area.x + coord_system->area.w) >= point.x &&
           coord_system->area.y <= point.y && (coord_system->area.y + coord_system->area.h) >= point.y;
}

CoordinateSystem* deleteCoordinateSystem(CoordinateSystem* coord_system)
{
    free(coord_system);

    return nullptr;
}