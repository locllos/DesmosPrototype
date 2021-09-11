#include "hdr/vector.h"

Vector::Vector() : x_(0), y_(0), length_(0), angle_(0) {};

Vector::Vector(double x_component, double y_component) : x_(x_component), y_(y_component)
{
    length_ = sqrt(x_ * x_ + y_ * y_);
    angle_ = acos(x_ / length_);
}

Vector::Vector(const Vector& copy_vector) : x_(copy_vector.x_),
                                            y_(copy_vector.y_),
                                            length_(copy_vector.length_),
                                            angle_(copy_vector.angle_) {}

double Vector::x() const { return x_; }
double Vector::y() const { return y_; }
double Vector::length() const { return length_; }
double Vector::angle() const { return angle_; }

void Vector::xy(double x, double y)
{
    x_ = x;
    y_ = y;

    length_ = sqrt(x_ * x_ + y_ * y_);
    angle_ = acos(x_ / length_);
}

void Vector::x(double x)
{   
    xy(x, y_);
}

void Vector::y(double y)
{   
    xy(x_, y);
}

void Vector::length(double length)
{   
    if (length < 0) return;

    length_ = length;

    x_ = length_ * cos(angle_);
    y_ = length_ * sin(angle_);
}

void Vector::angle(double angle)
{
    angle_ = angle;

    x_ = length_ * cos(angle_);
    y_ = length_ * sin(angle_);
}

Vector& Vector::operator=(const Vector& copy_vector)
{
    x_ = copy_vector.x_;
    y_ = copy_vector.y_;
    angle_ = copy_vector.angle_;
    length_ = copy_vector.length_;

    return *this;
}

bool Vector::operator==(const Vector& rhs_vector) const 
{
    return (x_ == rhs_vector.x_ && y_ == rhs_vector.y_);
}

bool Vector::operator!=(const Vector& rhs_vector) const
{
    return (!this->operator==(rhs_vector));
}

Vector& Vector::operator*=(double scalar)
{
    xy(x_ * scalar, y_ * scalar);

    return *this;
}

Vector& Vector::operator/=(double scalar)
{
    xy(x_ / scalar, y_ / scalar);

    return *this;
}

Vector& Vector::operator+=(const Vector& rhs_vector)
{
    xy(x_ + rhs_vector.x_, y_ + rhs_vector.y_);

    return *this;
}

Vector& Vector::operator-=(const Vector& rhs_vector)
{
    xy(x_ - rhs_vector.x_, y_ - rhs_vector.y_);

    return *this;
}

Vector Vector::operator+(const Vector& rhs_vector) const
{
    Vector result_vector(x_, y_);

    result_vector += rhs_vector;

    return result_vector;
}

Vector Vector::operator-(const Vector& rhs_vector) const
{
    Vector result_vector(x_, y_);

    result_vector -= rhs_vector;

    return result_vector;
}

double Vector::operator*(const Vector& rhs_vector)
{
    return (x_ * rhs_vector.x_ + y_ * rhs_vector.y_);
}

void Vector::Rotate(double rotation_angle)
{
    angle(angle_ + rotation_angle);
}

void Vector::Normalize()
{
    x_ /= length_;
    y_ /= length_;

    length_ = 1;
}

double deltaX(const Vector& vector_a, const Vector& vector_b)
{
    return (vector_a.x() - vector_b.x());
}

double deltaY(const Vector& vector_a, const Vector& vector_b)
{
    return (vector_a.y() - vector_b.y());
}

// void vectorRotate(Vector* vector, double angle)
// {
//     double sina = sin(angle);
//     double cosa = cos(angle);

//     double x_component = vector->x_component;
//     double y_component = vector->y_component;

//     vector->x_component = x_component * cosa - y_component * sina;
//     vector->y_component = x_component * sina + y_component * cosa;
// }