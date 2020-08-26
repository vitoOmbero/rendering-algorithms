#ifndef POINT2D_H
#define POINT2D_H
#include "typedefs.h"
namespace ra_core::figures2d
{
struct point2d
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
};
} // namespace ra_core::figures2d
#endif // POINT2D_H
