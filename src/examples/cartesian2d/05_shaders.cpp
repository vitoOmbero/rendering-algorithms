#include "05_shaders.h"

#include <array>

#include "algorithm_proxy.h"
#include "canvas2d.h"
#include "circle.h"
#include "color_map.h"
#include "dot.h"
#include "line_segment.h"
#include "quadrangle.h"
#include "triangle.h"
#include "algorithms_registry.h"
#include "examples_types.h"
#include "math2d.h"
#include "ra_types.h"
#include "renderer.h"

#include "rendering_target_base.h"

namespace ra_examples::cartesian2d
{

void draw_triangles(ra_core::pipeline::DrawingMode mode)
{
    using namespace ra_core;
    using namespace ra_core::figures2d;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::setDrawingMode(mode);

    Color col_eptr = Color::k_FIRST_;

    auto generateColor = [&cm, &col_eptr]() {
        col_eptr = static_cast<Color>(1 + (int)col_eptr);
        if (col_eptr == Color::k_LAST_)
            col_eptr = static_cast<Color>(1 + (int)Color::k_FIRST_);
        return cm.FindRgbCode(col_eptr);
    };

    Point2i        c{ 399, 299 };
    displacement2i dx = { 15, 0 };
    displacement2i dy = { 0, 15 };

    for (Point2i tB_1{ 399, 0 }, tB_2{ 0, 599 }, tB_3{ 799, 599 };
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

    renderer::UseLineAlgorithm(RenderingAlgorithm::kLineBresenhamInt);
    renderer::UseFillingTriangle(FillingAlgorithm::kFill3LineSweeping);

    draw_triangles(pipeline::DrawingMode::kShape);

    return renderer::getCanvas();
}

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

ra_core::pipeline::Canvas2d pixel_shader_concept_invert()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;

    renderer::UseLineAlgorithm(RenderingAlgorithm::kLineBresenhamInt);
    renderer::UseFillingTriangle(FillingAlgorithm::kFill3LineSweeping);

    draw_triangles(pipeline::DrawingMode::kShape);

    auto pshader_invert_color =
        [](ra_types::Point2i first, ra_types::Point2i second,
           ra_types::Point2i third, ra_types::Rgb888 color_code,
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
                    auto y = first.y + i;
                    // if ra_core::pipeline had vertex and primitive stages, all
                    // shader code would be:
                    color_code = target.getColorCode(
                        { x, y }); // that's why pixel shader
                    color_code.r = (uchar)255 - color_code.r;
                    color_code.g = (uchar)255 - color_code.g;
                    color_code.b = (uchar)255 - color_code.b;
                    // end;
                    target.Mark(color_code, { x, y });
                }
            }

            return counter;
        };

    // fill pixel buffer and canvas
    renderer::StumpCanvas();

    // setup to draw in pixel buffer
    renderer::setRenderingTarget(pipeline::Target::kPixelBuffer);
    renderer::setExportTarget(pipeline::Target::kPixelBuffer);

    // shader is autonomous program which is using rendering pipeline API to
    // manipulate data.

    // OPENGL produces this API in state machine style, where
    // you configure rendering pipeline domain objects with data usally in raw
    // format

    // However, there is no vertex and primitives in ra_core::pipeline at the
    // moment, that's why shader include triangle filling algorithm and example
    // uses Filling renderer API

    renderer::UseCustomFillingTriangle(pshader_invert_color);
    renderer::setDrawingMode(pipeline::DrawingMode::kShape);

    Point2i tB_1{ 0, 399 }, tB_2{ 599, 0 }, tB_3{ 599, 599 };

    figures2d::border   border;
    figures2d::Triangle inversion_area(tB_1, tB_2, tB_3, border);

    renderer::Draw(inversion_area);

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d vertex_shader_concept_gradient()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;

    renderer::UseLineAlgorithm(RenderingAlgorithm::kLineBresenhamInt);
    renderer::UseFillingTriangle(FillingAlgorithm::kFill3LineSweeping);

    draw_triangles(pipeline::DrawingMode::kShape);

    auto vshader_gradient_color =
        [](ra_types::Point2i first, ra_types::Point2i second,
           ra_types::Point2i third, ra_types::Rgb888 color_code,
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

                    auto y  = first.y + i;
                    auto v1 = first; // that's why vertex shader
                    auto v2 = second;
                    auto v3 = third;

                    // if ra_core::pipeline had vertex and primitive stages, all
                    // shader code would be:

                    auto nd12x = (float)(v1.x - x) / (v1.x - v2.x);
                    auto nd12y = (float)(v1.y - y) / (v1.y - v2.y);

                    color_code.r =
                        (uchar)127 * nd12x + (uchar)127 * nd12y + (uchar)1;
                    color_code.g = (uchar)127 * (1 - nd12x) +
                                   (uchar)127 * (1 - nd12y) + (uchar)1;

                    auto nd31x = (float)(v3.x - x) / (v3.x - v1.x);
                    auto nd31y = (float)(v3.y - y) / (v3.y - v1.y);

                    color_code.b =
                        (uchar)127 * nd31x + (uchar)127 * nd31y + (uchar)1;
                    // end;
                    target.Mark(color_code, { x, y });
                }
            }

            return counter;
        };

    // fill pixel buffer and canvas
    renderer::StumpCanvas();

    // setup to draw in pixel buffer
    renderer::setRenderingTarget(pipeline::Target::kPixelBuffer);
    renderer::setExportTarget(pipeline::Target::kPixelBuffer);

    // shader is autonomous program which is using rendering pipeline API to
    // manipulate data.

    // OPENGL produces this API in state machine style, where
    // you configure rendering pipeline domain objects with data usally in raw
    // format

    // However, there is no vertex and primitives in ra_core::pipeline at the
    // moment, that's why shader include triangle filling algorithm and example
    // uses Filling renderer API

    renderer::UseCustomFillingTriangle(vshader_gradient_color);
    renderer::setDrawingMode(pipeline::DrawingMode::kShape);

    Point2i tB_1{ 0, 399 }, tB_2{ 599, 0 }, tB_3{ 599, 599 };

    figures2d::border   border;
    figures2d::Triangle inversion_area(tB_1, tB_2, tB_3, border);

    renderer::Draw(inversion_area);

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d vertex_shader_concept_gradient2()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;

    renderer::UseLineAlgorithm(RenderingAlgorithm::kLineBresenhamInt);
    renderer::UseFillingTriangle(FillingAlgorithm::kFill3LineSweeping);

    draw_triangles(pipeline::DrawingMode::kShape);

    auto vshader_gradient_color =
        [](ra_types::Point2i first, ra_types::Point2i second,
           ra_types::Point2i third, ra_types::Rgb888 color_code,
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

                    auto y  = first.y + i;
                    auto v1 = first; // that's why vertex shader
                    auto v2 = second;
                    auto v3 = third;

                    // if ra_core::pipeline had vertex and primitive stages, all
                    // shader code would be:

                    auto              c = (v1 + v2 + v3) / 3;
                    ra_types::Point2i p{ x, y };

                    auto ndp = [&c](ra_types::Point2i p, ra_types::Point2i v) {
                        return (
                            (float)ra_services::math2d::CalcDistance(v, p) /
                            ra_services::math2d::CalcDistance(v, c));
                    };

                    color_code.r = 255 * ndp(p, v1);

                    color_code.g = 255 * ndp(p, v2);

                    color_code.b = 255 * ndp(p, v3);
                    // end;
                    target.Mark(color_code, { x, y });
                }
            }

            return counter;
        };

    // fill pixel buffer and canvas
    renderer::StumpCanvas();

    // setup to draw in pixel buffer
    renderer::setRenderingTarget(pipeline::Target::kPixelBuffer);
    renderer::setExportTarget(pipeline::Target::kPixelBuffer);

    // shader is autonomous program which is using rendering pipeline API to
    // manipulate data.

    // OPENGL produces this API in state machine style, where
    // you configure rendering pipeline domain objects with data usally in raw
    // format

    // However, there is no vertex and primitives in ra_core::pipeline at the
    // moment, that's why shader include triangle filling algorithm and example
    // uses Filling renderer API

    renderer::UseCustomFillingTriangle(vshader_gradient_color);
    renderer::setDrawingMode(pipeline::DrawingMode::kShape);

    Point2i tB_1{ 0, 399 }, tB_2{ 599, 0 }, tB_3{ 599, 599 };

    figures2d::border   border;
    figures2d::Triangle inversion_area(tB_1, tB_2, tB_3, border);

    renderer::Draw(inversion_area);

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d vertex_shader_concept_gradient3()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;

    renderer::UseLineAlgorithm(RenderingAlgorithm::kLineBresenhamInt);
    renderer::UseFillingTriangle(FillingAlgorithm::kFill3LineSweeping);

    draw_triangles(pipeline::DrawingMode::kShape);

    auto vshader_gradient_color =
        [](ra_types::Point2i first, ra_types::Point2i second,
           ra_types::Point2i third, ra_types::Rgb888 color_code,
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

                    auto y  = first.y + i;
                    auto v1 = first; // that's why vertex shader
                    auto v2 = second;
                    auto v3 = third;

                    auto nd = [](ra_types::Point2i p, ra_types::Point2i v_min,
                                 ra_types::Point2i v_max) {
                        return (
                            (float)ra_services::math2d::CalcDistance(v_min,
                                                                      p) /
                            ra_services::math2d::CalcDistance(v_min, v_max));
                    };

                    using namespace ra_services::math2d;

                    // if ra_core::pipeline had vertex and primitive stages, all
                    // shader code would be:
                    Point2i p{ x, y };

                    color_code.r =
                        255 - 255 * nd(p, v1, CalcMiddlePoint(v2, v3));
                    color_code.g =
                        255 - 255 * nd(p, v2, CalcMiddlePoint(v1, v3));
                    color_code.b =
                        255 - 255 * nd(p, v3, CalcMiddlePoint(v1, v2));

                    // end;
                    target.Mark(color_code, { x, y });
                }
            }

            return counter;
        };

    // fill pixel buffer and canvas
    renderer::StumpCanvas();

    // setup to draw in pixel buffer
    renderer::setRenderingTarget(pipeline::Target::kPixelBuffer);
    renderer::setExportTarget(pipeline::Target::kPixelBuffer);

    // shader is autonomous program which is using rendering pipeline API to
    // manipulate data.

    // OPENGL produces this API in state machine style, where
    // you configure rendering pipeline domain objects with data usally in raw
    // format

    // However, there is no vertex and primitives in ra_core::pipeline at the
    // moment, that's why shader include triangle filling algorithm and example
    // uses Filling renderer API

    renderer::UseCustomFillingTriangle(vshader_gradient_color);
    renderer::setDrawingMode(pipeline::DrawingMode::kShape);

    Point2i tB_1{ 0, 399 }, tB_2{ 599, 0 }, tB_3{ 599, 599 };

    figures2d::border   border;
    figures2d::Triangle inversion_area(tB_1, tB_2, tB_3, border);

    renderer::Draw(inversion_area);

    return renderer::getCanvas();
}

Shaders::Shaders()
{
    name_ = "05_shaders";
    AddExample(initial, "initial");
    AddExample(pixel_shader_concept_invert, "pixel_shader_concept_invert");
    AddExample(vertex_shader_concept_gradient,
               "vertex_shader_concept_gradient");
    AddExample(vertex_shader_concept_gradient2,
               "vertex_shader_concept_gradient2");
    AddExample(vertex_shader_concept_gradient3,
               "vertex_shader_concept_gradient3");
}
} // namespace ra_examples::cartesian2d
