#include "01_Elemantary.h"

/*
 * draft
 * previous version
 *
  static void test_1(const char* filepath) {
    using namespace simple_drawing;

primitive_canvas canvas(height, width);

auto dt = dot({20, 20}, color::DarkOrange1B);

canvas.draw(dt);

canvas.save<display_size>(filepath);

std::cout << filepath << " is ready" << std::endl;
}
*/

std::unique_ptr<ra_core::canvas2d::RectangularPixelBuffer> example_draw_dot()
{
    ra_services::color_rgb::ColorMap cm;

    ra_core::canvas2d::Canvas2d canvas; // TODO: forbid deafult ctor

    ra_core::figures2d::border border;

    ra_core::figures2d::Dot dot(150, 150, border);

    dot.SetColor(cm.FindRgbCode(ra_services::color_rgb::color::White));
    dot.SetColor({ 111, 111, 111 });

    canvas.Draw(dot);

    for (int i = 0; i < 10; ++i)
    {
        dot.setX(150 + i);
        canvas.Draw(dot);
    }

    return canvas.getPixelBuffer();
    // TODO: shared pointer!
}

namespace ra_examples
{

namespace cartesian2d
{

Elementary::Elementary()
{
    AddExample(example_draw_dot, "example_draw_dot");
}

} // namespace cartesian2d

} // namespace ra_examples
