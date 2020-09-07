#ifndef ALGORITHMS_LINE_CLASSIC_H
#define ALGORITHMS_LINE_CLASSIC_H

#include "RenderingTargetBase.h"
#include "point2i.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d::line
{
/**
 * @brief bresenham_defect_diag_line - relisation with defective diagonal line
 * drawing
 * @details see Minsk, BSUIR, 2002, "ISBN 985-444-" (?)
 * @param first
 * @param second
 * @param color_code
 * @param dotbuf
 * @return dots drawn number
 */
ra_types::n0_t bresenham_defect_diag_line(
    ra_types::point2i first, ra_types::point2i second,
    ra_types::rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& target);

/**
 * @brief bresenham_int_line - integer nice realisation
 * @details see
 * <https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Algorithm_for_integer_arithmetic>
 * @param first
 * @param second
 * @param color_code
 * @param dotbuf
 * @return dots drawn number
 */
ra_types::n0_t bresenham_int_line(
    ra_types::point2i first, ra_types::point2i second,
    ra_types::rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& target);
#endif // ALGORITHMS_LINE_CLASSIC_H
}
