#include "matrix_calculator_simple.h"

#include "math2d.h"

namespace ra_services::geometric_transformations_in_homogeneous_coordinates
{

using namespace ra_services::math2d;
using namespace ra_types;

MatrixCalculatorSimple::MatrixCalculatorSimple() = default;

Notation MatrixCalculatorSimple::getNotation() const
{
    return notation_;
}

ra_core::figures2d::LineSegment MatrixCalculatorSimple::Move(
    ra_core::figures2d::LineSegment ls, ra_types::displacement1i_t dx,
    ra_types::displacement1i_t dy) const
{
    Vec2h<ra_types::displacement1i_t> v1(ls.getFirstPoint().x,
                                         ls.getFirstPoint().y);
    Vec2h<ra_types::displacement1i_t> v2(ls.getSecondPoint().x,
                                         ls.getSecondPoint().y);

    auto v1m = MoveMatrix<displacement1i_t>(dx, dy) * v1;
    auto v2m = MoveMatrix<displacement1i_t>(dx, dy) * v2;

    ls.setFirstPoint({ v1m.col1[0], v1m.col1[1] });
    ls.setSecondPoint({ v2m.col1[0], v2m.col1[1] });
    return ls;
}

ra_core::figures2d::Circle MatrixCalculatorSimple::Move(
    ra_core::figures2d::Circle cr, displacement1i_t dx,
    displacement1i_t dy) const
{
    Vec2h<ra_types::displacement1i_t> v1(cr.getCenter().x, cr.getCenter().y);

    auto v1m = MoveMatrix<displacement1i_t>(dx, dy) * v1;

    cr.setCenter({ v1m.col1[0], v1m.col1[1] });
    return cr;
}

} // namespace ra_services::geometric_transformations_in_homogeneous_coordinates
