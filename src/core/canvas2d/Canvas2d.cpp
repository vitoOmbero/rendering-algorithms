#include "Canvas2d.h"
namespace ra_core::canvas2d
{

Canvas2d::Canvas2d()
    : rpb{ new RectangularPixelBuffer() }
    , drawVisitor{ new DrawFigure2dVisitor(*rpb) }
{
}

Canvas2d::~Canvas2d()
{
    delete rpb;
    delete drawVisitor;
}

RectangularPixelBuffer Canvas2d::GetPixelBuffer() const
{
    return *rpb;
}

void Canvas2d::Draw(const ra_core::figures2d::DrawableInterface& drawable) const
{
    drawable.AcceptFigure2dVisitor(drawVisitor);
}
} // namespace ra_core::canvas2d
