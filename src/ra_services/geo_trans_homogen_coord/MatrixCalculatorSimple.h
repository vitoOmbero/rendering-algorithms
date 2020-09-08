#ifndef MATRIXCALCULATORSIMPLE_H
#define MATRIXCALCULATORSIMPLE_H

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>

#include "Circle.h"
#include "LineSegment.h"
#include "Quadrangle.h"
#include "Triangle.h"

#include "geometry_types.h"

namespace ra_services::geometric_transformations_in_homogeneous_coordinates
{

enum class eRotationDirection2d
{
    Clockwise,
    Anticlock
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
    mat2x2h<T> MakeMoveMatrixReverse(ra_types::displacement1i_t dx,
                                     ra_types::displacement1i_t dy) const;

    template <typename T>
    mat2x2h<T> MakeStretchMatrix(float xCoef, float yCoef) const;

    template <typename T>
    mat2x2h<T> MakeRotateClockwiseMatrix(T angle) const;

    template <typename T>
    mat2x2h<T> MakeRotateAntiClockMatrix(T angle) const;

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
    void Move(std::array<ra_types::point2i, N>& vertices,
              ra_types::displacement1i_t        dx = 0,
              ra_types::displacement1i_t        dy = 0) const;

    /**
     * @brief Stretch - moves each point in provided std::array
     * @param vertices - non const reference to std::array of vertices in
     * carthesian 2d coordinate system
     * @param xCoef - streching above Ox
     * @param yCoef - streching above Oy
     */
    template <ra_types::n1_t N>
    void Stretch(std::array<ra_types::point2i, N>& vertices, float xCoef,
                 float yCoef) const;

    /**
     * @brief Rotate - rotate each point in provided std::array relative to
     * centroid
     * @param vertices - non const reference to std::array of vertices in
     * carthesian 2d coordinate system
     * @param angle - rotation angle (should be positive) (measured in radians)
     * @param dir - rotatetion direction enum pointer
     */
    template <std::size_t N, typename T>
    void Rotate(
        std::array<ra_types::point2i, N>& vertices, T angle,
        eRotationDirection2d dir = eRotationDirection2d::Clockwise) const;

    /**
     * @brief Rotate - rotate each point in provided std::array relative to
     * rcenter point
     * @param vertices - non const reference to std::array of vertices in
     * carthesian 2d coordinate system
     * @param angle - rotation angle (should be positive) (measured in radians)
     * @param dir - rotatetion direction enum pointer
     */
    template <std::size_t N, typename T>
    void Rotate(
        std::array<ra_types::point2i, N>& vertices, T angle,
        ra_types::point2i    rcenter,
        eRotationDirection2d dir = eRotationDirection2d::Clockwise) const;

private:
    const eNotation notation{ 0 };
};

template <std::size_t N, typename T>
void MatrixCalculatorSimple::Rotate(std::array<ra_types::point2i, N>& vertices,
                                    T angle, ra_types::point2i rcenter,
                                    eRotationDirection2d dir) const
{
    auto R = dir == eRotationDirection2d::Clockwise
                 ? MakeRotateClockwiseMatrix<T>(angle)
                 : MakeRotateAntiClockMatrix<T>(angle);

    auto M  = MakeMoveMatrix<float>(rcenter.x, rcenter.y);
    auto MR = MakeMoveMatrixReverse<float>(rcenter.x, rcenter.y);

    for (auto i = vertices.begin(); i != vertices.end(); ++i)
    {
        vec2h<T> vhp(i->x, i->y);

        vhp = M * R * MR * vhp;

        i->x = std::lrint(vhp.col1[0]);
        i->y = std::lrint(vhp.col1[1]);
    }
}

template <std::size_t N, typename T>
void MatrixCalculatorSimple::Rotate(std::array<ra_types::point2i, N>& vertices,
                                    T angle, eRotationDirection2d dir) const
{

    auto centroid = std::accumulate(
        vertices.cbegin(), vertices.cend(), ra_types::point2i{ 0, 0 },
        [](ra_types::point2i sum_point, ra_types::point2i const& point) {
            return sum_point + point;
        });

    Rotate(vertices, angle, centroid, dir);
}

template <typename T>
mat2x2h<T> MatrixCalculatorSimple::MakeRotateAntiClockMatrix(T angle) const
{
    mat2x2h<T> R;
    auto       cos = std::cos(angle);
    auto       sin = std::sin(angle);
    R.col1[0]      = cos;
    R.col1[1]      = -sin;
    R.col2[0]      = sin;
    R.col2[1]      = cos;
    return R;
}

template <typename T>
mat2x2h<T> MatrixCalculatorSimple::MakeRotateClockwiseMatrix(T angle) const
{
    mat2x2h<T> R;
    auto       cos = std::cos(angle);
    auto       sin = std::sin(angle);
    R.col1[0]      = cos;
    R.col1[1]      = sin;
    R.col2[0]      = -sin;
    R.col2[1]      = cos;
    return R;
}

template <typename T>
mat2x2h<T> MatrixCalculatorSimple::MakeMoveMatrixReverse(
    ra_types::displacement1i_t dx, ra_types::displacement1i_t dy) const
{
    return MakeMoveMatrix<T>(-dx, -dy);
}

template <ra_types::n1_t N>
void MatrixCalculatorSimple::Stretch(std::array<ra_types::point2i, N>& vertices,
                                     float xCoef, float yCoef) const
{
    auto S = MakeStretchMatrix<float>(xCoef, yCoef);

    // point with minimum potential should be moved to zero point

    auto* min = std::min_element(vertices.cbegin(), vertices.cend());

    auto M  = MakeMoveMatrix<float>(min->x, min->y);
    auto MR = MakeMoveMatrixReverse<float>(min->x, min->y);

    for (auto i = vertices.begin(); i != vertices.end(); ++i)
    {
        vec2h<float> vhp1(i->x, i->y);

        vhp1 = M * S * MR * vhp1;

        i->x = std::lrint(vhp1.col1[0]);
        i->y = std::lrint(vhp1.col1[1]);
    }
}

template <ra_types::n1_t N>
void MatrixCalculatorSimple::Move(std::array<ra_types::point2i, N>& vertices,
                                  ra_types::displacement1i_t        dx,
                                  ra_types::displacement1i_t        dy) const
{
    if (dx == 0 && dy == 0)
        return;

    auto M = MakeMoveMatrix<ra_types::displacement1i_t>(dx, dy);

    for (auto i = vertices.begin(); i != vertices.end(); ++i)
    {
        vec2h<ra_types::displacement1i_t> v1((*i).x, (*i).y);
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
    mat.col1[0] = T(xCoef);
    mat.col2[1] = T(yCoef);
    return mat;
}

} // namespace ra_services::geometric_transformations_in_homogeneous_coordinates
#endif // MATRIXCALCULATORSIMPLE_H
