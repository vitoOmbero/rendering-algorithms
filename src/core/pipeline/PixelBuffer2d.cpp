#include "PixelBuffer2d.h"

#include <algorithm>

#include "ra_get_string.h"

namespace ra_core::pipeline
{

typedef std::vector<ra_types::rgb888> line_t;

PixelBuffer2d::PixelBuffer2d(
    const ra_types::Space2i&                                  spaceRef,
    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& ctsRef,
    ra_types::rgb888 default_color_code)
    : name{ "RectangularPixelBuffer" }
    , spaceRef{ spaceRef }
    , ctsRef{ ctsRef }
{

    auto vline =
        std::vector<ra_types::rgb888>(spaceRef.viewWidth, default_color_code);

    vector2d_ptr = new std::vector<line_t>(spaceRef.viewHeight, vline);
    vector2d_ptr->shrink_to_fit();
}

PixelBuffer2d::~PixelBuffer2d()
{
    delete vector2d_ptr;
}

std::string PixelBuffer2d::getName() const
{
    return this->name;
}

void PixelBuffer2d::Mark(const ra_types::rgb888  code,
                         const ra_types::point2i point)
{
    auto p                    = ctsRef.TranslateCanvasToPixelBuffer(point);
    (*vector2d_ptr)[p.y][p.x] = code;
}

void PixelBuffer2d::Mark(const ra_types::rgb888  code,
                         const ra_types::point2i start,
                         const ra_types::point2i end)
{
    for (auto y = start.y; y <= end.y; ++y)
    {
        for (auto x = start.x; x <= end.x; ++x)
        {
            auto i = ctsRef.TranslateCanvasToPixelBuffer({ x, y });
            (*vector2d_ptr)[i.y][i.x] = code;
        }
    }
}

ra_types::rgb888 PixelBuffer2d::getColorCode(const ra_types::point2i point)
{
    auto p = ctsRef.TranslateCanvasToPixelBuffer(point);
    return (*vector2d_ptr)[p.y][p.x];
}

std::unique_ptr<std::vector<ra_types::rgb888>> PixelBuffer2d::CreateCopy() const
{
    std::vector<ra_types::rgb888>* v = new std::vector<ra_types::rgb888>(
        spaceRef.viewWidth * spaceRef.viewHeight);
    v->shrink_to_fit();

    ra_types::distance1ui_t i = 0;
    for (auto oe = v->begin(); oe != v->end(); oe += spaceRef.viewWidth)
    {
        auto cb = (*vector2d_ptr)[i].cbegin();
        auto ce = (*vector2d_ptr)[i].cend();

        std::copy(cb, ce, oe);
        ++i;
    }

    std::unique_ptr<std::vector<ra_types::rgb888>> ptr(v);
    return ptr;
}

} // namespace ra_core::pipeline
