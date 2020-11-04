#include "line_segment.h"
namespace ra_core::figures2d
{

LineSegment::LineSegment(ra_types::Point2i one, ra_types::Point2i two,
                         struct border border)
    : CircuitBase{ border }
    , p1_{ one }
    , p2_{ two }
{
}

void LineSegment::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitLine(this);
}

void LineSegment::setFirstPoint(const ra_types::Point2i& value)
{
    p1_ = value;
}

void LineSegment::setSecondPoint(const ra_types::Point2i& value)
{
    p2_ = value;
}

} // namespace ra_core::figures2d
