#ifndef DRAWABLEINTERFACE_H
#define DRAWABLEINTERFACE_H

#include "figure2d_visitor.h"
#include "border.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::figures2d
{
using namespace ra_types;
class DrawableInterface
{
public:
    virtual ~DrawableInterface() = default;
    [[nodiscard]] virtual displacement1i_t getMaxX() const = 0;
    [[nodiscard]] virtual displacement1i_t getMaxY() const = 0;
    [[nodiscard]] virtual displacement1i_t getMinX() const = 0;
    [[nodiscard]] virtual displacement1i_t getMinY() const = 0;

    [[nodiscard]] virtual const Rgb888& getColorCode() const     = 0;
    virtual void          setColorCode(Rgb888 rgb) = 0;

    [[nodiscard]] virtual const border& getBorder() const        = 0;
    virtual void          setBorder(border border) = 0;

    virtual void AcceptFigure2dVisitor(Figure2dVisitor* fv) const = 0;
};

} // namespace ra_core::figures2d

#endif // DRAWABLEINTERFACE_H
