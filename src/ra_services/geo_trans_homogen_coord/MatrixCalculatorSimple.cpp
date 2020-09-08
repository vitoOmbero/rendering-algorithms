#include "MatrixCalculatorSimple.h"

#include "math2d.h"

namespace ra_services::geometric_transformations_in_homogeneous_coordinates
{

using namespace ra_services::math2d;
using namespace ra_types;

MatrixCalculatorSimple::MatrixCalculatorSimple()
{

}

eNotation MatrixCalculatorSimple::getNotation() const
{
    return notation;
}

ra_core::figures2d::LineSegment MatrixCalculatorSimple::Move(
    ra_core::figures2d::LineSegment ls, ra_types::displacement1i_t dx,
    ra_types::displacement1i_t dy) const
{
    vec2h<ra_types::displacement1i_t> v1(
        make_displacement2d(ls.getFirstPoint()));
    vec2h<ra_types::displacement1i_t> v2(
        make_displacement2d(ls.getSecondPoint()));

    auto v1m = MakeMoveMatrix<displacement1i_t>(dx, dy) * v1;
    auto v2m = MakeMoveMatrix<displacement1i_t>(dx, dy) * v2;

    ls.setFirstPoint({ v1m.col1[0], v1m.col1[1] });
    ls.setSecondPoint({ v2m.col1[0], v2m.col1[1] });
    return ls;
}

ra_core::figures2d::Circle MatrixCalculatorSimple::Move(
    ra_core::figures2d::Circle cr, displacement1i_t dx,
    displacement1i_t dy) const
{
    vec2h<ra_types::displacement1i_t> v1(make_displacement2d(cr.getCenter()));

    auto v1m = MakeMoveMatrix<displacement1i_t>(dx, dy) * v1;

    cr.setCenter({ v1m.col1[0], v1m.col1[1] });
    return cr;
}

/*
ra_core::figures2d::LineSegment MatrixCalculatorSimple::Stretch(
    ra_core::figures2d::LineSegment ls, float xCoef, float yCoef) const
{

    auto vecline = calc_distance(ls.getFirstPoint(), ls.getSecondPoint());
}
*/
} // namespace ra_services::geometric_transformations_in_homogeneous_coordinates
