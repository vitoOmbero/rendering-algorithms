#ifndef ALGORTITHMS_FILLING_3V_LINE_SWEEPING_H
#define ALGORTITHMS_FILLING_3V_LINE_SWEEPING_H

#include "Rectangular1dDotBuffer.h"
#include "point2d.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d::filling
{

ra_types::n0_t fill3_line_sweeping_phase01_sides(
    ra_core::figures2d::point2d first, ra_core::figures2d::point2d second,
    ra_core::figures2d::point2d third, ra_types::rgb888 color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);

ra_types::n0_t fill3_line_sweeping_phase02_sides(
    ra_core::figures2d::point2d first, ra_core::figures2d::point2d second,
    ra_core::figures2d::point2d third, ra_types::rgb888 color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);

ra_types::n0_t fill3_line_sweeping(
    ra_core::figures2d::point2d first, ra_core::figures2d::point2d second,
    ra_core::figures2d::point2d third, ra_types::rgb888 color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf);

} // namespace ra_core::rendering2d::filling

#endif // ALGORTITHMS_FILLING_3V_LINE_SWEEPING_H
