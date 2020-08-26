#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include <cmath>

#include "CircuitBase.h"
#include "border.h"
#include "point2d.h"
#include "typedefs.h"

namespace ra_core::figures2d
{
class LineSegment final : public CircuitBase
{
public:
    LineSegment(point2d firstPoint, point2d secondPoint, struct border border);

    inline displacement_t getMaxX() const override
    {
        return std::max(firstPoint.x, secondPoint.x);
    };
    inline displacement_t getMaxY() const override
    {
        return std::max(firstPoint.y, secondPoint.y);
    };
    inline displacement_t getMinX() const override
    {
        return std::min(firstPoint.x, secondPoint.x);
    };
    inline displacement_t getMinY() const override
    {
        return std::min(firstPoint.y, secondPoint.y);
    };

    inline point2d getFirstPoint() const { return firstPoint; };
    inline point2d getSecondPoint() const { return secondPoint; };

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

    void setFirstPoint(const point2d& value);

    void setSecondPoint(const point2d& value);

private:
    point2d firstPoint;
    point2d secondPoint;
};
} // namespace ra_core::figures2d
#endif // LINESEGMENT_H
