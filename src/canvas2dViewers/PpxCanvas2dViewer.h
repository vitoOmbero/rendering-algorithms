#ifndef PPXCANVAS2DVIEWER_H
#define PPXCANVAS2DVIEWER_H

#include <iostream>
#include <string>

#include "Canvas2dViewerInterface.h"

/**
 * @brief The PpxCanvas2dViewer class - generate PPM image
 * (<https://ru.wikipedia.org/wiki/Portable_anymap>)
 */
class PpxCanvas2dViewer : public Canvas2dViewerInterface
{

public:
    PpxCanvas2dViewer();
    ~PpxCanvas2dViewer();

    void ViewResult(const ra_core::canvas2d::RectangularPixelBuffer& pb,
                    const std::string_view description) const override;
};

#endif // PPXCANVAS2DVIEWER_H
