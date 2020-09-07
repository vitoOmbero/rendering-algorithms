#include "DrawShape2dVisitor.h"

#include "Pipeline.h"

namespace ra_core::pipeline
{

DrawShape2dVisitor::DrawShape2dVisitor(Pipeline& pipeline)
    : pipeline{ pipeline }
{
}

void DrawShape2dVisitor::VisitDot(const ra_core::figures2d::Dot* dot) const
{
    pipeline.DrawCircuit(*dot);
}

void DrawShape2dVisitor::VisitLine(const figures2d::LineSegment* ls) const
{
    pipeline.DrawCircuit(*ls);
}

void DrawShape2dVisitor::VisitCircle(const figures2d::Circle* c) const
{
    pipeline.DrawShape(*c);
}

void DrawShape2dVisitor::VisitTriangle(const figures2d::Triangle* tr) const
{
    pipeline.DrawShape(*tr);
}

} // namespace ra_core::canvas2d
