#include "01_Elemantary.h"
#include "AlgorithmProxy.h"

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
example_draw_lines_naive()
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

void draw_star_and_cross_lines(const ra_services::color_rgb::ColorMap cm,
                               const ra_core::canvas2d::Canvas2d&     canvas,
                               const ra_core::figures2d::border&      border)
{
    typedef ra_core::figures2d::LineSegment ls;
    typedef ra_services::color_rgb::color   col;

    auto Red           = cm.FindRgbCode(col::Red);
    auto Yellow        = cm.FindRgbCode(col::Yellow);
    auto Indigo        = cm.FindRgbCode(col::Indigo);
    auto Orange        = cm.FindRgbCode(col::Orange);
    auto Blue          = cm.FindRgbCode(col::Blue);
    auto Purple        = cm.FindRgbCode(col::Purple);
    auto Green         = cm.FindRgbCode(col::Green);
    auto Gray          = cm.FindRgbCode(col::Gray);
    auto Black         = cm.FindRgbCode(col::Black);
    auto Green_springB = cm.FindRgbCode(col::Green_springB);
    auto Khaki1_l      = cm.FindRgbCode(col::Khaki1_l);
    auto Lime          = cm.FindRgbCode(col::Lime);
    auto Cyan          = cm.FindRgbCode(col::Cyan);
    auto Teal          = cm.FindRgbCode(col::Teal);

    ls lin1({ 87, 87 }, { 177, 177 }, border);
    lin1.setColorCode(Red);
    canvas.Draw(lin1);

    ls lin3({ 87, 87 }, { 177, 87 }, border);
    lin1.setColorCode(Yellow);
    canvas.Draw(lin3);

    ls lin6({ 87, 87 }, { 177, 27 }, border);
    lin6.setColorCode(Indigo);
    canvas.Draw(lin6);

    ls lin2({ 87, 87 }, { 87, 177 }, border);
    lin2.setColorCode(Orange);
    canvas.Draw(lin2);

    ls lin5({ 87, 87 }, { 87, 27 }, border);
    lin5.setColorCode(Blue);
    canvas.Draw(lin5);

    ls lin7({ 87, 87 }, { 27, 177 }, border);
    lin7.setColorCode(Purple);
    canvas.Draw(lin7);

    ls lin4({ 87, 87 }, { 27, 87 }, border);
    lin4.setColorCode(Green);
    canvas.Draw(lin4);

    ls lin8({ 87, 87 }, { 27, 27 }, border);
    lin8.setColorCode(Gray);
    canvas.Draw(lin8);

    ls lin({ 87, 87 }, { 87, 87 }, border);
    lin.setColorCode(Cyan);
    canvas.Draw(lin);

    ls lin9({ 0, 0 }, { 190, 13 }, border);
    lin9.setColorCode(Black);
    canvas.Draw(lin9);

    ls lin10({ 190, 14 }, { 0, 1 }, border);
    lin10.setColorCode(Orange);
    canvas.Draw(lin10);

    ls lin11({ 0, 13 }, { 190, 0 }, border);
    lin11.setColorCode(Green_springB);
    canvas.Draw(lin11);

    ls lin12({ 190, 1 }, { 0, 14 }, border);
    lin12.setColorCode(Khaki1_l);
    canvas.Draw(lin12);

    ls lin13({ 0, 0 }, { 13, 190 }, border);
    lin13.setColorCode(Lime);
    canvas.Draw(lin13);

    ls lin14({ 14, 190 }, { 1, 0 }, border);
    lin14.setColorCode(Red);
    canvas.Draw(lin14);

    ls lin15({ 13, 0 }, { 0, 190 }, border);
    lin15.setColorCode(Cyan);
    canvas.Draw(lin15);

    ls lin16({ 1, 190 }, { 14, 0 }, border);
    lin16.setColorCode(Teal);
    canvas.Draw(lin16);
}

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer>
example_draw_lines_bresenham_int()
{
    ra_services::color_rgb::ColorMap cm;
    ra_core::canvas2d::Canvas2d      canvas;
    ra_core::figures2d::border       border;

    canvas.UseLineAlgorithm(ra_core::canvas2d::AlgorithmProxy::
                                rendering_algorithm::line_bresenham_int);
    draw_star_and_cross_lines(cm, canvas, border);

    return canvas.getPixelBuffer();
}

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer>
example_draw_lines_bresenham_defect()
{
    ra_services::color_rgb::ColorMap cm;
    ra_core::canvas2d::Canvas2d      canvas;
    ra_core::figures2d::border       border;

    canvas.UseLineAlgorithm(ra_core::canvas2d::AlgorithmProxy::
                                rendering_algorithm::line_bresenham_defect);
    draw_star_and_cross_lines(cm, canvas, border);

    return canvas.getPixelBuffer();
}

namespace ra_examples::cartesian2d
{

Elementary::Elementary()
{
    AddExample(example_draw_dot, "example_draw_dot");
    // AddExample(example_draw_line_of_dots, "example_draw_line_of_dots");
    AddExample(example_draw_lines_naive, "example_draw_lines_naive");
    AddExample(example_draw_lines_bresenham_int,
               "example_draw_lines_bresenham_int");
    AddExample(example_draw_lines_bresenham_defect,
               "example_draw_lines_bresenham_defect");
}

} // namespace ra_examples::cartesian2d
