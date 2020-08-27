#ifndef CIRCLE_H
#define CIRCLE_H
#include "CircuitBase.h"
#include "border.h"
#include "point2d.h"
#include "typedefs.h"

namespace ra_core::figures2d
{

class Circle final : public CircuitBase
{
public:
    Circle(point2d center, distance_t radius, struct border border);
    Circle(point2d center, point2d point, struct border border);

    inline displacement_t getMaxX() const override
    {
        return (center + radius).x;
    };
    inline displacement_t getMaxY() const override
    {
        return (center + radius).y;
    };
    inline displacement_t getMinX() const override
    {
        return (center - radius).x;
    };
    inline displacement_t getMinY() const override
    {
        return (center - radius).y;
    };

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

    point2d getCenter() const;
    void    setCenter(const point2d& value);

    distance_t getRadius() const;
    void       setRadius(const distance_t& value);

private:
    point2d    center;
    distance_t radius;
};
} // namespace ra_core::figures2d
#endif // CIRCLE_H
