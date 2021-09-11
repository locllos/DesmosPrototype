#pragma once

#include <math.h>

class Vector
{
private:
    
    double x_;
    double y_;

    double length_;
    double angle_;


public:

    Vector();
    Vector(double x_component, double y_component);
    Vector(const Vector& copy_vector);

    double x() const;
    double y() const;
    double length() const;
    double angle() const;

    void xy(double x, double y);
    void x(double x);
    void y(double y);
    void length(double length);
    void angle(double angle);

    Vector& operator=(const Vector& copy_vector);

    bool operator==(const Vector& rhs_vector) const;
    bool operator!=(const Vector& rhs_vector) const;

    Vector& operator*=(double scalar);
    Vector& operator/=(double scalar);

    Vector& operator+=(const Vector& rhs_vector);
    Vector& operator-=(const Vector& rhs_vector);

    Vector operator+(const Vector& lhs_vector) const;
    Vector operator-(const Vector& lhs_vector) const;

    double operator*(const Vector& rhs_vector);

    void Rotate(double angle);
    void Normalize();
    
    ~Vector() = default;
};

double deltaX(const Vector& vector_a, const Vector& vector_b);
double deltaY(const Vector& vector_a, const Vector& vector_b);