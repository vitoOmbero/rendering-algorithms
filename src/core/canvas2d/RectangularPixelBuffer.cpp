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
    , xAxisDirection{ ra_types::eScreenDirection::East }
    , yAxisDirection{ ra_types::eScreenDirection::South }
    , zeroPointOffset{ 0, 0 }
    , raproxy()
{

    lowestVisiblePoint = CalculateLowestVisiblePoint(this);
    assert(zeroPointOffset >= lowestVisiblePoint);
    highestVisiblePoint = CalculateHighestVisiblePoint(this);
    dotbuf = new Rectangular1dDotBuffer(width, height, zeroPointOffset);

    raproxy.setRenderingAlgorithm(
        ra_core::figures2d::eFigure2dType::Dot,
        AlgorithmProxy::rendering_algorithm::dot_naive);
    raproxy.setRenderingAlgorithm(
        ra_core::figures2d::eFigure2dType::Line,
        AlgorithmProxy::rendering_algorithm::line_bresenham_int);
    raproxy.setRenderingAlgorithm(
        ra_core::figures2d::eFigure2dType::Circle,
        AlgorithmProxy::rendering_algorithm::circle_bresenham_int);
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

ra_types::eScreenDirection RectangularPixelBuffer::getXAxisDirection() const
{
    return xAxisDirection;
}

ra_types::eScreenDirection RectangularPixelBuffer::getYAxisDirection() const
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
    std::cout << "Draw Dot " << ra_types::GetString(dot.getPoint(), true)
              << " with rgb " << GetString(dot.GetColorCode()) << std::endl;

    if (IsVisible(dot.getX(), dot.getY()))
    {
        auto point =
            Cartesian2dToCanvas2d({ dot.getX(), dot.getY() }, zeroPointOffset);

        auto ra_dot_func = raproxy.getRenderingDot();

        auto dotsdrawn =
            ra_dot_func(point.x, point.y, dot.GetColorCode(), *dotbuf);

        dotbuf->UpdateDotsNumber(dotsdrawn);
    }
}

void RectangularPixelBuffer::Draw(const figures2d::LineSegment& ls) const
{
    // TODO: move to algoritm + add compile options and debug mode
    std::cout << "Draw LineSegment "
              << ra_types::GetString(ls.getFirstPoint(), true) << "-"
              << ra_types::GetString(ls.getSecondPoint(), true) << " with rgb "
              << GetString(ls.GetColorCode()) << std::endl;

    if (IsVisible(ls.getMaxX(), ls.getMaxY()) &
        IsVisible(ls.getMinX(), ls.getMinY()))
    {
        auto first_d = Cartesian2dToCanvas2d(
            { ls.getFirstPoint().x, ls.getFirstPoint().y }, zeroPointOffset);
        auto second_d = Cartesian2dToCanvas2d(
            { ls.getSecondPoint().x, ls.getSecondPoint().y }, zeroPointOffset);

        ra_core::figures2d::point2d first{ first_d.x, first_d.y };
        ra_core::figures2d::point2d second{ second_d.x, second_d.y };

        auto ra_linesegment_func = raproxy.getRenderingLineSegment();

        auto dotsdrawn =
            ra_linesegment_func(first, second, ls.GetColorCode(), *dotbuf);

        dotbuf->UpdateDotsNumber(dotsdrawn);
    }
}

void RectangularPixelBuffer::Draw(const figures2d::Circle& c) const
{
    // TODO: move to algoritm + add compile options and debug mode
    std::cout << "Draw Circle in " << ra_types::GetString(c.getCenter(), true)
              << "with R: " << c.getRadius() << " and rgb "
              << GetString(c.GetColorCode()) << std::endl;

    if (IsVisible(c.getMaxX(), c.getMaxY()) &
        IsVisible(c.getMinX(), c.getMinY()))
    {
        auto center_d = Cartesian2dToCanvas2d(
            { c.getCenter().x, c.getCenter().y }, zeroPointOffset);

        ra_core::figures2d::point2d center{ center_d.x, center_d.y };

        auto ra_circle_func = raproxy.getRenderingCircle();

        auto dotsdrawn =
            ra_circle_func(center, c.getRadius(), c.GetColorCode(), *dotbuf);

        dotbuf->UpdateDotsNumber(dotsdrawn);
    }
}

void RectangularPixelBuffer::Draw(const figures2d::Triangle& tr) const
{
    // TODO: move to algoritm + add compile options and debug mode
    std::cout << "Draw Triangle " << ra_types::GetString(tr.getP1(), true)
              << "-" << ra_types::GetString(tr.getP2(), true) << "-"
              << ra_types::GetString(tr.getP3(), true) << "with rgb "
              << GetString(tr.GetColorCode()) << std::endl;

    if (IsVisible(tr.getMaxX(), tr.getMaxY()) &
        IsVisible(tr.getMinX(), tr.getMinY()))
    {
        auto p1_d = Cartesian2dToCanvas2d({ tr.getP1().x, tr.getP1().y },
                                          zeroPointOffset);
        auto p2_d = Cartesian2dToCanvas2d({ tr.getP2().x, tr.getP2().y },
                                          zeroPointOffset);
        auto p3_d = Cartesian2dToCanvas2d({ tr.getP3().x, tr.getP3().y },
                                          zeroPointOffset);

        ra_core::figures2d::point2d p1{ p1_d.x, p1_d.y };
        ra_core::figures2d::point2d p2{ p2_d.x, p2_d.y };
        ra_core::figures2d::point2d p3{ p3_d.x, p3_d.y };

        auto ra_ls_func = raproxy.getRenderingLineSegment();

        auto dotsdrawn = ra_ls_func(p1, p2, tr.GetColorCode(), *dotbuf);
        dotsdrawn += ra_ls_func(p2, p3, tr.GetColorCode(), *dotbuf);
        dotsdrawn += ra_ls_func(p3, p1, tr.GetColorCode(), *dotbuf);

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

void RectangularPixelBuffer::UseLineAlgorithm(
    AlgorithmProxy::rendering_algorithm algo_ptr)
{
    raproxy.setRenderingAlgorithm(figures2d::eFigure2dType::Line, algo_ptr);
}

void RectangularPixelBuffer::UseCircleAlgorithm(
    AlgorithmProxy::rendering_algorithm algo_ptr)
{
    raproxy.setRenderingAlgorithm(figures2d::eFigure2dType::Circle, algo_ptr);
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
