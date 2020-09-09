#ifndef PIPELINE_H
#define PIPELINE_H

#include "AlgorithmProxy.h"
#include "Canvas2d.h"
#include "ClippingRectangularWindow.h"
#include "DotLinearBuffer2d.h"
#include "PipelineTargets.h"
#include "PixelBuffer2d.h"
#include "RasterizerSimple.h"
#include "RenderingTargetBase.h"
#include "SpaceCoordinateTranslatorSimple.h"

#include "Circle.h"
#include "Dot.h"
#include "LineSegment.h"
#include "Quadrangle.h"
#include "Triangle.h"

namespace ra_core::pipeline
{

class Pipeline
{
public:
    Pipeline(const ClippingRectangularWindow*       clipwin_ptr,
             const AlgorithmProxy&                  raproxyRef,
             const SpaceCoordinateTranslatorSimple& spaceCoordTransRef);

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
    inline bool IsVisible(ra_types::point2i point) const
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
    inline bool IsVisible(ra_types::displacement1i_t x,
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
    bool IsVisibleLineSegment(ra_types::point2i& p1,
                              ra_types::point2i& p2) const;

    pipeline::eTarget getExportTarget() const;
    void              setExportTarget(const pipeline::eTarget& value);

    pipeline::eTarget getRenderingTarget() const;
    void              setRenderingTarget(const pipeline::eTarget& value);

    /**
     * @brief TranslateToRenderingTarget - translate coordinates to actual
     * coordinate system
     * @param p
     */
    ra_types::pointXi TranslateToRenderingTarget(
        const ra_types::point2i& p) const;

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
    const ClippingRectangularWindow* clipwin_ptr;

    const AlgorithmProxy& raproxyRef;

    const SpaceCoordinateTranslatorSimple& spaceCoordTransRef;

    DotLinearBuffer2d dotbuf;

    PixelBuffer2d pixbuf;

    Canvas2d canvas;

    RasterizerSimple rasterizer;

    pipeline::eTarget renderingTarget;
    pipeline::eTarget exportTarget;
    RenderingTargetBase* renderingTarget_ptr;
};

} // namespace ra_core::pipeline
#endif // PIPELINE_H
