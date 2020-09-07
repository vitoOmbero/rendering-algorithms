#ifndef ALGORITHMPROXY_H
#define ALGORITHMPROXY_H

#include <map>

#include "Figures2dTypeRegistry.h"
#include "algorithms_registry.h"
#include "algorithms_types.h"

namespace ra_core::pipeline
{
using namespace ra_core::rendering2d; // TODO: remove this

class AlgorithmProxy
{
public:
    AlgorithmProxy();

    ra_core::rendering2d::rendering_dot_fptr getRenderDot() const;

    ra_core::rendering2d::rendering_line_segment_fptr getRenderLineSegment()
        const;

    /**
     * @brief setRenderingAlgorithm - common setter for supported rendering
     * algorithms
     * @param figure2dType - enum type pointer to supported figure2d
     * @param ra - enum type pointer to supported rendering algorithm
     * @return true if set successfully
     */
    bool setRenderingCircuitAlgorithm(
        ra_core::figures2d::eFigure2dType figure2dType, rendering_algorithm ra);

    /**
     * @brief setFillingAlgorithm - common setter for supported filling
     * algorithms
     * @param figure2dType
     * @param ra
     * @return true if set successfully
     */
    bool setFillingAlgorithm(ra_core::figures2d::eFigure2dType figure2dType,
                             filling_algorithm                ca);

    /**
     * @brief setCustomRenderingAlgorithm - common setter for custom
     * rendering algorithm
     * @param figure2dType - enum type pointer to supported figure2d
     * @param function_ptr - suitable unction pointer for figure2d
     * rendering. See \link algorithms_types.h \endlink
     * @return true if set successfully
     */
    bool setCustomRenderingAlgorithm(
        ra_core::figures2d::eFigure2dType figure2dType, void* function_ptr);

    bool setClippingAlgorithm(clipping_algorithm alro_ptr);

    ra_core::rendering2d::rendering_circle_fptr getRenderCircle() const;

    ra_core::rendering2d::filling_triangle_fptr getFillTriangle() const;

    ra_core::rendering2d::clipping_line_fptr getClipRectangular() const;

private:
    /**
     * @brief IsValidRenderingAlgorithm - planned feature
     * @return always true !!! WARNING !!!
     */
    bool IsValidRenderingAlgorithm();

    typedef std::map<rendering_algorithm,
                     ra_core::rendering2d::rendering_dot_fptr>
        ra_dot_map;

    typedef std::map<rendering_algorithm,
                     ra_core::rendering2d::rendering_line_segment_fptr>
        ra_ls_map;

    typedef std::map<rendering_algorithm,
                     ra_core::rendering2d::rendering_circle_fptr>
        ra_cir_map;

    typedef std::map<filling_algorithm,
                     ra_core::rendering2d::filling_triangle_fptr>
        ra_fill3_map;

    typedef std::map<clipping_algorithm,
                     ra_core::rendering2d::clipping_line_fptr>
        ra_clip_map;

    ra_dot_map   rendering_dot_map;
    ra_ls_map  rendering_line_segment_map;
    ra_cir_map rendering_circle_map;
    ra_fill3_map fill3_map;
    ra_clip_map  clip_map;

    ra_core::rendering2d::rendering_dot_fptr          renderDot;
    ra_core::rendering2d::rendering_line_segment_fptr renderLineSegment;
    ra_core::rendering2d::rendering_circle_fptr       renderCircle;
    ra_core::rendering2d::filling_triangle_fptr       fillTriangle;
    ra_core::rendering2d::clipping_line_fptr          clipRectangular;
};
} // namespace ra_core::canvas2d
#endif // ALGORITHMPROXY_H
