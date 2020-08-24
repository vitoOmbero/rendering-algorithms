#include "ColorMap.h"
namespace ra_services::color_rgb
{
const std::map<color, rgb888> ColorMap::color_map = {
    { color::Black, rgb888(0, 0, 0) },
    { color::Navy, rgb888(0, 0, 128) },
    { color::Blue, rgb888(0, 0, 255) },
    { color::Green, rgb888(0, 128, 0) },
    { color::Teal, rgb888(0, 128, 128) },
    { color::Blue_light, rgb888(0, 128, 255) },
    { color::Lime, rgb888{ 0, 255, 0 } },
    { color::Green_springB, rgb888{ 0, 255, 128 } },
    { color::Cyan, rgb888{ 0, 255, 255 } },
    { color::Indigo, rgb888{ 75, 0, 130 } },
    { color::Maroon, rgb888{ 128, 0, 0 } },
    { color::Purple, rgb888{ 128, 0, 128 } },
    { color::Purple_blue, rgb888{ 128, 0, 255 } },
    { color::Olive, rgb888{ 128, 128, 0 } },
    { color::Gray, rgb888{ 128, 128, 128 } },
    { color::Sky_blue_dark, rgb888{ 128, 128, 255 } },
    { color::Silver, rgb888{ 192, 192, 192 } },
    { color::Violet, rgb888{ 238, 130, 238 } },
    { color::Red, rgb888{ 255, 0, 0 } },
    { color::Fuchsia_dark, rgb888{ 255, 0, 128 } },
    { color::Magenta, rgb888{ 255, 0, 255 } },
    { color::DarkOrange1B, rgb888{ 255, 128, 0 } },
    { color::Orange, rgb888{ 255, 165, 0 } },
    { color::Coral_lightd, rgb888{ 255, 128, 128 } },
    { color::Orchid1_l, rgb888{ 255, 128, 255 } },
    { color::Yellow, rgb888{ 255, 255, 0 } },
    { color::Khaki1_l, rgb888{ 255, 255, 128 } },
    { color::White, rgb888{ 255, 255, 255 } }
};

ColorMap::ColorMap()
{
    
}

color ColorMap::FindColor(const rgb888 rgb) const
{

    auto findResult =
        std::find_if(color_map.begin(), color_map.end(),
                     [&rgb](const std::pair<color, rgb888>& pair) {
                         return pair.second == rgb;
                     });

    if (findResult != std::end(color_map))
    {
        return findResult->first;
    }
    else
    {
        return color::No;
    }
}

rgb888 ColorMap::FindRgbCode(const color colorName) const
{
    auto findResult =
        std::find_if(color_map.begin(), color_map.end(),
                     [&colorName](const std::pair<color, rgb888>& pair) {
                         return pair.first == colorName;
                     });

    if (findResult != std::end(color_map))
    {
        return findResult->second;
    }
    else
    {
        return rgb888();
    }
}

color ColorMap::FindClosestColor(const rgb888 rgb) const
{
    auto findResult =
        std::find_if(color_map.begin(), color_map.end(),
                     [&rgb](const std::pair<color, rgb888>& pair) {
                         return pair.second == rgb;
                     });

    if (findResult != std::end(color_map))
    {
        return findResult->first;
    }
    else
    {
        std::map<color, rgb888> potentials;

        for (auto pair : color_map)
        {
            potentials.insert(std::pair(pair.first, (rgb - pair.second)));
        }

        auto closest =
            std::min_element(potentials.begin(), potentials.end(),
                             [](const std::pair<color, rgb888>& pair_left,
                                const std::pair<color, rgb888>& pair_right) {
                                 return pair_left.second < pair_right.second;
                             });
        return closest->first;
    }
}
} // namespace ra_services::color_rgb
