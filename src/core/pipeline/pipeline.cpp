#include "pipeline.h"

#include <iostream>

#include "ra_get_string.h"

namespace ra_core::pipeline
{
Pipeline::Pipeline(const ClippingRectangularWindow*       clipwin_ptr,
                   const AlgorithmProxy&                  rp,
                   const SpaceCoordinateTranslatorSimple& sct)
    : clipwin_ptr_{ clipwin_ptr }
    , raproxy_{ rp }
    , space_coord_trans_{ sct }
    , dotbuf_(sct.getDotBuffer1dSpace(), sct,
              ra_core::renderer::CANVAS_WIDTH_DT)
    , pixbuf_(sct.getPixelBuffer2dSpace(), sct,
              ra_core::renderer::WORLD_DEFAULT_COLOR_CODE)
    , canvas_{ sct.getCanvas2dSpace() }
    , rasterizer_(dotbuf_, pixbuf_, canvas_, sct)
    , rendering_target_{ pipeline::Target::kDotBuffer } // NOTE: Draw depends on
    , export_target_{ pipeline::Target::kDotBuffer }    // NOTE: Draw depends on
    , renderingTarget_ptr_{ &dotbuf_ }

{
}

bool Pipeline::IsVisibleLineSegment(ra_types::Point2i& p1,
                                    ra_types::Point2i& p2) const
{
    if (clipwin_ptr_ != nullptr)
    {
        auto clip = raproxy_.getClipRectangular();

        auto result = clip(p1, p2, clipwin_ptr_->getMax_X_max_Y(),
                           clipwin_ptr_->getMin_X_min_Y());

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

pipeline::Target Pipeline::getExportTarget() const
{
    return export_target_;
}

void Pipeline::setExportTarget(const pipeline::Target& value)
{
    export_target_ = value;
}

pipeline::Target Pipeline::getRenderingTarget() const
{
    return rendering_target_;
}

void Pipeline::setRenderingTarget(const pipeline::Target& value)
{
    rendering_target_ = value;
    if (rendering_target_ == Target::kDotBuffer)
        renderingTarget_ptr_ = &dotbuf_;
    else
        renderingTarget_ptr_ = &pixbuf_;
}

inline ra_types::displacement2i Cartesian2dToCanvas2d(
    ra_types::displacement2i point, ra_types::displacement2i offset)
{
    return point - offset;
}

ra_types::pointXi Pipeline::TranslateToRenderingTarget(
    const ra_types::Point2i& p) const
{
    ra_types::pointXi point{};

    // NOTE: ignores space offset currently

    if (rendering_target_ == Target::kDotBuffer)
    {
        point.point2i = p;
    }
    else
    {
        point.point2i = space_coord_trans_.TranslateCanvasToPixelBuffer(p);
    }
    return point;
}

void Pipeline::StumpCanvas()
{
    if (export_target_ == pipeline::Target::kDotBuffer)
    {
        rasterizer_.ImageDotBufferToPixelBuffer();
      canvas_.ImagePixelBuffer2d(pixbuf_);
    }
    else
    {
      canvas_.ImagePixelBuffer2d(pixbuf_);
    }
}

void Pipeline::DrawCircuit(const ra_core::figures2d::Dot& dot)
{
    std::cout << "Draw Dot " << ra_types::GetString(dot.getPoint(), true)
              << " with rgb " << GetString(dot.getColorCode()) << std::endl;

    auto p = dot.getPoint();

    space_coord_trans_.TranslateWorldToCanvas(p);

    if (!IsVisible(p))
    {
        std::cout << "Object is not visible!" << std::endl;
    }
    else
    {
        auto ra_dot_func = raproxy_.getRenderDot();
        auto point       = TranslateToRenderingTarget(p).point2i;
        auto dotsdrawn   = ra_dot_func(point.x, point.y, dot.getColorCode(),
                                     *renderingTarget_ptr_);
        (*renderingTarget_ptr_).UpdateDotsNumber(dotsdrawn);
    }
}

void Pipeline::DrawCircuit(const figures2d::LineSegment& ls)
{
    std::cout << "Draw LineSegment "
              << ra_types::GetString(ls.getFirstPoint(), true) << "-"
              << ra_types::GetString(ls.getSecondPoint(), true) << " with rgb "
              << GetString(ls.getColorCode()) << std::endl;

    auto p1 = ls.getFirstPoint();
    auto p2 = ls.getSecondPoint();

    space_coord_trans_.TranslateWorldToCanvas(p1);
    space_coord_trans_.TranslateWorldToCanvas(p2);

    if (!IsVisibleLineSegment(p1, p2))
    {
        std::cout << "Object is invisible!" << std::endl;
    }
    else
    {
        auto ra_linesegment_func = raproxy_.getRenderLineSegment();

        auto point1 = TranslateToRenderingTarget(p1).point2i;
        auto point2 = TranslateToRenderingTarget(p2).point2i;

        auto dotsdrawn = ra_linesegment_func(point1, point2, ls.getColorCode(),
                                             *renderingTarget_ptr_);

        renderingTarget_ptr_->UpdateDotsNumber(dotsdrawn);
    }
}

void Pipeline::DrawCircuit(const figures2d::Circle& c)
{
    std::cout << "Draw Circle in " << ra_types::GetString(c.getCenter(), true)
              << "with R: " << c.getRadius() << " and rgb "
              << GetString(c.getColorCode()) << std::endl;

    auto center = c.getCenter();
    space_coord_trans_.TranslateWorldToCanvas(center);

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

        auto ra_circle_func = raproxy_.getRenderCircle();

        auto dotsdrawn = ra_circle_func(centerPoint, c.getRadius(),
                                        c.getColorCode(), *renderingTarget_ptr_);

        renderingTarget_ptr_->UpdateDotsNumber(dotsdrawn);
    }
}

void Pipeline::DrawCircuit(const figures2d::Triangle& tr)
{
    std::cout << "Draw Triangle " << ra_types::GetString(tr.getP1(), true)
              << "-" << ra_types::GetString(tr.getP2(), true) << "-"
              << ra_types::GetString(tr.getP3(), true) << "with rgb "
              << GetString(tr.getColorCode()) << std::endl;

    auto p1 = tr.getP1();
    auto p2 = tr.getP2();
    auto p3 = tr.getP3();

    space_coord_trans_.TranslateWorldToCanvas(p1);
    space_coord_trans_.TranslateWorldToCanvas(p2);
    space_coord_trans_.TranslateWorldToCanvas(p3);

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

    ra_types::Point2i P1{ TranslateToRenderingTarget(p1).point2i };
    ra_types::Point2i P2{ TranslateToRenderingTarget(p2).point2i };
    ra_types::Point2i P3{ TranslateToRenderingTarget(p3).point2i };

    auto ra_ls_func = raproxy_.getRenderLineSegment();

    auto dotsdrawn =
        ra_ls_func(P1, P2, tr.getColorCode(), *renderingTarget_ptr_);
    dotsdrawn += ra_ls_func(P2, P3, tr.getColorCode(), *renderingTarget_ptr_);
    dotsdrawn += ra_ls_func(P3, P1, tr.getColorCode(), *renderingTarget_ptr_);

    renderingTarget_ptr_->UpdateDotsNumber(dotsdrawn);
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
              << GetString(tr.getColorCode()) << std::endl;

    auto p1 = tr.getP1();
    auto p2 = tr.getP2();
    auto p3 = tr.getP3();

    // NOTE: actually can be 6 vertices, todo Polygon_partition
    space_coord_trans_.TranslateWorldToCanvas(p1);
    space_coord_trans_.TranslateWorldToCanvas(p2);
    space_coord_trans_.TranslateWorldToCanvas(p3);

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

    ra_types::Point2i P1{ TranslateToRenderingTarget(p1).point2i };
    ra_types::Point2i P2{ TranslateToRenderingTarget(p2).point2i };
    ra_types::Point2i P3{ TranslateToRenderingTarget(p3).point2i };

    auto ra_trf_func = raproxy_.getFillTriangle();

    auto dotsdrawn =
        ra_trf_func(P1, P2, P3, tr.getColorCode(), *renderingTarget_ptr_);

    renderingTarget_ptr_->UpdateDotsNumber(dotsdrawn);
}

void Pipeline::DrawCircuit(const figures2d::Quadrangle& qd)
{
    std::cout << "Draw Quadrangle " << ra_types::GetString(qd.getP1(), true)
              << "-" << ra_types::GetString(qd.getP2(), true) << "-"
              << ra_types::GetString(qd.getP3(), true) << "-"
              << ra_types::GetString(qd.getP4(), true) << "with rgb "
              << GetString(qd.getColorCode()) << std::endl;

    auto p1 = qd.getP1();
    auto p2 = qd.getP2();
    auto p3 = qd.getP3();
    auto p4 = qd.getP4();

    space_coord_trans_.TranslateWorldToCanvas(p1);
    space_coord_trans_.TranslateWorldToCanvas(p2);
    space_coord_trans_.TranslateWorldToCanvas(p3);
    space_coord_trans_.TranslateWorldToCanvas(p4);

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

    ra_types::Point2i P1{ TranslateToRenderingTarget(p1).point2i };
    ra_types::Point2i P2{ TranslateToRenderingTarget(p2).point2i };
    ra_types::Point2i P3{ TranslateToRenderingTarget(p3).point2i };
    ra_types::Point2i P4{ TranslateToRenderingTarget(p4).point2i };

    auto ra_ls_func = raproxy_.getRenderLineSegment();

    auto dotsdrawn =
        ra_ls_func(P1, P2, qd.getColorCode(), *renderingTarget_ptr_);
    dotsdrawn += ra_ls_func(P2, P3, qd.getColorCode(), *renderingTarget_ptr_);
    dotsdrawn += ra_ls_func(P3, P4, qd.getColorCode(), *renderingTarget_ptr_);
    dotsdrawn += ra_ls_func(P4, P1, qd.getColorCode(), *renderingTarget_ptr_);

    renderingTarget_ptr_->UpdateDotsNumber(dotsdrawn);
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

    auto copy(canvas_);

    return copy;
}

void Pipeline::setClipwin_ptr(const ClippingRectangularWindow* value)
{
    clipwin_ptr_ = value;
}

} // namespace ra_core::pipeline
