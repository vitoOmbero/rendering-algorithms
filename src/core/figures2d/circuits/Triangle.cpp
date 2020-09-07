#include "Triangle.h"
namespace ra_core::figures2d
{
Triangle::Triangle(ra_types::point2i p1, ra_types::point2i p2,
                   ra_types::point2i p3, struct border border)
    : CircuitBase(border)
    , p1{ p1 }
    , p2{ p2 }
    , p3{ p3 }
{
}

void Triangle::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitTriangle(this);
}

ra_types::point2i Triangle::getP1() const
{
    return p1;
}

void Triangle::setP1(const ra_types::point2i& value)
{
    p1 = value;
}

ra_types::point2i Triangle::getP2() const
{
    return p2;
}

void Triangle::setP2(const ra_types::point2i& value)
{
    p2 = value;
}

ra_types::point2i Triangle::getP3() const
{
    return p3;
}

void Triangle::setP3(const ra_types::point2i& value)
{
    p3 = value;
}

} // namespace ra_core::figures2d
