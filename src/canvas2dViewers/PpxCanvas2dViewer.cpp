#include "PpxCanvas2dViewer.h"

PpxCanvas2dViewer::PpxCanvas2dViewer()
{
    
}

PpxCanvas2dViewer::~PpxCanvas2dViewer() {}

void PpxCanvas2dViewer::ViewResult(
    const ra_core::canvas2d::RectangularPixelBuffer& pb,
    const std::string_view                           description) const
{
    std::string_view d = description;
    d                  = "";
    pb.Foo();
}
