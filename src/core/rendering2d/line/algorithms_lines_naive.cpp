#include "algorithms_lines_naive.h"
#include "typedefs.h"

ra_types::n0_t ra_core::rendering2d::line::naive_dot(
    ra_types::displacement1i_t x, ra_types::displacement1i_t y,
    ra_types::Rgb888 color_code, ra_core::pipeline::RenderingTargetBase& target)
{
    target.Paint(color_code);
    target.Mark({ x, y });
    return 1;
}

ra_types::n0_t ra_core::rendering2d::line::naive_hv_line(
    ra_types::Point2i first, ra_types::Point2i second,
    ra_types::Rgb888 color_code, ra_core::pipeline::RenderingTargetBase& target)
{
    target.Paint(color_code);

    ra_types::Point2i& closestToZero  = first <= second ? first : second;
    ra_types::Point2i& farthestToZero = first <= second ? second : first;
    ra_types::displacement1i_t c = 0;

    for (auto i = closestToZero.x, j = closestToZero.y;
         i <= farthestToZero.x && j <= farthestToZero.y; ++i, ++j)
    {
        target.Mark({ i, j });
        ++c;
    }
    return c;
}
