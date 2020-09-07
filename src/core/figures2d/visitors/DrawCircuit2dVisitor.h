#ifndef DRAWFIGURE2DVISITOR_H
#define DRAWFIGURE2DVISITOR_H

#include "Figure2dVisitor.h"

namespace ra_core::pipeline
{

class Pipeline;

class DrawCircuit2dVisitor final : public ra_core::figures2d::Figure2dVisitor
{
public:
    DrawCircuit2dVisitor(Pipeline& pipeline);
    void VisitDot(const ra_core::figures2d::Dot* dot) const override;
    void VisitLine(const ra_core::figures2d::LineSegment* ls) const override;
    void VisitCircle(const ra_core::figures2d::Circle* c) const override;
    void VisitTriangle(const ra_core::figures2d::Triangle* tr) const override;

private:
    Pipeline& pipeline;
};

} // namespace ra_core::canvas2d

#endif // DRAWFIGURE2DVISITOR_H
