#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <string>

#include "rendering_target_base.h"
#include "space_coordinate_translator_simple.h"
#include "algorithms_lines_naive.h"
#include "ra_types.h"

namespace ra_core::pipeline
{
/**
 * @brief The RectangularPixelBuffer class - provides view for cartesian 2d
 * space
 * @details The class is supporting friendship between view 2d limited space,
 * cartesian unlimited coordinate system and limitied dot buffer space (which is
 * at least 1d space). NOTE: this class is implicitly lazy: not visible dots are
 * not drawn.
 */
class PixelBuffer2d final : public RenderingTargetBase
{
public:
    PixelBuffer2d(const ra_types::Space2i& space,
                  const ra_core::pipeline::SpaceCoordinateTranslatorSimple& cts,
                  ra_types::Rgb888 default_color_code);
    ~PixelBuffer2d() override;

    /**
     * @brief getName - viewable Buffer type name
     * @return readonly string_view
     */
    [[nodiscard]] std::string getName() const;

    void Mark(ra_types::Rgb888  code,
              ra_types::Point2i point) override;

    void Mark(ra_types::Rgb888 code, ra_types::Point2i start,
              ra_types::Point2i end) override;

    ra_types::Rgb888 getColorCode(ra_types::Point2i point) override;

    [[nodiscard]] std::unique_ptr<std::vector<ra_types::Rgb888>> CreateCopy() const override;

    [[nodiscard]] ra_types::displacement2i getZeroPointOffset() const
    {
        return space_.viewZeroPointOffset;
    };

private:
    const std::string name_;
    /**
     * @brief space_ - reference to space description object
     */
    const ra_types::Space2i& space_;

    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& cts_;
    std::vector<std::vector<ra_types::Rgb888>>*               vector2d_ptr_;
};

} // namespace ra_core::pipeline

#endif // PIXELBUFFER_H
