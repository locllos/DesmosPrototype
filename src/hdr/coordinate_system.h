#include "display.h"

struct CoordinateSystem
{
    SDL_Rect area;
    SDL_Point abs_origin_point; // в пикселях

    SDL_Point min_coord;
    SDL_Point max_coord;

    int x_scale;                  // чем равна одна единица координат в пикселях
    int y_scale;                  // чем равна одна единица координат в пикселях
};

struct Point
{
    double x;
    double y;
};

// I know, I know, it's the same as Point, but you dont understand, it's another
struct Vector
{
    double x_component;
    double y_component;
};

void constructCoordinateSystem(CoordinateSystem* coord_system, 
                               int x_pos, int y_pos, 
                               int width, int height,
                               SDL_Point origin_point, 
                               SDL_Point min_coord, SDL_Point max_coord);
CoordinateSystem* newCoordinateSystem(int x_pos, int y_pos, 
                                      int width, int height,
                                      SDL_Point origin_point,
                                      SDL_Point min_coord, SDL_Point max_coord);
CoordinateSystem* deleteCoordinateSystem(CoordinateSystem* coord_system);

SDL_Point getAbsCoordinatesFromRelative(CoordinateSystem* coord_system, Point rel_point);

Point getRelativeCoordinatesFromAbs(CoordinateSystem* coord_system, SDL_Point abs_point);
Point pointAdd(Point point_a, Point point_b);

bool      isEqual                      (SDL_Point point_a, SDL_Point point_b);
bool      isWithinCoordSystem          (CoordinateSystem* coord_system, SDL_Point point);