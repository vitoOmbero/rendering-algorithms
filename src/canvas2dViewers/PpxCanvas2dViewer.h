#ifndef PPXCANVAS2DVIEWER_H
#define PPXCANVAS2DVIEWER_H

#include "Canvas2dViewerInterface.h"

class PpxCanvas2dViewer : public Canvas2dViewerInterface
{
public:
    PpxCanvas2dViewer();

    void ViewResult(PixelBuffer& pb) override;
};

#endif // PPXCANVAS2DVIEWER_H
