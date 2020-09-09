#include "05_Shaders.h"

#include <array>

#include "AlgorithmProxy.h"
#include "Canvas2d.h"
#include "Circle.h"
#include "ColorMap.h"
#include "Dot.h"
#include "LineSegment.h"
#include "Quadrangle.h"
#include "Triangle.h"
#include "algorithms_registry.h"
#include "examples_types.h"
#include "math2d.h"
#include "ra_types.h"
#include "renderer.h"

#include "RenderingTargetBase.h"

namespace ra_examples::cartesian2d
{

void draw_triangles(ra_core::pipeline::eDrawingMode mode)
{
    using namespace ra_core;
    using namespace ra_core::figures2d;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::setDrawingMode(mode);

    eColor col_eptr = eColor::_FIRST_;

    auto generateColor = [&cm, &col_eptr]() {
        col_eptr = static_cast<eColor>(1 + (int)col_eptr);
        if (col_eptr == eColor::_LAST_)
            col_eptr = static_cast<eColor>(1 + (int)eColor::_FIRST_);
        return cm.FindRgbCode(col_eptr);
    };

    point2i        c{ 399, 299 };
    displacement2i dx = { 15, 0 };
    displacement2i dy = { 0, 15 };

    for (point2i tB_1{ 399, 0 }, tB_2{ 0, 599 }, tB_3{ 799, 599 };
         tB_1.y < c.y;)
    {
        tB_1 = tB_1 + dy;
        tB_2 = tB_2 - dy + dx;
        tB_3 = tB_3 - dy - dx;

        Triangle B(tB_1, tB_2, tB_3, border);

        B.setColorCode(generateColor());
        renderer::Draw(B);
    };
}

ra_core::pipeline::Canvas2d initial()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    draw_triangles(pipeline::eDrawingMode::Shape);

    return renderer::getCanvas();
}

inline void bubble_sort_by_y(ra_types::point2i& p1, ra_types::point2i& p2,
                             ra_types::point2i& p3)
{
    if (p1.y > p2.y)
        std::swap(p1, p2);
    if (p1.y > p2.y)
        std::swap(p1, p2);
    if (p2.y > p3.y)
        std::swap(p2, p3);
}

ra_core::pipeline::Canvas2d pixel_shader_concept_invert()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    draw_triangles(pipeline::eDrawingMode::Shape);

    auto pshader_invert_color =
        [](ra_types::point2i first, ra_types::point2i second,
           ra_types::point2i third, ra_types::rgb888 color_code,
           ra_core::pipeline::RenderingTargetBase& target) {
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
                    (float)(i - (upper_half ? second.y - first.y : 0)) /
                    segment_height;

                typedef ra_types::displacement2i vec2i;

                vec2i A = make_displacement2d(first + (third - first) * alpha);
                vec2i B =
                    upper_half
                        ? make_displacement2d(second + (third - second) * beta)
                        : make_displacement2d(first + (second - first) * beta);

                if (A.x > B.x)
                    std::swap(A, B);

                for (ra_types::displacement1i_t x = A.x; x <= B.x;
                     ++x, ++counter)
                {
                    // if ra_core::pipeline had vertex and primitive stages, all
                    // shader code was:
                    color_code   = target.getColorCode({ x, first.y + i });
                    color_code.r = (uchar)255 - color_code.r;
                    color_code.g = (uchar)255 - color_code.g;
                    color_code.b = (uchar)255 - color_code.b;
                    target.Mark(color_code, { x, first.y + i });
                    // end;
                }
            }

            return counter;
        };

    // fill pixel buffer and canvas
    renderer::StumpCanvas();

    // setup to draw in pixel buffer
    renderer::setRenderingTarget(pipeline::eTarget::PixelBuffer);
    renderer::setExportTarget(pipeline::eTarget::PixelBuffer);

    // shader is autonomous program which is using rendering pipeline API to
    // manipulate data.

    // OPENGL produces this API in state machine style, where
    // you configure rendering pipeline domain objects with data usally in raw
    // format

    // However, there is no vertex and primitives in ra_core::pipeline at the
    // moment, that's why shader include triangle filling algorithm and example
    // uses Filling renderer API

    renderer::UseCustomFillingTriangle(pshader_invert_color);
    renderer::setDrawingMode(pipeline::eDrawingMode::Shape);

    point2i tB_1{ 0, 399 }, tB_2{ 599, 0 }, tB_3{ 599, 599 };

    figures2d::border   border;
    figures2d::Triangle inversion_area(tB_1, tB_2, tB_3, border);

    renderer::Draw(inversion_area);

    return renderer::getCanvas();
}

Shaders::Shaders()
{
    name = "05_shaders";
    AddExample(initial, "initial");
    AddExample(pixel_shader_concept_invert, "pixel_shader_concept_invert");
}
} // namespace ra_examples::cartesian2d
