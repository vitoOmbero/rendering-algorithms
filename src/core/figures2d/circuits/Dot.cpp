#include "Dot.h"
namespace ra_core::figures2d
{

Dot::Dot(displacement_t x, displacement_t y, struct border border)
    : CircuitBase(border)
    , x{ x }
    , y{ y }
{
}

Dot::Dot(point2d p, struct border border)
    : CircuitBase(border)
    , x{ p.x }
    , y{ p.y }
{
}

displacement_t Dot::getX() const
{
    return x;
}

displacement_t Dot::getY() const
{
    return y;
}

void Dot::setX(displacement_t x)
{
    this->x = x;
}

void Dot::setY(displacement_t y)
{
    this->y = y;
}

point2d Dot::getPoint() const
{
    return point2d{ x, y };
}

void Dot::AcceptFigure2dVisitor(Figure2dVisitor* fv) const
{
    fv->VisitDot(this);
}

} // namespace ra_core::figures2d
