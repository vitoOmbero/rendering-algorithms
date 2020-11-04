#ifndef DEFAULT_PIPELINE_VALUES_INC
#define DEFAULT_PIPELINE_VALUES_INC

#include "ra_types.h"

namespace ra_core::renderer
{

inline constexpr ra_types::Rgb888 CANVAS_DEFAULT_COLOR_CODE =
    ra_types::Rgb888();
inline constexpr ra_types::Rgb888 WORLD_DEFAULT_COLOR_CODE =
    ra_types::Rgb888(127);
inline constexpr ra_types::n0_t                  CANVAS_WIDTH_DT        = 800;
inline constexpr ra_types::n0_t                  CANVAS_HEIGHT_DT       = 600;
[[maybe_unused]] inline constexpr ra_types::n0_t RASTERIZATION_DOT_SIZE = 1;
inline constexpr ra_types::n0_t                  CANVAS_WIDTH_PX        = 800;
inline constexpr ra_types::n0_t                  CANVAS_HEIGHT_PX       = 600;
inline constexpr ra_types::displacement2i        ZERO_OFFSET =
    ra_types::displacement2i{ 0, 0 };

} // namespace ra_core::renderer
#endif // DEFAULT_PIPELINE_VALUES_INC
