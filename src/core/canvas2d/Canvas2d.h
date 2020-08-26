#ifndef CANVAS2D_H
#define CANVAS2D_H

#include <memory>

#include "DrawFigure2dVisitor.h"
#include "DrawableInterface.h"
#include "Figure2dVisitor.h"
#include "RectangularPixelBuffer.h"

namespace ra_core::canvas2d
{

class Canvas2d
{
public:
    Canvas2d();
    ~Canvas2d();

    std::unique_ptr<RectangularPixelBuffer> getPixelBuffer();

    void Draw(const ra_core::figures2d::DrawableInterface& drawable) const;

private:
    std::unique_ptr<RectangularPixelBuffer> rpb;
    ra_core::figures2d::Figure2dVisitor*    drawVisitor;
};
} // namespace ra_core::canvas2d
#endif // CANVAS2D_H
