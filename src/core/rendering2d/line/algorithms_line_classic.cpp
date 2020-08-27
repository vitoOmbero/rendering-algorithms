#include "algorithms_line_classic.h"

#include <cmath>

namespace ra_core::rendering2d::line
{

template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

ra_types::n0_t bresenham_defect_diag_line(
    figures2d::point2d first, figures2d::point2d second,
    ra_types::rgb888 color_code, canvas2d::Rectangular1dDotBuffer& dotbuf)
{
    ra_types::n0_t counter = 0;
    dotbuf.Paint(color_code);
    typedef ra_types::displacement_t coord_t;
    // 1. income points
    ra_core::figures2d::point2d& closestToMinInf =
        first <= second ? first : second;
    ra_core::figures2d::point2d& farthestToMinInf =
        first <= second ? second : first;
    // 2. deltas along axes
    coord_t delta_x = farthestToMinInf.x - closestToMinInf.x;
    coord_t delta_y = farthestToMinInf.y - closestToMinInf.y;
    // 3. calculate signed steps for axes
    coord_t step_x = sign(delta_x);
    coord_t step_y = sign(delta_y);
    // 4. absolute deltas with var reuse
    delta_x = std::abs(delta_x);
    delta_y = std::abs(delta_y);
    // 5. calculate leading axe coefficient
    coord_t lac = delta_y - delta_x;
    // 6. analyze m and change leading axe from 0x to 0y if m > 0
    bool is_x_axe_leading = true;
    if (lac > 0)
    {
        is_x_axe_leading = false;
        coord_t temp     = delta_x;
        delta_x          = delta_y;
        delta_y          = temp;
    }
    // 7. init mistake value
    coord_t m = 2 * delta_y - delta_x;
    // 8. init current dot coords
    coord_t x = closestToMinInf.x;
    coord_t y = closestToMinInf.y;
    // 9. draw loop
    bool is_loop_continue = true;
    bool one_dot          = closestToMinInf == farthestToMinInf;
    while (is_loop_continue)
    {
        // 9.1 draw dot
        dotbuf.Mark({ x, y });
        ++counter;
        // 9.2 calc next coords
        if (m >= 0)
        {
            x += step_x;
            y += step_y;
            m -= 2 * delta_x; // mistake correction
        }
        else
        {
            if (is_x_axe_leading)
                x += step_x;
            else
                y += step_y;
            m += 2 * delta_y;
        }

        if (is_x_axe_leading)
        {
            is_loop_continue = x <= farthestToMinInf.x;
        }
        else
        {
            is_loop_continue = y <= farthestToMinInf.y;
        }
        if (one_dot)
            break;
    }
    // line is drawn!
    return counter;
}

ra_types::n0_t bresenham_int_line(
    ra_core::figures2d::point2d first, ra_core::figures2d::point2d second,
    ra_types::rgb888                           color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf)
{
    ra_types::n0_t counter = 0;
    dotbuf.Paint(color_code);
    typedef ra_types::displacement_t coord_t;

    coord_t& x1 = first.x;
    coord_t& x2 = second.x;
    coord_t& y1 = first.y;
    coord_t& y2 = second.y;

    auto draw = [&dotbuf, &counter](coord_t x, coord_t y) {
        dotbuf.Mark({ x, y });
        ++counter;
    };

    auto lineX = [&draw](coord_t x1, coord_t y1, coord_t x2, coord_t y2) {
        coord_t dx = x2 - x1;
        coord_t dy = y2 - y1;
        coord_t yi = 1;
        if (dy < 0)
        {
            yi = -1;
            dy = -dy;
        }
        coord_t D = 2 * dy - dx;
        coord_t y = y1;

        for (coord_t x = x1; x <= x2; ++x)
        {
            draw(x, y);
            if (D > 0)
            {
                y += yi;
                D -= 2 * dx;
            }
            D += 2 * dy;
        }
    };

    auto lineY = [&draw](coord_t x1, coord_t y1, coord_t x2, coord_t y2) {
        coord_t dx = x2 - x1;
        coord_t dy = y2 - y1;
        coord_t xi = 1;
        if (dx < 0)
        {
            xi = -1;
            dx = -dx;
        }
        coord_t D = 2 * dx - dy;
        coord_t x = x1;

        for (coord_t y = y1; y <= y2; ++y)
        {
            draw(x, y);
            if (D > 0)
            {
                x += xi;
                D -= 2 * dy;
            }
            D += 2 * dx;
        }
    };

    if (std::abs(y2 - y1) < std::abs(x2 - x1))
    {
        if (x1 > x2)
        {
            lineX(x2, y2, x1, y1);
        }
        else
        {
            lineX(x1, y1, x2, y2);
        }
    }
    else
    {
        if (y1 > y2)
        {
            lineY(x2, y2, x1, y1);
        }
        else
        {
            lineY(x1, y1, x2, y2);
        }
    }
    return counter;
}
} // namespace ra_core::rendering2d::line
