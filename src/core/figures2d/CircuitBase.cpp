#include "CircuitBase.h"
namespace ra_core::figures2d
{
CircuitBase::CircuitBase(struct border border)
{
    this->border_ = border;
}

CircuitBase::~CircuitBase() {}

const Rgb888& CircuitBase::GetColorCode() const
{
    return this->border_.color_code;
}

void CircuitBase::setColorCode(Rgb888 rgb)
{
    this->border_.color_code = rgb;
}

const border& CircuitBase::GetBorder() const
{
    return this->border_;
}

void CircuitBase::SetBorder(struct border border)
{
    this->border_ = border;
}

} // namespace ra_core::figures2d
