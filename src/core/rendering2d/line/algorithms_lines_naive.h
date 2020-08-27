#ifndef NAIVE_H
#define NAIVE_H

#include "Rectangular1dDotBuffer.h"
#include "point2d.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d::line
{
/**
 * @brief naive_dot - simple dot rendering
 * @param x
 * @param y
 * @param color_code
 * @param[out] dotbuf - refernce to the buffer where rendering result will be
 * applied
 * @return number of dots were rendered
 */
ra_types::n0_t naive_dot(ra_types::displacement_t x, ra_types::displacement_t y,
                         ra_types::rgb888                           color_code,
                         ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);

/**
 * @brief naive_hv_line - naive rendering for line segments.
 * @details Algorithm is correct for horizontal, vertical and 45 deg diagonal
 * line segments only
 * @param first - point #1
 * @param second - point #2
 * @param color_code - color code
 * @param dotbuf - refernce to the buffer where rendering result will be
 * applied
 * @return number of dots were rendered
 */
ra_types::n0_t naive_hv_line(ra_core::figures2d::point2d first,
                             ra_core::figures2d::point2d second,
                             ra_types::rgb888            color_code,
                             ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);

} // namespace ra_core::rendering2d::line
#endif // NAIVE_H
