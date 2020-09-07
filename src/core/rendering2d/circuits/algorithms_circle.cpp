#include "algorithms_circle.h"

ra_types::n0_t ra_core::rendering2d::circuits::bresenham_int_circle(
    ra_types::point2i center, ra_types::distance1ui_t radius,
    ra_types::rgb888 color_code, ra_core::pipeline::RenderingTargetBase& dotbuf)
{
    ra_types::n0_t counter = 0;
    dotbuf.Paint(color_code);
    typedef ra_types::displacement1i_t coord_t;

    auto draw = [&dotbuf, &counter](coord_t x, coord_t y) {
        dotbuf.Mark({ x, y });
        ++counter;
    };

    auto&   c     = center;
    coord_t x     = 0;
    coord_t y     = coord_t(radius);
    coord_t delta = 1 - 2 * coord_t(radius);
    coord_t error = 0;

    while (y >= 0)
    {

        draw(c.x + x, c.y + y);
        draw(c.x + x, c.y - y);
        draw(c.x - x, c.y + y);
        draw(c.x - x, c.y - y);

        error = 2 * (delta + y) - 1;
        if ((delta < 0) && (error <= 0))
        {
            delta += 2 * ++x + 1;
            continue;
        }
        if ((delta > 0) && (error > 0))
        {
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - y--);
    }

    return counter;
}
