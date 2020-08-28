#ifndef CANVAS2D_H
#define CANVAS2D_H

#include <memory>

#include "AlgorithmProxy.h"
#include "DrawCircuit2dVisitor.h"
#include "DrawShape2dVisitor.h"
#include "DrawableInterface.h"
#include "Figure2dVisitor.h"
#include "RectangularPixelBuffer.h"

namespace ra_core::canvas2d
{

/**
 * @brief The Canvas2d class - main showcase functionality interface
 * @details Naturally, class implemets not only abstraction of the canvas, but
 * rendering configuration for pixel and dot buffers. Client can get the copy of
 * pixel buffer any time as canvas object exists.
 */
class Canvas2d
{
public:
    enum Mode
    {
        Ciruit,
        Shape
    };

    Canvas2d(Mode             mode       = Ciruit,
             ra_types::rgb888 color_code = ra_types::rgb888());
    ~Canvas2d();

    std::unique_ptr<RectangularPixelBuffer> getPixelBuffer();

    void Draw(const ra_core::figures2d::DrawableInterface& drawable) const;

    void setDrawingMode(Mode mode);

    void UseLineAlgorithm(AlgorithmProxy::rendering_algorithm algo_ptr) const;
    void UseCircleAlgorithm(AlgorithmProxy::rendering_algorithm algo_ptr) const;

    void UseFillingTriangle(AlgorithmProxy::rendering_algorithm algo_ptr) const;

private:
    std::unique_ptr<RectangularPixelBuffer> rpb;
    ra_core::figures2d::Figure2dVisitor*    drawVisitor;
};
} // namespace ra_core::canvas2d
#endif // CANVAS2D_H
