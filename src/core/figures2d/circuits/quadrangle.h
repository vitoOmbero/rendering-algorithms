#ifndef QUADRANGLE_H
#define QUADRANGLE_H
#include <algorithm>
#include <initializer_list>

#include "circuit_base.h"
#include "border.h"
#include "point2i.h"
#include "typedefs.h"

namespace ra_core::figures2d
{

class Quadrangle final : public CircuitBase
{
public:
    Quadrangle(ra_types::Point2i p1_, ra_types::Point2i p2_,
               ra_types::Point2i p3_, ra_types::Point2i p4_,
               struct border border);

    [[nodiscard]] inline displacement1i_t getMaxX() const override
    {
        return std::max({ p1_.x, p2_.x, p3_.x, p4_.x });
    };
    [[nodiscard]] inline displacement1i_t getMaxY() const override
    {
        return std::max({ p1_.y, p2_.y, p3_.y, p4_.y });
    };
    [[nodiscard]] inline displacement1i_t getMinX() const override
    {
        return std::min({ p1_.x, p2_.x, p3_.x, p4_.x });
    };
    [[nodiscard]] inline displacement1i_t getMinY() const override
    {
        return std::min({ p1_.y, p2_.y, p3_.y, p4_.y });
    };

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

    [[nodiscard]] ra_types::Point2i getP1() const;
    void              setP1(const ra_types::Point2i& value);

    [[nodiscard]] ra_types::Point2i getP2() const;
    void              setP2(const ra_types::Point2i& value);

    [[nodiscard]] ra_types::Point2i getP3() const;
    void              setP3(const ra_types::Point2i& value);

    [[nodiscard]] ra_types::Point2i getP4() const;
    void              setP4(const ra_types::Point2i& value);

private:
    ra_types::Point2i p1_;
    ra_types::Point2i p2_;
    ra_types::Point2i p3_;
    ra_types::Point2i p4_;
};
} // namespace ra_core::figures2d
#endif // QUADRANGLE_H
