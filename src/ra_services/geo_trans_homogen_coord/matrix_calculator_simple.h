#ifndef MATRIXCALCULATORSIMPLE_H
#define MATRIXCALCULATORSIMPLE_H

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>

#include "circle.h"
#include "line_segment.h"
#include "quadrangle.h"
#include "triangle.h"

#include "geometry_types.h"

namespace ra_services::geometric_transformations_in_homogeneous_coordinates
{

enum class RotationDirection2d
{
    kClockwise,
    KAntiClock
};

enum class Notation
{
    kVerticalOriented,
    // NOTE: HorizontalOriented notation is not supported currently
};

class MatrixCalculatorSimple
{
public:
    MatrixCalculatorSimple();

    [[nodiscard]] Notation getNotation() const;

    template <typename T>
    [[nodiscard]] Mat2x2h<T> MoveMatrix(ra_types::displacement1i_t dx,
                          ra_types::displacement1i_t dy) const;

    template <typename T>
    [[nodiscard]] Mat2x2h<T> MoveMatrixReverse(ra_types::displacement1i_t dx,
                                 ra_types::displacement1i_t dy) const;

    template <typename T>
    [[nodiscard]] Mat2x2h<T> StretchMatrix(float xCoef, float yCoef) const;

    template <typename T>
    Mat2x2h<T> RotateClockwiseMatrix(T angle) const;

    template <typename T>
    Mat2x2h<T> RotateAntiClockMatrix(T angle) const;

    [[nodiscard]] ra_core::figures2d::LineSegment Move(ra_core::figures2d::LineSegment ls,
                                         ra_types::displacement1i_t      dx,
                                         ra_types::displacement1i_t dy) const;
    /**
     * @brief Move
     * @param cr
     * @param dx
     * @param dy
     * @return
     */
    [[nodiscard]] ra_core::figures2d::Circle Move(ra_core::figures2d::Circle cr,
                                    ra_types::displacement1i_t dx,
                                    ra_types::displacement1i_t dy) const;

    /**
     * @brief Move - moves each point in provided std::array
     * @param arr - non const reference to std::array
     * @param dx
     * @param dy
     */
    template <ra_types::n1_t N>
    void Move(std::array<ra_types::Point2i, N>& vertices,
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
    void Stretch(std::array<ra_types::Point2i, N>& vertices, float xCoef,
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
        std::array<ra_types::Point2i, N>& vertices, T angle,
        RotationDirection2d dir = RotationDirection2d::kClockwise) const;

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
        std::array<ra_types::Point2i, N>& vertices, T angle,
        ra_types::Point2i   rcenter,
        RotationDirection2d dir = RotationDirection2d::kClockwise) const;

private:
    const Notation notation_{ 0 };
};

template <std::size_t N, typename T>
void MatrixCalculatorSimple::Rotate(std::array<ra_types::Point2i, N>& vertices,
                                    T angle, ra_types::Point2i rcenter,
                                    RotationDirection2d dir) const
{
    auto R = dir == RotationDirection2d::kClockwise
                 ? RotateClockwiseMatrix<T>(angle)
                 : RotateAntiClockMatrix<T>(angle);

    auto M  = MoveMatrix<float>(rcenter.x, rcenter.y);
    auto MR = MoveMatrixReverse<float>(rcenter.x, rcenter.y);

    for (auto i = vertices.begin(); i != vertices.end(); ++i)
    {
        Vec2h<T> vhp(i->x, i->y);

        vhp = M * R * MR * vhp;

        i->x = std::lrint(vhp.col1[0]);
        i->y = std::lrint(vhp.col1[1]);
    }
}

template <std::size_t N, typename T>
void MatrixCalculatorSimple::Rotate(std::array<ra_types::Point2i, N>& vertices,
                                    T angle, RotationDirection2d dir) const
{

    auto centroid = std::accumulate(
        vertices.cbegin(), vertices.cend(), ra_types::Point2i{ 0, 0 },
        [](ra_types::Point2i sum_point, ra_types::Point2i const& point) {
            return sum_point + point;
        });

    Rotate(vertices, angle, centroid, dir);
}

template <typename T>
Mat2x2h<T> MatrixCalculatorSimple::RotateAntiClockMatrix(T angle) const
{
    Mat2x2h<T> R;
    auto       cos = std::cos(angle);
    auto       sin = std::sin(angle);
    R.col1[0]      = cos;
    R.col1[1]      = -sin;
    R.col2[0]      = sin;
    R.col2[1]      = cos;
    return R;
}

template <typename T>
Mat2x2h<T> MatrixCalculatorSimple::RotateClockwiseMatrix(T angle) const
{
    Mat2x2h<T> R;
    auto       cos = std::cos(angle);
    auto       sin = std::sin(angle);
    R.col1[0]      = cos;
    R.col1[1]      = sin;
    R.col2[0]      = -sin;
    R.col2[1]      = cos;
    return R;
}

template <typename T>
Mat2x2h<T> MatrixCalculatorSimple::MoveMatrixReverse(
    ra_types::displacement1i_t dx, ra_types::displacement1i_t dy) const
{
    return MoveMatrix<T>(-dx, -dy);
}

template <ra_types::n1_t N>
void MatrixCalculatorSimple::Stretch(std::array<ra_types::Point2i, N>& vertices,
                                     float xCoef, float yCoef) const
{
    auto S = StretchMatrix<float>(xCoef, yCoef);

    // point with minimum potential should be moved to zero point

    auto* min = std::min_element(vertices.cbegin(), vertices.cend());

    auto M  = MoveMatrix<float>(min->x, min->y);
    auto MR = MoveMatrixReverse<float>(min->x, min->y);

    for (auto i = vertices.begin(); i != vertices.end(); ++i)
    {
        Vec2h<float> vhp1(i->x, i->y);

        vhp1 = M * S * MR * vhp1;

        i->x = std::lrint(vhp1.col1[0]);
        i->y = std::lrint(vhp1.col1[1]);
    }
}

template <ra_types::n1_t N>
void MatrixCalculatorSimple::Move(std::array<ra_types::Point2i, N>& vertices,
                                  ra_types::displacement1i_t        dx,
                                  ra_types::displacement1i_t        dy) const
{
    if (dx == 0 && dy == 0)
        return;

    auto M = MoveMatrix<ra_types::displacement1i_t>(dx, dy);

    for (auto i = vertices.begin(); i != vertices.end(); ++i)
    {
        Vec2h<ra_types::displacement1i_t> v1((*i).x, (*i).y);
        auto                              v1m = M * v1;
        *i                                    = { v1m.col1[0], v1m.col1[1] };
    }
}

template <typename T>
Mat2x2h<T> MatrixCalculatorSimple::MoveMatrix(
    ra_types::displacement1i_t dx, ra_types::displacement1i_t dy) const
{
    Mat2x2h<T> mat;
    mat.col3[0] = T(dx);
    mat.col3[1] = T(dy);
    return mat;
}

template <typename T>
Mat2x2h<T> MatrixCalculatorSimple::StretchMatrix(float xCoef, float yCoef) const
{
    Mat2x2h<T> mat;
    mat.col1[0] = T(xCoef);
    mat.col2[1] = T(yCoef);
    return mat;
}

} // namespace ra_services::geometric_transformations_in_homogeneous_coordinates
#endif // MATRIXCALCULATORSIMPLE_H
