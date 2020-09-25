#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include <cmath>

#include "CircuitBase.h"
#include "border.h"
#include "point2i.h"
#include "typedefs.h"

namespace ra_core::figures2d
{
class LineSegment final : public CircuitBase
{
public:
    LineSegment(ra_types::Point2i p1_, ra_types::Point2i p2_,
                struct border border);

    inline displacement1i_t getMaxX() const override
    {
        return std::max(p1_.x, p2_.x);
    };
    inline displacement1i_t getMaxY() const override
    {
        return std::max(p1_.y, p2_.y);
    };
    inline displacement1i_t getMinX() const override
    {
        return std::min(p1_.x, p2_.x);
    };
    inline displacement1i_t getMinY() const override
    {
        return std::min(p1_.y, p2_.y);
    };

    inline ra_types::Point2i getFirstPoint() const { return p1_; };
    inline ra_types::Point2i getSecondPoint() const { return p2_; };

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

    void setFirstPoint(const ra_types::Point2i& value);

    void setSecondPoint(const ra_types::Point2i& value);

private:
    ra_types::Point2i p1_;
    ra_types::Point2i p2_;
};
} // namespace ra_core::figures2d
#endif // LINESEGMENT_H
