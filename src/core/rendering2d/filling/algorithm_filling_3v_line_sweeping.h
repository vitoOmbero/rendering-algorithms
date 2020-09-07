#ifndef ALGORTITHMS_FILLING_3V_LINE_SWEEPING_H
#define ALGORTITHMS_FILLING_3V_LINE_SWEEPING_H

#include "RenderingTargetBase.h"
#include "point2i.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::rendering2d::filling
{

ra_types::n0_t fill3_line_sweeping_phase01_sides(
    ra_types::point2i first, ra_types::point2i second, ra_types::point2i third,
    ra_types::rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& dotbuf);

ra_types::n0_t fill3_line_sweeping_phase02_sides(
    ra_types::point2i first, ra_types::point2i second, ra_types::point2i third,
    ra_types::rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& dotbuf);

ra_types::n0_t fill3_line_sweeping(
    ra_types::point2i first, ra_types::point2i second, ra_types::point2i third,
    ra_types::rgb888                        color_code,
    ra_core::pipeline::RenderingTargetBase& dotbuf);

} // namespace ra_core::rendering2d::filling

#endif // ALGORTITHMS_FILLING_3V_LINE_SWEEPING_H
