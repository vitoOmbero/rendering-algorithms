#include "Dot.h"
namespace ra_core::figures2d
{

Dot::Dot(displacement1i_t x, displacement1i_t y, struct border border)
    : CircuitBase(border)
    , x_{ x }
    , y_{ y }
{
}

Dot::Dot(ra_types::Point2i p, struct border border)
    : CircuitBase(border)
    , x_{ p.x }
    , y_{ p.y }
{
}

displacement1i_t Dot::getX() const
{
    return x_;
}

displacement1i_t Dot::getY() const
{
    return y_;
}

void Dot::setX(displacement1i_t x)
{
    this->x_ = x;
}

void Dot::setY(displacement1i_t y)
{
    this->y_ = y;
}

ra_types::Point2i Dot::getPoint() const
{
    return ra_types::Point2i{ x_, y_ };
}

void Dot::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitDot(this);
}

} // namespace ra_core::figures2d
