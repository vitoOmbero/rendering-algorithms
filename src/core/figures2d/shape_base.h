#ifndef SHAPEBASE_H
#define SHAPEBASE_H

#include "drawable_interface.h"
#include "border.h"
#include "rgb888.h"
#include "utility"
namespace ra_core::figures2d
{

class ShapeBase : public DrawableInterface
{
public:
    ~ShapeBase() override;

    [[nodiscard]] const Rgb888& getColorCode() const override;
    void          setColorCode(Rgb888 rgb) override;

    [[nodiscard]] const border& getBorder() const override;
    void          setBorder(border border) override;

protected:
    border* border_ptr_;
    Rgb888  color_code_;
};
} // namespace ra_core::figures2d
#endif // SHAPEBASE_H
