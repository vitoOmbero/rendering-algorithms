#include "ColorMap.h"
namespace ra_services::color_rgb
{
const std::map<eColor, rgb888> ColorMap::color_map = {
    { eColor::Black, rgb888(0, 0, 0) },
    { eColor::Navy, rgb888(0, 0, 128) },
    { eColor::Blue, rgb888(0, 0, 255) },
    { eColor::Green, rgb888(0, 128, 0) },
    { eColor::Teal, rgb888(0, 128, 128) },
    { eColor::Blue_light, rgb888(0, 128, 255) },
    { eColor::Lime, rgb888{ 0, 255, 0 } },
    { eColor::Green_springB, rgb888{ 0, 255, 128 } },
    { eColor::Cyan, rgb888{ 0, 255, 255 } },
    { eColor::Indigo, rgb888{ 75, 0, 130 } },
    { eColor::Maroon, rgb888{ 128, 0, 0 } },
    { eColor::Purple, rgb888{ 128, 0, 128 } },
    { eColor::Purple_blue, rgb888{ 128, 0, 255 } },
    { eColor::Olive, rgb888{ 128, 128, 0 } },
    { eColor::Gray, rgb888{ 128, 128, 128 } },
    { eColor::Sky_blue_dark, rgb888{ 128, 128, 255 } },
    { eColor::Silver, rgb888{ 192, 192, 192 } },
    { eColor::Violet, rgb888{ 238, 130, 238 } },
    { eColor::Red, rgb888{ 255, 0, 0 } },
    { eColor::Fuchsia_dark, rgb888{ 255, 0, 128 } },
    { eColor::Magenta, rgb888{ 255, 0, 255 } },
    { eColor::DarkOrange1B, rgb888{ 255, 128, 0 } },
    { eColor::Orange, rgb888{ 255, 165, 0 } },
    { eColor::Coral_lightd, rgb888{ 255, 128, 128 } },
    { eColor::Orchid1_l, rgb888{ 255, 128, 255 } },
    { eColor::Yellow, rgb888{ 255, 255, 0 } },
    { eColor::Khaki1_l, rgb888{ 255, 255, 128 } },
    { eColor::White, rgb888{ 255, 255, 255 } }
};

ColorMap::ColorMap()
{
    
}

eColor ColorMap::FindColor(const rgb888 rgb) const
{

    auto findResult =
        std::find_if(color_map.begin(), color_map.end(),
                     [&rgb](const std::pair<eColor, rgb888>& pair) {
                         return pair.second == rgb;
                     });

    if (findResult != std::end(color_map))
    {
        return findResult->first;
    }
    else
    {
        return eColor::No;
    }
}

rgb888 ColorMap::FindRgbCode(const eColor colorName) const
{
    auto findResult =
        std::find_if(color_map.begin(), color_map.end(),
                     [&colorName](const std::pair<eColor, rgb888>& pair) {
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

eColor ColorMap::FindClosestColor(const rgb888 rgb) const
{
    auto findResult =
        std::find_if(color_map.begin(), color_map.end(),
                     [&rgb](const std::pair<eColor, rgb888>& pair) {
                         return pair.second == rgb;
                     });

    if (findResult != std::end(color_map))
    {
        return findResult->first;
    }
    else
    {
        std::map<eColor, rgb888> potentials;

        for (auto pair : color_map)
        {
            potentials.insert(std::pair(pair.first, (rgb - pair.second)));
        }

        auto closest =
            std::min_element(potentials.begin(), potentials.end(),
                             [](const std::pair<eColor, rgb888>& pair_left,
                                const std::pair<eColor, rgb888>& pair_right) {
                                 return pair_left.second < pair_right.second;
                             });
        return closest->first;
    }
}
} // namespace ra_services::color_rgb
