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
#include "ra_types.h"
#include "renderer.h"

#include "geometry_types.h"

void draw_figures(ra_types::point2i tA_1, ra_types::point2i tA_2,
                  ra_types::point2i tA_3, ra_types::point2i tA_4,
                  ra_types::point2i tB_1, ra_types::point2i tB_2,
                  ra_types::point2i tB_3)
{
    using namespace ra_core;
    using namespace ra_core::figures2d;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    Quadrangle A(tA_1, tA_2, tA_3, tA_4, border);
    Triangle   B(tB_1, tB_2, tB_3, border);

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

    std::array<point2i, n1_t(4)> arr{ qA_1, qA_2, qA_3, qA_4 };
    std::array<point2i, n1_t(3)> arr2{ tB_1, tB_2, tB_3 };

    displacement1i_t dx = 200;
    displacement1i_t dy = -10;

    mc.Move<n1_t(4)>(arr, dx, -dy);
    mc.Move<n1_t(3)>(arr2, dx, -dy);

    draw_figures(arr[0], arr[1], arr[2], arr[3], arr2[0], arr2[1], arr2[2]);

    return renderer::getCanvas();
}

/*
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
    point2i qA_2{ 150, 50 };
    point2i qA_3{ 150, 150 };
    point2i qA_4{ 50, 150 };

    point2i tB_1{ 100, 400 };
    point2i tB_2{ 150, 505 };
    point2i tB_3{ 15, 578 };

    draw_figures(qA_1, qA_2, qA_3, qA_4, tB_1, tB_2, tB_3);

    auto dA1 = make_displacement2d(qA_1);
    auto dA2 = make_displacement2d(qA_2);
    auto dA3 = make_displacement2d(qA_3);
    auto dA4 = make_displacement2d(qA_4);

    auto mc = renderer::getMatrixCalculatorSimple();

    auto dA12 = mc.Stretch({ dA1, dA2 });

    return renderer::getCanvas();
}

*/

namespace ra_examples::cartesian2d
{
Transitions::Transitions()
{
    name = "04_transitions";
    AddExample(initial, "initial");
    AddExample(move, "move");
    // AddExample(stretching, "stretching");
}
} // namespace ra_examples::cartesian2d
