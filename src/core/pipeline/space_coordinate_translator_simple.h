#ifndef SIMPLESPACECOORDINATETRANSLATOR_H
#define SIMPLESPACECOORDINATETRANSLATOR_H

#include "ra_types.h"

namespace ra_core::pipeline
{

/**
 * @brief The SpaceCoordinateTranslatorSimple class - provides cross coordinate
 * system translation
 * @details Canvas system has offset relative to world system. Buffers' systems
 * have offset relative to Canvas coordinate system.
 */
class SpaceCoordinateTranslatorSimple
{
public:
    SpaceCoordinateTranslatorSimple();

    [[nodiscard]] const ra_types::Space2i& getPixelBuffer2dSpace() const;

    [[nodiscard]] const ra_types::Space1i& getDotBuffer1dSpace() const;

    [[nodiscard]] const ra_types::Space2i& getCanvas2dSpace() const;

    [[nodiscard]] const ra_types::Space2i& getClippingWindow2dSpace() const;

    void setClippingWindow2dSpace(const ra_types::Space2i& value);

    void setClippingWindowsOffset(ra_types::displacement2i newOffset);

    /**
     * @brief modClipwinSize - size modification for always centered clipping
     * window
     * @param half_width_modification - linear displacement for left and right
     * sides
     * @param half_height_modification - linear displacement for top and bottom
     * sides
     */
    void modClippingWindowSize(ra_types::displacement1i_t half_width_modification,
                               ra_types::displacement1i_t half_height_modification);

    /**
     * @brief TranslateWorldToCanvas - cross coordinate system translation
     * @param p - reference to value to be translated
     */
    void TranslateWorldToCanvas(ra_types::Point2i& p) const;

    [[nodiscard]] ra_types::displacement1i_t TranslateCanvasToDotBuffer(
        const ra_types::Point2i& p, ra_types::n0_t line_width) const;

    [[nodiscard]] ra_types::Point2i TranslateDotBufferToCanvas(
        ra_types::displacement1i_t point1d,
        ra_types::n0_t                   line_width) const;

    [[nodiscard]] ra_types::Point2i TranslateCanvasToPixelBuffer(
        const ra_types::Point2i& p) const;

private:
    ra_types::Space2i canvas2d_space_;
    ra_types::Space2i clipwin2d_space_;
    ra_types::Space1i dot_buffer1d_space_;
    ra_types::Space2i pixel_buffer2d_space_;
};

} // namespace ra_core::pipeline

#endif // SIMPLESPACECOORDINATETRANSLATOR_H
