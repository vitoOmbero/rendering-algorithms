#ifndef POINT2D_H
#define POINT2D_H
#include <cmath>

#include "Axes.h"
#include "ViewDirection2d.h"
#include "displacement2i.h"
#include "typedefs.h"

namespace ra_types
{

struct point2i final
{
    ra_types::displacement1i_t x;
    ra_types::displacement1i_t y;

    point2i operator-(const point2i& b) const { return { x - b.x, y - b.y }; };

    bool operator==(const point2i& b) const { return x == b.x & y == b.y; };

    bool operator!=(const point2i& b) const { return x != b.x && y != b.y; };

    bool operator<(const point2i& b) const { return x < b.x || y < b.y; };

    bool operator>(const point2i& b) const { return x > b.x || y > b.y; };

    bool operator<=(const point2i& b) const { return *this < b || *this == b; };

    bool operator>=(const point2i& b) const { return *this > b || *this == b; };

    point2i operator+(const ra_types::displacement2i& d2d) const
    {
        return { x + d2d.x, y + d2d.y };
    };

    point2i operator-(const ra_types::displacement2i& d2d) const
    {
        return { x - d2d.x, y - d2d.y };
    };

    point2i operator+(const ra_types::displacement1i_t& d1d) const
    {
        return { x + d1d, y + d1d };
    };

    point2i operator-(const ra_types::displacement1i_t& d1d) const
    {
        return { x - d1d, y - d1d };
    };

    point2i operator+(const point2i& p) const { return { x + p.x, y + p.y }; };

    point2i operator*(float val) const
    {
        point2i p;
        p.x = std::round(static_cast<double>(x) * val);
        p.y = std::round(static_cast<double>(y) * val);
        return p;
    };

    point2i operator/(std::size_t num) const
    {
        return { std::lrint((float)this->x / num),
                 std::lrint((float)this->y / num) };
    }
};

inline ra_types::displacement2i make_displacement2d(const point2i p)
{
    return { p.x, p.y };
};

inline point2i make_point2d(const ra_types::displacement2i p)
{
    return { p.x, p.y };
};
} // namespace ra_types

#endif // POINT2D_H
