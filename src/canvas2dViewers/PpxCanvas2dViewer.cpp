#include <algorithm>

#include "PpxCanvas2dViewer.h"
#include "imgfile.hpp"
#include "renderer.h"

PpxCanvas2dViewer::PpxCanvas2dViewer() {}

PpxCanvas2dViewer::~PpxCanvas2dViewer() {}

void PpxCanvas2dViewer::ViewResult(const ra_core::pipeline::Canvas2d& canvas,
                                   const std::string_view description) const
{
    std::string          name(description);
    data_export::imgFile ppx(name);

    auto pixv = canvas.getImage();

    std::array<ra_types::rgb888, ra_core::renderer::CANVAS_WIDTH_DT *
                                     ra_core::renderer::CANVAS_HEIGHT_DT>
        arr;

    std::move(pixv.begin(), pixv.end(), arr.begin());

    ppx.save_p6(arr, ra_core::renderer::CANVAS_WIDTH_DT,
                ra_core::renderer::CANVAS_HEIGHT_DT);

    std::cout << "  === PpxCanvas2dViewer: " << name << ".ppx is ready."
              << std::endl;
}
