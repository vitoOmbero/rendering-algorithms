#ifndef CANVAS2D_H
#define CANVAS2D_H

#include <algorithm>

#include "ra_types.h"

#include "DEFAULT_PIPELINE_VALUES.h"
#include "pixel_buffer2d.h"

namespace ra_core::pipeline
{

/**
 * @brief The Canvas2d class - lightweight abstraction provides view on the
 * world space.
 */
class Canvas2d
{
public:
    explicit Canvas2d(const ra_types::Space2i& space)
        : space_{ space }
        , x_axis_view_{ ra_types::ViewDirection2d::kEast }
        , y_axis_view_{ ra_types::ViewDirection2d::kSouth } {};

    /**
     * @brief getHighestVisiblePoint - point with highest potential along 0x and
     * 0y in canvas coordinate system
     * @details \link Rectangular1DotBuffer::lastIndex in 1dBuffer \endlink
     * @return result is packed into 2d displacement struct
     */
    [[nodiscard]] ra_types::Point2i getHighestVisiblePoint() const
    {
        return space_.getHighestVisiblePoint();
    };

    /**
     * @brief getLowestVisiblePoint - point with lowest potential along 0x and
     * 0y in canvas coordinate system
     * @details \link Rectangular1dDotBuffer::zeroPointIndex
     * \endlink
     * @return result is packed into 2d displacement struct
     */
    [[nodiscard]] ra_types::Point2i getLowestVisiblePoint() const
    {
        return space_.getLowestVisiblePoint();
    };

    /**
     * @brief zeroPointOffset - zeroPoint is the displacement2i of cartesian
     * O(0;0) point in canvas coordinate system
     * @details zeroPointOffset is measured in canvas coordinate system. e.g.
     * (5;5) offset lifts up cartesian zero point by 5 dots along two axes.
     * This one shows 2d displacement between imaginable cartesian 2d space
     * and 2d canvas space as canvas have its own coordinate system with
     * non-negative numbers (Q1 only). \link
     * Rectangular1dDotBuffer::zeroPointIndex in 1dBuffer \endlink
     * @return result is packed into 2d displacement struct
     */
    [[nodiscard]] ra_types::displacement2i getZeroPointOffset() const
    {
        return space_.viewZeroPointOffset;
    };

    /**
     * @brief  - get immutable image
     * @return std::array of rgb888
     */
    [[nodiscard]] ra_types::ImageRgb888Const<
        ra_core::renderer::CANVAS_WIDTH_PX *
        ra_core::renderer::CANVAS_HEIGHT_PX>
    getImage() const
    {
        return image_;
    };

    void ImagePixelBuffer2d(const ra_core::pipeline::PixelBuffer2d& pixbuf)
    {
        // NOTE: currently ignoring directions

        auto copy = pixbuf.CreateCopy();
        auto pixv = *copy;

        std::move(pixv.begin(), pixv.end(), image_.begin());
        pixv.erase(pixv.begin(), pixv.end());
    }

    [[nodiscard]] ra_types::ViewDirection2d getXAxisView() const
    {
        return x_axis_view_;
    }

    [[nodiscard]] ra_types::ViewDirection2d getYAxisView() const
    {
        return y_axis_view_;
    }

private:
    const ra_types::Space2i&  space_;
    ra_types::ViewDirection2d x_axis_view_;
    ra_types::ViewDirection2d y_axis_view_;
    ra_types::ImageRgb888Const<ra_core::renderer::CANVAS_WIDTH_PX *
                               ra_core::renderer::CANVAS_HEIGHT_PX>
        image_;
};

} // namespace ra_core::pipeline
#endif // CANVAS2D_H
