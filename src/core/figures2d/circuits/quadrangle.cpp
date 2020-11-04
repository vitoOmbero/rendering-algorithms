#include "quadrangle.h"

namespace ra_core::figures2d
{

Quadrangle::Quadrangle(Point2i p1, Point2i p2, Point2i p3, Point2i p4,
                       struct border border)
    : CircuitBase(border)
    , p1_{ p1 }
    , p2_{ p2 }
    , p3_{ p3 }
    , p4_{ p4 }
{
    // NOTE: tesselation?
    // NOTE: invariant?
}

void Quadrangle::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitQuadrangle(this);
}

ra_types::Point2i Quadrangle::getP1() const
{
    return p1_;
}

void Quadrangle::setP1(const ra_types::Point2i &value)
{
    p1_ = value;
}

ra_types::Point2i Quadrangle::getP2() const
{
    return p2_;
}

void Quadrangle::setP2(const ra_types::Point2i &value)
{
    p2_ = value;
}

ra_types::Point2i Quadrangle::getP3() const
{
    return p3_;
}

void Quadrangle::setP3(const ra_types::Point2i &value)
{
    p3_ = value;
}

ra_types::Point2i Quadrangle::getP4() const
{
    return p4_;
}

void Quadrangle::setP4(const ra_types::Point2i &value)
{
    p4_ = value;
}

} // namespace ra_core::figures2d
