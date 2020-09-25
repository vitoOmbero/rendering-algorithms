#ifndef ALGORITHM_CLIPPING_COEN_SUZ_H
#define ALGORITHM_CLIPPING_COEN_SUZ_H

#include <array>

#include "point2i.h"
#include "typedefs.h"

/*
 * 10:01 | 10:00 | 10:10
 * ---------------------
 * 00:01 | 00:00 | 00:10
 * ---------------------
 * 01:01 | 01:00 | 01:10
 *
 * code bits: UD:RL
 */

namespace ra_core::rendering2d::clipping
{
/**
 * @brief clipping_cohen_sutherland - naive plain realization
 * @param first - point in the cartesian2d coordinates
 * @param second
 * @param rectwindow_maxX_maxY - rectangular window coordinates in canvas2d
 * @param rectwindow_minX_minY
 * @return
 */
std::array<ra_types::Point2i, 2> clipping_cohen_sutherland_int(
    ra_types::Point2i first, ra_types::Point2i second,
    ra_types::Point2i rectwindow_maxX_maxY,
    ra_types::Point2i rectwindow_minX_minY);
}

#endif // ALGORITHM_CLIPPING_COEN_SUZ_H
