#ifndef DRAWFIGURE2DVISITOR_H
#define DRAWFIGURE2DVISITOR_H

#include "figure2d_visitor.h"

namespace ra_core::pipeline
{

class Pipeline;

class DrawCircuit2dVisitor final : public ra_core::figures2d::Figure2dVisitor
{
public:
    explicit DrawCircuit2dVisitor(Pipeline& pipeline_);
    void VisitDot(const ra_core::figures2d::Dot* dot) const override;
    void VisitLine(const ra_core::figures2d::LineSegment* ls) const override;
    void VisitCircle(const ra_core::figures2d::Circle* c) const override;
    void VisitTriangle(const ra_core::figures2d::Triangle* tr) const override;
    void VisitQuadrangle(
        const ra_core::figures2d::Quadrangle* tr) const override;

private:
    Pipeline& pipeline_;
};

} // namespace ra_core::canvas2d

#endif // DRAWFIGURE2DVISITOR_H
