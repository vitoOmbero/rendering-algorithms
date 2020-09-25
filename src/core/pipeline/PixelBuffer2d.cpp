#include "PixelBuffer2d.h"

#include <algorithm>

#include "ra_get_string.h"

namespace ra_core::pipeline
{

typedef std::vector<ra_types::Rgb888> line_t;

PixelBuffer2d::PixelBuffer2d(
    const ra_types::Space2i&                                  space,
    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& cts,
    ra_types::Rgb888 default_color_code)
    : name_{ "RectangularPixelBuffer" }
    , space_{ space }
    , cts_{ cts }
{

    auto vline =
        std::vector<ra_types::Rgb888>(space.viewWidth, default_color_code);

    vector2d_ptr_ = new std::vector<line_t>(space.viewHeight, vline);
    vector2d_ptr_->shrink_to_fit();
}

PixelBuffer2d::~PixelBuffer2d()
{
    delete vector2d_ptr_;
}

std::string PixelBuffer2d::getName() const
{
    return this->name_;
}

void PixelBuffer2d::Mark(const ra_types::Rgb888  code,
                         const ra_types::Point2i point)
{
    auto p                     = cts_.TranslateCanvasToPixelBuffer(point);
    (*vector2d_ptr_)[p.y][p.x] = code;
}

void PixelBuffer2d::Mark(const ra_types::Rgb888  code,
                         const ra_types::Point2i start,
                         const ra_types::Point2i end)
{
    for (auto y = start.y; y <= end.y; ++y)
    {
        for (auto x = start.x; x <= end.x; ++x)
        {
            auto i = cts_.TranslateCanvasToPixelBuffer({ x, y });
            (*vector2d_ptr_)[i.y][i.x] = code;
        }
    }
}

ra_types::Rgb888 PixelBuffer2d::getColorCode(const ra_types::Point2i point)
{
    auto p = cts_.TranslateCanvasToPixelBuffer(point);
    return (*vector2d_ptr_)[p.y][p.x];
}

std::unique_ptr<std::vector<ra_types::Rgb888>> PixelBuffer2d::CreateCopy() const
{
    std::vector<ra_types::Rgb888>* v =
        new std::vector<ra_types::Rgb888>(space_.viewWidth * space_.viewHeight);
    v->shrink_to_fit();

    ra_types::distance1ui_t i = 0;
    for (auto oe = v->begin(); oe != v->end(); oe += space_.viewWidth)
    {
        auto cb = (*vector2d_ptr_)[i].cbegin();
        auto ce = (*vector2d_ptr_)[i].cend();

        std::copy(cb, ce, oe);
        ++i;
    }

    std::unique_ptr<std::vector<ra_types::Rgb888>> ptr(v);
    return ptr;
}

} // namespace ra_core::pipeline
