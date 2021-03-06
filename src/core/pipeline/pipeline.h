#ifndef PIPELINE_H
#define PIPELINE_H

#include "algorithm_proxy.h"
#include "canvas2d.h"
#include "clipping_rectangular_window.h"
#include "dot_linear_buffer2d.h"
#include "pipeline_targets.h"
#include "pixel_buffer2d.h"
#include "rasterizer_simple.h"
#include "rendering_target_base.h"
#include "space_coordinate_translator_simple.h"

#include "circle.h"
#include "dot.h"
#include "line_segment.h"
#include "quadrangle.h"
#include "triangle.h"

namespace ra_core::pipeline
{

class Pipeline
{
public:
    Pipeline(const ClippingRectangularWindow*       clipwin,
             const AlgorithmProxy&                  raproxy,
             const SpaceCoordinateTranslatorSimple& space_coord_trans);

    /**     * @brief DrawCircuit using world coordinate system
     * @param dot
     */
    void DrawCircuit(const ra_core::figures2d::Dot& dot);
    /**
     * @brief DrawCircuit using world coordinate system
     * @param ls
     */
    void DrawCircuit(const ra_core::figures2d::LineSegment& ls);
    /**
     * @brief DrawCircuit using world coordinate system
     * @param c
     */
    void DrawCircuit(const ra_core::figures2d::Circle& c);
    /**
     * @brief DrawCircuit using world coordinate system
     * @param tr
     */
    void DrawCircuit(const ra_core::figures2d::Triangle& tr);

    /**
     * @brief DrawShape using world coordinate system
     * @param c
     */
    void DrawShape(const ra_core::figures2d::Circle& c);
    /**
     * @brief DrawShape using world coordinate system
     * @param tr
     */
    void DrawShape(const ra_core::figures2d::Triangle& tr);

    /**
     * @brief DrawCircuit using world coordinate system
     * @param tr
     */
    void DrawCircuit(const ra_core::figures2d::Quadrangle& tr);
    /**
     * @brief DrawShape using world coordinate system
     * @param tr
     */
    void DrawShape(const ra_core::figures2d::Quadrangle& tr);

    /**
     * @brief IsVisible - visability check with clipping in canvas coordinate
     * system
     * @param point - 2d point
     * @return a truth you have to come to terms with
     */
    [[nodiscard]] inline bool IsVisible(ra_types::Point2i point) const
    {
        return IsVisibleLineSegment(point, point);
    };

    /**
     * @brief IsVisible - visability check with clipping in canvas coordinate
     * system
     * @param x - checked with width
     * @param y - checked with height
     * @return a truth you have to come to terms with
     */
    [[nodiscard]] inline bool IsVisible(ra_types::displacement1i_t x,
                          ra_types::displacement1i_t y) const
    {
        return IsVisible({ x, y });
    };

    /**
     * @brief IsVisibleLineSegment - calls clipping window to process points if
     * one is set, otherwise returns true;
     * @param p1 - first point
     * @param p2 - second point
     * @return  a truth you have to come to terms with
     */
    bool IsVisibleLineSegment(ra_types::Point2i& p1,
                              ra_types::Point2i& p2) const;

    [[nodiscard]] pipeline::Target getExportTarget() const;
    void              setExportTarget(const pipeline::Target& value);

    [[nodiscard]] pipeline::Target getRenderingTarget() const;
    void              setRenderingTarget(const pipeline::Target& value);

    /**
     * @brief TranslateToRenderingTarget - translate coordinates to actual
     * coordinate system
     * @param p
     */
    [[nodiscard]] ra_types::pointXi TranslateToRenderingTarget(
        const ra_types::Point2i& p) const;

    /**
     * @brief StumpCanvas - stump target buffer into canvas
     */
    void StumpCanvas();

    /**
     * @brief ExportCanvas - render export target into image and get result
     * canvas
     * @return reasult Canvas2d value copy
     */
    ra_core::pipeline::Canvas2d ExportCanvas();

    /**
     * @brief setClipwin_ptr - pipeline use clipping if is set
     * @param value
     */
    void setClipwin_ptr(const ClippingRectangularWindow* value);

private:
    const ClippingRectangularWindow* clipwin_ptr_;

    const AlgorithmProxy& raproxy_;

    const SpaceCoordinateTranslatorSimple& space_coord_trans_;

    DotLinearBuffer2d dotbuf_;

    PixelBuffer2d pixbuf_;

    Canvas2d canvas_;

    RasterizerSimple rasterizer_;

    pipeline::Target     rendering_target_;
    pipeline::Target     export_target_;
    RenderingTargetBase* renderingTarget_ptr_;
};

} // namespace ra_core::pipeline
#endif // PIPELINE_H
