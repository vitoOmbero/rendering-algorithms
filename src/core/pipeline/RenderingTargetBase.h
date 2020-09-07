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
    virtual ~RenderingTargetBase(){};

    /**
     * @brief UpdateDotsNumber - utility function to count painted dots
     * @param inc - increment
     */
    virtual void UpdateDotsNumber(ra_types::n0_t inc) { total += inc; }

    /**
     * @brief Paint - set active color
     * @param code - color code
     */
    void Paint(const ra_types::rgb888 code) { activeColor = code; };
    /**
     * @brief Mark - paint dot with selected paint color
     * @param point - point with coordinates
     */
    void Mark(const ra_types::point2i point) { Mark(activeColor, point); };
    /**
     * @brief Mark - paint line segment with selected paint color
     * @param start - cartesian coordinates of first segment's end
     * @param end - cartesian coordinates of second segment's end
     */
    void Mark(const ra_types::point2i start, const ra_types::point2i end)
    {
        Mark(activeColor, start, end);
    };

    virtual void Mark(const ra_types::rgb888  code,
                      const ra_types::point2i point) = 0;

    virtual void Mark(const ra_types::rgb888  code,
                      const ra_types::point2i start, ra_types::point2i end) = 0;

    virtual std::unique_ptr<std::vector<ra_types::rgb888>> CreateCopy()
        const = 0;

    ra_types::n0_t getTotalElementsDrawn() const { return total; };

protected:
    ra_types::rgb888 activeColor;
    ra_types::n0_t   total;
};

} // namespace ra_core::pipeline

#endif // DRAWTARGETINTERFACE_H
