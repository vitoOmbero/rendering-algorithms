#include "Rectangular1dDotBuffer.h"

namespace ra_core::canvas2d
{

// NOTE: todo coord translation service?
inline ra_types::n0_t Canvas2dToIndex1d(ra_types::displacement2d point,
                                        ra_types::n0_t           lineLastIndex)
{
    assert(point.x >= 0 & point.y >= 0);

    // NOTE: depends on arithmetic type of ra_types::displacement_t
    auto y_1d = point.y * lineLastIndex;
    return point.x + y_1d;
}

ra_types::n0_t CalculateIndex(const Rectangular1dDotBuffer* buf,
                              ra_types::displacement2d      point)
{
    assert(point.x <= buf->width - 1);
    assert(point.y <= buf->height - 1);
    return Canvas2dToIndex1d(point, buf->width - 1);
}

Rectangular1dDotBuffer::Rectangular1dDotBuffer(
    ra_types::distance_t width, ra_types::distance_t height,
    ra_types::displacement2d zeroPointOffset)
    : width{ width }
    , height{ height }
    , dotsNumber{ 0 }
    , dotSize{ 1 } // NOTE: is scale

{
    dots =
        new std::vector<ra_types::rgb888>(width * height, ra_types::rgb888());
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
    dots->at(Canvas2dToIndex1d(point, lineLastIndex)) = code;
}

void Rectangular1dDotBuffer::Mark(ra_types::rgb888         code,
                                  ra_types::displacement2d start,
                                  ra_types::displacement2d end)
{
    auto ist = Canvas2dToIndex1d(start, lineLastIndex);
    auto ind = Canvas2dToIndex1d(end, lineLastIndex);
    for (auto i = ist; i <= ind; ++i)
    {
        dots->at(i) = code;
    }
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
