#include "CircuitBase.h"
namespace ra_core::figures2d
{
CircuitBase::CircuitBase(struct border border)
{
    this->border = border;
}

CircuitBase::~CircuitBase() {}

const rgb888& CircuitBase::GetColor() const
{
    return this->border.color;
}

void CircuitBase::SetColor(rgb888 rgb)
{
    this->border.color = rgb;
}

const border& CircuitBase::GetBorder() const
{
    return this->border;
}

void CircuitBase::SetBorder(struct border border)
{
    this->border = border;
}

} // namespace ra_core::figures2d
