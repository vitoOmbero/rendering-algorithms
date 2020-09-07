#include "Circle.h"

#include "math2d.h"

namespace ra_core::figures2d
{

Circle::Circle(ra_types::point2i center, distance1ui_t radius,
               struct border border)
    : CircuitBase(border)
    , center{ center }
    , radius{ radius }
{
}

Circle::Circle(ra_types::point2i center, ra_types::point2i point,
               struct border border)
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

ra_types::point2i Circle::getCenter() const
{
    return center;
}

void Circle::setCenter(const ra_types::point2i& value)
{
    center = value;
}

distance1ui_t Circle::getRadius() const
{
    return radius;
}

void Circle::setRadius(const distance1ui_t &value)
{
    radius = value;
}
} // namespace ra_core::figures2d
