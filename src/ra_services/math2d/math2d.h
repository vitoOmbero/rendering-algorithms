#ifndef MATH2D_H
#define MATH2D_H

#include <cmath>

#include "point2i.h"
#include "typedefs.h"

namespace ra_services::math2d
{

inline ra_types::distance1ui_t calc_distance(ra_types::point2i from,
                                             ra_types::point2i to)
{
    auto value = sqrt(pow((from.x - to.x), 2) + pow((from.y - to.y), 2));
    return value;
}

inline ra_types::point2i calc_midddle_point(ra_types::point2i p1,
                                            ra_types::point2i p2)
{
    if (p1 < p2)
        std::swap(p1, p2);

    ra_types::point2i p;
    p.x = (float)(p1.x - p2.x) / 2 + p1.x;
    p.y = (float)(p1.y - p2.y) / 2 + p1.y;
    return p;
}

/*static*/ const float PI = 3.14159265;

inline ra_types::n0_t make_angle_degrees(float radians)
{
    return radians * 180. / PI;
}

inline float make_angle_radians(ra_types::n0_t degrees)
{
    return degrees * PI / 180.;
}

} // namespace ra_services::math2d

#endif // MATH2D_H
