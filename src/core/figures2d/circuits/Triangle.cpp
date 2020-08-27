#include "Triangle.h"
namespace ra_core::figures2d
{
Triangle::Triangle(point2d p1, point2d p2, point2d p3, struct border border)
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

point2d Triangle::getP1() const
{
    return p1;
}

void Triangle::setP1(const point2d& value)
{
    p1 = value;
}

point2d Triangle::getP2() const
{
    return p2;
}

void Triangle::setP2(const point2d& value)
{
    p2 = value;
}

point2d Triangle::getP3() const
{
    return p3;
}

void Triangle::setP3(const point2d& value)
{
    p3 = value;
}

} // namespace ra_core::figures2d
