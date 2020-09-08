#include "renderer.h"

#include "AlgorithmProxy.h"
#include "Canvas2d.h"
#include "ClippingRectangularWindow.h"
#include "DrawCircuit2dVisitor.h"
#include "DrawShape2dVisitor.h"
#include "Pipeline.h"
#include "PixelBuffer2d.h"
#include "RasterizerSimple.h"
#include "SpaceCoordinateTranslatorSimple.h"

namespace ra_core::renderer
{

bool IsInitialized = false;

#include "INIT_GUARD_MACRO.inc"

static const ra_services::color_rgb::ColorMap              cm;
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

    setDrawingMode(pipeline::eDrawingMode::Circuit);
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
        setDrawingMode(pipeline::eDrawingMode::Circuit);
        drawable.AcceptFigure2dVisitor(drawVisitor_ptr);
    }
}

void setDrawingMode(pipeline::eDrawingMode mode)
{
    INIT_GUARD(IsInitialized, )

    if (drawVisitor_ptr != nullptr)
        delete drawVisitor_ptr;

    if (mode == pipeline::eDrawingMode::Circuit)
        drawVisitor_ptr = new pipeline::DrawCircuit2dVisitor(*pipeline_ptr);
    else
        drawVisitor_ptr = new pipeline::DrawShape2dVisitor(*pipeline_ptr);
}

void UseLineAlgorithm(ra_core::rendering2d::rendering_algorithm algo_ptr)
{
    INIT_GUARD(IsInitialized, )
    raproxy.setRenderingCircuitAlgorithm(figures2d::eFigure2dType::Line,
                                         algo_ptr);
}

void UseCircleAlgorithm(ra_core::rendering2d::rendering_algorithm algo_ptr)
{
    INIT_GUARD(IsInitialized, )
    raproxy.setRenderingCircuitAlgorithm(figures2d::eFigure2dType::Circle,
                                         algo_ptr);
}

void UseFillingTriangle(ra_core::rendering2d::filling_algorithm algo_ptr)
{
    INIT_GUARD(IsInitialized, )
    raproxy.setFillingAlgorithm(figures2d::eFigure2dType::Triangle, algo_ptr);
}

void UseClippingWindow(ra_types::n0_t offsetX, ra_types::n0_t offsetY,
                       ra_core::rendering2d::clipping_algorithm algo_ptr)
{
    INIT_GUARD(IsInitialized, )

    UseNoClippingWindow();

    spaceCoordTrans_ptr->setClipwinOffset({ offsetX, offsetY });

    using namespace ra_types;

    spaceCoordTrans_ptr->modClipwinSize(displacement1i_t{ -offsetX },
                                        displacement1i_t{ -offsetY });

    clipwin_ptr = new pipeline::ClippingRectangularWindow(
        spaceCoordTrans_ptr->getClipwin2dSpaceRef(), algo_ptr);
    pipeline_ptr->setClipwin_ptr(clipwin_ptr);

    raproxy.setClippingAlgorithm(clipwin_ptr->getClippingAlgo_ptr());
}

ra_core::pipeline::Canvas2d getCanvas()
{
    INIT_GUARD(IsInitialized, ra_core::pipeline::Canvas2d(ra_types::Space2i()))

    return pipeline_ptr->ExportCanvas();
}

void setExportTarget(pipeline::eTarget target)
{
    INIT_GUARD(IsInitialized, )

    pipeline_ptr->setExportTarget(target);
}

void setRenderingTarget(pipeline::eTarget target)
{
    INIT_GUARD(IsInitialized, )

    pipeline_ptr->setRenderingTarget(target);
}

const ra_services::color_rgb::ColorMap& getColorMap()
{
    return cm;
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

} // namespace ra_core::renderer
