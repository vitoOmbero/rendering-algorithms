#include "algorithms_filling_naive.h"

//:^) where is std::swap ?
#include <algorithm>
#include <initializer_list>
#include <string_view>
#include <utility>
#include <vector>

using namespace ra_types;
using namespace ra_core::figures2d;

typedef displacement_t coord_t;

// TODO: add doxygen friendly annotations for example of very bad realization

struct terriffying_naive_bad_filling_pack
{

    void line_positions(point2d p1, point2d p2,
                        std::vector<point2d>& positions_output,
                        n0_t&                 pixels_count_output)
    {
        coord_t x1 = p1.x;
        coord_t y1 = p1.y;
        coord_t x2 = p2.x;
        coord_t y2 = p2.y;

        auto lineX = [&](coord_t x1, coord_t y1, coord_t x2, coord_t y2) {
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
                positions_output.push_back({ x, y });
                pixels_count_output++;
                if (D > 0)
                {
                    y += yi;
                    D -= 2 * dx;
                }
                D += 2 * dy;
            }
        };

        auto lineY = [&](coord_t x1, coord_t y1, coord_t x2, coord_t y2) {
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
                positions_output.push_back({ x, y });
                pixels_count_output++;
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
    }

    struct borders
    {
        std::vector<point2d> left_border;
        std::vector<point2d> right_border;
    };

    borders get_borders(std::vector<point2d>& v)
    {
        v.shrink_to_fit();
        assert(v.size() == 3);

        /*
        point2d max{ std::max({ v[0].x, v[1].x, v[2].x }),
                     std::max({ v[0].y, v[1].y, v[2].y }) };
        point2d min{ std::min({ v[0].x, v[1].x, v[2].x }),
                     std::min({ v[0].y, v[1].y, v[2].y }) };
*/
        auto       LD = new std::vector<point2d>;
        auto       RD = new std::vector<point2d>;
        distance_t countL{ 0 };
        distance_t countR{ 0 };

        // imagine all possible triangles with 3 verteces
        // & collect info about left and right sides

        // 1) 2 eq x coords:  1L | 1R
        // 2) 2 eq y coords:  3rd has x max : 1L | 2R
        //                    3rd has x min : 2L | 1R
        // 3) 2 in top:       righter is higher : 2L | 1R
        //                    lefter is higher  : 1L | 2R
        // 4) 1 in top:       righter is lower : 2L | 1R
        //                    lefter is lower  : 1L | 2R

        // try to find mistakes

        /*
        if (v[0].y == v[2].y && v[1].y == min.y)
        {
            line_positions(v[0], v[1], *LD, countL);
            line_positions(v[2], v[1], *RD, countR);
        }
        else if (v[0].y == v[2].y && v[1].y == max.y)
        {
            line_positions(v[0], v[2], *LD, countL);
            line_positions(v[1], v[2], *RD, countR);
        }
        else if (v[0].x == min.x && v[1].x == v[2].x)
        { // undefined direction
            if (v[1].y < v[2].y)
            {
                line_positions(v[2], v[0], *LD, countL);
                line_positions(v[0], v[1], *LD, countL);
                line_positions(v[2], v[1], *RD, countR);
            }
            else
            {
                line_positions(v[1], v[0], *LD, countL);
                line_positions(v[0], v[2], *LD, countL);
                line_positions(v[1], v[2], *RD, countR);
            }
        }
        else if (v[2].x == max.x && v[0].x == v[1].x)
        { // undefined direction
            if (v[1].y > v[0].y)
            {
                line_positions(v[1], v[0], *LD, countL);
                line_positions(v[1], v[2], *RD, countR);
                line_positions(v[2], v[0], *RD, countR);
            }
            else
            {
                line_positions(v[0], v[1], *LD, countL);
                line_positions(v[0], v[2], *RD, countR);
                line_positions(v[2], v[1], *RD, countR);
            }
        }
        else if (v[2].y == max.y)
        {
            line_positions(v[2], v[0], *LD, countL);
            line_positions(v[0], v[1], *LD, countL);
            line_positions(v[2], v[1], *RD, countR);
        }
        else if (v[0].y == max.y)
        {
            line_positions(v[0], v[1], *LD, countL);
            line_positions(v[0], v[2], *RD, countR);
            line_positions(v[2], v[1], *RD, countR);
        }

*/

        // kind of sort?
        if (v[0].y > v[1].y)
            std::swap(v[0], v[1]);
        if (v[0].y > v[2].y)
            std::swap(v[0], v[2]);
        if (v[1].y > v[2].y)
            std::swap(v[1], v[2]);

        // now read RD as lesser border

        line_positions(v[0], v[1], *LD, countL);
        line_positions(v[1], v[2], *LD, countL);
        line_positions(v[2], v[0], *RD, countR);

        auto distinct_and_sort_by_y_coord =
            [&](std::vector<point2d>* bigger_side) {
                auto iter = std::unique(
                    bigger_side->begin(), bigger_side->end(),
                    [](point2d a, point2d b) -> bool { return a.y == b.y; });
                bigger_side->erase(iter, bigger_side->end());
                bigger_side->shrink_to_fit();
                std::sort(
                    bigger_side->begin(), bigger_side->end(),
                    [](point2d a, point2d b) -> bool { return a.y < b.y; });
            };

        distinct_and_sort_by_y_coord(RD); // just for sure
        distinct_and_sort_by_y_coord(LD);

        return borders{ *LD, *RD };
    }
};

static terriffying_naive_bad_filling_pack
    gebr; ///< good example of bad realization

ra_types::n0_t ra_core::rendering2d::filling::fill3_naive_hr(
    ra_core::figures2d::point2d first, ra_core::figures2d::point2d second,
    ra_core::figures2d::point2d third, ra_types::rgb888 color_code,
    ra_core::canvas2d::Rectangular1dDotBuffer& dotbuf)
{
    n0_t counter = 0;

    std::vector<point2d> v{ first, second, third };
    auto                 borders = gebr.get_borders(v);

    auto LD = &borders.left_border;  // now read as larger
    auto RD = &borders.right_border; // now read as lesser

    // because of bresenham's line algorithm precision one border is slightly
    // bigger
    auto count = LD->size() > RD->size() ? RD->size() : LD->size();
    // filling horizontal line by line
    for (ulong i = 0; i < count - 1; ++i)
    {
        point2d larger = LD->at(i);
        point2d lesser = RD->at(i);
        // line we need
        if (larger.y == lesser.y)
            for (int j = lesser.x; j < larger.x; ++j)
            {
                dotbuf.Mark(color_code, { j, larger.y });
                ++counter;
            }
    }
    return counter;
}
