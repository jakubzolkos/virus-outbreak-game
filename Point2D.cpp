#include <cmath>
#include <iostream>
#include "Vector2D.h"
#include "Point2D.h"
using namespace std;


Point2D::Point2D() : x(0), y(0) {}

Point2D::~Point2D() {}

Point2D::Point2D(double in_x, double in_y) : x(in_x), y(in_y) {}

double GetDistanceBetween(const Point2D &p1, const Point2D &p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

ostream& operator<<(ostream& os, const Point2D &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

Point2D operator+(const Point2D &p1, const Vector2D &v1)
{
    Point2D p;
    p.x = p1.x + v1.x;
    p.y = p1.y + v1.y;
    return p;
}


Vector2D operator-(const Point2D &p1, const Point2D &p2)
{
    Vector2D v;
    v.x = p1.x - p2.x;
    v.y = p1.y - p2.y;
    return v;
}
