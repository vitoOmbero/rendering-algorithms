#include "DrawCircuit2dVisitor.h"
namespace ra_core::canvas2d
{

DrawCircuit2dVisitor::DrawCircuit2dVisitor(RectangularPixelBuffer& rpb)
    : rpb{ rpb }
{
}

void DrawCircuit2dVisitor::VisitDot(const ra_core::figures2d::Dot* dot) const
{
    rpb.DrawCircuit(*dot);
}

void DrawCircuit2dVisitor::VisitLine(const figures2d::LineSegment* ls) const
{
    rpb.DrawCircuit(*ls);
}

void DrawCircuit2dVisitor::VisitCircle(const figures2d::Circle* c) const
{
    rpb.DrawCircuit(*c);
}

void DrawCircuit2dVisitor::VisitTriangle(const figures2d::Triangle* tr) const
{
    rpb.DrawCircuit(*tr);
}

} // namespace ra_core::canvas2d
