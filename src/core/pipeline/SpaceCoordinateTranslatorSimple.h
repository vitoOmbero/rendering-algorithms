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

    const ra_types::Space2i& getPixelBuffer2dSpaceRef() const;

    const ra_types::Space1i& getDotBuffer1dSpaceRef() const;

    const ra_types::Space2i& getCanvas2dSpaceRef() const;

    const ra_types::Space2i& getClipwin2dSpaceRef() const;

    void setClipwin2dSpace(const ra_types::Space2i& value);

    void setClipwinOffset(ra_types::displacement2i newOffset);

    /**
     * @brief modClipwinSize - size modification for always centered clipping
     * window
     * @param halfWidthMod - linear displacement for left and right sides
     * @param halfHeightMod - linear displacement for top and bottom sides
     */
    void modClipwinSize(ra_types::displacement1i_t halfWidthMod,
                        ra_types::displacement1i_t halfHeightMod);

    /**
     * @brief TranslateWorldToCanvas - cross coordinate system translation
     * @param p - reference to value to be translated
     */
    void TranslateWorldToCanvas(ra_types::point2i& p) const;

    ra_types::displacement1i_t TranslateCanvasToDotBuffer(
        const ra_types::point2i& p, ra_types::n0_t line_width) const;

    ra_types::point2i TranslateDotBufferToCanvas(
        const ra_types::displacement1i_t point1d,
        ra_types::n0_t                   line_width) const;

    ra_types::point2i TranslateCanvasToPixelBuffer(
        const ra_types::point2i& p) const;

private:
    ra_types::Space2i canvas2dSpace;
    ra_types::Space2i clipwin2dSpace;
    ra_types::Space1i dotBuffer1dSpace;
    ra_types::Space2i pixelBuffer2dSpace;
};

} // namespace ra_core::pipeline

#endif // SIMPLESPACECOORDINATETRANSLATOR_H
