#include "02_Shapes.h"

#include "AlgorithmProxy.h"
#include "Canvas2d.h"
#include "Circle.h"
#include "ColorMap.h"
#include "Dot.h"
#include "examples_types.h"
#include "typedefs.h"

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer>
example_draw_triangles_filled_01_naive()
{
    ra_services::color_rgb::ColorMap cm;
    ra_core::canvas2d::Canvas2d      canvas;
    ra_core::figures2d::border       border;

    canvas.UseLineAlgorithm(ra_core::canvas2d::AlgorithmProxy::
                                rendering_algorithm::line_bresenham_int);
    canvas.setDrawingMode(ra_core::canvas2d::Canvas2d::Shape);

    ra_core::figures2d::Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 },
                                    border);
    tr.setColorCode(cm.FindRgbCode(ra_services::color_rgb::color::Orange));

    canvas.Draw(tr);
    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(ra_services::color_rgb::color::Teal));
    canvas.Draw(tr);

    return canvas.getPixelBuffer();
}

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer>
example_draw_triangles_filled_02_line_sweeping_ph01()
{
    using namespace ra_services::color_rgb;
    using namespace ra_core::figures2d;
    using namespace ra_core::canvas2d;

    ColorMap cm;
    Canvas2d canvas(Canvas2d::Shape, cm.FindRgbCode(color::Black));
    border   border;

    canvas.UseLineAlgorithm(
        AlgorithmProxy::rendering_algorithm::line_bresenham_int);
    canvas.UseFillingTriangle(
        AlgorithmProxy::rendering_algorithm::fill3_line_sweeping_phase_01);

    ra_core::figures2d::Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 },
                                    border);

    tr.setColorCode(cm.FindRgbCode(color::Orange));
    canvas.Draw(tr);

    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(color::Teal));
    canvas.Draw(tr);

    ra_core::figures2d::Triangle tr2({ 200, 50 }, { 300, 500 }, { 400, 250 },
                                     border);
    tr2.setColorCode(cm.FindRgbCode(color::Blue));
    ra_core::figures2d::Triangle tr3({ 500, 250 }, { 600, 50 }, { 700, 500 },
                                     border);
    tr2.setColorCode(cm.FindRgbCode(color::Purple_blue));

    canvas.Draw(tr2);
    canvas.Draw(tr3);

    return canvas.getPixelBuffer();
}

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer>
example_draw_triangles_filled_02_line_sweeping_ph02()
{
    using namespace ra_services::color_rgb;
    using namespace ra_core::figures2d;
    using namespace ra_core::canvas2d;

    ColorMap cm;
    Canvas2d canvas(Canvas2d::Shape, cm.FindRgbCode(color::Black));
    border   border;

    canvas.UseLineAlgorithm(
        AlgorithmProxy::rendering_algorithm::line_bresenham_int);
    canvas.UseFillingTriangle(
        AlgorithmProxy::rendering_algorithm::fill3_line_sweeping_phase_02);

    ra_core::figures2d::Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 },
                                    border);

    tr.setColorCode(cm.FindRgbCode(color::Orange));
    canvas.Draw(tr);

    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(color::Teal));
    canvas.Draw(tr);

    ra_core::figures2d::Triangle tr2({ 200, 50 }, { 300, 500 }, { 400, 250 },
                                     border);
    tr2.setColorCode(cm.FindRgbCode(color::Blue));
    ra_core::figures2d::Triangle tr3({ 500, 250 }, { 600, 50 }, { 700, 500 },
                                     border);
    tr3.setColorCode(cm.FindRgbCode(color::Purple_blue));

    canvas.Draw(tr2);
    canvas.Draw(tr3);

    return canvas.getPixelBuffer();
}

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer>
example_draw_triangles_filled_02_line_sweeping_ph03_full()
{
    using namespace ra_services::color_rgb;
    using namespace ra_core::figures2d;
    using namespace ra_core::canvas2d;

    ColorMap cm;
    Canvas2d canvas(Canvas2d::Shape, cm.FindRgbCode(color::Black));
    border   border;

    canvas.UseLineAlgorithm(
        AlgorithmProxy::rendering_algorithm::line_bresenham_int);
    canvas.UseFillingTriangle(
        AlgorithmProxy::rendering_algorithm::fill3_line_sweeping);

    ra_core::figures2d::Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 },
                                    border);

    tr.setColorCode(cm.FindRgbCode(color::Orange));
    canvas.Draw(tr);

    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(color::Teal));
    canvas.Draw(tr);

    ra_core::figures2d::Triangle tr2({ 200, 50 }, { 300, 500 }, { 400, 250 },
                                     border);
    tr2.setColorCode(cm.FindRgbCode(color::Blue));
    ra_core::figures2d::Triangle tr3({ 500, 250 }, { 600, 50 }, { 700, 500 },
                                     border);
    tr3.setColorCode(cm.FindRgbCode(color::Purple_blue));

    canvas.Draw(tr2);
    canvas.Draw(tr3);

    return canvas.getPixelBuffer();
}

namespace ra_examples::cartesian2d
{

Shapes::Shapes()
{
    AddExample(example_draw_triangles_filled_01_naive,
               "example_draw_triangles_filled_01_naive");
    AddExample(example_draw_triangles_filled_02_line_sweeping_ph01,
               "example_draw_triangles_filled_02_line_sweeping_ph01");
    AddExample(example_draw_triangles_filled_02_line_sweeping_ph02,
               "example_draw_triangles_filled_02_line_sweeping_ph02");
    AddExample(example_draw_triangles_filled_02_line_sweeping_ph03_full,
               "example_draw_triangles_filled_02_line_sweeping_ph03_full");
}
} // namespace ra_examples::cartesian2d
