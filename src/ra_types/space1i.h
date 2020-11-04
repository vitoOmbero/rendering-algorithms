#ifndef VIEWSPACE1I_H
#define VIEWSPACE1I_H

#include "direction1d.h"
#include "typedefs.h"

namespace ra_types
{

struct Space1i
{
    /**
     * @brief lenght - viewable distance. Should never be zero.
     */
    distance1ui_t viewLength = 1;
    /**
     * @brief viewZeroPointOffset - offset of point O(0) in local coordinate
     * system
     */
    displacement1i_t viewZeroPointOffset;
    /**
     * @brief directionOx - 0x axis direction
     */
    Direction1d directionOx;

    inline displacement1i_t getHighestVisiblePoint() const
    {
        if (directionOx == Direction1d::kPosInf)
            return viewZeroPointOffset + displacement1i_t{ viewLength - 1 };
        else
            return viewZeroPointOffset;
    }

    inline displacement1i_t getLowestVisiblePoint() const
    {
        if (directionOx == Direction1d::kPosInf)
            return viewZeroPointOffset;
        else
            return viewZeroPointOffset - displacement1i_t{ viewLength + 1 };
    }
};

} // namespace ra_types

#endif // VIEWSPACE1I_H
