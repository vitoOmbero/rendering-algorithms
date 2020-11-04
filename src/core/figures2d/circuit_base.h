#ifndef CURCUITBASE_H
#define CURCUITBASE_H

#include "drawable_interface.h"
#include "border.h"
#include "rgb888.h"

namespace ra_core::figures2d
{
class CircuitBase : public DrawableInterface
{
public:
    ~CircuitBase() override;

    [[nodiscard]] const Rgb888& getColorCode() const override;
    void          setColorCode(Rgb888 rgb) override;

    [[nodiscard]] const border& getBorder() const override;
    void          setBorder(border border) override;

protected:
    explicit CircuitBase(border border);

    border border_;
};
} // namespace ra_core::figures2d
#endif // CURCUITBASE_H
