#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <cstdint>

namespace ra_types
{

// NOTE: distinct uchar and byte: https://en.cppreference.com/w/cpp/types/byte
typedef unsigned char uchar;

// NOTE: rendering algorithms showcases use implicitly defined cartesian 2d
// coordinate system. Add namespaces (for static coordinate systems) or
// coordinate system service (for dynamic switch in runtime) when adding new
// coordinate system

typedef void*
    coordinate_t; ///< placeholder type or coordinate in any coordinate system

/**
 * @brief distance_t lightweight abstraction for linear distance
 */
typedef std::uint64_t distance_t;
/**
 * @brief displacement_t lightweight abstraction for linear path, displacement
 * @details E.g. The main idea of coordinate in coodinate system is the
 * displacement for point from the zero point by each axis.
 */
typedef std::int32_t displacement_t;
/**
 * @brief size_t - lightweight abstraction for linear and geometrical size
 */
typedef std::uint64_t size_t;
/**
 * @brief n0_t non-negative positives
 */
typedef std::uint64_t n0_t;

} // namespace ra_types

#endif // TYPEDEFS_H
