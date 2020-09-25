#ifndef DOT_H
#define DOT_H

#include "CircuitBase.h"
#include "border.h"
#include "point2i.h"
#include "typedefs.h"

namespace ra_core::figures2d
{

class Dot final : public CircuitBase
{
public:
    Dot(displacement1i_t x_, displacement1i_t y_, struct border border);
    Dot(ra_types::Point2i p, struct border border);

    inline displacement1i_t getMaxX() const override { return getX(); };
    inline displacement1i_t getMaxY() const override { return getY(); };
    inline displacement1i_t getMinX() const override { return getX(); };
    inline displacement1i_t getMinY() const override { return getY(); };

    displacement1i_t getX() const;
    displacement1i_t getY() const;
    void              setX(displacement1i_t x_);
    void              setY(displacement1i_t y_);
    ra_types::Point2i getPoint() const;

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

private:
    displacement1i_t x_;
    displacement1i_t y_;
};
} // namespace ra_core::figures2d
#endif // DOT_H
