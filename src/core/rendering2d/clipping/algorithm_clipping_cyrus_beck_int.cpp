#include "algorithm_clipping_cyrus_beck_int.h"

namespace ra_core::rendering2d::clipping
{
std::array<ra_types::point2i, 2> clipping_cyrus_beck_int(
    ra_types::point2i first, ra_types::point2i second,
    ra_types::point2i rectwindow_maxX_maxY,
    ra_types::point2i rectwindow_minX_minY)
{

    // TODO: implement clipping_cyrus_beck_int clipping
    first = second = rectwindow_maxX_maxY = rectwindow_minX_minY = { 0, 0 };
    // auto t_left_e = -(first.x - rectwindow_minX_minY.x) /
    return std::array<ra_types::point2i, 2>();
}
} // namespace ra_core::rendering2d::clipping
