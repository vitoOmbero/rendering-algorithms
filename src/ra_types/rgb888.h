#ifndef RGB888_H
#define RGB888_H

#include "typedefs.h"

namespace ra_types
{

/**
 * @brief Storage class for color data.
 */
struct rgb888 final
{
    uchar r;
    uchar g;
    uchar b;

    rgb888();

    /**
     * Special constructor
     * @param val One value for r,g and b color codes.
     */
    rgb888(uchar val);

    /**
     * @brief rgb888 utility constructor
     * @param r_ red value code 0-255
     * @param g_ green value 0-255
     * @param b_ blue value 0-255
     */
    rgb888(uchar r_, uchar g_, uchar b_);

    bool operator==(const rgb888& b) const;

    bool operator!=(const rgb888& b) const;

    bool operator<(const rgb888& b) const;

    rgb888 operator-(const rgb888& b) const;
    /**
     * @brief blue - helper getter
     * @return at least 16bit int
     */
    int blue() const { return static_cast<int>(b); };
    /**
     * @brief green - helper getter
     * @return at least 16bit int
     */
    int green() const { return static_cast<int>(g); };
    /**
     * @brief red - helper getter
     * @return at least 16bit int
     */
    int red() const { return static_cast<int>(r); };
};

} // namespace ra_types
#endif // RGB888_H
