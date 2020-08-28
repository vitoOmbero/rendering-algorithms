#ifndef ALGORITHMS_TYPES_H
#define ALGORITHMS_TYPES_H

#include "Rectangular1dDotBuffer.h"
#include "point2d.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d
{

typedef ra_types::n0_t (*rendering_dot_fptr)(
    ra_types::displacement_t x, ra_types::displacement_t y,
    ra_types::rgb888                           color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);

typedef ra_types::n0_t (*rendering_line_segment_fptr)(
    ra_core::figures2d::point2d first, ra_core::figures2d::point2d second,
    ra_types::rgb888                           color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);

typedef ra_types::n0_t (*rendering_circle_fptr)(
    ra_core::figures2d::point2d center, ra_types::distance_t radius,
    ra_types::rgb888                           color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);

// TODO: add into type ptr to line algorithm
typedef ra_types::n0_t (*rendering_triangle_filling_fptr)(
    ra_core::figures2d::point2d first, ra_core::figures2d::point2d second,
    ra_core::figures2d::point2d third, ra_types::rgb888 color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);

} // namespace ra_core::rendering2d

#endif // ALGORITHMS_TYPES_H
