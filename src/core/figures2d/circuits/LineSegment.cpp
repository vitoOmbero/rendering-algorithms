#include "LineSegment.h"
namespace ra_core::figures2d
{

LineSegment::LineSegment(ra_types::point2i one, ra_types::point2i two,
                         struct border border)
    : CircuitBase{ border }
    , firstPoint{ one }
    , secondPoint{ two }
{
}

void LineSegment::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitLine(this);
}

void LineSegment::setFirstPoint(const ra_types::point2i& value)
{
    firstPoint = value;
}

void LineSegment::setSecondPoint(const ra_types::point2i& value)
{
    secondPoint = value;
}

} // namespace ra_core::figures2d
