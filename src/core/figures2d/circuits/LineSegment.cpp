#include "LineSegment.h"
namespace ra_core::figures2d
{

LineSegment::LineSegment(point2d one, point2d two, struct border border)
    : CircuitBase{ border }
    , firstPoint{ one }
    , secondPoint{ two }
{
}

void LineSegment::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitLine(this);
}

void LineSegment::setFirstPoint(const point2d& value)
{
    firstPoint = value;
}

void LineSegment::setSecondPoint(const point2d& value)
{
    secondPoint = value;
}

} // namespace ra_core::figures2d
