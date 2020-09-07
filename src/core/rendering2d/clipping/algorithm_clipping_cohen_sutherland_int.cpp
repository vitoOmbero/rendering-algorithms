#include "algorithm_clipping_cohen_sutherland_int.h"

inline int check_bit(int number, char bit_1_based_index)
{
    return number & (1 << (bit_1_based_index - 1));
}

unsigned char calculte_code(ra_types::point2i&          p,
                            ra_types::displacement1i_t& minX,
                            ra_types::displacement1i_t& minY,
                            ra_types::displacement1i_t& maxX,
                            ra_types::displacement1i_t& maxY)
{

    // U D R L
    unsigned char code{ 0 };

    code += (p.y > maxY) << 3;
    code += (p.y < minY) << 2;
    code += (p.x > maxX) << 1;
    code += p.x < minX;

    return code;
}

std::array<ra_types::point2i, 2>
ra_core::rendering2d::clipping::clipping_cohen_sutherland_int(
    ra_types::point2i first, ra_types::point2i second,
    ra_types::point2i rectwindow_maxX_maxY,
    ra_types::point2i rectwindow_minX_minY)
{
    // TODO: realize

    std::array<ra_types::point2i, 2> result{ first, second };

    auto P1 =
        calculte_code(first, rectwindow_minX_minY.x, rectwindow_minX_minY.y,
                      rectwindow_maxX_maxY.x, rectwindow_maxX_maxY.y);
    auto P2 =
        calculte_code(second, rectwindow_minX_minY.x, rectwindow_minX_minY.y,
                      rectwindow_maxX_maxY.x, rectwindow_maxX_maxY.y);

    unsigned char codes[]{ P1, P2 };

    // trivial visability
    if ((P1 + P2) == 0)
        return result;
    else
        // trivial invisability
        if ((P1 & P2))
        return std::array<ra_types::point2i, 2>{ { { -1, 0 } } };
    else
        // untrivial case (this check is not really needed)
        if ((P1 & P2) == 0)
    {
        /* parametric line eq:
         * y2 = m(x2 - x1) + y1
         * where m is the incline coefficient:
         *      y2 - y1
         *  m = -------
         *      x2 - x1
         *
         * intersection |
         * with window  |           X             |           Y             |
         * -------------|-------------------------|-------------------------|
         *    left      |         x_min           |  m * (x_min - x1) + y1  |
         * -------------|-------------------------|-------------------------|
         *    right     |         x_max           |  m * (x_max - x1) + y1  |
         * -------------|-------------------------|-------------------------|
         *    top       | x1 + 1/m * (y_max - y1) |         y_max           |
         * -------------|-------------------------|-------------------------|
         *    bot       | x1 + 1/m * (y_min - y1) |         y_min           |
         * -------------|-------------------------|-------------------------|
         *
         */

        for (auto i = 0; i < 2; ++i)
        {
            auto P = codes[i];
            if (P == 0)
                continue;
            auto& point = result[i];

            // order is imortant!

            if (check_bit(P, 1)) // left
            {
                point.x = rectwindow_minX_minY.x;
                point.y = first.y + (float)(second.y - first.y) /
                                        (second.x - first.x) *
                                        (rectwindow_minX_minY.x - first.x);
            }
            else if (check_bit(P, 2)) // right
            {
                point.x = rectwindow_maxX_maxY.x;
                point.y = first.y + (float)(second.y - first.y) /
                                        (second.x - first.x) *
                                        (rectwindow_maxX_maxY.x - first.x);
            }
            else if (check_bit(P, 3)) // bot
            {
                point.x = first.x + (float)(second.x - first.x) /
                                        (second.y - first.y) *
                                        (rectwindow_minX_minY.y - first.y);
                point.y = rectwindow_minX_minY.y;
            }
            else if (check_bit(P, 4)) // top
            {
                point.x = first.x + (float)(second.x - first.x) /
                                        (second.y - first.y) *
                                        (rectwindow_maxX_maxY.y - first.y);
                point.y = rectwindow_maxX_maxY.y;
            }
        }
    }
    return result;
}
