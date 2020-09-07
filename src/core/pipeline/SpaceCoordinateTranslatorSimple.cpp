#include "SpaceCoordinateTranslatorSimple.h"

#include "renderer.h"

namespace ra_core::pipeline
{

SpaceCoordinateTranslatorSimple::SpaceCoordinateTranslatorSimple()
{

    auto default_2d_space =
        ra_types::Space2i{ renderer::ZERO_OFFSET, renderer::CANVAS_WIDTH_DT,
                           renderer::CANVAS_HEIGHT_DT,
                           ra_types::eDirection1d::PosInf,
                           ra_types::eDirection1d::PosInf };

    canvas2dSpace      = { default_2d_space };
    pixelBuffer2dSpace = { default_2d_space };

    clipwin2dSpace = { default_2d_space };

    // NOTE: C++20?
    /*
    dotBuffer1dSpace = { ra_types::Space1i{
        .viewLength = renderer::CANVAS_WIDTH_DT * renderer::CANVAS_HEIGHT_DT,
        .viewZeroPointOffset = 0,
        .directionOx         = ra_types::eDirection1d::PosInf } };
*/
    dotBuffer1dSpace = { ra_types::Space1i{
        renderer::CANVAS_WIDTH_DT * renderer::CANVAS_HEIGHT_DT, 0,
        ra_types::eDirection1d::PosInf } };
}

const ra_types::Space2i&
SpaceCoordinateTranslatorSimple::getPixelBuffer2dSpaceRef() const
{
    return pixelBuffer2dSpace;
}

const ra_types::Space1i&
SpaceCoordinateTranslatorSimple::getDotBuffer1dSpaceRef() const
{
    return dotBuffer1dSpace;
}

const ra_types::Space2i& SpaceCoordinateTranslatorSimple::getCanvas2dSpaceRef()
    const
{
    return canvas2dSpace;
}

const ra_types::Space2i& SpaceCoordinateTranslatorSimple::getClipwin2dSpaceRef()
    const
{
    return clipwin2dSpace;
}

void SpaceCoordinateTranslatorSimple::setClipwin2dSpace(
    const ra_types::Space2i& value)
{
    clipwin2dSpace = value;
}

void SpaceCoordinateTranslatorSimple::setClipwinOffset(
    ra_types::displacement2i newOffset)
{
    clipwin2dSpace.viewZeroPointOffset = newOffset;
}

void SpaceCoordinateTranslatorSimple::modClipwinSize(
    ra_types::displacement1i_t halfWidthMod,
    ra_types::displacement1i_t halfHeightMod)
{
    clipwin2dSpace.viewWidth  = clipwin2dSpace.viewWidth + 2 * halfWidthMod;
    clipwin2dSpace.viewHeight = clipwin2dSpace.viewHeight + 2 * halfHeightMod;
}

ra_types::displacement1i_t
SpaceCoordinateTranslatorSimple::TranslateCanvasToDotBuffer(
    const ra_types::point2i& p, ra_types::n0_t line_width) const
{
    // NOTE: currently ignores axes directions
    auto y_1d   = p.y * line_width;
    auto xny_1d = p.x + y_1d;

    // cutting

    if (dotBuffer1dSpace.directionOx == ra_types::eDirection1d::PosInf)
    {
        if (xny_1d > dotBuffer1dSpace.getHighestVisiblePoint())
            xny_1d = dotBuffer1dSpace.getHighestVisiblePoint();
        // you shall not pass!!!
        else if (xny_1d < dotBuffer1dSpace.getLowestVisiblePoint())
            xny_1d = dotBuffer1dSpace.getLowestVisiblePoint();
    }
    else
    {
        if (xny_1d < dotBuffer1dSpace.getHighestVisiblePoint())
            xny_1d = dotBuffer1dSpace.getHighestVisiblePoint();
        // you shall not pass!!!
        else if (xny_1d > dotBuffer1dSpace.getLowestVisiblePoint())
            xny_1d = dotBuffer1dSpace.getLowestVisiblePoint();
    }

    return xny_1d;
}

ra_types::point2i SpaceCoordinateTranslatorSimple::TranslateDotBufferToCanvas(
    const ra_types::displacement1i_t point1d, ra_types::n0_t line_width) const
{
    // NOTE: ignores axes directions and cutting
    auto y = point1d / line_width;
    auto x = point1d % line_width;
    return ra_types::point2i{ x, y };
}

ra_types::point2i SpaceCoordinateTranslatorSimple::TranslateCanvasToPixelBuffer(
    const ra_types::point2i& p) const
{
    auto result = p + pixelBuffer2dSpace.viewZeroPointOffset;

    // cutting
    // NOTE: currently ignores axes directions

    if (result.x < 0)
        result.x = 0;
    if (result.y < 0)
        result.y = 0;
    if (result.x > pixelBuffer2dSpace.viewWidth - 1)
        result.x = pixelBuffer2dSpace.viewWidth - 1;
    if (result.y > pixelBuffer2dSpace.viewHeight - 1)
        result.y = pixelBuffer2dSpace.viewHeight - 1;

    result.x = result.x % pixelBuffer2dSpace.viewWidth;

    return result;
}

void SpaceCoordinateTranslatorSimple::TranslateWorldToCanvas(
    ra_types::point2i& p) const
{
    // NOTE: currently ignores axes directions
    p = p + canvas2dSpace.viewZeroPointOffset;
}

} // namespace ra_core::pipeline
