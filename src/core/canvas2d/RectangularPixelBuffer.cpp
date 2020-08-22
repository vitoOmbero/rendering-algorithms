#include "RectangularPixelBuffer.h"

namespace ra_core
{
namespace canvas2d
{

RectangularPixelBuffer::RectangularPixelBuffer() {}

std::string_view RectangularPixelBuffer::GetName() const
{
    return this->name;
}

ra_types::size_t RectangularPixelBuffer::GetWidth() const
{
    return width;
}

ra_types::size_t RectangularPixelBuffer::GetHeight() const
{
    return height;
}

ra_types::n0_t RectangularPixelBuffer::GetDotsNumber() const
{
    return dotsNumber;
}

ra_types::size_t RectangularPixelBuffer::GetDotSize() const
{
    return dotSize;
}

ra_types::eDirection RectangularPixelBuffer::GetXAxisDirection() const
{
    return xAxisDirection;
}

ra_types::eDirection RectangularPixelBuffer::GetYAxisDirection() const
{
    return yAxisDirection;
}

ra_types::displacement2d RectangularPixelBuffer::GetZeroPointOffset() const
{
    return zeroPointOffset;
}

void RectangularPixelBuffer::Foo() const {}
} // namespace canvas2d
} // namespace ra_core
