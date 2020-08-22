#ifndef CANVAS2DVIEWERINTERFACE_H
#define CANVAS2DVIEWERINTERFACE_H

#include <string>

#include "RectangularPixelBuffer.h"

class Canvas2dViewerInterface
{
public:
    virtual void ViewResult(const ra_core::canvas2d::RectangularPixelBuffer& pb,
                            const std::string_view description) const = 0;
};

#endif // CANVAS2DVIEWERINTERFACE_H
