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
    auto                                    old = std::move(rpb);
    rpb                                         = std::move(new_);
    return old;
}

void Canvas2d::Draw(const ra_core::figures2d::DrawableInterface& drawable) const
{
    drawable.AcceptFigure2dVisitor(drawVisitor);
}
} // namespace ra_core::canvas2d
