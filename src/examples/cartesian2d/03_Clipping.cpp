#include "03_Clipping.h"

#include "Canvas2d.h"
#include "ColorMap.h"
#include "color.h"
#include "typedefs.h"

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer>
example_draw_triangles_line_cicle_cutting()
{
    using namespace ra_services::color_rgb;
    using namespace ra_core::figures2d;
    using namespace ra_core::canvas2d;
    using namespace ra_types;

    ColorMap cm;
    Canvas2d canvas(Canvas2d::Shape, cm.FindRgbCode(color::Black));
    border   border;

    canvas.UseLineAlgorithm(
        AlgorithmProxy::rendering_algorithm::line_bresenham_int);
    canvas.UseFillingTriangle(
        AlgorithmProxy::rendering_algorithm::fill3_line_sweeping);

    Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 }, border);
    tr.setColorCode(cm.FindRgbCode(color::Orange));
    canvas.Draw(tr);

    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(color::Teal));
    canvas.Draw(tr);

    Triangle tr2({ 200, 50 }, { 300, 500 }, { 400, 250 }, border);
    tr2.setColorCode(cm.FindRgbCode(color::Blue));
    Triangle tr3({ 500, 250 }, { 600, 50 }, { 700, 500 }, border);
    tr3.setColorCode(cm.FindRgbCode(color::Purple_blue));

    canvas.Draw(tr2);
    canvas.Draw(tr3);

    tr2.setP1(tr2.getP1() + 150);
    tr2.setP2(tr2.getP2() + 150);
    tr2.setP3(tr2.getP3() + 150);
    tr3.setP1(tr2.getP1() + 150);
    tr3.setP2(tr2.getP2() + 150);
    tr3.setP3(tr2.getP3() + 150);

    canvas.Draw(tr2);
    canvas.Draw(tr3);

    Circle c({ 300, 50 }, 150, border);
    c.setColorCode(cm.FindRgbCode(color::Red));
    canvas.Draw(c);

    return canvas.getPixelBuffer();
}

namespace ra_examples::cartesian2d
{

Clipping::Clipping()
{
    AddExample(example_draw_triangles_line_cicle_cutting,
               "example_draw_triangles_line_cicle_cutting");
}
} // namespace ra_examples::cartesian2d
