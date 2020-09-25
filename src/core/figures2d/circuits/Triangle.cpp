#include "Triangle.h"
namespace ra_core::figures2d
{
Triangle::Triangle(ra_types::Point2i p1, ra_types::Point2i p2,
                   ra_types::Point2i p3, struct border border)
    : CircuitBase(border)
    , p1_{ p1 }
    , p2_{ p2 }
    , p3_{ p3 }
{
}

void Triangle::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitTriangle(this);
}

ra_types::Point2i Triangle::getP1() const
{
    return p1_;
}

void Triangle::setP1(const ra_types::Point2i& value)
{
    p1_ = value;
}

ra_types::Point2i Triangle::getP2() const
{
    return p2_;
}

void Triangle::setP2(const ra_types::Point2i& value)
{
    p2_ = value;
}

ra_types::Point2i Triangle::getP3() const
{
    return p3_;
}

void Triangle::setP3(const ra_types::Point2i& value)
{
    p3_ = value;
}

} // namespace ra_core::figures2d
