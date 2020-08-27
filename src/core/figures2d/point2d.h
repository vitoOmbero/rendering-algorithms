#ifndef POINT2D_H
#define POINT2D_H
#include "Axes.h"
#include "Directions.h"
#include "displacement2d.h"
#include "typedefs.h"

namespace ra_core::figures2d
{
struct point2d final
{
    ra_types::displacement_t x;
    ra_types::displacement_t y;

    point2d operator-(const point2d& b) const { return { x - b.x, y - b.y }; };

    bool operator==(const point2d& b) const { return x == b.x & y == b.y; };

    bool operator!=(const point2d& b) const { return x != b.x && y != b.y; };

    bool operator<(const point2d& b) const { return x < b.x || y < b.y; };

    bool operator>(const point2d& b) const { return x > b.x || y > b.y; };

    bool operator<=(const point2d& b) const { return *this < b || *this == b; };

    bool operator>=(const point2d& b) const { return *this > b || *this == b; };

    point2d operator+(const ra_types::displacement2d& d2d) const
    {
        return { x + d2d.x, y + d2d.y };
    };

    point2d operator-(const ra_types::displacement2d& d2d) const
    {
        return { x - d2d.x, y - d2d.y };
    };

    point2d operator+(const ra_types::displacement_t& d1d) const
    {
        return { x + d1d, y + d1d };
    };

    point2d operator-(const ra_types::displacement_t& d1d) const
    {
        return { x - d1d, y - d1d };
    };
};
} // namespace ra_core::figures2d
#endif // POINT2D_H
