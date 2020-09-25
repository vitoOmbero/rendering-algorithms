#ifndef CIRCLE_H
#define CIRCLE_H
#include "CircuitBase.h"
#include "border.h"
#include "point2i.h"
#include "typedefs.h"

namespace ra_core::figures2d
{

class Circle final : public CircuitBase
{
public:
    Circle(ra_types::Point2i center_, distance1ui_t radius_,
           struct border border);
    Circle(ra_types::Point2i center_, ra_types::Point2i point,
           struct border border);

    inline displacement1i_t getMaxX() const override
    {
        return (center_ + radius_).x;
    };
    inline displacement1i_t getMaxY() const override
    {
        return (center_ + radius_).y;
    };
    inline displacement1i_t getMinX() const override
    {
        return (center_ - radius_).x;
    };
    inline displacement1i_t getMinY() const override
    {
        return (center_ - radius_).y;
    };

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

    ra_types::Point2i getCenter() const;
    void              setCenter(const ra_types::Point2i& value);

    distance1ui_t getRadius() const;
    void       setRadius(const distance1ui_t& value);

private:
    ra_types::Point2i center_;
    distance1ui_t     radius_;
};
} // namespace ra_core::figures2d
#endif // CIRCLE_H
