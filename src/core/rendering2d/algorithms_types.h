#ifndef ALGORITHMS_TYPES_H
#define ALGORITHMS_TYPES_H

#include "array"

#include "RenderingTargetBase.h"
#include "point2i.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d
{

typedef ra_types::n0_t (*rendering_dot_fptr)(
    ra_types::displacement1i_t x, ra_types::displacement1i_t y,
    ra_types::rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& target);

typedef ra_types::n0_t (*rendering_line_segment_fptr)(
    ra_types::point2i first, ra_types::point2i second,
    ra_types::rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& target);

typedef ra_types::n0_t (*rendering_circle_fptr)(
    ra_types::point2i center, ra_types::distance1ui_t radius,
    ra_types::rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& target);

// TODO: add into type ptr to line algorithm
typedef ra_types::n0_t (*filling_triangle_fptr)(
    ra_types::point2i first, ra_types::point2i second, ra_types::point2i third,
    ra_types::rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& target);

typedef std::array<ra_types::point2i, 2> (*clipping_line_fptr)(
    ra_types::point2i first, ra_types::point2i second,
    ra_types::point2i rectwindow_maxX_maxY,
    ra_types::point2i rectwindow_minX_minY);

} // namespace ra_core::rendering2d

#endif // ALGORITHMS_TYPES_H
