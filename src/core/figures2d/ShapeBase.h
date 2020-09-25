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

    virtual const Rgb888& GetColorCode() const override;
    virtual void          setColorCode(Rgb888 rgb) override;

    virtual const border& GetBorder() const override;
    virtual void          SetBorder(border border) override;

protected:
    border* border_ptr_;
    Rgb888  color_code_;
};
} // namespace ra_core::figures2d
#endif // SHAPEBASE_H
