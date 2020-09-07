#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <algorithm>
#include <initializer_list>

#include "CircuitBase.h"
#include "border.h"
#include "point2i.h"
#include "typedefs.h"

namespace ra_core::figures2d
{

class Triangle final : public CircuitBase
{
public:
    Triangle(ra_types::point2i p1, ra_types::point2i p2, ra_types::point2i p3,
             struct border border);

    inline displacement1i_t getMaxX() const override
    {
        return std::max({ p1.x, p2.x, p3.x });
    };
    inline displacement1i_t getMaxY() const override
    {
        return std::max({ p1.y, p2.y, p3.y });
    };
    inline displacement1i_t getMinX() const override
    {
        return std::min({ p1.x, p2.x, p3.x });
    };
    inline displacement1i_t getMinY() const override
    {
        return std::min({ p1.y, p2.y, p3.y });
    };

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

    ra_types::point2i getP1() const;
    void              setP1(const ra_types::point2i& value);

    ra_types::point2i getP2() const;
    void              setP2(const ra_types::point2i& value);

    ra_types::point2i getP3() const;
    void              setP3(const ra_types::point2i& value);

private:
    ra_types::point2i p1;
    ra_types::point2i p2;
    ra_types::point2i p3;
};
} // namespace ra_core::figures2d
#endif // TRIANGLE_H
