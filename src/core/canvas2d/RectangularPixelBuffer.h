#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <string>

#include "Directions.h"
#include "displacement2d.h"
#include "typedefs.h"

namespace ra_core
{
namespace canvas2d
{
class RectangularPixelBuffer
{
public:
    RectangularPixelBuffer();

    std::string_view     GetName() const;
    ra_types::size_t     GetWidth() const;
    ra_types::size_t     GetHeight() const;
    ra_types::n0_t       GetDotsNumber() const;
    ra_types::size_t     GetDotSize() const;
    ra_types::eDirection GetXAxisDirection() const;
    ra_types::eDirection GetYAxisDirection() const;
    /**
     * @brief GetZeroPointOffset dispalcemant from the left upper point at
     * screenview
     * @return result is packed into 2d displacement struct
     */
    ra_types::displacement2d GetZeroPointOffset() const;

    // TODO: remove placeholder
    void Foo() const;

private:
    const std::string_view name = "RectangularPixelBuffer";
    ra_types::size_t       width;
    ra_types::size_t       height;
    ra_types::n0_t         dotsNumber;
    ra_types::size_t       dotSize;
    ra_types::eDirection   xAxisDirection;
    ra_types::eDirection     yAxisDirection;
    ra_types::displacement2d zeroPointOffset;
};
} // namespace canvas2d

}; // namespace ra_core

#endif // PIXELBUFFER_H
