#include "Rectangular1dDotBuffer.h"

namespace ra_core::canvas2d
{

// NOTE: todo coord translation service?
ra_types::n0_t Rectangular1dDotBuffer::Canvas2dToIndex1d(
    ra_types::displacement2d point, ra_types::n0_t line_width)
{
    // NOTE: depends on arithmetic type of ra_types::displacement_t
    auto y_1d = point.y * line_width;
    auto xny_1d = point.x + y_1d;

    // cutting
    if (xny_1d > lastIndex)
        xny_1d = lastIndex;
    // you shall not pass!!!
    if (xny_1d < zeroIndex)
        xny_1d = zeroIndex;

    return xny_1d;
}

ra_types::n0_t Rectangular1dDotBuffer::CalculateIndex(
    const Rectangular1dDotBuffer* buf, ra_types::displacement2d point)
{
    assert(point.x <= buf->width - 1);
    assert(point.y <= buf->height - 1);
    return Canvas2dToIndex1d(point, buf->width - 1);
}

Rectangular1dDotBuffer::Rectangular1dDotBuffer(
    ra_types::distance_t width, ra_types::distance_t height,
    ra_types::displacement2d zeroPointOffset,
    ra_types::rgb888         default_color_code)
    : width{ width }
    , height{ height }
    , dotsNumber{ 0 }
    , dotSize{ 1 } // NOTE: is scale

{
    dots =
        new std::vector<ra_types::rgb888>(width * height, default_color_code);
    lastIndex      = width * height - 1; // NOTE: depends on scale
    lineLastIndex  = width - 1;
    zeroPointIndex = CalculateIndex(this, zeroPointOffset);
}

Rectangular1dDotBuffer::~Rectangular1dDotBuffer()
{
    delete dots;
}

ra_types::n0_t Rectangular1dDotBuffer::getDotsNumber() const
{
    return dotsNumber;
}

void Rectangular1dDotBuffer::UpdateDotsNumber(ra_types::n0_t inc)
{
    dotsNumber += inc;
}

void Rectangular1dDotBuffer::Mark(ra_types::rgb888         code,
                                  ra_types::displacement2d point)
{
    auto i      = Canvas2dToIndex1d(point, width);
    dots->at(i) = code;
}

void Rectangular1dDotBuffer::Mark(ra_types::rgb888         code,
                                  ra_types::displacement2d start,
                                  ra_types::displacement2d end)
{
    auto ist = Canvas2dToIndex1d(start, width);
    auto ind = Canvas2dToIndex1d(end, width);
    for (auto i = ist; i <= ind; ++i)
    {
        dots->at(i) = code;
    }
}

std::unique_ptr<std::vector<ra_types::rgb888>>
Rectangular1dDotBuffer::CreateCopy() const
{
    std::vector<ra_types::rgb888>* v = new std::vector<ra_types::rgb888>(*dots);
    std::unique_ptr<std::vector<ra_types::rgb888>> ptr(v);
    return ptr;
}

ra_types::n0_t Rectangular1dDotBuffer::getZeroIndex() const
{
    return zeroIndex;
}

ra_types::n0_t Rectangular1dDotBuffer::getLastIndex() const
{
    return lastIndex;
}

ra_types::n0_t Rectangular1dDotBuffer::getZeroPointIndex() const
{
    return zeroPointIndex;
}

ra_types::n0_t Rectangular1dDotBuffer::getWidth() const
{
    return width;
}

ra_types::n0_t Rectangular1dDotBuffer::getHeight() const
{
    return height;
}

ra_types::n0_t Rectangular1dDotBuffer::getDotSize() const
{
    return dotSize;
}

} // namespace ra_core::canvas2d
