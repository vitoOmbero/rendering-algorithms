#ifndef DRAWSHAPE2DVISITOR_H
#define DRAWSHAPE2DVISITOR_H

#include "Figure2dVisitor.h"
#include "RectangularPixelBuffer.h"

namespace ra_core::canvas2d
{
class DrawShape2dVisitor final : public ra_core::figures2d::Figure2dVisitor
{
public:
    DrawShape2dVisitor(RectangularPixelBuffer& rpb);
    void VisitDot(const ra_core::figures2d::Dot* dot) const override;
    void VisitLine(const ra_core::figures2d::LineSegment* ls) const override;
    void VisitCircle(const ra_core::figures2d::Circle* c) const override;
    void VisitTriangle(const ra_core::figures2d::Triangle* tr) const override;

private:
    RectangularPixelBuffer& rpb;
};
} // namespace ra_core::canvas2d
#endif // DRAWSHAPE2DVISITOR_H
