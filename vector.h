#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

struct vec2
{
    double x;
    double y;

    vec2(double x=0, double y=0, double length=0, double angle=0) : x(x), y(y)
    {
        if (length != 0)
            set_length(length);
        if (angle != 0)
            set_angle(angle);
    }

    double get_length() const { return sqrt((x * x) + (y * y)); }
    double get_angle() const { return atan2(y, x); }
    void set_length(const double length)
    {
        double angle = get_angle();
        x = cos(angle) * length;
        y = sin(angle) * length;
    }
    void set_angle(const double angle)
    {
        double length = get_length();
        x = cos(angle) * length;
        y = sin(angle) * length;
    }
    double distance(const vec2& v) const
    {
        return sqrt(pow(v.x - x, 2) + pow(v.y - y, 2));
    }

    vec2 operator+(const vec2& v) const
    {
        return vec2(x + v.x, y + v.y);
    }
    void operator+=(const vec2& v)
    {
        x += v.x;
        y += v.y;
    }
    vec2 operator-(const vec2& v) const
    {
        return vec2(x - v.x, y - v.y);
    }
    vec2 operator*(const double v) const
    {
        return vec2(x * v, y * v);
    }
    vec2 operator/(const double v) const
    {
        return vec2(x / v, y / v);
    }
};

#endif  // VECTOR_H
