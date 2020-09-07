#include "03_Clipping.h"

#include "AlgorithmProxy.h"
#include "Canvas2d.h"
#include "Circle.h"
#include "ColorMap.h"
#include "Dot.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "algorithms_registry.h"
#include "examples_types.h"
#include "ra_types.h"
#include "renderer.h"

void draw_cross()
{
    using namespace ra_core;
    using namespace ra_core::figures2d;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    auto x = 399;
    auto y = 299;
    auto w = 799;
    auto h = 599;
    auto d = 25;

    LineSegment net_v({ x + d, y }, { w, y }, border);
    net_v.setColorCode(cm.FindRgbCode(eColor::Gray));
    LineSegment net_h({ x, y + d }, { x, h }, border);
    net_h.setColorCode(cm.FindRgbCode(eColor::Gray));
    renderer::Draw(net_v);
    renderer::Draw(net_h);
    net_v.setSecondPoint({ 0, y });
    net_h.setSecondPoint({ x, 0 });
    renderer::Draw(net_v);
    renderer::Draw(net_h);
    LineSegment d1({ x + d, y + d }, { w, h }, border);
    LineSegment d2({ x - d, y + d }, { 0, h }, border);
    LineSegment d3({ x + d, y - d }, { w, 0 }, border);
    LineSegment d4({ x - d, y - d }, { 0, 0 }, border);
    d1.setColorCode(cm.FindRgbCode(eColor::Gray));
    d2.setColorCode(cm.FindRgbCode(eColor::Gray));
    d3.setColorCode(cm.FindRgbCode(eColor::Gray));
    d4.setColorCode(cm.FindRgbCode(eColor::Gray));
    renderer::Draw(d1);
    renderer::Draw(d2);
    renderer::Draw(d3);
    renderer::Draw(d4);
}

void draw_aim()
{
    using namespace ra_core;
    using namespace ra_core::figures2d;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    auto x = 399;
    auto y = 299;
    auto w = 799;
    auto h = 599;
    auto d = 25;

    auto vx_left  = x - d;
    auto vx_right = x + d;
    auto hx_left  = vx_left - d;
    auto hx_right = vx_right + d;

    auto hy_top = y - d;
    auto hy_bot = y + d;
    auto vy_top = hy_top - d;
    auto vy_bot = hy_bot + d;

    LineSegment net_v({ vx_left, vy_top }, { vx_left, 0 }, border);
    net_v.setColorCode(cm.FindRgbCode(eColor::Lime));
    renderer::Draw(net_v);
    net_v.setFirstPoint({ vx_right, vy_top });
    net_v.setSecondPoint({ vx_right, 0 });
    renderer::Draw(net_v);
    net_v.setFirstPoint({ vx_left, vy_bot });
    net_v.setSecondPoint({ vx_left, h });
    renderer::Draw(net_v);
    net_v.setFirstPoint({ vx_right, vy_bot });
    net_v.setSecondPoint({ vx_right, h });
    renderer::Draw(net_v);

    LineSegment net_h({ hx_right, hy_top }, { w, hy_top }, border);
    net_h.setColorCode(cm.FindRgbCode(eColor::Orange));
    renderer::Draw(net_h);
    net_h.setFirstPoint({ hx_right, hy_bot });
    net_h.setSecondPoint({ w, hy_bot });
    renderer::Draw(net_h);
    net_h.setFirstPoint({ hx_left, hy_top });
    net_h.setSecondPoint({ 0, hy_top });
    renderer::Draw(net_h);
    net_h.setFirstPoint({ hx_left, hy_bot });
    net_h.setSecondPoint({ 0, hy_bot });
    renderer::Draw(net_h);

    net_h.setColorCode(cm.FindRgbCode(eColor::Purple_blue));
    net_v.setColorCode(cm.FindRgbCode(eColor::Purple_blue));
    net_h.setFirstPoint({ 0, y });
    net_h.setSecondPoint({ w, y });
    net_v.setFirstPoint({ x, 0 });
    net_v.setSecondPoint({ x, h });
    renderer::Draw(net_h);
    renderer::Draw(net_v);
}

void draw_figures()
{
    using namespace ra_core;
    using namespace ra_core::figures2d;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 }, border);
    tr.setColorCode(cm.FindRgbCode(eColor::Orange));
    renderer::Draw(tr);

    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(eColor::Teal));
    renderer::Draw(tr);

    Triangle tr2({ 200, 50 }, { 300, 500 }, { 400, 250 }, border);
    tr2.setColorCode(cm.FindRgbCode(eColor::Blue));
    Triangle tr3({ 500, 250 }, { 600, 50 }, { 700, 500 }, border);
    tr3.setColorCode(cm.FindRgbCode(eColor::Purple_blue));

    renderer::Draw(tr2);
    renderer::Draw(tr3);

    tr2.setP1(tr2.getP1() + 150);
    tr2.setP2(tr2.getP2() + 150);
    tr2.setP3(tr2.getP3() + 150);
    tr3.setP1(tr2.getP1() + 150);
    tr3.setP2(tr2.getP2() + 150);
    tr3.setP3(tr2.getP3() + 150);

    renderer::Draw(tr2);
    renderer::Draw(tr3);

    Circle c({ 300, 50 }, 150, border);
    c.setColorCode(cm.FindRgbCode(eColor::Red));
    renderer::Draw(c);
}

ra_core::pipeline::Canvas2d cutting()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    draw_figures();

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d cohen_sutherland_aim_before()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    // renderer::UseClippingWindow(        100, 50,
    // AlgorithmProxy::clipping_algorithm::cohen_sutherland);

    draw_aim();

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d cohen_sutherland_aim_after()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    renderer::UseClippingWindow(100, 50, clipping_algorithm::cohen_sutherland);

    draw_aim();

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d cohen_sutherland_cross_before()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);
    /*
        renderer::UseClippingWindow(
            100, 50, AlgorithmProxy::clipping_algorithm::cohen_sutherland);
    */
    draw_cross();

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d cohen_sutherland_cross_after()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    renderer::UseClippingWindow(100, 50, clipping_algorithm::cohen_sutherland);

    draw_cross();

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d
example_draw_triangles_line_cicle_cutting_clipping_kb()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    renderer::UseClippingWindow(100, 50, clipping_algorithm::cohen_sutherland);

    draw_figures();

    return renderer::getCanvas();
}

namespace ra_examples::cartesian2d
{

Clipping::Clipping()
{
    name = "03_clpping";
    AddExample(cutting, "cutting");
    AddExample(cohen_sutherland_aim_before, "cohen_sutherland_aim_before");
    AddExample(cohen_sutherland_aim_after, "cohen_sutherland_aim_after");
    AddExample(cohen_sutherland_cross_before, "cohen_sutherland_cross_before");
    AddExample(cohen_sutherland_cross_after, "cohen_sutherland_cross_after");
}
} // namespace ra_examples::cartesian2d
