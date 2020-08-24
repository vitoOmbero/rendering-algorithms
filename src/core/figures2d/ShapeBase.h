#ifndef SHAPEBASE_H
#define SHAPEBASE_H

#include "DrawableInterface.h"
#include "border.h"
#include "rgb888.h"
#include "utility"
namespace ra_core::figures2d
{

class ShapeBase : public DrawableInterface
{
public:
    virtual ~ShapeBase();

    virtual const rgb888& GetColor() const override;
    virtual void          SetColor(rgb888 rgb) override;

    virtual const border& GetBorder() const override;
    virtual void          SetBorder(border border) override;

protected:
    border* border_ptr;
    rgb888  color_code;
};
} // namespace ra_core::figures2d
#endif // SHAPEBASE_H
