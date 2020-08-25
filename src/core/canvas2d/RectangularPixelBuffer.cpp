#include "RectangularPixelBuffer.h"
#include "GetString.h"
#include "cassert"
namespace ra_core::canvas2d
{

// TODO: need buffers factory
// NOTE: is coord translation service needed?

inline ra_types::displacement2d Cartesian2dToCanvas2d(
    ra_types::displacement2d point, ra_types::displacement2d offset)
{
    return point - offset;
}

inline ra_types::displacement2d CalculateLowestVisiblePoint(
    RectangularPixelBuffer* b)
{
    // NOTE: depends on scale
    auto x = b->zeroPointOffset.x * (-1);
    auto y = b->zeroPointOffset.y * (-1);
    return { x, y };
}

inline ra_types::displacement2d CalculateHighestVisiblePoint(
    RectangularPixelBuffer* b)
{
    // NOTE: depends on scale
    return ra_types::displacement2d{ b->width, b->height } - b->zeroPointOffset;
}

RectangularPixelBuffer::RectangularPixelBuffer()
    : name{ "RectangularPixelBuffer" }
    , width{ 800 }
    , height{ 600 }
    , xAxisDirection{ ra_types::eDirection::East }
    , yAxisDirection{ ra_types::eDirection::South }
    , zeroPointOffset{ 0, 0 }
{

    lowestVisiblePoint = CalculateLowestVisiblePoint(this);
    assert(zeroPointOffset >= lowestVisiblePoint);
    highestVisiblePoint = CalculateHighestVisiblePoint(this);
    dotbuf = new Rectangular1dDotBuffer(width, height, zeroPointOffset);
}

RectangularPixelBuffer::~RectangularPixelBuffer()
{
    delete dotbuf;
}

std::string_view RectangularPixelBuffer::getName() const
{
    return this->name;
}

ra_types::n0_t RectangularPixelBuffer::getPxWidth() const
{
    return width;
}

ra_types::n0_t RectangularPixelBuffer::getPxHeight() const
{
    return height;
}

ra_types::n0_t RectangularPixelBuffer::getBufferDotsNumber() const
{
    return dotbuf->getDotsNumber();
}

ra_types::n0_t RectangularPixelBuffer::getBufferDotSize() const
{
    return dotbuf->getDotSize();
}

ra_types::n0_t RectangularPixelBuffer::getBufferZeroIndex() const
{
    return dotbuf->getZeroIndex();
}

ra_types::n0_t RectangularPixelBuffer::getBufferLastIndex() const
{
    return dotbuf->getLastIndex();
}

ra_types::n0_t RectangularPixelBuffer::getBufferZeroPointIndex() const
{
    return dotbuf->getZeroPointIndex();
}

ra_types::n0_t RectangularPixelBuffer::getDtWidth() const
{
    return dotbuf->getWidth();
}

ra_types::n0_t RectangularPixelBuffer::getDtHeight() const
{
    return dotbuf->getHeight();
}

ra_types::eDirection RectangularPixelBuffer::getXAxisDirection() const
{
    return xAxisDirection;
}

ra_types::eDirection RectangularPixelBuffer::getYAxisDirection() const
{
    return yAxisDirection;
}

ra_types::displacement2d RectangularPixelBuffer::getZeroPointOffset() const
{
    return zeroPointOffset;
}

void RectangularPixelBuffer::Draw(const ra_core::figures2d::Dot& dot) const
{
    // TODO: move to algoritm + add compile options and debug mode
    std::cout << "Draw Dot with color " << GetString(dot.GetColorCode())
              << std::endl;

    if (IsVisible(dot.getX(), dot.getY()))
    {
        auto point =
            Cartesian2dToCanvas2d({ dot.getX(), dot.getY() }, zeroPointOffset);
        // TODO: use pointers to algorithms
        auto dotsdrawn = ra_core::rendering2d::line::naive_dot(
            point.x, point.y, dot.GetColorCode(), *dotbuf);
        dotbuf->UpdateDotsNumber(dotsdrawn);
    }
}

std::unique_ptr<std::vector<ra_types::rgb888>>
RectangularPixelBuffer::StumpBufferCopy(ra_types::n0_t           width_px,
                                        ra_types::n0_t           height_px,
                                        ra_types::displacement_t xOffset,
                                        ra_types::displacement_t yOffset) const
{
    // TODO: fill if bigger, cut if smaller
    width_px  = 0;
    height_px = 0;
    xOffset   = 0;
    yOffset   = 0;
    // TODO: make stamp use dot scale
    return dotbuf->CreateCopy();
}

ra_types::displacement2d RectangularPixelBuffer::getHighestVisiblePoint() const
{
    return highestVisiblePoint;
}

ra_types::displacement2d RectangularPixelBuffer::getLowestVisiblePoint() const
{
    return lowestVisiblePoint;
}

} // namespace ra_core::canvas2d
