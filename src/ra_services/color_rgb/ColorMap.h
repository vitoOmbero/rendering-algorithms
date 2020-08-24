#ifndef COLORMAP_H
#define COLORMAP_H

#include <algorithm>
#include <map>

#include "color.h"
#include "rgb888.h"

namespace ra_services::color_rgb
{

using namespace ra_types;
/**
 * @brief The ColorMap class - explicit and possible color <-> rgb888
 * conversions
 * @details  Color rgb codes were taken from
 * http://shallowsky.com/colormatch/index.php
 */
class ColorMap final
{
public:
    ColorMap();

    color  FindColor(const rgb888 rgb) const;
    rgb888 FindRgbCode(const color colorName) const;
    color  FindClosestColor(const rgb888 rgb) const;

private:
    static const std::map<color, rgb888> color_map;
};
} // namespace ra_services::color_rgb
#endif // COLORMAP_H
