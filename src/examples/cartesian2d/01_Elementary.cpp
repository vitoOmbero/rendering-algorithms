#include <memory>
#include <vector>

#include "01_Elemantary.h"

#include "AlgorithmProxy.h"
#include "Canvas2d.h"
#include "Circle.h"
#include "ColorMap.h"
#include "Dot.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "examples_types.h"
#include "ra_types.h"
#include "renderer.h"

ra_core::pipeline::Canvas2d dots()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    figures2d::Dot   dot(0, 0, border);
    auto             col1 = cm.FindRgbCode(eColor::White);
    ra_types::rgb888 col2{ 111, 111, 111 };

    auto width  = renderer::CANVAS_WIDTH_DT;
    auto height = renderer::CANVAS_HEIGHT_DT;

    int step = 50;

    auto switchDotColor = [&dot, col1, col2]() {
        static bool bstate = false;
        bstate             = !bstate;
        if (bstate)
            dot.setColorCode(col1);
        else
            dot.setColorCode(col2);
    };

    for (ra_types::n0_t y = 0; y <= height; y += step)
    {
        dot.setY(y);
        switchDotColor();
        for (ra_types::n0_t x = 0; x <= width; x += step)
        {
            dot.setX(x);
            renderer::Draw(dot);
        }
    }

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d line_of_dots()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    ra_core::figures2d::Dot dot(150, 150, border);

    dot.setColorCode(cm.FindRgbCode(ra_services::color_rgb::eColor::Green));

    for (int i = 0; i < 200; ++i)
    {
        dot.setX(150 + i);
        renderer::Draw(dot);
    }

    return renderer::getCanvas();
}

void draw_star_and_cross_lines(const ra_services::color_rgb::ColorMap cm,
                               const ra_core::figures2d::border&      border)
{
    typedef ra_core::figures2d::LineSegment ls;
    typedef ra_services::color_rgb::eColor   col;

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

    auto w = 799;
    auto h = 599;
    auto x = 399;
    auto y = 299;
    auto d = 100;

    ls lin1({ x, y }, { x + d, y + d }, border);
    lin1.setColorCode(Red);
    ra_core::renderer::Draw(lin1);

    ls lin3({ x, y }, { w, y }, border);
    lin1.setColorCode(Yellow);
    ra_core::renderer::Draw(lin3);

    ls lin6({ x, y }, { x + d, y - d }, border);
    lin6.setColorCode(Indigo);
    ra_core::renderer::Draw(lin6);

    ls lin2({ x, y }, { x, y + d }, border);
    lin2.setColorCode(Orange);
    ra_core::renderer::Draw(lin2);

    ls lin5({ x, y }, { x, y - d }, border);
    lin5.setColorCode(Blue);
    ra_core::renderer::Draw(lin5);

    ls lin7({ x, y }, { x - d, y + d }, border);
    lin7.setColorCode(Purple);
    ra_core::renderer::Draw(lin7);

    ls lin4({ x, y }, { x - d, y }, border);
    lin4.setColorCode(Green);
    ra_core::renderer::Draw(lin4);

    ls lin8({ x, y }, { x - d, y - d }, border);
    lin8.setColorCode(Gray);
    ra_core::renderer::Draw(lin8);

    ls lin({ x, y }, { x, y }, border);
    lin.setColorCode(Cyan);
    ra_core::renderer::Draw(lin);

    ls lin9({ 0, 0 }, { 190, 150 }, border);
    lin9.setColorCode(Black);
    ra_core::renderer::Draw(lin9);

    ls lin10({ 190, 151 }, { 0, 1 }, border);
    lin10.setColorCode(Orange);
    ra_core::renderer::Draw(lin10);

    ls lin11({ 0, 150 }, { 190, 0 }, border);
    lin11.setColorCode(Green_springB);
    ra_core::renderer::Draw(lin11);

    ls lin12({ 190, 1 }, { 0, 151 }, border);
    lin12.setColorCode(Khaki1_l);
    ra_core::renderer::Draw(lin12);

    ls lin13({ 0, 0 }, { 150, h }, border);
    lin13.setColorCode(Lime);
    ra_core::renderer::Draw(lin13);

    ls lin14({ 151, h }, { 1, 0 }, border);
    lin14.setColorCode(Red);
    ra_core::renderer::Draw(lin14);

    ls lin15({ 150, 0 }, { 0, h }, border);
    lin15.setColorCode(Cyan);
    ra_core::renderer::Draw(lin15);

    ls lin16({ 1, h }, { 151, 0 }, border);
    lin16.setColorCode(Teal);
    ra_core::renderer::Draw(lin16);
}

ra_core::pipeline::Canvas2d naive_line_algo()
{
    ra_core::renderer::Init();
    using namespace ra_core::figures2d;
    using namespace ra_core::pipeline;
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::UseLineAlgorithm(rendering_algorithm::line_naive_hor_vert_diag);

    draw_star_and_cross_lines(cm, border);

    return ra_core::renderer::getCanvas();
}

ra_core::pipeline::Canvas2d bresenham_int_line()
{
    ra_core::renderer::Init();
    using namespace ra_core::figures2d;
    using namespace ra_core::pipeline;
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);

    draw_star_and_cross_lines(cm, border);

    return ra_core::renderer::getCanvas();
}

ra_core::pipeline::Canvas2d bresenham_defect_line()
{
    ra_core::renderer::Init();
    using namespace ra_core::figures2d;
    using namespace ra_core::pipeline;
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_defect);

    draw_star_and_cross_lines(cm, border);

    return ra_core::renderer::getCanvas();
}

ra_core::pipeline::Canvas2d bresenham_circles()
{
    ra_core::renderer::Init();
    using namespace ra_core::figures2d;
    using namespace ra_core::pipeline;
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::UseCircleAlgorithm(rendering_algorithm::circle_bresenham_int);

    displacement1i_t x = 400;
    displacement1i_t y = 300;

    Circle c({ x, y }, 150, border);
    c.setColorCode(cm.FindRgbCode(eColor::Purple_blue));

    ra_core::renderer::Draw(c);

    c.setCenter({ x - 50, y });
    renderer::Draw(c);
    c.setCenter({ x + 50, y });
    renderer::Draw(c);
    c.setCenter({ x, y - 50 });
    renderer::Draw(c);
    c.setCenter({ x, y + 50 });
    renderer::Draw(c);
    c.setCenter({ x + 50, y - 50 });
    renderer::Draw(c);
    c.setCenter({ x + 50, y + 50 });
    renderer::Draw(c);
    c.setCenter({ x - 50, y - 50 });
    renderer::Draw(c);
    c.setCenter({ x - 50, y + 50 });
    renderer::Draw(c);

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d triangles()
{
    ra_core::renderer::Init();
    using namespace ra_core::figures2d;
    using namespace ra_core::pipeline;
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);

    Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 }, border);
    tr.setColorCode(cm.FindRgbCode(eColor::Red));

    renderer::Draw(tr);

    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(eColor::Teal));
    renderer::Draw(tr);

    tr.setP1({ 0, 0 });
    tr.setP2({ 799, 599 });
    tr.setP3({ 199, 299 });
    renderer::Draw(tr);

    return renderer::getCanvas();
}

namespace ra_examples::cartesian2d
{

Elementary::Elementary()
{
    name = "01_elementary";
    AddExample(dots, "dots");
    AddExample(line_of_dots, "line_of_dots");
    AddExample(naive_line_algo, "naive_line_algo");
    AddExample(bresenham_defect_line, "bresenham_defect_line");
    AddExample(bresenham_int_line, "bresenham_int_line");
    AddExample(bresenham_circles, "bresenham_circles");
    AddExample(triangles, "triangles");
}

} // namespace ra_examples::cartesian2d
