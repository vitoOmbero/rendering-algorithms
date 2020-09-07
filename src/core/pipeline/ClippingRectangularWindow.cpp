#include "ClippingRectangularWindow.h"

namespace ra_core::pipeline
{
ClippingRectangularWindow::ClippingRectangularWindow(
    const ra_types::Space2i&                 spaceRef,
    ra_core::rendering2d::clipping_algorithm algo_ptr)
    : spaceRef{ spaceRef }
    , clipping_algo_ptr{ algo_ptr }
{
    ra_types::displacement1i_t minX = spaceRef.getLowestVisibleOx();
    ra_types::displacement1i_t maxX = spaceRef.getHighestVisibleOx();
    ra_types::displacement1i_t minY = spaceRef.getLowestVisibleOy();
    ra_types::displacement1i_t maxY = spaceRef.getHighestVisibleOy();
    max_X_max_Y                   = { maxX, maxY };
    max_X_min_Y                   = { maxX, minY };
    min_X_max_Y                   = { minX, maxY };
    min_X_min_Y                   = { minX, minY };
}

ra_core::rendering2d::clipping_algorithm
ClippingRectangularWindow::getClippingAlgo_ptr() const
{
    return clipping_algo_ptr;
}

ra_types::point2i ClippingRectangularWindow::getMax_X_max_Y() const
{
    return max_X_max_Y;
}

ra_types::point2i ClippingRectangularWindow::getMin_X_min_Y() const
{
    return min_X_min_Y;
}

const ra_types::Space2i &ClippingRectangularWindow::getSpaceRef() const
{
    return spaceRef;
}

} // namespace ra_core::canvas2d
