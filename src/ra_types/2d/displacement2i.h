#ifndef POINT_H
#define POINT_H

#include "typedefs.h"

namespace ra_types
{

struct displacement2i final
{
    displacement1i_t x;
    displacement1i_t y;

    displacement2i operator-(const displacement2i& b) const
    {
        return { x - b.x, y - b.y };
    };

    bool operator==(const displacement2i& b) const
    {
        return x == b.x & y == b.y;
    };

    bool operator!=(const displacement2i& b) const
    {
        return x != b.x && y != b.y;
    };

    /**
     * @brief operator < - comparison of the potential by both 0x, 0y
     * @param b
     * @return
     */
    bool operator<(const displacement2i& b) const
    {
        return x < b.x || y < b.y;
    };

    bool operator>(const displacement2i& b) const
    {
        return x > b.x || y > b.y;
    };

    bool operator<=(const displacement2i& b) const
    {
        return *this < b || *this == b;
    };

    bool operator>=(const displacement2i& b) const
    {
        return *this > b || *this == b;
    };
};

} // namespace ra_types
#endif // POINT_H
