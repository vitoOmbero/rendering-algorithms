#include "clipping_rectangular_window.h"

namespace ra_core::pipeline
{
ClippingRectangularWindow::ClippingRectangularWindow(
    const ra_types::Space2i&                spaceRef,
    ra_core::rendering2d::ClippingAlgorithm algo)
    : space_{ spaceRef }
    , clipping_algo_enum_{ algo }
{
    ra_types::displacement1i_t minX = spaceRef.getLowestVisibleOx();
    ra_types::displacement1i_t maxX = spaceRef.getHighestVisibleOx();
    ra_types::displacement1i_t minY = spaceRef.getLowestVisibleOy();
    ra_types::displacement1i_t maxY = spaceRef.getHighestVisibleOy();
    max_X_max_Y_                    = { maxX, maxY };
    max_X_min_Y_                    = { maxX, minY };
    min_X_max_Y_                    = { minX, maxY };
    min_X_min_Y_                    = { minX, minY };
}

ra_core::rendering2d::ClippingAlgorithm
ClippingRectangularWindow::getClippingAlgo() const
{
    return clipping_algo_enum_;
}

ra_types::Point2i ClippingRectangularWindow::getMax_X_max_Y() const
{
    return max_X_max_Y_;
}

ra_types::Point2i ClippingRectangularWindow::getMin_X_min_Y() const
{
    return min_X_min_Y_;
}

const ra_types::Space2i &ClippingRectangularWindow::getSpaceRef() const
{
    return space_;
}

} // namespace ra_core::canvas2d
