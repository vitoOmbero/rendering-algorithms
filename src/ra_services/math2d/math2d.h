#ifndef MATH2D_H
#define MATH2D_H

#include <cmath>

#include "point2d.h"
#include "typedefs.h"

namespace ra_services::math2d
{

ra_types::distance_t calc_distance(ra_core::figures2d::point2d from,
                                   ra_core::figures2d::point2d to)
{
    auto value = sqrt(pow((from.x - to.x), 2) + pow((from.y - to.y), 2));
    return value;
}

} // namespace ra_services::math2d

#endif // MATH2D_H
