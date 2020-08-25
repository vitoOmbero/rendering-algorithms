#include "algorithms_naive.h"

ra_types::n0_t ra_core::rendering2d::line::naive_dot(
    ra_types::displacement_t x, ra_types::displacement_t y,
    ra_types::rgb888                           color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf)
{
    dotbuf.Paint(color_code);
    dotbuf.Mark({ x, y });
    return 1;
}
