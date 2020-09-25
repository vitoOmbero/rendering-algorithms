#include "Circle.h"

#include "math2d.h"

namespace ra_core::figures2d
{

Circle::Circle(ra_types::Point2i center, distance1ui_t radius,
               struct border border)
    : CircuitBase(border)
    , center_{ center }
    , radius_{ radius }
{
}

Circle::Circle(ra_types::Point2i center, ra_types::Point2i point,
               struct border border)
    : CircuitBase(border)
    , center_{ center }
{
    radius_ = ra_services::math2d::CalcDistance(center, point);
}

void ra_core::figures2d::Circle::AcceptFigure2dVisitor(
    ra_core::figures2d::Figure2dVisitor* fv) const
{
    fv->VisitCircle(this);
}

ra_types::Point2i Circle::getCenter() const
{
    return center_;
}

void Circle::setCenter(const ra_types::Point2i& value)
{
    center_ = value;
}

distance1ui_t Circle::getRadius() const
{
    return radius_;
}

void Circle::setRadius(const distance1ui_t &value)
{
    radius_ = value;
}
} // namespace ra_core::figures2d
