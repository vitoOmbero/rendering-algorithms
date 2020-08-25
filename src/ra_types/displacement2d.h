#ifndef POINT_H
#define POINT_H

#include "typedefs.h"

namespace ra_types
{

struct displacement2d
{
    displacement_t x;
    displacement_t y;

    displacement2d operator-(const displacement2d& b) const
    {
        return { x - b.x, y - b.y };
    };

    bool operator==(const displacement2d& b) const
    {
        return x == b.x & y == b.y;
    };

    bool operator!=(const displacement2d& b) const
    {
        return x != b.x && y != b.y;
    };

    bool operator<(const displacement2d& b) const
    {
        return x < b.x || y < b.y;
    };

    bool operator>(const displacement2d& b) const
    {
        return x > b.x || y > b.y;
    };

    bool operator<=(const displacement2d& b) const
    {
        return *this < b || *this == b;
    };

    bool operator>=(const displacement2d& b) const
    {
        return *this > b || *this == b;
    };
};

} // namespace ra_types
#endif // POINT_H
