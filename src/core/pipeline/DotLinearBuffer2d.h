#ifndef RECTANGULAR1DPIXELBUFFER_H
#define RECTANGULAR1DPIXELBUFFER_H
#include <cassert>
#include <memory>
#include <vector>

#include "RenderingTargetBase.h"
#include "SpaceCoordinateTranslatorSimple.h"
#include "ra_types.h"

namespace ra_core::pipeline
{

class DotLinearBuffer2d final : public RenderingTargetBase
{
public:
    DotLinearBuffer2d(
        const ra_types::Space1i&                                  spaceRef,
        const ra_core::pipeline::SpaceCoordinateTranslatorSimple& ctsRef,
        ra_types::n0_t                                            lineWidth,
        ra_types::rgb888 default_color_code = ra_types::rgb888());

    ~DotLinearBuffer2d();

    /**
     * @brief Mark - paint dot with selected paint color
     * @param code - color for current mark
     * @param point - dot cartesian coordinates
     */
    void Mark(const ra_types::rgb888  code,
              const ra_types::point2i point) override;
    /**
     * @brief Mark - paint horizontal line segment with selected paint color
     * @param code - color for current mark
     * @param start - cartesian coordinates of first segment's end
     * @param end - cartesian coordinates of second segment's end
     */
    void Mark(const ra_types::rgb888 code, const ra_types::point2i start,
              const ra_types::point2i end) override;

    std::unique_ptr<std::vector<ra_types::rgb888>> CreateCopy() const override;

    ra_types::n0_t getLastIndex() const;
    ra_types::n0_t getZeroPointIndex() const;

    const ra_types::Space1i& getSpaceRef() const;

    ra_types::n0_t getLineWidth() const;

    ra_types::displacement1i_t getZeroPointOffset() const
    {
        return spaceRef.viewZeroPointOffset;
    };

private:
    std::vector<ra_types::rgb888>* dots;

    /**
     * @brief spaceRef - reference to space description object
     */
    const ra_types::Space1i& spaceRef;

    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& ctsRef;
    /**
     * @brief lineWidth - buffer line width for 1d-2d traslation
     */
    ra_types::n0_t lineWidth;
};

} // namespace ra_core::canvas2d
#endif // RECTANGULAR1DPIXELBUFFER_H
