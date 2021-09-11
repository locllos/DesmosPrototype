#pragma once

#include "renderer.h"
#include "vector.h"


class CoordinateSystem
{
private:
    
    Rectangle area_;
    PixelPoint abs_origin_point_;

    Vector min_coord_;
    Vector max_coord_;

    int x_scale_;
    int y_scale_;

public:

    CoordinateSystem(int x, int y, int width, int height, Vector min_coord, Vector max_coord); 
    CoordinateSystem(int x, int y, int width, int height, int x_min, int y_min, int x_max, int y_max);

    Rectangle area() const;
    PixelPoint abs_origin_point() const;
    Vector min_coord() const;
    Vector max_coord() const;
    int x_scale();
    int y_scale();

    PixelPoint getAbsCoordinatesFromRelative(Vector& rel_point) const;

    Vector getRelativeCoordinatesFromAbs(PixelPoint abs_point) const;

    bool isWithinCoordSystem(PixelPoint point) const;
    bool isWithinCoordSystem(Vector point) const;

    ~CoordinateSystem() = default;
};
