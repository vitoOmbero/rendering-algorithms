#ifndef MATRIXCALCULATORSIMPLE_H
#define MATRIXCALCULATORSIMPLE_H

#include <array>

#include "Circle.h"
#include "LineSegment.h"
#include "Quadrangle.h"
#include "Triangle.h"

#include "geometry_types.h"

namespace ra_services::geometric_transformations_in_homogeneous_coordinates
{

template <>
struct vec2<ra_types::displacement1i_t>
{
    ra_types::displacement1i_t col1[2]{ 1, 1 };

    vec2()
        : col1{ 1, 1 } {};

    vec2(const ra_types::displacement1i_t arr[2])
        : col1{ arr[0], arr[1] } {};

    vec2(ra_types::displacement2i d2d)
        : col1{ d2d.x, d2d.y } {};
};

template <>
struct vec2h<ra_types::displacement1i_t>
{
    ra_types::displacement1i_t col1[3]{ 1, 1, 1 };

    vec2h()
        : col1{ 1, 1, 1 } {};

    vec2h(const ra_types::displacement1i_t arr[3])
        : col1{ arr[0], arr[1], arr[3] } {};

    vec2h(ra_types::displacement2i d2d)
        : col1{ d2d.x, d2d.y, 1 } {};
};

enum class eNotation
{
    VerticalOriented,
    // NOTE: HorizontalOriented notation is not supported currently
};

class MatrixCalculatorSimple
{
public:
    MatrixCalculatorSimple();

    eNotation getNotation() const;

    template <typename T>
    mat2x2h<T> MakeMoveMatrix(ra_types::displacement1i_t dx,
                              ra_types::displacement1i_t dy) const;

    template <typename T>
    mat2x2h<T> MakeStretchMatrix(float xCoef, float yCoef) const;
    /*
        ra_core::figures2d::LineSegment Stretch(ra_core::figures2d::LineSegment
       ls, float xCoef, float yCoef) const;
    */
    ra_core::figures2d::LineSegment Move(ra_core::figures2d::LineSegment ls,
                                         ra_types::displacement1i_t      dx,
                                         ra_types::displacement1i_t dy) const;
    /**
     * @brief Move
     * @param cr
     * @param dx
     * @param dy
     * @return
     */
    ra_core::figures2d::Circle Move(ra_core::figures2d::Circle cr,
                                    ra_types::displacement1i_t dx,
                                    ra_types::displacement1i_t dy) const;

    /**
     * @brief Move - moves each point in provided std::array
     * @param arr - non const reference to std::array
     * @param dx
     * @param dy
     */
    template <ra_types::n1_t N>
    void Move(std::array<ra_types::point2i, N>& arr,
              ra_types::displacement1i_t        dx,
              ra_types::displacement1i_t        dy) const;

private:
    const eNotation notation{ 0 };
};

template <ra_types::n1_t N>
void MatrixCalculatorSimple::Move(std::array<ra_types::point2i, N>& arr,
                                  ra_types::displacement1i_t        dx,
                                  ra_types::displacement1i_t        dy) const
{
    auto M = MakeMoveMatrix<ra_types::displacement1i_t>(dx, dy);

    for (auto i = arr.begin(); i != arr.end(); ++i)
    {
        vec2h<ra_types::displacement1i_t> v1(ra_types::make_displacement2d(*i));
        auto                              v1m = M * v1;
        *i                                    = { v1m.col1[0], v1m.col1[1] };
    }
}

template <typename T>
mat2x2h<T> MatrixCalculatorSimple::MakeMoveMatrix(
    ra_types::displacement1i_t dx, ra_types::displacement1i_t dy) const
{
    mat2x2h<T> mat;
    mat.col3[0] = T(dx);
    mat.col3[1] = T(dy);
    return mat;
}

template <typename T>
mat2x2h<T> MatrixCalculatorSimple::MakeStretchMatrix(float xCoef,
                                                     float yCoef) const
{
    mat2x2h<T> mat;
    mat.col1[2] = T(xCoef);
    mat.col2[2] = T(yCoef);
    return mat;
}

} // namespace ra_services::geometric_transformations_in_homogeneous_coordinates
#endif // MATRIXCALCULATORSIMPLE_H
