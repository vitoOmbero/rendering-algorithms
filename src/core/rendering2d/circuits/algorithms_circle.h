#ifndef ALGORITHMS_CIRCLE_H
#define ALGORITHMS_CIRCLE_H

#include "Rectangular1dDotBuffer.h"
#include "point2d.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d::circuits
{
ra_types::n0_t bresenham_int_circle(
    ra_core::figures2d::point2d center, ra_types::distance_t radius,
    ra_types::rgb888                           color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);
}

#endif // ALGORITHMS_CIRCLE_H
