#include "DotLinearBuffer2d.h"

namespace ra_core::pipeline
{

const ra_types::Space1i &DotLinearBuffer2d::getSpaceRef() const
{
    return spaceRef;
}

ra_types::n0_t DotLinearBuffer2d::getLineWidth() const
{
    return lineWidth;
}

DotLinearBuffer2d::DotLinearBuffer2d(
    const ra_types::Space1i&                                  spaceRef,
    const ra_core::pipeline::SpaceCoordinateTranslatorSimple& ctsRef,
    ra_types::n0_t lineWidth, ra_types::rgb888 default_color_code)
    : spaceRef{ spaceRef }
    , ctsRef{ ctsRef }
    , lineWidth{ lineWidth }

{
    dots = new std::vector<ra_types::rgb888>(spaceRef.viewLength,
                                             default_color_code);
}

DotLinearBuffer2d::~DotLinearBuffer2d()
{
    delete dots;
}

void DotLinearBuffer2d::Mark(const ra_types::rgb888  code,
                             const ra_types::point2i point)
{
    auto i      = ctsRef.TranslateCanvasToDotBuffer(point, lineWidth);
    dots->at(i) = code;
}

void DotLinearBuffer2d::Mark(const ra_types::rgb888  code,
                             const ra_types::point2i start,
                             const ra_types::point2i end)
{
    auto ist = ctsRef.TranslateCanvasToDotBuffer(start, lineWidth);
    auto ind = ctsRef.TranslateCanvasToDotBuffer(end, lineWidth);
    for (auto i = ist; i <= ind; ++i)
    {
        dots->at(i) = code;
    }
}

std::unique_ptr<std::vector<ra_types::rgb888>>
DotLinearBuffer2d::CreateCopy() const
{
    std::vector<ra_types::rgb888>* v = new std::vector<ra_types::rgb888>(*dots);
    std::unique_ptr<std::vector<ra_types::rgb888>> ptr(v);
    return ptr;
}

ra_types::n0_t DotLinearBuffer2d::getLastIndex() const
{
    return spaceRef.viewLength - 1;
}

ra_types::n0_t DotLinearBuffer2d::getZeroPointIndex() const
{
    return std::abs(spaceRef.viewZeroPointOffset);
}

} // namespace ra_core::canvas2d
