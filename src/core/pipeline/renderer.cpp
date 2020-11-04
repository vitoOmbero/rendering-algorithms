#include "renderer.h"

#include "algorithm_proxy.h"
#include "canvas2d.h"
#include "clipping_rectangular_window.h"
#include "draw_circuit2d_visitor.h"
#include "draw_shape2d_visitor.h"
#include "pipeline.h"
#include "pixel_buffer2d.h"
#include "rasterizer_simple.h"
#include "space_coordinate_translator_simple.h"

namespace ra_core::renderer
{

bool IsInitialized = false;

#include "INIT_GUARD_MACRO.inc"

static const ra_services::color_rgb::ColorMap kColorMap;
static ra_services::geometric_transformations_in_homogeneous_coordinates::
    MatrixCalculatorSimple                                 mcx;
static ra_core::pipeline::AlgorithmProxy                   raproxy;

ra_core::pipeline::Pipeline*                        pipeline_ptr;
ra_core::figures2d::Figure2dVisitor*                drawVisitor_ptr;
ra_core::pipeline::ClippingRectangularWindow*       clipwin_ptr;
ra_core::pipeline::SpaceCoordinateTranslatorSimple* spaceCoordTrans_ptr;

void Init()
{
    using namespace ra_core::pipeline;

    if (IsInitialized)
        Destroy();

    spaceCoordTrans_ptr = new SpaceCoordinateTranslatorSimple();
    pipeline_ptr  = new Pipeline(clipwin_ptr, raproxy, *spaceCoordTrans_ptr);
    IsInitialized = true;

    setDrawingMode(pipeline::DrawingMode::kCircuit);
}

void Destroy()
{
    if (IsInitialized)
    {
        delete spaceCoordTrans_ptr;
        spaceCoordTrans_ptr = nullptr;
        delete clipwin_ptr;
        clipwin_ptr = nullptr;
        delete pipeline_ptr;
        pipeline_ptr = nullptr;

        IsInitialized = false;
    }
}

void Draw(const ra_core::figures2d::DrawableInterface& drawable)
{
    INIT_GUARD(IsInitialized, )

    if (drawVisitor_ptr != nullptr)
        drawable.AcceptFigure2dVisitor(drawVisitor_ptr);
    else
    {
        setDrawingMode(pipeline::DrawingMode::kCircuit);
        drawable.AcceptFigure2dVisitor(drawVisitor_ptr);
    }
}

void setDrawingMode(pipeline::DrawingMode mode)
{
    INIT_GUARD(IsInitialized, )

    if (drawVisitor_ptr != nullptr)
        delete drawVisitor_ptr;

    if (mode == pipeline::DrawingMode::kCircuit)
        drawVisitor_ptr = new pipeline::DrawCircuit2dVisitor(*pipeline_ptr);
    else
        drawVisitor_ptr = new pipeline::DrawShape2dVisitor(*pipeline_ptr);
}

void UseLineAlgorithm(ra_core::rendering2d::RenderingAlgorithm kAlgo)
{
    INIT_GUARD(IsInitialized, )
    raproxy.setRenderingCircuitAlgorithm(figures2d::Figure2dType::kLine, kAlgo);
}

void UseCircleAlgorithm(ra_core::rendering2d::RenderingAlgorithm kAlgo)
{
    INIT_GUARD(IsInitialized, )
    raproxy.setRenderingCircuitAlgorithm(figures2d::Figure2dType::kCircle,
                                         kAlgo);
}

void UseFillingTriangle(ra_core::rendering2d::FillingAlgorithm kAlgo)
{
    INIT_GUARD(IsInitialized, )
    raproxy.setFillingAlgorithm(figures2d::Figure2dType::kTriangle, kAlgo);
}

void UseClippingWindow(ra_types::n0_t offsetX, ra_types::n0_t offsetY,
                       ra_core::rendering2d::ClippingAlgorithm kAlgo)
{
    INIT_GUARD(IsInitialized, )

    UseNoClippingWindow();

    spaceCoordTrans_ptr->setClippingWindowsOffset({ offsetX, offsetY });

    using namespace ra_types;

    spaceCoordTrans_ptr->modClippingWindowSize(displacement1i_t{ -offsetX },
                                        displacement1i_t{ -offsetY });

    clipwin_ptr = new pipeline::ClippingRectangularWindow(
        spaceCoordTrans_ptr->getClippingWindow2dSpace(), kAlgo);
    pipeline_ptr->setClipwin_ptr(clipwin_ptr);

    raproxy.setClippingAlgorithm(clipwin_ptr->getClippingAlgo());
}

ra_core::pipeline::Canvas2d getCanvas()
{
    INIT_GUARD(IsInitialized, ra_core::pipeline::Canvas2d(ra_types::Space2i()))

    return pipeline_ptr->ExportCanvas();
}

void setExportTarget(pipeline::Target target)
{
    INIT_GUARD(IsInitialized, )

    pipeline_ptr->setExportTarget(target);
}

void setRenderingTarget(pipeline::Target target)
{
    INIT_GUARD(IsInitialized, )

    pipeline_ptr->setRenderingTarget(target);
}

const ra_services::color_rgb::ColorMap& getColorMap()
{
    return kColorMap;
}

void UseNoClippingWindow()
{
    if (clipwin_ptr != nullptr)
    {
        delete clipwin_ptr;
        clipwin_ptr = nullptr;
        pipeline_ptr->setClipwin_ptr(nullptr);
    }
}

ra_services::geometric_transformations_in_homogeneous_coordinates::
    MatrixCalculatorSimple&
    getMatrixCalculatorSimple()
{
    return mcx;
}

void UseCustomFillingTriangle(rendering2d::FillingTriangleFunction func_ptr)
{
    raproxy.setCustomFillingAlgorithm(
        ra_core::figures2d::Figure2dType::kTriangle,
        reinterpret_cast<void*>(func_ptr));
}

void StumpCanvas()
{
    pipeline_ptr->StumpCanvas();
}

} // namespace ra_core::renderer
