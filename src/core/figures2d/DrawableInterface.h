#ifndef DRAWABLEINTERFACE_H
#define DRAWABLEINTERFACE_H

#include "Figure2dVisitor.h"
#include "border.h"
#include "rgb888.h"
#include "typedefs.h"

namespace ra_core::figures2d
{
using namespace ra_types;
class DrawableInterface
{
public:
    virtual ~DrawableInterface() {}
    virtual displacement1i_t getMaxX() const = 0;
    virtual displacement1i_t getMaxY() const = 0;
    virtual displacement1i_t getMinX() const = 0;
    virtual displacement1i_t getMinY() const = 0;

    virtual const Rgb888& GetColorCode() const     = 0;
    virtual void          setColorCode(Rgb888 rgb) = 0;

    virtual const border& GetBorder() const        = 0;
    virtual void          SetBorder(border border) = 0;

    virtual void AcceptFigure2dVisitor(Figure2dVisitor* fv) const = 0;
};

} // namespace ra_core::figures2d

#endif // DRAWABLEINTERFACE_H
