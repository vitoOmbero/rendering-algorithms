#ifndef ALGORITHMPROXY_H
#define ALGORITHMPROXY_H

#include <map>

#include "Figures2dTypeRegistry.h"
#include "algorithms_types.h"

namespace ra_core::canvas2d
{

class AlgorithmProxy
{
public:
    AlgorithmProxy();

#include "rendering_algorithm_registry.inc"

    ra_core::rendering2d::rendering_dot_fptr getRenderingDot() const;

    ra_core::rendering2d::rendering_line_segment_fptr getRenderingLineSegment()
        const;

    /**
     * @brief setRenderingAlgorithm - common setter for supported rendering
     * algorithms
     * @param figure2dType - enum type pointer to supported figure2d
     * @param ra - enum type pointer to supported rendering algorithm
     * @return true if set successfully
     */
    bool setRenderingAlgorithm(ra_core::figures2d::eFigure2dType figure2dType,
                               rendering_algorithm               ra);
    /**
     * @brief setCustomRenderingAlgorithm - common setter for custom rendering
     * algorithm
     * @param figure2dType - enum type pointer to supported figure2d
     * @param function_ptr - suitable unction pointer for figure2d rendering.
     * See \link algorithms_types.h \endlink
     * @return true if set successfully
     */
    bool setCustomRenderingAlgorithm(
        ra_core::figures2d::eFigure2dType figure2dType, void* function_ptr);

    ra_core::rendering2d::rendering_circle_fptr getRenderingCircle() const;

private:
    bool IsValidRenderingAlgorithm(); // placeholder - should be
                                      // deleted

    typedef std::map<rendering_algorithm,
                     ra_core::rendering2d::rendering_dot_fptr>
        ra_dot_map;

    typedef std::map<rendering_algorithm,
                     ra_core::rendering2d::rendering_line_segment_fptr>
        ra_ls_map;

    typedef std::map<rendering_algorithm,
                     ra_core::rendering2d::rendering_circle_fptr>
        ra_cir_map;

    ra_dot_map rendering_dot_map;
    ra_ls_map  rendering_line_segment_map;
    ra_cir_map rendering_circle_map;

    ra_core::rendering2d::rendering_dot_fptr          renderingDot;
    ra_core::rendering2d::rendering_line_segment_fptr renderingLineSegment;
    ra_core::rendering2d::rendering_circle_fptr       renderingCircle;
};
} // namespace ra_core::canvas2d
#endif // ALGORITHMPROXY_H
