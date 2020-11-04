#ifndef RECTANGULAR1DPIXELBUFFER_H
#define RECTANGULAR1DPIXELBUFFER_H
#include <cassert>
#include <memory>
#include <vector>

#include "rendering_target_base.h"
#include "space_coordinate_translator_simple.h"
#include "ra_types.h"

namespace ra_core::pipeline
{

class DotLinearBuffer2d final : public RenderingTargetBase
{
public:
    DotLinearBuffer2d(
        const ra_types::Space1i&                                  space,
        const ra_core::pipeline::SpaceCoordinateTranslatorSimple& cts,
        ra_types::n0_t                                            line_width,
        ra_types::Rgb888 default_color_code = ra_types::Rgb888());

    ~DotLinearBuffer2d() override;

    /**
     * @brief Mark - paint dot with selected paint color
     * @param code - color for current mark
     * @param point - dot cartesian coordinates
     */
    void Mark(ra_types::Rgb888  code,
              ra_types::Point2i point) override;
    /**
     * @brief Mark - paint horizontal line segment with selected paint color
     * @param code - color for current mark
     * @param start - cartesian coordinates of first segment's end
     * @param end - cartesian coordinates of second segment's end
     */
    void Mark(ra_types::Rgb888 code, ra_types::Point2i start,
              ra_types::Point2i end) override;

    ra_types::Rgb888 getColorCode(ra_types::Point2i point) override;

    [[nodiscard]] std::unique_ptr<std::vector<ra_types::Rgb888>> CreateCopy() const override;

    [[nodiscard]] ra_types::n0_t getLastIndex() const;
    [[nodiscard]] ra_types::n0_t getZeroPointIndex() const;

    [[nodiscard]] const ra_types::Space1i& getSpaceRef() const;

    [[nodiscard]] ra_types::n0_t getLineWidth() const;

    [[nodiscard]] ra_types::displacement1i_t getZeroPointOffset() const
    {
        return space_.viewZeroPointOffset;
    };

private:
    std::vector<ra_types::Rgb888>* dots_ptr_;

    /**
     * @brief spaceRef - reference to space description object
     */
    const ra_types::Space1i& space_;

    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& cts_;
    /**
     * @brief lineWidth - buffer line width for 1d-2d traslation
     */
    ra_types::n0_t line_width_;
};

} // namespace ra_core::canvas2d
#endif // RECTANGULAR1DPIXELBUFFER_H
