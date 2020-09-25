#ifndef IMAGE_TYPES_H
#define IMAGE_TYPES_H

#include <array>
#include <vector>

#include <rgb888.h>

namespace ra_types
{

template <std::size_t N>
using ImageRgb888Const = std::array<Rgb888, N>;

using ImageRgb888Volatile = std::vector<Rgb888>;

} // namespace ra_types

#endif // IMAGE_TYPES_H
