#ifndef RECTANGULARCLIPPINGWINDOW_H
#define RECTANGULARCLIPPINGWINDOW_H

#include "algorithms_registry.h"
#include "ra_types.h"

namespace ra_core::pipeline
{
/**
 * @brief The RectangularClippingWindow class - is set in center of the
 * canvas always
 */
class ClippingRectangularWindow
{
public:
    ClippingRectangularWindow(const ra_types::Space2i&                space_,
                              ra_core::rendering2d::ClippingAlgorithm kAlgo);

    ra_core::rendering2d::ClippingAlgorithm getClippingAlgo() const;

    ra_types::Point2i getMax_X_max_Y() const;

    ra_types::Point2i getMin_X_min_Y() const;

    const ra_types::Space2i& getSpaceRef() const;

private:
    const ra_types::Space2i&                space_;
    ra_types::Point2i                       max_X_max_Y_;
    ra_types::Point2i                       max_X_min_Y_;
    ra_types::Point2i                       min_X_max_Y_;
    ra_types::Point2i                       min_X_min_Y_;
    ra_core::rendering2d::ClippingAlgorithm clipping_algo_enum_;
};
} // namespace ra_core::canvas2d
#endif // RECTANGULARCLIPPINGWINDOW_H
