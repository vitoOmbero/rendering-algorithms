#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <string>

namespace ra_types
{
/**
 * @brief The eScreenDirection enum - description of screenview based direction
 */
enum class eScreenDirection
{
    North,
    East,
    South,
    West
};

/**
 * @brief The eDirection1d enum - 1d direction
 */
enum class eDirection1d
{
    InfPos, ///< poisitive infinity
    InfNeg  ///< negative infinity
};
} // namespace ra_types
#endif // DIRECTIONS_H
