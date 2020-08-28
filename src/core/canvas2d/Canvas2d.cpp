#include "Canvas2d.h"
namespace ra_core::canvas2d
{

Canvas2d::Canvas2d(Mode mode, ra_types::rgb888 color_code)
    : rpb{ new RectangularPixelBuffer(color_code) }
    , drawVisitor{ nullptr }
// TODO: cache params for pixbuf creation
{
    setDrawingMode(mode);
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

void Canvas2d::setDrawingMode(Canvas2d::Mode mode)
{
    if (drawVisitor != nullptr)
        delete drawVisitor;
    if (mode == Ciruit)
        drawVisitor = new DrawCircuit2dVisitor(*rpb);
    else
        drawVisitor = new DrawShape2dVisitor(*rpb);
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

void Canvas2d::UseFillingTriangle(
    AlgorithmProxy::rendering_algorithm algo_ptr) const
{
    rpb->UseFilling3v(algo_ptr);
}
} // namespace ra_core::canvas2d
