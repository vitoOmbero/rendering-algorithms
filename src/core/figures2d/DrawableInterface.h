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
    virtual displacement_t GetMaxX() const = 0;
    virtual displacement_t GetMaxY() const = 0;
    virtual displacement_t GetMinX() const = 0;
    virtual displacement_t GetMinY() const = 0;

    virtual const rgb888& GetColor() const     = 0;
    virtual void          SetColor(rgb888 rgb) = 0;

    virtual const border& GetBorder() const        = 0;
    virtual void          SetBorder(border border) = 0;

    virtual void AcceptFigure2dVisitor(Figure2dVisitor* fv) const = 0;
};

} // namespace ra_core::figures2d

#endif // DRAWABLEINTERFACE_H
