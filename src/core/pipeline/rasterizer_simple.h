#ifndef SIMPLERASTERIZER_H
#define SIMPLERASTERIZER_H

#include <memory>
#include <vector>

#include "canvas2d.h"
#include "dot_linear_buffer2d.h"
#include "pixel_buffer2d.h"
#include "ra_types.h"

namespace ra_core::pipeline
{

class RasterizerSimple
{
public:
    RasterizerSimple(
        const ra_core::pipeline::DotLinearBuffer2d&               dotbuf,
        ra_core::pipeline::PixelBuffer2d&                         pixbuf,
        ra_core::pipeline::Canvas2d&                              canvas,
        const ra_core::pipeline::SpaceCoordinateTranslatorSimple& cts);

    [[nodiscard]] ra_types::n0_t getDotSize() const;

    /**
     * @brief ImageDotBufferToPixelBuffer - rasterize dot image
     */
    void ImageDotBufferToPixelBuffer() const;

    [[nodiscard]] ra_core::pipeline::Canvas2d& getCanvasRef() const;

    [[nodiscard]] const ra_core::pipeline::SpaceCoordinateTranslatorSimple& getCtsRef() const;

private:
    /**
     * @brief dotSize - scale of canvas image unit
     * @details dotSize = 2 means canvas unit is 2x2 pixel group
     */
    ra_types::n0_t                                            dot_size_ = 1;
    const ra_core::pipeline::DotLinearBuffer2d&               dotbuf_;
    ra_core::pipeline::PixelBuffer2d&                         pixbuf_;
    ra_core::pipeline::Canvas2d&                              canvas_;
    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& cts_;
};

} // namespace ra_core::pipeline
#endif // SIMPLERASTERIZER_H
