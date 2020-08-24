#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <iostream>
#include <string>

#include "Directions.h"
#include "Dot.h"
#include "displacement2d.h"
#include "typedefs.h"

namespace ra_core::canvas2d
{

class RectangularPixelBuffer
{
public:
    RectangularPixelBuffer();

    std::string_view     GetName() const;
    ra_types::n0_t       GetWidth() const;
    ra_types::n0_t       GetHeight() const;
    ra_types::n0_t       GetDotsNumber() const;
    ra_types::n0_t       GetDotSize() const;
    ra_types::eDirection GetXAxisDirection() const;
    ra_types::eDirection GetYAxisDirection() const;
    /**
     * @brief GetZeroPointOffset dispalcemant from the left upper point at
     * screenview
     * @return result is packed into 2d displacement struct
     */
    ra_types::displacement2d GetZeroPointOffset() const;

    void Draw(const ra_core::figures2d::Dot& dot) const;

    // TODO: remove placeholder when implementin ppxviewer
    void Foo() const;

private:
    const std::string_view name = "RectangularPixelBuffer";
    ra_types::n0_t           width           = 800;
    ra_types::n0_t           height          = 600;
    ra_types::n0_t           dotsNumber      = 0;
    ra_types::n0_t           dotSize         = 1;
    ra_types::eDirection     xAxisDirection  = ra_types::eDirection::East;
    ra_types::eDirection     yAxisDirection  = ra_types::eDirection::South;
    ra_types::displacement2d zeroPointOffset = { 0, 0 };
};

}; // namespace ra_core::canvas2d

#endif // PIXELBUFFER_H
