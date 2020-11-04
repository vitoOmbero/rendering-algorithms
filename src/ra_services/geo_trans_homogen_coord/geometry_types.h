#ifndef GEOMETRY_TYPES_H
#define GEOMETRY_TYPES_H

#include <cmath>

#include "ra_types.h"

// geometric transformations in homogeneous coordinates

namespace ra_services::geometric_transformations_in_homogeneous_coordinates
{

// reducing for loops usage & KISS

#define VERTICAL_ORIENTED_VECTOR_NOTATION

#ifdef VERTICAL_ORIENTED_VECTOR_NOTATION

template <typename T>
struct Vec2
{
    T col1[2];

    Vec2()
        : col1{ T(1), T(1) } {};

    explicit Vec2(const T arr[2])
        : col1{ arr[0], arr[1] } {};

    Vec2(T val0, T val1)
        : col1{ val0, val1 } {};
};

template <typename T>
struct Vec2h
{
    T col1[3];

    Vec2h()
        : col1{ T(1), T(1), T(1) } {};

    explicit Vec2h(const T arr[3])
        : col1{ arr[0], arr[1], arr[2] } {};

    Vec2h(T val0, T val1)
        : col1{ val0, val1, T(1) } {};
};

template <typename T>
Vec2h<T> VecToVec2h(Vec2<T> v)
{
    return Vec2h<T>{ { v.col1[0], v.col1[1], T(1) } };
}

template <typename T>
Vec2<T> VecToVec2(Vec2h<T> v)
{
    return Vec2<T>{ { v.col1[0], v.col1[1] } };
}

template <typename T>
struct Mat2x2
{
    T col1[2];
    T col2[2];

    Mat2x2()
        : col1{ T(1), T() }
        , col2{ T(), T(1) } {};

    Mat2x2(T arr1[], T arr2[])
        : col1{ arr1[0], arr1[1] }
        , col2{ arr2[0], arr2[1] } {};
};

template <typename T>
struct Mat2x2h
{
    T col1[3];
    T col2[3];
    T col3[3];

    Mat2x2h()
        : col1{ T(1), T(), T() }
        , col2{ T(), T(1), T() }
        , col3{ T(), T(), T(1) } {};

    Mat2x2h(T arr1[], T arr2[], T arr3[])
        : col1{ arr1[0], arr1[1], arr1[2] }
        , col2{ arr2[0], arr2[1], arr2[2] }
        , col3{ arr3[0], arr3[1], arr3[2] } {};

    /**
     * @brief operator *
     * @param v
     * @details Each line of matrix elements is translated into one vertical
     * vector element with help of SUM and multiplying each matrix element with
     * vector element.
     * @return vec2h<T>
     */
    Vec2h<T> operator*(const Vec2h<T> v) const
    {
        T arr[]{ this->col1[0] * v.col1[0] + this->col2[0] * v.col1[1] +
                     this->col3[0] * v.col1[2],
                 this->col1[1] * v.col1[0] + this->col2[1] * v.col1[1] +
                     this->col3[1] * v.col1[2],
                 this->col1[2] * v.col1[0] + this->col2[2] * v.col1[1] +
                     this->col3[2] * v.col1[2] };
        return Vec2h<T>(arr);
    };

    /**
     * @brief operator *
     * @param m
     * @details If matrix A(size: l*m) (X) matrix B(size: m*n) to get matrix C,
     * then C[i][j] = SUM (A[i][k]*B[k][j]), where k=1..m; i=1..l; j=1..n;
     * @return mat2x2h<T>
     */
    Mat2x2h<T> operator*(const Mat2x2h<T> m) const
    {
        T arr1[]{ this->col1[0] * m.col1[0] + this->col2[0] * m.col1[1] +
                      this->col3[0] * m.col1[2],
                  this->col1[0] * m.col2[0] + this->col2[0] * m.col2[1] +
                      this->col3[0] * m.col2[2],
                  this->col1[0] * m.col3[0] + this->col2[0] * m.col3[1] +
                      this->col3[0] * m.col3[2] };
        T arr2[]{ this->col1[1] * m.col1[0] + this->col2[1] * m.col1[1] +
                      this->col3[1] * m.col1[2],
                  this->col1[1] * m.col2[0] + this->col2[1] * m.col2[1] +
                      this->col3[1] * m.col2[2],
                  this->col1[1] * m.col3[0] + this->col2[1] * m.col3[1] +
                      this->col3[1] * m.col3[2] };
        T arr3[]{ this->col1[2] * m.col1[0] + this->col2[2] * m.col1[1] +
                      this->col3[2] * m.col1[2],
                  this->col1[2] * m.col2[0] + this->col2[2] * m.col2[1] +
                      this->col3[2] * m.col2[2],
                  this->col1[2] * m.col3[0] + this->col2[2] * m.col3[1] +
                      this->col3[2] * m.col3[2] };

        return Mat2x2h<T>(arr1, arr2, arr3);
    };
};

template <typename T>
Mat2x2h<T> MatToMat2x2h(Mat2x2<T> m)
{
    return Mat2x2h<T>{ { m.col1[0], m.col1[1], T() },
                       { m.col2[0], m.col2[1], T() },
                       { T(), T(), T(1) } };
}

template <typename T>
Mat2x2<T> MatToMat2x2(Mat2x2h<T> m)
{
    return Mat2x2<T>{ { m.col1[0], m.col1[1] }, { m.col2[0], m.col2[1] } };
}

#endif // VERTICAL_ORIENTED_VECTOR_NOTATION

} // namespace ra_services::geometric_transformations_in_homogeneous_coordinates

#endif // GEOMETRY_TYPES_H
