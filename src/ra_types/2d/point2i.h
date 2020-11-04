#ifndef POINT2D_H
#define POINT2D_H
#include <cmath>

#include "axes.h"
#include "displacement2i.h"
#include "typedefs.h"
#include "view_direction2d.h"

namespace ra_types
{

struct Point2i
{
    ra_types::displacement1i_t x;
    ra_types::displacement1i_t y;

    Point2i operator-(const Point2i& b) const { return { x - b.x, y - b.y }; };

    bool operator==(const Point2i& b) const { return x == b.x && y == b.y; };

    bool operator!=(const Point2i& b) const { return x != b.x && y != b.y; };

    bool operator<(const Point2i& b) const { return x < b.x || y < b.y; };

    bool operator>(const Point2i& b) const { return x > b.x || y > b.y; };

    bool operator<=(const Point2i& b) const { return *this < b || *this == b; };

    bool operator>=(const Point2i& b) const { return *this > b || *this == b; };

    Point2i operator+(const ra_types::displacement2i& d2d) const
    {
        return { x + d2d.x, y + d2d.y };
    };

    Point2i operator-(const ra_types::displacement2i& d2d) const
    {
        return { x - d2d.x, y - d2d.y };
    };

    Point2i operator+(const ra_types::displacement1i_t& d1d) const
    {
        return { x + d1d, y + d1d };
    };

    Point2i operator-(const ra_types::displacement1i_t& d1d) const
    {
        return { x - d1d, y - d1d };
    };

    Point2i operator+(const Point2i& p) const { return { x + p.x, y + p.y }; };

    Point2i operator*(float val) const
    {
        Point2i p{};
        p.x = std::round(static_cast<double>(x) * val);
        p.y = std::round(static_cast<double>(y) * val);
        return p;
    };

    Point2i operator/(std::size_t num) const
    {
        return { std::lrint((float)this->x / num),
                 std::lrint((float)this->y / num) };
    }
};

inline ra_types::displacement2i make_displacement2d(const Point2i p)
{
    return { p.x, p.y };
}

inline Point2i make_point2d(const ra_types::displacement2i p)
{
    return { p.x, p.y };
}
} // namespace ra_types

#endif // POINT2D_H
