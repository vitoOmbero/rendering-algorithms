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
    ClippingRectangularWindow(
        const ra_types::Space2i&                 spaceRef,
        ra_core::rendering2d::clipping_algorithm algo_ptr);

    ra_core::rendering2d::clipping_algorithm getClippingAlgo_ptr() const;

    ra_types::point2i getMax_X_max_Y() const;

    ra_types::point2i getMin_X_min_Y() const;

    const ra_types::Space2i& getSpaceRef() const;

private:
    const ra_types::Space2i&                 spaceRef;
    ra_types::point2i                  max_X_max_Y;
    ra_types::point2i                  max_X_min_Y;
    ra_types::point2i                  min_X_max_Y;
    ra_types::point2i                  min_X_min_Y;
    ra_core::rendering2d::clipping_algorithm clipping_algo_ptr;
};
} // namespace ra_core::canvas2d
#endif // RECTANGULARCLIPPINGWINDOW_H
