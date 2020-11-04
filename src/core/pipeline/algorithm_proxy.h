#ifndef ALGORITHMPROXY_H
#define ALGORITHMPROXY_H

#include <map>

#include "figures2d_type_registry.h"
#include "algorithms_registry.h"
#include "algorithms_types.h"

namespace ra_core::pipeline
{
using namespace ra_core::rendering2d; // TODO: remove this

class AlgorithmProxy
{
public:
    AlgorithmProxy();

    [[nodiscard]] ra_core::rendering2d::RenderingDotFunction getRenderDot() const;

    [[nodiscard]] ra_core::rendering2d::RenderingLineSegmentFunction getRenderLineSegment()
        const;

    /**
     * @brief setRenderingAlgorithm - common setter for supported rendering
     * algorithms
     * @param figure2dType - enum type pointer to supported figure2d
     * @param ra - enum type pointer to supported rendering algorithm
     * @return true if set successfully
     */
    bool setRenderingCircuitAlgorithm(
        ra_core::figures2d::Figure2dType figure2d_type,
        RenderingAlgorithm               algo);

    /**
     * @brief setFillingAlgorithm - common setter for supported filling
     * algorithms
     * @param figure2dType
     * @param ra
     * @return true if set successfully
     */
    bool setFillingAlgorithm(ra_core::figures2d::Figure2dType figure2d_type,
                             FillingAlgorithm                 algo);

    /**
     * @brief setCustomRenderingAlgorithm - common setter for custom
     * rendering algorithm
     * @param figure2dType - enum type pointer to supported figure2d
     * @param function_ptr - suitable unction pointer for figure2d
     * rendering. See \link algorithms_types.h \endlink
     * @return true if set successfully
     */
    bool setCustomRenderingAlgorithm(
        ra_core::figures2d::Figure2dType figure2d_type, void* function_ptr);

    bool setCustomFillingAlgorithm(
        ra_core::figures2d::Figure2dType figure2d_type, void* function_ptr);

    bool setClippingAlgorithm(ClippingAlgorithm algo);

    [[nodiscard]] ra_core::rendering2d::RenderingCircleFunction getRenderCircle() const;

    [[nodiscard]] ra_core::rendering2d::FillingTriangleFunction getFillTriangle() const;

    [[nodiscard]] ra_core::rendering2d::ClippingLineFunction getClipRectangular() const;

private:
    // NOTE: todo algo validation
    /**
     * @brief IsValidRenderingAlgorithm - planned feature
     * @return always true !!! WARNING !!!
     */
    bool IsValidRenderingAlgorithm();

    typedef std::map<RenderingAlgorithm,
                     ra_core::rendering2d::RenderingDotFunction>
        DotMap;

    typedef std::map<RenderingAlgorithm,
                     ra_core::rendering2d::RenderingLineSegmentFunction>
        LineSegMap;

    typedef std::map<RenderingAlgorithm,
                     ra_core::rendering2d::RenderingCircleFunction>
        CircMap;

    typedef std::map<FillingAlgorithm,
                     ra_core::rendering2d::FillingTriangleFunction>
        Fill3Map;

    typedef std::map<ClippingAlgorithm,
                     ra_core::rendering2d::ClippingLineFunction>
        ClipMap;

    DotMap     rendering_dot_map_;
    LineSegMap rendering_line_segment_map_;
    CircMap    rendering_circle_map_;
    Fill3Map   fill3_map_;
    ClipMap    clip_map_;

    ra_core::rendering2d::RenderingDotFunction render_dot_func_{};
    ra_core::rendering2d::RenderingLineSegmentFunction
                                                  render_line_segment_func_{};
    ra_core::rendering2d::RenderingCircleFunction render_circle_func_{};
    ra_core::rendering2d::FillingTriangleFunction fill_triangle_func_{};
    ra_core::rendering2d::ClippingLineFunction    clip_rectangular_func_{};
};
} // namespace ra_core::canvas2d
#endif // ALGORITHMPROXY_H
