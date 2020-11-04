#ifndef VIEWSPACE2D_H
#define VIEWSPACE2D_H

#include "direction1d.h"
#include "displacement2i.h"
#include "point2i.h"
#include "typedefs.h"

namespace ra_types
{

/**
 * @brief The Space2i struct - descriptive DO
 */
struct Space2i
{
    /**
     * @brief viewZeroPointOffset - offset of point zero point in local
     * coordinate system.
     */
    displacement2i viewZeroPointOffset;
    /**
     * @brief viewWidth - 0x viewable distance. Should be never 0.
     */
    distance1ui_t viewWidth{ 1 };
    /**
     * @brief viewHeight - 0y viewable distance. Should be never 0.
     */
    distance1ui_t viewHeight{ 1 };
    /**
     * @brief directionOx - 0x axis direction
     */
    Direction1d directionOx;
    /**
     * @brief directionOy - 0y axis direction
     */
    Direction1d directionOy;

    inline displacement1i_t getHighestVisibleOx() const
    {
        if (directionOx == Direction1d::kPosInf)
            return viewZeroPointOffset.x + displacement1i_t{ viewWidth - 1 };
        else
            return viewZeroPointOffset.x;
    }

    inline displacement1i_t getLowestVisibleOx() const
    {
        if (directionOx == Direction1d::kPosInf)
            return viewZeroPointOffset.x;
        else
            return viewZeroPointOffset.x - displacement1i_t{ viewWidth + 1 };
    }

    inline displacement1i_t getHighestVisibleOy() const
    {
        if (directionOy == Direction1d::kPosInf)
            return viewZeroPointOffset.y + displacement1i_t{ viewHeight - 1 };
        else
            return viewZeroPointOffset.y;
    }

    inline displacement1i_t getLowestVisibleOy() const
    {
        if (directionOy == Direction1d::kPosInf)
            return viewZeroPointOffset.y;
        else
            return viewZeroPointOffset.y - displacement1i_t{ viewHeight + 1 };
    }

    inline Point2i getHighestVisiblePoint() const
    {
        if (directionOx == Direction1d::kPosInf)
        {
            if (directionOy == Direction1d::kPosInf)
                return { getHighestVisibleOx(), getHighestVisibleOy() };
            else
                return { getHighestVisibleOx(), getLowestVisibleOy() };
        }
        else
        {
            if (directionOy == Direction1d::kPosInf)
                return { getLowestVisibleOx(), getHighestVisibleOy() };
            else
                return { getLowestVisibleOx(), getLowestVisibleOy() };
        }
    }

    inline Point2i getLowestVisiblePoint() const
    {
        if (directionOx == Direction1d::kPosInf)
        {
            if (directionOy == Direction1d::kPosInf)
                return { getLowestVisibleOx(), getLowestVisibleOy() };
            else
                return { getLowestVisibleOx(), getHighestVisibleOy() };
        }
        else
        {
            if (directionOy == Direction1d::kPosInf)
                return { getHighestVisibleOx(), getLowestVisibleOy() };
            else
                return { getHighestVisibleOx(), getHighestVisibleOy() };
        }
    }
};

} // namespace ra_types

#endif // VIEWSPACE2D_H
