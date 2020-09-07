#include "Dot.h"
namespace ra_core::figures2d
{

Dot::Dot(displacement1i_t x, displacement1i_t y, struct border border)
    : CircuitBase(border)
    , x{ x }
    , y{ y }
{
}

Dot::Dot(ra_types::point2i p, struct border border)
    : CircuitBase(border)
    , x{ p.x }
    , y{ p.y }
{
}

displacement1i_t Dot::getX() const
{
    return x;
}

displacement1i_t Dot::getY() const
{
    return y;
}

void Dot::setX(displacement1i_t x)
{
    this->x = x;
}

void Dot::setY(displacement1i_t y)
{
    this->y = y;
}

ra_types::point2i Dot::getPoint() const
{
    return ra_types::point2i{ x, y };
}

void Dot::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitDot(this);
}

} // namespace ra_core::figures2d
