#ifndef BORDER_H
#define BORDER_H

#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::figures2d
{

/**
 * @brief The border struct - lightweight geometrical border abstaction
 */
struct border
{
    enum border_placement
    {
        logical,   ///< a half of boder image is inside the area of figure
        inclusive, ///< whole image is inside
        exclusive  ///< whole image is outside
    };

    enum border_type
    {
        solid,
        dotted,
        stripped
    };

    /**
     * @brief Thickness Size in dots
     */
    ra_types::n1_t Thickness = 1;

    /**
     * @brief type pointer
     */
    border_type type = solid;

    /**
     * @brief gap - Size in dots.
     * @details Depends on type.
     * Solid: logical constraint is (gap == 0), but practically can be ignored;
     * Dotted: natural numbers;
     * Stripped: natural numbers > 1.
     */
    ra_types::n0_t gap = 0;

    /**
     * @brief pin - Size in dots.
     * @details Depends on type.
     * Solid: logical constraint is (dash == 0), but practically can be ignored;
     * Dotted: logical constraint is (dash == thikness), but practically can be
     * ignored; Stripped: logical constraint is (dash > 1).
     */
    ra_types::n0_t dash = 0;

    /**
     * @brief placement indicator
     */
    border_placement placement = logical;

    /**
     * @brief color value
     */
    ra_types::rgb888 color = ra_types::rgb888(0);
};
} // namespace ra_core::figures2d

#endif // BORDER_H
