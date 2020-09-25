#ifndef NAIVE_H
#define NAIVE_H

#include "RenderingTargetBase.h"
#include "point2i.h"
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
ra_types::n0_t naive_dot(ra_types::displacement1i_t              x,
                         ra_types::displacement1i_t              y,
                         ra_types::Rgb888                        color_code,
                         ra_core::pipeline::RenderingTargetBase& target);

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
ra_types::n0_t naive_hv_line(ra_types::Point2i first, ra_types::Point2i second,
                             ra_types::Rgb888                        color_code,
                             ra_core::pipeline::RenderingTargetBase& target);

} // namespace ra_core::rendering2d::line
#endif // NAIVE_H
