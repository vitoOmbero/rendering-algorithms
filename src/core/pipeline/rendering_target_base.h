#ifndef DRAWTARGETINTERFACE_H
#define DRAWTARGETINTERFACE_H

#include <memory>
#include <variant>
#include <vector>

#include "ra_types.h"

namespace ra_core::pipeline
{

class RenderingTargetBase

{
public:
    virtual ~RenderingTargetBase() = default;

    /**
     * @brief UpdateDotsNumber - utility function to count painted dots
     * @param inc - increment
     */
    virtual void UpdateDotsNumber(ra_types::n0_t inc) { total_ += inc; }

    /**
     * @brief Paint - set active color
     * @param code - color code
     */
    void Paint(const ra_types::Rgb888 code) { active_color_ = code; };
    /**
     * @brief Mark - paint dot with selected paint color
     * @param point - point with coordinates
     */
    void Mark(const ra_types::Point2i point) { Mark(active_color_, point); };
    /**
     * @brief Mark - paint line segment with selected paint color
     * @param start - cartesian coordinates of first segment's end
     * @param end - cartesian coordinates of second segment's end
     */
    void Mark(const ra_types::Point2i start, const ra_types::Point2i end)
    {
        Mark(active_color_, start, end);
    };

    virtual void Mark(ra_types::Rgb888 code, ra_types::Point2i point) = 0;

    virtual void Mark(ra_types::Rgb888 code, ra_types::Point2i start,
                      ra_types::Point2i end) = 0;

    [[nodiscard]] virtual std::unique_ptr<std::vector<ra_types::Rgb888>>
    CreateCopy() const = 0;

    virtual ra_types::Rgb888 getColorCode(ra_types::Point2i point) = 0;

    [[nodiscard]] ra_types::n0_t getTotalElementsDrawn() const
    {
        return total_;
    };

protected:
    ra_types::Rgb888 active_color_;
    ra_types::n0_t   total_{};
};

} // namespace ra_core::pipeline

#endif // DRAWTARGETINTERFACE_H
