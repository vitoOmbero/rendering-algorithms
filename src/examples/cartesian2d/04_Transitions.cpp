#include "04_Transitions.h"

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

#include "geometry_types.h"

void draw_figures(ra_types::point2i A_1, ra_types::point2i A_2,
                  ra_types::point2i A_3, ra_types::point2i A_4,
                  ra_types::point2i B_1, ra_types::point2i B_2,
                  ra_types::point2i B_3)
{
    using namespace ra_core;
    using namespace ra_core::figures2d;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    Quadrangle A(A_1, A_2, A_3, A_4, border);
    Triangle   B(B_1, B_2, B_3, border);

    renderer::setDrawingMode(pipeline::eDrawingMode::Circuit);

    A.setColorCode(cm.FindRgbCode(eColor::Orange));
    renderer::Draw(A);

    renderer::setDrawingMode(pipeline::eDrawingMode::Shape);

    B.setColorCode(cm.FindRgbCode(eColor::Purple_blue));
    renderer::Draw(B);
}

ra_core::pipeline::Canvas2d initial()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    point2i qA_1{ 50, 50 };
    point2i qA_2{ 100, 50 };
    point2i qA_3{ 100, 100 };
    point2i qA_4{ 50, 100 };

    point2i tB_1{ 100, 400 };
    point2i tB_2{ 150, 505 };
    point2i tB_3{ 15, 578 };

    draw_figures(qA_1, qA_2, qA_3, qA_4, tB_1, tB_2, tB_3);

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d move()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    point2i qA_1{ 50, 50 };
    point2i qA_2{ 100, 50 };
    point2i qA_3{ 100, 100 };
    point2i qA_4{ 50, 100 };

    point2i tB_1{ 100, 400 };
    point2i tB_2{ 150, 505 };
    point2i tB_3{ 15, 578 };

    draw_figures(qA_1, qA_2, qA_3, qA_4, tB_1, tB_2, tB_3);

    auto mc = renderer::getMatrixCalculatorSimple();

    std::array<point2i, n1_t(4)> qVertices{ qA_1, qA_2, qA_3, qA_4 };
    std::array<point2i, n1_t(3)> tVertices{ tB_1, tB_2, tB_3 };

    displacement1i_t dx = 200;
    displacement1i_t dy = 150;

    mc.Move<n1_t(4)>(qVertices, dx, dy);
    mc.Move<n1_t(3)>(tVertices, dx, -dy);

    draw_figures(qVertices[0], qVertices[1], qVertices[2], qVertices[3],
                 tVertices[0], tVertices[1], tVertices[2]);

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d stretching()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;
    using namespace ra_services::
        geometric_transformations_in_homogeneous_coordinates;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    point2i qA_1{ 50, 50 };
    point2i qA_2{ 100, 50 };
    point2i qA_3{ 100, 100 };
    point2i qA_4{ 50, 100 };

    point2i tB_1{ 100, 200 - 40 };
    point2i tB_2{ 150, 305 - 40 };
    point2i tB_3{ 15, 378 - 40 };

    // initial state draw
    draw_figures(qA_1, qA_2, qA_3, qA_4, tB_1, tB_2, tB_3);

    // prepare points
    std::array<point2i, 4 + 3> vertices{ qA_1, qA_2, qA_3, qA_4,
                                         tB_1, tB_2, tB_3 };
    // go
    auto mc = renderer::getMatrixCalculatorSimple();

    // next state draw will be done righter
    displacement1i_t dx = 100;
    mc.Move<7>(vertices, dx);

    // prepare data
    std::array<point2i, 4> quadrangle{ vertices[0], vertices[1], vertices[2],
                                       vertices[3] };
    std::array<point2i, 3> triangle{ vertices[4], vertices[5], vertices[6] };

    // streching
    mc.Stretch<4>(quadrangle, 2.5, 2.5);
    mc.Stretch<3>(triangle, 1.7, 1.7);

    // draw streched

    mc.Move<3>(triangle, 0, -350);

    draw_figures(quadrangle[0], quadrangle[1], quadrangle[2], quadrangle[3],
                 triangle[0], triangle[1], triangle[2]);

    using namespace ra_core::figures2d;

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d rotation()
{
    ra_core::renderer::Init();
    using namespace ra_core;
    using namespace ra_core::pipeline;
    using namespace ra_types;
    using namespace ra_services::
        geometric_transformations_in_homogeneous_coordinates;

    renderer::UseLineAlgorithm(rendering_algorithm::line_bresenham_int);
    renderer::UseFillingTriangle(filling_algorithm::fill3_line_sweeping);

    point2i qA_1{ 50, 50 };
    point2i qA_2{ 100, 50 };
    point2i qA_3{ 100, 100 };
    point2i qA_4{ 50, 100 };

    point2i tB_1{ 100, 200 - 40 };
    point2i tB_2{ 150, 305 - 40 };
    point2i tB_3{ 15, 378 - 40 };

    // initial state draw
    draw_figures(qA_1, qA_2, qA_3, qA_4, tB_1, tB_2, tB_3);

    // prepare points
    std::array<point2i, 4 + 3> vertices{ qA_1, qA_2, qA_3, qA_4,
                                         tB_1, tB_2, tB_3 };
    // go
    auto mc = renderer::getMatrixCalculatorSimple();

    // next state draw will be done righter
    displacement1i_t dx = 100;
    mc.Move<7>(vertices, dx);

    // prepare data
    std::array<point2i, 4> quadrangle{ vertices[0], vertices[1], vertices[2],
                                       vertices[3] };
    std::array<point2i, 3> triangle{ vertices[4], vertices[5], vertices[6] };

    // rotation

    auto ang45 = ra_services::math2d::make_angle_radians(45);
    auto ang30 = ra_services::math2d::make_angle_radians(30);

    mc.Rotate<4, float>(quadrangle, ang45);
    mc.Rotate<3>(triangle, ang30, eRotationDirection2d::Anticlock);

    // draw rotated

    mc.Move<4>(quadrangle, -100, -100);
    mc.Move<3>(triangle, 100, -450);

    draw_figures(quadrangle[0], quadrangle[1], quadrangle[2], quadrangle[3],
                 triangle[0], triangle[1], triangle[2]);

    using namespace ra_core::figures2d;

    return renderer::getCanvas();
}

namespace ra_examples::cartesian2d
{
Transitions::Transitions()
{
    name = "04_transitions";
    AddExample(initial, "initial");
    AddExample(move, "move");
    AddExample(stretching, "stretching");
    AddExample(rotation, "rotation");
}
} // namespace ra_examples::cartesian2d
