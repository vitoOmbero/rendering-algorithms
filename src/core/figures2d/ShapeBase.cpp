#include "ShapeBase.h"
namespace ra_core::figures2d
{
ShapeBase::~ShapeBase()
{
    delete border_ptr_;
}

const Rgb888& ShapeBase::GetColorCode() const
{
    return this->color_code_;
}

void ShapeBase::setColorCode(Rgb888 rgb)
{
    this->color_code_ = rgb;
    if (border_ptr_ != nullptr)
    {
        border_ptr_->color_code = rgb;
    }
}

const border& ShapeBase::GetBorder() const
{
    if (border_ptr_ != nullptr)
        return *border_ptr_;
    return std::move(border());
}

// TODO: remove heap allocation for each object (nowhere to place right now)
void ShapeBase::SetBorder(border border)
{
    border_ptr_ = new struct border(std::move(border));
}
} // namespace ra_core::figures2d
