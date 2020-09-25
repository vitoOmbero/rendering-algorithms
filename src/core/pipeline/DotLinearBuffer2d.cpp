#include "DotLinearBuffer2d.h"

namespace ra_core::pipeline
{

const ra_types::Space1i &DotLinearBuffer2d::getSpaceRef() const
{
    return space_;
}

ra_types::n0_t DotLinearBuffer2d::getLineWidth() const
{
    return line_width_;
}

DotLinearBuffer2d::DotLinearBuffer2d(
    const ra_types::Space1i&                                  space,
    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& cts,
    ra_types::n0_t lineWidth, ra_types::Rgb888 default_color_code)
    : space_{ space }
    , cts_{ cts }
    , line_width_{ lineWidth }

{
    dots_ptr_ =
        new std::vector<ra_types::Rgb888>(space.viewLength, default_color_code);
}

DotLinearBuffer2d::~DotLinearBuffer2d()
{
    delete dots_ptr_;
}

void DotLinearBuffer2d::Mark(const ra_types::Rgb888  code,
                             const ra_types::Point2i point)
{
    auto i      = cts_.TranslateCanvasToDotBuffer(point, line_width_);
    dots_ptr_->at(i) = code;
}

void DotLinearBuffer2d::Mark(const ra_types::Rgb888  code,
                             const ra_types::Point2i start,
                             const ra_types::Point2i end)
{
    auto ist = cts_.TranslateCanvasToDotBuffer(start, line_width_);
    auto ind = cts_.TranslateCanvasToDotBuffer(end, line_width_);
    for (auto i = ist; i <= ind; ++i)
    {
        dots_ptr_->at(i) = code;
    }
}

ra_types::Rgb888 DotLinearBuffer2d::getColorCode(const ra_types::Point2i point)
{
    auto i = cts_.TranslateCanvasToDotBuffer(point, line_width_);
    return dots_ptr_->at(i);
}

std::unique_ptr<std::vector<ra_types::Rgb888>>
DotLinearBuffer2d::CreateCopy() const
{
    std::vector<ra_types::Rgb888>* v = new std::vector<ra_types::Rgb888>(*dots_ptr_);
    std::unique_ptr<std::vector<ra_types::Rgb888>> ptr(v);
    return ptr;
}

ra_types::n0_t DotLinearBuffer2d::getLastIndex() const
{
    return space_.viewLength - 1;
}

ra_types::n0_t DotLinearBuffer2d::getZeroPointIndex() const
{
    return std::abs(space_.viewZeroPointOffset);
}

} // namespace ra_core::canvas2d
