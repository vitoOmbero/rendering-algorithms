#ifndef CANVAS2D_H
#define CANVAS2D_H

#include <memory>

#include "AlgorithmProxy.h"
#include "DrawFigure2dVisitor.h"
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
    Canvas2d();
    ~Canvas2d();

    std::unique_ptr<RectangularPixelBuffer> getPixelBuffer();

    void Draw(const ra_core::figures2d::DrawableInterface& drawable) const;

    void UseLineAlgorithm(AlgorithmProxy::rendering_algorithm algo_ptr) const;

private:
    std::unique_ptr<RectangularPixelBuffer> rpb;
    ra_core::figures2d::Figure2dVisitor*    drawVisitor;
};
} // namespace ra_core::canvas2d
#endif // CANVAS2D_H
