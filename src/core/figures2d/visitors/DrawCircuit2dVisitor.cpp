#include "DrawCircuit2dVisitor.h"

#include "Pipeline.h"

namespace ra_core::pipeline
{

DrawCircuit2dVisitor::DrawCircuit2dVisitor(
    ra_core::pipeline::Pipeline& pipeline)
    : pipeline{ pipeline }
{
}

void DrawCircuit2dVisitor::VisitDot(const ra_core::figures2d::Dot* dot) const
{
    pipeline.DrawCircuit(*dot);
}

void DrawCircuit2dVisitor::VisitLine(const figures2d::LineSegment* ls) const
{
    pipeline.DrawCircuit(*ls);
}

void DrawCircuit2dVisitor::VisitCircle(const figures2d::Circle* c) const
{
    pipeline.DrawCircuit(*c);
}

void DrawCircuit2dVisitor::VisitTriangle(const figures2d::Triangle* tr) const
{
    pipeline.DrawCircuit(*tr);
}

} // namespace ra_core::canvas2d
