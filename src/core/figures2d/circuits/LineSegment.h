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
    LineSegment(ra_types::point2i firstPoint, ra_types::point2i secondPoint,
                struct border border);

    inline displacement1i_t getMaxX() const override
    {
        return std::max(firstPoint.x, secondPoint.x);
    };
    inline displacement1i_t getMaxY() const override
    {
        return std::max(firstPoint.y, secondPoint.y);
    };
    inline displacement1i_t getMinX() const override
    {
        return std::min(firstPoint.x, secondPoint.x);
    };
    inline displacement1i_t getMinY() const override
    {
        return std::min(firstPoint.y, secondPoint.y);
    };

    inline ra_types::point2i getFirstPoint() const { return firstPoint; };
    inline ra_types::point2i getSecondPoint() const { return secondPoint; };

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

    void setFirstPoint(const ra_types::point2i& value);

    void setSecondPoint(const ra_types::point2i& value);

private:
    ra_types::point2i firstPoint;
    ra_types::point2i secondPoint;
};
} // namespace ra_core::figures2d
#endif // LINESEGMENT_H
