#include "01_Elemantary.h"

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer> example_draw_dot()
{
    ra_services::color_rgb::ColorMap cm;

    ra_core::canvas2d::Canvas2d canvas; // TODO: forbid deafult ctor

    ra_core::figures2d::border border;

    ra_core::figures2d::Dot dot(100, 100, border);

    dot.setColorCode(cm.FindRgbCode(ra_services::color_rgb::color::White));
    dot.setColorCode({ 111, 111, 111 });

    canvas.Draw(dot);

    return canvas.getPixelBuffer();
}

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer>
example_draw_line_of_dots()
{
    ra_services::color_rgb::ColorMap cm;
    ra_core::canvas2d::Canvas2d      canvas;
    ra_core::figures2d::border       border;

    ra_core::figures2d::Dot dot(150, 150, border);

    dot.setColorCode(cm.FindRgbCode(ra_services::color_rgb::color::Green));

    for (int i = 0; i < 100; ++i)
    {
        dot.setX(150 + i);
        canvas.Draw(dot);
    }

    return canvas.getPixelBuffer();
}

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer>
example_naive_draw_lines()
{
    ra_services::color_rgb::ColorMap cm;
    ra_core::canvas2d::Canvas2d      canvas;
    ra_core::figures2d::border       border;

    ra_core::figures2d::LineSegment diag_line({ 300, 300 }, { 400, 400 },
                                              border);
    diag_line.setColorCode(cm.FindRgbCode(ra_services::color_rgb::color::Blue));
    canvas.Draw(diag_line);

    ra_core::figures2d::LineSegment cust_line({ 0, 0 }, { 47, 285 }, border);
    cust_line.setColorCode(cm.FindRgbCode(ra_services::color_rgb::color::Red));
    canvas.Draw(cust_line);

    return canvas.getPixelBuffer();
}

namespace ra_examples::cartesian2d
{

Elementary::Elementary()
{
    AddExample(example_draw_dot, "example_draw_dot");
    // AddExample(example_draw_line_of_dots, "example_draw_line_of_dots");
    AddExample(example_naive_draw_lines, "example_naive_draw_lines");
}

} // namespace ra_examples::cartesian2d
