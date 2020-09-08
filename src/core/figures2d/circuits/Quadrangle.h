#ifndef QUADRANGLE_H
#define QUADRANGLE_H
#include <algorithm>
#include <initializer_list>

#include "CircuitBase.h"
#include "border.h"
#include "point2i.h"
#include "typedefs.h"

namespace ra_core::figures2d
{

class Quadrangle final : public CircuitBase
{
public:
    Quadrangle(ra_types::point2i p1, ra_types::point2i p2, ra_types::point2i p3,
               ra_types::point2i p4, struct border border);

    inline displacement1i_t getMaxX() const override
    {
        return std::max({ p1.x, p2.x, p3.x, p4.x });
    };
    inline displacement1i_t getMaxY() const override
    {
        return std::max({ p1.y, p2.y, p3.y, p4.y });
    };
    inline displacement1i_t getMinX() const override
    {
        return std::min({ p1.x, p2.x, p3.x, p4.x });
    };
    inline displacement1i_t getMinY() const override
    {
        return std::min({ p1.y, p2.y, p3.y, p4.y });
    };

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

    ra_types::point2i getP1() const;
    void              setP1(const ra_types::point2i& value);

    ra_types::point2i getP2() const;
    void              setP2(const ra_types::point2i& value);

    ra_types::point2i getP3() const;
    void              setP3(const ra_types::point2i& value);

    ra_types::point2i getP4() const;
    void              setP4(const ra_types::point2i& value);

private:
    ra_types::point2i p1;
    ra_types::point2i p2;
    ra_types::point2i p3;
    ra_types::point2i p4;
};
} // namespace ra_core::figures2d
#endif // QUADRANGLE_H
