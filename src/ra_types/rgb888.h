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

    rgb888(uchar r_, uchar g_, uchar b_);

    bool operator==(const rgb888& b) const;

    bool operator!=(const rgb888& b) const;
};

} // namespace ra_types
#endif // RGB888_H
