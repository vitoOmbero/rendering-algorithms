#include "DrawShape2dVisitor.h"
namespace ra_core::canvas2d
{
DrawShape2dVisitor::DrawShape2dVisitor(RectangularPixelBuffer& rpb)
    : rpb{ rpb }
{

}

void DrawShape2dVisitor::VisitDot(const ra_core::figures2d::Dot* dot) const
{
    rpb.DrawCircuit(*dot);
}

void DrawShape2dVisitor::VisitLine(const figures2d::LineSegment* ls) const
{
    rpb.DrawCircuit(*ls);
}

void DrawShape2dVisitor::VisitCircle(const figures2d::Circle* c) const
{
    rpb.DrawShape(*c);
}

void DrawShape2dVisitor::VisitTriangle(const figures2d::Triangle* tr) const
{
    rpb.DrawShape(*tr);
}

} // namespace ra_core::canvas2d
