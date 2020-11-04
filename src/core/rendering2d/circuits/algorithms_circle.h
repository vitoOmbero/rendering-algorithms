#ifndef ALGORITHMS_CIRCLE_H
#define ALGORITHMS_CIRCLE_H

#include "rendering_target_base.h"
#include "point2i.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d::circuits
{
ra_types::n0_t bresenham_int_circle(
    ra_types::Point2i center, ra_types::distance1ui_t radius,
    ra_types::Rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& dotbuf);
}

#endif // ALGORITHMS_CIRCLE_H
