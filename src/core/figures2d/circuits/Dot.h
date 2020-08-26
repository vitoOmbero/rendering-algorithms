#ifndef DOT_H
#define DOT_H

#include "CircuitBase.h"
#include "border.h"
#include "point2d.h"
#include "typedefs.h"

namespace ra_core::figures2d
{

class Dot final : public CircuitBase
{
public:
    Dot(displacement_t x, displacement_t y, struct border border);
    Dot(point2d p, struct border border);

    inline displacement_t getMaxX() const override { return getX(); };
    inline displacement_t getMaxY() const override { return getY(); };
    inline displacement_t getMinX() const override { return getX(); };
    inline displacement_t getMinY() const override { return getY(); };

    displacement_t getX() const;
    displacement_t getY() const;
    void           setX(displacement_t x);
    void           setY(displacement_t y);
    point2d        getPoint() const;

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

private:
    displacement_t x;
    displacement_t y;
};
} // namespace ra_core::figures2d
#endif // DOT_H
