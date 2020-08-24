#ifndef DRAWFIGURE2DVISITOR_H
#define DRAWFIGURE2DVISITOR_H

#include "Figure2dVisitor.h"
#include "RectangularPixelBuffer.h"

namespace ra_core::canvas2d
{

class DrawFigure2dVisitor final : public ra_core::figures2d::Figure2dVisitor
{
public:
    DrawFigure2dVisitor(RectangularPixelBuffer& rpb);
    void VisitDot(const ra_core::figures2d::Dot* dot) const override;

private:
    RectangularPixelBuffer& rpb;
};

} // namespace ra_core::canvas2d

#endif // DRAWFIGURE2DVISITOR_H
