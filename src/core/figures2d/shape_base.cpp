#include "shape_base.h"
namespace ra_core::figures2d
{
ShapeBase::~ShapeBase()
{
    delete border_ptr_;
}

const Rgb888& ShapeBase::getColorCode() const
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

const border& ShapeBase::getBorder() const
{
    // TODO: borders for figures settings controller?
    static border default_borer;
    if (border_ptr_ != nullptr)
        return *border_ptr_;
    return default_borer;
}

// TODO: remove heap allocation for each object (nowhere to place right now)
void ShapeBase::setBorder(border border)
{
    border_ptr_ = new struct border(border);
}
} // namespace ra_core::figures2d
