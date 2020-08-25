#ifndef CURCUITBASE_H
#define CURCUITBASE_H

#include "DrawableInterface.h"
#include "border.h"
#include "rgb888.h"

namespace ra_core::figures2d
{
class CircuitBase : public DrawableInterface
{
public:
    virtual ~CircuitBase();

    virtual const rgb888& GetColorCode() const override;
    virtual void          SetColor(rgb888 rgb) override;

    virtual const border& GetBorder() const override;
    virtual void          SetBorder(border border) override;

protected:
    CircuitBase(border border);

    border border;
};
} // namespace ra_core::figures2d
#endif // CURCUITBASE_H
