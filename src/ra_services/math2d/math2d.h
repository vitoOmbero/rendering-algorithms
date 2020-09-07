#ifndef MATH2D_H
#define MATH2D_H

#include <cmath>

#include "point2i.h"
#include "typedefs.h"

namespace ra_services::math2d
{

ra_types::distance1ui_t calc_distance(ra_types::point2i from,
                                     ra_types::point2i to)
{
    auto value = sqrt(pow((from.x - to.x), 2) + pow((from.y - to.y), 2));
    return value;
}

} // namespace ra_services::math2d

#endif // MATH2D_H
