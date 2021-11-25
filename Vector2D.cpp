#include <iostream>
#include "Vector2D.h"
using namespace std;


Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::~Vector2D() {}

Vector2D::Vector2D(double in_x, double in_y) : x(in_x), y(in_y) {}

Vector2D operator*(const Vector2D &v1, const double d)
{
    Vector2D v;
    v.x = v1.x * d;
    v.y = v1.y * d;
    return v;
}

Vector2D operator/(const Vector2D &v1, const double d)
{
    if (d == 0)
    {
        return v1;
    }
    else
    {
        Vector2D v;    
        v.x = v1.x / d;
        v.y = v1.y / d;
        return v;
    }
}

ostream& operator<<(ostream& os, const Vector2D &v1)
{
    os << "<" << v1.x << ", " << v1.y << ">";
    return os;
}