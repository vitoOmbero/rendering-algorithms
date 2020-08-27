#include "Circle.h"

#include "math2d.h"

namespace ra_core::figures2d
{

Circle::Circle(point2d center, distance_t radius, struct border border)
    : CircuitBase(border)
    , center{ center }
    , radius{ radius }
{
}

Circle::Circle(point2d center, point2d point, struct border border)
    : CircuitBase(border)
    , center{ center }
{
    radius = ra_services::math2d::calc_distance(center, point);
}

void ra_core::figures2d::Circle::AcceptFigure2dVisitor(
    ra_core::figures2d::Figure2dVisitor* fv) const
{
    fv->VisitCircle(this);
}

point2d Circle::getCenter() const
{
    return center;
}

void Circle::setCenter(const point2d &value)
{
    center = value;
}

distance_t Circle::getRadius() const
{
    return radius;
}

void Circle::setRadius(const distance_t &value)
{
    radius = value;
}
} // namespace ra_core::figures2d
