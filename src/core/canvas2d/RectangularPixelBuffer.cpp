#include "RectangularPixelBuffer.h"
#include "GetString.h"
namespace ra_core::canvas2d
{

RectangularPixelBuffer::RectangularPixelBuffer() {}

std::string_view RectangularPixelBuffer::GetName() const
{
    return this->name;
}

ra_types::n0_t RectangularPixelBuffer::GetWidth() const
{
    return width;
}

ra_types::n0_t RectangularPixelBuffer::GetHeight() const
{
    return height;
}

ra_types::n0_t RectangularPixelBuffer::GetDotsNumber() const
{
    return dotsNumber;
}

ra_types::n0_t RectangularPixelBuffer::GetDotSize() const
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

void RectangularPixelBuffer::Draw(const ra_core::figures2d::Dot& dot) const
{
    // TODO: implement ppximageviewer
    std::cout << "Fake draw Dot with color " << GetString(dot.GetColor())
              << std::endl;
}

void RectangularPixelBuffer::Foo() const {}
} // namespace ra_core::canvas2d
