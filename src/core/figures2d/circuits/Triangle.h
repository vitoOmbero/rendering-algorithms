#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <algorithm>
#include <initializer_list>

#include "CircuitBase.h"
#include "border.h"
#include "point2d.h"
#include "typedefs.h"

namespace ra_core::figures2d
{

class Triangle final : public CircuitBase
{
public:
    Triangle(point2d p1, point2d p2, point2d p3, struct border border);

    inline displacement_t getMaxX() const override
    {
        return std::max({ p1.x, p2.x, p3.x });
    };
    inline displacement_t getMaxY() const override
    {
        return std::max({ p1.y, p2.y, p3.y });
    };
    inline displacement_t getMinX() const override
    {
        return std::min({ p1.x, p2.x, p3.x });
    };
    inline displacement_t getMinY() const override
    {
        return std::min({ p1.y, p2.y, p3.y });
    };

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

    point2d getP1() const;
    void    setP1(const point2d& value);

    point2d getP2() const;
    void    setP2(const point2d& value);

    point2d getP3() const;
    void    setP3(const point2d& value);

private:
    point2d p1;
    point2d p2;
    point2d p3;
};
} // namespace ra_core::figures2d
#endif // TRIANGLE_H
