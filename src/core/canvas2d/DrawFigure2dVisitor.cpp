#include "DrawFigure2dVisitor.h"
namespace ra_core::canvas2d
{

DrawFigure2dVisitor::DrawFigure2dVisitor(RectangularPixelBuffer& rpb)
    : rpb{ rpb }
{
}

void DrawFigure2dVisitor::VisitDot(const ra_core::figures2d::Dot* dot) const
{
    rpb.Draw(*dot);
}

} // namespace ra_core::canvas2d
