#include "SpaceCoordinateTranslatorSimple.h"

#include "renderer.h"

namespace ra_core::pipeline
{

SpaceCoordinateTranslatorSimple::SpaceCoordinateTranslatorSimple()
{

    auto default_2d_space =
        ra_types::Space2i{ renderer::ZERO_OFFSET, renderer::CANVAS_WIDTH_DT,
                           renderer::CANVAS_HEIGHT_DT,
                           ra_types::Direction1d::kPosInf,
                           ra_types::Direction1d::kPosInf };

    canvas2d_space_      = { default_2d_space };
    pixel_buffer2d_space_ = { default_2d_space };

    clipwin2d_space_ = { default_2d_space };

    // NOTE: C++20?
    /*
    dotBuffer1dSpace = { ra_types::Space1i{
        .viewLength = renderer::CANVAS_WIDTH_DT * renderer::CANVAS_HEIGHT_DT,
        .viewZeroPointOffset = 0,
        .directionOx         = ra_types::eDirection1d::PosInf } };
*/
    dot_buffer1d_space_ = { ra_types::Space1i{
        renderer::CANVAS_WIDTH_DT * renderer::CANVAS_HEIGHT_DT, 0,
        ra_types::Direction1d::kPosInf } };
}

const ra_types::Space2i&
SpaceCoordinateTranslatorSimple::getPixelBuffer2dSpaceRef() const
{
    return pixel_buffer2d_space_;
}

const ra_types::Space1i&
SpaceCoordinateTranslatorSimple::getDotBuffer1dSpaceRef() const
{
    return dot_buffer1d_space_;
}

const ra_types::Space2i& SpaceCoordinateTranslatorSimple::getCanvas2dSpaceRef()
    const
{
    return canvas2d_space_;
}

const ra_types::Space2i& SpaceCoordinateTranslatorSimple::getClipwin2dSpaceRef()
    const
{
    return clipwin2d_space_;
}

void SpaceCoordinateTranslatorSimple::setClipwin2dSpace(
    const ra_types::Space2i& value)
{
    clipwin2d_space_ = value;
}

void SpaceCoordinateTranslatorSimple::setClipwinOffset(
    ra_types::displacement2i newOffset)
{
    clipwin2d_space_.viewZeroPointOffset = newOffset;
}

void SpaceCoordinateTranslatorSimple::modClipwinSize(
    ra_types::displacement1i_t half_width_modification,
    ra_types::displacement1i_t half_height_modification)
{
    clipwin2d_space_.viewWidth =
        clipwin2d_space_.viewWidth + 2 * half_width_modification;
    clipwin2d_space_.viewHeight =
        clipwin2d_space_.viewHeight + 2 * half_height_modification;
}

ra_types::displacement1i_t
SpaceCoordinateTranslatorSimple::TranslateCanvasToDotBuffer(
    const ra_types::Point2i& p, ra_types::n0_t line_width) const
{
    // NOTE: currently ignores axes directions
    auto y_1d   = p.y * line_width;
    auto xny_1d = p.x + y_1d;

    // cutting

    if (dot_buffer1d_space_.directionOx == ra_types::Direction1d::kPosInf)
    {
        if (xny_1d > dot_buffer1d_space_.getHighestVisiblePoint())
            xny_1d = dot_buffer1d_space_.getHighestVisiblePoint();
        // you shall not pass!!!
        else if (xny_1d < dot_buffer1d_space_.getLowestVisiblePoint())
            xny_1d = dot_buffer1d_space_.getLowestVisiblePoint();
    }
    else
    {
        if (xny_1d < dot_buffer1d_space_.getHighestVisiblePoint())
            xny_1d = dot_buffer1d_space_.getHighestVisiblePoint();
        // you shall not pass!!!
        else if (xny_1d > dot_buffer1d_space_.getLowestVisiblePoint())
            xny_1d = dot_buffer1d_space_.getLowestVisiblePoint();
    }

    return xny_1d;
}

ra_types::Point2i SpaceCoordinateTranslatorSimple::TranslateDotBufferToCanvas(
    const ra_types::displacement1i_t point1d, ra_types::n0_t line_width) const
{
    // NOTE: ignores axes directions and cutting
    auto y = point1d / line_width;
    auto x = point1d % line_width;
    return ra_types::Point2i{ x, y };
}

ra_types::Point2i SpaceCoordinateTranslatorSimple::TranslateCanvasToPixelBuffer(
    const ra_types::Point2i& p) const
{
    auto result = p + pixel_buffer2d_space_.viewZeroPointOffset;

    // cutting
    // NOTE: currently ignores axes directions

    if (result.x < 0)
        result.x = 0;
    if (result.y < 0)
        result.y = 0;
    if (result.x > pixel_buffer2d_space_.viewWidth - 1)
        result.x = pixel_buffer2d_space_.viewWidth - 1;
    if (result.y > pixel_buffer2d_space_.viewHeight - 1)
        result.y = pixel_buffer2d_space_.viewHeight - 1;

    result.x = result.x % pixel_buffer2d_space_.viewWidth;

    return result;
}

void SpaceCoordinateTranslatorSimple::TranslateWorldToCanvas(
    ra_types::Point2i& p) const
{
    // NOTE: currently ignores axes directions
    p = p + canvas2d_space_.viewZeroPointOffset;
}

} // namespace ra_core::pipeline
