#include <algorithm>

#include "PpxCanvas2dViewer.h"
#include "imgfile.hpp"

PpxCanvas2dViewer::PpxCanvas2dViewer() {}

PpxCanvas2dViewer::~PpxCanvas2dViewer() {}

void PpxCanvas2dViewer::ViewResult(
    const ra_core::canvas2d::RectangularPixelBuffer& pb,
    const std::string_view                           description) const
{
    std::string          name(description);
    data_export::imgFile ppx(name);

    auto pixv = *pb.StumpBufferCopy(800, 600);

    // ra_types::rgb888* pixarr = &(*pixv)[0];

    std::array<ra_types::rgb888, 800 * 600> arr;

    std::move(pixv.begin(), pixv.end(), arr.begin());

    pixv.erase(pixv.begin(), pixv.end());

    ppx.save_p6(arr, 800, 600);

    std::cout << "PpxCanvas2dViewer: " << name << ".ppx is ready." << std::endl;
}
