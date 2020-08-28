#ifndef ALGORITHMS_FILLING_NAIVE_H
#define ALGORITHMS_FILLING_NAIVE_H
#include "Rectangular1dDotBuffer.h"
#include "point2d.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d::filling
{

ra_types::n0_t fill3_naive_hr(
    ra_core::figures2d::point2d first, ra_core::figures2d::point2d second,
    ra_core::figures2d::point2d third, ra_types::rgb888 color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);
}
#endif // ALGORITHMS_FILLING_NAIVE_H
