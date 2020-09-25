#include "02_Shapes.h"

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

ra_core::pipeline::Canvas2d filling_triangle_naive()
{
    ra_core::renderer::Init();
    using namespace ra_core::figures2d;
    using namespace ra_core::pipeline;
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::UseLineAlgorithm(RenderingAlgorithm::kLineBresenhamInt);
    renderer::setDrawingMode(DrawingMode::kShape);

    renderer::UseFillingTriangle(FillingAlgorithm::kFill3NaiveHorizontal);

    Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 }, border);
    tr.setColorCode(cm.FindRgbCode(Color::kOrange));

    renderer::Draw(tr);
    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(Color::kTeal));
    renderer::Draw(tr);

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d triangle_line_sweeping_ph01()
{
    ra_core::renderer::Init();
    using namespace ra_core::figures2d;
    using namespace ra_core::pipeline;
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::setDrawingMode(DrawingMode::kShape);
    renderer::UseLineAlgorithm(RenderingAlgorithm::kLineBresenhamInt);
    renderer::UseFillingTriangle(
        FillingAlgorithm::kFill3LineSweepingPhase01);

    ra_core::figures2d::Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 },
                                    border);

    tr.setColorCode(cm.FindRgbCode(Color::kOrange));
    renderer::Draw(tr);

    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(Color::kTeal));
    renderer::Draw(tr);

    ra_core::figures2d::Triangle tr2({ 200, 50 }, { 300, 500 }, { 400, 250 },
                                     border);
    tr2.setColorCode(cm.FindRgbCode(Color::kBlue));
    ra_core::figures2d::Triangle tr3({ 500, 250 }, { 600, 50 }, { 700, 500 },
                                     border);
    tr2.setColorCode(cm.FindRgbCode(Color::kPurpleBlue));

    renderer::Draw(tr2);
    renderer::Draw(tr3);

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d triangle_line_sweeping_ph02()
{
    ra_core::renderer::Init();
    using namespace ra_core::figures2d;
    using namespace ra_core::pipeline;
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::setDrawingMode(DrawingMode::kShape);
    renderer::UseLineAlgorithm(RenderingAlgorithm::kLineBresenhamInt);
    renderer::UseFillingTriangle(
        FillingAlgorithm::kFill3LineSweepingPhase02);

    Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 }, border);

    tr.setColorCode(cm.FindRgbCode(Color::kOrange));
    renderer::Draw(tr);

    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(Color::kTeal));
    renderer::Draw(tr);

    Triangle tr2({ 200, 50 }, { 300, 500 }, { 400, 250 }, border);
    tr2.setColorCode(cm.FindRgbCode(Color::kBlue));
    Triangle tr3({ 500, 250 }, { 600, 50 }, { 700, 500 }, border);
    tr3.setColorCode(cm.FindRgbCode(Color::kPurpleBlue));

    renderer::Draw(tr2);
    renderer::Draw(tr3);

    return renderer::getCanvas();
}

ra_core::pipeline::Canvas2d triangle_line_sweeping_full()
{
    ra_core::renderer::Init();
    using namespace ra_core::figures2d;
    using namespace ra_core::pipeline;
    using namespace ra_core;
    using namespace ra_types;
    auto              cm = renderer::getColorMap();
    figures2d::border border;

    renderer::setDrawingMode(DrawingMode::kShape);
    renderer::UseLineAlgorithm(RenderingAlgorithm::kLineBresenhamInt);
    renderer::UseFillingTriangle(FillingAlgorithm::kFill3LineSweeping);

    Triangle tr({ 50, 50 }, { 100, 300 }, { 0, 500 }, border);

    tr.setColorCode(cm.FindRgbCode(Color::kOrange));
    renderer::Draw(tr);

    tr.setP1({ 100, 100 });
    tr.setP2({ 50, 350 });
    tr.setP3({ 15, 400 });
    tr.setColorCode(cm.FindRgbCode(Color::kTeal));
    renderer::Draw(tr);

    Triangle tr2({ 200, 50 }, { 300, 500 }, { 400, 250 }, border);
    tr2.setColorCode(cm.FindRgbCode(Color::kBlue));
    Triangle tr3({ 500, 250 }, { 600, 50 }, { 700, 500 }, border);
    tr3.setColorCode(cm.FindRgbCode(Color::kPurpleBlue));

    renderer::Draw(tr2);
    renderer::Draw(tr3);

    return renderer::getCanvas();
}

namespace ra_examples::cartesian2d
{

Shapes::Shapes()
{
    name_ = "02_shapes";
    AddExample(filling_triangle_naive, "filling_triangle_naive");
    AddExample(triangle_line_sweeping_ph01, "triangle_line_sweeping_ph01");
    AddExample(triangle_line_sweeping_ph02, "triangle_line_sweeping_ph02");
    AddExample(triangle_line_sweeping_full, "triangle_line_sweeping_full");
}
} // namespace ra_examples::cartesian2d
