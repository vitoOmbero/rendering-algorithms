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

    inline displacement_t GetMaxX() const override { return getX(); };
    inline displacement_t GetMaxY() const override { return getY(); };
    inline displacement_t GetMinX() const override { return getX(); };
    inline displacement_t GetMinY() const override { return getY(); };

    displacement_t getX() const;
    displacement_t getY() const;
    void           SetX(displacement_t x);
    void           SetY(displacement_t y);

    void AcceptFigure2dVisitor(Figure2dVisitor* fv) const override;

private:
    displacement_t x;
    displacement_t y;
};
} // namespace ra_core::figures2d
#endif // DOT_H
