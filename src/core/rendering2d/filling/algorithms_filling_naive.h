#ifndef ALGORITHMS_FILLING_NAIVE_H
#define ALGORITHMS_FILLING_NAIVE_H
#include "RenderingTargetBase.h"
#include "point2i.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d::filling
{

ra_types::n0_t fill3_naive_hr(ra_types::Point2i first, ra_types::Point2i second,
                              ra_types::Point2i third,
                              ra_types::Rgb888  color_code,
                              ra_core::pipeline::RenderingTargetBase& dotbuf);
}
#endif // ALGORITHMS_FILLING_NAIVE_H
