#include "draw_circuit2d_visitor.h"

#include "pipeline.h"

namespace ra_core::pipeline
{

DrawCircuit2dVisitor::DrawCircuit2dVisitor(
    ra_core::pipeline::Pipeline& pipeline)
    : pipeline_{ pipeline }
{
}

void DrawCircuit2dVisitor::VisitDot(const ra_core::figures2d::Dot* dot) const
{
    pipeline_.DrawCircuit(*dot);
}

void DrawCircuit2dVisitor::VisitLine(const figures2d::LineSegment* ls) const
{
    pipeline_.DrawCircuit(*ls);
}

void DrawCircuit2dVisitor::VisitCircle(const figures2d::Circle* c) const
{
    pipeline_.DrawCircuit(*c);
}

void DrawCircuit2dVisitor::VisitTriangle(const figures2d::Triangle* tr) const
{
    pipeline_.DrawCircuit(*tr);
}

void DrawCircuit2dVisitor::VisitQuadrangle(
    const figures2d::Quadrangle* tr) const
{
    pipeline_.DrawCircuit(*tr);
}

} // namespace ra_core::canvas2d
