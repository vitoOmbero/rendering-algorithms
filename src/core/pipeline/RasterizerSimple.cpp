#include "RasterizerSimple.h"

namespace ra_core::pipeline
{
ra_types::n0_t RasterizerSimple::getDotSize() const
{
    return dotSize;
}

void RasterizerSimple::ImageDotBufferToPixelBuffer() const
{
    // NOTE: currently ignore axes directions
    if (dotSize == 1)
    {
        auto dbcopy = dotbufRef.CreateCopy();

        ra_types::n0_t coord = 0;
        for (auto i = dbcopy->cbegin(); i != dbcopy->cend(); ++i)
        {
            pixbufRef.Mark(*i, ctsRef.TranslateDotBufferToCanvas(
                                   coord, dotbufRef.getLineWidth()));
            ++coord;
        }
    }
}

ra_core::pipeline::Canvas2d& RasterizerSimple::getCanvasRef() const
{
    return canvasRef;
}

const ra_core::pipeline::SpaceCoordinateTranslatorSimple &RasterizerSimple::getCtsRef() const
{
    return ctsRef;
}

RasterizerSimple::RasterizerSimple(
        const ra_core::pipeline::DotLinearBuffer2d&               dotbufRef,
        ra_core::pipeline::PixelBuffer2d&                         pixbufRef,
    ra_core::pipeline::Canvas2d&                              canvasRef,
    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& ctsRef)
    : dotbufRef{ dotbufRef }
    , pixbufRef{ pixbufRef }
    , canvasRef{ canvasRef }
    , ctsRef{ ctsRef }
{
}
} // namespace ra_core::pipeline
