#include "rasterizer_simple.h"

namespace ra_core::pipeline
{
ra_types::n0_t RasterizerSimple::getDotSize() const
{
    return dot_size_;
}

void RasterizerSimple::ImageDotBufferToPixelBuffer() const
{
    // NOTE: currently ignore axes directions
    if (dot_size_ == 1)
    {
        auto dbcopy = dotbuf_.CreateCopy();

        ra_types::n0_t coord = 0;
        for (auto i = dbcopy->cbegin(); i != dbcopy->cend(); ++i)
        {
            pixbuf_.Mark(*i, cts_.TranslateDotBufferToCanvas(
                                   coord, dotbuf_.getLineWidth()));
            ++coord;
        }
    }
}

ra_core::pipeline::Canvas2d& RasterizerSimple::getCanvasRef() const
{
    return canvas_;
}

const ra_core::pipeline::SpaceCoordinateTranslatorSimple &RasterizerSimple::getCtsRef() const
{
    return cts_;
}

RasterizerSimple::RasterizerSimple(
        const ra_core::pipeline::DotLinearBuffer2d&               dotbufRef,
        ra_core::pipeline::PixelBuffer2d&                         pixbufRef,
    ra_core::pipeline::Canvas2d&                              canvasRef,
    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& ctsRef)
    : dotbuf_{ dotbufRef }
    , pixbuf_{ pixbufRef }
    , canvas_{ canvasRef }
    , cts_{ ctsRef }
{
}
} // namespace ra_core::pipeline
