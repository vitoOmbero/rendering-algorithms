#ifndef COLORMAP_H
#define COLORMAP_H

#include <algorithm>
#include <map>

#include "color.h"
#include "rgb888.h"

// TODO: static service

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

    Color  FindColor(const Rgb888 rgb) const;
    Rgb888 FindRgbCode(const Color colorName) const;
    Color  FindClosestColor(const Rgb888 rgb) const;

private:
    static const std::map<Color, Rgb888> color_map_;
};
} // namespace ra_services::color_rgb
#endif // COLORMAP_H
