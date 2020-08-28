#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "AlgorithmProxy.h"
#include "Circle.h"
#include "Directions.h"
#include "Dot.h"
#include "LineSegment.h"
#include "Rectangular1dDotBuffer.h"
#include "Triangle.h"
#include "algorithms_lines_naive.h"
#include "displacement2d.h"
#include "typedefs.h"

namespace ra_core::canvas2d
{
/**
 * @brief The RectangularPixelBuffer class - provides view for cartesian 2d
 * space
 * @details The class is supporting friendship between view 2d limited space,
 * cartesian unlimited coordinate system and limitied dot buffer space (which is
 * at least 1d space). NOTE: this class is implicitly lazy: not visible dots are
 * not drawn.
 */
class RectangularPixelBuffer
{
public:
    RectangularPixelBuffer(
        ra_types::rgb888 default_color_code = ra_types::rgb888());
    ~RectangularPixelBuffer();

    std::string_view         getName() const;
    ra_types::n0_t           getPxWidth() const;
    ra_types::n0_t           getPxHeight() const;
    ra_types::n0_t           getBufferDotsNumber() const;
    ra_types::n0_t           getBufferDotSize() const;
    ra_types::n0_t           getBufferZeroIndex() const;
    ra_types::n0_t           getBufferLastIndex() const;
    ra_types::n0_t           getBufferZeroPointIndex() const;
    ra_types::n0_t           getDtWidth() const;
    ra_types::n0_t           getDtHeight() const;
    ra_types::eScreenDirection     getXAxisDirection() const;
    ra_types::eScreenDirection     getYAxisDirection() const;
    ra_types::displacement2d getHighestVisiblePoint() const;
    ra_types::displacement2d getLowestVisiblePoint() const;
    /**
     * @brief GetZeroPointOffset dispalcemant from the left upper point at
     * screenview
     * @return result is packed into 2d displacement struct
     */
    ra_types::displacement2d getZeroPointOffset() const;

    void DrawCircuit(const ra_core::figures2d::Dot& dot) const;
    void DrawCircuit(const ra_core::figures2d::LineSegment& ls) const;
    void DrawCircuit(const ra_core::figures2d::Circle& c) const;
    void DrawCircuit(const ra_core::figures2d::Triangle& tr) const;

    void DrawShape(const ra_core::figures2d::Circle& c) const;
    void DrawShape(const ra_core::figures2d::Triangle& tr) const;

    /**
     * @brief StumpBufferCopy - make new copy of pixel buffer
     * @param width_px - desired width in pixels
     * @param height_px - desired height in pixels
     * @param xOffset - additional offset along 0x
     * @param yOffset - additional offset along 0y
     * @return unique pointer to vector
     */
    std::unique_ptr<std::vector<ra_types::rgb888>> StumpBufferCopy(
        ra_types::n0_t width_px, ra_types::n0_t height_px,
        ra_types::displacement_t xOffset = 0,
        ra_types::displacement_t yOffset = 0) const;

    // when add new Use* do not forget to set the default value in ctor
    void UseLineAlgorithm(AlgorithmProxy::rendering_algorithm algo_ptr);
    void UseCircleAlgorithm(AlgorithmProxy::rendering_algorithm algo_ptr);
    void UseFilling3v(AlgorithmProxy::rendering_algorithm algo_ptr);

private:
    /**
     * @brief IsVisible - visability check in canvas coordinate system
     * @param x - checked with width
     * @param y - checked with height
     * @return a truth you have to come to terms with
     */
    inline bool IsVisible(ra_types::displacement_t x,
                          ra_types::displacement_t y) const
    {
        return IsVisible({ x, y });
    };
    /**
     * @brief IsVisible - visability check in canvas coordinate system
     * @param point - 2d displacement
     * @return a truth you have to come to terms with
     */
    inline bool IsVisible(ra_types::displacement2d point) const
    {
        return point >= lowestVisiblePoint && point <= highestVisiblePoint;
    };
    friend ra_types::displacement2d CalculateLowestVisiblePoint(
        RectangularPixelBuffer*);
    friend ra_types::displacement2d CalculateHighestVisiblePoint(
        RectangularPixelBuffer*);
    friend ra_types::displacement2d Cartesian2dToCanvas2d(
        ra_types::displacement2d point, ra_types::displacement2d offset);

    const std::string_view name = "RectangularPixelBuffer";
    /**
     * @brief width - in pixels
     */
    ra_types::n0_t width;
    /**
     * @brief height - in pixels
     */
    ra_types::n0_t height;

    /**
     * @brief xAxisDirection - view relative direction
     */
    ra_types::eScreenDirection xAxisDirection;
    /**
     * @brief yAxisDirection - view relative direction
     */
    ra_types::eScreenDirection yAxisDirection;
    /**
     * @brief zeroPointOffset - zeroPoint is cartesian O(0;0) point
     * @details zeroPointOffset is measured in canvas coordinate system. e.g.
     * (5;5) offset lifts up cartesian zero point by 5 dots along two axes.
     * This one shows 2d displacement between imaginable carthesian 2d space and
     * 2d canvas space as canvas have its own coordinate system with
     * non-negative numbers (Q1 only). \link
     * Rectangular1dDotBuffer::zeroPointIndex in 1dBuffer \endlink
     */
    ra_types::displacement2d zeroPointOffset;
    /**
     * @brief lowestVisiblePoint - point (0;0) at canvas coordinate system
     * @details \link Rectangular1dDotBuffer::zeroPointIndex
     * \endlink
     */
    ra_types::displacement2d lowestVisiblePoint;
    /**
     * @brief highestVisiblePoint - point (width;height) at canvas coordinate
     * system
     * @details \link Rectangular1DotBuffer::lastIndex in 1dBuffer \endlink
     */
    ra_types::displacement2d highestVisiblePoint;
    /**
     * @brief dots - canvas dots storage.
     * @details 1 dot == 1 pixel when dotSize = 1.
     */
    Rectangular1dDotBuffer* dotbuf;
    AlgorithmProxy          raproxy;
};

}; // namespace ra_core::canvas2d

#endif // PIXELBUFFER_H
