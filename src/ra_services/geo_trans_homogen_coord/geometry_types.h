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
struct vec2
{
    T col1[2];

    vec2()
        : col1{ T(1), T(1) } {};

    vec2(const T arr[2])
        : col1{ arr[0], arr[1] } {};

    vec2(T val0, T val1)
        : col1{ val0, val1 } {};
};

template <typename T>
struct vec2h
{
    T col1[3];

    vec2h()
        : col1{ T(1), T(1), T(1) } {};

    vec2h(const T arr[3])
        : col1{ arr[0], arr[1], arr[2] } {};

    vec2h(T val0, T val1)
        : col1{ val0, val1, T(1) } {};
};

template <typename T>
vec2h<T> make_vec2h(vec2<T> v)
{
    return vec2h<T>{ { v.col1[0], v.col1[1], T(1) } };
}

template <typename T>
vec2<T> make_vec2(vec2h<T> v)
{
    return vec2<T>{ { v.col1[0], v.col1[1] } };
}

template <typename T>
struct mat2x2
{
    T col1[2];
    T col2[2];

    mat2x2()
        : col1{ T(1), T() }
        , col2{ T(), T(1) } {};

    mat2x2(T arr1[], T arr2[])
        : col1{ arr1[0], arr1[1] }
        , col2{ arr2[0], arr2[1] } {};
};

template <typename T>
struct mat2x2h
{
    T col1[3];
    T col2[3];
    T col3[3];

    mat2x2h()
        : col1{ T(1), T(), T() }
        , col2{ T(), T(1), T() }
        , col3{ T(), T(), T(1) } {};

    mat2x2h(T arr1[], T arr2[], T arr3[])
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
    vec2h<T> operator*(const vec2h<T> v) const
    {
        T arr[]{ this->col1[0] * v.col1[0] + this->col2[0] * v.col1[1] +
                     this->col3[0] * v.col1[2],
                 this->col1[1] * v.col1[0] + this->col2[1] * v.col1[1] +
                     this->col3[1] * v.col1[2],
                 this->col1[2] * v.col1[0] + this->col2[2] * v.col1[1] +
                     this->col3[2] * v.col1[2] };
        return vec2h<T>(arr);
    };

    /**
     * @brief operator *
     * @param m
     * @details If matrix A(size: l*m) (X) matrix B(size: m*n) to get matrix C,
     * then C[i][j] = SUM (A[i][k]*B[k][j]), where k=1..m; i=1..l; j=1..n;
     * @return mat2x2h<T>
     */
    mat2x2h<T> operator*(const mat2x2h<T> m) const
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

        return mat2x2h<T>(arr1, arr2, arr3);
    };
};

template <typename T>
mat2x2h<T> make_mat2x2h(mat2x2<T> m)
{
    return mat2x2h<T>{ { m.col1[0], m.col1[1], T() },
                       { m.col2[0], m.col2[1], T() },
                       { T(), T(), T(1) } };
}

template <typename T>
mat2x2<T> make_mat2x2(mat2x2h<T> m)
{
    return mat2x2<T>{ { m.col1[0], m.col1[1] }, { m.col2[0], m.col2[1] } };
}

#endif // VERTICAL_ORIENTED_VECTOR_NOTATION

} // namespace ra_services::geometric_transformations_in_homogeneous_coordinates

#endif // GEOMETRY_TYPES_H
