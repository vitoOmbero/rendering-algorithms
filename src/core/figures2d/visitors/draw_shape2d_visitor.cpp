#include "draw_shape2d_visitor.h"

#include "pipeline.h"

namespace ra_core::pipeline
{

DrawShape2dVisitor::DrawShape2dVisitor(Pipeline& pipeline)
    : pipeline_{ pipeline }
{
}

void DrawShape2dVisitor::VisitDot(const ra_core::figures2d::Dot* dot) const
{
    pipeline_.DrawCircuit(*dot);
}

void DrawShape2dVisitor::VisitLine(const figures2d::LineSegment* ls) const
{
    pipeline_.DrawCircuit(*ls);
}

void DrawShape2dVisitor::VisitCircle(const figures2d::Circle* c) const
{
    pipeline_.DrawShape(*c);
}

void DrawShape2dVisitor::VisitTriangle(const figures2d::Triangle* tr) const
{
    pipeline_.DrawShape(*tr);
}

void DrawShape2dVisitor::VisitQuadrangle(const figures2d::Quadrangle* tr) const
{
    pipeline_.DrawShape(*tr);
}

} // namespace ra_core::pipeline
