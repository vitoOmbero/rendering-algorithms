#include "ShapeBase.h"
namespace ra_core::figures2d
{
ShapeBase::~ShapeBase()
{
    delete border_ptr;
}

const rgb888& ShapeBase::GetColorCode() const
{
    return this->color_code;
}

void ShapeBase::SetColor(rgb888 rgb)
{
    this->color_code = rgb;
    if (border_ptr != nullptr)
    {
        border_ptr->color_code = rgb;
    }
}

const border& ShapeBase::GetBorder() const
{
    if (border_ptr != nullptr)
        return *border_ptr;
    return std::move(border());
}

void ShapeBase::SetBorder(border border)
{
    border_ptr = new struct border(std::move(border));
}
} // namespace ra_core::figures2d
