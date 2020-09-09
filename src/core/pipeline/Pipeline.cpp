#include "Pipeline.h"

#include <iostream>

#include "ra_get_string.h"

namespace ra_core::pipeline
{
Pipeline::Pipeline(const ClippingRectangularWindow*       clipwin_ptr,
                   const AlgorithmProxy&                  raproxyRef,
                   const SpaceCoordinateTranslatorSimple& spaceCoordTransRef)
    : clipwin_ptr{ clipwin_ptr }
    , raproxyRef{ raproxyRef }
    , spaceCoordTransRef{ spaceCoordTransRef }
    , dotbuf(spaceCoordTransRef.getDotBuffer1dSpaceRef(), spaceCoordTransRef,
             ra_core::renderer::CANVAS_WIDTH_DT)
    , pixbuf(spaceCoordTransRef.getPixelBuffer2dSpaceRef(), spaceCoordTransRef,
             ra_core::renderer::WORLD_DEFAULT_COLOR_CODE)
    , canvas{ spaceCoordTransRef.getCanvas2dSpaceRef() }
    , rasterizer(dotbuf, pixbuf, canvas, spaceCoordTransRef)
    , renderingTarget{ pipeline::eTarget::DotBuffer } // NOTE: Draw depends on
    , exportTarget{ pipeline::eTarget::DotBuffer }    // NOTE: Draw depends on
    , renderingTarget_ptr{ &dotbuf }

{
}

bool Pipeline::IsVisibleLineSegment(ra_types::point2i& p1,
                                    ra_types::point2i& p2) const
{
    if (clipwin_ptr != nullptr)
    {
        auto clip = raproxyRef.getClipRectangular();

        auto result = clip(p1, p2, clipwin_ptr->getMax_X_max_Y(),
                           clipwin_ptr->getMin_X_min_Y());

        if (result[0].x < 0) // NOTE: result.empty() // for vector, but array is
                             // already initialized
            return false;
        else
        {
            p1 = result[0];
            p2 = result[1];
            return true;
        }
    }
    return true;
}

pipeline::eTarget Pipeline::getExportTarget() const
{
    return exportTarget;
}

void Pipeline::setExportTarget(const pipeline::eTarget& value)
{
    exportTarget = value;
}

pipeline::eTarget Pipeline::getRenderingTarget() const
{
    return renderingTarget;
}

void Pipeline::setRenderingTarget(const pipeline::eTarget& value)
{
    renderingTarget = value;
    if (renderingTarget == eTarget::DotBuffer)
        renderingTarget_ptr = &dotbuf;
    else
        renderingTarget_ptr = &pixbuf;
}

inline ra_types::displacement2i Cartesian2dToCanvas2d(
    ra_types::displacement2i point, ra_types::displacement2i offset)
{
    return point - offset;
}

ra_types::pointXi Pipeline::TranslateToRenderingTarget(
    const ra_types::point2i& p) const
{
    ra_types::pointXi point;

    // NOTE: ignores spce offset currently

    if (renderingTarget == eTarget::DotBuffer)
    {
        point.point2i = p;
    }
    else
    {
        point.point2i = spaceCoordTransRef.TranslateCanvasToPixelBuffer(p);
    }
    return point;
}

void Pipeline::StumpCanvas()
{
    if (exportTarget == pipeline::eTarget::DotBuffer)
    {
        rasterizer.ImageDotBufferToPixelBuffer();
        canvas.imagePixelBuffer2d(pixbuf);
    }
    else
    {
        canvas.imagePixelBuffer2d(pixbuf);
    }
}

void Pipeline::DrawCircuit(const ra_core::figures2d::Dot& dot)
{
    std::cout << "Draw Dot " << ra_types::GetString(dot.getPoint(), true)
              << " with rgb " << GetString(dot.GetColorCode()) << std::endl;

    auto p = dot.getPoint();

    spaceCoordTransRef.TranslateWorldToCanvas(p);

    if (!IsVisible(p))
    {
        std::cout << "Object is not visible!" << std::endl;
    }
    else
    {
        auto ra_dot_func = raproxyRef.getRenderDot();
        auto point       = TranslateToRenderingTarget(p).point2i;
        auto dotsdrawn   = ra_dot_func(point.x, point.y, dot.GetColorCode(),
                                     *renderingTarget_ptr);
        (*renderingTarget_ptr).UpdateDotsNumber(dotsdrawn);
    }
}

void Pipeline::DrawCircuit(const figures2d::LineSegment& ls)
{
    std::cout << "Draw LineSegment "
              << ra_types::GetString(ls.getFirstPoint(), true) << "-"
              << ra_types::GetString(ls.getSecondPoint(), true) << " with rgb "
              << GetString(ls.GetColorCode()) << std::endl;

    auto p1 = ls.getFirstPoint();
    auto p2 = ls.getSecondPoint();

    spaceCoordTransRef.TranslateWorldToCanvas(p1);
    spaceCoordTransRef.TranslateWorldToCanvas(p2);

    if (!IsVisibleLineSegment(p1, p2))
    {
        std::cout << "Object is invisible!" << std::endl;
    }
    else
    {
        auto ra_linesegment_func = raproxyRef.getRenderLineSegment();

        auto point1 = TranslateToRenderingTarget(p1).point2i;
        auto point2 = TranslateToRenderingTarget(p2).point2i;

        auto dotsdrawn = ra_linesegment_func(point1, point2, ls.GetColorCode(),
                                             *renderingTarget_ptr);

        renderingTarget_ptr->UpdateDotsNumber(dotsdrawn);
    }
}

void Pipeline::DrawCircuit(const figures2d::Circle& c)
{
    std::cout << "Draw Circle in " << ra_types::GetString(c.getCenter(), true)
              << "with R: " << c.getRadius() << " and rgb "
              << GetString(c.GetColorCode()) << std::endl;

    auto center = c.getCenter();
    spaceCoordTransRef.TranslateWorldToCanvas(center);

    if (!IsVisible(c.getMaxX(), c.getMaxY()) ||
        !IsVisible(c.getMinX(), c.getMinY()))
    {
        if (!IsVisible(center))
            std::cout << "Center is invisible." << std::endl;
        std::cout << "Missing clipping algorithm for circle." << std::endl;
        std::cout << "Circle is not drawn." << std::endl;
    }
    else
    {
        auto centerPoint = TranslateToRenderingTarget(center).point2i;

        auto ra_circle_func = raproxyRef.getRenderCircle();

        auto dotsdrawn = ra_circle_func(centerPoint, c.getRadius(),
                                        c.GetColorCode(), *renderingTarget_ptr);

        renderingTarget_ptr->UpdateDotsNumber(dotsdrawn);
    }
}

void Pipeline::DrawCircuit(const figures2d::Triangle& tr)
{
    std::cout << "Draw Triangle " << ra_types::GetString(tr.getP1(), true)
              << "-" << ra_types::GetString(tr.getP2(), true) << "-"
              << ra_types::GetString(tr.getP3(), true) << "with rgb "
              << GetString(tr.GetColorCode()) << std::endl;

    auto p1 = tr.getP1();
    auto p2 = tr.getP2();
    auto p3 = tr.getP3();

    spaceCoordTransRef.TranslateWorldToCanvas(p1);
    spaceCoordTransRef.TranslateWorldToCanvas(p2);
    spaceCoordTransRef.TranslateWorldToCanvas(p3);

    if (!IsVisible(tr.getMaxX(), tr.getMaxY()) ||
        !IsVisible(tr.getMinX(), tr.getMinY()))

    {
        std::cout << "Clipping is applied." << std::endl;
        std::cout << "Cliping for Triangle Circuit is not implemented! <<<"
                  << std::endl;
    }

    // NOTE: actually can be 6 vertices, todo Polygon_partition
    IsVisibleLineSegment(p1, p2);
    IsVisibleLineSegment(p2, p3);
    IsVisibleLineSegment(p3, p1);

    ra_types::point2i P1{ TranslateToRenderingTarget(p1).point2i };
    ra_types::point2i P2{ TranslateToRenderingTarget(p2).point2i };
    ra_types::point2i P3{ TranslateToRenderingTarget(p3).point2i };

    auto ra_ls_func = raproxyRef.getRenderLineSegment();

    auto dotsdrawn =
        ra_ls_func(P1, P2, tr.GetColorCode(), *renderingTarget_ptr);
    dotsdrawn += ra_ls_func(P2, P3, tr.GetColorCode(), *renderingTarget_ptr);
    dotsdrawn += ra_ls_func(P3, P1, tr.GetColorCode(), *renderingTarget_ptr);

    renderingTarget_ptr->UpdateDotsNumber(dotsdrawn);
}

void Pipeline::DrawShape(const figures2d::Circle& c)
{
    DrawCircuit(c);
    std::cout << ">>>  Draw Circle Shape is not implemented! <<<" << std::endl;
}

void Pipeline::DrawShape(const figures2d::Triangle& tr)
{
    // TODO: move to algoritm + add compile options and debug mode
    std::cout << "Draw Filled Triangle "
              << ra_types::GetString(tr.getP1(), true) << "-"
              << ra_types::GetString(tr.getP2(), true) << "-"
              << ra_types::GetString(tr.getP3(), true) << "with rgb "
              << GetString(tr.GetColorCode()) << std::endl;

    auto p1 = tr.getP1();
    auto p2 = tr.getP2();
    auto p3 = tr.getP3();

    // NOTE: actually can be 6 vertices, todo Polygon_partition
    spaceCoordTransRef.TranslateWorldToCanvas(p1);
    spaceCoordTransRef.TranslateWorldToCanvas(p2);
    spaceCoordTransRef.TranslateWorldToCanvas(p3);

    if (!IsVisible(tr.getMaxX(), tr.getMaxY()) ||
        !IsVisible(tr.getMinX(), tr.getMinY()))
    {
        std::cout << "Clipping should be applied." << std::endl;
        std::cout << "Cliping for Triangle Shape is not implemented! <<<"
                  << std::endl;
    }

    IsVisibleLineSegment(p1, p2);
    IsVisibleLineSegment(p2, p3);
    IsVisibleLineSegment(p3, p1);

    ra_types::point2i P1{ TranslateToRenderingTarget(p1).point2i };
    ra_types::point2i P2{ TranslateToRenderingTarget(p2).point2i };
    ra_types::point2i P3{ TranslateToRenderingTarget(p3).point2i };

    auto ra_trf_func = raproxyRef.getFillTriangle();

    auto dotsdrawn =
        ra_trf_func(P1, P2, P3, tr.GetColorCode(), *renderingTarget_ptr);

    renderingTarget_ptr->UpdateDotsNumber(dotsdrawn);
}

void Pipeline::DrawCircuit(const figures2d::Quadrangle& qd)
{
    std::cout << "Draw Quadrangle " << ra_types::GetString(qd.getP1(), true)
              << "-" << ra_types::GetString(qd.getP2(), true) << "-"
              << ra_types::GetString(qd.getP3(), true) << "-"
              << ra_types::GetString(qd.getP4(), true) << "with rgb "
              << GetString(qd.GetColorCode()) << std::endl;

    auto p1 = qd.getP1();
    auto p2 = qd.getP2();
    auto p3 = qd.getP3();
    auto p4 = qd.getP4();

    spaceCoordTransRef.TranslateWorldToCanvas(p1);
    spaceCoordTransRef.TranslateWorldToCanvas(p2);
    spaceCoordTransRef.TranslateWorldToCanvas(p3);
    spaceCoordTransRef.TranslateWorldToCanvas(p4);

    if (!IsVisible(qd.getMaxX(), qd.getMaxY()) ||
        !IsVisible(qd.getMinX(), qd.getMinY()))

    {
        std::cout << "Clipping is applied." << std::endl;
        std::cout << "Cliping for Quadrangle Circuit is not implemented! <<<"
                  << std::endl;
    }

    // NOTE: actually can be 8 vertices, todo Polygon_partition
    IsVisibleLineSegment(p1, p2);
    IsVisibleLineSegment(p2, p3);
    IsVisibleLineSegment(p3, p4);
    IsVisibleLineSegment(p4, p1);

    ra_types::point2i P1{ TranslateToRenderingTarget(p1).point2i };
    ra_types::point2i P2{ TranslateToRenderingTarget(p2).point2i };
    ra_types::point2i P3{ TranslateToRenderingTarget(p3).point2i };
    ra_types::point2i P4{ TranslateToRenderingTarget(p4).point2i };

    auto ra_ls_func = raproxyRef.getRenderLineSegment();

    auto dotsdrawn =
        ra_ls_func(P1, P2, qd.GetColorCode(), *renderingTarget_ptr);
    dotsdrawn += ra_ls_func(P2, P3, qd.GetColorCode(), *renderingTarget_ptr);
    dotsdrawn += ra_ls_func(P3, P4, qd.GetColorCode(), *renderingTarget_ptr);
    dotsdrawn += ra_ls_func(P4, P1, qd.GetColorCode(), *renderingTarget_ptr);

    renderingTarget_ptr->UpdateDotsNumber(dotsdrawn);
}

void Pipeline::DrawShape(const figures2d::Quadrangle& tr)
{
    DrawCircuit(tr);
    std::cout << ">>>  Draw Quadrangle Shape is not implemented! <<<"
              << std::endl;
}

ra_core::pipeline::Canvas2d ra_core::pipeline::Pipeline::ExportCanvas()
{
    StumpCanvas();

    auto copy(canvas);

    return copy;
}

void Pipeline::setClipwin_ptr(const ClippingRectangularWindow* value)
{
    clipwin_ptr = value;
}

} // namespace ra_core::pipeline
