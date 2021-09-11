#include "hdr/coordinate_system.h"

CoordinateSystem::CoordinateSystem(int x, int y, int width, int height, 
                                   Vector min_coord, Vector max_coord) :
    area_({x, y, width, height}), min_coord_(min_coord), max_coord_(max_coord) 
{
    x_scale_ = width  / (max_coord_.x() - min_coord_.x());
    y_scale_ = height / (max_coord_.y()- min_coord_.y());

    abs_origin_point_ = { (int)(x_scale_ * abs(min_coord_.x())) + area_.x, 
                          (int)(y_scale_ * abs(max_coord_.y())) + area_.y };

}

Rectangle CoordinateSystem::area() const { return area_; };
PixelPoint CoordinateSystem::abs_origin_point() const { return abs_origin_point_; };
Vector CoordinateSystem::min_coord() const { return min_coord_; };
Vector CoordinateSystem::max_coord() const { return max_coord_; };
int CoordinateSystem::x_scale() { return x_scale_; };
int CoordinateSystem::y_scale() { return y_scale_; };

CoordinateSystem::CoordinateSystem(int x, int y, int width, int height, 
                                   int x_min, int y_min, int x_max, int y_max) :
    area_({x, y, width, height}), min_coord_(Vector(x_min, y_min)), max_coord_(Vector(x_max, y_max)) 
{
    x_scale_ = width  / (max_coord_.x() - min_coord_.x());
    y_scale_ = height / (max_coord_.y()- min_coord_.y());

    abs_origin_point_ = { (int)(x_scale_ * abs(min_coord_.x())) + area_.x, 
                          (int)(y_scale_ * abs(max_coord_.y())) + area_.y };
}


PixelPoint CoordinateSystem::getAbsCoordinatesFromRelative(Vector& rel_point) const
{
    return { (int)(rel_point.x()  * x_scale_) + abs_origin_point_.x,  
             (int)(-rel_point.y() * y_scale_) + abs_origin_point_.y};
}

Vector CoordinateSystem::getRelativeCoordinatesFromAbs(PixelPoint abs_point) const
{
    return Vector((abs_point.x  - abs_origin_point_.x) / x_scale_, 
                  (-abs_point.y + abs_origin_point_.y) / y_scale_);
}

bool CoordinateSystem::isWithinCoordSystem(PixelPoint point) const
{
    return area_.x <= point.x && (area_.x + area_.width) >= point.x &&
           area_.y <= point.y && (area_.y + area_.height) >= point.y;
}

bool CoordinateSystem::isWithinCoordSystem(Vector point) const
{
    return isWithinCoordSystem(getAbsCoordinatesFromRelative(point));
}