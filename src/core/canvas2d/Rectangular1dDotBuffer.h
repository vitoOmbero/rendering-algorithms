#ifndef RECTANGULAR1DPIXELBUFFER_H
#define RECTANGULAR1DPIXELBUFFER_H
#include <cassert>
#include <memory>
#include <vector>

#include "displacement2d.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::canvas2d
{

class Rectangular1dDotBuffer
{
public:
    Rectangular1dDotBuffer(
        ra_types::n0_t width, ra_types::n0_t height,
        ra_types::displacement2d zeroPointOffset,
        ra_types::rgb888         default_color_code = ra_types::rgb888());
    ~Rectangular1dDotBuffer();

    /**
     * @brief UpdateDotsNumber - utility function to count painted dots
     * @param inc - increment
     */
    void UpdateDotsNumber(ra_types::n0_t inc);

    /**
     * @brief Paint - set active color
     * @param code - color code
     */
    void Paint(ra_types::rgb888 code) { activeColor = code; };
    /**
     * @brief Mark - paint dot with selected paint color
     * @param point - dot cartesian coordinates
     */
    void Mark(ra_types::displacement2d point) { Mark(activeColor, point); };
    /**
     * @brief Mark - paint line segment with selected paint color
     * @param start - cartesian coordinates of first segment's end
     * @param end - cartesian coordinates of second segment's end
     */
    void Mark(ra_types::displacement2d start, ra_types::displacement2d end)
    {
        Mark(activeColor, start, end);
    };
    /**
     * @brief Mark - paint dot with selected paint color
     * @param code - color for current mark
     * @param point - dot cartesian coordinates
     */
    void Mark(ra_types::rgb888 code, ra_types::displacement2d point);
    /**
     * @brief Mark - paint line segment with selected paint color
     * @param code - color for current mark
     * @param start - cartesian coordinates of first segment's end
     * @param end - cartesian coordinates of second segment's end
     */
    void Mark(ra_types::rgb888 code, ra_types::displacement2d start,
              ra_types::displacement2d end);

    std::unique_ptr<std::vector<ra_types::rgb888>> CreateCopy() const;

    ra_types::n0_t       getDotsNumber() const;
    ra_types::n0_t getZeroIndex() const;
    ra_types::n0_t getLastIndex() const;
    ra_types::n0_t getZeroPointIndex() const;
    ra_types::distance_t getWidth() const;
    ra_types::distance_t getHeight() const;
    ra_types::n0_t       getDotSize() const;

private:
    friend ra_types::n0_t CalculateIndex(const Rectangular1dDotBuffer* buf,
                                         ra_types::displacement2d      point);

    std::vector<ra_types::rgb888>* dots;
    ra_types::n0_t                 width;
    ra_types::n0_t                 height;
    /**
     * @brief dotsNumber - number of used units
     * @details - updated after each Draw
     */
    ra_types::n0_t dotsNumber;
    /**
     * @brief dotSize - scale of canvas image unit
     * @details dotSize = 2 means canvas unit is 2x2 pixel group
     */
    ra_types::n0_t dotSize; // TODO: implement more sizes
    /**
     * @brief activeColor - current active color
     */
    ra_types::rgb888 activeColor;
    /**
     * @brief zeroIndex - named constant
     */
    const ra_types::n0_t zeroIndex = 0;
    /**
     * @brief lastIndex - \link RectangularPixelBuffer::highestVisiblePoint in
     * cartesian 2d coordinate system \endlink
     */
    ra_types::n0_t lastIndex;
    /**
     * @brief zeroPointIndex - O(0;0) in the cartesian 2d coordinate system
     * \link RectangularPixelBuffer::zeroPointOffset \endlink
     */
    ra_types::n0_t zeroPointIndex;
    /**
     * @brief lineLastIndex - canvas 2d point at (0;buffer_width)
     */
    ra_types::n0_t lineLastIndex;
};

} // namespace ra_core::canvas2d
#endif // RECTANGULAR1DPIXELBUFFER_H
