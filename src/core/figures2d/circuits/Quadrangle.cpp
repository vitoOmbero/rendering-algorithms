#include "Quadrangle.h"

namespace ra_core::figures2d
{

Quadrangle::Quadrangle(point2i p1, point2i p2, point2i p3, point2i p4,
                       struct border border)
    : CircuitBase(border)
    , p1{ p1 }
    , p2{ p2 }
    , p3{ p3 }
    , p4{ p4 }
{
    // NOTE: tesselation?
    // NOTE: invariant?
}

void Quadrangle::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitQuadrangle(this);
}

ra_types::point2i Quadrangle::getP1() const
{
    return p1;
}

void Quadrangle::setP1(const ra_types::point2i &value)
{
    p1 = value;
}

ra_types::point2i Quadrangle::getP2() const
{
    return p2;
}

void Quadrangle::setP2(const ra_types::point2i &value)
{
    p2 = value;
}

ra_types::point2i Quadrangle::getP3() const
{
    return p3;
}

void Quadrangle::setP3(const ra_types::point2i &value)
{
    p3 = value;
}

ra_types::point2i Quadrangle::getP4() const
{
    return p4;
}

void Quadrangle::setP4(const ra_types::point2i &value)
{
    p4 = value;
}

} // namespace ra_core::figures2d
