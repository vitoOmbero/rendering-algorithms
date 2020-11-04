#include "circuit_base.h"
namespace ra_core::figures2d
{
CircuitBase::CircuitBase(struct border border)
{
    this->border_ = border;
}

CircuitBase::~CircuitBase() {}

const Rgb888& CircuitBase::getColorCode() const
{
    return this->border_.color_code;
}

void CircuitBase::setColorCode(Rgb888 rgb)
{
    this->border_.color_code = rgb;
}

const border& CircuitBase::getBorder() const
{
    return this->border_;
}

void CircuitBase::setBorder(struct border border)
{
    this->border_ = border;
}

} // namespace ra_core::figures2d
