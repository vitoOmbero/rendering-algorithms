#include "algorithm_filling_3v_line_sweeping.h"
#include "ColorMap.h"
#include "algorithms_line_classic.h"
#include "algorithms_lines_naive.h"

inline void bubble_sort_by_y(ra_types::Point2i& p1, ra_types::Point2i& p2,
                             ra_types::Point2i& p3)
{
    if (p1.y > p2.y)
        std::swap(p1, p2);
    if (p1.y > p2.y)
        std::swap(p1, p2);
    if (p2.y > p3.y)
        std::swap(p2, p3);
}

ra_types::n0_t ra_core::rendering2d::filling::fill3_line_sweeping_phase01_sides(
    ra_types::Point2i first, ra_types::Point2i second, ra_types::Point2i third,
    ra_types::Rgb888 color_code, ra_core::pipeline::RenderingTargetBase& dotbuf)
{
    ra_types::n0_t counter = 0;

    bubble_sort_by_y(first, second, third);

    ra_services::color_rgb::ColorMap cm;

    color_code = cm.FindRgbCode(ra_services::color_rgb::Color::kLime);
    counter += line::bresenham_int_line(first, second, color_code, dotbuf);
    counter += line::bresenham_int_line(second, third, color_code, dotbuf);

    color_code = cm.FindRgbCode(ra_services::color_rgb::Color::kViolet);
    line::bresenham_int_line(third, first, color_code, dotbuf);

    return counter;
}

ra_types::n0_t ra_core::rendering2d::filling::fill3_line_sweeping_phase02_sides(
    ra_types::Point2i first, ra_types::Point2i second, ra_types::Point2i third,
    ra_types::Rgb888 color_code, ra_core::pipeline::RenderingTargetBase& dotbuf)
{

    auto fillColor = color_code;

    ra_types::n0_t counter = 0;

    bubble_sort_by_y(first, second, third);

    ra_services::color_rgb::ColorMap cm;

    int total_height = third.y - first.y;
    for (int y = first.y; y <= second.y; ++y)
    {
        int   segment_height = second.y - first.y + 1;
        float alpha          = (float)(y - first.y) / total_height;
        float beta           = (float)(y - first.y) / segment_height;

        typedef ra_types::displacement2i vec2i;

        vec2i A = make_displacement2d(first + (third - first) * alpha);
        vec2i B = make_displacement2d(first + (second - first) * beta);

        color_code = cm.FindRgbCode(ra_services::color_rgb::Color::kViolet);
        counter += line::naive_dot(A.x, y, color_code, dotbuf);

        color_code = cm.FindRgbCode(ra_services::color_rgb::Color::kLime);
        counter += line::naive_dot(B.x, y, color_code, dotbuf);
    }

    for (int y = second.y; y <= third.y; ++y)
    {
        int   segment_height = third.y - second.y + 1;
        float alpha          = (float)(y - first.y) / total_height;
        float beta           = (float)(y - second.y) / segment_height;

        typedef ra_types::displacement2i vec2i;

        vec2i A = make_displacement2d(first + (third - first) * alpha);
        vec2i B = make_displacement2d(second + (third - second) * beta);

        if (A.x > B.x)
            std::swap(A, B);
        dotbuf.Mark(fillColor, { A.x, y }, { B.x, y });
    }

    return counter;
}

ra_types::n0_t ra_core::rendering2d::filling::fill3_line_sweeping(
    ra_types::Point2i first, ra_types::Point2i second, ra_types::Point2i third,
    ra_types::Rgb888 color_code, ra_core::pipeline::RenderingTargetBase& dotbuf)
{

    ra_types::n0_t counter = 0;

    bubble_sort_by_y(first, second, third);

    ra_services::color_rgb::ColorMap cm;

    int total_height = third.y - first.y;

    for (int i = 0; i < total_height; ++i)
    {
        bool upper_half = i > second.y - first.y || second.y == first.y;
        int  segment_height =
            upper_half ? third.y - second.y : second.y - first.y;
        float alpha = (float)i / total_height;
        float beta =
            (float)(i - (upper_half ? second.y - first.y : 0)) / segment_height;

        typedef ra_types::displacement2i vec2i;

        vec2i A = make_displacement2d(first + (third - first) * alpha);
        vec2i B = upper_half
                      ? make_displacement2d(second + (third - second) * beta)
                      : make_displacement2d(first + (second - first) * beta);

        if (A.x > B.x)
            std::swap(A, B);
        dotbuf.Mark(color_code, { A.x, first.y + i }, { B.x, first.y + i });
    }

    return counter;
}
