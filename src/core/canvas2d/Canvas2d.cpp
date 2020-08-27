#include "Canvas2d.h"
namespace ra_core::canvas2d
{

Canvas2d::Canvas2d()
    : rpb{ new RectangularPixelBuffer() }
    // TODO: cache params for pixbuf creation
    , drawVisitor{ new DrawFigure2dVisitor(*rpb) }
{
}

Canvas2d::~Canvas2d()
{
    delete drawVisitor;
}

std::unique_ptr<RectangularPixelBuffer> Canvas2d::getPixelBuffer()
{
    std::unique_ptr<RectangularPixelBuffer> new_(new RectangularPixelBuffer());
    auto old = std::move(rpb); // TODO: copy ctor (copy buffer settings)
    rpb                                         = std::move(new_);
    return old;
}

void Canvas2d::Draw(const ra_core::figures2d::DrawableInterface& drawable) const
{
    drawable.AcceptFigure2dVisitor(drawVisitor);
}

void Canvas2d::UseLineAlgorithm(
    AlgorithmProxy::rendering_algorithm algo_ptr) const
{
    rpb->UseLineAlgorithm(algo_ptr);
}

void Canvas2d::UseCircleAlgorithm(
    AlgorithmProxy::rendering_algorithm algo_ptr) const
{
    rpb->UseCircleAlgorithm(algo_ptr);
}
} // namespace ra_core::canvas2d
